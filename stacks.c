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

/*
typedef struct node{
  char element;
  struct node* next;
}node;
*/

void push(node** top, double n){
  node* new = malloc(sizeof(node));
  if(!new){
    exit(-1);
  }
  new->element = n;
  new->next = *top;
  *top =new;
}

double pop(node** top){
  double element;
  node* temp;

  if(!(*top)){
    printf("Error: no nodes to pop\n" );
    return 0;
  }
  temp = *top;
  *top = temp->next;
  element = temp->element;
  free(temp);

  return element;

}
