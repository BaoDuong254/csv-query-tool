# Week 1 Report

In Week 1, the primary goals were to implement the Command-Line Interface (CLI) and SQL Lexer for the project. Below is a summary of the work completed during this week.

## Command-Line Interface

Successfully developed a basic command-line tool named `exql` that allows users to execute SQL queries directly from the terminal. The tool can accept SQL queries as input and display them as output.

### Example Usage
Compile program:
```sh
g++ exql.cpp main.cpp -o exql
```
Running the command:
```sh
./exql "SELECT id, name FROM users;"
