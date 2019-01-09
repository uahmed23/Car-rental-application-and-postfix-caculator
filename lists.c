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


int options(){

  int transactionCode;

  printf("\n***************************************************************************\n" );
  printf("Transaction options:\n\n");
  printf("1. Add a new car to the available-for-rent list\n");
  printf("2. Add a returned car to the available-for-rent list\n");
  printf("3. Add a returned car to the repair list\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list\n");
  printf("5. Rent the first available car\n");
  printf("6. Print all the lists\n");
  printf("7. Quit.\n");
  printf("***************************************************************************\n" );
  printf("\nTransaction code (1-7): ");
  scanf("%d", &transactionCode );
  printf("\n");

  return transactionCode;
}



car *new_car(  char plateNum[10], int mileage, int expectedReturnDate){

  car* cp;
  if( (cp = malloc(sizeof (car))) == NULL ){

    printf("new_car: dynamic allocation failed. \n");
    exit(0);
  }

  strcpy(cp->plateNum, plateNum);
  cp->mileage = mileage;
  cp->expectedReturnDate = expectedReturnDate;
  return cp;

}

 void insert_car_list(car **hp, car* new)
{
  car *prev = NULL, *curr;
  //new = new_car(plateNum, mileage, expectedReturnDate);
  curr = *hp;

  while(curr && ( new->mileage > curr->mileage) ){

    prev = curr;
    curr = curr->next;

  }

  if(prev == NULL ){
    new->next = *hp;
    *hp = new;
  }
  else{
    prev->next = new;
    new->next = curr;
  }

}

void insert_rented_list(car **hp, car *new)
{
 car *prev = NULL, *curr;
 curr = *hp;

 while(curr && ( new->expectedReturnDate > curr->expectedReturnDate) ){
   prev = curr;
   curr = curr->next;
 }
 if(prev == NULL){
   new->next = *hp;
   *hp = new;
 }
 else{
   prev->next = new;
   new->next = curr;
 }

}



//This  function will go into any list find a car with a matching plate number,
//remmove that car from the list, and return the cars pointer.
car* remove_car(car **hp, char plateNum[10])
{
  car dummy, *old, *p;
  p = &dummy;
  dummy.next = *hp;

  while(p->next && strcmp(plateNum, p->next->plateNum)!= 0){
    p= p->next;
  }
  if (p->next){
    old= p->next;
    p->next = p->next->next;
    *hp = dummy.next;
    return old;
  }
  return NULL;

}
void available_to_rent(car **rent_head, car **rented_head,  int expectedReturnDate){

  car *rent;

  if(*rent_head == NULL ){
    printf("\n\n\nERROR: No cars available to rent\n" );
  }
  else{
    rent= *rent_head;
    *rent_head = rent->next;

    rent->expectedReturnDate = expectedReturnDate;
    insert_rented_list(rented_head, rent);
    printf("\n\n\nUPDATE: %s has been moved from the available-for-rent list to the rented list\n",rent->plateNum);


  }

}
void rented_to_available(car **rent_head, car **rented_head, char plateNum[10], int mileage, double *totalIncome )
{
  car *transfer = NULL;
  double difference;

  transfer = remove_car(rented_head,plateNum);

  difference = mileage - transfer->mileage;

  if(transfer == NULL){
    printf("\n\n\nERROR: Car was never rented. Try again\n" );
  }
  else{
    if(difference > 100){
      *totalIncome = *totalIncome + 40 + ((difference-100) * 0.15);
    }
    else{
      *totalIncome = *totalIncome +40;
    }
    transfer->mileage =mileage;
    transfer->expectedReturnDate = 0;
    insert_car_list(rent_head, transfer);
    printf("\n\n\nUPDATE: %s has been moved from the rented list to the available-for-rent list\n",plateNum);

  }
}

void rented_to_repair(car **rented_head, car **repair_head, char plateNum[10], int mileage,double *totalIncome)
{
  car *transfer = NULL;
  double difference;

  transfer = remove_car(rented_head,plateNum);

  difference = mileage - transfer->mileage;

  if(transfer == NULL){
    printf("\n\n\nERROR: Car was never rented. Try again\n" );
  }
  else{
    if(difference > 100){
      *totalIncome = *totalIncome + 40 + ((difference-100)* 0.15);
    }
    else{
      *totalIncome = *totalIncome +40;
    }
    totalIncome = totalIncome+40;
    transfer->mileage =mileage;
    transfer->expectedReturnDate = 0;
    insert_car_list(repair_head, transfer);
    printf("\n\n\nUPDATE: %s has been moved from the rented list to the repair list\n",plateNum);

  }
}

void repair_to_available(car **rent_head, car **repair_head, char plateNum[10]){

  car *transfer = NULL;

  transfer = remove_car(repair_head,plateNum);

  if(transfer == NULL){
    printf("\n\n\nERROR: Car is not in repair. Try again\n" );
  }
  else{
    insert_car_list(rent_head, transfer);
    printf("\n\n\nUPDATE: %s has been moved from the repair list to the available-for-rent list\n",plateNum);

  }
}

void print_list(car* cp){
  car *print;

  print = cp;

  if(print == NULL){
    printf("No cars.\n" );
  }
  while(print){
    printf("Plate Number: %s\t| Mileage: %d\t\t| Expected Return Date: %d \n",print->plateNum, print->mileage, print->expectedReturnDate);
    print = print->next;
  }
}

int get_mileage(){

  int mileage;

  printf("\nPlease enter an integer of the cars mileage: ");
  scanf("%d", &mileage);

  return mileage;

}

int get_returnDate(){

  int returnDate;

  printf("\nPlease enter an integer of the cars expected return date(yymmdd): ");
  scanf("%d", &returnDate);

  return returnDate;
}


void read_available_file(car **rent_head){

  char tempPlate[8];
  char tempMileage[10];
  int toIntMileage;
  FILE *fp =NULL;
  car *newCar = NULL;

  fp = fopen("available.txt","r");

  if (fp== NULL){
    printf("Can't open or find available.txt\n");
  }
  else{

    while(true){
      fgets(tempPlate, 8, fp);
      fgets(tempMileage,10,fp);
      toIntMileage= atoi(tempMileage);

      if(feof(fp)){
        break;
      }
      newCar = new_car(tempPlate, toIntMileage, 0);
      insert_car_list(rent_head, newCar);
    }

    fclose(fp);
  }


}


void read_rented_file(car **rented_head){

  char tempPlate[8];
  char tempMileage[10];
  int toIntMileage;
  char tempReturn[7];
  int toIntReturn;
  FILE *fp =NULL;
  car *newCar = NULL;

  fp = fopen("rented.txt","r");

  if (fp== NULL){
    printf("Can't open or find repair.txt\n");
  }
  else{

    while(true){
      fgets(tempPlate,8, fp);
      fgets(tempReturn, 7,fp);
      toIntReturn = atoi(tempReturn);
      fgets(tempMileage,10,fp);
      toIntMileage= atoi(tempMileage);

      if(feof(fp)){
        break;
      }
      newCar = new_car(tempPlate, toIntMileage, toIntReturn);
      insert_rented_list(rented_head, newCar);
    }

    fclose(fp);
  }

}

void read_repair_file(car **repair_head){

  char tempPlate[8];
  char tempMileage[10];
  int toIntMileage;
  FILE *fp =NULL;
  car *newCar = NULL;

  fp = fopen("repair.txt","r");

  if (fp== NULL){
    printf("Can't open or find repair.txt\n");
  }
  else{

    while(true){
      fgets(tempPlate,8, fp);
      fgets(tempMileage,10,fp);
      toIntMileage= atoi(tempMileage);

      if(feof(fp)){
        break;
      }
      newCar = new_car(tempPlate, toIntMileage, 0);
      insert_car_list(repair_head, newCar);
    }

    fclose(fp);
  }
}

void write_available_file(car *rent_head){

  car *print;
  FILE *fp = NULL;

  print = rent_head;

  fp = fopen("available.txt","w+");

  while(print){
    fprintf(fp,"%s%d\n",print->plateNum, print->mileage);
    print = print->next;
  }
  fclose(fp);
}

void write_repair_file(car *repair_head){
  car *print;
  FILE *fp = NULL;

  print = repair_head;

  fp = fopen("repair.txt","w+");

  while(print){
    fprintf(fp,"%s%d\n",print->plateNum, print->mileage);
    print = print->next;
  }
  fclose(fp);

}

void write_rented_file(car *rented_head){

  car *print;
  FILE *fp = NULL;

  print = rented_head;

  fp = fopen("rented.txt","w+");

  while(print){
    fprintf(fp,"%s%d%d\n",print->plateNum,print->expectedReturnDate,print->mileage);
    print = print->next;
  }
  fclose(fp);

}
