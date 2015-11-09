/****************************************************************************
Copyright (C) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
CopyRight (c) 2013-2014 Chukong Technologies Inc.
 
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
#ifndef __ACTION_CCPROGRESS_TIMER_H__
#define __ACTION_CCPROGRESS_TIMER_H__

#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/**
@brief @~english Progress to percentage.
 * @~chinese �ٷֱȽ�������
@details @~english This action show the target node from current percentage to the specified percentage.
        You should specify the destination percentage when creating the action.
 * @~chinese ��һ������ʾ��Ŀ��ڵ�ӵ�ǰ�ٷֱȵ�ָ���İٷֱȡ�
 * ��Ӧ���ڴ���������ʱ��ָ��Ŀ��ٷֱȡ�
@since v0.99.1
*/
class CC_DLL ProgressTo : public ActionInterval
{
public:
    /** 
     * @brief @~english Create and initializes with a duration and a destination percentage.
     * @~chinese ʹ�ó���ʱ���Ŀ��ٷֱ��������ͳ�ʼ����
     * @param duration @~english Specify the duration of the ProgressTo action. It's a value in seconds.
     * @~chinese ָ��ProgressTo�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param percent @~english Specify the destination percentage.
     * @~chinese ָ��Ŀ��ٷֱȡ�
     * @return @~english If the creation sucess, return a pointer of ProgressTo action; otherwise, return nil.
     * @~chinese ��������ɹ�,����һ��ProgressTo������ָ��;����,���ؿա�
     */
    static ProgressTo* create(float duration, float percent);

    //
    // Overrides
    //
	virtual ProgressTo* clone() const override;
	virtual ProgressTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressTo() {}
    virtual ~ProgressTo() {}

    /** 
     * @brief @~english Initializes with a duration and destination percentage. 
     * @~chinese ʹ�ó���ʱ���Ŀ��ٷֱ�����ʼ����
     * @param duration @~english Specify the duration of the ProgressTo action. It's a value in seconds.
     * @~chinese ָ��ProgressTo�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param percent @~english Specify the destination percentage.
     * @~chinese ָ��Ŀ��ٷֱȡ�
     * @return @~english If the creation sucess, return true; otherwise, return false.
     * @~chinese ��������ɹ�,����true,���򷵻�false��
     */
    bool initWithDuration(float duration, float percent);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressTo);
};

/**
@brief @~english Progress from a percentage to another percentage.
 * @~chinese ��һ���ٷֱȵ���һ���ٷֱȵĽ��ȡ�
@since v0.99.1
*/
class CC_DLL ProgressFromTo : public ActionInterval
{
public:
    /** 
     * @brief @~english Create and initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @~chinese ʹ�ó���ʱ�䣬����ʼ�ٷֱȡ��͡������ٷֱȡ��������ͳ�ʼ����
     * @param duration @~english Specify the duration of the ProgressFromTo action. It's a value in seconds.
     * @~chinese ָ��ProgressFromTo�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param fromPercentage @~english Specify the source percentage.
     * @~chinese ָ����ʼ�ٷֱȡ�
     * @param toPercentage @~english Specify the destination percentage.
     * @~chinese ָ�������ٷֱȡ�
     * @return @~english If the creation sucess, return a pointer of ProgressFromTo action; otherwise, return nil.
     * @~chinese ��������ɹ�������һ��ProgressFromTo������ָ�룬���򷵻�false��
     */
    static ProgressFromTo* create(float duration, float fromPercentage, float toPercentage);

    //
    // Overrides
    //
	virtual ProgressFromTo* clone() const override;
	virtual ProgressFromTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ProgressFromTo() {}
    virtual ~ProgressFromTo() {}

    /**
     * @brief @~english Initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @~chinese ʹ�ó���ʱ�䣬����ʼ�ٷֱȡ��͡������ٷֱȡ�����ʼ����
     * @param duration @~english Specify the duration of the ProgressFromTo action. It's a value in seconds.
     * @~chinese ָ��ProgressFromTo�����ĳ���ʱ�䡣����һ������Ϊ��λ��ֵ��
     * @param fromPercentage @~english Specify the source percentage.
     * @~chinese ָ����ʼ�ٷֱȡ�
     * @param toPercentage @~english Specify the destination percentage.
     * @~chinese ָ�������ٷֱȡ�
     * @return @~english If the creation sucess, return true; otherwise, return false.
     * @~chinese ��������ɹ�,����true,���򷵻�false��
     */
    bool initWithDuration(float duration, float fromPercentage, float toPercentage);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProgressFromTo);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCPROGRESS_TIMER_H__
