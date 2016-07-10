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
#include "Enemy.h"

//////////////////////////////////////////////////////////////////////////////
/// Constructor
//////////////////////////////////////////////////////////////////////////////
Enemy::Enemy(PlayerDirection direction,
      unsigned int x, unsigned int y)
{
	m_Direction = direction;
    m_x = x;
    m_y = y;
}

//////////////////////////////////////////////////////////////////////////////
/// Copy-Constructor
//////////////////////////////////////////////////////////////////////////////
Enemy::Enemy(const Enemy& board)
{
	m_Direction = board.m_Direction;
    m_x = board.m_x;
    m_y = board.m_y;
}

//////////////////////////////////////////////////////////////////////////////
/// Assigment operator
//////////////////////////////////////////////////////////////////////////////
void Enemy::operator=(const Enemy& board)
{
	m_Direction = board.m_Direction;
    m_x = board.m_x;
    m_y = board.m_y;
}

//////////////////////////////////////////////////////////////////////////////
/// Update the position of the enemy
//////////////////////////////////////////////////////////////////////////////
void Enemy::update()
{
    switch (m_Direction)
    {
        case Enemy::PlayerDirection::SOUTH:
            m_y += 1;
            break;
        case Enemy::PlayerDirection::NORTH:
            m_y -= 1;
            break;
        case Enemy::PlayerDirection::EAST:
            m_x += 1;
            break;
        case Enemy::PlayerDirection::WEST:
            m_x -= 1;
            break;
        case Enemy::PlayerDirection::NORTH_WEST:
            m_x -= 1;
            m_y -= 1;
            break;
        case Enemy::PlayerDirection::SOUTH_WEST:
            m_x -= 1;
            m_y += 1;
            break;
        case Enemy::PlayerDirection::NORTH_EAST:
            m_x += 1;
            m_y -= 1;
            break;
        case Enemy::PlayerDirection::SOUTH_EAST:
            m_x += 1;
            m_y += 1;
            break;
        default:
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////
/// Get the X position of the enemy
//////////////////////////////////////////////////////////////////////////////
unsigned int Enemy::getX()
{
	return m_x;
}

//////////////////////////////////////////////////////////////////////////////
/// Get the Y position of the enemy
//////////////////////////////////////////////////////////////////////////////
unsigned int Enemy::getY()
{
	return m_y;
}

//////////////////////////////////////////////////////////////////////////////
/// Change the move direction of the enemy
//////////////////////////////////////////////////////////////////////////////
void Enemy::changeDirection(Enemy::Border border)
{
    switch (m_Direction)
    {
        case PlayerDirection::SOUTH:
            m_Direction = PlayerDirection::NORTH;
            break;
        case PlayerDirection::NORTH:
            m_Direction = PlayerDirection::SOUTH;
            break;
        case PlayerDirection::EAST:
            m_Direction = PlayerDirection::WEST;
            break;
        case PlayerDirection::WEST:
            m_Direction = PlayerDirection::EAST;
            break;
        case PlayerDirection::NORTH_WEST:
            if(border == Border::TOP)
            {
                m_Direction = PlayerDirection::SOUTH_WEST;
            }
            else
            {
                m_Direction = PlayerDirection::NORTH_EAST;
            }
            break;
        case PlayerDirection::SOUTH_WEST:
            if(border == Border::BOTTOM)
            {
                m_Direction = PlayerDirection::NORTH_WEST;
            }
            else
            {
                m_Direction = PlayerDirection::SOUTH_EAST;
            }
            break;
        case PlayerDirection::NORTH_EAST:
            if(border == Border::TOP)
            {
                m_Direction = PlayerDirection::SOUTH_EAST;
            }
            else
            {
                m_Direction = PlayerDirection::NORTH_WEST;
            }
            break;
        case PlayerDirection::SOUTH_EAST:
            if(border == Border::BOTTOM)
            {
                m_Direction = PlayerDirection::NORTH_EAST;
            }
            else
            {
                m_Direction = PlayerDirection::SOUTH_WEST;
            }
            break;
        default:
            break;
    }
}
