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

    //������ nick, phone
    void WriteUnfUserData(std::ofstream& out) const;

    //������ nick,phone
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

    ////////////////////////////////////////////���������� �� ������������ ��������//////////////////////////////////////

    // 
    bool SaveUserData(const std::string& name) const;
    bool ReadUserData(const std::string& name);

    ////////////////////////////////////////////������������ ������� �����������//////////////////////////////////////////////

    void SaveUserSettings();

    //////////////////////////////////////////���� ������//////////////////////////////////////////////////

    //������ ������ � UsersData (login, password).
    void ChangeAccountPass(const std::string& a, const short& choise);

    //////////////////////////////////////////�������� ����� �� ������////////////////////////////////////////////////

    //�������� �� ������������� login, password.
    bool CheckAccountLogin(const std::string& a, const std::string& b)noexcept;
    bool CheckAccountLogin(const std::string& a)noexcept;

    /////////////////////////////////////////������������ �����//////////////////////////////////

    static void LangLoad(std::vector<std::string>& Language, const short& index);

    //���� ����
    void SwitchLanguage(const short& choise, bool check_state);

    //������� ���������� ����� � �������� ��� ���.
    void FileNameFormat(const short& choise);

    //������� �������� ������ ������.
    short SetDelay(const short& choise);

    //���� ���� ������������.
    void printloadbar(const short& index_lang);

    //������� �������� �� ��������� ���� ������������
    void SetLoad(const short& choise);

    //����� / ������ ����������� ����������
    void AutoSave(const short& choise);

    ////////////////////////////////////////////���� ��������� �����////////////////////////////

    //����� ���������
    void GetDireList();

    //�������, �� ���� ����� ������ ������� �� ��������� ����� (����� ���� ����������� ������� UserDireCorrect).
    void AddContactToDire(const short& times);

    //�������, �� ���� ����� �������� �������. ���� �������� ������, ������� ������� ����������� ��� ����� �����.
    void DeleteContact(const size_t& contact);

    //�������������� �������� �� ��������� DataBase.h, ���� ������������ ����, ���������� ������.
    void RenameContact(const short& choise_rename, const size_t& contact, const std::string& name);

    //���������� ��������� � ������� ���������� <algorithm>. ��� ���� ����������(�...�, �...�)
    void SortContacts(const short& choise);

    //����� ��������, ���� �� ������� ���������� ������ �����
    size_t GetSearchContact(const std::string& name);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    //static void CheckState_Dire();

    void ReadUserData();

protected:

    void ReadUserSettings();
    void SaveUserData() const;

    //�������, �� ���� ����� ����������� �������� ������ ��������. ���� ���� ��������, �� ���������� � ������� AddContactToDire.
    bool UserDireCorrect(const std::string& name, const std::string& phone) const;
    bool UserDireCorrect(const std::string& name, int choise) const;

public:
    ~Dire();

};

/////////////////////////////////////////////////////

struct LoginSystem {

    //����������� ���� ��������� ���� �����
    LoginSystem();

    std::vector<Dire> UsersData;
    unsigned int user_position = 0;

    //���� ������� � UsersData
    bool SetPassToAccount(const std::string& a, const std::string& b, const std::string& c);

    //���� �������� ���� �� ������, ���� ���������, 
    //�� ������� ������� ���������� ����������� 
    int GetLoginToAccount(const std::string& a, const std::string& b);

    //���� ����� �������� ��� ��������
    void GetChangeAccount(const short& choise);

    //������� �������
    void GetDeleteAccount();

private:

    //������ UsersData � ���� ���� �� ������
    void SaveDataBase() const;

    //��������� �� ����� ���� �� ������ � UsersData
    void ReadDataBase();

    void DataBaseCleaner(const size_t& index);

public:
    ~LoginSystem();
};

/////////////////////////////////////////////////////

void GetExport_string(std::ofstream& out, const std::string& str);
std::string GetImport_string(std::ifstream& in, std::string& str);

//������� ������� ������
int GetKey();

//������� ��� ����� ����� � �������
void ChangeColour(int colour);

//���� ��������� ����������� ������� n ������� ������������ ��������.
void MassiveAdd(LoginSystem& contacts, const size_t& position, const size_t& amount);

/////////////////////////////////////////////////////

//�������� ������� ������ � ���� �� string (������ ���� Dire, Contact, LoginSystem)
template <typename T>
void GetExport_vector(std::ofstream &out, const std::vector<T>& ex_data) {
    size_t n = ex_data.size();
    out.write((char*)&n, sizeof(n));

    for (int i = 0; i < n; ++i)
        ex_data.at(i).WriteUnfUserData(out);
}

//�������� ������� ������� �� ����� � string (������ ���� Dire, Contact, LoginSystem)
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