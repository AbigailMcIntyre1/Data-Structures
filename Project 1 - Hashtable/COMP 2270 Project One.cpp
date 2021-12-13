// Abigail McIntyre
// Project One
// Data Structures - Fall 2021
// Due 09/01/2021

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

const int TABLESIZE = 19;
const int NAMESIZE = 40;

struct Table
{
    char name[41];                              // holds the name of the person whose information is being stored
    int key;                                    // holds the key entered by the user

    // default constructor
    Table()
    {
        // initialize the variables to -1 to symbolize that they're empty
        strcpy(name, "");
        key = -1;
    }

}; 


// -------- function Prototypes ---------------------------------------------------------------------------

int linearProbingInsertion(int key, Table hashTable[]);                         // linear probing function to insert
void linearProbingDeletion(int key, Table hashTable[]);                         // linear probing function to delete
void displayTable(int index, int key, int numNameChars, Table hashTable[]);     // displays the hash table

// ---------------------------------------------------------------------------------------------------------


int main()
{
    int probingAnswer;                      // holds the answer to if the user wants linear, quadratic, or double-hashing
    int key;                                // holds a three-digit integer key
    int index;                              // holds the home address (hashed key) where the key and data will be stored in the table
    int numNameChars;                       // holds the number of characters in the entered name
    char nameAnswer[NAMESIZE];              // a variable used to store the answer until a location in the structure is found
    string answer = "yes";                  // holds if the user wants to continue the program or not
    string answer2;

    // create an array of structures for the hash table
    Table hashTable[TABLESIZE];

    // while the user still wants to input or delete data
    while (answer == "yes" || answer == "Yes")
    {
        cout << "This program puts inputted data into a hash table" << endl << endl;

        cout << "Would you like to add, search, or delete? ";
        cin >> answer2;

        while (answer2 == "add" || answer2 == "Add" || answer2 == "yes" || answer2 == "Yes")
        {
            // ask for the name to be inserted into the table
            cout << "Please enter a name: ";
            cin.ignore();
            cin.getline(nameAnswer, NAMESIZE + 1);                   // get the name to be inserted into the table; no more than 40 characters

            // count the number of characters in the entered name
            int j = 0;

            while (nameAnswer[j] != NULL)
                j++;

            numNameChars = j;

            // ask for the key
            cout << "Please enter a key: ";
            cin >> key;

            // if the key is less than 000 or greater than 999 then it throws an error and the user has to reenter it
            while (key < 000 || key > 999)
            {
                cout << "Error, invalid key" << endl;
                cin >> key;
            }

            // use linear probing to find the index
            index = linearProbingInsertion(key, hashTable);

            // set the key in the structure to the key entered by the user
            hashTable[index].key = key;

            // set the name in the structure to the name entered by the user
            for (int h = 0; h < numNameChars; h++)
            {
                hashTable[index].name[h] = nameAnswer[h];
            }

            // display the table
            displayTable(index, key, numNameChars, hashTable);

            // ask if the user would like to continue the program
            cout << endl << "Would you like to continue adding names? ";
            cin >> answer2;

            if (answer2 == "no" || answer2 == "No")
            {
                cout << endl << endl << "Would you like to continue the program? ";
                cin >> answer;
            }
            cout << endl << endl << "------------------------------------------------------------------" << endl << endl;
        }

        while (answer2 == "delete" || "Delete")
        {
            cout << "What key would you like to delete? ";
            cin >> key;

           // linearProbingDeletion(key, hashTable);

            // display the table
            displayTable(index, key, numNameChars, hashTable);

            // ask if the user would like to continue the program
            cout << endl << "Would you like to continue deleting names? ";
            cin >> answer2;

            if (answer2 == "no" || answer2 == "No")
            {
                cout << endl << endl << "Would you like to continue the program? ";
                cin >> answer;
            }
            cout << endl << endl << "------------------------------------------------------------------" << endl << endl;
        }


    } // end while


} // end main

// ---------- Functions ---------------------------------------------------------------------------------------------------------------------

// returns the index 
int hashFunction(int key)
{
    return key % TABLESIZE;

} 

// linear probing:
// if the home address is already occupied, move forward through the table and store the key and data in the first "free" location you encounter
int linearProbingInsertion(int key, Table hashTable[])
{
    // use the hash function to get the index
    int hashIndex = hashFunction(key);

    // find an index that isn't taken
    while (hashTable[hashIndex].key != -1)
    {
        hashIndex++;
       // hashIndex %= TABLESIZE;
    }

    return hashIndex;

} 

/*
// linear probing for deletion
void linearProbingDeletion(int key, Table hashTable[])
{
    // use the hash function to get the index
    int hashIndex = hashFunction(key);

    while (hashTable[hashIndex].key != -1)
    {
        // if it's been found
        if (hashTable[hashIndex].key == key)
        {
            for (int x = 0; x < NAMESIZE; x++)
                hashTable[hashIndex].name[x] = '_';
            hashTable[hashIndex].key = -1;
        }

        hashIndex++;
    }
}
*/

// displays the table - does not work well
void displayTable(int index, int key, int numNameChars, Table hashTable[])
{
    cout << endl << "Index       Key        Name" << endl;
    cout << "----------------------------" << endl;


    /*
    for (int i = 0; i < TABLESIZE; i++)
    {
        cout << i << "           " << hashTable[i].key << "           ";

        for (int j = 0; j < numNameChars; j++)
        {
            cout << hashTable[i].name[j];
        }

        cout << endl;
    }
    */
    int j = 0;

    // very very messed up
    for (int i = 0; i < TABLESIZE; i++)
    {
        cout << setw(12) << left << i << setw(13) << left << hashTable[i].key;

        while (j < numNameChars && hashTable[i].name[j] != '_')
        {
            cout << hashTable[i].name[j];
            j++;
        }

        cout << endl;
    }

} 


