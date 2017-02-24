#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "originalnumber.h"
#include "calculatingclass.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDebug>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    parenthesis_count(0)
{
    ui->setupUi(this);

    ori_num = new OriginalNumber();
    cal_class = new CalculatingClass();

    passThisGroup();


    //connects
    QObject::connect(ui->num_1_PushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingNumberButtons()));
    QObject::connect(ui->num_2_PushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingNumberButtons()));
    QObject::connect(ui->num_3_PushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingNumberButtons()));
    QObject::connect(ui->num_4_PushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingNumberButtons()));
    //right parenthesis is like number pushbuttons,but it has conflict with left one
    QObject::connect(ui->rightParenthesisPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingRightPrenthesisButton()));
    //left parenthesis is like other operator pushbuttons
    QObject::connect(ui->leftParenthesisPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingOperatorButtons()));
    QObject::connect(ui->plusPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingOperatorButtons()));
    QObject::connect(ui->minusPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingOperatorButtons()));
    QObject::connect(ui->multiplyPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingOperatorButtons()));
    QObject::connect(ui->dividePushButton,SIGNAL(clicked(bool)),
                     this,SLOT(afterHittingOperatorButtons()));
    //manipulating pushbuttons
    QObject::connect(ui->passPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(passThisGroup()));
    QObject::connect(ui->confirmPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(confirmInput()));
    QObject::connect(ui->undoPushButton,SIGNAL(clicked(bool)),
                     this,SLOT(undoOneStep()));
}

MainWidget::~MainWidget()
{
    delete ori_num;
    delete cal_class;
    delete ui;
}


//public slots
void MainWidget::initialNumberButtons()
{
    ori_num->generateNewNumbers();

    ui->num_1_PushButton->setText(QString("%1").arg(ori_num->getNum_1()));
    ui->num_2_PushButton->setText(QString("%1").arg(ori_num->getNum_2()));
    ui->num_3_PushButton->setText(QString("%1").arg(ori_num->getNum_3()));
    ui->num_4_PushButton->setText(QString("%1").arg(ori_num->getNum_4()));

    ui->confirmPushButton->setEnabled(false);
    ui->undoPushButton->setEnabled(false);

    return;
}

void MainWidget::passThisGroup()
{
    clicked_pushbuttons.clear();
    char_stack.clear();
    ui->formulaLineEdit->clear();
    ui->formulaVerticalTextEdit->clear();
    parenthesis_count = 0;
    //clear operating class
    cal_class->clearClass();

    initialNumberButtons();
    setNumberPushButtonsEnableAttribute(true);
    setOperatorPushButtonsEnableAttribute(false);
    checkUndoButtonState();
    checkUndoButtonState();

    return;
}

void MainWidget::undoOneStep()
{
//qDebug() << "Count: " << parenthesis_count << endl;

    if(char_stack.empty()){
        checkUndoButtonState();
        return;
    }

    if(char_stack.top().at(0).isNumber()){
        clicked_pushbuttons.pop();
        //afterHittingOperatorButtons();
        setOperatorPushButtonsEnableAttribute(false);
        setNumberPushButtonsEnableAttribute(true);

    }
    else if(char_stack.top().at(0).unicode() == ')'){
        undoARightParenthesis();
    }
    else if(char_stack.top().at(0).unicode() == '('){
        undoALeftParenthesis();
        //afterHittingRightPrenthesisButton();
    }
    else{
        //afterHittingNumberButtons();
        setNumberPushButtonsEnableAttribute(false);
        if(clicked_pushbuttons.size() != TOTN){
            setOperatorPushButtonsEnableAttribute(true);

        }

            if(isParenthesisMatched()){
                ui->rightParenthesisPushButton->setEnabled(false);
                //qDebug() << "right parenthesis!" << endl;
            }
            else{
                ui->rightParenthesisPushButton->setEnabled(true);
            }

    }

    char_stack.pop();
    checkUndoButtonState();
    checkConfirmButtonState();

    displayTheCharacter();

    return;
}

void MainWidget::confirmInput()
{
    if(clicked_pushbuttons.size() != TOTN){
        hintWithMessageBox(tr("Not Complished!"));
        return;
    }
    else if(!isParenthesisMatched()){
        hintWithMessageBox(tr("Parenthesis Not Matched!"));
        return;
    }
    else{
        useCalculatingClass();
    }

    return;
}

void MainWidget::afterHittingNumberButtons()
{
    QPushButton *pbp = qobject_cast<QPushButton*>(sender());

    //qDebug() << pbp->objectName() << endl;

    displayTheCharacter(pbp->text());

    clicked_pushbuttons.push_back(pbp);
    setNumberPushButtonsEnableAttribute(false);
    if(clicked_pushbuttons.size() != TOTN){
        setOperatorPushButtonsEnableAttribute(true);
    }

        if(isParenthesisMatched()){
            ui->rightParenthesisPushButton->setEnabled(false);
        }
        else{
            ui->rightParenthesisPushButton->setEnabled(true);
        }


    checkUndoButtonState();
    checkConfirmButtonState();

    return;
}

void MainWidget::afterHittingOperatorButtons()
{
    QPushButton *pbp = qobject_cast<QPushButton*>(sender());
    displayTheCharacter(pbp->text());

    setOperatorPushButtonsEnableAttribute(false);
    setNumberPushButtonsEnableAttribute(true);

    checkUndoButtonState();

    return;
}


void MainWidget::afterHittingRightPrenthesisButton()
{
    QPushButton *pbp = qobject_cast<QPushButton*>(sender());
    displayTheCharacter(pbp->text());

//    setNumberPushButtonsEnableAttribute(false);
//    setOperatorPushButtonsEnableAttribute(true);
//    ui->leftParenthesisPushButton->setEnabled(false);

    if(isParenthesisMatched()){
        ui->rightParenthesisPushButton->setEnabled(false);
    }

    checkConfirmButtonState();

    return;

}


//public functions
void MainWidget::checkConfirmButtonState()
{
    if((clicked_pushbuttons.size() == TOTN) && isParenthesisMatched()){
        ui->confirmPushButton->setEnabled(true);
    }
    else{
        ui->confirmPushButton->setEnabled(false);
    }

    return;
}

void MainWidget::checkUndoButtonState()
{
    if(!char_stack.empty()){
        ui->undoPushButton->setEnabled(true);
    }
    else{
        ui->undoPushButton->setEnabled(false);
    }

    return;
}

//private functions
void MainWidget::setNumberPushButtonsEnableAttribute(bool b)
{

    ui->num_1_PushButton->setEnabled(b);
    ui->num_2_PushButton->setEnabled(b);
    ui->num_3_PushButton->setEnabled(b);
    ui->num_4_PushButton->setEnabled(b);
    ui->leftParenthesisPushButton->setEnabled(b);

    if(b){
        //unable hitted pushbuttons
        foreach(QPushButton* tpb,clicked_pushbuttons){
            tpb->setEnabled(!b);
        }
    }

    return;
}

void MainWidget::setOperatorPushButtonsEnableAttribute(bool b)
{
    ui->plusPushButton->setEnabled(b);
    ui->minusPushButton->setEnabled(b);
    ui->multiplyPushButton->setEnabled(b);
    ui->dividePushButton->setEnabled(b);
    ui->rightParenthesisPushButton->setEnabled(b);

    return;
}

void MainWidget::displayTheCharacter(QString char_string)
{
    char_stack.push_back(char_string);

    if(char_string == QString("(")){
       inputALeftParenthesis();
    }
    else if(char_string == QString(")")){
       inputARightParenthesis();
    }
    else{
        ;
    }

    ui->formulaLineEdit->clear();
    ui->formulaVerticalTextEdit->clear();
    //display on lineEdit and textEdit
    foreach(QString t_c,char_stack){
        ui->formulaLineEdit->insert(t_c);
        ui->formulaLineEdit->insert(QString("  "));
        ui->formulaVerticalTextEdit->insertPlainText(QString("  "));
        ui->formulaVerticalTextEdit->insertPlainText(t_c);
        ui->formulaVerticalTextEdit->insertPlainText(QString("\n"));
    }

    return;
}

void MainWidget::displayTheCharacter()
{


    ui->formulaLineEdit->clear();
    ui->formulaVerticalTextEdit->clear();

    //qDebug() << "In Display func!" << endl;
    //display on lineEdit and textEdit
    foreach(QString t_c,char_stack){
        ui->formulaLineEdit->insert(t_c);
        ui->formulaLineEdit->insert(QString("  "));
        ui->formulaVerticalTextEdit->insertPlainText(QString("  "));
        ui->formulaVerticalTextEdit->insertPlainText(t_c);
        ui->formulaVerticalTextEdit->insertPlainText(QString("\n"));
    }

    return;
}


void MainWidget::inputALeftParenthesis()
{
    ++parenthesis_count;

    return;
}

void MainWidget::inputARightParenthesis()
{
    --parenthesis_count;

    return;
}

void MainWidget::undoALeftParenthesis()
{
    --parenthesis_count;

    return;
}

void MainWidget::undoARightParenthesis()
{
    ++parenthesis_count;

    return;
}

bool MainWidget::isParenthesisMatched()
{
    if(parenthesis_count == 0)
        return true;
    else
        return false;
}


void MainWidget::hintWithMessageBox(QString h_m)
{
    QMessageBox::warning(this,tr("hint"),
                         h_m,QMessageBox::Ok);

    return;
}

void MainWidget::displaySuffixInTextEdit()
{
    ui->formulaVerticalTextEdit->clear();
    QStringList t_list = cal_class->getSuffixExpression();
    foreach(QString t_s,t_list){
        //qDebug() << t_s;
        ui->formulaVerticalTextEdit->insertPlainText(QString("  "));
        ui->formulaVerticalTextEdit->insertPlainText(t_s);
        ui->formulaVerticalTextEdit->insertPlainText(QString("\n"));
    }
    return;
}


void MainWidget::useCalculatingClass()
{
    //qDebug() << "char stack size: " << char_stack.size();
    foreach(QString t_c,char_stack){
        //qDebug() << t_c;
        cal_class->setNodesValue(t_c);
    }

    //test
    //cal_class->isValid();
    int exp_value;
    exp_value = cal_class->calculateWithPostfixAlgorithm();
    displaySuffixInTextEdit();
    //qDebug() << exp_value;
    if(exp_value == TWENTYFOUR){
        hintWithMessageBox(tr("The Answer is Right!"));
        passThisGroup();
    }
    else{
        hintWithMessageBox(tr("The Answer is Wrong!"));
        ui->confirmPushButton->setEnabled(false);
    }

    return;
}
