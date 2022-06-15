#include "tests.h"
#include <QtTest/QTest>
#include "header.h"

#include <QString>
#include <QList>

tests::tests(QObject *parent)
    : QObject(parent)
{

}

bool isClassesEquals(struct ClassInfo &class1, struct ClassInfo &class2)
{
    if (class1.className != class2.className) return false;
    if (class1.properties.count() != class2.properties.count()) return false;

    if (class1.childClasses.count() != class2.childClasses.count()) return false;

    for (int i = 0; i < class1.properties.count(); i++)
    {
        if (class1.properties[i].propertyName != class2.properties[i].propertyName) return false;
        if (class1.properties[i].valuesCount != class2.properties[i].valuesCount) return false;
        if (class1.properties[i].values != class2.properties[i].values) return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////

// parseString tests

//////////////////////////////////////////////////////////////////////

void tests::parseString_complexTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\" свойство \"Способ перемещения\" = \"2\" количество значений свойства \"Оружие\" = \"4\"";
    struct ClassInfo test_classs;

    parseString(test_string, test_classs);

    struct ClassInfo right_classs;
    right_classs.className = "Тяжёлый военный корабль";

    struct PropertyInfo prop1;
    prop1.propertyName = "Способ перемещения";
    prop1.values = {2};
    prop1.valuesCount = 1;

    struct PropertyInfo prop2;
    prop2.propertyName = "Оружие";
    prop2.valuesCount = 4;

    right_classs.properties.append(prop1);
    right_classs.properties.append(prop2);

    QVERIFY2(isClassesEquals(test_classs, right_classs) == true, "Classes is not equal");
}

void tests::parseString_multiplePropsTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\" свойство \"Способ перемещения\" = \"2\" свойство \"Оружие\" = \"4\"";
    struct ClassInfo test_classs;

    parseString(test_string, test_classs);

    struct ClassInfo right_classs;
    right_classs.className = "Тяжёлый военный корабль";

    struct PropertyInfo prop1;
    prop1.propertyName = "Способ перемещения";
    prop1.values = {2};
    prop1.valuesCount = 1;

    struct PropertyInfo prop2;
    prop2.propertyName = "Оружие";
    prop2.values = {4};
    prop2.valuesCount = 1;

    right_classs.properties.append(prop1);
    right_classs.properties.append(prop2);

    QVERIFY2(isClassesEquals(test_classs, right_classs) == true, "Classes is not equal");
}

void tests::parseString_noPropsAllTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\"";
    struct ClassInfo test_classs;

    parseString(test_string, test_classs);

    struct ClassInfo right_classs;
    right_classs.className = "Тяжёлый военный корабль";

    QVERIFY2(isClassesEquals(test_classs, right_classs) == true, "Classes is not equal");
}

void tests::parseString_noPropsSimpleTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\" количество значений свойства \"Способ перемещения\" = \"2\" количество значений свойства \"Оружие\" = \"4\"";
    struct ClassInfo test_classs;

    parseString(test_string, test_classs);

    struct ClassInfo right_classs;
    right_classs.className = "Тяжёлый военный корабль";

    struct PropertyInfo prop1;
    prop1.propertyName = "Способ перемещения";
    prop1.valuesCount = 2;

    struct PropertyInfo prop2;
    prop2.propertyName = "Оружие";
    prop2.valuesCount = 4;

    right_classs.properties.append(prop1);
    right_classs.properties.append(prop2);

    QVERIFY2(isClassesEquals(test_classs, right_classs) == true, "Classes is not equal");
}

void tests::parseString_wrongClassNameTest()
{
    QString test_string = "Клас \"Тяжёлый военный корабль\"";
    struct ClassInfo test_classs;

    QVERIFY_EXCEPTION_THROWN(parseString(test_string, test_classs), Error);
}

void tests::parseString_wrongPropNameTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\" свойство Способ перемещения = \"2\"";
    struct ClassInfo test_classs;

    parseString(test_string, test_classs);

    struct ClassInfo right_classs;
    right_classs.className = "Тяжёлый военный корабль";

    QVERIFY2(isClassesEquals(test_classs, right_classs) == true, "Classes is not equal");
}

void tests::parseString_wrongPropValueTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\" количество свойства \"Способ перемещения\" = \"2\"";
    struct ClassInfo test_classs;

    parseString(test_string, test_classs);

    struct ClassInfo right_classs;
    right_classs.className = "Тяжёлый военный корабль";

    QVERIFY2(isClassesEquals(test_classs, right_classs) == true, "Classes is not equal");
}

void tests::parseString_wrongPropCountValueTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\" свойство \"Способ перемещения\" = \"\"";
    struct ClassInfo test_classs;

    QVERIFY_EXCEPTION_THROWN(parseString(test_string, test_classs), Error);
}

void tests::parseString_multipleValueTest()
{
    QString test_string = "Класс \"Тяжёлый военный корабль\" свойство \"Способ перемещения\" = \"2, 3, 1\" количество значений свойства \"Оружие\" = \"4\"";
    struct ClassInfo test_classs;

    parseString(test_string, test_classs);

    struct ClassInfo right_classs;
    right_classs.className = "Тяжёлый военный корабль";

    struct PropertyInfo prop1;
    prop1.propertyName = "Способ перемещения";
    prop1.values = {2, 3, 1};
    prop1.valuesCount = 3;

    struct PropertyInfo prop2;
    prop2.propertyName = "Оружие";
    prop2.valuesCount = 4;

    right_classs.properties.append(prop1);
    right_classs.properties.append(prop2);

    QVERIFY2(isClassesEquals(test_classs, right_classs) == true, "Classes is not equal");
}

//////////////////////////////////////////////////////////////////////

// parseInputFile tests

//////////////////////////////////////////////////////////////////////

void tests::parseInputFile_complexTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input1.txt";
    QList<ClassInfo> testClasses;

    QList<ClassInfo> rightClasses;
    struct ClassInfo right_class;
    struct PropertyInfo prop1;
    struct PropertyInfo prop2;

    right_class.className = "Транспорт";
    prop1.propertyName = "Способ перемещения";
    prop1.valuesCount = 0;
    right_class.properties.append(prop1);
    rightClasses.append(right_class);

    right_class.properties.clear();

    right_class.className = "Воздушный";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {1};
    prop1.valuesCount = 1;
    right_class.properties.append(prop1);
    rightClasses.append(right_class);

    right_class.properties.clear();

    right_class.className = "Водный";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {2};
    prop1.valuesCount = 1;
    right_class.properties.append(prop1);
    rightClasses.append(right_class);

    right_class.properties.clear();

    right_class.className = "Военный корабль";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {2};
    prop1.valuesCount = 1;
    right_class.properties.append(prop1);
    prop2.propertyName = "Оружие";
    prop2.valuesCount = 0;
    right_class.properties.append(prop2);
    rightClasses.append(right_class);

    right_class.properties.clear();

    right_class.className = "Гражданский самолёт";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {1};
    prop1.valuesCount = 1;
    right_class.properties.append(prop1);
    prop2.propertyName = "Вместительность салона";
    prop2.valuesCount = 0;
    right_class.properties.append(prop2);
    rightClasses.append(right_class);

    right_class.properties.clear();

    right_class.className = "Тяжёлый военный корабль";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {2};
    prop1.valuesCount = 1;
    right_class.properties.append(prop1);
    prop2.propertyName = "Оружие";
    prop2.valuesCount = 4;
    right_class.properties.append(prop2);
    rightClasses.append(right_class);

    parseInputFile(filePath, testClasses);
    for (int i = 0; i < testClasses.count(); i++)
    {
        QVERIFY2(isClassesEquals(testClasses[i], rightClasses[i]) == true, "Classes is not equal");
    }
}

void tests::parseInputFile_singleClassTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input2.txt";
    QList<ClassInfo> testClasses;

    QList<ClassInfo> rightClasses;
    struct ClassInfo right_class;
    struct PropertyInfo prop1;
    struct PropertyInfo prop2;

    right_class.className = "Транспорт";
    prop1.propertyName = "Способ перемещения";
    prop1.valuesCount = 0;
    right_class.properties.append(prop1);
    rightClasses.append(right_class);

    parseInputFile(filePath, testClasses);
    for (int i = 0; i < testClasses.count(); i++)
    {
        QVERIFY2(isClassesEquals(testClasses[i], rightClasses[i]) == true, "Classes is not equal");
    }
}

void tests::parseInputFile_noClassesTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input3.txt";
    QList<ClassInfo> testClasses;

    parseInputFile(filePath, testClasses);

    QVERIFY2(testClasses.count() == 0, "Wrong classes count");
}

void tests::parseInputFile_noNumberTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input4.txt";
    QList<ClassInfo> testClasses;

    QVERIFY_EXCEPTION_THROWN(parseInputFile(filePath, testClasses), Error);
}

void tests::parseInputFile_wrongNumberTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input5.txt";
    QList<ClassInfo> testClasses;

    QVERIFY_EXCEPTION_THROWN(parseInputFile(filePath, testClasses), Error);
}

//////////////////////////////////////////////////////////////////////

// getHighestClasses tests

//////////////////////////////////////////////////////////////////////

void tests::getHighestClasses_complexTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input1.txt";
    QList<struct ClassInfo> classes;
    QList<struct ClassInfo> highestClasses;

    parseInputFile(filePath, classes);
    getHighestClasses(classes, highestClasses);

    QList<struct ClassInfo> right_highestClasses;
    ClassInfo right_class;
    PropertyInfo prop1;

    right_class.className = "Транспорт";
    prop1.propertyName = "Способ перемещения";
    prop1.valuesCount = 0;
    right_class.properties.append(prop1);
    right_highestClasses.append(right_class);

    QVERIFY2(right_highestClasses.count() == highestClasses.count(), "Wrong classes count");
    for (int i = 0; i < highestClasses.count(); i++)
    {
        QVERIFY2(isClassesEquals(highestClasses[i], right_highestClasses[i]) == true, "Classes is not equal");
    }
}

void tests::getHighestClasses_singleClassTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input2.txt";
    QList<struct ClassInfo> classes;
    QList<struct ClassInfo> highestClasses;

    parseInputFile(filePath, classes);
    getHighestClasses(classes, highestClasses);

    QList<struct ClassInfo> right_highestClasses;
    ClassInfo right_class;
    PropertyInfo prop1;

    right_class.className = "Транспорт";
    prop1.propertyName = "Способ перемещения";
    prop1.valuesCount = 0;
    right_class.properties.append(prop1);
    right_highestClasses.append(right_class);

    QVERIFY2(right_highestClasses.count() == highestClasses.count(), "Wrong classes count");
    for (int i = 0; i < highestClasses.count(); i++)
    {
        QVERIFY2(isClassesEquals(highestClasses[i], right_highestClasses[i]) == true, "Classes is not equal");
    }
}

void tests::getHighestClasses_multipleHighestClassesTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input6.txt";
    QList<struct ClassInfo> classes;
    QList<struct ClassInfo> highestClasses;

    parseInputFile(filePath, classes);
    getHighestClasses(classes, highestClasses);

    QList<struct ClassInfo> right_highestClasses;
    ClassInfo right_class;
    PropertyInfo prop1;

    right_class.className = "Воздушный";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {1};
    prop1.valuesCount = 1;
    right_class.properties.append(prop1);
    right_highestClasses.append(right_class);

    right_class.properties.clear();

    right_class.className = "Водный";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {2};
    prop1.valuesCount = 1;
    right_class.properties.append(prop1);
    right_highestClasses.append(right_class);

    QVERIFY2(right_highestClasses.count() == highestClasses.count(), "Wrong classes count");
    for (int i = 0; i < highestClasses.count(); i++)
    {
        QVERIFY2(isClassesEquals(highestClasses[i], right_highestClasses[i]) == true, "Classes is not equal");
    }
}

void tests::getHighestClasses_noClassesTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input3.txt";
    QList<struct ClassInfo> classes;
    QList<struct ClassInfo> highestClasses;

    parseInputFile(filePath, classes);
    getHighestClasses(classes, highestClasses);

    QList<struct ClassInfo> right_highestClasses;

    QVERIFY2(right_highestClasses.count() == highestClasses.count(), "Wrong classes count");
}

void tests::getHighestClasses_differentPropertyTypesTest()
{
    QString filePath = "C:\\Users\\user\\source\\_Conding_extra\\Kinpo\\Tests\\input7.txt";
    QList<struct ClassInfo> classes;
    QList<struct ClassInfo> highestClasses;

    parseInputFile(filePath, classes);
    getHighestClasses(classes, highestClasses);

    QList<struct ClassInfo> right_highestClasses;
    ClassInfo right_class;
    PropertyInfo prop1;

    right_class.className = "Водный";
    prop1.propertyName = "Способ перемещения";
    prop1.values = {1, 2, 3};
    prop1.valuesCount = 3;
    right_class.properties.append(prop1);
    right_highestClasses.append(right_class);

    QVERIFY2(right_highestClasses.count() == highestClasses.count(), "Wrong classes count");
    for (int i = 0; i < highestClasses.count(); i++)
    {
        QVERIFY2(isClassesEquals(highestClasses[i], right_highestClasses[i]) == true, "Classes is not equal");
    }
}
