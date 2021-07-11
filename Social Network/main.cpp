#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "UserInfo.h"
#include "FriendsBST.h"
using namespace std;


/*****************LINKED LIST CONTAINING USERS DATA IS MADE GLOBAL SO AS TO BE VISIBLE IN ALL SCOPES*********************/
LinkedList UserList;
/***********************************************************************************************************************/


void createLinkedList(){ //Function to create and initialize linked list with users data read from the all-users.in file.
    string line;
    ifstream myFile ("D:\\C++\\Social Network\\all-users.in");
    if (myFile.is_open())
    {
        while ( getline (myFile,line) )
        {
            string str[3];
            int j=0;
            //cout << line << '\n';
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
            int choice=0;
            while(choice!=6) {
                cout<<"\n**********MENU**********\n";
                cout<<"1- Show Friend List\n2- Find User in friend list\n3- Add user as friend\n4- Remove a friends\n6- Logout"<<endl;
                cin>>choice;
                switch (choice) {
                    case 1:
                        UserList.FriendsList(commands);
                        break;
                    case 2:
                        cout<<"Enter friend username: ";
                        cin>>_friend;
                            if(UserList.searchUserInFriendList(commands,_friend)){
                                cout<<"User is your friend!\n";
                            }
                        break;
                    case 3:
                        cout<<"Enter friend username: ";
                        cin>>_friend;
                        UserList.add_Friends(commands,_friend);
                        break;
                    case 4:
                        cout<<"Enter friend username: ";
                        cin>>_friend;
                        UserList.remove_Friends(commands,_friend);
                        break;
                    case 5:
                        UserList.peopleYouMayKnow(user);
                        //PEOPLE YOU MAY KNOW
                        break;
                    case 6:
                        //LOGOUT
                        break;
                    default:
                        cout<<"Invalid choice!"<<endl;
                        break;
                }
            }
        }else{
            cout<<"User could not be found!"<<endl;
        }
    }
    /**********************************************************/
    return 0;
}
