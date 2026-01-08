# simple_shell

`hsh` is a minimal UNIX command interpreter built for the Holberton School **simple_shell** project.
It reads commands from `stdin`, tokenizes them into an argument vector, resolves executables using
`PATH` (or absolute/relative paths), then runs them via `fork()` + `execve()`.

## Features

- **Interactive mode** (TTY): shows the prompt `($) ` and executes commands line-by-line.
- **Non-interactive mode** (pipe/file): reads until EOF without printing a prompt.
- **PATH resolution**: searches each directory in `PATH` using `access()`.
- **Built-ins**:
  - `exit [status]` (defaults to last command status)
  - `env`
- **Error format**: matches `/bin/sh` style and prints `argv[0]` with a line counter:
  - `./hsh: 1: qwerty: not found`

## Requirements

- Ubuntu 20.04 LTS
- `gcc` with flags: `-Wall -Wextra -Werror -pedantic -std=gnu89`
- Betty style

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive

```bash
./hsh
($) /bin/ls
($) ls -l
($) exit 0
```

### Non-interactive

```bash
echo "/bin/ls" | ./hsh
cat script.txt | ./hsh
```

## Built-ins
- `exit [status]` - exit the shell with the given status (default: last command status).
- `env` - print the current environment.

## Behavior details (reviewer notes)

- **Exit status**:
  - If a command executes, `hsh` returns that command’s exit status.
  - If a command is not found, `hsh` returns **127**.
  - `exit` with no argument exits with the **last command status**.
- **Non-interactive mode**:
  - Works with pipes/redirection from the parent shell, e.g. `echo "/bin/ls" | ./hsh`
- **Limitations**:
  - Does not support pipes (`|`), quotes, or command chaining.

## Files

- `shell.h`: shared declarations/prototypes
- `main.c`: entry point
- `loop_helpers.c`: main read/parse/dispatch loop
- `path.c`: `PATH` searching
- `execute.c`: `fork()`/`execve()` execution
- `builtins.c`: builtin commands (`exit`, `env`)
- `errors.c`: error printing
- `man_1_simple_shell`: manual page
- `AUTHORS`: contributors

## Authors
- Johnson Martinez <jamhalex@gmail.com>
- Joshua Santiago <joshua.d.santiago92@gmail.com>

