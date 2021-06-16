#include "Dire.h"

//////////////////////////Настройки///////////////////////////////////

void Dire::FileNameFormat(const short& choise) {
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
        std::cout << Language[2];
        Sleep(arr_settings[0]);
    }
}

void Dire::SetLoad(const short& choise) {
    printloadbar(17);
    system("cls");
    switch (choise) {
    case 1:
        std::cout << Language[37];
        Sleep(arr_settings[0]);
        arr_settings[2] = true;
        break;
    case 2:
        std::cout << Language[69];
        Sleep(arr_settings[0]);
        arr_settings[2] = false;
        break;
    }
}

int Dire::SetDelay(const short& choise) {
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
        std::cout << Language[2];
        Sleep(arr_settings[0]);
        arr_settings[1] = 100;

        return arr_settings[0];
    }
}

void Dire::printloadbar(const short &index_lang) {
    std::string a = "title " + Language[index_lang];
    a.append(" [");
    for (int i = 0; i < 7; i++) {
        a.append(":::");
        if (i == 6) 
            a.append("] 100%\n");
        system(a.c_str());
        Sleep(arr_settings[1]-40);
    }
    a.clear();
    Sleep(100);
    system("title ");
}

void Dire::MassiveAdd(const size_t& amount) {
    auto temp = MainContacts;
    
    try {
        printloadbar(68);
        for (int i = 0; i < amount; ++i)
            MainContacts.push_back(Contact("testing name", "9999999999"));
        SaveUserData(); 
    }
    catch (const std::exception& ex)
    {
        ChangeColour(LightRed);
        std::cout << "Something went wrong!\n[MassiveAdd] Code: "<<ex.what();
        Sleep(arr_settings[0]);
        MainContacts.clear();
        MainContacts = temp;
    }
}

void Dire::AutoSave(const short& choise) {
    printloadbar(17);
    system("cls");
    ChangeColour(LightGreen);
    switch (choise) {
    case 1:
        std::cout << Language[40];
        Sleep(arr_settings[0]);
        arr_settings[3] = true;

        break;

    case 2:
        
        std::cout << Language[92];
        Sleep(arr_settings[0]);
        arr_settings[3] = false;

        break;

    case 3:
        printloadbar(26);

        break;

    default:
        ChangeColour(Yellow);
        std::cout << Language[2];
        Sleep(arr_settings[0]);
    }
}

//////////////////////////////////////////////////////////////////////