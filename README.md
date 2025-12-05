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
