//Header File


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define WORD_LEN 10
#define DEF_LEN 100

enum ORDER
{
    PRE,
    IN,
    POST
};
enum BALANCE
{
    LH = 1,
    EH = 0,
    RH = -1
};

typedef struct node
{
    struct node *LC;
    struct node *RC;
    char *word;
    char *def;
    int level;
    int bal;
} NODE;

int level(NODE *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->level;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

char *strlwr(char *word)
{
    unsigned char *a = (unsigned char *)word;

    while (*a)
    {
        *a = tolower((unsigned char)*a);
        a++;
    }

    return word;
}

int findBalance(NODE *node)
{
    if (node == NULL)
    {
        return EH;
    }
    else
    {
        return level(node->LC) - level(node->RC);
    }
}

NODE *addNode(char *word, char *def);
NODE *insertNode(NODE *root, char *word, char *def);
NODE *searchNode(NODE *root, char *toFind);
NODE *deleteNode(NODE *root, char *toDel);
NODE *minNode(NODE *node);
NODE *rotateRight(NODE *root);
NODE *rotateLeft(NODE *root);
void printAVL(NODE *root, int order);
