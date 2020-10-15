printf "\n%-35s" "Building..."
g++ -std=c++11 src/main.cpp src/Register.cpp src/Entry.cpp src/ComputerConnections.cpp -o src/main.out
echo BUILD COMPLETE
cd src
./main.out
rm main.out