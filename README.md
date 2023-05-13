# JaniX ed ( jed )
`jed` is line oriented text editor with easier syntax and usability unlike GNU ed. Not to mention it is smaller

## Compilation
To compile `jed`, simply compile main.c using your favourite compiler, you don't need to compile anything else

## Usage
* To start `jed` with fresh buffer, simply run it
* To start `jed` with buffer loaded from file, run it with leading file path as argument

## Commands
```
i -- insert
a -- append
r -- replace
l -- line utils
b -- buffer utils
p -- print utils
w -- write utils
```
## Insert mode
By default, you start at the start of current buffer
To exit insert mode, the current line where you type must contain only `.`, if you need it there, simply escape it using `\.`

however, you can use subcommands:
* `l` -- `i l 1` will start insert mode at the start of line 1
* `p` -- `i p 20` will start inserting before 20th character
> Subcommands can be chained together, like `i l 2 p 10` -- this will start insert mode at line 2, 10th character
## Append mode
By default, you start at the end of current buffer
To exit append mode, the current line where you type must contain only `.`, if you need it there, simply escape it using `\.`

however, you can use subcommands:
* `l` -- `i l 1` will start append mode at the start of line 1
* `p` -- `i p 20` will start appending after 20th character
> Subcommands can be chained together, like `a l 2 p 10` -- this will start append mode at line 2, 10th character
## Replace mode
Replace mode by default searches for first occurence from the start of the buffer and replaces it with the new one
Replace mode's syntax is following `r [subcmds] foo bar`, this will replace first `foo` with `bar`

to improve usage, you can use these subcommands:
* `g` -- `r g foo bar` will replace every single `foo` with `bar` in the entire buffer
* `l` -- `r l 1 foo bar` will replace first occurence of `foo` in line `1` and replace it with `bar`
* `i` -- `r i foo bar` on the first occurence it will show you some useful info about `foo`'s location and ask you if you want to replace it with `bar`

> Subcommands can be together, like `r g i foo bar` -- this will find occurence of `foo` and it will every time start interactive mode if you want to replace it with `bar`
## Line utils
Line utils help you with managing lines in current buffer, with it you can remove, insert, add, wipe line in simple command
Syntax example looks like `l (line) [subcmds]` will run action on line `(line)`

Subcommands:
* `r` -- `l 1 r` will remove line 1
* `i` -- `l 1 i` will insert line before line 1
* `a` -- `l 1 a` will append line after line 1
* `w` -- `l 1 w` will empty out entire line 1

> Subcommands cannot be chained!
## Buffer utils
Buffer utils help you with editing the entire buffer
Syntax example looks like `b [subcmds]` will run action on the entire buffer

Subcommands:
* `s` -- `b s file` will set content of buffer from `file`
* `d` -- `b d` will wipe the entire buffer
* `a` -- `b a file` will append content of `file` to current buffer
* `i` -- `b i file` will insert content of `file` at the start of current buffer

> Subcommands cannot be chained!
## Print utils
Want to know how the current buffer looks like? print utils are just for that!
Syntax example looks like `p [subcmds]` will print buffer to the sceen based on action
By default `p` will just print out the entire buffer

Subcommands:
* `n` -- `p n` will print out the entire buffer with line numbers on the left with separator
* `l` -- `p l 1` will print out line 1 OR `p l 1-3` will print line 1, 2 and 3

> Subcommands can be chained
## Write utils
You also want to store your buffer somewhere right?
Syntax example looks like `w (file) [subcmds]` will write your buffer into `(file)`

Subcommands:
* `a` -- `w file a` will append buffer to `file`
* `i` -- `w file i` will insert buffer at the start of `file`

> Subcommands cannot be chained!

