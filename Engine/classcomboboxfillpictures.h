#ifndef CLASSCOMBOBOXFILLPICTURES_H
#define CLASSCOMBOBOXFILLPICTURES_H

#include <QComboBox>

class ClassComboBoxFillPictures
{
public:
    ClassComboBoxFillPictures();
    void AddIconsToCombobox(QComboBox *Combox);
    QIcon GetIconFor(int number);
};

#endif // CLASSCOMBOBOXFILLPICTURES_H
