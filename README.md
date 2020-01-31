# Basic calculator parser
A simple tool to parse one digit calculator syntax using only **+**, **-**, * and **/** operators. It is allowed to use parenthesis **(**,**)** as well. 
## Usage
*Parser* tool will try to parse any expression that come from standard input:
```bash
$ echo "2+2" | Parser
4
$ Parser < expression.txt
44.8
```
## Building code
Use cmake to build the code. For example:
```bash
$ cd Parser
$ mkdir bin
$ cd bin
$ cmake ..
...
$ make
$ echo "1+1" | ./Parser
2
```
## Unit tests
Project also has unit-tests and to build them do similar:
```bash
$ cd Parser
$ mkdir test-bin
$ cd test-bin
$ cmake ../test
...
$ make
```
