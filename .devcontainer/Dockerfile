FROM mcr.microsoft.com/devcontainers/base:ubuntu

RUN apt-get update && apt-get install -y python3 python3-pip python3-venv cmake build-essential ninja-build

RUN apt-get install -y \
    git \
    wget \
    libgl1-mesa-dev \
    libxkbcommon-x11-0 \
    libxcb-cursor0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-render-util0 \
    libxrender1 \
    libx11-xcb1 \
    libxcb-xinerama0 \
    libxcb-xfixes0 \
    libxcb-shape0 \
    libxcb-randr0 \
    libxcb-shm0 \
    libxext6 \
    libsm6 \
    libice6 \
    && apt-get clean

RUN apt-get install -y \
            qtbase5-dev \
            qtdeclarative5-dev \
            libqt5serialport5-dev \
            libqt5serialbus5-dev \
            qttools5-dev-tools \
            qttools5-dev \
            libqt5serialbus5

WORKDIR /workspace
