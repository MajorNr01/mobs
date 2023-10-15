#include "mobs-ui.hpp"

#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QProcess>
#include <QAccessible>

#include "obs-app.hpp"
#include "window-basic-main.hpp"

MOBSUI::MOBSUI()
{

}

void MOBSUI::Init()
{
	mobsWindow = new QWidget();
	mobsWindow->setAttribute(Qt::WA_DeleteOnClose, true);
	mobsWindow->resize(320, 240);
	mobsWindow->setWindowTitle("MOBS");
	QObject::connect(mobsWindow, &QWidget::destroyed, App()->GetMainWindow(), &OBSBasic::close);
	mobsWindow->show();
}
