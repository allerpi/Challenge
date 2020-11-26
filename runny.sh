printf "\n%-35s" "Building..."
g++ -std=c++11 src/*.cpp -o src/main.out
echo BUILD COMPLETE
cd src
./main.out
rm main.out