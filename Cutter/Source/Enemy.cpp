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
