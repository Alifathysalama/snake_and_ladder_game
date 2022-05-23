#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<dos.h>
#include <math.h>
/*include some basic libraries in c
*
<conio.h> : a header file used in c and cpp and it includes inbuilt functions like getch() and clrscr()

<time. h>header file contains definitions of functions to get and manipulate date and time information

<windows. h> header file is used to access the Win32 API functions and it makes it easier for the user to use the in-built functionality

<dos.h> This library has functions that are used for handling interrupts, producing sound, date and time functions*/
/*
To calculate time taken by a process, we can use clock() function which is available in time.h.
We can call the clock function at the beginning and end of the code for which we measure time, subtract the values,
and then divide by CLOCKS_PER_SEC (the number of clock ticks per second) to get processor time, like following.
*/
int COLORS[] = {12 , 2 , 9}; //colors of each player
int LADDER_SIZE = 9; // size of ladder array
int ladder_positions[] = {4 , 9 , 21 , 28 , 37 , 51 , 72 , 78 , 80}; // ladder positions
int next_ladder_position[] = {14 , 31 , 42 , 84 , 61 , 67 , 91 , 92 , 99}; //the new ladder position
int SNAKE_SIZE = 7; //size of snake array
int snake_positions[] = {17 , 47 , 62, 54 , 87 , 64 , 95}; //positions of snakes in the game
int next_snake_positions[] = {7 , 13, 19 , 25, 36 , 44 , 75}; //next position of player after getting a snake

int findIndex(int arr[] , int size , int value)  // used to check if the index  of the player is either snake or ladder else return -1
{
    int i = 0;
    for(; i < size; i++){
        if(value == arr[i])
            return i;
    }
    return -1;
}

int dice,num_of_player;
int checkposition ();
int pos,player=1,pos1=-1,pos2=-1,pos3=-1, newposition;
char a[20]=" <--- ";                              // array of char to insert your name into later
void insertnode ();		                         // to insert new node to the linked list
void mini_game();                                // the mini game to ease the mode
void game();                                     // the flow of the game
void player_turn();                              // function to control each player turn
void check_num();                                // check the number of player the number
HANDLE hConsole;                                 // coloring the players
struct node                                      // linked list node
{
  int score;
  struct node *next;	                               //creating struct names node to be used in linked list structure
};
struct node *head = NULL;
struct node *createnode ()                    //a function that creates a node using dynamic allocation.
{
  struct node *n;
  n = (struct node *) malloc (sizeof (struct node));
  return (n);
}

void gotoxy (int x, int y)                 //a function used to set the cursor of command window at a specific position
{
  COORD c;
  c.X = x;
  c.Y = y;
  SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
}
void print_screen();                        //print the screen of the game
void print_board();                         // print board in the first
void main()
{
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  clock_t start,end;
  double cpu_time_used;
  start=clock();
  mini_game();
  end=clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("the time used of the mini_game is %fs\n",cpu_time_used);
  print_screen();
  printf ("maximum numbers of players can be 3\n\n");   //the few following line take from user number of player and check if it's right input or not
  again:
  printf ("enter number of players: ");
  scanf ("%d", &num_of_player);
  if(num_of_player>3)
  {
      printf("Maximum number of player is 3\n");
      goto again;
  }
        printf("                     \n\n\nhello , thank you for coming.\n\n                    The rules are simple \n\nyou can press enter to roll the dice\n\nwinner will be the one who gets to 100 first\n\n ");
        printf("\n\nLets start the real game\n\n");
	    print_board();                 //layout of the the board of the game
	    printf("\n\n");
	    start=clock();
        game();                         //the function that contain flow of the
        end=clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("the game to be played time taken is %fs\n",cpu_time_used);
        leadership();                  //the function to print the winner player and the ranks of the player
}
void printLadder(int curPosition , int nextPosition) //if player got a ladder it will send him to the next postion
{
    printf
	  ("\nwell done ,you have landed on a ladder,you are now on position %d.\n",
	   newposition);
        printf( "   %d\n" , curPosition);
        int i = 0;
        for(;i < 6 ; i++)
            printf("  |__|\n" );
		printf("   %d    \n" , nextPosition);

}
void printSnake(int curPosition , int nextPosition)  //if player got a snake it will send him to the next postion
{
    printf
	  ("\nsorry but you have landed on a snake and your new position is %d\n",
	   newposition);
	    printf( "              **    **    **        \n" );
        printf ( "   %d  <<*  *   *  *  *  *  *  *>>  %d \n" , curPosition , nextPosition);
		printf( "          **     **    **    **     \n" );

}
void changePlayerPosition()                          //set the new positions
{
    if(player == 1)
        pos1 = newposition;
    if(player == 2)
        pos2 = newposition;
    if(player == 3)
        pos3 = newposition;
}
int checkposition()		//check if you got a snake or a ladder
{
    int index = -1;
    index = findIndex(snake_positions , SNAKE_SIZE , pos);
    if(index != -1)
    {
        newposition = next_snake_positions[index];
        printSnake(pos , newposition);
        changePlayerPosition();
        return newposition;
    }
    index = findIndex(ladder_positions , LADDER_SIZE , pos);
    if(index != -1)
    {
        newposition = next_ladder_position[index];
        changePlayerPosition();
        printLadder(pos , newposition);
        return newposition;
    }
    printGame();
    return newposition = pos;
}

void insertnode (int player)   //storing the ranks of player
{
  struct node *temp, *t;
  temp = createnode ();
  temp->score = player;
  temp->next = NULL;
  if (head == NULL)
    head = temp;
  else
    {
      t = head;
      while (t->next != NULL)
	{
	  t = t->next;
	}
      t->next = temp;
    }
}

 void print_screen()
{
 printf ("\t\t*                                               *\n");
  printf
    (" -----------------------------------------------------------------------------\n");
  printf
    ("|                                                                            |\n");
  printf
    ("|                                                                            |\n");
  printf
    ("| ######   ######  ######  ######  ######  ######  #      #  ######   ###### |\n");
  printf
    ("| #        #    #  #       #         #       #     # #    #  #        #      |\n");
  printf
    ("| #  ####  ######  #####   #####     #       #     #  #   #  #  ####  ###### |\n");
  printf
    ("| #    #   #  #    #       #         #       #     #   #  #  #    #        # |\n");
  printf
    ("| ######   #   #   ######  ######    #     ######  #    # #  ######   ###### |\n");
  printf
    ("|                                                                            |\n");
  printf
    (" -----------------------------------------------------------------------------\n");
  printf ("\t\t*****************\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*        -----------------------------          *\n");
  printf ("\t\t*         WELCOME TO SNAKE AND LADDER           *\n");
  printf ("\t\t*        -----------------------------          *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*                                               *\n");
  printf ("\t\t*****************\n\n\n");
}

void print_board()
{
printf ("                      welcome to snake and ladder \n\n");
	    printf
	      (" |100  99  98  97  96  95  94  93  92  91|     1=start          4=ladder to 14\n ");
	    printf
	      ("| 81  82  83  84  85  86  87  88  89  90|     9=ladder to 31   17=snake to  7\n ");

	    printf
	      ("| 80  79  78  77  76  75  74  73  72  71|     21=ladder to 42  46=snake to  13\n ");
	    printf
	      ("| 61  62  63  64  65  66  67  68  69  70|     28=ladder to 84  62=snake to  19\n ");
	    printf
	      ("| 60  59  58  57  56  55  54  53  52  51|     37=ladder to 61  54=snake to  25\n ");
	    printf
	      ("| 41  42  43  44  45  46  47  48  49  50|     51=ladder to 67  87=snake to  36\n ");
	    printf
	      ("| 40  39  38  37  36  35  34  33  32  31|     72=ladder to 91  64=snake to  44\n ");
	    printf
	      ("| 21  22  23  24  25  26  27  28  29  30|     78=ladder to 92  95=snake to  75\n ");
	    printf
	      ("| 20  19  18  17  16  15  14  13  12  11|     80=ladder to 99     100=END\n");
	    printf (" |  1   2   3   4   5   6   7   8   9  10|      \n");

}
int getPlayer(int position)     //check what player you are either 1 , 2 or 3
{
    if(position == pos1){
        SetConsoleTextAttribute(hConsole , COLORS[0]);
        return 1;
    }
    if(position == pos2){
        SetConsoleTextAttribute(hConsole , COLORS[1]);
        return 2;
    }
    if(position == pos3){
        SetConsoleTextAttribute(hConsole , COLORS[2]);
        return 3;
    }
}

void printCell(int cell)    //print the player location on the board
{
    if(  cell == pos1 || cell == pos2 || cell == pos3)
    {
        int curPlayer = getPlayer(cell);
        printf("PLAYER #%d  " , curPlayer);
        SetConsoleTextAttribute(hConsole , 15);
        return;
    }

    int cell_length = 11;
    int len = (int) (log(cell) / log(10) + 1);
    printf("%d" , cell);
    int i = len;
    for(; i < cell_length ; i++)
        printf(" ");
}
void printGame()   // print the board of the game after each player's turn
{
    int i = 10;
    for(; i >= 1; i--)
    {
        if(i % 2 == 0)
        {
            int j = 10 * i;
            for(; j > 10 * (i - 1) ; j--)
            {
                printCell(j);
            }
            printf("\n");
        }
        else
        {
            int j = 10 * (i - 1) + 1    ;
            for(; j <= 10 * i ; j++)
            {
                printCell(j);
            }
            printf("\n");
        }
    }
}

void player_turn() //function for each player turn
{
        if(player == 1) pos = pos1;
        else if (player == 2) pos = pos2 ;
        else if (player == 3) pos = pos3;
        int dice;
        printf("\n\nplayer%d turn,",player);
		printf ("press any key to roll the dice\n\n");
		dice -= (getche ());
		dice = ((rand () % 6) + 1);	//gets a value for the dice between 1 and 6
		printf ("you rolled the dice and you got %d\n ", dice);
		generate_dice(dice);
		pos+=dice;
		if(pos>=100)
        {
            pos=100;
        }
		if(player == 1) pos1 = pos;
        else if (player == 2) pos2 = pos ;
        else if (player == 3) pos3 = pos;
		pos = checkposition();
		printf ("\nplayer%d position is: %d\n",player, pos);
		if(pos>=100)
        {
            insertnode(player);
        }
        check_num();
        return;
}
void check_num()   //function to check the number of player the users entered
{
if(num_of_player==1)
        {
            return;
        }
        else if (num_of_player==2)
        {
            if(player==2)
                player =1 ;
            else
                player++;
        }
        else if (num_of_player==3)
        {
            if(player==3)
        {
            player=1;
        }
        else
            player++;

            return;
        }
}

void initializePlayerLocation() //to initialize player location
{
    if(num_of_player >= 1)
        pos1 = 1;
    if(num_of_player >= 2)
        pos2 = 1;
    if(num_of_player >= 3)
        pos3 = 1;

}
void game() //main game body
{    clock_t start,end;
    double cpu_time_used;
    initializePlayerLocation();
     while(1)
    {
        if (num_of_player == 2)
        {
            if(pos1>=100)
            {
                insertnode(2);
                break;
            }
            else if (pos2>=100)
            {
                insertnode(1);
                break;
            }
        }
        if(pos1>=100 && pos2>=100)
        {  if(num_of_player==3)
            {   insertnode(3);
                break;}
            else
                break;
        }
        else if(pos1>=100 && pos3 >=100)
        {
            insertnode(2);
            break;
        }
        else if(pos3>=100 && pos2 >=100)
        {
            insertnode(1);
            break;
        }
        if(player==1)
        {
            if(pos1<100)

            { start=clock();
              player_turn();
              end=clock();
              cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("the player turn time taken %fs\n",cpu_time_used);

            }
            else if (pos1>=100 && num_of_player>=2)
                player=2;
                else
                    break;
        }
        else if (player==2)
        {
            if(pos2<100)
            { start=clock();
              player_turn();
              end=clock();
              cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("the player turn time taken %fs\n",cpu_time_used);

            }
            else if (pos2>=100 && num_of_player == 3)
                player=3;
                else
                    player=1;
        }
        else if (player==3)
        {
            if(pos3<100)
            { start=clock();
              player_turn();
              end=clock();
              cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("the player turn time taken %fs\n",cpu_time_used);

            }
            else if (pos3>=100)
                player=1;
        }
    }
}
void generate_dice(int dice)  //function to print the dice and generate it's value
{
        if (dice == 6)
		  {
		    printf ("_________\n");
		    printf ("|         |\n");
		    printf ("|  O   O  |\n");
		    printf ("|  O   O  |\n|  O   O  |\n|_________|\n");
		  }
		if (dice == 1)
		  {
		    printf ("_________\n");
		    printf ("|         |\n");
		    printf ("|         |\n");
		    printf ("|    O    |\n|         |\n|_________|\n");

		  }
		else if (dice == 2)
		  {
		    printf ("_________\n");
		    printf ("|         |\n");
		    printf ("|  O      |\n");
		    printf ("|         |\n|      O  |\n|_________|\n");
		  }
		else if (dice == 3)
		  {
		    printf ("_________\n");
		    printf ("|         |\n");
		    printf ("|  O      |\n");
		    printf ("|    O    |\n|      O  |\n|_________|\n");
		  }
		else if (dice == 4)
		  {
		    printf ("_________\n");
		    printf ("|         |\n");
		    printf ("|  O   O  |\n");
		    printf ("|         |\n|  O   O  |\n|_________|\n");
		  }
		else if (dice == 5)
		  {
		    printf ("_________\n");
		    printf ("|         |\n");
		    printf ("|  O   O  |\n");
		    printf ("|    O    |\n|  O   O  |\n|_________|\n");
		  }


}

void leadership()         //print the leadership board after the end of the game
{

      printf ("\n\n");
      printf ("\t\t*************************************************\n");
      printf ("\t\t*                                               *\n");
      printf ("\t\t*        -----------------------------          *\n");
      printf ("\t\t*               LEADERSHIP BOARD                *\n");
      printf ("\t\t*        -----------------------------          *\n");
      printf ("\t\t*                                               *\n");
      printf ("\t\t*************************************************\n\n");
      printf ("\nthe player who won the game is player%d ",head->score);
      if(num_of_player==2)
      {
          printf ("\n\nthe list of players is\n");
          printf("\nFirst:player%d\n",head->score);
          printf("\nSecond:player%d\n",head->next->score);
      }
      else if (num_of_player==3)
      {
          printf ("\n\nthe list of players is\n");
          printf("\nFirst:player%d\n",head->score);
          printf("\nSecond:player%d\n",head->next->score);
          printf("\nThird:player%d\n",head->next->next->score);
      }
}

void mini_game()      //the mini game function main body
{
    // system ("color 4E");		// changing the color of command window background to red
  int x = 30, y = 10;
  char ch ;
  printf ("Before playing the game, lets play a mini game\n");
  printf ("\n press enter");
  printf ("\n");
  _getch (); //getch is used to hold the screen until we press a key
  gotoxy (x, y);
  printf ("%s\n", a);		//print player name at position (10,10)
  gotoxy (10, 10);
  printf ("*");
  while (1)
    {

      ch = _getch ();
      switch (ch)
	{
	case 'a':
	  x--;
	  break;
	case 'd':
	  x++;
	  break;
	case 'w':
	  y--;
	  break;
	case 's':
	  y++;
	  break;

	case 27:
	  exit (0);
	}
      system ("cls");
      gotoxy (x, y);
      printf ("%s", a);
      gotoxy (10, 10);
      printf ("*");
      if (x == 10 && y == 10)
	{
	  system ("cls");
	  break;
	}
    }
  /*the above while loop is a mini  game that you can move an arrow around the command window by entering certain keys
     which represents the four dimensions */
}
