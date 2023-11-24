#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <vector>
using namespace std;

// Best,Average and total:Theta(1)
SortedMap::SortedMap(Relation r)  {
    this->relation = r;
    this->capacity = 10;
    this->DLLANodes = new Node[this->capacity];
    this->length = 0;
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->DLLANodes[firstEmpty].prev = -1;
    this->DLLANodes[firstEmpty].next = 1;
    this->DLLANodes[firstEmpty].info = NULL_TPAIR;
    ///We set the previous and the next for the first empty position
    ///After that we set the links between the other nodes from the array, starting from the second node until the last but one
    for (int i = 1; i < this->capacity - 1; i++)
    {
        ///We establish the position path for the rest of the nodes
        this->DLLANodes[i].next = i + 1;
        this->DLLANodes[i].prev = i - 1;
        this->DLLANodes[i].info = NULL_TPAIR;
    }
    this->DLLANodes[this->capacity - 1].next = -1;
    this->DLLANodes[this->capacity - 1].prev = this->capacity - 2;
    this->DLLANodes[this->capacity - 1].info = NULL_TPAIR;
}
/// Theta(this->capacity)


// Best: Theta(1) when the map is empty, Average: Theta(n), Total: Theta(n)
TValue SortedMap::add(TKey c, TValue v) {
    TValue old_v = NULL_TVALUE;

    // Check if the key already exists in the map
    int current = head;
    while (current != -1) {
        if (DLLANodes[current].info.first == c) {
            old_v = DLLANodes[current].info.second;
            DLLANodes[current].info.second = v;
            return old_v;
        }
        current = DLLANodes[current].next;
    }

    // Key doesn't exist, add a new element to the map
    if (length == capacity)
        resize();
    //Case 1:The map is empty
    if (length == 0 && head == -1) {
        length++;
        head = firstEmpty;
        firstEmpty = DLLANodes[firstEmpty].next;
        if (firstEmpty != -1)
            DLLANodes[firstEmpty].prev = -1;
        DLLANodes[head].info.first = c;
        DLLANodes[head].info.second = v;
        DLLANodes[head].next = -1;
        tail = head;
    }
    //Case 2:The element has to be added before the current head
    else if (relation(c, DLLANodes[head].info.first) && c != DLLANodes[head].info.first) {
        length++;
        int new_head = firstEmpty;
        firstEmpty = DLLANodes[firstEmpty].next;
        if (firstEmpty != -1)
            DLLANodes[firstEmpty].prev = -1;
        DLLANodes[new_head].next = head;
        DLLANodes[new_head].prev = -1;
        DLLANodes[new_head].info.first = c;
        DLLANodes[new_head].info.second = v;
        DLLANodes[head].prev = new_head;
        head = new_head;
    }
    //If the map is not empty,nor the element has to be added in the first position,we'll search for the proper position
    else {
        int current_element = head;
        while (DLLANodes[current_element].next != -1 && !relation(c, DLLANodes[DLLANodes[current_element].next].info.first)) {
            current_element = DLLANodes[current_element].next;
        }
        //Case 3:The position should be after the tail
        if (DLLANodes[current_element].next == -1 && c != DLLANodes[current_element].info.first) {
            length++;
            int new_element = firstEmpty;
            firstEmpty = DLLANodes[firstEmpty].next;
            if (firstEmpty != -1)
                DLLANodes[firstEmpty].prev = -1;
            DLLANodes[tail].next = new_element;
            int old_tail = tail;
            tail = new_element;
            DLLANodes[tail].next = -1;
            DLLANodes[tail].prev = old_tail;
            DLLANodes[tail].info.first = c;
            DLLANodes[tail].info.second = v;
        }
        //Case 4:The position is between the head and the tail
        else if (DLLANodes[current_element].next != -1 && relation(c, DLLANodes[DLLANodes[current_element].next].info.first) && c != DLLANodes[DLLANodes[current_element].next].info.first) {
            length++;
            int new_element = firstEmpty;
            firstEmpty = DLLANodes[firstEmpty].next;
            if (firstEmpty != -1)
                DLLANodes[firstEmpty].prev = -1;
            int next_element = DLLANodes[current_element].next;
            int previous_element = current_element;
            DLLANodes[current_element].next = new_element;
            DLLANodes[next_element].prev = new_element;
            DLLANodes[new_element].prev = current_element;
            DLLANodes[new_element].next = next_element;
            DLLANodes[new_element].info.first = c;
            DLLANodes[new_element].info.second = v;
        }
    }

    return old_v;
}

// Best: Theta(1) when the first element is the searched one, Average: Theta(n), Total: Theta(n)
TValue SortedMap::search(TKey k) const {
    vector<TValue> values;
    int CurrentElement = this->head;
    while (CurrentElement != -1) {
        if (this->relation(this->DLLANodes[CurrentElement].info.first, k))
        {
            if (this->DLLANodes[CurrentElement].info.first == k)
            {
                return DLLANodes[CurrentElement].info.second;
            }
            CurrentElement = this->DLLANodes[CurrentElement].next;
        }
        else
            break;
    }
    return NULL_TVALUE;
}

// Best: Theta(1) when the first element is the searched one, Average: Theta(n), Total: Theta(n)
TValue SortedMap::remove(TKey k) {
    int CurrentElement = this->head;
    TValue deleted_v = NULL_TVALUE;
    while (CurrentElement != -1)
    {
        /// We found the element
        if (this->DLLANodes[CurrentElement].info.first == k)
        {
            deleted_v = this->DLLANodes[CurrentElement].info.second;
            this->DLLANodes[CurrentElement].info = NULL_TPAIR;
            this->length--;

            ///Now we have to remove the element from the list
            ///Case 1: It means the list have only one element
            if (CurrentElement == this->head && CurrentElement == this->tail)
            {
                this->head = -1;
                this->tail = -1;
            }
            ///Case 2: It means the element we have to remove is the head
            else if (CurrentElement == this->head)
            {
                this->head = this->DLLANodes[this->head].next;
                this->DLLANodes[this->head].prev = -1;
            }
            ///Case 3: It means the element we have to remove is the tail
            else if (CurrentElement == this->tail)
            {
                this->tail = this->DLLANodes[this->tail].prev;
                this->DLLANodes[this->tail].next = -1;
            }
            ///Case 4: It means the element we have to remove is somewhere between the head and the tail
            else
            {

                int PreviousElement = this->DLLANodes[CurrentElement].prev;
                int NextElement = this->DLLANodes[CurrentElement].next;
                this->DLLANodes[PreviousElement].next = NextElement;
                this->DLLANodes[NextElement].prev = PreviousElement;

            }
            ///We free the position of the deleted node
            free(CurrentElement);
        }
        else
            CurrentElement = this->DLLANodes[CurrentElement].next;

    }
    return deleted_v;
}

// Best,Average and total:Theta(1)
int SortedMap::size() const {
    return length;
}

// Best,Average and total:Theta(1)
bool SortedMap::isEmpty() const {
    if (this->length == 0)
        return true;
    return false;
}

// Best,Average and total:Theta(1)
SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

// Best,Average and total:Theta(n)
SortedMap::~SortedMap() {
    delete[] this->DLLANodes;
}

//Best,Average and total:Theta(n) n being the size of the array
void SortedMap::resize() {

    this->capacity = 2 * this->capacity;
    Node* NewArray = new Node[this->capacity];
    for (int i = 0; i < this->length; i++)
        NewArray[i] = this->DLLANodes[i];

    this->firstEmpty = this->length;
    NewArray[firstEmpty].prev = -1;
    NewArray[firstEmpty].next = this->length + 1;
    NewArray[firstEmpty].info = NULL_TPAIR;

    for (int i = this->length + 1; i < this->capacity - 1; i++)
    {
        NewArray[i].prev = i - 1;
        NewArray[i].next = i + 1;
        NewArray[i].info = NULL_TPAIR;
    }
    NewArray[this->capacity - 1].prev = this->capacity - 2;
    NewArray[this->capacity - 1].next = -1;
    NewArray[this->capacity - 1].info = NULL_TPAIR;

    delete[] this->DLLANodes;
    this->DLLANodes = NewArray;
}

// Best average and total:Theta(1)
int SortedMap::allocate() {
    int newElem = this->firstEmpty;
    if (newElem != -1) {
        this->firstEmpty = this->DLLANodes[this->firstEmpty].next;
        if (this->firstEmpty != -1)
            this->DLLANodes[this->firstEmpty].prev = -1;
        this->DLLANodes[newElem].next = -1;
        this->DLLANodes[newElem].prev = -1;
    }
    return newElem;
}

// Best average and total:Theta(1)
void SortedMap::free(int position) {
    this->DLLANodes[position].next = this->firstEmpty;
    this->DLLANodes[position].prev = -1;
    this->DLLANodes[this->firstEmpty].prev = position;
    this->firstEmpty = position;
}

    

