#!/usr/bin/env bash
set -e

echo "Installing Qt 5.15 dependencies..."

# For Qt5 dev packages
sudo apt-get update && sudo apt-get install -y \
  qtbase5-dev \
  qtchooser \
  qt5-qmake \
  qtbase5-dev-tools \
  qttools5-dev-tools \
  qtdeclarative5-dev \
  qtserialport5-dev \
  qtserialbus5-dev \
  qttools5-dev \
  qttools5-dev-tools \
  qtscript5-dev \
  qml-module-qtquick-controls \
  qml-module-qtquick-controls2 \
  qml-module-qtgraphicaleffects \
  qml-module-qtwebsockets \
  qml-module-qt-labs-platform

echo "Qt setup complete"
