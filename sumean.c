/**
****************************************************************************
* @detailed
* - @Author   Author: Francesco Lazzarotto <francesco.lazzarotto@inaf.it> 
* - @Date     Date: 12/12/2021 
* - @Version  Version: 0.0.1
* - @Compiler Compiler: gcc (iso c99)
* - @Target   Target: provide a programming example
* - @Notes    Notes: TBD
* @section  LICENSE
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 3 of
* the License, or (at your option) any later version.
*
*
*******************************************************************************/

/** @file sumean.c
    @brief SUM & MEAN : simple terminal app example in c language
*/
/** @tableofcont */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 /** @function PAUSE() @brief pause the execution until a key and enter are pressed */
void PAUSE();

/** @function fpurge_stdin() purge the stdin for terminal I/O */
void fpurge_stdin();

/** 
 * @function isanumber() check if a given string is a positive integer
 * @param	char s[] characters array containing the string to check 
 * @return returns 1 if the string is a positive integer, 0 if it is not
 */
int isanumber(char s[]);

/** @function present() print a description of what app is doing and usage */
void present();

/** @function main() main function of the app  
* @detailed
* 
* This example accepts a list of positive integers
* And computes their sum and average. 
* The list can be read from stdin (keyboard or file redirection)
*      - Present to the user what the app is doing 
*      - Tell user to enter data points; maximum of allowed pts = 39
*      - Start an infinite loop, flow interrupted only by break;
*      - Read a value; check for end of file (EOF val = -1) 
*      - Value input before is in string format
*      - If the string correctly express a legal numerical value, convert it into integer
*        and then insert it in the 1-D points array and increment the partial sum with its value
*      - Reject the item value otherwise
*      - check when the end of the dataset is reached (reading -1)
*      - -1 read --> break; continue the loop otherwise
*      - EOF detected --> compute average
*      - print final report #points, sum, average.
*/
int main(int argc, char **argv);
/** @section Global-Variables */
char temp[1024]; /** @var temporal string to read numbers */
long int point[40]; /** @var point: monodimensional points array, max dimension is 40 */
unsigned char w=0;  /** @var w: flag for warnings w>0 if you got warnings */
unsigned long count=0; /** @var count used to count TBC */
unsigned char skip=0;  /** @var skip used to skip God Knows */

int main(int argc, char **argv)
{
   int index = 0;    /** @var index of the points array */
   double sum = 0.0; /** @var sum saves the sum of points values */
   double avg;       /** @var avg saves the average of points values */
   int nopoints;     /** @var nopoints saves the actual number of points in the array */
   int stdn_fn = 0;
   long int ret;
      /* If stdin is the terminal, fileno(stdin) is always 0. */
    #ifdef __GNUC__
    if (isatty(stdn_fn))
    #endif
      /*  Present to the user what the app is doing */
	present();
      /*  Tell user to enter data points; maximum = 39. */
 	  fprintf(stderr, "%s: Enter positive integer numbers (-1 to indicate end of list).\n", argv[0]);  /*  this print only in interactive */
   for(;;){ /*  infinite loop, flow interrupted only by break;*/
        skip=0;
        #ifdef DEBUG
        fprintf(stderr, "%s: processing attempt number[%li] START \n", argv[0], count);
        #endif
         /*  Read number; check for end of file. */
         /*  Read before as a string */
        ret = scanf("%s", temp);
        /*  convert into integer if it is a correct string */
        #ifdef DEBUG
        fprintf(stderr, "%s: length of the scanned string is %li\n", argv[0], strlen(temp));
        #endif
        if ( isanumber(temp) ){ /*  if the string is a number */
            #ifdef DEBUG
            fprintf(stderr, "%s: %s can be accepted as positive integer number \n", argv[0], temp);
            #endif
            point[index] = atoi(temp); /*  insert the number in the 1-D points array */
        } else { /*  reject otherwise */
            fprintf(stderr, "%s: warning, %s cannot be accepted as a positive integer number \n", argv[0], temp);
            point[index] = -2;
            skip=1;
        }

        #ifdef DEBUG
        fprintf(stderr, "pv=%s;av=%li ", temp, point[index]);
        #endif
        if (ret <= 0){
            #ifdef DEBUG
            fprintf(stderr, "%s: warning, scanf returned %li\n", argv[0], ret);
            fprintf(stderr, "%s: input warning, maybe you didn't enter '-1'?\n", argv[0]);
            #endif
            w++;
            break;
        }

        /*  check when the end of the dataset is reached (reading -1) */
        if (point[index] == -1){
            #ifdef DEBUG
            fprintf(stderr, "\n%s: detected end of dataset\n", argv[0]);
            #endif
            break;
        }

        /*  accept only positive integers */
        if ((point[index] >= 0)&&(skip==0)){
            sum += point[index];
            ++index;
        } else if(skip==1){
            #ifdef DEBUG
            fprintf(stderr, "%s: warning, skipping negative point value %li\n", argv[0], point [index]);
            #endif
            w++;
        }
        #ifdef DEBUG
        fprintf(stderr, "\n%s: processing number[%li] STOP \n", argv[0], count);
        #endif
        count++; /** increment the acquisitions counter*/
   }
   nopoints = index; /** save the actual n. of input 1-D points */
   if (nopoints > 0)
        avg = sum / nopoints; /* compute the average */ 
   else {
        #ifdef DEBUG
        fprintf(stderr, "\n%s: warning, attempt to divide by 0 \n", argv[0]);
        #endif
        avg = 0;
        w++;
   }

   fprintf(stderr, "%s: you got %d warnings\n", argv[0], w);
   fprintf(stderr, "%s: valid numbers read: %d \n",argv[0] , nopoints);
   fprintf(stderr, "%s: sum: %f \n",argv[0], sum);
   fprintf(stderr, "%s: average: %f\n",argv[0], avg);
   fprintf(stderr, "%s: showing results:\n",argv[0] );
/*   fprintf(stderr, "%s: #points\tsum\taverage\n",argv[0] ); */
    fprintf(stderr, "#points\tsum\t\taverage\n"); 
    printf("%d\t%f\t%f\n",nopoints,sum,avg);
}

void fpurge_stdin(){
#ifdef __DEBUG__
    __fpurge(stdin);
#else
	fflush(stdin);
#endif
}

void present(){
        fprintf(stderr, "**************************************\n");
        fprintf(stderr, "***          SUM & MEAN            ***\n");
        fprintf(stderr, "**************************************\n");
        fprintf(stderr, "*** this example accepts           ***\n"); 
        fprintf(stderr, "*** a list of positive integers    ***\n");
        fprintf(stderr, "*** and computes their sum         ***\n"); 
        fprintf(stderr, "*** and average. The list can      ***\n");
        fprintf(stderr, "*** be read from standard input    ***\n");
        fprintf(stderr, "*** (keyboard or file redirection) ***\n"); 
        fprintf(stderr, "**************************************\n");
}

void PAUSE(){
    char c[20];
    printf("Please press a key and then enter\n");
    fpurge_stdin();
    if (scanf("%s", c) <=0) fprintf(stderr, "warning in acquiring data\n") ;
}

int isanumber(char s[] ){
        unsigned int good_number=0;
        unsigned char lc;
        #ifdef DEBUG
        fprintf(stderr, "isanumber() string to check has lenght %c\n", strlen(s));
        fprintf(stderr, "isanumber() first character in string is %c\n", s[0]);
        #endif
        lc=0;
        /* if first char is a number or '-' ok */
        if ( ((s[lc] >= 48) && (s[lc] <= 57)) || (s[lc] == 45) )
                good_number = 1;
        else
                good_number = 0;
        lc++;
        #ifdef DEBUG
        fprintf(stderr, "isanumber() following chars in string ");
        #endif
        while(lc<strlen(s)){
        /* following numbers must be numbers */
            if ( (s[lc] < 48) || (s[lc] > 57) ){
                good_number = 0;
                return good_number;
            } else {
                good_number = 1;
            }

        #ifdef DEBUG
            fprintf(stderr, "%c ", s[lc]);
        #endif
                lc++;
        }

        #ifdef DEBUG
        fprintf(stderr, "\nisanumber() returning value %i\n", good_number);
        #endif
        return good_number;
}
