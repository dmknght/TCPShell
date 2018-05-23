clrPasswd = raw_input("Enter Password: ")
encPasswd = ''

for char in clrPasswd:
	_tmp = (ord(char) >> 5) | (ord(char) << 1)
	#print _tmp
	encPasswd += chr(_tmp)

encPasswd = '\\x' + '\\x'.join(x.encode('hex') for x in encPasswd)
print encPasswd
