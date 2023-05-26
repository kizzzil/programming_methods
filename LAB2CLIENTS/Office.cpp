#include <iostream>
#include "TicketingMachine.cpp"
#include "Customer.cpp"
#include "Logger.cpp"
#include "Config.cpp"
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <algorithm>
#include <map>

using namespace std;
class Office{
private:
    int InitialNumberForTickets;
    int minCustomerArrivalTime;
    int maxCustomerArrivalTime;
    int minServiceTime;
    int maxServiceTime;
    int servedCustomer = 0;
    int maxCustomerAmount;
    int amountOfDesks;
    Logger logger;
    TicketingMachine ticketingMachine;
    queue<Customer> queueOfCustomer;
    // int 

    int generateRandomNumber(int min, int max) {
        random_device rd;  // Инициализация генератора случайных чисел
        mt19937 mt(rd());  // Инициализация генератора случайных чисел
        uniform_int_distribution<int> dist(min, max);  // Определение диапазона
        return dist(mt);  // Генерация случайного числа
    }

    Customer generateCustomer(TicketingMachine& ticketingMachine){
        Customer customer = Customer(ticketingMachine.giveTicket());
        return customer;
    }


    void customersGenetator(){
        for (int i = 0; i < maxCustomerAmount; i++){
            int timeInterval = generateRandomNumber(minCustomerArrivalTime, maxCustomerArrivalTime);
            this_thread::sleep_for(chrono::milliseconds(timeInterval));
            Customer customer = generateCustomer(ticketingMachine);
            // ОБработать лок 
            queueOfCustomer.push(customer);
            logger.log("Arrive new customer with Ticket №" + customer.getTicketNumber());
        }
        logger.log("Closed for new customers, only those in the queue will be served.");
    }



public:
    Office(){
            // Конфигурационные данные 
        Config config = Config();

        this->ticketingMachine = TicketingMachine(config.getConfMap("INITIAL_NUMBER"));
        this->logger = Logger();
        this->queueOfCustomer = queue<Customer>();
        this->maxCustomerAmount = config.getConfMap("MAX_CUSTOMER_AMOUNT");
        this->amountOfDesks = config.getConfMap("AMOUNT_OF_DESKS");
        this->minCustomerArrivalTime = config.getConfMap("MIN_CUSTOMER_ARRIVAL_TIME");
        int maxCustomerArrivalTime = config.getConfMap("MAX_CUSTOMER_ARRIVAL_TIME");
        int minServiceTime = config.getConfMap("MIN_SERVICE_TIME");
        int maxServiceTime = config.getConfMap("MAX_SERVICE_TIME");
    }

    
    void simulateOffice(){
        mutex mutex;
        vector<thread> desks(amountOfDesks);
        cout << "Office opened, welcome!\nToday there are " << amountOfDesks << " desks in the office and it will be able to take "<< maxCustomerAmount <<" customers.\n";

        // thread clients(customersGenetator);
        // clients.join();
    
        // for (int i = 0; i < amountOfDesks; ++i) {
        //     thread()
        // }
        // Дожидаемся завершения всех потоков
        // for_each(threads.begin(), threads.end(), [](thread& t) {
        //     t.join();
        // });

        cout << "Office closed, see you tommorow.";
    }
};
