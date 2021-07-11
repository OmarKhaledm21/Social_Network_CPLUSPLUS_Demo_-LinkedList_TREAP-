//
// Created by Omar on 7/8/2021.
//

#ifndef SOCIAL_NETWORK_LINKEDLIST_H
#define SOCIAL_NETWORK_LINKEDLIST_H
#include <iostream>
#include "UserInfo.h"
#include "FriendsBST.h"
using namespace std;

struct node {
    UserInfo info;
    FriendsBST myTree;
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

    FriendsBST createFriendList(string username,FriendsBST& myList){
        string line2;
        ifstream myFile2 ("D:\\C++\\Social Network\\all-users-relations.in");
        if (myFile2.is_open())
        {
            while ( getline (myFile2,line2) )
            {
                string str[2];
                int j=0;
                //cout << line2 << '\n';
                for(int i=0; i<line2.size(); i++) {
                    if(line2[i]==','){
                        i+=2;
                        j++;
                    }
                    str[j]+=line2[i];
                }
                if(str[0]==username) {
                    UserInfo *temp = new UserInfo(this->search(str[1]));
                    myList.Add(str[1], temp);
                }
            }
            myFile2.close();
        }else {
            cout << "Unable to open file";
        }
        return myList;
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
        if(!found){
            UserInfo* temp= new UserInfo("","","");
            return *temp;
        }
        return current->info;
    }

    bool searchUserInFriendList(string username,string target){
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
        if(found){
            bool foundUser = current->myTree.Find(target);
            return foundUser;
        }else{
            cout<<"This user is not your friend! :(\n";
            return false;
        }
    }

    void add_Friends(string username,string target){
        node* current;
        node* newFriends;
        bool found = false;
        bool found_target=false;

        current = head;
        while (current != NULL && !found) {
            if (current->info.getUsername() == username) {
                found = true;
            }
            else {
                current = current->link;
            }
        }

        newFriends=head;
        while (newFriends!=NULL && !found_target){
            if(newFriends->info.getUsername()==target){
                found_target=true;
            }else{
                newFriends = newFriends->link;
            }
        }
        if(found_target && found) {
            current->myTree.Add(newFriends->info.getUsername(), &newFriends->info);
            newFriends->myTree.Add(current->info.getUsername(),&current->info);
            cout << "User added to friends list\n";
        }else {
            cout << "This user is not avalible\n";
        }
    }

    void remove_Friends(string username,string target){
        node* current;
        node* newFriends;
        bool found = false,found_target=false;
        newFriends=head;
        current = head;

        while (current != NULL && !found) {
            if (current->info.getUsername() == username) {
                found = true;
            }
            else {
                current = current->link;
            }
        }

        while (newFriends!=NULL && !found_target){
            if(newFriends->info.getUsername()==target){
                found_target=true;
            }else{
                newFriends = newFriends->link;
            }
        }

        if(found_target && found) {
            current->myTree.Remove(newFriends->info.getUsername());
            newFriends->myTree.Remove(current->info.getUsername());
            cout << "User removed from friends list\n";
        }else {
            cout << "This user is not in your friends list\n";
        }
    }

    void peopleYouMayKnow(UserInfo user){
        cout<<"---------------People you may know------------------\n";
        string username = user.getUsername();
        node* current=head;
        int counter=0;
        while (current!=NULL && counter!=5){
            if(current->info.getUsername()==username){
                current=current->link;
                continue;
            }else if(current->myTree.Find(username)){
                current=current->link;
                continue;
            }else{
                cout<<"User "<<counter+1<<": \n";
                current->info.printInfo();
                current=current->link;
                counter++;
            }
        }
    }

    void FriendsList(string username) {
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
        if(found){
            current->myTree.printInOrder();
        }else{
            cout<<"Could not find any friends!  :(\n";
        }
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


        string line2;
        ifstream myFile2 ("D:\\C++\\Social Network\\all-users-relations.in");
        if (myFile2.is_open())
        {
            while ( getline (myFile2,line2) )
            {
                string str[2];
                int j=0;
                //cout << line2 << '\n';
                for(int i=0; i<line2.size(); i++) {
                    if(line2[i]==','){
                        i+=2;
                        j++;
                    }
                    str[j]+=line2[i];
                }
                if(str[0]==newNode->info.getUsername()) {

                    string USERS_INFO;
                    ifstream USERS_FILE ("D:\\C++\\Social Network\\all-users.in");
                    if (USERS_FILE.is_open())
                    {
                        while ( getline (USERS_FILE, USERS_INFO) )
                        {
                            string users_line[3];
                            int x=0;
                            for(int z=0; z < USERS_INFO.size(); z++) {
                                if(USERS_INFO[z] == ','){
                                    z+=2;
                                    x++;
                                }
                                users_line[x]+=USERS_INFO[z];
                            }
                            if(users_line[0]==str[1]) {
                                UserInfo *temp = new UserInfo(users_line[0], users_line[1], users_line[2]);
                                newNode->myTree.Add(str[1], temp);
                            }
                        }
                        USERS_FILE.close();
                    }else {
                        cout << "Unable to open file";
                    }

                }else if(str[1]==newNode->info.getUsername()){
                    string USERS_INFO;
                    ifstream USERS_FILE ("D:\\C++\\Social Network\\all-users.in");
                    if (USERS_FILE.is_open())
                    {
                        while ( getline (USERS_FILE, USERS_INFO) )
                        {
                            string users_line[3];
                            int x=0;
                            for(int z=0; z < USERS_INFO.size(); z++) {
                                if(USERS_INFO[z] == ','){
                                    z+=2;
                                    x++;
                                }
                                users_line[x]+=USERS_INFO[z];
                            }
                            if(users_line[0]==str[0]) {
                                UserInfo *temp = new UserInfo(users_line[0], users_line[1], users_line[2]);
                                newNode->myTree.Add(str[0], temp);
                            }
                        }
                        USERS_FILE.close();
                    }else {
                        cout << "Unable to open file";
                    }
                }else{
                    continue;
                }
            }
            myFile2.close();
        }else {
            cout << "Unable to open file";
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
