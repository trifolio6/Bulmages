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

#include <QWidget>

#include "comercialclienteview.h"
#include "funcaux.h"


///
/**
\param parent
**/
ComercialClienteView::ComercialClienteView ( QWidget *parent )
        : FichaBf ( NULL, parent )
{
    _depura ( "ComercialClienteView::ComercialClienteView", 0 );
    setupUi ( this );
    _depura ( "ENd ComercialClienteView::ComercialClienteView", 0 );
}


///
/**
**/
ComercialClienteView::~ComercialClienteView()
{
    _depura ( "ENd ~ComercialClienteView::ComercialClienteView", 0 );
}


///
/**
\param comp
**/
void ComercialClienteView::setEmpresaBase ( Company *comp )
{
    _depura ( "ComercialClienteView::setcompany", 0 );
    PEmpresaBase::setEmpresaBase ( comp );
    mui_idzonacomercial->setEmpresaBase ( comp );
    mui_idzonacomercial->setidzonacomercial ( "0" );
    _depura ( "END ComercialClienteView::setcompany", 0 );
}