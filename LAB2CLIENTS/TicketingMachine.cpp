#include <string>
using namespace std;
class TicketingMachine {
private:
    int currentNumberOfTicket;
public:
    int giveTicket(){
        // lock_guard<mutex> lock(mutex);
        return currentNumberOfTicket++;
    } 

    TicketingMachine(int initialNumber){
        this->currentNumberOfTicket = initialNumber;
    }
    // ЧТобы компилятор не ругался
    TicketingMachine(){}
};
