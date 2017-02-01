#include <cmath>
#include <iostream>

#ifndef Vec3_hpp
#define Vec3_hpp

namespace Maths {

    class Vec3 final {
    public:
        // member functions
        //---------------------------------------------------------
        //RAII
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        // getters
        float getX() const;
        float getY() const;
        float getZ() const;

        // vector opperations
        float length() const;
        float length2() const;
        void normalise();
        float dot(Vec3 const & vec) const;
        Vec3 cross(Vec3 const & vec);

        // unary opps
        Vec3 operator + () const;
        Vec3 operator - () const;
        
        // maths operators -  (non cost this, const vec || float scalar)
        Vec3 operator + (Vec3 const & vec);
        Vec3 operator - (Vec3 const & vec);
        Vec3 operator * (Vec3 const & vec);
        Vec3 operator / (Vec3 const & vec);
        Vec3 operator + (float scalar);
        Vec3 operator - (float scalar);
        Vec3 operator * (float scalar);
        Vec3 operator / (float scalar);

        // assignment operators (Vec3 [operator] Vec3)
        Vec3 & operator += (Vec3 const & vec);
        Vec3 & operator -= (Vec3 const & vec);
        Vec3 & operator *= (Vec3 const & vec);
        Vec3 & operator /= (Vec3 const & vec);
        Vec3 & operator += (float scalar);
        Vec3 & operator -= (float scalar);
        Vec3 & operator *= (float scalar);
        Vec3 & operator /= (float scalar);
        
        // non member - free functions
        //---------------------------------------------------------
        // friend free operators -  (scalar [operator] Vec3)
        friend Vec3 operator += (float lhs, Vec3 const & rhs);
        friend Vec3 operator -= (float lhs, Vec3 const & rhs);
        friend Vec3 operator *= (float lhs, Vec3 const & rhs);
        friend Vec3 operator /= (float lhs, Vec3 const & rhs);
        
        friend Vec3 operator + (float lhs, Vec3 const & rhs);
        friend Vec3 operator - (float lhs, Vec3 const & rhs);
        friend Vec3 operator * (float lhs, Vec3 const & rhs);
        friend Vec3 operator / (float lhs, Vec3 const & rhs);
        friend Vec3 operator + (Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 operator - (Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 operator * (Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 operator / (Vec3 const & lhs, Vec3 const & rhs);

        // free function versions of members
        friend float length2(Vec3 const & vec);
        friend float length(Vec3 const & vec);
        friend float distance(Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 getLongest(Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 normalise(Vec3 const & vec);
        friend float dot(Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 cross(Vec3 const & lhs, Vec3 const & rhs);

        // free function print
        friend std::ostream & operator << (std::ostream & lhs, Vec3 const & rhs);

    private:
        float m_data[3];
    };

    /* RAII */

    //------------------------------------------------------------
    Vec3::Vec3(float x, float y, float z)
    :
        m_data{x,y,z}
    {
    // empty
    }

    /* getters */

    //------------------------------------------------------------
    float
    Vec3::getX() const {
        return m_data[0];
    }

    //------------------------------------------------------------
    float 
    Vec3::getY() const {
        return m_data[1];
    }

    //------------------------------------------------------------
    float 
    Vec3::getZ() const {
        return m_data[2];
    }

    /* vector operations */

    //------------------------------------------------------------
    float 
    Vec3::length() const {
        return std::sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2]);
    }
    
    //------------------------------------------------------------
    float
    Vec3::length2() const {
        return m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2];
    }
    
    //------------------------------------------------------------
    void 
    Vec3::normalise() {
        float len = length();
        m_data[0]   /= len;
        m_data[1]   /= len;
        m_data[2]   /= len;
    }

    //------------------------------------------------------------
    float 
    Vec3::dot(Vec3 const & vec) const {
        return m_data[0] * vec.m_data[0] + m_data[1] * vec.m_data[1] + m_data[2] * m_data[2];
    }

    //------------------------------------------------------------
    Vec3
    Vec3::cross(Vec3 const & vec) {
        auto x = (m_data[1] * vec.m_data[2]) - (m_data[2] * vec.m_data[1]);
        auto y = (m_data[2] * vec.m_data[0]) - (m_data[0] * vec.m_data[2]);
        auto z = (m_data[0] * vec.m_data[1]) - (m_data[1] * vec.m_data[0]);
        return Vec3(x,y,z);
    }

    /* unary operators */

    //------------------------------------------------------------
    Vec3 
    Vec3::operator + () const {
        return *this;
    }

    //------------------------------------------------------------
    Vec3 
    Vec3::operator - () const {
        return Vec3(-m_data[0], -m_data[1], -m_data[2]);
    }

    /* maths operators */

    //------------------------------------------------------------
    Vec3
    Vec3::operator + (Vec3 const & vec) {
        return Vec3(m_data[0] + vec.m_data[0], m_data[1] + vec.m_data[1], m_data[2] + vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator - (Vec3 const & vec) {
        return Vec3(m_data[0] - vec.m_data[0], m_data[1] - vec.m_data[1], m_data[2] - vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator * (Vec3 const & vec) {
        return Vec3(m_data[0] * vec.m_data[0], m_data[1] * vec.m_data[1], m_data[2] * vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator / (Vec3 const & vec) {
        return Vec3(m_data[0] / vec.m_data[0], m_data[1] / vec.m_data[1], m_data[2] / vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator + (float scalar) {
        return Vec3(m_data[0] + scalar, m_data[1] + scalar, m_data[2] + scalar);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator - (float scalar) {
        return Vec3(m_data[0] - scalar, m_data[1] - scalar, m_data[2] - scalar);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator * (float scalar) {
        return Vec3(m_data[0] * scalar, m_data[1] * scalar, m_data[2] * scalar);
    }


    //------------------------------------------------------------
    Vec3
    Vec3::operator / (float scalar) {
        return Vec3(m_data[0] / scalar, m_data[1] / scalar, m_data[2] / scalar);
    }

    /* Vec3 assignment operators */

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator += (Vec3 const & vec) {
        m_data[0] += vec.m_data[0];
        m_data[1] += vec.m_data[1];
        m_data[2] += vec.m_data[2];
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator -= (Vec3 const & vec) {
        m_data[0] -= vec.m_data[0];
        m_data[1] -= vec.m_data[1];
        m_data[2] -= vec.m_data[2];
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator *= (Vec3 const & vec) {
        m_data[0] *= vec.m_data[0];
        m_data[1] *= vec.m_data[1];
        m_data[2] *= vec.m_data[2];
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator /= (Vec3 const & vec) {
        m_data[0] /= vec.m_data[0];
        m_data[1] /= vec.m_data[1];
        m_data[2] /= vec.m_data[2];
        return *this;
    }

    /* scalar assignment opperators */

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator += (float scalar) {
        m_data[0] += scalar;
        m_data[1] += scalar;
        m_data[2] += scalar;
        return *this;
    }

    //------------------------------------------------------------
    Vec3 &
    Vec3::operator -= (float scalar) {
        m_data[0] -= scalar;
        m_data[1] -= scalar;
        m_data[2] -= scalar;
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator *= (float scalar) {
        m_data[0] *= scalar;
        m_data[1] *= scalar;
        m_data[2] *= scalar;
        return *this;
    }

    //------------------------------------------------------------
    Vec3 &
    Vec3::operator /= (float scalar) {
        m_data[0] /= scalar;
        m_data[1] /= scalar;
        m_data[2] /= scalar;
        return *this;
    }

    /* free function operators - (scalar [operator] Vec3) */

    //------------------------------------------------------------
    inline Vec3
    operator += (float lhs, Vec3 const & rhs) {
        return Vec3(lhs + rhs.m_data[0], lhs + rhs.m_data[1], lhs + rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator -= (float lhs, Vec3 const & rhs) {
        return Vec3(lhs - rhs.m_data[0], lhs - rhs.m_data[1], lhs - rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator *= (float lhs, Vec3 const & rhs) {
        return Vec3(lhs * rhs.m_data[0], lhs * rhs.m_data[1], lhs * rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator /= (float lhs, Vec3 const & rhs) {
        return Vec3(lhs / rhs.m_data[0], lhs / rhs.m_data[1], lhs / rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator + (float lhs, Vec3 const & rhs) {
        return Vec3(lhs + rhs.m_data[0], lhs + rhs.m_data[1], lhs + rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator - (float lhs, Vec3 const & rhs) {
        return Vec3(lhs - rhs.m_data[0], lhs - rhs.m_data[1], lhs - rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator * (float lhs, Vec3 const & rhs) {
        return Vec3(lhs * rhs.m_data[0], lhs * rhs.m_data[1], lhs * rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator / (float lhs, Vec3 const & rhs) {
        return Vec3(lhs / rhs.m_data[0], lhs / rhs.m_data[1], lhs / rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator + (Vec3 const & lhs, Vec3 const & rhs) {
        return Vec3(lhs.m_data[0] + rhs.m_data[0], lhs.m_data[1] + rhs.m_data[1], lhs.m_data[2] + rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator - (Vec3 const & lhs, Vec3 const & rhs) {
        return Vec3(lhs.m_data[0] - rhs.m_data[0], lhs.m_data[1] - rhs.m_data[1], lhs.m_data[2] - rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator * (Vec3 const & lhs, Vec3 const & rhs) {
         return Vec3(lhs.m_data[0] * rhs.m_data[0], lhs.m_data[1] * rhs.m_data[1], lhs.m_data[2] * rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    operator / (Vec3 const & lhs, Vec3 const & rhs) {
         return Vec3(lhs.m_data[0] / rhs.m_data[0], lhs.m_data[1] / rhs.m_data[1], lhs.m_data[2] / rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline std::ostream &
    operator << (std::ostream & lhs, Vec3 const & rhs) {
        lhs << "Vec3([x:" << rhs.m_data[0] << "], [y: " << rhs.m_data[1] << "], [z: " << rhs.m_data[2] << "])\n";
        return lhs;
    }

    /* free function versions of member functions */

     //------------------------------------------------------------
    inline float
    length(Vec3 const & vec) {
        return std::sqrt(vec.m_data[0] * vec.m_data[0] + vec.m_data[1] * vec.m_data[1] + vec.m_data[2] * vec.m_data[2]);
    }

    //------------------------------------------------------------
    inline float
    length2(Vec3 const & vec) {
        return vec.m_data[0] * vec.m_data[0] + vec.m_data[1] * vec.m_data[1] + vec.m_data[2] * vec.m_data[2];
    }

    //------------------------------------------------------------
    inline Vec3
    getLongest(Vec3 const & lhs, Vec3 const & rhs) {
        if(Maths::length2(lhs) > Maths::length2(rhs)) {
            return lhs;
        } else {
            return rhs;
        }
    }

    //------------------------------------------------------------
    inline float
    distance(Vec3 const & lhs, Vec3 const & rhs) {
        Vec3 temp =  lhs - rhs;
        return temp.length();
    }
    
    //------------------------------------------------------------
    inline Vec3
    normalise(Vec3 const & vec) {
        float len = length(vec);
        return Vec3(vec.m_data[0] / len, vec.m_data[1] / len, vec.m_data[2] / len);
    }
    
    //------------------------------------------------------------
    inline float
    dot(Vec3 const & lhs, Vec3 const & rhs) {
        return (lhs.m_data[0] * rhs.m_data[0] + lhs.m_data[1] * rhs.m_data[1] + lhs.m_data[2] * rhs.m_data[2]);
    }

    //------------------------------------------------------------
    inline Vec3
    cross(Vec3 const & lhs, Vec3 const & rhs) {
        auto x = (lhs.m_data[1] * rhs.m_data[2]) - (lhs.m_data[2] * rhs.m_data[1]);
        auto y = (lhs.m_data[2] * rhs.m_data[0]) - (lhs.m_data[0] * rhs.m_data[2]);
        auto z = (lhs.m_data[0] * rhs.m_data[1]) - (lhs.m_data[1] * rhs.m_data[0]);
        return Vec3(x,y,z);
    }
} // namespace maths
#endif // Vec3_hpp
