#include "InfoPage.h"

void InfoPage::returnMenu()
{
	mainWindow->changePageToHome();
}

InfoPage::InfoPage(MainWindow* mainWin)
{
	mainWindow = mainWin;
	const int imageButtonSize = 50;
	QImage newImage = QImage(".\\Images\\X_Button.png");
	QImage X_Button = newImage.scaled(imageButtonSize, imageButtonSize, Qt::IgnoreAspectRatio);

	widget = new QLabel;

	QPixmap pic(".\\Images\\manette1.png");
	QPixmap scaledPic = pic.scaled(755,372);
	widget->setPixmap(scaledPic);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignHCenter);
	layout->addStretch();

	QFont fontTitle = QFont("Comic Sans MS", 25, 12, false);
	QLabel* title = new QLabel("Les instructions du jeu :");
	title->setFont(fontTitle);
	layout->addWidget(title);

	QFont font = QFont("Arial", 17, 8, false);
	QLabel* label = new QLabel();
	label->setText(QString::fromUtf8("1: Le but du jeu est d'atteindre la fin de chaque niveau (6 au total) sans entrer en collision avec les obstacles.\n2: Pour bouger, le joueur doit d'abord choisir une direction avec le joystick et ensuite appuyer sur 'B'.\n3: L'obtention et l'activation (secouer la manette) d'un bonus (petits hamburgers enfouis dans les niveaux) permet au joueur d'effectuer\n\t5 mouvements sans mourir. Le joueur peut accumuler plusieurs bonus.\n4: Si le joueur bat le meilleur score actuel, le score de celui-ci sera visible pour les prochains. L'expertitude du joueur dans le domaine\n\tsera ainsi reconnue internationalement."));
	label->setFont(font);
	layout->addWidget(label);
	QHBoxLayout* quitLayout = new QHBoxLayout();
	QPushButton* menu = new QPushButton("Retourner");
	connect(menu, &QPushButton::released, this, &InfoPage::returnMenu);
	menu->setFixedHeight(100);
	menu->setFixedWidth(150);
	QFont menuFont = QFont("Comic Sans MS", 17, 8, false);
	menu->setFont(menuFont);
	menu->setStyleSheet(" QPushButton {"
		"border-radius: 5px; "
		"border: 1.5px solid rgb(91,231,255); "
		"background-color: white; }"
		"QPushButton:pressed {"
		"border: 1.4px solid rgb(73,186,205); }"
		"QPushButton:hover {"
		"font-size: 30px;"
		"transition: 0.9s; }");

	QLabel* quitLButton = new QLabel();
	quitLButton->setPixmap(QPixmap::fromImage(X_Button));
	quitLayout->addWidget(menu);
	quitLayout->addWidget(quitLButton);


	layout->addWidget(widget);
	layout->addStretch();
	layout->addLayout(quitLayout);

	layout->addStretch();


}