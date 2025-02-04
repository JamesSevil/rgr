#include "Cryptosystem.h"

const int g = 613, n = 6949;

int VzaimProst(int a, int b) { // ���(a, b) ��� ��������, �������� �� ����� ���������������
    if (b == 0) return a;
    return VzaimProst(b, a % b);
}

bool CheckPrime(int num) { // ��������, �������� �� ����� �������
    if (num <= 1) return false; 
    for (int i = 2; i * i <= num; ++i) { 
        if (num % i == 0) return false;
    }
    return true;
}

int fi(int num) { // ������� ������
    int result = 1;
    int stepen = 0;
    for (int i = 2; i <= num; ++i) {
        while (num % i == 0) {
            stepen++;
            num /= i;
        }
        if (stepen != 0) {
            result *= pow(i, stepen - 1) * (i - 1);
        }
        stepen = 0;
    }
    return result;
}

int Pow(int a, int x, int p) { // a^x mod p
    int result = 1;
    if (CheckPrime(p) == true) { // �������
        x %= p-1;
    } else { // �� �������
        x %= fi(p);     
    }
    for (int i = 1; i <= x; ++i) {
        result = (result * a) % p;
    }
    return result;
}

int inversia(int c, int m) { // �������� ���������� ����� d(c^-1 mod m)
    int q; 
    vector<int> one = {m, 0};
    vector<int> two = {c, 1};
    vector<int> three(2);
    while (two[0] != 0) {
        q = one[0] / two[0];
        three[0] = one[0] % two[0];
        three[1] = one[1] - (q * two[1]);
        one[0] = two[0]; one[1] = two[1];
        two[0] = three[0]; two[1] = three[1];
    }
    if (one[1] < 0) {
        one[1] += m;
    }
    return one[1];
}

int GenerateKey() {
    int x = 100 + rand() % 100000; // ������� A �������� ��������� ������ ����� � ���������� �������� ����
    int k = Pow(g, x, n);
    int y = 100 + rand() % 100000; // ������� B �������� ��������� ������ �����
    while (VzaimProst(y, n-1) != 1) {
        y = 100 + rand() % 100000;  
    }
    int Y = Pow(g, y, n); // ������� B �������� �������� A
    int X = Pow(Y, x, n); // ������� � �������� �������� B
    int z = inversia(y, n-1); // ������� B ���������
    int ksh = Pow(X, z, n); // ������� B ��������� ����
    if (k == ksh) {
        return k;
    } else {
        return 0;
    }
}

string hughesEncDesc(string message, int key){ // �������� � �����������
    for (int i = 0; i < message.length(); ++i) {
        message[i] = message[i] ^ key;
    }
    return message;
}