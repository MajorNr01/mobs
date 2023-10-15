#include "mobs-ui.hpp"

#include <string>

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
	connect(mobsWindow, &QWidget::destroyed, App()->GetMainWindow(), &OBSBasic::close);

	layout = new QFormLayout(mobsWindow);

	mobsButton = new QPushButton("Start Streaming");
	connect(mobsButton, &QPushButton::clicked, this, &MOBSUI::buttonClicked);

	mobsWindowList = new QComboBox(mobsButton);
	fillWindowList();
	connect(mobsWindowList, &QComboBox::currentIndexChanged, this, &MOBSUI::windowChanged);

	layout->addRow(mobsWindowList);
	layout->addRow(mobsButton);

	mobsWindow->show();
	mobsWindow->move(QApplication::primaryScreen()->geometry().center() - mobsWindow->rect().center());
}

void MOBSUI::fillWindowList()
{
	obs_properties_t* windowCaptureProperties = obs_get_source_properties("window_capture");
	obs_property_t* windowCaptureWindowProperty = obs_properties_get(windowCaptureProperties, "window");
	size_t numWindowCaptureWindowProperyItems = obs_property_list_item_count(windowCaptureWindowProperty);

	for (unsigned int i = 0; i < numWindowCaptureWindowProperyItems; i++)
	{
		std::string itemText = std::string(obs_property_list_item_name(windowCaptureWindowProperty, i));
		std::string itemValue = std::string(obs_property_list_item_string(windowCaptureWindowProperty, i));
		mobsWindowList->addItem(itemText.c_str(), itemValue.c_str());
	}
}

void MOBSUI::buttonClicked(bool checked)
{
	if (obs_frontend_streaming_active())
	{
		obs_frontend_streaming_stop();
		mobsButton->setText("Start Streaming");
	}

	else
	{
		obs_frontend_streaming_start();
		mobsButton->setText("Stop Streaming");
	}
}

void MOBSUI::windowChanged(int index)
{
	std::string currentValue = mobsWindowList->currentData().toString().toStdString();

	obs_enum_sources(MOBSUI::setWindowCaptureWindow, &currentValue);
}

bool MOBSUI::setWindowCaptureWindow(void* param, obs_source_t* source)
{
	std::string value = *((std::string*) param);

	std::string sourceName = obs_source_get_name(source);

	if (sourceName == "mobs-window-capture" || sourceName == "mobs-application-audio-capture")
	{
		obs_data_t* settings = obs_source_get_settings(source);
		obs_data_set_string(settings, "window", value.c_str());
		obs_source_update(source, settings);
	}

	return true;
}
