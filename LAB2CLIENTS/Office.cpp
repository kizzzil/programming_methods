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
    mutex mutex;
    int minCustomerArrivalTime;
    int maxCustomerArrivalTime;
    int minServiceTime;
    int maxServiceTime;
    int servedCustomer = 0;
    int maxCustomerAmount;
    int amountOfDesks;
    Logger logger;
    TicketingMachine ticketingMachine;
    queue<Customer> queueOfCustomers;
    // int 

    int generateRandomNumber(int min, int max) {
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(gen);  // Генерация случайного числа
    }

    // Появление новых посетителей с некоторой задержкой 
    void customersGenetator(){
        for (int i = 0; i < maxCustomerAmount; i++){
            mutex.lock();
            int timeInterval = generateRandomNumber(minCustomerArrivalTime, maxCustomerArrivalTime);
            this_thread::sleep_for(chrono::milliseconds(timeInterval));
            Customer customer = Customer(ticketingMachine.giveTicket());
            queueOfCustomers.push(customer);
            mutex.unlock();
            logger.log("Arrive new customer with Ticket N" + to_string(customer.getTicketNumber()));
        }
        logger.log("Closed for new customers, only those in the queue will be served.");
    }

    // Обслуживание
    void serveCustomer(Customer &customer, int deskNumber){
        int serviceTime = generateRandomNumber(minCustomerArrivalTime, maxCustomerArrivalTime);
        this_thread::sleep_for(chrono::milliseconds(serviceTime));
        mutex.lock();
        servedCustomer++;
        string ticket = to_string(customer.getTicketNumber());
        // cout << customer.getTicketNumber() <<"\n";
        mutex.unlock();
        logger.log("Desk "+ to_string(deskNumber) + " served customer N" + ticket);
    }

    bool isTooManyCustomers(){
        lock_guard<std::mutex> lock(mutex);
        return servedCustomer < maxCustomerAmount;
    }

    bool isCustomerWaiting(){
        lock_guard<std::mutex> lock(mutex);
        return !queueOfCustomers.empty();
    }




public:
    Office(): logger(mutex){
            // Конфигурационные данные 
        Config config = Config();
        this->ticketingMachine = TicketingMachine(config.getConfMap("INITIAL_NUMBER"));
        // this->logger = Logger();
        this->queueOfCustomers = queue<Customer>();
        this->maxCustomerAmount = config.getConfMap("MAX_CUSTOMER_AMOUNT");
        this->amountOfDesks = config.getConfMap("AMOUNT_OF_DESKS");
        this->minCustomerArrivalTime = config.getConfMap("MIN_CUSTOMER_ARRIVAL_TIME");
        this->maxCustomerArrivalTime = config.getConfMap("MAX_CUSTOMER_ARRIVAL_TIME");
        this->minServiceTime = config.getConfMap("MIN_SERVICE_TIME");
        this->maxServiceTime = config.getConfMap("MAX_SERVICE_TIME");
    }

    
    void simulateOffice(){
        vector<thread> desks;
        vector<bool> busyDesks(amountOfDesks, false);
        cout << "Office opened, welcome!\nToday there are " << amountOfDesks << " desks in the office and it will be able to take "<< maxCustomerAmount <<" customers.\n";

        thread customers([&]{
            customersGenetator();
        });
        // customersGenetator(mutex);

        for (int i = 0; i < amountOfDesks; ++i) {
            desks.emplace_back([&, i]() {
            logger.log("Desk N" + to_string(i+1) + " active.");
            while (isTooManyCustomers()) { 
                if (isCustomerWaiting()){
                    mutex.lock();
                    Customer customer = queueOfCustomers.front();
                    // cout << "1:" << customer.getTicketNumber() << "\n";
                    queueOfCustomers.pop();
                    mutex.unlock();
                    serveCustomer(customer, i + 1);
                }
            }

            logger.log("Desk " + std::to_string(i + 1) + " closed.");
        });
        }
        customers.join();

        // for(int i = 0; i < amountOfDesks; i++){
            
        //     logger.log("Desk N" + to_string(i+1) + " active.");
        // }
    
        // for (int i = 0; i < amountOfDesks; ++i) {
        //     thread()
        // }
        
        // Дожидаемся завершения всех потоков
        for_each(desks.begin(), desks.end(), [](thread& t) {
            t.join();
        });
        // customers.join()

        // customers.join();
        logger.log("Office closed, see you tommorow.");
        logger.log(to_string(servedCustomer));
    }
};