#include "Dire.h"

///////////////////Система логина(PhoneDire)////////////////////////////

LoginSystem::LoginSystem() {
    UsersData.push_back({});
}

void LoginSystem::DataBaseCleaner(const size_t& index) {
    UsersData.erase(UsersData.begin(), UsersData.begin() + index);
    if (!UsersData.empty()) {
        UsersData.erase(++UsersData.begin(), UsersData.end());
        user_position = UsersData.size()-1;
        if (UsersData.
            
            empty())
            UsersData.push_back({});
    }
    UsersData.shrink_to_fit();
}

void Dire::ChangeAccountPass(const std::string& a, const short& choise) {
    if (a.size() > 2) {
        switch (choise) {
        case 1:
            this->login = a;
            break;
        case 2:
            this->password = a;
            break;
        }
    }
    else {
        system("cls");
        ChangeColour(LightRed);
        std::cout << Language.at(87);
        Sleep(arr_settings[0]);
    }
}

bool Dire::CheckAccountLogin(const std::string& a, const std::string& b) noexcept {
    if (login == a && password == b)
        return true;
    return false;
}

bool Dire::CheckAccountLogin(const std::string& a) noexcept {
    if (login == a)
        return true;
    return false;
}

bool LoginSystem::SetPassToAccount(const std::string& a, const std::string& b, const std::string& c) {
    system("cls");

    if (!a.empty() | !b.empty() | !c.empty()) {
        if (b==c) {
            if (a.size() > 2 && b.size() > 1) {
                ReadDataBase();
                //Проверка на существование аккаунта
                for (size_t i = 0; i < UsersData.size(); ++i) {
                    if (UsersData.at(i).CheckAccountLogin(a, b)) {
                        ChangeColour(Yellow);
                        std::cout << UsersData.at(i).Language.at(75);
                        Sleep(UsersData.at(i).arr_settings[0]);
                        DataBaseCleaner(i);

                        return false;
                    }
                }
                UsersData.push_back(Dire(a,b));
                user_position = UsersData.size() - 1;
                UsersData.at(user_position).printloadbar(18);
                std::cout << UsersData.at(user_position).Language.at(71);
                Sleep(UsersData.at(user_position).arr_settings[0]);
                SaveDataBase();
                DataBaseCleaner(user_position);

                return true;
            }
            else {
                ChangeColour(Yellow);
                std::cout << UsersData.at(user_position).Language.at(87);
                Sleep(UsersData.at(user_position).arr_settings[0]);

                return false;
            }
        }
        else {
            ChangeColour(Yellow);
            std::cout << UsersData.at(user_position).Language.at(94);
            Sleep(UsersData.at(user_position).arr_settings[0]);

            return false;
        }
    }
    else {
        ChangeColour(LightRed);
        std::cout << UsersData.at(user_position).Language.at(87);
        Sleep(UsersData.at(user_position).arr_settings[0]);

        return false;
    }
}

int LoginSystem::GetLoginToAccount(const std::string& a, const std::string& b) {
    system("cls");
    unsigned int bad_position = 0; user_position = 0;

    //Пошук аккаунта

    ReadDataBase();
    if (!UsersData.empty()) {
        if (!a.empty() | !b.empty()) {
            for (size_t i = 0; i < UsersData.size(); ++i) {
                if (UsersData.at(i).CheckAccountLogin(a, b)) {
                    DataBaseCleaner(i);
                    ChangeColour(LightGreen);
                    std::cout << UsersData.at(user_position).Language.at(72);
                    Sleep(UsersData.at(user_position).arr_settings[0]);
                    return user_position;
                }
            }
        }
        //Аккаунт не знайдено
        user_position = UsersData.size() - 1;
        DataBaseCleaner(user_position);
        ChangeColour(LightRed);
        std::cout << UsersData.at(user_position).Language.at(73);
        Sleep(UsersData.at(user_position).arr_settings[0]);
        system("cls");
        std::cout << UsersData.at(user_position).Language.at(74);
        Sleep(UsersData.at(user_position).arr_settings[0]);
        system("cls");
        bad_position = UsersData.size() + 2;

        return bad_position;
    }
    else {
        UsersData.push_back({});
        ChangeColour(LightRed);
        std::cout << UsersData.at(user_position).Language.at(73);
        Sleep(UsersData.at(user_position).arr_settings[0]);
        system("cls");
        bad_position = UsersData.size() + 2;
        
        return bad_position;
    }
}

void LoginSystem::GetChangeAccount(const short& choise) {
    if (choise <= 2) {
        std::string temp_login = UsersData.at(user_position).login, old_name_file = "", str_temp_phonedire = "", new_name_file = "";

        old_name_file.append("Users_Data/" + UsersData.at(user_position).login + "_data" + UsersData.at(user_position).format_file);
        system("cls");

        ReadDataBase();

        for (unsigned int i = 0; i < UsersData.size(); ++i)
            if (UsersData.at(i).CheckAccountLogin(temp_login)) {
                user_position = i;
                break;
            };

        switch (choise) {
        case 1:

            std::cout << UsersData.at(user_position).Language.at(83);
            getline(std::cin, str_temp_phonedire);

            new_name_file.append("Users_Data/" + str_temp_phonedire + "_data" + UsersData.at(user_position).format_file);

            if (rename(old_name_file.c_str(), new_name_file.c_str()) == 1)
                std::cout << UsersData.at(user_position).Language.at(11);

            UsersData.at(user_position).ChangeAccountPass(str_temp_phonedire, 1);
            SaveDataBase();
            DataBaseCleaner(user_position);

            break;

        case 2:

            std::cout << UsersData.at(user_position).Language.at(84);
            getline(std::cin, str_temp_phonedire);

            UsersData.at(user_position).ChangeAccountPass(str_temp_phonedire, 2);
            SaveDataBase();
            DataBaseCleaner(user_position);
            break;
        }
    }
    else {
        ChangeColour(Yellow);
        std::cout << UsersData.at(user_position).Language.at(2);
        Sleep(UsersData.at(user_position).arr_settings[0]);
    }
}

void LoginSystem::GetDeleteAccount() {
    system("cls");
    std::string str_temp_phonedire = "", temp_login = UsersData.at(user_position).login;
    str_temp_phonedire.append("Users_Data/" + UsersData.at(user_position).login + "_data.bin");

    ReadDataBase();

    for (unsigned int i = 0; i < UsersData.size(); ++i) {
        if (UsersData.at(i).CheckAccountLogin(temp_login)) {
            user_position = i;
            break;
        }
    }

    if (user_position < UsersData.size()) {
        remove(str_temp_phonedire.c_str());

        UsersData.erase(UsersData.begin() + user_position);
        UsersData.shrink_to_fit();

        if (!UsersData.empty()) {
            user_position = 0;
            SaveDataBase();

            UsersData.clear();
            UsersData.push_back({});

            UsersData.at(user_position).printloadbar(19);
            ChangeColour(LightGreen);
            std::cout << UsersData.at(user_position).Language.at(88);
            Sleep(UsersData.at(user_position).arr_settings[0]);
        }
        else {
            UsersData.push_back({});
            SaveDataBase();
            UsersData.at(user_position).printloadbar(19);
            ChangeColour(LightGreen);
            std::cout << UsersData.at(user_position).Language.at(88);
            Sleep(UsersData.at(user_position).arr_settings[0]);
        }
    }
}

LoginSystem::~LoginSystem() {
    UsersData.clear();
    user_position = 0;
}

////////////////////////////////////////////////////////////////////////