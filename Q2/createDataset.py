import random
import os
import sys



WORDS = open("/usr/share/dict/words").read().splitlines()
def createDir(path,k,b,l):
	if len(path.split("/"))==k:
		content=""
		for i in range(l):
			content+=(random.choice(WORDS)+" ")
		for i in range(b):
			f=open(path+"/"+str(i), "w")
			f.write(content)
			f.close()
		return

	for i in range(b):
		newpath=path+"/"+str(i)
		print(newpath)
		os.mkdir(newpath)
		createDir(newpath,k,b,l)

rootfile="D"+sys.argv[1]+"B"+sys.argv[2]
os.mkdir(rootfile)
createDir("D"+sys.argv[1]+"B"+sys.argv[2],int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3]))
