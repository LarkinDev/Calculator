#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rx.setPattern("^(\\-?\\d+(\\.?\\d+)?[\\+\\-\\*\\//]{1})+\\d+(\\.?\\d+)?$");
    validator = new QRegularExpressionValidator(rx, this);
    intialSinals();
}

void MainWindow::intialSinals()
{
    connect(ui->button0,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button1,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button2,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button3,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button4,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button5,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button6,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button7,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button8,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->button9,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->buttonPoint,SIGNAL(clicked()),this, SLOT(showInput()));

    connect(ui->buttonPlus,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->buttonMinus,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->buttonMult,SIGNAL(clicked()),this, SLOT(showInput()));
    connect(ui->buttonDiv,SIGNAL(clicked()),this, SLOT(showInput()));

    connect(ui->buttonBack,SIGNAL(clicked()),this, SLOT(showBack()));
    connect(ui->buttonClear,SIGNAL(clicked()),this, SLOT(clearRes()));

    connect(ui->buttonEqual,SIGNAL(clicked()),this, SLOT(showEquals()));
}


bool MainWindow::checkInput(QString line)
{
    int pos = 0;
    bool flag = true;
    auto v = validator->validate(line,pos);
    if (line.length() > 2)
    {
        auto x1 = line[line.length() - 1];
        auto x2 = line[line.length() - 2];
        if (calc.operators.contains(x1) && calc.operators.contains(x2))
        {
            flag = false;
        }
    }
    if(v != QValidator::Invalid && flag)
    {
        return  true;
    }
    return false;
}

void MainWindow::showInput()
{
    QPushButton* btn = (QPushButton*)sender();
    showInput(btn->text());
}

void MainWindow::showBack()
{
    QString oldRes = ui->labelResult->text();
    QString res = "";
    if(oldRes.length() == 1)
    {
        clearRes();
    }
    else
    {
        res = oldRes.mid(0, oldRes.length() - 1);
    }
    ui->labelResult->setText(res);
}

void MainWindow::clearRes()
{
    ui->labelResult->clear();
    calc.clearCollections();
}

void MainWindow::showEquals()
{
    QString formattedInput = ui->labelResult->text();
    if(formattedInput != "")
    {
        if(calc.operators.contains(formattedInput[formattedInput.length() - 1]))
        {
            formattedInput = formattedInput.mid(0, formattedInput.length() - 1);
        }
        calc.updateList(formattedInput);
        calc.getRPNlist();
        calc.exprCalc();
        ui->labelResult->setText(calc.res.top());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_0: showInput("0"); break;
    case Qt::Key_1: showInput("1"); break;
    case Qt::Key_2: showInput("2"); break;
    case Qt::Key_3: showInput("3"); break;
    case Qt::Key_4: showInput("4"); break;
    case Qt::Key_5: showInput("5"); break;
    case Qt::Key_6: showInput("6"); break;
    case Qt::Key_7: showInput("7"); break;
    case Qt::Key_8: showInput("8"); break;
    case Qt::Key_9: showInput("9"); break;
    case Qt::Key_Period: showInput("."); break;
    case Qt::Key_Comma: showInput("."); break;
    case Qt::Key_Plus: showInput("+"); break;
    case Qt::Key_Minus: showInput("-"); break;
    case Qt::Key_Asterisk: showInput("*"); break;
    case Qt::Key_Slash: showInput("/"); break;
    case Qt::Key_Backspace: showBack(); break;
    case Qt::Key_Return: showEquals(); break;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showInput(QString str)
{
    QString newLabel = ui->labelResult->text() + str;
    if(checkInput(newLabel) && newLabel.length() < 25)
    {
        ui->labelResult->setText(newLabel);
    }
}




