#include "calculateexpressionbyconvertingtosuffix.h"
#include "calnode.h"

#include <QDebug>

//#define CTDEBUG

#ifdef CTDEBUG

#endif

//public functions
CalculateExpressionByConvertingToSuffix::CalculateExpressionByConvertingToSuffix()
{

}

int CalculateExpressionByConvertingToSuffix::calculateExpression(QVector<CalNode *>& nodes_vector)
{
/*
    qDebug() << "ToSuffix Algorithm!" << endl;
    CalNode *tn1,*tn2,*tn3;
    tn1 = nodes_vector[0];
    tn2 = nodes_vector[2];
    (*tn1) += (*tn2);
    qDebug() << "Value after using reloaded operator: numerator: " << tn1->numerator
             << "  denominator: " << tn1->denominator << endl;
*/

    //invalid
    //(*tn1) = (*tn2) + (*tn3);
    //can not work correctly
    //tn1 = (*tn2) + (*tn3);
    //qDebug() << "Value after using reloaded operator: numerator: " << tn1->numerator
    //         << "  denominator: " << tn1->denominator << endl;

//step 1: Copy pointers from vector in case of memory leak
    clearAlgorithm();

    foreach(CalNode* t_n,nodes_vector){
        suf_nodes_vec.push_back(t_n);
    }

//step 2:
    convertExpressionToSuffix();

//step 3:
    return getExpressionValue();
}

QString CalculateExpressionByConvertingToSuffix::getConvertedExpression()
{
    return suf_exp;
}

/**********************************************************************************/
//private functions
int CalculateExpressionByConvertingToSuffix::getPrecedenceValue(const CalNode* const s_top,
                       const CalNode* const cur_c)
{
    if(s_top->c_operator == '('){
        return LOW;
    }
    else if((s_top->c_operator == '+') || (s_top->c_operator == '-')){
        if((cur_c->c_operator == '*') || (cur_c->c_operator == '/')){
            return LOW;
        }
        else{
            return EQU;
        }
    }
    else if((s_top->c_operator == '*') || (s_top->c_operator == '/')){
        if((cur_c->c_operator == '+') || (cur_c->c_operator == '-')){
            return PRE;
        }
        else{
            return EQU;
        }
    }

    //just for avoiding the warn
    return EQU;
}


void CalculateExpressionByConvertingToSuffix::convertExpressionToSuffix()
{
    foreach(CalNode* t_n , suf_nodes_vec){
        analyzeNode(t_n);
    }

    while(!suf_opr_stack.empty()){
        suf_exp_vec.push_back(suf_opr_stack.top());
        suf_opr_stack.pop();
    }

    foreach(CalNode* t_n , suf_exp_vec){
        if(t_n->isNumber()){
            suf_exp.append(QString("%1,").arg(t_n->numerator));
        }
        else{
            suf_exp.append(QString("%1,").arg(t_n->c_operator));
        }
    }
#ifdef CTDEBUG
    qDebug() << "Coverted Exp: " << suf_exp << endl;
#endif

    return;
}

void CalculateExpressionByConvertingToSuffix::analyzeNode(CalNode* t_n)
{
    if(t_n->isNumber()){
        suf_exp_vec.push_back(t_n);
#ifdef CTDEBUG
qDebug() << "Vector Size after number: " << suf_exp_vec.size() << endl;
#endif
    }
    else if(t_n->c_operator == '('){
        suf_opr_stack.push(t_n);
    }
    else if(t_n->c_operator == ')'){
        while(suf_opr_stack.top()->c_operator != '('){
            suf_exp_vec.push_back(suf_opr_stack.top());
            suf_opr_stack.pop();
        }
        suf_opr_stack.pop();
    }
    else{
        if(suf_opr_stack.empty()){
            suf_opr_stack.push(t_n);
            return;
        }


        int pre_value = getPrecedenceValue(suf_opr_stack.top(),t_n);
        if(pre_value == LOW){
            suf_opr_stack.push(t_n);
        }
        else{
            while((pre_value == EQU) || (pre_value == PRE)){
                suf_exp_vec.push_back(suf_opr_stack.top());
                suf_opr_stack.pop();
                if(suf_opr_stack.empty()){
                    break;
                }
                pre_value = getPrecedenceValue(suf_opr_stack.top(),t_n);
            }
            suf_opr_stack.push(t_n);
        }
    }
    return;

}

//calculate for value
int CalculateExpressionByConvertingToSuffix::getExpressionValue()
{
    foreach(CalNode* t_n,suf_exp_vec){
        if(t_n->isNumber()){
            suf_cal_stack.push(t_n);
        }
        else{
            CalNode* s = suf_cal_stack.top();
            suf_cal_stack.pop();
            CalNode* f = suf_cal_stack.top();
            suf_cal_stack.pop();
            calculateOneStep(f,s,t_n);
        }
    }

    CalNode* f_val = suf_cal_stack.top();
    if((f_val->numerator % f_val->denominator) != 0){
        return 0;
    }
    else{
        return ((f_val->numerator)/(f_val->denominator));
    }
}

void CalculateExpressionByConvertingToSuffix::calculateOneStep(CalNode* f_n , CalNode* s_n , CalNode* opr_n)
{
    if(opr_n->c_operator == '+'){
        (*f_n) += (*s_n);
    }
    else if(opr_n->c_operator == '-'){
        (*f_n) -= (*s_n);
        //qDebug() << f_n->numerator << "  " << f_n->denominator << endl;
    }
    else if(opr_n->c_operator == '*'){
        (*f_n) *= (*s_n);
    }
    else if(opr_n->c_operator == '/'){
        (*f_n) /= (*s_n);
    }
    else{
        ;
    }

    suf_cal_stack.push(f_n);

    return;
}


void CalculateExpressionByConvertingToSuffix::clearAlgorithm()
{
    suf_exp.clear();
    suf_cal_stack.clear();
    suf_nodes_vec.clear();
    suf_opr_stack.clear();
    suf_exp_vec.clear();

    return;
}
