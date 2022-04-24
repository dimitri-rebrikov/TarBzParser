#include <stdio.h>
#include "BzReader.h"

/** 
 * abstract reader function 
 */
size_t readFromFile(void* f, char* buffer, size_t size) {
    return fread(buffer, sizeof(char), size, (FILE*)f);
}

int main() {
    bz_stream bStream;
    char  buf[BUF_READER_BUFFER_SIZE];

    FILE* in  = fopen ("../test/BzReaderTest1.txt.bz2", "r" );
    if (!in ) {
         fprintf(stderr, "cannot open file for read");
         return -1;
    }

    FILE* out = fopen("../test/BzReaderTest1.txt.tmp", "w+" );
    if(!out) {
        fprintf(stderr, "cannot open file to write");
        return -1;
    }

    BufReader_t reader;
    BufReader_init(&reader, &readFromFile, in);

    BzReader_handle_t bzHandle;

    if(BzReader_init(&bzHandle, &reader)!=0) {
        fprintf(stderr, "error during bzReader_init\n");
        return -1;
    }

    int read;
    do {
        read = BzReader_read(&bzHandle, buf, sizeof(buf));
        if(read > 0) {
            printf("Decompressed %d bytes \n", read);
            fwrite(buf, sizeof(char), read, out);
        }
    } while (read == sizeof(buf));

    BzReader_close(&bzHandle);

    fclose(in);
    fclose(out);
    
}