#include "Header.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	List list;
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
		default:
			return 0;
		}
		mainMenuChoice = mainMenu();
	}
}