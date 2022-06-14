#include "tests.h"
#include <QtTest/QTest>
#include "header.h"

tests::tests(QObject *parent)
    : QObject(parent)
{

}

void tests::test1()
{
    QVERIFY2(2 == 2, "Wrong answer");
}
