/***************************************************************************
 *   Copyright (C) 2004 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   Copyright (C) 2006 by Fco. Javier M. C. (Porting to QT4)              *
 *   fcojavmc@todo-redes.com                                               *
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

#include <QMessageBox>
#include <QWidget>
#include <QComboBox>
#include <QToolButton>
#include <QTextStream>
#include <QLayout>
#include <QMessageBox>
#include <fstream>

#include "listseriefacturaview.h"
#include "bfcompany.h"
#include "blconfiguration.h"
#include "busquedafecha.h"
#include "blfunctions.h"


///
/**
\param comp
\param parent
**/
ListSerieFacturaView::ListSerieFacturaView ( BfCompany *comp, QWidget *parent )
        : FichaBf ( comp, parent )
{
    _depura ( "INIT_ListSerieFacturaView::ListSerieFacturaView", 1 );
    setTitleName ( _( "Serie de Factura" ) );
    setDbTableName ( "serie_factura" );
    setAttribute ( Qt::WA_DeleteOnClose );
    setupUi ( this );
    mui_listado->setMainCompany ( comp );
    mui_listado->cargar();
    meteWindow ( windowTitle(), this );
    _depura ( "END_ListSerieFacturaView::ListSerieFacturaView", 1 );
}


///
/**
**/
ListSerieFacturaView::~ListSerieFacturaView()
{
    _depura ( "ListSerieFacturaView::~ListSerieFacturaView", 0 );
    _depura ( "END ListSerieFacturaView::~ListSerieFacturaView", 0 );
}


/// ===================================== SUBFORMULARIO ===============================================
///
/**
\param parent
**/
ListSerieFacturaSubForm::ListSerieFacturaSubForm ( QWidget *parent ) : BfSubForm ( parent )
{
    _depura ( "ListSerieFacturaSubForm::ListSerieFacturaSubForm", 0 );
    setDbTableName ( "serie_factura" );
    setDbFieldId ( "codigoserie_factura" );
    addSubFormHeader ( "codigoserie_facturaorig", BlDbField::DBvarchar, BlDbField::DBDupPrimaryKey | BlDbField::DBNoSave, BlSubFormHeader::DBNoView | BlSubFormHeader::DBBlockView, "codigoserie_factura" );
    addSubFormHeader ( "codigoserie_factura", BlDbField::DBvarchar, BlDbField::DBNotNull, BlSubFormHeader::DBNone, _( "Codigo serie factura" ) );
    addSubFormHeader ( "descserie_factura", BlDbField::DBvarchar, BlDbField::DBNotNull, BlSubFormHeader::DBNone, _( "Descripcion serie factura" ) );
    setinsercion ( TRUE );
    _depura ( "END ListSerieFacturaSubForm::ListSerieFacturaSubForm", 0 );
}
