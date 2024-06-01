#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <cmath>

using namespace std;

const string passwd = "9056"; // пароль

// шифр Полибия
string polybiumEncryption(string message);
string polybiumDescryption(string message);
vector<char> checkinputpolibi(string message);

// шифр Виженера
string vijenerEncryption(string message, string key);
string vijenerDescryption(string message, string key);
vector<char> checkinputvijener(string message);

// шифр Хьюза
int VzaimProst(int a, int b);
bool CheckPrime(int num);
int fi(int num);
int Pow(int a, int x, int p);
int inversia(int c, int m);
int GenerateKey();
string hughesEncDesc(string message, int key);