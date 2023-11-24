#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <stdexcept>
using namespace std;

SortedMap::SortedMap(Relation r) {
    capacity = 10; // Initial capacity
    count = 0;
    hashtable = new Node * [capacity]();
    relation = r;
}

// Adds a pair (key, value) to the map
TValue SortedMap::add(TKey key, TValue value) {
    int hash = hashCode(key);
    Node* newNode = new Node(TElem(key, value));

    if (hashtable[hash] == nullptr) {
        hashtable[hash] = newNode;
    }
    else {
        Node* current = hashtable[hash];
        Node* prev = nullptr;

        while (current != nullptr && !relation(current->pair.first, key)) {
            prev = current;
            current = current->next;
        }

        if (current != nullptr && relation(current->pair.first, key)) {
            TValue oldValue = current->pair.second;
            current->pair.second = value;
            delete newNode;
            return oldValue;
        }

        if (prev == nullptr) {
            newNode->next = hashtable[hash];
            hashtable[hash] = newNode;
        }
        else {
            newNode->next = prev->next;
            prev->next = newNode;
        }
    }

    count++;
    if (count >= 0.75 * capacity) {
        resize();
    }

    return NULL_TVALUE;
}

// Searches for the key and returns the associated value if found, otherwise returns NULL_TVALUE
TValue SortedMap::search(TKey key) const {
    int hash = hashCode(key);
    Node* current = hashtable[hash];

    while (current != nullptr && !relation(current->pair.first, key)) {
        current = current->next;
    }

    if (current != nullptr && relation(current->pair.first, key)) {
        return current->pair.second;
    }

    return NULL_TVALUE;
}
TValue SortedMap::remove(TKey key) {
    int hash = hashCode(key);
    Node* current = hashtable[hash];
    Node* prev = nullptr;

    while (current != nullptr && !relation(current->pair.first, key)) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr && relation(current->pair.first, key)) {
        TValue value = current->pair.second;

        if (prev == nullptr) {
            hashtable[hash] = current->next;
        }
        else {
            prev->next = current->next;
        }

        delete current;
        count--;
        return value;
    }

    return NULL_TVALUE;
}

// Returns the number of pairs (key, value) in the map
int SortedMap::size() const {
    return count;
}

// Checks whether the map is empty or not
bool SortedMap::isEmpty() const {
    return count == 0;
}

// Returns the iterator for the map
SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

// Destructor
SortedMap::~SortedMap() {
    for (int i = 0; i < capacity; i++) {
        Node* current = hashtable[i];

        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    delete[] hashtable;
}
void SortedMap::resize() {
    int newCapacity = capacity * 2;
    Node** newHashtable = new Node * [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newHashtable[i] = nullptr;
    }

    for (int i = 0; i < capacity; i++) {
        Node* current = hashtable[i];
        while (current != nullptr) {
            int hash = hashCode(current->pair.first) % newCapacity;

            Node* newNode = new Node(current->pair);

            if (newHashtable[hash] == nullptr) {
                newHashtable[hash] = newNode;
            }
            else {
                Node* temp = newHashtable[hash];
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            current = current->next;
        }
    }

    delete[] hashtable;
    hashtable = newHashtable;
    capacity = newCapacity;
}
