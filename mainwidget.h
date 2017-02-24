#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStack>

class OriginalNumber;
class QPushButton;
class CalculatingClass;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public slots:
    void initialNumberButtons();
    void passThisGroup();
    void undoOneStep();
    void confirmInput();
    void afterHittingNumberButtons();
    void afterHittingOperatorButtons();
    void afterHittingRightPrenthesisButton();


public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void checkConfirmButtonState();
    void checkUndoButtonState();

private:
    Ui::MainWidget *ui;
    OriginalNumber *ori_num;
    CalculatingClass *cal_class;
    QStack<QPushButton*> clicked_pushbuttons;
    QStack<QString> char_stack;

    const static int TOTN = 4;
    const static int TWENTYFOUR = 24;
    int parenthesis_count;

    void setNumberPushButtonsEnableAttribute(bool);
    void setOperatorPushButtonsEnableAttribute(bool);
    void displayTheCharacter(QString);
    void displayTheCharacter();
    void inputALeftParenthesis();
    void inputARightParenthesis();
    void undoALeftParenthesis();
    void undoARightParenthesis();
    bool isParenthesisMatched();
    void hintWithMessageBox(QString h_m);
    void displaySuffixInTextEdit();

    void useCalculatingClass();


};

#endif // MAINWIDGET_H
