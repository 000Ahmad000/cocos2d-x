/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __MATH_CCAFFINETRANSFORM_H__
#define __MATH_CCAFFINETRANSFORM_H__

#include "platform/CCPlatformMacros.h"

#include "math/CCGeometry.h"
#include "math/CCMath.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/**
@struct AffineTransform
@brief
@~english
 Affine transform
 a   b    0
 c   d    0
 tx  ty   1
 
 Identity
 1   0    0
 0   1    0
 0   0    1
 * @~chinese 
 * ����任
 a   b    0
 c   d    0
 tx  ty   1
 * 
 * ��λ�任
 1   0    0
 0   1    0
 0   0    1
 */
struct CC_DLL AffineTransform {
    float a, b, c, d;
    float tx, ty;
    /**@~english indentity AffineTransform. @~chinese ��λ�任��*/
    static const AffineTransform IDENTITY;
};

/**@~english Make affine transform from a, b, c, d, tx, ty.. @~chinese ��a,b,c,d,tx,ty��������任��*/
CC_DLL AffineTransform __CCAffineTransformMake(float a, float b, float c, float d, float tx, float ty);
#define AffineTransformMake __CCAffineTransformMake

/**@~english Multiply point (x,y,1) by a  affine tranform. @~chinese �÷������任��(x,y,1)��*/
CC_DLL Vec2 __CCPointApplyAffineTransform(const Vec2& point, const AffineTransform& t);
#define PointApplyAffineTransform __CCPointApplyAffineTransform

/**@~english Multiply size (width,height,0) by a  affine tranform. @~chinese �÷������任(width,height,0)��*/
CC_DLL Size __CCSizeApplyAffineTransform(const Size& size, const AffineTransform& t);
#define SizeApplyAffineTransform __CCSizeApplyAffineTransform
/**@~english Make identity affine transform. @~chinese ����һ����λ����任����*/
CC_DLL AffineTransform AffineTransformMakeIdentity();
/**@~english Transform Rect, which will transform the four vertice of the point. @~chinese �任����,�⽫����任���ε��ĸ����㡣*/
CC_DLL Rect RectApplyAffineTransform(const Rect& rect, const AffineTransform& anAffineTransform);
/**@~english
 Transform Rect by Mat4.
 * @~chinese 
 * ʹ��Mat4�任Rect.
 */
CC_DLL Rect RectApplyTransform(const Rect& rect, const Mat4& transform);
/**@~english
 Transform Rect by Mat4.
 * @~chinese 
 * ʹ��Mat4�任Vec2.
 */
CC_DLL Vec2 PointApplyTransform(const Vec2& point, const Mat4& transform);
/**@~english
 Translation, equals
 1  0  1
 0  1  0   * affine transform
 tx ty 1
 * @~chinese 
 * ����ƽ��,��Ч���ȼ���
 1  0  1
 0  1  0   * affinetransform
 tx ty 1
 */
CC_DLL AffineTransform AffineTransformTranslate(const AffineTransform& t, float tx, float ty);
/**@~english
 Rotation, equals
 cos(angle)   sin(angle)   0
 -sin(angle)  cos(angle)   0  * AffineTransform
 0            0            1
 * @~chinese 
 * ������ת,�ȼ���
 cos(angle)   sin(angle)   0
 -sin(angle)  cos(angle)   0  * AffineTransform
 0            0            1
 */
CC_DLL AffineTransform AffineTransformRotate(const AffineTransform& aTransform, float anAngle);
/**@~english
 Scale, equals
 sx   0   0
 0    sy  0  * affineTransform
 0    0   1
 * @~chinese 
 * ��������,�ȼ���
 sx   0   0
 0    sy  0  * affineTransform
 0    0   1
 */
CC_DLL AffineTransform AffineTransformScale(const AffineTransform& t, float sx, float sy);
/**@~english Concat two affine transform, t1*t2.  @~chinese ������������任t1*t2 */
CC_DLL AffineTransform AffineTransformConcat(const AffineTransform& t1, const AffineTransform& t2);
/**@~english Compare affine transform. @~chinese �жϷ���任�Ƿ���ȡ�*/
CC_DLL bool AffineTransformEqualToTransform(const AffineTransform& t1, const AffineTransform& t2);
/**@~english Get the inverse of affine transform. @~chinese �õ�����任���档*/
CC_DLL AffineTransform AffineTransformInvert(const AffineTransform& t);
/**@~english Concat Mat4, return t1*t2  @~chinese ���˾���t1*t2��*/
CC_DLL Mat4 TransformConcat(const Mat4& t1, const Mat4& t2);
/**@~english identity affineTransform. @~chinese ��λ����任����*/
extern CC_DLL const AffineTransform AffineTransformIdentity;

NS_CC_END

// end of base transform
/// @}

#endif // __MATH_CCAFFINETRANSFORM_H__
