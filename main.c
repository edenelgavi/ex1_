#define encoded 'e'
#define inverted 'i'
#include "AsciiArtTool.h"
#include "RLEList.h"
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
    FILE * target = fopen(argv[3],"w");
    if(!target)
    {
        fclose(source);
        return 0;
    }
    if(flags[0] != '-' || (flags[1]!= encoded||flags[1]!=inverted) )
    {
        fclose(source);
        fclose(target);
        return 0;
    }
    if(flags[1]== encoded)
    {
        RLEList list = asciiArtRead(source);
        asciiArtPrintEncoded(list,target);
        fclose(source);
        fclose(target);
        RLEListDestroy(list);
        return 0;
    }

    if(flags[1]== inverted)
    {
        RLEList list = asciiArtRead(source);
        RLEListMap(list,change);
        asciiArtPrint( list, target);
        fclose(source);
        fclose(target);
        RLEListDestroy(list);
        return 0;
    }

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

