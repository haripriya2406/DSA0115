#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class SavingsAccount {
private:
    static const int MAX_TX = 10;
    double balance;
    string transactions[MAX_TX];
    int head;
    int count;

    void record(const string& entry) {
        int position;
        if (count < MAX_TX) {
            position = (head + count) % MAX_TX;
            ++count;
        } else {
            position = head;
            head = (head + 1) % MAX_TX;
        }
        transactions[position] = entry;
    }

public:
    explicit SavingsAccount(double openingBalance)
        : balance(openingBalance), head(0), count(0) {}

    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        record("Deposit: +" + to_string(amount));
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        record("Withdraw: -" + to_string(amount));
        return true;
    }

    double getBalance() const {
        return balance;
    }

    void printStatement() const {
        cout << "\nLast " << count << " transactions:\n";
        for (int i = 0; i < count; ++i) {
            int position = (head + i) % MAX_TX;
            cout << transactions[position] << '\n';
        }
        cout << fixed << setprecision(2)
             << "Current balance: Rs. " << balance << '\n';
    }
};

int main() {
    SavingsAccount account(5000.00);

    account.deposit(1000);
    account.withdraw(500);
    account.deposit(250);
    account.withdraw(100);
    account.deposit(700);
    account.withdraw(200);
    account.deposit(300);
    account.withdraw(150);
    account.deposit(400);
    account.withdraw(50);
    account.deposit(900); // 11th transaction overwrites the oldest

    cout << fixed << setprecision(2)
         << "Balance: Rs. " << account.getBalance() << '\n';

    if (!account.withdraw(10000))
        cout << "Overdraft rejected.\n";
    if (!account.deposit(-100))
        cout << "Invalid deposit rejected.\n";

    account.printStatement();
    return 0;
}