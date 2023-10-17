#include <map>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = {{"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"}};
    TwitterData *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }


    //
    // Your code goes here
    //

    // Map Scenario 1:
    cout << "Print SearchByName map:" << endl << endl;

    map<string, TwitterData> m;

    // stores values into map by username
    for(int i = 0; i < 5; i++)
    {
        m[twitter_data[i].getUserName()] = twitter_data[i];
    }

    map<string, TwitterData>::iterator itr;

    // Iterate through the std::map and print the key-value pairs line by line
    for (itr = m.begin(); itr != m.end(); ++itr) 
    {
        cout << "KEY: " << itr->first << ", VALUE: " << itr->second.print() << endl;
    }

    cout << endl;

    // Find username savage1 and print out the entire record
    for(itr = m.begin(); itr != m.end(); ++itr)
    {
        if(itr->first == "savage1")
        {
            cout << "Value to Delete: " << itr->second.print() << endl << endl;
        }
    }

    // remove savage1
    m.erase("savage1");

    for (itr = m.begin(); itr != m.end(); ++itr) 
    {
        cout << "KEY: " << itr->first << ", VALUE: " << itr->second.print()
             << '\n';
    }

    // Map Scenario 2:
    cout << endl << "Print SearchByEmail map:" << endl << endl;

    // create new map
    map<string, TwitterData> m2;

    // store data into map with email as key
    for(int i = 0; i < 5; i++)
    {
        m2[twitter_data[i].getEmail()] = twitter_data[i];
    }

    // iterate through map and print each record
    for (itr = m2.begin(); itr != m2.end(); ++itr) 
    {
        cout << "KEY: " << itr->first << ", VALUE: " << itr->second.print() << endl;
    }

    cout << endl;

    // find kat@gmail.com and print entire record
    for(itr = m2.begin(); itr != m2.end(); ++itr)
    {
        if(itr->first == "kat@gmail.com")
        {
            cout << "Value to Delete: " << itr->second.print() << endl << endl;
        }
    }

    // delete record form map 
    m2.erase("kat@gmail.com");

    for (itr = m2.begin(); itr != m2.end(); ++itr) 
    {
        cout << "KEY: " << itr->first << ", VALUE: " << itr->second.print() << endl;
    }

    return 0;
}