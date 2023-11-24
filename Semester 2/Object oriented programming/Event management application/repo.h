#pragma once
#include <iostream>
#include "dynamicarray.h"
#include "event.h"
#include <stdexcept>
#include <vector>
#include "custom_errors.h"

template <typename T>
class Repo {
private:
	int size;
	int capacity;
	std::vector<T> arr;

public:
	Repo<T>& operator=(const Repo& repo);
	const T& operator[](int index)const;
	T& operator [](int index);
	void delete_element(int index);
	void add_element(T elem);
	Repo(int capacity);
	~Repo();
	Repo(const Repo<T>& repo);
	int get_size()const;
	int get_capacity();
	void update_event(int index, const Event& updated_event);
	void change_data(std::vector<T> new_values);
	std::vector<T> return_data();
};

template<typename T>
Repo<T>::Repo(const Repo<T>& repo) : capacity(repo.capacity), size(repo.size), arr(repo.arr) {

}

template<typename T>
 const T& Repo<T>:: operator[](int index)const {
	if (index < 0 || index >= this->arr.size())
		throw RepoError("Invalid index");
	return this->arr[index];

}
template<typename T>
void Repo<T>::delete_element(int index) {
	if (index < 0 || index >= this->arr.size())
		throw RepoError("Invalid index");
	this->arr.erase(this->arr.begin() + index);

}
template<typename T>
void Repo<T>::add_element(T elem) {
	auto it = std::find_if(arr.begin(), arr.end(), [&](T X) {return X == elem; });
	if(it != arr.end())
		throw RepoError("Element already exists");
	this->arr.push_back(elem);
	this->size++;
}
template<typename T>
Repo<T>::Repo(int capacity) : capacity(capacity), size(0) {
	arr.reserve(capacity);
}
template<typename T>
Repo<T>::~Repo() = default;

template<typename T>
Repo<T>& Repo<T>::operator=(const Repo<T>& repo) {
	if (this == &repo)
		return *this;

	this->capacity = repo.capacity;
	this->size = repo.size;
	this->arr = repo.arr;
	return *this;
}
template<typename T>
int Repo<T>::get_size()const {
	return this->arr.size();
}

template<typename T>
int Repo<T>::get_capacity() {
	return this->arr.capacity();
}

template<typename T>
void Repo<T>::update_event(int index, const Event& updated_event) {
	if (index < 0 || index >= this->arr.size())
		throw RepoError("invalid index");
	this->arr[index] = updated_event;
	
}

template<typename T>
void  Repo<T>::change_data(std::vector<T> new_values) {
	this->arr = new_values;
}

template<typename T>
 std::vector<T> Repo<T>::return_data() {
	 return this->arr;
}

template<typename T>
T& Repo<T>::operator[](int index) {
	if (index < 0 || index >= this->arr.size())
		throw RepoError("Invalid index");
	return this->arr[index];
}

/*
Repo(const Repo<T>&): Copy constructor.
Initializes a new Repo object by copying the values of another Repo object.


T& operator[](int) const: Subscript operator.
Returns a reference to the element at the specified index.
Throws a length_error exception if the index is out of bounds.


void delete_element(int): Delete element function.
Deletes an element from the Repo at the specified index.
Throws a length_error exception if the index is out of bounds.


void add_element(T): Add element function.
Adds an element to the Repo.
Throws an invalid_argument exception if the element already exists in the Repo.


Repo(int): Parameterized constructor.
Initializes a Repo object with the given capacity using a DynamicArray.


~Repo(): Destructor.
Destroys the Repo object.


Repo<T>& operator=(const Repo<T>&): Assignment operator.
Assigns the values of one Repo object to another.


int get_size(): Getter function for the size.
Returns the current size of the Repo.


int get_capacity(): Getter function for the capacity.
Returns the current capacity of the Repo.


void update_event(int, const Event&): Update event function.
Updates the event at the specified index with the provided updated_event.
Throws a length_error exception if the index is out of bounds.

*/