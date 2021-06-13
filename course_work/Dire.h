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
void GetExport_vector(std::ofstream& out, const std::vector<T>& ex_data);

template <typename T>
void GetImport_vector(std::ifstream& in, std::vector<T>& im_data);

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

    Contact() {
        nick = "Unknown_name";
        phone = "Unknown_phone";
    }

    Contact(const std::string& a, const std::string& b);

    //Запись nick,phone
    void WriteUnfUserData(std::ofstream& out) const;

    //Чтение nick,phone
    void ReadUnfUserData(std::ifstream& in);

    std::string nick, phone;

    ~Contact();
};

/////////////////////////////////////////////////////

struct Dire {

    Dire();

    Dire(std::string& a, std::string& b);

    std::vector<Contact> MainContacts;
    std::vector<std::string> Language;

    std::string login, format_file = ".bin";

private:
    std::string password; int delay_text, delay_load, lang_state, lang_choise, format_type;

    bool auto_save, exec_bar; 
public:

    int arr_settings[7]{ delay_text, delay_load, exec_bar, auto_save, lang_choise, lang_state, format_type };

    //
    void WriteUnfUserData(std::ofstream& out) const;

    //
    void ReadUnfUserData(std::ifstream& in);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadUser();

    ////////////////////////////////////////////Збереження та завантаження контактів//////////////////////////////////////

    // 
    bool SaveUserData(std::string& name);

    bool ReadUserData(std::string& name);

    ////////////////////////////////////////////Завантаження конфігу налаштувань//////////////////////////////////////////////

    void SaveUserSettings();

    //////////////////////////////////////////Зміна паролю//////////////////////////////////////////////////

    //Меняет данные в UsersData (login, password).
    void ChangeAccountPass(std::string& a, int choise);

    //////////////////////////////////////////Перевірка логіна та пароля////////////////////////////////////////////////

    //Проверка на существование login, password.
    bool CheckAccountLogin(std::string& a, std::string& b);
    bool CheckAccountLogin(std::string& a);

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
    void RenameContact(short choise_rename, const size_t contact, const std::string& name);

    //Сортировка контактов с помощью библиотеки <algorithm>. Два типа сортировки(А...Я, Я...А)
    void SortContacts(short choise);

    //Поиск контакта, если не находит возвращает данные назад
    size_t GetSearchContact(const std::string& name);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ReadUserData();

protected:

    void ReadUserSettings();
    void SaveUserData();

    //функція, що надає змогу користувачу виводити список контактів. Якщо немає контактів, то переходить у функцію AddContactToDire.
    bool UserDireCorrect(const std::string& name, const std::string& phone);
    bool UserDireCorrect(const std::string& name, int choise);

public:
    ~Dire();
};

/////////////////////////////////////////////////////

struct LoginSystem {

    //Конструктор який завантажує базу даних
    LoginSystem();

    std::vector<Dire> UsersData;
    size_t user_position = 0;

    //Додає аккаунт в UsersData
    bool SetPassToAccount(std::string& a, std::string& b, std::string& c);

    //Шукає існуючий логін та пароль, якщо знаходить, 
    //то повертає позицію знайденого користувача 
    int GetLoginToAccount(std::string& a, std::string& b);

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

void GetExport_string(std::ofstream& out, const std::string& str);

std::string GetImport_string(std::ifstream& in, std::string& str);

/////////////////////////////////////////////////////

//Шаблонна функція запису у файл із string (шаблон типа Dire, Contact, LoginSystem)
template <typename T>
void GetExport_vector(std::ofstream &out, const std::vector<T>& ex_data) {
    size_t n = ex_data.size();
    out.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; i++)
        ex_data[i].WriteUnfUserData(out);
}

//Шаблонна функція читання із файла у string (шаблон типа Dire, Contact, LoginSystem)
template <typename T>
void GetImport_vector(std::ifstream& in, std::vector<T>& im_data) {
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