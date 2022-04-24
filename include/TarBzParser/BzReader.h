#include "bzlib.h"
#include "BufReader.h"

/**
 * This reader can unpack bzip2 data from an abstract data stream
 */

/**
 * Structure holding the context data for the bz reader
 */
typedef struct BzReader_handle {
    bz_stream bStream; // the actual bzip stream to process
    BufReader_t* reader; // the reader to get the source bzip data from
} BzReader_handle_t;

/*
 * Inits the bz reader handle with provided reader
 */
int BzReader_init(BzReader_handle_t* handle, BufReader_t* reader);

/*
 * Reads the bzip2 data from reader's hanlde into the output buffer
 */
size_t BzReader_read(BzReader_handle_t* handle, char* outputBuffer, size_t outputBufferSize);


/*
 * Closes the reader
 */
void BzReader_close(BzReader_handle_t* handle);