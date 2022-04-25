#include <stdio.h>
#include "TarBzParser/BzReader.h"
#include "TarBzParser/TarParser.h"


size_t readFromBz(void* f, char* buffer, size_t size) {
    return BzReader_read(f, buffer, size);
}

int TarBzParser_parse(Reader_t* reader, TarParser_callback_t* callback) {

    BufReader_t fReader;
    BufReader_init(&fReader, reader->parentReader, reader->parentStream);

    BzReader_handle_t bzHandle;

    if(BzReader_init(&bzHandle, &fReader)!=0) {
        fprintf(stderr, "error during BzReader_init\n");
        return -1;
    }

    Reader_t bzReader;
    bzReader.parentReader = &readFromBz;
    bzReader.parentStream = &bzHandle;

    if(TarParser_parse(&bzReader, callback)!=0){
        fprintf(stderr, "error during TarParser_parse\n");
        return -1;
    }

}