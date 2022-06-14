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
