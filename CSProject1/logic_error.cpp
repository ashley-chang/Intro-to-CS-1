// Ashley Chang 504449890

// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;   // pp. 37-38 in Savitch book explain this line

int main()
{
    int numberSurveyed;
    int preferChocolate;
    int preferVanilla;
    
    cout << "How many ice cream lovers were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them prefer chocolate to vanilla? ";
    cin >> preferChocolate;
    cout << "How many of them prefer vanilla to chocolate? ";
    cin >> preferVanilla;
    
    double pctChocolate = 100.0 * preferChocolate / numberSurveyed;
    double pctVanilla = 1000 * preferVanilla / numberSurveyed;      // Logic error: Missing decimal pt.
    
    cout.setf(ios::fixed);       // see pp. 30-31 in Savitch book
    cout.precision(1);
    
    cout << endl;
    cout << pctChocolate << "% prefer chocolate." << endl;
    cout << pctVanilla << "% prefer vanilla." << endl;
    
    if (preferChocolate < preferVanilla)    // Logic error: preferChocolate > preferVanilla
        cout << "Chocolate is more popular than vanilla." << endl;
    else
        cout << "Vanilla is more popular than chocolate." << endl;
}