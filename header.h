#pragma once

#include <QString>
#include <QList>

/*!
 * Информация о свойствах класса
 */
struct PropertyInfo
{
    QString propertyName; /*! Название свойства */
    QList<int> values;    /*! Список значений */
    int valuesCount;      /*! Количество значений */
};

/*!
 * Информация о классе
 */
struct ClassInfo
{
    QString className;              /*! Название класса */
    QList<PropertyInfo> properties; /*! Список свойств класса */
    int hierarchyNumber;            /*! Номер класса в иерархии */
    QList<ClassInfo> childClasses;  /*! Список дочерних классов */
};

/*!
 * Описание ошибки
 */
struct Error
{
    QString errorText;
    int errorCode;
};

/*!
 * Функция для парсинга входного файла
 *
 * @param[in] inputFile путь к входному файлу (.txt)
 * @param[out] classes  список классов, которые будут получены из входного файла
 */
void parseInputFile(QString inputFile, QList<ClassInfo> &classes);

/*!
 * Функция для парсинга одной строки входного файла
 *
 * @param[in] string    одна строка входного файла
 * @param[out] classs   информация о текущем классе, полученная из данной строки
 */
void parseString(QString string, struct ClassInfo &classs);

/*!
 * Получить список наивысших классов в иерархии
 *
 * @param[in] classes           список всех классов
 * @param[out] highestClasses   список наивысших классов иерархии
 */
void getHighestClasses(QList<struct ClassInfo> &classes, QList<struct ClassInfo> &highestClasses);

/*!
 * Получить список классов с данными свойствами
 *
 * @param[in] propertyNames             список названий свойств
 * @param[in] classes                   список всех классов
 * @param[out] classesWithGivenProperty список классов с данными свойствами
 */
void getClassesWithGivenProperties(QList<QString> propertyNames, QList<struct ClassInfo> &classes, QList<struct ClassInfo> &classesWithGivenProperty);

/*!
 * Проверить, равны ли свойства двух классов
 *
 * @param[in] class1        первый класс для сравнения
 * @param[in] class2        второй класс для сравнения
 * @param[in] propertyName  название свойства для сравнения
 * @return                  равны ли свойства двух классов
 */
bool IsClassPropertiesEqual(struct ClassInfo &class1, struct ClassInfo &class2, QString propertyName);

/*!
 * Распределить классы по вертикальной иерархии
 *
 * @param[in|out] classes   список классов
 */
void splitByHierarchy(QList<struct ClassInfo> &classes);

/*!
 * Распределить классы по "родственным" связям, т.е. определить связи между предками и потомками
 *
 * @param[in|out] classes   список классов
 */
void splitByRelationship(QList<struct ClassInfo> &classes);

/*!
 * Записать информацию о распределенных классах в выходной XML файл
 *
 * @param[in] classes       список классов
 * @param[out] outputFile   путь к выходному файлу (.xml)
 */
void writeToXML(QList<struct ClassInfo> &classes, QString outputFile);

/*!
 * Записать информацию об одном классе в список xml-формата
 *
 * @param[in] classs                    список классов
 * @param[in|out] outputXML                 список XML-формата
 * @param[int|out] closedTagsStringIndexes   индексы строк с закрытыми тегами
 */
void writeClassToXML(struct ClassInfo &classs, QList<QString> &outputXML, QList<int> &closedTagsStringIndexes);
