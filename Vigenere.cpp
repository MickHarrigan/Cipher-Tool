#include "Vigenere.h"

Vigenere::Vigenere(){
    SetMessage("test");
    m_key = "test";

} // end of default constructor

Vigenere::Vigenere(string message, bool isEncrypted, string key){
    SetMessage(message);
    m_key = key;
    // if it is in the wrong encryption state, alters it to fit
    // in the end this may be overkill and not necessary
    if (GetIsEncrypted() != isEncrypted){
        ToggleEncrypted();

    } // end of if statement

} // end of overloaded constructor

Vigenere::~Vigenere(){
    SetMessage("");
    ToggleEncrypted();
    m_key = "test";

} // end of destructor

void Vigenere::Encrypt(){
    string message = GetMessage(); // sets the mesage to a variable to be manipulated
    string fixedKey = ""; // the key that is used to compare to the message
    string output = ""; // what will ultimately be output from this function
    int length = message.length(); // variable for iterating across the length of the initial message
    int index = 0; // used to add the correct letter from the key to the fixedKey
    char temp; // used for each character in the message for alteration into the output

    // make the lenths of the key and the message the same

    for (int i = 0; i < length; i++){
        // if the char is an upper case letter
        if ((message.at(i) >= 'A') and (message.at(i) <= 'Z')){
            fixedKey += m_key.at(index);
            index++;

        } // end of if statement

        // if the char is a lower case letter
        else if ((message.at(i) >= 'a') and (message.at(i) <= 'z')){
            fixedKey += m_key.at(index);
            index++;

        } // end of if statement

        else{
            // arbitrary char for replacing later
            fixedKey += IGNORE;

        } // end of else statement

        // if the index is about to go out of bounds, sets it back to zero to repeat through the key
        if (index > int(m_key.length() - 1)){
            index = 0;

        } // end of if statement

    } // end of for loop

    // at this point the fixedKey and the message should be the same length, where the encryption itself can now occur

    for (int i = 0; i < length; i++){
        // if the blocker char is present, ignores changes, places char into temp
        if (fixedKey.at(i) == IGNORE){
            temp = message.at(i);

        } // end of if statement

        // if the letter is a capital letter, places a capital letter in the temp for the output
        else if ((message.at(i) >= 'A') and (message.at(i) <= 'Z')){
            temp = 'A';
            // moves the fixedKey back a letters since they have only been lower case
            temp += (message.at(i) - 'A' + fixedKey.at(i) - 'a') % ALPHABET_LENGTH;

        } // end of if statement

        // if the letter is a lower case, places a lower case in the temp for the output
        else if ((message.at(i) >= 'a') and (message.at(i) <= 'z')){
            temp = 'a';
            // given that both messaage.at(i) and fixedKey will be lowercase, both the lowercase a's are used
            temp += (message.at(i) - 'a' + fixedKey.at(i) - 'a') % ALPHABET_LENGTH;

        } // end of else if statement

        // appends the temp to the output
        output += temp;
        
    } // end of for loop

    // sets the message to that of the output
    SetMessage(output);

    // changes the encrypted state
    ToggleEncrypted();

} // end of Encrypt

void Vigenere::Decrypt(){
    string message = GetMessage(); // sets the mesage to a variable to be manipulated
    string fixedKey = ""; // the key that is used to compare to the message
    string output = ""; // what will ultimately be output from this function
    int length = message.length(); // variable for iterating across the length of the initial message
    int index = 0; // used to add the correct letter from the key to the fixedKey
    char temp; // used for each character in the message for alteration into the output


    /* EXACT SAME CODE AS ENCRYPT */

    // make the lenths of the key and the message the same

    for (int i = 0; i < length; i++){
        // if the char is an upper case letter
        if ((message.at(i) >= 'A') and (message.at(i) <= 'Z')){
            fixedKey += m_key.at(index);
            index++;

        } // end of if statement

        // if the char is a lower case letter
        else if ((message.at(i) >= 'a') and (message.at(i) <= 'z')){
            fixedKey += m_key.at(index);
            index++;

        } // end of if statement

        else{
            // arbitrary char for replacing later
            fixedKey += IGNORE;

        } // end of else statement

        // if the index is about to go out of bounds, sets it back to zero to repeat through the key
        if (index > int(m_key.length() - 1)){
            index = 0;

        } // end of if statement

    } // end of for loop

    // at this point the fixedKey and the message should be the same length, where the encryption itself can now occur

    for (int i = 0; i < length; i++){
        // if the blocker char is present, ignores changes, places char into temp
        if (fixedKey.at(i) == IGNORE){
            temp = message.at(i);

        } // end of if statement

        // if the letter is a capital letter, places a capital letter in the temp for the output
        else if ((message.at(i) >= 'A') and (message.at(i) <= 'Z')){
            temp = 'A';
            temp += ((message.at(i) - 'A') - (fixedKey.at(i) - 'a') + ALPHABET_LENGTH) % ALPHABET_LENGTH;

        } // end of if statement

        // if the letter is a lower case, places a lower case in the temp for the output
        else if ((message.at(i) >= 'a') and (message.at(i) <= 'z')){
            temp = 'a';
            temp += ((message.at(i) - 'a') - (fixedKey.at(i) - 'a') + ALPHABET_LENGTH) % ALPHABET_LENGTH;

        } // end of if statement

        // appends the temp to the output
        output += temp;
        
    } // end of for loop

    // sets the message to that of the output
    SetMessage(output);

    // changes the encrypted state
    ToggleEncrypted();

} // end of Decrypt

string Vigenere::ToString(){
    return VIGENERE;

} // end of ToString

string Vigenere::FormatOutput(){
    stringstream output; // stringstream object to return in the specified format
    string message = GetMessage(); // the message to format

    // modifies the stringstream object with cipher type, encryption type, message, and key, with delimeters between
    output << "v" << "|" << GetIsEncrypted() << "|" << message << "|" << m_key;

    // returns the stringstream object as a string 
    return output.str();

} // end of FormatOutput