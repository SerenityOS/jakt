# To build: docker build --no-cache -t jakt:latest -f Dockerfile .
# To run: docker run -it jakt:latest
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y \
    && apt-get install -y \
        build-essential \
        cmake \
        git \
        ninja-build \
        clang \
        libclang-dev \
    && rm -rf /var/lib/apt/lists/

COPY . /project/jakt/
WORKDIR /project/jakt/

RUN cmake -B build -GNinja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=jakt-install
RUN ninja -C build install

RUN ln -s /project/jakt/jakt-install/bin/jakt /usr/bin/jakt

