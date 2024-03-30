

#ifndef WG_H
#define WG_H
#include <string>
using namespace std;
//#include <iostream> 

typedef std::string GuestType;
class WeddingGuest {
private: 
    struct Node {
        std::string firstName; 
        std::string lastName;
        GuestType value; 
        Node* next; 
        Node* prev; 
    };
    Node* head; 
    void sortedInsert(std::string firstName, std::string lastName, GuestType value); 
    bool isGuestOnList(std::string firstName, std::string lastName) const; 
    void deleteNode(std::string firstName, std::string lastName, GuestType value); 
    void insertToBack(std::string firstName, std::string lastName, GuestType value);
    void printList() const;
public:
    WeddingGuest(); 

    bool noGuests() const; 

    int guestCount() const; 

    bool inviteGuest(const std::string& firstName, 
        const std::string& lastName, const GuestType& value); 

    bool alterGuest(const std::string& firstName, const std::string& lastName, 
        const GuestType& value); 

    bool inviteOrAlter(const std::string& firstName, 
        const std::string& lastName, const GuestType& value); 

    bool crossGuestOff(const std::string& firstName, const std::string& lastName);

    bool invitedToTheWedding(const std::string& firstName, 
        const std::string& lastName) const; 

    bool matchInvitedGuest(const std::string& firstName, const std::string& lastName, 
        GuestType& value) const;   

    bool verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, 
        GuestType& value) const;

    void swapWeddingGuests(WeddingGuest& other); 

    ~WeddingGuest(); 
    
    WeddingGuest(const WeddingGuest& rhs); 

    const WeddingGuest& operator= (const WeddingGuest& rhs); 
};
#endif
bool joinGuests(const WeddingGuest& odOne, const WeddingGuest& odTwo,
    WeddingGuest& joinedList);
void attestGuests(const std::string& fsearch, const std::string& lsearch,
    const WeddingGuest& odOne, WeddingGuest& odResult);
