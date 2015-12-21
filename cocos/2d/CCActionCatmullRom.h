/****************************************************************************
 * Copyright (c) 2008 Radu Gruian
 * Copyright (c) 2011 Vit Valentin
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Original code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So
 *
 * Adapted to cocos2d-x by Vit Valentin
 *
 * Adapted from cocos2d-x to cocos2d-iphone by Ricardo Quesada
 ***************************************************************************/


#ifndef __CCACTION_CATMULLROM_H__
#define __CCACTION_CATMULLROM_H__

#include <vector>

#include "2d/CCActionInterval.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN;

class Node;

/**
 * @addtogroup actions
 * @{
 */

/** @~english An Array that contain control points.
 * Used by CardinalSplineTo, CardinalSplineBy, CatmullRomTo and CatmullRomBy actions.
 * @~chinese һ���������Ƶ���Ϣ�����顣
 * �������������߶���CardinalSplineTo��CardinalSplineBy��Catmull-Rom�������߶���CatmullRomTo��CatmullRomBy��ʹ��
 * @ingroup Actions
 * @js NA
 */
class CC_DLL PointArray : public Ref, public Clonable
{
public:

    /** @~english Creates and initializes a Points array with capacity.
     * @~chinese ��������ʼ��һ��һ�����������顣
     * @param capacity @~english The size of the array.
     * @~chinese �����������
     * @js NA
     */
    static PointArray* create(ssize_t capacity);

    /**
     * @js NA
     * @lua NA
     */
    virtual ~PointArray();
    /**
     * @js NA
     * @lua NA
     */
    PointArray();

    /** @~english Initializes a Catmull Rom or a Cardinal Spline control point array with a capacity hint.
     *
     * @~chinese ��һ��������ʼ��һ��Catmull-Rom����������������Ƶ����顣
     * 
     * @param capacity @~english The size of the array.
     * @~chinese �����������
     * @return @~english True if successfully initialized, false otherwise.
     * @~chinese �����ʼ���ɹ��򷵻�True�����򷵻�False��
     * @js NA
     */
    bool initWithCapacity(ssize_t capacity);

    /** @~english Appends a control point.
     *
     * @~chinese ������ĩβ����һ�����Ƶ㡣
     * 
     * @param controlPoint @~english A control point.
     * @~chinese һ�����Ƶ㡣
     * @js NA
     */
    void addControlPoint(Vec2 controlPoint);

    /** @~english Inserts a control point at a given index.
     *
     * @~chinese ������ָ��λ�ò���һ�����Ƶ㡣
     * 
     * @param controlPoint @~english A control point.
     * @~chinese һ�����Ƶ㡣
     * @param index @~english The index to insert the point.
     * @~chinese �����λ�á�
     * @js NA
     */
    void insertControlPoint(Vec2 &controlPoint, ssize_t index);

    /** @~english Replaces an existing control point at a given index.
     *
     * @~chinese ������ָ��λ���滻һ�����Ƶ㡣
     * 
     * @param controlPoint @~english A new control point.
     * @~chinese һ���µĿ��Ƶ㡣
     * @param index @~english The index of the contorl point to be replaced.
     * @~chinese ��Ҫ�滻�Ŀ��Ƶ��������е�λ�á�
     * @js NA
     */
    void replaceControlPoint(Vec2 &controlPoint, ssize_t index);

    /** @~english Get the value of a control point at a given index.
     *
     * @~chinese �������ָ��λ�õĿ��Ƶ㡣
     * 
     * @param index @~english The index of the control point.
     * @~chinese ���Ƶ��������е�λ�á�
     * @return @~english Return the control point.
     * @~chinese ���ؿ��Ƶ㡣
     * @js NA
     */
    Vec2 getControlPointAtIndex(ssize_t index);

    /** @~english Deletes a control point at a given index
     *
     * @~chinese ɾ��ָ��λ�õĿ��Ƶ�
     * 
     * @param index @~english The index of the control point.
     * @~chinese ��Ҫɾ���Ŀ��Ƶ��������е�λ�á�
     * @js NA
     */
    void removeControlPointAtIndex(ssize_t index);

    /** @~english Returns the number of objects of the control point array.
     *
     * @~chinese ���������еĿ��Ƶ�������
     * 
     * @return @~english The number of objects of the control point array.
     * @~chinese �����еĿ��Ƶ�������
     * @js NA
     */
    ssize_t count() const;

    /** @~english Returns a new copy of the array reversed. User is responsible for releasing this copy.
     *
     * @~chinese ����һ���µĿ��Ƶ�����Ŀ��������������ԭ����ķ�ת���û������ͷ����������
     * 
     * @return @~english A new copy of the array reversed.
     * @~chinese ����ķ�ת������
     * @see `reverseInline`
     * @js NA
     */
    PointArray* reverse() const;

    /** @~english Reverse the current control point array inline, without generating a new one.
     * @~chinese ֱ�ӷ�ת��ǰ���飬���API��������µ����顣
     * @see `reverse`
     * @js NA
     */
    void reverseInline();
    /**
     * @js NA
     * @lua NA
     */
    virtual PointArray* clone() const;
    /**
     * @js NA
     */
    const std::vector<Vec2*>* getControlPoints() const;
    /**
     * @js NA
     */
    void setControlPoints(std::vector<Vec2*> *controlPoints);
private:
    /** @~english Array that contains the control points.  @~chinese ���Ƶ����顣*/
    std::vector<Vec2*> *_controlPoints;
};

/** @class CardinalSplineTo
 * @~english
 * An action that moves the target with a Cardinal Spline curve to a destination point.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 * @~chinese 
 * CardinalSplineTo������һ����Ŀ��ڵ���Cardinal Spline�������ߵ���Ŀ�ĵصĶ�����
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 * @ingroup Actions
 */
class CC_DLL CardinalSplineTo : public ActionInterval
{
public:

    /** @~english Creates an CardinalSplineTo action with a Cardinal Spline array of control points and tension.
     * @~chinese ��һ�������������߿��Ƶ���Ϣ����������һ�������������߶�����
     * @param duration @~english Duration in seconds.
     * @~chinese ����Ϊ��λ�ĳ���ʱ�䡣
     * @param points @~english An control point array.
     * @~chinese ���Ƶ����顣
     * @param tension @~english Goodness of fit.
     * @~chinese ����������
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var t,var table)
     * In lua: local create(local t, local table)
     * @endcode
     */
    static CardinalSplineTo* create(float duration, PointArray* points, float tension);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CardinalSplineTo();
    /**
     * @js ctor
     * @lua NA
     */
    CardinalSplineTo();

    /** @~english
     * Initializes the action with a duration and an array of control points.
     *
     * @~chinese 
     * �ó���ʱ��Ϳ��Ƶ������ʼ�����������
     * 
     * @param duration @~english Duration in seconds.
     * @~chinese ����Ϊ��λ�ĳ���ʱ�䡣
     * @param points @~english An control point array.
     * @~chinese ���Ƶ����顣
     * @param tension @~english Goodness of fit.
     * @~chinese ����������
     */
    bool initWithDuration(float duration, PointArray* points, float tension);
    /** @~english It will update the target position and change the `_previousPosition` to `newPos`
     *
     * @~chinese ��������Ŀ��λ�ò���`_previousPosition`����Ϊ`newPos`
     * 
     * @param newPos @~english The new position.
     * @~chinese �µ�λ�á�
     */
    virtual void updatePosition(Vec2 &newPos);
    /** @~english Return the control point array.
     *
     * @~chinese ���ؿ��Ƶ����顣
     * 
     * @return @~english Control point array.
     * @~chinese ���Ƶ�����
     */
    inline PointArray* getPoints() { return _points; }
    /**
     * @js NA
     * @lua NA
     */
    inline void setPoints(PointArray* points)
    {
        CC_SAFE_RETAIN(points);
        CC_SAFE_RELEASE(_points);
        _points = points;
    }

    // Overrides
    virtual CardinalSplineTo *clone() const override;
    virtual CardinalSplineTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    
    /**
     * @param time @~english Interval in seconds.
     * @~chinese ����Ϊ��λ��ʱ������
     */
    virtual void update(float time) override;

protected:
    /** @~english Array of control points  @~chinese һϵ�п��Ƶ�*/
    PointArray *_points;
    float _deltaT;
    float _tension;
    Vec2	_previousPosition;
    Vec2	_accumulatedDiff;
};

/** @class CardinalSplineBy
 * @~english
 * An action that moves the target with a Cardinal Spline curve by a certain distance.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 * @~chinese 
 * CardinalSplineBy������һ����Ŀ��ڵ���Cardinal Spline���������ƶ�һ������Ķ�����
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 * @ingroup Actions
 */
class CC_DLL CardinalSplineBy : public CardinalSplineTo
{
public:

    /** @~english Creates an CardinalSplineBy action with a Cardinal Spline array of control points and tension.
     * @~chinese ��һ�������������߿��Ƶ���Ϣ����������һ�������������߶�����
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var t,var table).
     * In lua: local create(local t, local table).
     * @endcode
     * 
     * @param duration @~english Duration in seconds.
     * @~chinese ����Ϊ��λ�ĳ���ʱ�䡣
     * @param points @~english An control point array.
     * @~chinese ���Ƶ����顣
     * @param tension @~english Goodness of fit.
     * @~chinese ����������
     */
    static CardinalSplineBy* create(float duration, PointArray* points, float tension);

    CardinalSplineBy();

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void updatePosition(Vec2 &newPos) override;
    virtual CardinalSplineBy *clone() const override;
    virtual CardinalSplineBy* reverse() const override;

protected:
    Vec2 _startPosition;
};

/** @class CatmullRomTo
 * @~english
 * An action that moves the target with a CatmullRom curve to a destination point.
 * A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 * @~chinese 
 * CatmullRomTo������һ����Ŀ��ڵ���Catmull-Rom�������ߵ���Ŀ�ĵصĶ�����
 * һ��Catmull-Rom����������һ������Ϊ0.5�Ļ����������ߡ�
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 * @ingroup Actions
 */
class CC_DLL CatmullRomTo : public CardinalSplineTo
{
public:

    /** @~english Creates an CatmullRomTo action with an array of control points and tension.
     * @~chinese ��һ��Catmull-Rom�������߿��Ƶ���Ϣ����������һ��Catmull-Rom�������߶�����
     * @param dt @~english Duration in seconds.
     * @~chinese ����Ϊ��λ�ĳ���ʱ�䡣
     * @param points @~english An control point array.
     * @~chinese ���Ƶ����顣
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var dt,var table).
     * In lua: local create(local dt, local table).
     * @endcode
     */
    static CatmullRomTo* create(float dt, PointArray* points);

    /** @~english
     * Initializes the action with a duration and an array of points.
     *
     * @~chinese 
     * �ó���ʱ��Ϳ��Ƶ������ʼ�����������
     * 
     * @param dt @~english Duration in seconds.
     * @~chinese ����Ϊ��λ�ĳ���ʱ�䡣
     * @param points @~english An control point array.
     * @~chinese ���Ƶ����顣
     */
    bool initWithDuration(float dt, PointArray* points);

    // Override
    virtual CatmullRomTo *clone() const override;
    virtual CatmullRomTo *reverse() const override;
};

/** @class CatmullRomBy
 * @~english
 * An action that moves the target with a CatmullRom curve by a certain distance.
 * A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 * @~chinese 
 * CatmullRomBy������һ����Ŀ��ڵ���Catmull-Rom���������ƶ�һ������Ķ�����
 * һ��Catmull-Rom����������һ������Ϊ0.5�Ļ����������ߡ�
 * http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 * @ingroup Actions
 */
class CC_DLL CatmullRomBy : public CardinalSplineBy
{
public:
    /** @~english Creates an CatmullRomBy action with an array of control points and tension.
     * @~chinese ��һ��Catmull-Rom�������߿��Ƶ���Ϣ����������һ��Catmull-Rom�������߶�����
     * @param dt @~english Duration in seconds.
     * @~chinese ����Ϊ��λ�ĳ���ʱ�䡣
     * @param points @~english An control point array.
     * @~chinese ���Ƶ����顣
     * @code
     * When this function bound to js or lua,the input params are changed.
     * In js: var create(var dt,var table).
     * In lua: local create(local dt, local table).
     * @endcode
     */
    static CatmullRomBy* create(float dt, PointArray* points);

    /** @~english Initializes the action with a duration and an array of points.
     *
     * @~chinese �ó���ʱ��Ϳ��Ƶ������ʼ�����������
     * 
     * @param dt @~english Duration in seconds.
     * @~chinese ����Ϊ��λ�ĳ���ʱ�䡣
     * @param points @~english An control point array.
     * @~chinese ���Ƶ����顣
     */
    bool initWithDuration(float dt, PointArray* points);

    // Override
    virtual CatmullRomBy *clone() const override;
    virtual CatmullRomBy *reverse() const override;

};

/** @~english Returns the Cardinal Spline position for a given set of control points, tension and time.  @~chinese ����һ�������Ŀ��Ƶ㣬������ʱ��㷵�ػ������������ϵ�λ�á� */
extern CC_DLL Vec2 ccCardinalSplineAt(Vec2 &p0, Vec2 &p1, Vec2 &p2, Vec2 &p3, float tension, float t);

// end of actions group
/// @}

NS_CC_END;

#endif // __CCACTION_CATMULLROM_H__
