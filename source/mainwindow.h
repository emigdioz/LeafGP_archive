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
 *  \file   source/mainwindow.h
 *  \brief  Definition of UI main window
 *  \author Emigdio Z.Flores
 *  $Revision: 1.0 $
 *  $Date: 2016/04/04 $
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QThread>
#include <QListWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QString>
#include <QLabel>
#include <QProgressBar>
#include <QDateTime>
#include <QDebug>
#include <QGraphicsView>
#include <QFontDatabase>
#include <QPixmap>
#include <QThread>
#include <QtConcurrentMap>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <math.h>
#include "worker.h"
#include "node.h"
#include "edge.h"
#include <qwt3d_gridplot.h>
#include <qwt3d_function.h>
#include <qwt3d_plot3d.h>
#include <qwt3d_scale.h>
#include <qcustomplot.h>
#include "aboutwindow.h"
#include "puppy_regprimitives.hpp"
#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "jkqtmathtext.h"
#include "puppy_main.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);
    Qwt3D::GridPlot* plot;
    ~MainWindow();
    void calculateQuartiles(std::vector<double> data, double& Q1, double& Q2, double& Q3, double& min, double& max, QVector<double>& outliers);
    double rollUniform(double inLow, double inUp);
    int runCount;
    int batchRun;
    QFutureWatcher<QVector<Puppy::Tree> > futureWatcher;
    Worker::OneTree tempTree;
    QVector<Worker::OneTree> allpop;
    QVector<Puppy::Tree> outpop;

private:
    QThread* thread;
    Worker* worker;
    Ui::MainWindow* ui;
    QList<QStringList> csv;
    QStandardItemModel* model;
    QList<QStandardItem*> standardItemList;
    bool GPthreadstarted;
    void setupPlots();
    double maxSize;
    double maxFitness;
    QGraphicsScene* scene;
    int countLeaves(int index, int count);
    void positionLeaves(int index, int depth);
    void positionParents(int index, int depth);
    int nLeaves;
    Worker::TreeStruct selectedTree;
    std::vector<Worker::TreeStruct> runTree;
    std::vector<Worker::Stats> runStats;
    QVector<QString> TreeString;
    QVector<QString> TreeStringInfix;
    QVector<QString> TreeStringLatex;
    void gen_benchmark(int selection);
    void populateTable();
    int plot3D_width1;
    int plot3D_width2;
    void initializePlots();
    QTimer* timerGP;
    QDateTime startedDateTime;
    void showStartedTime();
    void showStartedDate();
    QString seconds_to_DHMS(qint64 duration);
    void view_single_tree(Worker::TreeStruct data);
    QCPStatisticalBox* trainBox;
    QCPStatisticalBox* testBox;
    bool run_batch;
    bool openColorMap(Qwt3D::ColorVector& cv, QString fname);
    QVector<int> arity;
    QVector<int> depth;
    QVector<QString> name;
    QVector<int> subtreesize;
    QPixmap pixmap;
    aboutwindow* aboutDialog;
    bool fitnessFinished;

signals:
    void finishedCalc();

private slots:
    void runGP();
    void on_actionE_xit_triggered();
    void received_stats(Worker::Stats data);
    void received_stats_end(Worker::Stats data);
    void received_tree(Worker::TreeStruct data);
    void on_actionLoad_file_triggered();
    void checkString(QString& temp, QChar character = 0);
    void received_GPstarted(QString value);
    void thread_finished();
    void on_horizontalSlider_valueChanged(int value);
    void plot3DUpdateData(Worker::fitnessdata data);
    void receivedEvalFunc(unsigned long value);
    void on_ButtonStart_clicked();
    void on_ButtonStop_clicked();
    void on_listFunctions_itemSelectionChanged();
    void on_spinBox_valueChanged(int arg1);
    void on_lineEdit_5_textChanged(const QString& arg1);
    void on_lineEdit_9_textChanged(const QString& arg1);
    void on_lineEdit_4_textChanged(const QString& arg1);
    void on_lineEdit_6_textChanged(const QString& arg1);
    void on_lineEdit_8_textChanged(const QString& arg1);
    void on_lineEdit_10_textChanged(const QString& arg1);
    void on_lineEdit_7_textChanged(const QString& arg1);
    void on_lineEdit_11_textChanged(const QString& arg1);
    void on_lineEdit_12_textChanged(const QString& arg1);
    void on_lineEdit_13_textChanged(const QString& arg1);
    void received_tree_string(const QString data);
    void received_tree_infix_string(const QString data);
    void received_tree_latex_string(const QString data);
    void showElapsedTime();
    void on_listTerminals_itemSelectionChanged();
    void on_tableRuns_itemSelectionChanged();
    void on_ButtonBatch_clicked();
    void on_spinBoxRuns_valueChanged(int arg1);
    void ShowContextMenu(const QPoint& pos);
    void on_actionPrefix_syntax_triggered();
    void on_actionInfix_syntax_triggered();
    void on_actionKoza_1_triggered();
    void on_actionKoza_2_triggered();
    void on_actionKoza_3_triggered();
    void on_actionLatex_Syntax_triggered();
    void showRealTimePreview(const QImage& preview, bool latexerror);
    void on_actionAbout_triggered();
    void on_tableView_clicked(const QModelIndex& index);
    void showPointToolTip(QMouseEvent* event);
    void on_checkBox_toggled(bool checked);
    void on_checkBox_2_toggled(bool checked);
    void requestedFitnessCalc(Worker::TreeContainer data);
    void finished_fitness_calc();
};
#endif // MAINWINDOW_H
