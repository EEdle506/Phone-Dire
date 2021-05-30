using namespace std;
#include "Dire.h"

const int maxNamesize = 16; const char separator = ' '; int PrintDataCount = 0;
string str_temp_database, str_temp_database1;

//////////////////////////////////////////Конуструктор//////////////////////////////////////

Contact::Contact(string& nick, string& phone) {
    this->nick = nick;
    this->phone = phone;
}

//////////////////////////////////////Конуструктор//////////////////////////////////////////

Dire::Dire() {
    ReadUserSettings();
    SwitchLanguage(arr_settings[4],false);
    system("cls");
    FileNameFormat(arr_settings[6]);
}

Dire::Dire(string & login, string & password) {
    this->login = login;
    this->password = password;
    ReadUserSettings();
    SwitchLanguage(arr_settings[4], false);
    system("cls");
    FileNameFormat(arr_settings[6]);
}

////////////////////////////////////////////Загрузка языка//////////////////////////////////

void Dire::LoadUser() {
    ReadUserSettings();
    ReadUserData();
}

void Dire::SwitchLanguage(short choise, bool check_state) {
    str_temp_database.clear();
    size_t size_vec;

    if (!check_state) {
        arr_settings[4] = choise;   //lang_choise
        switch (choise) {
        case 1:

            str_temp_database.assign("Languages/russian.bin");

            break;

        case 2:

            str_temp_database.assign("Languages/english.bin");

            break;
        case 3:

            str_temp_database.assign("Languages/ukrainian.bin");

            break;
        }

        ifstream lang(str_temp_database, ios::binary);

        if (lang.is_open()) {

            lang.read((char*)&size_vec, sizeof(size_vec));

            Language.clear();

            str_temp_database.clear();

            for (int i = 0; i < size_vec; ++i) {
                str_temp_database = GetImport_string(lang, str_temp_database);

                Language.push_back(str_temp_database);
            }
        }
        else {
            ChangeColour(LightRed);
            cout << "+~~~~~~~(Предупреждение)~~~~~~~+\n | Файл не может быть открыт! |\n+==============================+\n";
            cout << "Примечание: Возможно вы удалили файлы языка!\nЧтобы их восстановить зайдите в папку deleted_language!";
            lang.close();
            exit(-1);
        }
        lang.close();
    }
    else {
        if (arr_settings[5] != choise) {    //lang_state
            ChangeColour(LightGreen);
            if (choise < 4) {
           
                arr_settings[4] = arr_settings[5] = choise;
                SaveUserSettings();
                switch (choise) {
                case 1:
                    str_temp_database.assign("Languages/russian.bin");
                    break;

                case 2:
                    str_temp_database.assign("Languages/english.bin");
                    break;
                case 3:
                    str_temp_database.assign("Languages/ukrainian.bin");
                    break;
                }

                ifstream lang(str_temp_database, ios::binary);
                
                Language.clear();
                str_temp_database.clear();
                lang.read((char*)&size_vec, sizeof(size_vec));
                for (size_t i = 0; i < size_vec; i++) {
                    str_temp_database = GetImport_string(lang, str_temp_database);
                    Language.push_back(str_temp_database);
                }
                lang.close();
                printloadbar(63);
                system("cls");
                cout << Language[13];
                Sleep(arr_settings[0]);
            }
            else {
                printloadbar(63);
                system("cls");
                ChangeColour(Yellow);
                cout << Language[2];
                Sleep(arr_settings[0]);
            }
        }
        else {
            printloadbar(63);
            system("cls");
            ChangeColour(Yellow);
            cout << Language[64];
            Sleep(arr_settings[0]);
        }
    }
}

////////////////////////////////////////////Меню данных/////////////////////////////////////

void Dire::GetDireList() {
    system("cls");
    PrintDataCount = 0; str_temp_database = ""; string temp_phone = "";

    if (!MainContacts.empty()) {
        ChangeColour(White);
        cout << Language[47];
        for (auto elem : MainContacts) {
            PrintDataCount++;
            cout << Language[48] << right << setw(5) << setfill(separator) 
                << PrintDataCount<< Language[49] << left 
                << setw(maxNamesize) << setfill(separator) 
                << elem.nick << Language[50]
                << left << setw(10) << setfill(separator) 
                << elem.phone << Language[51];
        }
        cout << Language[52];

        if (_getch() == 27) printloadbar(26);
        else
            GetDireList();
    }
    else {
        ChangeColour(LightRed);
        cout << Language[0];
        Sleep(arr_settings[0]);
        system("cls");
        ChangeColour(White);
        cout << Language[90];
        if (_getch() == 27) printloadbar(26);
        else
            AddContactToDire(GetKey());
    }
}

bool Dire::UserDireCorrect(const string& name, const string& phone) {
    system("cls");
    ChangeColour(LightRed);
    if (name.empty() | phone.empty()) {
        cout << Language[8];
        Sleep(arr_settings[0]);
        return false;
    }
    for (int i = 0; i < phone.size(); i++) {
        if (64 < (int)phone[i] && 123 > (int)phone[i]) {
            cout << Language[6];
            Sleep(arr_settings[0]);
            return false;
        }
    }
    for (auto element : MainContacts) {
        if (element.nick == name) {
            cout << Language[7];
            Sleep(arr_settings[0]);
            return false;
        }
    }
    if ((phone.size() > 10) | (phone.size() < 9)) {
        cout << Language[6];
        Sleep(arr_settings[0]);
        return false;
    }
    else if (name.size() < 2) {
        cout << Language[8];
        Sleep(arr_settings[0]);
        return false;
    }
    else if (name.size() > 16) {
        cout << Language[9];
        Sleep(arr_settings[0]);
        return false;
    }
    else {
        ChangeColour(White);
        return true;
    }
}

bool Dire::UserDireCorrect(const string& name, int choise) {
    system("cls");
    ChangeColour(LightRed);

    switch (choise) {
    case 1: //name
        for (auto element : MainContacts) {
            if (element.nick == name) {
                cout << Language[7];
                Sleep(arr_settings[0]);
                return false;
            }
        }
        if (name.size() < 2) {
            cout << Language[8];
            Sleep(arr_settings[0]);
            return false;
        }
        else if (name.size() > 16) {
            cout << Language[9];
            Sleep(arr_settings[0]);
            return false;
        }
        ChangeColour(White);
        return true;

    case 2: //phone

        for (int i = 0; i < name.size(); i++) {
            if (64 < (int)name[i] && 123 > (int)name[i]) {
                cout << Language[6];
                Sleep(arr_settings[0]);
                return false;
            }
        }
        if ((name.size() > 10) | (name.size() < 9)) {
            cout << Language[6];
            Sleep(arr_settings[0]);
            return false;
        }
        ChangeColour(White);
        return true;
    default:
        ChangeColour(Yellow);
        cout << Language[2];
        Sleep(arr_settings[0]);
    }
    return false;
}

void Dire::AddContactToDire(short times) {
    if (times < 7 && times > 0) {
        printloadbar(63);
        for (int i = 0; i < times; i++) {
            system("cls");
            ChangeColour(White);
            cout << Language[28];
            getline(cin, str_temp_database);
            cout << Language[29];
            getline(cin, str_temp_database1);
            if (UserDireCorrect(str_temp_database, str_temp_database1)) {
                printloadbar(18);
                MainContacts.push_back(Contact(str_temp_database, str_temp_database1));
                ChangeColour(LightGreen);
                cout << Language[53] << left << setw(maxNamesize) 
                    << setfill(separator) << str_temp_database
                    << Language[54] << left << setw(10) << setfill(separator) 
                    << str_temp_database1 << Language[55];
                Sleep(arr_settings[0]);
            }
        }
    }
    else {
        system("cls");
        ChangeColour(Yellow);
        cout << Language[2];
        Sleep(arr_settings[0]);
    }
    SaveUserData();
}

void Dire::DeleteContact(const size_t contact) {
    system("cls");
    ChangeColour(LightGreen);

    cout << Language[53] << left << setw(maxNamesize) 
        << setfill(separator) << MainContacts[contact].nick
        << Language[54] << left << setw(10) 
        << setfill(separator) << MainContacts[contact].phone << Language[56];
    Sleep(arr_settings[0]);

    MainContacts.erase(MainContacts.begin() + contact);
    MainContacts.shrink_to_fit();

    SaveUserData();
}

void Dire::RenameContact(short choise_rename, const size_t contact, const string& name) {
    system("cls");
    ChangeColour(LightGreen);
    if (UserDireCorrect(name, choise_rename)) {
        switch (choise_rename) {
        case 1:
            MainContacts[contact].nick = name;
            cout << Language[59] << Language[60] << left << setw(maxNamesize) 
                << setfill(separator) << MainContacts[contact].nick
                << Language[60] << left << setw(14) << setfill(separator) << MainContacts[contact].phone
                << Language[61] << Language[62];
            Sleep(arr_settings[0]);

            break;

        case 2:

            MainContacts[contact].phone = name;
            cout << Language[59] << Language[60] << left << setw(maxNamesize) 
                << setfill(separator) << MainContacts[contact].nick
                << Language[60] << left << setw(14) << setfill(separator) << MainContacts[contact].phone
                << Language[61] << Language[62];
            Sleep(arr_settings[0]);

            break;
        }
        SaveUserData();
    }
}

void Dire::SortContacts(short choise) {
    system("cls");

    if (MainContacts.size() < 2) {
        ChangeColour(Yellow);
        cout << Language[65];
        Sleep(arr_settings[0]);
    }
    else {
        if (MainContacts.empty()) {
            ChangeColour(LightRed);
            cout << Language[0];
            Sleep(arr_settings[0]);
        }
        else {
            ChangeColour(LightGreen);
            printloadbar(20);
            switch (choise) {
            case 1:
                
                sort(MainContacts.begin(), MainContacts.end(), [](const Contact& d, const Contact& d1) {
                    return d.nick > d1.nick; 
                });
                cout << Language[89];
                Sleep(arr_settings[0]);

                break;
            case 2:
                
                sort(MainContacts.begin(), MainContacts.end(), [](const Contact& d, const Contact& d1) {
                    return d.nick < d1.nick; 
                });
                cout << Language[89];
                Sleep(arr_settings[0]);

                break;
            case 3:														//Leave

                printloadbar(26);

                break;
            default:

                ChangeColour(Yellow);
                cout << Language[2];
                Sleep(arr_settings[0]);
            }
            SaveUserData();
        }
    }
}

size_t Dire::GetSearchContact(const string& name) {
    system("cls");
    size_t position_vec = 0;
    if (MainContacts.empty()) {
        ChangeColour(LightRed);
        cout << Language[0];
        Sleep(arr_settings[0]);
        return -1;
    }
    else {
        for (auto element : MainContacts) {
            if (!element.nick.find(name)) {
                return position_vec;
            }
            position_vec++;
        }
        ChangeColour(LightRed);
        cout << Language[5];
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