<p align="center" width="100%"><img src="./icons/icon-alpha.png" alt="icon" width=100 height=100 style="display: block; margin: 0 auto" /></p>

# STAKZ

## What is STAKZ?
**STAKZ** is a stack-based language with enforced types, created for use on the [Apple M1 Processor](https://en.wikipedia.org/wiki/Apple_M1).

*Example*
```stakz
func main
	args [argc: int, argv: string[]] = // Accept 2 arguments into the function 
	"Hello World"
	let n: string pop // `n` is now "Hello World"
	n "!" += // `n` is now "Hello World!"
	n out // Prints "Hello World!"
END
```
*Further examples can be found in the `/examples` dir*

---

### Todos
- [x] Create Lexer
- [x] Create Parser
- [x ] Generate Assembly from Parser

---

**References used for making the Compiler**

For helping decide how to implement the Parser
- [Designing and Implementing a Syntactic Parser](https://www.jstor.org/stable/24147875?seq=1#metadata_info_tab_contents)
- [Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
- [Constructing an Abstract Syntax Tree](https://stackoverflow.com/questions/1721553/how-to-construct-an-abstract-syntax-tree)
