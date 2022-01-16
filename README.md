## VM (GC)

A virtual machine (p-code machine) that executes byte code of an imaginary language. There is also a **mark-and-sweep** garbage collector (gc) implemented.

```python
instr =  [
	'halt', 'jump', 'jnz', 'dup', 'swap', 'drop', 
	'push4', 'push2', 'push1', 
	'add', 'sub', 'mul', 'div', 'mod', 
	'eq', 'ne', 'lt', 'gt', 'le', 'ge', 
	'not', 'and', 'or', 
	'input', 'output', 
	'clock', 
	'cons', 'hd', 'tl']
```