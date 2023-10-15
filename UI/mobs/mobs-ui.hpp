#pragma once

#include <QApplication>
#include <QTranslator>
#include <QPointer>
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>

#include <obs.h>
#include <obs-frontend-api.h>

class MOBSUI : public QObject
{
private:
	QPointer<QWidget> mobsWindow;

	QFormLayout* layout;
	QComboBox* mobsWindowList;
	QPushButton* mobsButton;

public:
	MOBSUI();

	void Init();

private:
	void fillWindowList();
	void windowChanged(int index);
	void buttonClicked(bool checked);
	static bool setWindowCaptureWindow(void* param, obs_source_t* source);
};
