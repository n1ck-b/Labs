#include "Header.h"

List::~List()
{
	for (int i = 0; i < num; i++)
	{
		removeByIndex(0);
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
		temp->car.setObject(year, mileage, price, brand, model);
		return;
	}
	last->next = temp;
	last = temp;
	last->car.setObject(year, mileage, price, brand, model);
	num++;
}
void List::print()
{
	Node* temp = first;
	int i = 0;
	while (temp != nullptr)
	{
		cout << "\n" << i + 1 << "-й автомобиль:" << endl;
		temp->car.readObject();
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
	while(temp != nullptr)
	{
		if (match(temp, choice, year, mileage, priceLow, priceHigh, brand, model))
		{
			cout << flag + 1 << "-й автомобиль:" << endl;
			temp->car.readObject();
			flag++;
		}
		temp = temp->next;
	}
	if (flag == 0)
	{
		cout << "Автомобилей по данному критерию не найдено" << endl;
	}
}