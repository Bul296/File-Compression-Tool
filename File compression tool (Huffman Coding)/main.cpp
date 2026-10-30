#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

//1. Node Structure
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char ch, int freq){
        this->ch = ch;
        this->freq = freq;
        this->left = this->right = nullptr;
    }
};

// Heap Comparator
struct compare {
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq;
    }
};

//2. Helper function to generate codes 
void generateCodes(Node* root, string str, unordered_map<char, string>& huffmanCode){
    if (!root) return;
    if (!root->left && !root->right){
        huffmanCode[root->ch] = str;
    }
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "0", huffmanCode);
}

// 3. Compress function (.txt to binary representation string)
void compressFile(string inputFileName, string outputFileName, unordered_map<char, string>& huffmanCode){
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()){
        cout<<"Error opening files!"<<endl;
        return;
    }

    char ch;
    string compressedData = "";
    while (inputFile.get(ch)) {
        compressedData += huffmanCode[ch];
     }

     // Storing the binary string in output file
     outputFile << compressedData;

     inputFile.close();
     outputFile.close();
     cout<<"Success : File compressed successfully to " << outputFileName << endl;
}

// 4. Decompress function 
void decompressFile(string compressedFileName, string decompressedFileName, Node* root){
    ifstream inputFile(compressedFileName);
    ofstream outputFile(decompressedFileName);

    if (!inputFile.is_open() || !outputFile.is_open()){
        cout<<"Error opening files!" << endl;
        return;
    }

    char bit;
    Node* current = root;
    while(inputFile >> bit) {
        if (bit == '0'){
            current = current->left;
        } else {
            current = current->right;
        }

        // leaf node reached
        if (!current->left && !current->right){
            outputFile << current->ch;
            current = root; // Reset to top for next character
        }
    }

    inputFile.close();
    outputFile.close();
    cout<< "Sucess : File decompressed successfully to" << decompressedFileName << endl;
}

// 5. Main execution logic
int main(){

    // a. pehle ek 'sample.txt' file manually bana lijiye jisme kuch text ho
    string text = "google step internship in indore";
    ofstream createInput("sample.txt");
    createInput << text;
    createInput.close();

    //b. calculate frequency
    unordered_map<char, int> freq;
    for (char ch : text){
        freq[ch]++;
    }

    //c. build min-heap
    priority_queue<Node* , vector<Node*> , compare> minHeap;
    for (auto pair : freq) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    //d. build tree
    while(minHeap.size() != 1){
        Node *left = minHeap.top(); minHeap.pop();
        Node *right = minHeap.top(); minHeap.pop();
        Node *sum = new Node('$', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        minHeap.push(sum);
    }
    Node* root = minHeap.top();

    //e. generate bit maps
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    //f. run compression & decompression
    compressFile("sample.txt", "compressed.txt", huffmanCode);
    decompressFile("compressed.txt", "output_original.txt", root);

    return 0;
}


















