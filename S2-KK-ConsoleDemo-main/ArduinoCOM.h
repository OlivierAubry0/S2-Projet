#pragma once
#include <iostream>
#include <string>

/*-------------------------- Librairies externes ----------------------------*/
#include "SerialPort.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 9600           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message

/*---------------------------- Variables globales ---------------------------*/
//SerialPort* arduino; //doit etre un objet global!

bool SendToSerial(SerialPort* arduino, QJsonDocument j_msg);


bool RcvFromSerial(SerialPort* arduino, std::string& msg);