
#include "Dire.h"

//////////////////////////////////////////////////////////////

void ChangeColour(int colour) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, colour);
}

int GetKey() {
    int a = 0;
    a = _getch();
    return a - 48;
}

void LangLoad(std::vector<std::string> &language, const short &index) {
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

        language.clear();

        for (int i = 0; i < size_vec; ++i) {
            str_temp_database = GetImport_string(lang, str_temp_database);
            language.push_back(str_temp_database);
        }

        lang.close();
    }
    else {
        ChangeColour(LightRed);
        std::cout << "+~~~~~~~(Предупреждение)~~~~~~~+\n | Файл не может быть открыт! |\n+==============================+\n";
        "Примечание: Возможно вы удалили файлы языка!\nЧтобы их восстановить зайдите в папку deleted_language!";
        lang.close();
        exit(-1);
    }
}

//////////////////////////////////////////////////////////////