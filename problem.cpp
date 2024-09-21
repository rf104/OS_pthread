#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex accountMutex;
int accountBalance = 300000;

void withdraw(int amt) {
    lock_guard<mutex> lock(accountMutex);
    if (accountBalance >= amt) {
        accountBalance -= amt;
        cout << "Withdrawal: " << amt << "  New balance: " << accountBalance <<"\n";
    }
    else {
        cout << "No money to withdrawal: "<<amt <<"\n";
    }
}

void credit(int amt) {
    lock_guard<mutex> lock(accountMutex);
    accountBalance += amt;
    cout << "Credit: " << amt << "  New balance: " << accountBalance <<"\n";
}

int main() {
    thread withdraw1(withdraw, 20);
    thread withdraw2(withdraw, 2000);
    thread withdraw3(withdraw, 60);
    thread creditThread(credit, 40000);

    withdraw1.join();
    withdraw2.join();
    withdraw3.join();
    creditThread.join();

    cout << "Final account balance: " << accountBalance << endl;

    return 0;
}
