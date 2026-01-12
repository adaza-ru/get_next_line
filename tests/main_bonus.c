//cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1 = open("file1b.txt", O_RDONLY);
	int fd2 = open("file2b.txt", O_RDONLY);
	int fd3 = open("file3b.txt", O_RDONLY);
    char *line;
	int doraemon[10]= {fd1, fd2, fd2, fd3, fd2, fd3, fd3, fd1, fd1, fd2};
	int i = 0;

 	while (i < 10)
    {
		line = get_next_line(doraemon[i]);
        printf("%s", line);
        free(line);
		i++;
    }
    close(fd1);
	close(fd2);
	close(fd3);
    return (0);
}