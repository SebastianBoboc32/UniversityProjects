#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <stdexcept>

using namespace std;


SMIterator::SMIterator(const SortedMap& map) : map(map) {
    first();
}

void SMIterator::first() {
    for (int i = 0; i < map.capacity; i++) {
        if (map.hashtable[i] != nullptr) {
            currentNode = map.hashtable[i];
            currentHash = i;
            return;
        }
    }

    currentNode = nullptr;
    currentHash = -1;
}

void SMIterator::next() {
    if (!valid()) {
        throw std::runtime_error("Invalid iterator!");
    }

    if (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    else {
        currentHash++;
        while (currentHash < map.capacity && map.hashtable[currentHash] == nullptr) {
            currentHash++;
        }

        if (currentHash < map.capacity) {
            currentNode = map.hashtable[currentHash];
        }
        else {
            currentNode = nullptr;
            currentHash = -1;
        }
    }
}

bool SMIterator::valid() const {
    return currentNode != nullptr && currentHash >= 0 && currentHash < map.capacity;
}

TElem SMIterator::getCurrent() const {
    if (!valid()) {
        throw std::runtime_error("Invalid iterator!");
    }

    return currentNode->pair;
}
