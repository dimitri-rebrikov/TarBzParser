#include "BufReader.h"

#define TAR_BLOCK_SIZE 512

/**
 * This parser is able to read the data from an abstract stream 
 * and parse them calling the correspoinding callback functions provided by the consumer.
 */

/**
 * Structure containg the callbacks called by parser od corresponding entry found in the TAR stream
 */
typedef struct TarParser_callback {
    void (*dirCallback)(void* context, char* dirName);
    void (*fileCallback)(void* context, char* fileName);
    void (*dataCallback)(void* context, char* data, size_t dataSize);
    void* context; // the context for all callbacks
} TarParser_callback_t;

/**
 * Parses the TAR stream from reader and uses callback to notify the consumer about entries found.
 * Returns 0 in case of success and -1 in case of failure
 */
int TarParser_parse(Reader_t* reader, TarParser_callback_t* callback);