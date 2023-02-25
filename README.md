# minishell

42 Cursus - minishell: this project is about creating your own shell, inspired by bash.

## Table of contents 📑
- [Status](#status)
- [About the project](#about-the-project)
    * [Project boundaries](#project-boundaries)
- [How to use](#how-to-use)

## Status ✔️
- Status: not quite finished
- Score: -%
- Observations: bash's syntaxis is tricky, learned a lot about processes and file descriptors

## About the project 👩‍💻

Creating a shell is creating a software to communicate with a computer using lines of commands in a language somewhat close to the human language.

### Attributes 👾
 - Display a prompt when waiting for new command.
 - Working history  of commands.
 - Pipes `|` work like in bash.
 - Redirections `<`, `>`, `<<`, `>>` work like in bash.
 - `$?` works like in bash.
 - Signals handled: `Ctrl-C`, `Ctrl-D` and `Ctrl-\` work like in bash.
 - Enviroment variables.

### Built-ins 🔧

 - `echo`  with option `-n`
 - `cd` with only a relative or absolute path.
 - `pwd` with no options
 - `export` with no options
 - `unset` with no options
 - `env`with no options or arguments
 - `exit` with no options.
 
###  Extras ✚
 - Wildcards `*` work fot the current directory.
 - Interprets special characters such as `\` (backslash).
 - `cd` with any option.

## How to use

Need installed readline library

```sh
brew install readline
```

Run `make`

```sh
./minishell
```
To test what happens without environment variables

```sh
env -i ./minishell
```

##
