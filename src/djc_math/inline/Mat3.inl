namespace djc_math {

//------------------------------------------------------------
template<typename T>
Mat3<T>::Mat3() {
    m_matrix.fill(T());
}

//------------------------------------------------------------
template<typename T>
Mat3<T>::Mat3(std::array<T, 9> matrix)
: m_matrix(matrix) 
{
    // empty
}

// //------------------------------------------------------------
// template<typename T> void
// clear() {
//     m_matrix.fill(T());
// }

// //------------------------------------------------------------
// template<typename T> void
// clear(T value) {
//     m_matrix.fill(value);
// }

//------------------------------------------------------------
template<typename T> /* friend */ Mat3<T> 
operator * (Mat3<T> const & lhs, Mat3<T> const & rhs) {
    //-------------------- 
    //   [0]  [1]  [2] 
    //   [3]  [4]  [5]   
    //   [6]  [7]  [8] 
    //---------------------
    
    return Mat3<T>(std::array<T, 9>{{
        ///////
        /*[0]*/ (lhs[0] * rhs[0]) + (lhs[1] * rhs[3]) + (lhs[2] * rhs[6]),
        /*[1]*/ (lhs[0] * rhs[1]) + (lhs[1] * rhs[4]) + (lhs[2] * rhs[7]),
        /*[2]*/ (lhs[0] * rhs[2]) + (lhs[1] * rhs[5]) + (lhs[2] * rhs[8]),
        ///////
        /*[0]*/ (lhs[3] * rhs[0]) + (lhs[4] * rhs[3]) + (lhs[5] * rhs[6]),
        /*[1]*/ (lhs[3] * rhs[1]) + (lhs[4] * rhs[4]) + (lhs[5] * rhs[7]),
        /*[2]*/ (lhs[3] * rhs[2]) + (lhs[4] * rhs[5]) + (lhs[5] * rhs[8]),
        ///////
        /*[0]*/ (lhs[6] * rhs[0]) + (lhs[7] * rhs[3]) + (lhs[8] * rhs[6]),
        /*[1]*/ (lhs[6] * rhs[1]) + (lhs[7] * rhs[4]) + (lhs[8] * rhs[7]),
        /*[2]*/ (lhs[6] * rhs[2]) + (lhs[7] * rhs[5]) + (lhs[8] * rhs[8]),
        ///////
    }});
}

//------------------------------------------------------------
template<typename T> Vec3<T>
operator * (Mat3<T> const & lhs, Vec3<T> const & rhs) {
    return Vec3<T>(
        /*[x]*/ (lhs[0] * rhs.x) + (lhs[1] * rhs.y) + (lhs[2] * rhs.z),
        /*[y]*/ (lhs[3] * rhs.x) + (lhs[4] * rhs.y) + (lhs[5] * rhs.z),
        /*[z]*/ (lhs[6] * rhs.x) + (lhs[7] * rhs.y) + (lhs[8] * rhs.z));
}

//------------------------------------------------------------
template<typename T> /* friend */ std::ostream & 
operator << (std::ostream & lhs, Mat3<T> const & rhs) {

    lhs << " Mat3\n-----------------\n";
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
                lhs << "[" << rhs.m_matrix[3 * x + y] << "] "; 
        }
        lhs << "\n";
    }
    lhs << "-----------------";
    return lhs;
}

//------------------------------------------------------------
template<typename T> float & 
Mat3<T>::operator [] (std::size_t index) {
    return m_matrix[index];
}

//------------------------------------------------------------
template<typename T> float const & 
Mat3<T>::operator [] (std::size_t index) const {
    return m_matrix[index];
}

} /* namespace djc_math */