#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Real trap shit");
    setFixedSize(frameWidth, frameHeight);

    nameRe = new QLabel("Коэффициент: ", this);
    nameRe->setGeometry(setCoefsX, setCoefsY, 90, 20);

    inputRe = new QLineEdit("1", this);
    inputRe->setGeometry(setCoefsX+90, setCoefsY, 30, 20);

    nameIm = new QLabel(" + i*", this);
    nameIm->setGeometry(setCoefsX+120, setCoefsY, 25, 20);

    inputIm = new QLineEdit("0", this);
    inputIm->setGeometry(setCoefsX+145, setCoefsY, 30, 20);

    createCoef = new QPushButton("Добавить корень", this);
    createCoef->setGeometry(setCoefsX+35, setCoefsY+30, 110, 20);

    changeCoefButton = new QPushButton("Изм. корень под индексом", this);
    changeCoefButton->setGeometry(setCoefsX, setCoefsY+50, 165, 20);

    changeCoefIndex = new QLineEdit("0", this);
    changeCoefIndex->setGeometry(setCoefsX+170, setCoefsY+50, 30, 20);

    nameAnRe = new QLabel("An: ", this);
    nameAnRe->setGeometry(setCoefsX+35, setCoefsY+90, 20, 20);

    inputAnRe = new QLineEdit("1", this);
    inputAnRe->setGeometry(setCoefsX+55, setCoefsY+90, 30, 20);

    nameAnIm = new QLabel(" + i*", this);
    nameAnIm->setGeometry(setCoefsX+85, setCoefsY+90, 25, 20);

    inputAnIm = new QLineEdit("0", this);
    inputAnIm->setGeometry(setCoefsX+110, setCoefsY+90, 30, 20);

    createAn = new QPushButton("Задать An", this);
    createAn->setGeometry(setCoefsX+35, setCoefsY+120, 90, 20);

    nameEvaluateRe = new QLabel("Вычислить в точке", this);
    nameEvaluateRe->setGeometry(setCoefsX, setCoefsY+150, 130, 20);

    inputEvaluateRe = new QLineEdit("1", this);
    inputEvaluateRe->setGeometry(setCoefsX+110, setCoefsY+150, 30, 20);

    nameEvaluateIm = new QLabel(" + i*", this);
    nameEvaluateIm->setGeometry(setCoefsX+140, setCoefsY+150, 25, 20);

    inputEvaluateIm = new QLineEdit("0", this);
    inputEvaluateIm->setGeometry(setCoefsX+165, setCoefsY+150, 30, 20);

    evaluateButton = new QPushButton("Вычислить  ", this);
    evaluateButton->setGeometry(setCoefsX+35, setCoefsY+180, 90, 20);

    nameResize = new QLabel("Изменить макс. размер массива:", this);
    nameResize->setGeometry(setCoefsX, setCoefsY+210, 180, 20);

    inputResize = new QLineEdit("1", this);
    inputResize->setGeometry(setCoefsX+185, setCoefsY+210, 30, 20);

    resizeButton = new QPushButton("Изменить", this);
    resizeButton->setGeometry(setCoefsX+35, setCoefsY+240, 90, 20);

    showPolynomClassic = new QPushButton("Класс. полином", this);
    showPolynomClassic->setGeometry(setCoefsX+35, setCoefsY+270, 110, 20);

    showPolynomCanon = new QPushButton("Канон. полином", this);
    showPolynomCanon->setGeometry(setCoefsX+35, setCoefsY+290, 110, 20);

    output = new QLabel(this);
    output->setGeometry(setCoefsX, setCoefsY+320, 220, 20);

    connect(createCoef, SIGNAL(pressed()), this, SLOT(setCoef()));
    connect(createAn, SIGNAL(pressed()), this, SLOT(setAn()));
    connect(showPolynomClassic, SIGNAL(pressed()), this, SLOT(printPolynomClassic()));
    connect(showPolynomCanon, SIGNAL(pressed()), this, SLOT(printPolynomCanon()));
    connect(changeCoefButton, SIGNAL(pressed()), this, SLOT(changeCoef()));
    connect(evaluateButton, SIGNAL(pressed()), this, SLOT(evaluateSlot()));
    connect(resizeButton, SIGNAL(pressed()), this, SLOT(resizeSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete nameRe;
    delete inputRe;
    delete nameIm;
    delete inputIm;
    delete createCoef;
    delete changeCoefButton;
    delete changeCoefIndex;
    delete nameAnRe;
    delete inputAnRe;
    delete nameAnIm;
    delete inputAnIm;
    delete createAn;
    delete nameEvaluateRe;
    delete inputEvaluateRe;
    delete nameEvaluateIm;
    delete inputEvaluateIm;
    delete evaluateButton;
    delete nameResize;
    delete inputResize;
    delete resizeButton;
    delete showPolynomClassic;
    delete showPolynomCanon;
    delete output;
}

void MainWindow::setCoef() {
    QString str("Добавлен корень");
    number num(inputRe->text().toDouble(), inputIm->text().toDouble());
    polynom.addRoot(num);
    output->setText(str);
}

void MainWindow::setAn() {
    QString str("Назначен An");
    number An(inputAnRe->text().toDouble(), inputAnIm->text().toDouble());
    polynom.setAn(An);
    output->setText(str);
}

void MainWindow::printPolynomClassic() {
    QString str("p(x)=");
    bool firstTerm = true;
    for (size_t i = polynom.getCoefs().getSize(); i-- > 0;) {
        if (polynom.getCoefs()[i].getRe() != 0 || polynom.getCoefs()[i].getIm() != 0) {
            double re = polynom.getCoefs()[i].getRe();
            double im = polynom.getCoefs()[i].getIm();

            if (!firstTerm) {
                str+=(re < 0 || (re == 0 && im < 0) ? " - " : " + ");
            }

            firstTerm = false;

            if (im == 0) {
                if (re != 0) {
                    str+=QString().setNum(std::abs(re));
                }

                if (im != 0) {
                    str+=(im > 0 ? " + " : " - ");
                    str+=QString().setNum(std::abs(im));
                    str+="i";
                }
            }
            else {
                str+="(";

                if (re != 0) {
                    str+=QString().setNum(std::abs(re));
                }

                if (im != 0) {
                    str+=(im > 0 ? " - " : " + ");
                    str+=QString().setNum(std::abs(im));
                    str+="i";
                }

                str+=")";
            }


            if (i > 0) {
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
    output->setText(str);

}

void MainWindow::printPolynomCanon() {
    QString str("p(x)=");

    if (polynom.getAn().getRe() != 0 || polynom.getAn().getIm() != 0) {
        str+="(";
        str+=polynom.formatComplex(polynom.getAn());
        str+=")";
    }

    for (size_t i = 0; i < polynom.getRoots().getSize(); ++i) {
        str+="(x ";
        double reRoot = polynom.getRoots()[i].getRe();
        double imRoot = polynom.getRoots()[i].getIm();

        if (reRoot != 0) {
            str+=(reRoot > 0 ? "- " : "+ ");
            str+=QString().setNum(std::abs(reRoot));
        }

        if (imRoot != 0) {
            str+=(imRoot > 0 ? " - " : " + ");
            str+=QString().setNum(std::abs(imRoot));
            str+="i";
        }

        str+=")";
    }

    if (polynom.getRoots().getSize() == 0 && (polynom.getAn().getRe() == 0 && polynom.getAn().getIm() == 0)) {
        str+="0";
    }
    output->setText(str);
}

void MainWindow::changeCoef() {
    QString str("");
    number newRoot(inputRe->text().toDouble(), inputIm->text().toDouble());
    if (changeCoefIndex->text().toInt()<polynom.getCoefs().getSize()) {
        polynom.setRoot(changeCoefIndex->text().toInt(), newRoot);
        str+="Корень изменен";
        output->setText(str);
    }
    else {
        str+="Индекса под таким корнем нет!";
        output->setText(str);
    }
}

void MainWindow::evaluateSlot() {
    QString str("");
    number evaluateRoot(inputEvaluateRe->text().toDouble(), inputEvaluateIm->text().toDouble());
    str+="p(";
    str+=QString().setNum(inputEvaluateRe->text().toDouble());
    if (inputEvaluateRe->text().toDouble()>=0) str +="+";
    str+=QString().setNum(inputEvaluateIm->text().toDouble());
    str+="i)=";
    str+=QString().setNum(polynom.evaluate(evaluateRoot).getRe());
    if (polynom.evaluate(evaluateRoot).getIm()>=0) str +="+";
    str+=QString().setNum(polynom.evaluate(evaluateRoot).getIm());
    str+="i";
    output->setText(str);
}

void MainWindow::resizeSlot() {
    QString str("Размерность массива изменена");

    polynom.resize(inputResize->text().toInt());

    output->setText(str);
}
