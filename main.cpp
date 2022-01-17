#include "Chat.h"
#include <Windows.h>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Chat chat;

	chat.start();

	while(chat.ChatWork()) {
		chat.showLoginMenu();
		while(chat.getCurrentUser())	{
			chat.showUserMenu();
		}
	}
	return 0;
}