#include "Header.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	Car** array = new Car*;
	int numOfCars = 0;
	int mainMenuChoice = mainMenu();
	while (true)
	{
		switch (mainMenuChoice)
		{
		case 1:
			array = addOneCar(array, numOfCars);
			break;
		case 2:
			catalogOutput(array, numOfCars);
			break;
		case 3:
			array = updateCarInfo(array, numOfCars);
			break;
		case 4:
			array = deleteOneCar(array, numOfCars);
			break;
		default:
			freeMemory(array, numOfCars);
			return 0;
		}
		mainMenuChoice = mainMenu();
	}
}