#include <iostream>
#include "dynamicarray.h"
#include "event.h"
#include <cassert>
#include "repo.h"
#include <stdexcept>
#include "admin.h"
#include "user.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>

using namespace std;


void test_event() {
	Event event(10, "https://example.com", "2022-04-03 14:30", "Example Event", "This is an example event.");
	Event event1(5, "https://event1.com", "01-01-2023 18:00", "Event 1", "Description 1");
	Event event2(7, "https://event2.com", "01-02-2023 18:00", "Event 2", "Description 2");
	Event event3(9, "https://event3.com", "02-01-2023 18:00", "Event 3", "Description 3");
	Event event4(3, "https://event4.com", "01-01-2024 18:00", "Event 4", "Description 4");
	Event event5(8, "https://event5.com", "01-01-2023 19:00", "Event 5", "Description 5");
	Event event6(2, "https://event6.com", "01-01-2023 18:30", "Event 6", "Description 6");
	Event event7;

	assert(event1 < event2);
	assert(event1 < event3);
	assert(event1 < event4);
	assert(event1 < event5);
	assert(event1 < event6);

	assert(!(event2 < event1));
	assert(!(event2 < event3));
	assert(event2 < event4);
	assert(!(event2 < event5));
	assert(!(event2 < event6));

	assert(!(event3 < event1));
	assert(event3 < event2);
	assert(event3 < event4);
	assert(!(event3 < event5));
	assert(!(event3 < event6));

	assert(!(event4 < event1));
	assert(!(event4 < event2));
	assert(!(event4 < event3));
	assert(!(event4 < event5));
	assert(!(event4 < event6));
	
	assert(event.get_number_of_people() == 10);
	assert(event.get_link() == "https://example.com");
	assert(event.get_description() == "This is an example event.");
	assert(event.get_title() == "Example Event");

	
	event.set_number_of_people(20);
	assert(event.get_number_of_people() == 20);

	event.set_link("https://newexample.com");
	assert(event.get_link() == "https://newexample.com");

	event.set_description("This is a new example event.");
	assert(event.get_description() == "This is a new example event.");

	event.set_date_and_time("2022-04-04 14:30");
	assert(event.get_date_and_time() == "2022-04-04 14:30");

	event.set_title("New Example Event");
	assert(event.get_title() == "New Example Event");

	
	Event event_copy(event);
	assert(event_copy == event);


	Event event_copy2 = event;
	assert(event_copy2 == event);
	Event e8;
	std::cin >> e8;
	assert(e8.get_link() == "url");

}

void testRepo() {

	Repo<Event> repo(5);
	assert(repo.get_size() == 0);
	assert(repo.get_capacity() == 5);
	Event e1(10, "www.google.com", "2022-04-01 10:00", "Event 1", "Description 1");
	repo.add_element(e1);
	assert(repo.get_size() == 1);
	std::cout << repo[0].get_title();
	assert(repo[0].get_title() == "Event 1");

	Repo<Event> repo2(repo);
	assert(repo2.get_size() == 1);
	assert(repo2[0].get_title() == "Event 1");
	Event e2(20, "www.facebook.com", "2022-05-01 10:00", "Event 2", "Description 2");
	repo2.add_element(e2);
	assert(repo2.get_size() == 2);
	assert(repo2[1].get_title() == "Event 2");
	repo = repo2;
	assert(repo.get_size() == 2);
	assert(repo[0].get_title() == "Event 1");
	assert(repo[1].get_title() == "Event 2");

	repo.delete_element(1);
	assert(repo.get_size() == 1);
	assert(repo[0].get_title() == "Event 1");

	Event e3(30, "www.youtube.com", "2022-06-01 10:00", "Event 3", "Description 3");
	repo.add_element(e3);
	repo[1].set_link("wwww.manele.com");
	assert(repo[1].get_title() == "Event 3");
	assert(repo[1].get_link() == "wwww.manele.com");
	try {
		string st = repo[8].get_title();
		assert(false);
	}
	catch (const std::length_error& e) {
		cout << e.what()<<'\n';
		assert(true);
	}
	try {
		repo.delete_element(45);
		assert(false);
	}
	catch (const std::length_error& e) {
		cout << e.what() << '\n';
		assert(true);
	}
	try {
		repo.update_event(77, Event(30, "www.youtube.com", "2022-06-01 10:00", "Event 3", "Description 3"));
		assert(false);
	}
	catch (const std::length_error& e) {
		cout << e.what() << '\n';
		assert(true);
	}
	try {
		Event e4(50, "www.youtube.com", "2022-08-22 07:55", "Event 1", "Description 4");
		repo.add_element(e4);
		assert(false);
	}
	catch (const std::invalid_argument& e) {
		cout  << e.what()<<'\n';
		assert(true);
	}
	
	repo.update_event(0, Event(30, "www.ccccccc.com", "2022-06-01 10:00", "Event 3", "Description 3"));
	assert(repo[0].get_link() == "www.ccccccc.com");
}

void test_admin() {
	try {
		
		Administrator admin;

		
		Event event1(100, "https://event1.com", "01-05-2023 19:00", "Event 1", "Description for Event 1");
		Event event2(200, "https://event2.com", "02-05-2023 20:00", "Event 2", "Description for Event 2");
		Event event3(300, "https://event3.com", "03-05-2023 21:00", "Event 3", "Description for Event 3");

		
		admin.add_element(event1);
		admin.add_element(event2);
		admin.add_element(event3);

		
		assert(admin.list_all().find("Event 1") != std::string::npos);
		assert(admin.list_all().find("Event 2") != std::string::npos);
		assert(admin.list_all().find("Event 3") != std::string::npos);

		
		Event updated_event(150, "https://event1-updated.com", "01-05-2023 19:30", "Event 1 Updated", "Description for Event 1 Updated");
		admin.update_event(0, updated_event);

		
		assert(admin.list_all().find("Event 1 Updated") != std::string::npos);
		assert(admin.list_all().find("https://event1-updated.com") != std::string::npos);

		
		admin.delete_element(1);

		
		assert(admin.list_all().find("Event 2") == std::string::npos);
		Repo<Event>repo(100);
		Administrator admin_1(repo);
		Repo<Event>repo_1 = admin.Data();

	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}

void test_show_based_on_month() {
	Repo<Event> repo(100);
	repo.add_element(Event(5, "https://event1.com", "01-03-2023 18:00", "Event 1", "Description 1"));
	repo.add_element(Event(7, "https://event2.com", "02-03-2023 19:00", "Event 2", "Description 2"));
	repo.add_element(Event(9, "https://event3.com", "15-04-2023 20:00", "Event 3", "Description 3"));

	User user(repo);
	repo.add_element(Event(1, "ww.net", "01-01-2020 00:00", "EV1", "ds1"));

	std::cout << "User data size: " << user.data_size() << std::endl; // Debug print statement

	std::vector<Event> events = user.show_based_on_month("03");
	std::vector<Event> events_1 = user.show_based_on_month("");
	assert(events_1.size() == 3);
	std::cout << events.size();
	//assert(events.size() == 2);
	assert(events[0].get_title() == "Event 1");
	assert(events[1].get_title() == "Event 2");
	std::cout << "PASSED";

	try {
		user.show_based_on_month("13");
		assert(false);
	}
	catch (const std::invalid_argument& e) {
		assert(std::string(e.what()) == "The input is not a valid month");
	}
}

void test_add_to_my_list() {
	Repo<Event> repo(100);
	repo.add_element(Event(5, "https://event1.com", "01-03-2023 18:00", "Event 1", "Description 1"));
	repo.add_element(Event(7, "https://event2.com", "02-03-2023 19:00", "Event 2", "Description 2"));
	repo.add_element(Event(9, "https://event3.com", "15-04-2023 20:00", "Event 3", "Description 3"));
	User user(repo);
	assert(user.My_List().get_size() == 0);
	user.add_to_my_list(repo[0]);
	Repo<Event> my_list = user.display_my_list();
	assert(my_list.get_size() == 1);
	assert(my_list[0].get_title() == "Event 1");
	user.add_element(Event(6, "5555", "00-00-0000 00:00", "EV!", "DS!"));
	user.update_event(3, Event(7,"5555", "00-00-0000 00:00", "EV!", "DS!"));
	user.delete_element(0);

}

void test_remove_from_my_list() {
	User nulluser;
	nulluser.add_to_my_list(Event(0, "https://event1.com", "01-03-2023 18:00", "Event 1", "Description 1"));
	Repo<Event> repo(100);
	repo.add_element(Event(5, "https://event1.com", "01-03-2023 18:00", "Event 1", "Description 1"));
	repo.add_element(Event(7, "https://event2.com", "02-03-2023 19:00", "Event 2", "Description 2"));
	repo.add_element(Event(9, "https://event3.com", "15-04-2023 20:00", "Event 3", "Description 3"));

	User user(repo);
	user.add_to_my_list(repo[0]);
	user.add_to_my_list(repo[1]);
	user.add_to_my_list(repo[2]);
	user.remove_from_my_list(0);
	Repo<Event> my_list = user.display_my_list();
	assert(my_list.get_size() == 2);
	assert(my_list[0].get_title() == "Event 2");
	Repo<Event>repo_1 = user.Data();
}

void test_user() {
	test_show_based_on_month();
	test_add_to_my_list();
	test_remove_from_my_list();
}


/*
int main() {
	test_event();
	testRepo();
	test_admin();
	test_user();
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
*/


