#include "Menu.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////

LoginSystem Dire;

int menutype, delay1_text = 1250; const int maxNamesize1 = 16; const char separator1 = ' ';

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GetLoginMenu() {

	while (true) {
		std::string UsersLog = "", UsersPass = "", ContName = "";
		system(Dire.UsersData[Dire.user_position].Language[95].c_str());
		system("cls");
		ChangeColour(White);
		std::cout << Dire.UsersData[Dire.user_position].Language[76];
		if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); break; }

		switch (GetKey()) {
		case 1:																		//log in

			Dire.UsersData[Dire.user_position].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[108].c_str());
			system("cls");

			std::cout << Dire.UsersData[Dire.user_position].Language[77]
			<< Dire.UsersData[Dire.user_position].Language[81];

			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData[Dire.user_position].Language[82];
			getline(std::cin, UsersPass);

			GetDireMainMenu(Dire.GetLoginToAccount(UsersLog, UsersPass));

			continue;

		case 2:																		//sign in

			Dire.UsersData[Dire.user_position].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[109].c_str());
			system("cls");

			std::cout << Dire.UsersData[Dire.user_position].Language[78]
			<< Dire.UsersData[Dire.user_position].Language[81];
			
			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }
			
			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData[Dire.user_position].Language[82];
			getline(std::cin, UsersPass);
			system("cls");
			std::cout << Dire.UsersData[Dire.user_position].Language[93];
			getline(std::cin, ContName);

			if (Dire.SetPassToAccount(UsersLog, UsersPass, ContName)) continue;

			continue;

		case 3:																		//change log/pass
			Dire.UsersData[Dire.user_position].printloadbar(63);

			system(Dire.UsersData[Dire.user_position].Language[110].c_str());
			system("cls");

			std::cout << Dire.UsersData[Dire.user_position].Language[80];
			std::cout << Dire.UsersData[Dire.user_position].Language[81];
			
			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData[Dire.user_position].Language[82];
			getline(std::cin, UsersPass);

			if (Dire.GetLoginToAccount(UsersLog, UsersPass) < Dire.UsersData.size()) {
				Dire.UsersData[Dire.user_position].printloadbar(63);
				system("cls");
				ChangeColour(White);
				std::cout << Dire.UsersData[Dire.user_position].Language[79];

				if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

				Dire.GetChangeAccount(GetKey());
			}

			continue;

		case 4:																					//delete account
			Dire.UsersData[Dire.user_position].printloadbar(63);

			system(Dire.UsersData[Dire.user_position].Language[111].c_str());

			system("cls");
			std::cout << Dire.UsersData[Dire.user_position].Language[85]
			<< Dire.UsersData[Dire.user_position].Language[81];

			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData[Dire.user_position].Language[82];
			getline(std::cin, UsersPass);

			if (Dire.GetLoginToAccount(UsersLog, UsersPass) < Dire.UsersData.size()) {
				Dire.UsersData[Dire.user_position].printloadbar(63);
				system("cls");
				ChangeColour(White);
				std::cout << Dire.UsersData[Dire.user_position].Language[86];

				if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

				switch (GetKey()) {
				case 1:

					Dire.GetDeleteAccount();

					continue;

				case 2:

					Dire.UsersData[Dire.user_position].printloadbar(26);
					system("cls");

					continue;

				default:

					system("cls");
					ChangeColour(Yellow);
					std::cout << Dire.UsersData[Dire.user_position].Language[2];
					Sleep(delay1_text);

					continue;
				}
			}

			continue;

		case 5:																					//change language
			Dire.UsersData[Dire.user_position].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[98].c_str());
			system("cls");
			std::cout << Dire.UsersData[Dire.user_position].Language[43];
			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }
			Dire.UsersData[Dire.user_position].SwitchLanguage(GetKey(), true);

			continue;

		case 6:

			Dire.UsersData[Dire.user_position].printloadbar(26);
			system("cls");
			break;

		default:
			Dire.UsersData[Dire.user_position].printloadbar(63);
			system("cls");
			ChangeColour(Yellow);
			std::cout << Dire.UsersData[Dire.user_position].Language[2];
			Sleep(delay1_text);

			continue;
		}
		break;
	}
}

void GetDireMainMenu(const size_t index) {

	if (index < Dire.UsersData.size()) {
		Dire.UsersData[index].LoadUser();
		Dire.UsersData[index].printloadbar(16);
		while (true) {
			std::string UsersLog = "";
			system(Dire.UsersData[Dire.user_position].Language[96].c_str());
			system("cls");
			ChangeColour(White);

			std::cout << Dire.UsersData[index].Language[38];
			if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); break; }

			switch (GetKey()) {
			case 1:																			//Телефон

				GetDireMenu(index);

				continue;

			case 2:																			//Экспорт

				Dire.UsersData[index].printloadbar(63);
				system(Dire.UsersData[Dire.user_position].Language[112].c_str());
				system("cls");
				std::cout << Dire.UsersData[index].Language[39];

				if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); continue; }

				getline(std::cin, UsersLog);

				if (Dire.UsersData[index].SaveUserData(UsersLog)) {
					Dire.UsersData[index].printloadbar(21);
					system("cls");

					std::cout << Dire.UsersData[index].Language[12];
					Sleep(delay1_text);

					continue;
				}
				else {
					system("cls");
					ChangeColour(LightRed);
					std::cout << Dire.UsersData[index].Language[0];
					Sleep(delay1_text);

					continue;
				}

				continue;

			case 3:																			//Импорт

				Dire.UsersData[index].printloadbar(63);
				system(Dire.UsersData[Dire.user_position].Language[113].c_str());
				system("cls");

				std::cout << Dire.UsersData[index].Language[41];

				if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); continue; }

				getline(std::cin, UsersLog);

				if (Dire.UsersData[index].ReadUserData(UsersLog)) {
					Dire.UsersData[index].printloadbar(22);
					system("cls");

					std::cout << Dire.UsersData[index].Language[14];
					Sleep(delay1_text);

					continue;
				}
				continue;

			case 4:																			//Настройки

				GetSettings(index);

				continue;

			case 5:

				Dire.UsersData[index].printloadbar(26);
				Dire.UsersData[index].MainContacts.clear();

				break;

			default:

				Dire.UsersData[index].printloadbar(63);
				system("cls");

				ChangeColour(Yellow);
				std::cout << Dire.UsersData[index].Language[2];
				Sleep(delay1_text);

				continue;
			}
			break;
		}
		
	}
}

void GetDireMenu(const size_t index) {
	Dire.UsersData[index].printloadbar(63);
	while (true) {
		std::string ContName = "";
		system(Dire.UsersData[Dire.user_position].Language[97].c_str());
		system("cls");

		ChangeColour(White);
		std::cout << Dire.UsersData[index].Language[27];

		if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); break; }

		switch (GetKey()) {
		case 1:

			Dire.UsersData[index].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[105].c_str());
			system("cls");
			Dire.UsersData[index].GetDireList();

			continue;

		case 2:

			Dire.UsersData[index].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[106].c_str());
			system("cls");
			ChangeColour(White);
			std::cout << Dire.UsersData[index].Language[30];

			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

			getline(std::cin, ContName);

			Dire.UsersData[index].printloadbar(15);
			ContactPrefs(index, Dire.UsersData[index].GetSearchContact(ContName));

			continue;
		case 3:

			Dire.UsersData[index].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[104].c_str());
			system("cls");

			ChangeColour(White);
			std::cout << Dire.UsersData[index].Language[90];

			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

			Dire.UsersData[index].AddContactToDire(GetKey());

			continue;

		case 4:
			Dire.UsersData[index].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[107].c_str());
			system("cls");

			ChangeColour(White);
			std::cout << Dire.UsersData[index].Language[31];

			if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

			Dire.UsersData[index].SortContacts(GetKey());

			continue;
		case 5:

			Dire.UsersData[index].printloadbar(26);

			break;

		default:

			Dire.UsersData[index].printloadbar(63);
			system("cls");

			ChangeColour(Yellow);
			std::cout << Dire.UsersData[index].Language[2];
			Sleep(delay1_text);

			continue;
		}
		break;
	}
}

void GetSettings(const size_t index) {

	Dire.UsersData[index].printloadbar(23);

	while (true) {
		system(Dire.UsersData[Dire.user_position].Language[99].c_str());
		system("cls");

		ChangeColour(White);
		std::cout << Dire.UsersData[index].Language[42];

		if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); break; }

		switch (GetKey()) {
		case 1:

			Dire.UsersData[index].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[101].c_str());
			system("cls");

			ChangeColour(White);
			std::cout << Dire.UsersData[index].Language[44];

			if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); continue; }

			delay1_text = Dire.UsersData[index].SetDelay(GetKey());

			continue;

		case 2:

			Dire.UsersData[index].printloadbar(63);
			system("cls");

			ChangeColour(White);

			std::cout << Dire.UsersData[index].Language[67];

			if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); continue; }

			std::cin >> menutype;
			std::cin.ignore();
			Dire.UsersData[index].printloadbar(63);
			Dire.UsersData[index].MassiveAdd(menutype);

			continue;

		case 3:																			//Отключение формата файла (пользователь вводит в ручную), влючение формата файла (програма сама применяет .txt или .bin)

			Dire.UsersData[index].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[102].c_str());
			system("cls");

			std::cout << Dire.UsersData[index].Language[45];

			if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); continue; }

			switch (GetKey()) {
			case 1:

				Dire.UsersData[index].printloadbar(63);
				system("cls");

				std::cout << Dire.UsersData[index].Language[46];

				if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }

				Dire.UsersData[index].FileNameFormat(GetKey());

				continue;
			case 2:

				Dire.UsersData[index].printloadbar(63);
				system("cls");

				Dire.UsersData[index].FileNameFormat(3);

				continue;

			case 3:

				Dire.UsersData[index].printloadbar(26);

				continue;
			default:

				Dire.UsersData[index].printloadbar(63);
				system("cls");

				ChangeColour(Yellow);
				std::cout << Dire.UsersData[index].Language[2];
				Sleep(delay1_text);

				continue;
			}
			continue;

		case 4:

			Dire.UsersData[index].printloadbar(63);
			system(Dire.UsersData[Dire.user_position].Language[103].c_str());
			system("cls");

			std::cout << Dire.UsersData[index].Language[91];

			if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); continue; }

			Dire.UsersData[index].AutoSave(GetKey());

			continue;

		case 5:

			Dire.UsersData[index].printloadbar(26);

			break;

		default:

			Dire.UsersData[index].printloadbar(63);
			system("cls");

			ChangeColour(Yellow);
			std::cout << Dire.UsersData[index].Language[2];
			Sleep(delay1_text);

			continue;
		}
		break;
	}
	Dire.UsersData[index].SaveUserSettings();
}

void ContactPrefs(const size_t index, const size_t contact) {

	if (contact > Dire.UsersData[index].MainContacts.size());
	else {
		if (!Dire.UsersData[index].MainContacts.empty()) {
			std::string ContName = "";
			while (true) {
				system(Dire.UsersData[Dire.user_position].Language[100].c_str());
				system("cls");
				ChangeColour(White);
				std::cout << Dire.UsersData[index].Language[32] << std::left << std::setw(maxNamesize1) << std::setfill(separator1)
					<< Dire.UsersData[index].MainContacts[contact].nick << Dire.UsersData[index].Language[33]
					<< std::left << std::setw(10) << std::setfill(separator1) << Dire.UsersData[index].MainContacts[contact].phone
					<< Dire.UsersData[index].Language[34];

				if (_getch() == 27) { Dire.UsersData[index].printloadbar(26); break; }

				switch (GetKey()) {
				case 1:

					Dire.UsersData[index].printloadbar(63);
					ChangeColour(White);
					system("cls");
					std::cout << Dire.UsersData[index].Language[35];
					
					if (_getch() == 27) { Dire.UsersData[Dire.user_position].printloadbar(26); continue; }
					
					menutype = GetKey();
					
					std::cout << Dire.UsersData[index].Language[36];
					getline(std::cin, ContName);

					Dire.UsersData[index].printloadbar(58);

					Dire.UsersData[index].RenameContact(menutype, contact, ContName);
					
					continue;

				case 2:

					Dire.UsersData[index].printloadbar(19);

					Dire.UsersData[index].DeleteContact(contact);

					break;

				case 3:

					Dire.UsersData[index].printloadbar(26);

					break;

				default:

					Dire.UsersData[index].printloadbar(63);

					ChangeColour(Yellow);
					std::cout << Dire.UsersData[index].Language[2];
					Sleep(delay1_text);

					continue;
				}
				system("cls");
				break;
			}
		}
		else {
			system("cls");
			ChangeColour(LightRed);
			std::cout << Dire.UsersData[index].Language[0];
			Sleep(delay1_text);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////