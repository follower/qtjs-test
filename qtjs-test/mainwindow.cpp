#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "appapi.h"

TheApi *AppAPI;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(runScript()));

    // TODO: Do this initialisation in `main()` and/or don't store `MainWindow`?
    AppAPI = new TheApi(this);

    // TODO: Do this in `TheApi()` constructor instead?
    connect(AppAPI, SIGNAL(dialValueChanged(int)),
            this->ui->dial, SLOT(setValue(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runScript() {
    ui->txtOutput->appendPlainText(AppAPI->evaluate(ui->editJsSource->document()->toPlainText()).toString());
}

void MainWindow::on_btnExecute_clicked()
{
    timer.stop();
    this->runScript();

    if (ui->checkBox->isChecked()) {
        timer.start(500);
    }
}

void MainWindow::on_checkBox_stateChanged(int newState)
{
    if (newState == Qt::Unchecked) {
        this->timer.stop();
    }
}
