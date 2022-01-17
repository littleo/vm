## VM (GC)

A virtual machine (p-code machine) that executes byte code of an imaginary language. There is also a **mark-and-sweep** garbage collector (gc) implemented.

You can experiment writing your own program (unfortunately, in assembly). It follows a list of the available instructions and a simple example for practice. 

```python
	'halt', 'jump', 'jnz', 'dup', 'swap', 'drop', 
	'push4', 'push2', 'push1', 
	'add', 'sub', 'mul', 'div', 'mod', 
	'eq', 'ne', 'lt', 'gt', 'le', 'ge', 
	'not', 'and', 'or', 
	'input', 'output', 
	'clock', 
	'cons', 'hd', 'tl'
```


```assembly
# Read input (n) and print [n,n-1,..1]

main:
input
jump loop

loop:
dup 0
output
1
sub
dup 0
'0'
eq
jnz end
'-'
output
jump loop

end:
halt


```

The assembler then parses your assembly code and produces a bytecode sequence. To run this, pass it as an argument to the `vm`.

```
~ python3 assembler.py input.asb output.b
~ ./vm output.b
```