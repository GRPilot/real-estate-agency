#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "widgetmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      manager(std::make_unique<WidgetManager>(this)){
    ui->setupUi(this);
    ui->layout->addWidget(manager->getCurrentWidget());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onChangedWidget(WidgetType type) {
    QWidget *currentWidget = manager->getCurrentWidget();
    currentWidget->hide();
    ui->layout->removeWidget(currentWidget);
    currentWidget = manager->getWidget(type);
    ui->layout->addWidget(currentWidget);
    currentWidget->show();
}
