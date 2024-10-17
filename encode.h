#ifndef ENCODE_H
#define ENCODE_H


/**
 * Encodes input data from a file into Base64-like format using emojis and prints the encoded output.
 *
 * @param file  The input file pointer containing the raw data to be encoded.
 */
void encode();

/**
 * Decodes a Base64-like encoded input stream from a file and prints the decoded characters.
 *
 * @param file  The input file pointer containing the encoded data.
 */
void decode();


#endif // ENCODE_H
