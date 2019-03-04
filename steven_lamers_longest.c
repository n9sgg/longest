/*
*
* Program to print the top 10 longest words in the file name that is given on the command line 
*
* Author: Steven Lamers 
*
* Version: 1.0 Mar 3, 2019
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 50 	/* longest word in english dictionay is 45 chars */

typedef struct TOP_TEN {
	char	word[MAX_LINE_LENGTH];
	int		len;
} TOP_TEN ;

TOP_TEN topten[10] = { {"",0}, {"",0}, {"",0}, {"",0}, {"",0}, {"",0}, {"",0}, {"",0}, {"",0}, {"",0}  };

int main(int argc, char **argv) {

  FILE 	*fp;
  char 	buffer[MAX_LINE_LENGTH];
  int 	x,q;
  int 	temp_len;

  /* Quit if no arguments are passed. */
  if ( argc <= 1 ) {
    printf("Usage: %s <file>\n", argv[0]);
    exit(1);
  }

  /* Open the file */
  fp = fopen(argv[1], "r");

  if ( fp != NULL )
  {

    /* Read lines from the file */
    while (fgets(buffer , MAX_LINE_LENGTH , fp))
    {

      /* get length of string from file */
      temp_len = strlen(buffer); 	

      /* Search for a current top ten word length */
      for( x = 0 ; x < 10 ; x++ )
      {

      	/* if the word from the file is the same length or longer 
		* than the one on the stack, push stack down and insert  */
      	if ( temp_len >= topten[ x ].len )
      	{
			/* push stack down at current index */
			for( q = 9 ; q > x ; q-- )
			{
				/* push */
				strcpy( topten[ q ].word , topten[ q - 1 ].word );			
				topten[ q ].len	= topten[ q - 1 ].len;
			}

			/* Insert the word in the  stack */
			strcpy( topten[ x ].word , buffer ); 
			topten[ x ].len = temp_len ;
			break;
        }
      }
    }

    /* Print output to stdout */
    for( x=0 ; x < 10 ;  x++ )
    {
		/* print the word */
		printf( "%s" , topten[ x ].word );
    }

  }
  else
  {
    /* Can't open file */
    printf("%s\n", "cant open input file");

    exit(1);

  }

  exit(0);

}

