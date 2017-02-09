#ifndef MultiArray_hpp
#define MultiArray_hpp

template<typename T, int width, int height>
class MultiArray
{
public:
    MultiArray() { 
        m_data = new T[width * height];

        if(m_data == 0) {
            std::cout << "multi array failed: out of memory" << std::endl;
            exit(-1);
        }
    }

    ~MultiArray() {
         delete [] m_data; 
    }

    // access as 1D array
    T & operator() (int x) {
         return m_data[x];
    }

    // access as 2D array - row major
    T & operator() (int row, int col) {
        return m_data[width * row + col];
    }

    T * getData() {
         return m_data;
    }

private:
    T * m_data;
};

#endif /* MultiArray_hpp */