#include <iostream>
using namespace std;

class CashRegister
{
public:
    CashRegister(double rate = 0.0);

    void clear();
    void add_item(double price);              
    void add_taxable_item(double price);      
    int get_count() const;
    double get_total() const;
    double get_total_tax() const;

private:
    double prices[100];
    bool is_taxable[100];
    int count;
    double tax_rate;
};


CashRegister::CashRegister(double rate)
{
    tax_rate = rate;
    count = 0;
}

void CashRegister::clear()
{
    count = 0;
}

void CashRegister::add_item(double price)
{
    prices[count] = price;
    is_taxable[count] = false;
    count++;
}

void CashRegister::add_taxable_item(double price)
{
    prices[count] = price;
    is_taxable[count] = true;
    count++;
}

int CashRegister::get_count() const
{
    return count;
}

double CashRegister::get_total() const
{
    double total = 0;
    for (int i = 0; i < count; i++)
    {
        total += prices[i];
    }
    return total + get_total_tax(); 
}

double CashRegister::get_total_tax() const
{
    double tax = 0;
    for (int i = 0; i < count; i++)
    {
        if (is_taxable[i])
        {
            tax += prices[i] * tax_rate;
        }
    }
    return tax;
}


int main()
{
    CashRegister reg1(0.07); 
    reg1.clear();
    reg1.add_item(5.00);              
    reg1.add_taxable_item(10.00);     

    cout << "Subtotal: $" << reg1.get_total() - reg1.get_total_tax() << endl;
    cout << "Tax: $" << reg1.get_total_tax() << endl;
    cout << "Total due: $" << reg1.get_total() << endl;

    return 0;
}

