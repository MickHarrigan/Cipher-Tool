#include "Ong.h"

Ong::Ong(){
    SetMessage("test");

} // end of default constructor

Ong::Ong(string message, bool isEncrypted){
    SetMessage(message);
    // if it is in the wrong encryption state, alters it to fit
    // in the end this may be overkill and not necessary
    if (GetIsEncrypted() != isEncrypted){
        ToggleEncrypted();

    } // end of if statement

} // end of overloaded constructor

Ong::~Ong(){
    SetMessage("");

} // end of destructor

bool Ong::IsVowel(char letter){
    int vowels[] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'}; // array of the vowels
    
    // if the letter is a vowel, return true
    for (int i = 0; i < 10; i++){
        if (letter == vowels[i]){
            return true;

        } // end of if statement

    } // end of for loop

    // checks for if the value of letter is that of one of the punctuation
    if ((letter >= 32) and (letter < 65)){
        return true;

    } // end of if statement

    if ((letter >= 91) and (letter < 97)){
        return true;

    } // end of if statement

    if ((letter >= 123) and (letter < 127)){
        return true;

    } // end of if statement

    // if it is not a vowel or a punctuation point, returns false
    else{
        return false;

    } // end of else statement


} // end of IsVowel

void Ong::Encrypt(){
    string message = GetMessage(); // sets the mesage to a variable to be manipulated
    int length = message.length(); // variable for iterating across the length of the initial message
    string output = ""; // what will ultimately be output from this function

    for (int i = 0; i < length; i++){
        // checks the char if it is a consonant
        if (!IsVowel(message.at(i))){
            // if char is a consonant, appends the char to the output and the Ongifier right after it
            output += message.at(i);
            output.append(ONGER);

            // checks if the following char is a letter, to remove the trailing -
            // removes the - at the end in cases like is -> i-song- which becomes i-song
            if (!(message.at(i + 1) >= 'A') and (message.at(i + 1) <= 'Z')){
                output.pop_back();

            } // end of if statement

            else if (!(message.at(i + 1) >= 'a') and (message.at(i + 1) <= 'z')){
                output.pop_back();

            } // end of else if statement

        } // end of if statement

        // if the char is a vowel or a punctuation point
        else{
            // returns the char as is
            output += message.at(i);

            // checks for letters, then adds a - after them
            // the char can only be a vowel in this range but this still works; and this is easier than putting other code here
            if ((message.at(i) >= 'A') and (message.at(i) <= 'Z')){
                // puts a - behind each vowel
                output += '-';

            } // end of if statement

            else if ((message.at(i) >= 'a') and (message.at(i) <= 'z')){
                // puts a - behind each vowel
                output += '-';

            } // end of else if statement

            // checks for the bounds first
            if (i != length - 1){
                // checks for non letters, then removes the - that is extra
                // occurs in cases where a word ends in a vowel, and removes it
                // (the -> tong-hong-e-) without this, and (the -> tong-hong-e) with this code
                if (!(message.at(i + 1) >= 'A') and (message.at(i + 1) <= 'Z')){
                    if (output[output.length() - 1] == '-'){
                        output.pop_back();

                    } // end of if statement

                } // end of if statement

                else if (!(message.at(i + 1) >= 'a') and (message.at(i + 1) <= 'z')){
                    if (output[output.length() - 1] == '-'){
                        output.pop_back();

                    } // end of if statement 

                } // end of else if statement

            } // end of if statement

        } // end of else statement

    } // end of for loop

    // sets the message to that of the output
    SetMessage(output);

    // changes the encrypted state
    ToggleEncrypted();

} // end of Encrypt

void Ong::Decrypt(){
    string encMessage = GetMessage(); // sets the mesage to a variable to be manipulated
    int length = encMessage.length(); // variable for iterating across the length of the initial message
    string output = ""; // what will ultimately be output from this function

    for (int i = 0; i < length; i++){
        // if the char is a consonant
        if (!(IsVowel(encMessage.at(i)))){
            int counter = 0; // amount of chars to skip when a consonant is found

            // adds the char to the output
            output += encMessage.at(i);

            // checks each next char for the letters ong
            // short circuit may be unnecessary over the regular and
            while (counter == 0 and ((encMessage.at(i + 1) == 'o') && (encMessage.at(i + 2) == 'n') && (encMessage.at(i + 3) == 'g'))){
                // if the char after g is not a -
                if (encMessage.at(i + 4) != '-'){
                    // 3 skips
                    counter = 3;

                } // end of if statement

                // if the char after g is -
                else{
                    // 4 skips
                    counter = 4;

                } // end of else statement

            } // end of while loop

            // add the counter for skips to i
            i += counter;
        
        } // end of if statement

        // if the char is a vowel or a punctuation point
        else{
            // removes the trailing - after each vowel in the middle of a word
            if (encMessage.at(i) != '-'){
                // returns the char as is if it is not a -
                output += encMessage.at(i);

            } // end of if statement

        } // end of else statement

    } // end of for loop

    // sets the message to that of the output
    SetMessage(output);

    // changes the encrypted state
    ToggleEncrypted();

} // end of Decrypt

string Ong::ToString(){
    return ONG;

} // end of ToString

string Ong::FormatOutput(){
    stringstream output; // stringstream object to return in the specified format
    string message = GetMessage(); // the message to format

    // modifies the stringstream object with cipher type, encryption type, and message with delimeters between
    output << "o" << "|" << GetIsEncrypted() << "|" << GetMessage() << "|" << " ";

    // returns the stringstream object as a string 
    return output.str();

} // end of FormatOutput