// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <deque>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    
    std::deque<char> fab;
    for (unsigned int i = 0; i < floating.length(); i++)
    {
        fab.push_back(floating[i]);
    }
    int blanks = 0;
    for (unsigned int i = 0; i < in.length(); i++)
    {
        if (in[i] == '-') blanks++;
    }
    for (unsigned int i = 0; i < blanks - floating.length(); i++)
    {
        fab.push_back('*');
    }

    std::set<std::string> answers;
    wordleHelper(in, fab, dict, "", answers);


    return answers;

}

void wordleHelper(
    const std::string& in,
    std::deque<char> fab,
    const std::set<std::string>& dict,
    //unsigned int floa,
    std::string match,
    std::set<std::string>& answers)
{
    
    if (match.length() >= in.length())
    {
        if (dict.find(match) != dict.end()) 
        {
            answers.insert(match);
            //std::cout << match << std::endl;
            return;
        }
        else return;
    }

    int index = match.length();

    //"ab"
    //"--c--"

    if (in[index] != '-')
    {
        wordleHelper(in, fab, dict, match+in[index], answers);
    }
    else
    {
        string alph = "abcdefghijklmnopqrstuvwxyz";
        
        for (unsigned int i =0; i < fab.size(); i++)
        {
            char c = fab.front();
            fab.pop_front();
            if (c != '*') wordleHelper(in, fab, dict, match+c, answers);
            else
            {
                for (unsigned int i = 0; i < alph.length(); i++) wordleHelper(in, fab, dict, match+alph[i], answers);
            }

            fab.push_back(c);
            //if (c == '*') break;
        }

    }

    return;



}
