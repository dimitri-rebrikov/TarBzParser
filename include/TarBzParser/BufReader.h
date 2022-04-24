#ifndef _BUF_READER_H
#define _BUF_READER_H

#include <stdio.h>

#define BUF_READER_BUFFER_SIZE 512

/**
 * This reader is for use in the situations where there is no guarantee 
 * that the data loaded from the parent reader can be processed at one call 
 * so this reader introduce a intermediate buffer in wich the data are read from the parent reader into 
 * an then can be used by multiple calls.
 * 
 * The concrete usage is the implemntation of the bzip2 reader where the compact imput stream produces the ouput of much bigger side 
 * so the size of the output buffer might be not suffcient to fit the data read from the parrent reader. 
 * So the remaining input data are stored in the buffer for the next call.
 */

/**
 * Simple reader function abstraction
 */
typedef size_t (*ParentReader_t)(void *stream, char *buffer, size_t size);

/**
 * Structure holding the abstract reader, the data stream to read data from 
 */
typedef struct Reader {
    ParentReader_t parentReader; // pointer to the function reading the data from stream 
    void* parentStream; // the abstract stream with the data
} Reader_t;

/**
 *  Structure holding the data buffer, its size and the current position
 */
typedef struct BufReader_buffer{
    char buf[BUF_READER_BUFFER_SIZE]; // the data buffer
    size_t size; // the size of the data in the buffer 
    size_t offset; // the current reader's position in the buffer, shall be set by the code using the data from the buffer
} BufReader_buffer_t;

/**
 * Structure holding the abstract reader, the data stream and the buffer to read the data into
 */
typedef struct BufReader {
    ParentReader_t parentReader; // pointer to the function reading the data from stream into the buffer
    void* parentStream; // the abstract stream with the data
    BufReader_buffer_t buffer; // the buffer from with the data theh shall be read after they are loaded from the parent reader
} BufReader_t;

/**
 * Inits the reader with the reader function and the stream the reader function shall read the data from
 */
void BufReader_init(BufReader_t* reader, ParentReader_t parentReader, void* parentStream);

/**
 * Reads the data from stream into the buffer using the reader function 
*/
void BufReader_read2buffer(BufReader_t* reader);

/**
 * Returns 1 if there are data remaining in the buffer. This relies on the offset which shall be adjusted by the code which uses the data from buffer.
*/
int BufReader_hasDataInBuffer(BufReader_t* reader);

#endif // _BUF_READER_H