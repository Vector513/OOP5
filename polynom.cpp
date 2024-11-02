#include "polynom.h"
#include <sstream>
#include <iomanip>

Polynom::Polynom() : degree(0), An(), roots(), coefs() {}

Polynom::~Polynom() {}

void Polynom::clear() {}

void Polynom::fillRoots(const std::string& input) {
    roots.fill(input);
    degree = roots.getSize();
    calculateCoefs();
}

Array Polynom::multiplyPolynomials(const Array& poly1, const Array& poly2) {
    Array result;
    size_t newSize = poly1.getSize() + poly2.getSize() - 1;
    result.resize(newSize);

    for (size_t i = 0; i < poly1.getSize(); ++i) {
        for (size_t j = 0; j < poly2.getSize(); ++j) {
            result[i + j] += poly1[i] * poly2[j];
        }
    }

    return result;
}

void Polynom::calculateCoefs() {
    Array currentPoly;
    currentPoly.add(An);

    for (size_t i = 0; i < roots.getSize(); ++i) {
        Array factor;
        factor.add(-roots[i]);
        factor.add(1.0);
        currentPoly = multiplyPolynomials(currentPoly, factor);
    }

    coefs = currentPoly;
}

void Polynom::setRoot(const int index, const number& newRoot) {
    roots[index] = newRoot;
    calculateCoefs();
}

void Polynom::addRoot(const number& newRoot) {
    roots.add(newRoot);
    calculateCoefs();
    degree++;
}

void Polynom::setAn(const number& newAn) {
    An = newAn;
    calculateCoefs();
}

size_t Polynom::getDegree() const {
    return degree;
}

number Polynom::getAn() {
    return An;
}

Array Polynom::getRoots() {
    return roots;
}

Array Polynom::getCoefs() {
    return coefs;
}

number Polynom::evaluate(const number& x) const {
    number result = An;

    for (size_t i = 0; i < roots.getSize(); ++i) {
        result *= (x - roots[i]);
    }

    return result;
}

void Polynom::resize(const int newSize) {
    roots.resize(newSize);
    coefs.resize(newSize);
}

std::string Polynom::formatComplex(const number& num) const {
    double re = num.getRe();
    double im = num.getIm();
    std::ostringstream result;
    result << std::fixed << std::setprecision(2);

    if (re != 0) {
        result << re;
    }

    if (im > 0) {
        result << (re != 0 ? " + " : "") << im << "i";
    }
    else if (im < 0) {
        result << (re != 0 ? " - " : "") << -im << "i";
    }

    return result.str();
}

void Polynom::show(std::ostream& output, bool isFirstForm) const {
    if (isFirstForm) {
        output << "p(x) = ";
        bool firstTerm = true;
        for (size_t i = coefs.getSize(); i-- > 0;) {
            if (coefs[i].getRe() != 0 || coefs[i].getIm() != 0) {
                double re = coefs[i].getRe();
                double im = coefs[i].getIm();

                if (!firstTerm) {
                    output << (re < 0 || (re == 0 && im < 0) ? " - " : " + ");
                }

                firstTerm = false;

                if (re != 0) {
                    output << std::abs(re);
                }

                if (im != 0) {
                    output << (im > 0 ? " + " : " - ") << std::abs(im) << "i";
                }

                if (i > 0) {
                    output << "x";
                    if (i > 1) {
                        output << "^" << i;
                    }
                }
            }
        }

        if (firstTerm) {
            output << "0";
        }
        output << '\n';
    }
    else {
        output << "p(x) = ";

        if (An.getRe() != 0 || An.getIm() != 0) {
            output << "(" << formatComplex(An) << ")";
        }

        for (size_t i = 0; i < roots.getSize(); ++i) {
            output << "(x ";
            double reRoot = roots[i].getRe();
            double imRoot = roots[i].getIm();

            if (reRoot != 0) {
                output << (reRoot > 0 ? "- " : "+ ") << std::abs(reRoot);
            }

            if (imRoot != 0) {
                output << (imRoot > 0 ? " - " : " + ") << std::abs(imRoot) << "i";
            }

            output << ")";
        }

        if (roots.getSize() == 0 || (An.getRe() == 0 && An.getIm() == 0)) {
            output << "0";
        }

        output << '\n';
    }
}
