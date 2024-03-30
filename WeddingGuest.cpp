#include "WeddingGuest.h"
using namespace std; 
#include <iostream>



void attestGuests(const std::string& fsearch, const std::string& lsearch,
	const WeddingGuest& odOne, WeddingGuest& odResult) {
	string FN1, LN1;
	GuestType val1;
	WeddingGuest tempList;
	bool matched = false;

	for (int i = 0; i < odOne.guestCount(); i++) {
		odOne.verifyGuestOnTheList(i, FN1, LN1, val1);
		if (fsearch == FN1) {
			matched = true;
			tempList.inviteGuest(FN1, LN1, val1);
		}
		else if (lsearch == LN1) {
			matched = true;
			tempList.inviteGuest(FN1, LN1, val1);
		}
	}
	if (matched == false)
		tempList = odOne;

	odResult = tempList;

	//cout << "\n************* JOINED LIST ***************\n";
	//odResult.printList();
}

bool joinGuests(const WeddingGuest& odOne, const WeddingGuest& odTwo,
	WeddingGuest& joinedList) {
	string FN1, LN1;
	GuestType val1;
	string FN2, LN2;
	GuestType val2;
	bool unique = true;
	bool toReturn = true;
	WeddingGuest tempList;

	for (int i = 0; i < odOne.guestCount(); i++) {
		unique = true;
		odOne.verifyGuestOnTheList(i, FN1, LN1, val1);
		for (int j = 0; j < odTwo.guestCount(); j++) {
			odTwo.verifyGuestOnTheList(j, FN2, LN2, val2);
			if (FN1 == FN2 && LN1 == LN2 && val1 == val2) {
				tempList.inviteGuest(FN1, LN1, val1);
			}
			else if (FN1 == FN2 && LN1 == LN2 && val1 != val2) {
				unique = false;
				toReturn = false;
			}
		}
		if (unique == true) {
			tempList.inviteGuest(FN1, LN1, val1);
		}
	}

	for (int i = 0; i < odTwo.guestCount(); i++) {
		unique = true;
		odTwo.verifyGuestOnTheList(i, FN2, LN2, val2);
		for (int j = 0; j < odOne.guestCount(); j++) {
			odOne.verifyGuestOnTheList(j, FN1, LN1, val1);
			if (FN2 == FN1 && LN2 == LN1 && val2 != val1) {
				unique = false;
				toReturn = false;
			}
		}
		if (unique == true) {
			tempList.inviteGuest(FN2, LN2, val2);
		}
	}
	joinedList = tempList;

	//cout << "\n************* JOINED LIST ***************\n";
	//joinedList.printList();
	return toReturn;
}


const  WeddingGuest& WeddingGuest :: operator =(const WeddingGuest& rhs) {
	// check for allias copy
	if (this == &rhs)
		return *this;

	// delete this's nodes 
	Node* currNode = this->head;
	Node* nextNode = this->head;
	while (currNode != nullptr && nextNode != nullptr) {
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	this->head = nullptr;

	// fill this, with RHS data 
	Node* p = rhs.head;
	for (int i = 0; i < rhs.guestCount(); i++) {
		this->insertToBack(p->firstName, p->lastName, p->value);
		p = p->next;
	}
	return *this;
}

void WeddingGuest::insertToBack(std::string firstName, std::string lastName, GuestType value) {
	Node* newNode = new Node;
	newNode->firstName = firstName;
	newNode->lastName = lastName;
	newNode->value = value;
	newNode->prev = nullptr;
	newNode->next = nullptr;

	// case1- inserting to back of an empty LL
	if (head == nullptr) {
		head = newNode;
		return;
	}
	// case2 - insertring back to a filled LL
	Node* p = head;
	while (p->next != nullptr)
		p = p->next;
	p->next = newNode;
	newNode->prev = p;
	newNode->next = nullptr;
	return;
}


WeddingGuest::WeddingGuest(const WeddingGuest& rhs) {
	// copy elements from rhs to this
	Node* p = rhs.head;
	for (int i = 0; i < rhs.guestCount(); i++) {
		this->sortedInsert(p->firstName, p->lastName, p->value);
		p = p->next;
	}
}

WeddingGuest ::~WeddingGuest() {
	Node* currNode = head;
	Node* nextNode = head;
	while (currNode != nullptr && nextNode != nullptr) {
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	this->head = nullptr;
}


void WeddingGuest::swapWeddingGuests(WeddingGuest& other) {
	// swap heads 
	Node* tempNode = this->head;
	this->head = other.head;
	other.head = tempNode;
}

bool WeddingGuest::verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName,
	GuestType& value) const {
	if (this->head == nullptr)
		return false; 
	Node* p;
	if (i >= 0 && i < this->guestCount()) {
		p = head;
		for (int j = 0; j < i; j++)
			p = p->next;
		firstName = p->firstName;
		lastName = p->lastName;
		value = p->value;
		return true;
	}
	return false;
}

bool WeddingGuest:: matchInvitedGuest(const std::string& firstName, 
	const std::string& lastName, GuestType& value) const {
	if (isGuestOnList(firstName, lastName) == true) {
		for (Node* p = head; p != nullptr; p = p->next) {
			if (p->firstName == firstName && p->lastName == lastName) {
				value = p->value; 
				return true; 
			}
		}
	}
	return false; 
}


bool WeddingGuest:: invitedToTheWedding(const std::string& firstName, 
	const std::string& lastName) const {
	if (isGuestOnList(firstName, lastName) == true)
		return true; 
	return false; 
}

bool WeddingGuest::crossGuestOff(const std::string& firstName, const std::string& lastName) {
	if (isGuestOnList(firstName, lastName) == true) {
		for (Node* p = head; p != nullptr; p = p->next) {
			if (p->firstName == firstName && p->lastName == lastName) {
				this->deleteNode(p->firstName, p->lastName, p->value); 
				return true; 
			}
		}
	}
	return false; 
}

bool WeddingGuest::inviteOrAlter(const std::string& firstName, const std::string& lastName, 
	const GuestType& value) {
	if (isGuestOnList(firstName, lastName) == true) {
		for (Node* p = head; p != nullptr; p = p->next) {
			if (p->firstName == firstName && p->lastName == lastName) {
				p->value = value;
				return true;
			}
		}
	}
	sortedInsert(firstName, lastName, value); 
	return true; 
}

bool WeddingGuest::alterGuest(const std::string& firstName, const std::string& lastName, 
	const GuestType& value) {
	if (isGuestOnList(firstName, lastName) == true) {
		for (Node* p = head; p != nullptr; p = p->next) {
			if (p->firstName == firstName && p->lastName == lastName) {
				p->value = value; 
				return true; 
			}
		}
	}
	return false; 
}

bool WeddingGuest::inviteGuest(const std::string& firstName, const std::string& lastName, 
	const GuestType& value) {
	if (!isGuestOnList(firstName, lastName)) {
		this->sortedInsert(firstName, lastName, value); 
		return true;
	}
	return false; 
}
int WeddingGuest::guestCount() const {
	if (this->head == nullptr)
		return 0;
	int counter = 0;
	for (Node* p = head; p != nullptr; p = p->next)
		counter++;
	return counter;
}

bool WeddingGuest::noGuests() const {
	if (this->head == nullptr)
		return true;
	return false;
}

WeddingGuest::WeddingGuest() {
	this->head = nullptr;
}

void WeddingGuest::deleteNode(std::string firstName, std::string lastName, GuestType value) {
	if (head == nullptr)
		return;
	// case1 - deleting 1st node 
	if (head->firstName == firstName && head->lastName == lastName) {
		Node* p1 = head;
		head = head->next;
		delete p1;
		if (head != nullptr) {
			head->prev = nullptr;
		}
		return;
	}
	// case2 - deleting at any postion 
	Node* p;
	for (p = head; p != nullptr; p = p->next) {
		if (p->firstName == firstName && p->lastName == lastName) {
			break;
		}
	}
	//  cout<<" P IS POINTING ON ---------> "<<p->data<<endl; 
	if (p)
		p->prev->next = p->next;
	if (p->next != nullptr && p) {
		p->next->prev = p->prev;
	}
	delete p;
}
void WeddingGuest::printList() const {
	if (this->head == nullptr)
		return;
	
	for (Node* p = head; p != nullptr; p = p->next) {
		cout << p->firstName
			<< ", " << p->lastName
			<< ", " << p->value << "\n";
	}
	cout << endl;
}

bool WeddingGuest::isGuestOnList(std::string firstName, std::string lastName) const {
	if (this->head == nullptr)
		return false; 
	bool found = false;
	for (Node* p = head; p != nullptr; p = p->next) {
		if (p->firstName == firstName && p->lastName == lastName) {
			found = true;
			break;
		}
	}
	return found;
}

void WeddingGuest::sortedInsert(std::string firstName, std::string lastName, 
	GuestType value) {
	Node* newNode = new Node;
	newNode->value = value;
	newNode->firstName = firstName;
	newNode->lastName = lastName;
	newNode->next = nullptr;
	newNode->prev = nullptr;

	// case1 - insertInOrder in an empty list 
	if (head == nullptr) {
		head = newNode;
		return;
	}
	// case2 - insertInOrder as the firstNode [inserting b4 1st node]
	else if (lastName < head->lastName) {
		newNode->prev = nullptr;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		return;
	}
	// case3 - insertInOrder before firstNode, with same lastName
	else if (lastName == head->lastName) {
		if (firstName < head->firstName) {
			newNode->prev = nullptr;
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
			return;
		}
	}
	// case4 - insertInOrder in with lastName in middle or end  
	for (Node* p = head; p != nullptr; p = p->next) {
		if (p->lastName == lastName) {
			if (p->firstName < firstName) {
				newNode->next = p->next;
				newNode->prev = p;
				if (p->next != nullptr) {
					p->next->prev = newNode;
				}
				p->next = newNode;
				return;
			}
		}
	}

	Node* ptr = head;
	while (ptr->lastName < lastName && ptr->next != nullptr) {
		ptr = ptr->next;
	}
	if (ptr->lastName < lastName && ptr->next == nullptr) {
		ptr->next = newNode;
		newNode->prev = ptr;
		newNode->next = nullptr;
		return; 
	}
	if (ptr != head) {
		ptr = ptr->prev;
		newNode->next = ptr->next;
		newNode->prev = ptr;
	}
	if (ptr->next != nullptr) {
		ptr->next->prev = newNode;
	}
	ptr->next = newNode;
	return;
}
