<p align="center" width="100%"><img src="./icons/icon-alpha.png" alt="icon" width=100 height=100 style="display: block; margin: 0 auto" /></p>

# STAKZ

## What is STAKZ?
**STAKZ** is a stack-based language with enforced types, created for use on the [Apple M1 Processor](https://en.wikipedia.org/wiki/Apple_M1).

## How do I run a STAKZ Program?
First, you'll need to be using a variant of the Apple M1 chip. If you're not, unfortunately, you can't run the compiled binary.
If you are on a variant of the M1, congrats, you can continue!

**Step 1**
Create a file, e.g `test.stx`. Write some stakz code inside of it (check out the `/examples` dir for some basic examples).

**Step 2**
Run `make` to create an executable of the compiler.
```console
$ make
```

**Step 3**
Once the compiler has been made, run it:
```console
$ ./a <path-to-file>
```

**Step 4**
The previous step will have generated the assembly for your fantastic program. Now all you need to do is build it and you'll be able to run it!
```console
$ make build
```

**Step 5 (The best one)**
Run your program!
```console
$ ./stakz
```

*Example*
```stakz
"Hello, World!" out
```
*Further examples can be found in the `/examples` dir*

---

### Todos
- [x] Create Lexer
- [x] Create Parser
- [x] Generate Assembly from Parser

---

**References used for making the Compiler**

For helping decide how to implement the Parser
- [Designing and Implementing a Syntactic Parser](https://www.jstor.org/stable/24147875?seq=1#metadata_info_tab_contents)
- [Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
- [Constructing an Abstract Syntax Tree](https://stackoverflow.com/questions/1721553/how-to-construct-an-abstract-syntax-tree)
