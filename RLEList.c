//
// Created by eden on 24/04/2022.
//

#include "RLEList.h"
#include <stdlib.h>


struct RLEList_t{
    int num;
    char letter;
    struct RLEList_t* next;
};

RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
    if (!list)
    {
        return NULL;
    }
    list->num = 0;
    list->letter = '\0';
    list->next = NULL;
    return list;
}

void RLEListDestroy(RLEList list)
{
    if (list == NULL)
    {
        return;
    }
    RLEListDestroy(list->next);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL || value == '\0')
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while(list->next != NULL)
    {
        list = list->next;
    }
    if(list->num==0 && list->letter =='\0')
    {
        list->num =1;
        list->letter = value;
        return RLE_LIST_SUCCESS;
    }
    if (list->letter == value)
    {
        list->num++;
        return RLE_LIST_SUCCESS;
    }
    list->next = RLEListCreate();
    if(list->next==NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    list=list->next;
    list->num = 1;
    list->letter = value;
    list->next=NULL;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return -1;
    }
    int counter = 0;
    while(list!= NULL)
    {
        counter += list->num;
        list = list->next;
    }
    return counter;
}


char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    int size = RLEListSize(list);
    if (index >= size || index < 0)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    int repetitions =0;
    while (repetitions + list->num <=index)
    {
        repetitions = repetitions + list->num;
        list = list->next;
    }
    char letter=list->letter;
    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return letter;

}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int length = 0;
    RLEList counterForList = list;
    int indexOfNumber = 0;
    int counter;
    while(counterForList!=NULL)
    {
        if((list->letter != '\0')&&(list->num>0))
        {
            counter = list->num;

            while(counter!=0){
                indexOfNumber++;
                counter/=10;
            }
            length+=indexOfNumber+2;
            counterForList = counterForList->next;
        } else return NULL;
    }
    char *out = malloc(length + 1);
    if (out == NULL)
    {
        if(result != NULL)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }

        return NULL;
    }
    int i = 0;
    int countForNum;
    int numberForNum;
    while(list)
    {
        out[i] = list->letter;
        countForNum =0;
        numberForNum = list->num;
        while (numberForNum!=0){
            countForNum++;
            numberForNum/=10;
        }
        numberForNum = list->num;
        for (int j = countForNum; j >0; j--)
        {
            out[i+j] = (char)(numberForNum%10 +'0');
            numberForNum/=10;
        }
        i+=countForNum+1;
        out[i++] = '\n';
        list = list->next;
    }

    if(result!= NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }

    return out;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList temp = list;
    if( temp->num == 0 && temp->letter=='\0')
    {
        temp = temp->next;
    }
    while (temp)
    {
        temp->letter = map_function(temp->letter);
        temp = temp->next;
    }

    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size = RLEListSize(list);
    if (index >= size || index < 0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList indexBefore = list;
    RLEList tempList = list;
    int repetitions =0;
    while(repetitions + tempList->num < index)
    {
        repetitions += tempList->num;
        indexBefore = tempList;
        tempList = tempList->next;
    }
    tempList=indexBefore->next;
    if(tempList->num>1)
    {
        tempList->num--;
        return RLE_LIST_SUCCESS;
    }
    indexBefore->next=tempList->next;
    free(tempList);
    RLEList temp=indexBefore->next;
    if (indexBefore->letter == temp->letter){
        indexBefore->num+=temp->num;
        indexBefore->next=temp->next;
        free(temp);
        }


        return RLE_LIST_SUCCESS;

}
