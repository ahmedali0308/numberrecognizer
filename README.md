# Number recognizer Project

## What is it?
"Number recognizer" is a project where I experimented with neural networks, specifically recognition of user-drawn numbers. This involves training a neural network with modified data from the MNIST dataset (https://git-disl.github.io/GTDLBench/datasets/mnist_datasets/)

*The graphic interface is rendered using the SFML Graphics library*

## How does it work?
Upon opening the executable a window pops up where the user can freely draw onto a drawing area. The input (pixels on the board) are scaled down to an area of 28x28 pixels and then fed into a neural network as the "first layer". Having been trained beforehand to find the right weights and biases, it uses the this data to output a set of probabilities for numbers 0 to 9.

Here is a demonstration of the program in action:

/
