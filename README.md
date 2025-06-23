# minishell

A minimal Unix shell implementation in C, developed as part of the 42 school curriculum. `minishell` aims to replicate the basic behavior of bash, supporting command execution, pipelines, redirections, environment variables, and several built-in commands.

## Features

- **Prompt**: Displays a customizable prompt and reads user input.
- **Command Execution**: Runs binaries from the system's `$PATH` and supports argument passing.
- **Built-in Commands**: Implements the following built-ins:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **Pipelines**: Supports chaining commands with `|`.
- **Redirections**: Handles input `<`, output `>`, append `>>`, and heredoc `<<`.
- **Environment Variables**: Expands variables (e.g., `$HOME`) and manages the shell environment.
- **Quotes**: Handles single `'` and double `"` quotes for grouping and variable expansion.
- **Signal Handling**: Manages `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` gracefully.
- **Error Handling**: Provides informative error messages for invalid commands, syntax errors, and failed operations.
- **Memory Management**: Cleans up all allocated resources to avoid leaks.

## Getting Started

### Prerequisites

- GNU Make
- GCC or Clang
- `readline` and `ncurses` libraries

### Build

```sh
make
```

This will compile the shell and its dependencies (including a custom `libft`).

### Run

```sh
./minishell
```

You'll see a prompt where you can type commands as in a regular shell.

### Docker (Optional)

A `Dockerfile` is provided for building and running `minishell` in a containerized environment:

```sh
docker build -t minishell .
docker run -it minishell
```

## Usage

- Type commands and press Enter to execute.
- Use pipes (`|`) to chain commands.
- Redirect input/output using `<`, `>`, `>>`, and `<<`.
- Use built-in commands for shell management.
- Press `Ctrl+D` to exit the shell.

### Examples

```sh
ls -l | grep minishell > result.txt
export MYVAR=42
echo $MYVAR
cat << EOF
Hello minishell!
EOF
```

## Project Structure

- `src/` — Core shell logic (parsing, execution, environment, signals, etc.)
- `builtins/` — Implementations of built-in commands
- `libft/` — Custom standard library functions
- `get_next_line/` — Line reading utility
- `incl/` — Header files

## Authors

- Valeria Harkusha
- Yen Nguyen

## Notes

- This project is a learning exercise and may not cover all edge cases or advanced shell features.
- Memory management is a work in progress; some leaks may remain.

## License

This project is for educational purposes and is not intended for production use.
