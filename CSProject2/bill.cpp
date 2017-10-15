// Project 2
// Ashley Chang 504449890
// Due 4/18/2015 9:00 PM

#include <iostream>
#include <string>

using namespace std;

int main ()
{
    int initialReading;
    int finalReading;
    
    cout << "Initial meter reading: ";              // Meter readings in HCF; get values
    cin >> initialReading;
    cout << "Final meter reading: ";
    cin >> finalReading;
    cin.ignore(10000, '\n');                        // Ask for string after asking for integer--ignore
    
    string customerName;                            // Get customer name in string
    cout << "Customer name: ";
    getline(cin, customerName);
    
    int monthNumber;                                // Get month number
    cout << "Month number (1=Jan, 2=Feb, etc.): ";
    cin >> monthNumber;
    
    cout << "---" << endl;                          // Finish collecting data
    
    // Set up bill variables
    
    int totalUsage = finalReading - initialReading;
    double finalBill;
    cout.setf(ios::fixed);
    cout.precision(2);
    
    const double FIRST_TIER_RATE = 2.75;
    const double SECOND_TIER_RATE_HIGH = 3.38;
    const double SECOND_TIER_RATE_LOW = 2.89;
    const int HCF_THRESHOLD_HIGH = 44;
    const int HCF_THRESHOLD_LOW = 31;
    
    // Error Messages

    if (initialReading < 0)                                 // Initial meter reading is negative
    {
        cout << "The initial meter reading must be nonnegative." << endl;
    }
    else if (finalReading < initialReading)                 // Final reading less than initial reading
    {
        cout << "The final reading must be at least as large as the initial reading." << endl;
    }
    else if (customerName == "")                            // Empty string provided for customer name
    {
        cout << "You must enter a customer name." << endl;
    }
    else if (monthNumber < 1 || monthNumber > 12)           // Month no. not integer between 1 & 12
    {
        cout << "The month number must be in the range 1 through 12." << endl;
    }
    else
    {
        if (monthNumber >= 4 && monthNumber <= 10)          // HIGH usage season from April to October
        {
            if (totalUsage <= HCF_THRESHOLD_HIGH)           // If use 44 or less HCF, charge first tier
            {
                finalBill = totalUsage * FIRST_TIER_RATE;
            }
            else                                            // If use more than 44 HCF, charge second tier high
            {
                finalBill = (HCF_THRESHOLD_HIGH * FIRST_TIER_RATE) + ((totalUsage - HCF_THRESHOLD_HIGH) * SECOND_TIER_RATE_HIGH);
            }
        }
        else if (monthNumber <= 3 || monthNumber >= 11)     // LOW usage season from November to March
        {
            if (totalUsage <= HCF_THRESHOLD_LOW)            // If use 31 or less HCF, charge first tier
            {
                finalBill = totalUsage * FIRST_TIER_RATE;
            }
            else                                            // If use more than 31 HCF, charge second tier low
            {
                finalBill = (HCF_THRESHOLD_LOW * FIRST_TIER_RATE) + ((totalUsage - HCF_THRESHOLD_LOW) * SECOND_TIER_RATE_LOW);
            }
    }
        cout << "The bill for " << customerName << " is $" << finalBill << endl;
    }
   
    return 0;
}
