#include <stdio.h>
#include <stdlib.h>

struct Node // Self-Referential Structure (type of recursion in which a struct calls itself)
{
    char character;
    int frequency;
    struct Node *left;
    struct Node *right; // holding the memory address of a node at the right (pointing towards it)
};

struct Node* newNode(char c, int freq)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // first time using malloc
    newNode->frequency = freq;
    newNode->character = c;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
};

// This function is called by qsort automatically.
// qsort asks: "Here are two items from your array. Which one is bigger?"
int compareNodes(const void* a, const void* b){

    // STEP A: The Setup
    // qsort doesn't know we are sorting 'struct Node*'. It just sees generic 'void*' pointers.
    // We are looking at a SLOT in the array. Inside that slot is a pointer to our Node.
    // So 'a' is a "Pointer (to the slot) -> pointing to a Pointer (the node)".
    // Type: struct Node**

    struct Node** nodeA = (struct Node**)a;
    struct Node** nodeB = (struct Node**)b;

    // STEP B: The Unlock (Dereferencing)
    // We have the address of the SLOT. We want the value INSIDE the slot.
    // The value inside is the address of the actual Node on the heap.
    // We use '*' to "open the slot".

    struct Node* actualNodeA = *nodeA;
    struct Node* actualNodeB = *nodeB;
    
    // STEP C: The Comparison
    // Now we have the actual Nodes. We can look at their frequency numbers.
    // If (5 - 2) = 3 (Positive), it means A is bigger.
    // If (2 - 5) = -3 (Negative), it means A is smaller.

    // if (actualNodeA->frequency > actualNodeB->frequency)
    // {
    //     return 1;

    // }
    // if (actualNodeA->frequency < actualNodeB->frequency)
    // {
    //     return -1;
    // }
    // if(actualNodeA->frequency == actualNodeB->frequency){
    //     return 0;
    // }
    return (actualNodeA->frequency - actualNodeB->frequency);
    
}

void printCodes(struct Node* root, int arr[], int top){
    if (root == NULL)
        {
            return;
        }
    if (root->left == NULL && root->right == NULL)
    {
        printf("Char: '%c' | Code:", root->character);
        for (int i = 0; i < top; i++)
        {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
    if (root->left)
    {
    arr[top] = 0;
    printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
    }
    
}

int bucket[256] = {0};

int main (){
    FILE *fptr = fopen("read.txt", "r"); // opening a file

    int ch;
    int freq;

    while((ch = fgetc(fptr)) != EOF) // ch = fgetc(fptr) != EOF prints boolean value true or false in terms of 1 and 0
    { // correct method is to first assign then compare (ch = fgetc(fptr))
        // ch = (char) ch; 
        // printf("%c = ", ch); // prints the character
        // ch = (int) ch; // typecasting 
        bucket[ch] += 1; // array bucket at the position 65 (becuase of the character) stores the value 1
        // printf("%d \n", bucket[ch]); // printing the value stored at that location 
    }

    for (int i = 0; i < 256; i++)
    {
        if (bucket[i] > 0)
        {
            printf("%c : %d \n", i, bucket[i]); // we loop through values and for values greater than 0
            // first we print them as charcter and then the value stored in the array bucket at that index

        }
        
    }

    struct Node *nodeArray[256];
    int nodeCount = 0;

    for (int i = 0; i < 256; i++)
    {
        if (bucket[i] > 0)
        {
            nodeArray[nodeCount] = newNode(i,bucket[i]);
            nodeCount++;
        }    
    }
    while (nodeCount > 1)
    {
        qsort(nodeArray, nodeCount, sizeof(struct Node*), compareNodes);
        struct Node* left = nodeArray[0];
        struct Node* right = nodeArray[1];

        int sumFreq = left->frequency + right->frequency;

        struct Node* parent = newNode('$', sumFreq); // check newNode for reference you'll get it
        parent->left = left;
        parent->right = right;

        nodeArray[0] = parent;

        for (int i = 1; i < nodeCount - 1 ; i++)
        {
            nodeArray[i] = nodeArray[i + 1]; // shifting everything towards left 
        }
        nodeCount--;

    }
    struct Node* root = nodeArray[0]; 

    int codeBuffer[100];
    printCodes(root, codeBuffer, 0);
    
    
    fclose(fptr);
    return 0;
}