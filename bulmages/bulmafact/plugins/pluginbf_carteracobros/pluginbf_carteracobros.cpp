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

#include <stdio.h>
#include <QTime>
#include <QWidget>

#include "pluginbf_carteracobros.h"
#include "blmaincompany.h"
#include "blfunctions.h"
#include "carteracobroslist.h"

///
/**
**/
MyPluginCarteraCobros::MyPluginCarteraCobros()
{
    _depura ( "MyPluginCarteraCobros::MyPluginCarteraCobros", 0 );
    _depura ( "END MyPluginCarteraCobros::MyPluginCarteraCobros", 0 );
}

///
/**
**/
MyPluginCarteraCobros::~MyPluginCarteraCobros()
{
    _depura ( "MyPluginCarteraCobros::~MyPluginCarteraCobros", 0 );
    _depura ( "END MyPluginCarteraCobros::~MyPluginCarteraCobros", 0 );
}


///
/**
**/
void MyPluginCarteraCobros::elslot()
{
    _depura ( "MyPluginCarteraCobros::elslot", 0 );
    CarteraCobrosList *vehiculoview = new CarteraCobrosList ( ( BfCompany * ) m_conexionbase );
    m_bulmafact->workspace() ->addWindow ( vehiculoview );
    vehiculoview->show();
    _depura ( "END MyPluginCarteraCobros::elslot", 0 );
}


///
/**
\param bges
**/
void MyPluginCarteraCobros::inicializa ( BfBulmaFact *bges )
{
    _depura ( "MyPluginCarteraCobros::inicializa", 0 );
    /// Creamos el men&uacute;.
    m_conexionbase = bges->company();
    m_bulmafact = bges;

    /// Miramos si existe un menu Ventas
	QMenu *pPluginMenu = bges->newMenu("&Compras", "menuVentas", "menuMaestro");

    QAction *accion = new QAction ( "&Cartera de Cobros", 0 );
    accion->setStatusTip ( "Cartera de Cobros" );
    accion->setWhatsThis ( "Cartera de Cobros" );
    connect ( accion, SIGNAL ( activated() ), this, SLOT ( elslot() ) );
    /// A&ntilde;adimos la nueva opci&oacute;n al men&uacute; principal del programa.
    pPluginMenu->addSeparator();
    pPluginMenu->addAction ( accion );
	bges->Listados->addAction (accion);
    _depura ( "END MyPluginCarteraCobros::inicializa", 0 );
}






///
/**
\param bges
\return
**/
int entryPoint ( BfBulmaFact *bges )
{
    _depura ( "Punto de Entrada del plugin de Cartera de Cobros\n", 0 );
    MyPluginCarteraCobros *plug = new MyPluginCarteraCobros();
    plug->inicializa ( bges );
    return 0;
}


///
/**
\param art
\return
**/
int ClienteView_ClienteView_Post ( ClienteView *art )
{
    _depura ( "ArticuloView_ArticuloView", 0 );

    /// Agregamos el subformulario de validaciones.
    BfSubForm *l = new BfSubForm ( art );
    l->setObjectName ( QString::fromUtf8 ( "vencimientocliente" ) );
    l->setMainCompany ( art->mainCompany() );
    l->setDbTableName ( "vencimientocliente" );
    l->setDbFieldId ( "idvencimientocliente" );
    l->addSubFormHeader ( "idvencimientocliente", BlDbField::DbInt, BlDbField::DbPrimaryKey, BlSubFormHeader::DbHideView , QApplication::translate("TrabajadorView", "ID Vencimiento"));
    l->addSubFormHeader ( "diasvencimientocliente", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbNone , QApplication::translate ( "TrabajadorView", "Dias tras Factura" ) );
    l->addSubFormHeader ( "porcentajevencimientocliente", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbNone, QApplication::translate ( "TrabajadorView", "Porcentaje" ) );
    l->addSubFormHeader ( "descforma_pago", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone, QApplication::translate ( "TrabajadorView", "Forma de Pago" ) );
    l->addSubFormHeader ( "idcliente", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite , QApplication::translate ( "TrabajadorView", "Id Articulo" ) );
    l->addSubFormHeader ( "idforma_pago", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbNone, QApplication::translate ( "TrabajadorView", "ID Forma de Pago" ) );
    l->setInsert ( TRUE );
    l->setDelete ( TRUE );
    l->setSortingEnabled ( FALSE );
    art->dialogChanges_setQObjectExcluido ( l->mui_list );

    art->mui_tab->addTab ( l, "Vencimientos" );
    l->cargar("SELECT * FROM vencimientocliente WHERE idcliente IS NULL");
    _depura ( "END ArticuloView_ArticuloView", 0 );
    return 0;
}


///
/**
\param art
\return
**/
int ClienteView_cargarPost_Post ( ClienteView *art )
{
    _depura ( "ArticuloView_cargar", 0 );
    BfSubForm *l = art->findChild<BfSubForm *> ( "vencimientocliente" );
    if ( l ) {
        l->cargar ( "SELECT * FROM vencimientocliente LEFT JOIN forma_pago ON vencimientocliente.idforma_pago = forma_pago.idforma_pago WHERE idcliente =  " + art->dbValue("idcliente"));
    } // end if
    _depura ( "END ArticuloView_cargar", 0 );
    return 0;
}


void generarVencimientos (FacturaView *art) {
			BlDbRecordSet *cur1 = art->mainCompany()->loadQuery("SELECT totalfactura FROM factura WHERE idfactura = " + art->dbValue("idfactura"));
			mensajeInfo( "El total de la factura es :" + cur1->valor("totalfactura"));
			BlFixed contado("0.00");

			BlDbRecordSet *cur = art->mainCompany()->loadQuery("SELECT * FROM vencimientocliente WHERE idcliente = " + art->dbValue("idcliente"));
			while (!cur->eof())  {
				QString query = "SELECT ffactura + " + cur->valor("diasvencimientocliente") + " AS fechav, totalfactura / 100 * "+cur->valor("porcentajevencimientocliente")+" AS porcent FROM factura WHERE idfactura = " + art->dbValue("idfactura");
				if (cur->isLastRecord()) {
					query = "SELECT ffactura + " + cur->valor("diasvencimientocliente") + " AS fechav, totalfactura - "+ contado.toQString('.') +" AS porcent FROM factura WHERE idfactura = " + art->dbValue("idfactura");
				} //end if
				BlDbRecordSet *cur2 = art->mainCompany()->loadQuery(query);
				/// REALIZAMOS EL QUERY
				query = "INSERT INTO vencimientoc (idfactura, fechavencimientoc, cantvencimientoc, idforma_pago, refvencimientoc, idcliente) VALUES ("+art->dbValue("idfactura")+",'"+cur2->valor("fechav")+"',"+cur2->valor("porcent")+","+cur->valor("idforma_pago")+",'"+art->dbValue("reffactura")+"',"+art->dbValue("idcliente")+")";
				contado = contado + BlFixed(cur2->valor("porcent"));
				art->mainCompany()->runQuery(query);
				delete cur2;
				cur->nextRecord();
			} // end while
			delete cur;
			delete cur1;
}


///
/**
\param art
\return
**/
int BlForm_guardar_Post_Post ( BlForm *art )
{
    _depura ( "ArticuloView_guardar_post", 0 );
    try {

        BfSubForm *l = art->findChild<BfSubForm *> ( "vencimientocliente" );
	if (l) {
		l->setColumnValue ( "idcliente", art->dbValue ( "idcliente" ) );
		l->guardar();
        } // end if

	
	/* ES EL GUARDADO DE LA FACTURA */
        BfSubForm *l1 = art->findChild<BfSubForm *> ( "vencimientoc" );
	if (l1) {
		if (l1->rowCount() > 1) {

			QMessageBox msgBox;
			msgBox.setText("Hay Vencimientos generados para esta factura. Que desea hacer?");
			QPushButton *guardarButton = msgBox.addButton("Guardar", QMessageBox::ActionRole);
			QPushButton *regenerarButton = msgBox.addButton("Regenerar", QMessageBox::ActionRole);
			QPushButton *nadaButton = msgBox.addButton("Dejar Actuales", QMessageBox::ActionRole);
			msgBox.exec();
			if (msgBox.clickedButton() == guardarButton) {
				l1->setColumnValue ( "idfactura", art->dbValue ( "idfactura" ) );
				l1->setColumnValue ( "idcliente", art->dbValue ( "idcliente" ) );
				l1->guardar();
			} else if (msgBox.clickedButton() == regenerarButton) {
				QString query = "DELETE FROM vencimientoc WHERE idfactura="+ art->dbValue("idfactura");
				art->mainCompany()->runQuery(query);
				generarVencimientos( (FacturaView *)art);
			} // end if
		} else {
			generarVencimientos((FacturaView *)art);
		} // end if
        } // end if
        return 0;
    } catch ( ... ) {
        _depura ( "Hubo un error al guardar los vencimientos", 2 );
        return 0;
    } // end try
}




int FacturaView_FacturaView (FacturaView *factp) {
    _depura ( "ArticuloView_ArticuloView", 0 );
    /// Agregamos el subformulario de validaciones.
    BfSubForm *l = new BfSubForm ( factp );
    l->setObjectName ( QString::fromUtf8 ( "vencimientoc" ) );
    l->setMainCompany ( factp->mainCompany() );
    l->setDbTableName ( "vencimientoc" );
    l->setDbFieldId ( "idvencimientoc" );
    l->addSubFormHeader ( "idvencimientoc", BlDbField::DbInt, BlDbField::DbPrimaryKey, BlSubFormHeader::DbHideView , QApplication::translate("TrabajadorView", "ID Vencimiento"));
    l->addSubFormHeader ( "fechavencimientoc", BlDbField::DbDate, BlDbField::DbNotNull, BlSubFormHeader::DbNone , QApplication::translate ( "TrabajadorView", "Fecha" ) );
    l->addSubFormHeader ( "cantvencimientoc", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbNone, QApplication::translate ( "TrabajadorView", "Cantidad" ) );
    l->addSubFormHeader ( "descforma_pago", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone, QApplication::translate ( "TrabajadorView", "Forma de Pago" ) );
    l->addSubFormHeader ( "procesadovencimientoc", BlDbField::DbBoolean, BlDbField::DbNothing, BlSubFormHeader::DbNone, QApplication::translate ( "TrabajadorView", "Procesado" ) );
    l->addSubFormHeader ( "idfactura", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite , QApplication::translate ( "TrabajadorView", "Id Articulo" ) );
    l->addSubFormHeader ( "idforma_pago", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite, QApplication::translate ( "TrabajadorView", "ID Forma de Pago" ) );
    l->addSubFormHeader ( "idcliente", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite , QApplication::translate ( "Cliente", "Id Cliente" ) );
    l->setInsert ( TRUE );
    l->setDelete ( TRUE );
    l->setSortingEnabled ( FALSE );
    factp->dialogChanges_setQObjectExcluido ( l->mui_list );

    factp->m_desdfgs->addTab ( l, "Vencimientos" );
    l->cargar("SELECT * FROM vencimientoc WHERE idfactura IS NULL");
    _depura ( "END ArticuloView_ArticuloView", 0 );
    return 0;
}

///
/**
\param art
\return
**/
int FacturaView_cargarPost_Post ( FacturaView *art )
{
    _depura ( "FacturaView_cargarPost_Post", 0 );

    /// Para que funcione el identificador de factura debe ser valido
    if (art->dbValue("idfactura") != "") {

	BfSubForm *l = art->findChild<BfSubForm *> ( "vencimientoc" );
	if ( l ) {
		l->cargar ( "SELECT * FROM vencimientoc LEFT JOIN forma_pago ON vencimientoc.idforma_pago = forma_pago.idforma_pago WHERE idfactura =  " + art->dbValue("idfactura"));
	} // end if
    } // end if
    _depura ( "END FacturaView_cargarPost_Post", 0 );
    return 0;
}


///
/**
\param art
\return
**/
int FacturaView_borrarPre ( FacturaView *art )
{
    _depura ( "FacturaView_borrarPre", 0 );

    /// Para que funcione el identificador de factura debe ser valido
    if (art->dbValue("idfactura") != "") {

	BfSubForm *l = art->findChild<BfSubForm *> ( "vencimientoc" );
	if ( l ) {
		l->mainCompany()->runQuery ( "DELETE FROM vencimientoc WHERE idfactura =  " + art->dbValue("idfactura"));
	} // end if
    } // end if
    _depura ( "END FacturaView_borrarPre", 0 );
    return 0;
}