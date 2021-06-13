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

    //������ nick,phone
    void WriteUnfUserData(std::ofstream& out) const;

    //������ nick,phone
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

    ////////////////////////////////////////////���������� �� ������������ ��������//////////////////////////////////////

    // 
    bool SaveUserData(std::string& name);

    bool ReadUserData(std::string& name);

    ////////////////////////////////////////////������������ ������� �����������//////////////////////////////////////////////

    void SaveUserSettings();

    //////////////////////////////////////////���� ������//////////////////////////////////////////////////

    //������ ������ � UsersData (login, password).
    void ChangeAccountPass(std::string& a, int choise);

    //////////////////////////////////////////�������� ����� �� ������////////////////////////////////////////////////

    //�������� �� ������������� login, password.
    bool CheckAccountLogin(std::string& a, std::string& b);
    bool CheckAccountLogin(std::string& a);

    /////////////////////////////////////////������������ �����//////////////////////////////////

    //���� ����
    void SwitchLanguage(short choise, bool check_state);

    //������� ���������� ����� � �������� ��� ���.
    void FileNameFormat(short choise);

    //������� �������� ������ ������.
    int SetDelay(short choise);

    //���� ���� ������������.
    void printloadbar(short index_lang);

    //������� �������� �� ��������� ���� ������������
    void SetLoad(int choise);

    //���� ��������� ����������� ������� n ������� ������������ ��������.
    void MassiveAdd(size_t amount);

    //����� / ������ ����������� ����������
    void AutoSave(short choise);

    ////////////////////////////////////////////���� ��������� �����////////////////////////////

    //����� ���������
    void GetDireList();

    //�������, �� ���� ����� ������ ������� �� ��������� ����� (����� ���� ����������� ������� UserDireCorrect).
    void AddContactToDire(short times);

    //�������, �� ���� ����� �������� �������. ���� �������� ������, ������� ������� ����������� ��� ����� �����.
    void DeleteContact(const size_t contact);

    //�������������� �������� �� ��������� DataBase.h, ���� ������������ ����, ���������� ������.
    void RenameContact(short choise_rename, const size_t contact, const std::string& name);

    //���������� ��������� � ������� ���������� <algorithm>. ��� ���� ����������(�...�, �...�)
    void SortContacts(short choise);

    //����� ��������, ���� �� ������� ���������� ������ �����
    size_t GetSearchContact(const std::string& name);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ReadUserData();

protected:

    void ReadUserSettings();
    void SaveUserData();

    //�������, �� ���� ����� ����������� �������� ������ ��������. ���� ���� ��������, �� ���������� � ������� AddContactToDire.
    bool UserDireCorrect(const std::string& name, const std::string& phone);
    bool UserDireCorrect(const std::string& name, int choise);

public:
    ~Dire();
};

/////////////////////////////////////////////////////

struct LoginSystem {

    //����������� ���� ��������� ���� �����
    LoginSystem();

    std::vector<Dire> UsersData;
    size_t user_position = 0;

    //���� ������� � UsersData
    bool SetPassToAccount(std::string& a, std::string& b, std::string& c);

    //���� �������� ���� �� ������, ���� ���������, 
    //�� ������� ������� ���������� ����������� 
    int GetLoginToAccount(std::string& a, std::string& b);

    //���� ����� �������� ��� ��������
    void GetChangeAccount(short choise);

    //������� �������
    void GetDeleteAccount();

private:
    //������ UsersData � ���� ���� �� ������
    void SaveDataBase();

    //��������� �� ����� ���� �� ������ � UsersData
    void ReadDataBase();

    void DataBaseCleaner(size_t index);

public:
    ~LoginSystem();
};

/////////////////////////////////////////////////////

//������� ������� ������
int GetKey();

//������� ��� ����� ����� � �������
void ChangeColour(int colour);

void GetExport_string(std::ofstream& out, const std::string& str);

std::string GetImport_string(std::ifstream& in, std::string& str);

/////////////////////////////////////////////////////

//�������� ������� ������ � ���� �� string (������ ���� Dire, Contact, LoginSystem)
template <typename T>
void GetExport_vector(std::ofstream &out, const std::vector<T>& ex_data) {
    size_t n = ex_data.size();
    out.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; i++)
        ex_data[i].WriteUnfUserData(out);
}

//�������� ������� ������� �� ����� � string (������ ���� Dire, Contact, LoginSystem)
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