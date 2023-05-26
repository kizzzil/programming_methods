#include <string>
using namespace std;
class TicketingMachine {
private:
    int currentNumberOfTicket;
public:
    int giveTicket(){
        return currentNumberOfTicket++;
    } 
    TicketingMachine(int initialNunber){
        this->currentNumberOfTicket = initialNunber;
    }


// private:
//     int currentNumberOfTicket;
//     static TicketsMachine* instance;
//     TicketsMachine(){}

// public:
//     TicketsMachine(const TicketsMachine&) = delete; // Запрет копирования
    
//     static TicketsMachine* getInstance(){
//         if (instance == NULL){
//             // We can access private members
//             // within the class.
//             instance = new TicketsMachine;
            
//             // returning the instance pointer
//             return instance;
//         }
//         else
//         {
//             return instance;
//         }
//     }
    // int giveTicket(){
    //     return ++currentNumberOfTicket;
    // } 

    // void setInitial(int initialNumber){
    //     this->currentNumberOfTicket = initialNumber;
    // }
    // Другие методы и члены класса
};
