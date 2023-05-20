#pragma once
#include <QWidget>
#include <string>
#include "MainWindow.h"
#include "Leaderboard.h"
#include "string.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QApplication>

class InfoPage : public QWidget
{
	Q_OBJECT
private:
	MainWindow* mainWindow;
	std::string instructions;
	QImage image;
	QLabel* widget;
public:
	InfoPage(MainWindow* mainWin);
private slots:
	void returnMenu();
};