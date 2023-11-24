#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	rel = r;
	binary_search_tree = new BST;
	binary_search_tree->root = new Node;
	first_free = 0;
}


void SortedBag::add(TComp e) {
	if (binary_search_tree->root == nullptr) {
		binary_search_tree->root = new Node;
		binary_search_tree->root->data = e;
		binary_search_tree->root->left = nullptr;
		binary_search_tree->root->right = nullptr;
	}
	else {
		Node* temp = binary_search_tree->root;
		//Node* prev = new Node;
		if (temp != nullptr) {
			while (temp->left != nullptr || temp->right != nullptr) {
				if ( temp != nullptr && !rel(temp->data, e) && temp->left != nullptr) {
					//prev = temp;
					temp = temp->left;
				}
				else if (temp != nullptr && temp->right != nullptr) {
					//prev = temp;
					temp = temp->right;
				}
				else if (temp != nullptr && temp->left == nullptr && !rel(temp->data, e)) {
					break;
				}
				else if (temp != nullptr && temp->right == nullptr && rel(temp->data, e)) {
					break;
				}
			}
			if (temp != nullptr && rel(temp->data, e)) {
				Node* to_be_added = new Node;
				to_be_added->data = e;
				to_be_added->left = nullptr;
				to_be_added->right = nullptr;
				temp->right = to_be_added;
			}
			else if(temp != nullptr){
				Node* to_be_added = new Node;
				to_be_added->data = e;
				to_be_added->left = nullptr;
				to_be_added->right = nullptr;
				temp->left = to_be_added;
			}
		}
	}
	first_free++;
}


bool SortedBag::remove(TComp e) {
	
	if(!search(e))
		return false;

	if (binary_search_tree->root->left == nullptr && binary_search_tree->root->right == nullptr) {
		delete binary_search_tree->root;
		return true;
	}
	else {
		Node* temp = binary_search_tree->root;
		Node* prev = binary_search_tree->root;
		Node* to_be_changed = new Node;
		while ( temp != nullptr && temp->data != e)
			if (!rel(temp->data, e)) {
				prev = temp;
				temp = temp->left;
			}
			else {
				prev = temp;
				temp = temp->right;
			}
		if ( temp != nullptr && temp->left == nullptr && temp->right == nullptr)
			delete temp;
		else if (temp != nullptr && temp->left == nullptr) {
			to_be_changed = temp;
			while (temp->left != nullptr && temp->right != nullptr) {
				prev = temp;
				temp = temp->left;
			}
			to_be_changed->data = temp->data;
			if (temp->right != nullptr) {
				prev->right = temp->right;
			}
			delete temp;
		}
		else if (temp != nullptr) {
			to_be_changed = temp;
			while (temp->left != nullptr && temp->right != nullptr) {
				prev = temp;
				temp = temp->right;
			}
			to_be_changed->data = temp->data;
			if (temp->left != nullptr) {
				prev->left = temp->left;
			}
			delete temp;
		}
		return true;
	}
}


bool SortedBag::search(TComp elem) const {
	if (binary_search_tree->root != nullptr) {
		Node* temp = binary_search_tree->root;
		while (temp != nullptr && (temp->left != nullptr || temp->right != nullptr)) {
			if (elem == temp->data)
				return true;
			else if (rel(temp->data, elem) && temp->right != nullptr)
				temp = temp->right;
			else if (!rel(temp->data, elem) && temp->left != nullptr)
				temp = temp->left;
			else if (!rel(temp->data, elem) && temp->left == nullptr)
				return false;
			else if (rel(temp->data, elem) && temp->right == nullptr)
				return false;
		}
		if (temp != nullptr && temp->data == elem)
			return true;
	}
	return false;
}

/*
bool SortedBag::search(TComp elem) const {
	Node* temp = binary_search_tree->root;
	while (temp != nullptr) {
		if (elem == temp->data)
			return true;
		else if (rel(elem, temp->data))
			temp = temp->left;
		else
			temp = temp->right;
	}
	return false;
}
*/
int SortedBag::nrOccurrences(TComp elem) const {
	SortedBagIterator it = iterator();
	int nr_oc = 0;
	for (int i = 0; i < it.queue.sz(); ++i)
		if (it.queue[i] == elem)
			nr_oc++;
	return nr_oc;
}


int SortedBag::size() const {
	return first_free;
}


bool SortedBag::isEmpty() const {
	return first_free == 0;
}

void SortedBag::delete_nodes(Node* root)
{
	if (root != nullptr) {
		delete_nodes(root->left);
		delete_nodes(root->right);
		delete root;
	}
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete_nodes(binary_search_tree->root);
	delete binary_search_tree;
}
