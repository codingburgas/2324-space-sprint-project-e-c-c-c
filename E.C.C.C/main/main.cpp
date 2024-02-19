#include <thread>
#include "mainMenu.hpp"
#include "audio.hpp"

int main()
{
	//std::thread audioThread(initializeSoundtrack);
	mainMenu();
	//soundtrackEnd = true;
	//audioThread.join();
	return 0;
}