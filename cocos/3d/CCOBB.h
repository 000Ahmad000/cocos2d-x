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

#ifndef __CC_OBB_H__
#define __CC_OBB_H__

#include "CCAABB.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @~english Oritened Bounding Box(OBB)
 * @class OBB
 * @brief @~english The OBB is similar to the AABB but the bounding box has the same direction as Sprite3D. so it's collistion detection more precise than AABB
 * @~chinese  OBB��Χ����AABB��Χ�����ƣ�������ֲ�����ϵ�������Ტ������������ϵ��������ƽ�У������������������ת�������������ṩ��AABB��Ϊ׼ȷ����ײ���
 * @js NA
 */
class CC_DLL OBB
{
public:
    OBB();

    /*
     * @~english Construct obb from axis aligned bounding box(AABB).
     * @~chinese ͨ��AABB ����OBB
     * @param aabb @~english The AABB object.
     * @~chinese AABB ����
     * @lua NA
     */
    OBB(const AABB& aabb);
    
    /*
     * @~english Construct obb from points.
     * @~chinese ͨ�������Ķ������鴴��OBB
     * @param verts @~english Vertices array.
     * @~chinese �����Ķ�������
     * @param num @~english The size of the verticies array. 
     * @~chinese ��������Ĵ�С
     * @lua NA
     */
    OBB(const Vec3* verts, int num);
    
    /**
     * @~english Check if the point is contained in the bounding box.
     * @~chinese ���һ�����Ƿ��ڰ�Χ����
     * @param point @~english The specified point.
     * @~chinese �����ĵ�
     * @return @~english Return true when the point is contained in the bounding box, otherwise return false.
     * @~chinese ���õ��ڰ�Χ����ʱ������True����֮����false.
     */
    bool containPoint(const Vec3& point) const;

    /*
     * @~english Specify obb values
     * @~chinese ָ��OBB���������
     * @param center @~english The obb's center.
     * @~chinese OBB�е�
     * @param _xAxis @~english The obb's X axis in wrold space.
     * @~chinese OBB����������ϵ�µ�X��
     * @param _yAxis @~english The obb's Y axis in wrold space.
     * @~chinese OBB����������ϵ�µ�Y��
     * @param _zAxis @~english The obb's Z axis in wrold space.
     * @~chinese OBB����������ϵ�µ�Z��
     * @param _extents @~english The obb's size.
     * @~chinese OBB�ĳߴ�(���߱߳�)
     */
    void set(const Vec3& center, const Vec3& _xAxis, const Vec3& _yAxis, const Vec3& _zAxis, const Vec3& _extents);
    
    /*
     * Clear obb
     * @~chinese ���OBB����
     */ 
    void reset();

    /** 
     * @~english Get Obb's corners.
     * @~chinese ��ȡOBB�ĸ�����
     * @param verts @~english The Corners vertices array.
     * @~chinese ��������
     * @note @~english Face to the obb's -z direction
     * verts[0] : left top front
     * verts[1] : left bottom front
     * verts[2] : right bottom front
     * verts[3] : right top front
     *
     * face to the obb's z direction
     * verts[4] : right top back
     * verts[5] : right bottom back
     * verts[6] : left bottom back
     * verts[7] : left top back
     * @~chinese ������XOYƽ�泯-z������ȥ��OBB�����������Ϊ
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
    void getCorners(Vec3* verts) const;
    
    /**
    * @~english Tests whether this bounding box intersects the specified bounding object.
    * @~chinese ���ָ���İ�Χ���Ƿ������ཻ
    * @param box @~english The specified bounding box.
    * @~chinese ָ���İ�Χ��
    * @return @~english Return true when two OOBBS intersect, otherwise return false.
    * @~chinese ���ཻʱ����true����֮����false
    */
    bool intersects(const OBB& box) const;
    
	/**
     * @~english Transforms the obb by the given transformation matrix.
     * @~chinese ͨ�������ľ���任OBB����
     * @param mat @~english The transform matrix.
     * @~chinese ָ���ı任����
     */
    void transform(const Mat4& mat);
    
protected:
    /*
    * @~english Compute extX, extY, extZ
    */
    void computeExtAxis()
    {
        _extentX = _xAxis * _extents.x;
        _extentY = _yAxis * _extents.y;
        _extentZ = _zAxis * _extents.z;
    }
    
    /*
     * Project point to the target axis
     */
    float projectPoint(const Vec3& point, const Vec3& axis) const;
    
    /*
     * Calculate the min and max project value of through the box's corners
     */
    void getInterval(const OBB& box, const Vec3& axis, float &min, float &max) const;
    
    /*
     * Get the edge of x y z axis direction
     */
    Vec3 getEdgeDirection(int index) const;
    
    /*
     * Get the face of x y z axis direction
     */
    Vec3 getFaceDirection(int index) const;

public:
    Vec3 _center;   // obb center
    Vec3 _xAxis;    // x axis of obb, unit vector
    Vec3 _yAxis;    // y axis of obb, unit vector
    Vec3 _zAxis;    // z axis of obb, unit vector
    Vec3 _extentX;  // _xAxis * _extents.x
    Vec3 _extentY;  // _yAxis * _extents.y
    Vec3 _extentZ;  // _zAxis * _extents.z
    Vec3 _extents;  // obb length along each axis
};

// end of 3d group
/// @}

NS_CC_END

#endif
