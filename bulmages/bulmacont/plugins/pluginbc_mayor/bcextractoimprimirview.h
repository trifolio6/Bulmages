/***************************************************************************
 *   Copyright (C) 2003 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   Copyright (C) 2003 by Antoni Mirabete i Teres                         *
 *   amirabet@biada.org                                                    *
 *   http://www.iglues.org Asociación Iglues -- Contabilidad Linux         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef EXTRACTOPRINTVIEW_H
#define EXTRACTOPRINTVIEW_H

#include <errno.h>

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QRadioButton>

#include "blfunctions.h"
#include "ui_bcextractoimprimirbase.h"
#include "blwidget.h"


class BcCompany;


/// Clase que corresponde con la ventana de impresi&oacute;n de extractos.
/** \todo Falta hacer que en los campos se haga el autocompletado.
    \todo Falta incluir el filtrado en el extracto. */
class BC_EXPORT BcExtractoImprimirView : public QDialog, public Ui_BcExtractoImprimirBase, BlMainCompanyPointer
{
    Q_OBJECT

public:
    char *fichero;
    BcExtractoImprimirView ( BcCompany *, QWidget * );
    void presentar ( const QString &tipus );
    ~BcExtractoImprimirView();

private:
    QString montaQuery();

public slots:
    virtual void accept();
};

#endif
