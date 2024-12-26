# Custom Shell Implementation in C++

[![progress-banner](https://backend.codecrafters.io/progress/shell/f44fef23-4bc3-47db-a63c-1d1b5dbeca14)](https://app.codecrafters.io/users/codecrafters-bot?r=2qF)

This project implements a custom shell in C++ that supports basic POSIX commands and features. The shell allows users to run external programs, execute built-in commands like `cd`, `pwd`, `echo`, and `cat`, and interact with the system using command-line inputs.

This project is my solution for the [**"Build Your Own Shell" Challenge**](https://app.codecrafters.io/courses/shell/overview). The goal of the challenge is to create a POSIX-compliant shell that can interpret shell commands, execute built-in commands, and run external programs.

## Features

- **Built-in Commands**:
  - `echo`: Outputs text to the terminal.
  - `pwd`: Displays the current working directory.
  - `cd`: Changes the current directory to the specified path (or home directory `~`).
  - `cat`: Displays the contents of a file.

- **External Commands**: Executes any command available in the system's PATH.

- **Command Parsing**: Supports proper handling of argument parsing and quoting, making the shell more flexible and robust.

- **Process Management**: Supports creating and executing processes using `fork()` and `execvp()`.

## Getting Started

### Prerequisites

- C++17 or later
- A POSIX-compliant operating system (Linux/macOS)

### Installation

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/hemang111/My-shell.git
   cd My-shell
   ```

2. Compile the code:
   ```bash
   g++ -std=c++17 -o shell main.cpp commands.cpp shell_util.cpp
   ```

3. Run the shell:
   ```bash
   ./shell
   ```

## Usage

Once the shell starts, you can interact with it using the following commands:

### Built-in Commands:

- **`pwd`**: Displays the current working directory.
- **`echo 'Hello World!'`**: Prints `Hello World!`.
- **`cd /path/to/directory`**: Changes the current directory to the specified path.
- **`cat filename`**: Displays the contents of the specified file.

### External Commands:
The shell also supports running any external commands available in your system's PATH. For example:
- **`ls`**: Lists the files in the current directory.
- **`gcc --version`**: Displays the version of the GCC compiler.

### Exit the Shell:
To exit the shell, type:
```bash
exit 0
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

