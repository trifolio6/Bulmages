/***************************************************************************
 *   Copyright (C) 2004 by Marcos Mezo                                     *
 *   mmezo@selexco.net                                                     *
 *   http://www.iglues.org                                                 *
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

#ifndef CLIENTEVIEW_H
#define CLIENTEVIEW_H

#include "fichabf.h"
#include "ui_clientebase.h"


/** Clase que se encarga de la pantalla de cliente.
    Deriva de la clase FichaBf para la estandarizacion de pantallas y
    de la clase Cliente para el manejo con la base de datos.
    Se encarga de recibir y lanzar eventos.
*/
class ClienteView : public FichaBf, public Ui_ClienteBase
{
    Q_OBJECT

public:
    ClienteView ( Company *emp, QWidget *parent = 0 );
    ~ClienteView();

public:
    int cargarPost ( QString client );
    void activaDocumentos();
    void desactivaDocumentos();

public slots:
    /// \TODO: Muchos metodos aqui implementados deberian estar en Ficha.
    virtual void on_mui_informe_clicked();
    virtual void on_mui_cifcliente_lostFocus();
};

#endif
