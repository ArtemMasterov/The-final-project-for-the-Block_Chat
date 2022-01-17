#include<iostream>
#include"Chat.h"
using namespace std;

void Chat::start()
{
	ChatWork_ = true;
}
shared_ptr<User> Chat::getUserByLogin(const string& login) const
{
	for (auto &user: users_)
	{
		if (login == user.getUserLogin())
			return make_shared<User>(user);
	}
	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const
{
	for (auto& user: users_)
	{
		if (name == user.getUserName())
			return make_shared<User>(user);
	}
	return nullptr;
}
void Chat::login()
{
	string login, password;
	char operation;

	do
	{
		cout << "Логин:";
		cin >> login;
		cout << "Пароль:";
		cin >> password;

		currentUser_ = getUserByLogin(login);
		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;
			cout << "Ошибка входа..." << endl;
			cout << "(0)выход (любая клавиша) для повтора: ";
			cin >> operation;

			if (operation == '0')
				break;
		}
	} while (!currentUser_);
}
void Chat::signUp()
{
	string login, password, name;

	cout << "Логин:  ";
	cin >> login;
	cout << "Пароль:  ";
	cin >> password;
	cout << "Имя:   ";
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>(user);
}
void Chat::showChat()const
{
	string from;
	string to;

	cout << "------Чат------" << endl;

	for (auto& mess : messeges_)
	{
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom() ? "Меня" : getUserByLogin(mess.getFrom())->getUserName());
			if (mess.getTo() == "all")
			{
				to = "(всем)";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "Мне" : getUserByLogin(mess.getTo())->getUserName();
			}

			cout << "  Сообщение от  " << from << "  Кому  " << to << endl;
			cout << "Текст  " << mess.getText() << endl;
		}
	}
	cout << "---------------" << endl;
}
void Chat::showLoginMenu()
{
	currentUser_ = nullptr;
	char operation;
	do
	{
		cout << "\033[32m" << "(1)Логин" << endl;
		cout << "(2)Регистрация" << endl;
		cout << "(0)Выход из программы" << endl;
		cout << "\033[36m" << ">>" << "\033[0m";
		cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case'0':
			ChatWork_ = false;
			break;
		default:
			cout << "1 или 2..."<<endl;
			break;
		}
	} while (!currentUser_ && ChatWork_);
}
void Chat::showUserMenu()
{
	char operation;

	cout << "Привет," << currentUser_->getUserName() << endl;
	while (currentUser_) {
		cout << "Меню: (1) показать чат | (2) добавить сообщение | (3) пользователи | (0) выход из системы ";


		cout << endl;
		cout << ">> ";
		cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case'2':
			addMessege();
			break;
		case'3':
			showAllUserName();
			break;
		case'0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "неизвестный выбор..." << endl;
			break;
		}
	}
}

void Chat::showAllUserName() const
{
	cout << "--Пользователь--" << endl;
	for (auto& user : users_)
	{
		cout << user.getUserName();

		if (currentUser_->getUserLogin() == user.getUserLogin())
			cout << "(Я)";

		cout << endl;
	}
	cout << "----------------" << endl;
}

void Chat::addMessege()
{
	string to, text;

	cout << "Кому (укажите имя или all (всем): ";
	cin >> to;
	cout << "Текст:  ";
	cin.ignore();
	getline(cin,text);

	if (!(to == "all" || getUserByName(to)))
	{
		cout << "Ошибка. Сообщение не отправлено. Не удаеться найти: " << to << endl;
		return;
	}

	if (to == "all")
		messeges_.push_back(Messege(currentUser_->getUserLogin(),"all" , text ));
	else
		messeges_.push_back(Messege(currentUser_ ->getUserLogin(), getUserByName(to)->getUserLogin(), text ));
}