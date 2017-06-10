namespace djc_math {

//------------------------------------------------------------
template<typename T>
Mat4<T>::Mat4() {
    m_matrix.fill(T());
}

//------------------------------------------------------------
template<typename T>
Mat4<T>::Mat4(std::array<T, 16> const & matrix) 
: m_matrix(matrix)
{
    // empty
}

//------------------------------------------------------------
template<typename T> 
Mat4<T>::Mat4(Mat3<T> const & matrix, T lastVal) 
:   m_matrix(std::array<T, 16>{{
        matrix[0], matrix[1], matrix[2], 0,
        matrix[3], matrix[4], matrix[5], 0,
        matrix[6], matrix[7], matrix[8], 0,
                0,         0,         0, lastVal}}) // [15] fix : should be 1 ? 0 maybe make this function in utils?
{

}

//------------------------------------------------------------
template<typename T> Mat3<T>
Mat4<T>::toMat3() const {
    return Mat3<T>(std::array<T, 9> {{
        m_matrix[0], m_matrix[1], m_matrix[2],
        m_matrix[4], m_matrix[5], m_matrix[6],
        m_matrix[8], m_matrix[9], m_matrix[10]
    }});
}

// //------------------------------------------------------------
// template<typename T> void
// Mat4<T>::clear() {
//     m_matrix.fill(T());
// }

// //------------------------------------------------------------
// template<typename T> void
// Mat4<T>::clear(T value) {
//     m_matrix.fill(value);
// }

//------------------------------------------------------------
template<typename T> /* friend */ Mat4<T> 
operator * (Mat4<T> const & lhs, Mat4<T> const & rhs) {
    //----------------------    
    // [0 ]  [1 ]  [2 ] [3 ]  
    // [4 ]  [5 ]  [6 ] [7 ]  
    // [8 ]  [9 ]  [10] [11]  
    // [12]  [13]  [14] [15]  
    //----------------------  
    
    return Mat4<T>(std::array<T, 16>{{
      ///////
      /*[ 0]*/ (lhs[ 0] * rhs[ 0]) + (lhs[ 1] * rhs[ 4]) + (lhs[ 2] * rhs[ 8]) + (lhs[ 3] * rhs[12]),
      /*[ 1]*/ (lhs[ 0] * rhs[ 1]) + (lhs[ 1] * rhs[ 5]) + (lhs[ 2] * rhs[ 9]) + (lhs[ 3] * rhs[13]),
      /*[ 2]*/ (lhs[ 0] * rhs[ 2]) + (lhs[ 1] * rhs[ 6]) + (lhs[ 2] * rhs[10]) + (lhs[ 3] * rhs[14]),
      /*[ 3]*/ (lhs[ 0] * rhs[ 3]) + (lhs[ 1] * rhs[ 7]) + (lhs[ 2] * rhs[11]) + (lhs[ 3] * rhs[15]),
      ///////
      /*[ 4]*/ (lhs[ 4] * rhs[ 0]) + (lhs[ 5] * rhs[ 4]) + (lhs[ 6] * rhs[ 8]) + (lhs[ 7] * rhs[12]),
      /*[ 5]*/ (lhs[ 4] * rhs[ 1]) + (lhs[ 5] * rhs[ 5]) + (lhs[ 6] * rhs[ 9]) + (lhs[ 7] * rhs[13]),
      /*[ 6]*/ (lhs[ 4] * rhs[ 2]) + (lhs[ 5] * rhs[ 6]) + (lhs[ 6] * rhs[10]) + (lhs[ 7] * rhs[14]),
      /*[ 7]*/ (lhs[ 4] * rhs[ 3]) + (lhs[ 5] * rhs[ 7]) + (lhs[ 6] * rhs[11]) + (lhs[ 7] * rhs[15]),
      ///////
      /*[ 8]*/ (lhs[ 8] * rhs[ 0]) + (lhs[ 9] * rhs[ 4]) + (lhs[10] * rhs[ 8]) + (lhs[11] * rhs[12]),
      /*[ 9]*/ (lhs[ 8] * rhs[ 1]) + (lhs[ 9] * rhs[ 5]) + (lhs[10] * rhs[ 9]) + (lhs[11] * rhs[13]),
      /*[10]*/ (lhs[ 8] * rhs[ 2]) + (lhs[ 9] * rhs[ 6]) + (lhs[10] * rhs[10]) + (lhs[11] * rhs[14]),
      /*[11]*/ (lhs[ 8] * rhs[ 3]) + (lhs[ 9] * rhs[ 7]) + (lhs[10] * rhs[11]) + (lhs[11] * rhs[15]),
      ///////
      /*[12]*/ (lhs[12] * rhs[ 0]) + (lhs[13] * rhs[ 4]) + (lhs[14] * rhs[ 8]) + (lhs[15] * rhs[12]),
      /*[13]*/ (lhs[12] * rhs[ 1]) + (lhs[13] * rhs[ 5]) + (lhs[14] * rhs[ 9]) + (lhs[15] * rhs[13]),
      /*[14]*/ (lhs[12] * rhs[ 2]) + (lhs[13] * rhs[ 6]) + (lhs[14] * rhs[10]) + (lhs[15] * rhs[14]),
      /*[15]*/ (lhs[12] * rhs[ 3]) + (lhs[13] * rhs[ 7]) + (lhs[14] * rhs[11]) + (lhs[15] * rhs[15]),
      ///////
    }});
}

//------------------------------------------------------------
template<typename T> /* friend */ Vec4<T> 
operator * (Mat4<T> const & lhs, Vec4<T> const & rhs) {
    return Vec4<T>(
        /*[x]*/ (lhs[ 0] * rhs.x) + (lhs[ 1] * rhs.y) + (lhs[ 2] * rhs.z) + (lhs[ 3] * rhs.w),
        /*[y]*/ (lhs[ 4] * rhs.x) + (lhs[ 5] * rhs.y) + (lhs[ 6] * rhs.z) + (lhs[ 7] * rhs.w),
        /*[z]*/ (lhs[ 8] * rhs.x) + (lhs[ 9] * rhs.y) + (lhs[10] * rhs.z) + (lhs[11] * rhs.w),
        /*[w]*/ (lhs[12] * rhs.x) + (lhs[13] * rhs.y) + (lhs[14] * rhs.z) + (lhs[15] * rhs.w)
    );
}

//------------------------------------------------------------
template<typename T> /* friend */ std::ostream & 
operator << (std::ostream & lhs, Mat4<T> const & rhs) {
    lhs << "Mat4\n-----------------\n";
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
                lhs << "[" << rhs.m_matrix[4 * x + y] << "] "; 
        }
          lhs << "\n";
    }
    lhs << "-----------------";
    return lhs;
}

//------------------------------------------------------------
template<typename T> float & 
Mat4<T>::operator [] (std::size_t index) {
    return m_matrix[index];
}

//------------------------------------------------------------
template<typename T> float const & 
Mat4<T>::operator [] (std::size_t index) const {
    return m_matrix[index];
}
} /* namespace djc_math */

