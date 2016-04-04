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
 *  \file   source/aboutwindow.h
 *  \brief  Definition of the About window class
 *  \author Emigdio Z.Flores
 *  $Revision: 1.0 $
 *  $Date: 2016/04/04 $
 */

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class aboutwindow;
}

class aboutwindow : public QDialog {
    Q_OBJECT

public:
    explicit aboutwindow(QWidget* parent = 0);
    ~aboutwindow();

private:
    Ui::aboutwindow* ui;
};

#endif // ABOUTWINDOW_H
