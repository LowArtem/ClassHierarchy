#include <QCoreApplication>

#include <QtTest/QTest>
#include <QFile>
#include <QTextStream>
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
    file.close();
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

        fIndex += 4;
        lIndex = string.indexOf('\"', fIndex);

        QSet<int> values;
        QString strValues = string.mid(fIndex, lIndex - fIndex);
        QList<QString> strValuesList = strValues.split(',');
        for (int i = 0; i < strValuesList.count(); i++)
        {
            bool isConvertationOk = false;
            values.insert(strValuesList[i].toInt(&isConvertationOk));

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
    // нахождение минимального количества свойств
    int minPropCount = 10000000;
    QList<struct ClassInfo> minPropCountClasses;

    for (int i = 0; i < classes.count(); i++)
    {
        if (classes[i].properties.count() < minPropCount)
        {
            minPropCount = classes[i].properties.count();
        }
    }

    // получение классов с минимальным количество свойств
    for (int i = 0; i < classes.count(); i++)
    {
        if (classes[i].properties.count() == minPropCount)
            minPropCountClasses.append(classes[i]);
    }

    // если такой класс 1 - вернуть его
    if (minPropCountClasses.count() == 1)
    {
        highestClasses.append(minPropCountClasses[0]);
        return;
    }

    // Для каждого класса из списка с минимальным количеством свойств
    for (int i = 0; i < minPropCountClasses.count(); i++)
    {
        /*
         * Каждому классу присвоить номер в иерархии относительно содержания свойств
         * (наличие свойства - 1, количество значений свойства - 2, набор значений свойства - 3, конкретное значение свойства - 4)
         */

        int score = 0;

        // для каждого свойства
        for (int j = 0; j < minPropCountClasses[i].properties.count(); j++)
        {
            if (minPropCountClasses[i].properties[j].values.count() == 0 && minPropCountClasses[i].properties[j].valuesCount == 0)
            {
                score += 1;
            }
            else if (minPropCountClasses[i].properties[j].values.count() == 0 && minPropCountClasses[i].properties[j].valuesCount > 0)
            {
                score += 2;
            }
            else if (minPropCountClasses[i].properties[j].values.count() > 1)
            {
                score += 3;
            }
            else if (minPropCountClasses[i].properties[j].values.count() == 1)
            {
                score += 4;
            }
        }

        minPropCountClasses[i].hierarchyNumber = score;
    }

    // нахождение минимального уровня в иерархии
    int minScore = 10000000;

    for (int i = 0; i < minPropCountClasses.count(); i++)
    {
        if (minPropCountClasses[i].hierarchyNumber < minScore)
        {
            minScore = minPropCountClasses[i].hierarchyNumber;
        }
    }

    // получение классов минимального уровня в иерархии
    for (int i = 0; i < minPropCountClasses.count(); i++)
    {
        if (minPropCountClasses[i].hierarchyNumber == minScore)
            highestClasses.append(minPropCountClasses[i]);
    }
}

void getClassesWithGivenProperties(QList<QString> propertyNames, QList<struct ClassInfo> &classes, QList<struct ClassInfo> &classesWithGivenProperty)
{
    for (int i = 0; i < classes.count(); i++)
    {
        QList<bool> hasProperties;
        for (int j = 0; j < classes[i].properties.count(); j++)
        {
            if (propertyNames.contains(classes[i].properties[j].propertyName))
            {
                hasProperties.append(true);
            }
        }
        if (hasProperties.count() == propertyNames.count())
        {
            classesWithGivenProperty.append(classes[i]);
        }
    }
}

bool IsClassPropertiesEqual(struct ClassInfo &class1, struct ClassInfo &class2, QString propertyName)
{
    // проверка наличия свойств в классах

    bool hasProperty1 = false;
    bool hasProperty2 = false;

    PropertyInfo prop1;
    PropertyInfo prop2;

    for (int i = 0; i < class1.properties.count(); i++)
    {
        if (class1.properties[i].propertyName == propertyName)
        {
            hasProperty1 = true;
            prop1 = class1.properties[i];
            break;
        }
    }
    for (int i = 0; i < class2.properties.count(); i++)
    {
        if (class2.properties[i].propertyName == propertyName)
        {
            hasProperty2 = true;
            prop2 = class2.properties[i];
            break;
        }
    }

    if (!hasProperty1 || !hasProperty2) return false;

    // Если не равно количество значений в наборе значений
    if (prop1.values.count() != prop2.values.count()) return false;

    // Если свойства содержат набор значений
    if (prop1.values.count() > 0)
    {
        return prop1.values == prop2.values;
    }
    // Если свойства содержат количество значений
    else
    {
        return prop1.valuesCount == prop2.valuesCount;
    }
}

void splitByHierarchy(QList<struct ClassInfo> &classes)
{

}

void splitByRelationship(QList<struct ClassInfo> &classes)
{

}

void writeToXML(QList<struct ClassInfo> &classes, QString outputFile)
{
    QList<QString> outputXML;
    QList<int> closedTagsStringIndexes;

    // Добавить данный класс с его потомками в строковый список XML формата
    for (int i = 0; i < classes.count(); i++)
    {
        writeClassToXML(classes[i], outputXML, closedTagsStringIndexes);
    }

    // Записать строковый список в файл
    QFile file(outputFile);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        for (int i = 0; i < outputXML.count(); i++)
        {
            stream << outputXML[i] << "\n";
        }
        file.close();
    }
    else
    {
        throw Error {"Output file opening error", 3};
    }
}

void writeClassToXML(struct ClassInfo &classs, QList<QString> &outputXML, QList<int> &closedTagsStringIndexes)
{

}
