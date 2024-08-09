#include "kvpolibi.cpp"
#include "vijener.cpp"
#include "hughes.cpp"
#include "Cryptosystem.h"

string FileInput(string filename) { // �-�� ������ �� �����
    string str;
    ifstream input;
    input.open(filename);
    if (input.is_open()) {
        getline(input, str);
        input.close();
        return str;
    } else {
        return "Error: Unable to open the file";
    }
}

string FileOutput(string filename, string str) { // �-�� ����� � ����
    ofstream output;
    output.open(filename);
    if (output.is_open()) {
        output << str;
        output.close();
        return "Completed";
    } else {
        return "Error: Unable to open the file";
    }
}

void input_and_check(string& message, string choice_shifr, string message_or_key) { // �-�� ����� ��������� � ���������� � ��� ��������
    if (message_or_key == "message") {
        cout << "������� ���������: ";
    } else {
        cout << "������� ������� �����: ";
    }
    cin.ignore();
    while (true) {
        getline(cin, message);
        vector<char> errorinput;
        if (choice_shifr == "Polibi") {
            errorinput = checkinputpolibi(message);
        } else {
            errorinput = checkinputvijener(message);
        }
        if (!errorinput.empty()) {
            cout << "������, ������� ������������ �������: ";
            for (auto elem : errorinput) {
                cout << elem << " ";
            }
            cout << endl << "��������� ������� �����: ";
        } else {
            if (message_or_key == "message") {
                cout << "��������� �������!" << endl;
            } else {
                cout << "������� ����� �������!" << endl;
            }
            break;
        }
    }

}

void Enc_and_Desc(string choice_shifr) {
    string message, wordkey, filename;
    int key;
    
    if (choice_shifr == "Polibi") {
        input_and_check(message, "Polibi", "message");
    } else if (choice_shifr == "Vijener") {
        input_and_check(message, "Vijener", "message");
        input_and_check(wordkey, "Vijener", "key");
    } else if (choice_shifr == "Hughes") {
        input_and_check(message, "Hughes", "message");
        key = GenerateKey();
    }
    cout << "������� �������� �����, � ������� ����� �������� ���������: ";
    cin >> filename;
    FileOutput(filename, message);
    

    // �������� //
    message = FileInput(filename);
    string Encrypted, Descrypted;
    if (choice_shifr == "Polibi") {
        Encrypted = polybiumEncryption(message);
    } else if (choice_shifr == "Vijener") {
        Encrypted = vijenerEncryption(message, wordkey);
    }
    else if (choice_shifr == "Hughes") {
        Encrypted = hughesEncDesc(message, key);
    }
    cout << "������������� ���������: " << Encrypted << endl;
    cout << "������� �������� �����, � ������� ����� �������� ������������� ���������: ";
    cin >> filename;
    string check = FileOutput(filename, Encrypted); // ���������� � ����
    if (check != "Completed") {
        cout << "������, ���������� ������� ���� " << filename << "!" << endl;
    } else {
        cout << "��������� �������� � ���� " << filename << "!" << endl;
                
        // ����������� //
        cout << "������������ ���������? ��� ������������� ������� /y/ ��� /Y/: ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            Encrypted.clear();
            cout << "������� �������� �����, � ������� �������� ������������� ���������: ";
            cin >> filename;
            Encrypted = FileInput(filename);
            if (Encrypted != "Error: Unable to open the file") {
                if (choice_shifr == "Polibi") {
                    Descrypted = polybiumDescryption(Encrypted);
                } else if (choice_shifr == "Vijener") {
                    Descrypted = vijenerDescryption(Encrypted, wordkey);
                } else if (choice_shifr == "Hughes") {
                    Descrypted = hughesEncDesc(Encrypted, key);
                }
                cout << "�������������� ���������: " << Descrypted << endl;
                cout << "������� �������� �����, � ������� ����� �������� ������������� ����: ";
                cin >> filename;
                check = FileOutput(filename, Descrypted); // ���������� � ����
                if (check != "Completed") {
                    cout << "������, ���������� ������� ���� " << filename << "!" << endl;
                } else {
                    cout << "��������� �������� � ���� " << filename << "!" << endl;
                }
            } else {
                cout << "������, ���������� ������� ���� " << filename << "!" << endl;
            }
        }
    }
}


int main() {
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    string password;
    cout << "������� ������: ";
    cin >> password;
    if (password != passwd) {
        cout << "������ ��������! ���������� ��� ���: ";
        cin >> password;
        if (password != passwd) {
            cout << "�� ������� �������� ������! ��������� �������: ";
            cin >> password;
            if (password != passwd) {
                cout << "�� ������������ ��� �������! ���������� ���������...";
                exit(0);
            }
        }
    }

    system("cls");
    cout << "\n����� ����������!\n" << "------------------------------\n" << "1 - ���������� � ������� �������� �������\n" 
    << "2 - ���� ��������\n" << "3 - ���������� � ������� ��������� �����\n" << "0 - ����� �� ���������\n" 
    << "------------------------------\n";

    while (true) {
        
        int choice;
        while (true) {
            try { // ��������� ������
                cout << "\n�������� ����� �����: ";
                cin >> choice;
                if (cin.fail()) {
                    throw invalid_argument("������� ������ �����!");
                }
                break;
            } catch (invalid_argument& ex) { // ����� ������, ������� � ������������ � ����������� ���� ������
                cin.clear();
                cin.ignore();
                cout << "������: " << ex.what() << endl;
            }
        }

        if (choice == 1) {
            Enc_and_Desc("Polibi");
        } else if (choice == 2) {
            Enc_and_Desc("Vijener");
        } else if (choice == 3) {
            Enc_and_Desc("Hughes");
        } else if (choice == 0) {
            cout << "����� �� ���������...";
            exit(0);
        } else {
            cout << "������ �������� ����� �����!" << endl;
        }

    }

    return 0;
}