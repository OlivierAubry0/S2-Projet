#include "GamePage.h"
#include <QLabel>
#include "constants.h"
#include <string> 
#include <QPropertyAnimation>

void LoadImages() 
{
	QImage newImage = QImage(".\\Images\\Empty.png");
	Square::EmptyImage = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\Car.png");
	Square::CarImage = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\Blocker.png");
	Square::BlockerImage = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\Bonus.png");
	Square::BonusImage = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\Player.png");
	Square::PlayerImage = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	//Auto Left
	newImage = QImage(".\\Images\\auto_front_flipped.png");
	Square::AutoLeftFront = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\auto_rear_flipped.png");
	Square::AutoLeftRear = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	//Limo left
	newImage = QImage(".\\Images\\limo_front_flipped.png");
	Square::LimoLeftFront = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\limo_rear_flipped.png");
	Square::LimoLeftRear = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\limo_middle.png");
	Square::LimoMid = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	//Truck left
	newImage = QImage(".\\Images\\truck_front_flipped.png");
	Square::TruckLeftFront = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\truck_rear_flipped.png");
	Square::TruckLeftRear = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\truck_middle.png");
	Square::TruckMid = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	//Auto Right
	newImage = QImage(".\\Images\\auto_front.png");
	Square::AutoRightFront = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\auto_rear.png");
	Square::AutoRightRear = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	//Limo Right
	newImage = QImage(".\\Images\\limo_front.png");
	Square::LimoRightFront = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\limo_rear.png");
	Square::LimoRightRear = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	//Truck Right
	newImage = QImage(".\\Images\\truck_front.png");
	Square::TruckRightFront = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
	newImage = QImage(".\\Images\\truck_rear.png");
	Square::TruckRightRear = newImage.scaled(IMAGE_SIZE, IMAGE_SIZE, Qt::IgnoreAspectRatio);
}


GamePage::GamePage(MainWindow* mainWin)
{
	oldLevel = 0;
	changingLevel = false;
	QFont font =  QFont("Comic Sans MS", 20, 3, false);
	LoadImages();
	mainWindow = mainWin;
	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addStretch();
	for (int h = 0; h < HEIGHT; h++)
	{
		QHBoxLayout* hbox = new QHBoxLayout;
		hbox->addStretch();
		for (int w = 0; w < WIDTH; w++)
		{
			Square* square = new Square();
			square->setFixedSize(QSize(IMAGE_SIZE, IMAGE_SIZE));
			square->setContentsMargins(0, 0, 0, 0);
			squares.push_back(square);
			hbox->addWidget(square);
		}
		hbox->addStretch();
		//hbox->setContentsMargins(0, 0, 0, 0);
		hbox->setSpacing(0);
		vbox->addLayout(hbox);
	}
	QHBoxLayout* hboxtext = new QHBoxLayout;
	hboxtext->addStretch();
	int currentLvl = mainWindow->con->currentLevel + 1;
	scoreLabel = new QLabel;
	powerUpsLabel = new QLabel;
	lvlLabel = new QLabel;

	powerUpsLabel->setFont(font);
	scoreLabel->setFont(font);
	lvlLabel->setFont(font);
	scoreLabel->setMargin(15);
	powerUpsLabel->setMargin(15);
	lvlLabel->setMargin(15);

	/*animation = new QPropertyAnimation(lvlLabel, "font", this);
	animation->setStartValue(goofyFont);
	animation->setEndValue(font);
	animation->setDuration(1000);*/
	/*animation = new QPropertyAnimation(lvlLabel, "font");
	animation->setStartValue(font);
	animation->setEndValue(goofyFont);
	animation->setDuration(3000);*/

	hboxtext->addWidget(scoreLabel);
	hboxtext->addWidget(lvlLabel);
	hboxtext->addWidget(powerUpsLabel);
	hboxtext->addStretch();
	vbox->addLayout(hboxtext);
	vbox->addStretch();
	vbox->setSpacing(0);
	
	
	//animation = new QPropertyAnimation(lvlLabel, "geometry");
	//animation->setDuration(1000);
	//animation->setKeyValueAt(0, lvlLabel->geometry());
	//animation->setKeyValueAt(0.5, lvlLabel->geometry().adjusted(500, 400, 500, 400));
	//animation->setKeyValueAt(1, lvlLabel->geometry());

	
}

void GamePage::display(std::string gameBoard)
{	
	for (int i = 0; i < gameBoard.size(); i++)
	{
		squares[i]->ChangeImage(gameBoard[i]);
	}

	int currentLvl = mainWindow->con->currentLevel + 1;
	int currentScore = mainWindow->con->score;
	int nbPowerUps = mainWindow->nbPowerUps;
	scoreLabel->setText(QString::fromStdString("Score : " + std::to_string(currentScore)));
	lvlLabel->setText(QString::fromStdString("Niveau : " + std::to_string(currentLvl)));
	powerUpsLabel->setText(QString::fromStdString("Power Ups : " + std::to_string(nbPowerUps)));
	if ((currentLvl - oldLevel) > 1 && !changingLevel) {
		changingLevel = true;
		oldLevel++;
		shakeLabel(lvlLabel);
		//animation->start();
		//lvlLabel->setFont(font);
		//lvlLabel->setFont(goofyFont);
		//Sleep(200);
		//changingLevel = true;
		//Sleep(200);
		//lvlLabel->setFont(font);
	}
	if (mainWindow->isDead()) {
		oldLevel = 0;
	}
	changingLevel = false;
	

}

void GamePage::returnMenu()
{
	mainWindow->changePageToHome();
}
