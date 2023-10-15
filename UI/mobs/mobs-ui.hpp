#pragma once

#include <QApplication>
#include <QTranslator>
#include <QPointer>

class MOBSUI
{
private:
	QPointer<QWidget> mobsWindow;
public:
	MOBSUI();

	void Init();
};
