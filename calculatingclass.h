#ifndef CALCULATINGCLASS_H
#define CALCULATINGCLASS_H

#include <QVector>


class CalNode;
class CalculateExpressionAlgorithm;

class CalculatingClass
{
public:
    CalculatingClass();
    ~CalculatingClass();

    void setNodesValue(QString);
    void clearClass();
    bool isValid();
    int calculateWithPostfixAlgorithm();
    int calculateWithAnalyzingTreeAlgorithm();
    QStringList& getSuffixExpression();

private:
    QVector<CalNode*> nodes_vector;
    CalculateExpressionAlgorithm *cal_alg;
    QStringList suf_list;

    //containers for suffix algrithm
//    QVector<CalNode*> suf_nodes_vec;
//    QStack<CalNode*> suf_opr_stack;
//    QStack<CalNode*> suf_cal_stack;

    void setNodeValue(char);
    void setNodeValue(int);
    //functions for suffix


    //function for debug
    void testContainerAsDebug();

};

#endif // CALCULATINGCLASS_H
