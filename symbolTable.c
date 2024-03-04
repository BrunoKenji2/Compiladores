#include "symbolTable.h"

Symbol *hashTable[HASH_SIZE];

int hash(char *key)
{
    int temp = 0;
    int i;

    for (i = 0; key[i] != '\0'; i++)
    {
        temp = ((temp << SHIFT) + key[i]) % HASH_SIZE;
    }
    return temp;
}

void insertSymbol(char *name, int value)
{
    int index = hash(name);
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    newSymbol->value = value;
    newSymbol->next = NULL;

    if (hashTable[index] == NULL)
    {
        hashTable[index] = newSymbol;
    }
    else
    {
        Symbol *current = hashTable[index];

        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newSymbol;
    }
}

void removeSymbol(char *name)
{
    int index = hash(name);
    Symbol *current = hashTable[index];
    Symbol *previous = NULL;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (previous == NULL)
            {
                hashTable[index] = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

Symbol *findSymbol(char *name)
{
    int index = hash(name);
    Symbol *current = hashTable[index];

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// void printHashTable()
// {
//     for (int i = 0; i < HASH_SIZE; i++)
//     {
//         Symbol *current = hashTable[i];
//         printf("Index %d: ", i);
//         while (current != NULL)
//         {
//             printf("(%s, %d) ", current->name, current->value);
//             current = current->next;
//         }
//         printf("\n");
//     }
// }

// int main()
// {
//     insertSymbol("x", 10);
//     insertSymbol("x", 13);
//     insertSymbol("y", 20);
//     insertSymbol("z", 30);

//     Symbol *symbol = findSymbol("y");

//     printHashTable();

//     return 0;
// }
