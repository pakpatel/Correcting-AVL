//AVL Tree Functions

#include "header.h"




NODE *treeFromFile(char *filename, NODE *root)
{
	//got rid of cwd because I wasn't sure that it was needed after my changes
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("ERROR - Unable to Open File: %s", filename);
        return NULL;
    }

    char word[WORD_LEN];
    char def[DEF_LEN];
    //got rid of root here because it caused errors when building to existing tree
    //got rid of temp because it was no longer need for this version

    while (fscanf(fp, "%s\t%[^\n]", word,def) != EOF)// instead of getting word and def seperatily now both gotten at once and no longer need to check for unnecessary characters
    {
        root = insertNode(root, strlwr(word), def); //got rid of &s
    }
    fclose(fp);
    return root;
}

NODE *addNode(char *word, char *def) //made sure words were lower case
{
    NODE *newLeaf = (NODE *)malloc(sizeof(NODE));

    newLeaf->word = strlwr(word);
    newLeaf->def = strlwr(def);
    newLeaf->LC = NULL;
    newLeaf->RC = NULL;
    newLeaf->level = 0;
    newLeaf->bal = EH;

    return newLeaf;
}

NODE *insertNode(NODE *root, char *word, char *def)
{
    if (root == NULL)
    {
        return addNode(word, def);
    }

    int diff = strcmp(word, root->word);

    if (diff < 0) //got rid of <= because the = would result in node being inserted in wrong place
    {
        root->LC = insertNode(root->LC, word, def);
    }
    else if (diff > 0)
    {
        root->RC = insertNode(root->RC, word, def);
    }
    else if (diff == 0)
    {
    	printf("That word is already in the list and will not be added.\n");
        return root;
    }

    root->level = max(level(root->LC), level(root->RC));
    root->bal = findBalance(root);

    if (root->bal > 1)
    {
        if (root->LC->bal > 0)
        {
            return rotateRight(root);
        }
        else if (root->LC->bal < 0)
        {
            root->LC = rotateRight(root->LC);
            return rotateRight(root);
        }
    }
    else if (root->bal < -1)
    {
        if (root->RC->bal < 0)
        {
            return rotateLeft(root);
        }
        else if (root->RC->bal > 0)
        {
            root->RC = rotateLeft(root->RC);
            return rotateLeft(root);
        }
    }

    return root;
}

NODE *searchNode(NODE *root, char *toFind)
{
    if (root != NULL)
    {
        int diff = strcmp(root->word, toFind); //could have also swapped the arguments of the compare

        if (diff == 0)
        {
            return root;
        }
        else if (diff < 0) //had to swap left and right cases since the signs were reversed
        {
            return searchNode(root->RC, toFind);
        }
        else if (diff > 0)
        {
            return searchNode(root->LC, toFind);
        }
    }
    else
    {
        return root;
    }
    return root;
}

NODE *deleteNode(NODE *root, char *toDel)
{
    if (root != NULL)
    {
        int diff = strcmp(root->word, toDel);

        if (diff == 0)
        {
            NODE *temp = NULL;
            int option = 0;
            int child = 0;

            //Check for Children
            if (root->LC != NULL)
            {
                option++;
                child = child + 1;
            }
            if (root->RC != NULL)
            {
                option++;
                child = child + 2;
            }

            switch (option)
            {
            //One Child
            case 1:
            {
                if (child == 1)
                {
                    temp = root->LC;
                }
                else if (child == 2)
                {
                    temp = root->RC;
                }

                *root = *temp;
                //Copy data
                break; //added breaks
            }

            //Two Children
            case 2:
            {
                temp = minNode(root->RC);
                root->word = temp->word;
                root->def = temp->def;
                root->RC = deleteNode(root->RC, temp->word);
                break; //added breaks
            }

            //No Children
            default:
            {
                temp = root;
                root = NULL;
                //Dereference
            }
            }
        }
        else if (diff > 0)
        {
            root->LC = deleteNode(root->LC, toDel);
        }
        else if (diff < 0)
        {
            root->RC = deleteNode(root->RC, toDel);
        }
    }
    else
    {
        return NULL;
    }

    if (root == NULL)
    {
        return root;
    }

    root->level = max(level(root->LC), level(root->RC));
    root->bal = findBalance(root);

    if (root->bal > 1)
    {
        root->LC->bal = findBalance(root->LC);
        if (root->LC->bal > 0)
        {
            return rotateRight(root);
        }
        else if (root->LC->bal < 0)
        {
            root->LC = rotateLeft(root->LC);
            return rotateRight(root);
        }
    }
    else if (root->bal < -1)
    {
        root->RC->bal = findBalance(root->RC);
        if (root->RC->bal < 0)
        {
            return rotateLeft(root);
        }
        else if (root->RC->bal > 0)
        {
            root->RC = rotateRight(root->RC);
            return rotateLeft(root);
        }
    }

    return root;
}

NODE *minNode(NODE *node)
{
    NODE *temp = node;

    while (temp->LC != NULL)
    {
        temp = temp->LC;
    }

    return node;
}

NODE* rotateRight(NODE* root)
{
    NODE *L = root->LC;
    NODE *LR = L->RC;

    L->RC = root;
    root->LC = LR;

    root->level = max(level(root->LC), level(root->RC)) + 1;
    L->level = max(level(L->LC), level(L->RC)) + 1;

    root->bal = findBalance(root);
    L->bal = findBalance(L);

    return L;
}

NODE *rotateLeft(NODE *root)
{
    NODE *R = root->RC;
    NODE *RL = R->LC;

    R->LC = root;
    root->RC = RL;

    root->level = max(level(root->LC), level(root->RC)) + 1;
    R->level = max(level(R->LC), level(R->RC)) + 1;

    root->bal = findBalance(root);
    R->bal = findBalance(R);

    return R;
}

void printAVL(NODE *root,int order) //changed switch from order+1 to just order since it was printing in post order instead of inorder
{
	if(root!= NULL){
        switch ((order))
        {
        //Pre-Order
        case 1:
        {
            printf("%s  -   %s\n\n", root->word, root->def);
            printAVL(root->LC, order);
            printAVL(root->RC, order);
            break;
        }

        //In-Order
        case 2:
        {
            printAVL(root->LC, order);
            printf("%s  -   %s\n\n", root->word, root->def);
            printAVL(root->RC, order);
            break;
        }

        //Post-Order
        case 3:
        {
            printAVL(root->LC, order);
            printAVL(root->RC, order);
            printf("%s  -   %s\n\n", root->word, root->def);
        }
        }
    }

}
