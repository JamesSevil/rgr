#include "Cryptosystem.h"

const int str = 18, stlb = 9;
const char table[str][stlb] = {
                        {'�', '�', '�', '�', '�', '�', '�', '�', '�'},
                        {'�', '�', '�', '�', '�', '�', '�', '�', '�'},
                        {'�', '�', '�', '�', '�', '�', '�', '�', '�'},
                        {'�', '�', '�', '�', '�', '�', 'A', 'B', 'C'},
                        {'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'},
                        {'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U'},
                        {'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd'},
                        {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'},
                        {'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'},
                        {'w', 'x', 'y', 'z', '�', '�', '�', '�', '�'},
                        {'�', '�', '�', '�', '�', '�', '�', '�', '�'},
                        {'�', '�', '�', '�', '�', '�', '�', '�', '�'},
                        {'�', '�', '�', '�', '�', '�', '�', '�', '�'},
                        {'�', '+', '-', '*', '/', '=', ' ', '.', ','},
                        {'!', '?', '<', '>', ':', ';', '"', '&', '^'},
                        {'%', '$', '#', '�', '@', '`', '~', '(', ')'},
                        {'[', ']', '{', '}', '|', '0', '1', '2', '3'},
                        {'4', '5', '6', '7', '8', '9'}
};

string polybiumEncryption(string& message) { // ��������
    string Encrypted;
    
    for (int element = 0; element < message.length(); ++element) {
        for (int stroka = 0; stroka < str; ++stroka) {
            for (int stolbec = 0; stolbec < stlb; ++stolbec) {
                if (message[element] == table[stroka][stolbec]) {
                    Encrypted += to_string(stroka+1);
                    Encrypted += to_string(stolbec+1);
                    Encrypted += ' ';
                }
            }
        }
    }
    Encrypted.erase(Encrypted.end()-1);

    return Encrypted;
}

string polybiumDescryption(string& message) { // �����������
    string Descrypted;
    
    int stroka, stolbec;
    string element;
    for (auto elem : message) {
        if (elem == ' ') {
            stroka = (stoi(element) / 10) - 1;
            stolbec = (stoi(element) % 10) - 1;
            Descrypted += table[stroka][stolbec];
            element.clear();
        } else {
            element += elem;
        }
    }
    stroka = (stoi(element) / 10) - 1;
    stolbec = (stoi(element) % 10) - 1;
    Descrypted += table[stroka][stolbec];

    return Descrypted;
}

vector<char> checkinputpolibi(string& message) { // �������� �����
    vector<bool> check(message.length());
    for (int simvolmessage = 0; simvolmessage < message.length(); ++simvolmessage) {
        for (int stroka = 0; stroka < str; ++stroka) {
            for (int stolbec = 0; stolbec < stlb; ++stolbec) {
                if (message[simvolmessage] == table[stroka][stolbec]) {
                   check[simvolmessage] = true;
                }
            }
        }
        if (check[simvolmessage] != true) {
            check[simvolmessage] = false;
        }
    }
    vector<char> errorinput;
    for (int simvol = 0; simvol < check.size(); simvol++) {
        if (check[simvol] != true) {
            errorinput.push_back(message[simvol]);
        }
    }
    return errorinput;
}