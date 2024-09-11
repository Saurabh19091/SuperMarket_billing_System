#include <bits/stdc++.h>
using namespace std;

class Bill
{
private:
    string Items;
    int Quantity, Rate;

public:
    Bill() : Items(""), Rate(0), Quantity(0) {}

    void setItem(string items)
    {
        Items = items;
    }

    void setRate(int rate)
    {
        Rate = rate;
    }

    void setQuantity(int quant)
    {
        Quantity = quant;
    }

    string getItem()
    {
        return Items;
    }

    int getRate()
    {
        return Rate;
    }

    int getQuantity()
    {
        return Quantity;
    }
};

void addItem(Bill &b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1.Add." << endl;
        cout << "\t2.close" << endl;
        cout << "\tEnter Choice";
        cin >> choice;
        if (choice == 1)
        {
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
            if (!out)
            {
                cout << "\tError: File can't Open!" << endl;
            }
            else
            {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuantity() << endl
                    << endl;
            }
            out.close();
            cout << "\tItem Added Successfully" << endl;
            Sleep(3000);
        }
        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
        }
    }
}

int main()
{
    Bill b1;
    bool exit = false;
    while (!exit)
    {
        system("cls");
        int val;
        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t***************************************" << endl;
        cout << "\t\t1.add Item." << endl;
        cout << "\t\t2.Print Bill." << endl;
        cout << "\t\t3.Exit." << endl;
        cout << "\t\Enter Choice: ";
        cin >> val;
        if (val == 1)
        {
            addItem(b1);
        }
        else if (val == 2)
        {
            // Add code to print bill
        }
        else if (val == 3)
        {
            exit = true;
        }
    }
    return 0;
}