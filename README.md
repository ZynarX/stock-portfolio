# STOCK PORTFOLIO

A simple custom stock portfolio application built entirely in C++

-------------------------------------------------------------------------

## OVERVIEW

This is a *fully functional console-based stock portfolio application* that allows users to:

 - Buy custom stocks
 - Sell stocks from their portfolio
 - View stock portfolio
 - Save user portfolio stocks into a `.csv` folder

All built entirely with C++ without using any external libraries.

-------------------------------------------------------------------------

## FEATURES

| Feature | Description |
|---------|-------------|
| **FileIO** | Loads user stock portfolio from a `.csv` folder |
| **View Portfolio** | Lets users view their stocks |
| **Buy Stocks** | Lets users buy custom stocks |
| **Sell Stocks** | Lets users sell stocks from their portfolio |

-------------------------------------------------------------------------

## TECHNOLOGIES USED

 - **C++17**
 - **Standard Template Library (STL)**: `iostream`, `vector`, `string`, `fstream`
 - **Object-Oriented Programming (OOP)**: Structured around `Portfolio` and `Stock` classes
 - **FileIO**: Load portfolio data from a `csv` file

-------------------------------------------------------------------------

## GETTING STARTED

### PREREQUISITES

 - **C++ Compiler**: `g++`, `clang++`, `MSVC`
 - **Terminal** or command-line interface access

### BUILD INSTRUCTIONS

To compile and run the app from project root:

`g++ src/main.cpp src/portfolio.cpp src/stock.cpp -o portfolio`
`./portfolio`
