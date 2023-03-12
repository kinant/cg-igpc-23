#include "Game.h"
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <assert.h>

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

Game::Game()
	: m_bIsGameOver(false)
    , m_bUserQuit(false)
{

}
Game::~Game() 
{

}

bool Game::Load() 
{
	return m_Level.Load("Level3.txt", m_Player.GetXPositionPointer(), m_Player.GetYPositionPointer());
}

void Game::Run() 
{
	Draw();

	m_bIsGameOver = Update();

	if (m_bIsGameOver) 
	{
		Draw();
	}
}

bool Game::IsGameOver() 
{
	return m_bIsGameOver;
}

bool Game::Update()
{
    int Input = _getch();
    int ArrowInput = 0;

    int NewPlayerX = m_Player.GetXPosition();
    int NewPlayerY = m_Player.GetYPosition();

    // one of the arrow keys was pressed
    if (Input == kArrowInput) 
    {
        ArrowInput = _getch();
    }

    if ((Input == kArrowInput && ArrowInput == kLeftArrow) ||
        (char)Input == 'A' || (char)Input == 'a') 
    {
        NewPlayerX--;
    }
    else if ((Input == kArrowInput && ArrowInput == kRightArrow) ||
        (char)Input == 'D' || (char)Input == 'd')
    {
        NewPlayerX++;
    }
    else if ((Input == kArrowInput && ArrowInput == kUpArrow) ||
        (char)Input == 'W' || (char)Input == 'w')
    {
        NewPlayerY--;
    }
    else if ((Input == kArrowInput && ArrowInput == kDownArrow) ||
        (char)Input == 'S' || (char)Input == 's')
    {
        NewPlayerY++;
    }
    else if (Input == kEscapeKey) 
    {
        m_bUserQuit = true;
        return true;
    }
    else if ((char)Input == 'Z' || (char)Input == 'z')
    {
        m_Player.DropKey();
    }

    // If position never changed
    if (NewPlayerX == m_Player.GetXPosition() && NewPlayerY == m_Player.GetYPosition()) 
    {
        return false;
    }
    else 
    {
        return HandleCollision(NewPlayerX, NewPlayerY);
    }
}

bool Game::HandleCollision(int NewPlayerX, int NewPlayerY) 
{
    bool bIsGameDone = false;

    AActor* CollidedActor = m_Level.UpdateActors(NewPlayerX, NewPlayerY);

    if (CollidedActor != nullptr && CollidedActor->IsActive()) 
    {
        switch (CollidedActor->GetType()) 
        {
            case ActorType::Enemy:
            {
                Enemy* CollidedEnemy = dynamic_cast<Enemy*>(CollidedActor);
                assert(CollidedEnemy);
                
                CollidedEnemy->Remove();
                m_Player.SetPosition(NewPlayerX, NewPlayerY);

                m_Player.DecrementLives();

                if (m_Player.GetLives() < 0)
                {
                    bIsGameDone = true;
                }
              
                break;
            }
            case ActorType::Money:
            {
                Money* CollidedMoney = dynamic_cast<Money*>(CollidedActor);
                assert(CollidedMoney);
                
                CollidedMoney->Remove();
                m_Player.AddMoney(CollidedMoney->GetWorth());
                m_Player.SetPosition(NewPlayerX, NewPlayerY);
                
                break;
            }
            case ActorType::Key:
            {
                Key* CollidedKey = dynamic_cast<Key*>(CollidedActor);
                assert(CollidedKey);
                
                if (!m_Player.HasKey())
                {
                    m_Player.PickupKey(CollidedKey);
                    CollidedKey->Remove();
                    m_Player.SetPosition(NewPlayerX, NewPlayerY);
                    //PlayKeyPickupSound();
                }
                
                break;
            }
            case ActorType::Door:
            {
                Door* CollidedDoor = dynamic_cast<Door*>(CollidedActor);
                assert(CollidedDoor);
                
                if (!CollidedDoor->IsOpen())
                {
                    if (m_Player.HasKey(CollidedDoor->GetColor()))
                    {
                        CollidedDoor->Open();
                        CollidedDoor->Remove();
                        m_Player.UseKey();
                        m_Player.SetPosition(NewPlayerX, NewPlayerY);
                        //PlayDoorOpenSound();
                    }
                    else
                    {
                        //PlayDoorClosedSound();
                    }
                }
                else
                {
                    m_Player.SetPosition(NewPlayerX, NewPlayerY);
                }
                
                break;
            }
            case ActorType::Goal:
            {
                Goal* CollidedGoal = dynamic_cast<Goal*>(CollidedActor);
                assert(CollidedGoal);
                
                CollidedGoal->Remove();
                m_Player.SetPosition(NewPlayerX, NewPlayerY);
                bIsGameDone = true;
                
                break;
            }
            default:
                break;
        }
    }
    else if (m_Level.IsSpace(NewPlayerX, NewPlayerY)) // no collision
    {
        m_Player.SetPosition(NewPlayerX, NewPlayerY);
    }
    else if (m_Level.IsWall(NewPlayerX, NewPlayerY)) 
    {
        // wall collision, do nothing
    }

    return bIsGameDone;
}

void Game::Draw() 
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("CLS");
    
    m_Level.Draw();

    // set cursor for player
    COORD ActorCursorPosition;
    ActorCursorPosition.X = m_Player.GetXPosition();
    ActorCursorPosition.Y = m_Player.GetYPosition();
    SetConsoleCursorPosition(console, ActorCursorPosition);
    m_Player.Draw();

    // set cursor to the end of the level
    COORD CurrentCursorPosition;
    CurrentCursorPosition.X = 0;
    CurrentCursorPosition.Y = m_Level.GetHeight();
    SetConsoleCursorPosition(console, CurrentCursorPosition);
}