#include "TarParser.h"

/**
 * This parser is able to read the data from an abstract stream containing tar.bz2 data
 * and parse them calling the correspoinding callback functions provided by the consumer.
 */

/**
 * Parses the TAR.BZ2 stream from reader and uses callback to notify the consumer about entries found.
 * Returns 0 in case of success and -1 in case of failure
 */
int TarBzParser_parse(Reader_t* reader, TarParser_callback_t* callback);