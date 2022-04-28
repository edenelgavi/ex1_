#define encoded "-e"
#define inverted "-i"
#include "AsciiArtTool.h"
#include "RLEList.h"
#include <string.h>
char change(char value);


int main(int argc,char**argv)
{
    if(argc != 4)
    {
        return 0;
    }
    char *flags = argv[1];
    FILE * source = fopen(argv[2],"r");

    if(!source)
    {
        return 0;
    }
    RLEList list = asciiArtRead(source);
    fclose(source);
    if (list == NULL)
    {
        return 0;
    }
    FILE * target = fopen(argv[3],"w");
    if(!target)
    {
        return 0;
    }
    if(strcmp(flags,encoded) == 0)
    {
        asciiArtPrintEncoded(list,target);
    }

    else if(strcmp(flags,inverted) == 0)
    {
        RLEListMap(list,&change);
        asciiArtPrint( list, target);
    }
    fclose(target);
    RLEListDestroy(list);
    return 0;

}

char change(char value)
{
    if(value == ' ')
    {
        return '@';
    }
    if (value == '@')
    {
        return ' ';
    }
    return value;
}

