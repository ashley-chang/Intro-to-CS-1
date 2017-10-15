// Project 3 - 4/29/2015
// Ashley Chang
// 504449890

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isTuneWellFormed (string tune);
int translateTune (string tune, string& instructions, int& badBeat);
bool isValidColor (char color);
int charToInt (char a);
int findBeat (string tune, int start, int stop);

int main(){
    string myTune;
    cout << "Enter a string: " << endl;
    getline (cin, myTune);
    
    string instructions = "?????";
    int badBeat = -888;
    int valid = translateTune (myTune, instructions, badBeat);
    cout << valid << endl;
    cout << instructions << endl;
    cout << badBeat << endl;
    
    
}

bool isValidColor (char color)      // Check to see if letter specifies a valid color
{
    switch (color) {
        case 'G':
        case 'g':
        case 'R':
        case 'r':
        case 'Y':
        case 'y':
        case 'B':
        case 'b':
        case 'O':
        case 'o':
            return true;
            break;
        default:
            return false;
    }
}


bool isTuneWellFormed (string tune)
{
    int k=0;
    if (k == 0 && k == tune.size())             // If the tune is empty, then well formed
        return true;
    
    while (k != tune.size())                    // If string has substance, observe all the characters in the string
    {
        if (tune[k] == '/')                     // If a single slash, then marks one beat
        {
            k++;
        }
        else if (isValidColor (tune[k]))        // If not a slash, check to see if valid color
        {
            if (tune[k+1] != '/')               // Color needs to be followed by at least one slash to indicate one full beat
                return false;
        
            k++;
        }
        
        else if (isdigit (tune[k]))              // If not a slash or color, check to see if digit
        {
            if (isdigit (tune[k+1]) && !isdigit(tune [k+2])) // Check to see if (at most) 2 digit number
            {
                k++;
              
            }
            
            else if (!isValidColor (tune[k+1])) // If two digits and next character is not a valid color letter, then not well-formed
            {
                return false;
            }
            else
                k++;                            // Advance k if 1 digit number
            
        }
        else
            return false;                       // If character at spot is anything except slash/letter/digit, then not well-formed
    }
    return true;                                // Pass all error checks, so tune is well formed
}



int charToInt (char a)                          // Convert characters to integers
{
    return (a - '0');
}

int findBeat (string tune, int start, int stop) // Count number of beats (slashes) up to a certain point
{
    int k = 0;
    for (int i = start; i <= stop; i++)
    {
        if (tune[i] == '/')
            k++;
    }
    return k;
}



int translateTune(string tune, string& instructions, int& badBeat)
{
    // Check to see if dealing with well-formed tune
    if (!isTuneWellFormed (tune))
        return 1;
    
    // Continue if tune is well formed
    
    int k = 0;
    while (k != tune.size())
    {
        // *********************************************************************************
        // STAGE 1: FIND ANY BEAT ERRORS
        // *********************************************************************************
        if (isdigit(tune[k]))
        {
            // *********************************************************************************
            // Check if sustained note < 2
            // *********************************************************************************
            if (isdigit (tune[k+1])) // Check if two digit number
            {
                int num = (10 * charToInt(tune[k])) + charToInt(tune[k+1]);
                if (num < 2)                            // Check if number < 2
                {
                    badBeat = findBeat(tune, 0, k+3);   // Find beat where faulty sustained note occurs
                    return 2;
                }
            }
            else if (charToInt(tune[k]) < 2)        // Check if (one digit) number < 2
            {
                badBeat = findBeat (tune, 0, k+2);  // Find beat where faulty sustained note occurs
                return 2;
            }
            // Sustained note (indicated digit) should now be at least 2.
            // **********************************************************************************
            // Check if sustained note has appropriate beats/slashes
            // **********************************************************************************
            if (!isdigit(tune[k+1]))                                    // Check if one digit number
            {
                int properLength = charToInt(tune[k]);                  // Record how many beats (slashes) are specified
                string checkLength = tune.substr((k+2), properLength);  // Observe area where beats (slashes) should occur in tune
                for (int j = 0; j != checkLength.size(); j++)           // Check to see that slashes match number of beats specified
                {
                    if (checkLength[j] != '/')
                    {
                        int mismatchedBeat = (k + 2) + j;               // Stop and record where bad beat occurs (note is interrupted)
                        badBeat = findBeat (tune, 0, mismatchedBeat) + 1;
                        return 3;
                    }
                }
                
            }
            else if (isdigit(tune[k+1]))                                            // Check if two digit number
            {
                int properLength = 10*charToInt(tune[k]) + charToInt (tune[k+1]);   // Record how many beats (slashes) are specified
                string checkLength = tune.substr((k+3), properLength);              // Observe area where beats (slashes) should occur in tune
                for (int j = 0; j != checkLength.size(); j++)                       // Check to see that slashes match number of beats specified
                {
                    if (checkLength[j] != '/')
                    {
                        int mismatchedBeat = (k + 3) + j;                           // Stop and record where bad beat occurs (note is interrupted)
                        badBeat = findBeat(tune, 0, mismatchedBeat) + 1;
                        return 3;
                    }
                }
            }
            // Length of note and slashes should now match up.
            // *********************************************************************************
            // Check if tune ends prematurely
            // *********************************************************************************
            if (!isdigit(tune[k+1]))                                        // Check if one digit number
            {
                int properLength = charToInt(tune[k]);                      // Record how long note should last
                string checkLength =  tune.substr((k+2), properLength);     // Observe area where beats should occur
                if (checkLength.size() != properLength)                     // Check if enough beats. If not,
                {
                    int goodBeats = findBeat (tune, 0, k);                  // Record placement of prematurely-ending note
                    int endsPrematurely = 0;
                    for (int m = k+1; m != tune.size(); m++)                // Record how many good beats do exist if not enough
                    {
                        if (tune[m] == '/')
                            endsPrematurely++;
                    }
                    
                    badBeat = goodBeats + endsPrematurely + 1;              // Bad beat occurs where end of tune is missing a beat (premature ending)
                    return 4;
                }
            }
            else if (isdigit(tune[k+1]))                                            // Check if two digit number
            {
                int properLength = 10*charToInt(tune[k]) + charToInt(tune[k+1]);    // Record how long note should last
                string checkLength = tune.substr((k+3),properLength);               // Observe area where slashes should occur
                if (checkLength.size() != properLength)                             // Check if enough beats. If not,
                {
                    int goodBeats = findBeat (tune, 0, k+1);                        // Record placement of prematurely-ending note
                    int endsPrematurely = 0;
                    for (int m = k+2; m != tune.size(); m++)                        // Record how many good beats do exist if not enough
                    {
                        if (tune[m] == '/')
                            endsPrematurely++;
                    }
                    
                    badBeat = goodBeats + endsPrematurely + 1;                      // Bad beat occurs where end of tune is missing a beat (premature ending)
                    return 4;
                }
            }
            
        }
        k++;
    }
        // Tune should be well-formed. Notes are full-length with the appropriate number of slashes.
    
        // Prepare instructions string for translation
    k = 0;
    instructions = "";
    while (k != tune.size())
    {
        
        // **************************************************************************************
        // STAGE 2: BEGIN TRANSLATION
        // **************************************************************************************
        if (isdigit (tune[k]))
        {
            if (!isdigit(tune[k+1]))                        // For single digit sustained notes
            {
                int sustain = charToInt(tune[k]);           // Record how many beats note should last
                for (int j = 0; j < sustain; j++)           // Add appropriate number of notes to instructions (in color specified)
                    instructions += toupper(tune[k+1]);
                k += sustain + 1;                           // Move position in tune to end of sustained note
            }
            
            else if (isdigit (tune[k+1]))                                       // For double digit sustained notes
            {
                int sustain = 10*charToInt(tune[k]) + charToInt(tune[k+1]);     // Record how many beats note should last
                for (int j = 0; j < sustain; j++)                               // Add appropriate number of notes to instructions (in color specified)
                    instructions += toupper(tune[k+1]);
                k += sustain + 2;                                               // Move position in tune to end of sustained note
            }
        }
        
        else if (isalpha(tune[k]))                          // For non-sustained, stand-alone notes (single color, single slash)
        {
            if (tune[k+2] != '/' || !isdigit(tune[k-1]))    // Add single note to instructions (in color specified)
            {
                instructions += tolower(tune[k]);
                k++;                                        // Move position in tune to end of single note
            }
        }
        else if (tune[k] == '/')            // For non-sustained beats consisting of only a slash
        {
            instructions += 'x';            // Add beat to instructions (no color specified)
        }
        
        k++;                                // Finish translation for one sustained/non-sustained note. Move to next new note
        
    } // end of while statement
    return 0;                               // TRANSLATION SUCCESSFUL! Bad beat remains unchanged.
}



