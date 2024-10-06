#include "Header.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	List list;
	readFromFile(list);
	int mainMenuChoice = mainMenu();
	while (true)
	{
		switch (mainMenuChoice)
		{
		case 1:
			addOneCar(list);
			break;
		case 2:
			catalogOutput(list);
			break;
		case 3:
			updateCarInfo(list);
			break;
		case 4:
			deleteOneCar(list);
			break;
		case 5:
			searchForCar(list);
			break;
		case 6:
			compareCars(list);
			break;
		default:
			return 0;
		}
		mainMenuChoice = mainMenu();
	}
}