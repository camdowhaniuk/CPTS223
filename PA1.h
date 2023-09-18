#include <iostream>
#include <fstream>
#include <sstream>
#include "List.h"

using namespace std;

struct profile
{
    string name;
    int points;
};

template <class C, class D>
ifstream & operator>> (ifstream &input, List<C, D> &rhs);

template <class C, class D>
ostream & operator<< (ostream &output, List<C, D> &rhs);

template <class C, class D>
void loadList(List<C, D> &list);

void loadArray(profile profiles[]);

template <class C, class D>
void displayMenu(List<C, D> &list, profile profiles[]);

void displayGameRules();

template <class C, class D>
void playGame(List<C, D> &list, profile profiles[]);

template <class C, class D>
void loadPrevGame(List<C,D> &list, profile profiles[]);

template <class C, class D>
void addCommand(List<C, D> &list);

template <class C, class D>
void removeCommand(List<C, D> &list);

template <class C, class D>
int countCommands(List<C, D> &list);

template <class C, class D>
void findRandCommand(List<C, D> &list, C &command, D &description1, string &description2, string &description3);

void loadArray(profile profiles[]);

void insertFrontArray(profile profiles[], profile p, int size);

int findSizeArray(profile profiles[]);

template <class C, class D>
void writeCommands(List<C, D> &list);

void writeProfiles(profile profiles[]);
















// overloaded stream extraction operator to read commands and their descriptions from file to list
template <class C, class D>
ifstream & operator>> (ifstream &input, List<C, D> &rhs)
{
	while (!input.eof()) 
    {
        string line;
        getline(input, line);

        // find the position of the comma
        size_t pos = line.find(",");
        if (pos != string::npos) {
            // extract command and description
            C command = line.substr(0, pos);
            D description = line.substr(pos + 1); // skip the comma

            rhs.insertFront(command, description);
        }
    }


	return input;
}

// overloaded stream insertion operator to write commands and their descriptions from list to file
template <class C, class D>
ostream & operator<< (ostream &output, List<C, D> &rhs)
{
	node<C, D> *pCur = rhs.getHead();

	while (pCur != nullptr)
	{
		output << pCur->command << ", " << pCur->description << endl;
		pCur = pCur->next;
	}

	return output;
}

// loads list from commands.csv file
template <class C, class D>
void loadList(List<C, D> &list)
{
    ifstream ifs("commands.csv");

    ifs >> list; 
}

// displays menu
template <class C, class D>
void displayMenu(List<C, D> &list, profile profiles[])
{
    int choice = 0;
    while (choice != 6)
    {
        cout << "Select one of the following options: " << endl;
        cout << "1. Game Rules" << endl << "2. Play Game" << endl << "3. Load Previous Game" << endl << "4. Add Command" << endl << "5. Remove Command" << endl << "6. Exit" << endl;
        cin >> choice;
        switch(choice)
        {
            case 1:
            displayGameRules();
            break;

            case 2:
            playGame(list, profiles);
            break;

            case 3:
            loadPrevGame(list, profiles);
            break;

            case 4:
            addCommand(list);
            break;

            case 5:
            removeCommand(list);
            break;

            case 6:
            writeCommands(list);
            writeProfiles(profiles);
            break;
        }
    }
}

// main part of program which plays the game
template <class C, class D>
void playGame(List<C, D> &list, profile profiles[])
{
    string name, description2, description3, commandsUsed[30];
    C command;
    D description1;
    int listSize = countCommands(list), numCommands = 0, i = 0, selection = 0, correctChoice = 0, j = 0, points = 0, a = 0;
    
    // cout << listSize << endl << r1 << "  " << r2 << endl;
    cout << "What is your name? ";
    cin >> name;
    
    // loops until user inputs number between 5 and 30
    while(numCommands < 5 || numCommands > 30)
    {
        cout << "How many commands do you want to generate for matching?(between 5-30) ";
        cin >> numCommands;
        if(numCommands < 5 || numCommands > 30)
        {
            cout << "Invalid input. Enter number between 5 and 30." << endl;
        }
    }

    // loops for number of commands user selected
    while(i != numCommands)
    {
        a = 0;
        int r1 = rand() % 3, r2 = rand() % 3;
        // loops until r1 and r2 are different values
        while(r1 == r2)
        {
            r2 = rand() % 3;
        }
        findRandCommand(list, command, description1, description2, description3);
        // loops until a different command is displayed that hasn't been displayed already
        while(a == 0)
        {
            a = 1;
            for(int k = 0; k < i; k++)
            {
                if(command == commandsUsed[k])
                {
                    findRandCommand(list, command, description1, description2, description3);
                    a = 0;
                }
            }
        }

        commandsUsed[i] = command;

        if(r1 == 0)
        {
            cout << "Command: " << command << endl << "1. " << description1 << endl << "2. " << description2 << endl << "3. " << description3 << endl;
            correctChoice = 1;
        }
        else if(r2 == 0)
        {
            cout << "Command: " << command << endl << "1. " << description2 << endl << "2. " << description1 << endl << "3. " << description3 << endl;
            correctChoice = 2;
        }
        else
        {
            cout << "Command: " << command << endl << "1. " << description2 << endl << "2. " << description3 << endl << "3. " << description1 << endl;
            correctChoice = 3;
        }

        cout << "Which description is correct? ";
        cin >> selection;

        if(selection == correctChoice)
        {
            cout << "Correct! " << command << "- " << description1 << endl << endl;
            points++;
        }
        else
        {
            cout << "Incorrect! " << command << "- " << description1 << endl << endl;
            points--;
        }

        i++;
    }

    cout << points << endl;

    profile p;
    p.name = name;
    p.points = points;
    insertFrontArray(profiles, p, findSizeArray(profiles));

}

// loads previous game by finding profile and plays like playGame()
template <class C, class D>
void loadPrevGame(List<C,D> &list, profile profiles[])
{
    string name, description2, description3, commandsUsed[30];
    C command;
    D description1;
    int listSize = countCommands(list), numCommands = 0, i = 0, selection = 0, correctChoice = 0, x = 0, points = 0, a = 0;
    
    cout << "Enter profile name to load profile... ";
    cin >> name;

    for(int j = 0; j < 5; j++)
    {
        if(profiles[j].name == name)
        {
            points = profiles[j].points;
            cout << "Welcome " << name << "! You have " << profiles[j].points << " points" << endl;
            x = j;
        }
    }

    while(numCommands < 5 || numCommands > 30)
    {
        cout << "How many commands do you want to generate for matching?(between 5-30) ";
        cin >> numCommands;
        if(numCommands < 5 || numCommands > 30)
        {
            cout << "Invalid input. Enter number between 5 and 30." << endl;
        }
    }

    while(i != numCommands)
    {
        a = 0;
        int r1 = rand() % 3, r2 = rand() % 3;
        while(r1 == r2)
        {
            r2 = rand() % 3;
        }
        findRandCommand(list, command, description1, description2, description3);
        while(a == 0)
        {
            a = 1;
            for(int k = 0; k < i; k++)
            {
                if(command == commandsUsed[k])
                {
                    findRandCommand(list, command, description1, description2, description3);
                    a = 0;
                }
            }
        }

        commandsUsed[i] = command;

        if(r1 == 0)
        {
            cout << "Command: " << command << endl << "1. " << description1 << endl << "2. " << description2 << endl << "3. " << description3 << endl;
            correctChoice = 1;
        }
        else if(r2 == 0)
        {
            cout << "Command: " << command << endl << "1. " << description2 << endl << "2. " << description1 << endl << "3. " << description3 << endl;
            correctChoice = 2;
        }
        else
        {
            cout << "Command: " << command << endl << "1. " << description2 << endl << "2. " << description3 << endl << "3. " << description1 << endl;
            correctChoice = 3;
        }

        cout << "Which description is correct? ";
        cin >> selection;

        if(selection == correctChoice)
        {
            cout << "Correct! " << command << "- " << description1 << endl << endl;
            points++;
        }
        else
        {
            cout << "Incorrect! " << command << "- " << description1 << endl << endl;
            points--;
        }

        i++;
    }

    profiles[x].points = points;
}

// allows user to add command to list
template <class C, class D>
void addCommand(List<C, D> &list)
{
    C command;
    D description;
    int dup = 0;
    node <C, D> *cur = list.getHead();
    cout << list.getSize() << endl;

    while(dup == 0)
    {
        cur = list.getHead();
        cout << "Enter command to add to current list... ";
        cin >> command;
        dup = 1;
        for(int i = 0; i < list.getSize() && cur != nullptr; i++, cur = cur->next)
        {
            if(command == cur->command)
            {
                dup = 0;
                cout << "That command is already in the current list. Please enter another one." << endl;
            }
        }
    }

    cout << "Enter description to add for that command... ";
    getchar();
    getline(cin, description);

    list.insertFront(command, description);
}

// allows user to remove command from list
template <class C, class D>
void removeCommand(List<C, D> &list)
{
    C command;
    cout << "Enter command to remove from list... ";
    cin >> command;
    list.deleteNode(command);
}

// finds list size
template <class C, class D>
int countCommands(List<C, D> &list)
{
    node<C, D> *cur = list.getHead();
    int listSize = 0;
    while(cur != nullptr)
    {
        listSize++;
        cur = cur->next;
    }

    return listSize;
}

// finds random command from list with its corresponding decription along with 2 other random descriptions
template <class C, class D>
void findRandCommand(List<C, D> &list, C &command, D &description1, string &description2, string &description3)
{
    int randNum = rand() % countCommands(list) + 1, i = 1;
    node<C, D> *cur = list.getHead();
    while(cur != nullptr && i != randNum)
    {
        cur = cur->next;
        i++;
    }
    command = cur->command;
    description1 = cur->description;

    int randNum2 = rand() % countCommands(list) + 1;
    while(randNum2 == randNum)
    {
        randNum2 = rand() % countCommands(list) + 1;
    }
    i = 1;
    cur = list.getHead();
    while(cur != nullptr && i != randNum2)
    {
        cur = cur->next;
        i++;
    }
    description2 = cur->description;

    int randNum3 = rand() % countCommands(list) + 1;
    while(randNum3 == randNum || randNum3 == randNum2)
    {
        randNum3 = rand() % countCommands(list) + 1;
    }
    i = 1;
    cur = list.getHead();
    while(cur != nullptr && i != randNum3)
    {
        cur = cur->next;
        i++;
    }
    description3 = cur->description;
}

// writes list to commands.csv file
template <class C, class D>
void writeCommands(List<C, D> &list)
{
    ofstream ost;
    ost.open("commands.csv");
    ost << list;

    ost.close();
}