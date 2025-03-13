# Pipex

## Description
Pipex is a 42 project that aims to replicate the behavior of shell pipes (`|`). It allows redirecting the output of one command as the input of another, similar to how Unix pipelines work. The project reinforces knowledge of process creation, file descriptors, and inter-process communication using pipes.

## Mandatory Requirements
Pipex should handle the following command:
```bash
./pipex infile cmd1 cmd2 outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 > outfile
```
Where:
- `infile` is the file providing input.
- `cmd1` is the first command executed.
- `cmd2` is the second command executed, receiving `cmd1`'s output as input.
- `outfile` is the file where `cmd2`'s output is written.

## Bonus
The bonus part should handle multiple pipes:
```bash
./pipex infile cmd1 cmd2 cmd3 ... cmdN outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile
```
Additionally, `here_doc` functionality should be implemented:
```bash
./pipex here_doc LIMITER cmd1 cmd2 outfile
```
Equivalent to:
```bash
<< LIMITER cmd1 | cmd2 >> outfile
```
Where `here_doc` mode takes user input until `LIMITER` is reached.

## Allowed Functions
- `open`, `close`, `read`, `write`
- `malloc`, `free`
- `pipe`, `dup`, `dup2`
- `execve`, `fork`, `wait`, `waitpid`
- `perror`, `exit`

## Compilation
Compile the project with:
```bash
make
```
To remove object files:
```bash
make clean
```
To remove binaries:
```bash
make fclean
```
To recompile from scratch:
```bash
make re
```

## Usage
```bash
./pipex infile "cmd1" "cmd2" outfile
```
Example:
```bash
./pipex input.txt "cat" "grep hello" output.txt
```
This executes:
```bash
cat input.txt | grep hello > output.txt
```

## Error Handling
- Check for proper argument count.
- Handle invalid files and commands.
- Properly close file descriptors to prevent leaks.

## Author
El Mehdi Belfkih

