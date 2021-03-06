/******************************************************************************

Game object acts as the game manager for the masterMind game. The constructor
requires the difficulty as an argument (an integer from 1-4) and then creates
the solution and sets the member variables. Game object keeps track of the
number of players guesses, max tries, and win conditions. Game object also contains
the functionality to update whether or not the game is complete or not.

******************************************************************************/
#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>

// Instead of using a pair<int, int> to keep track of the hits and near hits
// I decided to just make a structure that held those values in unambiguous
// variables.
struct HitSummary
{
    unsigned int hits;
    unsigned int nearHits;
};

class Game
{
public:

    Game(int difficulty, std::string validChars);
    // Precondition: validChars MUST contain only 4 characters.
    // Constructor sets m_attempts to 0, m_isGameWon to false, as well as
    // generates the solution by calling private function generateSolution()
    // it then maps a table based on the solution. Sets difficulty based on
    // arguments value 1-4.

    void guessStatus(std::string guess);
    // Iterates through each character of the guess. If the character matches
    // the solution in both character and index, we increment Hits. Otherwise,
    // checks if the character exists on the solution table and increment
    // nearHit if true.

    void updateGameWon();
    // Sets game is won flag to true if the hits are equal to the length of the
    // solution.

    bool isGameComplete();
    // Returns true if game is won or attempts exceed max tries


//////////////////////////////GETTERS///////////////////////////////////////////

    bool isGameWon();
    unsigned int getSolutionLength();
    unsigned int getAttempts();
    unsigned int getMaxAttempts();
    unsigned int getDifficulty();
    std::string getSolution();
    HitSummary getResults();

//////////////////////////////SETTERS///////////////////////////////////////////

    void incrementAttempt();

private:

    void difficultyScaler();
    // Sets maxTries and Solution lengths values to scale with difficulty.

    std::string generateHardSolution();
    // uses rand() to pick a number between 0-3 and then switch off that number.
    // Can allow for duplicated characters, for use in hard and expert mode.

    std::string generateBasicSolution();
    // Precondition: the solutionLength MUST match the length of the valid
    // chars.
    // Picks from valid Chars only once to ensure no duplicates are in the
    // solution.

    std::map<char, bool> createSolutionTable(std::string solution);
    // Iterates through solution, and stores the character as a key
    // and sets it's value as true. Returns the map of the solution.

//////////////////////////////VARIABLES/////////////////////////////////////////

    unsigned int m_attempts;
    unsigned int m_maxAttempts;
    unsigned int m_solutionLength;
    unsigned int m_difficulty; // Ranges 1 - 4
    HitSummary m_results; // Holds the results of the previous guess.
    std::string m_solution;
    std::string m_validChars;
    std::map<char, bool> m_solutionTable;
    bool m_isGameWon;
};


#endif // GAME_H
