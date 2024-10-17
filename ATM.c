#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10
#define MAX_HISTORY 20

// Structure to represent an account
struct Account {
    int accountNumber;
    char name[50];
    float balance;
    char pin[5];
    char history[MAX_HISTORY][100];
    int historyCount;
};

struct Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
int currentAccountIndex = -1;

void displayBalance(struct Account *account) {
    printf("Account Number: %d\n", account->accountNumber);
    printf("Name: %s\n", account->name);
    printf("Your account balance is: $%.2f\n", account->balance);
}

void deposit(struct Account *account) {
    float amount;
    printf("Enter the amount to deposit: $");
    scanf("%f", &amount);

    if (amount > 0) {
        account->balance += amount;
        printf("Deposit successful. Your new balance is: $%.2f\n", account->balance);
        snprintf(account->history[account->historyCount], sizeof(account->history[account->historyCount]), "Deposited $%.2f", amount);
        account->historyCount++;
    } else {
        printf("Invalid amount. Please enter a positive amount.\n");
    }
}

void withdraw(struct Account *account) {
    float amount;
    printf("Enter the amount to withdraw: $");
    scanf("%f", &amount);

    if (amount > 0) {
        if (amount <= account->balance) {
            account->balance -= amount;
            printf("Withdrawal successful. Your new balance is: $%.2f\n", account->balance);
            snprintf(account->history[account->historyCount], sizeof(account->history[account->historyCount]), "Withdrawn $%.2f", amount);
            account->historyCount++;
        } else {
            printf("Insufficient balance. Your balance is: $%.2f\n", account->balance);
        }
    } else {
        printf("Invalid amount. Please enter a positive amount.\n");
    }
}

void showHistory(struct Account *account) {
    printf("Transaction History for Account Number %d:\n", account->accountNumber);
    for (int i = 0; i < account->historyCount; i++) {
        printf("%d. %s\n", i + 1, account->history[i]);
    }
}

void createAccount() {
    if (accountCount < MAX_ACCOUNTS) {
        struct Account newAccount;
        newAccount.accountNumber = accountCount + 1;
        printf("Enter your name: ");
        scanf("%s", newAccount.name);
        printf("Enter a 4-digit PIN for your account: ");
        scanf("%s", newAccount.pin);
        newAccount.balance = 0.0;
        newAccount.historyCount = 0;
        accounts[accountCount] = newAccount;
        printf("Account created successfully. Your account number is: %d\n", newAccount.accountNumber);
        accountCount++;
    } else {
        printf("Maximum number of accounts reached. Cannot create more accounts.\n");
    }
}

int authenticateAccount() {
    char pin[5];
    printf("Enter your account number: ");
    int accountNumber;
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Enter your 4-digit PIN: ");
            scanf("%s", pin);
            if (strcmp(accounts[i].pin, pin) == 0) {
                currentAccountIndex = i;
                return 1; // Authentication successful
            }
        }
    }
    return 0; // Authentication failed
}

int main() {
    int choice;

    while (1) {
        if (currentAccountIndex == -1) {
            printf("\nWelcome to the ATM\n");
            printf("1. Create Account\n");
            printf("2. Login\n");
            printf("3. Exit\n");
        } else {
            printf("\nATM Menu:\n");
            printf("1. Check Balance\n");
            printf("2. Deposit\n");
            printf("3. Withdraw\n");
            printf("4. View Transaction History\n");
            printf("5. Logout\n");
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (currentAccountIndex == -1) {
            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    if (authenticateAccount()) {
                        printf("Login successful.\n");
                    } else {
                        printf("Login failed. Please check your account number and PIN.\n");
                    }
                    break;
                case 3:
                    printf("Thank you for using this ATM. Goodbye!\n");
                    return 0;
                default:
                    printf("Invalid choice. Please select a valid option.\n");
            }
        } else {
            switch (choice) {
                case 1:
                    displayBalance(&accounts[currentAccountIndex]);
                    break;
                case 2:
                    deposit(&accounts[currentAccountIndex]);
                    break;
                case 3:
                    withdraw(&accounts[currentAccountIndex]);
                    break;
                case 4:
                    showHistory(&accounts[currentAccountIndex]);
                    break;
                case 5:
                    printf("Logout successful. Thank you for using this ATM. Goodbye!\n");
                    currentAccountIndex = -1;
                    break;
                default:
                    printf("Invalid choice. Please select a valid option.\n");
            }
        }
    }

    return 0;
}                            
