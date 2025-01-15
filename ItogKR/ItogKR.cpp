#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

//Функция для ввода чисел с консоли
string InputConsole() {
    string n;
    cout << "Введите число:\n" << endl;
    cin >> n;
    cout << "\n";

    //Проверяем, что все символы в строке являются цифрами или минусом
    bool hasMinus = false;
    for (int i = 0; i < n.size(); ++i) {
        if (n[i] == '-') {
            if (i != 0 || hasMinus) {
                cout << "Ошибка: Введено не число. Пожалуйста, попробуйте снова.\n" << endl;
                return InputConsole();
            }
            hasMinus = true;
        }
        else if (n[i] < '0' || n[i] > '9') {
            cout << "Ошибка: Введено не число. Пожалуйста, попробуйте снова.\n" << endl;
            return InputConsole();
        }
    }

    //Проверяем, что длина числа больше 20
    if (n.size() <= 20) {
        cout << "Ошибка: Длина числа должна быть больше 20. Пожалуйста, попробуйте снова.\n" << endl;
        return InputConsole();
    }
    return n;
}



//Функция для ввода чисел с помощью рандома
string InputRand() {
    string r = "";

    //Генерируем первую цифру от 1 до 9
    int firstDigit = rand() % 9 + 1;
    r += to_string(firstDigit);

    //Генерируем случайную длину числа (от 21 до 30)
    int minLength = 21;
    int maxLength = 30;
    int length = minLength + rand() % (maxLength - minLength + 1);

    //Генерируем остальные цифры от 0 до 9
    while (r.size() < length) {
        int randomNumber = rand() % 10;
        r += to_string(randomNumber);
    }

    //Случайным образом делаем число отрицательным
    if (rand() % 2 == 0)
        r = "-" + r;

    return r;
}

//Функция для ввода чисел из файла
pair <string,string> InputFile() {
    ifstream File("number.txt");

    if (!File) {
        cout << "Ошибка: Не удаётся открыть файл.\n";
        return {};
    }

    string n1,n2; 
    File >> n1;
    File >> n2;

    if (n1.empty() || n2.empty()) {
        cout << "Ошибка: Файл пуст или содержит некорректные данные.\n" << endl;
        return {};
    }

    //Проверяем, что все символы в строке являются цифрами или минусом
    bool hasMinus = false;
    for (int i = 0; i < n1.size(); ++i) {
        if (n1[i] == '-') {
            if (i != 0 || hasMinus) {
                cout << "Ошибка: Введено не число. Пожалуйста, проверьте содержимое файла.\n" << std::endl;
                return {};
            }
            hasMinus = true;
        }
        else if (n1[i] < '0' || n1[i] > '9') {
            cout << "Ошибка: Введено не число. Пожалуйста, проверьте содержимое файла.\n" << std::endl;
            return {};
        }
    }

    hasMinus = false;
    for (int i = 0; i < n2.size(); ++i) {
        if (n2[i] == '-') {
            if (i != 0 || hasMinus) {
                cout << "Ошибка: Введено не число. Пожалуйста, проверьте содержимое файла.\n" << std::endl;
                return {};
            }
            hasMinus = true;
        }
        else if (n2[i] < '0' || n2[i] > '9') {
            cout << "Ошибка: Введено не число. Пожалуйста, проверьте содержимое файла.\n" << std::endl;
            return {};
        }
    }

    //Проверяем, что длина числа больше 20
    if (n1.size() <= 20 || n2.size() <= 20) {
        cout << "Ошибка: Длины чисел должны быть больше 20. Пожалуйста, проверьте содержимое файла.\n" << endl;
        return {};
    }

    File.close();
    return { n1,n2 };
}

//Функция для сравнения двух строк
int compare(const string a, const string b) {
    if (a.size() != b.size()) {
        if (a.size() > b.size())
            return 1;
        else
            return -1;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            if (a[i] > b[i])
                return 1;
            else
                return -1;
        }
    }
    return 0;
}

//Функция для вычитания двух строк
string substract(const string a, const string b) {
    string result;

    int borrow = 0;
    int maxSize = max(a.size(), b.size());

    for (int i = 0; i < maxSize; ++i) {
        int diff = borrow;
        if (i < a.size()) 
            diff += a[a.size() - 1 - i] - '0';
        if (i < b.size()) 
            diff -= b[b.size() - 1 - i] - '0';

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        }
        else
            borrow = 0;

        result.push_back(diff + '0');
    }

    //Удаляем ведущие нули
    reverse(result.begin(), result.end());
    result.erase(0, result.find_first_not_of('0'));
    if (result.empty())
        result = "0";

    return result;
}

//Функция для нахождения остатка от деления чисел
string mod(const string a, const string b) {

    char ch = '0';

        int count = 0;
    for (int i = 0; (i = b.find(ch, i)) != -1; i++) 
        count++;

    if (count == b.size()) {
        cout << "Ошибка: Деление на 0.\n" << endl;
        return "Ошибка";
    }

    count = 0;
    for (int i = 0; (i = a.find(ch, i)) != -1; i++)
        count++;

    if (count == a.size())
        return "0";
    
    //Проверяем, являются ли числа отрицательными
    bool aNegative = (a[0] == '-');
    bool bNegative = (b[0] == '-');

    string aAbs = a;
    string bAbs = b;

    if (aNegative)
        aAbs = a.substr(1);
    if (bNegative)
        bAbs = b.substr(1);

    bool flag_aAbs = false;

    //Обрабатываем случаи, когда a и b имеют разные знаки
    if (aNegative) {
        if (!bNegative)
        {
            if (compare(bAbs, aAbs) > 0)
                aAbs = substract(bAbs, aAbs);
            else
                flag_aAbs = true;
        }
    }
    else {
        if (bNegative)
        {
            if (compare(bAbs, aAbs) > 0)
                aAbs = substract(bAbs, aAbs);
            else
                flag_aAbs = true;
        }
    }

    string remainder = aAbs;//Остаток от деления
    string divisor = bAbs;//Делитель

    //Выполняем деление с остатком
    while (compare(remainder, divisor) >= 0)
        remainder = substract(remainder, divisor);

    if (flag_aAbs)
        remainder = substract(bAbs, remainder);

    //Учитываем знак остатка
    if (bNegative)
        remainder = "-" + remainder;
    return remainder;
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));

    while (true) {
        int choice;
        cout << "Выберите способ ввода чисел:\n" << endl;
        cout << "1. Ввод с консоли" << endl;
        cout << "2. Ввод с помощью рандома" << endl;
        cout << "3. Ввод из файла" << endl;
        cout << "4. Выход\n" << endl;
        cin >> choice;
        cout <<"\n";

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
        }

        string a, b;
        pair<string, string> p;

        switch (choice) {
        case 1:
            a = InputConsole();
            b = InputConsole();
            break;
        case 2:
            a = InputRand(); 
            b = InputRand();
            break;
        case 3:
            p = InputFile();
            if (p.first.empty() || p.second.empty())
                continue;
            a = p.first;
            b = p.second;
            break;
        case 4:
            return 0;
        default:
            cout << "Ошибка: Некорректный ввод. Пожалуйста, введите цифру от 1 до 4.\n" << endl;
            continue;
        }

        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "\n";

        string remainder = mod(a, b);

        cout << "Остаток от деления: " << remainder<< endl;
        cout << "________________________________________________________________________________________________________________________"<<endl;
        cout << "\n";
    }
    return 0;
}