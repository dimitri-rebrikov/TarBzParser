/*
 * The implementation is deriver from the untar.c from libArchive
 * Written by Tim Kientzle, March 2009 and released into the public domain.
 */

#include <stdlib.h>
#include <string.h>

#include "TarParser.h"

/* Parse an octal number, ignoring leading and trailing nonsense. */
static int
parseoct(const char *p, size_t n)
{
	int i = 0;

	while ((*p < '0' || *p > '7') && n > 0) {
		++p;
		--n;
	}
	while (*p >= '0' && *p <= '7' && n > 0) {
		i *= 8;
		i += *p - '0';
		++p;
		--n;
	}
	return (i);
}

/* Returns true if this is TAR_BLOCK_SIZE zero bytes. */
static int
is_end_of_archive(const char *p)
{
	int n;
	for (n = 511; n >= 0; --n)
		if (p[n] != '\0')
			return (0);
	return (1);
}

/* Verify the tar checksum. */
static int
verify_checksum(const char *p)
{
	int n, u = 0;
	for (n = 0; n < TAR_BLOCK_SIZE; ++n) {
		if (n < 148 || n > 155)
			/* Standard tar checksum adds unsigned bytes. */
			u += ((unsigned char *)p)[n];
		else
			u += 0x20;

	}
	return (u == parseoct(p + 148, 8));
}

void TarParser_parse(Reader_t* reader, TarParser_callback_t* callback)
{
	char buff[TAR_BLOCK_SIZE];
	size_t bytes_read;
	int filesize;

	for (;;) {
		bytes_read = reader->parentReader(reader->parentStream, buff, TAR_BLOCK_SIZE);
		if (bytes_read < TAR_BLOCK_SIZE) {
			fprintf(stderr,
			    "Short read: expected %d, got %d\n",
			 TAR_BLOCK_SIZE, (int)bytes_read);
			return;
		}
		if (is_end_of_archive(buff)) {
			printf("End of archve\n");
			return;
		}
		if (!verify_checksum(buff)) {
			fprintf(stderr, "Checksum failure\n");
			return;
		}
		filesize = parseoct(buff + 124, 12);
		switch (buff[156]) {
		case '1':
			printf(" Ignoring hardlink %s\n", buff);
			break;
		case '2':
			printf(" Ignoring symlink %s\n", buff);
			break;
		case '3':
			printf(" Ignoring character device %s\n", buff);
			break;
		case '4':
			printf(" Ignoring block device %s\n", buff);
			break;
		case '5':
			printf(" Processing dir name %s\n", buff);
            callback->dirCallback(callback->context, buff);
            filesize = 0;
			break;
		case '6':
			printf(" Ignoring FIFO %s\n", buff);
			break;
		default:
			printf(" Processing file name %s\n", buff);
            callback->fileCallback(callback->context, buff);
			break;
		}
		while (filesize > 0) {
			bytes_read = reader->parentReader(reader->parentStream, buff, TAR_BLOCK_SIZE);
			if (bytes_read < TAR_BLOCK_SIZE) {
				fprintf(stderr,
				    "Short read Expected TAR_BLOCK_SIZE, got %d\n",
				    (int)bytes_read);
				return;
			}
			if (filesize < TAR_BLOCK_SIZE)
				bytes_read = filesize;
			
            printf(" Processing data %d bytes\n", (int)bytes_read);
            callback->dataCallback(callback->context, buff, bytes_read);

			filesize -= bytes_read;
		}
	}
}