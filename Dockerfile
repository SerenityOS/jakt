# To build: docker build --no-cache -t jakt:latest -f Dockerfile .
# To run: docker run -it jakt:latest
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y \
    && apt-get install -y \
        build-essential \
        cmake \
        git \
        ninja-build \
        clang-15 \
        libclang-15-dev \
    && rm -rf /var/lib/apt/lists/

COPY . /project/jakt/
WORKDIR /project/jakt/

RUN ln -s /usr/bin/clang++-15 /usr/bin/clang++; \
    ln -s /usr/bin/clang-15 /usr/bin/clang; \
    ln -s /usr/bin/clang-cpp-15 /usr/bin/clang-cpp

RUN cmake -B build -GNinja -DCMAKE_CXX_COMPILER=clang++-15 -DCMAKE_INSTALL_PREFIX=jakt-install
RUN ninja -C build install

RUN ln -s /project/jakt/jakt-install/bin/jakt /usr/bin/jakt

ENTRYPOINT ["/bin/bash"]

