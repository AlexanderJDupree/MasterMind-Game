#include <cstdlib>
#include "MasterMind.h"

Game::Game()
{
    m_attempts = 0;
    m_maxAttempts = 5;
    m_isGameWon = false;
    m_solution = generateSolution();
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

void Game::difficultyScaler(unsigned int difficulty)
// TODO: NEEDS TWEEKING
{
    switch(m_difficulty)
    {
        case 1: m_maxAttempts = 5;
                m_solutionLength = 4;
                break;
        case 2: m_maxAttempts = 5;
                m_solutionLength = 4;
                break;
        case 3: m_maxAttempts = 5;
                m_solutionLength = 4;
                break;
        case 4: m_maxAttempts = 5;
                m_solutionLength = 4;
                break;
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

std::string Game::getSolution()
{
    return m_solution;
}

HitSummary Game::getResults()
{
    return m_results;
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

//////////////////////////////// SETTERS //////////////////////////////////////

void Game::incrementAttempt()
{
    m_attempts += 1;
    return;
}

void Game::setDifficulty(unsigned int difficulty)
{
    m_difficulty = difficulty;
}

//////////////////////////////// PRIVATE //////////////////////////////////////

std::string Game::generateSolution()
{
    std::string solution = "";
    for (unsigned int i = 0; i < m_solutionLength; i++)
    {
        switch (rand() % 4)
        {
            case 0 : solution += 'y'; break;
            case 1 : solution += 'r'; break;
            case 2 : solution += 'g'; break;
            case 3 : solution += 'b'; break;
            default : break; // Default case should be impossible.
        }
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
