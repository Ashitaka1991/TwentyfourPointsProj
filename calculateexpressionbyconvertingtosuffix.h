#ifndef CALCULATEEXPRESSIONBYCONVERTINGTOSUFFIX_H
#define CALCULATEEXPRESSIONBYCONVERTINGTOSUFFIX_H

#include "calculateexpressionalgorithm.h"
#include <QVector>
#include <QStack>

class CalNode;

class CalculateExpressionByConvertingToSuffix : public CalculateExpressionAlgorithm
{
public:
    CalculateExpressionByConvertingToSuffix();
    virtual int calculateExpression(QVector<CalNode *>& nodes_vector);
    virtual QString getConvertedExpression();

private:
    enum{
        LOW = 0,
        EQU,
        PRE
    };

    QVector<CalNode*> suf_nodes_vec;
    QVector<CalNode*> suf_exp_vec;
    QStack<CalNode*> suf_opr_stack;
    QStack<CalNode*> suf_cal_stack;
    QString suf_exp;


    void clearAlgorithm();
    int getPrecedenceValue(const CalNode* const s_top,
                           const CalNode* const cur_c);
    void convertExpressionToSuffix();
    void analyzeNode(CalNode* t_n);
    //calculate for value
    int getExpressionValue();
    void calculateOneStep(CalNode* f_n , CalNode* s_n , CalNode* opr_n);
};

#endif // CALCULATEEXPRESSIONBYCONVERTINGTOSUFFIX_H
