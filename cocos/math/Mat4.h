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

#ifndef MATH_MAT4_H
#define MATH_MAT4_H

#include "base/ccMacros.h"

#include "math/Vec3.h"
#include "math/Vec4.h"

#ifdef __SSE__
#include <xmmintrin.h>
#endif

/**
 * @addtogroup base
 * @{
 */

NS_CC_MATH_BEGIN

//class Plane;

/**
@class Mat4
@brief
@~english
 * Defines a 4 x 4 floating point matrix representing a 3D transformation.
 *
 * Vectors are treated as columns, resulting in a matrix that is represented as follows,
 * where x, y and z are the translation components of the matrix:
 *
 *     1  0  0  x
 *     0  1  0  y
 *     0  0  1  z
 *     0  0  0  1
 *
 * This matrix class is directly compatible with OpenGL since its elements are
 * laid out in memory exactly as they are expected by OpenGL.
 * The matrix uses column-major format such that array indices increase down column first.
 * Since matrix multiplication is not commutative, multiplication must be done in the
 * correct order when combining transformations. Suppose we have a translation
 * matrix T and a rotation matrix R. To first rotate an object around the origin
 * and then translate it, you would multiply the two matrices as TR.
 *
 * Likewise, to first translate the object and then rotate it, you would do RT.
 * So generally, matrices must be multiplied in the reverse order in which you
 * want the transformations to take place (this also applies to
 * the scale, rotate, and translate methods below; these methods are convenience
 * methods for post-multiplying by a matrix representing a scale, rotation, or translation).
 *
 * @~chinese 
 * ���ඨ����һ��4��4�������,�������ڱ�ʾһ��3dת����
 * 
 * �����ǰ��������ȵķ�ʽ������֯��,���ԣ�һ��ֻ����ƽ��(x,y,z)�ľ�����������:
 * 
 * 1 0 0 x
 * 0 1 0 y
 * 0 0 1 z
 * 0 0 0 1
 * 
 * �������ֱ�Ӽ���openGL����Ϊ���ڴ���֯��ʽ��openGL�ľ�����֯��ʽ��ͬ��
 * ����ʹ�������ȵ���֯��ʽ,�����������Ȱ�����˳��
 * ��Ϊ����˷��У�����˳�򲻿ɽ���,����������Ҫ������ȷ��˳��������
 * ����������һ��ƽ��T��һ����ת����R�������Ҫ������ת���壬Ȼ����ƽ�ƣ���ô���Ͼ���Ӧ����T*R
 * 
 * ͬ��,���ȰѶ���ƽ��,Ȼ����ת,����Ҫ��R*T�����㡣
 * ����һ����˵,����˷���˳������������б任��˳�������෴(��Ҳ������
 * ���š���ת�������ƽ�ƺ���,��Щ�����Ǳ�������
 * ��ͨ���ҳ˾�����ʵ��һ������,��ת,��ƽ��)��
 * 
 */
class CC_DLL Mat4
{
public:
    // //temp add conversion
    // operator kmMat4() const
    // {
    //     kmMat4 result;
    //     kmMat4Fill(&result, m);
    //     return result;
    // }
    
    // Mat4(const kmMat4& mat)
    // {
    //     set(mat.mat);
    // }
    /**@~english
     * Stores the columns of this 4x4 matrix.
     * @~chinese 
     * �̵��4 x4������С�
     * */
#ifdef __SSE__
    union {
        __m128 col[4];
        float m[16];
    };
#else
    float m[16];
#endif

    /** @~english
     * Default constructor.
     * Constructs a matrix initialized to the identity matrix:
     *
     *     1  0  0  0
     *     0  1  0  0
     *     0  0  1  0
     *     0  0  0  1
     * @~chinese 
     * Ĭ�Ϲ��캯����
     * ����һ����λ����:
     * 
     * 1 0 0 0
     * 1 0 0 0
     * 1 0 0 0
     * 0 0 0 1
     */
    Mat4();

    /**@~english
     * Constructs a matrix initialized to the specified value.
     *
     * @~chinese 
     * ����һ�������ʼ��Ϊָ����ֵ��
     * 
     * @param m11 @~english The first element of the first row.
     * @~chinese ��һ�еĵ�һ��Ԫ�ء�
     * @param m12 @~english The second element of the first row.
     * @~chinese ��һ�еĵڶ���Ԫ�ء�
     * @param m13 @~english The third element of the first row.
     * @~chinese ��һ�еĵ�����Ԫ�ء�
     * @param m14 @~english The fourth element of the first row.
     * @~chinese ��һ�еĵ��ĸ�Ԫ�ء�
     * @param m21 @~english The first element of the second row.
     * @~chinese �ڶ��еĵ�һ��Ԫ�ء�
     * @param m22 @~english The second element of the second row.
     * @~chinese �ڶ��еĵڶ���Ԫ�ء�
     * @param m23 @~english The third element of the second row.
     * @~chinese �ڶ��еĵ�����Ԫ�ء�
     * @param m24 @~english The fourth element of the second row.
     * @~chinese �ڶ��еĵ��ĸ�Ԫ�ء�
     * @param m31 @~english The first element of the third row.
     * @~chinese �����еĵ�һ��Ԫ�ء�
     * @param m32 @~english The second element of the third row.
     * @~chinese �����еĵڶ���Ԫ�ء�
     * @param m33 @~english The third element of the third row.
     * @~chinese �����еĵ�����Ԫ�ء�
     * @param m34 @~english The fourth element of the third row.
     * @~chinese �����еĵ��ĸ�Ԫ�ء�
     * @param m41 @~english The first element of the fourth row.
     * @~chinese �����еĵ�һ��Ԫ�ء�
     * @param m42 @~english The second element of the fourth row.
     * @~chinese �����еĵڶ���Ԫ�ء�
     * @param m43 @~english The third element of the fourth row.
     * @~chinese �����еĵ�����Ԫ�ء�
     * @param m44 @~english The fourth element of the fourth row.
     * @~chinese �����еĵ��ĸ�Ԫ�ء�
     */
    Mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    /**@~english
     * Creates a matrix initialized to the specified column-major array.
     *
     * The passed-in array is in column-major order, so the memory layout of the array is as follows:
     *
     *     0   4   8   12
     *     1   5   9   13
     *     2   6   10  14
     *     3   7   11  15
     *
     * @~chinese 
     * ����һ�����󣬲������鱻��Ϊ�����ȵ���֯��ʽ��
     * 
     * ��������鱻��Ϊ���������ȷ�ʽ��֯,����������ڴ沼������:
     * 
     *    0   4   8   12
     *    1   5   9   13
     *    2   6   10  14
     *    3   7   11  15
     * 
     * @param mat @~english An array containing 16 elements in column-major order.
     * @~chinese һ������,���а���16��Ԫ�أ��������ȷ�ʽ��֯��
     */
    Mat4(const float* mat);

    /**@~english
     * Constructs a new matrix by copying the values from the specified matrix.
     *
     * @~chinese 
     * �������캯����
     * 
     * @param copy @~english The matrix to copy.
     * @~chinese Ҫ���Ƶľ���
     */
    Mat4(const Mat4& copy);

    /**@~english
     * Destructor.
     * @~chinese 
     * ����������
     */
    ~Mat4();

    /**@~english
     * Creates a view matrix based on the specified input parameters.
     *
     * @~chinese 
     * ����ָ���������������һ����ͼ����
     * 
     * @param eyePosition @~english The eye position.
     * @~chinese �ӵ��λ�á�
     * @param targetPosition @~english The target's center position.
     * @~chinese Ŀ�������λ�á�
     * @param up @~english The up vector.
     * @~chinese up��������
     * @param dst @~english A matrix to store the result in.
     * @~chinese ���صĽ������
     */
    static void createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, Mat4* dst);

    /**@~english
     * Creates a view matrix based on the specified input parameters.
     *
     * @~chinese 
     * ����һ����ͼ�������ָ�������������
     * 
     * @param eyePositionX @~english The eye x-coordinate position.
     * @~chinese �ӵ��x���ꡣ
     * @param eyePositionY @~english The eye y-coordinate position.
     * @~chinese �ӵ��y���ꡣ
     * @param eyePositionZ @~english The eye z-coordinate position.
     * @~chinese �ӵ��z���ꡣ
     * @param targetCenterX @~english The target's center x-coordinate position.
     * @~chinese Ŀ�����ĵ�x���ꡣ
     * @param targetCenterY @~english The target's center y-coordinate position.
     * @~chinese Ŀ�����ĵ�y���ꡣ
     * @param targetCenterZ @~english The target's center z-coordinate position.
     * @~chinese Ŀ�������z���ꡣ
     * @param upX @~english The up vector x-coordinate value.
     * @~chinese up����x�����ֵ��
     * @param upY @~english The up vector y-coordinate value.
     * @~chinese up����y�����ֵ��
     * @param upZ @~english The up vector z-coordinate value.
     * @~chinese up����z�����ֵ��
     * @param dst @~english A matrix to store the result in.
     * @~chinese ���صĽ������
     */
    static void createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                             float targetCenterX, float targetCenterY, float targetCenterZ,
                             float upX, float upY, float upZ, Mat4* dst);

    /**@~english
     * Builds a perspective projection matrix based on a field of view and returns by value.
     *
     * Projection space refers to the space after applying projection transformation from view space.
     * After the projection transformation, visible content has x- and y-coordinates ranging from -1 to 1,
     * and a z-coordinate ranging from 0 to 1. 
     * @~chinese 
     * ����Fov������һ��͸��ͶӰ����
     * 
     * ͶӰ�ռ�ָ���ǿռ���ӵ�ռ�Ӧ��ͶӰ�任��Ŀռ䡣
     * ͶӰ�任��,�ɼ����ݵ�x��y������ֵλ�ڣ�1��1֮ǰ��Zλ��0��1֮��,
     * 
     * @param fieldOfView @~english The field of view in the y direction (in degrees).
     * @~chinese ��y�᷽���FOV��
     * @param aspectRatio @~english The aspect ratio, defined as view space width divided by height.
     * @~chinese ��߱�,����Ϊ��ͼ�ռ��ȳ��Ը߶ȡ�
     * @param zNearPlane @~english The distance to the near view plane.
     * @~chinese �����ü���ľ��롣
     * @param zFarPlane @~english The distance to the far view plane.
     * @~chinese ��Զ�ü���ľ��롣
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢ͶӰ����
     */
    static void createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane, Mat4* dst);

    /**@~english
     * Creates an orthographic projection matrix.
     *
     * @~chinese 
     * ����һ������ͶӰ����
     * 
     * @param width @~english The width of the view.
     * @~chinese ��ͼ�Ŀ�ȡ�
     * @param height @~english The height of the view.
     * @~chinese ��ͼ�ĸ߶ȡ�
     * @param zNearPlane @~english The minimum z-value of the view volume.
     * @~chinese �����ü���ľ��롣
     * @param zFarPlane @~english The maximum z-value of the view volume.
     * @~chinese ��Զ�ü���ľ��롣
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢ͶӰ����
     */
    static void createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Mat4* dst);

    /**@~english
     * Creates an orthographic projection matrix.
     * 
     * @~chinese 
     * ����һ������ͶӰ����
     * 
     * @param left @~english The minimum x-value of the view volume.
     * @~chinese �ӵ�����ϵ����С�ɼ���Xֵ��
     * @param right @~english The maximum x-value of the view volume.
     * @~chinese �ӵ�����ϵ�����ɼ���Xֵ��
     * @param bottom @~english The minimum y-value of the view volume.
     * @~chinese �ӵ�����ϵ����С�ɼ���Yֵ��
     * @param top @~english The maximum y-value of the view volume.
     * @~chinese �ӵ�����ϵ�����ɼ���Yֵ��
     * @param zNearPlane @~english The minimum z-value of the view volume.
     * @~chinese �����ü���ľ��롣
     * @param zFarPlane @~english The maximum z-value of the view volume.
     * @~chinese ��Զ�ü���ľ��롣
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢ͶӰ����
     */
    static void createOrthographicOffCenter(float left, float right, float bottom, float top,
                                            float zNearPlane, float zFarPlane, Mat4* dst);

    /**@~english
     * Creates a spherical billboard that rotates around a specified object position.
     *
     * This method computes the facing direction of the billboard from the object position
     * and camera position. When the object and camera positions are too close, the matrix
     * will not be accurate. To avoid this problem, this method defaults to the identity
     * rotation if the positions are too close. (See the other overload of createBillboard
     * for an alternative approach).
     *
     * @~chinese 
     * ����һ������Billborad����bilboard������ĳһ������ת��
     * 
     * �÷�������������λ�ú������λ��������Billborad�ĳ����������������̫����������ܲ�׼ȷ��
     * Ϊ�˱���������⣬������̫��ʱ�������õ�λ������Ϊ��תҲ���㳯��
     * 
     * @param objectPosition @~english The position of the object the billboard will rotate around.
     * @~chinese billboard��ת�����ġ�
     * @param cameraPosition @~english The position of the camera.
     * @~chinese �������λ�á�
     * @param cameraUpVector @~english The up vector of the camera.
     * @~chinese �����up������
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                                const Vec3& cameraUpVector, Mat4* dst);

    /**@~english
     * Creates a spherical billboard that rotates around a specified object position with
     * provision for a safe default orientation.
     *
     * This method computes the facing direction of the billboard from the object position
     * and camera position. When the object and camera positions are too close, the matrix
     * will not be accurate. To avoid this problem, this method uses the specified camera
     * forward vector if the positions are too close. (See the other overload of createBillboard
     * for an alternative approach).
     *
     * @~chinese 
     * ����һ������Billborad����bilboard������ĳһ������ת��
     * 
     * �÷�������������λ�ú������λ��������Billborad�ĳ����������������̫����������ܲ�׼ȷ��
     * Ϊ�˱���������⣬������̫��ʱ���������������forward�����㳯��
     * 
     * @param objectPosition @~english The position of the object the billboard will rotate around.
     * @~chinese billboard��ת�����ġ�
     * @param cameraPosition @~english The position of the camera.
     * @~chinese �������λ�á�
     * @param cameraUpVector @~english The up vector of the camera.
     * @~chinese �����up������
     * @param cameraForwardVector @~english The forward vector of the camera, used if the positions are too close.
     * @~chinese �����forward����,��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                                const Vec3& cameraUpVector, const Vec3& cameraForwardVector,
                                Mat4* dst);

    //Fills in an existing Mat4 so that it reflects the coordinate system about a specified Plane.
    //plane The Plane about which to create a reflection.
    //dst A matrix to store the result in.
    //static void createReflection(const Plane& plane, Mat4* dst);

    /**@~english
     * Creates a scale matrix.
     *
     * @~chinese 
     * ͨ�����Ŵ���һ������
     * 
     * @param scale @~english The amount to scale.
     * @~chinese ����ֵ��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createScale(const Vec3& scale, Mat4* dst);

    /**@~english
     * Creates a scale matrix.
     *
     * @~chinese 
     * �������Ŵ���һ������
     * 
     * @param xScale @~english The amount to scale along the x-axis.
     * @~chinese ����x������š�
     * @param yScale @~english The amount to scale along the y-axis.
     * @~chinese ����y������š�
     * @param zScale @~english The amount to scale along the z-axis.
     * @~chinese ����z������š�
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createScale(float xScale, float yScale, float zScale, Mat4* dst);

    /**@~english
     * Creates a rotation matrix from the specified quaternion.
     *
     * @~chinese 
     * ������Ԫ����ת������һ������
     * 
     * @param quat @~english A quaternion describing a 3D orientation.
     * @~chinese һ����������3D��ת����Ԫ����
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createRotation(const Quaternion& quat, Mat4* dst);

    /**@~english
     * Creates a rotation matrix from the specified axis and angle.
     *
     * @~chinese 
     * ͨ��������ת������һ���任����
     * 
     * @param axis @~english A vector describing the axis to rotate about.
     * @~chinese ��ת���ᡣ
     * @param angle @~english The angle (in radians).
     * @~chinese ��ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createRotation(const Vec3& axis, float angle, Mat4* dst);

    /**@~english
     * Creates a matrix describing a rotation around the x-axis.
     *
     * @~chinese 
     * ��X����ת������һ���任����
     * 
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese ��X����ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createRotationX(float angle, Mat4* dst);

    /**@~english
     * Creates a matrix describing a rotation around the y-axis.
     *
     * @~chinese 
     * ��Y����ת������һ���任����
     * 
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese ��Y����ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createRotationY(float angle, Mat4* dst);

    /**@~english
     * Creates a matrix describing a rotation around the z-axis.
     *
     * @~chinese 
     * ��Z����ת������һ���任����
     * 
     * @param angle @~english The angle of rotation (in radians).
     * @~chinese ��Z����ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createRotationZ(float angle, Mat4* dst);

    /**@~english
     * Creates a translation matrix.
     *
     * @~chinese 
     * ����ƽ�ƴ���һ���任����
     * 
     * @param translation @~english The translation.
     * @~chinese ƽ�ơ�
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createTranslation(const Vec3& translation, Mat4* dst);

    /**@~english
     * Creates a translation matrix.
     *
     * @~chinese 
     * ����ƽ�ƴ���һ���任����
     * 
     * @param xTranslation @~english The translation on the x-axis.
     * @~chinese ��x���ϵ�ƽ�ơ�
     * @param yTranslation @~english The translation on the y-axis.
     * @~chinese ��y���ϵ�ƽ�ơ�
     * @param zTranslation @~english The translation on the z-axis.
     * @~chinese ��z���ϵ�ƽ�ơ�
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢�������
     */
    static void createTranslation(float xTranslation, float yTranslation, float zTranslation, Mat4* dst);

    /**@~english
     * Adds a scalar value to each component of this matrix.
     *
     * @~chinese 
     * �Ծ����ÿһ��Ԫ�ؼ���scalar��Ȼ�󱣴浽this��
     * 
     * @param scalar @~english The scalar to add.
     * @~chinese Ҫ���ϵ�scalarֵ��
     */
    void add(float scalar);

    /**@~english
     * Adds a scalar value to each component of this matrix and stores the result in dst.
     *
     * @~chinese 
     * �Ծ����ÿһ��Ԫ�ؼ���scalar��Ȼ�󱣴浽dst�С�
     * 
     * @param scalar @~english The scalar value to add.
     * @~chinese Ҫ���ϵ�scalarֵ��
     * @param dst @~english A matrix to store the result in.
     * @~chinese ���ڴ����������
     */
    void add(float scalar, Mat4* dst);

    /**@~english
     * Adds the specified matrix to this matrix.
     *
     * @~chinese 
     * ��һ�������ľ�����ӣ������������this�С�
     * 
     * @param mat @~english The matrix to add.
     * @~chinese Ҫ�ӵľ���
     */
    void add(const Mat4& mat);

    /**@~english
     * Adds the specified matrices and stores the result in dst.
     *
     * @~chinese 
     * ������������ĺ͡�
     * 
     * @param m1 @~english The first matrix.
     * @~chinese ��һ������
     * @param m2 @~english The second matrix.
     * @~chinese �ڶ�������
     * @param dst @~english The destination matrix to add to.
     * @~chinese �洢��������
     */
    static void add(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**@~english
     * Decomposes the scale, rotation and translation components of this matrix.
     *
     * @~chinese 
     * ������ֽ�Ϊƽ�ƣ���ת�����ŷ�����
     * 
     * @param scale @~english The scale.
     * @~chinese ���ŷ�����
     * @param rotation @~english The rotation.
     * @~chinese ��ת������
     * @param translation @~english The translation.
     * @~chinese ƽ�Ʒ�����
     */
    bool decompose(Vec3* scale, Quaternion* rotation, Vec3* translation) const;

    /**@~english
     * Computes the determinant of this matrix.
     *
     * @~chinese 
     * ������������ʽ���ȡ�
     * 
     * @return @~english The determinant.
     * @~chinese ���������ʽ���ȡ�
     */
    float determinant() const;

    /**@~english
     * Gets the scalar component of this matrix in the specified vector.
     *
     * If the scalar component of this matrix has negative parts,
     * it is not possible to always extract the exact scalar component;
     * instead, a scale vector that is mathematically equivalent to the
     * original scale vector is extracted and returned.
     *
     * @~chinese 
     * �õ������������ŷ�����
     * 
     * �����������и����Ų��֣���ô������׼ȷ�õ�ԭʼ�����ŷ�����
     * ���صļ��������Ľ��
     * 
     * @param scale @~english A vector to receive the scale.
     * @~chinese ���ڱ������ŷ�����
     */
    void getScale(Vec3* scale) const;

    /**@~english
     * Gets the rotational component of this matrix in the specified quaternion.
     *
     * @~chinese 
     * �õ��������ת������
     * 
     * @param rotation @~english A quaternion to receive the rotation.
     * 
     * @~chinese ������ת��Ԫ����
     * 
     * @return @~english true if the rotation is successfully extracted, false otherwise.
     * @~chinese ����ɹ���ȡ��ת��������,���򷵻ؼ١�
     */
    bool getRotation(Quaternion* rotation) const;

    /**@~english
     * Gets the translational component of this matrix in the specified vector.
     *
     * @~chinese 
     * �õ���������ƽ�Ʒ�����
     * 
     * @param translation @~english A vector to receive the translation.
     * @~chinese ���ڴ洢ƽ�Ʒ���
     */
    void getTranslation(Vec3* translation) const;

    /**@~english
     * Gets the up vector of this matrix.
     *
     * @~chinese 
     * �õ����ϵ��������൱�ڱ任Vec3(0,1,0)��
     * 
     * @param dst @~english The destination vector.
     * @~chinese ���ڴ洢Ŀ��������
     */
    void getUpVector(Vec3* dst) const;

    /**@~english
     * Gets the down vector of this matrix.
     *
     * @~chinese 
     * �õ����µ��������൱�ڱ任Vec3(0,-1,0)��
     * 
     * @param dst @~english The destination vector.
     * @~chinese ���ڴ洢Ŀ��������
     */
    void getDownVector(Vec3* dst) const;

    /**@~english
     * Gets the left vector of this matrix.
     *
     * @~chinese 
     * �õ�������������൱�ڱ任Vec3(��1,0,0)��
     * 
     * @param dst @~english The destination vector.
     * @~chinese ���ڴ洢Ŀ��������
     */
    void getLeftVector(Vec3* dst) const;

    /**@~english
     * Gets the right vector of this matrix.
     *
     * @~chinese 
     * �õ����ҵ��������൱�ڱ任Vec3(1,0,0)��
     * 
     * @param dst @~english The destination vector.
     * @~chinese ���ڴ洢Ŀ��������
     */
    void getRightVector(Vec3* dst) const;

    /**@~english
     * Gets the forward vector of this matrix.
     *
     * @~chinese 
     * �õ���ǰ������,�൱�ڱ任Vec3(0,0,��1)��
     * 
     * @param dst @~english The destination vector.
     * @~chinese ���ڴ洢Ŀ��������
     */
    void getForwardVector(Vec3* dst) const;

    /**@~english
     * Gets the backward vector of this matrix.
     *
     * @~chinese 
     * �õ���������,�൱�ڱ任Vec3(0,0,1)��
     * 
     * @param dst @~english The destination vector.
     * @~chinese ���ڴ洢Ŀ��������
     */
    void getBackVector(Vec3* dst) const;

    /**@~english
     * Inverts this matrix.
     *
     * @~chinese 
     * �Ծ������棬��������this�С�
     * 
     * @return @~english true if the the matrix can be inverted, false otherwise.
     * @~chinese �������������棬������,���򷵻ؼ١�
     */
    bool inverse();

    /**@~english
     * Get the inversed matrix.
     * @~chinese 
     * �õ������m(m*this = this *m = IDENTITY)��
     */
    Mat4 getInversed() const;

    /**@~english
     * Determines if this matrix is equal to the identity matrix.
     *
     * @~chinese 
     * ȷ����������Ƿ���ڵ�λ����
     * 
     * @return @~english true if the matrix is an identity matrix, false otherwise.
     * @~chinese ���������һ����λ����,�򷵻��棬���򷵻ؼ١�
     */
    bool isIdentity() const;

    /**@~english
     * Multiplies the components of this matrix by the specified scalar.
     *
     * @~chinese 
     * �Ծ����ÿһ��Ԫ�س���scalar����������this�С�
     * 
     * @param scalar @~english The scalar value.
     * @~chinese ����ֵ��
     */
    void multiply(float scalar);

    /**@~english
     * Multiplies the components of this matrix by a scalar and stores the result in dst.
     *
     * @~chinese 
     * �Ծ����ÿһ��Ԫ�س���scalar��������dst��.
     * 
     * @param scalar @~english The scalar value.
     * @~chinese ����ֵ��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �������Ľ����
     */
    void multiply(float scalar, Mat4* dst) const;

    /**@~english
     * Multiplies the components of the specified matrix by a scalar and stores the result in dst.
     *
     * @~chinese 
     * �Ծ���mat��ÿһ��Ԫ�س���scalar��������dst��.
     * 
     * @param mat @~english The matrix.
     * @~chinese ����
     * @param scalar @~english The scalar value.
     * @~chinese ����ֵ��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �������Ľ����
     */
    static void multiply(const Mat4& mat, float scalar, Mat4* dst);

    /**@~english
     * Multiplies this matrix by the specified one.
     *
     * @~chinese 
     * �ҳ˾����ұ�����this�С�
     * 
     * @param mat @~english The matrix to multiply.
     * @~chinese Ҫ�ҳ˵ľ���
     */
    void multiply(const Mat4& mat);

    /**@~english
     * Multiplies m1 by m2 and stores the result in dst.
     *
     * @~chinese 
     * �������m1*m2��
     * 
     * @param m1 @~english The first matrix to multiply.
     * @~chinese ��һ������m1��
     * @param m2 @~english The second matrix to multiply.
     * @~chinese �ڶ�������m2��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �������Ľ����
     */
    static void multiply(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**@~english
     * Negates this matrix.
     * @~chinese 
     * ��������(��ÿһ��Ԫ�س��ԣ�1)����������this�С�
     */
    void negate();

    /**@~english
     Get the Negated matrix.
     * @~chinese 
     * �õ�������(��ÿһ��Ԫ�س��ԣ�1)��
     */
    Mat4 getNegated() const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified quaternion rotation.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param q @~english The quaternion to rotate by.
     * @~chinese ��ת����Ԫ����
     */
    void rotate(const Quaternion& q);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified quaternion rotation and stores the result in dst.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param q @~english The quaternion to rotate by.
     * @~chinese ��ת����Ԫ����
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void rotate(const Quaternion& q, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation about the specified axis.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param axis @~english The axis to rotate about.
     * @~chinese ��ת���ᡣ
     * @param angle @~english The angle (in radians).
     * @~chinese ��ת�ĽǶ�(����)��
     */
    void rotate(const Vec3& axis, float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the specified
     * rotation about the specified axis and stores the result in dst.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param axis @~english The axis to rotate about.
     * @~chinese ��ת���ᡣ
     * @param angle @~english The angle (in radians).
     * @~chinese ��ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void rotate(const Vec3& axis, float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the x-axis.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese ��X����ת�ĽǶ�(����)��
     */
    void rotateX(float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the x-axis and stores the result in dst.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese ��X����ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void rotateX(float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the y-axis.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese ��Y����ת�ĽǶ�(����)��
     */
    void rotateY(float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the y-axis and stores the result in dst.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese ��Y����ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void rotateY(float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the z-axis.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese ��Z����ת�ĽǶ�(����)��
     */
    void rotateZ(float angle);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the z-axis and stores the result in dst.
     *
     * @~chinese 
     * ������ת��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param angle @~english The angle (in radians).
     * @~chinese ��Z����ת�ĽǶ�(����)��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void rotateZ(float angle, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @~chinese 
     * ����scale��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param value @~english The amount to scale along all axes.
     * @~chinese �ȱ�����ֵ��
     */
    void scale(float value);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @~chinese 
     * ����scale��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param value @~english The amount to scale along all axes.
     * @~chinese �ȱ�����ֵ��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void scale(float value, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @~chinese 
     * ����scale��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param xScale @~english The amount to scale along the x-axis.
     * @~chinese ����x������š�
     * @param yScale @~english The amount to scale along the y-axis.
     * @~chinese ����y������š�
     * @param zScale @~english The amount to scale along the z-axis.
     * @~chinese ����z������š�
     */
    void scale(float xScale, float yScale, float zScale);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @~chinese 
     * ����scale��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param xScale @~english The amount to scale along the x-axis.
     * @~chinese ����x������š�
     * @param yScale @~english The amount to scale along the y-axis.
     * @~chinese ����y������š�
     * @param zScale @~english The amount to scale along the z-axis.
     * @~chinese ����z������š�
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void scale(float xScale, float yScale, float zScale, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @~chinese 
    * ����scale��������󣬲��ҽ��þ����ҳ�this������洢��this�С�
     * 
     * @param s @~english The scale values along the x, y and z axes.
     * @~chinese ����ֵ��
     */
    void scale(const Vec3& s);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @~chinese 
     * ����scale��������󣬲��ҽ��þ����ҳ�this������洢��dst�С�
     * 
     * @param s @~english The scale values along the x, y and z axes.
     * @~chinese ����ֵ��
     * @param dst @~english A matrix to store the result in.
     * @~chinese �洢����Ľ����
     */
    void scale(const Vec3& s, Mat4* dst) const;

    /**@~english
     * Sets the values of this matrix.
     *
     * @~chinese 
     * ���þ����ֵ��
     * 
     * @param m11 @~english The first element of the first row.
     * @~chinese ��һ�еĵ�һ��Ԫ�ء�
     * @param m12 @~english The second element of the first row.
     * @~chinese ��һ�еĵڶ���Ԫ�ء�
     * @param m13 @~english The third element of the first row.
     * @~chinese ��һ�еĵ�����Ԫ�ء�
     * @param m14 @~english The fourth element of the first row.
     * @~chinese ��һ�е���Ԫ�ء�
     * @param m21 @~english The first element of the second row.
     * @~chinese �ڶ��еĵ�һ��Ԫ�ء�
     * @param m22 @~english The second element of the second row.
     * @~chinese �ڶ��еĵڶ���Ԫ�ء�
     * @param m23 @~english The third element of the second row.
     * @~chinese �ڶ��еĵ�����Ԫ�ء�
     * @param m24 @~english The fourth element of the second row.
     * @~chinese �ڶ��еĵ��ĸ�Ԫ�ء�
     * @param m31 @~english The first element of the third row.
     * @~chinese �����еĵ�һ��Ԫ�ء�
     * @param m32 @~english The second element of the third row.
     * @~chinese �����еĵڶ���Ԫ�ء�
     * @param m33 @~english The third element of the third row.
     * @~chinese �����еĵ�����Ԫ�ء�
     * @param m34 @~english The fourth element of the third row.
     * @~chinese �����еĵ��ĸ�Ԫ�ء�
     * @param m41 @~english The first element of the fourth row.
     * @~chinese �����еĵ�һ��Ԫ�ء�
     * @param m42 @~english The second element of the fourth row.
     * @~chinese �����еĵڶ���Ԫ�ء�
     * @param m43 @~english The third element of the fourth row.
     * @~chinese �����еĵ�����Ԫ�ء�
     * @param m44 @~english The fourth element of the fourth row.
     * @~chinese �����еĵ��ĸ�Ԫ�ء�
     */
    void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    /**@~english
     * Sets the values of this matrix to those in the specified column-major array.
     *
     * @~chinese 
     * ��������ֵ����Ϊһ����������������ݡ�
     * 
     * @param mat @~english An array containing 16 elements in column-major format.
     * @~chinese �����ȵ����顣
     */
    void set(const float* mat);

    /**@~english
     * Sets the values of this matrix to those of the specified matrix.
     *
     * @~chinese 
     * ��������ֵ����Ϊָ���ľ���
     * 
     * @param mat @~english The source matrix.
     * @~chinese Դ����
     */
    void set(const Mat4& mat);

    /**@~english
     * Sets this matrix to the identity matrix.
     * @~chinese 
     * ����������Ϊ��λ����
     */
    void setIdentity();

    /**@~english
     * Sets all elements of the current matrix to zero.
     * @~chinese 
     * �����������Ԫ������Ϊ�㡣
     */
    void setZero();

    /**@~english
     * Subtracts the specified matrix from the current matrix.
     *
     * @~chinese 
     * �ӵ�ǰ�����ȥһ������
     * 
     * @param mat @~english The matrix to subtract.
     * @~chinese Ҫ��ȥ�ľ���
     */
    void subtract(const Mat4& mat);

    /**@~english
     * Subtracts the specified matrix from the current matrix.
     *
     * @~chinese 
     * �����������
     * 
     * @param m1 @~english The first matrix.
     * @~chinese ��һ������
     * @param m2 @~english The second matrix.
     * @~chinese �ڶ�������
     * @param dst @~english A matrix to store the result in.
     * @~chinese ����Ľ����
     */
    static void subtract(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**@~english
     * Transforms the specified point by this matrix.
     *
     * The result of the transformation is stored directly into point.
     *
     * @~chinese 
     * �任һ���㣬����洢��Ҫ�任�ĵ���
     * 
     * 
     * @param point @~english The point to transform and also a vector to hold the result in.
     * @~chinese Ҫ�任�ĵ㡣
     */
    inline void transformPoint(Vec3* point) const { GP_ASSERT(point); transformVector(point->x, point->y, point->z, 1.0f, point); }

    /**@~english
     * Transforms the specified point by this matrix, and stores
     * the result in dst.
     *
     * @~chinese 
     * �任һ���㣬����洢��dst��
     * 
     * @param point @~english The point to transform.
     * @~chinese Ҫ�任�ĵ㡣
     * @param dst @~english A vector to store the transformed point in.
     * @~chinese �任��Ľ����
     */
    inline void transformPoint(const Vec3& point, Vec3* dst) const { GP_ASSERT(dst); transformVector(point.x, point.y, point.z, 1.0f, dst); }

    /**@~english
     * Transforms the specified vector by this matrix by
     * treating the fourth (w) coordinate as zero.
     *
     * The result of the transformation is stored directly into vector.
     *
     * @~chinese 
     * �任һ�����������ĸ�����w��������0�����ֱ�Ӵ洢��Ҫ�任��������
     * 
     * @param vector @~english The vector to transform and also a vector to hold the result in.
     * @~chinese Ҫ�任��������
     */
    void transformVector(Vec3* vector) const;

    /**@~english
     * Transforms the specified vector by this matrix by
     * treating the fourth (w) coordinate as zero, and stores the
     * result in dst.
     *
     * @~chinese 
     * �任һ�����������ĸ�����w��������0���任�Ľ���洢��dst��
     * 
     * @param vector @~english The vector to transform.
     * @~chinese Ҫ�任��������
     * @param dst @~english A vector to store the transformed vector in.
     * @~chinese �任��Ľ����
     */
    void transformVector(const Vec3& vector, Vec3* dst) const;

    /**@~english
     * Transforms the specified vector by this matrix.
     *
     * @~chinese 
     * �任һ������
     * 
     * @param x @~english The vector x-coordinate to transform by.
     * @~chinese Ҫ�任������x���ꡣ
     * @param y @~english The vector y-coordinate to transform by.
     * @~chinese Ҫ�任������y���ꡣ
     * @param z @~english The vector z-coordinate to transform by.
     * @~chinese Ҫ�任������z���ꡣ
     * @param w @~english The vector w-coordinate to transform by.
     * @~chinese Ҫ�任������w���ꡣ
     * @param dst @~english A vector to store the transformed point in.
     * @~chinese �任��Ľ����
     */
    void transformVector(float x, float y, float z, float w, Vec3* dst) const;

    /**@~english
     * Transforms the specified vector by this matrix.
     *
     * The result of the transformation is stored directly into vector.
     *
     * @~chinese 
     * �任һ���������任���ֱ�ӱ����ڲ���vector��
     * 
     * 
     * @param vector @~english The vector to transform.
     * @~chinese Ҫ�任��������
     */
    void transformVector(Vec4* vector) const;

    /**@~english
     * Transforms the specified vector by this matrix.
     *
     * @~chinese 
     * �任һ��������
     * 
     * @param vector @~english The vector to transform.
     * @~chinese Ҫ�任��������
     * @param dst @~english A vector to store the transformed point in.
     * @~chinese �任��Ľ����
     */
    void transformVector(const Vec4& vector, Vec4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation.
     *
     * @~chinese 
     * ����ƽ�ƹ������󣬲��ҽ�this�����ҳˣ�����洢��this�С�
     * 
     * @param x @~english The amount to translate along the x-axis.
     * @~chinese ������x���ƽ�ơ�
     * @param y @~english The amount to translate along the y-axis.
     * @~chinese ������y���ƽ�ơ�
     * @param z @~english The amount to translate along the z-axis.
     * @~chinese ������z���ƽ�ơ�
     */
    void translate(float x, float y, float z);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation and stores the result in dst.
     *
     * @~chinese 
     * ����ƽ�ƹ������󣬲��ҽ�����this���ҳ˽���洢��dst�С�
     * 
     * @param x @~english The amount to translate along the x-axis.
     * @~chinese ������x���ƽ�ơ�
     * @param y @~english The amount to translate along the y-axis.
     * @~chinese ������y���ƽ�ơ�
     * @param z @~english The amount to translate along the z-axis.
     * @~chinese ������z���ƽ�ơ�
     * @param dst @~english A matrix to store the result in.
     * @~chinese ���صĽ����
     */
    void translate(float x, float y, float z, Mat4* dst) const;

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation.
     *
     * @~chinese 
     * ����ƽ�ƹ������󣬲��ҽ�this�����ҳˣ�����洢��this�С�
     * 
     * @param t @~english The translation values along the x, y and z axes.
     * @~chinese ��x,y��z���ƽ�ơ�
     */
    void translate(const Vec3& t);

    /**@~english
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation and stores the result in dst.
     *
     * @~chinese 
     * ����ƽ�ƹ������󣬲��ҽ�����this���ҳ˽���洢��dst�С�
     * 
     * @param t @~english The translation values along the x, y and z axes.
     * @~chinese ��x,y��z���ƽ�ơ�
     * @param dst @~english A matrix to store the result in.
     * @~chinese ���صĽ����
     */
    void translate(const Vec3& t, Mat4* dst) const;

    /**@~english
     * Transposes this matrix.
     * @~chinese 
     * ת���Լ�(���л���)��
     */
    void transpose();

    /**@~english
     * Get the Transposed matrix.
     * @~chinese 
     * �õ�ת�þ���(���л���)��
     */
    Mat4 getTransposed() const;

    /**@~english
     * Calculates the sum of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * ����this�������mat����Ľ����
     * 
     * ע��:�Ⲣ���޸��������
     * 
     * @param mat @~english The matrix to add.
     * @~chinese Ҫ�ӵľ���
     * @return @~english The matrix sum.
     * @~chinese ��������֮�͡�
     */
    inline const Mat4 operator+(const Mat4& mat) const;
    
    /**@~english
     * Adds the given matrix to this matrix.
     * 
     * @~chinese 
     * this������ϸ����ľ���
     * 
     * @param mat @~english The matrix to add.
     * @~chinese Ҫ�ӵľ���
     * @return @~english This matrix, after the addition occurs.
     * @~chinese this�������֮�󣬷��ؽ����
     */
    inline Mat4& operator+=(const Mat4& mat);

    /**@~english
     * Calculates the difference of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * ����this�����ȥmat����Ľ����
     * 
     * ע��:�Ⲣ���޸��������
     * 
     * @param mat @~english The matrix to subtract.
     * @~chinese Ҫ��ȥ�ľ���
     * @return @~english The matrix difference.
     * @~chinese ����Ľ����
     */
    inline const Mat4 operator-(const Mat4& mat) const;

    /**@~english
     * Subtracts the given matrix from this matrix.
     * 
     * @~chinese 
     * this�����ȥ�����ľ���
     * 
     * @param mat @~english The matrix to subtract.
     * @~chinese Ҫ��ȥ�ľ���
     * @return @~english This matrix, after the subtraction occurs.
     * @~chinese this�������󣬷��ؼ����ľ���
     */
    inline Mat4& operator-=(const Mat4& mat);

    /**@~english
     * Calculates the negation of this matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * �Ծ�����󷴣��൱�ڳ��ԣ�1��
     * 
     * ע��:�Ⲣ���޸��������
     * 
     * @return @~english The negation of this matrix.
     * @~chinese �������ķ�����
     */
    inline const Mat4 operator-() const;

    /**@~english
     * Calculates the matrix product of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @~chinese 
     * ����this������˸����ľ���ĳ˻���
     * 
     * ע��:�Ⲣ���޸��������
     * 
     * @param mat @~english The matrix to multiply by.
     * @~chinese Ҫ����˵ľ���
     * @return @~english The matrix product.
     * @~chinese �˻������
     */
    inline const Mat4 operator*(const Mat4& mat) const;

    /**@~english
     * Right-multiplies this matrix by the given matrix.
     * 
     * @~chinese 
     * �ø��������ҳ��Լ�
     * 
     * @param mat @~english The matrix to multiply by.
     * @~chinese �ҳ˵ľ���
     * @return @~english This matrix, after the multiplication occurs.
     * @~chinese �ҳ��Լ�֮�󣬷��ؽ��
     */
    inline Mat4& operator*=(const Mat4& mat);

    /** @~english equals to a matrix full of zeros.  @~chinese ȫ�����*/
    static const Mat4 ZERO;
    /** @~english equals to the identity matrix.  @~chinese ��λ����*/
    static const Mat4 IDENTITY;

private:

    static void createBillboardHelper(const Vec3& objectPosition, const Vec3& cameraPosition,
                                      const Vec3& cameraUpVector, const Vec3* cameraForwardVector,
                                      Mat4* dst);
};

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * �ø����ľ���ȥ�任һ��������
 * 
 * ע:��Ը�����������Ϊһ������,������һ���㡣
 * 
 * @param v @~english The vector to transform.
 * @~chinese Ҫ�任��������
 * @param m @~english The matrix to transform by.
 * @~chinese �任����
 * @return @~english This vector, after the transformation occurs.
 * @~chinese ���ر任���������
 */
inline Vec3& operator*=(Vec3& v, const Mat4& m);

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * �ø����ľ���ȥ�任һ��������
 * 
 * ע:��Ը�����������Ϊһ������,������һ���㡣
 * 
 * @param m @~english The matrix to transform by.
 * @~chinese �任����
 * @param v @~english The vector to transform.
 * @~chinese Ҫ�任��������
 * @return @~english The resulting transformed vector.
 * @~chinese ���ر任���������
 */
inline const Vec3 operator*(const Mat4& m, const Vec3& v);

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * �ø����ľ���ȥ�任һ��������
 * 
 * ע:��Ը�����������Ϊһ������,������һ���㡣
 * 
 * @param v @~english The vector to transform.
 * @~chinese Ҫ�任��������
 * @param m @~english The matrix to transform by.
 * @~chinese �任����
 * @return @~english This vector, after the transformation occurs.
 * @~chinese ���ر任���������
 */
inline Vec4& operator*=(Vec4& v, const Mat4& m);

/**@~english
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @~chinese 
 * �ø����ľ���ȥ�任һ��������
 * 
 * ע:��Ը�����������Ϊһ������,������һ���㡣
 * 
 * @param m @~english The matrix to transform by.
 * @~chinese �任����
 * @param v @~english The vector to transform.
 * @~chinese Ҫ�任��������
 * @return @~english The resulting transformed vector.
 * @~chinese ���ر任���������
 */
inline const Vec4 operator*(const Mat4& m, const Vec4& v);

NS_CC_MATH_END
/**
 end of base group
 @}
 */
#include "math/Mat4.inl"

#endif // MATH_MAT4_H
