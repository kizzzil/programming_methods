#include <iostream>
#include "TicketingMachine.cpp"
#include "Customer.cpp"
#include "Logger.cpp"
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
class Office{
private:
    const int minCustomerArrivalTime = 200;
    const int maxCustomerArrivalTime = 300;
    const int minServiceTime = 2000;
    const int maxServiceTime = 3000;
    int servedCustomer = 0;
    int maxCustomerAmount;
    int amountOfDesks;
    Logger *logger;
    TicketingMachine *ticketingMachine;
    queue<Customer> *queueOfCustomer;
    // int 

public:
    Office(int InitialNumberForTickets, int maxCustomerAmount, int amountOfDesks){
        this->ticketingMachine = new TicketingMachine(InitialNumberForTickets);
        this->logger = new Logger;
        this->queueOfCustomer = new queue<Customer>;
        this->maxCustomerAmount = maxCustomerAmount;
        this->amountOfDesks = amountOfDesks;
    }
    
    void simulateOffice(){
        vector<thread> threads;
        cout << "Office opened, welcome!\nToday there are " << amountOfDesks << " desks in the office and it will be able to take "<< maxCustomerAmount <<" customers.\n";
        for (int i = 0; i < amountOfDesks; ++i) {

        }

        // Дожидаемся завершения всех потоков
        // std::for_each(threads.begin(), threads.end(), [](std::thread& t) {
        //     t.join();
        // });
        cout << "Office closed, see you tommorow.";
    }
};
