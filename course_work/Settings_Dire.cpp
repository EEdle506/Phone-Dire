using namespace std;
#include "Dire.h"

//////////////////////////Настройки///////////////////////////////////

void Dire::FileNameFormat(short choise) {
    printloadbar(17);
    system("cls");
    switch (choise) {
    case 1:
        format_file = ".bin";
        arr_settings[6] = choise;
        break;
    case 2:
        format_file = ".txt";
        arr_settings[6] = choise;
        break;
    case 3:
        format_file = "";
        arr_settings[6] = choise;
        break;
    default:
        ChangeColour(Yellow);
        cout << Language[2];
        Sleep(arr_settings[0]);
    }
}

void Dire::SetLoad(int choise) {
    printloadbar(17);
    system("cls");
    switch (choise) {
    case 1:
        cout << Language[37];
        Sleep(arr_settings[0]);
        arr_settings[2] = true;
        break;
    case 2:
        cout << Language[69];
        Sleep(arr_settings[0]);
        arr_settings[2] = false;
        break;
    }
}

int Dire::SetDelay(short choise) {
    printloadbar(17);
    
    switch (choise) {
    case 1:

        arr_settings[0] = 1500;
        arr_settings[1] = 250;

        return arr_settings[0];

    case 2:

        arr_settings[0] = 1000;
        arr_settings[1] = 150;

        return arr_settings[0];

    case 3:

        arr_settings[0] = 750;
        arr_settings[1] = 100;

        return arr_settings[0];

    default:

        system("cls");
        ChangeColour(Yellow);
        cout << Language[2];
        Sleep(arr_settings[0]);
        arr_settings[1] = 100;

        return arr_settings[0];
    }
}

void Dire::printloadbar(short index_lang) {
    string a = "title " + Language[index_lang];
    a.append(" [");
    for (int i = 0; i < 7; i++) {
        a.append("::::");
        if (i == 6) a.append("] 100%\n");
        system(a.c_str());
        Sleep(arr_settings[1]-40);
    }
    a.clear();
    Sleep(100);
    system("title ");
}

void Dire::MassiveAdd(size_t amount) {
    printloadbar(68);
    string text = "testing name"; string phone = "9999999999";

    if (amount < 2147483647) {
        for (int i = 0; i < amount; i++) {
            MainContacts.push_back(Contact(text, phone));
        }
        SaveUserData();
        printloadbar(63);
    }
    else {
        ChangeColour(LightRed);
        cout << Language[2];
        Sleep(arr_settings[0]);
    }
}

void Dire::AutoSave(short choise) {
    printloadbar(17);
    system("cls");
    ChangeColour(LightGreen);
    switch (choise) {
    case 1:
        cout << Language[40];
        Sleep(arr_settings[0]);
        arr_settings[3] = true;

        break;

    case 2:
        
        cout << Language[92];
        Sleep(arr_settings[0]);
        arr_settings[3] = false;

        break;

    case 3:
        printloadbar(26);

        break;

    default:
        ChangeColour(Yellow);
        cout << Language[2];
        Sleep(arr_settings[0]);
    }
}

//////////////////////////////////////////////////////////////////////