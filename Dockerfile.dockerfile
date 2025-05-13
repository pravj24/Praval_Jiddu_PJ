FROM gcc:11

RUN apt-get update && apt-get install -y \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

#Set working directory
WORKDIR /app

#Copy all files to the container
COPY . /app/

RUN mkdir -p /app/users

#Compile the C++ code
RUN g++ -o Task2Praval_J_app Task2Praval_J.cpp -lcrypto -std=c++17 -lstdc++fs

#Run the compiled code
CMD ["./Task2Praval_J_app"]
