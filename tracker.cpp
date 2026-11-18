#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <sstream>   
#include <cctype>    
#include <limits>    

using namespace std;

struct Expense {
    string item;
    double price;                  
    string category;
    vector<string> subcategories;  
};

struct ExpenseNode {
    double total = 0.0;
    map<string, ExpenseNode> children;
    vector<Expense> items;
};

struct Settings {
    string symbol = "PHP";   
    char position = 'L';     
    char treeSort = 'I';     
};

Settings settings;           

money(double amount) {
    ostringstream out;
    out << fixed << setprecision(2) << amount;
    string number = out.str();

    string symbol = settings.symbol;
    if (symbol.empty()) return number;

    if (settings.position == 'L') {
        
        bool letters = isalpha(static_cast<unsigned char>(symbol.back()));
        return symbol + (letters ? " " : "") + number;
    } else {
        bool letters = isalpha(static_cast<unsigned char>(symbol.front()));
        return number + (letters ? " " : "") + symbol;
    }
}


void printTreeSorted(const ExpenseNode& node, int depth = 0) {
    vector<const pair<const string, ExpenseNode>*> entries;
    for (const auto& entry : node.children) entries.push_back(&entry);

    stable_sort(entries.begin(), entries.end(),
        [](const pair<const string, ExpenseNode>* a,
           const pair<const string, ExpenseNode>* b) -> bool {
            switch (settings.treeSort) {
                case 'C': return a->second.total < b->second.total;
                case 'E': return a->second.total > b->second.total;
                default:  return a->first < b->first;
            }
        });

    for (const auto* entry : entries) {
        const string& name = entry->first;
        const ExpenseNode& child = entry->second;

        cout << string(depth * 2, ' ') << name
             << " (Total: " << money(child.total) << ")\n";

        vector<const Expense*> items;
        for (const auto& expense : child.items) items.push_back(&expense);

        stable_sort(items.begin(), items.end(),
            [](const Expense* a, const Expense* b) -> bool {
                switch (settings.treeSort) {
                    case 'C': return a->price < b->price;
                    case 'E': return a->price > b->price;
                    default:  return a->item < b->item;
                }
            });

        for (const auto* expense : items) {
            cout << string((depth + 1) * 2, ' ')
                 << "- " << expense->item << " (" << money(expense->price) << ")\n";
        }

        printTreeSorted(child, depth + 1);
    }
}


void changeCurrency() {
    cout << "\n\tCURRENCY\n";
    cout << "Current: " << settings.symbol << " (" << settings.position << ")\n";

    string symbol;
    cout << "Symbol: ";
    getline(cin, symbol);
    if (!symbol.empty()) settings.symbol = symbol;   

    char pos;
    while (true) {
        cout << "Position (L/R): ";
        cin >> pos;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pos = static_cast<char>(toupper(static_cast<unsigned char>(pos)));
        if (pos == 'L' || pos == 'R') break;
        cout << "Please enter L or R.\n";
    }
    settings.position = pos;

    cout << "Currency updated! Example: " << money(1234.5) << "\n";
}

void treeSorting() {
    char choice;
    do {
        cout << "\n\tTREE SORTING\n"
             << "[I] - Order by item\n"
             << "[C] - Order by cheapest\n"
             << "[E] - Order by most expensive\n"
             << "[R] - Return\n"
             << "Choose: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = static_cast<char>(toupper(static_cast<unsigned char>(choice)));

        switch (choice) {
            case 'I': settings.treeSort = 'I'; cout << "Tree is now ordered by item.\n"; break;
            case 'C': settings.treeSort = 'C'; cout << "Tree is now ordered by cheapest.\n"; break;
            case 'E': settings.treeSort = 'E'; cout << "Tree is now ordered by most expensive.\n"; break;
            case 'R': break;
            default:  cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 'R');
}

void optionsMenu() {
    char choice;
    do {
        cout << "\n\tOPTIONS\n"
             << "[C] - Change currency\n"
             << "[S] - Tree sorting\n"
             << "[R] - Return\n"
             << "Choose: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = static_cast<char>(toupper(static_cast<unsigned char>(choice)));

        switch (choice) {
            case 'C': changeCurrency(); break;
            case 'S': treeSorting();    break;
            case 'R': cout << "Returning to Main Menu.\n"; break;
            default:  cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 'R');
}

void printExpense(const Expense& expense) {
    cout << "Item: " << expense.item
         << " | Price: " << money(expense.price)   
         << " | Category: " << expense.category;

    if (!expense.subcategories.empty()) {
        cout << " | Subcategories: ";
        for (size_t i = 0; i < expense.subcategories.size(); ++i) {
            if (i > 0) cout << " > ";
            cout << expense.subcategories[i];
        }
    }
    cout << '\n';
}

void printTree(const ExpenseNode& node, int depth = 0) {
    for (const auto& entry : node.children) {
        const string& name = entry.first;
        const ExpenseNode& child = entry.second;

        cout << string(depth * 2, ' ') << name
             << " (Total: " << child.total << ")\n";

        for (const auto& expense : child.items) {
            cout << string((depth + 1) * 2, ' ')
                 << "- " << expense.item << " (" << expense.price << ")\n";
        }

        printTree(child, depth + 1);
    }
}

void addExpense(vector<Expense>& expenses) {
    Expense expense;
    string subcategory;

    cout << "\n\tADD EXPENSES\n";

    cout << "Item: ";
    getline(cin, expense.item);    

    cout << "Price: ";
    cin >> expense.price;
    cin.ignore();                  

    cout << "Category: ";
    getline(cin, expense.category);

    for (int i = 1; i <= 5; i++) { 
        cout << "Subcategory " << i << ": ";
        getline(cin, subcategory);
        if (subcategory.empty()) break;  
        expense.subcategories.push_back(subcategory);
    }

    expenses.push_back(expense);   
    cout << "Your item has been listed!\n";
}


void viewExpenses(const vector<Expense>& expenses) {
    cout << "\n\t===VIEW EXPENSES===\n";

    if (expenses.empty()) {
        cout << "No expenses to display.\n";
        return;
    }

    char choiceVIEW;

    cout << "[T] - Tree view\n"
         << "[I] - Order by Item\n"
         << "[C] - Order by Cheapest Price\n"
         << "[E] - Order by Most Expensive\n"
         << "[R] - Return to Main Menu\n"
         << "Choose a view: ";

    cin >> choiceVIEW;

    cout << fixed << setprecision(2);

    vector<Expense> sortedExpenses = expenses;

    switch (choiceVIEW) {
        case 'T':case 't': {
            ExpenseNode root;

            for (const auto& expense : expenses) {
                ExpenseNode* current =
                    &root.children[expense.category];

                current->total += expense.price;

                for (const auto& subcategory : expense.subcategories) {
                    current = &current->children[subcategory];
                    current->total += expense.price;
                }

                current->items.push_back(expense);
            }

            cout << "\nTREE\n";
            printTreeSorted(root);   
            break;
        }

        case 'I':case 'i':
            stable_sort(
                sortedExpenses.begin(),
                sortedExpenses.end(),
                [](const Expense& a, const Expense& b) {
                    return a.item < b.item;
                }
            );

            cout << "\nExpenses ordered by Item:\n";

            for (const auto& expense : sortedExpenses) {
                printExpense(expense);
            }
            break;

        case 'C':case 'c':
            stable_sort(
                sortedExpenses.begin(),
                sortedExpenses.end(),
                [](const Expense& a, const Expense& b) {
                    return a.price < b.price;
                }
            );

            cout << "\nExpenses ordered by Cheapest Price:\n";

            for (const auto& expense : sortedExpenses) {
                printExpense(expense);
            }
            break;

        case 'E':case 'e':
            stable_sort(
                sortedExpenses.begin(),
                sortedExpenses.end(),
                [](const Expense& a, const Expense& b) {
                    return a.price > b.price;
                }
            );

            cout << "\nExpenses ordered by Most Expensive:\n";

            for (const auto& expense : sortedExpenses) {
                printExpense(expense);
            }
            break;

        case 'R':case 'r':
            cout << "Returning to Main Menu.\n";
            break;

        default:
            cout << "Invalid choice. Returning to Main Menu.\n";
    }
}

int main() {
    vector<Expense> expenses;
    int choice;

    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Options\n";
        cout << "4. Exit\n";              
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                optionsMenu(); 
                break;
            case 4:                         
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
