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
#ifndef __CCANIMATIONCURVE_H__
#define __CCANIMATIONCURVE_H__

#include <functional>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "math/CCMath.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#undef NEAR
#endif

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @enum EvaluateType
 * @brief @~english The evalute type for the curve evaluation(interpolation).
 * @~chinese �������(��ֵ)����
 */
enum class EvaluateType
{
    /**
     * linear interpolation
     * @~chinese �����Բ�ֵ
     **/
    INT_LINEAR, 
    /**
     * Nearest neighbor interpolation
     * @~chinese ������ֵ
     */
    INT_NEAR,
    /**
     * Quaternion spherical linear interpolation
     * @~chinese �������Բ�ֵ(slerp)
     **/
    INT_QUAT_SLERP,
    /**
     * User defined interpolation.
     * @~chinese �û��Զ����ֵ����
     */
    INT_USER_FUNCTION,
};

/**
 * @class AnimationCurve
 * @brief @~english Curve of bone's position, rotation or scale
 * @~chinese �������ߣ����Ա�ʾ����������ƽ�ơ���ת���������ŵ�����
 * @lua NA
 */
template <int componentSize>
class AnimationCurve: public Ref
{
public:
    
    /**
     * @~english Create animation curve.
     * @~chinese ��������������
     * @param @~english Keytime the key time value.
     * @~chinese ÿ���ؼ�֡��Ӧ��ʱ�������
     * @param value @~english The value.
     * @~chinese ÿ���ؼ�֡ʱ���ߵ�ֵ������
     * @param count @~english The count of key frames array.
     * @~chinese �ؼ�֡�����С
     **/
    static AnimationCurve* create(float* keytime, float* value, int count);
    
    /**
     * @~english Evalute value of time
     * @~chinese ��⣨��ֵ������ʱ��ʱ�����ߵ�ֵ
     * @param time @~english Time to be estimated
     * @~chinese ������ʱ���
     * @param dst @~english Estimated value of that time
     * @~chinese �õ�ʱ�������Ĺ���ֵ��ָ��
     * @param type @~english EvaluateType
     * @~chinese ���ʱ�ķ�������
     */
    void evaluate(float time, float* dst, EvaluateType type) const;
    
    /**
     * @~english Set evaluate function, allow the user use own function.
     * @~chinese ������⣨��ֵ�������������û�ʹ���Լ��Ĳ�ֵ����
     * @param fun @~english The callback function
     * @~chinese ��ֵ���û��ص�����
     */
    void setEvaluateFun(std::function<void(float time, float* dst)> fun);
    
    /**
     * @~english Get start time
     * @~chinese ��ȡ��ʼʱ��
     * @return @~english The start time
     * @~chinese ��ʼʱ��
     */
    float getStartTime() const;
    
    /**
     * @~english Get the end time.
     * @~chinese ��ȡ����ʱ��
     * @return @~english The end time.
     * @~chinese ����ʱ��
     */
    float getEndTime() const;
    
CC_CONSTRUCTOR_ACCESS:

    /**
     * Constructor
     */
    AnimationCurve();

    /**
     * Destructor
     */
    virtual ~AnimationCurve();
    
    /**
     * @~english Determine index by time.
     * @~chinese ��ȡ����ʱ���Ĺؼ�֡����
     * @param time @~english The specified time
     * @~chinese ������ĳһʱ���
     * @return @~english The index.
     * @~chinese �ؼ�֡����
     */
    int determineIndex(float time) const;
    
protected:
    
    float* _value;   //
    float* _keytime; //key time(0 - 1), start time _keytime[0], end time _keytime[_count - 1]
    int _count;
    int _componentSizeByte; //component size in byte, position and scale 3 * sizeof(float), rotation 4 * sizeof(float)
    
    std::function<void(float time, float* dst)> _evaluateFun; //user defined function
};

// end of 3d group
/// @}

NS_CC_END

#include "CCAnimationCurve.inl"

#endif
