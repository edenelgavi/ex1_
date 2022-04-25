//
// Created by eden on 24/04/2022.
//

#ifndef IWANTTODIE_ASCIIARTTOOL_H
#define IWANTTODIE_ASCIIARTTOOL_H



#include "RLEList.h"

/**
* asciiArtRead: reads the attached file and returns an RLE list of the characters
*
* @param in_stream - FILE object - contains said picture - If FILE is NULL nothing will be done
 * @return RLEList that contains the characters of the picture
*/
RLEList asciiArtRead(FILE* in_stream);

/**
* asciiArtPrint: writes a picture with the RLEList of the file
*
* @param list - an RLEList with the characters of the picture
 * @param stream_out - a FILE object for the printed picture
 * @return -
 * RLE_LIST_NULL_ARGUMENT - if a NULL was sent as one of the parameters
 * LIST_SUCCESS - if the encoding was done successfully.
*/

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
* asciiArtPrintEncoded: writes a picture with the RLEList of the file that has been compressed
*
* @param list - an RLEList with the characters of the picture
* @param stream_out - a FILE object for the printed picture
 * @return –
 * RLE_LIST_NULL_ARGUMENT - if a NULL was sent as one of the parameters
 * LIST_SUCCESS - if the encoding was done successfully.
*/

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //IWANTTODIE_ASCIIARTTOOL_H
