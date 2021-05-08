//Main function

#include "AVL.c"

int main(void) //added flushes where necessary
{
    NODE *root = NULL;
    NODE *found = NULL;
    char word[WORD_LEN];
    char def[DEF_LEN];
    int choice = 0;
    int len = 0;
    char filename[20];

    while (choice != 6) //fixed spelling error and now the while loop waits for 6 instead of only printing at 6
    {
        printf("---------------------------------------\n");
        printf(" 1   -   Build AVL Tree from File\n");
        printf(" 2   -   Insert New Entry\n");
        printf(" 3   -   Delete Entry\n");
        printf(" 4   -   Search for Entry\n");
        printf(" 5   -   Print the Tree Alphabetically\n");
        printf(" 6   -   Quit the Program\n");
        printf("---------------------------------------\n");
        printf("Enter a Menu Selection: ");
        fflush(stdout);
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        //Build AVL Tree from File
        case 1:
        {


            printf("\nFile name: ");
            fflush(stdout);
            scanf("%s", filename);
            fflush(stdin);
            //Read File

            root = treeFromFile(filename,root);
            if (root==NULL)
            {
                printf("\nFailed to Build BST.\n");

            }
            else
            {
                printf("\nSuccess, BST Built!\n\n");
            }

            break;
        }

        //Insert New Entry
        case 2:
        {
            printf("\nWord to Insert: ");
            fflush(stdout);
            fgets(word, sizeof(def), stdin);
            fflush(stdin);
            //Read

            len = strlen(word);
            if (word[len - 1] == '\n')
            {
                word[len - 1] = 0;
            }

            printf("Definition: ");
            fflush(stdout);
            fgets(def, sizeof(def), stdin);
            fflush(stdin);
            //Read

            len = strlen(def);
            if (def[len - 1] == '\n') //fixed index for def array so it checks and deletes the right spot of the string
            {
                def[len-1] = 0;
            }

            root = insertNode(root, strlwr(word), def); //got rid of loop and will make sure that a node is always inserted and the root is always returned


            printf("\nEntry Successfully Inserted!\n\n");
            break; //added breaks
            //end
        }

        //Delete Entry
        case 3:
        {
            printf("\nWord to Delete: ");
            fflush(stdout);
            fgets(word, sizeof(word), stdin);
            fflush(stdin);
            //Read

            len = strlen(word);
            if (word[len - 1] == '\n') //fixed word array index
            {
                word[len-1] = 0;
            }

            root = deleteNode(root, strlwr(word));

            printf("\nEntry Successfully Removed!\n\n");
            break; //added breaks
            //end
        }

        //Search for Entry
        case 4:
        {
            printf("\nWord to Find: ");
            fflush(stdout);
            fgets(word, sizeof(word), stdin);
            fflush(stdin);
            //Read

            len = strlen(word);
            if (word[len -1] == '\n') //fixed the word array indexes
            {
                word[len-1] = 0;
            }

            found = searchNode(root, strlwr(word));

            if (found == NULL)
            {
                printf("\nEntry Not Found.\n\n");
            }
            else
            {
                printf("\nEntry Found!\n");
                printf("\nWord: %s", found->word);
                printf("\nDefinition: %s\n\n", found->def);
            }

            found = 0;

            free(found);
            break; //added breaks
        }

        //Print Tree In-Order
        case 5:
        {
            printf("\n");
            printAVL(root,POST);
            printf("\n");
            //end
            break; //added breaks
        }

        //Quit the Program
        case 6:
        {
            printf("\nClosing the Program...\n\n");
            return 0; //ends program
            //end
        }

        default:
        {
            printf("\nInvalid Selection, Choose Again.\n\n");
            break;   //added break
        }
        }
    }
}
