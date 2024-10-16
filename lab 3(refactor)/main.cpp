#include "Header.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int mainMenuChoice = mainMenu();
	while (true)
	{
		switch (mainMenuChoice)
		{
		case 1:
			addOneCar();
			break;
		case 2:
			catalogOutput();
			break;
		case 3:
			updateCarInfo();
			break;
		case 4:
			deleteOneCar();
			break;
		case 5:
			searchForCar();
			break;
		case 6:
			compareCars();
			break;
		default:
			return 0;
		}
		mainMenuChoice = mainMenu();
	}
}