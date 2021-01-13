fichier = open("/dev/urandom", encoding="utf8", errors='ignore')
data = ""

i=0
while True:
	data += fichier.read(1000000) # 1kb 
	#if (i%2) == 0:
	i += 1 
	print(str(i*10) + "mb")
		
