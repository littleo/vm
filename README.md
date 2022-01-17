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

### Example

```python
# Read input (n) and print [n,n-1,..1]

main:
input			# read input
jump loop		# jump to label: loop

loop:
dup 0			# duplicate stack's first entry (0)
output			# write stack entry
1 			# push 1 into stack
sub			# pop 2 entries (b,a) and push (a-b)
dup 0			# duplicate entry 0
'0'			# push 0-ascii code
eq 			# pop b,a : check whether a==b
jnz end			# if (a==b): jump to end
'-'	
output
jump loop

end:
halt			# terminate program


```

The assembler then parses your assembly code and produces a bytecode sequence.

```bash
~ python3 assembler.py input.asb output.b
```

To run this, pass it as an argument (argv[1]) to the `vm`.

```bash
~ ./vm output.b
```