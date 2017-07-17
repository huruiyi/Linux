#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// using message
	if (argc != 2)
	{
		printf("using message: a.out <fileName>!\n");
		exit(1);
	}

	// open file
	int fd = open(argv[1], O_RDONLY);

	// for error open
	if (-1 == fd)
	{
		printf("can't open %s\n", argv[1]);
		exit(1);
	}

	char buf[4096] = {0};

	int n;
	while (0 < (n = read(fd, buf, 4096)))
	{
		if (n != write(STDOUT_FILENO, buf, n))
		{
			printf("write error\n");
			exit(1);
		}
	}

	// for error read
	if (0 > n)
	{
		printf("read error\n");
		exit(1);
	}

	return 0;
}
