#pragma once
#include <iostream>
#include "repo.h"
#include "event.h"

class Administrator {
private:
	Repo<Event> data;

public:
	Administrator();
	Administrator(const Repo<Event>& repo);
	void delete_element(int index);
	void add_element(Event elem);
	void update_event(int index, const Event& updated_event);
	~Administrator();
	std::string list_all();
	Repo<Event>Data();

};

/*
Administrator(): Default constructor.
Initializes an Administrator object with a default Repo<Event> object of capacity 100.


void delete_element(int): Delete element function.
Deletes an element (Event) from the Administrator's Repo at the specified index.


void add_element(Event): Add element function.
Adds an element (Event) to the Administrator's Repo.


void update_event(int, const Event&): Update event function.
Updates the event at the specified index with the provided updated_event in the Administrator's Repo.


~Administrator(): Destructor.
Destroys the Administrator object and calls the destructor of the Repo object.


std::string list_all(): List all function.
Returns a string containing the details of all the events in the Administrator's Repo, separated by newlines.


Administrator(const Repo<Event>&): Parameterized constructor.
Initializes an Administrator object with the given Repo<Event> object.


Repo<Event> Data(): Data function.
Returns the Administrator's Repo object containing the events.
*/