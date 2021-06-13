#include "Dire.h"

size_t bad_position = 0;

///////////////////Система логина(PhoneDire)////////////////////////////

LoginSystem::LoginSystem() {
    UsersData.push_back({});
}

void LoginSystem::DataBaseCleaner(size_t index) {
    UsersData.erase(UsersData.begin(), UsersData.begin() + index);
    if (!UsersData.empty()) {
        UsersData.erase(UsersData.begin() + 1, UsersData.end());
        user_position = UsersData.size() - 1;
        if (UsersData.empty()) {
            UsersData.push_back({});
        }
    }
    UsersData.shrink_to_fit();
}

void Dire::ChangeAccountPass(std::string& a, int choise) {
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
        std::cout << Language[87];
        Sleep(arr_settings[0]);
    }
}

bool Dire::CheckAccountLogin(std::string& a, std::string& b) {
    if (login == a && password == b) {
        return true;
    }
    return false;
}

bool Dire::CheckAccountLogin(std::string& a) {
    if (login == a) {
        return true;
    }
    return false;
}

bool LoginSystem::SetPassToAccount(std::string& a, std::string& b, std::string& c) {
    system("cls");

    if (!a.empty() | !b.empty() | !c.empty()) {
        if (b==c) {
            if (a.size() > 2 && b.size() > 1) {
                ReadDataBase();
                //Проверка на существование аккаунта
                for (size_t i = 0; i < UsersData.size(); i++) {
                    if (UsersData[i].CheckAccountLogin(a, b)) {
                        ChangeColour(Yellow);
                        std::cout << UsersData[i].Language[75];
                        Sleep(UsersData[i].arr_settings[0]);
                        DataBaseCleaner(i);

                        return false;
                    }
                }
                UsersData.push_back(Dire(a,b));
                user_position = UsersData.size() - 1;
                UsersData[user_position].printloadbar(18);
                std::cout << UsersData[user_position].Language[71];
                Sleep(UsersData[user_position].arr_settings[0]);
                SaveDataBase();
                DataBaseCleaner(user_position);

                return true;
            }
            else {
                ChangeColour(Yellow);
                std::cout << UsersData[user_position].Language[87];
                Sleep(UsersData[user_position].arr_settings[0]);

                return false;
            }
        }
        else {
            ChangeColour(Yellow);
            std::cout << UsersData[user_position].Language[94];
            Sleep(UsersData[user_position].arr_settings[0]);

            return false;
        }
    }
    else {
        ChangeColour(LightRed);
        std::cout << UsersData[user_position].Language[87];
        Sleep(UsersData[user_position].arr_settings[0]);

        return false;
    }
}

int LoginSystem::GetLoginToAccount(std::string& a, std::string& b) {
    system("cls");
    bad_position = 0; user_position = 0;
    //Пошук аккаунта
    ReadDataBase();
    if (!UsersData.empty()) {
        if (!a.empty() | !b.empty()) {
            for (size_t i = 0; i < UsersData.size(); i++) {
                if (UsersData[i].CheckAccountLogin(a, b)) {
                    DataBaseCleaner(i);
                    ChangeColour(LightGreen);
                    std::cout << UsersData[user_position].Language[72];
                    Sleep(UsersData[user_position].arr_settings[0]);
                    return user_position;
                }
            };
        }
        //Аккаунт не знайдено
        user_position = UsersData.size() - 1;
        DataBaseCleaner(user_position);
        ChangeColour(LightRed);
        std::cout << UsersData[user_position].Language[73];
        Sleep(UsersData[user_position].arr_settings[0]);
        system("cls");
        std::cout << UsersData[user_position].Language[74];
        Sleep(UsersData[user_position].arr_settings[0]);
        system("cls");
        bad_position = UsersData.size() + 2;

        return bad_position;
    }
    else {
        UsersData.push_back({});
        ChangeColour(LightRed);
        std::cout << UsersData[user_position].Language[73];
        Sleep(UsersData[user_position].arr_settings[0]);
        system("cls");
        bad_position = UsersData.size() + 2;
        
        return bad_position;
    }
}

void LoginSystem::GetChangeAccount(short choise) {
    if (choise <= 2) {
        std::string temp_login = UsersData[user_position].login, old_name_file = "", str_temp_phonedire = "", new_name_file = "";
        
        old_name_file.append("Users_Data/" + UsersData[user_position].login + "_data" + UsersData[user_position].format_file);
        system("cls");

        ReadDataBase();

        for (size_t i = 0; i < UsersData.size(); i++) {
            if (UsersData[i].CheckAccountLogin(temp_login)) {
                user_position = i;
                break;
            }
        }

        switch (choise) {
        case 1:

            std::cout << UsersData[user_position].Language[83];
            getline(std::cin, str_temp_phonedire);

            new_name_file.append("Users_Data/" + str_temp_phonedire + "_data" + UsersData[user_position].format_file);

            if (rename(old_name_file.c_str(), new_name_file.c_str()) == 1) std::cout << UsersData[user_position].Language[11];

            UsersData[user_position].ChangeAccountPass(str_temp_phonedire, 1);
            SaveDataBase();
            DataBaseCleaner(user_position);

            break;

        case 2:

            std::cout << UsersData[user_position].Language[84];
            getline(std::cin, str_temp_phonedire);

            UsersData[user_position].ChangeAccountPass(str_temp_phonedire, 2);
            SaveDataBase();
            DataBaseCleaner(user_position);
            break;
        }
    }
    else {
        ChangeColour(Yellow);
        std::cout << UsersData[user_position].Language[2];
        Sleep(UsersData[user_position].arr_settings[0]);
    }
}

void LoginSystem::GetDeleteAccount() {
    system("cls");
    std::string str_temp_phonedire = "", temp_login = UsersData[user_position].login;
    str_temp_phonedire.append("Users_Data/" + UsersData[user_position].login + "_data.bin");

    ReadDataBase();

    for (size_t i = 0; i < UsersData.size(); i++) {
        if (UsersData[i].CheckAccountLogin(temp_login)) {
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

            UsersData[user_position].printloadbar(19);
            ChangeColour(LightGreen);
            std::cout << UsersData[user_position].Language[88];
            Sleep(UsersData[user_position].arr_settings[0]);
        }
        else {
            UsersData.push_back({});
            SaveDataBase();
            UsersData[user_position].printloadbar(19);
            ChangeColour(LightGreen);
            std::cout << UsersData[user_position].Language[88];
            Sleep(UsersData[user_position].arr_settings[0]);
        }
    }
}

LoginSystem::~LoginSystem() {
    UsersData.clear();
}

////////////////////////////////////////////////////////////////////////