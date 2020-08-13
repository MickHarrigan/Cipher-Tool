#include "CipherTool.h"

CipherTool::CipherTool(string file){
    m_filename = file;

} // end of constructor

CipherTool::~CipherTool(){
    // iterates over the vector and deletes the pointers inside
    for (unsigned int i = 0; i < m_ciphers.size(); i++){
        delete m_ciphers.at(i);
    }

    // erases the filename that was used

    m_filename = "";

} // end of destructor

void CipherTool::LoadFile(){
    // opens the file from m_filename
    ifstream File(m_filename);

    if (File.is_open()){
        // checks for the end of the file being read
        while (File.peek() != EOF){
            
            // temp variables to be used to load each of the ciphers into the program
            char cipherType; // letter that denotes what cipher is used
            bool isEncrypted; // boolean telling if the message is currently encrypted or not
            string message; // the message to be encrypted/decrypted
            
            string key; // used for Vigenere cipher
            int shift; // used for Caesar cipher


            // fills in the variables that are shared between each of the types of the ciphers
            // ignores the | that is after each piece of information
            File >> cipherType;
            File.ignore(1, '|');
            File >> isEncrypted;
            File.ignore(1, '|');
            getline(File, message, '|');

            // checks for Caesar
            if (cipherType == 'c'){
                // fills in the rest of the information, and creates a dynamic pointer to have in the vector
                File >> shift;
                File.ignore(256, '\n');
                Cipher *temp = new Caesar(message, isEncrypted, shift);

                m_ciphers.push_back(temp);

            } // end of if statement

            // checks for Vigenere
            else if (cipherType == 'v'){
                // fills in the rest of the information, and creates a dynamic pointer to have in the vector
                getline(File, key, '\n');
                Cipher *temp = new Vigenere(message, isEncrypted, key);

                m_ciphers.push_back(temp);

            } // end of else if statement

            // checks for Ong
            else if (cipherType == 'o'){
                File.ignore(256, '\n');
                // dynamically creates a new cipher to add to the vector
                Cipher *temp = new Ong(message, isEncrypted);

                m_ciphers.push_back(temp);

            } // end of else if

        } // end of while loop

    } // end of if statement

    // closes the file
    File.close();

} // end of LoadFile

void CipherTool::DisplayCiphers(){
    for (unsigned int i = 0; i < m_ciphers.size(); i++){
        // uses the overloaded << operator and prints the ciphers out individually
        cout << i + 1 << ". " << *m_ciphers.at(i) << endl << endl;
    
    } // end of for loop

} // end of DisplayCiphers

void CipherTool::EncryptDecrypt(bool encrypt){
    int counter = 0; // used for telling how many are encrypted or decrypted
    for (unsigned int i = 0; i < m_ciphers.size(); i++){

        // checks for either encryption or decryption by parameter

        // if the message is not encrypted, encrypts
        if ((m_ciphers.at(i)->GetIsEncrypted() == false) and (encrypt)){
            m_ciphers.at(i)->Encrypt();
            counter++;

        } // end of if statement

        // if the message is encrypted, decrypts
        else if ((m_ciphers.at(i)->GetIsEncrypted() == true) and (!encrypt)){
            m_ciphers.at(i)->Decrypt();
            counter++;

        } // end of else if statement

    } // end of for loop

    // checks what operation was done, and outputs the correct statement
    if (encrypt){
        cout << counter << " Ciphers Encrypted" << endl;

    } // end of if statement

    else{
        cout << counter << " Ciphers Decrypted" << endl;

    } // end of else statement

} // end of EncryptDecrypt

void CipherTool::Export(){
    string expFile = "test.txt"; // filename for exporting
    cout << "What would you like to call the export file? " << endl;
    cin >> expFile;

    // opens the file that the user input
    ofstream File(expFile);

    // writes each of the ciphers entirely into the file
    for (unsigned int i = 0; i < m_ciphers.size(); i++){
        File << m_ciphers.at(i)->FormatOutput() << endl;

    } // end of for loop

    // closes the file
    File.close();

} // end of Export

int CipherTool::Menu(){
    int playerInput; // the choice that the user will input
    do{
        cout << "What would you like to do?" << endl;
        cout << "1. Display all Ciphers" << endl;
        cout << "2. Encrypt all Ciphers" << endl;
        cout << "3. Decrypt all Ciphers" << endl;
        cout << "4. Export all Ciphers" << endl;
        cout << "5. Exit" << endl;

        cin >> playerInput;
    
    // checks that the input is valid, else runs again
    } while ((playerInput > END) or (playerInput < DISP));
    
    return playerInput;

} // end of Menu

char CipherTool::GetType(Cipher *cipher){
    // Disclaimer, I have no idea how to use this function whatsoever
    // The only thing that I would have used it for is overlapped in the FormatOutput function
    // Thus, this is not actually used, but could be in my code to make it harder
    string type = cipher->ToString();

    if (type == "Caesar"){
        return 'c';
    
    } // end of if statement

    else if (type == "Vigenere"){
        return 'v';
    
    } // end of else if statement

    else if (type == "Ong"){
        return 'o';

    } // end of else if statement

    else{
        // fallback letter for 'n'ot working
        // mainly to stop the -Wall warnings
        return 'n';

    } // end of else statement

} // end of GetType

void CipherTool::Start(){
    // runs the LoadFile function
    LoadFile();

    // displays the menu
    int playerInput = Menu();
    bool dispMenu = false; // used for reprompts

    while (playerInput != END){
        // if the menu should be redisplayed
        if (dispMenu){
            playerInput = Menu();

        } // end of if statement

        switch(playerInput){
            case DISP:
                DisplayCiphers();
                break;
            case ENC:
                EncryptDecrypt(true);
                break;
            case DEC:
                EncryptDecrypt(false);
                break;
            case EXP:
                Export();
                break;
            case END:
                break;
            default:
                cout << "Please enter something between 1 and 5" << endl;
                playerInput = Menu();
                break;

        } // end of switch statement

        // sets the value to true for redisplaying the board when the switch statement is rerun
        dispMenu = true;

    } // end of while loop

} // end of Start