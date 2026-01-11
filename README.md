# Simple Shell

## Description

This project implements a simple UNIX command interpreter written in C.  
It was developed as part of the Holberton School curriculum and is designed to reproduce the basic behavior of a UNIX shell (`sh`).  
The shell can run both in interactive mode and non-interactive (pipeline) mode, execute commands found in the system's `$PATH`, and handle a small set of built-in commands.

This project demonstrates process creation, PATH resolution, file execution, environment management, and robust error handling.

---

## Features

- Interactive mode with the prompt `($)`
- Non-interactive mode (commands through pipeline or file)
- Command execution using both absolute paths and `$PATH` lookup
- Built-in commands: `exit` and `env`
- Handling of whitespace, empty lines, and input formatting
- Proper exit status management (0, 126, 127, 128+signal)
- Error messages formatted like a UNIX shell
- Modular architecture for maintainability and clarity

---

## Requirements

- Ubuntu 20.04 LTS
- `gcc` compiler
- Betty style compliance

---

## Compilation

To compile the program, use:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

Usage
Interactive Mode

Run the program as follows:
./hsh

The shell will display:
```
($)
```

Then wait for commands such as:
```
($) ls
($) /bin/pwd
($) env
($) exit
```

Non-interactive Mode

In non-interactive mode, the shell reads commands from standard input and executes them sequentially, without displaying the prompt.
Commands can be piped into the shell:
```
echo "ls" | ./hsh
echo "pwd" | ./hsh
printf "ls\nwhoami\n" | ./hsh
```

---

## Project Structure

```
.
├── README.md                # Project documentation
├── man_1_hsh                # Manual page (man 1 hsh)
├── shell.h                  # Header file (function prototypes + libraries)
│
├── builtin.c                # Built-in functions (exit, env)
├── error.c                  # Error handling and formatted messages
├── execute.c                # Forking and executing commands
├── loop.c                   # Main loop, I/O handling, mode selection
├── parsing.c                # Input formatting, tokenizing, memory handling
├── path.c                   # PATH lookup, env value management
├── path_utils.c             # Helpers for building and validating paths
└── prompt.c                 # Prompt printing in interactive mode
```

---

## Supported Commands

### Built-in Commands

- exit  
  Exit the shell (no arguments supported).

- env  
  Print the current environment variables.


### External Commands

The shell supports:

Absolute path commands:
/bin/ls, /bin/pwd, /usr/bin/whoami, etc.

Commands located through $PATH:
`ls`, `pwd`, `echo`, etc.

### Limitations

This shell does not support:
- Pipes (|)
- Redirections (<, >, >>)
- Command chaining (&&, ||)
- Wildcards (*)
- Aliases
- Signal handling (Ctrl+C behavior is default)


Programs available in custom PATH directories

Usage Examples
```
$ ./hsh
($) ls
builtin.c  error.c  execute.c  hsh  loop.c  parsing.c  path.c  path_utils.c  prompt.c  shell.h
($) /bin/pwd
/home/user/simple_shell
($) whoami
user
($) env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user
...
($) exit
$
```
---

## Environment

This shell uses the environment variables inherited from the parent process.

The `PATH` environment variable is used to locate executable files when
commands are not provided with an absolute or relative path.

The shell does not modify the environment but passes it directly to executed
programs using `execve`.

---

## Error Handling

This shell implements structured error messages similar to /bin/sh, using the format:
```
program_name: line_number: command: error_message
```

Examples:
```
./hsh: 3: aaa: not found
./hsh: 5: ./dir: Permission denied
./hsh: 7: /bin/shh: No such file or directory
```

### Error cases handled include:

* Command not found
* Permission denied / not executable
* No such file or directory
* Child process terminated by a signal
* Internal errors (e.g. `fork`/`waitpid` failure)

### Return Values

- Returns 0 on successful execution
- Returns 126 when a command is found but not executable
- Returns 127 when a command is not found
- Returns 128 + signal number when terminated by a signal

---

## Manual Page

A manual page is provided for this shell.

File: `hsh.1`
Section: 1 (User Commands)

You can view it with:
man ./hsh.1

You can also preview the manual page here :

![View man page hsh](img/man_page_hsh.png)

---

## Process Flow (Overview)

### Main logic of the shell

1. Initialize variables and determine if the shell is running in interactive mode using `isatty`.
2. If running in interactive mode, display the prompt (`$`).
3. Read a line from standard input using `getline`.
4. Clean and normalize the input line:
   - Remove the trailing newline
   - Trim leading and trailing whitespace
5. If the line is empty or contains only whitespace, restart the loop.
6. Split the input line into tokens (command only, no arguments).
7. Check if the command is a built-in:
   - `exit`
   - `env`
8. If the command is not a built-in:
   1. Determine how to resolve the command:
      - Use the command directly if it contains a `/`
      - Otherwise, search for it in the `PATH`
   2. Fork a child process.
   3. Execute the command using `execve`.
   4. If execution fails, print the appropriate error message.
9. In the parent process, wait for the child process using `waitpid`.
10. Retrieve and store the exit status of the command.
11. Repeat the loop until `exit` is called or EOF is reached.

A graphical flowchart can be added in a subdirectory, for example:

![Simple Shell – Process Flowchart](img/simple_shell_flowchart.png)

and referenced from this README.

---

## Testing and Debugging

Compilation Check
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

Memory Leak Check (Valgrind)
```
valgrind --leak-check=full ./hsh
```

---

## Author

- **Morgane abbattista** (Alreix)
- GitHub: https://github.com/Alreix
 
---

## License
This project is part of the Holberton School curriculum and is provided for educational purposes.
