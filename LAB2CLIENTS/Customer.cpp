class Customer{
private:
    int ticket;
    /* data */
public:
    int getTicketNumber(){
        return  this->ticket;
    }

    Customer(int ticket){
        this->ticket = ticket;
    }
};
