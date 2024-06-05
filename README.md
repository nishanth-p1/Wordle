# Wordle Game in C++

## Introduction
This project is a C++ implementation of the popular word-guessing game Wordle, designed to run in a web browser. The game allows players to guess a secret five-letter word within six attempts, providing feedback after each guess to aid in narrowing down the correct answer.

## Features
- **Web Browser Interface:** Play the game directly in your web browser.
- **Interactive Feedback System:** After each guess, the game provides visual hints to indicate the accuracy of the guessed letters.
- **Random Word Selection:** Each game session starts with a randomly selected word from a predefined list.
- **Input Validation:** Ensures that all guesses are valid five-letter words.

## How to Play
1. **Compile the Game:** Use the provided Makefile to compile the game.
2. **Open the Game:** A new browser tab will automatically open where you can play the game.
3. **Gameplay Instructions:**
   - Enter your guess in the provided text box and submit it.
   - Colored hints will help guide your next guess:
     - **Green** indicates the right letter in the right spot.
     - **Yellow** indicates the right letter in the wrong spot.
     - **Red** indicates a letter that is not in the word at all.
4. **Winning and Losing:** The game concludes when you either guess the word correctly or exhaust your six tries.

## Requirements
- C++17 Compiler (e.g., GCC or Clang)
- Web Browser

## Compilation and Execution
To set up and run the game, execute the following in your terminal:
```bash
make
