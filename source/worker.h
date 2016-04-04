#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>
#include <iostream>
#include <vector>
#include <QVector>
#include <QString>
#include <QWaitCondition>
#include "puppy_main.hpp"

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0);
    void requestWork();
    void abort();
    int start_main(void);

    unsigned int evaluateFitness(std::vector<Puppy::Tree>& ioPopulation,
                                 Puppy::Context& ioContext,
                                 double* inX,
                                 double* inF,int cols, int rows, std::vector<bool> &terSelection);

    unsigned int evaluateFitness_multithread(std::vector<Puppy::Tree>& ioPopulation,
                                 Puppy::Context& ioContext,
                                 double* inX,
                                 double* inF, int cols, int rows, std::vector<bool> &terSelection, bool multithread);

    unsigned int evaluateFitnessTesting(Puppy::Tree &individual,
                                 Puppy::Context& ioContext,
                                 double* inX,
                                 double* inF,int cols, int rows, std::vector<bool> &terSelection);

    unsigned int evaluateFitnessTraining(Puppy::Tree &individual,
                                 Puppy::Context& ioContext,
                                 double* inX,
                                 double* inF,int cols, int rows, std::vector<bool> &terSelection);
    int applyLS(Puppy::Tree &individual, Puppy::Context& ioContext, double* inX, double* inF, int cols, int rows, std::vector<bool> &terSelection, float &oriFit, float &optFit);

    int ngen;
    int popsize;
    int tournamentsize;
    int maxdepth;
    int mininitdepth;
    int maxinitdepth;
    float crossoverp;
    float crossoverdp;
    float mutationp;
    int mutationmaxr;
    int randomseed;
    double *dataset;
    int dataset_cols;
    int dataset_rows;
    double *dataset_training;
    double *dataset_testing;
    int trainingP;    
    bool LSactivated;
    bool multicore_activated;
    std::vector<bool> terminalselection;
    std::vector<bool> functionselection;    
    void subsetData(double *input, double *training, double *testing, int cols, int rows, int trainsize, int *index);
    typedef struct
    {
      double train;
      double test;
      double avgsize;
      double maxsize;
      double minsize;
      double gen;
    } Stats;

    typedef struct
    {
      QVector<QString> mName;
      QVector<int> mNumberArguments;
      QVector<int> mSubTreeSize;
      QVector<float> posX;
      QVector<float> posY;
      QVector<int> index;
    } TreeStruct;

    struct fitnessdata {
      double **data;
    };

    typedef struct {
        QVector<Puppy::Tree> bunchTrees;
        double* inX;
        double* inF;
        int cols;
        int rows;
        std::vector<bool> terSelection;
        Puppy::Context ioContext;
    }TreeContainer;

    typedef struct {
        Puppy::Tree selTree;
        double* inX;
        double* inF;
        int rows;
        int cols;
        std::vector<bool> terSelection;
        Puppy::Context ioContext;
    } OneTree;
    void suspend();
    void resume();
    QVector<Puppy::Tree> fitnessValid;
    bool fitnessValidFinished;
    TreeContainer wholePop;

private:
    bool _abort;
    bool _working;
    QMutex mutex;
    QString datar;
    bool toSuspend;
    QWaitCondition waitCondition;    

signals:
    void workRequested();
    void valueChanged(const QString &value);
    void send_stats(Worker::Stats data);
    void send_stats_end(Worker::Stats data);
    void send_tree(Worker::TreeStruct data);
    void progressChanged(const int value);
    void GPstarted(const QString value);
    void plot3DSendData(Worker::fitnessdata data);
    void sendEvalFunc(unsigned long value);
    void send_tree_string(const QString data);
    void send_tree_infix_string(const QString data);
    void send_tree_latex_string(const QString data);
    void finished();
    void requestFitnessCalc(const Worker::TreeContainer data);

public slots:
    void doWork();
    void ResumeRequested();
};

#endif // WORKER_H
