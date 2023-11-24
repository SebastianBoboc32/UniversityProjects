#pragma once
#include <iostream>
#include <string>

class Event {
private:
	int number_of_people;
	std::string link;
	std::string date_and_time;
	std::string title;
	std::string description;

public:
	friend std::ostream& operator<<(std::ostream& os, const Event&);
	friend std::istream& operator >>(std::istream& is, Event&);
	Event(const int&, const std::string&, const std::string&, const std::string&, const std::string&);

	Event();


	Event(const Event& event);


	int get_number_of_people()const;
	
	std::string get_link()const;

	std::string get_description()const;

	std::string get_title()const;

	void set_number_of_people(const int new_nr);

	void set_link(const std::string str);

	void set_description(const std::string desc);

	void set_date_and_time(const std::string date_time);

	void set_title(const std::string title);

	std::string get_date_and_time()const;

	std::string str()const;

	~Event();

	Event& operator = (const Event& event);

	bool operator == (const Event& event) const;
	bool operator <(const Event& event) const;
};

/*

Event(): Default constructor.
Initializes an empty Event object with default values for number_of_people (0), link (""),
date_and_time (""), title (""), and description ("").


Event(const int&, const std::string&, const std::string&, const std::string&, const std::string&):
Parameterized constructor.
Initializes an Event object with the provided values for number_of_people, link, date_and_time, title, and description.


Event(const Event&): Copy constructor.
Initializes a new Event object by copying the values of another Event object.


int get_number_of_people() const: Getter function for the number of people.
Returns the number of people attending the event.


std::string get_link() const: Getter function for the link.
Returns the URL/link of the event.


std::string get_description() const: Getter function for the description.
Returns the description of the event.


std::string get_title() const: Getter function for the title.
Returns the title of the event.


std::string get_date_and_time() const: Getter function for the date and time.
Returns the date and time of the event.


void set_number_of_people(const int): Setter function for the number of people.
Sets the number of people attending the event to the specified value.


void set_link(const std::string): Setter function for the link.
Sets the URL/link of the event to the specified value.


void set_description(const std::string): Setter function for the description.
Sets the description of the event to the specified value.


void set_date_and_time(const std::string): Setter function for the date and time.
Sets the date and time of the event to the specified value.


void set_title(const std::string): Setter function for the title.
Sets the title of the event to the specified value.


std::string str() const: String representation function.
Returns a formatted string representation of the Event object, including its title,
number of people, description, date and time, and link.


~Event(): Destructor.
Destroys the Event object.


Event& operator=(const Event&): Assignment operator.
Assigns the values of one Event object to another.


bool operator==(const Event&) const: Equality operator.
ompares two Event objects for equality based on their title and link.


bool operator<(const Event&) const: Less-than operator.
Compares two Event objects based on their date and time.
Returns true if the first Event object's date and time is earlier than the second Event object's date and time.
*/