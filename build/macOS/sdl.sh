echo "------------------------"
echo "------Build Started-----"
echo "------------------------"
echo "clang++ -O3 -Werror -framework SDL2 -stdlib=libc++ -std=c++14 -o PathTracer ../../src/main.cpp"
clang++ -O3 -Werror -framework SDL2 -stdlib=libc++ -std=c++14 -o PathTracer ../../src/main.cpp
echo "------------------------"
echo -e "\n\n"