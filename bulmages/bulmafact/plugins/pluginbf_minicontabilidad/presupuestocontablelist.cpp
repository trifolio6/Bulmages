/***************************************************************************
 *   Copyright (C) 2004 by J. M. Estopa Rey                                *
 *   pepma@telefonica.net                                                  *
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

#include <QLineEdit>
#include <QTextStream>
#include <QFileDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QMenu>

#include "presupuestocontablelist.h"
#include "presupuestocontableview.h"
#include "bfcompany.h"
#include "blfunctions.h"
#include "blimportexport.h"
#include "bfinformereferencia.h"
#include "blplugins.h"


/** Inicializa todos los componentes del listado.
    Hace una presentacion inicial.
    Mete la ventana en el workSpace si estamos en modo edicion.
*/
PresupuestoContableList::PresupuestoContableList ( BfCompany *comp, QWidget *parent, Qt::WFlags flag, edmode editmode )
        : BlFormList ( comp, parent, flag, editmode ), BlImportExport ( comp )
{
    _depura ( "PresupuestoContableList::PresupuestoContableList", 0 );
    setupUi ( this );

    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "PresupuestoContableList_PresupuestoContableList", this );
    if ( res != 0 )
        return;

    mui_list->setMainCompany ( comp );
    setSubForm ( mui_list );
    mdb_idpresupuestocontable = "";
    mdb_conceptopresupuestocontable = "";
    hideBusqueda();
    /// Si estamos en el modo edici&oacute;n metemos la ventana en el workSpace.
    if ( modoEdicion() ) {
        mainCompany() ->meteWindow ( windowTitle(), this );
    } else {
        setWindowTitle ( _ ( "Selector de presupuesto contable" ) );
        mui_editar->setHidden ( TRUE );
        mui_crear->setHidden ( TRUE );
        mui_borrar->setHidden ( TRUE );
        mui_imprimir->setHidden ( TRUE );
    } // end if
    presentar();
    /// Hacemos el tratamiento de los permisos que desabilita botones en caso de no haber suficientes permisos.
    trataPermisos ( "presupuestocontable" );
    _depura ( "END PresupuestoContableList::PresupuestoContableList", 0 );
}


/** No requiere acciones especiales en el destructor de la clase.
*/
PresupuestoContableList::~PresupuestoContableList()
{
    _depura ( "PresupuestoContableList::~PresupuestoContableList", 0 );
    _depura ( "END PresupuestoContableList::~PresupuestoContableList", 0 );
}


/** Todo el listado de presupuestocontables lo presenta el Subformulario mui_list del tipo ListLinPresupuestoContable.
*/
/// \TODO: Mejorar el sistema de filtrado incluyendo una funcion de generar Filtro.
void PresupuestoContableList::presentar()
{
    _depura ( "PresupuestoContableList::presenta", 0 );
    mui_list->cargar ( "SELECT * FROM presupuestocontable  WHERE lower(conceptopresupuestocontable) LIKE lower('%" + m_filtro->text() + "%') ORDER BY conceptopresupuestocontable" );
    _depura ( "END PresupuestoContableList::presenta", 0 );
}


/** LA accion de editar tiene una doble vertiente dependiendo del modo en que se ha abierto la ventana.
    Modo Edicion:
 - Crea una instancia de PresupuestoContableView, lo inicializa y lo presenta.
    Modo Seleccion:
 - Establece cual es el elemento seleccionado y se cierra la ventana para devolver el control.
*/
void PresupuestoContableList::editar ( int row )
{
    _depura ( "PresupuestoContableList::editar", 0 );
    mdb_idpresupuestocontable = mui_list->dbValue ( "idpresupuestocontable", row );
    mdb_conceptopresupuestocontable = mui_list->dbValue ( "conceptopresupuestocontable", row );
    if ( modoEdicion() ) {
        PresupuestoContableView * prov = new PresupuestoContableView ( ( BfCompany * ) mainCompany(), 0 ) ;
        if ( prov->cargar ( mdb_idpresupuestocontable ) ) {
            delete prov;
            return;
        } // end if
        mainCompany() ->m_pWorkspace->addWindow ( prov );
        prov->show();
    } else {
        emit ( selected ( mdb_idpresupuestocontable ) );
    } // end if
    _depura ( "END PresupuestoContableList::editar", 0 );
}


/** SLOT que responde a la pulsacion del boton imprimir.
    La impresion de listados esta completamente delegada a SubForm3
*/
void PresupuestoContableList::imprimir()
{
    _depura ( "PresupuestoContableList::on_mui_imprimir_released", 0 );
    mui_list->imprimirPDF ( _ ( "Listado de Presupuestos Contables" ) );
    _depura ( "PresupuestoContableList::on_mui_imprimir_released", 0 );
}



/** SLOT que responde a la pulsacion del boton borrar.
    Instancia la clase PresupuestoContableView, lo inicializa con el presupuestocontable seleccionado y le lanza el evento de borrar.
    Esta es la forma adecuada de borrar desde el listado ya que asi preservamos el tema plugins.
*/
void PresupuestoContableList::borrar()
{
    _depura ( "PresupuestoContableList::on_mui_borrar_released", 0 );
    try {
        QString idpresupuestocontable = mui_list->dbValue ( "idpresupuestocontable" );
        PresupuestoContableView *cli = new PresupuestoContableView ( ( BfCompany * ) mainCompany(), 0 ) ;
        if ( cli->cargar ( idpresupuestocontable ) ) {
            delete cli;
            throw - 1;
        } // end if
        cli->on_mui_borrar_released();
        delete cli;
        presentar();
    } catch ( ... ) {
        mensajeInfo ( _ ( "Error al borrar un presupuestocontable" ) );
    } // end try
    _depura ( "END:PresupuestoContableList::on_mui_borrar_released", 0 );
}



/** Devuelve el identificador del presupuestocontable seleccionado
**/
QString PresupuestoContableList::idpresupuestocontable()
{
    return mdb_idpresupuestocontable;
}

/** Devuelve el nombre del presupuestocontable seleccionado
**/
QString PresupuestoContableList::conceptopresupuestocontable()
{
    return mdb_conceptopresupuestocontable;
}


/** SLOT automatico que se ejecuta al pulsar sobre el boton de crear en la botonera
**/
void PresupuestoContableList::crear()
{
    PresupuestoContableView *bud = new PresupuestoContableView ( ( BfCompany * ) mainCompany() , 0 );
    mainCompany()->m_pWorkspace->addWindow ( bud );
    bud->inicializar();
    bud->pintar();
    bud->show();
    bud->setWindowTitle ( _ ( "Nuevo presupuestocontable" ) );
    /// Deshabilitamos las pestanyas que no se utilizan al crear un nuevo presupuestocontable.
    bud->desactivaDocumentos();
}


/** \TODO: REVISAR ESTE METODO YA QUE NO PARECE SER EL ADECUADO
    EN LA LLAMADA DE SUBMENUS
*/
void PresupuestoContableList::submenu ( const QPoint & )
{
    _depura ( "ArticuloList::on_mui_list_customContextMenuRequested", 0 );
    int a = mui_list->currentRow();
    if ( a < 0 )
        return;
    QMenu *popup = new QMenu ( this );
    QAction *edit = popup->addAction ( _ ( "Editar presupuestocontable" ) );
    QAction *del = popup->addAction ( _ ( "Borrar presupuestocontable" ) );
    QAction *opcion = popup->exec ( QCursor::pos() );
    if ( opcion == del )
        on_mui_borrar_released();
    if ( opcion == edit )
        on_mui_editar_released();
    delete popup;
}

/// =============================================================================
///                    SUBFORMULARIO
/// =============================================================================
/** PRepara el subformulario para trabajar con la tabla presupuestocontable.
    Establece que no se puedan insertar ni borrar lineas.
*/
PresupuestoContableListSubform::PresupuestoContableListSubform ( QWidget *parent, const char * ) : BfSubForm ( parent )
{
    _depura ( "PresupuestoContableListSubform::PresupuestoContableListSubform", 0 );
    setDbTableName ( "presupuestocontable" );
    setDbFieldId ( "idpresupuestocontable" );
    addSubFormHeader ( "idpresupuestocontable", BlDbField::DbInt, BlDbField::DbNotNull | BlDbField::DbPrimaryKey, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite, _ ( "ID presupuestocontable" ) );
    addSubFormHeader ( "fechapresupuestocontable", BlDbField::DbDate, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "Codigo" ) );
    addSubFormHeader ( "conceptopresupuestocontable", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, _ ( "C.I.F." ) );
    setInsert ( FALSE );
    setDelete ( FALSE );
    setSortingEnabled ( TRUE );
    _depura ( "END PresupuestoContableListSubform::PresupuestoContableListSubform", 0 );
}

PresupuestoContableListSubform::~PresupuestoContableListSubform()
{
    _depura ( "PresupuestoContableListSubform::~PresupuestoContableListSubform", 0 );
    _depura ( "END PresupuestoContableListSubform::~PresupuestoContableListSubform", 0 );
}