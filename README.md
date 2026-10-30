# File Compression Tool (Huffman Coding)

A C++ program that shrinks the size of text files to save storage space. 
It uses the Huffman Coding Algorithm to compress files into a binary format and decompress 
them back safely.

## Features
- **Compresses Files:** Converts normal text files (.txt) into a smaller binary file format.
- **Decompresses Files:** Restores the compressed file back to its original text without any data loss.
- **Data Structures Used:** Built using **Binary Trees** and **Min-Heaps (Priority Queues)** in C++.

## How it Works
1. The program reads a text file and counts how often each letter appears.
2. It assigns shorter binary codes (like 0 or 1) to letters that appear most frequently.
3. It creates a compressed file and can reverse the process to give back the original text.
