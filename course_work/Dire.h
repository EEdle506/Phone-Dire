#pragma once
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <Windows.h>

template <typename T>
void GetExport_vector(ofstream& out, const vector<T>& ex_data);

template <typename T>
void GetImport_vector(ifstream& in, vector<T>& im_data);

/////////////////////////////////////////////////////

enum ColoursType {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15,
};

/////////////////////////////////////////////////////

struct Contact {

    Contact() {};
    Contact(string& a, string& b);

    //Запись nick,phone
    void WriteUnfUserData(ofstream& out) const;

    //Чтение nick,phone
    void ReadUnfUserData(ifstream& in);

    string nick; string phone;

    ~Contact();
};

/////////////////////////////////////////////////////

struct Dire {

    Dire();

    Dire(string& a, string& b);

    vector<Contact> MainContacts;
    vector<string> Language;

    string login, format_file = ".bin";

private:
    string password; int delay_text, delay_load;

    bool auto_save, exec_bar; short lang_state, lang_choise, format_type;
public:

    int arr_settings[7]{ delay_text, delay_load, exec_bar, auto_save, lang_choise, lang_state, format_type };

    //
    void WriteUnfUserData(ofstream& out) const;

    //
    void ReadUnfUserData(ifstream& in);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadUser();

    ////////////////////////////////////////////Збереження та завантаження контактів//////////////////////////////////////

    // 
    void SaveUserData();
    bool SaveUserData(string& name);

    bool ReadUserData(string& name);

    ////////////////////////////////////////////Завантаження конфігу налаштувань//////////////////////////////////////////////

    void SaveUserSettings();

    //////////////////////////////////////////Зміна паролю//////////////////////////////////////////////////

    //Меняет данные в UsersData (login, password).
    void ChangeAccountPass(string& a, int choise);

    //////////////////////////////////////////Перевірка логіна та пароля////////////////////////////////////////////////

    //Проверка на существование login, password.
    bool CheckAccountLogin(string& a, string& b);
    bool CheckAccountLogin(string& a);

    /////////////////////////////////////////Налаштування книги//////////////////////////////////

    //Зміна мови
    void SwitchLanguage(short choise, bool check_state);

    //Функція збереження файлу з форматом або без.
    void FileNameFormat(short choise);

    //Ставить затримку вивода тексту.
    int SetDelay(short choise);

    //Вивід меню завантаження.
    void printloadbar(short index_lang);

    //Функція вімкнення та вимикання меню завантаження
    void SetLoad(int choise);

    //Надає можливість користувачу вводити n кількість згенерованих контактів.
    void MassiveAdd(size_t amount);

    //Вмткає / вимикає автоматичне збереження
    void AutoSave(short choise);

    ////////////////////////////////////////////Меню телефонної книги////////////////////////////

    //Вывод контактов
    void GetDireList();

    //функція, що надає змогу додати контакт до телефонної книги (також вона використовує функцію UserDireCorrect).
    void AddContactToDire(short times);

    //функція, що надає змогу видалити контакт. Якщо записник пустий, функція видасть повідомлення про пусту книгу.
    void DeleteContact(const size_t contact);

    //Переименование контакта из структуры DataBase.h, если пользователя нету, возвращает данные.
    void RenameContact(short choise_rename, const size_t contact, const string& name);

    //Сортировка контактов с помощью библиотеки <algorithm>. Два типа сортировки(А...Я, Я...А)
    void SortContacts(short choise);

    //Поиск контакта, если не находит возвращает данные назад
    size_t GetSearchContact(const string& name);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

    //
    void ReadUserData();

    void ReadUserSettings();

    //функція, що надає змогу користувачу виводити список контактів. Якщо немає контактів, то переходить у функцію AddContactToDire.
    bool UserDireCorrect(const string& name, const string& phone);
    bool UserDireCorrect(const string& name, int choise);

public:
    ~Dire();
};

/////////////////////////////////////////////////////

struct LoginSystem {

    //Конструктор який завантажує базу даних
    LoginSystem();

    vector<Dire> UsersData;
    size_t user_position = 0;

    //Додає аккаунт в UsersData
    bool SetPassToAccount(string& a, string& b, string& c);

    //Шукає існуючий логін та пароль, якщо знаходить, 
    //то повертає позицію знайденого користувача 
    int GetLoginToAccount(string& a, string& b);

    //Надає змогу змінювати дані аккаунта
    void GetChangeAccount(short choise);

    //Видаляє аккаунт
    void GetDeleteAccount();

private:
    //Зберігає UsersData у файл логін та пароль
    void SaveDataBase();

    //Завантажує із файлу логін та пароль у UsersData
    void ReadDataBase();

    void DataBaseCleaner(size_t index);

public:
    ~LoginSystem();
};

/////////////////////////////////////////////////////

//Считует нажатие клавиш
int GetKey();

//Функция для смены цвета в консоли
void ChangeColour(int colour);

void GetExport_string(ofstream& out, const string& str);

string GetImport_string(ifstream& in, string& str);

/////////////////////////////////////////////////////

//Шаблонна функція запису у файл із string (шаблон типа Dire, Contact, LoginSystem)
template <typename T>
void GetExport_vector(ofstream &out, const vector<T>& ex_data) {
    size_t n = ex_data.size();
    out.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; i++) {
        ex_data[i].WriteUnfUserData(out);
    }
}

//Шаблонна функція читання із файла у string (шаблон типа Dire, Contact, LoginSystem)
template <typename T>
void GetImport_vector(ifstream& in, vector<T>& im_data) {
    size_t size_vec = 0;
    T data_contacts;

    in.read((char*)&size_vec, sizeof(size_vec));
    im_data.clear();
    im_data.reserve(size_vec);

    for (int i = 0; i < size_vec; i++) {
        data_contacts.ReadUnfUserData(in);
        im_data.push_back(data_contacts);
    }
}

/////////////////////////////////////////////////////