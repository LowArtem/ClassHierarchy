#pragma once

#include <QString>
#include <QList>
#include <QSet>
#include <QDomDocument>

/*!
 * Информация о свойствах класса
 */
struct PropertyInfo
{
    QString propertyName; /*! Название свойства */
    QSet<int> values;    /*! Список значений */
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
    QList<ClassInfo*> childClasses;  /*! Список дочерних классов */
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
 * Получить список классов с данным свойством
 *
 * @param[in] property                  свойство, по которому нужно искать классы
 * @param[in] classes                   список всех классов
 * @param[out] classesWithGivenProperty список классов с данным свойством
 */
void getClassesWithGivenProperty(struct PropertyInfo property, QList<struct ClassInfo> &classes, QList<struct ClassInfo> &classesWithGivenProperty);

/*!
 * Проверить, равно ли свойство класса данному
 *
 * @param[in] class         класс для сравнения
 * @param[in] property      свойство для сравнения
 * @return                  равны ли свойства
 */
bool IsClassPropertyEqualsToGiven(struct ClassInfo &classs, struct PropertyInfo property);

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
void splitByRelationship(QList<struct ClassInfo> &classes, int maxHierarchyNumber);

/*!
 * Записать информацию о распределенных классах в выходной XML файл
 *
 * @param[in] classes       список классов
 * @param[out] outputFile   путь к выходному файлу (.xml)
 */
void writeToXML(QList<struct ClassInfo> &classes, QString outputFile);

/*!
 * Записать информацию об одном классе в xml-объект
 *
 * @param[in] classs                         список классов
 * @param[in|out] root                       корневой элемент
 */
void writeClassToXML(struct ClassInfo classs, QDomElement &root, QDomDocument &xmlDocument);
