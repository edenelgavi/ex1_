//
// Created by eden on 24/04/2022.
//



#include "AsciiArtTool.h"
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream)
{
    if (in_stream == NULL)
    {
        return NULL;
    }
    char temp ='\0';
    RLEList list = RLEListCreate();
    while (fscanf(in_stream,"%c",&temp)!=EOF)
    {
        RLEListAppend(list,temp);
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if( list == NULL|| out_stream ==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size = RLEListSize(list);
    RLEListResult result = RLE_LIST_SUCCESS;
    char temp = '\0';

    for (int i = 0; i < size && result == RLE_LIST_SUCCESS; i++)
    {
        temp= RLEListGet(list,i,&result);
        fprintf(out_stream,&temp);
    }

    return result;
}
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if( list == NULL|| out_stream ==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char* encoded_list = RLEListExportToString(list,&result);
    if(result != RLE_LIST_SUCCESS)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    fprintf(out_stream,encoded_list);
    return RLE_LIST_SUCCESS;

}
