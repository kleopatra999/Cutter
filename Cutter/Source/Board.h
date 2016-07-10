//
// Copyright 2016 David Roller
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//  http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef __Cutter__Board__
#define __Cutter__Board__

// ***************************************************************************
// Include Files
// ***************************************************************************
#include <vector>
#include "Enemy.h"

// ***************************************************************************
// Class definition
// ***************************************************************************
class Board
{
public:
    /// Constructor
    Board(unsigned int screenWidth, unsigned int screenHeight);

    /// Copy-Constructor
    Board(const Board& board);

    /// Assignment operator
    void operator=(const Board& board);

public:
    /// Bosrd element types
    enum Element
    {
		BackgroundElement,
        BoardElement,
        PlayerElement,
        EnemyElement
    };

    /// Defines a positions on the board
    struct Position
    {
        unsigned int x;
        unsigned int y;
    };

public:
	/// Initialize the position of the player
    void InitializePlayer();

    /// Initialize the position of the enemies
    void InitializeEnemies();

    /// Get the actual position of the player
    Position getPlayer() const;

    /// Get the width of the board
	unsigned int getWidth() const;

    /// Get the height of the board
	unsigned int getHeight() const;

    /// Get the width of one board element
	unsigned int getElementWidth() const;

    /// Get the height of one board element
	unsigned int getElementHeight() const;

    /// Get the padding of the board
	unsigned int getBoardPadding() const;

    /// Update the positions of the enemies
	void updateEnemyPositions(bool& loose);

    /// Clear the board and re-initialize the player end enemies
    void clearBoard(unsigned int enemyCount);

    /// Kill an enemy and remove him from the board
    void killEnemy(unsigned int x, unsigned int y);

    /// Set the actual position of the player
    void setPlayer(unsigned int x, unsigned int y);

    /// Checks if the given position is on the board
    bool onBoard(unsigned int x, unsigned int y) const;

    /// Get the element type at a position on the board
    Element getElement(unsigned int x, unsigned int y) const;

    /// Set the element type at a position on the board
    void setElement(unsigned int x, unsigned int y, Element element);

private:
    /// Create the board vectors
    void createBoard();

private:
    const unsigned int m_ScreenWidth;
    const unsigned int m_ScreenHeight;

    const unsigned int m_ElementWidth;
    const unsigned int m_ElementHeight;

    const unsigned int m_BoardPadding;

    Position m_PlayerPos;
    unsigned int m_Enemies;
    std::vector<Enemy> m_EnemyPos;
    std::vector<std::vector<Element>> m_Board;
};

#endif /* defined(__Cutter__Board__) */
