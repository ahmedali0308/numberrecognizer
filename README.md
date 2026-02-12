# Number Recognizer Project

A neural network-based handwritten digit recognition application built with C++ and SFML.

## What is it?

"Number recognizer" is a project where I experimented with neural networks, specifically recognition of user-drawn numbers. This involves training a neural network with modified data from the [MNIST dataset](https://git-disl.github.io/GTDLBench/datasets/mnist_datasets/).

*The graphic interface is rendered using the SFML Graphics library.*

## How does it work?

Upon opening the executable, a window pops up where the user can freely draw onto a drawing area. The input (pixels on the board) are scaled down to an area of 28×28 pixels and then fed into a neural network as the "first layer". Having been trained beforehand to find the right weights and biases, it uses this data to output a set of probabilities for numbers 0 to 9.

## Implementation

This project features a **custom neural network implementation** built from scratch in C++. Unlike many machine learning projects that rely on frameworks like TensorFlow or PyTorch, all core components are hand-written:

- **Neural network architecture** - Forward and backward propagation implemented manually
- **Matrix operations** - Custom matrix class for all mathematical computations
- **Training algorithms** - Gradient descent and backpropagation coded from the ground up
- **Data preprocessing** - MNIST data handling and normalization

**The only external dependency is SFML**, which is used exclusively for graphics rendering and window management. All machine learning logic, mathematical operations, and neural network functionality is original code written for this project.

## Features

- Interactive 28×28 drawing canvas for digit input
- Real-time digit recognition using neural networks
- AI training interface with customizable parameters
- Training progress visualization with accuracy graphs
- Probability display for each digit (0-9)

## Prerequisites

### Required Tools

- **CMake** (version 3.28 or higher)
- **C++ Compiler** with C++17 support:
  - **Windows**: MSVC (Visual Studio 2022 Build Tools) or MinGW-w64
  - **Linux**: GCC or Clang
  - **macOS**: Clang (Xcode Command Line Tools)
- **Git**

### Installing Prerequisites

#### Windows

**Option 1: Using winget (recommended)**
```powershell
winget install Kitware.CMake
winget install Git.Git
winget install Microsoft.VisualStudio.2022.BuildTools --override "--quiet --wait --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
```

**Option 2: Using Chocolatey**
```powershell
choco install cmake git visualstudio2022buildtools -y
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake git
```

#### Linux (Fedora/RHEL)
```bash
sudo dnf install gcc-c++ cmake git
```

#### macOS
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake git

# Install Xcode Command Line Tools
xcode-select --install
```

## Dependencies

The project uses the following libraries (automatically downloaded via CMake):

- **SFML 3.0.1** - Graphics and window management
  - Automatically fetched from GitHub during build

## Building the Project

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/numberrecognizer.git
cd numberrecognizer
```

### 2. Create Build Directory

```bash
mkdir build
cd build
```

### 3. Configure with CMake

**Windows (MSVC):**
```powershell
cmake ..
```

**Windows (MinGW):**
```powershell
cmake .. -G "MinGW Makefiles"
```

**Linux/macOS:**
```bash
cmake ..
```

### 4. Build the Project

**Windows:**
```powershell
cmake --build . --config Release
```

**Linux/macOS:**
```bash
cmake --build .
```

### 5. Run the Application

**Windows:**
```powershell
.\bin\Release\main.exe
```

**Linux/macOS:**
```bash
./bin/main
```

## Usage

### Drawing and Recognition

1. **Drawing Mode**: Use left mouse button to draw digits on the canvas
2. **Erasing**: Use right mouse button to erase your drawing
3. **Recognition**: The application displays real-time confidence scores for each digit (0-9)

### Training the Neural Network

1. Configure Settings 
2. Launch the AI training window
3. Monitor training progress through the accuracy graph
4. Trained weights and biases are automatically applied for recognition

### Demonstration

/


## Author

Ahmed Ali 2025

## Acknowledgments

- **SFML** - Graphics library for window management and rendering
- **MNIST Dataset** - Training data from the [Modified National Institute of Standards and Technology database](https://git-disl.github.io/GTDLBench/datasets/mnist_datasets/)
- Neural network implementation developed from scratch for learning purposes
