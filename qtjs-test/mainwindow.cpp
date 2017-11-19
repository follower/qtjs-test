#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "appapi.h"

TheApi *AppAPI;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    AppAPI = new TheApi(this);

    connect(AppAPI, SIGNAL(dialValueChanged(int)),
            this->ui->dial, SLOT(setValue(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnExecute_clicked()
{
    ui->txtOutput->appendPlainText(AppAPI->evaluate(ui->editJsSource->document()->toPlainText()).toString());
}
