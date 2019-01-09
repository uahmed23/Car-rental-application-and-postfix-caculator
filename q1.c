#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

int main(int argc, char const *argv[]) {

  car *rent_head = NULL;
  car *rented_head =NULL;
  car *repair_head =NULL;
  car *newCar = NULL;
  double totalIncome = 0;
  char plateNum[10];
  int mileage = 0;
  int returnDate = 0;
  bool loop = true;
  int transactionCode = 0;
  int i =0;


  read_available_file(&rent_head);
  read_repair_file(&repair_head);
  read_rented_file(&rented_head);



  printf("\n\t\t\t\tWELCOME\n" );
  while (loop) {

    transactionCode = options();

    if(transactionCode == 1){
    //1. add a new car to the available-for-rent list

      printf("Please enter a string of the cars plate number: ");

      getchar(); // empties stdin of extra spaces
      fgets(plateNum, 10, stdin);
      for(i=0; i<strlen(plateNum); i++ ){ //removes a newline char from string
        if(plateNum[i] == '\n'){
          plateNum[i] = '\0';
        }
      }

      mileage = get_mileage();

      newCar = new_car(plateNum, mileage, 0);
      insert_car_list(&rent_head, newCar);

      printf("\n\n\nUPDATE: %s has been added to the available-for-rent list\n",plateNum);


    }
    if(transactionCode == 2 ){
    //2. add a returned car to the available-for-rent list

      printf("Please enter a string of the cars plate number: ");

      getchar(); // empties stdin of extra spaces
      fgets(plateNum, 10, stdin);
      for(i=0; i<strlen(plateNum); i++ ){ //removes a newline char from string
        if(plateNum[i] == '\n'){
          plateNum[i] = '\0';
        }
      }

      mileage = get_mileage();

      rented_to_available(&rent_head, &rented_head, plateNum, mileage, &totalIncome);


    }

    if(transactionCode == 3 ){
    //3. add returned car to the repair list.

      printf("Please enter a string of the cars plate number: ");

      getchar(); // empties stdin of extra spaces
      fgets(plateNum, 10, stdin);

        for(i=0; i<strlen(plateNum); i++ ){ //removes a newline char from string
        if(plateNum[i] == '\n'){
          plateNum[i] = '\0';
        }

      }

      mileage = get_mileage();

      rented_to_repair(&rented_head, &repair_head, plateNum, mileage, &totalIncome);


    }
    else if(transactionCode == 4){
    //Transfer a car from the repair list to the available-for-rent list
      printf("Please enter a string of the cars plate number: ");

      getchar(); // empties stdin of extra spaces
      fgets(plateNum, 10, stdin);

      for(i=0; i<strlen(plateNum); i++ ){ //removes a newline char from string
        if(plateNum[i] == '\n'){
          plateNum[i] = '\0';
        }
      }

      repair_to_available(&rent_head, &repair_head, plateNum);

    }
    else if(transactionCode == 5){
    //rent the first available car
      returnDate = get_returnDate();
      available_to_rent(&rent_head, &rented_head, returnDate);

    }
    else if(transactionCode == 6){
    //Print all lists

    printf("Cars available to rent:\n" );
    print_list(rent_head);

    printf("\nCars in repair:\n" );
    print_list(repair_head);

    printf("\nCars rented:\n" );
    print_list(rented_head);
    }

    else if(transactionCode == 7){
    // Exit
      printf("Total Income: %.2lf\n",totalIncome );
      loop = false;
    }
    else if (transactionCode<1 || transactionCode>7 ){
      printf("\n\n\nError: please enter vaild transaction codes\n" );
    }

  }

  write_available_file(rent_head);
  write_repair_file(repair_head);
  write_rented_file(rented_head);


  return 0;
}
