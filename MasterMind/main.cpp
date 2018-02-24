/******************************************************************************
* File: masterMind_driver.cpp
* Description: TODO Description
* Author: Alexander DuPree, Jake Bickle
* Date: 2/24/2018
* Compiler: GNU CC Compiler 5.4.0
* Modifications:
    - Added getInput()
    - Added two checks, isValidInput() which calls on isValidChars() to return
        a boolean
    - Created an encompassing lowercase function, lowerCase()
    - Added resetInputStream() for bad inputs
    - Started game loop in main()

    In the header file
    - Added struct HitSummary to keep track of hits and near hits.
    - Finished Constructor
    - Added private function generateSolution()
    - Added private function createSolutionTable(), makes the hash table for
      the solution.
    - Finished public function guessStatus().
    - Added public function updateGameWon()
    - Added public function isGameComplete()
    - Added getters for isGameWon, solution length, solution, and results.
    - Added incrementAttempt()

******************************************************************************/

#include <iostream>
#include "MasterMind.h"

#define LOG(x) std::cout << x << std::endl;

using namespace std;

void intro(); // TODO jake
void displayResults(); // TODO  jake
void gameSummary(); // TODO jake
void resetInputStream();
// resets failure state and discards bad characters on any input that failed.

string lowerCase(string input);
// std::string doesn't contain a encompassing lowercase function. So I made one.
string getInput(string prompt);

bool isValidInput(unsigned int length, string input, const string &validChars);
bool isValidChars(string input, const string &validChars);

int main()
{
    const string validChars = "bgyr";

    do {
        Game game; // instantiates new game manager object.
        unsigned int solutionLength = game.getSolutionLength();
        do {
        string guess;
        guess = getInput("Enter your guess:  ");
        if (isValidInput(solutionLength, guess, validChars))
        {
            game.guessStatus(guess);
            game.updateGameWon();
            game.incrementAttempt();
            // TODO display results
        }
        else
        {
            // TODO bad input, print error message
        }
        } while (!game.isGameComplete());
        // TODO Game summary
    } while (false); // TODO while user wants to play again.


    return 0;
}

void resetInputStream()
{
    // get rid of failure state
    cin.clear();

    // discard 'bad' characters
    cin.ignore(100, '\n');
    return;
}

string lowerCase(string input)
{
    string newString = "";
    for (unsigned int i = 0; i < input.length(); i++)
    {
        newString += tolower(input[i]);
    }
    return newString;
}

string getInput(string prompt)
{
    string userInput;
    cout << prompt;
    cin >> userInput;
    userInput = lowerCase(userInput);
    return userInput;
}

bool isValidInput(unsigned int length, string input, const string &validChars)
{
    if (input.length() == length && isValidChars(input, validChars))
    {
        return true;
    }
    else
    {
        resetInputStream();
        return false;
    }
}

bool isValidChars(string input, const string &validChars)
{
    map<char, bool> charTable;
    for (unsigned int i = 0; i < validChars.length(); i++)
    {
        charTable[validChars[i]] = true;
    }
    for (unsigned int i = 0; i < input.length(); i++)
    {
        if (!charTable[input[i]]) { return false;}
    }
    return true;
}
