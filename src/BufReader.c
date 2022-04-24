#include "TarBzParser/BufReader.h"


void BufReader_init(BufReader_t* reader, ParentReader_t parentReader, void* parentStream) {
    reader->parentReader = parentReader;
    reader->parentStream = parentStream;
    reader->buffer.size = 0;
    reader->buffer.offset = 0;
}

void BufReader_read2buffer(BufReader_t* reader) {
    int read = reader->parentReader(reader->parentStream, reader->buffer.buf, BUF_READER_BUFFER_SIZE);
    reader->buffer.size = read;
    reader->buffer.offset = 0;
}

int BufReader_hasDataInBuffer(BufReader_t* reader) {
    if(reader->buffer.size > reader->buffer.offset) {
        return 1;
    } else {
        return 0;
    }
}