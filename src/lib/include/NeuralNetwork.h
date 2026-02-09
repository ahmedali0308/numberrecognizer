#include "matrix.h"
#pragma once

class NeuralNetwork {
    public:
        NeuralNetwork(Matrix trainingData);

        Matrix trainingData;
        int* n;
    private:
};