/*
 * CO222 PROJECT 01 : DIGITAL CLOCK
 * Author : M.D.Chamara Dilshan Senevirathna
 * Reg. NO: E / 18 / 327
 * Date : 05 / 09 / 2021
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//prototype functions
int find_colour(char *val);
void fill_colour(int num);
void digital_num(int digit,int loc,int colour);
void print_digit(int (*new_array)[6],int loc,int colour);
void print_colon(int colour,int loc);
int seperate_digit(char arr[], int loc);
int block_location(int digit_location);

//Defining global variables
int num_array0[5][6]={			// 0
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,0,0,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1}
	};

int num_array1[5][6]={			// 1
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1}
	};


int num_array2[5][6]={			// 2
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1},
		{1,1,0,0,0,0},
		{1,1,1,1,1,1}
	};


int num_array3[5][6]={			// 3
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1}
	};


int num_array4[5][6]={			// 4
		{1,1,0,0,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1}
	};

int num_array5[5][6]={			// 5
		{1,1,1,1,1,1},
		{1,1,0,0,0,0},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1}
	};


int num_array6[5][6]={			// 6
		{1,1,1,1,1,1},
		{1,1,0,0,0,0},
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1}
	};

int num_array7[5][6]={			// 7
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1}
	};

int num_array8[5][6]={			// 8
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1}
	};

int num_array9[5][6]={			// 9
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1}
	};


int main(int argc,char **argv)
{
    //Declaring the variables
    int colour_num ;
    char str1[3] = {"-c"} ;
    char str2[3] = {"-h"} ;

    //assigning the command line arguments into variables
    if(argc <= 2)
    {
        char *colour = "white"; //default colour
        colour_num = find_colour(colour);
    }

    else if(argc >= 3)
    {
        char *colour = (argv[2]); //new colour
        colour_num = find_colour(colour);

    }


    //checking the command line arguments
    if( (argc == 1) || ( (argc == 2) && (strcmp(str2,argv[1]) != 0)  && (strlen(argv[1]) != 2) )  || ((argc >= 3) && (strcmp(str1,argv[1]) == 0) && (colour_num != 999)) ) //when the inputs are correct
    {
        printf("\033[?25l");	// Hiding the cursor
        printf("\033[2J");		// Clear console

        while(1)
        {
            char current_time[20];
            char date[20];
            time_t time_now;
            time(&time_now);

            struct tm *mytime = localtime(&time_now);

            strftime(current_time,20,"%X", mytime); //getting the system time
            strftime(date,20,"%Y-%m-%d", mytime); //getting the system date

            //printing the clock
            int location;

            // Print the first two digits
            for(location=0;location<2;location++)
            {
                digital_num( seperate_digit(current_time,location), location, colour_num);
            }

            print_colon(colour_num,15);		// Print colon

            // Print the second two digits
  	        for(location=3;location<5;location++)
            {
                digital_num( seperate_digit(current_time,location), location, colour_num);
            }

  	        print_colon(colour_num,34); //print colon

  	        // Print the last two digits
  	        for(location=6;location<8;location++)
            {
                digital_num( seperate_digit(current_time,location), location, colour_num);
            }

            printf("\033[8;23H");
            printf("\033[0m");

            int i;
  	        for(i=0; i<10; i++)
                {
                    printf("\033[%dm%c", 30 + colour_num, date[i]);
                }

            putchar('\n');
            printf("\033[0m");

  	        sleep(1);


        }

    }

    else if(strcmp(str2,argv[1]) == 0)//when the '-h' flag is given or the given arguments are invalid
    {
        printf("usage : -h                      quick help on cmd\n");
        printf("usage : clock -c <color>        print clock with a color\n");
        printf("<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
    }
    else if( (argc >= 3) && (strcmp(str1,argv[1]) == 0) && (colour_num == 999) ) //when the input colour is wrong
    {
        printf("%s ;This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", argv[2]);
    }
    else if( argc != 1 ) //when the arguments are invalid
    {
        printf("Invalid use of arguments.\n");
        printf("usage : clock -h                quick help on cmd\n");
        printf("usage : clock -c <color>        print clock with a color\n");
    }


    return 0;
}


//Defining the functions
int find_colour(char *val) // finding the colour of the clock
{
    //defining the variables
    char *colours[] = {"black","red","green","yellow","blue","magenta","cyan","white"};
    int num;

    for( num=0; num < 8; num++)
    {
        if( strcasecmp(val,colours[num])== 0 )
        {
            return num;
        }
    }
    return 999;


}

//printing coloured squares
void fill_colour(int num)
{
    printf("\033[%dm " ,num + 40 );
}



//printing the clock
void print_digit(int (*new_array)[6],int loc,int colour)
{
    int row,col;

    for(row = 0; row < 5; row++)
    {
        for(col = 0; col < 6; col++)
        {
            printf("\033[%d;%dH", row + 2, col + block_location(loc));
            if( new_array[row][col] == 1 )
            {
                fill_colour(colour);
            }
            else if( new_array[row][col] == 0 )
            {
                printf("\033[0m ");
            }
        }
    }
    printf("\033[0m"); //reset default colour
}

int block_location(int digit_location)
{

	int spacing;

	if (digit_location==0)
		spacing=2;
	else if(digit_location==1)
		spacing=9;
	else if(digit_location==3)
		spacing=21;
	else if(digit_location==4)
		spacing=28;
	else if(digit_location==6)
		spacing=40;
	else if(digit_location==7)
		spacing=47;

	return spacing;
}

//changing the number size and print
void digital_num(int digit,int loc,int colour)
{

    if(digit==0)
    {
        print_digit(num_array0, loc, colour);
    }

	else if(digit==1)
    {
        print_digit(num_array1, loc, colour);
    }

	else if(digit==2)
    {
            print_digit(num_array2, loc, colour);
    }

	else if(digit==3)
    {
        print_digit(num_array3, loc, colour);
    }

	else if(digit==4)
    {
        print_digit(num_array4, loc, colour);

	}

	else if(digit==5)
    {
        print_digit(num_array5, loc, colour);
    }

	else if(digit==6)
    {
        print_digit(num_array6, loc, colour);
    }

	else if(digit==7)
    {
        print_digit(num_array7, loc, colour);
    }

	else if(digit==8)
    {
        print_digit(num_array8, loc, colour);
    }

	else if(digit==9)
	{
        print_digit(num_array9, loc, colour);
	}

}

//seperating the digital value
int seperate_digit(char arr[], int loc)
{
    char numbers[] = {'0','1','2','3','4','5','6','7','8','9'} ;
    int number;
    int arraysize = sizeof(numbers)/sizeof(numbers[0]);

    for(number = 0; number < arraysize; number++)
    {
        if(arr[loc] == numbers[number])
        {
            return number;
        }
    }
    return 0;


}

//printing the colon between two digital number
void print_colon(int colour,int loc)
{
    int num_array[5][6] =
    {
        {0,0,0,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,0,0,0}
    };

    int row,col;

    for(row = 0; row < 5; row++)
    {
        for(col = 0; col < 6; col++)
        {
            printf("\033[%d;%dH",row + 2,col + loc);
            if( num_array[row][col] == 1 )
            {
                fill_colour(colour);
            }
        }
        putchar('\n');
    }

}



















