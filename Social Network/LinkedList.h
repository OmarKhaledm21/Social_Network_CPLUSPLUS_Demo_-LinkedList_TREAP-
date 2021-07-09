//
// Created by Omar on 7/8/2021.
//

#ifndef SOCIAL_NETWORK_LINKEDLIST_H
#define SOCIAL_NETWORK_LINKEDLIST_H
#include <iostream>
#include "UserInfo.h"
using namespace std;

struct node {
    UserInfo info;
    node* link;
};

class LinkedList {
public:
    int count;
    node* head;
    node* tail;
public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    bool isEmpty()const {
        return head == nullptr;
    }

    void print()const {
        node* current = head;
        while (current != nullptr) {
            cout << current->info << " ";
            current = current->link;
        }
    }

    int length()const {
        return count;
    }

    UserInfo front()const {
        if (head != nullptr) { return head->info; }
        else { cout<<"Users List is empty!\n"; }
        UserInfo nullObj;
        return nullObj;
    }

    UserInfo back()const {
        if (tail != nullptr) { return tail->info; }
        else { cout<<"Users List is empty!\n"; }
        UserInfo nullObj;
        return nullObj;
    }

    void deleteNode(UserInfo& deleteItem) {
        node* current=NULL;
        node* trailCurrent=NULL;
        bool found;
        if (head == NULL) {
            cout << "List is empty" << endl;
        }
        else {
            found = false;
            trailCurrent = head;
            current = head->link;
        }
        while (current != NULL && !found)
        {
            if (current->info.getName() != deleteItem.getName())
            {
                trailCurrent = current;
                current = current->link;
            }
            else {
                found = true;
            }
        }
        if (found == true) {
            trailCurrent->link = current->link;
            count--;
            if (tail == current) {
                tail = trailCurrent;
            }
            delete current;
        }
        else if (found == false) {
            cout << "Item is not found!" << endl;
        }
    }

    UserInfo& search(string username) {
        node* current;
        bool found = false;
        current = head;
        while (current != NULL && !found) {
            if (current->info.getUsername() == username) {
                found = true;
            }
            else {
                current = current->link;
            }
        }
        return current->info;
    }

    void push_front(const UserInfo& newItem) {
        node* newNode;
        newNode = new node;
        newNode->info = newItem;
        newNode->link = head;
        head = newNode;
        count++;
        if (tail == NULL)
            tail = newNode;
    }
    void push_back(const UserInfo& newItem) {
        node* newNode = new node;
        newNode->info = newItem;
        newNode->link = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            count++;
        }
        else {
            tail->link = newNode;
            tail = newNode;
            count++;
        }
    }

    void printList(){
        node* cur=head;
        while (cur!= nullptr){
            cur->info.printInfo();
            cur=cur->link;
        }
    }

    void destroyList() {
        node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->link;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    ~LinkedList() { destroyList(); }
};


#endif //SOCIAL_NETWORK_LINKEDLIST_H
