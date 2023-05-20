TEMPLATE     = vcapp
TARGET       = KrustyKrabRoad.Console
CONFIG      += warn_on qt debug windows console
CONFIG 		-= flat
CONFIG	+=-finput-charset=UTF-8
HEADERS     += .\*.h
SOURCES     += .\*.cpp
QT          += widgets
QT		+=core gui \
		multimedia