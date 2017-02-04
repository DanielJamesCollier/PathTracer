#ifndef MultiArray_hpp
#define MultiArray_hpp

template<typename T, int width, int height>
class MultiArray
{
public:
    T& operator() (int x, int y) { return data[x][y]; }
    MultiArray() { data = new cols[width]; }
    ~MultiArray() { delete [] data; }
private:
    typedef T cols[height];
    cols * data;
};

#endif /* MultiArray_hpp */