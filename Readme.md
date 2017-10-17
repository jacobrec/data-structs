# C++ Data Structures
Helping me learn C++ as well as testing

## List
An array list implementation with python-like slicing
Use:
```c
List<int> i;
i += 'a';
i += 'b';
i += 'c';
i.add('e');
i.insert('d',1);

i.sort();// performs an in place quickSort

i.indexOf('c');// does a binary search when sorted

i["2:-1"]; //List object holding ['c','d','e']
i["-3:-1"]; //List object also holding ['c','d','e']
```
