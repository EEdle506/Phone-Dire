#include "Dire.h"

void GetExport_string(std::ofstream& out, const std::string& str) {
    size_t n = str.size();
    out.write((char*)&n, sizeof(n));
     
    if (n > 0)
        out.write(str.c_str(), n);
}

std::string GetImport_string(std::ifstream& in, std::string& str) {
    size_t n;
    in.read((char*)&n, sizeof(n));

    if (n > 0) {
        std::vector<char> v(n);
        in.read(&v[0], n);
        str.assign(v.begin(), v.begin() + n);
        v.clear();
        return str;
    }
    str = "";
    return str;
}

///////////Запись/Чтение nick, phone(Contact//////////////////////

void Contact::WriteUnfUserData(std::ofstream& out)const {        //MainContact
    GetExport_string(out, nick);
    GetExport_string(out, phone);
}

void Contact::ReadUnfUserData(std::ifstream& in) {                //MainContact
    GetImport_string(in, nick);
    GetImport_string(in, phone);
}

//////////////////////Загрузка настроек///////////////////////////

void Dire::SaveUserSettings() {

    std::ofstream out("Settings/settings.txt");

    if (out.is_open()) {
        for (int i = 0; i < 7; ++i)
            out << arr_settings[i] << std::endl;
        printloadbar(25);
    }
    else {
        system("cls");
        out.close();
        ChangeColour(LightRed);
        std::cout << "Удалена папка Settings! \nПожалуйста создайте её!";
        exit(-1);
    }
    out.close();
}

void Dire::ReadUserSettings() {
    int i = 0;
    std::ifstream in("Settings/settings.txt");

    if (in.is_open()) {
        while (!in.eof()) {
            in >> arr_settings[i];
            ++i;
        }
        in.close();
    }
    else {
        system("cls");
        in.close();
        ChangeColour(LightRed);
        std::cout << "Ошбка при открытии файла settings.txt";
        exit(-1);
    }
}

/////////////Запись/Чтение контактов(Dire)////////////////////////

void Dire::WriteUnfUserData(std::ofstream& out) const {      //UsersData
    GetExport_string(out, login);
    GetExport_string(out, password);
}

void Dire::ReadUnfUserData(std::ifstream& in) {              //UsersData
    GetImport_string(in, login);
    GetImport_string(in, password);
    SwitchLanguage(arr_settings[4], false);
}

void Dire::SaveUserData() const {
    if (arr_settings[3]) {
        std::string str_temp_saveread = "";
        str_temp_saveread.append("Users_Data/" + login + "_data.bin");
        std::ofstream name_out(str_temp_saveread, std::ios::binary);

        if (!MainContacts.empty())
            GetExport_vector(name_out, MainContacts);
        name_out.close();
    }
}

bool Dire::SaveUserData(const std::string& name) const {
    std::string str_temp_saveread = "";
    str_temp_saveread.append(name + format_file);
    std::ofstream name_out(str_temp_saveread, std::ios::binary);

    if (!MainContacts.empty()) {
        GetExport_vector(name_out, MainContacts);
        name_out.close();

        return true;
    }
    name_out.close();
    return false;
}

void Dire::ReadUserData() {
    std::string str_temp_saveread = "";
    str_temp_saveread.append("Users_Data/" + login + "_data.bin");
    std::ifstream name_in(str_temp_saveread, std::ios::binary);

    if (name_in.is_open()) {
        if (name_in.peek() != EOF) {
            GetImport_vector(name_in, MainContacts);
            printloadbar(24);
        }
    }
    else {
        system("cls");
        ChangeColour(Yellow);
        std::cout << Language.at(10);
        Sleep(arr_settings[0]);
    }
    name_in.close();
}

bool Dire::ReadUserData(const std::string& name) {
    system("cls");
    std::string str_temp_saveread = "";
    str_temp_saveread.append(name + format_file);
    std::ifstream name_in(str_temp_saveread, std::ios::binary);

    if (name_in.is_open())
        if (name_in.peek() != EOF) {
            GetImport_vector(name_in, MainContacts);
            printloadbar(24);
            name_in.close();
            return true;
        }
    else {
        ChangeColour(Yellow);
        std::cout << Language.at(10);
        Sleep(arr_settings[0]);
        system("cls");
    }
    name_in.close();
    return false;
}

////////////Запись/Чтение логин и пароль (LoginSystem)////////////

void LoginSystem::SaveDataBase() const {
    std::ofstream login_data_out("DataBase/login_data.bin", std::ios::binary);
    GetExport_vector(login_data_out, UsersData);
    login_data_out.close();
}

void LoginSystem::ReadDataBase() {
    std::ifstream login_data_in("DataBase/login_data.bin", std::ios::binary);
    if (login_data_in.is_open()) {
        GetImport_vector(login_data_in, UsersData);
        if (UsersData.empty())
            UsersData.push_back({});
        UsersData.shrink_to_fit();
        UsersData.at(user_position).printloadbar(24);
    }
    login_data_in.close();
}

//////////////////////////////////////////////////////////////////