#ifndef TESTS_H
#define TESTS_H

#include <QObject>

class tests : public QObject
{
    Q_OBJECT
public:
    explicit tests(QObject *parent = nullptr);

private slots:
    void parseString_complexTest();
    void parseString_multiplePropsTest();
    void parseString_noPropsAllTest();
    void parseString_noPropsSimpleTest();
    void parseString_wrongClassNameTest();
    void parseString_wrongPropNameTest();
    void parseString_wrongPropValueTest();
    void parseString_wrongPropCountValueTest();
    void parseString_multipleValueTest();

    void parseInputFile_complexTest();
    void parseInputFile_singleClassTest();
    void parseInputFile_noClassesTest();
    void parseInputFile_noNumberTest();
    void parseInputFile_wrongNumberTest();
};

#endif // TESTS_H
