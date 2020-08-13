#include "Cipher.h"

Cipher::Cipher(){
    m_message = "TKL keyboards are fire, but look up the TGR Alice.";
    m_isEncrypted = false;

} // end of default constructor

Cipher::Cipher(string message, bool isEncrypted){
    SetMessage(message);
    cout << "ahaha" << endl;
    ToggleEncrypted();

} // end of overloaded constructor

Cipher::~Cipher(){
    m_message = "";
    m_isEncrypted = false;

} // end of destructor

// getter function for m_message
string Cipher::GetMessage(){return m_message;}

// getter function for m_isEncrypted
bool Cipher::GetIsEncrypted(){return m_isEncrypted;}

// setter function for m_message
void Cipher::SetMessage(string message){m_message = message;}

// "setter" for alternating m_isEncrypted from true to false or vice versa
void Cipher::ToggleEncrypted(){m_isEncrypted = !m_isEncrypted;}

// when the << is used with a Cipher type object, outputs the m_message member as well as calling the virtual ToString function
ostream &operator << (ostream &output, Cipher &C){
    output << C.GetMessage() << " " << C.ToString();
    return output;

} // end of overloading << operator