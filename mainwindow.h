#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WidgetManager;
enum class WidgetType;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onChangedWidget(WidgetType type);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<WidgetManager> manager;
};
#endif // MAINWINDOW_H
