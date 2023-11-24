#pragma once
#include <iostream>
#include "repo.h"
#include <vector>

class User {
private:
	Repo<Event>data;
	Repo<Event>my_list;

public:
	User();
	User(const Repo<Event>& repo);
	std::vector<Event> show_based_on_month(const std::string month);
	void add_to_my_list(const Event& event);
	Repo<Event> display_my_list();
	void remove_from_my_list(int index);
	~User();
	int data_size() ;
	Repo<Event> Data();
	void add_element(const Event& event);
	void delete_element(int index);
	void update_event(int index, const Event& event);
	Repo<Event> My_List();
};

/*
User(): Default constructor.
Initializes a User object with a default Repo<Event> object of capacity 100 for both data and my_list.


User(const Repo<Event>&): Parameterized constructor.
Initializes a User object with the given Repo<Event> object for data and a default Repo<Event> object 
of capacity 100 for my_list.


DynamicArray<Event> show_based_on_month(const std::string): Show events based on month function.
Returns a DynamicArray of events that match the given month. If the month parameter is an empty string, it returns all events.


void add_to_my_list(const Event&): Add to my list function.
Adds the given event to the User's my_list and increments the number of people for the event in the data Repo.


Repo<Event> display_my_list(): Display my list function.
Returns the User's my_list Repo object containing the events.


void remove_from_my_list(int): Remove from my list function.
Removes the event at the specified index from the User's my_list and
decrements the number of people for the event in the data Repo.


~User(): Destructor.
Destroys the User object and calls the destructor of the data and my_list Repo objects.


int data_size(): Data size function.
Returns the size of the data Repo.


Repo<Event> Data(): Data function.
Returns the User's data Repo object containing the events.


void add_element(const Event&): Add element function.
Adds the given event to the User's data Repo.


void delete_element(int): Delete element function.
Deletes the event at the specified index from the User's data Repo.


void update_event(int, const Event&): Update event function.
Updates the event at the specified index with the provided updated_event in the User's data Repo.
*/