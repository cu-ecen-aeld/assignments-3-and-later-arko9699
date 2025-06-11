#include<syslog.h>
#include<stdlib.h>

#include<sys/stat.h>
#include<fcntl.h>

#include<string.h>
#include<unistd.h>

int main (int argc, char* argv[]) {

	openlog("writer", LOG_CONS, LOG_USER);
	setlogmask(LOG_UPTO(LOG_DEBUG));

	if (argc != 3) {
		syslog(LOG_ERR, "Insufficient arguments");
		exit(1);
	}

	syslog(LOG_DEBUG, "Got arguments writefile %s and writestr %s", argv[1], argv[2]);

	int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

	if (fd == -1) {
		syslog(LOG_ERR, "Could not access file %s", argv[1]);
	}

	ssize_t wroteBytes = write(fd, argv[2], strlen(argv[2]));

	if (wroteBytes == -1) {
		syslog(LOG_ERR, "Could not write string %s to file %s", argv[2], argv[1]);
	}

	closelog();
}