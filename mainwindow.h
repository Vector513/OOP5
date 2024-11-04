#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPushButton>
#include <QLabel>
#include "polynom.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Polynom& otherPolynom, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Polynom& polynom;

    QLabel *evaluateOutput, *polynomFirstForm, *polynomSecondForm, *lastAction;
    QLineEdit *inputAnRe, *inputAnIm, *inputRootRe, *inputRootIm, *inputIndex, *inputResize, *inputEvaluateRe, *inputEvaluateIm;
    QPushButton *changeAn, *addRoot, *changeRoot, *rootsResize, *evaluate;

    void showPolynomClassic();
    void showPolynomCanon();

    void setupAnSection(QWidget* parent, QVBoxLayout* parentLayout, QLineEdit*& inputAnRe, QLineEdit*& inputAnIm, QPushButton*& changeAn);
    void setupRootSection(QWidget* parent, QVBoxLayout* parentLayout, QLineEdit*& inputRootRe, QLineEdit*& inputRootIm, QPushButton*& addRoot, QLineEdit*& inputIndex, QPushButton*& changeRoot, QLineEdit*& inputResize, QPushButton*& rootsResize);
    void setupEvaluateSection(QWidget* parent, QVBoxLayout* parentLayout, QLineEdit*& inputEvaluateRe, QLineEdit*& inputEvaluateIm, QPushButton*& evaluate, QLabel*& evaluateOutput);
    void setupPolynomSection(QWidget* parent, QVBoxLayout* parentLayout, QLabel*& polynomFirstForm, QLabel*& polynomSecondForm);
    void setupLastActionSection(QWidget* parent, QVBoxLayout* parentLayout, QLabel*& lastAction);

    void connectSignals(QPushButton* changeAn, QPushButton* addRoot, QPushButton* changeRoot, QPushButton* rootsResize, QPushButton* evaluate);

private slots:
    void onChangeAnClicked();
    void onAddRootClicked();
    void onChangeRootClicked();
    void onRootsResizeClicked();
    void onEvaluateClicked();
};

#endif // MAINWINDOW_H
