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
 *  \file   source/node.cpp
 *  \brief  Painter for GP tree nodes
 *  \author Emigdio Z.Flores
 *  $Revision: 1.0 $
 *  $Date: 2016/04/04 $
 */

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(GraphWidget* graphWidget)
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge* edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge*> Node::edges() const
{
    return edgeList;
}

bool Node::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-20 - adjust, -20 - adjust, 43 + adjust, 43 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 40, 40);
    return path;
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    if (option->state & QStyle::State_Sunken) {
        painter->setBrush(QColor(255, 105, 156, 255));
    }
    else {
        painter->setBrush(QColor(0, 173, 250, 255));
    }
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-20, -20, 40, 40);

    if (!nameNode.isEmpty()) {
        QRectF textRect(-20, -20, 40, 40);
        QFont font = painter->font();
        font.setBold(false);
        font.setPointSize(14);
        painter->setFont(font);
        painter->setPen(Qt::white);
        bool ok;
        double number = nameNode.toDouble(&ok);
        if (!ok)
            painter->drawText(textRect, Qt::AlignCenter, GraphWidget::tr(nameNode.toLatin1()));
        else { // is a number
            painter->drawText(textRect, Qt::AlignCenter, GraphWidget::tr(QString::number(number, 'g', 2).toLatin1()));
        }
    }
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge* edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        update();
        QGraphicsItem::mousePressEvent(event);
    }
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        update();
        QGraphicsItem::mouseReleaseEvent(event);
    }
}
