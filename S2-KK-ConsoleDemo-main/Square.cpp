#include "Square.h"
#include <QPixmap>
#include "constants.h"

QImage Square::BlockerImage = QImage();
QImage Square::PlayerImage = QImage();
QImage Square::CarImage = QImage();
QImage Square::EmptyImage = QImage();
QImage Square::BonusImage = QImage();

//Auto
QImage Square::AutoLeftFront = QImage();
QImage Square::AutoLeftRear = QImage();
QImage Square::AutoRightFront = QImage();
QImage Square::AutoRightRear = QImage();
//Limo
QImage Square::LimoLeftFront = QImage();
QImage Square::LimoLeftRear = QImage();
QImage Square::LimoMid = QImage();
QImage Square::LimoRightFront = QImage();
QImage Square::LimoRightRear = QImage();
//Truck
QImage Square::TruckLeftFront = QImage();
QImage Square::TruckLeftRear = QImage();
QImage Square::TruckMid = QImage();
QImage Square::TruckRightFront = QImage();
QImage Square::TruckRightRear = QImage();

Square::Square()
{
	widget = new QLabel(this);
	widget->setMargin(0);
	ChangeImage(' ');
}

void Square::ChangeImage(char c)
{
	if (currentChar == c) 
	{
		return;
	}
	currentChar = c;
	switch (c)
	{
	case 'X':
		widget->setPixmap(QPixmap::fromImage(BlockerImage));
		break;
	case '$':
		widget->setPixmap(QPixmap::fromImage(BonusImage));
		break;
	case 'O':
		widget->setPixmap(QPixmap::fromImage(PlayerImage));
		break;
	case '@':
		widget->setPixmap(QPixmap::fromImage(CarImage));
		break;
	case 'a':
		widget->setPixmap(QPixmap::fromImage(AutoLeftFront));
		break;
	case 'b':
		widget->setPixmap(QPixmap::fromImage(AutoLeftRear));
		break;
	case 'c':
		widget->setPixmap(QPixmap::fromImage(LimoLeftFront));
		break;
	case 'd':
		widget->setPixmap(QPixmap::fromImage(LimoMid));
		break;
	case 'e':
		widget->setPixmap(QPixmap::fromImage(LimoLeftRear));
		break;
	case 'f':
		widget->setPixmap(QPixmap::fromImage(TruckLeftFront));
		break;
	case 'g':
		widget->setPixmap(QPixmap::fromImage(TruckMid));
		break;
	case 'h':
		widget->setPixmap(QPixmap::fromImage(TruckLeftRear));
		break;
	case 'i':
		widget->setPixmap(QPixmap::fromImage(AutoRightFront));
		break;
	case 'j':
		widget->setPixmap(QPixmap::fromImage(AutoRightRear));
		break;
	case 'k':
		widget->setPixmap(QPixmap::fromImage(LimoRightFront));
		break;
	case 'm':
		widget->setPixmap(QPixmap::fromImage(LimoRightRear));
		break;
	case 'n':
		widget->setPixmap(QPixmap::fromImage(TruckRightFront));
		break;
	case 'p':
		widget->setPixmap(QPixmap::fromImage(TruckRightRear));
		break;
	default:
		widget->setPixmap(QPixmap::fromImage(EmptyImage));
		break;
	}
	//widget->setFixedSize(QSize(IMAGE_SIZE, IMAGE_SIZE));
}
