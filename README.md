## vm-gc

A virtual machine (p-code machine) that executes byte code of an imaginary language.  There is also a **mark-and-sweep** garbage collector (gc) implemented.


```python
opcode = {
  'halt': b'\x00',
  'jump': b'\x01',
  'jnz': b'\x02',
  'dup': b'\x03',
  'swap': b'\x04',
  'drop': b'\x05',
  'push4': b'\x06',
  'push2': b'\x07',
  'push1': b'\x08',
  'add': b'\x09',
  'sub': b'\x0a',
  'mul': b'\x0b',
  'div': b'\x0c',
  'mod': b'\x0d',
  'eq': b'\x0e',
  'ne': b'\x0f',
  'lt': b'\x10',
  'gt': b'\x11',
  'le': b'\x12',
  'ge': b'\x13',
  'not': b'\x14',
  'and': b'\x15',
  'or': b'\x16',
  'input': b'\x17',
  'output': b'\x18',
  'clock': b'\x2a',
  'cons': b'\x30',
  'hd': b'\x31',
  'tl': b'\x32',
}
```python
