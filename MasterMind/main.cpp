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
    - Added displayResults()
    - Added gameSummary()

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
    - Added difficultyScaler
    - Added various getters and setters


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
    - Finished difficulty scaler, now called from the constructor.

    2/24/2018
    - removed merge conflicts again
    - added getDifficulty in main, is called before game object is instantiated

******************************************************************************/

#include <iostream>
#include "MasterMind.h"

#define LOG(x) std::cout << x << std::endl;

using namespace std;

void intro();
void displayResults(Game &game);
// Displays hits, near hits, misses, and attempts remaining.
void gameSummary(Game &game);
// Displays correct solution, whether player has one or lost, attempts, and
// the difficulty.
void displayErrorMessage(int solutionLength, string validChars);
void resetInputStream();
// resets failure state and discards bad characters on any input that failed.
int getGameDifficulty();
// Asks user what difficulty setting to play on.
string lowerCase(string input);
// std::string doesn't contain a encompassing lowercase function. So I made one.
string getInput(string prompt);
bool playerReplay();
bool isValidInput(unsigned int length, string input, const string &validChars);
bool isValidChars(string input, const string &validChars);

int main()
{
    const string validChars = "bgyr";
    int difficulty;
    bool playerWantsToReplay;

    intro();

    do
    {
        difficulty = getGameDifficulty();
        Game game(difficulty); // instantiates new game manager object.

        int solutionLength = game.getSolutionLength();
        cout << "\nYour solution contains " << solutionLength << " characters.";

        LOG(game.getSolution()); // DEBUG LOG
        do
        {
            string guess;
            guess = getInput("Enter your guess:  ");
            if (isValidInput(solutionLength, guess, validChars))
            {
                game.guessStatus(guess);
                game.updateGameWon();
                game.incrementAttempt();
                displayResults(game); // game is passed by reference

            }
            else { displayErrorMessage(solutionLength, validChars); }
        } while (!game.isGameComplete());

        gameSummary(game);

    } while (playerReplay());
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

void gameSummary(Game &game)
{
    string solution = game.getSolution();
    int difficultyNum = game.getDifficulty();
    unsigned int attempts = game.getAttempts();
    unsigned int maxAttempts = game.getMaxAttempts();
    bool win = game.isGameWon();

    string difficulty;
    switch(difficultyNum)
    {
        case 1: difficulty = "EASY"; break;
        case 2: difficulty = "MEDIUM"; break;
        case 3: difficulty = "HARD"; break;
        case 4: difficulty = "EXPERT"; break;
    }

    cout << string(100 , '\n')
         << "\n\n\n\t\t\t\t\tThe solution is: " << solution;

    if(win)
        cout << "\n\n\t\t\tCONGRATULATIONS, YOU'VE WON!";
    else
        cout << "\n\n\t\t\tYou've LOST!";

    cout << "\n\t\t\tDIFFICULTY: " << difficulty
         << "\n\t\t\tIt took you " << attempts << " out of " << maxAttempts
         << " attempts.\n\n\n\n\n\n\n\n\n\n";

    /*
    THE SOLUTION IS: YRGB

    CONGRATULATIONS, YOU'VE WON!
    Difficulty: EASY/NORMAL/HARD/EXPERT

    It took you blank out of blank attempts.

    */
}

void displayErrorMessage(int solutionLength, string validChars)
{
    cout << "\aInput must be " << solutionLength << " characters long";
    cout << " and only contain the letters: ";
    for (unsigned int i = 0; i < validChars.length(); i++)
        cout << validChars[i] << " ";

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

int getGameDifficulty()
{
    int difficulty;
    cout << "1. Easy\n2. Medium\n3. Hard\n4. EXPERT!" << endl;
    cout << "Enter the number of your chosen difficulty:  ";
    cin >> difficulty;
    if (difficulty > 4 || difficulty < 1)
    {
        cout << "Unrecognized input, defaulting to Medium difficulty.\n\n";
        resetInputStream(); // In case user inputs a character.
        return 2;
    }
    cout << "Good luck!\n" << endl;
    return difficulty;
}

string lowerCase(string input)
{
    string newString = "";
    for (unsigned int i = 0; i < input.length(); i++)
        newString += tolower(input[i]);
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

bool playerReplay()
{
    char ch;
    cout << "\n\n\nWould you like to replay the game?"
         << "\nEnter 'y' to replay, or 'n' to quit:  ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
        return true;
    return false;
}
