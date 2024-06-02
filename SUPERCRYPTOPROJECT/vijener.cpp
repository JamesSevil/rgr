#include "Cryptosystem.h"

const int razmer = 159;
const char tableVijener[razmer] = {
                            'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 
                            'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
                            'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 
                            'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
                            'v', 'w', 'x', 'y', 'z', 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 
                            'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я', '+', '-', 
                            '*', '/', '=', ' ', '.', ',', '!', '?', '<', '>', ':', ';', '"', '&', '^', '%', '$', '#', '№', '@', 
                            '`', '~', '(', ')', '[', ']', '{', '}', '|', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

string vijenerEncryption(string message, string key) { // шифровка
    int iter = 0;
    int lenghtkey = key.length();
    while (key.length() < message.length()) {
        if (iter == lenghtkey) {
            iter = 0;
        }
        key += key[iter];
        iter++;
    }
    vector<int> codemessage;
    for (int i = 0; i < message.size(); ++i) {
        for (int j = 0; j < razmer; ++j) {
            if (message[i] == tableVijener[j]) {
                codemessage.push_back(j);
            }
        }
    }
    vector<int> codekey;
    for (int i = 0; i < key.size(); ++i) {
        for (int j = 0; j < razmer; ++j) {
            if (key[i] == tableVijener[j]) {
                codekey.push_back(j);
            }
        }
    }
    vector<int> codeEncrypted;
    for (int i = 0; i < message.size(); ++i) {
        int code = (codemessage[i] + codekey[i]) % razmer;
        codeEncrypted.push_back(code);
    }
    string Encrypted;
    for (int i = 0; i < codeEncrypted.size(); ++i) {
        Encrypted += tableVijener[codeEncrypted[i]];
    }
    return Encrypted;
}

string vijenerDescryption(string message, string key) { // расшифровка
    int iter = 0;
    int lenghtkey = key.length();
    while (key.length() < message.length()) {
        if (iter == lenghtkey) {
            iter = 0;
        }
        key += key[iter];
        iter++;
    }
    vector<int> codeEncrypt;
    for (int i = 0; i < message.size(); i++) {
        for (int j = 0; j < razmer; j++) {
            if (message[i] == tableVijener[j]) {
                codeEncrypt.push_back(j);
            }
        }
    }
    vector<int> codekey;
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < razmer; j++) {
            if (key[i] == tableVijener[j]) {
                codekey.push_back(j);
            }
        }
    }
    vector<int> codeDescrypted;
    for (int i = 0; i < codeEncrypt.size(); i++) {
        int code = (codeEncrypt[i] - codekey[i]) % razmer;
        if (code < 0) {
            code = (code + razmer) % razmer;
        }
        codeDescrypted.push_back(code);
    }
    string Descrypted;
    for (int i = 0; i < codeDescrypted.size(); i++) {
        Descrypted += tableVijener[codeDescrypted[i]];
    }
    return Descrypted;
}

vector<char> checkinputvijener(string message) { // проверка ввода
    vector<bool> check(message.size());
    for (int i = 0; i < message.size(); ++i) {
        for (int j = 0; j < razmer; ++j) {
            if (message[i] == tableVijener[j]) {
                check[i] = true;
            }
        }
        if (check[i] != true) {
            check[i] = false;
        }
    }
    vector<char> errorinput;
    for (int i = 0; i < check.size(); i++) {
        if (check[i] != true) {
            errorinput.push_back(message[i]);
        }
    }
    return errorinput;
}