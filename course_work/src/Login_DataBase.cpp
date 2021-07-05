#include "Dire.h"

///////////////////Ñèñòåìà ëîãèíà(PhoneDire)////////////////////////////

LoginSystem::LoginSystem() {
    UsersData.push_back({});
}

void LoginSystem::DataBaseCleaner(const size_t& index) {
    UsersData.erase(UsersData.begin(), UsersData.begin() + index);
    if (!UsersData.empty()) {
        UsersData.erase(++UsersData.begin(), UsersData.end());
        if (UsersData.empty())
            UsersData.push_back({});
    }
    UsersData.shrink_to_fit();
    user_position = static_cast<unsigned int>(UsersData.size() - 1);
}

void Dire::ChangeAccountPass(const std::string& login, const short& choise) {
    if (login.size() > 2)
        switch (choise) {
        case 1: this->login = login; break;
        case 2: this->password = login; break;
        }
    else {
        system("cls");
        ChangeColour(LightRed);
        std::cout << Language.at(87);
        Sleep(arr_settings[0]);
    }
}

bool Dire::CheckAccountLogin(const std::string& login, const std::string& password) noexcept {
    if (this->login == login && this->password == password)
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
            if (a.size() > 2 && b.size() > 3) {
                ReadDataBase();
                //Поиск по базе существующий аккаунт
                for (size_t i = 0;i<UsersData.size();++i) {
                    if (UsersData.at(i).CheckAccountLogin(a)) {
                        ChangeColour(Yellow);
                        std::cout << UsersData.at(i).Language.at(75);
                        Sleep(UsersData.at(i).arr_settings[0]);
                        DataBaseCleaner(i);

                        return false;
                    }
                }

                UsersData.push_back(Dire(a,b));
                user_position = static_cast<unsigned int>(UsersData.size() - 1);

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

    //Ïîøóê àêêàóíòà
    ReadDataBase();

    if (!a.empty() | !b.empty())
        for (size_t i = 0; i < UsersData.size(); ++i) {
            if (UsersData.at(i).CheckAccountLogin(a, b)) {
                DataBaseCleaner(i);

                ChangeColour(LightGreen);
                std::cout << UsersData.at(user_position).Language.at(72);
                Sleep(UsersData.at(user_position).arr_settings[0]);

                return user_position;
            }
        }

    //Àêêàóíò íå çíàéäåíî
    DataBaseCleaner(user_position);

    ChangeColour(LightRed); 
    std::cout << UsersData.at(user_position).Language.at(73);
    Sleep(UsersData.at(user_position).arr_settings[0]);
    system("cls");

    return static_cast<int>(UsersData.size() * 2 + 1);
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
        system("cls");
        remove(str_temp_phonedire.c_str());

        UsersData.erase(UsersData.begin() + user_position);
        UsersData.shrink_to_fit();

        if (!UsersData.empty()) {
            user_position = 0;
            SaveDataBase();
            UsersData.clear();
            UsersData.push_back({});
        }
        else {
            UsersData.push_back({});
            SaveDataBase();
        }

        UsersData.at(user_position).printloadbar(19);
        ChangeColour(LightGreen);
        std::cout << UsersData.at(user_position).Language.at(88);
        Sleep(UsersData.at(user_position).arr_settings[0]);
    }
}

LoginSystem::~LoginSystem() {
    UsersData.clear();
    user_position = 0;
}

////////////////////////////////////////////////////////////////////////