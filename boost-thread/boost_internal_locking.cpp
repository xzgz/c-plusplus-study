#include <boost/thread/thread.hpp>
#include <iostream>


class BankAccount {
    boost::mutex mtx_;
    int balance_ = 0;
public:
    void Deposit(int amount) {
        mtx_.lock();
        balance_ += amount;
        mtx_.unlock();
    }
    void Withdraw(int amount) {
        mtx_.lock();
        balance_ -= amount;
        mtx_.unlock();
    }
    int GetBalance() {
        mtx_.lock();
        int b = balance_;
        mtx_.unlock();
        return b;
    }
};


BankAccount JoesAccount;

void bankAgent()
{
    for (int i =10; i>0; --i) {
        JoesAccount.Deposit(500);
    }
}

void Joe() {
    for (int i =10; i>0; --i) {
        JoesAccount.Withdraw(100);
        int myPocket = JoesAccount.GetBalance();
        std::cout << myPocket << std::endl;
    }
}

int main() {
    //...
    boost::thread thread1(bankAgent); // start concurrent execution of bankAgent
    boost::thread thread2(Joe); // start concurrent execution of Joe
    thread1.join();
    thread2.join();
    std::cout << "final balance: " << JoesAccount.GetBalance() << std::endl;

    return 0;
}