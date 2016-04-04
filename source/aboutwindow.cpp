/****************************************************************************
 * LeafGP
 *  Copyright (C) 2016 by Emigdio Z-Flores
 *  emigdioz@gmail.com
 *
 * $LEAFGP_BEGIN_LICENSE:LGPL$
 *
 * This work is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the license, or (at your option) any later version.
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * LICENSE.txt for more details.
 *
 * $LEAFGP_END_LICENSE$
 *
 * Contact:
 * Posgrado de Ciencias de la Ingenieria
 * Instituto Tecnologico de Tijuana
 * Tree-lab research group
 * http://www.tree-lab.org
 *
****************************************************************************/

/*!
 *  \file   source/aboutwindow.cpp
 *  \brief  About window class methods
 *  \author Emigdio Z.Flores
 *  $Revision: 1.0 $
 *  $Date: 2016/04/04 $
 */

#include "aboutwindow.h"
#include "ui_aboutwindow.h"

aboutwindow::aboutwindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::aboutwindow)
{
    ui->setupUi(this);
}

aboutwindow::~aboutwindow()
{
    delete ui;
}
