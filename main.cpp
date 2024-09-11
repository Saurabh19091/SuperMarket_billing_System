#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

// Bill class encapsulating item details and method overloading for cost calculation
class Bill {
private:
    string Items;
    int Quantity, Rate;

public:
    Bill() : Items(""), Rate(0), Quantity(0) {}

    void setItem(string items) {
        Items = items;
    }

    void setRate(int rate) {
        Rate = rate;
    }

    void setQuantity(int quant) {
        Quantity = quant;
    }

    string getItem() {
        return Items;
    }

    int getRate() {
        return Rate;
    }

    int getQuantity() {
        return Quantity;
    }

    // Method overloading for calculating the total cost

    // Simple method to calculate cost without discount
    double bill(double cost) {
        return cost;
    }

    // Method to calculate cost with a flat discount
    double bill(double cost, double discount) {
        return cost - discount;
    }

    // Method to calculate cost with a percentage discount
    double bill(double cost, double discountPercent, bool isPercentage) {
        if (isPercentage) {
            return cost - (cost * discountPercent / 100);
        }
        return cost;
    }

    // Method to calculate cost with a coupon code
    double bill(double cost, string coupon, map<string, double>& couponData) {
        // Check if the coupon is valid
        if (couponData.find(coupon) != couponData.end()) {
            double discountPercent = couponData[coupon];
            cout << "\nCoupon Applied: " << coupon << ", Discount: " << discountPercent << "%\n";
            return cost - (cost * discountPercent / 100);
        } else {
            cout << "\nInvalid Coupon Code! No discount applied.\n";
            return cost;
        }
    }
};

// Function to add items
void addItem(Bill& b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add Item." << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;
        if (choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity of Item: ";
            cin >> quant;
            b.setQuantity(quant);

            ofstream out("D:\\saurabh\\bill.txt", ios::app); 
            if (!out) {
                cout << "\tError: File can't Open!" << endl;
            } else {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuantity() << endl << endl;
            }
            out.close();
            cout << "\tItem Added Successfully" << endl;
            Sleep(3000);
        } else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
        }
    }
}

// Function to print bill using overloaded methods
void printBill(Bill& b, map<string, double>& couponData) {
    system("cls");
    int totalAmount = 0;
    bool close = false;
    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Add Bill" << endl;
        cout << "\t2. Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;
        if (choice == 1) {
            string itemName;
            int quant;
            cout << "\tEnter Item: ";
            cin >> itemName;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("D:\\saurabh\\bill.txt");
            ofstream out("D:\\saurabh\\bill temp.txt");

            string line;
            bool found = false;
            while (getline(in, line)) {
                stringstream ss;
                ss << line;
                string name;
                int rate, itemQuant;
                char delimiter;
                ss >> name >> delimiter >> rate >> delimiter >> itemQuant;
                if (itemName == name) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = rate * quant;
                        cout << "\t Item  | Rate | Quantity | Amount" << endl;
                        cout << "\t" << name << "\t " << rate << "\t " << quant << "\t" << amount << endl;
                        int newQuant = itemQuant - quant;
                        itemQuant = newQuant;
                        totalAmount += amount;
                        out << "\t" << name << " : " << rate << " : " << itemQuant << endl << endl;
                    } else {
                        cout << "\tSorry, " << itemName << " Ended!" << endl;
                    }
                } else {
                    out << line << endl;
                }
            }
            if (!found) {
                cout << "\t" << itemName << " Not Available!" << endl;
            }
            out.close();
            in.close();
            remove("D:\\saurabh\\bill.txt");
            rename("D:\\saurabh\\bill temp.txt", "D:\\saurabh\\bill.txt");
        } else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
        }
        Sleep(3000);
    }

    // Apply bill method overloading to calculate final amount
    cout << "\nChoose Discount Type:" << endl;
    cout << "\t1. No Discount" << endl;
    cout << "\t2. Flat Discount" << endl;
    cout << "\t3. Percentage Discount" << endl;
    cout << "\t4. Coupon Discount" << endl;
    cout << "\tEnter Choice: ";
    int discountChoice;
    cin >> discountChoice;

    double finalAmount = 0;

    if (discountChoice == 1) {
        // No discount
        finalAmount = b.bill(totalAmount);
    } else if (discountChoice == 2) {
        // Flat discount (e.g., $50 off)
        double flatDiscount;
        cout << "\tEnter Flat Discount Amount: ";
        cin >> flatDiscount;
        finalAmount = b.bill(totalAmount, flatDiscount);
    } else if (discountChoice == 3) {
        // Percentage discount (e.g., 10% off)
        double percentage;
        cout << "\tEnter Discount Percentage: ";
        cin >> percentage;
        finalAmount = b.bill(totalAmount, percentage, true);
    } else if (discountChoice == 4) {
        // Coupon discount
        string coupon;
        cout << "\tEnter Coupon Code: ";
        cin >> coupon;
        finalAmount = b.bill(totalAmount, coupon, couponData);
    }

    cout << "\tTotal Amount: " << totalAmount << endl;
    cout << "\tFinal Amount after Discount: " << finalAmount << endl;
    cout << "\tThank you for shopping!" << endl;
    Sleep(5000);
}

int main() {
    Bill b1;
    
    // Initialize coupon data (coupon codes and discount percentages)
    map<string, double> couponData;
    couponData["SAVE10"] = 10.0; // 10% discount
    couponData["OFF50"] = 50.0;  // 50% discount
    couponData["WELCOME20"] = 20.0; // 20% discount

    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t***************************************" << endl;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Print Bill" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            addItem(b1);
        } else if (val == 2) {
            system("cls");
            printBill(b1, couponData);
        } else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(3000);
        }
    }
    return 0;
}

