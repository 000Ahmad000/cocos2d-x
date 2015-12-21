/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCSCHEDULER_H__
#define __CCSCHEDULER_H__

#include <functional>
#include <mutex>
#include <set>

#include "base/CCRef.h"
#include "base/CCVector.h"
#include "base/uthash.h"

NS_CC_BEGIN

class Scheduler;

typedef std::function<void(float)> ccSchedulerFunc;

/**
 * @cond
 */
class CC_DLL Timer : public Ref
{
protected:
    Timer();
public:
    /** @~english get interval in seconds  @~chinese ��ȡʱ��������λΪ��*/
    inline float getInterval() const { return _interval; };
    /** @~english set interval in seconds  @~chinese ����ʱ��������λΪ��*/
    inline void setInterval(float interval) { _interval = interval; };
    
    void setupTimerWithInterval(float seconds, unsigned int repeat, float delay);
    
    virtual void trigger(float dt) = 0;
    virtual void cancel() = 0;
    
    /** @~english triggers the timer  @~chinese ������ʱ��*/
    void update(float dt);
    
protected:
    
    Scheduler* _scheduler; // weak ref
    float _elapsed;
    bool _runForever;
    bool _useDelay;
    unsigned int _timesExecuted;
    unsigned int _repeat; //0 = once, 1 is 2 x executed
    float _delay;
    float _interval;
};


class CC_DLL TimerTargetSelector : public Timer
{
public:
    TimerTargetSelector();

    /** @~english Initializes a timer with a target, a selector and an interval in seconds, repeat in number of times to repeat, delay in seconds.
     *  @~chinese ʹ��ָ����Ŀ����󣬻ص�������ʱ�������ظ��������ӳ�ʱ���ʼ��һ����ʱ����
     */
    bool initWithSelector(Scheduler* scheduler, SEL_SCHEDULE selector, Ref* target, float seconds, unsigned int repeat, float delay);
    
    inline SEL_SCHEDULE getSelector() const { return _selector; };
    
    virtual void trigger(float dt) override;
    virtual void cancel() override;
    
protected:
    Ref* _target;
    SEL_SCHEDULE _selector;
};


class CC_DLL TimerTargetCallback : public Timer
{
public:
    TimerTargetCallback();
    
    // Initializes a timer with a target, a lambda and an interval in seconds, repeat in number of times to repeat, delay in seconds.
    bool initWithCallback(Scheduler* scheduler, const ccSchedulerFunc& callback, void *target, const std::string& key, float seconds, unsigned int repeat, float delay);
    
    inline const ccSchedulerFunc& getCallback() const { return _callback; };
    inline const std::string& getKey() const { return _key; };
    
    virtual void trigger(float dt) override;
    virtual void cancel() override;
    
protected:
    void* _target;
    ccSchedulerFunc _callback;
    std::string _key;
};

#if CC_ENABLE_SCRIPT_BINDING

class CC_DLL TimerScriptHandler : public Timer
{
public:
    bool initWithScriptHandler(int handler, float seconds);
    inline int getScriptHandler() const { return _scriptHandler; };
    
    virtual void trigger(float dt) override;
    virtual void cancel() override;
    
private:
    int _scriptHandler;
};

#endif

/**
 * @endcond
 */

/**
 * @addtogroup base
 * @{
 */

struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;

#if CC_ENABLE_SCRIPT_BINDING
class SchedulerScriptHandlerEntry;
#endif

/** @brief @~english Scheduler is responsible for triggering the scheduled callbacks.
You should not use system timer for your game logic. Instead, use this class.

There are 2 different types of callbacks (selectors):

- update selector: the 'update' selector will be called every frame. You can customize the priority.
- custom selector: A custom selector will be called every frame, or with a custom interval of time

The 'custom selectors' should be avoided when possible. It is faster, and consumes less memory to use the 'update selector'.

 * @~chinese
 * Scheduler �Ǹ��𴥷��ص��������ࡣ
 * ����������Ϸ������ֱ��ʹ��ϵͳ�Ķ�ʱ�����Ƽ�ʹ���������ʵ�ֶ�ʱ�����ܡ�
 * 
 * �����ֲ�ͬ���͵Ķ�ʱ��:
 * - update ��ʱ����ÿһ֡���ᴥ�����������Զ������ȼ���
 * - �Զ��嶨ʱ�����Զ��嶨ʱ������ÿһ֡�����Զ����ʱ����������
 * 
 * Ӧ�þ�������ʹ���Զ��嶨ʱ����ʹ�� update ��ʱ�����죬�������ĸ��ٵ��ڴ档
 * 
*/
class CC_DLL Scheduler : public Ref
{
public:
    /** @~english Priority level reserved for system services. 
     * @~chinese ϵͳ��������ȼ���
     * @lua NA
     * @js NA
     */
    static const int PRIORITY_SYSTEM;
    
    /** @~english Minimum priority level for user scheduling. 
     * Priority level of user scheduling should bigger then this value.
     *
     * @~chinese �û����ȵ�������ȼ���
     * �û����ȵ����ȼ�Ӧ�ñ����ֵ��
     * 
     * @lua NA
     * @js NA
     */
    static const int PRIORITY_NON_SYSTEM_MIN;
    
    /**@~english
     * Constructor
     *
     * @~chinese 
     * ���캯��
     * 
     * @js ctor
     */
    Scheduler();
    
    /**@~english
     * Destructor
     *
     * @~chinese 
     * ��������
     * 
     * @js NA
     * @lua NA
     */
    virtual ~Scheduler();

    /**@~english
     * Gets the time scale of schedule callbacks.
     * @~chinese 
     * ��ȡʱ���������ű�����
     * @see Scheduler::setTimeScale()
     */
    inline float getTimeScale() { return _timeScale; }
    /** @~english Modifies the time of all scheduled callbacks.
     * You can use this property to create a 'slow motion' or 'fast forward' effect.
     * Default is 1.0. To create a 'slow motion' effect, use values below 1.0.
     * To create a 'fast forward' effect, use values higher than 1.0.
     * @~chinese ����ʱ���������ű�����
     * ������ʹ���������������һ�������������򡰿������Ч����
     * Ĭ����1.0��Ҫ����һ������������Ч��,ʹ��ֵ����1.0��
     * Ҫʹ�á������Ч����ʹ��ֵ���� 1.0��
     * @since v0.8
     * @warning @~english It will affect EVERY scheduled selector / action.
     * @~chinese ����Ӱ�����еĶ�ʱ����
     */
    inline void setTimeScale(float timeScale) { _timeScale = timeScale; }

    /** @~english 'update' the scheduler.
     * You should NEVER call this method, unless you know what you are doing.
     * @~chinese update ��������
     * ��Ӧ��ֱ�ӵ������������������ȫ�˽���ô���Ľ����
     * @lua NA
     */
    void update(float dt);

    /////////////////////////////////////
    
    // schedule
    
    /** @~english The scheduled method will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdate' instead.
     If the 'callback' is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use CC_REPEAT_FOREVER to let the action run continuously
     delay is the amount of time the action will wait before it'll start.
     * @~chinese ��ʱ�����ﵽָ��ֵʱ�����õĻص��������ᱻ���á�
     * ��� paused ֵΪ true����ôֱ�� resume �����òſ�ʼ��ʱ��
     * ��� interval ֵΪ0����ô�ص�����ÿһ֡���ᱻ���á������������������ʹ�� `scheduleUpdate` ���档
     * ����ص������Ѿ�����ʱ��ʹ�ã���ôֻ�����֮ǰ��ʱ����ʱ�������������������µĶ�ʱ����
     * repeat ֵ�����ö�ʱ������ repeat + 1 �Σ�ʹ�� `CC_REPEAT_FOREVER` �����ö�ʱ��һֱѭ��������
     * delay ֵָ���ӳ�ʱ�䡣��ʱ�������ӳ�ָ����ʱ��֮��ʼ��ʱ��
     @param callback @~english The callback function.
     * @~chinese �ص�������
     @param target @~english The target of the callback function.
     * @~chinese �ص������Ķ���
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese ���õ�ʱ�����������ֵΪ0,��ÿһ֡���ᴥ���ص�������
     @param repeat @~english repeat+1 times to schedule the callback.
     * @~chinese �ص����������� repeat + 1 �Ρ�
     @param delay @~english Schedule call back after `delay` seconds. If the value is not 0, the first schedule will happen after `delay` seconds.
            But it will only affect first schedule. After first schedule, the delay time is determined by `interval`.
     * @~chinese ��һ�δ����ص����ӳ�ʱ�䡣�����ֵ����0����һ�λص������Ĵ���ʱ�佫���Ƴ�ָ����������
     * ��ֻ��Ӱ���һ�ζ�ʱ���Ĵ�����֮��ÿ�ζ�ʱ���Ĵ���ʱ������ interval ֵ������
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese �Ƿ�Ҫ��ͣ��
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese �����������ص������Ĺؼ��֣���Ϊû�а취���� std::function<> �Ƿ���ͬ��
     @since v3.0
     */
    void schedule(const ccSchedulerFunc& callback, void *target, float interval, unsigned int repeat, float delay, bool paused, const std::string& key);

    /** @~english The scheduled method will be called every 'interval' seconds for ever.
     * @~chinese �����ʱ���ᰴ��ָ����ʱ�������ϵĴ�����
     @param callback @~english The callback function.
     * @~chinese �ص�������
     @param target @~english The target of the callback function.
     * @~chinese �ص������Ķ���
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese ���õ�ʱ�����������ֵΪ0,��ÿһ֡���ᴥ���ص�������
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese �Ƿ�Ҫ��ͣ��
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese �����������ص������Ĺؼ��֣���Ϊû�а취���� std::function<> �Ƿ���ͬ��
     @since v3.0
     */
    void schedule(const ccSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key);
    
    
    /** @~english The scheduled method will be called every `interval` seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdate' instead.
     If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use CC_REPEAT_FOREVER to let the action run continuously
     delay is the amount of time the action will wait before it'll start
     
     * @~chinese ��ʱ�����ﵽָ��ֵʱ�����õĻص��������ᱻ���á�
     * ��� paused ֵΪ true����ôֱ�� resume �����òſ�ʼ��ʱ��
     * ��� interval ֵΪ0����ô�ص�����ÿһ֡���ᱻ���á������������������ʹ�� `scheduleUpdate` ���档
     * ����ص������Ѿ�����ʱ��ʹ�ã���ôֻ�����֮ǰ��ʱ����ʱ�������������������µĶ�ʱ����
     * repeat ֵ�����ö�ʱ������ repeat + 1 �Σ�ʹ�� `CC_REPEAT_FOREVER` �����ö�ʱ��һֱѭ��������
     * delay ֵָ���ӳ�ʱ�䡣��ʱ�������ӳ�ָ����ʱ��֮��ʼ��ʱ��
     @param selector @~english The callback function.
     * @~chinese �ص�������
     @param target @~english The target of the callback function.
     * @~chinese �ص������Ķ���
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese ���õ�ʱ�����������ֵΪ0,��ÿһ֡���ᴥ���ص�������
     @param repeat @~english repeat+1 times to schedule the callback.
     * @~chinese �ص����������� repeat + 1 �Ρ�
     @param delay @~english Schedule call back after `delay` seconds. If the value is not 0, the first schedule will happen after `delay` seconds.
     But it will only affect first schedule. After first schedule, the delay time is determined by `interval`.
     * @~chinese ��һ�δ����ص����ӳ�ʱ�䡣�����ֵ����0����һ�λص������Ĵ���ʱ�佫���Ƴ�ָ����������
     * ��ֻ��Ӱ���һ�ζ�ʱ���Ĵ�����֮��ÿ�ζ�ʱ���Ĵ���ʱ������ interval ֵ������
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese �Ƿ�Ҫ��ͣ��
     @since v3.0
     */
    void schedule(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused);
    
    /** @~english The scheduled method will be called every `interval` seconds for ever.
     * @~chinese �����ʱ���ᰴ��ָ����ʱ�������ϵĴ�����
     @param selector @~english The callback function.
     * @~chinese �ص�������
     @param target @~english The target of the callback function.
     * @~chinese �ص������Ķ���
     @param interval @~english The interval to schedule the callback. If the value is 0, then the callback will be scheduled every frame.
     * @~chinese ���õ�ʱ�����������ֵΪ0,��ÿһ֡���ᴥ���ص�������
     @param paused @~english Whether or not to pause the schedule.
     * @~chinese �Ƿ�Ҫ��ͣ��
     */
    void schedule(SEL_SCHEDULE selector, Ref *target, float interval, bool paused);
    
    /** @~english Schedules the 'update' selector for a given target with a given priority.
     The 'update' selector will be called every frame.
     The lower the priority, the earlier it is called.
     * @~chinese ʹ��ָ�������ȼ�Ϊָ���Ķ������� update ��ʱ����
     * update ��ʱ��ÿһ֡���ᱻ������
     * ���ȼ���ֵԽ�ͣ���ʱ����������Խ�硣
     @since v3.0
     @lua NA
     */
    template <class T>
    void scheduleUpdate(T *target, int priority, bool paused)
    {
        this->schedulePerFrame([target](float dt){
            target->update(dt);
        }, target, priority, paused);
    }

#if CC_ENABLE_SCRIPT_BINDING
    // Schedule for script bindings.
    /** @~english The scheduled script callback will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame.
     return schedule script entry ID, used for unscheduleScriptFunc().
     
     * @~chinese Ϊ�ű��㶨�ƵĶ�ʱ�����ص�������ָ����ʱ������������
     * ��� paused ֵΪ true����ôֱ����ʱ�� resume �ŻῪʼ��ʱ��
     * ��� interval ֵΪ0����ÿһ֡���ᴥ���ص�������
     * ����һ�� ID������ unscheduleScriptFunc()��
     * 
     @warning @~english Don't invoke this function unless you know what you are doing.
     * @~chinese ��Ҫֱ�ӵ������������������֪��������ʲô��
     @js NA
     @lua NA
     */
    unsigned int scheduleScriptFunc(unsigned int handler, float interval, bool paused);
#endif
    /////////////////////////////////////
    
    // unschedule

    /** @~english Unschedules a callback for a key and a given target.
     If you want to unschedule the 'callbackPerFrame', use unscheduleUpdate.
     * @~chinese ����ָ���� key �� target ȡ����Ӧ�Ķ�ʱ����
     * �����Ҫȡ�� `callbackPerFrame` ��ʱ������ʹ�� `unscheduleUpdate`��
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese ʶ��ص������Ĺؼ��֣���Ϊû�а취���� std::function<> �Ƿ���ͬ��
     @param target @~english The target to be unscheduled.
     * @~chinese ��Ҫȡ����ʱ���Ķ���
     @since v3.0
     */
    void unschedule(const std::string& key, void *target);

    /** @~english Unschedules a selector for a given target.
     If you want to unschedule the "update", use `unscheudleUpdate()`.
     * @~chinese ����ָ���Ļص������� target ����ȡ����Ӧ�Ķ�ʱ����
     * �����Ҫȡ�� `update` ��ʱ������ʹ�� `unscheudleUpdate()`��
     @param selector @~english The selector that is unscheduled.
     * @~chinese ��Ҫȡ���Ļص�������
     @param target @~english The target of the unscheduled selector.
     * @~chinese ��Ҫȡ����ʱ���Ķ���
     @since v3.0
     */
    void unschedule(SEL_SCHEDULE selector, Ref *target);
    
    /** @~english Unschedules the update selector for a given target
     * @~chinese ȡ�� update ��ʱ����
     @param target @~english The target to be unscheduled.
     * @~chinese ��Ҫȡ����ʱ���Ķ���
     @since v0.99.3
     */
    void unscheduleUpdate(void *target);
    
    /** @~english Unschedules all selectors for a given target.
     This also includes the "update" selector.
     * @~chinese ȡ��ָ����������ж�ʱ����
     * ���� update ��ʱ��
     @param target @~english The target to be unscheduled.
     * @~chinese ��Ҫȡ����ʱ���Ķ���
     @since v0.99.3
     @lua NA
     */
    void unscheduleAllForTarget(void *target);
    
    /** @~english Unschedules all selectors from all targets.
     You should NEVER call this method, unless you know what you are doing.
     * @~chinese ȡ�����ж�������ж�ʱ����
     * ���õ��ô˺�����������ָ��������ʲô��
     @since v0.99.3
     */
    void unscheduleAll();
    
    /** @~english Unschedules all selectors from all targets with a minimum priority.
     You should only call this with `PRIORITY_NON_SYSTEM_MIN` or higher.
     * @~chinese ȡ���������ȼ���ֵ���� minPriority �Ķ�ʱ����
     * ��Ӧ��ֻȡ�����ȼ���ֵ���� `PRIORITY_NON_SYSTEM_MIN` �Ķ�ʱ����
     @param minPriority @~english The minimum priority of selector to be unscheduled. Which means, all selectors which
            priority is higher than minPriority will be unscheduled.
     * @~chinese ָ�������ȼ����ֵ������ζ�ţ��������ȼ���ֵ���� minPriority �Ķ�ʱ�����ᱻȡ����
     @since v2.0.0
     */
    void unscheduleAllWithMinPriority(int minPriority);
    
#if CC_ENABLE_SCRIPT_BINDING
    /** @~english Unschedule a script entry. 
     * @~chinese ȡ���ű����ָ����ʱ����
     * @warning @~english Don't invoke this function unless you know what you are doing.
     * @~chinese ��Ҫ�����������,������֪��������ʲô��
     * @js NA
     * @lua NA
     */
    void unscheduleScriptEntry(unsigned int scheduleScriptEntryID);
#endif
    
    /////////////////////////////////////
    
    // isScheduled
    
    /** @~english Checks whether a callback associated with 'key' and 'target' is scheduled.
     * @~chinese ���ָ���Ĺؼ���������Ƿ������˶�ʱ����
     @param key @~english The key to identify the callback function, because there is not way to identify a std::function<>.
     * @~chinese ʶ��ص������Ĺؼ��֣���Ϊû�а취���� std::function<> �Ƿ���ͬ��
     @param target @~english The target of the callback.
     * @~chinese �ص������Ķ���
     @return @~english True if the specified callback is invoked, false if not.
     * @~chinese ��������˶�ʱ�������� true�����򷵻� false��
     @since v3.0.0
     */
    bool isScheduled(const std::string& key, void *target);
    
    /** @~english Checks whether a selector for a given taget is scheduled.
     * @~chinese ���ָ���Ļص������Ͷ����Ƿ������˶�ʱ����
     @param selector @~english The selector to be checked.
     * @~chinese ��Ҫ���Ļص�������
     @param target @~english The target of the callback.
     * @~chinese �ص������Ķ���
     @return @~english True if the specified selector is invoked, false if not.
     * @~chinese ��������˶�ʱ�������� true�����򷵻� false��
     @since v3.0
     */
    bool isScheduled(SEL_SCHEDULE selector, Ref *target);
    
    /////////////////////////////////////
    
    /** @~english Pauses the target.
     All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.
     If the target is not present, nothing happens.
     * @~chinese ��ָͣ������Ķ�ʱ����
     * ָ����������ж�ʱ�����ᱻ��ͣ��
     * ���ָ���Ķ���û�ж�ʱ����ʲôҲ���ᷢ����
     @param target @~english The target to be paused.
     * @~chinese ��Ҫ��ͣ�Ķ���
     @since v0.99.3
     */
    void pauseTarget(void *target);

    /** @~english Resumes the target.
     The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.
     If the target is not present, nothing happens.
     * @~chinese �ָ�ָ����������ж�ʱ����
     * ָ���Ķ�������ж�ʱ��������������
     * ���ָ���Ķ���û�ж�ʱ����ʲôҲ���ᷢ����
     @param target @~english The target to be resumed.
     * @~chinese ��Ҫ�ָ���ʱ���Ķ���
     @since v0.99.3
     */
    void resumeTarget(void *target);

    /** @~english Returns whether or not the target is paused.
     * @~chinese ����ָ���Ķ���Ķ�ʱ���Ƿ���ͣ�ˡ�
     * @param target @~english The target to be checked.
     * @~chinese ��Ҫ���Ķ���
     * @return @~english True if the target is paused, false if not.
     * @~chinese �������ͣ״̬������ true�����򷵻� false��
     * @since v1.0.0
     * @lua NA
     */
    bool isTargetPaused(void *target);

    /** @~english Pause all selectors from all targets.
      You should NEVER call this method, unless you know what you are doing.
     * @~chinese ��ͣ���ж�������ж�ʱ����
     * ��Ҫ�����������,������֪����������ʲô��
     @since v2.0.0
      */
    std::set<void*> pauseAllTargets();

    /** @~english Pause all selectors from all targets with a minimum priority.
      You should only call this with PRIORITY_NON_SYSTEM_MIN or higher.
     * @~chinese ��ͣ�������ȼ���ֵ���� minPriority �Ķ�ʱ����
     * ��Ӧ��ֻ��ͣ���ȼ���ֵ���� `PRIORITY_NON_SYSTEM_MIN` �Ķ�ʱ����
      @param minPriority @~english The minimum priority of selector to be paused. Which means, all selectors which
            priority is higher than minPriority will be paused.
     * @~chinese ָ�������ȼ����ֵ������ζ�ţ��������ȼ���ֵ���� minPriority �Ķ�ʱ�����ᱻ��ͣ��
      @since v2.0.0
      */
    std::set<void*> pauseAllTargetsWithMinPriority(int minPriority);

    /** @~english Resume selectors on a set of targets.
     This can be useful for undoing a call to pauseAllSelectors.
     * @~chinese �ָ�ָ�������������ж���Ķ�ʱ����
     * ���������������ȡ�� `pauseAllSelectors` ��Ч����
     @param targetsToResume @~english The set of targets to be resumed.
     * @~chinese ��Ҫ�ָ��Ķ������顣
     @since v2.0.0
      */
    void resumeTargets(const std::set<void*>& targetsToResume);

    /** @~english Calls a function on the cocos2d thread. Useful when you need to call a cocos2d function from another thread.
     This function is thread safe.
     * @~chinese �� cocos2d �߳��ϵ���һ��������������Ҫ����һ���̵߳��� cocos2d ����ʱ����ʹ�����������
     * ����������̰߳�ȫ�ġ�
     @param function @~english The function to be run in cocos2d thread.
     * @~chinese cocos2d �߳���Ҫ���еĺ�����
     @since v3.0
     @js NA
     */
    void performFunctionInCocosThread( const std::function<void()> &function);
    
    /////////////////////////////////////
    
    // Deprecated methods:
    
    /** @~english The scheduled method will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdateForTarget:' instead.
     If the selector is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use CC_REPEAT_FOREVER to let the action run continuously
     delay is the amount of time the action will wait before it'll start
     * @~chinese ��ʱ�����ﵽָ��ֵʱ�����õĻص��������ᱻ���á�
     * ��� paused ֵΪ true����ôֱ�� resume �����òſ�ʼ��ʱ��
     * ��� interval ֵΪ0����ô�ص�����ÿһ֡���ᱻ���á������������������ʹ�� `scheduleUpdate` ���档
     * ����ص������Ѿ�����ʱ��ʹ�ã���ôֻ�����֮ǰ��ʱ����ʱ�������������������µĶ�ʱ����
     * repeat ֵ�����ö�ʱ������ repeat + 1 �Σ�ʹ�� `CC_REPEAT_FOREVER` �����ö�ʱ��һֱѭ��������
     * delay ֵָ���ӳ�ʱ�䡣��ʱ�������ӳ�ָ����ʱ��֮��ʼ��ʱ��
     @deprecated Please use `Scheduler::schedule` instead.
     @since v0.99.3, repeat and delay added in v1.1
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused)
    {
        schedule(selector, target, interval, repeat, delay, paused);
    };
    
    /** @~english Calls scheduleSelector with CC_REPEAT_FOREVER and a 0 delay.
     * @~chinese �� repeat ֵΪ `CC_REPEAT_FOREVER` �� delay ֵΪ 0 ���� `scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused)`.
     *  @deprecated Please use `Scheduler::schedule` instead.
     *  @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, bool paused)
    {
        schedule(selector, target, interval, paused);
    };
    
    /** @~english Schedules the 'update' selector for a given target with a given priority.
     The 'update' selector will be called every frame.
     The lower the priority, the earlier it is called.
     * @~chinese Ϊָ���Ķ������� update ��ʱ����update ��ʱ��ÿһ֡���ᱻ���á�
     * ���ȼ���ֵԽ�ͣ�Խ�类���á�
     @deprecated Please use 'Scheduler::scheduleUpdate' instead.
     @since v0.99.3
     */
    template <class T>
    CC_DEPRECATED_ATTRIBUTE void scheduleUpdateForTarget(T* target, int priority, bool paused) { scheduleUpdate(target, priority, paused); };
    
    /** @~english Unschedule a selector for a given target.
     If you want to unschedule the "update", use unscheudleUpdateForTarget.
     * @~chinese ����ָ���Ļص������� target ����ȡ����Ӧ�Ķ�ʱ����
     * �����Ҫȡ�� `update` ��ʱ������ʹ�� `unscheudleUpdate()`��
     @deprecated Please use 'Scheduler::unschedule' instead.
     @since v0.99.3
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void unscheduleSelector(SEL_SCHEDULE selector, Ref *target) { unschedule(selector, target); };
    
    /** @~english Checks whether a selector for a given target is scheduled.
     * @~chinese �ж�ָ���Ķ���ͻص������Ƿ������˶�ʱ����
     @deprecated Please use 'Scheduler::isScheduled' instead.
     @since v0.99.3
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE bool isScheduledForTarget(Ref *target, SEL_SCHEDULE selector) { return isScheduled(selector, target); };
    
    /** @~english Unschedules the update selector for a given target
     * @~chinese ȡ��ָ����������ж�ʱ����
     @deprecated Please use 'Scheduler::unscheduleUpdate' instead.
     @since v0.99.3
     */
    CC_DEPRECATED_ATTRIBUTE void unscheduleUpdateForTarget(Ref *target) { return unscheduleUpdate(target); };
    
protected:
    void schedulePerFrame(const ccSchedulerFunc& callback, void *target, int priority, bool paused);
    
    void removeHashElement(struct _hashSelectorEntry *element);
    void removeUpdateFromHash(struct _listEntry *entry);

    // update specific

    void priorityIn(struct _listEntry **list, const ccSchedulerFunc& callback, void *target, int priority, bool paused);
    void appendIn(struct _listEntry **list, const ccSchedulerFunc& callback, void *target, bool paused);


    float _timeScale;

    //
    // "updates with priority" stuff
    //
    struct _listEntry *_updatesNegList;        // list of priority < 0
    struct _listEntry *_updates0List;            // list priority == 0
    struct _listEntry *_updatesPosList;        // list priority > 0
    struct _hashUpdateEntry *_hashForUpdates; // hash used to fetch quickly the list entries for pause,delete,etc

    // Used for "selectors with interval"
    struct _hashSelectorEntry *_hashForTimers;
    struct _hashSelectorEntry *_currentTarget;
    bool _currentTargetSalvaged;
    // If true unschedule will not remove anything from a hash. Elements will only be marked for deletion.
    bool _updateHashLocked;
    
#if CC_ENABLE_SCRIPT_BINDING
    Vector<SchedulerScriptHandlerEntry*> _scriptHandlerEntries;
#endif
    
    // Used for "perform Function"
    std::vector<std::function<void()>> _functionsToPerform;
    std::mutex _performMutex;
};

// end of base group
/// @}

NS_CC_END

#endif // __CCSCHEDULER_H__
