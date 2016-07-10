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
