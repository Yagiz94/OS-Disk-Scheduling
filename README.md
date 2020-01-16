# OS-Disk-Scheduling
Disk Scheduling
The diskschedule.c file compiles when you compile the makefile.

When the user enters ./diskschedule <headpos> the program gives output format as:
	FCFS :   ......
	SSTF :   ......
	SCAN :   .....
	CSCAN :  ....
	LOOK :   .....
	CLOOK :   ......
	
Example: ./diskschedule 1200 command gives output as:
	FCFS : 1615853
	SSTF : 8768
	SCAN : 8764
	CSCAN : 9996
	LOOK : 8762
	CLOOK : 9926
	
-The requests are generated randomly if the user does not give any input file. 
If the input file is given the requests are generated according to the data inside inputfile.

Participant:
Yagiz Gani
