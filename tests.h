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

    void getHighestClasses_complexTest();
    void getHighestClasses_singleClassTest();
    void getHighestClasses_multipleHighestClassesTest();
    void getHighestClasses_noClassesTest();
    void getHighestClasses_differentPropertyTypesTest();

    void getClassesWithGivenProperty_multipleClassesWithPropertyTest();
    void getClassesWithGivenProperty_singleClassWithPropertyTest();
    void getClassesWithGivenProperty_noClassesWithPropertyTest();
    void getClassesWithGivenProperty_noClassesTest();

    void IsClassPropertyEqualsToGiven_EqualPropertyTest();
    void IsClassPropertyEqualsToGiven_HasNoPropertyTest();
    void IsClassPropertyEqualsToGiven_UnequalPropertyTest();
    void IsClassPropertyEqualsToGiven_HighestLevelPropertyTest();

    void splitByHierarchy_complexTest();
    void splitByHierarchy_singleClassForOneLevelTest();
    void splitByHierarchy_multipleClassesForOneLevelTest();
    void splitByHierarchy_noClassesTest();
    void splitByHierarchy_singleClassTest();

    void splitByRelationship_singleClassTest();
    void splitByRelationship_noClassesTest();
    void splitByRelationship_multipleRelativesTest();
    void splitByRelationship_oneRelativeTest();
};

#endif // TESTS_H
