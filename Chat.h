#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Messege.h"
using namespace std;

struct UserLoginExp : public exception

{
	const char* what() const noexcept override { return "Ошибка: пользовательский логин занят"; }
};

struct UserNameExp : public exception
{
	const char* what() const noexcept override { return "Ошибка: пользовательское имя занято"; }
};

class Chat
{
private:
	bool ChatWork_ = false;
	vector<User> users_;
	vector<Messege> messeges_;
	shared_ptr<User> currentUser_ = nullptr;

	void login();
	void signUp();
	void showChat() const;
	void showAllUserName() const;
	void addMessege();
	vector<User>& getAllUser() { return users_; }
	vector<Messege>& getAllMessege() { return messeges_; }
	shared_ptr<User> getUserByLogin(const string& login) const;
	shared_ptr<User> getUserByName(const string& name) const;
public:
	void start();
	bool ChatWork() const { return ChatWork_; }
	shared_ptr<User> getCurrentUser()const { return currentUser_; }
	void showLoginMenu();
	void showUserMenu();

};