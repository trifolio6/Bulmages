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

#include "pluginfacturar.h"
#include "blfunctions.h"
#include "impqtoolbutton.h"


///
/**
\return
**/
int entryPoint ( Bulmafact * )
{
    _depura ( "Estoy dentro del plugin de facturar", 0 );

    /// Inicializa el sistema de traducciones 'gettext'.
    setlocale(LC_ALL, "");
    bindtextdomain ("pluginfacturar", confpr->valor(CONF_DIR_TRADUCCION).toAscii().constData());

    return 0;
}


///
/**
\return
**/
int AlbaranClienteListSubform_AlbaranClienteListSubform ( AlbaranClienteListSubform *l )
{
    _depura ( "AlbaranClienteListSubform_AlbaranClienteListSubform", 0 );
    if ( !l->existsHeader ( "selector" ) ) {
        l->addSubFormHeader ( "selector", BlDbField::DbBoolean, BlDbField::DbNoSave | BlDbField::DbNoLoad, BlSubFormHeader::DbNone | BlSubFormHeader::DbNoWrite, "selector" );
    } // end if
    _depura ( "END AlbaranClienteListSubform_AlbaranClienteListSubform", 0 );
    return 0;
}


///
/**
\param l
\return
**/
int AlbaranClienteList_AlbaranClienteList ( AlbaranClienteList *l )
{
    _depura ( "AlbaranClienteList_AlbaranClienteList", 0 );
    ImpQToolButton *imp = new ImpQToolButton ( NULL,  NULL, l, NULL, l->mui_plugbotones );

    QHBoxLayout *m_hboxLayout1 = l->mui_plugbotones->findChild<QHBoxLayout *> ( "hboxLayout1" );
    if ( !m_hboxLayout1 ) {
        m_hboxLayout1 = new QHBoxLayout ( l->mui_plugbotones );
        m_hboxLayout1->setSpacing ( 5 );
        m_hboxLayout1->setMargin ( 5 );
        m_hboxLayout1->setObjectName ( QString::fromUtf8 ( "hboxLayout1" ) );
    } // end if
    m_hboxLayout1->addWidget ( imp );

    _depura ( "END AlbaranClienteList_AlbaranClienteList", 0 );
    return 0;
}
