/***************************************************************************
 *   Copyright (C) 2005 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
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
#include <QKeyEvent>
#include <QEvent>
#include <QWaitCondition>

#include "listlinpresupuestoview.h"
#include "blfunctions.h"
#include "blfixed.h"


///
/**
\param parent
\return
**/
ListLinPresupuestoView::ListLinPresupuestoView ( QWidget *parent ) : BfSubForm ( parent )
{
    _depura ( "ListLinPresupuestoView::ListLinPresupuestoView", 0 );
    setDbTableName ( "lpresupuesto" );
    setDbFieldId ( "idlpresupuesto" );
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "ListLinPresupuestoView_ListLinPresupuestoView", this );
    if ( res != 0 ) {
        return;
    } // end if
    addSubFormHeader ( "idarticulo", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView, _( "Id articulo" ) );
    addSubFormHeader ( "codigocompletoarticulo", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone, _( "Codigo completo" ) );
    addSubFormHeader ( "nomarticulo", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNoWrite, _( "Nombre del articulo" ) );
    addSubFormHeader ( "idlpresupuesto", BlDbField::DbInt, BlDbField::DbPrimaryKey, BlSubFormHeader::DbHideView, _( "No de linea" ) );
    addSubFormHeader ( "desclpresupuesto", BlDbField::DbVarChar, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _( "Descripcion" ) );
    addSubFormHeader ( "cantlpresupuesto", BlDbField::DbNumeric, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _( "Cantidad" ) );
    addSubFormHeader ( "pvplpresupuesto", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _( "Precio de venta s/IVA" ) );
    addSubFormHeader ( "ivalpresupuesto", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _( "% I.V.A." ) );
    addSubFormHeader ( "reqeqlpresupuesto", BlDbField::DbNumeric, BlDbField::DbNothing, BlSubFormHeader::DbNone, _( "% Recargo E.Q." ) );
    addSubFormHeader ( "descuentolpresupuesto", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _( "% Descuento" ) );
    addSubFormHeader ( "idpresupuesto", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite, _( "Id presupuesto" ) );
    addSubFormHeader ( "ordenlpresupuesto", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView, _( "Orden" ) );
    setinsercion ( TRUE );
    setOrdenEnabled ( TRUE );
    setOrdenPorQuery ( FALSE );

    /// Lanzamos los plugins
    g_plugins->lanza ( "ListLinPresupuestoView_ListLinPresupuestoView_Post", this );
    _depura ( "END ListLinPresupuestoView::ListLinPresupuestoView", 0 );
}


///
/**
\param idpresupuesto
**/
void ListLinPresupuestoView::cargar ( QString idpresupuesto )
{
    _depura ( "ListLinPresupuestoView::cargar", 0 );
    mdb_idpresupuesto = idpresupuesto;
    /// Al hacer la carge usamos el ordenlpresupuesto para indicar que el campo de ordenacion es el que toca.
    BlSubForm::cargar ( "SELECT * FROM lpresupuesto LEFT JOIN articulo ON lpresupuesto.idarticulo = articulo.idarticulo WHERE idpresupuesto = " + mdb_idpresupuesto + " ORDER BY ordenlpresupuesto" );
    _depura ( "END ListLinPresupuestoView::cargar", 0 );
}


