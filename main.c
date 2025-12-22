#include <stdio.h>
#include <stdlib.h>

unsigned char buffer = 0;
int bitcount = 0;

char *codeTable[256];

void writeBit(int bit, FILE *fptr){
    buffer = buffer << 1; // shifiting all bits to the right
    if (bit == 1)
    {
        buffer = buffer | 1;
    }
    bitcount++;
    if (bitcount == 8)
    {
        fputc(buffer, fptr);
        bitcount = 0;
        buffer = 0;
    }
}

void flushBuffer(FILE *fptr){
    if (bitcount > 0)
    {
        int gap = 8 - bitcount;
        buffer = buffer << gap;

        fputc(buffer, fptr);

        buffer = 0;
        bitcount = 0; 
    }
    
}
void headerFile(FILE *outFile, int arr[], long total_count){
    fwrite(&total_count, sizeof(long), 1, outFile);
    fwrite(arr, sizeof(int), 256, outFile);
}

struct Node // Self-Referential Structure (type of recursion in which a struct calls itself)
{
    char character;
    int frequency;
    struct Node *left;
    struct Node *right; // holding the memory address of a node at the right (pointing towards it)
};

struct Node* newNode(char c, int freq) // a object new node under node
{ // need to pass the character and its frequency
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // first time using malloc assinging storage
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

void printCodes(struct Node* root, int arr[], int depth_count){ 
    // root is Where we are currently standing in the tree

    if (root == NULL)
        {
            return;
        }
    if (root->left == NULL && root->right == NULL)
    {
        // printf("Char: '%c' | Code:", root->character);
        // for (int i = 0; i < depth_count; i++)
        // {
        //     printf("%d", arr[i]);
        // }
        // printf("\n");
        char *newStr;
        newStr = (char*)malloc(depth_count+1); // +1 to store the null terminator (strig requires a null terminator)
        codeTable[root->character] = newStr;
        for (int i = 0; i < depth_count; i++)
        {
            newStr[i] = arr[i] + '0';
        }
        newStr[depth_count] = '\0';
    }

    if (root->left) // truthy value
    {
    arr[depth_count] = 0;
    printCodes(root->left, arr, depth_count + 1); // recursive function 
    }
    if (root->right)
    {
    arr[depth_count] = 1;
    printCodes(root->right, arr, depth_count + 1);
    }
    
}

int char_store[256] = {0};

int main (){
    FILE *fptr = fopen("read.txt", "r"); // opening a file
    FILE *outputFile = fopen("compressed.bin", "wb");

    int ch;
    int freq;
    long totalCharCount = 0;

    while((ch = fgetc(fptr)) != EOF) // ch = fgetc(fptr) != EOF prints boolean value true or false in terms of 1 and 0
    { // correct method is to first assign then compare (ch = fgetc(fptr))
        // ch = (char) ch; 
        // printf("%c = ", ch); // prints the character
        // ch = (int) ch; // typecasting 
        char_store[ch] += 1; // array char_store goes to the position 65 (becuase of the character) stores the value 1
        // printf("%d \n", char_store[ch]); // printing the value stored at that location 
        totalCharCount++;
    }

    for (int i = 0; i < 256; i++)
    {
        if  (char_store[i] > 0)
        {
            printf("%c : %d \n", i, char_store[i]); // we loop through values and for values greater than 0
            // first we print them as charcter and then the value stored in the array char_store at that index

        }
        
    }

    struct Node *nodeArray[256];
    int nodeCount = 0;

    for (int i = 0; i < 256; i++)
    {
        if  (char_store[i] > 0)
        {
            nodeArray[nodeCount] = newNode(i, char_store[i]);
            nodeCount++;
        }    
    }
    
    while (nodeCount > 1)
    {
        qsort(nodeArray, nodeCount, sizeof(struct Node*), compareNodes);
        struct Node* smallChild = nodeArray[0];
        struct Node* bigChild = nodeArray[1];

        int sumFreq = smallChild->frequency + bigChild->frequency;

        struct Node* parent = newNode('$', sumFreq); // check newNode for reference you'll get it
        parent->left = smallChild;
        parent->right = bigChild;

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

    rewind(fptr);
    headerFile(outputFile, char_store, totalCharCount);

    while ((ch = fgetc(fptr)) != EOF)
    {
        char *current_code = codeTable[ch];
       for (int i = 0; current_code[i] != '\0'; i++)
        {
            if (current_code[i] == '1')
            {
                writeBit(1,outputFile);
            } else {
                writeBit(0, outputFile);
            }
        }
    }
    flushBuffer(outputFile);
    
    
    fclose(fptr);
    fclose(outputFile);
    return 0;
}