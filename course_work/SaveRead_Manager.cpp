using namespace std;
#include "Dire.h"

string str_temp_saveread;

void GetExport_string(ofstream& out, const string& str) {
    size_t n = str.size();
    out.write((char*)&n, sizeof(n));

    if (n > 0) {
        out.write(str.c_str(), n);
    }
}

string GetImport_string(ifstream& in, string& str) {
    size_t n;
    in.read((char*)&n, sizeof(n));

    if (n > 0) {
        vector<char> v(n);
        in.read(&v[0], n);
        str.assign(&v[0], &v[0] + n);
        return str;
    }
    str = "";
    return str;
}

///////////Запись/Чтение nick, phone(Contact//////////////////////

void Contact::WriteUnfUserData(ofstream& out)const {        //MainContact
    GetExport_string(out, nick);
    GetExport_string(out, phone);
}

void Contact::ReadUnfUserData(ifstream& in) {                //MainContact
    GetImport_string(in, nick);
    GetImport_string(in, phone);
}

//////////////////////Загрузка настроек///////////////////////////

void Dire::SaveUserSettings() {

    ofstream out("Settings/settings.txt");

    if (out.is_open()) {
        for (int i = 0; i < 7; i++) {
            out << arr_settings[i] << endl;
        }
        printloadbar(25);
    }
    else {
        system("cls");
        out.close();
        ChangeColour(LightRed);
        cout << "Удалена папка Settings! \nПожалуйста создайте её!";
        exit(-1);
    }
    out.close();
}

void Dire::ReadUserSettings() {
    int i = 0;
    ifstream in("Settings/settings.txt");

    if (in.is_open()) {
        while (!in.eof()) {
            in >> arr_settings[i];
            i++;
        }
        in.close();
    }
    else {
        system("cls");
        in.close();
        ChangeColour(LightRed);
        cout << "Ошбка при открытии файла settings.txt";
        exit(-1);
    }
}

/////////////Запись/Чтение контактов(Dire)////////////////////////

void Dire::WriteUnfUserData(ofstream& out)const {      //UsersData
    GetExport_string(out, login);
    GetExport_string(out, password);
}

void Dire::ReadUnfUserData(ifstream& in) {              //UsersData
    GetImport_string(in, login);
    GetImport_string(in, password);
    this->SwitchLanguage(arr_settings[4], false);
}

void Dire::SaveUserData() {
    if (arr_settings[3]) {
        str_temp_saveread = "";
        str_temp_saveread.append("Users_Data/" + login + "_data.bin");
        ofstream name_out(str_temp_saveread,ios::binary);

        if (!MainContacts.empty()) {
            GetExport_vector(name_out, MainContacts);
            printloadbar(25);
        }
        name_out.close();
    }
}

bool Dire::SaveUserData(string& name) {
    str_temp_saveread = "";
    str_temp_saveread.append("imported_data/" + name + format_file);
    ofstream name_out(str_temp_saveread, ios::binary);

    if (!MainContacts.empty()) {
        GetExport_vector(name_out, MainContacts);
        printloadbar(25);
        name_out.close();
        return true;
    }
    name_out.close();
    return false;
}

void Dire::ReadUserData() {
    str_temp_saveread = "";
    str_temp_saveread.append("Users_Data/" + login + "_data.bin");
    ifstream name_in(str_temp_saveread, ios::binary);

    if (name_in.is_open()) {
        if (name_in.peek() != EOF) {
            GetImport_vector(name_in, MainContacts);
            printloadbar(24);
        }
    }
    else {
        system("cls");
        ChangeColour(Yellow);
        cout << Language[10];
        Sleep(arr_settings[0]);
    }
    name_in.close();
}

bool Dire::ReadUserData(string& name) {
    system("cls");
    str_temp_saveread = "";
    str_temp_saveread.append("imported_data/" + name + format_file);
    ifstream name_in(str_temp_saveread, ios::binary);

    if (name_in.is_open()) {
        if (name_in.peek() != EOF) {
            GetImport_vector(name_in, MainContacts);
            printloadbar(24);
            name_in.close();
            return true;
        }
        name_in.close();
        return false;
    }
    else {
        ChangeColour(Yellow);
        cout << Language[10];
        Sleep(arr_settings[0]);
        system("cls");
        name_in.close();
        return false;
    }
}

////////////Запись/Чтение логин и пароль (LoginSystem)////////////

void LoginSystem::SaveDataBase() {
    ofstream login_data_out("DataBase/login_data.bin", ios::binary);
    GetExport_vector(login_data_out, UsersData);
    UsersData[user_position].printloadbar(25);
    login_data_out.close();
}

void LoginSystem::ReadDataBase() {
    ifstream login_data_in("DataBase/login_data.bin", ios::binary);
    if (login_data_in.is_open()) {
        GetImport_vector(login_data_in, UsersData);
        if (UsersData.empty())
            UsersData.push_back({});
        UsersData.shrink_to_fit();
    }
    login_data_in.close();
}

//////////////////////////////////////////////////////////////////