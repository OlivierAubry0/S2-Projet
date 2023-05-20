#pragma once
#include <QMainWindow>
#include <QApplication>
#include <QtWidgets>
#include <string>
#include <QtGui>
#include "gameBoard.h"
#include "KeyboardData.h"
#include "console.h"
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStackedWidget* stackedWidget;
    GameBoard* _gd;
    KeyboardData* _kd;
    bool* _dead;
    bool* _end;
    QTimer* timer;
private slots:
    void nextCycle();
public:
    bool isDead() {
        return *_dead;
    }
    MainWindow(Console& console,KeyboardData& kd, bool& dead,GameBoard& gd, bool& end);
    void changePageToGame();
    void changePageToHome();
    void changePageToInfo();
    void closeEvent(QCloseEvent* event);
    void quit();
    void display(std::string gameBoard);
    Console* con;
    int nbPowerUps;
};