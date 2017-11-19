#ifndef APPAPI_H
#define APPAPI_H

#include <QObject>
#include <QJSEngine>

#include "mainwindow.h"


class TheApi : public QObject
{
    Q_OBJECT
public:
    TheApi(MainWindow *mainWindow) : _mainWindow(mainWindow) {

        // It seems like there should be a nicer way to link
        // the API to specific widgets...but I guess in reality
        // you wouldn't want to be directly controlling them
        // anyway...

        // These don't work due to `ui` being private:

        //    connect(this, SIGNAL(dialValueChanged(int)),
        //            this->_mainWindow, SLOT(ui->dial->setValue(int)));

        //    connect(this, SIGNAL(dialValueChanged(int)),
        //            this->_mainWindow->ui->dial, SLOT(setValue(int)));

        // This would work but it's un-ideal to have to add a new
        // method for every case like this... (TODO: Maybe some property thing?)

        //    connect(this, SIGNAL(dialValueChanged(int)),
        //            this->_mainWindow, SLOT(setDial(int)));

        Q_UNUSED(this->_mainWindow)

        TheApi::jsEngine.globalObject().setProperty("APP_HOST", "qtjs-test");

        jsAppAPI = TheApi::jsEngine.newQObject(this);

        TheApi::jsEngine.globalObject().setProperty("AppAPI", jsAppAPI);

    }
    virtual ~TheApi() {}

    Q_PROPERTY(QString version MEMBER version CONSTANT)

    Q_INVOKABLE void setDial(int value) {
        emit dialValueChanged(value);
    }

    QJSValue evaluate(const QString &program) {
        return TheApi::jsEngine.evaluate(program);
    }

signals:
    void dialValueChanged(int value);

private:
    const QString version = "0.0.1";
    MainWindow *_mainWindow;
    QJSEngine jsEngine;

    QJSValue jsAppAPI;

};

#endif // APPAPI_H
