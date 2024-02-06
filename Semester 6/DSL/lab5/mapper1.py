import sys

for line in sys.stdin:
	line=line.strip()
	words=line.split()

	for words in words:
		print("%s\t\t%s"%(words,1))
