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
