#pragma once
#include "matrix.h"
#include "MNISTLoader.h"
#include "TrainingConfig.h"
#include <algorithm>
#include <random>

class NeuralNetwork {
public:
    NeuralNetwork(TrainingConfig _config);
    float train_one_epoch(std::vector<MNISTSample>& trainData);
    std::vector<float> predict(Matrix image);
private:
    TrainingConfig config;
    std::vector<Matrix> weights;
    std::vector<Matrix> biases;
    
    void initNetwork();
    Matrix forward(Matrix input);
    Matrix forward_with_cache(Matrix input, 
                              std::vector<Matrix>& activations, 
                              std::vector<Matrix>& zValues); 
    void backward(Matrix input, Matrix target, float learningRate); 
    Matrix createOneHot(int label);
};