/*

Kaan Yuecel
C++ Fall 2021
Due: 12/8/2021
Lab Name: Lab 7 Battleship
Description:
For this lab you will make a simple battleship game. For this lab, you will need four
10 x 10 grids (two for the user and two for the computer). The program will begin with
setup. The program will need to randomly place the computers 5 ships, making sure the
ships do not overlap or go off the table.


*/

#include <iostream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <cassert> // Is letting me use asserts


using namespace std;

void ship(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& z, bool right, bool left, bool up, bool down);
//Precondition: While entering ship function, stream has to be valid until void ship in main is called
//Postconditin: void ship places ships legally


void createtable(char table_[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& z, bool right, bool left, bool up, bool down);
//Precondition: To enter this, stream has to be valid until void ship in main
//Postconditin: Outputs table to the screen


void text();
//Precondition: To enter this, stream has to be valid until void ship in main
//Postconditin: Outputs text to screen


void initialization(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& z, bool right, bool left, bool up, bool down);
//Precondition: To enter this, stream has to be valid until void ship in main
//Postconditin:this void is used to set default values at beginning of game and end if player replays


void game(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& win, int& loss);
//Precondition:  To enter this, stream has to be valid until void ship in main
//Postconditin: this function is to fire for player and computer. Checks for valid inputs


void eship(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10]);
//Precondition:  To enter this, stream has to be valid until void ship in main
//Postconditin:places enemy ships legally


int gameover(int win, int loss);
//Precondition: To enter this, stream has to be valid until void ship in main
//Postconditin: ending program if input is not valid


void playagain(int& win, int& loss, bool& endgame);
//Precondition: To enter this, stream has to be valid until void ship in main
//Postconditin: asking player if he wants to play again


//struct shipinfos safes information about the ships
struct shipinfos
{
    string name;
    int x_locations;
    int y_locations;
    int size;
    int health;
};

shipinfos enemyship[5];
shipinfos myship[5];

void initialization(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& z, bool right, bool left, bool up, bool down)

{

    //names equal to their array values
    myship[0].name = "Destroyer (Size 2)";
    myship[1].name = "Submarine (Size 3)";
    myship[2].name = "Cruiser (Size 3)";
    myship[3].name = "Battleship (Size 4)";
    myship[4].name = "Carrier (Size 5)";

    for (int z = 4; z >= 0; z--)
    {
        if (z == 1 || z == 0)
        {
            myship[z].x_locations = '0';
            myship[z].y_locations = '0';
            myship[z].size = z + 2;
            myship[z].health = z + 2;
        }
        else
        {
            myship[z].x_locations = '0';
            myship[z].y_locations = '0';
            myship[z].size = z + 1;
            myship[z].health = z + 1;
        }
    }
    for (int z = 4; z >= 0; z--)
    {
        if (z == 1 || z == 0)
        {
            enemyship[z].x_locations = '0';
            enemyship[z].y_locations = '0';
            enemyship[z].size = z + 2;
            enemyship[z].health = z + 2;
        }
        else
        {
            enemyship[z].x_locations = '0';
            enemyship[z].y_locations = '0';
            enemyship[z].size = z + 1;
            enemyship[z].health = z + 1;
        }
    }
    const char water = '~';

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            table[i][j] = water;
            table2[i][j] = water;
            table3[i][j] = water;
            table4[i][j] = water;
        }
    }
}
//void createtable is outputting the table
void createtable(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& z, bool right, bool left, bool up, bool down)
{
    cout << "\t\tPlayer table\t\t\t\t\t\t Computer table" << endl << "     1 2 3 4 5 6 7 8 9 10 \t\t\t     1 2 3 4 5 6 7 8 9 10" << endl << "     ====================  \t\t\t     ====================";
    for (int i = 0; i < 10; i++)
    {
        //This segment deals with spacing, rows, and columns
        cout << endl;
        if (i <= 9)
        {

            cout << setw(4) << i + 1;
            cout << "|";
        }
        //outputs water on the screen
        for (int j = 0; j < 10; j++)
        {
            cout << char(table[i][j]);
            cout << " ";
        }
        cout << "\t\t\t";
        if (i <= 9)
        {
            cout << setw(4) << i + 1;
            cout << "|";
        }
        for (int j = 0; j < 10; j++)
        {
            cout << char(table2[i][j]);
            cout << " ";
        }
    }

    cout << "\n";
}
//void playagain is asking the palyer if he/she wnats to play again
void playagain(int& win, int& loss, bool& endgame)
{
    int play;
    cout << "The game has ended. Enter 1 to plagy again or enter 2 to finish and display your score:" << endl;
    cin >> play;
    switch (play)
    {
    case 1:endgame = true;
        break;
    case 2: endgame = false;
        break;
    default:cout << "This is not a valid input the game will now end\n";
        gameover(win, loss);
        break;
    }
}
int main()
{

    bool endgame;
    int win = 0;
    int loss = 0;
    do
    {
        // the bool values place the ships
        bool up = true;
        bool down = true;
        bool right = true;
        bool left = true;
        //srand used to randomize ship placement of computer
        srand((unsigned int)time(NULL));

        int z;
        // table are the game tables
        char table[10][10];
        char table2[10][10];
        char table3[10][10];
        char table4[10][10];
        //data that is being transfered between the void functions

        //intialization sets all values and can reset the tables
        initialization(table, table2, table3, table4, z, right, left, up, down);
        createtable(table, table2, table3, table4, z, right, left, up, down);
        text();
        ship(table, table2, table3, table4, z, right, left, up, down);
        eship(table, table2, table3, table4);
        //This is the end of all ship placements

        game(table, table2, table3, table4, win, loss);
        playagain(win, loss, endgame);
    } while (endgame);
    gameover(win, loss);
    return 0;
}
//void game is the firing in the game to hit ships
void game(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& win, int& loss)
{
    //bools checking to see that the player or computer fired a legal shot
    bool friendvalid = true;
    bool enemyvalid = true;

    //bools check if player or computer has won the game
    bool playerwin = true;
    bool enemywin = true;

    //randomnumber for computer
    int randomnumber10;

    //int statements are for checking to see if someone has won the game
    int friendlyhits = 17;
    int enemyhits = 17;

    //These statements got rid of errors
    int z;
    bool up;
    bool down;
    //ints for player inputs of x and y
    int xloc;
    int yloc;
    //do while for checking to see if either player has won
    do
    {
        \
            do
            {
                //sets bool for validity of players turn has happened legally
                friendvalid = true;
                cout << "\nIt's now your turn to fire your shot:\n To succesfully fire your shot, add a space between your x and y coordinates. ";
                cout << "Enter an x coordinate and then a y coordinate or enter the number 0 to quit: ";
                cin >> xloc;
                //checks to see if input cin is valid
                assert(cin);
                //ends progam if player chooses to quit the game
                if (xloc == 0)
                {
                    gameover(win, loss);
                }
                cin >> yloc;
                //checks to see if input cin is valid
                assert(cin);
                //subtracts one from each of the inputs to match it with the table
                xloc = xloc - 1;
                yloc = yloc - 1;
                //This if statement checks to see if the inputs are within the limits of the table. If not the player has to rechoose them

                if ((xloc >= 0 && xloc < 10) && (yloc >= 0 && yloc < 10))
                {
                    //Checking if the inputs were already tried
                    if (table2[yloc][xloc] == 'M' || table2[yloc][xloc] == 'H')
                    {
                        cout << "This position has already been fired on. Select a different position";
                        friendvalid = false;
                    }
                    //Checks to see if it it is a hit
                    if (table3[yloc][xloc] == '#')
                    {
                        cout << "HIT\n";
                        table2[yloc][xloc] = 'H';
                        createtable(table, table2, table3, table4, z, right, left, up, down);
                        z = -1;
                        //calculates a win if limit is hit to end game
                        friendlyhits--;
                        //Checks to see if game is over with a winner
                        if (friendlyhits == 0)
                        {
                            win++;
                            playerwin = false;
                        }
                    }
                    //if statement for missed shot
                    if (table2[yloc][xloc] == '~')
                    {
                        cout << "You missed the shot.  The computer will now fire their shot\n";
                        table2[yloc][xloc] = 'M';
                        createtable(table, table2, table3, table4, z, right, left, up, down);
                    }
                }
                //checks if game is over and if player legally fired their shot
                else
                {
                    friendvalid = false;
                }
            } while (friendvalid == false);
            //sets random number for computer
            randomnumber10 = rand() % 10 + 1;
            int enemyxloc;
            int enemyyloc;
            //computers turn
            do
            {
                enemyvalid = true;

                //sets enemys x and y locations for targets to. Different from time to time

                enemyyloc = randomnumber10;
                randomnumber10 = rand() % 10 + 1;
                enemyxloc = randomnumber10;
                //subtracts to make valid
                enemyxloc = enemyxloc - 1;
                enemyyloc = enemyyloc - 1;
                //checks to see if valid
                if ((enemyxloc >= 0 && enemyxloc < 10) && (enemyyloc >= 0 && enemyyloc < 10))
                {
                    //Checks for hits, misses, and for hitting the same location twice
                    if (table[enemyyloc][enemyxloc] == '#')
                    {
                        cout << "THE ENEMY HIT YOU\n";
                        table[enemyyloc][enemyxloc] = 'H';
                        createtable(table, table2, table3, table4, z, right, left, up, down);
                        enemyhits--;
                        if (enemyhits == 0)
                        {
                            loss++;
                            enemywin = false;
                        }
                    }
                    if (table[enemyyloc][enemyxloc] == 'M' || table[enemyyloc][enemyxloc] == 'H')
                    {

                        enemyvalid = false;
                    }
                    if (table[enemyyloc][enemyxloc] == '~')
                    {
                        cout << "Your opponent missed the shot.\n";                        table[enemyyloc][enemyxloc] = 'M';
                        createtable(table, table2, table3, table4, z, right, left, up, down);
                    }
                }
                else
                {
                    enemyvalid = false;
                }
                //checking if computer fired legally
            } while (enemyvalid == false);
            //checks for  a winner
    } while (playerwin && enemywin);
}
//void eship is for placing enemy ships
void eship(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10])
{
    //random numbers for computer placing
    int randomnumber10;
    int randomnumber4;
    int direction;
    //placing ships
    for (int z = 4; z >= 0; z--)
    {
        randomnumber10 = rand() % 10 + 1;
        randomnumber4 = rand() % 4 + 1;
        bool right = true;
        bool left = true;
        bool up = true;
        bool down = true;

        enemyship[z].x_locations = randomnumber10 - 1;
        randomnumber10 = rand() % 10 + 1;
        enemyship[z].y_locations = randomnumber10 - 1;
        //if statement makes sure values are valid and within table limits
        if ((enemyship[z].x_locations >= 0 && enemyship[z].x_locations < 10) && (enemyship[z].y_locations >= 0 && enemyship[z].y_locations < 10))
        {
            //if statements checking if each directions are valid
            if ((enemyship[z].x_locations + enemyship[z].size <= 10))
            {
                for (int count = 0; enemyship[z].size >= count; count++)
                {
                    if (table3[enemyship[z].y_locations][enemyship[z].x_locations + count] != '~')
                    {
                        right = false;
                    }
                }
            }
            else
            {
                right = false;
            }
            if ((enemyship[z].x_locations - enemyship[z].size >= -1))
            {
                for (int count = 0; enemyship[z].size >= count; count++)
                {
                    if (table3[enemyship[z].y_locations][enemyship[z].x_locations - count] != '~')
                    {
                        left = false;
                    }
                }
            }
            else
            {
                left = false;
            }
            if ((enemyship[z].y_locations + enemyship[z].size <= 10))
            {
                for (int count = 0; enemyship[z].size >= count; count++)
                {
                    if (table3[enemyship[z].y_locations + count][enemyship[z].x_locations] != '~')
                    {
                        down = false;
                    }
                }
            }
            else
            {
                down = false;
            }
            if ((enemyship[z].y_locations - enemyship[z].size >= -1))
            {
                for (int count = 0; enemyship[z].size >= count; count++)
                {
                    if (table3[enemyship[z].y_locations - count][enemyship[z].x_locations] != '~')
                    {
                        up = false;
                    }
                }
            }
            else
            {
                up = false;
            }
            cout << "\n";
            direction = randomnumber4;
            randomnumber4 = rand() % 4 + 1;
            //switch for random direction
            switch (direction)
            {
                //cases for the computer to choose the direction it wants to go
            case 1:
                if (right)
                {
                    for (int count = 1; enemyship[z].size >= count; count++)
                    {
                        table3[enemyship[z].y_locations][enemyship[z].x_locations] = '#';
                        enemyship[z].x_locations = enemyship[z].x_locations + 1;
                    }
                }
                else
                {
                    z++;
                }
                break;
            case 2:
                if (left)
                {
                    for (int count = 1; enemyship[z].size >= count; count++)
                    {
                        table3[enemyship[z].y_locations][enemyship[z].x_locations] = '#';
                        enemyship[z].x_locations = enemyship[z].x_locations - 1;
                    }
                }
                else
                {
                    z++;
                }
                break;
            case 3:
                if (down)
                {
                    for (int count = 1; enemyship[z].size >= count; count++)
                    {
                        table3[enemyship[z].y_locations][enemyship[z].x_locations] = '#';
                        enemyship[z].y_locations = enemyship[z].y_locations + 1;
                    }
                }
                else
                {
                    //if computer chooses and invalid input it
                        // it does z++ to redo the picks and numbers
                    z++;
                }
                break;
            case 4:
                if (up)
                {
                    for (int count = 1; enemyship[z].size >= count; count++)
                    {
                        table3[enemyship[z].y_locations][enemyship[z].x_locations] = '#';
                        enemyship[z].y_locations = enemyship[z].y_locations - 1;
                    }
                }
                else
                {
                    z++;
                }
                break;
            }
        }
        else
        {
            z++;
        }
        //creates to table to display after the computer chooses its locations
        createtable(table, table2, table3, table4, z, right, left, up, down);
    }
}
//Text outputted to the screen to make it easier to play/understand for user
void text()
{
    cout << "\n\nWelcome to battleship game. Please start by placing your battleships. \nThe format should be:\n";
    cout << " Y (left) coordinates and X (top) coordinates,\n";
    cout << "Example: 5 5    This would place a ship beginning at x:5 y:5 .Then you will be asked if the ship should look up,down, left, right\n\n";
}
//This is for placing ships
//void ship is for placing player ships
void ship(char table[10][10], char table2[10][10], char table3[10][10], char table4[10][10], int& z, bool right, bool left, bool up, bool down)
{
    int direction;
    //placing ships
    //for statement for all of the different ships
    for (int z = 4; z >= 0; z--)
    {
        //setting default bool values
        right = true;
        left = true;
        up = true;
        down = true;
        cout << "\nFirst you will be placing the " << myship[z].name << ". . ." << myship[z].name << " has a size of " << myship[z].size << "\nTake the size into account when placing\n";
        cout << "Enter facing: X (top-row)  coords then  Y (left-side) coords with a space between the"; cout << " numbers\n";
        cout << "Example: 5 5    This would place a ship beginning at x:5 y:5 and make sure to put a space between the numbers\n";
        //cin inputs from player
        cin >> myship[z].x_locations >> myship[z].y_locations;
        //assert checks that the input is valid and ends progamm if it is false
        assert(cin);
        //subtracts one from inputs to make table correct
        myship[z].x_locations = myship[z].x_locations - 1;
        myship[z].y_locations = myship[z].y_locations - 1;
        cout << "Your options and their corresponding numbers are: ";
        //checks to see if inputs work with table values
        if ((myship[z].x_locations >= 0 && myship[z].x_locations < 10) && (myship[z].y_locations >= 0 && myship[z].y_locations < 10))
        {
            //if statements that check up,down,left, and right
            if ((myship[z].x_locations + myship[z].size <= 10))
            {
                for (int count = 0; myship[z].size >= count; count++)
                {
                    if (table[myship[z].y_locations][myship[z].x_locations + count] != '~')
                    {
                        right = false;
                    }
                }
                cout << "Right 1,";
            }
            else
            {
                right = false;
            }
            if ((myship[z].x_locations - myship[z].size >= 0))
            {

                for (int count = 0; myship[z].size >= count; count++)
                {
                    if (table[myship[z].y_locations][myship[z].x_locations - count] != '~')
                    {
                        left = false;
                    }
                }
                cout << " Left 2,";
            }
            else
            {
                left = false;
            }
            if ((myship[z].y_locations + myship[z].size <= 10))
            {

                for (int count = 0; myship[z].size >= count; count++)
                {
                    if (table[myship[z].y_locations + count][myship[z].x_locations] != '~')
                    {
                        down = false;
                    }
                }
                cout << " Down 3,";
            }
            else
            {
                down = false;
            }
            if ((myship[z].y_locations - myship[z].size >= -1))
            {
                for (int count = 0; myship[z].size >= count; count++)
                {
                    if (table[myship[z].y_locations - count][myship[z].x_locations] != '~')
                    {
                        up = false;
                    }
                }
                cout << " Up 4";
            }
            else
            {
                up = false;
            }
            cout << "\n";
            //gets input from player
            cin >> direction;
            //checks to see input is valid
            assert(cin);
            //switch statement for chooseing the direction to face the ships
            switch (direction)
            {
                //cases for facing also checks to see if valid
            case 1:
                if (right)
                {
                    for (int count = 1; myship[z].size >= count; count++)
                    {
                        table4[myship[z].y_locations][myship[z].x_locations] = '#';
                        table[myship[z].y_locations][myship[z].x_locations] = '#';
                        myship[z].x_locations = myship[z].x_locations + 1;
                    }
                }
                else
                {
                    cout << "INVALID INPUT";
                    z++;
                }
                break;
            case 2:
                if (left)
                {
                    for (int count = 1; myship[z].size >= count; count++)
                    {
                        table4[myship[z].y_locations][myship[z].x_locations] = '#';
                        table[myship[z].y_locations][myship[z].x_locations] = '#';
                        myship[z].x_locations = myship[z].x_locations - 1;


                    }
                }
                else
                {
                    cout << "INVALID INPUT";
                    z++;
                }
                break;
            case 3:
                if (down)
                {
                    for (int count = 1; myship[z].size >= count; count++)
                    {
                        table4[myship[z].y_locations][myship[z].x_locations] = '#';
                        table[myship[z].y_locations][myship[z].x_locations] = '#';
                        myship[z].y_locations = myship[z].y_locations + 1;
                    }
                }
                else
                {
                    cout << "INVALID INPUT";
                    z++;
                }
                break;
            case 4:
                if (up)
                {
                    for (int count = 1; myship[z].size >= count; count++)
                    {
                        table4[myship[z].y_locations][myship[z].x_locations] = '#';
                        table[myship[z].y_locations][myship[z].x_locations] = '#';
                        myship[z].y_locations = myship[z].y_locations - 1;
                    }
                }
                else
                {
                    //if invalid looks
                    cout << "INVALID INPUT";
                    z++;
                }
                break;

            default:cout << "**INVALID INPUT**";
                z++;
                break;
            }
            //creates table if valid inputs are used
            createtable(table, table2, table3, table4, z, right, left, up, down);
        }
        else
        {
            z++;
        }
    }
}
//Game over and exits program
int gameover(int win, int loss)
{
    cout << "This is the end of the battleshipe game. See your score here: " << endl;
    cout << "Total wins: " << win << "\n" << "Total losses: " << loss << "\n";
    exit(0);
}


