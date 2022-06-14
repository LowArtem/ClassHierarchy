#include <QCoreApplication>

#include <QtTest/QTest>
#include "header.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    QTest::qExec(new tests, argc, argv);

    return 0;
}

void parseInputFile(QString inputFile, QList<ClassInfo> &classes)
{

}

void parseString(QString string, struct ClassInfo &classs)
{

}

void getHighestClasses(QList<struct ClassInfo> &classes, QList<struct ClassInfo> &highestClasses)
{

}

void getClassesWithGivenProperties(QList<QString> propertyNames, QList<struct ClassInfo> &classes, QList<struct ClassInfo> &classesWithGivenProperty)
{

}

bool IsClassPropertiesEqual(struct ClassInfo &class1, struct ClassInfo &class2, QString propertyName)
{
    return false;
}

void splitByHierarchy(QList<struct ClassInfo> &classes)
{

}

void splitByRelationship(QList<struct ClassInfo> &classes)
{

}

void writeToXML(QList<struct ClassInfo> &classes, QString outputFile)
{

}

void writeClassToXML(struct ClassInfo &classs, QList<QString> &outputXML, QList<int> &closedTagsStringIndexes)
{

}






