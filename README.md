# What is STAX?
**STAX** is a stack-based language with enforced types.

*Example*
```stax
func main
	args [argc: int, argv: string[]] = // Accept 2 arguments into the function 
	"Hello World"
	let n: string pop // `n` is now "Hello World"
	n "!" += // `n` is now "Hello World!"
end
```
