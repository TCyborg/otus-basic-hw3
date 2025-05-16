FROM ubuntu:24.04

RUN apt update && apt install -y \
    build-essential \
    cmake \
    gcc g++ \
    clang clang-tidy \
    cppcheck \
    doxygen graphviz \
    libgtest-dev \
    git neovim

WORKDIR /workspace