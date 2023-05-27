#include <string>
using namespace std;
class TicketingMachine {
private:
    int currentNumberOfTicket;
public:
    int giveTicket(){
        // lock_guard<mutex> lock(mutex);
        int i = currentNumberOfTicket++;
        // cout << i << "\n";
        // return currentNumberOfTicket++;
        return i;
    } 

    TicketingMachine(int initialNumber){
        this->currentNumberOfTicket = initialNumber;
    }
    // ЧТобы компилятор не ругался
    TicketingMachine(){}
};
