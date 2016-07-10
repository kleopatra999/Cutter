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
#include "SDL.h"
#include "SDL_ttf.h"
#include "Board.h"
#include "Enemy.h"
#include "Flooding.h"

#include <sstream>
#include <string>

#ifdef WIN32
#include <Windows.h>
#endif

// ***************************************************************************
// Global definitions
// ***************************************************************************

//The attributes of the screen
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const double PLAYER_SPEED = 40;

// ***************************************************************************
// Function implementation
// ***************************************************************************

//////////////////////////////////////////////////////////////////////////////
/// Render the message we want to display to a texture for drawing
///
/// @param message The message we want to display
/// @param fontFile The font we want to use to render the text
/// @param color The color we want the text to be
/// @param fontSize The size we want the font to be
/// @param renderer The renderer to load the texture in
///
/// @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
//////////////////////////////////////////////////////////////////////////////
SDL_Texture* renderText(const std::string& message, const std::string& fontFile,
                        SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
    {
		return nullptr;
	}

	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr)
    {
		TTF_CloseFont(font);
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

//////////////////////////////////////////////////////////////////////////////
/// Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
/// the texture's width and height
///
/// @param tex The source texture we want to draw
/// @param ren The renderer we want to draw to
/// @param x The x coordinate to draw to
/// @param y The y coordinate to draw to
//////////////////////////////////////////////////////////////////////////////
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

//////////////////////////////////////////////////////////////////////////////
/// Repaint the board
//////////////////////////////////////////////////////////////////////////////
void repaint(SDL_Renderer* renderer, bool loose, unsigned int score, const Board& posBoard)
{
    for(unsigned int x = 0; x != posBoard.getWidth(); ++x)
    {
		for(unsigned int y = 0; y != posBoard.getHeight(); ++y)
        {
            Board::Element elem = posBoard.getElement(x, y);
            if(elem == Board::Element::BackgroundElement)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else if(elem == Board::Element::BoardElement)
            {
                SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
            }
            else if(elem == Board::Element::EnemyElement)
            {
                SDL_SetRenderDrawColor(renderer, 204, 0, 0, 255);
            }
            else if(elem == Board::Element::PlayerElement)
            {
                if(loose)
                {
                    SDL_SetRenderDrawColor(renderer, 204, 0, 0, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
                }
            }

            SDL_Rect rect;
            rect.x = x * posBoard.getElementWidth();
            rect.y = y * posBoard.getElementHeight();
            rect.w = posBoard.getElementWidth();
            rect.h = posBoard.getElementHeight();

            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_Color color = { 0, 0, 0, 0 };

    std::stringstream ss;
    ss << score;

    SDL_Texture *image = renderText(ss.str().c_str(), "default.ttf",
                                    color, 30, renderer);
    if (image != nullptr)
    {
        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        int x = SCREEN_WIDTH - iW - posBoard.getBoardPadding();
        int y = SCREEN_HEIGHT - iH;

        renderTexture(image, renderer, x, y);
    }

    SDL_RenderPresent(renderer);
}

//////////////////////////////////////////////////////////////////////////////
/// Update the position of the player
//////////////////////////////////////////////////////////////////////////////
bool updatePlayer(Enemy::PlayerDirection& goPlayer, Board& posBoard)
{
    Board::Position pos = posBoard.getPlayer();

    switch (goPlayer)
    {
        case Enemy::PlayerDirection::SOUTH:
            pos.y += 1;
            break;
        case Enemy::PlayerDirection::NORTH:
            pos.y -= 1;
            break;
        case Enemy::PlayerDirection::EAST:
            pos.x += 1;
            break;
        case Enemy::PlayerDirection::WEST:
            pos.x -= 1;
            break;
        default:
            goPlayer = Enemy::PlayerDirection::STOP;
            return false;
    }

    if(posBoard.onBoard(pos.x, pos.y))
    {
        posBoard.setPlayer(pos.x, pos.y);
        return true;
    }
    goPlayer = Enemy::PlayerDirection::STOP;
    return false;
}

//////////////////////////////////////////////////////////////////////////////
/// Change the direction of the moving player
//////////////////////////////////////////////////////////////////////////////
void changeDirection(Enemy::PlayerDirection& goPlayer, const SDL_Event& aEvent)
{
    switch(aEvent.key.keysym.sym)
    {
        case SDLK_LEFT:
            goPlayer = Enemy::PlayerDirection::WEST;
            break;
        case SDLK_RIGHT:
            goPlayer = Enemy::PlayerDirection::EAST;
            break;
        case SDLK_UP:
            goPlayer = Enemy::PlayerDirection::NORTH;
            break;
        case SDLK_DOWN:
            goPlayer = Enemy::PlayerDirection::SOUTH;
            break;
        default:
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////
/// The main entry point of the cutter game
//////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
    int WINAPI WinMain(HINSTANCE   hInstance,          // Instance
                       HINSTANCE    hPrevInstance,      // Previous Instance
                       LPSTR        lpCmdLine,          // Command Line Parameters
                       int          nCmdShow)           // Window Show State
#else
    int main(int argc, const char * argv[])
#endif
{
    //Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return 1;
    }

    //Set up screen
    SDL_Window* screen = SDL_CreateWindow("Cutter",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_OPENGL);
    if(screen == NULL)
    {
        return 1;
    }

    //Set up renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 0);
    if(renderer == NULL)
    {
        return 1;
    }

    if (TTF_Init() != 0)
    {
        return 1;
    }

    Board posBoard(SCREEN_WIDTH, SCREEN_HEIGHT);
    Flooding flooder;

    Enemy::PlayerDirection goPlayer = Enemy::PlayerDirection::STOP;

    bool quit = false;
	SDL_Event aEvent;

    bool loose = false;

    unsigned int score = 0;
	unsigned int UpdateTimer = SDL_GetTicks();

    // Game loop
	while(!quit)
	{
		while(SDL_PollEvent(&aEvent))
		{
			switch(aEvent.type)
			{
                case SDL_KEYDOWN:
                    if(aEvent.key.keysym.sym == SDLK_n)
                    {
                        score = 0;
                        posBoard.clearBoard(1);
                        goPlayer = Enemy::PlayerDirection::STOP;
                        loose = false;
                    }
                    changeDirection(goPlayer, aEvent);
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
			}
		}

        unsigned int finalUpdateTimer = SDL_GetTicks() - UpdateTimer;
        if(finalUpdateTimer >= PLAYER_SPEED && loose == false)
        {
            if(updatePlayer(goPlayer, posBoard))
            {
                Board::Position pos = posBoard.getPlayer();
                Board::Element elem = posBoard.getElement(pos.x, pos.y);
                if(elem == Board::Element::PlayerElement ||
                   elem == Board::Element::EnemyElement)
                {
                    loose = true;
                }
                else
                {
                    if(elem == Board::Element::BackgroundElement)
                    {
                        score += flooder.cut(posBoard);
                        goPlayer = Enemy::PlayerDirection::STOP;
                    }
                    posBoard.setElement(pos.x, pos.y, Board::Element::PlayerElement);
                }
            }

            posBoard.updateEnemyPositions(loose);
            if(loose)
            {
                goPlayer = Enemy::PlayerDirection::STOP;
            }
            UpdateTimer = SDL_GetTicks();
        }
        repaint(renderer, loose, score, posBoard);
	}

    SDL_Quit();

    return 0;
}

