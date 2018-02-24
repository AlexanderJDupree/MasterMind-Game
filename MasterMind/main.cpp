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

    2/24/2018
    - Moved setm_difficulty to the constructor, because the difficulty
      should be known before the game object is instantiated.
    - TODO Add function in main.cpp that asks for user difficulty before game
      object is instantiated.
    - Added setDifficultyAttributes the sets the solution length and max tries
      based on the difficulty. This function is called during the construction
      of the Game object.
    - Moved intro() to be the first function after main(). Matches the index
      of the prototypes.
    - Added getter, getRemainingTries(). To be used in future displayResults()
    - Added function call to intro()
    - Added a new line to intro() that tells the user the solution length will
      change based on difficulty settings.
    - Added error message on bad inputs.

    2/24/2018
    - removed merge conflicts
    - finished the renaming of maxTries to maxAttempts
    - removed #include <string> from main. It's already in the header file.

******************************************************************************/

#include <iostream>
#include "MasterMind.h"

#define LOG(x) std::cout << x << std::endl;

using namespace std;

void intro();
void displayResults(Game &game);
void gameSummary(); // TODO jake
void displayErrorMessage(int solutionLength, string validChars);
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

    intro();

    do {
        Game game(2); // instantiates new game manager object.
        int solutionLength = game.getSolutionLength();
        do {

        string guess;
        guess = getInput("Enter your guess:  ");
        if (isValidInput(solutionLength, guess, validChars))
        {
            game.guessStatus(guess);
            game.updateGameWon();
            game.incrementAttempt();
            displayResults(game);
            // game is passed by reference
        }
        else { displayErrorMessage(solutionLength, validChars); }
        } while (!game.isGameComplete());
        // TODO Game summary
    } while (false); // TODO while user wants to play again.
    return 0;
}

void intro()
{
    cout << "\t\tMASTER MIND"
         << "\n\n\tAUTHORS: Alex Dupree, Jacob Bickle"
         << "\n\n\tCREATED: 2/24/2018"

         << "\n\nIn this game, the computer will randomly generate (n) colors:"
         << "\nThe amount of colors will depend of the difficulty you choose."
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
         << "\n\n\n";

    cout << endl;
    return;
}

void displayResults(Game &game)
{
    unsigned int hits = game.getResults().hits;
    unsigned int nearHits = game.getResults().nearHits;
    unsigned int misses = game.getSolution().length() - (hits + nearHits);

    cout << "\n---=============---\n"
         << "HITS:\t\t" << hits << '\n'
         << "NEAR HITS:\t" << nearHits << '\n'
         << "MISSES: \t" << misses << '\n'
         << "ATTEMPTS:\t" << game.getAttempts() << '/' << game.getMaxAttempts()
         << "\n---=============---\n";
}

void displayErrorMessage(int solutionLength, string validChars)
{
    cout << "Input must be " << solutionLength << " characters long.";
    cout << " And only contain the letters: ";
    for (unsigned int i = 0; i < validChars.length(); i++)
    {
        cout << validChars[i] << " ";
    }
    cout << endl << endl;
    return;
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
