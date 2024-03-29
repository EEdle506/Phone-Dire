#include "Dire.h"

#define maxNamesize 16
#define separator ' '

//////////////////////////////////////////������������//////////////////////////////////////

Contact::Contact(std::string&& nick, std::string&& phone) {
    this->nick = nick;
    this->phone = phone;
}

Contact::Contact(std::string& nick, std::string& phone) {
    this->nick = nick;
    this->phone = phone;
}

//////////////////////////////////////������������//////////////////////////////////////////

Dire::Dire() {
    ReadUserSettings();
    SwitchLanguage(arr_settings[4],false);
    FileNameFormat(arr_settings[6]);
}

Dire::Dire(const std::string& login, const std::string& password) : login(login), password(password) {
    ReadUserSettings();
    SwitchLanguage(arr_settings[4], false);
    FileNameFormat(arr_settings[6]);
}

void Dire::LoadUser() {
    ReadUserSettings();
    ReadUserData();
}

////////////////////////////////////////////�������� �����//////////////////////////////////

void Dire::LangLoad(std::vector<std::string> &Language, const short& index)
{
    std::string str_temp_database;

    switch (index) {
    case 1:
        str_temp_database.assign("Languages/russian.bin"); break;
    case 2:
        str_temp_database.assign("Languages/english.bin"); break;
    case 3:
        str_temp_database.assign("Languages/ukrainian.bin"); break;
    }

    std::ifstream lang(str_temp_database, std::ios::binary);

    if (lang.is_open()) {
        size_t size_vec;
        lang.read((char*)&size_vec, sizeof(size_vec));

        Language.clear();

        for (int i = 0; i < size_vec; ++i) {
            str_temp_database = GetImport_string(lang, str_temp_database);
            Language.push_back(str_temp_database);
        }

        lang.close();
    }
    else {
        ChangeColour(LightRed);
        std::cout << "+~~~~~~~(��������������)~~~~~~~+\n | ���� �� ����� ���� ������! |\n+==============================+\n";
        "����������: �������� �� ������� ����� �����!\n����� �� ������������ ������� � ����� deleted_language!";
        lang.close();
        exit(-1);
    }
}

void Dire::SwitchLanguage(const short& choise, bool check_state) {
    
    //Without cheking language
    if (!check_state) {
        arr_settings[4] = choise;   //lang_choise
        Dire::LangLoad(Language,choise);
    }
    //With cheking language state
    else {
        if (arr_settings[5] != choise) {    //lang_state
            ChangeColour(LightGreen);

            if (choise < 4) {
                arr_settings[4] = arr_settings[5] = choise;

                SaveUserSettings();

                Dire::LangLoad(Language, choise);

                system("cls");
                std::cout << Language.at(13);
                Sleep(arr_settings[0]);
            }
            else {
                system("cls");
                ChangeColour(Yellow);
                std::cout << Language.at(2);
                Sleep(arr_settings[0]);
            }
        }
        else {

            system("cls");
            ChangeColour(Yellow);
            std::cout << Language.at(64);
            Sleep(arr_settings[0]);
        }
        printloadbar(63);
    }
    system("cls");
}

////////////////////////////////////////////���� ������/////////////////////////////////////

void Dire::GetDireList() {
    system("cls");
    if (!MainContacts.empty()) {
        ChangeColour(White);
        int PrintDataCount = 0;
        std::cout << Language.at(47);
        for (auto& elem : MainContacts) {
            PrintDataCount++;
            std::cout << Language.at(48) << std::right << std::setw(5) << std::setfill(separator)
                << PrintDataCount<< Language.at(49) << std::left
                << std::setw(maxNamesize) << std::setfill(separator)
                << elem.nick << Language.at(50)
                << std::left << std::setw(10) << std::setfill(separator)
                << elem.phone << Language.at(51);
        }
        std::cout << Language.at(52);

        if (_getch() == 27) printloadbar(26);
        else GetDireList();
    }
    else {
        ChangeColour(LightRed);
        std::cout << Language.at(0);
        Sleep(arr_settings[0]);
        system("cls");
        ChangeColour(White);
        std::cout << Language.at(90);
        if (_getch() == 27) printloadbar(26);
        else AddContactToDire(GetKey());
    }
}

bool Dire::UserDireCorrect(const std::string& name, const std::string& phone) const {
    system("cls");
    ChangeColour(LightRed);
    if (name.empty() | phone.empty()) {
        std::cout << Language.at(8);
        Sleep(arr_settings[0]);
        return false;
    }
    for (int i = 0; i < phone.size(); ++i) {
        if (64 < (int)phone.at(i) && 123 > (int)phone.at(i)) {
            std::cout << Language.at(6);
            Sleep(arr_settings[0]);
            return false;
        }
    }
    for (auto& elem : MainContacts) {
        if (elem.nick == name) {
            std::cout << Language.at(7);
            Sleep(arr_settings[0]);
            return false;
        }
    }
    if ((phone.size() > 10) | (phone.size() < 9)) {
        std::cout << Language.at(6);
        Sleep(arr_settings[0]);
        return false;
    }
    else if (name.size() < 2) {
        std::cout << Language.at(8);
        Sleep(arr_settings[0]);
        return false;
    }
    else if (name.size() > 16) {
        std::cout << Language.at(9);
        Sleep(arr_settings[0]);
        return false;
    }
    else {
        ChangeColour(White);
        return true;
    }
}

bool Dire::UserDireCorrect(const std::string& name, int choise) const {
    system("cls");
    ChangeColour(LightRed);

    switch (choise) {
    case 1: //name
        for (auto& elem : MainContacts) {
            if (elem.nick == name) {
                std::cout << Language.at(7);
                Sleep(arr_settings[0]);

                return false;
            }
        }
        if (name.size() < 2) {
            std::cout << Language.at(8);
            Sleep(arr_settings[0]);

            return false;
        }
        else if (name.size() > 16) {
            std::cout << Language.at(9);
            Sleep(arr_settings[0]);

            return false;
        }
        ChangeColour(White);

        return true;

    case 2: //phone

        for (int i = 0; i < name.size(); ++i) {
            if (64 < (int)name.at(i) && 123 > (int)name.at(i)) {
                std::cout << Language.at(6);
                Sleep(arr_settings[0]);

                return false;
            }
        }
        if ((name.size() > 10) | (name.size() < 9)) {
            std::cout << Language.at(6);
            Sleep(arr_settings[0]);

            return false;
        }
        ChangeColour(White);

        return true;
    default:
        ChangeColour(Yellow);
        std::cout << Language.at(2);
        Sleep(arr_settings[0]);
    }

    return false;
}

void Dire::AddContactToDire(const short& times) {
    if (times < 7 && times > 0) {
        printloadbar(63);
        std::string str_temp_database = "", str_temp_database1;
        for (int i = 0; i < times; ++i) {
            system("cls");
            ChangeColour(White);
            std::cout << Language.at(28);
            getline(std::cin, str_temp_database);
            std::cout << Language.at(29);
            getline(std::cin, str_temp_database1);
            if (UserDireCorrect(str_temp_database, str_temp_database1)) {
                printloadbar(18);
                MainContacts.push_back(Contact(str_temp_database, str_temp_database1));
                ChangeColour(LightGreen);
                std::cout << Language.at(53) << std::left << std::setw(maxNamesize)
                    << std::setfill(separator) << str_temp_database
                    << Language.at(54) << std::left << std::setw(10) << std::setfill(separator)
                    << str_temp_database1 << Language.at(55);
                Sleep(arr_settings[0]);
                SaveUserData();
            }
        }
    }
    else {
        system("cls");
        ChangeColour(Yellow);
        std::cout << Language.at(2);
        Sleep(arr_settings[0]);
    }
}

void Dire::DeleteContact(const size_t& contact) {
    system("cls");
    ChangeColour(LightGreen);

    std::cout << Language.at(53) << std::left << std::setw(maxNamesize)
        << std::setfill(separator) << MainContacts.at(contact).nick
        << Language.at(54) << std::left << std::setw(10)
        << std::setfill(separator) << MainContacts.at(contact).phone << Language.at(56);
    Sleep(arr_settings[0]);

    MainContacts.erase(MainContacts.begin() + contact);
    MainContacts.shrink_to_fit();

    SaveUserData();
}

void Dire::RenameContact(const short& choise_rename, const size_t& contact, const std::string& name) {
    system("cls");
    ChangeColour(LightGreen);

    if (UserDireCorrect(name, choise_rename)) {
        printloadbar(63);
        switch (choise_rename) {
        case 1:

            MainContacts.at(contact).nick = name;
            std::cout << Language.at(59) << Language.at(60) << std::left << std::setw(maxNamesize)
                << std::setfill(separator) << MainContacts.at(contact).nick
                << Language.at(60) << std::left << std::setw(14) << std::setfill(separator) << MainContacts.at(contact).phone
                << Language.at(61) << Language.at(62);
            Sleep(arr_settings[0]);

            break;

        case 2:

            MainContacts.at(contact).phone = name;
            std::cout << Language.at(59) << Language.at(60) << std::left << std::setw(maxNamesize)
                << std::setfill(separator) << MainContacts.at(contact).nick
                << Language.at(60) << std::left << std::setw(14) << std::setfill(separator) << MainContacts.at(contact).phone
                << Language.at(61) << Language.at(62);
            Sleep(arr_settings[0]);

            break;
        }
        SaveUserData();
    }
}

void Dire::SortContacts(const short& choise) {
    printloadbar(20);
    system("cls");

    if (MainContacts.size() < 2) {
        ChangeColour(Yellow);
        std::cout << Language.at(65);
        Sleep(arr_settings[0]);
    }
    else {
        if (MainContacts.empty()) {
            ChangeColour(LightRed);
            std::cout << Language.at(0);
            Sleep(arr_settings[0]);
        }
        else {
            ChangeColour(LightGreen);
            switch (choise) {
            case 1:
                
                std::sort(MainContacts.begin(), MainContacts.end(), [](const Contact& d, const Contact& d1) {
                    return d.nick > d1.nick; 
                });
                std::cout << Language.at(89);
                Sleep(arr_settings[0]);

                break;
            case 2:
                
                std::sort(MainContacts.begin(), MainContacts.end(), [](const Contact& d, const Contact& d1) {
                    return d.nick < d1.nick; 
                });
                std::cout << Language.at(89);
                Sleep(arr_settings[0]);

                break;
            case 3:														//Leave

                printloadbar(26);

                break;
            default:

                ChangeColour(Yellow);
                std::cout << Language.at(2);
                Sleep(arr_settings[0]);
            }
            SaveUserData();
        }
    }
}

size_t Dire::GetSearchContact(const std::string& name) {
    system("cls");
    size_t position_vec = 0;
    if (MainContacts.empty()) {
        ChangeColour(LightRed);
        std::cout << Language.at(0);
        Sleep(arr_settings[0]);
        return -1;
    }
    else {
        for (auto& element : MainContacts) {
            if (!element.nick.find(name)) {
                return position_vec;
            }
            position_vec++;
        }
        ChangeColour(LightRed);
        std::cout << Language.at(5);
        Sleep(arr_settings[0]);
        return -1;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

Contact::~Contact() {
    nick.clear();
    phone.clear();
}

Dire::~Dire() {
    MainContacts.clear();
    login.clear();
    password.clear();
    Language.clear();
}