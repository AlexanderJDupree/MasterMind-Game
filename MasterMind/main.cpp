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

void intro();
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

/*
void displayResults()
// Needs the struct as an arguement, but can't reference struct HitSummary
// in MasterMind.h from main.cpp
{
    unsigned int hits = results.hits;
    unsigned int nearHits = results.nearHits
    unsigned int misses = length(Game.getm_solution) - (hits + nearHits)

    cout << "\n==========\n"
         << "HITS:\t\t" << hits << '\n'
         << "NEAR HITS:\t" << nearHits << '\n'
         << "MISSES: \t" << misses << '\n'
         << "==========\n"
}
*/

void intro()
{
    cout << "\t\tMASTER MIND"
         << "\n\n\tAUTHORS: Alex Dupree, Jacob Bickle"
         << "\n\n\tCREATED: 2/24/2018"

         << "\n\nIn this game, the computer will randomly generate four colors:"
         << "\nRed (r), Green (g), Blue (b), and Yellow (y)."
         << "\nYour goal is to guess which order the computer has sorted the"
         << "\ncolors within a certain amount of attempts. "

         << "\n\nTo help you out, every guess will provide you feed back."
         << "\nA \"miss\" will mean that a color you specified is not apart"
         << "\nof the solution. A \"near hit\" means that a color you specified"
         << "\nis apart of the solution, but not in the correct location."
         << "\nA \"hit\" means a color you specified is in the correct location."

         << "\n\n\t\tEXAMPLE"
         << "\n\tCOMPUTER: rggy"
         << "\n\tPLAYER:   yrgb"
         << "\n\nThe player would receive one hit, two near hits, and one miss."
         << "\n\n\n\n";

         << "\n\n"
}
