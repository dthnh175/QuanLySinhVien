#pragma once
#include "Menu.h"
#include "Student.h"

Menu * createMainMenu();

Menu * createEditMenu();

Menu * createPrintMenu();

Menu * createSortFieldMenu();
Menu * createSortAlgoMenu();
enum SortKey  { NAME, DATE_OF_BIRTH, GPA, QUIT_SORTKEY_MENU };
enum SortAlgo { SELECTION, INSERTION, QUICK, MERGE, HEAP, QUIT_SORTALGO_MENU };

Menu * createSearchFieldMenu();
Menu * createSearchAlgoMenu();

Menu * createStatMenu();

Menu * createClassesMenu();

Menu * createStudentInfoMenu(Student * student);

