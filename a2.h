#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>


#ifndef A2_H
#define A2_H


typedef struct node{
  double element;
  struct node* next;
}node;

typedef struct car{
  char plateNum[10];
  int mileage;
  int expectedReturnDate;
  struct car* next;
}car;


int options();
int get_mileage();
int get_returnDate();
car *new_car(  char plateNum[10], int mileage, int expectedReturnDate);
void insert_car_list(car **hp, car *new);
void insert_rented_list(car **hp, car *new);
car* remove_car(car **hp,char plateNum[10]);
void rented_to_available(car **rent_head, car **rented_head, char plateNum[10], int mileage, double *totalIncome );
void rented_to_repair(car **rented_head, car **repair_head, char plateNum[10], int mileage, double *totalIncome);
void repair_to_available(car **rent_head, car **repair_head, char plateNum[10]);
void available_to_rent(car **rent_head, car **rented_head,  int expectedReturnDate);
void print_list(car* cp);
void read_available_file(car **rent_head);
void read_repair_file(car **repair_head);
void read_rented_file(car **rented_head);
void write_available_file(car *rent_head);
void write_repair_file(car *repair_head);
void write_rented_file(car *rented_head);


void push(node **top , double n);
double pop(node** top);

#endif
