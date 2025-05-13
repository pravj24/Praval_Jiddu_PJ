# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Update the package list and install g++
RUN apt-get update && apt-get install -y g++

# Set the working directory in the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the C++ code
RUN g++ -o main main.cpp

# Set the command to run the executable
CMD ["./main"]