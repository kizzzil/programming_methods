#include <iostream>
#include "Office.cpp"

using namespace std;

main(){
    // Конфигурационные данные 
    int initialNumber = 1;
    int maxCustomerAmount = 10;
    int amountOfDesks = 3;
    
    // Начало работы
    Office *office = new Office(initialNumber, maxCustomerAmount, amountOfDesks);
    office->simulateOffice();
}