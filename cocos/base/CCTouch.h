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

#ifndef __CC_TOUCH_H__
#define __CC_TOUCH_H__

#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

/**
 * @addtogroup base
 * @{
 */

/** @class Touch
 * @brief @~english Encapsulates the Touch information, such as touch point, id and so on,
 and provides the methods that commonly used.
 * @~chinese ��װ�˴�����ص���Ϣ���紥���㣬id�ȵȡ�
 * �����ṩ�˳��õķ�����
 */
class CC_DLL Touch : public Ref
{
public:
    /** @~english
     * Dispatch mode, how the touches are dispatched.
     * @~chinese 
     * ��Ϣ�ַ�ģʽ��������ηַ������¼���
     * @js NA
     */
    enum class DispatchMode {
        ALL_AT_ONCE, /** @~english All at once. @~chinese ��㴥���� */
        ONE_BY_ONE,  /** @~english One by one. @~chinese ���㴥���� */
    };

    /** @~english Constructor.
     * @~chinese ���캯����
     * @js ctor
     */
    Touch() 
        : _id(0),
        _startPointCaptured(false)
    {}

    /** @~english Returns the current touch location in OpenGL coordinates.
     *
     * @~chinese ��ȡ��ǰ�Ĵ������� OpenGL ����ϵ�µ����ꡣ
     * 
     * @return @~english The current touch location in OpenGL coordinates.
     * @~chinese ��ǰ�Ĵ������� OpenGL ����ϵ�µ����ꡣ
     */
    Vec2 getLocation() const;
    /** @~english Returns the previous touch location in OpenGL coordinates.
     *
     * @~chinese ��ȡ֮ǰ�Ĵ������� OpenGL ����ϵ�µ����ꡣ
     * 
     * @return @~english The previous touch location in OpenGL coordinates.
     * @~chinese ֮ǰ�Ĵ������� OpenGL ����ϵ�µ����ꡣ
     */
    Vec2 getPreviousLocation() const;
    /** @~english Returns the start touch location in OpenGL coordinates.
     *
     * @~chinese ��ȡ������ʼ���� OpenGL ����ϵ�µ����ꡣ
     * 
     * @return @~english The start touch location in OpenGL coordinates.
     * @~chinese ������ʼ���� OpenGL ����ϵ�µ����ꡣ
     */
    Vec2 getStartLocation() const;
    /** @~english Returns the delta of 2 current touches locations in screen coordinates.
     *
     * @~chinese ��ȡ��ǰ��������������Ļ����ϵ�µĲ�ֵ��
     * 
     * @return @~english The delta of 2 current touches locations in screen coordinates.
     * @~chinese ��ǰ��������������Ļ����ϵ�µĲ�ֵ��
     */
    Vec2 getDelta() const;
    /** @~english Returns the current touch location in screen coordinates.
     *
     * @~chinese ��ȡ��ǰ����������Ļ����ϵ�µ����ꡣ
     * 
     * @return @~english The current touch location in screen coordinates.
     * @~chinese ��ǰ����������Ļ����ϵ�µ����ꡣ
     */
    Vec2 getLocationInView() const;
    /** @~english Returns the previous touch location in screen coordinates. 
     *
     * @~chinese ��ȡ֮ǰ�Ĵ���������Ļ����ϵ�µ����ꡣ
     * 
     * @return @~english The previous touch location in screen coordinates.
     * @~chinese ֮ǰ�Ĵ���������Ļ����ϵ�µ����ꡣ
     */
    Vec2 getPreviousLocationInView() const;
    /** @~english Returns the start touch location in screen coordinates.
     *
     * @~chinese ��ȡ������ʼ������Ļ����ϵ�µ����ꡣ
     * 
     * @return @~english The start touch location in screen coordinates.
     * @~chinese ������ʼ������Ļ����ϵ�µ����ꡣ
     */
    Vec2 getStartLocationInView() const;
    
    /** @~english Set the touch infomation. It always used to monitor touch event.
     *
     * @~chinese ���ô�����ص���Ϣ�����ڼ�ش����¼���
     * 
     * @param id @~english A given id
     * @~chinese һ��������id
     * @param x @~english A given x coordinate.
     * @~chinese һ��������x���ꡣ
     * @param y @~english A given y coordinate.
     * @~chinese һ��������y���ꡣ
     */
    void setTouchInfo(int id, float x, float y)
    {
        _id = id;
        _prevPoint = _point;
        _point.x   = x;
        _point.y   = y;
        if (!_startPointCaptured)
        {
            _startPoint = _point;
            _startPointCaptured = true;
            _prevPoint = _point;
        }
    }
    /** @~english Get touch id.
     * @~chinese ��ȡ����id��
     *
     * @return @~english The id of touch.
     * @~chinese ����id
     * @js getId
     * @lua getId
     */
    int getID() const
    {
        return _id;
    }

private:
    int _id;
    bool _startPointCaptured;
    Vec2 _startPoint;
    Vec2 _point;
    Vec2 _prevPoint;
};

// end of base group
/// @}

NS_CC_END

#endif  // __PLATFORM_TOUCH_H__
