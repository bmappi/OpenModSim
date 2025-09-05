# Use Windows Server Core as base
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

# ... python -m pip install aqtinstall  + install qt 5.12.2
# Install aqtinstall
# RUN python3 -m pip install aqtinstall --break-system-packages

# Install Qt 5.12.2 using aqt
# WORKDIR /opt/Qt
# RUN python3 -m aqt install-qt \
#       linux desktop 5.12.2 gcc_64 \
#       -O /opt/Qt

# Add Qt to PATH
# ENV PATH="/opt/Qt/5.12.2/gcc_64/bin:${PATH}"
# ENV QT_QPA_PLATFORM=offscreen

RUN apt-get install -y \
            qtbase5-dev \
            qtdeclarative5-dev \
            libqt5serialport5-dev \
            libqt5serialbus5-dev \
            qttools5-dev-tools \
            qttools5-dev \
            libqt5serialbus5

# cmake -S /workspaces/OpenModSim/omodsim -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
# cmake --build build --config 

# Set working directory
WORKDIR /workspace
