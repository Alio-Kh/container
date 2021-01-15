import sys

i=0
s = ""
while True:
	s += "!" * 1000000
	i += 1 
	print(str(len(s)/1000000) + "Mo is Allocated")
