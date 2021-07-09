#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "UserInfo.h"
#include "FriendsBST.h"
using namespace std;

LinkedList UserList;

void createFriendList(string username){
    FriendsBST myList;
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
                UserInfo *temp = new UserInfo(UserList.search(str[1]));
                myList.Add(str[1], temp);
            }
        }
        myFile2.close();
    }else {
        cout << "Unable to open file";
    }

    cout<<"*************************************************\nYour Friends: \n";
    myList.printInOrder();
    cout<<"*************************************************\n";

}

int main() {

    FriendsBST userFriends;

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

            userFriends.Add(str[0],userInfo);
        }
        myFile.close();
    }else {
        cout << "Unable to open file";
    }

    createFriendList("olaa100");
    cout<<endl<<endl;
    //UserList.print();
    cout<<endl<<endl<<endl;
    //userFriends.printInOrder();
    return 0;
}
