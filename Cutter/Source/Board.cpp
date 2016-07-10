//
// Cutter
//
// Copyright (C) 2014 David Roller
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//

// ***************************************************************************
// Include Files
// ***************************************************************************
#include "Board.h"
#include <cstdlib>
#include <ctime>

//////////////////////////////////////////////////////////////////////////////
/// Constructor
//////////////////////////////////////////////////////////////////////////////
Board::Board(unsigned int screenWidth, unsigned int screenHeight) :
	m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight),
	m_ElementWidth(10), m_ElementHeight(10), m_BoardPadding(50)
{
    m_Enemies = 1;
    createBoard();
    clearBoard(1);
}

//////////////////////////////////////////////////////////////////////////////
/// Copy-Constructor
//////////////////////////////////////////////////////////////////////////////
Board::Board(const Board& board) :
    m_ScreenWidth(board.m_ScreenWidth), m_ScreenHeight(board.m_ScreenHeight),
    m_ElementWidth(10), m_ElementHeight(10), m_BoardPadding(50)
{
    m_Enemies = board.m_Enemies;
	m_Board = board.m_Board;
    m_PlayerPos = board.m_PlayerPos;
    m_EnemyPos = board.m_EnemyPos;
}

//////////////////////////////////////////////////////////////////////////////
/// Assignment operator
//////////////////////////////////////////////////////////////////////////////
void Board::operator=(const Board& board)
{
    m_Enemies = board.m_Enemies;
	m_Board = board.m_Board;
    m_PlayerPos = board.m_PlayerPos;
    m_EnemyPos = board.m_EnemyPos;
}

//////////////////////////////////////////////////////////////////////////////
/// Initialize the position of the player
//////////////////////////////////////////////////////////////////////////////
void Board::InitializePlayer()
{
    m_PlayerPos.x = static_cast<unsigned int>(m_Board.size() / 2);
    m_PlayerPos.y = (m_BoardPadding / m_ElementHeight) - 1;
    m_Board[m_PlayerPos.x][m_PlayerPos.y] = Element::PlayerElement;
}

//////////////////////////////////////////////////////////////////////////////
/// Initialize the position of the enemies
//////////////////////////////////////////////////////////////////////////////
void Board::InitializeEnemies()
{
    m_EnemyPos.clear();

    srand(static_cast<int>(time(NULL)));
	for (unsigned int i = 0; i != m_Enemies; ++i)
    {
        unsigned int padElemX = m_BoardPadding / m_ElementWidth;
        unsigned int maxX = static_cast<unsigned int>(m_Board.size() - 2 * padElemX);
    	unsigned int x = (rand() % (maxX - padElemX)) + padElemX;

        unsigned int padElemY = m_BoardPadding / m_ElementHeight;
        unsigned int maxY = static_cast<unsigned int>(m_Board[0].size() - 2 * padElemY);
    	unsigned int y = (rand() % (maxY - padElemY)) + padElemY;

        Enemy::PlayerDirection dir = Enemy::PlayerDirection::STOP;
        unsigned int rndDir = rand() % 3;
        if(rndDir == 0)
        {
			dir = Enemy::PlayerDirection::SOUTH_EAST;
        }
        else if(rndDir == 1)
        {
			dir = Enemy::PlayerDirection::SOUTH_WEST;
        }
        else if(rndDir == 2)
        {
			dir = Enemy::PlayerDirection::NORTH_EAST;
        }
        else if(rndDir == 3)
        {
			dir = Enemy::PlayerDirection::NORTH_WEST;
        }
    	Enemy enemy(dir, x, y);
    	m_Board[x][y] = Element::EnemyElement;
		m_EnemyPos.push_back(enemy);
    }
}

//////////////////////////////////////////////////////////////////////////////
/// Update the positions of the enemies
//////////////////////////////////////////////////////////////////////////////
void Board::updateEnemyPositions(bool& loose)
{
    for(unsigned int i = 0; i != m_EnemyPos.size(); ++i)
    {
        Enemy ene = m_EnemyPos[i];
		ene.update();

        if(m_Board[ene.getX()][ene.getY()] == Element::BackgroundElement)
        {
            Enemy::Border border = Enemy::Border::BOTTOM;
            if(m_Board[ene.getX()][ene.getY()-1] == Element::BoardElement)
            {
                border = Enemy::Border::BOTTOM;
            }
            if(m_Board[ene.getX()][ene.getY()+1] == Element::BoardElement)
            {
                border = Enemy::Border::TOP;
            }
            if(m_Board[ene.getX()+1][ene.getY()] == Element::BoardElement)
            {
                border = Enemy::Border::LEFT;
            }
            if(m_Board[ene.getX()-1][ene.getY()] == Element::BoardElement)
            {
                border = Enemy::Border::RIGHT;
            }
            m_EnemyPos[i].changeDirection(border);
        }
        else
        {
            if(m_Board[ene.getX()][ene.getY()] == Element::PlayerElement)
            {
                loose = true;
            }
            m_Board[m_EnemyPos[i].getX()][m_EnemyPos[i].getY()] = Element::BoardElement;
            m_EnemyPos[i].update();
            m_Board[ene.getX()][ene.getY()] = Element::EnemyElement;
        }
    }

    bool won = (m_EnemyPos.size() == 0);
    if(won)
    {
        clearBoard(m_Enemies +1);
    }
}

//////////////////////////////////////////////////////////////////////////////
/// Create the board vectors
//////////////////////////////////////////////////////////////////////////////
void Board::createBoard()
{
    unsigned int height = m_ScreenHeight / m_ElementHeight;
	unsigned int width = m_ScreenWidth / m_ElementWidth;

    for(unsigned int x = 0; x != width; ++x)
    {
        m_Board.push_back(std::vector<Element>());
		for(unsigned int y = 0; y != height; ++y)
        {
            m_Board[x].push_back(Element::BackgroundElement);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
/// Clear the board and re-initialize the player end enemies
//////////////////////////////////////////////////////////////////////////////
void Board::clearBoard(unsigned int enemyCount)
{
    m_Enemies = enemyCount;
    
    unsigned int height = getHeight();
	unsigned int width = getWidth();

    for(unsigned int x = 0; x != width; ++x)
    {
        unsigned int xPos = x * m_ElementWidth;
		for(unsigned int y = 0; y != height; ++y)
        {
            unsigned int yPos = y * m_ElementHeight;
            if(xPos < m_BoardPadding || xPos > (m_ScreenWidth-m_BoardPadding) ||
               yPos < m_BoardPadding || yPos > (m_ScreenHeight-m_BoardPadding))
            {
                m_Board[x][y] = Board::Element::BackgroundElement;
            }
            else
            {
                m_Board[x][y] = Board::Element::BoardElement;
            }
        }
    }
    InitializePlayer();
    InitializeEnemies();
}

//////////////////////////////////////////////////////////////////////////////
/// Kill an enemy and remove him from the board
//////////////////////////////////////////////////////////////////////////////
void Board::killEnemy(unsigned int x, unsigned int y)
{
	for (unsigned int i = 0; i != m_EnemyPos.size(); ++i)
    {
        Enemy& ene = m_EnemyPos[i];
        if(x == ene.getX() && y == ene.getY())
        {
            m_EnemyPos.erase(m_EnemyPos.begin() + i);
            return;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
/// Get the width of the board
//////////////////////////////////////////////////////////////////////////////
unsigned int Board::getWidth() const
{
	return static_cast<unsigned int>(m_Board.size());
}

//////////////////////////////////////////////////////////////////////////////
/// Get the height of the board
//////////////////////////////////////////////////////////////////////////////
unsigned int Board::getHeight() const
{
    if(m_Board.size() <= 0)
    {
        return 0;
    }
    return static_cast<unsigned int>(m_Board[0].size());
}

//////////////////////////////////////////////////////////////////////////////
/// Get the actual position of the player
//////////////////////////////////////////////////////////////////////////////
Board::Position Board::getPlayer() const
{
	return m_PlayerPos;
}

//////////////////////////////////////////////////////////////////////////////
/// Get the width of one board element
//////////////////////////////////////////////////////////////////////////////
unsigned int Board::getElementWidth() const
{
    return m_ElementWidth;
}

//////////////////////////////////////////////////////////////////////////////
/// Get the padding of the board
//////////////////////////////////////////////////////////////////////////////
unsigned int Board::getBoardPadding() const
{
	return m_BoardPadding;
}

//////////////////////////////////////////////////////////////////////////////
/// Get the height of one board element
//////////////////////////////////////////////////////////////////////////////
unsigned int Board::getElementHeight() const
{
	return m_ElementHeight;
}

//////////////////////////////////////////////////////////////////////////////
/// Set the actual position of the player
//////////////////////////////////////////////////////////////////////////////
void Board::setPlayer(unsigned int x, unsigned int y)
{
	m_PlayerPos.x = x;
    m_PlayerPos.y = y;
}

//////////////////////////////////////////////////////////////////////////////
/// Checks if the given position is on the board
//////////////////////////////////////////////////////////////////////////////
bool Board::onBoard(unsigned int x, unsigned int y) const
{
    return true;
}

//////////////////////////////////////////////////////////////////////////////
/// Set the element type at a position on the board
//////////////////////////////////////////////////////////////////////////////
void Board::setElement(unsigned int x, unsigned int y, Element element)
{
	m_Board[x][y] = element;
}

//////////////////////////////////////////////////////////////////////////////
/// Get the element type at a position on the board
//////////////////////////////////////////////////////////////////////////////
Board::Element Board::getElement(unsigned int x, unsigned int y) const
{
	return m_Board[x][y];
}

