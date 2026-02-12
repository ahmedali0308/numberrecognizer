#include <../include/NeuralNetwork.h>

NeuralNetwork::NeuralNetwork(TrainingConfig _config) {
    config = _config;
    initNetwork();
}

void NeuralNetwork::initNetwork() {
    std::vector<int> layerSizes;
    layerSizes.push_back(784);
    for (int i = 0; i < config.hiddenLayers; i++) {
        layerSizes.push_back(config.neuronsPerLayer);
    }
    layerSizes.push_back(10);
    
    for (int i = 0; i < layerSizes.size() - 1; i++) {
        // Xavier Initialization
        float limit = sqrt(6.0f / (layerSizes[i] + layerSizes[i+1]));
        
        Matrix w(layerSizes[i+1], layerSizes[i]);
        w.randomize(-limit, limit);
        weights.push_back(w);
        
        Matrix b(layerSizes[i+1], 1);
        b.randomize(-limit, limit);
        biases.push_back(b);
    }
}

std::vector<float> NeuralNetwork::predict(Matrix image) {
    Matrix output = forward(image);
    
    std::vector<float> probabilities;
    for (int i = 0; i < 10; i++) {
        probabilities.push_back(output(i, 0)*100);
    }
    
    return probabilities;
}

Matrix NeuralNetwork::forward(Matrix input) {
    Matrix activation = input;
    
    for (int i = 0; i < weights.size(); i++) {
        // z = W * a + b
        activation = weights[i] * activation + biases[i];
        
        switch (config.activationFunc)
        {
        case 0:
            activation.sigmoid();
            break;
        case 1:
            activation.relu();
            break;
        default:
            activation.sigmoid();
            break;
        }
    }
    
    return activation;
}

Matrix NeuralNetwork::forward_with_cache(Matrix input, 
                                         std::vector<Matrix>& activations, 
                                         std::vector<Matrix>& zValues) {
    activations.clear();
    zValues.clear();
    
    Matrix activation = input;
    activations.push_back(activation);
    
    for (int i = 0; i < weights.size(); i++) {
        Matrix z = weights[i] * activation + biases[i];
        zValues.push_back(z);
        
        activation = z;
        
        switch (config.activationFunc) {
            case 0: activation.sigmoid(); break;
            case 1: activation.relu(); break;
            default: activation.sigmoid(); break;
        }
        
        activations.push_back(activation);
    }
    
    return activation;
}

void NeuralNetwork::backward(Matrix input, Matrix target, float learningRate) {
    std::vector<Matrix> activations;
    std::vector<Matrix> zValues;
    Matrix output = forward_with_cache(input, activations, zValues);
    
    Matrix error = output - target;
    Matrix delta = error.hadamard(activations.back().sigmoid_derivative());
    
    for (int i = weights.size() - 1; i >= 0; i--) {
        Matrix weightGradient = delta * activations[i].transpose();
        weights[i] -= weightGradient * learningRate;
        biases[i] -= delta * learningRate;
        
        if (i > 0) {
            error = weights[i].transpose() * delta;
            
            switch (config.activationFunc) {
                case 0:
                    delta = error.hadamard(activations[i].sigmoid_derivative());
                    break;
                case 1:
                    delta = error.hadamard(zValues[i-1].relu_derivative());
                    break;
                default:
                    delta = error.hadamard(activations[i].sigmoid_derivative());
                    break;
            }
        }
    }
}

Matrix NeuralNetwork::createOneHot(int label) {
    Matrix oneHot(10, 1);
    for (int i = 0; i < 10; i++) {
        oneHot(i, 0) = (i == label) ? 1.0f : 0.0f;
    }
    return oneHot;
}

float NeuralNetwork::train_one_epoch(std::vector<MNISTSample>& trainData) {
    int correct = 0;
    
    for (auto& sample : trainData) {
        Matrix output = forward(sample.image);
        Matrix target = createOneHot(sample.label);
        backward(sample.image, target, config.learningRate);
        
        if (output.argmax() == sample.label) correct++;
    }
    
    return (float)correct / trainData.size();
}