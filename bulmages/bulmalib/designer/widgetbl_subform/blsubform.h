#ifndef BLSUBFORM_H
#define BLSUBFORM_H

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>

#include <QtGui>
#include "../../src/ui_blsubformbase.h"


class QDESIGNER_WIDGET_EXPORT BlSubForm : public QWidget, public Ui_BlSubFormBase
{
    Q_OBJECT

public:
    BlSubForm(QWidget *parent = 0);

};

#endif
