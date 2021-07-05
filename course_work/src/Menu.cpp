#include "Menu.h"

#include <thread>

#define maxNamesize1 16
#define separator1 ' '

////////////////////////////////////////////////////////////////////////////////////////////////////////////

LoginSystem Dire;

static int delay1_text = 1250;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GetLoginMenu() {

	while (true) {
		std::string UsersLog = "", UsersPass = "", ContName = "";
		system(Dire.UsersData.at(Dire.pos).Language.at(95).c_str());
		system("cls");
		ChangeColour(White);
		std::cout << Dire.UsersData.at(Dire.pos).Language.at(76);
		if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); break; }

		switch (GetKey()) {
		case 1:																		//log in

			Dire.UsersData.at(Dire.pos).printloadbar(63);
			system(Dire.UsersData.at(Dire.pos).Language.at(108).c_str());
			system("cls");

			std::cout << Dire.UsersData.at(Dire.pos).Language.at(77)
			<< Dire.UsersData.at(Dire.pos).Language.at(81);

			if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); continue; }

			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(82);
			getline(std::cin, UsersPass);

			GetDireMainMenu(Dire.GetLoginToAccount(UsersLog, UsersPass));

			continue;

		case 2:																		//sign in

			Dire.UsersData.at(Dire.pos).printloadbar(63);
			system(Dire.UsersData.at(Dire.pos).Language.at(109).c_str());
			system("cls");

			std::cout << Dire.UsersData.at(Dire.pos).Language.at(78)
			<< Dire.UsersData.at(Dire.pos).Language.at(81);
			
			if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); continue; }
			
			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(82);
			getline(std::cin, UsersPass);
			system("cls");
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(93);
			getline(std::cin, ContName);

			if (Dire.SetPassToAccount(UsersLog, UsersPass, ContName)) continue;

			continue;

		case 3:																		//change log/pass
			Dire.UsersData.at(Dire.pos).printloadbar(63);

			system(Dire.UsersData.at(Dire.pos).Language.at(110).c_str());
			system("cls");

			std::cout << Dire.UsersData.at(Dire.pos).Language.at(80);
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(81);
			
			if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); continue; }

			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(82);
			getline(std::cin, UsersPass);

			if (Dire.GetLoginToAccount(UsersLog, UsersPass) < Dire.UsersData.size()) {
				Dire.UsersData.at(Dire.pos).printloadbar(63);
				system("cls");
				ChangeColour(White);
				std::cout << Dire.UsersData.at(Dire.pos).Language.at(79);

				if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); continue; }

				Dire.GetChangeAccount(GetKey());
			}

			continue;

		case 4:																					//delete account
			Dire.UsersData.at(Dire.pos).printloadbar(63);

			system(Dire.UsersData.at(Dire.pos).Language.at(111).c_str());

			system("cls");
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(85)
			<< Dire.UsersData.at(Dire.pos).Language.at(81);

			if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); continue; }

			getline(std::cin, UsersLog);
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(82);
			getline(std::cin, UsersPass);

			if (Dire.GetLoginToAccount(UsersLog, UsersPass) < Dire.UsersData.size()) {
				Dire.UsersData.at(Dire.pos).printloadbar(63);
				system("cls");
				ChangeColour(White);
				std::cout << Dire.UsersData.at(Dire.pos).Language.at(86);

				if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); continue; }

				switch (GetKey()) {
				case 1:

					Dire.GetDeleteAccount();

					continue;

				case 2:

					Dire.UsersData.at(Dire.pos).printloadbar(26);
					system("cls");

					continue;

				default:

					system("cls");
					ChangeColour(Yellow);
					std::cout << Dire.UsersData.at(Dire.pos).Language.at(2);
					Sleep(delay1_text);

					continue;
				}
			}

			continue;

		case 5:																					//change language
			Dire.UsersData.at(Dire.pos).printloadbar(63);
			system(Dire.UsersData.at(Dire.pos).Language.at(98).c_str());
			system("cls");

			std::cout << Dire.UsersData.at(Dire.pos).Language.at(43);

			if (_getch() == 27) { Dire.UsersData.at(Dire.pos).printloadbar(26); continue; }

			Dire.UsersData.at(Dire.pos).SwitchLanguage(GetKey(), true);

			continue;

		case 6:

			Dire.UsersData.at(Dire.pos).printloadbar(26);
			system("cls");
			break;

		default:
			Dire.UsersData.at(Dire.pos).printloadbar(63);
			system("cls");
			ChangeColour(Yellow);
			std::cout << Dire.UsersData.at(Dire.pos).Language.at(2);
			Sleep(delay1_text);

			continue;
		}
		break;
	}
}

void GetDireMainMenu(const size_t index) {

	if (index < Dire.UsersData.size()) {
		Dire.UsersData.at(index).LoadUser();
		Dire.UsersData.at(index).printloadbar(16);
		while (true) {
			std::string UsersLog = "";
			system(Dire.UsersData.at(index).Language.at(96).c_str());
			system("cls");
			ChangeColour(White);

			std::cout << Dire.UsersData.at(index).Language.at(38);
			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); Dire.UsersData.at(index).MainContacts.clear(); break; }

			switch (GetKey()) {
			case 1:																			//Телефон

				GetDireMenu(index);

				continue;

			case 2:																			//Экспорт

				Dire.UsersData.at(index).printloadbar(63);
				system(Dire.UsersData.at(index).Language.at(112).c_str());
				system("cls");
				std::cout << Dire.UsersData.at(index).Language.at(39);

				if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

				getline(std::cin, UsersLog);

				if (Dire.UsersData.at(index).SaveUserData(UsersLog)) {
					Dire.UsersData.at(index).printloadbar(21);
					system("cls");

					std::cout << Dire.UsersData.at(index).Language.at(12);
					Sleep(delay1_text);

					continue;
				}
				else {
					system("cls");
					ChangeColour(LightRed);
					std::cout << Dire.UsersData.at(index).Language.at(0);
					Sleep(delay1_text);

					continue;
				}

				continue;

			case 3:																			//Импорт

				Dire.UsersData.at(index).printloadbar(63);
				system(Dire.UsersData.at(index).Language.at(113).c_str());
				system("cls");

				std::cout << Dire.UsersData.at(index).Language.at(41);

				if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

				getline(std::cin, UsersLog);

				if (Dire.UsersData.at(index).ReadUserData(UsersLog)) {
					Dire.UsersData.at(index).printloadbar(22);
					system("cls");

					std::cout << Dire.UsersData.at(index).Language.at(14);
					Sleep(delay1_text);

					continue;
				}
				continue;

			case 4:																			//Настройки

				GetSettings(index);

				continue;

			case 5:

				Dire.UsersData.at(index).printloadbar(26);
				Dire.UsersData.at(index).MainContacts.clear();

				break;

			default:

				Dire.UsersData.at(index).printloadbar(63);
				system("cls");

				ChangeColour(Yellow);
				std::cout << Dire.UsersData.at(index).Language.at(2);
				Sleep(delay1_text);

				continue;
			}
			break;
		}
	}
}

void GetDireMenu(const size_t index) {
	Dire.UsersData.at(index).printloadbar(63);
	while (true) {
		std::string ContName = "";
		system(Dire.UsersData.at(index).Language.at(97).c_str());
		system("cls");

		ChangeColour(White);
		std::cout << Dire.UsersData.at(index).Language.at(27);

		if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); break; }

		switch (GetKey()) {
		case 1:

			Dire.UsersData.at(index).printloadbar(63);
			system(Dire.UsersData.at(index).Language.at(105).c_str());
			system("cls");
			Dire.UsersData.at(index).GetDireList();

			continue;

		case 2:

			Dire.UsersData.at(index).printloadbar(63);
			system(Dire.UsersData.at(index).Language.at(106).c_str());
			system("cls");
			ChangeColour(White);
			std::cout << Dire.UsersData.at(index).Language.at(30);

			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

			getline(std::cin, ContName);

			Dire.UsersData.at(index).printloadbar(15);
			ContactPrefs(index, Dire.UsersData.at(index).GetSearchContact(ContName));

			continue;
		case 3:

			Dire.UsersData.at(index).printloadbar(63);
			system(Dire.UsersData.at(index).Language.at(104).c_str());
			system("cls");

			ChangeColour(White);
			std::cout << Dire.UsersData.at(index).Language.at(90);

			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

			Dire.UsersData.at(index).AddContactToDire(GetKey());

			continue;

		case 4:
			Dire.UsersData.at(index).printloadbar(63);
			system(Dire.UsersData.at(index).Language.at(107).c_str());
			system("cls");

			ChangeColour(White);
			std::cout << Dire.UsersData.at(index).Language.at(31);

			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

			Dire.UsersData.at(index).SortContacts(GetKey());

			continue;
		case 5:

			Dire.UsersData.at(index).printloadbar(26);

			break;

		default:

			Dire.UsersData.at(index).printloadbar(63);
			system("cls");

			ChangeColour(Yellow);
			std::cout << Dire.UsersData.at(index).Language.at(2);
			Sleep(delay1_text);

			continue;
		}
		break;
	}
}

void GetSettings(const size_t index) {
	int menutype;
	Dire.UsersData.at(index).printloadbar(23);

	while (true) {
		system(Dire.UsersData.at(index).Language.at(99).c_str());
		system("cls");

		ChangeColour(White);
		std::cout << Dire.UsersData.at(index).Language.at(42);

		if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); break; }

		switch (GetKey()) {
		case 1:

			Dire.UsersData.at(index).printloadbar(63);
			system(Dire.UsersData.at(index).Language.at(101).c_str());
			system("cls");

			ChangeColour(White);
			std::cout << Dire.UsersData.at(index).Language.at(44);

			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

			delay1_text = Dire.UsersData.at(index).SetDelay(GetKey());

			continue;

		case 2:

			Dire.UsersData.at(index).printloadbar(63);
			system("cls");

			ChangeColour(White);

			std::cout << Dire.UsersData.at(index).Language.at(67);

			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

			std::cin >> menutype;
			std::cin.ignore();

			MassiveAdd(Dire, index, menutype);

			Dire.UsersData.at(index).printloadbar(63);

			continue;

		case 3:																			//Отключение формата файла (пользователь вводит в ручную), влючение формата файла (програма сама применяет .txt или .bin)

			Dire.UsersData.at(index).printloadbar(63);
			system(Dire.UsersData.at(index).Language.at(102).c_str());
			system("cls");

			std::cout << Dire.UsersData.at(index).Language.at(45);

			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

			switch (GetKey()) {
			case 1:

				Dire.UsersData.at(index).printloadbar(63);
				system("cls");

				std::cout << Dire.UsersData.at(index).Language.at(46);

				if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

				Dire.UsersData.at(index).FileNameFormat(GetKey());

				continue;
			case 2:

				Dire.UsersData.at(index).printloadbar(63);
				system("cls");

				Dire.UsersData.at(index).FileNameFormat(3);

				continue;

			case 3:

				Dire.UsersData.at(index).printloadbar(26);

				continue;
			default:

				Dire.UsersData.at(index).printloadbar(63);
				system("cls");

				ChangeColour(Yellow);
				std::cout << Dire.UsersData.at(index).Language.at(2);
				Sleep(delay1_text);

				continue;
			}
			continue;

		case 4:

			Dire.UsersData.at(index).printloadbar(63);
			system(Dire.UsersData.at(index).Language.at(103).c_str());
			system("cls");

			std::cout << Dire.UsersData.at(index).Language.at(91);

			if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }

			Dire.UsersData.at(index).AutoSave(GetKey());

			continue;

		case 5:

			Dire.UsersData.at(index).printloadbar(26);

			break;

		default:

			Dire.UsersData.at(index).printloadbar(63);
			system("cls");

			ChangeColour(Yellow);
			std::cout << Dire.UsersData.at(index).Language.at(2);
			Sleep(delay1_text);

			continue;
		}
		break;
	}
	Dire.UsersData.at(index).SaveUserSettings();
}

void ContactPrefs(const size_t index, const size_t& contact) {
	if (contact > Dire.UsersData.at(index).MainContacts.size());
	else {
		if (!Dire.UsersData.at(index).MainContacts.empty()) {
			std::string ContName = "";
			int menutype;
			while (true) {
				system(Dire.UsersData.at(index).Language.at(100).c_str());
				system("cls");
				ChangeColour(White);
				std::cout << Dire.UsersData.at(index).Language.at(32) << std::left << std::setw(maxNamesize1) << std::setfill(separator1)
					<< Dire.UsersData.at(index).MainContacts.at(contact).nick << Dire.UsersData.at(index).Language.at(33)
					<< std::left << std::setw(10) << std::setfill(separator1) << Dire.UsersData.at(index).MainContacts.at(contact).phone
					<< Dire.UsersData.at(index).Language.at(34);

				if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); break; }

				switch (GetKey()) {
				case 1:

					Dire.UsersData.at(index).printloadbar(63);
					ChangeColour(White);
					system("cls");
					std::cout << Dire.UsersData.at(index).Language.at(35);
					
					if (_getch() == 27) { Dire.UsersData.at(index).printloadbar(26); continue; }
					
					menutype = GetKey();
					
					std::cout << Dire.UsersData.at(index).Language.at(36);
					getline(std::cin, ContName);

					Dire.UsersData.at(index).printloadbar(58);

					Dire.UsersData.at(index).RenameContact(menutype, contact, ContName);
					
					continue;

				case 2:

					Dire.UsersData.at(index).printloadbar(19);

					Dire.UsersData.at(index).DeleteContact(contact);

					break;

				case 3:

					Dire.UsersData.at(index).printloadbar(26);

					break;

				default:

					Dire.UsersData.at(index).printloadbar(63);

					ChangeColour(Yellow);
					std::cout << Dire.UsersData.at(index).Language.at(2);
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
			std::cout << Dire.UsersData.at(index).Language.at(0);
			Sleep(delay1_text);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////