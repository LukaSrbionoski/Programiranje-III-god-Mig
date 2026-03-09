#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <filesystem>
using namespace std;

struct HuffNode {
    unsigned char ch;
    int freq;
    HuffNode *left, *right;

    HuffNode(unsigned char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffNode(HuffNode* l, HuffNode* r) {
        ch = 0;
        freq = l->freq + r->freq;
        left = l;
        right = r;
    }
};

struct NodeCompare {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

unordered_map<unsigned char, int> buildFrequency(ifstream &in) {
    unordered_map<unsigned char, int> freq;
    unsigned char c;

    while (in.get(reinterpret_cast<char&>(c)))
        freq[c]++;

    return freq;
}

HuffNode* buildTree(const unordered_map<unsigned char, int> &freq) {
    priority_queue<HuffNode*, vector<HuffNode*>, NodeCompare> pq;

    for (auto &p : freq)
        pq.push(new HuffNode(p.first, p.second));

    while (pq.size() > 1) {
        HuffNode* a = pq.top(); pq.pop();
        HuffNode* b = pq.top(); pq.pop();
        pq.push(new HuffNode(a, b));
    }

    return pq.top();
}

void buildCodes(HuffNode* node, string code,
                unordered_map<unsigned char, string> &table) {
    if (!node) return;

    if (!node->left && !node->right) {
        table[node->ch] = code.empty() ? "0" : code;
        return;
    }

    buildCodes(node->left, code + "0", table);
    buildCodes(node->right, code + "1", table);
}

void encodeFile(ifstream &in, ofstream &out,
                unordered_map<unsigned char, string> &codes) {
    unsigned char c;
    while (in.get(reinterpret_cast<char&>(c)))
        out << codes[c];
}

void decodeFile(ifstream &in, ofstream &out, HuffNode* root) {
    HuffNode* cur = root;
    char bit;

    while (in.get(bit)) {
        cur = (bit == '0') ? cur->left : cur->right;

        if (!cur->left && !cur->right) {
            out.put(cur->ch);
            cur = root;
        }
    }
}

void deleteTree(HuffNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    cout << "Working directory: " << filesystem::current_path() << endl;

    ifstream input("pg1399.txt");
    if (!input) {
        cout << "File open error\n";
        return 1;
    }

    auto freq = buildFrequency(input);
    HuffNode* root = buildTree(freq);

    unordered_map<unsigned char, string> codes;
    buildCodes(root, "", codes);

    input.clear();
    input.seekg(0);

    ofstream compressed("compressed.txt");
    encodeFile(input, compressed, codes);

    input.close();
    compressed.close();

    ifstream compIn("compressed.txt");
    ofstream decompressed("decompressed.txt");

    decodeFile(compIn, decompressed, root);

    compIn.close();
    decompressed.close();

    deleteTree(root);
    return 0;
}