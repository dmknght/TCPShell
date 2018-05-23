import sys

#####	Generate password for linux_bind.c

try:
	clrPasswd = sys.argv[1]
except:
	sys.exit("Usage: python generate_password.py <your_password>")

encPasswd = ''

for char in clrPasswd:
	_tmp = (ord(char) >> 5) | (ord(char) << 1)
	#print _tmp
	encPasswd += chr(_tmp)

encPasswd = '\\x' + '\\x'.join(x.encode('hex') for x in encPasswd)
print encPasswd
