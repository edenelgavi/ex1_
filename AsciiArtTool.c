//
// Created by eden on 24/04/2022.
//



#include "AsciiArtTool.h"
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream)
{

    char* temp =" ";
    RLEList list = RLEListCreate();
    while ( fscanf(in_stream,"%c",*temp)!=EOF)
    {
        RLEListAppend(list,*temp);
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
    RLEListResult temp_result;
    RLEList temp_list = list;
    char temp = RLEListGet(list,0,&temp_result);
    fprintf(out_stream,"%c",temp);
    while (size)
    {
        RLEListRemove(temp_list,0);
        fprintf(out_stream,"%c",temp_list);
        size--;
    }

    return RLE_LIST_SUCCESS;
}
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if( list == NULL|| out_stream ==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult temp_result;
    char* encoded_list = RLEListExportToString(list,&temp_result);
    while (encoded_list)
    {
        fprintf(out_stream,"%c",encoded_list);
        encoded_list--;
    }
    return RLE_LIST_SUCCESS;

}
