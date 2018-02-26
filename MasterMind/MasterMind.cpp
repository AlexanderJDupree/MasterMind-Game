/******************************************************************************

MasterMind.cpp contains the implementation of the Game class defined in
MasterMind.h

******************************************************************************/

#include <cstdlib>
#include <ctime>
#include "MasterMind.h"

Game::Game(int difficulty, std::string validChars)
{
    m_attempts = 0;
    m_isGameWon = false;
    m_validChars = validChars;

    m_difficulty = difficulty;
    difficultyScaler();
    // sets solution length and max tries based on difficulty.
    if (m_difficulty <= 2) { m_solution = generateBasicSolution(); }
    else { m_solution = generateHardSolution(); }
    m_solutionTable = createSolutionTable(m_solution);
}

void Game::guessStatus(std::string guess)
{
    m_results = (HitSummary){.hits = 0, .nearHits = 0};
    // clear previous results

    for (unsigned int i = 0; i < m_solution.length(); i++)
    {
        if (guess[i] == m_solution[i])
        {
            m_results.hits += 1;
        }
        else
        {
            if (m_solutionTable[guess[i]])
            {
                m_results.nearHits += 1;
            }
        }
    }
    return;
}

void Game::updateGameWon()
{
    if (m_results.hits == m_solutionLength)
    {
        m_isGameWon = true;
    }
    return;
}

bool Game::isGameComplete()
{
    if (m_isGameWon || m_attempts >= m_maxAttempts)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///////////////////////////////// GETTERS /////////////////////////////////////

bool Game::isGameWon()
{
    return m_isGameWon;
}

unsigned int Game::getSolutionLength()
{
    return m_solutionLength;
}

unsigned int Game::getAttempts()
{
    return m_attempts;
}

unsigned int Game::getMaxAttempts()
{
    return m_maxAttempts;
}

unsigned int Game::getDifficulty()
{
    return m_difficulty;
}

std::string Game::getSolution()
{
    return m_solution;
}

HitSummary Game::getResults()
{
    return m_results;
}


//////////////////////////////// SETTERS //////////////////////////////////////

void Game::incrementAttempt()
{
    m_attempts += 1;
    return;
}

//////////////////////////////// PRIVATE //////////////////////////////////////

void Game::difficultyScaler()
{
    switch (m_difficulty)
    {
        case 1 : m_maxAttempts = 6; m_solutionLength = 3; break;
        case 2 : m_maxAttempts = 7; m_solutionLength = 4; break;
        case 3 : m_maxAttempts = 8; m_solutionLength = 5; break;
        case 4 : m_maxAttempts = 10; m_solutionLength = 6; break;
        default : m_maxAttempts = 5; m_solutionLength = 4;
        // default case sets difficulty to 2. Medium difficulty.
    }
    return;
}

std::string Game::generateHardSolution()
{
    std::string solution = "";
    std::srand(time(NULL));
    for (unsigned int i = 0; i < m_solutionLength; i++)
    {
        switch (rand() % 4)
        {
            case 0 : solution += m_validChars[0]; break;
            case 1 : solution += m_validChars[1]; break;
            case 2 : solution += m_validChars[2]; break;
            case 3 : solution += m_validChars[3]; break;
            default : break; // Default case should be impossible.
        }
    }
    return solution;
}

std::string Game::generateBasicSolution()
{
    std::string solution = "";
    std::string validChars = m_validChars;
    std::srand(time(NULL));

    int counter = m_solutionLength;
    while (counter > 0)
    {
        int index = rand() % counter;
        solution += validChars[index];
        validChars.erase(index, 1);
        counter --;
    }
    return solution;
}

std::map<char, bool> Game::createSolutionTable(std::string solution)
{
    std::map<char, bool> solutionTable;
    for (unsigned int i = 0; i < solution.length(); i++)
    {
        solutionTable[solution[i]] = true;
    };
    return solutionTable;
}
