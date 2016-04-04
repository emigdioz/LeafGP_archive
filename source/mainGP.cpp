#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <QVector>
#include <QString>
#include <sstream>
#include <QDebug>
#include <algorithm>
#include <QtConcurrent>
#include <QMap>

#include "puppy_main.hpp"
#include "puppy_regprimitives.hpp"
#include "mainwindow.h"
#include "worker.h"
#include "matrix.h"
#include <levmar.h>

#define POP_SIZE_DEFAULT 100
#define NBR_GEN_DEFAULT 100
#define NBR_PART_TOURNAMENT_DEFAULT 10
#define MAX_DEPTH_DEFAULT 17
#define MIN_INIT_DEPTH_DEFAULT 2
#define MAX_INIT_DEPTH_DEFAULT 5
#define INIT_GROW_PROBA_DEFAULT 0.5f
#define CROSSOVER_PROBA_DEFAULT 0.9f
#define CROSSOVER_DISTRIB_PROBA_DEFAULT 0.9f
#define MUT_STD_PROBA_DEFAULT 0.05f
#define MUT_MAX_REGEN_DEPTH_DEFAULT 5
#define MUT_SWAP_PROBA_DEFAULT 0.05f
#define MUT_SWAP_DISTRIB_PROBA_DEFAULT 0.5f
#define SEED_DEFAULT 0

using namespace Puppy;

// unsigned int evaluateFitness(std::vector<Tree>& ioPopulation,
//                             Context& ioContext,
//                             double* inX,
//                             double* inF,int cols, int rows, std::vector<bool>
//                             &terSelection);

// unsigned int evaluateFitness_multithread(std::vector<Tree>& ioPopulation,
//                             Context& ioContext,
//                             double* inX,
//                             double* inF, int cols, int rows,
//                             std::vector<bool> &terSelection, bool
//                             multithread);

// unsigned int evaluateFitnessTesting(Tree &individual,
//                             Context& ioContext,
//                             double* inX,
//                             double* inF,int cols, int rows, std::vector<bool>
//                             &terSelection);

// unsigned int evaluateFitnessTraining(Tree &individual,
//                             Context& ioContext,
//                             double* inX,
//                             double* inF,int cols, int rows, std::vector<bool>
//                             &terSelection);

// int applyLS(Tree &individual, Context& ioContext, double* inX, double* inF,
// int cols, int rows, std::vector<bool> &terSelection, float &oriFit, float
// &optFit);
void objFunc(double* p, double* x, int m, int n, void* data);

//struct OneTree {
//    Tree selTree;
//    double* inX;
//    double* inF;
//    int rows;
//    int cols;
//    std::vector<bool> terSelection;
//    Context ioContext;
//};

int single_ind_fitness(const int &ind);
void reduce(QVector<Tree>& result, const Tree& partial);
int mapfunction(const int &ind);
//Tree mapIndividual(const OneTree &element);
//QVector<Tree> start_fit_check(QVector<OneTree> all);

/*!
 *  \brief Program main routine.
 *  \param argc Number of arguments given on the command-line.
 *  \param argv Command-line arguments.
 *  \ingroup SymbReg
 */
int Worker::start_main(void)
{
    // Create parameter variables with default values.
    unsigned int lPopSize = POP_SIZE_DEFAULT;
    unsigned int lNbrGen = NBR_GEN_DEFAULT;
    unsigned int lNbrPartTournament = NBR_PART_TOURNAMENT_DEFAULT;
    unsigned int lMaxDepth = MAX_DEPTH_DEFAULT;
    unsigned int lMinInitDepth = MIN_INIT_DEPTH_DEFAULT;
    unsigned int lMaxInitDepth = MAX_INIT_DEPTH_DEFAULT;
    float lInitGrowProba = INIT_GROW_PROBA_DEFAULT;
    float lCrossoverProba = CROSSOVER_PROBA_DEFAULT;
    float lCrossDistribProba = CROSSOVER_DISTRIB_PROBA_DEFAULT;
    float lMutStdProba = MUT_STD_PROBA_DEFAULT;
    unsigned int lMutMaxRegenDepth = MUT_MAX_REGEN_DEPTH_DEFAULT;
    float lMutSwapProba = MUT_SWAP_PROBA_DEFAULT;
    float lMutSwapDistribProba = MUT_SWAP_DISTRIB_PROBA_DEFAULT;
    unsigned long lSeed = SEED_DEFAULT;

    lNbrGen = ngen;
    lPopSize = popsize;
    lNbrPartTournament = tournamentsize;
    lMaxDepth = maxdepth;
    lMinInitDepth = mininitdepth;
    lMaxInitDepth = maxinitdepth;
    lCrossoverProba = crossoverp;
    lCrossDistribProba = crossoverdp;
    lMutStdProba = mutationp;
    lMutMaxRegenDepth = mutationmaxr;
    lSeed = randomseed;

    qDebug() << "BEAGLE Puppy symbolic regression";
    qDebug() << "Copyright 2001-2004 by Christian Gagne and Marc Parizeau";
    qDebug() << "Parameters used are:";
    qDebug() << " Population size:                           " << lPopSize;
    qDebug() << " Number of generations:                     " << lNbrGen;
    qDebug() << " Number participants tournament:            "
             << lNbrPartTournament;
    qDebug() << " Maximum tree depth:                        " << lMaxDepth;
    qDebug() << " Minimum tree initialization depth:         " << lMinInitDepth;
    qDebug() << " Maximum tree initialization depth:         " << lMaxInitDepth;
    qDebug() << " Grow-type initialization proba.:           " << lInitGrowProba;
    qDebug() << " Crossover probability:                     " << lCrossoverProba;
    qDebug() << " Crossover distribution probability:        "
             << lCrossDistribProba;
    qDebug() << " Standard (Koza's) mutation proba.:         " << lMutStdProba;
    qDebug() << " Standard mutation max. regeneration depth: "
             << lMutMaxRegenDepth;
    qDebug() << " Swap point mutation probability:           " << lMutSwapProba;
    qDebug() << " Swap point mutation distribution proba.:   "
             << lMutSwapDistribProba;
    qDebug() << " Random number generator seed value:        " << lSeed;

    emit valueChanged(" Population size:                           " + QString::number(lPopSize));
    emit valueChanged(" Number of generations:                     " + QString::number(lNbrGen));
    emit valueChanged(" Number participants tournament:            " + QString::number(lNbrPartTournament));
    emit valueChanged(" Maximum tree depth:                        " + QString::number(lMaxDepth));
    emit valueChanged(" Minimum tree initialization depth:         " + QString::number(lMinInitDepth));
    emit valueChanged(" Maximum tree initialization depth:         " + QString::number(lMaxInitDepth));
    emit valueChanged(" Grow-type initialization proba.:           " + QString::number(lInitGrowProba));
    emit valueChanged(" Crossover probability:                     " + QString::number(lCrossoverProba));
    emit valueChanged(" Crossover distribution probability:        " + QString::number(lCrossDistribProba));
    emit valueChanged(" Standard (Koza's) mutation proba.:         " + QString::number(lMutStdProba));
    emit valueChanged(" Standard mutation max. regeneration depth: " + QString::number(lMutMaxRegenDepth));
    emit valueChanged(" Swap point mutation probability:           " + QString::number(lMutSwapProba));
    emit valueChanged(" Swap point mutation distribution proba.:   " + QString::number(lMutSwapDistribProba));
    emit valueChanged(" Random number generator seed value:        " + QString::number(lSeed));

    emit GPstarted("Stop");
    qDebug() << "Creating evolution context";
    emit valueChanged("Creating evolution context");
    Context lContext;

    // ++++++++++
    // +   LS
    // ++++++++++

    lContext.useLS = LSactivated;

    lContext.mRandom.seed(lSeed);
    emit valueChanged("Function set selected");
    if (functionselection.at(0)) {
        emit valueChanged("Add");
        lContext.insert(new Add);
    }
    if (functionselection.at(1)) {
        emit valueChanged("Substract");
        lContext.insert(new Subtract);
    }
    if (functionselection.at(2)) {
        emit valueChanged("Multiply");
        lContext.insert(new Multiply);
    }
    if (functionselection.at(3)) {
        emit valueChanged("Divide");
        lContext.insert(new Divide);
    }
    if (functionselection.at(4)) {
        emit valueChanged("Sin");
        lContext.insert(new Sin);
    }
    if (functionselection.at(5)) {
        emit valueChanged("Cos");
        lContext.insert(new Cos);
    }
    if (functionselection.at(6)) {
        emit valueChanged("Log");
        lContext.insert(new Log);
    }
    if (functionselection.at(7)) {
        emit valueChanged("Exp");
        lContext.insert(new Exp);
    }

    // Add terminals
    std::stringstream str;
    for (unsigned int i = 0; i < dataset_cols - 1; i++) {
        if (terminalselection.at(i)) { // Check selected variables
            str << "X" << (i + 1);
            lContext.insert(new TokenT<double>(str.str(), 0.0));
            str.str(std::string());
        }
    }
    // Check for ERC
    if (terminalselection.at(dataset_cols - 1))
        lContext.insert(new Ephemeral);

    // Prepare data, separating input and output variables
    std::vector<int> index;
    for (unsigned int i = 0; i < dataset_rows; ++i)
        index.push_back(i);
    // Make random indexing for training,testing partitioning
    std::random_shuffle(index.begin(), index.end());
    int* index_int = new int[dataset_rows];
    std::copy(index.begin(), index.end(), index_int);

    int size_training = (float)dataset_rows * (float)trainingP / 100;
    double* trainingSet = new double[size_training * dataset_cols];
    double* testingSet = new double[(dataset_rows - size_training) * dataset_cols];
    subsetData(dataset, trainingSet, testingSet, dataset_cols, dataset_rows,
        size_training, index_int);

    double* trainingIn = new double[size_training * (dataset_cols - 1)];
    double* trainingOut = new double[size_training];
    double* testingIn = new double[(dataset_rows - size_training) * (dataset_cols - 1)];
    double* testingOut = new double[(dataset_rows - size_training)];

    double* inputV = new double[dataset_rows * (dataset_cols - 1)];
    double* outputV = new double[dataset_rows];

    for (unsigned int j = 0; j < (dataset_cols - 1); j++) {
        // Training data
        for (unsigned int i = 0; i < size_training; i++) {
            trainingIn[(j * size_training) + i] = trainingSet[(j * size_training) + i];
        }
        // Testing data
        for (unsigned int i = 0; i < (dataset_rows - size_training); i++) {
            testingIn[(j * (dataset_rows - size_training)) + i] = testingSet[(j * (dataset_rows - size_training)) + i];
        }
    }
    for (unsigned int i = 0; i < size_training; i++) {
        trainingOut[i] = trainingSet[((dataset_cols - 1) * size_training) + i];
        // qDebug()<<i<<": "<<trainingOut[i];
    }
    for (unsigned int i = 0; i < (dataset_rows - size_training); i++) {
        testingOut[i] = testingSet[((dataset_cols - 1) * (dataset_rows - size_training)) + i];
        // qDebug()<<i<<": "<<testingOut[i];
    }
    emit valueChanged("Training size = " + QString::number(size_training) + " x " + QString::number(dataset_cols - 1));
    emit valueChanged("Testing size = " + QString::number(dataset_rows - size_training) + " x " + QString::number(dataset_cols - 1));

    // Initialize population.
    std::vector<Tree> lPopulation(lPopSize);
    qDebug() << "Initializing population";
    emit valueChanged("Initializing population");
    initializePopulation(lPopulation, lContext, lInitGrowProba, lMinInitDepth,
        lMaxInitDepth);
    // evaluateSymbReg(lPopulation, lContext, lX, lF);
    // temporal

    evaluateFitness_multithread(lPopulation, lContext, trainingIn, trainingOut,
        dataset_cols - 1, size_training, terminalselection,multicore_activated);

    Stats GPthis;
    QString message;
    double bfitTrain, bfitTest, avgSize;
    int bindex; // Best individual index
    calculateStats(lPopulation, 0, message, GPthis.train, bindex, GPthis.avgsize,
        GPthis.maxsize, GPthis.minsize);
    emit valueChanged(message);
    float progress_float;
    bool abort = _abort;
    unsigned int i;
    QString output;
    TreeStruct chosenTree;
    fitnessdata datafit;
    float preFitness, optFitness;

    datafit.data = new double*[lNbrGen];
    // prefill population empty fitness data
    for (i = 0; i < lNbrGen; ++i) {
        datafit.data[i] = new double[lPopSize];
        for (int j = 0; j < lPopSize; j++) {
            datafit.data[i][j] = 0;
        }
    }
    unsigned long nEvalFunc = 0;

    // Evolve population for the given number of generations

    qDebug() << "Starting evolution";
    emit valueChanged("Starting evolution");
    for (i = 1; i <= lNbrGen; ++i) {
        applySelectionTournament(lPopulation, lContext, lNbrPartTournament);
        applyCrossover(lPopulation, lContext, lCrossoverProba, lCrossDistribProba,
            lMaxDepth);
        applyMutationStandard(lPopulation, lContext, lMutStdProba,
            lMutMaxRegenDepth, lMaxDepth);
        applyMutationSwap(lPopulation, lContext, lMutSwapProba,
            lMutSwapDistribProba);
        // temporal

        nEvalFunc += evaluateFitness_multithread(lPopulation, lContext, trainingIn, trainingOut,
            dataset_cols - 1, size_training, terminalselection,multicore_activated);

        calculateStats(lPopulation, i, message, GPthis.train, bindex,
            GPthis.avgsize, GPthis.maxsize, GPthis.minsize);
        nEvalFunc += evaluateFitnessTesting(
            lPopulation[bindex], lContext, testingIn, testingOut, dataset_cols - 1,
            (dataset_rows - size_training), terminalselection);

        GPthis.test = lPopulation[bindex].rFitnessTest;
        GPthis.gen = i;

        lPopulation[bindex].write_qstring(output);
        qDebug() << i << " Train: " << lPopulation[bindex].mFitness
                 << " Test: " << lPopulation[bindex].mFitnessTest << " " << output;
        output.clear();

        if (lContext.useLS) {
            qDebug() << "Start";
            applyLS(lPopulation[bindex], lContext, trainingIn, trainingOut,
                dataset_cols - 1, size_training, terminalselection, preFitness,
                optFitness);
            qDebug() << "End [Original: " << preFitness
                     << " Optimized: " << optFitness;
        }

        emit valueChanged(message);
        emit send_stats(GPthis);
        progress_float = (i / (float)lNbrGen) * 100;
        emit progressChanged((int)progress_float);
        emit sendEvalFunc(nEvalFunc);
        // fill population fitness data
        // datafit.data[i-1] = new double[lPopSize];
        for (int j = 0; j < lPopSize; j++) {
            datafit.data[i - 1][j] = lPopulation[j].mFitness;
        }
        emit plot3DSendData(datafit);
        // Checks if the process should be aborted
        mutex.lock();
        abort = _abort;
        mutex.unlock();

        if (abort) {
            qDebug() << "Aborting worker process";
            break;
        }
    }

    qDebug() << "End of evolution";

    // Outputting best individual
    std::vector<Tree>::const_iterator lBestIndividual = std::max_element(lPopulation.begin(), lPopulation.end());
    qDebug() << "Best individual at generation " << (i - 1) << " is: ";

    // Visualize best tree
    for (unsigned int i = 0; i < lBestIndividual[0].size(); i++) {
        chosenTree.mName.append(
            QString::fromStdString(lBestIndividual[0][i].mPrimitive->getName()));
        chosenTree.mNumberArguments.append(
            lBestIndividual[0][i].mPrimitive->getNumberArguments());
        chosenTree.mSubTreeSize.append(lBestIndividual[0][i].mSubTreeSize);
        chosenTree.posX.append(0);
        chosenTree.posY.append(0);
        chosenTree.index.append(-1);
    }
    emit send_tree(chosenTree);

    lBestIndividual[0].write_qstring(output);

    emit valueChanged("Best individual at generation " + QString::number(i - 1) + " is: " + output + " with fitness: " + QString::number(lBestIndividual[0].mFitness));
    emit send_tree_string(output); // Prefix syntax
    output.clear();
    lBestIndividual[0].write_qstring_infix(output);
    emit send_tree_infix_string(output); // Infix syntax
    output.clear();
    lBestIndividual[0].write_qstring_latex(output);
    emit send_tree_latex_string(output); // Latex syntax

    emit send_stats_end(GPthis);

    // Clean up data
    delete inputV;
    delete outputV;
    delete trainingSet;
    delete testingSet;
    emit GPstarted("Run");
    emit finished();
    return 0;
}

unsigned int Worker::evaluateFitness(std::vector<Tree>& ioPopulation,
    Context& ioContext, double* inX,
    double* inF, int cols, int rows,
    std::vector<bool>& terSelection)
{
    std::stringstream var;
    double rowV, lQuadErr, lResult, lErr, lRMS;
    unsigned int lNbrEval = 0, i, j, k;
    for (i = 0; i < ioPopulation.size(); i++) {
        lQuadErr = 0.0;
        for (j = 0; j < rows; j++) {
            // Copy col wise data for variable usage
            for (k = 0; k < cols; k++) {
                if (terSelection.at(k)) {
                    rowV = inX[(k * rows) + j];
                    var << "X" << (k + 1);
                    ioContext.mPrimitiveMap[var.str()]->setValue(&rowV);
                    var.str(std::string());
                }
            }
            lResult = 0.0;
            lErr = 0.0;
            ioPopulation[i].interpret(&lResult, ioContext); // Computing is row wise
            lErr = lResult - inF[j];
            lQuadErr += (lErr * lErr);
        }

        lRMS = std::sqrt(lQuadErr / rows);
        ioPopulation[i].mFitness = 1. / (1. + lRMS);
        ioPopulation[i].rFitness = lRMS;
        ioPopulation[i].mValid = true;
        ++lNbrEval;
    }
    return lNbrEval;
}

unsigned int Worker::evaluateFitness_multithread(
    std::vector<Tree>& ioPopulation, Context& ioContext, double* inX,
    double* inF, int cols, int rows, std::vector<bool>& terSelection,
    bool multithread)
{
    std::stringstream var;
    double rowV, lQuadErr, lResult, lErr, lRMS;
    unsigned int lNbrEval = 0, i, j, k;
    int popsize = ioPopulation.size();
    // Copy population to QVector    
    wholePop.cols = cols;
    wholePop.rows = rows;
    wholePop.inF = inF;
    wholePop.inX = inX;
    wholePop.ioContext = ioContext;
    wholePop.terSelection = terSelection;
    wholePop.bunchTrees.resize(0);
    for (i = 0; i < popsize; ++i)
        wholePop.bunchTrees.append(ioPopulation[i]);    
    if (multithread) {
        //for(i=0;i<popsize;i++)
        //  input.append(ioPopulation.at(i));
        //wholePop = start_fit_check(allpop);

//          for (i = 0; i < popsize; ++i)
//            ioPopulation[i] = wholePop[i];
        fitnessValidFinished = false;
        toSuspend = true;
        emit requestFitnessCalc(wholePop);
        if(toSuspend) {
          mutex.lock();
          waitCondition.wait(&mutex);
          mutex.unlock();
        }
        while(!fitnessValidFinished);
        qDebug()<<"Data is almost ready";

        QVector<Tree> tempdata = fitnessValid;
        for (i = 0; i < popsize; ++i) {
          ioPopulation[i] = tempdata.at(i);
        }
        //evaluateFitness(ioPopulation,ioContext,inX,inF,cols,rows,terSelection);

      //QVector<Tree> output = QtConcurrent::blockingMappedReduced(input,mapfunction,reduce,QtConcurrent::OrderedReduce);
      //evaluateFitness(ioPopulation,ioContext,inX,inF,cols,rows,terSelection);
    }
    else
      evaluateFitness(ioPopulation,ioContext,inX,inF,cols,rows,terSelection);
    return popsize; //
}

unsigned int Worker::evaluateFitnessTesting(Tree& individual,
    Context& ioContext, double* inX,
    double* inF, int cols, int rows,
    std::vector<bool>& terSelection)
{
    std::stringstream var;
    double rowV;
    unsigned int lNbrEval = 0, j, k;
    double lQuadErr = 0.0, lResult, lErr, lRMS;
    // for(j=0;j<(cols*rows);j++) qDebug()<<j<<": "<<inX[j];

    for (j = 0; j < rows; j++) {
        // Copy col wise data for variable usage
        for (k = 0; k < cols; k++) {
            if (terSelection.at(k)) {
                rowV = inX[(k * rows) + j];
                var << "X" << (k + 1);
                ioContext.mPrimitiveMap[var.str()]->setValue(&rowV);
                var.str(std::string());
            }
        }
        lResult = 0.0;
        individual.interpret(&lResult, ioContext);
        lErr = lResult - inF[j];
        lQuadErr += (lErr * lErr);
    }
    lRMS = std::sqrt(lQuadErr / rows);
    individual.mFitnessTest = 1. / (1. + lRMS);
    individual.rFitnessTest = lRMS;
    individual.mValid = true;
    ++lNbrEval;
    return lNbrEval;
}

unsigned int Worker::evaluateFitnessTraining(Tree& individual,
    Context& ioContext, double* inX,
    double* inF, int cols, int rows,
    std::vector<bool>& terSelection)
{
    std::stringstream var;
    double rowV;
    unsigned int lNbrEval = 0, j, k;
    double lQuadErr = 0.0, lResult, lErr, lRMS;
    for (j = 0; j < rows; j++) {
        // Copy col wise data for variable usage
        for (k = 0; k < cols; k++) {
            if (terSelection.at(k)) {
                rowV = inX[(k * rows) + j];
                var << "X" << (k + 1);
                ioContext.mPrimitiveMap[var.str()]->setValue(&rowV);
                var.str(std::string());
            }
        }
        lResult = 0.0;
        individual.interpret(&lResult, ioContext);
        lErr = lResult - inF[j];
        lQuadErr += (lErr * lErr);
    }
    lRMS = std::sqrt(lQuadErr / rows);
    individual.mFitness = 1. / (1. + lRMS);
    individual.rFitness = lRMS;
    ++lNbrEval;
    return lNbrEval;
}

int Worker::applyLS(Tree& individual, Context& ioContext, double* inX,
    double* inF, int cols, int rows,
    std::vector<bool>& terSelection, float& oriFit,
    float& optFit)
{
    oriFit = individual.rFitness;
    Tree tmpInd = individual;
    OneTree bufferTree;
    int counter = 0;
    int ret;
    double info[LM_INFO_SZ];
    for (unsigned int i = 0; i < tmpInd.size(); i++) {
        QString temp = QString::fromStdString(tmpInd[i].mPrimitive->getName());
        if (temp.at(0) == 'X')
            counter += 1;
        if (temp.at(0) == '+')
            counter += 1;
        if (temp.at(0) == '-')
            counter += 1;
        if (temp.at(0) == '/')
            counter += 1;
    }
    int m = counter; // Number of parameters
    int n = rows; // Number of instances
    double p[m], x[n];
    // Parameter initialization
    for (unsigned int i = 0; i < m; i++) {
        p[i] = 0.5;
    }
    bufferTree.selTree = tmpInd;
    bufferTree.cols = cols;
    bufferTree.rows = rows;
    bufferTree.ioContext = ioContext;
    bufferTree.inX = inX;
    bufferTree.terSelection = terSelection;

    // Real output
    for (int j = 0; j < rows; j++)
        x[j] = inF[j];
    // Do Levenberg-Marquardt optimization
    ret = dlevmar_dif(objFunc, p, x, m, n, 100, NULL, info, NULL, NULL,
        &bufferTree);
    qDebug() << info[5] << " iterations";
    qDebug() << info[7] << " function evaluations";
    // Update optimized parameters in tree
    counter = 0;
    for (unsigned int i = 0; i < tmpInd.size(); i++) {
        QString temp = QString::fromStdString(tmpInd[i].mPrimitive->getName());
        if (temp.at(0) == 'X') {
            tmpInd[i].parameter = p[counter];
            counter += 1;
        }
        if (temp.at(0) == '+') {
            tmpInd[i].parameter = p[counter];
            counter += 1;
        }
        if (temp.at(0) == '-') {
            tmpInd[i].parameter = p[counter];
            counter += 1;
        }
        if (temp.at(0) == '/') {
            tmpInd[i].parameter = p[counter];
            counter += 1;
        }
        //    if(temp.at(0) == 'C') {
        //      tmpInd[i].parameter = p[counter];
        //      counter += 1;
        //    }
        //    if(temp.at(0) == 'S') {
        //      tmpInd[i].parameter = p[counter];
        //      counter += 1;
        //    }
        //    if(temp.at(0) == 'E') {
        //      tmpInd[i].parameter = p[counter];
        //      counter += 1;
        //    }
        //    if(temp.at(0) == 'L') {
        //      tmpInd[i].parameter = p[counter];
        //      counter += 1;
        //    }
    }
    // objFunc(p,x,m,n,&bufferTree);
    evaluateFitnessTraining(tmpInd, ioContext, inX, inF, cols, rows,
        terSelection);
    optFit = tmpInd.rFitness;
}

void objFunc(double* p, double* x, int m, int n, void* data)
{
    std::stringstream var;
    Worker::OneTree* dptr;
    dptr = (Worker::OneTree*)data;
    int counter = 0;
    // Retrieve parameter and update node parameter (here, only selected nodes are
    // used by updating its values)
    for (unsigned int i = 0; i < dptr->selTree.size(); i++) {
        QString temp = QString::fromStdString(dptr->selTree[i].mPrimitive->getName());
        if (temp.at(0) == 'X') {
            dptr->selTree[i].parameter = p[counter];
            counter += 1;
        }
        if (temp.at(0) == '+') {
            dptr->selTree[i].parameter = p[counter];
            counter += 1;
        }
        if (temp.at(0) == '-') {
            dptr->selTree[i].parameter = p[counter];
            counter += 1;
        }
        if (temp.at(0) == '/') {
            dptr->selTree[i].parameter = p[counter];
            counter += 1;
        }
        //    if(temp.at(0) == 'C') {
        //      dptr->selTree[i].parameter = p[counter];
        //      counter += 1;
        //    }
        //    if(temp.at(0) == 'S') {
        //      dptr->selTree[i].parameter = p[counter];
        //      counter += 1;
        //    }
        //    if(temp.at(0) == 'E') {
        //      dptr->selTree[i].parameter = p[counter];
        //      counter += 1;
        //    }
        //    if(temp.at(0) == 'L') {
        //      dptr->selTree[i].parameter = p[counter];
        //      counter += 1;
        //    }
    }
    // Evaluate row wise
    double rowV;
    double lResult;
    for (int j = 0; j < n; j++) {
        // Copy col wise data for variable usage
        for (int k = 0; k < dptr->cols; k++) {
            if (dptr->terSelection.at(k)) {
                rowV = dptr->inX[(k * dptr->rows) + j];
                var << "X" << (k + 1);
                dptr->ioContext.mPrimitiveMap[var.str()]->setValue(&rowV);
                var.str(std::string());
            }
        }
        lResult = 0.0;
        dptr->selTree.interpret(&lResult, dptr->ioContext);
        x[j] = lResult; // Fill tree output
    }
}
