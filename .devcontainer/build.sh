cd /workspaces/OpenModSim/
cmake -S omodsim -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

echo "Now run build/omodsim from vnc"