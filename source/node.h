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
 *  \file   source/node.h
 *  \brief  Definition of GP tree nodes
 *  \author Emigdio Z.Flores
 *  $Revision: 1.0 $
 *  $Date: 2016/04/04 $
 */

#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QString>
#include <QGraphicsView>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Node : public QGraphicsItem {
public:
    Node(GraphWidget* graphWidget);
    void addEdge(Edge* edge);
    QList<Edge*> edges() const;
    enum { Type = UserType + 1 };
    int type() const Q_DECL_OVERRIDE { return Type; }
    bool advance();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;
    QString nameNode;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) Q_DECL_OVERRIDE;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    QList<Edge*> edgeList;
    QPointF newPos;
    GraphWidget* graph;
    bool _pan;
    int _panStartX, _panStartY;
};

#endif // NODE_H
