#include "calculator.h"

Calculator::Calculator()
{
    operators = "+-*/";
}

void Calculator::getRPNlist()
{
    bool ok;
    for(int i = 0; i<exprList.length(); i++)
    {
        double d = exprList[i].toDouble(&ok);
        if(ok)
        {
            rpnList.append(QString::number(d));
        }
        else
        {
            if(rpnStack.isEmpty())
            {
                rpnStack.push(exprList[i]);
            }
            else if (((exprList[i] == "*" || exprList[i] == "/") && (rpnStack.top() == "+" || rpnStack.top() == "-")))
            {
                rpnStack.push(exprList[i]);
            }
            else if (operators.contains(exprList[i]))
            {
                while (!rpnStack.isEmpty())
                {
                    rpnList.append(rpnStack.pop());
                }
                rpnStack.push(exprList[i]);
            }
        }
    }
    while (!rpnStack.isEmpty())
    {
         rpnList.append(rpnStack.pop());
    }
}

void Calculator::exprCalc()
{
    res.clear();
    bool flag = false;
    for (int  i =0; i<rpnList.length(); i++)
    {
        if(!operators.contains(rpnList[i]))
        {
            res.push(rpnList[i]);
        }
        else
        {
            double a = res.pop().toDouble();
            double b = res.pop().toDouble();
            double c = 0;
            if (rpnList[i] == "+")
            {
                c = b + a;
            }
            else if (rpnList[i] == "-")
            {
                 c = b - a;
            }
            else if (rpnList[i] == "*")
            {
                 c = b * a;
            }
            else if (rpnList[i] == "/")
            {
                 c = b / a;
                 flag = true;
            }
            if (flag)
            {
                res.push(QString::number(c,'f', 3));
            }
            else
            {
                res.push(QString::number(c));
            }
        }
    }
}

void Calculator::updateList(QString str)
{
    int i = 0;
    int j = 0;
    QString dig = "";
    QString op = "";
    exprList.clear();
    bool flag = false;
    if ( str[0] == '-')
    {
       str = str.mid(1, str.length());
       flag = true;
    }
    while (i<str.length()) {
        while (j < str.length() && !operators.contains(str[j])) {
            j++;
        }
        dig = str.mid(i, j - i);

        exprList.append(dig);
        if(j < str.length())
        {
            op = str[j];
            exprList.append(op);
        }
        i = j + 1;
        j++;
    }
    if (flag)
    {
        double d = exprList[0].toDouble();
        d*= -1;
        exprList[0] = QString::number(d);
    }
}

void Calculator::clearCollections()
{
    exprList.clear();
    rpnList.clear();
    rpnStack.clear();
}
