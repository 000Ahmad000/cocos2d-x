/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
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

#ifndef __ACTION_CCINTERVAL_ACTION_H__
#define __ACTION_CCINTERVAL_ACTION_H__

#include <vector>

#include "2d/CCAction.h"
#include "2d/CCAnimation.h"
#include "base/CCProtocols.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Node;
class SpriteFrame;
class EventCustom;

/**
 * @addtogroup actions
 * @{
 */

/** @class ActionInterval
 * @brief @~english An interval action is an action that takes place within a certain period of time.
 * It has an start time, and a finish time. The finish time is the parameter duration plus the start time.
 * 
 * These ActionInterval actions have some interesting properties, like:
 * - They can run normally (default)
 * - They can run reversed with the reverse method
 * - They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.
 * 
 * For example, you can simulate a Ping Pong effect running the action normally and
 * then running it again in Reverse mode.
 * 
 * Example:
 * 
 * @~chinese ʱ����������ActionInterval����һ����һ��ʱ����ִ�еĶ�����
 * ����һ����ʼʱ������ʱ�䡣���ʱ�������ʼʱ����ϳ���ʱ��
 * 
 * ��ЩActionInterval������һЩ��Ȥ������,��:
 * - ���ǿ�����������(Ĭ��)
 * - ���ǿ���ͨ����ת������ת����Ч��
 * - ����������ʱ����ͨ�����ٶȣ�Accelerate�������ټ��٣�AccelDeccel�����ٶȣ�Speed���ȶ������޸���������ʱ���ᡣ
 * 
 * ���磬����Ҫģ��ƹ����Ч��������ִ��һ�������ٷ���ִ��һ��ͬ���Ķ���
 * 
 * ����:
 * 
 * @code
 * Action *pingPongAction = Sequence::actions(action, action->reverse(), nullptr);
 * @endcode
 */
class CC_DLL ActionInterval : public FiniteTimeAction
{
public:
    /** @~english How many seconds had elapsed since the actions started to run.
     *
     * @~chinese ��ȡ�Ӷ�����ʼ�����Ѿ���ȥ�˶೤ʱ�䡣
     * 
     * @return @~english The seconds had elapsed since the ations started to run.
     * @~chinese �Ӷ�����ʼ�����Ѿ���ȥ�˶೤ʱ�䡣
     */
    inline float getElapsed(void) { return _elapsed; }

    /** @~english Sets the amplitude rate, extension in GridAction
     *
     * @~chinese �������˥���ʣ�����GridAction����չ
     * 
     * @param amp   @~english The ampliture rate.
     * @~chinese ���˥���ʡ�
     */
    void setAmplitudeRate(float amp);
    
    /** @~english Gets the ampliture rate, extension in GridAction
     *
     * @~chinese ��ȡ���˥���ʣ�����GridAction����չ
     * 
     * @return @~english  The ampliture rate.
     * @~chinese ���˥���ʡ�
     */
    float getAmplitudeRate(void);

    //
    // Overrides
    //
    virtual bool isDone(void) const override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual ActionInterval* reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

    virtual ActionInterval *clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

CC_CONSTRUCTOR_ACCESS:
    /** @~english initializes the action with the duration.
     * @~chinese ʹ�ó���ʱ���ʼ������ 
     * @param d @~english The duration @~chinese ����ʱ��
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithDuration(float d);

protected:
    float _elapsed;
    bool _firstTick;

protected:
    bool sendUpdateEventToScript(float dt, Action *actionObject);
};

/** @class Sequence
 * @brief @~english Runs actions sequentially, one after another.
 * @~chinese ˳������Sequnce������˳���һ������һ�������ڲ��������С�
 */
class CC_DLL Sequence : public ActionInterval
{
public:
    /// @{ Constructor functions
    /// @brief @~english @~chinese ���캯��

    /**
     * @~english Helper constructor to create an array of sequenceable actions.
     *
     * @~chinese ���ڴ���һ�����԰�����ִ�ж�����Sequence���������һϵ�и������캯��
     * 
     * @return @~english An autoreleased Sequence object.
     * @~chinese һ�����ͷŵ�Sequence���������������ʧ���򷵻ؿ�ָ�롣
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported
    typedef FiniteTimeAction* M;
    static Sequence* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Sequence* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Sequence* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Sequence* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use the other create functions or variadicCreate with NULL as the last argument
    static Sequence* variadicCreate(FiniteTimeAction* item, ...);
#else
    static Sequence* create(FiniteTimeAction *action1, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** @~english Helper constructor to create an array of sequenceable actions given an array.
     * @~chinese ʹ��ָ�������������������԰�����ִ�е�Sequence��������
     * @code
     * When this function bound to the js or lua,the input params changed
     * in js  :var   create(var   object1,var   object2, ...)
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     *
     * @param arrayOfActions @~english An array of sequenceable actions.
     * @~chinese �������顣
     * @return @~english An autoreleased Sequence object.
     * @~chinese һ�����ͷ�Sequence�����������ʧ���򷵻ؿ�ָ�롣
     */
    static Sequence* create(const Vector<FiniteTimeAction*>& arrayOfActions);
    /** @~english Helper constructor to create an array of sequence-able actions.
     *
     * @~chinese �ö����б������԰�����ִ�е�Sequence��������
     * 
     * @param action1 @~english The first sequenceable action.
     * @~chinese ���������еĵ�һ��������
     * @param args @~english The variable list variable.
     * @~chinese �����б������
     * @return @~english An autoreleased Sequence object.
     * @~chinese һ�����ͷŵ�Sequence�����������ʧ���򷵻ؿ�ָ�롣
     * @js NA
     */
    static Sequence* createWithVariableList(FiniteTimeAction *action1, va_list args);
    /** @~english Creates the action with two actions.
     * @~chinese ��������������Sequence������
     * @param actionOne @~english The first sequenceable action.
     * @~chinese ��һ��������
     * @param actionTwo @~english The second sequenceable action.
     * @~chinese �ڶ���������
     * @return @~english An autoreleased Sequence object.
     * @~chinese һ�����ͷ�Sequence���������������ʧ���򷵻ؿ�ָ�롣
     * @js NA
     */
    static Sequence* createWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo);

    /// @} Constructor functions

    //
    // Overrides
    //
    virtual Sequence* clone() const override;
    virtual Sequence* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Sequence() {}
    virtual ~Sequence(void);

    /** @~english initializes the action  @~chinese ������������ʼ������ */
    bool initWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);
    bool init(const Vector<FiniteTimeAction*>& arrayOfActions);

protected:
    FiniteTimeAction *_actions[2];
    float _split;
    int _last;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Sequence);
};

/** @class Repeat
 * @brief @~english Repeats an action a number of times.
 * To repeat an action forever use the RepeatForever action.
 * @~chinese �ظ�������Repeat�����԰�һ�������ظ�һ��������
 * ʹ��RepeatForever��������Զ�ظ�һ��������
 */
class CC_DLL Repeat : public ActionInterval
{
public:
    /** @~english Creates a Repeat action. Parameter `times` is an unsigned integer between 1 and pow(2,30).
     *
     * @~chinese ����һ���ظ�������`times`������һ��ȡֵ��1��`pow(2, 30)`֮���������
     * 
     * @param action @~english The action needs to repeat.
     * @~chinese ��Ҫ�ظ���Ŀ�궯����
     * @param times @~english The repeat times.
     * @~chinese �ظ�������
     * @return @~english An autoreleased Repeat object.
     * @~chinese һ�����ͷŵ�Repeat�����������ʧ���򷵻ؿ�ָ�롣
     */
    static Repeat* create(FiniteTimeAction *action, unsigned int times);

    /** @~english Sets the inner action.
     *
     * @~chinese �����ڲ�������
     * 
     * @param action @~english The inner action.
     * @~chinese �ڲ�������
     */
    inline void setInnerAction(FiniteTimeAction *action)
    {
        if (_innerAction != action)
        {
            CC_SAFE_RETAIN(action);
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = action;
        }
    }

    /** @~english Gets the inner action.
     *
     * @~chinese ��ȡ�ڲ�������
     * 
     * @return @~english The inner action.
     * @~chinese �ڲ�������
     */
    inline FiniteTimeAction* getInnerAction()
    {
        return _innerAction;
    }

    //
    // Overrides
    //
    virtual Repeat* clone() const override;
    virtual Repeat* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float dt) override;
    virtual bool isDone(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    Repeat() {}
    virtual ~Repeat();

    /** @~english initializes a Repeat action. Times is an unsigned integer between 1 and pow(2,30)  
     * @~chinese ��ʼ��Repeat������`times`������һ��ȡֵ��1��`pow(2, 30)`֮���������
     * @param pAction @~english The action needs to repeat.
     * @~chinese ��Ҫ�ظ���Ŀ�궯����
     * @param times @~english The repeat times.
     * @~chinese �ظ�������
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithAction(FiniteTimeAction *pAction, unsigned int times);

protected:
    unsigned int _times;
    unsigned int _total;
    float _nextDt;
    bool _actionInstant;
    /** @~english Inner action  @~chinese �ڲ����� */
    FiniteTimeAction *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Repeat);
};

/** @class RepeatForever
 * @brief @~english Repeats an action forever.
 * To repeat the an action for a limited number of times use the Repeat action.
 * @~chinese ��Զ���ظ�һ��������
 * ���޴������ظ�һ��������ʹ��Repeat������
 * @warning @~english This action can't be Sequenceable because it is not an finite time action.
 * @~chinese ���������������������ж�������Ϊ������һ������ʱ�䶯����
 */
class CC_DLL RepeatForever : public ActionInterval
{
public:
    /** @~english Creates the action with an inner action.
     *
     * @~chinese ���ڲ���������һ��RepeatForever������
     * 
     * @param action @~english The action need to repeat forever.
     * @~chinese �ڲ������������������Զ�ظ���
     * @return @~english An autoreleased RepeatForever object.
     * @~chinese һ�����ͷŵ�RepeatForever�������������ʧ���򷵻ؿ�ָ�롣
     */
    static RepeatForever* create(ActionInterval *action);

    /** @~english Sets the inner action.
     *
     * @~chinese �����ڲ�������
     * 
     * @param action @~english The inner action.
     * @~chinese �ڲ�������
     */
    inline void setInnerAction(ActionInterval *action)
    {
        if (_innerAction != action)
        {
            CC_SAFE_RELEASE(_innerAction);
            _innerAction = action;
            CC_SAFE_RETAIN(_innerAction);
        }
    }

    /** @~english Gets the inner action.
     *
     * @~chinese ��ȡ�ڲ�������
     * 
     * @return @~english The inner action.
     * @~chinese �ڲ�������
     */
    inline ActionInterval* getInnerAction()
    {
        return _innerAction;
    }

    //
    // Overrides
    //
    virtual RepeatForever* clone() const override;
    virtual RepeatForever* reverse(void) const override;
    virtual void startWithTarget(Node* target) override;
    virtual void step(float dt) override;
    virtual bool isDone(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    RepeatForever()
    : _innerAction(nullptr)
    {}
    virtual ~RepeatForever();

    /** @~english initializes the action  @~chinese ���ڲ�������ʼ������ */
    bool initWithAction(ActionInterval *action);

protected:
    /** @~english Inner action  @~chinese �ڲ����� */
    ActionInterval *_innerAction;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RepeatForever);
};

/** @class Spawn
 * @brief @~english Spawn a group of actions
 * @~chinese ͬ��������Spawn������ͬ��ִ��һ�鶯��
 */
class CC_DLL Spawn : public ActionInterval
{
public:
    /// @{ Constructor functions
    /// @brief @~english @~chinese ���캯��

    /** @~english Helper constructor to create an array of spawned actions.
     * When this funtion bound to the js or lua, the input params changed.
     * @~chinese ��������һ��ͬ��������Spawn�����ĸ������캯����
     * ����������󶨵�js��lua�У������ᷢ���仯
     *
     * @code
     * in lua :local create(local object1,local object2, ...)
     * @endcode
     *
     * @return @~english An autoreleased Spawn object.
     * @~chinese һ�����ͷ�Spawn�����������ʧ���򷵻ؿ�ָ�롣
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported.
    typedef FiniteTimeAction* M;
    static Spawn* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Spawn* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Spawn* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Spawn* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use the other create functions or createSpawn with NULL as the last argument.
    static Spawn* variadicCreate(FiniteTimeAction* item, ...);
#else
    static Spawn* create(FiniteTimeAction *action1, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** @~english Helper constructor to create an array of spawned actions. 
     *
     * @~chinese ��һ�������б���Spawn������
     * 
     * @param action1   @~english The first inner action.
     * @~chinese ��һ��ͬ�����ڲ�������
     * @param args  @~english The va_list variable.
     * @~chinese �����б����.
     * @return @~english  An autoreleased Spawn object.
     * @~chinese һ�����ͷŵ�Spawn�����������ʧ���򷵻ؿ�ָ�롣
     * @js NA
     */
    static Spawn* createWithVariableList(FiniteTimeAction *action1, va_list args);

    /** @~english Helper constructor to create an array of spawned actions given an array.
     *
     * @~chinese ��һ���������鴴��һ��Spawn������
     * 
     * @param arrayOfActions    @~english An array of spawned actions.
     * @~chinese һ��ͬ���������顣
     * @return @~english  An autoreleased Spawn object.
     * @~chinese һ�����ͷŵ�Spawn�����������ʧ���򷵻ؿ�ָ�롣
     */
    static Spawn* create(const Vector<FiniteTimeAction*>& arrayOfActions);

    /** @~english Creates the Spawn action with two spawned actions.
     *
     * @~chinese ������ͬ����������Spawn������
     * 
     * @param action1   @~english The first spawned action.
     * @~chinese ��һ��ͬ��������
     * @param action2   @~english THe second spawned action.
     * @~chinese �ڶ���ͬ��������
     * @return @~english An autoreleased Spawn object.
     * @~chinese һ�����ͷŵ�Spawn�����������ʧ���򷵻ؿ�ָ�롣
     * @js NA
     */
    static Spawn* createWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);
    /// @}

    //
    // Overrides
    //
    virtual Spawn* clone() const override;
    virtual Spawn* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Spawn() {}
    virtual ~Spawn();

    /** @~english initializes the Spawn action with the 2 actions to spawn  
     * @~chinese ������ͬ��������ʼ��Spawn����
     * @param action1   @~english The first spawned action.
     * @~chinese ��һ��ͬ��������
     * @param action2   @~english THe second spawned action.
     * @~chinese �ڶ���ͬ��������
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithTwoActions(FiniteTimeAction *action1, FiniteTimeAction *action2);
    bool init(const Vector<FiniteTimeAction*>& arrayOfActions);

protected:
    FiniteTimeAction *_one;
    FiniteTimeAction *_two;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Spawn);
};

/** @class RotateTo
 * @brief @~english Rotates a Node object to a certain angle by modifying it's rotation attribute.
 * The direction will be decided by the shortest angle.
 * @~chinese RotateTo����������תһ���ڵ����һ���Ƕȣ�ͨ����֡�޸�����`rotation`���ԡ�
 * ��ת��������̵ĽǶȾ�����
 */ 
class CC_DLL RotateTo : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and separate rotation angles.
     *
     * @~chinese 
     * �ó���ʱ����X,Y���������ת�Ƕ�������RotateTo������
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ��,����Ϊ��λ��
     * @param dstAngleX @~english Destination angle x in degrees.
     * @~chinese X���Ŀ��Ƕȣ��ԽǶ�ֵ�ơ�
     * @param dstAngleY @~english Destination angle y in degrees.
     * @~chinese Y���Ŀ��Ƕȣ��ԽǶ�ֵ��
     * @return @~english An autoreleased RotateTo object.
     * @~chinese һ�����ͷŵ�RotateTo�����������ʧ���򷵻ؿ�ָ�롣
     */
    static RotateTo* create(float duration, float dstAngleX, float dstAngleY);

    /** @~english
     * Creates the action with duration and destination angle.
     *
     * @~chinese 
     * �ó���ʱ���Ŀ��Ƕȴ���RotateTo������
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param dstAngle @~english Destination angle in degrees.
     * @~chinese Ŀ��Ƕȣ��ԽǶ�ֵ�ơ�
     * @return @~english An autoreleased RotateTo object.
     * @~chinese һ�����ͷŵ�RotateTo�����������ʧ���򷵻ؿ�ָ�롣
     */
    static RotateTo* create(float duration, float dstAngle);

    /** @~english
     * Creates the action with 3D rotation angles.
     * @~chinese 
     * ����һ����ת����ά��ת�Ƕȵ�RotateTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param dstAngle3D @~english A Vec3 angle.
     * @~chinese ��ά��ת�Ƕȡ�
     * @return @~english An autoreleased RotateTo object.
     * @~chinese һ�����ͷŵ�RotateTo�����������ʧ���򷵻ؿ�ָ�롣
     */
    static RotateTo* create(float duration, const Vec3& dstAngle3D);

    //
    // Overrides
    //
    virtual RotateTo* clone() const override;
    virtual RotateTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    RotateTo();
    virtual ~RotateTo() {}

    /** @~english
     * initializes the action
     * @~chinese 
     * ��ʼ������
     * @param duration @~english Duration in seconds
     * @~chinese ����ʱ�䣬����Ϊ��λ
     * @param dstAngleX @~english Destination angle x in degrees.
     * @~chinese X���Ŀ��Ƕȣ��ԽǶ�ֵ�ơ�
     * @param dstAngleY @~english Destination angle y in degrees.
     * @~chinese Y���Ŀ��Ƕȣ��ԽǶ�ֵ�ơ�
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithDuration(float duration, float dstAngleX, float dstAngleY);
    /**@~english
     * initializes the action
     * @~chinese 
     * ��ʼ������
     * @param duration @~english Duration in seconds
     * @~chinese ����ʱ�䣬����Ϊ��λ
     * @param dstAngle3D @~english A Vec3 angle.
     * @~chinese ��ά��ת�Ƕȡ�
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithDuration(float duration, const Vec3& dstAngle3D);

    /** @~english
     * Calculates the start and diff angles
     * @~chinese 
     * ���㿪ʼ����ת�ǶȲ�ֵ��
     * @param startAngle @~english Start angle in degrees
     * @~chinese ��ʼ�Ƕȣ��ԽǶ�ֵ�ƣ����ڱ��������
     * @param diffAngle @~english Angle difference between start angle and destination angle in degrees
     * @~chinese ��ʼ�ǶȺ�Ŀ��Ƕ�֮��Ĳ�ֵ���ԽǶ�ֵ�ƣ����ڱ��������
     * @param dstAngle @~english Destination angle in degrees
     * @~chinese Ŀ��Ƕȣ��ԽǶ�ֵ��
     */
    void calculateAngles(float &startAngle, float &diffAngle, float dstAngle);
    
protected:
    bool _is3D;
    Vec3 _dstAngle;
    Vec3 _startAngle;
    Vec3 _diffAngle;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RotateTo);
};

/** @class RotateBy
 * @brief @~english Rotates a Node object clockwise a number of degrees by modifying it's rotation attribute.
 * @~chinese RotateBy��������˳ʱ����תһ���ڵ����ͨ���޸�������ת���ԡ�
*/
class CC_DLL RotateBy : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and delta angle to rotate.
     *
     * @~chinese 
     * �ó���ʱ�����ת�Ƕȴ���RotateBy������
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaAngle @~english Delta angle in degrees.
     * @~chinese ��ת�Ƕȡ�
     * @return @~english An autoreleased RotateBy object.
     * @~chinese һ�����ͷŵ�RotateBy�����������ʧ���򷵻ؿ�ָ�롣
     */
    static RotateBy* create(float duration, float deltaAngle);
    /**@~english
     * Creates the action with separate rotation angles.
     *
     * @~chinese 
     * ��X��Y���������ת�Ƕȴ���RotateBy������
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaAngleZ_X @~english Delta angle x in degrees.
     * @~chinese X����ת�Ƕȣ��ԽǶ�ֵ�ơ�
     * @param deltaAngleZ_Y @~english Delta angle y n degreesCW.
     * @~chinese Y����ת�Ƕȣ��ԽǶ�ֵ�ơ�
     * @return @~english An autoreleased RotateBy object.
     * @~chinese һ�����ͷŵ�RotateBy�����������ʧ���򷵻ؿ�ָ�롣
     * @warning @~english The physics body contained in Node doesn't support rotate with different x and y angle.
     * @~chinese ��������������Ľڵ㲻֧����x��y��������ת�Ƕȡ�
     */
    static RotateBy* create(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    /** @~english Creates the action with 3D rotation angles.
     *
     * @~chinese �ó���ʱ�����ά��ת�Ƕȴ���RotateBy������
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaAngle3D @~english A Vec3 angle.
     * @~chinese ��ά��ת�Ƕȡ�
     * @return @~english An autoreleased RotateBy object.
     * @~chinese һ�����ͷŵ�RotateBy�����������ʧ���򷵻ؿ�ָ�롣
     */
    static RotateBy* create(float duration, const Vec3& deltaAngle3D);

    //
    // Override
    //
    virtual RotateBy* clone() const override;
    virtual RotateBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    RotateBy();
    virtual ~RotateBy() {}

    /** @~english initializes the action  @~chinese �ó���ʱ�����ת�Ƕȳ�ʼ������ 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaAngle @~english Delta angle in degrees.
     * @~chinese ��ת�Ƕȡ�
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithDuration(float duration, float deltaAngle);
    /** 
     * @warning @~english The physics body contained in Node doesn't support rotate with different x and y angle.
     * @~chinese ��������������Ľڵ㲻֧����x��y��������ת�Ƕȡ�
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaAngleZ_X @~english Delta angle x in degrees.
     * @~chinese X����ת�Ƕȣ��ԽǶ�ֵ�ơ�
     * @param deltaAngleZ_Y @~english Delta angle y n degreesCW.
     * @~chinese Y����ת�Ƕȣ��ԽǶ�ֵ�ơ�
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithDuration(float duration, float deltaAngleZ_X, float deltaAngleZ_Y);
    /**
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaAngle3D @~english A Vec3 angle.
     * @~chinese ��ά��ת�Ƕȡ�
     * @return @~english Return true if initialized successfully, otherwise return false.
     * @~chinese �����ʼ���ɹ��򷵻�true�����򷵻�false
     */
    bool initWithDuration(float duration, const Vec3& deltaAngle3D);
    
protected:
    bool _is3D;
    Vec3 _deltaAngle;
    Vec3 _startAngle;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RotateBy);
};

/** @class MoveBy
 * @brief @~english Moves a Node object by x,y pixels by modifying it's position attribute.
 x and y are relative to the position of the object.
 Several MoveBy actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 * @~chinese MoveBy����ͨ���޸�һ��Ŀ��ڵ��λ�����Խ����ƶ�x��y���ء�
 * X���Y��λ��������ڽڵ�λ�õģ�
 * ����MoveBy�������Բ��У��ɴ˲�����λ�ƽ������и���λ�Ƶ��ܺ͡�
 @since v2.1beta2-custom
 */
class CC_DLL MoveBy : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and delta position.
     *
     * @~chinese 
     * �ó���ʱ���λ�ƴ���MoveBy������
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaPosition @~english The delta distance in 2d, it's a Vec2 type.
     * @~chinese λ�ƣ�Vec2���͡�
     * @return @~english An autoreleased MoveBy object.
     * @~chinese һ�����ͷŵ�MoveBy����
     */
    static MoveBy* create(float duration, const Vec2& deltaPosition);
    /**@~english
     * Creates the action with duration and 3d delta position.
     *
     * @~chinese 
     * �ó���ʱ�����άλ�ƴ���MoveBy������
     * 
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaPosition @~english The delta distance in 3d, it's a Vec3 type.
     * @~chinese ��άλ�ƣ�Vec3���͡�
     * @return @~english An autoreleased MoveBy object.
     * @~chinese һ�����ͷŵ�MoveBy����
     */
    static MoveBy* create(float duration, const Vec3& deltaPosition);

    //
    // Overrides
    //
    virtual MoveBy* clone() const override;
    virtual MoveBy* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    MoveBy():_is3D(false) {}
    virtual ~MoveBy() {}

    bool initWithDuration(float duration, const Vec2& deltaPosition);
    bool initWithDuration(float duration, const Vec3& deltaPosition);

protected:
    bool _is3D;
    Vec3 _positionDelta;
    Vec3 _startPosition;
    Vec3 _previousPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MoveBy);
};

/** @class MoveTo
 * @brief @~english Moves a Node object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
 Several MoveTo actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 * @~chinese MoveTo����ͨ���޸�һ��Ŀ��ڵ��λ�����Խ����ƶ����ض�λ�á�
 * ����MoveTo�������Բ��У��ɴ˲������˶��������и����˶����ܺ͡�
 @since v2.1beta2-custom
 */
class CC_DLL MoveTo : public MoveBy
{
public:
    /** @~english
     * Creates the action with duration and 2d position.
     * @~chinese 
     * �ó���ʱ��Ͷ�ά����Ŀ��λ�ô���MoveTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param position @~english The destination position in 2d.
     * @~chinese ��ά�����Ŀ��λ�á�
     * @return @~english An autoreleased MoveTo object.
     * @~chinese һ�����ͷŵ�MoveTo����
     */
    static MoveTo* create(float duration, const Vec2& position);
    /**@~english
     * Creates the action with duration and 3d position.
     * @~chinese 
     * �ó���ʱ�����ά����Ŀ��λ�ô���MoveTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param position @~english The destination position in 3d.
     * @~chinese ��ά����Ŀ��λ�á�
     * @return @~english An autoreleased MoveTo object.
     * @~chinese һ�����ͷ�MoveTo����
     */
    static MoveTo* create(float duration, const Vec3& position);

    //
    // Overrides
    //
    virtual MoveTo* clone() const override;
    virtual MoveTo* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    MoveTo() {}
    virtual ~MoveTo() {}

    bool initWithDuration(float duration, const Vec2& position);
    bool initWithDuration(float duration, const Vec3& position);

protected:
    Vec3 _endPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MoveTo);
};

/** @class SkewTo
 * @brief @~english Skews a Node object to given angles by modifying it's skewX and skewY attributes
 * @~chinese SkewTo����ͨ���޸�skewX��skewY������бһ���ڵ�����ض�����б�Ƕ�
@since v1.0
*/
class CC_DLL SkewTo : public ActionInterval
{
public:
    /** @~english
     * Creates the SkewTo action with the duration, x and y axis target skew parameters.
     * @~chinese 
     * �ó���ʱ�䣬X��Y��Ŀ����б��������SkewTo������
     * @param t @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param sx @~english Skew x angle.
     * @~chinese X��Ŀ����б�Ƕȡ�
     * @param sy @~english Skew y angle.
     * @~chinese Y��Ŀ����б�Ƕȡ�
     * @return @~english An autoreleased SkewTo object.
     * @~chinese һ�����ͷŵ�SkewTo����
     */
    static SkewTo* create(float t, float sx, float sy);

    //
    // Overrides
    //
    virtual SkewTo* clone() const override;
    virtual SkewTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    SkewTo();
    virtual ~SkewTo() {}
    bool initWithDuration(float t, float sx, float sy);

protected:
    float _skewX;
    float _skewY;
    float _startSkewX;
    float _startSkewY;
    float _endSkewX;
    float _endSkewY;
    float _deltaX;
    float _deltaY;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SkewTo);
};

/** @class SkewBy
* @brief @~english Skews a Node object by skewX and skewY degrees.
 * @~chinese SkewBy����������һ���Ƕ���бһ���ڵ㡣
@since v1.0
*/
class CC_DLL SkewBy : public SkewTo
{
public:
    /** @~english
     * Creates the SkewBy action with the duration, x and y axis delta skew parameters.
     * @~chinese 
     * �ó���ʱ�䣬X��Y����б�Ǵ���������
     * @param t @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaSkewX @~english Skew x delta angle.
     * @~chinese X����б�ǡ�
     * @param deltaSkewY @~english Skew y delta angle.
     * @~chinese Y����б�ǡ�
     * @return @~english An autoreleased SkewBy object.
     * @~chinese һ�����ͷŵ�SkewBy����
     */
    static SkewBy* create(float t, float deltaSkewX, float deltaSkewY);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual SkewBy* clone() const  override;
    virtual SkewBy* reverse(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    SkewBy() {}
    virtual ~SkewBy() {}
    bool initWithDuration(float t, float sx, float sy);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(SkewBy);
};

/** @class JumpBy
 * @brief @~english Moves a Node object simulating a parabolic jump movement by modifying it's position attribute.
 * @~chinese JumpBy��������ģ�����������˶��ƶ�һ���ڵ����
*/
class CC_DLL JumpBy : public ActionInterval
{
public:
    /** @~english
     * Creates the JumpBy action with duration, jumping distance, jumping height and number of jumps.
     * @~chinese 
     * �ó���ʱ�䣬��Ծ���룬��Ծ�߶Ⱥʹ�������JumpBy������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param position @~english The jumping distance.
     * @~chinese ��Ծ�ľ��롣
     * @param height @~english The jumping height.
     * @~chinese ��Ծ�ĸ߶ȡ�
     * @param jumps @~english The jumping times.
     * @~chinese ��Ծ������
     * @return @~english An autoreleased JumpBy object.
     * @~chinese һ�����ͷŵ�JumpBy����
     */
    static JumpBy* create(float duration, const Vec2& position, float height, int jumps);

    //
    // Overrides
    //
    virtual JumpBy* clone() const override;
    virtual JumpBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    JumpBy() {}
    virtual ~JumpBy() {}

    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);

protected:
    Vec2           _startPosition;
    Vec2           _delta;
    float           _height;
    int             _jumps;
    Vec2           _previousPos;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpBy);
};

/** @class JumpTo
 * @brief @~english Moves a Node object to a parabolic position simulating a jump movement by modifying it's position attribute.
 * @~chinese JumpTo��������ģ�����������˶��ƶ�һ���ڵ�����ض���λ�á�
*/ 
class CC_DLL JumpTo : public JumpBy
{
public:
    /** @~english
     * Creates the JumpTo action with duration, destination position, jumping height and number of jumps.
     * @~chinese 
     * �ó���ʱ�䣬Ŀ�ĵ�λ�ã���Ծ�߶Ⱥʹ�������JumpTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param position @~english The jumping destination position.
     * @~chinese ��Ծ��Ŀ�ĵص�λ�á�
     * @param height @~english The jumping height.
     * @~chinese ��Ծ�ĸ߶ȡ�
     * @param jumps @~english The jumping times.
     * @~chinese ��Ծ�Ĵ�����
     * @return @~english An autoreleased JumpTo object.
     * @~chinese һ�����ͷŵ�JumpTo����
     */
    static JumpTo* create(float duration, const Vec2& position, float height, int jumps);

    //
    // Override
    //
    virtual void startWithTarget(Node *target) override;
    virtual JumpTo* clone() const override;
    virtual JumpTo* reverse(void) const override;

CC_CONSTRUCTOR_ACCESS:
    JumpTo() {}
    virtual ~JumpTo() {}

    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);

protected:
    Vec2 _endPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpTo);
};

/** @struct ccBezierConfig @~english Bezier configuration structure
 * @~chinese Bezier�������ýṹ��
 */
typedef struct _ccBezierConfig {
    //! end position of the bezier
    Vec2 endPosition;
    //! Bezier control point 1
    Vec2 controlPoint_1;
    //! Bezier control point 2
    Vec2 controlPoint_2;
} ccBezierConfig;

/** @class BezierBy
 * @brief @~english An action that moves the target with a cubic Bezier curve by a certain distance.
 * @~chinese BezierBy�������Խ�һ���ڵ������α����������ƶ�һ�����롣
 */
class CC_DLL BezierBy : public ActionInterval
{
public:
    /** @~english Creates the action with a duration and a bezier configuration.
     * @~chinese �ó���ʱ��ͱ������������ô���BezierBy������
     * @param t @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param c @~english Bezier config.
     * @~chinese �������������á�
     * @return @~english An autoreleased BezierBy object.
     * @~chinese һ�����ͷŵ�BezierBy����
     * @code
     * When this function bound to js or lua,the input params are changed.
     * in js: var create(var t,var table)
     * in lua: local create(local t, local table)
     * @endcode
     */
    static BezierBy* create(float t, const ccBezierConfig& c);

    //
    // Overrides
    //
    virtual BezierBy* clone() const override;
    virtual BezierBy* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    BezierBy() {}
    virtual ~BezierBy() {}

    /** @~english
     * initializes the action with a duration and a bezier configuration
     * @~chinese 
     * �ó���ʱ��ͱ������������ó�ʼ��BezierBy������
     * @param t @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param c @~english Bezier config.
     * @~chinese �������������á�
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese �����ʼ���ɹ�����true�����򷵻�false��
     */
    bool initWithDuration(float t, const ccBezierConfig& c);

protected:
    ccBezierConfig _config;
    Vec2 _startPosition;
    Vec2 _previousPosition;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BezierBy);
};

/** @class BezierTo
 * @brief @~english An action that moves the target with a cubic Bezier curve to a destination point.
 * @~chinese BezierTo�������Խ�һ���ڵ������α����������ƶ����ض�λ�á�
 @since v0.8.2
 */
class CC_DLL BezierTo : public BezierBy
{
public:
    /** @~english Creates the action with a duration and a bezier configuration.
     * @~chinese �ó���ʱ��ͱ������������ô���BezierTo������
     * @param t @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param c @~english Bezier config.
     * @~chinese �������������á�
     * @return @~english An autoreleased BezierTo object.
     * @~chinese һ�����ͷŵ�BezierTo����
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var t,var table)
     * in lua: local create(local t, local table)
     * @endcode
     */
    static BezierTo* create(float t, const ccBezierConfig& c);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual BezierTo* clone() const override;
    virtual BezierTo* reverse(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    BezierTo() {}
    virtual ~BezierTo() {}
    
    /** @~english
     * initializes the action with a duration and a bezier configuration
     * @~chinese 
     * �ó���ʱ��ͱ������������ó�ʼ��BezierTo������
     * @param t @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param c @~english Bezier config.
     * @~chinese �������������á�
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese �����ʼ���ɹ�����true�����򷵻�false��
     */
    bool initWithDuration(float t, const ccBezierConfig &c);

protected:
    ccBezierConfig _toConfig;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(BezierTo);
};

/** @class ScaleTo
 @brief @~english Scales a Node object to a zoom factor by modifying it's scale attribute.
 * @~chinese ScaleTo����ͨ���޸�scale������һ���ڵ��������ŵ��ض���С��
 @warning @~english This action doesn't support "reverse".
 * @~chinese ���������֧�֡���ת����reverse����
 @warning @~english The physics body contained in Node doesn't support this action.
 * @~chinese ��������������Ľڵ㲻֧����һ������
 */
class CC_DLL ScaleTo : public ActionInterval
{
public:
    /** @~english
     * Creates the action with the same scale factor for X and Y.
     * @~chinese 
     * �ó���ʱ���X��Y����ͬ�����ű�������ScaleTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param s @~english Scale factor of x and y.
     * @~chinese X��Y������ű�����
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese һ�����ͷŵ�ScaleTo����
     */
    static ScaleTo* create(float duration, float s);

    /** @~english
     * Creates the action with and X factor and a Y factor.
     * @~chinese 
     * �ó���ʱ���X��Y��ֱ�����ű�������ScaleTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param sx @~english Scale factor of x.
     * @~chinese X�����ű�����
     * @param sy @~english Scale factor of y.
     * @~chinese Y������ű�����
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese һ�����ͷŵ�ScaleTo����
     */
    static ScaleTo* create(float duration, float sx, float sy);

    /** @~english
     * Creates the action with X Y Z factor.
     * @~chinese 
     * �ó���ʱ���X��Y��Z��ֱ�����ű�������ScaleTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ��,����Ϊ��λ��
     * @param sx @~english Scale factor of x.
     * @~chinese X�����ű�����
     * @param sy @~english Scale factor of y.
     * @~chinese Y�����ű�����
     * @param sz @~english Scale factor of z.
     * @~chinese Z�����ű�����
     * @return @~english An autoreleased ScaleTo object.
     * @~chinese һ�����ͷŵ�ScaleTo����
     */
    static ScaleTo* create(float duration, float sx, float sy, float sz);

    //
    // Overrides
    //
    virtual ScaleTo* clone() const override;
    virtual ScaleTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ScaleTo() {}
    virtual ~ScaleTo() {}

    /** @~english
     * Initialize the action with the same scale factor for X and Y.
     * @~chinese 
     * �ó���ʱ���X��Y����ͬ�����ű�����ʼ��ScaleTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param s @~english Scale factor of x and y.
     * @~chinese X��Y������ű�����
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese �����ʼ���ɹ�����true�����򷵻�false��
     */
    bool initWithDuration(float duration, float s);
    /** @~english
     * Initialize the action with and X factor and a Y factor.
     * @~chinese 
     * �ó���ʱ���X��Y��ֱ�����ű�����ʼ��ScaleTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param sx @~english Scale factor of x.
     * @~chinese X�����ű�����
     * @param sy @~english Scale factor of y.
     * @~chinese Y������ű�����
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese �����ʼ���ɹ�����true�����򷵻�false��
     */
    bool initWithDuration(float duration, float sx, float sy);
    /** @~english
     * Initializes the action with X Y Z factor 
     * @~chinese 
     * �ó���ʱ���X��Y��Z��ֱ�����ű�����ʼ��ScaleTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ��,����Ϊ��λ��
     * @param sx @~english Scale factor of x.
     * @~chinese X�����ű�����
     * @param sy @~english Scale factor of y.
     * @~chinese Y�����ű�����
     * @param sz @~english Scale factor of z.
     * @~chinese Z�����ű�����
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese �����ʼ���ɹ�����true�����򷵻�false��
     */
    bool initWithDuration(float duration, float sx, float sy, float sz);

protected:
    float _scaleX;
    float _scaleY;
    float _scaleZ;
    float _startScaleX;
    float _startScaleY;
    float _startScaleZ;
    float _endScaleX;
    float _endScaleY;
    float _endScaleZ;
    float _deltaX;
    float _deltaY;
    float _deltaZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ScaleTo);
};

/** @class ScaleBy
 * @brief @~english Scales a Node object a zoom factor by modifying it's scale attribute.
 * @~chinese ScaleTo����ͨ���޸�scale������һ���ڵ��������ŵ��ض�����������ڵ�ǰ��С��
 @warning @~english The physics body contained in Node doesn't support this action.
 * @~chinese ��������������Ľڵ㲻֧����һ������
*/
class CC_DLL ScaleBy : public ScaleTo
{
public:
    /** @~english
     * Creates the action with the same scale factor for X and Y.
     * @~chinese 
     * �ó���ʱ���X��Y����ͬ�����ű�������ScaleBy������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param s @~english Scale factor of x and y.
     * @~chinese X��Y������ű�����
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese һ�����ͷŵ�ScaleBy����
     */
    static ScaleBy* create(float duration, float s);

    /** @~english
     * Creates the action with and X factor and a Y factor.
     * @~chinese 
     * �ó���ʱ���X��Y��ֱ�����ű�������ScaleBy������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param sx @~english Scale factor of x.
     * @~chinese X�����ű�����
     * @param sy @~english Scale factor of y.
     * @~chinese Y������ű�����
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese һ�����ͷŵ�ScaleBy����
     */
    static ScaleBy* create(float duration, float sx, float sy);

    /** @~english
     * Creates the action with X Y Z factor.
     * @~chinese 
     * �ó���ʱ���X��Y��Z��ֱ�����ű�������ScaleBy������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ��,����Ϊ��λ��
     * @param sx @~english Scale factor of x.
     * @~chinese X�����ű�����
     * @param sy @~english Scale factor of y.
     * @~chinese Y�����ű�����
     * @param sz @~english Scale factor of z.
     * @~chinese Z�����ű�����
     * @return @~english An autoreleased ScaleBy object.
     * @~chinese һ�����ͷŵ�ScaleBy����
     */
    static ScaleBy* create(float duration, float sx, float sy, float sz);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual ScaleBy* clone() const override;
    virtual ScaleBy* reverse(void) const override;

CC_CONSTRUCTOR_ACCESS:
    ScaleBy() {}
    virtual ~ScaleBy() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ScaleBy);
};

/** @class Blink
 * @brief @~english Blinks a Node object by modifying it's visible attribute.
 * @~chinese Blink����ͨ���޸Ľڵ��visible�����ýڵ�����в������ֵ�Ч����
*/
class CC_DLL Blink : public ActionInterval
{
public:
    /** @~english
     * Creates the action with duration and number of blinks.
     * @~chinese 
     * �ó���ʱ������ִ�������Blink������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ��,����Ϊ��λ��
     * @param blinks @~english Blink times.
     * @~chinese ���ִ�����
     * @return @~english An autoreleased Blink object.
     * @~chinese һ�����ͷŵ�Blink������
     */
    static Blink* create(float duration, int blinks);

    //
    // Overrides
    //
    virtual Blink* clone() const override;
    virtual Blink* reverse() const override;
    virtual void update(float time) override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop() override;
    
CC_CONSTRUCTOR_ACCESS:
    Blink() {}
    virtual ~Blink() {}

    /** @~english
     * initializes the action with duration and number of blinks.
     * @~chinese 
     * �ó���ʱ������ִ�����ʼ��Blink������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ��,����Ϊ��λ��
     * @param blinks @~english Blink times.
     * @~chinese ���ִ�����
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese �����ʼ���ɹ�����true�����򷵻�false��
     */
    bool initWithDuration(float duration, int blinks);
    
protected:
    int _times;
    bool _originalState;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Blink);
};


/** @class FadeTo
 * @brief @~english Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 * @~chinese FadeTo�����䣩���Խ�һ��ʵ����RGBAProtocolЭ��Ķ���ӵ�ǰ͸���Ƚ��䵽ָ��͸���ȡ�
 @warning @~english This action doesn't support "reverse"
 * @~chinese ���������֧�֡���ת����reverse��
 */
class CC_DLL FadeTo : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and opacity.
     * @~chinese 
     * ʹ�ó���ʱ���Ŀ��͸���ȴ���FadeTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param opacity @~english A certain opacity, the range is from 0 to 255.
     * @~chinese Ŀ��͸���ȣ���Χ��0��255��
     * @return @~english An autoreleased FadeTo object.
     * @~chinese һ�����ͷŵ�FadeTo����
     */
    static FadeTo* create(float duration, GLubyte opacity);

    //
    // Overrides
    //
    virtual FadeTo* clone() const override;
    virtual FadeTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FadeTo() {}
    virtual ~FadeTo() {}

    /** @~english
     * initializes the action with duration and opacity 
     * @~chinese 
     * ʹ�ó���ʱ���Ŀ��͸���ȳ�ʼ��FadeTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param opacity @~english A certain opacity, the range is from 0 to 255.
     * @~chinese Ŀ��͸���ȣ���Χ��0��255��
     * @return @~english Return true if successfully initialized, otherwise return false
     * @~chinese �����ʼ���ɹ�����true�����򷵻�false��
     */
    bool initWithDuration(float duration, GLubyte opacity);

protected:
    GLubyte _toOpacity;
    GLubyte _fromOpacity;
    friend class FadeOut;
    friend class FadeIn;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeTo);
};

/** @class FadeIn
 * @brief @~english Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
 * @~chinese FadeIn�����룩����������һ��ʵ��RGBAProtocolЭ��Ķ����룬��ʹ�ڵ�ĵ�ǰ͸���Ƚ��䵽255��
 * ��һ�����ġ�������FadeOut������������
 */
class CC_DLL FadeIn : public FadeTo
{
public:
    /** @~english
     * Creates the action with duration.
     * @~chinese 
     * �ó���ʱ�䴴��FadeIn������
     * @param d @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @return @~english An autoreleased FadeIn object.
     * @~chinese һ�����ͷ�FadeIn����
     */
    static FadeIn* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeIn* clone() const override;
    virtual FadeTo* reverse(void) const override;

    /**
     * @~english Set the reverse action.
     * @~chinese ������ת������
     * @param ac @~english The reverse action @~chinese ��ת����
     * @js NA
     */
    void setReverseAction(FadeTo* ac);

CC_CONSTRUCTOR_ACCESS:
    FadeIn():_reverseAction(nullptr) {}
    virtual ~FadeIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeIn);
    FadeTo* _reverseAction;
};

/** @class FadeOut
 * @brief @~english Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
 * @~chinese FadeOut������������������һ��ʵ��RGBAProtocolЭ��Ķ��󵭳�����ʹ�ڵ�ĵ�ǰ͸���Ƚ��䵽0��
 * ��һ�����ġ�������FadeIn�����룩����
*/
class CC_DLL FadeOut : public FadeTo
{
public:
    /** @~english
     * Creates the action with duration.
     * @~chinese 
     * �ó���ʱ�䴴��FadeOut������
     * @param d @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @return @~english An autoreleased FadeOut object.
     * @~chinese һ�����ͷ�FadeOut����
     */
    static FadeOut* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeOut* clone() const  override;
    virtual FadeTo* reverse(void) const override;

    /**
     * @~english Set the reverse action.
     * @~chinese ������ת������
     * @param ac @~english The reverse action @~chinese ��ת����
     * @js NA
     */
    void setReverseAction(FadeTo* ac);

CC_CONSTRUCTOR_ACCESS:
    FadeOut():_reverseAction(nullptr) {}
    virtual ~FadeOut() {}
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOut);
    FadeTo* _reverseAction;
};

/** @class TintTo
 * @brief @~english Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 * @~chinese TintTo����������һ��ʵ��NodeRGBЭ��Ķ����ɫ���ض���ɫ��
 @warning @~english This action doesn't support "reverse"
 * @~chinese ���������֧�֡���ת����reverse��
 @since v0.7.2
*/
class CC_DLL TintTo : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and color.
     * @~chinese 
     * �ó���ʱ���Ŀ����ɫ����TintTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param red @~english Red Color, from 0 to 255.
     * @~chinese ��ɫ�ĺ�ɫͨ��ֵ����0��255��
     * @param green @~english Green Color, from 0 to 255.
     * @~chinese ��ɫ����ɫͨ��ֵ����0��255��
     * @param blue @~english Blue Color, from 0 to 255.
     * @~chinese ��ɫ����ɫͨ��ֵ����0��255��
     * @return @~english An autoreleased TintTo object.
     * @~chinese һ�����ͷŵ�TintTo����
     */
    static TintTo* create(float duration, GLubyte red, GLubyte green, GLubyte blue);
    /**@~english
     * Creates an action with duration and color.
     * @~chinese 
     * �ó���ʱ���Ŀ����ɫ����TintTo������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param color @~english It's a Color3B type color.
     * @~chinese һ��Color3B������ɫ��
     * @return @~english An autoreleased TintTo object.
     * @~chinese һ�����ͷŵ�TintTo����
     */
    static TintTo* create(float duration, const Color3B& color);

    //
    // Overrides
    //
    virtual TintTo* clone() const override;
    virtual TintTo* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TintTo() {}
    virtual ~TintTo() {}

    bool initWithDuration(float duration, GLubyte red, GLubyte green, GLubyte blue);

protected:
    Color3B _to;
    Color3B _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TintTo);
};

/** @class TintBy
 @brief @~english Tints a Node that implements the NodeRGB protocol from current tint to a custom one.
 * @~chinese TintBy����������һ��ʵ��NodeRGBЭ��Ķ���һ����ֵ�ı�����ɫ��
 @since v0.7.2
 */
class CC_DLL TintBy : public ActionInterval
{
public:
    /** @~english
     * Creates an action with duration and color.
     * @~chinese 
     * �ó���ʱ���Ŀ����ɫ����TintBy������
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param deltaRed @~english Delta red color.
     * @~chinese ��ɫ��ֵ�ĺ�ɫͨ��ֵ����0��255��
     * @param deltaGreen @~english Delta green color.
     * @~chinese ��ɫ��ֵ����ɫͨ��ֵ����0��255��
     * @param deltaBlue @~english Delta blue color.
     * @~chinese ��ɫ��ֵ����ɫͨ��ֵ����0��255��
     * @return @~english An autoreleased TintBy object.
     * @~chinese һ�����ͷŵ�TintBy����
     */
    static TintBy* create(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

    //
    // Overrides
    //
    virtual TintBy* clone() const override;
    virtual TintBy* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    TintBy() {}
    virtual ~TintBy() {}

    bool initWithDuration(float duration, GLshort deltaRed, GLshort deltaGreen, GLshort deltaBlue);

protected:
    GLshort _deltaR;
    GLshort _deltaG;
    GLshort _deltaB;

    GLshort _fromR;
    GLshort _fromG;
    GLshort _fromB;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TintBy);
};

/** @class DelayTime
 * @brief @~english Delays the action a certain amount of seconds.
 * @~chinese DelayTime���ӳٶ�����������Sequence�еĶ���ִ���ӳ�һ��ʱ�䡣
*/
class CC_DLL DelayTime : public ActionInterval
{
public:
    /** @~english
     * Creates the action with delayed duration.
     * @~chinese 
     * ���ӳ�ʱ�䴴��DelayTime������
     * @param d @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @return @~english An autoreleased DelayTime object.
     * @~chinese һ�����ͷŵ�DelayTime����
     */
    static DelayTime* create(float d);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual DelayTime* reverse() const override;
    virtual DelayTime* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    DelayTime() {}
    virtual ~DelayTime() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DelayTime);
};

/** @class ReverseTime
 * @brief @~english Executes an action in reverse order, from time=duration to time=0
 
 * @~chinese ReverseTime����������ת��ʱ����ִ��һ��Ŀ�궯������ת���ʱ�����time=duration��time=0
 * 
 @warning @~english Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
 * @~chinese ҪС��ʹ��������������ֶ��������Ա�������Sequence�����С�
 * ���԰�����ΪĬ�ϵġ���ת���ķ��������ڡ���ת����Χ��ʹ���ǲ��Ƽ��ġ�
 */
class CC_DLL ReverseTime : public ActionInterval
{
public:
    /** @~english Creates the action with the inner action.
     *
     * @~chinese ʹ���ڲ���������ReverseTime������
     * 
     * @param action @~english a certain action.
     * @~chinese �ڲ�������
     * @return @~english An autoreleased ReverseTime object.
     * @~chinese һ�����ͷŵ�ReverseTime����
     */
    static ReverseTime* create(FiniteTimeAction *action);

    //
    // Overrides
    //
    virtual ReverseTime* reverse() const override;
    virtual ReverseTime* clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ReverseTime();
    virtual ~ReverseTime(void);

    bool initWithAction(FiniteTimeAction *action);

protected:
    FiniteTimeAction *_other;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ReverseTime);
};

class Texture2D;
/** @class Animate
 * @brief @~english Animates a sprite given the Animation.
 * @~chinese Animate��������ʹ��Animation�����������󲥷�һ�����鶯����
 */
class CC_DLL Animate : public ActionInterval
{
public:
    /** @~english Creates the action with an Animation and will restore the original frame when the animation is over.
     *
     * @~chinese ʹ��Animation�����������󴴽�һ��Animate����Ŀ�꾫��ĳ�ʼ֡���ڶ��������󱻻ָ���
     * 
     * @param animation @~english A certain animation.
     * @~chinese Animation������������
     * @return @~english An autoreleased Animate object.
     * @~chinese һ�����ͷ�Animate����
     */
    static Animate* create(Animation *animation);

    /** @~english Sets the Animation object to be animated 
     * 
     * @~chinese ���ö�������
     * 
     * @param animation @~english certain animation.
     * @~chinese Animation������������
     */
    void setAnimation( Animation* animation );
    /** @~english returns the Animation object that is being animated 
     *
     * @~chinese ��ȡ��������
     * 
     * @return @~english Gets the animation object that is being animated.
     * @~chinese ��������
     */
    Animation* getAnimation() { return _animation; }
    const Animation* getAnimation() const { return _animation; }

    /**
     * Gets the index of sprite frame currently displayed.
     * @return int  the index of sprite frame currently displayed.
     */
    int getCurrentFrameIndex() { return _currFrameIndex; }
    //
    // Overrides
    //
    virtual Animate* clone() const override;
    virtual Animate* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float t) override;
    
CC_CONSTRUCTOR_ACCESS:
    Animate();
    virtual ~Animate();

    bool initWithAnimation(Animation *animation);

protected:
    std::vector<float>* _splitTimes;
    int             _nextFrame;
    SpriteFrame*    _origFrame;
    int _currFrameIndex;
    unsigned int    _executedLoops;
    Animation*      _animation;

    EventCustom*    _frameDisplayedEvent;
    AnimationFrame::DisplayedEventInfo _frameDisplayedEventInfo;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Animate);
};

/** @class TargetedAction
 * @brief @~english Overrides the target of an action so that it always runs on the target
 * specified at action creation rather than the one specified by runAction.
 * @~chinese TargetedAction�������ڲ�����ǿ����Ŀ��ڵ���ִ�У������ǵ���`runAction`����ʱָ���Ľڵ㡣
 */
class CC_DLL TargetedAction : public ActionInterval
{
public:
    /** @~english Create an action with the specified action and forced target.
     * 
     * @~chinese ʹ�ù̶�Ŀ����ڲ���������TargetedAction������
     * 
     * @param target @~english The target.
     * @~chinese �ö����Ĺ̶�Ŀ��ڵ�.
     * @param action @~english The action.
     * @~chinese �ڲ�������
     * @return @~english An autoreleased TargetedAction object.
     * @~chinese һ�����ͷŵ�TargetedAction����
     */
    static TargetedAction* create(Node* target, FiniteTimeAction* action);

    /** @~english Sets the target that the action will be forced to run with.
     *
     * @~chinese ���ù̶�Ŀ��ڵ㣬�ڲ�������ǿ�������Ŀ��ڵ���ִ�С�
     * 
     * @param forcedTarget @~english The target that the action will be forced to run with.
     * @~chinese �̶�Ŀ��ڵ㡣
     */
    void setForcedTarget(Node* forcedTarget);
    /** @~english returns the target that the action is forced to run with. 
     *
     * @~chinese ��ȡ�̶�Ŀ��ڵ㣬�ڲ�������ǿ�������Ŀ��ڵ���ִ�С�
     * 
     * @return @~english The target that the action is forced to run with.
     * @~chinese �̶�Ŀ��ڵ㡣
     */
    Node* getForcedTarget() { return _forcedTarget; }
    const Node* getForcedTarget() const { return _forcedTarget; }

    //
    // Overrides
    //
    virtual TargetedAction* clone() const override;
    virtual TargetedAction* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void stop(void) override;
    virtual void update(float time) override;
    //
    // Overrides
    //
    virtual bool isDone(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    TargetedAction();
    virtual ~TargetedAction();

    bool initWithTarget(Node* target, FiniteTimeAction* action);

protected:
    FiniteTimeAction* _action;
    Node* _forcedTarget;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TargetedAction);
};

/**
 * @class ActionFloat
 * @brief @~english Action used to animate any value in range [from,to] over specified time interval
 * @~chinese ActionFloat���Խ��κ�ֵ��һ��ʱ�����ڴ�ָ������ʼֵ�ı�Ϊָ��������ֵ
 */
class CC_DLL ActionFloat : public ActionInterval
{
public:
    /**@~english
     *  Callback function used to report back result
     * @~chinese 
     * ���ڱ������Ļص�����
     */
    typedef std::function<void(float value)> ActionFloatCallback;

    /**@~english
     * Creates FloatAction with specified duration, from value, to value and callback to report back results
     * @~chinese 
     * �ó���ʱ�䡢��ʼֵ������ֵ�ͻص�����������ActionFloat����
     * @param duration @~english Duration time, in seconds.
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * @param from @~english value to start from
     * @~chinese ��ʼֵ
     * @param to @~english value to be at the end of the action
     * @~chinese ����ֵ
     * @param callback @~english Callback to report back result
     * @~chinese �������Ļص�����
     * @return @~english An autoreleased ActionFloat object
     * @~chinese һ�����ͷŵ�ActionFloat����
     */
    static ActionFloat* create(float duration, float from, float to, ActionFloatCallback callback);

    void startWithTarget(Node* target) override;
    void update(float delta) override;
    ActionFloat* reverse() const override;
    ActionFloat* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    ActionFloat() {};
    virtual ~ActionFloat() {};

    bool initWithDuration(float duration, float from, float to, ActionFloatCallback callback);

protected:
    float _from;
    float _to;
    float _delta;

    ActionFloatCallback _callback;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ActionFloat);
};

// end of actions group
/// @}

NS_CC_END

#endif //__ACTION_CCINTERVAL_ACTION_H__
