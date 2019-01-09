/*
Name: Umer Ahmed
ID: 1010091
Date: October 15th 2018
Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

int main(int argc, char const *argv[]) {

  node *stack;
  int i;
  char toNum[2];
  double num;
  double a;
  double b;
  double result;


  if( argc != 2 ){
    printf("Invalid command line arguments.\n");
    printf("Enter a single string of your expression in postfix form into the command line\n");
    return 0;
  }

  for(i= 0; i< strlen(argv[1]); i++){


    if(argv[1][i]=='+' ){
      b=pop(&stack);
      a=pop(&stack);
      result = a + b;
      push(&stack,result);

    }
    else if(argv[1][i]=='-' ){
      b=pop(&stack);
      a=pop(&stack);
      result = a - b;
      push(&stack,result);
    }
    else if(argv[1][i]=='*' ){
      b=pop(&stack);
      a=pop(&stack);
      result = a * b;
      push(&stack,result);
    }
    else if(argv[1][i]=='/'   ){
      b=pop(&stack);
      a=pop(&stack);
      result = a / b;
      push(&stack,result);
    }
    else{

      toNum[0]= argv[1][i] ;
      num= (double)atoi(toNum);
      push(&stack, num);



    }

  }
  printf("result = %.2lf\n", pop(&stack) );

  return 0;
}
