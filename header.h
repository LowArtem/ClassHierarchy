#pragma once

#include <QString>
#include <QList>

struct PropertyInfo
{
    QString propertyName;
    QList<int> values;
    int valuesCount;
};

struct ClassInfo
{
    QString className;
    QList<PropertyInfo> properties;
    int hierarchyNumber;
    QList<ClassInfo> childClasses;
};

void parseInputFile(QString inputFile, QList<ClassInfo> &classes);

void parseString(QString string, struct ClassInfo &classs);

void getHighestClasses(QList<struct ClassInfo> &classes, QList<struct ClassInfo> &highestClasses);

void getClassesWithGivenProperties(QList<QString> propertyNames, QList<struct ClassInfo> &classes,  QList<struct ClassInfo> &classesWithGivenProperty);

bool IsClassPropertiesEqual(struct ClassInfo &class1, struct ClassInfo &class2, QString propertyName);

void splitByHierarchy(QList<struct ClassInfo> classes);

void splitByRelationship(QList<struct ClassInfo> &classes, QMap<QString, int> hierarchyDistributed);

void writeToXML(QList<struct ClassInfo> &classes, QString outputFile);

void writeClassToXML(struct ClassInfo &classs, QList<QString> &outputXML, QList<int> &closedTagsStringIndexes);
