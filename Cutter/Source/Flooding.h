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
#ifndef __Cutter__Flooding__
#define __Cutter__Flooding__

// ***************************************************************************
// Include Files
// ***************************************************************************
#include "Board.h"

// ***************************************************************************
// Class definition
// ***************************************************************************
class Flooding
{
public:
    /// Contructor
    Flooding();

private:
    /// Copy-Contructor
    Flooding(const Flooding& board);

    /// Assigment operator
    void operator=(const Flooding& board);

public:
	/// Cut the smaller board section
    unsigned int cut(Board& board);

private:
    /// Flooding algorithm to determine the size of the board area
    unsigned int flooding(unsigned int x, unsigned int y, Board& board);

    /// Find the next position of a board element
    void findBoardPos(Board& board, Board::Position& boardPos);
};

#endif /* defined(__Cutter__Flooding__) */
