/***************************************************************************
 *   Copyright (C) 2006 by Arturo Martin Llado                             *
 *   amartin@conetxia.com                                                  *
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

#include <QWidget>
#include "impqtoolbutton.h"
#include "funcaux.h"

/// Necesarios para importacion de efactura
#include <QtXml/QDomDocument>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomNode>
#include <QString>
#include <QFileDialog>
#include <QMap>
#include <QList>
#include "facturapview.h"
#include "fixed.h"

#include "presupuestolist.h"
#include "presupuestoview.h"
#include "pedidosclientelist.h"
#include "pedidoclienteview.h"
#include "albaranclienteview.h"
#include "albaranclientelist.h"
#include "facturaview.h"
#include "company.h"
#include "dbrecord.h"


///
/**
\param pres
\param ped
\param alb
\param fac
\param parent
**/
ImpQToolButton::ImpQToolButton ( PresupuestoList *pres, PedidosClienteList *ped, AlbaranClienteList *alb,  FacturasList *fac , QWidget *parent ) : QToolButton ( parent )
{
    _depura ( "ImpQToolButton::ImpQToolButton", 0 );
    m_presupuestoList = pres;
    m_pedidosClienteList = ped;
    m_albaranClienteList = alb;
    m_facturasList = fac;

    setBoton();
    _depura ( "END ImpQToolButton::ImpQToolButton", 0 );
}


///
/**
**/
ImpQToolButton::~ImpQToolButton()
{
    _depura ( "ImpQToolButton::~ImpQToolButton", 0 );
    _depura ( "END ImpQToolButton::~ImpQToolButton", 0 );
}


///
/**
**/
void ImpQToolButton::setBoton()
{
    _depura ( "ImpQToolButton::setBoton", 0 );
    connect ( this, SIGNAL ( clicked() ), this, SLOT ( click() ) );
    setObjectName ( QString::fromUtf8 ( "exporta1" ) );
    setStatusTip ( "Facturar elementos seleccionados" );
    setToolTip ( "Facturar elementos seleccionados" );
    setMinimumSize ( QSize ( 32, 32 ) );
    setIcon ( QIcon ( QString::fromUtf8 ( ":/Bulmafact48x48/images/png/48x48/i_bulmages_ventas_facturas.48x48.png" ) ) );
    setIconSize ( QSize ( 22, 22 ) );
    _depura ( "END ImpQToolButton::setBoton", 0 );
}


///
/**
**/
void ImpQToolButton::click()
{
    _depura ( "ImpQToolButton::click", 0 );

    QString res = "";

    if ( m_albaranClienteList != NULL ) {
        m_companyact = ( Company * ) m_albaranClienteList->empresaBase();
        SubForm3 *sub = m_albaranClienteList->mui_list;

        /// Creamos la factura
				/// Como estamos en un plugin buscamos nuevas formas de creacion de objetos.
				int resur = g_plugins->lanza ("SNewFacturaView", m_companyact);
				if (!resur) {
					mensajeInfo("no se pudo crear instancia de factura");
					return;
				} // end if
				FacturaView *fac = (FacturaView *) g_plugParams;
        m_companyact->m_pWorkspace->addWindow ( fac );

        /// Cargamos un elemento que no existe para inicializar bien la clase.
        fac->cargar ( "0" );

        /// Reseteamos los valores
        for ( int i = 0; i < sub->rowCount(); i++ ) {
            SDBRecord *rec = sub->lineaat ( i );
            rec->refresh();
            QString val = rec->DBvalue ( "selector" );
            if ( val == "TRUE" ) {
                QString id = rec->DBvalue ( "idalbaran" );

			/// Como estamos en un plugin buscamos nuevas formas de creacion de objetos.
				int resur = g_plugins->lanza ("SNewAlbaranClienteView", m_companyact);
				if (!resur) {
					mensajeInfo("no se pudo crear instancia de albaran");
					return;
				} // end if
                    AlbaranClienteView *pres = (AlbaranClienteView *) g_plugParams;
                pres->cargar ( id );
                if ( pres->mui_procesadoalbaran->isChecked() ) {
                    pres->close();
                    return;
                } // end if
                m_companyact->pWorkspace() ->addWindow ( pres );
                m_companyact->meteWindow ( pres->windowTitle(), pres, FALSE );
                pres->show();

                // El calculo de descuentos es complejo
                Fixed descgen1 = pres->getlistadescuentos() ->sumarCampo ( "proporciondalbaran" );
                Fixed descgen = Fixed ( "1.000" ) - descgen1 / Fixed ( "100" );

                /// Agregamos a comentarios que albaran se corresponde.
                QString comm = fac->DBvalue ( "comentfactura" ) + "(" + tr ( "ALBARAN: Num " ) + pres->DBvalue ( "numalbaran" ) + tr ( "Ref:" ) + " " + pres->DBvalue ( "refalbaran" ) + tr ( "Fecha:" ) + " " + pres->DBvalue ( "fechaalbaran" ) + ")\n";
                fac->setDBvalue ( "comentfactura", comm );
                fac->setDBvalue ( "idforma_pago", pres->DBvalue ( "idforma_pago" ) );
                fac->setDBvalue ( "reffactura", pres->DBvalue ( "refalbaran" ) );
                fac->setDBvalue ( "idcliente", pres->DBvalue ( "idcliente" ) );
                fac->setDBvalue ( "idalmacen", pres->DBvalue ( "idalmacen" ) );

                QString l;
                SDBRecord *linea, *linea1;
                for ( int i = 0; i < pres->getlistalineas() ->rowCount(); ++i ) {
                    linea = pres->getlistalineas() ->lineaat ( i );
                    if ( linea->DBvalue ( "idarticulo" ) != "" ) {
                        linea1 = fac->getlistalineas() ->lineaat ( fac->getlistalineas() ->rowCount() - 1 );
                        /// Haciendo el nuevo registro antes nos evitamos problemas de foco.
                        fac->getlistalineas() ->nuevoRegistro();
                        fac->getlistalineas() ->setProcesarCambios ( FALSE );
                        linea1->setDBvalue ( "codigocompletoarticulo", linea->DBvalue ( "codigocompletoarticulo" ) );
                        linea1->setDBvalue ( "desclfactura", linea->DBvalue ( "desclalbaran" ) );
                        linea1->setDBvalue ( "cantlfactura", linea->DBvalue ( "cantlalbaran" ) );
                        linea1->setDBvalue ( "pvplfactura", linea->DBvalue ( "pvplalbaran" ) );
                        linea1->setDBvalue ( "ivalfactura", linea->DBvalue ( "ivalalbaran" ) );
                        Fixed descpar1 = Fixed ( linea->DBvalue ( "descuentolalbaran" ) );
                        Fixed descpar = Fixed ( "1.000" ) - descpar1 / Fixed ( "100" );
                        Fixed desc = ( Fixed ( "1.00" ) - descpar * descgen ) * Fixed ( "100.00" );
                        linea1->setDBvalue ( "descuentolfactura", desc.toQString ( '.' ) );
                        linea1->setDBvalue ( "idarticulo", linea->DBvalue ( "idarticulo" ) );
                        linea1->setDBvalue ( "nomarticulo", linea->DBvalue ( "nomarticulo" ) );
                        fac->getlistalineas() ->setProcesarCambios ( TRUE );
                        linea1->refresh();
                    } // end if
                } // end for

                pres->mui_procesadoalbaran->setChecked ( TRUE );
            } // end if
        } // end for

        fac->calculaypintatotales();
        fac->pintar();
        fac->show();

    } // end if

    _depura ( "END ImpQToolButton::click", 0 );
}
