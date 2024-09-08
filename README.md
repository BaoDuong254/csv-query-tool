# Week 1 Report

In Week 1, the primary goals were to implement the Command-Line Interface (CLI) and SQL Lexer for the project. Below is a summary of the work completed during this week.

## Command-Line Interface

Successfully developed a basic command-line tool named `exql` that allows users to execute SQL queries directly from the terminal. The tool can accept SQL queries as input and display them as output.

## Example Usage
Compile program:
```sh
g++ exql.cpp main.cpp -o exql
```
Running the command:
```sh
./exql "SELECT id, name FROM users;"
```

# Week 2 & 3 Report
In week 2 & 3, the goal is to build a SQL parser that transforms a stream of tokens into an Abstract Syntax Tree (AST), representing the structure of SQL queries in a meaningful way.
## Progress
### Completed:
- **AST Definition**: Implemented the core classes for SQL statements and expressions.
### In Progress:
- **Parser Methods**: Developed methods for parsing SQL statements and expressions.
- **Basic Error Handling**: Set up an error-handling framework to catch and report parsing issues.
## Example Usage
Compile program:
```sh
g++ ast.cpp exql.cpp -o ast
```
Running the command:
```sh
./ast "SELECT id, name FROM users;"
```