simple_shell
===========

`hsh` is a minimal UNIX command interpreter built as part of the Holberton School simple_shell project. It supports basic command parsing, PATH resolution, and a small set of built-ins for portability testing.

Features
- Interactive prompt `($) ` with line counting for error messages.
- Executes commands found through the PATH or by absolute/relative path.
- Handles interactive and non-interactive (piped/file) input.
- Built-ins: `exit [status]`, `env`.

Requirements
- Ubuntu 20.04 LTS
- `gcc` with flags: `-Wall -Wextra -Werror -pedantic`
- POSIX environment and standard library headers

Compilation
```
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh
```

Usage
Interactive mode:
```
./hsh
($) ls -l
($) /bin/echo "Hello, world"
($) exit 0
```

Non-interactive mode:
```
echo "/bin/ls" | ./hsh
cat script.txt | ./hsh
```

Built-ins
- `exit [status]` – exit the shell with the given status (default: last command status).
- `env` – print the current environment.

Project Structure
- shell.h: shared declarations and prototypes.
- man_1_simple_shell: manual page for the program.
- AUTHORS: contributors.

Notes
- The shell returns the exit status of the last executed command.
- Errors are reported with the shell name and line count for easier debugging.

Authors
- Johnson (jamhalex@gmail.com)
- Joshua (please add your preferred email)
