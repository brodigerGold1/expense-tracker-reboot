# Expense Tracker
This program allows users to enter and store expense details through a simple command line interface, view previously entered expenses in various formats, and automatically remove old expenses if desired.

## Running the program
Running the program requires a C++ compiler to be used on `expense_tracker.cpp`. Using g++, perform the following.
1. Download `expense_tracker.cpp` at the desired directory.
2. Open the terminal/command prompt and navigate to the directory containing the .cpp file.
3. Run `g++ expense_tracker.cpp -std=c++20 -o {filename}`. This will generate a `{filename}.exe` file.
(e.g. `g++ expense_tracker.cpp -std=c++20 -o expense_tracker` will produce `expense_tracker.exe`)
4. Run `{filename}.exe`.
> [!TIP]
> To use the program for multiple users, perform the steps above on separate directories per user.

## Using the Program

### Main Menu
Upon loading the program, the user will see the following menu.
```text
Expense Tracker Menu:
1. Add Expense
2. View Expenses
3. Options
4. Exit
Enter your choice: 
```
A user must enter 1, 2, 3, or 4. Any other input will warn the user of their invalid choice and prompt the user to try again.

### Add Expense
The Add Expense menu will prompt the user to enter an item name, price, category, and up to five levels of optional subcategories. Upon entry, the user will be notified that their item has been added, including the date when it was added.
Example input with all five subcategory levels used:
```text
Item: Gaming Mouse
Price: 1500.00
Category: Electronics
Subcategory 1: Computers
Subcategory 2: Accessories
Subcategory 3: Peripherals
Subcategory 4: Input Devices
Subcategory 5: Gaming Mouse
Your item has been listed! Date: 2026-11-19
```
To use fewer subcategory levels, leave the first unused level blank and enter.
Example input with two subcategories:
```text
Item: Gaming Laptop
Price: 139990.00
Category: Electronics
Subcategory 1: Computers
Subcategory 2: Laptops
Subcategory 3:
Your item has been listed! Date: 2026-11-19
```

### View Expenses
The View Expense menu prompts the user to enter the corresponding letter (case-insensitive) to view saved expenses in various formats or return to the main menu.
- Tree view (T): shows a hierarchical tree view arranged based on categories and subcategories
- Order by Item (I): orders by item name (alphabetical)
- Order by Cheapest Price (C)/Most Expensive (E): orders by item price in ascending or descending order
- Order by Date (D): orders by date, latest expenses first

### Options
The Options menu prompts the user to enter the corresponding letter (case-insensitive) of the setting to be changed.
- Change currency (C): Changes the currency symbol/name to be used (default: PHP)
- Tree sorting (S): Changes how items within the same category and subcategories are ordered and prompts the user to choose an item ordering. May be ordered by item name (I), cheapest (C), or most expensive (E). (default: I)
- Automatic removal (A): Prompts the user to enter the number of days saved expenses will remain. 0 disables automatic removal. (default: 0)

### Exit
Upon exiting the program after entering 4 from the main menu saves all entered expenses and settings to a txt file and exits the program.
> [!CAUTION]
> Exiting the terminal while the program is running will not save added expenses and modified settings.
