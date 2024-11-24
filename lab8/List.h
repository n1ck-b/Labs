#pragma once
#include "Functions.h"
#include "Node.h"
//#include "Iterator.h"
#include <type_traits>

//template <typename T>
//class Iterator;

template <typename T>
class List
{
private:
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	int sizeOfList = 0;
public:
	class Iterator;
	Iterator begin()
	{
		return Iterator(first);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
	~List()
	{
		/*Node<T>* temp = first;
		while (temp != last && !isEmpty())
		{
			popBack();
			temp = temp->next;
		}*/
		List<T>::Iterator it = List<T>::begin();
		while (it != List::end())
		{
			popBack();
			++it;
		}
	}
	int size() const
	{
		return sizeOfList;
	}
	bool isEmpty() const
	{
		return first == nullptr;
	}
	void pushBack(T Car)
	{
		Node<T>* temp = new Node<T>;
		if (isEmpty())
		{
			first = temp;
			last = temp;
		}
		else
		{
			last->next = temp;
			temp->prev = last;
			last = temp;
		}
		temp->car.setYear(Car.getYear());
		temp->car.setMileage(Car.getMileage());
		temp->car.setPrice(Car.getPrice());
		temp->car.setBrand(Car.getBrand());
		temp->car.setModel(Car.getModel());
		if constexpr (std::is_same<T, CombustionEngineCar>::value || std::is_same<T, HybridEngineCar>::value)
			temp->car.setFuelTankCapacity(Car.getFuelTankCapacity());
		if constexpr (std::is_same<T, ElectricEngineCar>::value || std::is_same<T, HybridEngineCar>::value)
			temp->car.setBatteryCapacity(Car.getBatteryCapacity());
		if constexpr (std::is_same<T, HybridEngineCar>::value)
			temp->car.setHybridType(Car.getHybridType());
		sizeOfList++;
	}
	void popBack()
	{
		Node<T>* temp = last;
		last = last->prev;
		last->next = nullptr;
		delete temp;
		sizeOfList--;
	}
	void insert(Iterator it, T Car)
	{
		if (size() > 1 && it != first)
		{
			Node<T>* newNode = new Node<T>;
			Node<T>* prevNode = it.current->prev;
			it.current->prev = newNode;
			newNode->next = it.current;
			prevNode->next = newNode;
			newNode->prev = prevNode;
			newNode->car.setYear(Car.getYear());
			newNode->car.setMileage(Car.getMileage());
			newNode->car.setPrice(Car.getPrice());
			newNode->car.setBrand(Car.getBrand());
			newNode->car.setModel(Car.getModel());
			if constexpr (std::is_same<T, CombustionEngineCar>::value || std::is_same<T, HybridEngineCar>::value)
				newNode->car.setFuelTankCapacity(Car.getFuelTankCapacity());
			if constexpr (std::is_same<T, ElectricEngineCar>::value || std::is_same<T, HybridEngineCar>::value)
				newNode->car.setBatteryCapacity(Car.getBatteryCapacity());
			if constexpr (std::is_same<T, HybridEngineCar>::value)
				newNode->car.setHybridType(Car.getHybridType());
			sizeOfList++;
		}
		else
			pushBack(Car);
	}

};