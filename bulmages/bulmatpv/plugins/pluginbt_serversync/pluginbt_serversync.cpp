/***************************************************************************
 *   Copyright (C) 2005 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   Copyright (C) 2006 by Fco. Javier M. C.                               *
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

#include <QToolButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>

#include "pluginticketbasicoivainc.h"
#include "blfunctions.h"
#include "btticket.h"
#include "btcompany.h"
#include "mticketivainc.h"
#include "bldockwidget.h"

BlDockWidget *g_doc1 = NULL;
MTicketIVAInc *g_bud = NULL;

///
/**
\return
**/
int entryPoint ( BtBulmaTPV *tpv )
{
    _depura ( "pluginticketbasicoivainc::entryPoint", 0 );

    /// Inicializa el sistema de traducciones 'gettext'.
    setlocale(LC_ALL, "");
    bindtextdomain ("pluginticketbasicoivainc", g_confpr->valor(CONF_DIR_TRADUCCION).toAscii().constData());

    /// Vamos a probar con un docwindow.
    g_doc1 = new BlDockWidget ( "Ticket", tpv, "ticketbasico" );
    g_doc1->setFeatures ( QDockWidget::AllDockWidgetFeatures );
    
    g_doc1->setGeometry ( 100, 100, 100, 500 );
    g_doc1->resize ( 330, 400 );

    /// Presentamos el widget
    tpv->addDockWidget ( Qt::RightDockWidgetArea, g_doc1 );

    g_doc1->cargaconf();

    g_doc1->show();

    _depura ( "END pluginticketbasicoivainc::entryPoint", 0 );
    
    return 0;
}

///
/**
\return
**/
int exitPoint ( BtBulmaTPV *tpv )
{
    _depura ( "pluginticketbasicoivainc::exitPoint", 0 );
    
    delete g_doc1;
    
    _depura ( "END pluginticketbasicoivainc::exitPoint", 0 );
    
    return 0;
}

int BtCompany_createMainWindows_Post ( BtCompany *etpv )
{
    _depura ( "pluginticketbasicoivainc::BtCompany_createMainWindows_Post", 0 );
    
    g_bud =  new MTicketIVAInc ( etpv, g_doc1 );
    g_doc1->setWidget ( ( QWidget * ) g_bud );
    
    _depura ( "END pluginticketbasicoivainc::BtCompany_createMainWindows_Post", 0 );
    
    return 0;
}

int BtTicket_pintar ( BtTicket * )
{
    _depura ( "pluginticketbasicoivainc::BtTicket_pintar", 0 );
    
    if (g_bud) {
        g_bud->pintar();
    } // end if
    
    _depura ( "END pluginticketbasicoivainc::BtTicket_pintar", 0 );
    
    return 0;
}
