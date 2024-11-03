#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("Polynomial");
    setMinimumSize(400, 300);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setStyleSheet("QWidget { background-color: #b5b5b5; }");


    /*
    QPlainTextEdit *inputAnAndRoots = new QPlainTextEdit(centralWidget);
    inputAnAndRoots->setPlainText("Введите An и корни через пробел...");
    mainLayout->addWidget(new QLabel("Ввод как в консоле"));
    mainLayout->addWidget(inputAnAndRoots);
    */
    setupAnSection(centralWidget, mainLayout, inputAnRe, inputAnIm, changeAn);
    setupRootSection(centralWidget, mainLayout, inputRootRe, inputRootIm, addRoot, inputIndex, changeRoot, inputResize, rootsResize);
    setupEvaluateSection(centralWidget, mainLayout, inputEvaluateRe, inputEvaluateIm, evaluate, evaluateOutput);
    setupPolynomSection(centralWidget, mainLayout, polynomFirstForm, polynomSecondForm);
    connectSignals(changeAn, addRoot, changeRoot, rootsResize, evaluate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupAnSection(QWidget* parent, QVBoxLayout* parentLayout, QLineEdit*& inputAnRe, QLineEdit*& inputAnIm, QPushButton*& changeAn)
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(parent);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    QGroupBox* addAnBox = new QGroupBox("Изменить An", parent);
    QHBoxLayout* addAnBoxLayout = new QHBoxLayout(addAnBox);

    addAnBox->setStyleSheet("QGroupBox, QLabel, QLineEdit, QPushButton { background-color: white; }");

    addAnBoxLayout->addWidget(new QLabel("Корень: "));
    inputAnRe = new QLineEdit("0");
    inputAnRe->setValidator(doubleValidator);
    addAnBoxLayout->addWidget(inputAnRe);
    addAnBoxLayout->addWidget(new QLabel(" + "));
    inputAnIm = new QLineEdit("0");
    inputAnIm->setValidator(doubleValidator);
    addAnBoxLayout->addWidget(inputAnIm);
    addAnBoxLayout->addWidget(new QLabel("i"));
    changeAn = new QPushButton("Изменить An");
    addAnBoxLayout->addWidget(changeAn);

    addAnBox->setLayout(addAnBoxLayout);
    parentLayout->addWidget(addAnBox);
    /*
    layout->addWidget(new QLabel("Ввод как в консоле"));

    QPlainTextEdit *inputAnAndRoots = new QPlainTextEdit(this);
    inputAnAndRoots->setPlainText("Введите An и корни через пробел...");
    layout->addWidget(inputAnAndRoots);
    */
}

void MainWindow::setupRootSection(QWidget* parent, QVBoxLayout* parentLayout,
                   QLineEdit*& inputRootRe, QLineEdit*& inputRootIm, QPushButton*& addRoot,
                   QLineEdit*& inputIndex, QPushButton*& changeRoot,
                   QLineEdit*& inputResize, QPushButton*& rootsResize) {

    QDoubleValidator *doubleValidator = new QDoubleValidator(parent);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    QGroupBox *rootBox = new QGroupBox("Операции с корнями", parent);
    QVBoxLayout *rootBoxLayout = new QVBoxLayout(rootBox);

    rootBox->setStyleSheet("QWidget, QLabel, QLineEdit, QPushButton { "
                           "background-color: #f0cd4e;"
                           "margin-top: 1ex;"
                           "QWidget#SpecificWidget {border: 2px solid #FA9300;} "
                           "QWidget::title { background-color: #f1e0a0 } ");

    QWidget *addRootBox = new QWidget(rootBox);
    QHBoxLayout *addRootBoxLayout = new QHBoxLayout(addRootBox);

    addRootBoxLayout->addWidget(new QLabel("Корень: "));
    inputRootRe = new QLineEdit("0");
    inputRootRe->setValidator(doubleValidator);
    addRootBoxLayout->addWidget(inputRootRe);
    addRootBoxLayout->addWidget(new QLabel(" + "));
    inputRootIm = new QLineEdit("0");
    inputRootIm->setValidator(doubleValidator);
    addRootBoxLayout->addWidget(inputRootIm);
    addRootBoxLayout->addWidget(new QLabel("i"));
    addRoot = new QPushButton("Добавить корень");
    addRootBoxLayout->addWidget(addRoot);

    addRootBox->setLayout(addRootBoxLayout);
    rootBoxLayout->addWidget(addRootBox);

    QWidget *changeRootBox = new QWidget(rootBox);
    QHBoxLayout *changeRootBoxLayout = new QHBoxLayout(changeRootBox);

    QIntValidator *intValidator = new QIntValidator(parent);

    changeRootBoxLayout->addWidget(new QLabel("Индекс: "));
    inputIndex = new QLineEdit("0");
    inputIndex->setValidator(intValidator);
    changeRootBoxLayout->addWidget(inputIndex);
    changeRoot = new QPushButton("Изменить корень");
    changeRootBoxLayout->addWidget(changeRoot);

    changeRootBox->setLayout(changeRootBoxLayout);
    rootBoxLayout->addWidget(changeRootBox);

    QWidget *changeRootsSizeBox = new QWidget(rootBox);
    QHBoxLayout *changeRootsSizeBoxLayout = new QHBoxLayout(changeRootsSizeBox);

    changeRootsSizeBoxLayout->addWidget(new QLabel("Размер массива корней: "));
    inputResize = new QLineEdit("0");
    inputResize->setValidator(intValidator);
    changeRootsSizeBoxLayout->addWidget(inputResize);
    rootsResize = new QPushButton("Изменить размер");
    changeRootsSizeBoxLayout->addWidget(rootsResize);

    changeRootsSizeBox->setLayout(changeRootsSizeBoxLayout);
    rootBoxLayout->addWidget(changeRootsSizeBox);

    parentLayout->addWidget(rootBox);
}

void MainWindow::setupEvaluateSection(QWidget* parent, QVBoxLayout* parentLayout,
                                      QLineEdit*& inputEvaluateRe, QLineEdit*& inputEvaluateIm,
                                      QPushButton*& evaluate, QLabel*& evaluateOutput)
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(parent);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    QGroupBox *evaluateBox = new QGroupBox("Вычислить в точке", parent);
    QVBoxLayout *evaluateBoxLayout = new QVBoxLayout(evaluateBox);

    // Блок ввода значений для вычисления
    QWidget *evaluateInputBox = new QWidget(evaluateBox);
    QHBoxLayout *evaluateInputBoxLayout = new QHBoxLayout(evaluateInputBox);

    evaluateInputBoxLayout->addWidget(new QLabel("Значение: "));
    inputEvaluateRe = new QLineEdit("0");
    inputEvaluateRe->setValidator(doubleValidator);
    evaluateInputBoxLayout->addWidget(inputEvaluateRe);
    evaluateInputBoxLayout->addWidget(new QLabel(" + "));
    inputEvaluateIm = new QLineEdit("0");
    inputEvaluateIm->setValidator(doubleValidator);
    evaluateInputBoxLayout->addWidget(inputEvaluateIm);
    evaluateInputBoxLayout->addWidget(new QLabel("i"));
    evaluate = new QPushButton("Вычислить");
    evaluateInputBoxLayout->addWidget(evaluate);

    evaluateInputBox->setLayout(evaluateInputBoxLayout);
    evaluateBoxLayout->addWidget(evaluateInputBox);

    // Блок вывода результата
    QWidget *evaluateOutputBox = new QWidget(evaluateBox);
    QHBoxLayout *evaluateOutputBoxLayout = new QHBoxLayout(evaluateOutputBox);

    evaluateOutput = new QLabel("Результат: p(0) = 0");
    evaluateOutputBoxLayout->addWidget(evaluateOutput);

    evaluateOutputBox->setLayout(evaluateOutputBoxLayout);
    evaluateBoxLayout->addWidget(evaluateOutputBox);

    // Добавление evaluateBox в основной layout
    parentLayout->addWidget(evaluateBox);
}

void MainWindow::setupPolynomSection(QWidget* parent, QVBoxLayout* parentLayout,
                                     QLabel*& polynomFirstForm, QLabel*& polynomSecondForm)
{
    QGroupBox *polynomBox = new QGroupBox("Полином в двух формах", parent);
    QVBoxLayout *polynomBoxLayout = new QVBoxLayout(polynomBox);

    // Первая форма полинома
    QWidget *polynomFirstBox = new QWidget(polynomBox);
    QHBoxLayout *polynomFirstBoxLayout = new QHBoxLayout(polynomFirstBox);

    polynomFirstForm = new QLabel("Значение: p(x) = 0");
    polynomFirstForm->setWordWrap(true);
    polynomFirstBoxLayout->addWidget(polynomFirstForm);

    polynomFirstBox->setLayout(polynomFirstBoxLayout);
    polynomBoxLayout->addWidget(polynomFirstBox);

    // Вторая форма полинома
    QWidget *polynomSecondBox = new QWidget(polynomBox);
    QHBoxLayout *polynomSecondBoxLayout = new QHBoxLayout(polynomSecondBox);

    polynomSecondForm = new QLabel("Значение: p(x) = 0");
    polynomSecondForm->setWordWrap(true);
    polynomSecondBoxLayout->addWidget(polynomSecondForm);

    polynomSecondBox->setLayout(polynomSecondBoxLayout);
    polynomBoxLayout->addWidget(polynomSecondBox);

    // Добавление polynomBox в основной layout
    parentLayout->addWidget(polynomBox);
}

void MainWindow::connectSignals(QPushButton* changeAn, QPushButton* addRoot,
                                QPushButton* changeRoot, QPushButton* rootsResize,
                                QPushButton* evaluate) {
    connect(changeAn, &QPushButton::clicked, this, &MainWindow::onChangeAnClicked);
    connect(addRoot, &QPushButton::clicked, this, &MainWindow::onAddRootClicked);
    connect(changeRoot, &QPushButton::clicked, this, &MainWindow::onChangeRootClicked);
    connect(rootsResize, &QPushButton::clicked, this, &MainWindow::onRootsResizeClicked);
    connect(evaluate, &QPushButton::clicked, this, &MainWindow::onEvaluateClicked);
}

void MainWindow::onChangeAnClicked() {
    //QString str("Назначен An");
    polynom.setAn(number(inputAnRe->text().toDouble(), inputAnIm->text().toDouble()));
    showPolynomClassic();
    showPolynomCanon();
    //output->setText(str);
}

void MainWindow::onAddRootClicked() {
    //QString str("Добавлен корень");
    polynom.addRoot(number(inputRootRe->text().toDouble(), inputRootIm->text().toDouble()));
    showPolynomClassic();
    showPolynomCanon();
    //output->setText(str);
}

void MainWindow::onChangeRootClicked() {
    //QString str("");
    //number newRoot(inputRootRe->text().toDouble(), inputRootIm->text().toDouble());
    if (inputIndex->text().toInt() >= 0 && inputIndex->text().toInt() < polynom.getRoots().getSize()) {
        polynom.setRoot(inputIndex->text().toInt(), number(inputRootRe->text().toDouble(), inputRootIm->text().toDouble()));
        showPolynomClassic();
        showPolynomCanon();
        //str+="Корень изменен";
        //output->setText(str);
    }
    else {
        //str+="Индекса под таким корнем нет!";
        //output->setText(str);
    }
}

void MainWindow::onRootsResizeClicked() {
    //QString str("Размерность массива изменена");

    polynom.resize(inputResize->text().toInt());
    showPolynomClassic();
    showPolynomCanon();
    //output->setText(str);
}

void MainWindow::onEvaluateClicked() {
    QString res = "Результат: p(";
    if (inputEvaluateRe->text().toDouble() != 0 || inputEvaluateIm->text().toDouble() != 0) {
        if (inputEvaluateRe->text().toDouble() != 0) {
            res += QString().setNum(inputEvaluateRe->text().toDouble());
        }
        if (inputEvaluateIm->text().toDouble() != 0) {
            if (inputEvaluateIm->text().toDouble() > 0 && inputEvaluateRe->text().toDouble() != 0) res += "+";
            res += QString().setNum(inputEvaluateIm->text().toDouble()) + "i";
        }
    }
    else {
        res += QString().setNum(inputEvaluateRe->text().toDouble());
    }
    res += ") = ";
    if (polynom.evaluate(number(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble())).getRe() != 0 || polynom.evaluate(number(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble())).getIm() != 0) {
        if (polynom.evaluate(number(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble())).getRe() != 0) {
            res += QString().setNum(polynom.evaluate(number(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble())).getRe());
        }
        if (polynom.evaluate(number(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble())).getIm() != 0) {
            if (polynom.evaluate(number(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble())).getIm() > 0) res += "+";
            res += QString().setNum(polynom.evaluate(number(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble())).getIm()) + "i";
        }
    }
    else {
        res += "0";
    }

    evaluateOutput->setText(res);
    //output->setText(str);
}

void MainWindow::showPolynomClassic() {
    QString str("p(x) = ");
    bool firstTerm = true;
    bool needMinus = false;
    for (size_t i = polynom.getCoefs().getSize(); i-- > 0.0;) {
        if (polynom.getCoefs()[i].getRe() != 0.0 || polynom.getCoefs()[i].getIm() != 0.0) {
            double re = polynom.getCoefs()[i].getRe();
            double im = polynom.getCoefs()[i].getIm();

            if (!firstTerm) {
                needMinus = (re < 0.0 || (re == 0.0 && im < 0.0));
                str+= needMinus ? " - " : " + ";
            }
            else {
                firstTerm = false;
            }

            if (im == 0.0) {
                if (re != 0.0) {
                    str+=QString().setNum(std::abs(re));
                }
            }
            else {
                str+="(";

                if (re != 0.0) {
                    str+=QString().setNum(std::abs(re));
                }
                // 1 im > 0.0 0.0 +
                // 1 im > 0.0 1 -
                // 0.0 im < 0.0 0.0 -
                // 0.0 im < 0.0 1 +
                str+=((im > 0.0)^(needMinus) ? " + " : " - ");
                str+=QString().setNum(std::abs(im));
                str+="i";

                str+=")";
            }


            if (i > 0.0) {
                str+="x";
                if (i > 1) {
                    str+="^";
                    str+=QString().setNum(i);
                }
            }
        }
    }

    if (firstTerm) {
        str+="0";
    }
    polynomFirstForm->setText(str);

}

void MainWindow::showPolynomCanon() {
    QString str("p(x) = ");

    if (polynom.getAn().getRe() != 0.0 || polynom.getAn().getIm() != 0.0) {
        if (polynom.getAn().getIm() == 0.0) {
            str += QString().setNum(std::abs(polynom.getAn().getRe()));
        }
        else {
            str += "(";
            if (polynom.getAn().getRe() != 0.0) {
                std::cout << polynom.getAn().getRe();
                str += QString().setNum(std::abs(polynom.getAn().getRe()));
            }
            str += ((polynom.getAn().getIm() > 0.0) ? " + " : " - ") + QString().setNum(std::abs(polynom.getAn().getIm())) + "i)";
        }

        if (polynom.getRoots().getSize() != 0.0) {
            for (size_t i = 0.0; i < polynom.getRoots().getSize(); ++i) {
                str += "(x";
                double re = polynom.getRoots()[i].getRe();
                double im = polynom.getRoots()[i].getIm();

                if (re != 0.0) {
                    str += (re > 0.0 ? " - " : " + ") +  QString().setNum(std::abs(re));
                }

                if (im != 0.0) {
                    str += (im > 0.0 ? " - " : " + ") + QString().setNum(std::abs(im)) + "i";
                }
                str += ")";
            }
        }
    }

    else {
        str += "0";
    }
    polynomSecondForm->setText(str);
}
