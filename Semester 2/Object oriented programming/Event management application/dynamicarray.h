#pragma once
#include <iostream>
#include <string>
#include "event.h"
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
	T* data;
	int size;
	int capacity;
public:
	DynamicArray(int capacity);
	DynamicArray(const DynamicArray<T>& DynArr);
	DynamicArray<T>& operator= (const DynamicArray<T>& DynArr);
	 T& operator [](int index)const;
	void add_element(T elem);
	void delete_element(int index);
	~DynamicArray();
	int get_size()const;
	int get_capacity()const;
	T* get_data()const;
	void sort();
};
template<typename T>
DynamicArray<T>::DynamicArray(int capacity) {
	this->data = new T[capacity];
	this->size = 0;
	this->capacity = capacity;
}

template <typename T>
 T& DynamicArray<T> :: operator [](int index) const {
	return this->data[index];
}

template<typename T>
DynamicArray<T>& DynamicArray<T> :: operator= (const DynamicArray<T>& DynArr) {
	if (this == &DynArr)
		return *this;
	this->capacity = DynArr.capacity;
	this->size = DynArr.size;
	if(this->data !=NULL)
	delete[]this->data;

	this->data = new T[this->capacity];
	for (int i = 0; i < this->size; ++i)
		this->data[i] = DynArr[i];
	return *this;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& DynArr) {

		this->capacity = DynArr.capacity;
		this->size = DynArr.size;
		this->data = new T[this->capacity];

		for (int i = 0; i < DynArr.size; i++){
			this->data[i] = DynArr.data[i];
		}
	
}

template <typename T>
void DynamicArray<T> ::add_element(T elem) {
	if (this->size == this->capacity) {
		DynamicArray arr{ 2 * this->capacity };
		arr.size = this->get_size();
		for (int i = 0; i < this->size; ++i)
			arr.data[i] = this->data[i];
		if (this->data != NULL)
			delete[]this->data;
		this->data = arr.data;
		this->size = arr.size;
		this->capacity = arr.capacity;
		arr.data = nullptr; 
	}
	this->size++;
	this->data[this->size - 1] = elem;
}

template <typename T>
void DynamicArray<T> ::delete_element(int index) {
	
	if (index == this->size - 1) {
		this->size--;
		return;
	}
	for (int i = index; i < this->size; ++i)
		this->data[i] = this->data[i + 1];
	this->size--;
}

template <typename T>
DynamicArray<T> ::~DynamicArray<T>() {
	if (this->data != NULL) {
		delete[] this->data;
		this->data = NULL;
	}

}

template <typename T>
int  DynamicArray<T>::get_size()const {
	return this->size;
}
template <typename T>
int DynamicArray<T>::get_capacity()const {
	return this->capacity;
}
template <typename T>
T* DynamicArray<T>:: get_data() const{
	return this->data;
}

template<typename T>
void DynamicArray<T>::sort(){
	for(int i = 0;i<this->get_size()-1;++i)
		for(int j = i+1 ;j<this->get_size();++j)
			if (this->data[j] < this->data[i]) {
				T temp = this->data[i];
				this->data[i] = this->data[j];
				this->data[j] = temp;
			}
}



/*

DynamicArray(int): Parameterized constructor.
Initializes a DynamicArray object with the given capacity.
Allocates memory for the array data with the specified capacity.
Sets the size to 0.


T& operator[](int) const: Subscript operator.
Returns a reference to the element at the specified index.

DynamicArray<T>& operator=(const DynamicArray<T>&): Assignment operator.
Assigns the values of one DynamicArray object to another.
Deletes the existing data in the target DynamicArray, and allocates new memory for the copied data.


DynamicArray(const DynamicArray<T>&): Copy constructor.
Initializes a new DynamicArray object by copying the values of another DynamicArray object.


void add_element(T): Add element function.
Adds an element to the DynamicArray.
If the size of the DynamicArray reaches its capacity, it will resize the array by doubling its capacity.


void delete_element(int): Delete element function.
Deletes an element from the DynamicArray at the specified index.
Shifts all the elements to the right of the deleted element one position to the left.


~DynamicArray(): Destructor.
Destroys the DynamicArray object and deallocates its memory.


int get_size() const: Getter function for the size.
Returns the current size of the DynamicArray.


int get_capacity() const: Getter function for the capacity.
Returns the current capacity of the DynamicArray.


T* get_data() const: Getter function for the data.
Returns a pointer to the DynamicArray's data.


void sort(): Sort function.
Sorts the elements in the DynamicArray in ascending order using a simple comparison-based sorting algorithm (Bubble sort).
*/