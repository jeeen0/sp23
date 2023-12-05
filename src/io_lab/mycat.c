#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFF_SIZE 16

int main(int argc, char* argv[])
{
	int ifd, ofd;
	char* buff;
	ssize_t nreads, nwrites;

	if(argc < 2) {
		fprintf(stdout, "No arguments");
		return 0;
	} else if(argc == 2) {
		// output to stdout file  
		ifd = open(argv[1], O_RDONLY);
		if(ifd == -1) {
			fprintf(stdout, "Failed to open input file: %s", strerror(errno));
			return -1;
		}

	} else if(argc == 4 && !strcmp(argv[2], "into")) {
		// output to redirection file 
		ifd = open(argv[1], O_RDONLY);
		if(ifd == -1) {
			fprintf(stdout, "Failed to open input file: %s", strerror(errno));
			return -1;
		}

		ofd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(ofd == -1) {
			fprintf(stdout, "Failed to open output file: %s", strerror(errno));
			close(ifd);
			return -1;
		}

	} else {
		fprintf(stdout, "Wrong arguments");
		return 0;
	}

	// Allocate buffer 
	if(!(buff = (char*) malloc (sizeof(char) * BUFF_SIZE))){
		fprintf(stdout, "Failed to allocate memory");
		close(ifd);
		if(argc == 4 && !strcmp(argv[2], "into")) close(ofd);
		return -1;
	}

	// Copy files 
	while((nreads = read(ifd, buff, BUFF_SIZE)) > 0) {
		if(argc == 2) {
			if(write(STDOUT_FILENO, buff, nreads) != nreads) {
				fprintf(stdout, "Failed to write to stdout: %s", strerror(errno));
				close(ifd);
				free(buff);
				return -1;
			}
		} else if(argc == 4 && !strcmp(argv[2], "into")) {
			nwrites = write(ofd, buff, nreads);
			if(nwrites != nreads) {
				fprintf(stdout, "Failed to write to output file: %s", strerror(errno));
				close(ifd);
				close(ofd);
				free(buff);
				return -1;
			}
		}
	}

	if(nreads == -1) {
		fprintf(stdout, "Failed to read input file: %s", strerror(errno));
		close(ifd);
		if(argc == 4 && !strcmp(argv[2], "into")) close(ofd);
		free(buff);
		return -1;
	}

	// Close files 
	close(ifd);
	if(argc == 4 && !strcmp(argv[2], "into")) close(ofd);
	free(buff);

	return 0;
}
