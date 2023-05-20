#include "HomePage.h"
#include <QPushButton>
#include <QVBoxLayout>



void HomePage::quit()
{
	mainWindow->quit();
}
void HomePage::play()
{
	mainWindow->changePageToGame();
	bgMusic->stop();
	gameMusic->play();
	
}
void HomePage::info()
{
	mainWindow->changePageToInfo();
}

void HomePage::refreshValues()
{
	int highScore = mainWindow->con->leaderboard.getHighestScore();
	highScoreLabel->setText(QString::fromStdString("Meilleur score : " + std::to_string(highScore)));
	bgMusic->play();
	gameMusic->stop();
}

HomePage::HomePage(MainWindow* mainWin)
{
	//Buttons image
	const int imageButtonSize = 50;
	QImage newImage = QImage(".\\Images\\A_Button.png");
	QImage A_Button = newImage.scaled(imageButtonSize, imageButtonSize, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\B_Button.png");
	QImage B_Button = newImage.scaled(imageButtonSize, imageButtonSize, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\X_Button.png");
	QImage X_Button = newImage.scaled(imageButtonSize, imageButtonSize, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\Y_Button.png");
	QImage Y_Button = newImage.scaled(imageButtonSize, imageButtonSize, Qt::IgnoreAspectRatio);

	bgMusic->setAudioOutput(audioOutput);
	bgMusic->setSource(QUrl::fromLocalFile("./sounds/bgMusic.mp3"));
	audioOutput->setVolume(50);
	bgMusic->setLoops(QMediaPlayer::Infinite);
	bgMusic->play();

	gameMusic->setAudioOutput(audioOutput2);
	gameMusic->setSource(QUrl::fromLocalFile("./sounds/game.mp3"));
	audioOutput2->setVolume(10);
	gameMusic->setLoops(QMediaPlayer::Infinite);


	mainWindow = mainWin;
	QVBoxLayout* layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignHCenter);
	layout->addStretch();

	QFont font = QFont("Comic Sans MS", 17, 8, false);

	

	title = new QLabel;
	title->setFont(font);
	title->setFixedWidth(462);
	title->setFixedHeight(161);

	highScoreLabel = new QLabel;
	highScoreLabel->setFont(font);
	highScoreLabel->setFixedWidth(462);
	layout->addWidget(highScoreLabel);
	layout->addStretch();
	layout->addSpacing(20);
	layout->addWidget(title);
	layout->addSpacing(20);

	QPixmap logo("./Images/logo.png");
	QPalette palette;
	palette.setBrush(QPalette::Window, logo);
	title->setAutoFillBackground(true);
	title->setPalette(palette);

	QHBoxLayout* playLayout = new QHBoxLayout();
	QPushButton* button = new QPushButton("PLAY");
	button->setFont(font);
	button->setFixedHeight(100);
	button->setFixedWidth(462);
	button->setStyleSheet(" QPushButton {"
		"border-radius: 5px; "
		"border: 1.5px solid rgb(91,231,255); "
		"background-color: aqua; }"
		"QPushButton:pressed {"
		"border: 1.4px solid rgb(73,186,205); }"
		"QPushButton:hover {"
		"font-size: 40px;"
		"transition: 0.9s; }");
	QLabel* playLButton = new QLabel();
	playLButton->setPixmap(QPixmap::fromImage(Y_Button));
	playLayout->addWidget(button);
	playLayout->addWidget(playLButton);
	
	QHBoxLayout* infoLayout = new QHBoxLayout();
	QPushButton* infoButton = new QPushButton("INFO");
	infoButton->setFont(font);
	infoButton->setFixedWidth(462);
	infoButton->setFixedHeight(100);
	infoButton->setStyleSheet(" QPushButton {"
		"border-radius: 5px; "
		"border: 1.5px solid rgb(91,231,255); "
		"background-color: aqua; }"
		"QPushButton:pressed {"
		"border: 1.4px solid rgb(73,186,205); }"
		"QPushButton:hover {"
		"font-size: 40px;"
		"transition: 0.9s; }");
	QLabel* infoLButton = new QLabel();
	infoLButton->setPixmap(QPixmap::fromImage(A_Button));
	infoLayout->addWidget(infoButton);
	infoLayout->addWidget(infoLButton);

	QHBoxLayout* quitLayout = new QHBoxLayout();
	QPushButton* quitButton = new QPushButton("QUIT");
	quitButton->setFont(font);
	quitButton->setFixedHeight(100);
	quitButton->setFixedWidth(462);
	quitButton->setStyleSheet(" QPushButton {"
		"border-radius: 5px; "
		"border: 1.5px solid rgb(91,231,255); "
		"background-color: aqua; }"
		"QPushButton:pressed {"
		"border: 1.4px solid rgb(73,186,205); }"
		"QPushButton:hover {"
		"font-size: 40px;"
		"transition: 0.9s; }");
	QLabel* quitLButton = new QLabel();
	quitLButton->setPixmap(QPixmap::fromImage(X_Button));
	quitLayout->addWidget(quitButton);
	quitLayout->addWidget(quitLButton);

	layout->addLayout(playLayout);
	layout->addLayout(infoLayout);
	layout->addLayout(quitLayout);
	layout->addStretch();
	connect(button, &QPushButton::released, this, &HomePage::play);
	connect(quitButton, &QPushButton::released, this, &HomePage::quit);
	connect(infoButton, &QPushButton::released, this, &HomePage::info);
	setLayout(layout);

	layout->addStretch();
	layout->setSpacing(10);
	layout->setAlignment(Qt::AlignHCenter);
	refreshValues();
	
}
	

	