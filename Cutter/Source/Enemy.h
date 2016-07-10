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

#ifndef __Cutter__Enemy__
#define __Cutter__Enemy__

// ***************************************************************************
// Include Files
// ***************************************************************************

// ***************************************************************************
// Class definition
// ***************************************************************************
class Enemy
{
public:
    /// The borders of the board the enemy can touch
    enum Border
    {
        TOP, BOTTOM,
        RIGHT, LEFT
    };

    /// The direction in which a player or enemy can move
    enum PlayerDirection
    {
        STOP,
        EAST, WEST, NORTH, SOUTH,
        NORTH_WEST, SOUTH_WEST, NORTH_EAST, SOUTH_EAST
    };

public:
    /// Constructor
    Enemy(PlayerDirection direction,
          unsigned int x, unsigned int y);

    /// Copy-Constructor
    Enemy(const Enemy& board);

    /// Assigment operator
    void operator=(const Enemy& board);
    
public:
    /// Update the position of the enemy
    void update();

    /// Get the X position of the enemy
    unsigned int getX();

    /// Get the Y position of the enemy
    unsigned int getY();

    /// Change the move direction of the enemy
    void changeDirection(Border border);

private:
    PlayerDirection m_Direction;
    unsigned int m_x;
    unsigned int m_y;
};

#endif /* defined(__Cutter__Enemy__) */
