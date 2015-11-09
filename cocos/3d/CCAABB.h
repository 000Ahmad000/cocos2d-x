/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_AABB_H__
#define __CC_AABB_H__

#include "base/ccMacros.h"
#include "math/CCMath.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class AABB
 * @brief  @~english Axis Aligned Bounding Box (AABB), usually used to detect the collision at early step
 * @~chinese ������Χ�У�������Χ����һ������İ�Χ�У�
 * ���ı�����������ϵ�е���ƽ�У�ͨ����������ײ���֮����ǰ���ж�.
 */
class CC_DLL AABB
{

public:
    /**
     * Constructor.
     * @lua new
     */
    AABB();
    
    /**
     * @~english Constructor. construct the AABB object from min & max vector. @~chinese ���캯����ͨ������������С����������AABB
     * @lua new
     * @param min @~english The min vector
     * @~chinese ��С����
     * @param max The max vector
     * @~chinese �������
     */
    AABB(const Vec3& min, const Vec3& max);
    
    /**
     * @~english Constructor.
     * @~chinese �������캯��
     */
    AABB(const AABB& box);
    
    /**
     * @~english Gets the center point of the bounding box.
     * @~chinese ��ð�Χ�е��е�
     * @return @~english the centre point of the bounding box.
     * @~chinese ��Χ�е��е�
     */
    Vec3 getCenter();

    /**
     * @~english Gets the corners of the bounding box.
     * @~chinese ��ȡ��Χ�и�������
     * @param dst @~english A pointer to corners array.
     * @~chinese ���������ָ��
     * @note @~english Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
     * verts[0] : left top front
     * verts[1] : left bottom front
     * verts[2] : right bottom front
     * verts[3] : right top front
     *
     * Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
     * verts[4] : right top back
     * verts[5] : right bottom back
     * verts[6] : left bottom back
     * verts[7] : left top back
     * @~chinese �����ڸ���λ�ñ�ʾ�Ķ���������ʾ��ǰ����ָ����Y�Ḻ���򿴶��ԣ���
     * verts[0] : ����ǰ
     * verts[1] : ����ǰ
     * verts[2] : ����ǰ
     * verts[3] : ����ǰ
     *
     * verts[4] : ���Ϻ�
     * verts[5] : ���º�
     * verts[6] : ���º�
     * verts[7] : ���Ϻ�
     */
    void getCorners(Vec3 *dst) const;

    /**
     * @~english Tests whether this bounding box intersects with the specified bounding object.
     * @~chinese ������ָ����AABB�Ƿ��ཻ
     * @param aabb @~english The specified bounding box.
     * @~chinese ָ����AABB
     * @return @~english Return true when two AABBs intersect, otherwise return false.
     * @~chinese ����AABB�ཻʱ����true����֮��false
     */
    bool intersects(const AABB& aabb) const;

    /**
     * @~english Check if the point is contained in the bounding box.
     * @~chinese ���ָ�����Ƿ��ڰ�Χ����
     * @param point @~english The specified point @~chinese ָ���ĵ�
     * @return @~english Return true when the point is contained in the bounding box, otherwise return false.
     * @~chinese ��ָ���ڰ�Χ����ʱ����true����֮����false
     */
    bool containPoint(const Vec3& point) const;

    /**
     * @~english Sets this bounding box to the smallest bounding box that contains both this bounding object and the specified bounding box.
     * @~chinese �ϲ�ָ����Χ�У�ʹ����Χ�б�Ϊ��С���������ߵİ�Χ��
     * @param box @~english The specified box. 
     * @~chinese ָ���İ�Χ��
     */
    void merge(const AABB& box);

    /**
     * @~english Sets this bounding box to the specified values.
     * @~chinese ͨ��min max ���� �����ð�Χ��
     * @param min @~english the min vector
     * @~chinese min����
     * @param max @~english the max vector
     * @~chinese max����
     */
    void set(const Vec3& min, const Vec3& max);
    
    /**
     * @~english Reset min and max value.If you invoke this method, isEmpty() shall return true.
     * @~chinese �����Χ��
     */
    void reset();
    
    /**
     * @~english Check the AABB object is empty(reset).
     * @~chinese ����Χ���Ƿ�Ϊ��
     * @return @~english Return true when the AABB object is empty, otherwise return false.
     * @~chinese ����Χ�ж���Ϊ��ʱ����true����֮�򷵻�false
     */
    bool isEmpty() const;

    /**
     * @~english Update the _min and _max from the given point.
     * @~chinese ͨ��һ���������������°�Χ��
     * @param point @~english The points array.
     * @~chinese ��������
     * @param num @~english The pints array's size.
     * @~chinese ����Ĵ�С
     */
    void updateMinMax(const Vec3* point, ssize_t num);
    
    /**
     * @~english Transforms the bounding box by the given transformation matrix.
     * @~chinese ͨ��ָ���ı任�������任��Χ��
     * @param mat @~english the specified transform-matrix.
     * @~chinese ָ���ı任����
     */
    void transform(const Mat4& mat);

public:
    Vec3 _min;
    Vec3 _max;
};

// end of 3d group
/// @}

NS_CC_END

#endif
