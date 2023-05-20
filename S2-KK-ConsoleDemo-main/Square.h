#pragma once
#include <QWidget>
#include <QLabel>
class Square : public QWidget 
{
private:
	QLabel* widget;
	char currentChar = '\0';
public:
	static QImage EmptyImage;
	static QImage PlayerImage;
	static QImage BlockerImage;
	static QImage CarImage;
	static QImage BonusImage;
	//Auto
	static QImage AutoLeftFront;
	static QImage AutoLeftRear;
	static QImage AutoRightFront;
	static QImage AutoRightRear;
	//Limo
	static QImage LimoLeftFront;
	static QImage LimoLeftRear;
	static QImage LimoMid;
	static QImage LimoRightFront;
	static QImage LimoRightRear;
	//Truck
	static QImage TruckLeftFront;
	static QImage TruckLeftRear;
	static QImage TruckMid;
	static QImage TruckRightFront;
	static QImage TruckRightRear;
	Square();
	void ChangeImage(char c);
};