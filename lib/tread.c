#include "system.h"

#include "rpmio.h"

int timedRead(FD_t fd, void * bufptr, int length) {
    int bytesRead;
    int total = 0;
    char * buf = bufptr;
    fd_set readSet;
    struct timeval tv;

    while  (total < length) {
	FD_ZERO(&readSet);
	FD_SET(fdFileno(fd), &readSet);

	tv.tv_sec = 5;			/* FIXME: this should be configurable */
	tv.tv_usec = 0;

	if (select(fdFileno(fd) + 1, &readSet, NULL, NULL, &tv) != 1) 
	    return total;

	bytesRead = fdRead(fd, buf + total, length - total);

	if (bytesRead < 0)
	    return bytesRead;
	else if (bytesRead == 0) 
	    return total;

	total += bytesRead;
    }

    return length;
}
