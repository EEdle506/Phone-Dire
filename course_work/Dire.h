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

    //������ nick,phone
    void WriteUnfUserData(ofstream& out) const;

    //������ nick,phone
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

    ////////////////////////////////////////////���������� �� ������������ ��������//////////////////////////////////////

    // 
    void SaveUserData();
    bool SaveUserData(string& name);

    bool ReadUserData(string& name);

    ////////////////////////////////////////////������������ ������� �����������//////////////////////////////////////////////

    void SaveUserSettings();

    //////////////////////////////////////////���� ������//////////////////////////////////////////////////

    //������ ������ � UsersData (login, password).
    void ChangeAccountPass(string& a, int choise);

    //////////////////////////////////////////�������� ����� �� ������////////////////////////////////////////////////

    //�������� �� ������������� login, password.
    bool CheckAccountLogin(string& a, string& b);
    bool CheckAccountLogin(string& a);

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
    void RenameContact(short choise_rename, const size_t contact, const string& name);

    //���������� ��������� � ������� ���������� <algorithm>. ��� ���� ����������(�...�, �...�)
    void SortContacts(short choise);

    //����� ��������, ���� �� ������� ���������� ������ �����
    size_t GetSearchContact(const string& name);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

    //
    void ReadUserData();

    void ReadUserSettings();

    //�������, �� ���� ����� ����������� �������� ������ ��������. ���� ���� ��������, �� ���������� � ������� AddContactToDire.
    bool UserDireCorrect(const string& name, const string& phone);
    bool UserDireCorrect(const string& name, int choise);

public:
    ~Dire();
};

/////////////////////////////////////////////////////

struct LoginSystem {

    //����������� ���� ��������� ���� �����
    LoginSystem();

    vector<Dire> UsersData;
    size_t user_position = 0;

    //���� ������� � UsersData
    bool SetPassToAccount(string& a, string& b, string& c);

    //���� �������� ���� �� ������, ���� ���������, 
    //�� ������� ������� ���������� ����������� 
    int GetLoginToAccount(string& a, string& b);

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

void GetExport_string(ofstream& out, const string& str);

string GetImport_string(ifstream& in, string& str);

/////////////////////////////////////////////////////

//�������� ������� ������ � ���� �� string (������ ���� Dire, Contact, LoginSystem)
template <typename T>
void GetExport_vector(ofstream &out, const vector<T>& ex_data) {
    size_t n = ex_data.size();
    out.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; i++) {
        ex_data[i].WriteUnfUserData(out);
    }
}

//�������� ������� ������� �� ����� � string (������ ���� Dire, Contact, LoginSystem)
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