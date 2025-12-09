import argparse
import concurrent.futures
import datetime
import multiprocessing
import os
import subprocess
import sys
import time
from pathlib import Path

import pandas as pd
import psutil

def parse_solver_output(output_text):
    data = {}
    for line in output_text.strip().split('\n'):
        if ':' in line:
            key, val = line.split(':', 1)
            val = val.strip()
            try:
                data[key.strip()] = float(val) if '.' in val else int(val)
            except ValueError:
                data[key.strip()] = val
    return data
def process_instance(problem_type: str, file_path: str, upper_bound=None, time_limit: int = None,
                     queue: multiprocessing.Queue = None, use_incremental_solving: bool = False):
    """
    Process a single instance of the given path.
    """
    print(f"Solving {file_path}")
    stats = None
    if problem_type == 'BCP':
        try:
            command = ["./bcp", f"{file_path}"]

            if upper_bound:
                command.append("-ub")
                command.append(str(upper_bound))

            if time_limit:
                command.append("-t")
                command.append(str(time_limit))

            if use_incremental_solving:
                command.append("-i")

            result = subprocess.run(
                command,
                capture_output=True,
                text=True,
                check=True
            )

            stats = parse_solver_output(result.stdout)

        except subprocess.CalledProcessError as e:
            print(f"Command failed with return code {e.returncode}")
            print(f"Error message: {e.stderr}")
            exit(1)

    elif problem_type == 'BMCP':
        raise NotImplementedError()

    if stats['status'] == -1:
        stats['status'] = 'UNKNOWN'
    elif stats['status'] == 0:
        stats['status'] = 'UNSATISFIABLE'
    elif stats['status'] == 1:
        stats['status'] = 'SATISFIABLE'
    elif stats['status'] == 2:
        stats['status'] = 'OPTIMAL'

    queue.put(stats)

def worker(args):
    if len(args) == 4:
        problem_type, file_path, time_limit, use_incremental_solving = args
        upper_bound = None
    else:
        problem_type, file_path, upper_bound, time_limit, use_incremental_solving = args

    queue = multiprocessing.Queue()
    p = multiprocessing.Process(target=process_instance, kwargs={'problem_type': problem_type,
                                                                 'file_path': file_path,
                                                                 'upper_bound': upper_bound,
                                                                 'time_limit': time_limit,
                                                                 'queue': queue,
                                                                 'use_incremental_solving': use_incremental_solving})
    p.start()

    peak_memory = 0
    while p.is_alive():
        try:
            proc = psutil.Process(p.pid)
            mem = proc.memory_info().rss
            for child in proc.children(recursive=True):
                try:
                    mem += child.memory_info().rss
                except psutil.NoSuchProcess:
                    continue
            peak_memory = max(peak_memory, mem)
        except psutil.NoSuchProcess:
            break
        time.sleep(0.1)

    p.join()

    if p.exitcode != 0:
        raise RuntimeError(f"Process for {file_path} failed with exit code {p.exitcode}")

    p.terminate()
    instance_stats = queue.get()
    instance_stats['name'] = file_path.split('/')[-1]
    instance_stats['memory_usage'] = round(peak_memory / (1024 ** 2), 5)
    return instance_stats


def benchmark(problem_type: str, time_limit: int = None, continue_from: str = None,
              num_concurrent_processes: int = 1, save_interval_seconds: int = 60,
              use_predefine_upper_bound: bool = False, use_incremental_solving: bool = False):
    """
    Benchmark a dataset using concurrent.futures.ProcessPoolExecutor.
    Periodically exports partial results to avoid data loss from unexpected interruptions.
    """
    # Load existing progress if continuing
    if continue_from is None:
        dataset_stats = pd.DataFrame(columns=[
            'name', 'V', 'E', 'upper_bound', 'variables', 'clauses',
            'status', 'span', 'encoding_time', 'total_solving_time', 'time_used', 'memory_usage'
        ])
    else:
        dataset_stats = pd.read_csv(continue_from)

    tasks = []

    if use_predefine_upper_bound:
        bound = pd.read_csv(f'./bound/bound_{problem_type}.csv')
        for row in bound.itertuples():
            if row.name in dataset_stats['name'].values:
                continue

            tasks.append((
                problem_type,
                f'./dataset/{row.name}',
                row.upper_bound,
                time_limit,
                use_incremental_solving
            ))
    else:
        folder_path = Path(f"./dataset")
        files = [file.name for file in folder_path.iterdir() if file.is_file()]

        for file in files:
            if file in dataset_stats['name'].values:
                continue
            tasks.append((problem_type, f'{folder_path}/{file}', time_limit, use_incremental_solving))

    executor = concurrent.futures.ProcessPoolExecutor(max_workers=num_concurrent_processes)
    futures = []

    last_save_time = time.time()  # track time of last save

    try:
        for task in tasks:
            futures.append(executor.submit(worker, task))

        for future in concurrent.futures.as_completed(futures):
            try:
                result = future.result()
                result.pop('file_path', None)
                dataset_stats = pd.concat([dataset_stats, pd.DataFrame([result])],
                                          ignore_index=True)

                # Periodically save partial results
                current_time = time.time()
                if current_time - last_save_time >= save_interval_seconds:
                    export_result(problem_type, dataset_stats, suffix="partial")
                    last_save_time = current_time

            except Exception:
                for f in futures:
                    f.cancel()
                executor.shutdown(wait=False, cancel_futures=True)
                export_result(problem_type, dataset_stats, suffix="crash")
                sys.exit(1)

    except KeyboardInterrupt:
        for f in futures:
            f.cancel()
        executor.shutdown(wait=False, cancel_futures=True)
        export_result(problem_type, dataset_stats, suffix="interrupted")
        sys.exit(1)

    # Final export at the end
    export_result(problem_type, dataset_stats)


def export_result(problem_type: str, stat, suffix=None):
    """
    Export both detailed results and summary reports.
    `suffix` is appended to the filename to indicate partial or crash saves.
    """
    os.makedirs('./result', exist_ok=True)
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
    suffix = f"_{suffix}" if suffix else ""

    result_path = f'./result/{problem_type}{suffix}_{timestamp}.csv'
    report_path = f'./result/report_{problem_type}{suffix}_{timestamp}.csv'

    stat.to_csv(result_path, index=False)

    report = pd.DataFrame([{
        'UNSATISFIABLE': stat['status'].str.fullmatch('UNSATISFIABLE').sum(),
        'SATISFIABLE': stat['status'].str.fullmatch('SATISFIABLE').sum(),
        'OPTIMAL': stat['status'].str.fullmatch('OPTIMAL').sum(),
        'UNKNOWN': stat['status'].str.fullmatch('UNKNOWN').sum(),
        'average_encoding_time': stat['encoding_time'].mean(),
        "max_encoding_time": stat['encoding_time'].max(),
        "min_encoding_time": stat['encoding_time'].min(),
        "average_solving_time": stat['total_solving_time'].mean(),
        "max_solving_time": stat['total_solving_time'].max(),
        "min_solving_time": stat['total_solving_time'].min(),
        "average_memory_usage": stat['memory_usage'].mean(),
        "max_memory_usage": stat['memory_usage'].max(),
        "min_memory_usage": stat['memory_usage'].min(),
        "max_time_used": stat['time_used'].max(),
        "min_time_used": stat['time_used'].min(),
        "average_time_used": stat['time_used'].mean()
    }])
    report.T.reset_index().to_csv(report_path, index=False)


def main():
    parser = argparse.ArgumentParser(description='Benchmarking script for BCP solver.')
    parser.add_argument('problem_type', type=str, choices=['BCP', 'BMCP'], )
    parser.add_argument('--time_limit', type=int, help='Time limit for solving one instance.',
                        default=None)
    parser.add_argument('--continue_from', type=str, help='Result file name to continue from.',
                        default=None)
    parser.add_argument('--num_concurrent_processes', type=int, default=1,
                        help='Number of concurrent processes to use for benchmarking.')
    parser.add_argument('--save_interval_seconds', type=int, default=300,
                        help='Interval (in seconds) between periodic partial result exports. Default is 300 seconds.')
    parser.add_argument('--use_predefined_upper_bound', action='store_true',
                        help='Use predefined upper bounds from the bound files.')
    parser.add_argument('--use_incremental_solving', action='store_true', default=False,
                        help='Use incremental solving strategy (if applicable).')

    args = parser.parse_args()

    benchmark(args.problem_type, args.time_limit, args.continue_from,
              args.num_concurrent_processes, args.save_interval_seconds, args.use_predefined_upper_bound,
              args.use_incremental_solving)


if __name__ == "__main__":
    main()
