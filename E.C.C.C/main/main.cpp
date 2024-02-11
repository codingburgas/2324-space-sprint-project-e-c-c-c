#include <thread>
#include "mainMenu.hpp"
#include "audio.hpp"

int main()
{
	std::thread audioThread(initializeSoundtrack);
	mainMenu();
	return 0;
}