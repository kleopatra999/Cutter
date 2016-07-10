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
