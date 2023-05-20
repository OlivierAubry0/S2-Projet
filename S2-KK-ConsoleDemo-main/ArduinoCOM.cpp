/*
 * Auteurs: Jean-Samuel Lauzon
 * Date: Fevrier 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
*/

/*------------------------------ Librairies ---------------------------------*/
#include "ArduinoCOM.h"

/*---------------------------Definition de fonctions ------------------------*/
bool SendToSerial(SerialPort* arduino, QJsonDocument j_msg) {
    // Return 0 if error
    std::string msg = j_msg.toJson().toStdString();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


bool RcvFromSerial(SerialPort* arduino, std::string& msg) {
    // Return 0 if error
    // Message output in msg
    std::string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)

    // Version fonctionnel dans VScode, mais non fonctionnel avec Visual Studio

    while (msg.empty() || msg.back() != '\n') {
        if (msg.size() > MSG_MAX_SIZE) {
            return false;
        }

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);
    }
    // Version fonctionnelle dans VScode et Visual Studio

    /*buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    str_buffer.assign(char_buffer, buffer_size);
    msg.append(str_buffer);
    */
    //msg.pop_back(); //remove '/n' from string


    return true;
}

