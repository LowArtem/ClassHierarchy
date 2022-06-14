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
    QFile file(inputFile);
    if (file.open(QIODevice::ReadOnly))
    {
        QString line = file.readLine();
        bool isFirstNumberInteger = false;
        int ruleNumber = line.toInt(&isFirstNumberInteger);
        if (!isFirstNumberInteger)
        {
            qDebug() << "Неверный формат входных данных - не указаны правила, по которым строится иерархия классов";
            return;
        }

        while(!file.atEnd())
        {
            line = file.readLine();

            ClassInfo classInfo;
            parseString(line, classInfo);
            classes.append(classInfo);
        }
    }
    else
    {
        qDebug() << "Ошибка при открытии файла";
    }
}

void parseString(QString string, struct ClassInfo &classs)
{
    // Получение названия класса
    int fIndex = string.indexOf("Класс \"");

    if (fIndex == -1) throw Error {"Wrong class name", 1};

    fIndex += 7;
    int lIndex = string.indexOf('\"', fIndex);

    QString className = string.mid(fIndex, lIndex-fIndex);
    classs.className = className;

    // Получение свойств класса
    fIndex = string.indexOf("свойство \"");
    while(fIndex != -1)
    {
        // Получение названия свойства
        fIndex += 10;
        lIndex = string.indexOf('\"', fIndex);

        QString propertyName = string.mid(fIndex, lIndex - fIndex);

        // Получение значений свойства
        fIndex = string.indexOf(" = \"", lIndex);

        if (fIndex == -1) throw Error {"Property value doesn't exists", 1};

        fIndex += 4;
        lIndex = string.indexOf('\"', fIndex);

        QList<int> values;
        QString strValues = string.mid(fIndex, lIndex - fIndex);
        QList<QString> strValuesList = strValues.split(',');
        for (int i = 0; i < strValuesList.count(); i++)
        {
            bool isConvertationOk = false;
            values.append(strValuesList[i].toInt(&isConvertationOk));

            if (!isConvertationOk) throw Error {"Wrong property value", 1};
        }

        PropertyInfo prop;
        prop.propertyName = propertyName;
        prop.values = values;
        prop.valuesCount = strValuesList.count();

        classs.properties.append(prop);

        fIndex = string.indexOf("свойство \"", lIndex);
    }

    // Получение свойств с количеством значений
    fIndex = string.indexOf("количество значений свойства \"");
    while(fIndex != -1)
    {
        // Получение названия свойства
        fIndex += 30;
        lIndex = string.indexOf('\"', fIndex);

        QString propertyName = string.mid(fIndex, lIndex - fIndex);

        // Получение количества значений свойства
        fIndex = string.indexOf(" = \"", lIndex);
        fIndex += 4;
        lIndex = string.indexOf('\"', fIndex);
        QString valuesCountStr = string.mid(fIndex, lIndex - fIndex);

        PropertyInfo prop;
        prop.propertyName = propertyName;

        bool isConvertationOk = false;
        prop.valuesCount = valuesCountStr.toInt(&isConvertationOk);
        if (!isConvertationOk) throw Error {"Wrong property count", 1};

        classs.properties.append(prop);

        fIndex = string.indexOf("количество значений свойства \"", lIndex);
    }
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






