# Operating_System
A Simulation that uses First in first in first out paging technique to run up to 3 scripts, as well as handles task switching where each process has 2 quantas. Directory called "BackingStore" is used to simulate the backing store where all the files are stored. The files in the backing store are erased once the operating system quits (as demonstrfated in the demo).

### Available commands

_help_: Displays all commands

quit:Exits the shell with "Bye!"

set VAR STRING: Assigns a value to shell memory

print VAR: Displays the STRING assigned to VAR

run SCRIPT: Executes the file SCRIPT.TXT

exec SCRIPT1 SCRIPT2 SCRIPT3: executes the entered files

### Demo

![Demo](OS.gif)


### Running Instructions

In order to run the operating system run the following command in your terminal:

`./mykernel`
