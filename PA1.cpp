#include "PA1.h"

// displays rules of the game
void displayGameRules()
{
    cout << "In this game, you will be given a random Linux command with the goal of choosing the correct description for it out of the 3 descriptions that will be displayed. A correct choice is worth 1 point and an incorrect choice is -1 point (negative points are possible)." << endl;
}

// inserts profile at front of profile array
void insertFrontArray(profile profiles[], profile p, int size)
{
    for(int i = size; i >= 0; i--)
    {
        // shifts each profile over one index 
        profiles[i] = profiles[i - 1];
    }
    profiles[0] = p;
}

// finds size of profile array
int findSizeArray(profile profiles[])
{
    int size = 0, i = 0;
    while(profiles[i].name != "")
    {
        size++;
        i++;
    }

    return size;
}

// loads profile array 
void loadArray(profile profiles[])
{
    ifstream ifs("profiles.csv");
    // while not at end of file
    while(!ifs.eof())
    {
        string line;
        getline(ifs, line);

        // find the position of the comma
        size_t pos = line.find(",");
        if (pos != string::npos) 
        {
            // extract command and description
            string name = line.substr(0, pos);
            string points = line.substr(pos + 1); // skip the comma

            profile p;
            p.name = name;
            p.points = stoi(points);

            insertFrontArray(profiles, p, findSizeArray(profiles));
        }
    }
}

// writes profiles from profile array to profiles.csv file
void writeProfiles(profile profiles[])
{
    ofstream ost("profiles.csv");
    int i = 0;
    while(i < findSizeArray(profiles))
    {
        ost << profiles[i].name << ", " << profiles[i].points << endl;
        i++;
    }

    ost.close();
}