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
#include "polynom.h" // Убедитесь, что этот файл определяет класс Polynomial и класс number

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QLabel *evaluateOutput, *polynomFirstForm, *polynomSecondForm;
    QLineEdit *inputAnRe, *inputAnIm, *inputRootRe, *inputRootIm, *inputIndex, *inputResize, *inputEvaluateRe, *inputEvaluateIm;
    QPushButton *changeAn, *addRoot, *changeRoot, *rootsResize, *evaluate;

    Polynom polynom;

    // Функции для настройки секций интерфейса
    void setupAnSection(QWidget* parent, QVBoxLayout* parentLayout, QLineEdit*& inputAnRe, QLineEdit*& inputAnIm, QPushButton*& changeAn);
    void setupRootSection(QWidget* parent, QVBoxLayout* parentLayout, QLineEdit*& inputRootRe, QLineEdit*& inputRootIm, QPushButton*& addRoot, QLineEdit*& inputIndex, QPushButton*& changeRoot, QLineEdit*& inputResize, QPushButton*& rootsResize);
    void setupEvaluateSection(QWidget* parent, QVBoxLayout* parentLayout, QLineEdit*& inputEvaluateRe, QLineEdit*& inputEvaluateIm, QPushButton*& evaluate, QLabel*& evaluateOutput);
    void setupPolynomSection(QWidget* parent, QVBoxLayout* parentLayout, QLabel*& polynomFirstForm, QLabel*& polynomSecondForm);

    // Связь сигналов и слотов
    void connectSignals(QPushButton* changeAn, QPushButton* addRoot, QPushButton* changeRoot, QPushButton* rootsResize, QPushButton* evaluate);

private slots:
    void onChangeAnClicked();
    void onAddRootClicked();
    void onChangeRootClicked();
    void onRootsResizeClicked();
    void onEvaluateClicked();
    void showPolynomClassic();
    void showPolynomCanon();
};

#endif // MAINWINDOW_H
