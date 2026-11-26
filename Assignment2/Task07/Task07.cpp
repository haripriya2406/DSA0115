#include <iostream>
#include <string>
using namespace std;

class SavingsAccount {
private:
    static const int MAX_TX = 50;
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
        record("Deposit +" + to_string(amount));
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        record("Withdraw -" + to_string(amount));
        return true;
    }

    double getBalance() const {
        return balance;
    }

    void printStatement() const {
        cout << "Last " << count << " transactions:\n";
        for (int i = 0; i < count; ++i) {
            int position = (head + i) % MAX_TX;
            cout << transactions[position] << '\n';
        }
    }
};

int main() {
    SavingsAccount account(10000.0);

    for (int i = 1; i <= 60; ++i) {
        if (i % 2 == 0)
            account.withdraw(10.0);
        else
            account.deposit(20.0);
    }

    cout << "Final balance: " << account.getBalance() << '\n';
    cout << "Expected balance: 10300\n";
    cout << "Last 50 transactions (oldest to newest):\n";
    account.printStatement();

    if (account.withdraw(100000))
        cout << "Unexpected withdrawal success\n";
    else
        cout << "Overdraft test: PASS\n";

    if (account.deposit(-1))
        cout << "Unexpected invalid deposit success\n";
    else
        cout << "Invalid deposit test: PASS\n";

    return 0;
}