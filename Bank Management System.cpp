#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <limits>



struct BankAccount {
    int accountNumber, id;
    std::string accountHolderName;
    std::string accountID;
    std::string password;
    double accountBalance;
    bool loan;
    std::string cnic;
    BankAccount *next;
};


class Bank {
private:
    BankAccount *head;
public:
    Bank() {
        head = NULL;
    }

  void addAccount() {
    std::fstream file;
    std::string cnic;
    file.open("info.txt",std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    int accountNumber;
    std::string accountHolderName;
    double accountBalance;
    bool cnicEntered = false;
    while (!cnicEntered) {
        std::cout << "Enter CNIC (13 digits): ";
        std::cin >> cnic;
        if (cnic.length() == 13) {
            bool cnicIsValid = true;
            for (int i = 0; i < cnic.length(); i++) {
                if (!isdigit(cnic[i])) {
                    cnicIsValid = false;
                    break;
                }
            }
            if (cnicIsValid) {
                cnicEntered = true;
            } else {
                std::cout << "Invalid CNIC, please enter again" << std::endl;
                //break;
            }
        } else {
            std::cout << "Invalid CNIC, please enter again" << std::endl;
        }
    }
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter account holder name: ";
    std::getline(std::cin, accountHolderName);
    std::cout << "Enter account balance: ";
    std::cin >> accountBalance;
    BankAccount *newAccount = new BankAccount();
    newAccount->accountNumber = accountNumber;
    newAccount->accountHolderName = accountHolderName;
    newAccount->accountBalance = accountBalance;
    newAccount->cnic = cnic;
    newAccount->next = head;
    head = newAccount;
    file<< "cnic:" << cnic;
	file<< "\nnumber:" << accountNumber;
	file<< "\nname: " << accountHolderName;
	 file<< "\nbalance: " << accountBalance;
    file.close();
    std::cout << "Data written to file successfully!" << std::endl;
}


  
   void deposit() {
   	
    int accountNumber;
    double amount;
    
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    BankAccount *current = head;
    bool accountFound = false;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            accountFound = true;
            break;
        }
        current = current->next;
    }
    if (!accountFound) {
        std::cout << "Account not found.\n Press 1 to add account or any other key to exit." << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            addAccount();
        }
        else {
            return;
        }
    }
    std::cout << "Enter deposit amount: ";
    std::cin >> amount;

    current->accountBalance += amount;
}

   void withdraw() {
    int accountNumber;
    double amount;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    BankAccount *current = head;
    bool accountFound = false;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            accountFound = true;
            break;
        }
        current = current->next;
    }
    while (!accountFound) {
        std::cout << "Account not found.\n Press 1 to re-enter account number or any other key to exit." << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Enter account number: ";
            std::cin >> accountNumber;
            current = head;
            while (current != NULL) {
                if (current->accountNumber == accountNumber) {
                    accountFound = true;
                    break;
                }
                current = current->next;
            }
        }
        else {
            return;
        }
    }
    bool entered = false;
    while (!entered) {
        std::cout << "Enter withdraw amount: ";
        if (std::cin >> amount) {
            if (amount > 0 && amount <= current->accountBalance) {
                entered = true;
            } else {
                std::cout << "Invalid amount, please enter again" << std::endl;
            }
        } else {
            std::cout << "Invalid input, please enter again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    current->accountBalance -= amount;
}

    
    void displayAccountInfo() 
	{
        int accountNumber;
        
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;

        BankAccount *current = head;
        
        while (current != NULL) {
            if (current->accountNumber == accountNumber) {
                std::cout << "Account Number: " << current->accountNumber << std::endl;
                std::cout << "Account Holder Name: " << current->accountHolderName << std::endl;
                std::cout << "Account Balance: " << current->accountBalance << std::endl;
                break;
            }
            current = current->next;
        }
    }
    
void loan() {
    int accountNumber;
    double loanAmount;

    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    BankAccount *current = head;
    bool accountFound = false;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            accountFound = true;
            break;
        }
        current = current->next;
    }

    if (!accountFound) {
        std::cout << "Account not found. Press 1 to add account or any other key to exit." << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            addAccount();
        } else {
            return;
        }
    }
    std::cout << "Enter loan amount: ";
    std::cin >> loanAmount;

    current->accountBalance += loanAmount;
    current->loan = true;
    std::cout << "Loan approved. Your new balance is: " << current->accountBalance << std::endl;
}

void payLoan() {
    int accountNumber;
    double loanAmount;

    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    BankAccount *current = head;
    bool accountFound = false;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            accountFound = true;
            if(current->loan)
            {
                std::cout << "Enter loan amount to pay: ";
                std::cin >> loanAmount;
                current->accountBalance -= loanAmount;
                if(current->accountBalance>=0)
                {
                    current->loan = false;
                    std::cout << "Loan paid successfully." << std::endl;
                }
                else
                {
                    std::cout << "Insufficient funds." << std::endl;
                }
                break;
            }
            else
            {
                std::cout << "No loan to pay." << std::endl;
                return;
            }
        }
        current = current->next;
    }
    if(!accountFound)
    {
        std::cout << "No account found!" << std::endl;
    }
}

	void checkBalance() {
    int accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    BankAccount *current = head;
    bool accountFound = false;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            accountFound = true;
            break;
        }
        current = current->next;
    }
    if (!accountFound) {
        std::cout << "Account not found.\n Press 1 to add account or any other key to exit." << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            addAccount();
        }
        else {
            return;
        }
    }
    std::cout << "Account balance: " << current->accountBalance << std::endl;
}


void updateRecord() {
    int accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    BankAccount *current = head;
    bool accountFound = false;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            accountFound = true;
            break;
        }
        current = current->next;
    }
    if (!accountFound) {
        std::cout << "Account not found." << std::endl;
        return;
    }
    std::cout << "Enter new account holder name: ";
    std::cin >> current->accountHolderName;
    std::cout << "Record updated successfully." << std::endl;
}


void deleteAccount() {
    int accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    BankAccount *current = head;
    BankAccount *prev = NULL;
    bool accountFound = false;

    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            accountFound = true;
            if(current->loan)
            {
                std::cout << "Cannot delete account. You have an outstanding loan." << std::endl;
                return;
            }
            else
            {
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                std::cout << "Account deleted successfully." << std::endl;
                delete current;
                break;
            }
        }
        prev = current;
        current = current->next;
    }
    if(!accountFound)
    {
        std::cout << "No account found!" << std::endl;
    }
}

};

int main() {
    Bank bank;
    int choice;
    do {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "_________________________________________________________________________________\n";
		std::cout << "**************************** BANK MANAGEMENT SYSTEM ****************************\n";
		std::cout << "_________________________________________________________________________________\n\n\n";
		
		std::cout << "_________________________________________\n";
		std::cout << "1.\t Add account\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";
		std::cout << "2.\t Deposit money\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";
		std::cout << "3.\t Withdraw money\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";
		std::cout << "4.\t Display account information\t|" << std::endl;
		std::cout << "_________________________________________\n";
		std::cout << "5.\t Delete account\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";

		std::cout << "6.\t Loan\t\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";

		std::cout << "7.\t Paying Loan\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";

		
		std::cout << "8.\t Check balance\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";		
		
		std::cout << "9.\t Update Record\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";
		
		std::cout << "10.\t Exit\t\t\t\t|" << std::endl;
		std::cout << "_________________________________________\n";
				
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "\nEnter your choice: ";
		std::cin >> choice;

			switch (choice) {
				case 1:
					bank.addAccount();
					break;
					
				case 2:
					bank.deposit();
					break;
				
				case 3:
					bank.withdraw();
					break;
				
				case 4:
					bank.displayAccountInfo();
					break;

				case 5:
    				bank.deleteAccount();
    				break;
				case 6:
					bank.loan();
					break;
				case 7:
					bank.payLoan();
					break;
					
				case 8:
					bank.checkBalance();
					break;
				
				case 9:
					bank.updateRecord() ;
					break;
									
				case 10:
					exit(0);
			default:
				std::cout << "Invalid choice" << std::endl;
			}	
		} 
		while (true);
			return 0;
}	



