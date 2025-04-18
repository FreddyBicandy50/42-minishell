# minishell

<p align="center">
  <img src="https://github.com/FreddyBicandy50/FreddyBicandy50/blob/main/42_badges/minishelle.png" alt="minishell 42 project badge"/>
</p>

## Status

Started: 24/09/2024.

Finished: 18/04/2025.

Grade: pending...

## Project Idea

Minishell is a 42 school team project to create a basic shell program in C. It implements redirections and pipes, as well as environment variable expansions and the cd, echo, env, exit, export, pwd and unset builtin commands.

## Usage

Clone the repository:

```
git https://github.com/FreddyBicandy50/42-minishell.git
```

To compile:

```
cd minishell && make
```

To run the program:

```
./minishell
```

## Supported Features

Minishell is a miniature shell program based on Bash. Minishell supports:

- Prompt display
- Command history (up and down arrows)
- System executables available from the environment (`ls`, `cat`, `grep`, etc.)
- Local executables (`./minishell`)
- Builtin commands :
  - `echo` (and option `-n`)
  - `cd` (with only a relative or absolute path)
  - `pwd` (no options)
  - `export` (no options)
  - `unset` (no options)
  - `env` (no options or arguments)
  - `exit` (with exit number but no other options)
- Pipes `|` which redirect output from one command to input for the next
- Redirections:
  - `>` redirects output
  - `>>` redirects output in append mode
  - `<` redirects input
  - `<< DELIMITER` displays a new prompt, reads user input until reaching `DELIMITER`, redirects user input to command input (does not update history)
- Environment variables (i.e. `$USER` or `$VAR`) that expand to their values.
  - `$?` expands to the exit status of the most recently executed foreground pipeline.
- User keyboard signals:
  - `ctrl-c` displays a new prompt line.
  - `ctrl-d` exits minishell
  - `ctrl-\` does nothing

However, Minishell does not support `\`, `;`, `&&`, `||`, or wildcards.

## Guides

The most interesting part of any project is the research that goes behind it. If you are a student, please don't miss out on that opportunity by simply following guides such as these. In any case, they should under no circumstances be your only source of information about this project. Try things, fail, research, try again and succeed! And maybe write your own guide about it. Writing really is the best way to learn.

- [Bash reference manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Shell Program Explained](https://www.youtube.com/watch?v=ubt-UjcQUYg&t=473s&ab_channel=hhp3)

---

fbicandy@student.42.fr | LinkedIn: [fbicandy](https://www.linkedin.com/in/freddy-bicandy/)
