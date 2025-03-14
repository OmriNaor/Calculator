# C Project: Calculator

## Introduction

This Calculator is a command-line application implemented in C, designed to evaluate mathematical expressions. It supports basic arithmetic operations such as addition, subtraction, multiplication, division, and exponentiation. The calculator uses a stack-based approach to parse and evaluate the expressions efficiently, with an emphasis on minimizing `if` statements to maximize performance.

## Features

- Support for basic arithmetic operations: `+`, `-`, `*`, `/`, `^`.
- Parentheses support for controlling the order of operations.
- Error handling for invalid syntax and division by zero.
- Efficient operator precedence management using stacks, minimizing conditional logic for better performance.
- Ability to handle negative numbers.
- Easy-to-extend design for additional functionality.

## Components

The project's main components include:

- `calculator.c`: Contains the core logic for parsing, calculating, and handling user input.
- `calculator.h`: Header file containing declarations for functions and structures used in the calculator.
- `stack.c`: Implementation of stack data structures used for operand and operator management.
- `stack.h`: Header file for the stack data structures.
  
(Note: The `stack.c` and `stack.h` files are required and must be included to compile and run the project.)

## How It Works

1. The user enters a mathematical expression, which can include numbers, operators, and parentheses.
2. The calculator parses the expression using a stack to manage operands and operators.
3. Operator precedence is respected, and parentheses are handled correctly by evaluating expressions inside them first.
4. The design minimizes `if` statements by relying on lookup tables and efficient stack-based management to handle operators and operands.
5. The result is calculated and displayed to the user.

## Running the Calculator

To compile and run the calculator, follow these steps:

1. **Download the necessary files:**
   - Ensure that both `calculator.c`, `calculator.h`, `stack.c`, and `stack.h` are in the same directory.
   - Ensure to create a test file called 'calculator_test.c'.
   
2. **Compile the project:**
   - The easiest way to compile the project is by using the provided `Makefile`. Simply run: make
   - This will generate the executable `calculator` in the directory.
   
3. **Run the calculator:**
- After compilation, you can run the calculator by entering: ./calculator

## Example Usage

![Screenshot from 2025-03-14 17-40-00](https://github.com/user-attachments/assets/0daa2781-46c9-479f-b693-4a60ce8e71f7)


## Remarks

- The calculator is designed for educational purposes and demonstrates the use of stack-based algorithms, efficient operator precedence management, and minimal `if` conditions for better performance.
- It is not intended for production use but can be easily extended with features like additional operators or error handling improvements.
