#include "bzlib.h"
#include "BzReader.h"

int BzReader_init(BzReader_handle_t* handle, BufReader_t* reader) {

    handle->bStream.next_in = NULL;
    handle->bStream.avail_in = 0;
    handle->bStream.bzalloc = NULL;
    handle->bStream.bzfree = NULL;
    handle->bStream.opaque = NULL;

    int bReturn = BZ2_bzDecompressInit(&(handle->bStream),0,0);

    if (bReturn != BZ_OK)
    {
        printf("Error occurred during BZIP initialization.  BZIP error code: %d\n", bReturn);
        return -1;
    }

    handle->reader = reader;
    return 0;
}

size_t BzReader_read(BzReader_handle_t* handle, char* outputBuffer, size_t outputBufferSize) {
    
    int bReturn;
    int outputBufferOffset = 0;

    do {
        if(!BufReader_hasDataInBuffer(handle->reader)) {
            BufReader_read2buffer(handle->reader);
            printf("Read: %d\n", handle->reader->buffer.size);
        }

        if(handle->reader->buffer.size > 0 ) {

            handle->bStream.next_in = handle->reader->buffer.buf + handle->reader->buffer.offset;
            handle->bStream.avail_in = handle->reader->buffer.size - handle->reader->buffer.offset;

            handle->bStream.next_out = outputBuffer + outputBufferOffset;
            handle->bStream.avail_out = outputBufferSize - outputBufferOffset;

            printf("decompress...\n");
            bReturn = BZ2_bzDecompress(&handle->bStream);

            if (bReturn == BZ_OK || bReturn == BZ_STREAM_END)
            {
                handle->reader->buffer.offset += (handle->reader->buffer.size - handle->reader->buffer.offset) - handle->bStream.avail_in;
                outputBufferOffset += (outputBufferSize - outputBufferOffset) - handle->bStream.avail_out;
                printf("read so far %d, wrote %d\n", handle->bStream.total_in_lo32, handle->bStream.total_out_lo32);
            }
            else
            {
                printf("Error occurred during BZIP decompression.  BZIP error code: %d\n", bReturn);
                return 0;
            }
        }

    } while (handle->reader->buffer.size > 0 && bReturn == BZ_OK && outputBufferOffset != outputBufferSize);
    return outputBufferOffset;
}

void BzReader_close(BzReader_handle_t* handle) {
    BZ2_bzDecompressEnd(&handle->bStream);
}

