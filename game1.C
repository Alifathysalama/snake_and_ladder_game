#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<dos.h>
#include<chrono>
#define size1 2
#define size1 2//size1 represents 2 from now on

/*include some basic libiraries in c
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
struct node
{
    int info;
    struct node* link;    //creating struct names node to be used in linked list structure
};
struct node* start = NULL;
int rear = -1; /* rear and front will be used in definition of queue using arrays    */
int front = -1;
int queue[size1];
int size = 2;
int stack[2];    // creating a stack using array
int top = -1;
void insert1(int); //add the result of each player to be compared later
void display1(); // to print the queue content of players
void push(int); // to add element to stack
void display();//to print the stack content of players
int dice;
int checkposition(); // find out if the position we are at  is ladder or snake
int position, newposition, above;
void viewlist(); //to print the content of linked list
void insertnode(); // to insert new node to the linked list
int choice, count = 0;
int final;
char a[20]; // array of char to insert your name into later

//a function that creates a node using dynamic allocation.
struct node* createnode()
{
    struct node* n;
    n = (struct node*)malloc(sizeof(struct node));
    return (n);
}
//a function used to set the cursor of command window at a specific position
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
main()
{
    system("color 4E");   // changing the color of command window background to red

    int x = 30, y = 10, f, z = 0;
    char ch;
    srand(time(NULL));//Using time(NULL) to set a different seed of random through srand
    clock_t start, end,startmin,endmin;
    double cpu_time_used,timemin;
    start=clock();
    printf("Before playing the game, lets play a mini game\n");
    printf("\n press enter");
    printf("\n");
    _getch();     //getch is used to hold the screen until we press a key
    printf("enter your name:");
    gets(a);    //  insert player name
    printf("now collide your name's first letter with the given dot using the keys\n\n W for up \n S for down\n A for left\n D for right\n");
    gotoxy(x, y);
    printf("%s\n", a);  //print player name at position (10,10)
    gotoxy(10, 10);
    printf("*");

    while (1)
    {

        ch = _getch();
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
            exit(0);
        }
        system("cls");
        gotoxy(x, y);
        printf("%s", a);
        gotoxy(10, 10);
        printf("*");
        if (x == 10 && y == 10)
        {
            system("cls");
            break;
        }
    }
    end=clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nthe mini game took %f seconds to execute \n", cpu_time_used);
    /*the above while loop is a mini  game that you can move your name around the command window by entering certain keys
    which represents the four dimensions*/

    system("color 1F");   // changing the color of command window background again to blue

    printf("\t\t*                                               *\n");
    printf(" -----------------------------------------------------------------------------\n");
    printf("|                                                                            |\n");
    printf("|                                                                            |\n");
    printf("| ######   ######  ######  ######  ######  ######  #      #  ######   ###### |\n");
    printf("| #        #    #  #       #         #       #     # #    #  #        #      |\n");
    printf("| #  ####  ######  #####   #####     #       #     #  #   #  #  ####  ###### |\n");
    printf("| #    #   #  #    #       #         #       #     #   #  #  #    #        # |\n");
    printf("| ######   #   #   ######  ######    #     ######  #    # #  ######   ###### |\n");
    printf("|                                                                            |\n");
    printf(" -----------------------------------------------------------------------------\n");
    printf("\t\t*****************\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*        -----------------------------          *\n");  //printing the welcoming screen for the game.
    printf("\t\t*         WELCOME TO SNAKE AND LADDER           *\n");
    printf("\t\t*        -----------------------------          *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*****************\n\n\n");
    printf("maximum numbers of players can be 3\n\n");
    printf("enter number of players");

    scanf("%d", &f);  // f represents number of players
    start=clock();

    while (z < f)
    {

        printf("                      \n\n\nhello , thank you for coming.\n                      what would you like to do: \n                      1.read the rules\n                      2.play the game\n "
        );

        scanf("%d", &choice); //player enters his choice


        {if (choice == 1)  // if true  we print the rules of the game
        {
            printf("\n                      The rules are simple \n                      you can press enter to roll the dice");
            _getch();
            printf("\n\n\n\n\n                      enter your choice");
            continue;
        }

        if (choice == 2)   //if true enter the game
        {
            printf("                      welcome to snake and ladder \n");
            printf(" |100  99  98  97  96  95  94  93  92  91|     1=start          4=ladder to 14\n ");
            printf("| 81  82  83  84  85  86  87  88  89  90|     9=ladder to 31   17=snake to  7\n ");

            printf("| 80  79  78  77  76  75  74  73  72  71|     21=ladder to 42  46=snake to  13\n ");
            printf("| 61  62  63  64  65  66  67  68  69  70|     28=ladder to 84  62=snake to  19\n ");
            printf("| 60  59  58  57  56  55  54  53  52  51|     37=ladder to 61  54=snake to  25\n ");
            printf("| 41  42  43  44  45  46  47  48  49  50|     51=ladder to 67  87=snake to  36\n ");
            printf("| 40  39  38  37  36  35  34  33  32  31|     72=ladder to 91  64=snake to  44\n ");
            printf("| 21  22  23  24  25  26  27  28  29  30|     78=ladder to 92  95=snake to  75\n ");
            printf("| 20  19  18  17  16  15  14  13  12  11|     80=ladder to 99     100=END\n");
            printf(" |  1   2   3   4   5   6   7   8   9  10|      \n");
            //board of snake and ladder game.

            printf("winner will be the one who gets to 100 first that is minimum number of dice throws");
            do
            {   startmin=clock();
                printf("\npress any key to roll the dice\n\n");
                dice -= (getche());
                dice = ((rand() % 6) + 1);  //gets a value for the dice between 1 and 6
                printf("you rolled the dice and you got %d ", dice);
                position += dice;  // increase the position of the player by dice value
                endmin=clock();
                timemin = ((double) (endmin - startmin)) / CLOCKS_PER_SEC;
            printf("\ngenerating dice value and assigning it to the new position took %f seconds to execute \n", timemin);
/*   in average the time is about 0.8 second which depend on how fast or slow the user will enter any key to roll the dic */

if(dice == 6)
{
    printf("\n you got 6 on your dice as a result of which you get another throw\n");
    printf(" _________\n");
        printf("|         |\n");
        printf("|  O   O  |\n");
        printf("|  O   O  |\n|  O   O  |\n|_________|\n");
    continue;
}
printf("you landed on the poistion %d\n",position); // the next if statements to print the dice each time
if(dice==1)
{
    printf(" _________\n");
        printf("|         |\n");
        printf("|         |\n");
         printf("|    O    |\n|         |\n|_________|\n");

}
else if (dice==2)
{


        printf(" _________\n");
        printf("|         |\n");
        printf("|  O      |\n");
        printf("|         |\n|      O  |\n|_________|\n");




}
else if (dice==3)
        {
        printf(" _________\n");
        printf("|         |\n");
        printf("|  O      |\n");
        printf("|    O    |\n|      O  |\n|_________|\n");
        }
else if (dice==4)
    {
        printf(" _________\n");
        printf("|         |\n");
        printf("|  O   O  |\n");
        printf("|         |\n|  O   O  |\n|_________|\n");
        }
else if (dice==5)
    {
        printf(" _________\n");
        printf("|         |\n");
        printf("|  O   O  |\n");
        printf("|    O    |\n|  O   O  |\n|_________|\n");
        }
count++; // increase the count each till reaching position 100
startmin=clock();
checkposition();
endmin=clock();
timemin = ((double) (endmin - startmin)) / CLOCKS_PER_SEC;
printf("\nchecking the position if snake or ladder took %f seconds to execute \n", timemin);
/* the time of checkposition is almost 0 as it's just some switch case statements which take no time in cpu computing but
in worst case it will be 0.001 second as the cpu will run on all cases*/
position = newposition;
}
while(position<100);
printf("congratulations you have won!! in %d dice throws\n\n\n ",count);
_getch();
timemin=clock();
push(count); // to store the counts of first player
insert1(count);
insertnode();
z++; // increasing z so the other player will play in case of more than one player
position = 0; // returning position to 0 for the next player
count = 0; // same as position above
if(f!=1&&z!=f) // print statement for the next player
{printf("another player's chance\n");}
}
}
_getch(); // wait till the next player press any key
end=clock();  // to calculate time for each player per turn
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\nthe game took you %f seconds to win \n", cpu_time_used);
}


if(top!=0) // after the end of the game check who won the game with least number of counts
{printf("winner of the game is ");
display();}
if(rear!=0) //after the end of the game check who lost the game with most number of counts
{
printf("\n\nthe player who losses the game is ");
display1();
printf("\n\n");
printf("\t\t*************************************************\n");
printf("\t\t*                                               *\n");
printf("\t\t*        -----------------------------          *\n");
printf("\t\t*               LEADERSHIP BOARD                *\n");
printf("\t\t*        -----------------------------          *\n");
printf("\t\t*                                               *\n");
printf("\t\t*************************************************\n\n\n");
viewlist(); // show the player records
}
}
checkposition() //definition of the function checkposition() to know the snake and ladder positions
{
    switch(position)
    {
    case 4:
        newposition=14;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;

    case 9:
         newposition=31;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
    case 17:
        newposition=7;
        {
            printf("sorry but you have landed on a snake and your new position is %d",newposition);

        }
        break;
     case 21:
         newposition=42;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
         case 28:
         newposition=84;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
     case 37:
         newposition=61;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
         case 51:
         newposition=67;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
         case 72:
         newposition=91;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
         case 78:
         newposition=92;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
         case 80:
         newposition=99;
        {
            printf("\n well done ,you have landed on a ladder,you are now on space %d.\n",newposition);
        }
        break;
    case 46:
        newposition=13;
        {
            printf("sorry but you have landed on a snake and your new position is %d",newposition);

        }
        break;
        case 62:
        newposition=19;
        {
            printf("sorry but you have landed on a snake and your new position is %d",newposition);

        }
        break;
    case 54:
        newposition=25;
        {
            printf("sorry but you have landed on a snake and your new position is %d",newposition);

        }
        break;
        case 87:
        newposition=36;
        {
            printf("sorry but you have landed on a snake and your new position is %d",newposition);

        }
        break;
    case 64:
        newposition=44;
        {
            printf("sorry but you have landed on a snake and your new position is %d",newposition);

        }
        break;
        case 95:
        newposition=75;
        {
            printf("sorry but you have landed on a snake and your new position is %d",newposition);

        }
        break;
        default:
            return newposition = position;
}
}

void push(int x) /* push the count of each player in the top of the stack  */
{
    if(top==size)
    {
        printf("winner can be decided only between 3 players");
    }
    else
    {
        top++;
        stack[top]=x;
    }
    }
void insert1(int x) /* store the count of each player in the queue  */
    {
        if(rear==size1)
        {
            printf("winner can be decided only between 3 players");

        }
        else
        {
            if(front ==-1)
                front = 0;
            rear = rear +1;
             queue[rear]= x;
        }
    }

void display() /* display the player with least number of count to win the game   */
{
    if(top==0)
    {
        printf("player 1");
    }
    else if(top==1)



    {
        if (stack[0]<stack[1])
            printf("player 1");
        else
            printf("player 2");
    }

        else if(top==2)

    {
        if(stack[0]<stack[1]&&stack[0]<stack[2])

        printf("player 1 ");
        else
            {
            if(stack[1]<stack[0]&&stack[1]<stack[2])
                printf("player 2");
            else
                printf("player 3");}

    }


    }

void display1()/*  display the player with most number of count to lose the game      */
{
    if(rear==0)
    {
        printf("player 1");
    }
    else if(rear==1)



    {
        if (queue[0]>queue[1])
            printf("player 1");
        else
            printf("player 2");
    }

        else if(rear==2)

    {
        if(queue[0]>queue[1]&&queue[0]>queue[2])

        printf("player 1 ");
        else
            {
            if(queue[1]>queue[0]&&queue[1]>queue[2])
            printf("player 2");
        else
        printf("player 3");}




    }
    }
void viewlist()
{
struct node *t;
if(start==NULL)
printf("empty");
else
{
t=start;
if (t!=NULL)
for(int i=1;i<=3;i++)
{
    if(i<=top+1)
{printf("               player%d score is %d \n\n",i,t->info);
t=t->link;}
}}}
void insertnode()
{
struct node* temp,*t;
temp=createnode();
temp->info=count;
temp->link=NULL;
if(start==NULL)
start=temp;
else
{
t=start;
while(t->link!=NULL)
{t=t->link;}
t->link=temp;
}
}
