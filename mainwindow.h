#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "polynom.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *nameAnRe, *nameAnIm, *nameRe, *nameIm, *nameEvaluateRe, *nameEvaluateIm, *output, *nameResize;
    QLineEdit *inputAnRe, *inputAnIm, *inputRe, *inputIm, *changeCoefIndex, *inputEvaluateRe, *inputEvaluateIm, *inputResize;
    QPushButton *createCoef, *createAn, *showPolynomClassic, *showPolynomCanon, *changeCoefButton, *evaluateButton, *resizeButton;


    int
        setCoefsX = 50,
        setCoefsY = 50,
        frameWidth = 210+setCoefsX*2,
        frameHeight = 340+setCoefsY*2;

    Polynom polynom;

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void setCoef();
    void setAn();
    void printPolynomClassic();
    void printPolynomCanon();
    void changeCoef();
    void evaluateSlot();
    void resizeSlot();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
