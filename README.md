Huffman Coding File Compressor

A high-performance, lossless file compression tool implemented in C. This project demonstrates the application of the Huffman Coding algorithm to compress text files by assigning variable-length binary codes to characters based on their frequency.

🚀 Features

Lossless Compression: Reduces file size without losing any data.

Dynamic Memory Management: Efficient use of malloc and free to handle varying file sizes.

Data Structures: Implements Priority Queues (Min-Heap) and Binary Trees using struct pointers.

Bitwise Operations: Writes packed bits to binary files for maximum space efficiency.

Command Line Interface: Accepts input and output filenames via Command Line Arguments (CLA).

🛠️ Tech Stack

Language: C

Compiler: GCC

Core Concepts: Pointers, Structures, File Handling, Recursion, Dynamic Memory Allocation.

⚙️ How It Works

The algorithm follows a 4-step process:

Frequency Analysis: Reads the input file and counts the occurrence of every character.

Tree Construction:

Creates a leaf node for each character.

Inserts all nodes into a Min-Heap (Priority Queue) based on frequency.

Extracts the two smallest nodes, combines them into a new internal node, and re-inserts it until one root node remains.

Code Generation: Traverses the tree recursively (Left = 0, Right = 1) to generate unique binary codes for each character.

Encoding: Replaces characters in the input file with their corresponding binary codes and writes to the output file.

📦 Installation & Usage

1. Compile the Code

Use the GCC compiler to build the project.

gcc huffman.c -o huffman


2. Run the Compressor

Provide the input text file and the desired name for the compressed binary file.

./huffman input.txt compressed.bin


3. Decompress (Optional functionality)

If you implemented decompression:

./huffman -d compressed.bin output.txt


📊 Example

Input (input.txt):

BEEP BOOP BEER


Process:

B: Frequency 3

E: Frequency 4

P: Frequency 1

O: Frequency 2

R: Frequency 1

_: Frequency 2

Output:
The file size is reduced by replacing 8-bit ASCII characters with shorter bit sequences (e.g., E might become 01).

📂 Project Structure

.
├── huffman.c       # Main source code containing logic
├── huffman.h       # Header file with struct definitions (if applicable)
├── input.txt       # Sample text file for testing
├── README.md       # Project documentation
└── Makefile        # Build script (optional)


🤝 Contribution

Feel free to fork this repository and submit pull requests to improve the compression efficiency or add a GUI!

Created as part of the Data Structures & Algorithms curriculum.


(Content of this file were written using AI)

How It Works (The Logic)
This compressor implementation uses Huffman Coding, a lossless data compression algorithm that reduces file size by assigning variable-length binary codes to characters based on their frequency.

1. Frequency Analysis (The Census)
The program first scans the input file to build a frequency map (Histogram). It counts how many times each ASCII character appears.

Input: AAAAAAB

Map: A: 6, B: 1

2. Building the Huffman Tree (Bottom-Up Construction)
Instead of a fixed size (like standard 8-bit ASCII), we determine bit length dynamically:

Sorting: All characters are treated as "Nodes" and sorted by weight (frequency).

Merging: The two smallest nodes are removed, combined into a new "Parent" node (sum of their weights), and re-inserted into the list.

The "Queue Jump": This process repeats until only one node remains (the Root).

Result: Rare characters are "buried" deep in the tree (longer paths). Frequent characters float to the top (shorter paths).

3. Generating Prefix Codes
We traverse the tree from the Root to every Leaf (character):

Moving Left appends a 0.

Moving Right appends a 1.

Example: A frequent 'E' might be encoded as 0 (1 bit), while a rare 'Z' might be 1101 (4 bits).

4. Bit Packing (Physical Compression)
Standard C file operations write 8-bit bytes. To achieve real compression, we use a Bit Buffer:

Logical bits (0s and 1s) are accumulated in a 1-byte container using bitwise operators (<< for shifting, | for setting bits).

Once the container is full (8 bits), it is flushed to the output file as a single byte.

This ensures the output file is a true binary stream, not a text file of "0" and "1" characters.

Why This is Efficient
Standard ASCII: 'A' (65) = 01000001 (8 bits).

Huffman: If 'A' is frequent, it might become 1 (1 bit).

Result: We save 7 bits for every occurrence of 'A', leading to significant size reduction for text-heavy files.

This mechanism is purely a result of the Bottom-Up building process. It basically works like a "Reverse Tournament."Here is the logic in plain English: The "Losers" get buried, and the "Winners" stay at the top.1. The Mechanism: "Sinking" the Rare CharactersRemember your while loop that runs qsort?It always picks the two smallest numbers to merge.When you merge two nodes (say, Z and Q), they become children of a new Parent.Crucial Point: Being a "child" adds one extra bit to your code length (because you are now one step further away from the top).The Chain Reaction:Rare characters (e.g., 'Z', freq 1) are small. They get picked immediately in the first round. They become children. Code length = 1.Then their parent is usually still small. So the parent gets picked and merged again. Now 'Z' is a grandchild. Code length = 2.This keeps happening. 'Z' gets pushed deeper and deeper down the tree every time a merge happens above it.2. The Survival: "Floating" the Frequent CharactersNow look at a frequent character (e.g., 'E', freq 100).'E' is heavy (100).In the first round, qsort sees 1 and 2. It ignores 100.In the second round, it sees 5 and 10. It ignores 100.'E' sits there, waiting in the array, while everyone else is getting merged and buried.'E' only gets picked at the very end, when the only things left are massive chunks of the tree.Since 'E' enters the tree last, it ends up right near the Root.3. The Result (Visualized)Because 'E' is near the Root, its path is short (maybe just "Left").Because 'Z' was merged 10 times, its path is long (Left, Right, Right, Left...).
Example Tree:

      [ROOT]
      /    \
   [0]      [1]
  (E)      [Parent]
  freq:50   /    \
          [0]    [1]
         (A)   [Parent] 
        freq:20  /    \
               (Z)    (Q)
              freq:1  freq:1
To get to E: You go Left (0). Length: 1 bit.To get to Z: You go Right -> Right -> Left (110). Length: 3 bits.Summary:Low Frequency $\rightarrow$ Merged Early $\rightarrow$ Pushed Deep $\rightarrow$ More Bits.High Frequency $\rightarrow$ Merged Late $\rightarrow$ Stays at Top $\rightarrow$ Fewer Bits.This is why qsort was so important! It guarantees that the heavy weights always stay at the top.