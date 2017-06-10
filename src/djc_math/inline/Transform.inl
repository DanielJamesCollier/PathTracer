namespace djc_math {

//-------------------
/*      Mat3       */
//-------------------

//------------------------------------------------------------
template<typename T> inline Mat3<T>
createMat3IdentityMatrix() {
    static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, 
                  "createMat3IdentityMatrix() only accepts floating point, and integral values");

    return Mat3<T>(std::array<T, 9> {{ 
        1,  0,  0,
        0,  1,  0,
        0,  0,  1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat3<T>
createMat3RotationMatrix(Vec3<T> const & rotation) {
     static_assert(std::is_floating_point<T>::value,
                  "createMat3RotationMatrix() only accepts floating point values");

    T xSin = std::sin(rotation.x);
    T xCos = std::cos(rotation.x);

    T ySin = std::sin(rotation.y);
    T yCos = std::cos(rotation.y);

    T zSin = std::sin(rotation.z);
    T zCos = std::cos(rotation.z);
    
    Mat3<T> rotX(std::array<T, 9> {{
        1,    0,       0,
        0,    xCos,    -xSin,
        0,    xSin,    xCos,
    }});

    Mat3<T> rotY(std::array<T, 9>{{
        yCos,    0,    ySin,
        0,       1,    0,
        -ySin,   0,    yCos
    }});

    Mat3<T> rotZ(std::array<T, 9>{{
        zCos,    -zSin,   0,
        zSin,    zCos,    0,
        0,       0,       1
    }});
   
    return rotX * rotY * rotZ;
}

// use existing

//-------------------
/*      Mat4       */
//-------------------

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4IdentityMatrix() {
    static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, 
                  "createMat4IdentityMatrix() only accepts floating point, and integral values");

    return Mat4<T>(std::array<T, 16>{{
        1,    0,    0,    0,
        0,    1,    0,    0,
        0,    0,    1,    0,
        0,    0,    0,    1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4TranslationMatrix(Vec3<T> const & vec) {
    static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, 
                  "createMat4TranslationMatrix() only accepts floating point, and integral values");    

    return Mat4<T>(std::array<T, 16>{{
        1,    0,    0,    vec.x,
        0,    1,    0,    vec.y,
        0,    0,    1,    vec.z,
        0,    0,    0,    1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4RotationMatrix(Vec3<T> const & rotation) {
     static_assert(std::is_floating_point<T>::value,
                  "createMat4RotationMatrix() only accepts floating point values"); 

    T xSin(std::sin(rotation.x));
    T xCos(std::cos(rotation.x));

    T ySin(std::sin(rotation.y));
    T yCos(std::cos(rotation.y));

    T zSin(std::sin(rotation.z));
    T zCos(std::cos(rotation.z));

    Mat3<T> rotX(std::array<T, 9>{{
        1,    0,       0,    
        0,    xCos,    -xSin,
        0,    xSin,    xCos
    }});

    Mat3<T> rotY(std::array<T, 9>{{
        yCos,     0,    ySin,
        0,        1,    0,
        -ySin,    0,    yCos
    }});

    Mat3<T> rotZ(std::array<T, 9>{{
        zCos,    -zSin,  0,
        zSin,    zCos,   0,
        0,       0,      1
    }});

    return Mat4<T>((rotX * rotY * rotZ), static_cast<T>(1));
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ScaleMatrix(Vec3<T> const & vec) {
    static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, 
                "createMat4ScaleMatrix() only accepts floating point, and integral values"); 

     return Mat4<T>(std::array<T, 16>{{
        vec.x,    0,        0,        0,
        0,        vec.y,    0,        0,
        0,        0,        vec.z,    0,
        0,        0,        0,        1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ModelMatrix(Vec3<T> const & position, Vec3<T> const & rotation, Vec3<T> const & scale) {
    Mat4<T> _translation = createMat4TranslationMatrix<T>(position);
    Mat4<T> _rotation    = createMat4RotationMatrix<T>(rotation);
    Mat4<T> _scale       = createMat4ScaleMatrix<T>(scale);
    return _translation * _rotation * _scale;
}

//------------------------------------------------------------
template<typename T, typename U> inline Mat4<U> // @todo : needs looking at
createMat4OrthographicMatrix(U width, U height, T zNear, T zFar) { 
    T a(1.0f / static_cast<T>(width));
    T b(1.0f / static_cast<T>(height));
    T c(-(2.0f / (zFar - zNear)));
    T d(-((zFar + zNear) / (zFar - zNear)));

    return Mat4<U>(std::array<U, 16>{{
        a,    0,    0,    0,
        0,    b,    0,    0,
        0,    0,    c,    0,
        0,    0,    d,    1,
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ProjectionMatrix(T fov, T aspect, T near, T far) {
    static_assert(std::is_floating_point<T>::value, "createMat4ProjectionMatrix only accepts floating point values");

    T const rad = fov;
    T const tanHalfFovy = std::tan(rad / static_cast<T>(2));

    T sX(static_cast<T>(1) / (aspect * tanHalfFovy));
    T sY(static_cast<T>(1) / (tanHalfFovy));
    T sZ(- (far + near) / (far - near));
    T sA(static_cast<T>(-1));
    T sB(- (static_cast<T>(2) * far * near) / (far - near));
    
    T zero(static_cast<T>(0));

    return Mat4<T>(std::array<T, 16>{{
         sX,    0,     0,     0,
         0,     sY,    0,     0,
         0,     0,     sZ,    sB,
         0,     0,     sA,    0
    }});

    // most basic projection matrix - projecs Vec4 to [z]:-1 plane
    // return Mat4<T>(std::array<T, 16>{{
    //       1, 0,  0, 0,
    //       0, 1,  0, 0,
    //       0, 0,  1, 0,
    //       0, 0, -1, 0
    // }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T> 
createMat4ViewMatrix(Vec3<T> const & eye, Vec3<T> const & centre, Vec3<T> const & up) {

    Vec3<T> forward(0, 0,-1);
    Vec3<T> right(1, 0, 0);

    return Mat4<T>(std::array<T, 16>{{
           right.x,       right.y,       right.z,    -eye.x,
           up.x,          up.y,          up.z,       -eye.y,
           -forward.x,    -forward.y,    -forward.z, -eye.z,
           0,             0,              0,          1
    }});

}

//----------------------w--------------------------------------
template<typename T> inline Mat4<T>
createMat4BirdsEyeViewMatrix() {
    return Mat4<T>(std::array<T, 16> {{
        1,    0,    0,     0,
        0,    0,    -1,    0,
        0,    1,    0,     0,
        0,    0,    0,     1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ScreenSpaceTransform(T halfWidth, T halfHeight) {
    return Mat4<T>(std::array<T, 16>{{ 
          halfWidth,    0,              0,    0,
          0,            -halfHeight,    0,    0,
          0,            0,              1,    0,
          halfWidth,    halfHeight,     0,    1
    }});
}

//------------------------------------------------------------
template<typename T> inline void 
setMat4Identity(Mat4<T> & matrix) {
    matrix = Mat4<T>(std::array<T, 16>{{ 
        1,    0,    0,    0,
        0,    1,    0,    0,
        0,    0,    1,    0,
        0,    0,    0,    1
    }});
}

//-------------------//
/*      Other        */
//-------------------//

//------------------------------------------------------------
template<typename T> inline void
transform(Vec4<T> & vec, Mat4<T> const & transformation) {
    vec = transformation * vec;
}

//------------------------------------------------------------
template<typename T> inline Mat3<T>
rotate(T angle, Vec3<T> const & axis) {
    return createMat3RotationMatrix<T>(axis * angle);
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
rotate(T angle, Vec4<T> const & axis) {
    return createMat4RotationMatrix<T>(axis * angle);
}

} /* namespace djc_math */