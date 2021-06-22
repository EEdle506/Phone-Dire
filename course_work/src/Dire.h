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
void GetExport_vector(std::ofstream& out, const std::unique_ptr<std::vector<T>>& ex_data);

template <typename T>
void GetImport_vector(std::ifstream& in, std::unique_ptr<std::vector<T>>& im_data);

/////////////////////////////////////////////////////

enum ColoursType {
    Cyan = 3,
    Magenta = 5,
    LightBlue = 9,
    LightGreen = 10,
    LightRed = 12,
    Yellow = 14,
    White = 15,
};

/////////////////////////////////////////////////////

struct Contact {

    Contact() = default;

    Contact(std::string&& nick, std::string&& phone);
    Contact(std::string &nick, std::string &phone);

    //Запись nick, phone
    void WriteUnfUserData(std::ofstream& out) const;

    //Чтение nick,phone
    void ReadUnfUserData(std::ifstream& in);

    std::string nick, phone;


    ~Contact();
};

/////////////////////////////////////////////////////

struct Dire {

    Dire();

    Dire(const std::string& login, const std::string& password);

    std::vector<Contact> MainContacts;

    std::vector<std::string> Language;

    std::string login, format_file = ".bin";

private:
    std::string password; short delay_text, delay_load, lang_state, lang_choise, format_type;

    bool auto_save, exec_bar; 
public:

    short arr_settings[7]{ delay_text, delay_load, exec_bar, auto_save, lang_choise, lang_state, format_type };

    //
    void WriteUnfUserData(std::ofstream& out) const;

    //
    void ReadUnfUserData(std::ifstream& in);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    void LoadUser();

    ////////////////////////////////////////////Збереження та завантаження контактів//////////////////////////////////////

    // 
    bool SaveUserData(const std::string& name) const;
    bool ReadUserData(const std::string& name);

    ////////////////////////////////////////////Завантаження конфігу налаштувань//////////////////////////////////////////////

    void SaveUserSettings();

    //////////////////////////////////////////Зміна паролю//////////////////////////////////////////////////

    //Меняет данные в UsersData (login, password).
    void ChangeAccountPass(const std::string& a, const short& choise);

    //////////////////////////////////////////Перевірка логіна та пароля////////////////////////////////////////////////

    //Проверка на существование login, password.
    bool CheckAccountLogin(const std::string& a, const std::string& b)noexcept;
    bool CheckAccountLogin(const std::string& a)noexcept;

    /////////////////////////////////////////Налаштування книги//////////////////////////////////

    static void LangLoad(std::vector<std::string>& Language, const short& index);

    //Зміна мови
    void SwitchLanguage(const short& choise, bool check_state);

    //Функція збереження файлу з форматом або без.
    void FileNameFormat(const short& choise);

    //Ставить затримку вивода тексту.
    short SetDelay(const short& choise);

    //Вивід меню завантаження.
    void printloadbar(const short& index_lang);

    //Функція вімкнення та вимикання меню завантаження
    void SetLoad(const short& choise);

    //Вмткає / вимикає автоматичне збереження
    void AutoSave(const short& choise);

    ////////////////////////////////////////////Меню телефонної книги////////////////////////////

    //Вывод контактов
    void GetDireList();

    //функція, що надає змогу додати контакт до телефонної книги (також вона використовує функцію UserDireCorrect).
    void AddContactToDire(const short& times);

    //функція, що надає змогу видалити контакт. Якщо записник пустий, функція видасть повідомлення про пусту книгу.
    void DeleteContact(const size_t& contact);

    //Переименование контакта из структуры DataBase.h, если пользователя нету, возвращает данные.
    void RenameContact(const short& choise_rename, const size_t& contact, const std::string& name);

    //Сортировка контактов с помощью библиотеки <algorithm>. Два типа сортировки(А...Я, Я...А)
    void SortContacts(const short& choise);

    //Поиск контакта, если не находит возвращает данные назад
    size_t GetSearchContact(const std::string& name);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    //static void CheckState_Dire();

    void ReadUserData();

protected:

    void ReadUserSettings();
    void SaveUserData() const;

    //функція, що надає змогу користувачу виводити список контактів. Якщо немає контактів, то переходить у функцію AddContactToDire.
    bool UserDireCorrect(const std::string& name, const std::string& phone) const;
    bool UserDireCorrect(const std::string& name, int choise) const;

public:
    ~Dire();

};

/////////////////////////////////////////////////////

struct LoginSystem {

    //Конструктор який завантажує базу даних
    LoginSystem();

    std::vector<Dire> UsersData;
    unsigned int user_position = 0;

    //Додає аккаунт в UsersData
    bool SetPassToAccount(const std::string& a, const std::string& b, const std::string& c);

    //Шукає існуючий логін та пароль, якщо знаходить, 
    //то повертає позицію знайденого користувача 
    int GetLoginToAccount(const std::string& a, const std::string& b);

    //Надає змогу змінювати дані аккаунта
    void GetChangeAccount(const short& choise);

    //Видаляє аккаунт
    void GetDeleteAccount();

private:

    //Зберігає UsersData у файл логін та пароль
    void SaveDataBase() const;

    //Завантажує із файлу логін та пароль у UsersData
    void ReadDataBase();

    void DataBaseCleaner(const size_t& index);

public:
    ~LoginSystem();
};

/////////////////////////////////////////////////////

void GetExport_string(std::ofstream& out, const std::string& str);
std::string GetImport_string(std::ifstream& in, std::string& str);

//Считует нажатие клавиш
int GetKey();

//Функция для смены цвета в консоли
void ChangeColour(int colour);

//Надає можливість користувачу вводити n кількість згенерованих контактів.
void MassiveAdd(LoginSystem& contacts, const size_t& position, const size_t& amount);

/////////////////////////////////////////////////////

//Шаблонна функція запису у файл із string (шаблон типа Dire, Contact, LoginSystem)
template <typename T>
void GetExport_vector(std::ofstream &out, const std::vector<T>& ex_data) {
    size_t n = ex_data.size();
    out.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; ++i)
        ex_data.at(i).WriteUnfUserData(out);
}

//Шаблонна функція читання із файла у string (шаблон типа Dire, Contact, LoginSystem)
template <typename T>
void GetImport_vector(std::ifstream& in, std::vector<T>& im_data) {
    size_t size_vec = 0;
    T data_contacts;

    in.read((char*)&size_vec, sizeof(size_vec));
    im_data.clear();
    im_data.reserve(size_vec);

    for (int i = 0; i < size_vec; ++i) {
        data_contacts.ReadUnfUserData(in);
        im_data.push_back(data_contacts);
    }
}

/////////////////////////////////////////////////////