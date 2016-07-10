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
#include "Flooding.h"

//////////////////////////////////////////////////////////////////////////////
/// Contructor
//////////////////////////////////////////////////////////////////////////////
Flooding::Flooding()
{
    
}

//////////////////////////////////////////////////////////////////////////////
/// Cut the smaller board section
//////////////////////////////////////////////////////////////////////////////
unsigned int Flooding::cut(Board& board)
{
	unsigned int snakeScore = 0;
    for(unsigned int x = 0; x != board.getWidth(); ++x)
    {
		for(unsigned int y = 0; y != board.getHeight(); ++y)
        {
            if(board.getElement(x, y) == Board::Element::PlayerElement)
            {
				board.setElement(x, y, Board::Element::BackgroundElement);
                ++snakeScore;
            }
        }
    }

    if(snakeScore < 2)
    {
        // Do not count steps without cutting land
        // E.g. player moves on the background
        snakeScore = 0;
    }

    Board floodingBoard = board;

    Board::Position floodingStartFirst;
    findBoardPos(floodingBoard, floodingStartFirst);
    unsigned int first = flooding(floodingStartFirst.x,
                                  floodingStartFirst.y,
                                  floodingBoard);

    Board::Position floodingStartSecond;
    findBoardPos(floodingBoard, floodingStartSecond);
    unsigned int second = flooding(floodingStartSecond.x,
                                   floodingStartSecond.y,
                                   floodingBoard);

    if(first < second)
    {
		return snakeScore + flooding(floodingStartFirst.x,
                        			 floodingStartFirst.y,
                        			 board);
    }
    else
    {
		return snakeScore + flooding(floodingStartSecond.x,
                        			 floodingStartSecond.y,
                        			 board);
    }
}

//////////////////////////////////////////////////////////////////////////////
/// Find the next position of a board element
//////////////////////////////////////////////////////////////////////////////
void Flooding::findBoardPos(Board& board, Board::Position& boardPos)
{
    for(unsigned int x = 0; x != board.getWidth(); ++x)
    {
		for(unsigned int y = 0; y != board.getHeight(); ++y)
        {
            if(board.getElement(x, y) == Board::Element::BoardElement)
            {
                boardPos.x = x;
                boardPos.y = y;
                return;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
/// Flooding algorithm to determine the size of the board area
//////////////////////////////////////////////////////////////////////////////
unsigned int Flooding::flooding(unsigned int x, unsigned int y, Board& board)
{
    if(board.getWidth() == 0 || board.getWidth() <= x ||
       board.getHeight() == 0 || board.getHeight() <= y ||
       board.getElement(x, y) == Board::Element::BackgroundElement)
    {
        return 0;
    }

    if(board.getElement(x, y) == Board::Element::EnemyElement)
    {
		board.killEnemy(x, y);
    }
    else if(board.getElement(x, y) != Board::Element::BoardElement)
    {
        return 0;
    }

    int count = 0;

    board.setElement(x, y, Board::Element::BackgroundElement);
    count = count + 1;

    count += flooding(x+1, y, board);
    count += flooding(x-1, y, board);
    count += flooding(x, y+1, board);
    count += flooding(x, y-1, board);

	return count;
}
