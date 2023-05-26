class Customer{
private:
    int ticket;
    /* data */
public:
    int getTicketNumber(){
        return ticket;
    }
    Customer(int ticket){
        this->ticket = ticket;
    }
};
