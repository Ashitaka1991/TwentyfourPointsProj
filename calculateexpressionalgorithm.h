#ifndef CALCULATEEXPRESSIONALGORITHM_H
#define CALCULATEEXPRESSIONALGORITHM_H

#include <QVector>

class CalNode;

class CalculateExpressionAlgorithm
{
public:
    CalculateExpressionAlgorithm();
    ~CalculateExpressionAlgorithm();
    virtual int calculateExpression(QVector<CalNode*>& nodes_vector) = 0;
    virtual QString getConvertedExpression() = 0;

};

#endif // CALCULATEEXPRESSIONALGORITHM_H
