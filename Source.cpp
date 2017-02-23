//SDFD102 Assignment 1 - Christopher Haynes

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)  //keyboard input definition for key presses
#define KEY_UP  (vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)  //keyboard input definition for key releases

using namespace std;

void gotoxy(int, int);             //declare a function called gotoxy
void clrscr(void);                 //declare clear screen function
void textcolor(int);               //declare text colour function

void animation(void);              //the function containing the animated character instructions
void hline(int, int, int, int);    //a function for drawing a horizontal line at location x,y with a length of l and a colour of c
void vline(int, int, int, int);    //a function for drawing a vertical line at location x,y with a length of l and a colour of c
void link1(int, int);			   //link1 to link8 contain the instructions to draw one frame of the animation at (x,y)
void link2(int, int);
void link3(int, int);
void link4(int, int);
void link5(int, int);
void link6(int, int);
void link7(int, int);
void link8(int, int);

void randomblocks(void);            //the function containing the random block drawing and matrix instructions
void MatrixRand(void);              //the function for randomising specific colours and symbols for the matrix line drawing

void GOL(void);                     //the function containing the menu system for the three versions of game of life
void GOL1(void);                    //the function for the standard game of life
void GOL2(void);                    //the function for the preditor/prey version of game of life
void GOL3(void);                    //the function for the game of life with food resources

int color, symbol;                  //variables for the colour and symbol used in the matrix line drawing
int a[80][50];                      //global variable array used in the game of life functions
int b[80][50];                      //second global variable array used in the game of life functions
char z1 = 219;                      //character code for solid block, global variable used in most of the functions
int x, y, c = 0, d = 0;             //co-oridinate and couter variables for game of life, x and y are for postion, c and d are for counting the amount of objects in surrounding cells

void main(void)
{
	int choice;                    //menu variable used to store users choice

	do
	{
		do
		{
			clrscr(); z1 = 219; textcolor(10);                                       //clear the screen, reset z1 to solid block (219) and set text colour to green
			cout << "Press (1) for a controlable animated character";  
			cout << "\nPress (2) to draw random objects to the screen";
			cout << "\nPress (3) to play the game of life";
			cout << "\nPress (4) to exit the program";
			cout << "\n\nEnter 1, 2, 3 or 4";
			cout << "\n\nPress (ESC) at any time to return to the main menu";
			choice = _getch();                                                       //set the variable "choice" to the users input
		}

		while (choice != '1' && choice != '2' && choice != '3' && choice != '4');    //if the user doesn't input one of the available options, loop back to the start of the menu

		if (choice == '1')
		{
			clrscr(); choice = '0';              //clear the screen and set the menu choice variable back to '0'
			animation();                         //run the animation function
		}
		if (choice == '2')
		{
			clrscr(); choice = '0';              //clear the screen and set the menu choice variable back to '0'
			randomblocks();                      //run the randomblocks function
	    }
		if (choice == '3')
		{
			clrscr(); choice = '0';              //clear the screen and set the menu choice variable back to '0'
			GOL();	                             //run the game of life function
		}
	} while (choice != '4');                     //upon exiting any of the functions return to the main menu, as long as the menu choice variable doesn't equal 4
												 //if 4 is entered as the choice from the main menu, end the program
}                                                //end of main

void animation()
{

	int bx = 32, by = 17;						//Co-ordinates for link's starting postion
	int lt = 0;									//lt is a flip flop switch to draw the two frames of the walking down animation							

	DWORD   t1, t2;						    	//The two time variables used to set the refresh rate

	cout << "Use the arrow keys to move link around the screen.";
	cout << "\nPress two directions together to get him to move diagonally";
	cout << "\n\nPress any key to start";
    _getch(); clrscr();
	
	link1(bx, by);                              //Draws the first stationary image at the starting co-ordinates bx,by	
	
	t1 = GetTickCount();
	do
	{
		t2 = GetTickCount();
		if (t2 - t1>100)							//Compares tick counts to set refresh rate
		{
			t1 = t2;


			if (KEY_DOWN(VK_LEFT))					//Sets the next position for where the image will be drawn
			{
				bx--;
				if (bx<1) bx = 1;
			}
			if (KEY_DOWN(VK_RIGHT))
			{
				bx++;
				if (bx>65) bx = 65;
			}
			if (KEY_DOWN(VK_UP))
			{
				by--;
				if (bx<1) bx = 1;
			}
			if (KEY_DOWN(VK_DOWN))
			{
				by++;
			}
			if (by>34) by = 34;
			if (by<1) by = 1;

            //Drawing instructions 
			//If the corresponding key is held down the animation cycles between the two images
			//The _getch command allows the animation to be moved frame by frame

			//The first four if statements set the animations for exclusively up,down,left and right

			if (KEY_DOWN(VK_DOWN) && !KEY_DOWN(VK_LEFT) && !KEY_DOWN(VK_RIGHT) && !KEY_DOWN(VK_UP))  //if just the down key is held 
			{
				clrscr();                            //clear the screen                               
				if (lt == 0)                         //if the switch is set to 0
				{ link1(bx, by); lt = 1; _getch; }   //draw the first frame (link1) at position "bx,by", set the switch to 1, and wait for user input
				else                                 //if the switch is not set to 0
				{ link2(bx, by); lt = 0; _getch; }   //draw the second frame (link2) at position "bx,by", set the switch back to 0 and wait for user input
			}

			if (KEY_DOWN(VK_RIGHT) && !KEY_DOWN(VK_UP) && !KEY_DOWN(VK_DOWN) && !KEY_DOWN(VK_LEFT))
			{
				clrscr();
				if (lt == 0)
				{ link3(bx, by); lt = 1; _getch; }
				else
				{ link4(bx, by); lt = 0; _getch; }
			}

			if (KEY_DOWN(VK_LEFT) && !KEY_DOWN(VK_UP) && !KEY_DOWN(VK_DOWN) && !KEY_DOWN(VK_RIGHT))
			{
				clrscr();
				if (lt == 0)
				{ link5(bx, by); lt = 1; _getch; }
				else
				{ link6(bx, by); lt = 0; _getch; }
			}

			if (KEY_DOWN(VK_UP) && !KEY_DOWN(VK_LEFT) && !KEY_DOWN(VK_RIGHT) && !KEY_DOWN(VK_DOWN))
			{
				clrscr();
				if (lt == 0)
				{ link7(bx, by); lt = 1; _getch; }
				else
				{ link8(bx, by); lt = 0; _getch; }
			}

			//The following four if statements set the animations for the diagonals

			if (KEY_DOWN(VK_UP) && KEY_DOWN(VK_LEFT))
			{
				clrscr();
				if (lt == 0)
				{ link5(bx, by); lt = 1; _getch; }
				else
				{ link6(bx, by); lt = 0; _getch; }
			}

			if (KEY_DOWN(VK_UP) && KEY_DOWN(VK_RIGHT))
			{
				clrscr();
				if (lt == 0)
				{ link3(bx, by); lt = 1; _getch; }
				else
				{ link4(bx, by); lt = 0; _getch; }
			}

			if (KEY_DOWN(VK_DOWN) && KEY_DOWN(VK_LEFT))
			{
				clrscr();
				if (lt == 0)
				{ link5(bx, by); lt = 1; _getch; }
				else
				{ link6(bx, by); lt = 0; _getch; }
			}

			if (KEY_DOWN(VK_DOWN) && KEY_DOWN(VK_RIGHT))
			{
				clrscr();
				if (lt == 0)
				{ link3(bx, by); lt = 1; _getch; }
				else
				{ link4(bx, by); lt = 0; _getch; }
			}
		}
	}

	while (!KEY_DOWN(VK_ESCAPE));
}

void randomblocks()
{
	int x = 0, y = 0;                       //the co-ordinates used to draw the random blocks, and the first line in the matrix function
	int x2 = 0, y2 = 0;                     //the co-ordinates used to draw the second line in the matrix function
	int x3 = 0, y3 = 0;                     //the co-ordinates used to draw the third line in the matrix function
	int x4 = 0, y4 = 0;                     //the co-ordinates used to draw the fourth (black/removal) line in the matrix function
	int choice2;                            //the variable for holding the users menu choice for the randomblocks menu
	bool line2 = 0, line3 = 0, line4 = 0;   //switches to activate and deactive the drawing of each line in the matrix function

	DWORD   t1, t2;

	srand((unsigned)time(NULL));

	do
	{
		clrscr(); textcolor(10);                                            //clear the menu screen, set the text colour to green
		cout << "Press (1) for random blocks of a random colour";
		cout << "\nPress (2) for matrix random blocks";
		cout << "\n\nEnter 1 or 2";
		cout << "\n\nPress (ESC) at any time to return to the main menu";

		choice2 = _getch();                                                 //set the variable "choice2" to the users input
	} while (choice2 != '1' && choice2 != '2' && !KEY_DOWN(VK_ESCAPE));     //if the user doesn't input one of the available options, loop back to the start of this menu

	if (choice2 == '1')
	{
		clrscr(); choice2 = '0';                                            //clear the screen and set the menu variable "choice2" back to '0'
		cout << "Random coloured blocks are drawn at random positions on the screen.";
		cout << "\nPress the Space Bar at anytime to clear the screen and start again";
		cout << "\n\nPress any key to start";
		_getch(); clrscr();                                               //wait for any user input before clearing the screen continuing
		t1 = GetTickCount();

		do
		{
			t2 = GetTickCount();

			if (t2 - t1 > 10)							//compares tick counts to set refresh rate
			{
				t1 = t2;                                //reset the two tick counters

				x = rand() % 80; y = rand() % 50; color = rand() % 16;     //set "x" to a random value between 0 and 79, set "y" to a random value between 0 and 49, set "color" to a random value between 0 and 15
                gotoxy(x, y); textcolor(color); cout << z1;                //go to position "x,y", change the text colour to the value in the "color" variable and print z1 which is currently a solid block (219)
			}       

			if (KEY_DOWN(VK_SPACE)) { clrscr(); }      //if the user presses the space bar at any time; clear the screen
		} while (!KEY_DOWN(VK_ESCAPE));                //exit the function and return to the sub menu                                   
	}

	if (choice2 == '2')
	{
		clrscr(); choice2 = '0';
		cout << "This program simulates the screen from The Matrix";
		cout << "\n\nThree lines are drawn at random positions, from top to bottom of the screen.";
		cout << "\nThey can consist of 1 of 8 random symbols and 1 of 3 random colours";
		cout << "\nA single black line is also drawn, to represent the screen clearing a line.";
		cout << "\n\nPress any key to start";
		_getch(); clrscr();

		do
		{
			y = 0; x = rand() % 80;         //set "y" to 0 and "x" to a random value between 0 and 79

			for (y = 0; y < 49; y++)        //requirements for drawing the first line, start at "y = 0" and increment "y" until it reaches the bottom of the screen
			{
				if (y == 16)                //requirements for drawing the second line, once the first line is 16 cells down, begin the second line
				{ y2 = 0; x2 = rand() % 80; line2 = 1; }     //set "y2" to 0 and "x2" to a random value between 0 and 79, set the switch to begin drawing line 2 to true (1)
				
				if (line2 == 1 && y2 < 49)                   //once "line2" is true start drawing, until the second line has reached the bottom of the screen
				{ MatrixRand(); gotoxy(x2, y2); cout << z1; y2 = y2++; } //randomise the colour and symbol, go to the next position and print to screen , increase y2 by 1
                else { line2 = 0; }        //once line 2 has been drawn down to the bottom of the screen, set the line 2 switch to false (0)
                
				if (y == 32)               //requirements for drawing the third line, once the first line is 32 cells down, begin the third line
				{ y3 = 0; x3 = rand() % 80; line3 = 1; }  //set "y3" to 0 and "x3" to a random value between 0 and 79, set the switch to begin drawing line 3 to true (1)
				
				if (line3 == 1 && y3 < 49)                 //once "line3" is true start drawing, until the third line has reached the bottom of the screen
				{ MatrixRand(); gotoxy(x3, y3); cout << z1; y3 = y3++; } //randomise the colour and symbol, go to the next position and print to screen , increase y3 by 1
				else { line3 = 0; }         //once line 3 has been drawn down to the bottom of the screen, set the line 3 switch to false (0)

				if (y == 24)                //requirements for drawing the fourth line, once the first line is 24 cells down, begin the fourth line
				{ y4 = 0; x4 = rand() % 80; line4 = 1; }  //set "y4" to 0 and "x4" to a random value between 0 and 79, set the switch to begin drawing line 4 to true (1)
				
				if (line4 == 1 && y4 < 49)  //once "line4" is true start drawing, until the fourth line has reached the bottom of the screen
				{ textcolor(0); gotoxy(x4, y4); cout << z1; y4 = y4++; } //set the text colour to black, go to "x4,y4", print a black symbol to erase that space
		    	else { line4 = 0; }         //once line 4 has been drawn down to the bottom of the screen, set the line 4 switch to false (0)

				MatrixRand(); gotoxy(x, y); cout << z1; Sleep(3);        //go to "x,y" and print the random symbol in a random colour, wait
	    	}                                     //the if statements for drawing lines 2,3 and 4 had to be included within the for statement for the first line so that they didnt all draw one at a time
		} while (!KEY_DOWN(VK_ESCAPE));           //if the user pushes escape at any time, exit back to the main menu
    }
}

void MatrixRand()
{
	color = rand() % 3;                      //set "color" to a random value between 0 and 2
	if (color == 0) { textcolor(10); }       //if "color" is 0, set the text colour to light green (10)
	if (color == 1) { textcolor(2); }        //if "color" is 1, set the text colour to dark green (2)
	if (color == 2) { textcolor(0); }        //if "color" is 2, set the text colour to black (0)

	symbol = rand() % 8;                     //set "symbol" to a random value between 0 and 7, depending on the result, the symbol to be printed is changed
	if (symbol == 0) { z1 = 157; }
	if (symbol == 1) { z1 = 165; }
	if (symbol == 2) { z1 = 228; }
	if (symbol == 3) { z1 = 225; }
	if (symbol == 4) { z1 = 232; }
	if (symbol == 5) { z1 = 219; }
	if (symbol == 6) { z1 = 234; }
	if (symbol == 7) { z1 = 146; }
}

void GOL()
{
	int choice3;                       //"choice3" is used to store the users menu input choice

	do
	{
		do
		{
			clrscr(); textcolor(10);  //clear the menu screen, set the text colour to green

			cout << "Press (1) for standard game of life";
			cout << "\nPress (2) for game of life with preditors";
			cout << "\nPress (3) for game of life with food resources";
			cout << "\n\nEnter 1, 2 or 3";
			cout << "\n\nPress (ESC) at any time to return to the main menu";
			choice3 = _getch();      //set "choice3" to the user input

		} while (choice3 != '1' && choice3 != '2' && choice3 != '3' && !KEY_DOWN(VK_ESCAPE)); //if the user doesn't enter an available choice, loop back to the start of the menu

		if (choice3 == '1') 
		{
			clrscr(); choice3 = '0';           //clear the menu screen, and set the menu variable "choice3" back to '0' before printing the rules of the game of life
			cout << "This is the standard game of life, the rules are as follows;";
			cout << "\n\n1. Any live cell with fewer than two live neighbours dies.";
			cout << "\n2. Any live cell with two or three neighbours lives on to the next generation.";
			cout << "\n3. Any live cell with more than three live neighbours dies.";
			cout << "\n4. Any dead cell with exactly three live neighbours becomes a live cell.";
			cout << "\n\nEach generation shows for 0.5 second before the next is shown";
			cout << "\n\nPress any key to start the simulation";
			_getch(); textcolor(15); GOL1();  //wait for any user input before coninuing, change the text colour to white, run the first game of life function
		}

		if (choice3 == '2')
		{
			clrscr(); choice3 = '0';          //clear the menu screen, and set the menu variable "choice3" back to '0' before printing the rules of the second game of life
			cout << "This is my preditor version of the game of life, the rules are as follows;";
			cout << "\n\nRabbits Rules (Prey - Green Block)";
			cout << "\n\n1. Any rabbit cell with fewer than two rabbit neighbours dies.";
			cout << "\n2. A rabbit cell with two or three neighbours lives on to the next generation.";
			cout << "\n3. Any rabbit cell with more than three rabbit neighbours dies.";
			cout << "\n4. Any dead cell with two or three rabbit neighbours becomes a rabbit cell.";
			cout << "\n\nFox Rules (Preditor - Red Block)";
			cout << "\n\n1. Any fox cell with more than four fox neighbours dies.";
			cout << "\n2. Any rabbit cell with two or more fox neighbours becomes a fox.";
			cout << "\n3. If a fox has no adjacent rabbits it dies.";
			cout << "\n\nEach generation shows for 0.5 second before the next is shown";
			cout << "\n\nPress any key to start the simulation";
			_getch(); GOL2();               //wait for any user input before coninuing, then run the second game of life function
		}

		if (choice3 == '3')
		{
			clrscr(); choice3 = '0';        //clear the menu screen, and set the menu variable "choice3" back to '0' before printing the rules of the third game of life
			cout << "This is my version of the game of life with food resources;";
			cout << "\n\nEach position on the grid starts with three random values for;";
			cout << "\n\n 1. How much 'Grass' there is (0 - 90)";
			cout << "\n 2. If a 'Rabbit' is occupying the space (0 or 1)";
			cout << "\n 3. What the 'Rabbit's starting health is (50 -100)";
			cout << "\n\nEvery generation the 'Grass' in each cell grows by 5 and, any 'Rabbits' that are";
			cout << "alive randomly move to any of the 8 surrounding cells, or stay where they are.";
			cout << "\nBefore the 'Rabbit' moves it loses 8 health from growing older.";
			cout << "\nIf a 'Rabbit' is on a cell which has more than 25 'Grass' available, ";
			cout << "\nthe 'Rabbit' eats some, reducing the value by 25 and increasing the 'Rabbits'";
			cout << "\nhealth by 15. If at any point a 'Rabbits' health should reach zero it dies.";
			cout << "\n\nThe 'Grass' value is represented as the background colour.";
			cout << "\nBlack is 0-29, Dark Green is 30-60 and Light Green is 61-90";
			cout << "\n\nThe 'Rabbits' are represented as a small red square ontop of the grass";
			cout << "\n\nEach generation shows for 0.5 second before the next is shown";
			cout << "\n\nPress any key to start the simulation";
			_getch(); GOL3();            //wait for any user input before coninuing, then run the third game of life function
		}

	} while (!KEY_DOWN(VK_ESCAPE));      //if the user pushes escape at any time return to the main menu
}

void GOL1()
{
	srand((unsigned)time(NULL));        //randomise the random number generator
	
	for (x = 0; x<80; x++)
	{
		for (y = 0; y<50; y++)
		{
			a[x][y] = rand() % 2;       //for every position on the 80 by 50 array, set the variable a to a random number of either 0 or 1 
		}
	}
 
	do
	{
		Sleep(500); clrscr();           //wait for 0.5 of a second, then clear the screen
		
		for (x = 0; x<80; x++)     
		{
			for (y = 0; y<50; y++)
			{
				gotoxy(x, y); if (a[x][y] == 1) cout << z1;   //go to each position of the 80 by 50 array, if the a value is 1, print a solid block to the screen
			}
		}
		                                //calculate next generation
		for (x = 1; x<79; x++)
		{
			for (y = 1; y<49; y++)
			{
				c = 0;                          //"c" counts the amount of "alive" cells surrounding the current position, if any position has a value of 1, "c" is increased by 1
				if (a[x - 1][y - 1] == 1) c++;  //top left
				if (a[x    ][y - 1] == 1) c++;  //top middle
				if (a[x + 1][y - 1] == 1) c++;  //top right
				if (a[x - 1][y    ] == 1) c++;  //middle left
				if (a[x + 1][y    ] == 1) c++;  //middle right
				if (a[x - 1][y + 1] == 1) c++;  //bottom left
				if (a[x    ][y + 1] == 1) c++;  //bottom middle
				if (a[x + 1][y + 1] == 1) c++;  //bottom right
				                                                         //these are the rules of the game of life, their values are set into the second array "b"
				if (a[x  ][y  ] == 1 && c < 2)              b[x][y] = 0; //If the alive cell has less than two neighbours kill it
				if (a[x  ][y  ] == 1 && (c == 2 || c == 3)) b[x][y] = 1; //If the alive cell has exactly 2 or 3 neighbours it survives
				if (a[x  ][y  ] == 1 && c > 3)              b[x][y] = 0; //If the alive cell has more than three neighbours kill it
				if (a[x  ][y  ] == 0 && c == 3)             b[x][y] = 1; //If the dead cell has exactly three neighbours give it life
			}
		}
		                            
		for (x = 0; x<80; x++)
		{
			for (y = 0; y<50; y++)
			{
				a[x][y] = b[x][y];      //copy all of values from the "b" array into the "a" array
            }
		}
	} while (!KEY_DOWN(VK_ESCAPE));     //if the user presses escape at anytime return to the above menu
}

void GOL2()
{
	srand((unsigned)time(NULL));        //randomise the random number generator
	
	for (x = 0; x<80; x++)
	{
		for (y = 0; y<50; y++)
		{
			a[x][y] = rand() % 3;      //for every position on the 80 by 50 array, set the variable a to a random number of either 0,1 or 2
		}
	}

	do
	{
		Sleep(500); clrscr();          //wait for 0.5 of a second, then clear the screen

		for (x = 0; x<80; x++)
		{
			for (y = 0; y<50; y++)
			{
				gotoxy(x, y);                                      //go to the next cell in the array
				if (a[x][y] == 1) textcolor(10), cout << z1;       //if the array position contains a value of 1 draw a green block
                if (a[x][y] == 2) textcolor(4), cout << z1;        //if the array position contains a value of 2 draw a red block
			}                                                      //if the value is 0, leave the space blank
		}
														//calculate next generation
		for (x = 1; x<79; x++)
		{
			for (y = 1; y<49; y++)
			{
				c = 0, d = 0;					//"c" is the variable which holds the amount of rabbit cells around x,y."d" is the variable which holds the amount of fox cells around x,y
												//this is the check for how many rabbit cells surround x,y, c is incremented by 1 for each one detected
				if (a[x - 1][y - 1] == 1) c++;	//top left
				if (a[x    ][y - 1] == 1) c++;	//top middle
				if (a[x + 1][y - 1] == 1) c++;	//top right
				if (a[x - 1][y    ] == 1) c++;	//middle left
				if (a[x + 1][y    ] == 1) c++;	//middle right
				if (a[x - 1][y + 1] == 1) c++;	//bottom left
				if (a[x    ][y + 1] == 1) c++;	//bottom middle
				if (a[x + 1][y + 1] == 1) c++;	//bottom right
				                                //this is the check for how many foxes surround the current position of x,y, d is incremented by 1 for each one detected       
				if (a[x - 1][y - 1] == 2) d++;	//top left
				if (a[x    ][y - 1] == 2) d++;	//top middle
				if (a[x + 1][y - 1] == 2) d++;	//top right
				if (a[x - 1][y    ] == 2) d++;	//middle left
				if (a[x + 1][y    ] == 2) d++;	//middle right
				if (a[x - 1][y + 1] == 2) d++;	//bottom left
				if (a[x    ][y + 1] == 2) d++;	//bottom middle
				if (a[x + 1][y + 1] == 2) d++;	//bottom right

												                     //rabbit rules
				if (a[x][y] == 1 && c<2)                b[x][y] = 0; //If x,y is a rabbit cell and has less than two neighbours kill it
				if (a[x][y] == 1 && (c == 2 || c == 3)) b[x][y] = 1; //If x,y is a rabbit cell and has exactly 2 or 3 neighbours it survives
				if (a[x][y] == 1 && c>3)                b[x][y] = 0; //If x,y is a rabbit cell and has more than three neighbours kill it
				if (a[x][y] == 0 && (c == 3 || c == 2)) b[x][y] = 1; //If x,y is a dead cell has exactly two or three neighbours give it life
                 													 //fox rules
				if (a[x][y] == 2 && d>4) b[x][y] = 0;				 //If the fox cell has more than four fox neighbours kill it
				if (a[x][y] == 1 && d>1) b[x][y] = 2;				 //If an rabbit has at least 1 fox adjacent, change cell to a fox
				if (a[x][y] == 2 && c<1) b[x][y] = 0;				 //If a fox has no adjacent chickens it dies.
			}
		}
		                              
		for (x = 0; x<80; x++)
		{
			for (y = 0; y<50; y++)
			{
				a[x][y] = b[x][y];     //copy all of values from the "b" array into the "a" array
			}
		}
	} while (!KEY_DOWN(VK_ESCAPE));
}

void GOL3()
{
	int g[80][50];         //an 80 by 50 array contain the grass values
	int tx, ty;            //temporary values for x and y
	int GG = 5;            //grass growth rate
	char z2 = 254;         //the character for the small red square used to reprisent the rabbits

	struct rabbit {        //an 80 by 50 array containing variables for the rabbits health and status of wether it's alive
		int h;
		int a;
	} r[80][50];           

	srand((unsigned)time(NULL));  //randomise the random number generator

	for (x = 0; x<80; x++)
	{
		for (y = 0; y<50; y++)
		{                        //set the grass values between 0 and 90, the rabbit alive status to either 1 or 0 and the rabbit health between 50 and 100
			g[x][y] = rand() % 91; r[x][y].a = rand() % 2; r[x][y].h = 50 + rand() % 51; 
		}
	}
	
	do
	{
		Sleep(500); clrscr();  //wait for 0.5 of a second before continuing, then clear the screen
	    
		for (x = 0; x<79; x++)
		{
			for (y = 0; y<49; y++)
            {
				gotoxy(x, y);                                        //go to the next position of x,y
				if (g[x][y] < 30 && r[x][y].a == 0)                 
				{ textcolor(0); cout << z1;}                         //if the grass value is less than 30 and the rabbit is dead print a black solid block

				if (g[x][y] < 61 && g[x][y] > 29 && r[x][y].a == 0)
				{textcolor(2); cout << z1; }                         //if the grass value is between 30 and 60 and the rabbit is dead print a dark green solid block

				if (g[x][y] > 60 && r[x][y].a == 0)
				{ textcolor(10); cout << z1; }                       //if the grass value is more than 60 and the rabbit is dead print a light green solid block

				if (g[x][y] < 30 && r[x][y].a == 1)                 
				{ textcolor(4); cout << z2; }                        //if the grass value is less than 30 and the rabbit is alive print a red square on a black background

				if (g[x][y] < 61 && g[x][y] > 29 && r[x][y].a == 1)
				{ textcolor(36); cout << z2; }                      //if the grass value is between 30 and 60 and the rabbit is alive print a red square on a dark green background

				if (g[x][y] > 60 && r[x][y].a == 1)
				{ textcolor(164); cout << z2; }                     //if the grass value is more than 60 and the rabbit is alive print a red square on a light green background
			}
		}
		                                                  //calculate next generation
		for (x = 0; x<80; x++)
		{
			for (y = 0; y<50; y++)
			{
				r[x][y].h = r[x][y].h - 8;                //every iteration reduce the rabbit health by 8
				if (r[x][y].h < 1) r[x][y].a = 0;         //if a rabbit's health value drops below 1, set the alive status to 0 (dead)

				c = rand() % 9;                           //set "c" to a random number between 0 and 8
				                                          //the "c" variable chooses which direction the rabbit will move and sets the "tx,ty" variables to it's new planned position
				if (c == 0) { tx = x - 1, ty = y - 1; }   
				if (c == 1) { tx = x    , ty = y - 1; }
				if (c == 2) { tx = x + 1, ty = y - 1; }
				if (c == 3) { tx = x - 1, ty = y    ; }
				if (c == 4) { tx = x    , ty = y    ; }   //this option is to for the rabbit to stay in its current position
				if (c == 5) { tx = x + 1, ty = y    ; }
				if (c == 6) { tx = x - 1, ty = y + 1; }
				if (c == 7) { tx = x    , ty = y + 1; }
				if (c == 8) { tx = x + 1, ty = y + 1; }
				if (tx < 0) { tx = 80; }                 //if a rabbit tries to move past the boundry of the screen is wraped back to the opposite side
				if (tx > 80) { tx = 0; }
				if (ty < 0) { ty = 50; }
				if (ty > 50) { tx = 0; }

				if (g[x][y]>25 && r[x][y].a == 1)         //if there is enough grass for the rabbit to eat
				{
					g[x][y] = g[x][y] - 25;               //reduce grass value by 25
					r[x][y].h = r[x][y].h + 15;           //increase the rabbit health by 15
					if (r[x][y].h > 100) r[x][y].h = 100; //limit max health to 100
				}

				if (r[tx][ty].a == 0)                     //if the temporary position is not currently occupied 
				{ r[tx][ty] = r[x][y]; r[x][y].a = 0; }  //move the rabbit to the new position and mark the space as free in the original position
				
				if (r[tx][ty].a == 1) {}                  //if the temporary position is currently occupied, the rabbit does not move this generation
				 
				if (g[x][y] > 90) g[x][y] = 90;           //limits the maximum grass value to 90 
				
				g[x][y] = g[x][y] + GG;                   //increase the value in the grass array, at the current position, by the value of "GG" (currently 5)
			}
		}
	} while (!KEY_DOWN(VK_ESCAPE));                      //if the user presses escape at any time, exit to the previous menu
	                                                     //upon exiting, there are artifacts left when returning to the main menu, which would not clear with the "clrscr()" function
	for (x = 0; x < 79; x++)                             //to remedy this, I print a black block to every space on the grid before returning to the main manu
	{
		for (y = 0; y < 49; y++)
		{
			textcolor(0); gotoxy(x, y); cout << z1;
		}
	}
}

void link1(int x, int y)				//The link1 to link8 functions are the instructions for drawing each of the 8 frames, 2 for each direction
{

	// Head BG
	hline(x + 4, y, 6, 2);
	hline(x + 3, y + 1, 8, 2);
	gotoxy(x + 3, y + 2); cout << z1;
	gotoxy(x + 10, y + 2); cout << z1;
	hline(x + 4, y + 4, 6, 6);
	hline(x + 1, y + 5, 12, 6);
	hline(x + 4, y + 2, 6, 14);
	hline(x + 3, y + 3, 8, 14);
	gotoxy(x + 3, y + 4); cout << z1;
	gotoxy(x + 3, y + 5); cout << z1;
	gotoxy(x + 10, y + 4); cout << z1;
	gotoxy(x + 10, y + 5); cout << z1;
	hline(x + 2, y + 6, 10, 6);
	hline(x + 4, y + 7, 6, 6);
	hline(x + 5, y + 8, 4, 6);

	// Ears
	gotoxy(x + 1, y + 3); cout << z1;
	gotoxy(x + 12, y + 3); cout << z1;
	gotoxy(x + 1, y + 4); cout << z1;
	gotoxy(x + 12, y + 4); cout << z1;

	// Eyes and Mouth
	textcolor(2);
	gotoxy(x + 5, y + 4); cout << z1;
	gotoxy(x + 8, y + 4); cout << z1;
	textcolor(14);
	gotoxy(x + 5, y + 5); cout << z1;
	gotoxy(x + 8, y + 5); cout << z1;
	gotoxy(x + 6, y + 7); cout << z1;
	gotoxy(x + 7, y + 7); cout << z1;
	gotoxy(x + 12, y + 6); cout << z1;
	gotoxy(x + 12, y + 7); cout << z1;
	gotoxy(x + 11, y + 7); cout << z1;

	//Body BG
	textcolor(2);
	gotoxy(x + 3, y + 7); cout << z1;
	gotoxy(x + 10, y + 7); cout << z1;
	hline(x + 9, y + 8, 3, 2);
	hline(x + 6, y + 9, 6, 2);
	hline(x + 9, y + 10, 2, 2);
	gotoxy(x + 7, y + 11); cout << z1;
	gotoxy(x + 11, y + 11); cout << z1;
	hline(x + 9, y + 12, 3, 2);
	hline(x + 4, y + 13, 7, 2);
	textcolor(14);
	hline(x + 7, y + 10, 2, 14);
	gotoxy(x + 11, y + 10); cout << z1;
	hline(x + 8, y + 11, 3, 14);
	hline(x + 7, y + 12, 2, 14);
	gotoxy(x + 11, y + 13); cout << z1;
	hline(x + 9, y + 14, 3, 14);
	hline(x + 9, y + 15, 3, 14);
	gotoxy(x + 3, y + 13); cout << z1;
	hline(x + 3, y + 14, 3, 14);
	textcolor(6);

	//Arm
	gotoxy(x + 12, y + 8); cout << z1;
	gotoxy(x + 12, y + 9); cout << z1;

	//Sheild
	hline(x + 1, y + 8, 5, 14);
	hline(x, y + 9, 7, 14);
	hline(x, y + 10, 6, 14);
	hline(x, y + 11, 6, 14);
	hline(x, y + 12, 6, 14);
	hline(x, y + 13, 6, 14);
	hline(x + 1, y + 14, 5, 6);
	vline(x + 6, y + 10, 4, 6);
	hline(x + 1, y + 10, 3, 6);
	vline(x + 2, y + 9, 4, 6);
}

void link2(int x, int y)
{

	// Head BG
	hline(x + 4, y, 6, 2);
	hline(x + 3, y + 1, 8, 2);
	gotoxy(x + 3, y + 2); cout << z1;
	gotoxy(x + 10, y + 2); cout << z1;
	hline(x + 4, y + 4, 6, 6);
	hline(x + 1, y + 5, 12, 6);
	hline(x + 4, y + 2, 6, 14);
	hline(x + 3, y + 3, 8, 14);
	gotoxy(x + 3, y + 4); cout << z1;
	gotoxy(x + 3, y + 5); cout << z1;
	gotoxy(x + 10, y + 4); cout << z1;
	gotoxy(x + 10, y + 5); cout << z1;
	hline(x + 2, y + 6, 10, 6);
	hline(x + 4, y + 7, 6, 6);
	hline(x + 5, y + 8, 4, 6);

	// Ears
	gotoxy(x + 1, y + 3); cout << z1;
	gotoxy(x + 12, y + 3); cout << z1;
	gotoxy(x + 1, y + 4); cout << z1;
	gotoxy(x + 12, y + 4); cout << z1;

	// Eyes and Mouth
	textcolor(2);
	gotoxy(x + 5, y + 4); cout << z1;
	gotoxy(x + 8, y + 4); cout << z1;
	textcolor(14);
	gotoxy(x + 5, y + 5); cout << z1;
	gotoxy(x + 8, y + 5); cout << z1;
	gotoxy(x + 6, y + 7); cout << z1;
	gotoxy(x + 7, y + 7); cout << z1;
	gotoxy(x + 12, y + 6); cout << z1;
	gotoxy(x + 12, y + 7); cout << z1;
	gotoxy(x + 11, y + 7); cout << z1;

	//Body BG
	textcolor(2);
	gotoxy(x + 3, y + 7); cout << z1;
	gotoxy(x + 10, y + 7); cout << z1;
	hline(x + 9, y + 8, 3, 2);
	hline(x + 6, y + 9, 6, 2);
	hline(x + 9, y + 10, 2, 2);
	gotoxy(x + 7, y + 11); cout << z1;
	gotoxy(x + 11, y + 11); cout << z1;
	hline(x + 9, y + 12, 3, 2);
	hline(x + 4, y + 13, 7, 2);
	textcolor(14);
	hline(x + 7, y + 10, 2, 14);
	gotoxy(x + 11, y + 10); cout << z1;
	gotoxy(x + 6, y + 12); cout << z1;
	hline(x + 8, y + 11, 3, 14);
	hline(x + 7, y + 12, 2, 14);
	gotoxy(x + 11, y + 13); cout << z1;
	hline(x + 9, y + 14, 3, 14);
	gotoxy(x + 3, y + 13); cout << z1;
	hline(x + 3, y + 14, 3, 14);
	hline(x + 3, y + 15, 3, 14);
	textcolor(6);

	//Arm
	gotoxy(x + 12, y + 11); cout << z1;
	gotoxy(x + 12, y + 12); cout << z1;

	//Sheild
	hline(x + 1, y + 6, 5, 14);
	hline(x, y + 7, 7, 14);
	hline(x, y + 8, 6, 14);
	hline(x, y + 9, 6, 14);
	hline(x, y + 10, 6, 14);
	hline(x, y + 11, 6, 14);
	hline(x + 1, y + 12, 5, 6);
	vline(x + 6, y + 8, 4, 6);
	hline(x + 1, y + 8, 3, 6);
	vline(x + 2, y + 7, 4, 6);
}

void link3(int x, int y)
{

	// Head BG
	hline(x + 5, y, 4, 2);
	hline(x + 3, y + 1, 5, 2);
	hline(x + 1, y + 2, 6, 2);
	hline(x, y + 3, 4, 2);
	textcolor(2);
	gotoxy(x, y + 4); cout << z1;
	gotoxy(x + 2, y + 4); cout << z1;
	gotoxy(x + 3, y + 4); cout << z1;
	gotoxy(x + 2, y + 5); cout << z1;
	hline(x + 8, y + 1, 4, 14);
	hline(x + 7, y + 2, 6, 14);
	hline(x + 6, y + 3, 6, 14);
	textcolor(6);
	gotoxy(x + 4, y + 2); cout << z1;
	hline(x + 4, y + 3, 2, 6);
	hline(x + 4, y + 4, 8, 6);
	hline(x + 5, y + 5, 7, 6);
	hline(x + 6, y + 6, 8, 6);
	hline(x + 8, y + 7, 4, 6);

	// Head features
	hline(x + 3, y + 5, 2, 14);
	hline(x + 3, y + 6, 3, 14);
	vline(x + 7, y + 4, 2, 14);
	textcolor(2);
	gotoxy(x + 10, y + 4); cout << z1;
	textcolor(14);
	gotoxy(x + 10, y + 5); cout << z1;

	//Body
	hline(x + 4, y + 7, 4, 2);
	hline(x + 3, y + 8, 7, 2);
	hline(x + 4, y + 9, 7, 2);
	hline(x + 5, y + 10, 6, 2);
	hline(x + 5, y + 11, 5, 2);
	vline(x + 1, y + 9, 3, 14);
	vline(x + 2, y + 8, 4, 14);
	vline(x + 3, y + 9, 4, 14);
	vline(x + 4, y + 10, 3, 14);
	hline(x + 3, y + 12, 8, 14);
	gotoxy(x + 10, y + 11); cout << z1;
	hline(x + 10, y + 8, 3, 14);
	hline(x + 11, y + 9, 2, 14);
	hline(x + 11, y + 10, 2, 14);
	hline(x + 1, y + 13, 10, 2);
	textcolor(2);
	gotoxy(x + 2, y + 12); cout << z1;

	//Hands and shield
	vline(x + 13, y + 9, 2, 6);
	vline(x + 14, y + 7, 8, 14);
	hline(x + 5, y + 8, 3, 6);
	hline(x + 5, y + 9, 3, 6);
	hline(x + 5, y + 10, 2, 6);

	//Foot
	hline(x + 3, y + 14, 4, 14);
	hline(x + 3, y + 15, 5, 14);
}

void link4(int x, int y)
{

	// Head BG
	hline(x + 5, y, 4, 2);
	hline(x + 3, y + 1, 5, 2);
	hline(x + 1, y + 2, 6, 2);
	hline(x, y + 3, 4, 2);
	textcolor(2);
	gotoxy(x, y + 4); cout << z1;
	gotoxy(x + 2, y + 4); cout << z1;
	gotoxy(x + 3, y + 4); cout << z1;
	gotoxy(x + 2, y + 5); cout << z1;
	hline(x + 8, y + 1, 4, 14);
	hline(x + 7, y + 2, 6, 14);
	hline(x + 6, y + 3, 6, 14);
	textcolor(6);
	gotoxy(x + 4, y + 2); cout << z1;
	hline(x + 4, y + 3, 2, 6);
	hline(x + 4, y + 4, 8, 6);
	hline(x + 5, y + 5, 7, 6);
	hline(x + 6, y + 6, 8, 6);
	hline(x + 8, y + 7, 4, 6);

	// Head features
	hline(x + 3, y + 5, 2, 14);
	hline(x + 3, y + 6, 3, 14);
	vline(x + 7, y + 4, 2, 14);
	textcolor(2);
	gotoxy(x + 10, y + 4); cout << z1;
	textcolor(14);
	gotoxy(x + 10, y + 5); cout << z1;

	//Body
	hline(x + 4, y + 7, 4, 2);
	hline(x + 3, y + 8, 7, 2);
	hline(x + 4, y + 9, 7, 2);
	hline(x + 5, y + 10, 6, 2);
	hline(x + 5, y + 11, 5, 2);
	vline(x + 1, y + 9, 3, 14);
	vline(x + 2, y + 8, 4, 14);
	vline(x + 3, y + 9, 4, 14);
	vline(x + 4, y + 10, 3, 14);
	hline(x + 3, y + 12, 8, 14);
	gotoxy(x + 10, y + 11); cout << z1;
	hline(x + 10, y + 8, 3, 14);
	hline(x + 11, y + 9, 2, 14);
	hline(x + 11, y + 10, 2, 14);
	hline(x + 1, y + 13, 10, 2);
	textcolor(2);
	gotoxy(x + 2, y + 12); cout << z1;

	//Hands and shield
	vline(x + 13, y + 8, 2, 6);
	vline(x + 14, y + 5, 8, 14);
	hline(x + 5, y + 10, 3, 6);
	hline(x + 5, y + 11, 3, 6);
	hline(x + 5, y + 12, 2, 6);

	//Foot
	hline(x + 5, y + 14, 4, 14);
	hline(x + 5, y + 15, 5, 14);
}

void link5(int x, int y)
{

	//Head BG
	hline(x + 6, y, 4, 2);
	hline(x + 7, y + 1, 5, 2);
	hline(x + 8, y + 2, 2, 2);
	vline(x + 11, y + 1, 4, 2);
	vline(x + 12, y + 2, 4, 2);
	vline(x + 13, y + 2, 2, 2);
	vline(x + 14, y + 3, 2, 2);
	hline(x + 3, y + 1, 4, 14);
	hline(x + 2, y + 2, 6, 14);
	hline(x + 3, y + 3, 6, 14);
	vline(x + 10, y + 2, 3, 6);
	vline(x + 9, y + 3, 3, 6);
	hline(x + 3, y + 4, 8, 6);
	hline(x + 3, y + 5, 7, 6);
	hline(x + 1, y + 6, 8, 6);
	hline(x + 3, y + 7, 4, 6);
	hline(x + 10, y + 5, 2, 14);
	hline(x + 9, y + 6, 3, 14);

	//Head features
	vline(x + 7, y + 4, 2, 14);
	textcolor(2);
	gotoxy(x + 4, y + 4); cout << z1;
	textcolor(14);
	gotoxy(x + 4, y + 5); cout << z1;

	//Body
	hline(x + 7, y + 7, 4, 2);
	hline(x + 5, y + 8, 7, 2);
	hline(x + 4, y + 9, 7, 2);
	hline(x + 4, y + 10, 6, 2);
	hline(x + 5, y + 11, 5, 2);
	hline(x + 2, y + 8, 3, 14);
	hline(x + 2, y + 9, 2, 14);
	hline(x + 2, y + 10, 2, 14);
	gotoxy(x + 4, y + 11); cout << z1;
	hline(x + 4, y + 12, 8, 14);
	vline(x + 10, y + 10, 3, 14);
	vline(x + 11, y + 9, 4, 14);
	vline(x + 12, y + 8, 4, 14);
	vline(x + 13, y + 9, 3, 14);
	hline(x + 4, y + 13, 10, 2);
	textcolor(2);
	gotoxy(x + 12, y + 12); cout << z1;

	//Hands and Shield
	vline(x, y + 7, 2, 14);
	vline(x, y + 9, 6, 6);
	vline(x + 1, y + 9, 2, 6);
	hline(x + 7, y + 8, 3, 6);
	hline(x + 7, y + 9, 3, 6);
	hline(x + 8, y + 10, 2, 6);

	//Foot
	hline(x + 8, y + 14, 4, 14);
	hline(x + 7, y + 15, 5, 14);
}

void link6(int x, int y)
{

	//Head BG
	hline(x + 6, y, 4, 2);
	hline(x + 7, y + 1, 5, 2);
	hline(x + 8, y + 2, 2, 2);
	vline(x + 11, y + 1, 4, 2);
	vline(x + 12, y + 2, 4, 2);
	vline(x + 13, y + 2, 2, 2);
	vline(x + 14, y + 3, 2, 2);
	hline(x + 3, y + 1, 4, 14);
	hline(x + 2, y + 2, 6, 14);
	hline(x + 3, y + 3, 6, 14);
	vline(x + 10, y + 2, 3, 6);
	vline(x + 9, y + 3, 3, 6);
	hline(x + 3, y + 4, 8, 6);
	hline(x + 3, y + 5, 7, 6);
	hline(x + 1, y + 6, 8, 6);
	hline(x + 3, y + 7, 4, 6);
	hline(x + 10, y + 5, 2, 14);
	hline(x + 9, y + 6, 3, 14);

	//Head features
	vline(x + 7, y + 4, 2, 14);
	textcolor(2);
	gotoxy(x + 4, y + 4); cout << z1;
	textcolor(14);
	gotoxy(x + 4, y + 5); cout << z1;

	//Body
	hline(x + 7, y + 7, 4, 2);
	hline(x + 5, y + 8, 7, 2);
	hline(x + 4, y + 9, 7, 2);
	hline(x + 4, y + 10, 6, 2);
	hline(x + 5, y + 11, 5, 2);
	hline(x + 2, y + 8, 3, 14);
	hline(x + 2, y + 9, 2, 14);
	hline(x + 2, y + 10, 2, 14);
	gotoxy(x + 4, y + 11); cout << z1;
	hline(x + 4, y + 12, 8, 14);
	vline(x + 10, y + 10, 3, 14);
	vline(x + 11, y + 9, 4, 14);
	vline(x + 12, y + 8, 4, 14);
	vline(x + 13, y + 9, 3, 14);
	hline(x + 4, y + 13, 10, 2);
	textcolor(2);
	gotoxy(x + 12, y + 12); cout << z1;

	//Hands and Shield
	vline(x, y + 5, 2, 14);
	vline(x, y + 7, 6, 6);
	vline(x + 1, y + 8, 2, 6);
	hline(x + 7, y + 10, 3, 6);
	hline(x + 7, y + 11, 3, 6);
	hline(x + 8, y + 12, 2, 6);

	//Foot
	hline(x + 6, y + 14, 4, 14);
	hline(x + 5, y + 15, 5, 14);
}

void link7(int x, int y)
{

	//Head
	hline(x + 4, y, 6, 2);
	hline(x + 3, y + 1, 8, 2);
	hline(x + 3, y + 2, 8, 2);
	hline(x + 4, y + 3, 6, 2);
	hline(x + 5, y + 4, 4, 2);
	hline(x + 6, y + 5, 2, 2);
	vline(x + 3, y + 3, 3, 14);
	vline(x + 4, y + 4, 3, 14);
	vline(x + 5, y + 5, 2, 14);
	vline(x + 6, y + 6, 2, 14);
	vline(x + 7, y + 6, 2, 14);
	vline(x + 8, y + 5, 2, 14);
	vline(x + 9, y + 4, 3, 14);
	vline(x + 10, y + 3, 3, 14);
	vline(x + 1, y + 3, 3, 6);
	vline(x + 2, y + 5, 2, 6);
	vline(x + 3, y + 6, 2, 6);
	hline(x + 3, y + 7, 3, 6);
	hline(x + 8, y + 7, 3, 6);
	vline(x + 10, y + 6, 2, 6);
	vline(x + 11, y + 5, 2, 6);
	vline(x + 12, y + 3, 3, 6);

	//Body
	hline(x + 2, y + 8, 10, 2);
	hline(x + 6, y + 8, 2, 6);
	hline(x + 2, y + 9, 10, 2);
	hline(x + 2, y + 10, 10, 2);
	hline(x + 2, y + 11, 10, 14);
	hline(x + 2, y + 12, 10, 2);
	hline(x + 3, y + 13, 8, 2);
	vline(x + 12, y + 6, 2, 14);
	textcolor(14);
	gotoxy(x + 11, y + 7); cout << z1;
	gotoxy(x + 2, y + 13); cout << z1;
	gotoxy(x + 11, y + 13); cout << z1;

	//Hands and Shield
	vline(x, y + 9, 5, 14);
	vline(x + 1, y + 8, 6, 14);
	textcolor(6);
	gotoxy(x + 1, y + 14); cout << z1;
	vline(x + 12, y + 8, 2, 6);

	//Feet
	hline(x + 2, y + 14, 3, 14);
	hline(x + 2, y + 15, 3, 14);
	hline(x + 9, y + 14, 3, 14);

}

void link8(int x, int y)
{

	//Head
	hline(x + 4, y, 6, 2);
	hline(x + 3, y + 1, 8, 2);
	hline(x + 3, y + 2, 8, 2);
	hline(x + 4, y + 3, 6, 2);
	hline(x + 5, y + 4, 4, 2);
	hline(x + 6, y + 5, 2, 2);
	vline(x + 3, y + 3, 3, 14);
	vline(x + 4, y + 4, 3, 14);
	vline(x + 5, y + 5, 2, 14);
	vline(x + 6, y + 6, 2, 14);
	vline(x + 7, y + 6, 2, 14);
	vline(x + 8, y + 5, 2, 14);
	vline(x + 9, y + 4, 3, 14);
	vline(x + 10, y + 3, 3, 14);
	vline(x + 1, y + 3, 3, 6);
	vline(x + 2, y + 5, 2, 6);
	vline(x + 3, y + 6, 2, 6);
	hline(x + 3, y + 7, 3, 6);
	hline(x + 8, y + 7, 3, 6);
	vline(x + 10, y + 6, 2, 6);
	vline(x + 11, y + 5, 2, 6);
	vline(x + 12, y + 3, 3, 6);

	//Body
	hline(x + 2, y + 8, 10, 2);
	hline(x + 6, y + 8, 2, 6);
	hline(x + 2, y + 9, 10, 2);
	hline(x + 2, y + 10, 10, 2);
	hline(x + 2, y + 11, 10, 14);
	hline(x + 2, y + 12, 10, 2);
	hline(x + 3, y + 13, 8, 2);
	vline(x + 12, y + 6, 2, 14);
	textcolor(14);
	gotoxy(x + 11, y + 7); cout << z1;
	gotoxy(x + 2, y + 13); cout << z1;
	gotoxy(x + 11, y + 13); cout << z1;

	//Hands and Shield
	vline(x, y + 7, 5, 14);
	vline(x + 1, y + 6, 6, 14);
	textcolor(14);
	gotoxy(x + 2, y + 7); cout << z1;
	textcolor(6);
	gotoxy(x + 1, y + 12); cout << z1;
	vline(x + 12, y + 10, 2, 6);

	//Feet
	hline(x + 2, y + 14, 3, 14);
	hline(x + 9, y + 15, 3, 14);
	hline(x + 9, y + 14, 3, 14);

}

void hline(int x, int y, int l, int c)		//This functions allows a horizontal line to be drawn from point x,y with a length l and a colour of c
{
	int i;
    textcolor(c);                           //set the text colour to variable "c"
	for (i = 0; i<l; i++)                   //run the interval for the amount of times specified by length "l"
	{
		gotoxy(i + x, y); cout << z1;       //go to the position given, increasing the "x" value by 1 for every loop, and print the character z1 to the screen
	}
}

void vline(int x, int y, int l, int c)		//This functions allows a vertical line to be drawn from point x,y with a length l and a colour of c
{
	int i;
	textcolor(c);                           //set the text colour to variable "c"
	for (i = 0; i<l; i++)                   //run the loop for the amount of times specified by length "l"
	{
		gotoxy(x, i + y); cout << z1;       //go to the position given, increasing the "y" value by 1 for every loop, and print the character z1 to the screen
	}
}

void textcolor(int c)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
}

void gotoxy(int x, int y)         //define gotoxy function
{
	static HANDLE hStdout = NULL;
	COORD coord;

	coord.X = x;
	coord.Y = y;
	if (!hStdout) { hStdout = GetStdHandle(STD_OUTPUT_HANDLE); }
	SetConsoleCursorPosition(hStdout, coord);
}

void clrscr(void)
{
	static HANDLE hStdout = NULL;
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	const COORD startCoords = { 0,0 };
	DWORD dummy;

	if (!hStdout)
	{
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout, &csbi);
	}
	FillConsoleOutputCharacter(hStdout, ' ', csbi.dwSize.X * csbi.dwSize.Y, startCoords, &dummy);
	gotoxy(0, 0);
}