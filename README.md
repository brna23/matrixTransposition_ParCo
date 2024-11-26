# Parallel Programming Project: Matrix Transposition
## Student: Mattia Bernabè

This project is about transposing a matrix of variable size using three distinct approaches and study the execution time.

## Project Goal

The goal of this project is to implement a method to transpose a square matrix of variable size, using three approaches:

1. **Serial Execution**: A method that performs the transposition sequentially.
2. **Implicit Execution (Using Compiler Options)**: An approach that leverages compiler optimizations to improve performance.
3. **Parallel Execution with OpenMP (OMP)**: A parallel approach that uses OpenMP to accelerate the transposition process by utilizing multiple threads.

## Repository Contents

This repository contains the following files:

- **Source Code**:
  - `serial.cpp`: Code to perform the transposition serially.
  - `implicit.cpp`: Code to perform the transposition using compiler optimizations.
  - `parallel.cpp`: Code to perform the transposition using OpenMP.

- **Graphing**:
  - `Graphs.ipynb`: Python code to generate performance graphs based on the results from different methods.

- **CSV Data**:
  - `Execution_data/output.csv`: CSV file containing raw data about time execution of the differen programs.
  - `Execution_data/processed_execution_data.csv`: CSV file containing the processed data with average, speedup and efficiency

## Requirements

To run this project, you will need the following tools:

- A C/C++ compiler (such as GCC or Clang).
- Python (for generating the graphs).
- OpenMP support in the compiler (if not already enabled).

## How to Compile and Run the Code
In the source code folder is present the basah file that allow to submit the job in the cluster.
In alternative there are the lines to compile the different file .cpp: 

**Serial**: ```g++ -o serial serial.cpp -fopenmp```
**Parallel (Implicit)**: ```g++ -o implicit implicit.cpp -fopenmp -O2```
**Parallel (OMP)**: ```g++ -o serial serial.cpp -fopenmp```
