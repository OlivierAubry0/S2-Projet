#include "MainWindow.h"
#include <QLabel>
#include <QWidget>
#include "HomePage.h"
#include "GamePage.h"
#include "InfoPage.h"
#include "gameBoard.h"
HomePage* homePage;
GamePage* gamePage;
InfoPage* infoPage;
int currentWidgetIndex = 0;
bool starting = false;
bool justRestarted = false;
void MainWindow::changePageToHome()
{
	stackedWidget->setCurrentIndex(0);
	currentWidgetIndex = 0;
	homePage->refreshValues();
}
void MainWindow::quit()
{
	*(_end) = true;
	close();
}
void MainWindow::display(std::string gameBoard)
{
	gamePage->display(gameBoard);
}
void MainWindow::changePageToGame()
{
	stackedWidget->setCurrentIndex(1);
	_kd->lock();
	_kd->controls.RESTART = true;
	starting = true;
	_kd->unlock();
	currentWidgetIndex = 1;
}
void MainWindow::changePageToInfo()
{
	stackedWidget->setCurrentIndex(2);
	currentWidgetIndex = 2;
}
void MainWindow::closeEvent(QCloseEvent* event)
{
	quit();
	event->accept();
}
bool justQuit = false;
void MainWindow::nextCycle() 
{
	if (currentWidgetIndex == 1) 
	{
		justRestarted = false;
		_kd->lock();
		bool quit = _kd->controls.QUIT;
		_kd->unlock();
		_gd->lock();
		std::string board = _gd->content;
		nbPowerUps = _gd->nbPowerUp;
		_gd->unlock();
		display(board);
		if (!starting && *_dead)
		{
			changePageToHome();
		}
		if (starting && !*_dead)
		{
			starting = false;
		}
		if (quit) 
		{
			*_dead = true;
			justQuit = true;
		}
	}
	else if (currentWidgetIndex == 0)
	{
		_kd->lock();
		bool quit = _kd->controls.QUIT;
		bool restart = _kd->controls.RESTART;
		bool info = _kd->controls.PAUSE;
		_kd->unlock();
		if (info) 
		{
			changePageToInfo();
		}
		if (quit && !justQuit) 
		{
			*_end = true;
		}
		if (!quit && justQuit) 
		{
			justQuit = false;
		}
		if (restart && !justRestarted)
		{
			justRestarted = true;
			justQuit = true;
			homePage->play();
		}
	}
	else 
	{
		_kd->lock();
		bool quit = _kd->controls.QUIT;
		_kd->unlock();
		if (quit) 
		{
			justQuit = true;
			changePageToHome();
		}
	}
	if (*_end) 
	{
		quit();
	}
}

MainWindow::MainWindow(Console& console, KeyboardData& kd, bool& dead,GameBoard& gd, bool& end)
{
	nbPowerUps = 0;
	_gd = &gd;
	_end = &end;
	_dead = &dead;
	_kd = &kd;
	con = &console;
	stackedWidget = new QStackedWidget(this);
	homePage = new HomePage(this);
	gamePage = new GamePage(this);
	infoPage = new InfoPage(this);
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MainWindow::nextCycle);
	timer->start(30);

	stackedWidget->addWidget(homePage);

	QPixmap bg("./Images/bg.png");
	QPalette palette;
	palette.setBrush(QPalette::Window, bg);
	homePage->setAutoFillBackground(true);
	homePage->setPalette(palette);
	//infoPage->setAutoFillBackground(true);
	//infoPage->setPalette(palette);

	QPixmap gameBg("./Images/gameBg.png");
	//gameBg = gameBg.scaled(gamePage->size(), Qt::IgnoreAspectRatio);
	//gameBg.scaledToWidth(1920);
	//gameBg.scaledToHeight(1080);

	QPalette palet;
	palet.setBrush(QPalette::Window, gameBg);
	gamePage->setAutoFillBackground(true);

	gamePage->setPalette(palet);
	infoPage->setAutoFillBackground(true);
	infoPage->setPalette(palet);

	QPalette pal = this->palette();
	pal.setColor(QPalette::Window, Qt::cyan);
	this->setPalette(pal);


	stackedWidget->addWidget(gamePage);
	stackedWidget->addWidget(infoPage);
	stackedWidget->setCurrentIndex(0);
	setCentralWidget(stackedWidget);
}