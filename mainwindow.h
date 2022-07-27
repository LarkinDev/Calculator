#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QKeyEvent>
#include <calculator.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QRegularExpression rx;
    QValidator *validator;
    Calculator calc;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void showInput(QString str);
    void intialSinals();


private slots:
    bool checkInput(QString str);
    void showInput();
    void showBack();
    void clearRes();
    void showEquals();
    void keyPressEvent(QKeyEvent *e);
};
#endif // MAINWINDOW_H
