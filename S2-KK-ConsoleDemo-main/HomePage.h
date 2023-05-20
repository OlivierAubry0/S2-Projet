#pragma once
#include <QWidget> 
#include<QMediaPlayer>
#include<QAudioOutput>
#include "MainWindow.h"
class HomePage : public QWidget 
{
	Q_OBJECT
private:
	MainWindow* mainWindow;
	QLabel* title;
	QLabel* highScoreLabel;
	QMediaPlayer* bgMusic = new QMediaPlayer;

	QAudioOutput* audioOutput = new QAudioOutput;

	QMediaPlayer* gameMusic = new QMediaPlayer;

	QAudioOutput* audioOutput2 = new QAudioOutput;
public slots:
	void play();
	void quit();
	void info();
public:
	void refreshValues();
	HomePage(MainWindow* mainWin);
};