#pragma once
#include <QWidget>
#include "MainWindow.h"
#include "Leaderboard.h"
#include <string>
#include <vector>
#include "Square.h"
#include <QImage>
#include <QLabel>
#include<QMediaPlayer>
#include<QAudioOutput>
#include <QPoint>
class GamePage : public QWidget
{
	Q_OBJECT
private:
	MainWindow* mainWindow;
	std::vector<Square*> squares;
	int highestScore;
	QLabel* scoreLabel;
	QLabel* powerUpsLabel;
	int oldLevel;
	QPropertyAnimation* animation;

public:
	QLabel* lvlLabel;
	GamePage(MainWindow* mainWin);
	void display(std::string gameBoard);
	void nextLevel();
	bool changingLevel;
	void shakeLabel(QLabel* label)
	{
		QPropertyAnimation* animation = new QPropertyAnimation(label, "pos");
		animation->setDuration(500);
		QPoint labelPos = label->pos();
		int x = labelPos.x();
		int y = labelPos.y();
		animation->setKeyValueAt(0, QPoint(x, y));
		animation->setKeyValueAt(0.2, QPoint(x+10, y));
		animation->setKeyValueAt(0.4, QPoint(x-10, y));
		animation->setKeyValueAt(0.6, QPoint(x+10, y));
		animation->setKeyValueAt(0.8, QPoint(x-10, y));
		animation->setKeyValueAt(1, labelPos);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
	}

private slots:

	void returnMenu();
};