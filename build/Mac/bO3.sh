echo "------------------------"
echo "------Build Started-----"
echo "------------------------"
echo "clang++ -O3 -Werror  -L deps/ -framework SDL2 -stdlib=libc++ -std=c++14 -o PathTracer ../../src/main.cpp"
clang++ -O3 -Werror  -L deps/ -framework SDL2 -stdlib=libc++ -std=c++14 -o PathTracer ../../src/main.cpp
echo "------------------------"
echo -e "\n\n"/Users/danielcollier/Documents/repositories/PathTracer/build/Mac/bO3.sh
