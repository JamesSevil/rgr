#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <cmath>

using namespace std;

const string passwd = "9056";

string polybiumEncryption(const string& message);
string polybiumDescryption(const string& message);
vector<char> checkinputpolibi(const string& messagee);

string vijenerEncryption(const string& message, const string& key);
string vijenerDescryption(const string& message, const string& key);
vector<char> checkinputvijener(const string& message);

int VzaimProst(int a, int b);
bool CheckPrime(int num);
int fi(int num);
int Pow(int a, int x, int p);
int inversia(int c, int m);
int GenerateKey();
string hughesEncDesc(string message, int key);