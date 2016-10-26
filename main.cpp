//
//  main.cpp
//  BillSplitter
//
//  Created by Shwetabh Singh on 18/08/16.
//  Copyright © 2016 shwetabh. All rights reserved.
//

#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <array>


typedef unsigned int uint;

using namespace std;

// data structures used
uint graph[51][51];
map<string,uint> peopleArr;
map<string,uint> peopleIncludedInExpenseArr;

// variables used
uint len;
string group;

string personWhoPaid;
string personWhoTransfered;

uint expense;
uint eachPersonExpense;
uint transferMoney;

// iterator of map
map<string,uint> :: iterator it_type;

// method to get name associated with graph index
string findNameForIndex(uint index)
{
    for(it_type = peopleArr.begin(); it_type != peopleArr.end(); it_type++) {
        if(it_type->second == index)
        {
            return it_type->first;
        }
    }
    return "";
}

// method to see present state of expenses in group.
void settle(uint size)
{
    for (uint i = 0; i < size; i++)
        for (uint j = 0; j < size; j++)
        {
            if(graph[i][j] > 0)
            {
                cout << findNameForIndex(j) << " has to pay " << personWhoPaid << " " << graph[i][j] << "\n";
            }
        }
}

// method to transfer money in group
void transfer()
{
    cout << "Who transfered : ";
    cin >> personWhoTransfered;
    
    cout << "How much transfered : ";
    cin >> transferMoney;
    
    // set values to the graph
    graph[peopleArr[personWhoPaid]][peopleArr[personWhoTransfered]] = (expense / peopleIncludedInExpenseArr.size()) - transferMoney;
}

// method to add expense to group
void addExpense()
{
    cout << "Enter the expense to group " << group << " : ";
    cin >> expense;
    
    cout << "Who paid : ";
    cin >> personWhoPaid;
    
    uint n;
    string peop;
    cout << "Enter the number of people paid for : ";
    cin >> n;
    
    for (uint i = 0; i < n; i++) {
        cout << "Enter " << i+1 << " person : ";
        cin >> peop;
        peopleIncludedInExpenseArr[peop] = 1;
    }
    
    eachPersonExpense = expense / peopleIncludedInExpenseArr.size();
    
    // set values to the graph
    for(it_type = peopleIncludedInExpenseArr.begin(); it_type != peopleIncludedInExpenseArr.end(); it_type++) {
        graph[peopleArr[personWhoPaid]][peopleArr[it_type->first]] = eachPersonExpense;
    }
}

int main()
{
    cout << "Enter the group name : ";
    cin >> group;
    
    cout << "Enter the number of people in group " << group << " : ";
    cin >> len;
    
    string name;
    cout << "Enter the names of people in group " << group << " : ";
    for (uint i = 0; i < len; i++) {
        cin >> name;
        peopleArr[name] = i;
    }
    
    //SET graph values to 0;
    for (uint i = 0; i < len; i++)
        for (uint j = 0; j < len; j++)
            graph[i][j] = 0;
    
    uint option = 0;
    do {
        cout << "******** MAIN MENU ********";
        cout << "\n 1. Add expense to " << group;
        cout << "\n 2. Transfer in " << group;
        cout << "\n 3. Settle up " << group;
        cout << "\n 4. Exit.";
        
        cout << "\n Enter your option : ";
        cin >> option;
        
        switch (option) {
            case 1:
                addExpense();
                break;
                
            case 2:
                transfer();
                break;
                
            case 3:
                settle(len);
                break;
                
            default:
                break;
        }
        
    } while (option != 4);
    
    return 0;
}