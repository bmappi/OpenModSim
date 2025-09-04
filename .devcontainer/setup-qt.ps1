# Install aqtinstall
python -m pip install aqtinstall

# Create Qt directory
New-Item -ItemType Directory -Path "C:\Qt" -Force

# Install Qt 5.15.2 with required modules
python -m aqt install-qt windows desktop 5.15.2 win64_msvc2019_64 -O C:\Qt

# Add Qt to PATH
$env:PATH += ";C:\Qt\5.15.2\msvc2019_64\bin"

# Install build tools
choco install -y ninja cmake

# Verify installation
qmake -v
cmake --version
