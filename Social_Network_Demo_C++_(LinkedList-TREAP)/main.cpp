#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
using namespace std;

/*****************LINKED LIST CONTAINING USERS DATA IS MADE GLOBAL SO AS TO BE VISIBLE IN ALL SCOPES*********************/
LinkedList UserList;
/***********************************************************************************************************************/

void createLinkedList(){ //Function to create and initialize linked list with users data read from the all-users.in file.
    string line;
    ifstream myFile ("../all-users.in");
    if (myFile.is_open())
    {
        while ( getline (myFile,line) )
        {
            string str[3];
            int j=0;
            for(int i=0; i<line.size(); i++) {
                if(line[i]==','){
                    i+=2;
                    j++;
                }
                str[j]+=line[i];
            }
            UserInfo* userInfo = new UserInfo(str[0],str[1],str[2]);
            UserList.push_back(*userInfo);
        }
        myFile.close();
    }else {
        cout << "Unable to open file";
    }
}

int main() {

    // Creating and initializing linked list
    createLinkedList();

    //TEST CASE TO MAKE SURE LINKED LIST WORKS CORRECTLY
    //UserList.print();

    /***************************MAIN****************************/
    string commands="start";
    while (commands!="exit"){
        cout<<"Type your username to login or 'exit' to exit: ";
        cin>>commands;
        if(commands=="exit"){
            break;
        }
        UserInfo user = UserList.search(commands);
        string _friend;
        if(user.getUsername()!=""){
            string choice="0";
            while(choice!="logout") {
                cout<<"\n**********MENU**********\n";
                cout<<"1- Show Friend List\n2- Find User in friend list\n3- Add user as friend\n4- Remove a friends\n5- People you may know\nHint: type 'logout' to logout\n"<<endl;
                cin >> choice;
                if(choice=="1"){
                    UserList.FriendsList(commands);
                }else if (choice=="2"){
                    cout<<"Enter friend username: ";
                    cin>>_friend;
                    if(UserList.searchUserInFriendList(commands,_friend)){
                        cout<<"User is your friend!\n";
                    }else{
                        cout<<"User is not in your friend list\n";
                    }
                }else if(choice=="3"){
                    cout<<"Enter friend username: ";
                    cin>>_friend;
                    UserList.add_Friends(commands,_friend);
                }else if(choice=="4"){
                    cout<<"Enter friend username: ";
                    cin>>_friend;
                    UserList.remove_Friends(commands,_friend);
                }else if(choice=="5"){
                    UserList.peopleYouMayKnow(user);
                }else if(choice=="logout") {
                    break;
                }
                else{
                    cout<<"Invalid choice!"<<endl;
                    continue;
                }
            }
        }else{
            cout<<"User could not be found!"<<endl;
        }
    }
    /**********************************************************/
    return 0;
}
