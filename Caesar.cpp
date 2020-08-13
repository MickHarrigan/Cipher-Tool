#include "Caesar.h"

Caesar::Caesar(){
    SetMessage("test");
    m_shift = 3;

} // end of default constructor

Caesar::Caesar(string message, bool isEncrypted, int shift){
    SetMessage(message);
    cout << "kekeroni" << endl;
    m_shift = shift;
    // if it is in the wrong encryption state, alters it to fit
    // in the end this may be overkill and not necessary
    if (GetIsEncrypted() != isEncrypted){
        ToggleEncrypted();

    } // end of if statement

} // end of overloaded constructor

Caesar::~Caesar(){
    SetMessage("");
    ToggleEncrypted();
    // takes the negative of the current shift
    // this may be ultimately unnecessary
    m_shift = (0 - m_shift);

} // end of destructor

void Caesar::Encrypt(){
    string message = GetMessage(); // sets the mesage to a variable to be manipulated
    string output = ""; // what will ultimately be output from this function
    int length = message.length(); // variable for iterating across the length of the initial message
    int shift = m_shift % 26; // sets the shift within the bounds of the alphabet
    char temp; // used for each character in the message for alteration into the output

    for (int i = 0; i < length; i++){
        
        // arbitrarily sets the temp to the char, then goes through the checking process
        temp = message.at(i);
        
        // if the char is an upper case letter
        if ((message.at(i) >= 'A') and (message.at(i) <= 'Z')){

            // if the shift is positive
            if (shift > 0){
                // if the new char goes out of range of letters, sets it back into the range
                if (message.at(i) + shift > 'Z'){
                    temp = (message.at(i) + shift - ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continue as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else
            
            } // end of if statement

            // if the shift is negative
            else{
                // if the new char goes below the range of letters, sets it back into the range
                if (message.at(i) + shift < 'A'){
                    temp = (message.at(i) + shift + ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continues as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else statement

            } // end of else statement

        } // end of if statement

        // if the letter is a lower case, places a lower case in the temp for the output
        else if ((message.at(i) >= 'a') and (message.at(i) <= 'z')){
            
            // if the shift is positive
            if (shift > 0){
                // if the new char goes out of range of letters, sets it back into the range
                if (message.at(i) + shift > 'z'){
                    temp = (message.at(i) + shift - ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continues as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else
            
            } // end of if statement

            // if the shift is negative
            else{
                // if the new char goes below the range of letters, sets it back into the range
                if (message.at(i) + shift < 'a'){
                    temp = (message.at(i) + shift + ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continues as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else statement

            } // end of else statement

        } // end of else if statement

        // appends the temp char to the output after all the checking and setting has been complete
        output += temp;

    } // end of for loop

    // sets the message to that of the output
    SetMessage(output);

    // changes the encrypted state
    ToggleEncrypted();

} // end of Encrypt

void Caesar::Decrypt(){
    string message = GetMessage(); // sets the mesage to a variable to be manipulated
    string output = ""; // what will ultimately be output from this function
    int length = message.length(); // variable for iterating across the length of the initial message
    int shift = (0 - m_shift) % 26; // sets the shift to the inverse of what it was for the encryption
    char temp; // used for each character in the message for alteration into the output

    /* EXACT SAME CODE AS ENCRYPT, ONLY THING THAT HAS CHANGED IS THE SHIFT VARIABLE USED */

    for (int i = 0; i < length; i++){
        
        // arbitrarily sets the temp to the char, then goes through the checking process
        temp = message.at(i);
        
        // if the char is an upper case letter
        if ((message.at(i) >= 'A') and (message.at(i) <= 'Z')){

            // if the shift is positive
            if (shift > 0){
                // if the new char goes out of range of letters, sets it back into the range
                if (message.at(i) + shift > 'Z'){
                    temp = (message.at(i) + shift - ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continue as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else
            
            } // end of if statement

            // if the shift is negative
            else{
                // if the new char goes below the range of letters, sets it back into the range
                if (message.at(i) + shift < 'A'){
                    temp = (message.at(i) + shift + ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continues as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else statement

            } // end of else statement

        } // end of if statement

        // if the letter is a lower case, places a lower case in the temp for the output
        else if ((message.at(i) >= 'a') and (message.at(i) <= 'z')){
            
            // if the shift is positive
            if (shift > 0){
                // if the new char goes out of range of letters, sets it back into the range
                if (message.at(i) + shift > 'z'){
                    temp = (message.at(i) + shift - ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continues as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else
            
            } // end of if statement

            // if the shift is negative
            else{
                // if the new char goes below the range of letters, sets it back into the range
                if (message.at(i) + shift < 'a'){
                    temp = (message.at(i) + shift + ALPHABET_LENGTH);

                } // end of if statement

                // if the bounds are not of issue, continues as normal
                else{
                    temp = (message.at(i) + shift);

                } // end of else statement

            } // end of else statement

        } // end of else if statement

        // appends the temp char to the output after all the checking and setting has been complete
        output += temp;

    } // end of for loop

    // sets the message to that of the output
    SetMessage(output);

    // changes the encrypted state
    ToggleEncrypted();

} // end of Decrypt

string Caesar::ToString(){
    return CAESAR;

} // end of ToString

string Caesar::FormatOutput(){
    string message = GetMessage(); // creates a variable of the message
    stringstream fullString; // creates a stringstream object to modify

    // modifies the stringstream object with cipher type, encryption type, message, and shift, with delimeters between
    fullString << "c" << "|" << GetIsEncrypted() << "|" << message << "|" << m_shift;

    // returns the stringstream object as a string 
    return fullString.str();

} // end of FormatOutput