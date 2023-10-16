#pragma once

#include <QApplication>
#include <QTranslator>
#include <QPointer>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

#include <obs.h>
#include <obs-frontend-api.h>

class MOBSUI : public QObject
{
private:
	QPointer<QWidget> mobsWindow;

	QFormLayout* layout;
	QLabel* windowListLabel;
	QComboBox* mobsWindowListComboBox;
	QLabel* streamKeyLabel;
	QLineEdit* streamKeyLineEdit;
	QPushButton* mobsButton;

public:
	MOBSUI();

	void Init();

private:
	void fillWindowList();
	void fillStreamKeyTextEdit();
	void setStreamKey(const QString& text);
	void windowChanged(int index);
	void buttonClicked(bool checked);
	static bool setWindowCaptureWindow(void* param, obs_source_t* source);
};
