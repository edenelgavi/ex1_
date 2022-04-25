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

    RLEList lastNode = list->next;
    while(lastNode->next)
    {
        lastNode = lastNode->next;
    }

    if (lastNode->letter == value)
    {
        lastNode->num++;
        return RLE_LIST_SUCCESS;
    }

    lastNode->next = RLEListCreate();
    if (!lastNode->next)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    (lastNode->next)->letter = value;
    (lastNode->next)->num = 1;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return -1;
    }

    int counter = 0;
    RLEList temp = list;
    while(temp)
    {
        counter += temp->num;
        temp = temp->next;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size = RLEListSize(list);
    if (index > size || index < 0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    if (index <= list->num)
    {
        if (list->num > 1)
        {
            --list->num;
            return RLE_LIST_SUCCESS;
        }
        list->letter = (list->next)->letter;
        list->num = (list->next)->num;
        (list->next)->num = 1;
        index = list->num;
    }

    RLEList nodeBeforeIndex = list;
    index -= nodeBeforeIndex->num;

    while ((nodeBeforeIndex->next)->num < index)
    {
        nodeBeforeIndex = nodeBeforeIndex->next;
        index -= nodeBeforeIndex->num;
    }

    if ((nodeBeforeIndex->next)->num > 1)
    {
        --(nodeBeforeIndex->next)->num;
        return RLE_LIST_SUCCESS;
    }

    RLEList nodeAtIndex = nodeBeforeIndex->next;
    nodeBeforeIndex->next = nodeAtIndex->next;
    free(nodeAtIndex);
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if (index >= RLEListSize(list) || index < 0)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    RLEList nodeAtIndex = list;
    while (nodeAtIndex->num < index)
    {
        index -= nodeAtIndex->num;
        nodeAtIndex = nodeAtIndex->next;
    }

    *result = RLE_LIST_SUCCESS;
    return nodeAtIndex->letter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int numOfNodes = 0;
    RLEList temp = list;
    while (temp)
    {
        numOfNodes++;
        temp = temp->next;
    }

    char *out = malloc(sizeof(*out)*numOfNodes*3);
    if (out == NULL)
    {
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }

    temp = list;

    for (int i = 0; i < 3*numOfNodes; i += 3)
    {
        out[i] = temp->letter;
        out[i + 1] = (char)temp->num;
        out[i + 2] = '\n';
        temp = temp->next;
    }

    *result = RLE_LIST_SUCCESS;
    return out;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList temp = list;
    while (temp) {
        temp->letter = map_function(temp->letter);
        temp = temp->next;
    }
    return RLE_LIST_SUCCESS;
}