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
 *  \file   source/worker.cpp
 *  \brief  Main thread for GP process
 *  \author Emigdio Z.Flores
 *  $Revision: 1.0 $
 *  $Date: 2016/04/04 $
 */

#include "worker.h"
#include <QTimer>
#include <QEventLoop>
#include <vector>
#include <QThread>
#include <QDebug>

Worker::Worker(QObject* parent)
    : QObject(parent)
{
    _working = false;
    _abort = false;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug() << "Request worker start in Thread " << thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug() << "Request worker aborting in Thread " << thread()->currentThreadId();
    }
    mutex.unlock();
}

void Worker::doWork()
{
    qDebug() << "Starting worker process in Thread " << thread()->currentThreadId();
    mutex.lock();
    bool abort = _abort;
    mutex.unlock();
    if (abort) {
        qDebug() << "Aborting worker process in Thread " << thread()->currentThreadId();
    }
    start_main();
    mutex.lock();
    _working = false;
    mutex.unlock();
    qDebug() << "Worker process finished in Thread " << thread()->currentThreadId();
    emit finished();
}

void Worker::subsetData(double* input, double* training, double* testing, int cols, int rows, int trainsize, int* index)
{
    double rowV;
    int j;

    // Training partition
    for (unsigned int ind = 0; ind < trainsize; ind++) {
        j = index[ind];
        for (unsigned int k = 0; k < cols; k++) {
            rowV = input[(k * rows) + j];
            training[(k * trainsize) + ind] = rowV;
        }
    }

    // Testing partition
    for (unsigned int ind = 0; ind < (rows - trainsize); ind++) {
        j = index[trainsize + ind];
        for (unsigned int k = 0; k < cols; k++) {
            rowV = input[(k * rows) + j];
            testing[(k * (rows - trainsize)) + ind] = rowV;
        }
    }
}

void Worker::suspend()
{
    toSuspend = true;
}

void Worker::resume()
{
    if (!toSuspend)
        return;
    toSuspend = false;
    mutex.lock();
    waitCondition.wakeOne();
    mutex.unlock();
}

void Worker::ResumeRequested()
{
    while (!fitnessValidFinished);
    qDebug() << "Resume requested";
    resume();
}
