#include "Header.h"

using namespace std;

List::~List()
{
	for (int i = 0; i < num; i++)
	{
		removeByIndex(i);
	}
}
int List::getNum() const
{
	return num;
}
bool List::isEmpty() const
{
	return first == nullptr;
}
void List::push(int year, int mileage, float price, const string& brand, const string& model)
{
	Node* temp = new Node;
	if (isEmpty() == 1)
	{
		first = temp;
		last = temp;
		temp->setObject(year, mileage, price, brand, model);
		return;
	}
	last->next = temp;
	last = temp;
	last->setObject(year, mileage, price, brand, model);
	num++;
}
void List::print()
{
	Node* temp = first;
	int i = 0;
	while (temp != nullptr)
	{
		cout << "\n" << i + 1 << "-й автомобиль:" << endl;
		temp->readObject();
		temp = temp->next;
		i++;
	}
}
void List::removeByIndex(int index)
{
	Node* temp = first;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	if (temp == first)
	{
		first = first->next;
		delete temp;
		num--;
		return;
	}
	if (temp == last)
	{
		Node* temp1 = first;
		while (temp1->next != last)
			temp1 = temp1->next;
		temp1->next = nullptr;
		last = temp1;
		delete temp;
		num--;
		return;
	}
	Node* temp1 = first;
	while (temp1->next != temp)
		temp1 = temp1->next;
	temp1->next = temp->next;
	delete temp;
	num--;
}
Node* List::operator[] (const int index)
{
	if (isEmpty() == 1)
		return nullptr;
	Node* temp = first;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp;
}
void List::searchByParameter(int choice, int year, int mileage, float priceLow, float priceHigh, const string& brand, const string& model)
{
	Node* temp = first;
	int flag = 0;
	switch (choice)
	{
	case 1:
		cout << "ѕоиск по году выпуска:\n" << endl;
		while (temp != nullptr)
		{
			if (temp->getYear() == year)
			{
				cout << flag + 1 << "-й автомобиль:" << endl;
				temp->readObject();
				flag++;
			}
			temp = temp->next;
		}
		if (temp == nullptr && flag == 0)
		{
			cout << "јвтомобилей с таким годом выпуска не найдено" << endl;
		}
		break;
	case 2:
		cout << "ѕоиск по пробегу:\n" << endl;
		while (temp != nullptr)
		{
			if (temp->getMileage() == mileage)
			{
				cout << flag + 1 << "-й автомобиль:" << endl;
				temp->readObject();
				flag++;
			}
			temp = temp->next;
		}
		if (temp == nullptr && flag == 0)
		{
			cout << "јвтомобилей с таким пробегом не найдено" << endl;
		}
		break;
	case 3:
		cout << "ѕоиск по диапозону стоимости:\n" << endl;
		while (temp != nullptr)
		{
			if (priceLow <= temp->getPrice() && temp->getPrice() <= priceHigh)
			{
				cout << flag + 1 << "-й автомобиль:" << endl;
				temp->readObject();
				flag++;
			}
			temp = temp->next;
		}
		if (temp == nullptr && flag == 0)
		{
			cout << "јвтомобилей с таким диапозоном цены не найдено" << endl;
		}
		break;
	case 4:
		cout << "ѕоиск по марке:\n" << endl;
		while (temp != nullptr)
		{
			if (temp->getBrand() == brand)
			{
				cout << flag + 1 << "-й автомобиль:" << endl;
				temp->readObject();
				flag++;
			}
			temp = temp->next;
		}
		if (temp == nullptr && flag == 0)
		{
			cout << "јвтомобилей такой марки не найдено" << endl;
		}
		break;
	case 5:
		cout << "ѕоиск по модели:\n" << endl;
		while (temp != nullptr)
		{
			if (temp->getModel() == model)
			{
				cout << flag + 1 << "-й автомобиль:" << endl;
				temp->readObject();
				flag++;
			}
			temp = temp->next;
		}
		if (temp == nullptr && flag == 0)
		{
			cout << "јвтомобилей такой модели не найдено" << endl;
		}
		break;
	default:
		return;
	}
}