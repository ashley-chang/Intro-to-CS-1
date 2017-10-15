// Ashley Chang
// 504449890
// Project 4


#include <iostream>
#include <string>
#include <cassert> 

using namespace std;
// If n is negative, return -1.

// ******************************************************************************************************
// ENUMERATE

// Return number of strings in array that are equal to target.
// If n is negative, return -1.
int enumerate(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    int equal = 0; // Records how many times target appears
    for (int k = 0; k < n; k++) // Look at every string in array
    {
        if (a[k] == target) // If string is equal to target, equal counter increases by 1
            equal++;
    }
    return equal;
}
// ******************************************************************************************************
// LOCATE

// Return the position of the first string in the array that is equal to target.
// Return -1 if no such string.
int locate(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    for (int k = 0; k < n; k++) // Look at every string in array
    {
        if (a[k] == target) //As soon as a string is equal to target, return position of that element
        {
            return k;
        }
    }
    return -1;
}
// ******************************************************************************************************
// LOCATE SEQUENCE

bool locateSequence(const string a[], int n, string target, int& begin, int& end)
{
    if (n < 0)
        return false;
    for (int k = 0; k < n; k++)
    {
        if (a[k] == target) // If string is equal to target,
        {
            begin = k;
            int j = k+1;
            while (a[k] == a[j] && j < n) // Check if following strings are also equal (consecutive)
            {
                j++;
            }
            end = j-1; // If next string is not equal, then set end to last consecutive string
            return true;
        }
    }
    return false;
}
// ******************************************************************************************************
// LOCATION OF MIN

int locationOfMin(const string a[], int n)
{
    if (n <= 0)
        return -1;
    int smallestPosition = 0; //Stores the position of the current smallest string
    string smallest = a[0]; //Initialize the smallest string as the first string (will compare with other strings)

    for (int k = 0; k < n ; k++)
    {
        if (a[k] < smallest && a[k] != smallest) // If string is smaller than current smallest string, set it as the new smallest string
                                                 // Make sure that string is not the same as current smallest string, otherwise position will change
        {
            smallestPosition = k;
            smallest = a[k];
        }
        
    }
    return smallestPosition;
}
// ******************************************************************************************************
// MOVE TO END

int moveToEnd(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos > n-1) // Pos must be a valid position in array
        return -1;
    string eliminate = a[pos]; // Record the string that will be eliminated/moved
    for (int k = pos; k < n ; k++) //All the strings after eliminate will be shifted to the left
    {
        a[k] = a[k+1];
    }
    a[n-1] = eliminate; // Put eliminated string at end
    return pos;
}

// ******************************************************************************************************
// MOVE TO BEGINNING

int moveToBeginning(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos > n-1) // Pos must be a valid position in array
        return -1;
    string eliminate = a[pos]; // Record the string that will be eliminated/moved
    for (int k = pos; k > 0 ; k--) //All the strings before eliminate will be shifted to the right
    {
        a[k] = a[k-1];
    }
    a[0] = eliminate; // Put eliminated string at beginning
    return pos;
}
// ******************************************************************************************************
// LOCATE DIFFERENCE

int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    for (int k = 0; k < n1 && k < n2; k++) // While position is valid in both arrays, check for first difference betweeen strings
    {
        if (a1[k] != a2[k])
            return k;
    }
    // No differences found.
    
   if (n1 < n2) // If n1 array is smaller than n2, return n1
       return n1;
   else if (n2 < n1) // If n2 array is smaller than n1, return n2
       return n2;
   else // If arrays are equal, return size of arrays
       return n1;
        
}

// ******************************************************************************************************
// ELIMINATE DUPS

int eliminateDups(string a[], int n)
{
    if (n < 0)
        return -1;
    int count = 0; //records number of unique (non-consecutive) items
    for (int k = 0; k < n; k++)
    {
        a[count] = a[k]; // puts unique items in original order
        count++; // Records encounter of a unique (non-consecutive) item
        int j = k + 1; //j checks the next position to see if next item is consecutive
        while (j < n)
        {
            if (a[k]==a[j]) // If the next item is consecutive, check the item after
                j++;
            else
                break;
        }
        k = j-1; // If items are consecutive, k moves to the last consecutive item
    }
    return count;
}

// ******************************************************************************************************
// SUBSEQUENCE

bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return false;
    int order = 0;
    for (int k = 0 ; k < n2 ; k++) // For every element of the little string
    {
        if (a2[k] == "") // Empty string is always a subsequence
            break;
        for (int j = order; j < n1; j++) //check if it matches one of the elements of the big string
        {
            if (a2[k] == a1[j])
            {
                order = j+1;
                break;
            }
            else if (j== n1-1 && a2[k] != a1[j]) //As soon as little string element does not match a big string element, return false
                return false;
        }
        
    }
    return true;
}

// ******************************************************************************************************
// MAKE MERGER

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    // Check for invalid arguments
    if (n1+n2 > max || n1 < 0 || n2 < 0 || max < 0)
        return -1;
    // Check that a1's elements are in nondecreasing order
    for (int k = 0; k < n1; k++)
    {
        if (a1[k] > a1[k+1] && k+1 < n1)
            return -1;
    }
    
    // Check that a2's elements are in nondecreasing order
    for (int j = 0; j < n2; j++)
    {
        if (a2[j] > a2[j+1] && j+1 < n2)
            return -1;
    }
    
    // Both strings have n elements in nondecreasing order.
    
    int a1Index = 0;
    int a2Index = 0;
    int resultIndex= 0; //Empty position where element from a1/a2 can be stored
    
    //Compare strings and add elements to result up until either array runs out
    
    for (; a1Index < n1 && a2Index < n2; resultIndex++)
    {
        if (a1[a1Index] < a2[a2Index]) //If element from a1 < a2, then place in result and shift index (+1)
        {
            result[resultIndex] = a1[a1Index];
            a1Index++;
        }
        else //If element from a1 >= a2, then place a2 element in result and shift index (+1)
        {
            result[resultIndex] = a2[a2Index];
            a2Index++;
        }
    }
    // One array has run out
    if (a1Index == n1) //If a2 is the longer string, add the rest of the elements to result
    {
        for (; a2Index < n2; resultIndex++)
        {
            result[resultIndex] = a2[a2Index];
            a2Index++;
        }
        
    }
    else if (a2Index == n2) //If a1 is the longer string, add the rest of the elements to result
    {
        for (; a1Index < n1; resultIndex++)
        {
            result[resultIndex] = a1[a1Index];
            a1Index++;
        }
    }
    
    return n1+n2;
    
}
// ******************************************************************************************************
// DIVIDE

int divide(string a[], int n, string divider)
{
    if (n<0)
        return -1;
    for (int k = 0; k < n; k++) //Check elements in relation to divider
    {
        
        if (a[k] < divider) // If element is less than divider, move to beginning of array
        {
            moveToBeginning(a, n, k);
            
        }
    }
    // Now all smaller items are in front. Organize back half (in case greater elements show up before divider)
    
    for (int i= 0; i < n; i++)
    {
        if (a[i] > divider) // If greater than or equal to divider, move to end of array
        {
            moveToEnd(a, n, i);
        }
        
    }
    
    // If element is equal to divider, then leave alone
    
    for (int j = 0; j < n; j++) //Find first element that is greater than divider
    {
        if (a[j] >= divider)
            return j;
    }
    return n; // If no elements are greater than divider return n
    
}

// ******************************************************************************************************

int main()
{
    //Enumerate
    string h[10] = {"Ashley" , "Brandon" , "Brandon", "Brandon" , "Catherine" , "David" , "Emily" , "Floyd" , "Gabriel" , "Gabriel"};
    assert (enumerate (h, 8, "Brandon") == 3);
    assert (enumerate (h, 5, "Catherine") == 1);
    assert (enumerate (h, 3, "Gabriel") == 0);
    assert (enumerate (h, 10, "Gabriel") == 2);
    assert (enumerate (h, 8, "") == 0);
    cout << "All tests succeeded for Enumerate" << endl;
    
    //locate
    string i[10] = {"Ashley" , "Brandon" , "Brandon", "Brandon" , "Catherine" , "David" , "Emily" , "Floyd" , "Gabriel" , "Gabriel"};
    assert (locate (i, 5, "Gabriel") == -1);
    assert (locate (i, 10, "Gabriel") == 8);
    assert (locate (i, 3, "Brandon") == 1);
    assert (locate (i, 10, "Janet") == -1);
    assert (locate (i, 8, "Catherine") == 4);
    assert (locate (i, 2, "Ashley") == 0);
    cout << "All tests succeeded for locate" << endl;
    
    //locateSequence
    string d[9] = {"jon", "daenerys", "samwell", "samwell", "margaery", "margaery", "margaery", "samwell", "samwell"};
    int b;
    int e;
    assert (locateSequence(d, 9, "samwell", b, e) == true);
    assert (locateSequence(d, 9, "daenerys", b, e) == true);
    assert (locateSequence(d, 9, "cersei", b, e) == false);
    assert (locateSequence(d, 5, "partridge", b, e) == false);
    b=0; e=0;
    string w[6] = {"apple", "orange", "banana", "banana", "grape", "pear"};
    assert (locateSequence(w, 6, "watermelon", b, e) == false && b==0 && e==0);
    b=0; e=0;
    assert (locateSequence(w, 6, "banana", b, e) == true && b==2 && e==3);
    cout << "All tests succeeded for locateSequence" << endl;
    
    //locationOfMin
    string people[5] = { "samwell" , "jon" , "margaery" , "daenerys", "tyrion"};
    assert (locationOfMin (people, 5) == 3);
    assert (locationOfMin (people, 3) == 1);
    assert (locationOfMin (people, 2) == 1);
    assert (locationOfMin (people, 0) == -1);
    cout << "All tests succeeded for locationofMin" << endl;
    
    //moveToEnd
    string names[5] = { "samwell", "jon", "margaery", "daenerys", "tyrion" };
    assert (moveToEnd (names, 3, 3) == -1 && names[0]=="samwell");
    cout << "All tests succeeded for moveToEnd" << endl;
    
    //moveToBeginning
    string group[5] = { "samwell", "jon", "margaery", "daenerys", "tyrion" };
    assert(moveToBeginning (group, 4, 4) == -1);
    cout << "All tests succeeded for moveToBeginning" << endl;
    
    //locateDifference
    string cast[5] = { "samwell", "jon", "margaery", "daenerys", "tyrion" };
    string roles[4] = { "samwell", "jon", "sansa", "jaime" };
    assert (locateDifference (cast, 5, roles, 4) == 2);
    assert (locateDifference (cast, 2, roles, 1) == 1);
    assert (locateDifference (cast, 0, roles, 3) == 0);
    cout << "All tests succeeded for locateDifference" << endl;
    
    //eliminateDups
    string k[9] = {"jon", "daenerys", "samwell", "samwell", "margaery", "margaery", "margaery", "samwell", "samwell"};
    assert (eliminateDups (k, 9) == 5);
    int m = eliminateDups (k, 9);
    cout << m << endl;
    cout << k[0] << endl;
    cout << k[1] << endl;
    cout << k[2] << endl;
    cout << k[3] << endl;
    cout << k[4] << endl;
    cout << k[5] << endl;
    cout << k[6] << endl;
    cout << k[7] << endl;
    cout << "All tests succeeded for eliminateDups" << endl;
    
    //subsequence
    string big[10] = { "samwell", "jon", "margaery", "daenerys", "tyrion", "margaery" };
    string little1[10] = { "jon", "daenerys", "tyrion" };
    assert (subsequence (big, 6, little1, 3) == true);
    string little2[10] = { "margaery", "jon" };
    assert (subsequence (big, 6, little2, 2) == false);
    string little3[10] = { "jon", "margaery", "margaery" };
    assert (subsequence (big, 6, little3, 3) == true);
    string little4[10] = { "jon", "jon", "margaery" };
    assert (subsequence(big, 6, little4, 3) == false);
    cout << "All tests succeeded for subsequence" << endl;
    
    //makeMerger
    string x[5] = { "cersei", "jon", "margaery", "samwell", "sansa" };
    string y[4] = { "daenerys", "jon", "jon", "tyrion" };
    string z[20];
    cout << makeMerger(x, 4, y, 2, z, 8) << endl;
    cout << z[0] << endl;
    cout << z[1] << endl;
    cout << z[2] << endl;
    cout << z[3] << endl;
    cout << z[4] << endl;
    cout << z[5] << endl;
    cout << z[6] << endl;
    cout << z[7] << endl;
    cout << z[8] << endl;
    cout << "All tests succeeded for makeMerger" << endl;
    
    //divide
    string f[6] = { "cersei", "margaery", "sansa", "daenerys", "tyrion", "jon" };
    cout << divide (f, 6, "samwell") << endl;
    cout << f[0] << endl;
    cout << f[1] << endl;
    cout << f[2] << endl;
    cout << f[3] << endl;
    cout << f[4] << endl;
    cout << f[5] << endl;
    string g[4] = { "samwell", "margaery", "tyrion", "jon" };
    cout << divide(g, 4, "margaery") << endl;
    cout << g[0] << endl;
    cout << g[1] << endl;
    cout << g[2] << endl;
    cout << g[3] << endl;
    string a[6] = {"apple", "orange", "banana", "banana", "grape", "pear"};
    cout << divide (a, 5, "carrots") << endl;
    cout << a[0] << endl;
    cout << a[1] << endl;
    cout << a[2] << endl;
    cout << a[3] << endl;
    cout << a[4] << endl;
    string q[6] = {"apple", "orange", "banana", "banana", "grape", "pear"};
    cout << divide(q, 6, "banana") << endl;
    cout << q[0] << endl;
    cout << q[1] << endl;
    cout << q[2] << endl;
    cout << q[3] << endl;
    cout << q[4] << endl;
    cout << q[5] << endl;


}



    