#include <bits/stdc++.h>
#define SubKey vector<int>

using namespace std;

int vectorToInt(vector<int> bin) {
    int num = 0;
    for (int i = 0; i < bin.size(); ++i) {
        num += (bin[i] * (1 << (bin.size() - i - 1)));
    }
    return num;
}

vector<int> intToVector(int num) {
    vector<int> bin;
    while (num) {
        bin.push_back(num % 2);
        num /= 2;
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

void printKey(vector<int> key) {
    for (int i = 0; i < key.size(); ++i) {
        cout << key[i] << " ";
        if (i == (key.size() / 2) - 1) cout << "   ";
    }
    cout << "\n";
}

class Key {
    int p10[10] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};
    int p8[8] = {5, 2, 6, 3, 7, 4, 9, 8};

   public:
    SubKey subKey1;
    SubKey subKey2;

    Key(string key) {
        vector<int> mainKey;
        for (char c : key) {
            mainKey.push_back(c - '0');
        }
        generateKey(mainKey);
    }

    void generateKey(vector<int> mainKey) {
        vector<int> calculationKey = permutate10(mainKey);
        cout << "Key after applying P10: \n";
        printKey(calculationKey);

        calculationKey = leftShift(calculationKey);
        cout << "Left shifting key by 1 pos: \n";
        printKey(calculationKey);

        // Applying p8 operation
        vector<int> firstKey = applyP8(calculationKey);
        this->subKey1 = firstKey;

        cout << "Key after applying P8: \n";
        printKey(firstKey);

        // Calculation of subkey2
        // Do leftshift by 2 positions
        calculationKey = leftShift(calculationKey, 2);
        cout << "Left shifting key by 2 pos: \n";
        printKey(calculationKey);

        // Applying p8 operation
        calculationKey = applyP8(calculationKey);
        this->subKey2 = calculationKey;

        cout << "Key after applying P8: \n";
        printKey(calculationKey);

        printSubKeys();
    }

    vector<int> permutate10(vector<int> key) {
        vector<int> permutation(10, 0);
        for (int i = 0; i < 10; ++i) {
            permutation[i] = key[p10[i]];
        }
        return permutation;
    }

    vector<int> applyP8(vector<int> combinedKey) {
        vector<int> keyAferOperation(8, 0);
        for (int i = 0; i < 8; ++i) {
            keyAferOperation[i] = combinedKey[p8[i]];
        }
        return keyAferOperation;
    }

    void printSubKeys() {
        cout << "\n Key 1: ";
        for (int i = 0; i < this->subKey1.size(); ++i) {
            cout << this->subKey1[i] << " ";
        }
        cout << "\n Key 2: ";
        for (int i = 0; i < this->subKey1.size(); ++i) {
            cout << this->subKey2[i] << " ";
        }
        cout << "\n";
    }

    vector<int> leftShift(vector<int> key, int positions = 1) {
        vector<int> leftHalf(key.begin(), key.begin() + 5);
        vector<int> rightHalf(key.begin() + 5, key.end());

        rotate(leftHalf.begin(), leftHalf.begin() + positions, leftHalf.end());
        rotate(rightHalf.begin(), rightHalf.begin() + positions, rightHalf.end());

        vector<int> combined = leftHalf;
        combined.insert(combined.end(), rightHalf.begin(), rightHalf.end());
        return combined;
    }
};

class SDES {
    Key* key;

    int ip[8] = {1, 5, 2, 0, 3, 7, 4, 6};
    int ip_1[8] = {3, 0, 2, 4, 6, 1, 7, 5};
    int ep[8] = {3, 0, 1, 2, 1, 2, 3, 0};
    int p4[4] = {1, 3, 2, 0};
    vector<int> s0[4][4] = {{{0, 1}, {0, 0}, {1, 1}, {1, 0}},
                            {{1, 1}, {1, 0}, {0, 1}, {0, 0}},
                            {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
                            {{1, 1}, {0, 1}, {1, 1}, {1, 0}}};
    vector<int> s1[4][4] = {{{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                            {{1, 0}, {0, 0}, {0, 1}, {1, 1}},
                            {{1, 1}, {0, 0}, {0, 1}, {0, 0}},
                            {{1, 0}, {0, 1}, {0, 0}, {1, 1}}};

    vector<int> applyEP(vector<int> half) {
        vector<int> expandedText(8, 0);
        for (int i = 0; i < 8; ++i) {
            expandedText[i] = half[ep[i]];
        }
        return expandedText;
    }

    vector<int> xorVectors(vector<int> first, vector<int> second) {
        vector<int> xorred(first.size(), 0);
        for (int i = 0; i < first.size(); ++i) xorred[i] = first[i] ^ second[i];
        return xorred;
    }

    vector<int> applySBoxes(vector<int> bits) {
        vector<int> left(bits.begin(), bits.begin() + 4);
        vector<int> right(bits.begin() + 4, bits.end());
        vector<int> combined;

        int leftRow = vectorToInt({left[0], left[3]});
        int leftCol = vectorToInt({left[1], left[2]});

        vector<int> subLeft = s0[leftRow][leftCol];
        combined.insert(combined.end(), subLeft.begin(), subLeft.end());

        int rightRow = vectorToInt({right[0], right[3]});
        int rightCol = vectorToInt({right[1], right[2]});

        vector<int> subRight = s1[rightRow][rightCol];
        combined.insert(combined.end(), subRight.begin(), subRight.end());
        return combined;
    }

    vector<int> applyP4(vector<int> bits) {
        vector<int> ans(4, 0);
        for (int i = 0; i < 4; ++i) {
            ans[i] = bits[p4[i]];
        }
        return ans;
    }

    vector<int> fk(vector<int> left, vector<int> right, vector<int> key) {
        // Apply E/P to right
        vector<int> expanded = applyEP(right);
        cout << "Expansion: \n";
        printKey(expanded);

        vector<int> xorred = xorVectors(expanded, key);
        cout << "Xorring with key: \n";
        printKey(xorred);

        vector<int> sbox = applySBoxes(xorred);
        cout << "Sboxes output: \n";
        printKey(sbox);

        vector<int> permutate4 = applyP4(sbox);
        cout << "P4 output: \n";
        printKey(permutate4);

        vector<int> output = xorVectors(left, permutate4);
        cout << "Round output: \n";
        printKey(output);

        cout << "\n\n\n";
        return output;
    }

    vector<int> applyIP(vector<int> bits) {
        vector<int> ans(8, 0);
        for (int i = 0; i < 8; ++i) {
            ans[i] = bits[ip[i]];
        }
        return ans;
    }

    vector<int> applyIP_1(vector<int> bits) {
        vector<int> ans(8, 0);
        for (int i = 0; i < 8; ++i) {
            ans[i] = bits[ip_1[i]];
        }
        return ans;
    }

   public:
    SDES(string key) { this->key = new Key(key); }

    vector<int> encrypt(vector<int> text) {
        text = applyIP(text);
        cout << "Applying IP to plain text: \n";
        printKey(text);
        vector<int> left(text.begin(), text.begin() + 4);
        vector<int> right(text.begin() + 4, text.end());

        vector<int> firstRoundOutput = fk(left, right, this->key->subKey1);
        vector<int> secondRoundOutput = fk(right, firstRoundOutput, this->key->subKey2);

        vector<int> combined = secondRoundOutput;
        combined.insert(combined.end(), firstRoundOutput.begin(), firstRoundOutput.end());

        vector<int> encryptedTextVector = applyIP_1(combined);
        return encryptedTextVector;
    }

    vector<int> decrypt(vector<int> cipherText) {
        cipherText = applyIP(cipherText);
        cout << "Applying IP-1 to cipherText: \n";
        printKey(cipherText);
        vector<int> left(cipherText.begin(), cipherText.begin() + 4);
        vector<int> right(cipherText.begin() + 4, cipherText.end());

        vector<int> firstRoundOutput = fk(left, right, this->key->subKey2);
        vector<int> secondRoundOutput = fk(right, firstRoundOutput, this->key->subKey1);

        vector<int> combined = secondRoundOutput;
        combined.insert(combined.end(), firstRoundOutput.begin(), firstRoundOutput.end());

        vector<int> plainTextVector = applyIP_1(combined);
        return plainTextVector;
    }
};

int main() {
    SDES* algo = new SDES("1010110010");
    vector<int> cipherText = algo->encrypt({1, 1, 0, 0, 0, 1, 0, 1});

    cout << "Encrypted Text: ";
    for (int bit : cipherText) cout << bit << " ";
    cout << "\n";

    vector<int> plainText = algo->decrypt(cipherText);
    cout << "Decrypted Text: ";
    for (int bit : plainText) cout << bit << " ";
    cout << "\n";

    return 0;
}