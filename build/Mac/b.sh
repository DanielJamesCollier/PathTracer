echo "------------------------"
echo "------Build Started-----"
echo "------------------------"
echo "clang++ -Werror  -L deps/ -framework SDL2 -stdlib=libc++ -std=c++14 -o PathTracer ../../src/main.cpp"
clang++ -Werror  -L deps/ -framework SDL2 -stdlib=libc++ -std=c++14 -o PathTracer ../../src/main.cpp
echo "------------------------"
echo -e "\n\n"
