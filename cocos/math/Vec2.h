/**
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2014-2015 Chukong Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 */

#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include <algorithm>
#include <functional>
#include <math.h>
#include "math/CCMathBase.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_MATH_BEGIN

/** @~english Clamp a value between from and to.
 * @~chinese ���ڸ��������Ʒ�Χ���������ֵ������ֵ��������ֵ����[min_inclusive, max_inclusive]�����ڡ�
 *
 * @param value @~english A value to clamp. @~chinese Ҫ���Ƶ�ֵ��
 * @param min_inclusive @~english The specified minimum range. @~chinese ���Ʒ�Χ���ޡ�
 * @param max_inclusive @~english The specified maximum range. @~chinese ���Ʒ�Χ���ޡ�
 *
 * @return @~english The clamped value for the value parameter.@~chinese ����value������ֵ��
 */

inline float clampf(float value, float min_inclusive, float max_inclusive)
{
    if (min_inclusive > max_inclusive) {
        std::swap(min_inclusive, max_inclusive);
    }
    return value < min_inclusive ? min_inclusive : (value < max_inclusive? value : max_inclusive);
}

class Mat4;

/** @~english Defines a 2-element floating point vector.
 * @~chinese ������һ����ά����������
 */
class CC_DLL Vec2
{
public:

    /** @~english The x coordinate.
     * @~chinese x���ꡣ
     */
    float x;

    /** @~english The y coordinate.
     * @~chinese y���ꡣ
     */
    float y;

    /** 
     * @~english Constructs a new vector initialized to all zeros.
     * @~chinese ����һ���µ����������г�Ա���Գ�ʼ��Ϊ�㡣
     */
    Vec2();

    /** 
     * @~english Constructs a new vector initialized to the specified values.
     * @~chinese ����һ���µ�����������ʼ����Ա����Ϊָ����ֵ��
     * 
     * @param xx @~english The x coordinate. @~chinese x���ꡣ
     * @param yy @~english The y coordinate. @~chinese y���ꡣ
     */
    Vec2(float xx, float yy);

    /**
     * @~english Constructs a new vector from the values in the specified array.
     * @~chinese �ø��������е�ֵ����һ���µ�������
     * 
     * @param array @~english An array containing the elements of the vector in the order x, y.
     * @~chinese һ�����ΰ���x��y���������顣
     */
    Vec2(const float* array);

    /**
     * @~english Constructs a vector that describes the direction between the specified points.
     * @~chinese ����һ����p1ָ���p2��������
     * 
     * @param p1 @~english The first point. @~chinese ��һ�㡣
     * @param p2 @~english The second point. @~chinese �ڶ��㡣
     */
    Vec2(const Vec2& p1, const Vec2& p2);

    /**
     * @~english Constructs a new vector that is a copy of the specified vector.
     * @~chinese �������캯����
     * 
     * @param copy @~english The vector to copy. @~chinese ��������������
     */
    Vec2(const Vec2& copy);

    /** @~english Destructor. @~chinese ����������*/
    ~Vec2();

    /** 
     * @~english Indicates whether this vector contains all zeros.
     * @~chinese ���������з���ֵ�Ƿ��Ϊ0.0f��
     * 
     * @return @~english true if this vector contains all zeros, false otherwise.
     * @~chinese ������������з���ֵ��Ϊ0.0f�򷵻�true�����򷵻�false��
     */
    inline bool isZero() const;

    /**
     * @~english Indicates whether this vector contains all ones.
     * @~chinese ���������з���ֵ�Ƿ��Ϊ1.0f��
     * 
     * @return @~english true if this vector contains all ones, false otherwise.
     * @~chinese ������������з���ֵ��Ϊ1.0f���򷵻�true�����򷵻�false��
     */
    inline bool isOne() const;

    /**
     * @~english Returns the angle (in radians) between the specified vectors.
     * @~chinese ���ظ�������������֮��ĽǶ�(����)��
     * 
     * @param v1 @~english The first vector. @~chinese ��һ��������
     * @param v2 @~english The second vector. @~chinese �ڶ���������
     *
     * @return @~english The angle between the two vectors (in radians).
     * @~chinese ��������֮��ĽǶ�(����)��
     */
    static float angle(const Vec2& v1, const Vec2& v2);

    /**
     * @~english Adds the elements of the specified vector to this one.
     * @~chinese ��ָ��������ֵ��Ӹ����������
     * 
     * @param v @~english The vector to add. @~chinese ��ӵ�������
     */
    inline void add(const Vec2& v);

    /**
     * @~english Adds the specified vectors and stores the result in dst.
     * @~chinese ����������v1������v2��ӣ�������浽����dst�� 
     * 
     * @param v1 @~english The first vector. @~chinese ��һ��������
     * @param v2 @~english The second vector. @~chinese �ڶ���������
     * @param dst @~english A vector to store the result in. @~chinese ���Ա�������������
     */
    static void add(const Vec2& v1, const Vec2& v2, Vec2* dst);

    /**
     * @~english Clamps this vector within the specified range.
     * @~chinese ������ֵ������ָ�������ڡ�
     * 
     * @param min @~english The minimum value. @~chinese ��Сֵ�� 
     * @param max @~english The maximum value. @~chinese ���ֵ�� 
     */
    void clamp(const Vec2& min, const Vec2& max);

    /**
     * @~english Clamps the specified vector within the specified range and returns it in dst.
     * @~chinese ��ָ������v������[min,max]�����ڣ�����dst��������
     * 
     * @param v @~english The vector to clamp. @~chinese �����޶���������
     * @param min @~english The minimum value. @~chinese ��Сֵ��
     * @param max @~english The maximum value. @~chinese ���ֵ��
     * @param dst @~english A vector to store the result in. @~chinese һ�����Ա�������������
     */
    static void clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2* dst);

    /**
     * @~english Returns the distance between this point and v.
     * @~chinese �����������Ŀ���ľ��롣
     * 
     * @param v @~english The other point. @~chinese ��һ���㡣
     * 
     * @return @~english The distance between this point and v.
     * @~chinese �������Ŀ���v�ľ��롣
     * 
     * @see distanceSquared
     */
    float distance(const Vec2& v) const;

    /** @~english
     * Returns the squared distance between this point and v.
     *
     * When it is not necessary to get the exact distance between
     * two points (for example, when simply comparing the
     * distance between different points), it is advised to use
     * this method instead of distance.
     *
     * @~chinese ���ر��������Ŀ���v�ľ����ƽ����
     * �������Ҫ�õ�������֮���׼ȷ���룬 ����ֻ�ǱȽ�����֮��ľ����С��ʱ�� 
     * ����ʹ���������������distance������
     * 
     * @param v @~english The other point. @~chinese ��һ���㡣
     * 
     * @return @~english The squared distance between this point and v.
     * @~chinese ����������Ŀ���v�ľ����ƽ����
     * @see distance
     */
    inline float distanceSquared(const Vec2& v) const;

    /** 
     * @~english Returns the dot product of this vector and the specified vector.
     * @~chinese ���ر�������ָ������v�ĵ��
     * 
     * @param v @~english The vector to compute the dot product with.
     * @~chinese ��������������һ������
     * 
     * @return @~english The dot product. @~chinese �����
     */
    inline float dot(const Vec2& v) const;

    /**
     * @~english Returns the dot product between the specified vectors.
     * @~chinese ��������ָ�������ĵ����
     * 
     * @param v1 @~english The first vector. @~chinese ��һ��������
     * @param v2 @~english The second vector. @~chinese �ڶ���������
     * 
     * @return @~english The dot product between the vectors. @~chinese �����ĵ����
     */
    static float dot(const Vec2& v1, const Vec2& v2);

    /**
     * @~english Computes the length of this vector.
     * @~chinese ������������ĳ��ȡ�
     * 
     * @return @~english The length of the vector. @~chinese ��������ĳ��ȡ�
     * @see lengthSquared
     */
    float length() const;

    /** @~english
     * Returns the squared length of this vector.
     *
     * When it is not necessary to get the exact length of a
     * vector (for example, when simply comparing the lengths of
     * different vectors), it is advised to use this method
     * instead of length.
     *
     * @~chinese ������Ҫ��ȡ׼ȷ����������ʱ�� ����ֻ�Ǽ򵥱Ƚϲ�ͬ����֮��ĳ��ȴ�С�� 
     * ����ʹ�ñ���������length��
     * 
     * @return @~english The squared length of the vector.
     * @~chinese �����ĳ��ȵ�ƽ����
     * @see length
     */
    inline float lengthSquared() const;

    /** @~english Negates this vector. @~chinese �����󸺡�*/
    inline void negate();

    /** @~english
     * Normalizes this vector.
     *
     * This method normalizes this Vec2 so that it is of
     * unit length (in other words, the length of the vector
     * after calling this method will be 1.0f). If the vector
     * already has unit length or if the length of the vector
     * is zero, this method does nothing.
     * 
     * @~chinese 
     * ʹ���������һ��Ϊ��λ���ȣ����������������������Ϊ1.0f���� 
     * ��������Ѿ��ǵ�λ���Ȼ��߳���Ϊ�㣬 ������������κ����á�
     */
    void normalize();

    /** @~english Get the normalized vector. @~chinese �õ���һ��������*/
    Vec2 getNormalized() const;

    /** 
     * @~english Scales all elements of this vector by the specified value.
     * @~chinese ��ָ��������ϵ���������ĸ������������š�
     * 
     * @param scalar @~english The scalar value. @~chinese ����ϵ����
     */
    inline void scale(float scalar);

    /** @~english
     * Scales each element of this vector by the matching component of scale.
     *
     * @~chinese 
     * ��scale������x���������ű�������x��������scale������y���������ű�������y������
     * 
     * @param scale @~english The vector to scale by. @~chinese �������ӡ� 
     */
    inline void scale(const Vec2& scale);

    /** 
     * @~english Rotates this vector by angle (specified in radians) around the given point.
     * @~chinese ������ָ����point��תangle�ȣ�����angle�ĵ�λΪ����
     * 
     * @param point @~english The point to rotate around. @~chinese ��תê�㡣
     * @param angle @~english The angle to rotate by (in radians). @~chinese ��ת�Ƕ�(��λ������)�� 
     */
    void rotate(const Vec2& point, float angle);

    /**
     * @~english Sets the elements of this vector to the specified values.
     * @~chinese ���������ķ���ֵΪָ��ֵ��
     * 
     * @param xx @~english The new x coordinate. @~chinese �µ�x���ꡣ 
     * @param yy @~english The new y coordinate. @~chinese �µ�y���ꡣ
     */
    inline void set(float xx, float yy);

    /**
     * @~english Sets the elements of this vector from the values in the specified array.
     * @~chinese ������������ķ���Ϊָ�������е�ֵ��
     * 
     * @param array @~english An array containing the elements of the vector in the order x, y.
     * @~chinese һ�����ΰ���x��y���������顣
     */
    void set(const float* array);

    /**
     * @~english Sets the elements of this vector to those in the specified vector.
     * @~chinese ��ָ�������ĸ�����ֵ���ø���������
     * 
     * @param v @~english The vector to copy. @~chinese ��������������
     */
    inline void set(const Vec2& v);

    /**
     * @~english Sets this vector to the directional vector between the specified points.
     * @~chinese ��������ֵΪ����ָ����֮���������
     * 
     * @param p1 @~english The first point. @~chinese ��һ�㡣
     * @param p2 @~english The second point. @~chinese �ڶ��㡣
     */
    inline void set(const Vec2& p1, const Vec2& p2);

    /**
     * @~english Sets the elements of this vector to zero.
     * @~chinese ��������ĸ���������Ϊ�㡣
     */
    inline void setZero();

    /** @~english
     * Subtracts this vector and the specified vector as (this - v)
     * and stores the result in this vector.
     *
     * @~chinese ���������ĸ�������ָ�������Ķ�Ӧ����ֵ�����档
     * 
     * @param v @~english The vector to subtract.
     * @~chinese ���ڼ�ȥ��������
     */
    inline void subtract(const Vec2& v);

    /**@~english
     * Subtracts the specified vectors and stores the result in dst.
     * The resulting vector is computed as (v1 - v2).
     *
     * @~chinese 
     * ��������v1��ȥv2���ѽ������������dst
     * 
     * @param v1 @~english The first vector.
     * @~chinese ��һ��������
     * @param v2 @~english The second vector.
     * @~chinese �ڶ���������
     * @param dst @~english The destination vector.
     * @~chinese �����
     */
    static void subtract(const Vec2& v1, const Vec2& v2, Vec2* dst);

    /** @~english
     * Updates this vector towards the given target using a smoothing function.
     * The given response time determines the amount of smoothing (lag). A longer
     * response time yields a smoother result and more lag. To force this vector to
     * follow the target closely, provide a response time that is very small relative
     * to the given elapsed time.
     *
     * @~chinese 
     * ƽ�����������ĵ�ǰλ�ã�ָ��Ŀ��������
     * responseTime������ƽ��ʱ��������ֵԽ����Խƽ���� ��Ӧ���ӳ�ʱ��Խ����
     * ���ϣ����������target������ �ṩһ�����elapsedTimeС�ܶ��responseTimeֵ���ɡ�
     * 
     * @param target @~english target value.
     * @~chinese Ŀ��������
     * @param elapsedTime @~english elapsed time between calls.
     * @~chinese ����ʱ�䡣
     * @param responseTime @~english response time (in the same units as elapsedTime).
     * @~chinese ��Ӧʱ��(ʱ�䵥λ��elapsedTimeһ��)��
     */
    inline void smooth(const Vec2& target, float elapsedTime, float responseTime);

    /** @~english
     * Calculates the sum of this vector with the given vector.
     * Note: this does not modify this vector.
     * 
     * @~chinese �����ӷ������������������v�ĺ�
     * ע��:�Ⲣ���޸�ԭ������ֵ��
     * 
     * @param v @~english The vector to add. @~chinese ���ӵ�������
     * @return @~english The vector sum. @~chinese �����͡� 
     */
    inline const Vec2 operator+(const Vec2& v) const;

    /**
     * @~english Adds the given vector to this vector.
     * @~chinese �����ӷ������������������v�ĺͣ�����������ڸ������в����ء�
     * 
     * @param v @~english The vector to add. @~chinese ���ӵ�������
     * 
     * @return @~english This vector, after the addition occurs.
     * @~chinese �����͡�
     */
    inline Vec2& operator+=(const Vec2& v);

    /**
     * @~english Calculates the difference of this vector with the given vector.
     * Note: this does not modify this vector.
     * @~chinese �������������������������v�Ĳ�
     * ע��:�Ⲣ���޸�ԭ������ֵ��
     * 
     * @param v @~english The vector to minus. @~chinese ���ڼ�ȥ��������
     *
     * @return @~english The vector difference. @~chinese ���������
     */
    inline const Vec2 operator-(const Vec2& v) const;

    /**
     * @~english Subtracts the given vector from this vector.
     * @~chinese �������������������������v�Ĳ����������ڸ������в����ء�
     * 
     * @param v @~english The vector to subtract. @~chinese ���ڼ�ȥ��������
     * 
     * @return @~english This vector, after the subtraction occurs. @~chinese ���������
     */
    inline Vec2& operator-=(const Vec2& v);

    /**@~english
     * Calculates the negation of this vector.
     * Note: this does not modify this vector.
     * @~chinese ��������
     * ע��:�Ⲣ���޸�ԭ������ֵ��
     * 
     * @return @~english The negation of this vector. @~chinese ��������
     */
    inline const Vec2 operator-() const;

    /** @~english
     * Calculates the scalar product of this vector with the given value.
     * Note: this does not modify this vector.
     * @~chinese ���������������ϵ���ĳ˻���
     * ע��:�Ⲣ���޸�ԭ������ֵ��
     * 
     * @param s @~english The value to scale by. @~chinese ����ϵ����
     * 
     * @return @~english The scaled vector. @~chinese ���ź��������
     */
    inline const Vec2 operator*(float s) const;

    /**@~english
     * Scales this vector by the given value. 
     * @~chinese  ���������������ϵ���ĳ˻�������������浽��������
     * 
     * @param s @~english The value to scale by. @~chinese ����ϵ����
     * 
     * @return @~english This vector, after the scale occurs. @~chinese ���ź��������
     */
    inline Vec2& operator*=(float s);
    
    /**@~english
     * Returns the components of this vector divided by the given constant
     * Note: this does not modify this vector.
     * @~chinese ������������������̡�
     * ע��:�Ⲣ���޸�ԭ������ֵ��
     * 
     * @param s @~english the constant to divide this vector with
     * @~chinese ����Ҫ���ĳ�����
     * @return @~english the result is this vector divided by the given constant.
     * @~chinese ��������������
     */
    inline const Vec2 operator/(float s) const;

    /**
     * @~english Determines if this vector is less than the given vector.
     * @~chinese �жϸ������Ƿ�С�ڸ�������v��
     * 
     * @param v @~english The vector to compare against. @~chinese Ҫ�Ƚϵ�������
     * 
     * @return @~english True if this vector is less than the given vector, false otherwise.
     * @~chinese ���������С�ڸ�������������true�����򷵻�false��
     */
    inline bool operator<(const Vec2& v) const;
    
    /**
     * @~english Determines if this vector is greater than the given vector.
     * @~chinese �жϸ������Ƿ���ڸ�������v��
     * 
     * @param v @~english The vector to compare against. @~chinese Ҫ�Ƚϵ�������
     * 
     * @return @~english True if this vector is greater than the given vector, false otherwise.
     * @~chinese ������������ڸ�������������true�����򷵻�false��
     */
    inline bool operator>(const Vec2& v) const;

    /**
     * @~english Determines if this vector is equal to the given vector.
     * @~chinese �жϸ������Ƿ���ڸ�������v��
     * 
     * @param v @~english The vector to compare against. @~chinese Ҫ�Ƚϵ�������
     * 
     * @return @~english True if this vector is equal to the given vector, false otherwise.
     * @~chinese ������������ڸ�������������true�����򷵻�false��
     */
    inline bool operator==(const Vec2& v) const;

    /**
     * @~english Determines if this vector is not equal to the given vector.
     * @~chinese �жϸ������Ƿ񲻵��ڸ�������v��
     * 
     * @param v @~english The vector to compare against. @~chinese Ҫ�Ƚϵ�������
     * 
     * @return @~english True if this vector is not equal to the given vector, false otherwise.
     * @~chinese ��������������ڸ�������������true�����򷵻�false��
     */
    inline bool operator!=(const Vec2& v) const;

    //code added compatible for Point
public:
    /**
     * @~english Sets the elements of this point to the specified values.
     * @~chinese ���øõ������ֵΪָ��ֵ��
     * 
     * @param xx @~english The new x coordinate. @~chinese �µ�x���ꡣ
     * @param yy @~english The new y coordinate. @~chinese �µ�y���ꡣ
     * @js NA
     * @lua NA
     */
    inline void setPoint(float xx, float yy);

    /**
     * @~english Determines if this point is equal to the given point.
     * @~chinese �жϸõ��Ƿ����Ŀ��㡣
     * 
     * @param target @~english The point to compare against. @~chinese Ҫ�Ƚϵ�������
     * 
     * @return @~english True if this point is equal to the given point, false otherwise.
     * @~chinese ������������ڸ�������������true�����򷵻�false��
     * @js NA
     */
    bool equals(const Vec2& target) const;
    
    /** @returns @~english if points have fuzzy equality which means equal with some degree of variance.
     * @~chinese �жϵ��Ƿ���Ŀ���һ��ƫ�Χ�ڡ�
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    bool fuzzyEquals(const Vec2& target, float variance) const;

    /** @~english Calculates distance between point an origin.
     * @~chinese ����õ㵽ԭ��ľ��롣
     *
     * @return @~english distance between two points. @~chinese ������롣
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** @~english Calculates the square length of a Vec2 (not calling sqrt() )
     * @~chinese ����õ㵽ԭ������ƽ����
     *
     * @return @~english the square of distance. @~chinese �����ƽ����
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** @~english Calculates the square distance between two points (not calling sqrt() )
     * @~chinese ����õ㵽����������ƽ����
     *
     * @return @~english the square of distance. @~chinese �����ƽ����
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistanceSq(const Vec2& other) const {
        return (*this - other).getLengthSq();
    };

    /** @~english Calculates the distance between two points
     * @~chinese ����õ㵽������ľ��롣
     *
     * @return @~english distance between two points. @~chinese ������롣
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistance(const Vec2& other) const {
        return (*this - other).getLength();
    };

    /** @returns @~english the angle in radians between this vector and the x axis
     * @~chinese ��ȡ��������x��ļнǣ����ȣ���
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns @~english the angle in radians between two vector directions
     * @~chinese ��ȡ����������������ļнǣ����ȣ���
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    float getAngle(const Vec2& other) const;

    /** @~english Calculates cross product of two vectors.
     * @~chinese ����������������������������
     *
     * @return @~english the cross product. @~chinese ��������
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float cross(const Vec2& other) const {
        return x*other.y - y*other.x;
    };

    /** @~english Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     * @~chinese �����������ʱ����ת90�ȵ���������
     * @return @~english new vector. @~chinese ��������
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 getPerp() const {
        return Vec2(-y, x);
    };
    
    /** @~english Calculates midpoint between two points.
     * @~chinese ��������֮������ĵ㡣
     * @return @~english midpoint. @~chinese ���ĵ㡣
     * @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vec2 getMidpoint(const Vec2& other) const
    {
        return Vec2((x + other.x) / 2.0f, (y + other.y) / 2.0f);
    }
    
    /** @~english Clamp a point between from and to.
     * @~chinese ��ȡ�����������Ʒ�Χ�ڵ����Ƶ㡣
     * @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vec2 getClampPoint(const Vec2& min_inclusive, const Vec2& max_inclusive) const
    {
        return Vec2(clampf(x,min_inclusive.x,max_inclusive.x), clampf(y, min_inclusive.y, max_inclusive.y));
    }
    
    /** @~english Run a math operation function on each point component
     * absf, floorf, ceilf, roundf
     * any function that has the signature: float func(float);
     * For example: let's try to take the floor of x,y
     * p.compOp(floorf);
     *
     * @~chinese �Ըõ������ĸ�����ִ�и������������㣬�磺
     * absf��fllorf ceilf roundf
     * ����:��x,y����floor���㣬����� p.compOp(floorf)
     * @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vec2 compOp(std::function<float(float)> function) const
    {
        return Vec2(function(x), function(y));
    }

    /** @~english Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     * @~chinese ��������v˳ʱ����ת90�Ⱥ��ֵ��
     *
     * @return @~english Vec2 the result of rotated vector. @~chinese ��ת���������
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 getRPerp() const {
        return Vec2(y, -x);
    };

    /** @~english Calculates the projection of this over other.
     * @~chinese �������������һ����other�ϵ�ͶӰ��
     *
     * @param other @~english the other vector.  @~chinese ��һ��������
     * @return @~english the projection. @~chinese ͶӰ��
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 project(const Vec2& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** @~english Complex multiplication of two points ("rotates" two points).
     * @~chinese ����������Ƹ���������ת���õ�������
     *
     * @return @~english Vec2 vector with an angle of this.getAngle() + other.getAngle(),
     * and a length of this.getLength() * other.getLength().
     * @~chinese ��ת���������ĽǶȵ��ڣ�this.getAngle()+ other.getAngle(),
     * ���ȵ��ڣ�this.getLength����()* other.getLength()��
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 rotate(const Vec2& other) const {
        return Vec2(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** @~english Unrotates two points.
     * @~chinese ����������Ƹ���������תǰ��������
     *
     * @return @~english Vec2 vector with an angle of this.getAngle() - other.getAngle(),
     * and a length of this.getLength() * other.getLength().
     * @~chinese ��תǰ�����ĽǶȵ��ڣ�this.getAngle()����other.getAngle(),
     * ���ȵ��ڣ�this.getLength����()* other.getLength()��
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 unrotate(const Vec2& other) const {
        return Vec2(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** @~english Linear Interpolation between two points a and b
     * @~chinese ����������a��b֮������Բ�ֵ��
     *
     * @param other @~english The point to compute the linear interpolation with. 
     * @~chinese ���Լ������Բ�ֵ����һ���ꡣ
     * @param alpha @~english the coefficient of linear interpolation. 
     * @~chinese ���Բ�ֵϵ����
     *
     * @return @~english The result of the linear interpolation.
     * @~chinese ���Բ�ֵ�����
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vec2 lerp(const Vec2& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** @~english Rotates a point counter clockwise by the angle around a pivot
     * @~chinese ������pivotΪ����ʱ����תangle�Ⱥ�ĵ㡣����λΪ���ȣ���
     *
     * @param pivot @~english is the pivot, naturally. @~chinese �ᡣ
     * @param angle @~english is the angle of rotation ccw in radians. @~chinese ��ת�Ƕȡ�
     *
     * @returns @~english the rotated point. @~chinese ��ת��ĵ㡣
     * @since v2.1.4
     * @js NA
     * @lua NA
     */
    Vec2 rotateByAngle(const Vec2& pivot, float angle) const;

    /**
     * @js NA
     * @lua NA
     */
    static inline Vec2 forAngle(const float a)
    {
        return Vec2(cosf(a), sinf(a));
    }
    
    /** @~english A general line-line intersection test
     * @~chinese �жϸ����������߶��Ƿ��ཻ��
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶ε���ʼ�˵㡣
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶εĽ����˵㡣
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶ε���ʼ�˵㡣
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶εĽ����˵㡣
     * @param S   @~english the range for a hitpoint in L1 (p = A + S*(B - A))
     * @~chinese �ཻ�����߶�L1�ķ�Χ(p = A + S*(B - A))
     * @param T   @~english the range for a hitpoint in L2 (p = C + T*(D - C))
     * @~chinese �ཻ�����߶�L2�ķ�Χ(p = C + T*(D - C))
     *
     * @returns @~english  whether these two lines interects.
     *
     * Note that to truly test intersection for segments we have to make
     * sure that S & T lie within [0..1] and for rays, make sure S & T > 0
     * the hit point is        C + T * (D - C);
     * the hit point also is   A + S * (B - A);

     * @~chinese ���������߶��Ƿ��ཻ�� 
     * ע��, �ж��߶��Ƿ��ཻӦ��ȷ�Ϸ���ֵS��T��ֵ��������[0,1]�ڣ��ж������Ƿ��ཻӦ��ȷ�ϣ�S & T����ֵ����0.
     * �ཻ����ڣ�C + T * (D - C); Ҳ����A + S * (B - A);
     * @since 3.0
     * @js NA
     * @lua NA
     */
    static bool isLineIntersect(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 float *S = nullptr, float *T = nullptr);
    
    /**@~english
     * returns true if Line A-B overlap with segment C-D
     * @~chinese �ж� �߶�A-B �� �߶�C-D�Ƿ��ص���
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶ε���ʼ�˵㡣
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶εĽ����˵㡣
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶ε���ʼ�˵㡣
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶εĽ����˵㡣
     *
     * @returns @~english  whether these two lines overlap. 
     * @~chinese ������߶��ص�����true�����򷵻�false��
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineOverlap(const Vec2& A, const Vec2& B,
                                const Vec2& C, const Vec2& D);
    
    /**@~english
     * returns true if Line A-B parallel with segment C-D
     * @~chinese �ж� �߶�A-B �� �߶�C-D�Ƿ�ƽ�С�
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶ε���ʼ�˵㡣
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶εĽ����˵㡣
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶ε���ʼ�˵㡣
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶εĽ����˵㡣
     *
     * @returns @~english  whether these two lines is parallel. 
     * @~chinese ������߶�ƽ�з���true�����򷵻�false��
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineParallel(const Vec2& A, const Vec2& B,
                   const Vec2& C, const Vec2& D);
    
    /**@~english
     * returns true if Segment A-B overlap with segment C-D
     * @~chinese �ж� �߶�A-B �� �߶�C-D�Ƿ��ص���
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶ε���ʼ�˵㡣
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶εĽ����˵㡣
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶ε���ʼ�˵㡣
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶εĽ����˵㡣
     * @param S   @~english the start point
     * @~chinese ��㡣
     * @param E   @~english the endpoint
     * @~chinese �˵㡣
     *
     * @returns @~english  whether these two lines overlap. 
     * @~chinese ������߶��ص�����true�����򷵻�false��
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentOverlap(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 Vec2* S = nullptr, Vec2* E = nullptr);
    
    /**@~english
     * returns true if Segment A-B intersects with segment C-D
     * @~chinese �жϸ����������߶��Ƿ��ཻ��
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶ε���ʼ�˵㡣
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶εĽ����˵㡣
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶ε���ʼ�˵㡣
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶εĽ����˵㡣
     *
     * @returns @~english whether these two lines interects.
     * @~chinese ����߶��ཻ����true�����򷵻�false��
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentIntersect(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /**@~english
     * returns the intersection point of line A-B, C-D
     * @~chinese ��ȡ�����߶ε��ཻ�㡣
     *
     * @param A   @~english the startpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶ε���ʼ�˵㡣
     * @param B   @~english the endpoint for the first line L1 = (A - B)
     * @~chinese ��һ���߶εĽ����˵㡣
     * @param C   @~english the startpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶ε���ʼ�˵㡣
     * @param D   @~english the endpoint for the second line L2 = (C - D)
     * @~chinese �ڶ����߶εĽ����˵㡣
     *
     * @returns @~english the intersection point. @~chinese �ཻ�㡣
     * @since v3.0
     * @js NA
     * @lua NA
     */
    static Vec2 getIntersectPoint(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /** @~english equals to Vec2(0,0)  @~chinese ����Vec2(0,0)*/
    static const Vec2 ZERO;
    /** @~english equals to Vec2(1,1)  @~chinese ����Vec2(1,1)*/
    static const Vec2 ONE;
    /** @~english equals to Vec2(1,0)  @~chinese ����Vec2(0)*/
    static const Vec2 UNIT_X;
    /** @~english equals to Vec2(0,1)  @~chinese ����Vec2(0,1)*/
    static const Vec2 UNIT_Y;
    /** @~english equals to Vec2(0.5, 0.5)  @~chinese ����Vec2(0.5,0.5)*/
    static const Vec2 ANCHOR_MIDDLE;
    /** @~english equals to Vec2(0, 0)  @~chinese ����Vec2(0,0)*/
    static const Vec2 ANCHOR_BOTTOM_LEFT;
    /** @~english equals to Vec2(0, 1)  @~chinese ����Vec2(0,1)*/
    static const Vec2 ANCHOR_TOP_LEFT;
    /** @~english equals to Vec2(1, 0)  @~chinese equals to Vec2(1��0)*/
    static const Vec2 ANCHOR_BOTTOM_RIGHT;
    /** @~english equals to Vec2(1, 1)  @~chinese ����Vec2(1,1)*/
    static const Vec2 ANCHOR_TOP_RIGHT;
    /** @~english equals to Vec2(1, 0.5)  @~chinese ����Vec2(0.5)*/
    static const Vec2 ANCHOR_MIDDLE_RIGHT;
    /** @~english equals to Vec2(0, 0.5)  @~chinese ����Vec2(0,- 0.5)*/
    static const Vec2 ANCHOR_MIDDLE_LEFT;
    /** @~english equals to Vec2(0.5, 1)  @~chinese ����Vec2(0.5,1)*/
    static const Vec2 ANCHOR_MIDDLE_TOP;
    /** @~english equals to Vec2(0.5, 0)  @~chinese ����Vec2(0.5,0)*/
    static const Vec2 ANCHOR_MIDDLE_BOTTOM;
};

/**
 * @~english Calculates the scalar product of the given vector with the given value.
 * @~chinese ��������������������ϵ����˺��������
 * 
 * @param x @~english The value to scale by. @~chinese ����ϵ����
 * @param v @~english The vector to scale. @~chinese �����ŵ�������
 * 
 * @return @~english The scaled vector. @~chinese ���ź��������
 */
inline const Vec2 operator*(float x, const Vec2& v);

typedef Vec2 Point;

NS_CC_MATH_END


// end of base group
/// @}

#include "Vec2.inl"

#endif // MATH_VEC2_H
