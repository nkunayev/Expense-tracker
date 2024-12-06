#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

class Expense {
private:
    std::string category;
    double amount;

public:
    Expense(const std::string& category, double amount)
        : category(category), amount(amount) {}

    std::string getCategory() const { return category; }
    double getAmount() const { return amount; }

    // Display expense details
    void display() const {
        std::cout << std::left << std::setw(15) << category 
                  << "$" << std::fixed << std::setprecision(2) << amount << "\n";
    }
};

class ExpenseTracker {
private:
    std::vector<Expense> expenses;

public:
    // Add an expense
    void addExpense(const std::string& category, double amount) {
        expenses.emplace_back(category, amount);
        std::cout << "Expense added successfully!\n";
    }

    // Display all expenses
    void viewExpenses() const {
        std::cout << "\n=== Expense List ===\n";
        std::cout << std::left << std::setw(15) << "Category" << "Amount\n";
        std::cout << "---------------------\n";
        for (const auto& expense : expenses) {
            expense.display();
        }
        std::cout << "=====================\n";
    }

    // Save expenses to a file
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for writing!\n";
            return;
        }

        for (const auto& expense : expenses) {
            file << expense.getCategory() << "," << expense.getAmount() << "\n";
        }

        std::cout << "Expenses saved to " << filename << "\n";
    }

    // Load expenses from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading!\n";
            return;
        }

        expenses.clear();
        std::string category;
        double amount;
        while (file >> category >> amount) {
            expenses.emplace_back(category, amount);
        }

        std::cout << "Expenses loaded from " << filename << "\n";
    }
};

void displayMenu() {
    std::cout << "\n=== Expense Tracker ===\n";
    std::cout << "1. Add Expense\n";
    std::cout << "2. View Expenses\n";
    std::cout << "3. Save Expenses to File\n";
    std::cout << "4. Load Expenses from File\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    ExpenseTracker tracker;
    int choice;
    std::string category, filename;
    double amount;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter category: ";
            std::cin >> category;
            std::cout << "Enter amount: ";
            std::cin >> amount;
            tracker.addExpense(category, amount);
            break;

        case 2:
            tracker.viewExpenses();
            break;

        case 3:
            std::cout << "Enter filename to save: ";
            std::cin >> filename;
            tracker.saveToFile(filename);
            break;

        case 4:
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            tracker.loadFromFile(filename);
            break;

        case 5:
            std::cout << "Exiting program. Goodbye!\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
