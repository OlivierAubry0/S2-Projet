#include <iostream>
#include <Windows.h>
#include <console.h>
#include "gameBoard.h"
#include "keyboardData.h"
#include <thread>
#include <mutex>
#include <vector>
#include <gameController.h>
#include <constants.h>
#include <LevelsContructor.h>
#include "ArduinoCOM.h"
#include <Leaderboard.h>
#include <MainWindow.h>
#include <QApplication>
#include <chrono>
#include <QPropertyAnimation>

const bool arduinoControl = true;
const char* commPort = "COM5";
const int speed = 40;
int currentLvl = 1;
SerialPort* arduino;

void gameBoardFunction(Console& con, GameBoard& gb, KeyboardData& kd, bool& end,bool& dead, bool& pause)
{
    using namespace std::chrono;
    auto startOfIteration = high_resolution_clock::now();

    GameController gc = GameController(WIDTH/2,HEIGHT-1);
    Level l1 = LevelsContructor::Level1();
    gc.addLevel(l1);

    bool level1Incremented = false;
    bool level2Incremented = false;
    bool level3Incremented = false;
    bool level4Incremented = false;
    bool level5Incremented = false;
    bool level6Incremented = false;
    
    bool changingLvl = false;
    //gc.currentLevel=5;
    //con.currentLevel = gc.currentLevel;
    bool oldPauseValue = false;
   
    while (!dead && !end && gc.currentLevel<7)
    {
        startOfIteration = high_resolution_clock::now();
        Controls controls;
        kd.lock();
        controls.UP = kd.controls.UP;
        controls.DOWN = kd.controls.DOWN;
        controls.LEFT = kd.controls.LEFT;
        controls.RIGHT = kd.controls.RIGHT;
        bool pauseKeyPressed = kd.controls.PAUSE;
        //bool quit = kd.controls.QUIT;
        controls.ACTIVATEPOWERUP = kd.controls.ACTIVATEPOWERUP;
        kd.unlock();
        if (pauseKeyPressed && !oldPauseValue)
        {
            pause = !pause;
        }
        oldPauseValue = pauseKeyPressed;
        if (pause) {
            continue;
        }
        con.score=gc.score;
        if (gc.score == 20 && !level1Incremented) {
            Level l2 = LevelsContructor::Level2();
            gc.addLevel(l2);
            gc.currentLevel++;
            con.currentLevel = gc.currentLevel;
            level1Incremented = true;
            currentLvl++;
            changingLvl = true;
        }
        if (gc.score == 60 && !level2Incremented) {
            Level l3 = LevelsContructor::Level3();
            gc.addLevel(l3);
            gc.currentLevel++;
            con.currentLevel = gc.currentLevel;
            level2Incremented = true;
            currentLvl++;
            changingLvl = true;
        }
        if (gc.score == 120 && !level3Incremented) {
            Level l4 = LevelsContructor::Level4();
            gc.addLevel(l4);
            gc.currentLevel++;
            con.currentLevel = gc.currentLevel;
            level3Incremented = true;
            currentLvl++;
            changingLvl = true;
        }
        if (gc.score == 200 && !level4Incremented) {
            Level l5 = LevelsContructor::Level5();
            gc.addLevel(l5);
            gc.currentLevel++;
            con.currentLevel = gc.currentLevel;
            level4Incremented = true;
            currentLvl++;
            changingLvl = true;
        }
        if (gc.score == 300 && !level5Incremented) {
            Level l6 = LevelsContructor::Level6();
            gc.addLevel(l6);
            gc.currentLevel++;
            con.currentLevel = gc.currentLevel;
            gc.score += 20;
            level5Incremented = true;
            currentLvl++;
            changingLvl = true;
        }
        if (gc.score == 440 && !level6Incremented) {
            Level l3 = LevelsContructor::Level3();
            con.leaderboard.AddScore(500);
            level6Incremented = true;
            currentLvl++;
            dead = true;
        }
        if (gc.isDead()|| gc.currentLevel>6)
        {
            dead = true;
        }
        gc.movePlayer(controls);
        gc.nextCycle();
        std::string content = gc.display();

        gb.lock();
        gb.content = content;
        gb.nbPowerUp = gc.nbPowerUp;
        gb.unlock();
        auto now = high_resolution_clock::now();
        while (duration_cast<milliseconds>(now - startOfIteration).count() < 10) {
            now = high_resolution_clock::now();
        }
        if (changingLvl) 
        {
            
            Sleep(500);
        }
        changingLvl = false;
    }
        
}

enum DirectionJoy {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
void arduinoFunction(KeyboardData& kd, bool& end) {
    std::string raw_msg;
    // Initialisation du port de communication
    arduino = new SerialPort(commPort, BAUD);
    if (!arduino->isConnected()) {
        std::cerr << "Impossible de se connecter au port " << std::string(commPort) << ". Fermeture du programme!" << std::endl;
        end = true;
    }

    // Structure de donnees JSON pour envoie et reception
    QJsonDocument j_msg_send, j_msg_rcv;
    DirectionJoy lastDirection = DirectionJoy::UP;
    // Boucle pour tester la communication bidirectionnelle Arduino-PC
    while (!end) {
        QJsonObject object = j_msg_send.object();
        // Envoie message Arduino
        object["led"] = currentLvl;
        j_msg_send.setObject(object);
        if (!SendToSerial(arduino, j_msg_send)) {
            std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
        }
        // Reception message Arduino
        //j_msg_rcv.clear(); // effacer le message precedent
        if (!RcvFromSerial(arduino, raw_msg)) {
            std::cerr << "Erreur lors de la reception du message. " << std::endl;
        }

        // Impression du message de l'Arduino si valide
        if (raw_msg.size() > 0) {
            //cout << "raw_msg: " << raw_msg << endl;  // debug
            // Transfert du message en json
            j_msg_rcv = QJsonDocument::fromJson(raw_msg.c_str());
            //std::cout << "Message de l'Arduino: " << j_msg_rcv.toJson().toStdString() << std::endl;
            if (j_msg_rcv["haut"].toBool()) lastDirection = DirectionJoy::UP;
            if (j_msg_rcv["bas"].toBool()) lastDirection = DirectionJoy::DOWN;
            if (j_msg_rcv["gauche"].toBool()) lastDirection = DirectionJoy::LEFT;
            if (j_msg_rcv["droite"].toBool()) lastDirection = DirectionJoy::RIGHT;
            int nbMuons = j_msg_rcv["nbmuon"].toInt(-1);
            if (nbMuons != -1)
            {
                LevelsContructor::MuonsCount = nbMuons;
            }
            bool butD = j_msg_rcv["butD"].toBool();
            kd.lock();
            kd.controls.RIGHT = false;
            kd.controls.DOWN = false;
            kd.controls.LEFT = false;
            kd.controls.UP = false;
            kd.controls.ACTIVATEPOWERUP = j_msg_rcv["shaked"].toBool();
            kd.controls.RESTART = j_msg_rcv["butH"].toBool();
            kd.controls.QUIT = j_msg_rcv["butG"].toBool();
            kd.controls.PAUSE = j_msg_rcv["butB"].toBool();
            if (butD)
            {
                switch (lastDirection)
                {   
                case UP:
                    kd.controls.UP = true;
                    kd.controls.DOWN = false;
                    kd.controls.LEFT = false;
                    kd.controls.RIGHT = false;
                    break;
                case DOWN:
                    kd.controls.DOWN = true;
                    kd.controls.UP = false;
                    kd.controls.LEFT = false;
                    kd.controls.RIGHT = false;
                    break;
                case LEFT:
                    kd.controls.LEFT = true;
                    kd.controls.DOWN = false;
                    kd.controls.UP = false;
                    kd.controls.RIGHT = false;
                    break;
                case RIGHT:
                    kd.controls.RIGHT = true;
                    kd.controls.DOWN = false;
                    kd.controls.LEFT = false;
                    kd.controls.UP = false;
                    break;
                default:
                    kd.controls.RIGHT = false;
                    kd.controls.DOWN = false;
                    kd.controls.LEFT = false;
                    kd.controls.UP = false;
                    break;
                }
            }
            kd.unlock();
        }
        // Bloquer le fil pour environ 1 sec
        //Sleep(1); // 1000ms
    }
    QJsonObject object = j_msg_send.object();
    // Envoie message Arduino
    object["led"] = currentLvl;
    j_msg_send.setObject(object);
    if (!SendToSerial(arduino, j_msg_send)) {
        std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
    }

    return;
}


void keyboardFunction(KeyboardData& kd, bool &end)
{
    /*int max = speed;
    int counterUP = 0;
    int counterDown = 0;
    int counterLeft = 0;
    int counterRight = 0;*/
    while (!end)
    {
        bool upButton = GetKeyState(VK_UP) & 0x8000;
        bool downButton = GetKeyState(VK_DOWN) & 0x8000;
        bool leftButton = GetKeyState(VK_LEFT) & 0x8000;
        bool rightButton = GetKeyState(VK_RIGHT) & 0x8000;
        /*if (upButton) {
            counterUP++;
            if (counterUP >= max) 
            {
                upButton = false;
                counterUP = 0;
            }
        }
        if (downButton) {
            counterDown++;
            if (counterDown >= max)
            {
                downButton = false;
                counterDown = 0;
            }
        }
        if (leftButton) {
            counterLeft++;
            if (counterLeft >= max)
            {
                leftButton = false;
                counterLeft = 0;
            }
        }
        if (rightButton) {
            counterRight++;
            if (counterRight >= max)
            {
                rightButton = false;
                counterRight = 0;
            }
        }*/
        kd.lock();
        kd.controls.UP = upButton;
        kd.controls.DOWN = downButton;
        kd.controls.LEFT = leftButton;
        kd.controls.RIGHT = rightButton;
        //RIGHT CONTROL key
        kd.controls.ACTIVATEPOWERUP = GetKeyState(VK_SPACE) & 0x8000;
        //RIGHT SHIFT
        kd.controls.PAUSE = GetKeyState(VK_RSHIFT) & 0x8000;
        //Escape
        kd.controls.QUIT = GetKeyState(VK_ESCAPE) & 0x8000;
        //Enter
        kd.controls.RESTART = GetKeyState(VK_RETURN) & 0x8000;
        kd.unlock();
        Sleep(1);
        
    }
}

void displayFunction(Console& con, GameBoard& gd, bool& end)
{
    while (!end)
    {
        gd.lock();
        std::string content = gd.content;
        gd.unlock();
        con.display(content);
        Sleep(2);
    }
}
void UIMainThreadFunction(Console& con,KeyboardData& kd,bool& dead,GameBoard& gd, bool& end)
{
    QApplication app(__argc, __argv);
    MainWindow mainWin = MainWindow(con,kd,dead,gd,end);
    mainWin.showMaximized();
    app.exec();
}

int main()
{
    Leaderboard leaderboard;
    GameBoard gameBoard;
    KeyboardData keyboardData;
    Console con(WIDTH, HEIGHT);
    bool end = false;
    bool dead = true;
    bool pause = false;

    auto functionThreads = [&con,&gameBoard, &keyboardData, &end,&dead,&pause](int id) {
        if (id == 0) {
            if (arduinoControl) 
            {
                arduinoFunction(keyboardData, end);
            }
            else {
                keyboardFunction(keyboardData, end);
            }
        }
        if (id == 1) {
            displayFunction(con,gameBoard, end);
        }
        if (id == 2) {
            UIMainThreadFunction(con,keyboardData,dead,gameBoard, end);
        }
        if (id == 3) {
            gameBoardFunction(con,gameBoard, keyboardData, end, dead, pause);
        }
    };

    std::vector<std::thread> threads;
    //Starts threads
    for (int i = 0; i < 3; i++)
    {
        threads.emplace_back(functionThreads, i);
    }
    bool justDied = false;
    //Wait for app to end.
    while (!end) {
        if (dead) 
        {
            if (justDied) con.leaderboard.AddScore(con.score);
            justDied = false;
            keyboardData.lock();
            bool restart = keyboardData.controls.RESTART;
            keyboardData.unlock();
            if (restart) 
            {
                justDied = true;
                dead = false;
                currentLvl = 1;
                con.currentLevel = 0;
                con.score = 0;
                threads.emplace_back(functionThreads, 3);
            }
        }
    }
    //Closes the threads
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    gameBoard.lock();
    std::string content = gameBoard.content;
    con.display(content);
    gameBoard.unlock();

    return 0;
}