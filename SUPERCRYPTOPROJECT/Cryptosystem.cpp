#include "kvpolibi.cpp"
#include "vijener.cpp"
#include "hughes.cpp"
#include "Cryptosystem.h"

string FileInput(string filename) { // ф-ия вывода из файла
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

string FileOutput(string filename, string str) { // ф-ия ввода в файл
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

void input_and_check(string& message, string choice_shifr, string message_or_key) { // ф-ия ввода сообщения с клавиатуры и его проверка
    if (message_or_key == "message") {
        cout << "Введите сообщение: ";
    } else {
        cout << "Введите кодовое слово: ";
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
            cout << "Ошибка, введены некорректные символы: ";
            for (auto elem : errorinput) {
                cout << elem << " ";
            }
            cout << endl << "Повторите попытку ввода: ";
        } else {
            if (message_or_key == "message") {
                cout << "Сообщение принято!" << endl;
            } else {
                cout << "Кодовое слово принято!" << endl;
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
    cout << "Введите название файла, в который будет записано сообщение: ";
    cin >> filename;
    FileOutput(filename, message);
    

    // ШИФРОВКА //
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
    cout << "Зашифрованное сообщение: " << Encrypted << endl;
    cout << "Введите название файла, в который будет записано зашифрованное сообщение: ";
    cin >> filename;
    string check = FileOutput(filename, Encrypted); // записываем в файл
    if (check != "Completed") {
        cout << "Ошибка, невозможно открыть файл " << filename << "!" << endl;
    } else {
        cout << "Сообщение записано в файл " << filename << "!" << endl;
                
        // Расшифровка //
        cout << "Расшифровать сообщение? Для подтверждения введите /y/ или /Y/: ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            Encrypted.clear();
            cout << "Введите название файла, в котором хранится зашифрованное сообщение: ";
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
                cout << "Расшифрованное сообщение: " << Descrypted << endl;
                cout << "Введите название файла, в котором будет хранится зашифрованный файл: ";
                cin >> filename;
                check = FileOutput(filename, Descrypted); // записываем в файл
                if (check != "Completed") {
                    cout << "Ошибка, невозможно открыть файл " << filename << "!" << endl;
                } else {
                    cout << "Сообщение записано в файл " << filename << "!" << endl;
                }
            } else {
                cout << "Ошибка, невозможно открыть файл " << filename << "!" << endl;
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
    cout << "Введите пароль: ";
    cin >> password;
    if (password != passwd) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> password;
        if (password != passwd) {
            cout << "Вы вводите неверный пароль! Последняя попытка: ";
            cin >> password;
            if (password != passwd) {
                cout << "Вы использовали все попытки! Завершение программы...";
                exit(0);
            }
        }
    }

    system("cls");
    cout << "\nДобро пожаловать!\n" << "------------------------------\n" << "1 - шифрование с помощью квадрата Полибия\n" 
    << "2 - шифр Виженера\n" << "3 - шифрование с помощью алгоритма Хьюза\n" << "0 - выйти из программы\n" 
    << "------------------------------\n";

    while (true) {
        
        int choice;
        while (true) {
            try { // обработка ошибки
                cout << "\nВыберите номер шифра: ";
                cin >> choice;
                if (cin.fail()) {
                    throw invalid_argument("Вводите только число!");
                }
                break;
            } catch (invalid_argument& ex) { // ловим ошибку, выводим её пользователю и запрашиваем ввод заново
                cin.clear();
                cin.ignore();
                cout << "Ошибка: " << ex.what() << endl;
            }
        }

        if (choice == 1) {
            Enc_and_Desc("Polibi");
        } else if (choice == 2) {
            Enc_and_Desc("Vijener");
        } else if (choice == 3) {
            Enc_and_Desc("Hughes");
        } else if (choice == 0) {
            cout << "Выход из программы...";
            exit(0);
        } else {
            cout << "Выбран неверный номер шифра!" << endl;
        }

    }

    return 0;
}