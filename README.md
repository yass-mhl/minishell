# Minishell  
_As beautiful as a shell._

---

## 📚 Description

This project consists in building a minimal Unix shell — a simple command-line interpreter that mimics some functionalities of Bash.

---

## 🛠️ Features

- Prompt display when waiting for user input
- Command history support
- Execution of commands via:
  - Absolute/relative paths
  - `$PATH` environment variable
- Built-in commands:
  - `echo` (with `-n` option)
  - `cd` (with relative or absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Input/output redirections:
  - `<`, `>`, `>>`, `<<` (heredoc)
- Pipes (`|`) support
- Single and double quotes parsing:
  - `'` prevents all expansions
  - `"` prevents all except `$`
- Environment variables handling (`$VAR`, `$?`)
- Signal handling:
  - `Ctrl-C`: display new prompt
  - `Ctrl-D`: exit shell
  - `Ctrl-\`: does nothing

---

## ⚠️ Norm and Restrictions

- Code must follow the 42 Norm
- One global variable max (only for signal handling)
- No memory leaks (except `readline` internals)
- Makefile with rules: `all`, `clean`, `fclean`, `re`, and `$(NAME)`

---

## 🧪 Compilation

```bash
make
```

## 🔗 External Functions Allowed

``readline``, ``malloc``, ``free``, ``write``, ``fork``, ``execve``, ``pipe``, ``dup2``, ``chdir``, ``getcwd``, ``signal``, etc.

See the subject for the full list.




## Authors

- [@yass-mhl](https://www.github.com/yass-mhl)
- [@iamgrg](https://www.github.com/iamgrg)

