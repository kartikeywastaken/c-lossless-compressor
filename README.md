# Huffman Coding File Compressor

A high-performance, file compression tool implemented in C. 
This project demonstrates the application of the **Huffman Coding** algorithm to compress text files by replacing standard 8-bit ASCII characters with variable-length binary codes based on frequency.

> **Status:** Functional Prototype (Academic Project)

## 🚀 Features
- **Lossless Compression:** Reduces file size significantly without losing a single bit of data.
- **Dynamic Memory Management:** Efficient use of `malloc` and `free` to handle varying file sizes.
- **Bitwise Optimization:** Writes packed binary data (using bit buffers) rather than text strings for true storage efficiency.
- **Custom Data Structures:** Implements Priority Queues (Min-Heap) and Binary Trees from scratch.
- **Command Line Interface:** Accepts input and output filenames via standard arguments.

## 🛠️ Tech Stack
- **Language:** C (C99 Standard)
- **Compiler:** GCC
- **Core Concepts:** Pointers, Structs, Recursion, Bitwise Operators, File I/O.

## 📦 Installation & Usage

### 1. Compile the Code
Use GCC to build the project.
```bash 
gcc main.c -o compressor
Execute it -> ./compressor
```

### 📊 Example
``` INPUT (input.txt): Hello World; 
  Character	 Frequency	Code (Approx)
     l	    3	         0
     o          2	         10
     H 	    1	         110
     e	    1	         1110
     W	    1	         11110 
```

## ⚙️ How It Works: The Algorithm

The program follows a 4-step process to achieve compression:

1.  **Frequency Analysis (The Census):** Scans the input file to build a histogram (frequency map) of every character.
2.  **Tree Construction (The Tournament):**
    * Characters are treated as leaf nodes and inserted into a **Min-Heap**.
    * The two rarest nodes are extracted, combined into a parent node, and re-inserted.
    * This repeats until one "Root" node remains.
3.  **Code Generation:** Traverses the tree recursively (Left = `0`, Right = `1`) to assign unique binary codes.
4.  **Bit Packing:** The logical codes are packed into 8-bit bytes and written to the output file using bitwise shifting (`<<` and `|`).



## Visualising The Logic
      [ROOT]
      /    \
    (0)    (1)
    (E)   [Parent]   <-- Frequent 'E' is just 1 step away!
          /      \
        (0)      (1)
        (A)    [Parent]
               /      \
             (Z)      (Q) <-- Rare 'Z' is 3 steps away.


## 📂 Project Structure
``` .
├── main.c           # Main source code containing logic
├── huffman.h        # Header file with struct definitions (if applicable)
├── input.txt        # Sample text file for testing
├── compressed.bin   # Output binary file (generated)
└── README.md        # Project documentation```

