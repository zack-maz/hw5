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
    
    std::deque<char> fab; //floating char and blanks deque
    for (unsigned int i = 0; i < floating.length(); i++)
    {
        fab.push_back(floating[i]); //push all floating points
    }
    int blanks = 0;
    for (unsigned int i = 0; i < in.length(); i++)
    {
        if (in[i] == '-') blanks++; //count the number of blanks
    }
    for (unsigned int i = 0; i < blanks - floating.length(); i++)
    {
        fab.push_back('*'); //push * for # of blanks into fab
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
    
    if (match.length() >= in.length()) //if our word is the right length, it could be an answer
    {
        if (dict.find(match) != dict.end()) //if its in dict
        {
            answers.insert(match); //add to answers
            return;
        }
        else return;
    }

    int index = match.length(); //whats our current index in the word as we're building

    //"ab"
    //"--c--"

    if (in[index] != '-') //fixed character, add it to match
    {
        wordleHelper(in, fab, dict, match+in[index], answers);
    }
    else
    {
        string alph = "abcdefghijklmnopqrstuvwxyz"; //used for going through letters
        
        for (unsigned int i =0; i < fab.size(); i++)
        {
            char c = fab.front(); //check floating char or blank
            fab.pop_front();
            if (c != '*') wordleHelper(in, fab, dict, match+c, answers); //check w/ floating char
            else
            {
                //check any letter
                for (unsigned int i = 0; i < alph.length(); i++) wordleHelper(in, fab, dict, match+alph[i], answers);
            }

            fab.push_back(c); //add back into fab for next char position check
        }

        //basically we have x missing spots, which could either be a blank or a floating char
        //using the deque, we check to fill in everything

    }

    return;



}
