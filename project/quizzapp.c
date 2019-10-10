#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
void delay(int);
void quiz();
void displaypage(char*);
void user_info();
void gametype();
void menu();
void rules();
void check_score(int);
void typeofquiz(int,char*);
void displayqsns(char*,char);
void leaderboard();

int count=0;
char username[20];

//structure to store the questions
struct questions
{
    char id;
    char question[200];
    char options[150];
    char explaination[200];
    char optionright;
}qsn[100];

//to display rules of the quiz
void rules()
{
    int choice;
    system("cls");
    quiz();
    displaypage("rules.txt");
    scanf("%d",&choice);
         if(choice==0)
                    menu();
}

//to display the score of the player
void check_score(int count)
{
   FILE *fptr;
   fptr = fopen("score.txt", "a");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   fprintf(fptr,"%s ",username);
   fprintf(fptr,"%d",count);
   fprintf(fptr,"\n");
   fclose(fptr);
    printf("%s  TOTAL SCORE IS :%d\n",username,count);
}

//based on the quiz chosen the related filename is sent as a parameter and after choosing the level of difficulty,the quiz is displayed
void typeofquiz(int count,char* filename)
{
    int level_choice;
    char ch;
    system("cls");
    quiz();
    displaypage("levelsui.txt");
  x:
    printf("enter your choice\n");
    scanf("%d",&level_choice);
    if(level_choice==1)
        {
            system("cls");
            displayqsns(filename,'#'); //level choice =1 It displays easy level quiz
        }
    else if(level_choice==2)
        {
           system("cls");
           displayqsns(filename,'$'); //level choice =2 It displays medium level quiz
        }
    else if(level_choice==3)
        {
           system("cls");
           displayqsns(filename,EOF); //level choice =3 It displays hard level quiz
        }
    else if(level_choice==4)
        {
          system("cls");
          gametype(); //go back to previous page
        }
    else
        {
        printf("Invalid choice\nSelect a valid option"); //asks the user to enter an option again and stays in the same page
        goto x;
        }
}

//displays the quiz based on the level chosen
void displayqsns(char* filename,char symbol)
{
    FILE *filePointer;
    char ch;
    char choice;
    int i=0;
    int qsnnum=0;
    filePointer = fopen(filename, "r");
    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        if(symbol=='$')
        {
            while((ch = fgetc(filePointer)) != '#')
                {
                }
            ch=fgetc(filePointer);
        }
        if(symbol==EOF)
        {
            while((ch = fgetc(filePointer)) != '$')
            {
            }
           ch=fgetc(filePointer);
        }
    while((ch = fgetc(filePointer)) != symbol)
        {
          system("cls");
          printf(
 "***********************************************************************************************************************************************************************\n"
 "***********************************************************************Question %d*************************************************************************************\n"
 "***********************************************************************************************************************************************************************\n\n\n",qsnnum+1);
          fflush(stdin);
          qsn[qsnnum].optionright=ch; //to store the correct option from the file into structure
          qsn[qsnnum].id=fgetc(filePointer); //to read the space after the correct option
          qsn[qsnnum].id=fgetc(filePointer); //to store the question number from the file into structure
          printf("%c",qsn[qsnnum].id);
          i=0;
         while ((ch = fgetc(filePointer)) != '\n')
         {
           qsn[qsnnum].question[i++]=ch; //storing the question present in file by reading till the end of the line
         }
         puts(qsn[qsnnum].question);
         printf("\n\n");
        i=0;
         while ((ch = fgetc(filePointer)) != '\n')
         {
           qsn[qsnnum].options[i++]=ch; //to store the options of a question from the file into structure
         }
         puts(qsn[qsnnum].options);
         printf("\n\n");
         i=0;
         while ((ch = fgetc(filePointer)) != '^')
         {
           qsn[qsnnum].explaination[i++]=ch; //to store the explanation of the answer from the file into structure which ends with ^ to mark the end of the explanation
         }
        ch=fgetc(filePointer);
        printf(
 "***********************************************************************************************************************************************************************\n"
 "***********************************************************************************************************************************************************************\n");

        printf("Enter your choice\n");
        scanf("%c",&choice); //input from the user
        fflush(stdin);
        if(qsn[qsnnum].optionright==choice)
        {
        printf("Correct Answer!!!\n");
        count+=10; //award 10 points for each right answer
        }
            else
            printf("Wrong Answer!!!\n");
            printf("Correct option is: ");
        putchar(qsn[qsnnum].optionright);
        printf("\n");
        puts(qsn[qsnnum].explaination);
        qsnnum++;
        i=0;
        _getch();
    }
    }
    fclose(filePointer);
    check_score(count);
}

//Welcome page to the quiz game where the user enters his/her name
void user_info()
    {
       quiz();
       displaypage("userinfoui.txt");
       printf("Enter a username\n");
       scanf("%s",username);
    }

//Main menu of the game
void menu()
    {
   int choice;
   system("cls");
   quiz();
   displaypage("ui.txt");
   printf("Enter your choice\n");
   scanf("%d",&choice);
       switch(choice)
                   {
               case 1:
                   gametype();
                   break;
               case 2:
                   rules();
                   break;
               case 3:
                   leaderboard();
                   break;
               case 4:
                   exit(0);
                   break;
               default:
                   printf("INVALID CHOICE\n");
                   break;
                  }
}

//UI for the title quiz
void quiz(){
printf(
 "***********************************************************************************************************************************************************************\n"
 "***********************************************************************************************************************************************************************\n"
 "********************************************                                                                   ********************************************************\n"
 "********************************************                    * * *     *    *   *  ******                   ********************************************************\n"
 "********************************************                   *     *    *    *   *     *                     ********************************************************\n"
 "********************************************                  * * * * *   *    *   *    *                      ********************************************************\n"
 "********************************************                   *     *    *    *   *   *                       ********************************************************\n"
 "********************************************                    * * *  *  ******   *  ******                   ********************************************************\n"
 "********************************************                                                                   ********************************************************\n"
 "***********************************************************************************************************************************************************************\n"
 "***********************************************************************************************************************************************************************\n");
}

//UI for each page in the game is changed using the filename parameter like welcome page,main menu,levels etc
void displaypage(char *filename){
FILE *fptr;
	char  c;
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	c = fgetc(fptr);
	while (c != EOF)
	{
	    if(c!='*')
        delay(1);
		printf("%c", c); //printing character by character from the file.
		c = fgetc(fptr);
	}
	fclose(fptr);
}

//Selection for the type of quiz to be played
void gametype()
   {
    int option;
    system("cls");
    quiz();
    displaypage("gametype.txt");
    printf("enter your choice:");
    scanf("%d",&option);
            switch(option)
                         {
                            case 1:
                                   typeofquiz(count,"gkqsns.txt");
                                   break;
                            case 2:
                                   typeofquiz(count,"sportsqsns.txt");
                                   break;
                            case 3:
                                   typeofquiz(count,"historyqsns.txt");
                                   break;
                            case 4:
                                   typeofquiz(count,"entertainmentqsns.txt");
                                   break;
                            default:
                                   printf("Invalid choice\n");
                         }
}
void leaderboard(){
    system("cls");
    quiz();
FILE *fptr;
	char  c;
	fptr = fopen("score.txt", "r");
	if (fptr == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	c = fgetc(fptr);
	while (c != EOF)
	{
	    if(c!='*')
        delay(1);
		printf("%c", c); //printing character by character from the file.
		c = fgetc(fptr);
	}
	fclose(fptr);
	        printf(
 "***********************************************************************************************************************************************************************\n"
 "***********************************************************************************************************************************************************************\n");
}
int main()
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); //to set the font color to red on the console
    user_info(); //to ask the user to enter a user name so that the score can be displayed at the end of the quiz.
    menu(); //function call to the main menu
 //   check_score(count); //displays the final score
}
