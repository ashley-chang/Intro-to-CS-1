//
//  main.cpp
//  Project5
//
//  Created by Ashley Chang on 5/13/15.
//  Copyright (c) 2015 Ashley Chang. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>

using namespace std;
const int MAXCRIBLENGTH = 81; //including zero byte
const int CIPHERMESSAGELENGTH = 81;
const int NUMBEROFMESSAGES = 51;

//*********************************************
//Function to count number of words in one message (row)

int countWordsInMessage (char separateMessages_[][81], int rowNumberB)
{
    int pos;
    int wordCount=0;
    
    for (pos=0; separateMessages_[rowNumberB][pos] != '\0'; pos++) //For every character
    {
        
        if (isspace(separateMessages_[rowNumberB][pos]) && (isalpha(separateMessages_[rowNumberB][pos+1]) || separateMessages_[rowNumberB][pos+1] == '\0'))
        {
            wordCount++;
        }
        else if (separateMessages_[rowNumberB][pos+1] == '\0')
        {
            wordCount++;
        }
        
    }
    return wordCount;
    
}
//*********************************************

//*********************************************
//Function to clear key
void clearKey (char key[])
{
    for (int k=0; k<26; k++)
        key[k] = '\0';
}

//*********************************************

bool decrypt(const char ciphertext[], const char crib[])
{
    if (strlen(crib) > MAXCRIBLENGTH)
        return false;
    int notValid = 0;
    for (int k = 0; k < strlen(crib); k++)
    {
        if (isalpha(crib[k]))
            notValid++;
    }
    if (notValid == 0)
        return false;
   // cerr << crib << endl; //*********************************
    //cerr << crib [2] << endl;
    
    //***********************************************************************************************
    //GOAL: Create a new array to store the cipher text
    char separateMessages[NUMBEROFMESSAGES][CIPHERMESSAGELENGTH];

    int counter = 0; //Marks how many messages in cipher
    
    int j=0; // Marks placement in ciphertext
    int i;
    
    for(i = 0; i < strlen(ciphertext)+1; i++)
    {
        if(ciphertext[i]=='\n' || (ciphertext[i] == '\0' && ciphertext[i-1] != '\n'))
            counter++;
    }
    
    //cerr<<"counter:"<<counter<<endl;
    
    for (i=0; i <= counter; i++) //Marks row of 2d array; one row for each message
                                 //can have up to 50 new lines, last line doesn't need \n
    {
        int k;
        for (k=0; k != CIPHERMESSAGELENGTH && ciphertext[j] != '\n' && ciphertext[j] != '\0'; k++)
            //Marks columns of 2d array; length of a message
        {
            separateMessages[i][k] = ciphertext[j];
            j++;
        }
        //done storing 1 word from the ciphertext
        separateMessages[i][k]='\0';
        
        j++;
    }
    //COMPLETED: separated cipher into messages in a new 2D array.
    //***********************************************************************************************
    //GOAL: For every row of the separatedMessages (cipher), remove all nonalphabetic characters.
    
    //WILL BE MULTIPLE SPACES!!!
    
    for (int x=0; x <= counter; x++)
    {
        for (int y=0; separateMessages[x][y]!= '\0'; y++)
        {
            if (!isalpha(separateMessages[x][y]))
                separateMessages[x][y] = ' ';
        }
    }
    //COMPLETED: Messages are words and spaces only.
    //***********************************************************************************************
    //GOAL: Separate cipher messages into words (own arrays)
    
    //Make a 3D array
    char splitMessageWords[counter][CIPHERMESSAGELENGTH][CIPHERMESSAGELENGTH]; //[][81][81]
    
    //use separateMessages array: one message per row
    int r;
    int s;
    int t;
    int u;
    
    for (r=0; r <= counter; r++) //Examine one row of separateMessages (r for NUMBEROFMESSAGES),
    {
        t=0; // new word (row)
        u=0;
        
        for (s=0; separateMessages[r][s] != '\0'; s++) //For every character
        {
            
            if (isalpha(separateMessages[r][s])) //If alphabetic character in message, then append that character to row of new array
            {
                //r is message
                //t is word (row)
                //u is letter (column)
                splitMessageWords[r][t][u] = separateMessages[r][s];
                u++;
            }
            else if (isspace(separateMessages[r][s])&& (isalpha(separateMessages[r][s+1]) || separateMessages[r][s+1] == '\0'))
            {
                //set to zero byte and start a new row
                splitMessageWords[r][t][u] ='\0';
                t++;
                u=0;
            }
            
        }
    }
    
    
    //***********************************************************************************************
    //GOAL: Clean the crib so that there are no non-alphabetic characters, and only one space in between each word.
    
    //Create a new array for the clean crib
    char cleanupCrib [MAXCRIBLENGTH]; //currently empty
    int a;
    int newCleanedPos = 0;
    //cleanupCrib [0] = 'b';
    //cerr<< cleanupCrib[0];
    for (a=0; crib[a] != '\0'; a++) //Go through the crib until hit zero byte
    {
        if (isalpha(crib[a])) //If the indicated character is an alphabetic letter
        {
            cleanupCrib[newCleanedPos] = crib[a]; //Put it in a position in the new array (cleanupCrib)
            newCleanedPos++; //Prep the next position in the array for recording of next letter
        }
        else if (!isalpha(crib[a]) && isalpha(crib[a+1])) // If indicated character is not an alphabetic letter but the next letter is
        {
            cleanupCrib [newCleanedPos] = ' '; //Add a space to the new array
            newCleanedPos++; //Prep the next position in the array for recording of next letter
        }
        
        //Otherwise,
        //If the indicated character is not an alphabetic letter and the next letter isn't either, keep incrementing position in crib until
            // a) a marks the position of an alphabetic character
            // b) a marks the position of the last non-alphabetic character
                    // add a space only for last non-alphabetic character so that there is only one space between words
    }
    //When hit zero byte in crib, then stop forming cleanedCrib in new array
    cleanupCrib[newCleanedPos] = '\0';
    
    //for (int m=0; cleanupCrib[m] != '\0'; m++)
      //  cerr << cleanupCrib[m];
    //cerr<<endl;
    
    //COMPLETED: Cleaned crib so that only words separated by single spaces.
    //***********************************************************************************************
    
    //GOAL: Create a new array to store the crib, and separate the words in the crib so you can count and match
    
    //Count individual words in crib
    int countCrib=0;
    for (int p = 0; p < strlen(cleanupCrib)+1; p++)
    {
        if (cleanupCrib[p] == ' ' || cleanupCrib[p] == '\0')
            countCrib++;
    }
    
    //cerr << "countCrib: " << countCrib << endl;
    
    //Create 2D array
        //Rows: Individual words in crib (countcrib)
        //Columns: can't be longer than 80 characters not including zero byte (i.e. can't be > 81)
    
    char recordCrib[countCrib][MAXCRIBLENGTH]; //Want to separate each word in crib--each word in a row
    int v = 0; //Marks position in (cleaned) crib
    int q;
    int w;
    for (q= 0; q != countCrib; q++)
    {
        for (w=0; w != MAXCRIBLENGTH && cleanupCrib[v] != ' ' && cleanupCrib[v] != '\0'; w++) //Spell out word until hit space, then new row for new word
        {
            recordCrib[q][w]= cleanupCrib[v]; //Putting characters into array
            v++;                       //increment position in (cleaned) crib
        }
        //reach a space, so move on to next row
        v++; //increment position in crib so that you pass the space
        
        recordCrib[q][w] = '\0';
        
    }
    
    //***********************************************************************************************
    
    //***********************************************************************************************
    //MATCHING CRIB TO CIPHERTEXT
    //using: splitMessageWord[][][] & recordCrib [][]
    
    int b=0;
    char key[26];
    //Clear key
    clearKey (key);
    int foundMatch=0;
    int possible = 0;
    
    while (countWordsInMessage(separateMessages, b) < countCrib && b < counter)
    {
        b++;
        if (countWordsInMessage(separateMessages,b)>=countCrib)
            break;
    }
    while (countWordsInMessage (separateMessages, b) >= countCrib && b < counter) //Use this message only if there are enough words to fit Crib
    {

        //Start from first word in message.
        int msgCursor=0;
        while (msgCursor+countCrib <= countWordsInMessage(separateMessages,b) && foundMatch ==0) //While there is enough space for crib in message

        {
            if (strlen(splitMessageWords[b][msgCursor]) == strlen(recordCrib[0])) //Length of word in message is the same length as crib word!! Potential match
            {
                int saveCursor = msgCursor;
                possible = 1; //Possible Match
                while (possible == 1 && msgCursor < (msgCursor+countCrib-1)) //While possible match, go through the next (# of crib-1) words
                {
                    int continueCribComparison = 0;
                    if (strlen(splitMessageWords[b][msgCursor]) != strlen(recordCrib[continueCribComparison]))
                    {
                        msgCursor = saveCursor+1;
                        possible = 0; //breaks out of loop back to outer while loop
                    }
                    msgCursor++;
                    continueCribComparison++;
                }
                //**********************************************************************
                //Got through length check
                int go;
                clearKey(key);
                int goBack = saveCursor;
                possible = 1;
                int cribNum=0;
                for (int track = saveCursor; track <= (goBack+(countCrib-1)) && possible ==1; track++) //Track from a certain position in the message
                {
                    for (go=0; splitMessageWords[b][track][go] != '\0' && possible == 1; go++) //For each of the letters in the indicated msg word
                    {
                        int convert = tolower(splitMessageWords[b][track][go])-'a'; //Assign an integer value for the specified character
                        if (key[convert] == '\0')
                        {
                            for (int checkKey=0; checkKey<26; checkKey++) //Make sure the crib values are consistent and not already used
                            {
                                if (key[checkKey] == toupper(recordCrib[cribNum][go]))
                                    possible=0; //If a crib character was used for another msg character, exit loop
                            }
                            if (possible==0)
                                break;
                            key[convert] = toupper(recordCrib[cribNum][go]);
                        }
                        else if (isalpha(key[convert]) && toupper(key[convert]) != toupper(recordCrib[cribNum][go])) //Exit if not one-to-one
                        {
                            msgCursor = goBack;
                            possible = 0;
                            clearKey(key);
                        }
                        
                    }
                    if (cribNum == countCrib-1)
                        foundMatch = 1;
                    cribNum++;
                }
            }
            else
            {
                msgCursor++;
            }
            
            
            if (msgCursor == countWordsInMessage(separateMessages,b)-1 && foundMatch == 0)
            {
                b++;
                msgCursor = 0;
            }
    
        }
        b++;
    }
    

    
    //*******************************************************************************************************
    
    //Go through the cipher text and translate according to key
    char decipherment[NUMBEROFMESSAGES][CIPHERMESSAGELENGTH]; //Array to print out translation
    
    int translateLetter;
    int cipherPos=0; //Marks every letter in the cipher
    for (int g=0; g < counter; g++) //For every message of the cipher
    {
        for (translateLetter=0; ciphertext[cipherPos] != '\0'; translateLetter++) //Go through every letter
        {
            if (!isalpha(ciphertext[cipherPos])) //If the cipher letter is a nonalphabetic letter
                decipherment[g][translateLetter] = ciphertext[cipherPos]; //Store the same character in the array
            else //should be an alphabetic character
            {
                int decryption = tolower(ciphertext[cipherPos])-'a'; //key box that stores the crib letter
                if (key[decryption] == '\0')
                {
                    decipherment[g][translateLetter] = tolower(ciphertext[cipherPos]);
                }
                else
                {
                    decipherment[g][translateLetter] = toupper(key[decryption]);
                }
            }
            
            cipherPos++;
        }// end for loop
        decipherment[g][translateLetter] = '\0';
    }
    
    
    if (possible == 1) //If there was a match, then print
    {
    for (int decipherrow=0; decipherrow < counter; decipherrow++)
    {
        int print;
        for (print=0; decipherment[decipherrow][print] != '\0'; print++)
            cout << decipherment[decipherrow][print];
    
           
    }
    }
    
    if (possible ==0)
        return false;
    return true;
        
}


//If didn't get through all words of crib, clear key
int main()
    {
        cout << decrypt("Tftdn lxwdqkoft lhgzztr of Ltezgk zvtfzn-ltctf. \nO ziofa zit Zktqlxkt gy Doeiossofrq ol wxkotr lgdtvitkt of dn wqeanqkr.\nRor ngx itqk ziqz Sgktzzq ol ugofu gxz vozi Dqkexl?\nel 31 ol eiqsstfuofu!\n" , "treasure of michillinda");
    }
