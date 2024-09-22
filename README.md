# Report

## Week 1

In Week 1, the primary goals were to implement the Command-Line Interface (CLI) and SQL Lexer for the project. Below is a summary of the work completed during this week.

## Command-Line Interface

Successfully developed a basic command-line tool named `exql` that allows users to execute SQL queries directly from the terminal. The tool can accept SQL queries as input and display them as output.

## Example usage for week 1

Compile program:

```sh
g++ exql.cpp main.cpp -o exql
```

Running the command:

```sh
./exql "SELECT id, name FROM users;"
```

## Week 2, 3, 4 & 5

In these week, the goal is to build a SQL parser that transforms a stream of tokens into an Abstract Syntax Tree (AST), representing the structure of SQL queries in a meaningful way.

## Progress

### Completed

- **AST Definition**: Implemented the core classes for SQL statements and expressions.

- **Parser Methods**: Implemented the Pratt's parsing algorithm.

- **Parser Statement**: Successfully handle a variety of single-line SQL statements. I have tested it with several basic test cases, and it is working as expected. However, the parser currently lacks the ability to handle multi-line SQL queries, which is an area still under development.

### In Progress

- **Basic Error Handling**: Set up an error-handling framework to catch and report parsing issues.

## Example usage

Compile program:

```sh
g++ ast.cpp exql.cpp -o ast
```

Running the command:

```sh
./ast "SELECT id, name FROM users;"
```
