# Use the official LLVM image as the base image
FROM silkeh/clang:latest

# Set the working directory
WORKDIR /app

# Install any additional dependencies you need
RUN apt-get update && \
    apt-get install -y \
    cmake \
    git \
    gdb

# Copy your source code into the container
COPY . .

# Create a build directory and run CMake
RUN mkdir build && \
    cd build && \
    cmake ..

# Build the project
RUN cd build && \
    make
