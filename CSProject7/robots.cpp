//
//  main.cpp
//  Project7
//
//  Created by Ashley Chang on 5/29/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

// robots.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the arena
const int MAXCOLS = 40;             // max number of columns in the arena
const int MAXROBOTS = 130;          // max number of robots allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Robot declaration.

class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool takeDamageAndLive();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    // Finished: You'll probably find that a robot object needs an additional
    // data member to support your implementation of the behavior affected
    // by being hit and taking damage.
    int    m_alive;
};

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    ////////////////////////////////////////////////////////////////////////////allowed to do this?????
    m_alive = 2;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    if (m_alive > 0)
    {
        
    switch (rand() % 4)
    {
        case UP:
            if (m_row > 1)
                m_row--;
            // Finished:  Move the robot up one row if possible.
            break;
        case DOWN:
            if (m_row < (m_arena->rows()))
                m_row++;
            break;
        case LEFT:
            if (m_col > 1)
                m_col--;
            break;
        case RIGHT:
            if (m_col < (m_arena->cols()))
                m_col++;
            // Finished:  Implement the other movements.
            break;
        default:
            break;
            
    }
    }
}

bool Robot::takeDamageAndLive()
{
    // Finished:  If the robot has been hit once before, return false (since a
    // second hit kills a robot).  Otherwise, return true (since the robot
    // survived the damage).
    
    m_alive--; //take the damage

    if (m_alive > 0) //still has one hit left
    {
        return true;
    }
    else //hit twice, so false because dead
        return false;
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

string Player::takeComputerChosenTurn()
{
    // Finished: Replace this implementation:
/*
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."
    
    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest robot I can hit.
    
    // A more aggressive strategy is possible, where you hunt down robots.
    return "stood";
 */
    //Search adjacent spaces for Robots
    bool moved = false;
    if (moved == false && m_arena->nRobotsAt(m_row-1, m_col) == 0 && m_arena->nRobotsAt(m_row+1, m_col) == 0 && m_arena->nRobotsAt(m_row, m_col-1) == 0 && m_arena->nRobotsAt(m_row, m_col+1) == 0 && m_arena->nRobotsAt(m_row-2, m_col) == 0 && m_arena->nRobotsAt(m_row+2, m_col) == 0 && m_arena->nRobotsAt(m_row, m_col-2) == 0 && m_arena->nRobotsAt(m_row, m_col+2) == 0)
        {
            int currentRow = m_row;
            int currentCol = m_col;
            switch (rand() % 4)
            {
                case UP:
                        move(UP);
                    if (m_row == currentRow && m_col == currentCol) //Checks if it actually moved (edge)--if not, then shoot
                        break;
                    else
                        moved = true;
                    break;
                case DOWN:
                        move(DOWN);
                    if (m_row == currentRow && m_col == currentCol)
                        break;
                    else
                        moved = true;
                    break;
                case LEFT:
                        move(LEFT);
                    if (m_row == currentRow && m_col == currentCol)
                        break;
                    else
                        moved = true;
                    break;
                case RIGHT:
                        move(RIGHT);
                    if (m_row == currentRow && m_col == currentCol)
                        break;
                    else
                        moved = true;
                    break;
                default:
                    break;
            }
            if (moved == true)
                return "Moved.";
        }
    //There's some robot in the vicinity...move on to shoot
    else
        moved = false; //double check this is false to move on to shoot

    
    //Search each direction for robots until find nearest one
    if (moved == false)
    {
    for (int i = 1; i < m_arena->rows() || i < m_arena->cols(); i++)
    {
        //search up
        if (m_row-i > 0 && m_arena->nRobotsAt(m_row-i, m_col) >=1)
        {
            if (shoot(UP))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        //search down
        else if (m_row+i <= m_arena->rows() && m_arena->nRobotsAt(m_row+i, m_col) >=1)
        {
            if (shoot(DOWN))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        //search left
        else if (m_col-i > 0 && m_arena->nRobotsAt(m_row, m_col-i) >= 1)
        {
            if (shoot(LEFT))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
        //search right
        else if (m_col+i <= m_arena->cols() && m_arena->nRobotsAt(m_row, m_col+i) >= 1)
        {
            if (shoot(RIGHT))
                return "Shot and hit!";
            else
                return "Shot and missed!";
        }
    }
        //If have not moved there are no robots to shoot at
    }
    return "Stood.";
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
        case UP:
            if (m_row > 1)
                m_row--;
            // Finished:  Move the player up one row if possible.
            break;
        case DOWN:
            if (m_row < (m_arena->rows()))
                m_row++;
            break;
        case LEFT:
            if (m_col > 1)
                m_col--;
            break;
        case RIGHT:
            if (m_col < (m_arena->cols()))
                m_col++;
            // Finished:  Implement the other movements.
            break;
        default:
            break;
    }
}



bool Player::shoot(int dir)
{
    m_age++;
    
    if (rand() % 3 == 0)  // miss with 1/3 probability
        return false;
    
    // Finished: Damage the nearest robot in direction dir, returning
    // true if a robot is hit and damaged, false if not hit.
    switch (dir)
    {
        case UP:
            if (this->m_row > 1) //If the player is in a position to shoot upwards
            {
                for (int i = (m_row)-1; i > 0; i--)
                {
                    //if there's a robot in that direction
                    if (m_arena->nRobotsAt(i, this->m_col) >= 1)
                    {
                        //damage it
                        m_arena->damageRobotAt(i, this->m_col);
                        return true;
                    }
                }
            }
            return false;
            break;
        case DOWN:
            if (this->m_row < m_arena->rows()) //If the player is in a position to shoot downwards
            {
                for (int i = (m_row)+1; i <= m_arena->rows(); i++)
                {
                    if (m_arena->nRobotsAt(i, this->m_col) >= 1)
                    {
                        m_arena->damageRobotAt(i, this->m_col);
                        return true;
                    }
                }
                    
            }
            return false;
            break;
        case LEFT:
            if (this->m_col > 1) //If the player is in a position to shoot left
            {
                for (int i = (m_col)-1; i > 0; i--)
                {
                    if (m_arena->nRobotsAt(this->m_row, i) >=1)
                    {
                        m_arena->damageRobotAt(this->m_row, i);
                        return true;
                    }
                }
                    
            }
            return false;
            break;
        case RIGHT:
            if (this->m_col < m_arena->cols()) //If the player is in a position to shoort right
            {
                for (int i = (m_col)+1; i <= m_arena->cols(); i++)
                {
                   if(m_arena->nRobotsAt(this->m_row, i) >= 1)
                   {
                       m_arena->damageRobotAt(this->m_row, i);
                       return true;
                   }
                    
                }
            }
            return false;
            break;
        default:
            return false;
            
    }
    // This implementation compiles, but is incorrect.

    return false;
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
}

Arena::~Arena()
{
    // Finished:  Delete the player and all remaining dynamically allocated robots.
    delete  m_player;
    for (int i = 0; i < m_nRobots; i++)
    {
        delete m_robots[i];
    }
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{
    // Finished:  Return the number of robots at row r, column c.
    int numberOfRobots = 0;
    for (int i = 0; i < m_nRobots; i++)
    {
        if (m_robots[i]->row() == r && m_robots[i]->col() == c)
            numberOfRobots++;
        
    }
    return numberOfRobots;
}

void Arena::display(string msg) const
{
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each robot's position
    // Finished:  If one robot is at some grid point, set the char to 'R'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    for (int i = 0; i < m_nRobots; i++)
    {
        int indicateRow = (m_robots[i]->row());
        int indicateCol = (m_robots[i]->col());
        int howManyRobots = nRobotsAt(indicateRow, indicateCol);
        
        if (howManyRobots == 1)
            grid[indicateRow-1][indicateCol-1] = 'R';
        else if (howManyRobots >= 2 && howManyRobots <= 8)
            grid[indicateRow-1][indicateCol-1] = '0' + (howManyRobots);
        else if (howManyRobots >= 9)
            grid[indicateRow-1][indicateCol-1] = '9';
        else
            grid [indicateRow-1][indicateCol-1] = '.';
    }
    
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a robot there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.
    
    // Finished:  Implement this.
    if (m_nRobots >= MAXROBOTS)
        return false;
    else
    {
        m_robots[m_nRobots] = new Robot (this, r, c);
        m_nRobots++;
        return true;
    }
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::damageRobotAt(int r, int c)
{
    // Damage one robot at row r, column c if at least one is there.
    // If the robot does not survive the damage, destroy it.
    for (int i = 0; i < m_nRobots; i++)
    {
        if (m_robots[i]-> row()== r && m_robots[i]-> col() == c)
        {
            //takeDamageAndLive does the damage and then returns T/F
            if(!(m_robots[i]->takeDamageAndLive())) //If the robot does not live (false), destroy
            {
                delete m_robots[i];
                //shift everything over -1 starting from index i
                for (int a = i ; a < m_nRobots-1; a++)
                {
                    m_robots[a] = m_robots[a+1];
                }
                m_nRobots--;
                
            }
            return;
        }
    }
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
        // Have the k-th robot in the arena make one move.
        //        If that move results in that robot being in the same
        //        position as the player, the player dies.
        {
        m_robots[k]->move(); //called the move function on the robot, so now in different position
        
        //If robot is in same place as player
        if ((m_robots[k]->row() == m_player->row()) && (m_robots[k]->col() == m_player->col()))
            m_player->setDead();
        }
    }
    
    // return true if the player is still alive, false otherwise
    return !m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRobots)
{
    if (nRobots > MAXROBOTS)
    {
        cout << "***** Trying to create Game with " << nRobots
        << " robots; only " << MAXROBOTS << " are allowed!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with robots
    while (nRobots > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
        // Don't put a robot where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addRobot(r, c);
        nRobots--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display("");
        return;
    }
    string msg = "";
    do
    {
        m_arena->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r/su/sd/sl/sr/c//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'c':  // computer moves player
                    msg = p->takeComputerChosenTurn();
                    break;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
                case 's':
                    if (action.size() < 2)  // if no direction, nobody moves
                    {
                        cout << '\a' << endl;  // beep
                        continue;
                    }
                    switch (action[1])
                {
                    default:   // if bad direction, nobody moves
                        cout << '\a' << endl;  // beep
                        continue;
                    case 'u':
                    case 'd':
                    case 'l':
                    case 'r':
                        if (p->shoot(decodeDirection(action[1])))
                            msg = "Hit!";
                        else
                            msg = "Missed!";
                        break;
                }
                    break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display(msg);
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////
void doBasicTests();
int main()
{
    //doBasicTests();
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(5, 5, 10);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementations
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
#include <cassert>

#define CHECKTYPE(f, t) { (void)(t)(f); }

void thisFunctionWillNeverBeCalled()
{
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)
    
    Robot(static_cast<Arena*>(0), 1, 1);
    CHECKTYPE(&Robot::row,               int  (Robot::*)() const);
    CHECKTYPE(&Robot::col,               int  (Robot::*)() const);
    CHECKTYPE(&Robot::move,              void (Robot::*)());
    CHECKTYPE(&Robot::takeDamageAndLive, bool (Robot::*)());
    
    Player(static_cast<Arena*>(0), 1, 1);
    CHECKTYPE(&Player::row,                     int    (Player::*)() const);
    CHECKTYPE(&Player::col,                     int    (Player::*)() const);
    CHECKTYPE(&Player::age,                     int    (Player::*)() const);
    CHECKTYPE(&Player::isDead,                  bool   (Player::*)() const);
    CHECKTYPE(&Player::takeComputerChosenTurn,  string (Player::*)());
    CHECKTYPE(&Player::stand,                   void   (Player::*)());
    CHECKTYPE(&Player::move,                    void   (Player::*)(int));
    CHECKTYPE(&Player::shoot,                   bool   (Player::*)(int));
    CHECKTYPE(&Player::setDead,                 void   (Player::*)());
    
    Arena(1, 1);
    CHECKTYPE(&Arena::rows,          int     (Arena::*)() const);
    CHECKTYPE(&Arena::cols,          int     (Arena::*)() const);
    CHECKTYPE(&Arena::player,        Player* (Arena::*)() const);
    CHECKTYPE(&Arena::robotCount,    int     (Arena::*)() const);
    CHECKTYPE(&Arena::nRobotsAt,     int     (Arena::*)(int,int) const);
    CHECKTYPE(&Arena::display,       void    (Arena::*)(string) const);
    CHECKTYPE(&Arena::addRobot,      bool    (Arena::*)(int,int));
    CHECKTYPE(&Arena::addPlayer,     bool    (Arena::*)(int,int));
    CHECKTYPE(&Arena::damageRobotAt, void    (Arena::*)(int,int));
    CHECKTYPE(&Arena::moveRobots,    bool    (Arena::*)());
    
    Game(1,1,1);
    CHECKTYPE(&Game::play, void (Game::*)());
}

void doBasicTests()
{
    {
        Arena a(10, 20);
        assert(a.addPlayer(2, 6));
        Player* pp = a.player();
        assert(pp->row() == 2  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 6  && pp->isDead());
    }
    {
        Arena a(2, 2);
        assert(a.addPlayer(1, 1));
        assert(a.addRobot(2, 2));
        Player* pp = a.player();
        assert(a.moveRobots());
        assert( ! pp->isDead());
        for (int k = 0; k < 1000  &&  ! pp->isDead()  &&  a.moveRobots(); k++)
            ;
        assert(pp->isDead());
    }
    {
        Arena a(1, 40);
        assert(a.addPlayer(1, 1));
        assert(a.addRobot(1, 40));
        assert(a.addRobot(1, 40));
        assert(a.addRobot(1, 39));
        assert(a.robotCount() == 3  &&  a.nRobotsAt(1, 40) == 2);
        Player* pp = a.player();
        for (int k = 0; k < 1000  &&  a.robotCount() != 0; k++)
            pp->shoot(RIGHT);
        assert(a.robotCount() == 0);
        assert(a.addRobot(1, 40));
        for (int k = 0; k < 1000  &&  a.robotCount() != 0; k++)
            pp->takeComputerChosenTurn();
        assert(a.robotCount() == 0);
    }
    cout << "Passed all basic tests" << endl;
}
 

