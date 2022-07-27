#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QList>
#include <QStack>



class Calculator
{
public:
    Calculator();
    void getRPNlist();
    void exprCalc();
    void updateList(QString str);
    void clearCollections();
    QString operators;
    QStack<QString>res;
private:
    QList<QString> exprList;
    QList<QString> rpnList;
    QStack<QString> rpnStack;
};

#endif // CALCULATOR_H
