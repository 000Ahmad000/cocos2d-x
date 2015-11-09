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

#ifndef __SCRIPT_SUPPORT_H__
#define __SCRIPT_SUPPORT_H__

#include "base/ccConfig.h"
#include "platform/CCCommon.h"
#include "base/CCTouch.h"
#include "base/CCEventTouch.h"
#include "base/CCEventKeyboard.h"
#include <map>
#include <string>
#include <list>

/**
 * @addtogroup base
 * @{
 */

#if CC_ENABLE_SCRIPT_BINDING

typedef struct lua_State lua_State;

NS_CC_BEGIN

class TimerScriptHandler;
class Layer;
class MenuItem;
class CallFunc;
class Acceleration;
class Action;

enum ccScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};

/**@~english
 * This classes is wrapped to store the handler corresponding to the Lua function pointer and assign the handler a unique id
 * @~chinese 
 * ��������ڷ�װLua����ָ���Ӧ��handler��ÿһ��handler��Ӧһ��Ψһid.
 * @lua NA
 * @js NA
 */
class ScriptHandlerEntry : public Ref
{
public:
    
    /**@~english
     * create a ScriptHandlerEntry instance by the handler.
     *
     * @~chinese 
     * ������handler����һ��ScriptHandlerEntryʵ����
     * 
     * @param handler @~english corresponding to the Lua function pointer.
     * @~chinese Lua����������id��
     * @return @~english ScriptHandlerEntry instance.
     * @~chinese ScriptHandlerEntryʵ����
     * @js NA
     */
    static ScriptHandlerEntry* create(int handler);
    
    /**@~english
     * Destructor of ScriptHandlerEntry.
     * @~chinese 
     * ScriptHandlerEntry������������
     * @js NA
     */
    virtual ~ScriptHandlerEntry();
    
    /**@~english
     * Get the handler corresponding to the Lua function pointer.
     *
     * @~chinese 
     * ��ȡ��ӦLua������handler��
     * 
     * @return @~english the handler corresponding to the Lua function pointer.
     * @~chinese ��ӦLua������handler��
     * @js NA
     */
    int getHandler(void) {
        return _handler;
    }
    
    /**@~english
     * Get the unique id corresponding to the handler.
     *
     * @~chinese 
     * ��ȡ��Ӧhandler��ΨһID��
     * 
     * @return @~english the unique id corresponding to the handler.
     * @~chinese handler��Ψһid��
     * @js NA
     */
    int getEntryId(void) {
        return _entryId;
    }
    
protected:
    ScriptHandlerEntry(int handler)
    : _handler(handler)
    {
        static int newEntryId = 0;
        newEntryId++;
        _entryId = newEntryId;
    }
    
    int _handler;
    int _entryId;
};

/**@~english
 * The SchedulerScriptHandlerEntry is used to store the handler corresponding to the Lua function pointer and assign the handler a unique id like ScriptHandlerEntry.
 * Meanwhile,create a timer that named TimerScriptHandler to execute the Lua function corresponding to the handler in the interval time if the SchedulerScriptHandlerEntry object isn't paused.
 * @~chinese 
 * SchedulerScriptHandlerEntry��ScriptHandlerEntry���ƣ�����ӦLua������handler���з�װ���Ҹ����handler����һ��Ψһid.ͬʱ�����ᴴ��һ��TimerScriptHandler���͵Ķ�ʱ�������SchedulerScriptHandlerEntry����û����ͣ�������ᰴһ���ļ��ʱ��ִ��handler��Ӧ��Lua������
 * @lua NA
 * @js NA
 */
class SchedulerScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    /**@~english
     * create a SchedulerScriptHandlerEntry object.
     * 
     * @~chinese 
     * ����һ��SchedulerScriptHandlerEntry����
     * 
     * @param handler @~english the index corresponding to the Lua function pointer.
     * @~chinese ��ӦLua����������id��
     * @param interval @~english the interval to execute the Lua function. If the value is 0, then the lua function will be scheduled every frame.
     * @~chinese ִ��Lua������ʱ���������ֵΪ0����ôLua����ÿ֡��ִ��һ�Ρ�
     * @param paused @~english if paused is true, then the timer won't be started until it is resumed.
     * @~chinese ���pausedֵΪtrue,��ô��ʱ��ֻ�б��ָ�����ܿ�ʼ���С�
     * @return @~english a SchedulerScriptHandlerEntry object.
     * @~chinese SchedulerScriptHandlerEntry����
     */
    static SchedulerScriptHandlerEntry* create(int handler, float interval, bool paused);
    
    /**@~english
     * Destructor of SchedulerScriptHandlerEntry.
     * @~chinese 
     * SchedulerScriptHandlerEntry������������
     */
    virtual ~SchedulerScriptHandlerEntry();
    
    /**@~english
     * Get the pointer of TimerScriptHandler object.
     *
     * @~chinese 
     * ��ȡTimerScriptHandler�����ָ�롣
     * 
     * @return @~english the pointer of TimerScriptHandler object.
     * @~chinese TimerScriptHandler����ָ�롣
     */
    TimerScriptHandler* getTimer(void) {
        return _timer;
    }
    
    /**@~english
     * Get the flag whether paused or not.
     *
     * @~chinese 
     * ��ȡ�Ƿ�paused�ı�ǡ�
     * 
     * @return @~english the flag whether paused or not.
     * @~chinese �Ƿ�paused�ı�ǡ�
     */
    bool isPaused(void) {
        return _paused;
    }
    /**@~english
     * Set the markedForDeletion flag true.
     * @~chinese 
     * ����markedForDeletion���Ϊtrue��
     */
    void markedForDeletion(void) {
        _markedForDeletion = true;
    }
    /**@~english
     * Get the flag whether markedForDeletion or not.
     *
     * @~chinese 
     * ��ȡmarkedForDeletion��ǡ�
     * 
     * @return @~english the flag whether markedForDeletion or not.
     * @~chinese markedForDeletion�ı�ǡ�
     */
    bool isMarkedForDeletion(void) {
        return _markedForDeletion;
    }
    
private:
    SchedulerScriptHandlerEntry(int handler)
    : ScriptHandlerEntry(handler)
    , _timer(nullptr)
    , _paused(false)
    , _markedForDeletion(false)
    {
    }
    bool init(float interval, bool paused);
    
    TimerScriptHandler*   _timer;
    bool                _paused;
    bool                _markedForDeletion;
};


/**
 * @cond
 * @js NA
 */
class TouchScriptHandlerEntry : public ScriptHandlerEntry
{
public:

    static TouchScriptHandlerEntry* create(int handler, bool isMultiTouches, int priority, bool swallowsTouches);

    virtual ~TouchScriptHandlerEntry();

    bool isMultiTouches(void) {
        return _isMultiTouches;
    }

    int getPriority(void) {
        return _priority;
    }

    bool getSwallowsTouches(void) {
        return _swallowsTouches;
    }
    
private:
    TouchScriptHandlerEntry(int handler)
    : ScriptHandlerEntry(handler)
    , _isMultiTouches(false)
    , _priority(0)
    , _swallowsTouches(false)
    {
    }
    bool init(bool isMultiTouches, int priority, bool swallowsTouches);
    
    bool    _isMultiTouches;
    int     _priority;
    bool    _swallowsTouches;
};

/**
 * @endcond
 * @js NA
 */

/** @~english ScriptEventType enum @~chinese ScriptEventTypeö��*/
enum ScriptEventType
{
    kNodeEvent = 0,
    kMenuClickedEvent,
    kCallFuncEvent,
    kScheduleEvent,
    kTouchEvent,
    kTouchesEvent,
    kKeypadEvent,
    kAccelerometerEvent,
    kControlEvent,
    kCommonEvent,
    kComponentEvent,
    kRestartGame,
    kScriptActionEvent
};

/**@~english
 * For Lua, Wrapper the script data that should be used to find the handler corresponding to the Lua function by the nativeobject pointer and store the value pointer which would be converted concretely by the different events,then the converted data would be passed into the Lua stack.
 * @~chinese 
 * ����Lua,����һ���������ݷ�װ�ࡣ����,nativeObject���ڲ��Ҷ���Lua������handler��value��ֵ���ݲ�ͬ���¼�����ת���ɾ������͵����ݣ�����ת��������ݽ���ѹ�뵽Lua��ջ����ΪLua�����еĴ��������
 * @js NA
 * @lua NA
 */
struct BasicScriptData
{
    /** @~english
     * For Lua, nativeobject is used to get handler corresponding to the Lua function.
     *
     * @~chinese 
     * ����Lua, nativeobject���ڻ�ȡ����Lua������handler��
     * 
     */
    void* nativeObject;
    
    /**@~english
     * A pointer point to the value data which would be converted by different events.
     *
     * @~chinese 
     * һ����Ҫ���ݲ�ͬ�¼����о���ת��������ָ�롣
     */
    void* value;
    
    /**@~english
     * Constructor of BasicScriptData.
     *
     * @~chinese 
     * BasicScriptData�Ĺ��캯����
     */
    BasicScriptData(void* inObject,void* inValue = nullptr)
    : nativeObject(inObject),value(inValue)
    {
    }
};

/**@~english
 * For Lua, Wrapper the script data that should be used to find the handler corresponding to the Lua function by the nativeobject pointer and store the value pointer which would be converted concretely by the different events,then the converted data would be passed into the Lua stack.
 * @js NA
 */
struct ActionObjectScriptData
{
    /**
     * For Lua, nativeobject is used to get handler corresponding to the Lua function.
     *
     * @js NA
     * @lua NA
     */
    void* nativeObject;
    
    /**
     * A pointer point to the value data which event action
     *
     * @js NA
     * @lua NA
     */
    int* eventType;
    
    /**
     * A pointer point to the value data which would be converted by different events.
     *
     * @js NA
     * @lua NA
     */
    void* param;
    
    /**
     * Constructor of BasicScriptData.
     *
     * @js NA
     * @lua NA
     */
    ActionObjectScriptData(void* inObject,int* inValue = nullptr, void* inParam = nullptr)
    : nativeObject(inObject),eventType(inValue), param(inParam)
    {
    }
};

/**
 * For Lua, the SchedulerScriptData is used to find the Lua function pointer by the handler, then call the Lua function by push the elapse into the Lua stack as a parameter when scheduler update event is triggered.
 * @~chinese 
 * @~chinese ����Lua, SchedulerScriptDataҲ��һ�����ݷ�װ�ࡣ����ʱ��update�¼�������ʱ����ͨ��handler�ҵ���Ӧ��Lua������Ȼ��elpaseѹ��Lua��ջ��ΪLua�����Ĳ�����
 * @js NA
 * @lua NA
 */
struct SchedulerScriptData
{
    /** @~english
     * the handler corresponding to the Lua function pointer, only use in the Lua.
     *
     * @~chinese 
     * ��ӦLua����������id,ֻ����Lua��
     */
    int handler;
    /** @~english
     * the parameter would be passed in to the Lua function, only use in the Lua.
     *
     * @~chinese 
     * ����Lua�����Ĳ�����ֻ����Lua
     */
    float elapse;
    // js use
    void* node;
    
    /**@~english
     * constructor of SchedulerScriptData.
     *
     * @~chinese 
     * SchedulerScriptData�Ĺ��캯����
     */
    SchedulerScriptData(int inHandler,float inElapse,void* inNode = nullptr)
    : handler(inHandler),
      elapse(inElapse),
      node(inNode)
    {
    }
};

/**@~english
 * For Lua, the TouchesScriptData is used to find the Lua function pointer by the nativeObject, then call the Lua function by push touches data and actionType into the Lua stack as the parameters when the touches event is triggered.
 * @~chinese 
 * ����Lua, TouchesScriptData��װ��touches������ݡ���touches�¼�������������ͨ��nativeObject���Ҷ���Lua������handler,Ȼ��touches���ݺ�actionTypeѹ��Lua��ջ��ΪLua������������Lua������
 * @js NA
 * @lua NA
 */
struct TouchesScriptData
{
    /** @~english
     * The EventTouch::EventCode type. 
     *
     * @~chinese 
     * EventTouch::EventCode���͵�ֵ��
     */
    EventTouch::EventCode actionType;
    /** @~english
     * For Lua, it Used to find the Lua function pointer by the ScriptHandlerMgr.
     *
     * @~chinese 
     * ����Lua��nativeObject���ڲ��Ҷ�Lua������handler��
     */
    void* nativeObject;
    /** @~english
     * The vector of Touch.For Lua, it would be convert to the Lua table form to be pushed into the Lua stack. 
     *
     * @~chinese 
     * ����Touch��std::vector������Lua, ���vector��ת�ɶ�Ӧ��Lua tableѹ���Ӧ��Lua stack��
     */
    const std::vector<Touch*>& touches;
    /** @~english
     * event information, it is useless for Lua.
     *
     * @~chinese 
     * �¼���Ϣ��Lua�����õ����������
     */
    Event* event;
    
    /**@~english
     * Constructor of TouchesScriptData.
     *
     * @~chinese 
     * TouchesScriptData�Ĺ��캯����
     */
    TouchesScriptData(EventTouch::EventCode inActionType, void* inNativeObject, const std::vector<Touch*>& inTouches, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touches(inTouches),
      event(evt)
    {
    }
};

/**@~english
 * For Lua, the TouchScriptData is used to find the Lua function pointer by the nativeObject, then call the Lua function by push touch data and actionType converted to string type into the Lua stack as the parameters when the touch event is triggered.
 * @~chinese 
 * ����Lua, TouchScriptData��װ��touch������ݡ���touch�¼�������������ͨ��nativeObject���Ҷ���Lua������handler,Ȼ��touch���ݺ�actionTypeѹ��Lua��ջ��ΪLua�����Ĳ�������Lua������
 * @js NA
 * @lua NA
 */
struct TouchScriptData
{
    /** @~english
     * The EventTouch::EventCode type.
     *
     * @~chinese 
     * EventTouch::EventCode���͵�ֵ��
     */
    EventTouch::EventCode actionType;
    /** @~english
     * For Lua, it Used to find the Lua function pointer by the ScriptHandlerMgr.
     *
     * @~chinese 
     * ����Lua��nativeObject���ڲ��Ҷ�Lua����ָ���handler��
     */
    void* nativeObject;
    /** @~english
     * touch information. it would be in x,y form to push into the Lua stack.
     *
     * @~chinese 
     * touch��Ϣ��������x,y��ʽѹ��Lua��ջ��
     */
    Touch* touch;
    /**@~english
     * event information,it is useless for Lua.
     *
     * @~chinese 
     * �¼���Ϣ��Lua�����õ����������
     */
    Event* event;
    
    /** @~english
     * Constructor of TouchScriptData.
     *
     * @~chinese 
     * TouchScriptData�Ĺ��캯����
     */
    TouchScriptData(EventTouch::EventCode inActionType, void* inNativeObject, Touch* inTouch, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touch(inTouch),
      event(evt)
    {
    }
};


/**@~english
 * For Lua, the KeypadScriptData is used to find the Lua function pointer by the nativeObject, then call the Lua function by push the actionType converted to string type into the Lua stack as the parameters when the Keypad event is triggered.
 * @~chinese 
 * ����Lua��KeypadScriptData��װ�˹���Keypad��Ϣ��������ݡ���Keypad�¼�������������ͨ��nativeObject���Ҷ�ӦLua������handler,Ȼ��actionTypeת�ɶ�Ӧ���ַ���ѹ��Lua��ջ��ΪLua�����Ĳ�������Lua������
 * @js NA
 * @lua NA
 */
struct KeypadScriptData
{
    /** @~english
     * The specific type of EventKeyboard::KeyCode
     *
     * @~chinese 
     * EventKeyboard::KeyCode���͵�ֵ��
     */
    EventKeyboard::KeyCode actionType;
    /** @~english
     * For Lua, it Used to find the Lua function pointer by the ScriptHandlerMgr.
     *
     * @~chinese 
     * ����Lua��nativeObject���ڲ��Ҷ�Lua����ָ���handler��
     */
    void* nativeObject;
    
    /**@~english
     * Constructor of KeypadScriptData.
     *
     * @~chinese 
     * KeypadScriptData�Ĺ��캯����
     */
    KeypadScriptData(EventKeyboard::KeyCode inActionType,void* inNativeObject)
    : actionType(inActionType),nativeObject(inNativeObject)
    {
    }
};


/**@~english
 * For Lua, the CommonScriptData is used to find the Lua function pointer by the handler, then call the Lua function by push the eventName, eventSource(if it not nullptr), eventSourceClassName(if it is nullptr or "", and the eventSource is not nullptr,would give the default string "cc.Ref") into the Lua stack as the parameter when the common event such as is triggered.
 * @~chinese
 * ����Lua��CommonScriptData��װ��һ�����ݡ���һ���¼�����ʱ������ͨ��handler�ҵ���Ӧ��Lua����ָ�룬Ȼ��eventName��eventSource(�����Ϊ��)��eventSourceClassName(���eventSourceClassName��Ϊnullptr������eventSourceClassNameΪ�ջ���""�������ὫĬ�ϵؽ�"cc.Ref"ѹ�뵽Luaջ��)ѹ��Luaջ����ΪLua�����Ĳ�������Lua������
 * @js NA
 * @lua NA
 */
struct CommonScriptData
{
    /** @~english
     * The index to find the corresponding to the Lua function pointer.
     *
     * @~chinese 
     * ��ӦLua����������id,ֻ����Lua��
     */
    int handler;
    /** @~english
     * The string value to be pushed into the Lua stack.
     *
     * @~chinese 
     * ѹ��Luaջ���¼�����
     */
    char eventName[64];
    /** @~english
     * The source object trigger the event,could be nullptr.
     *
     * @~chinese 
     * �¼�����Դ�����ָ�룬����Ϊnullptr��
     */
    Ref* eventSource;
    /**@~english
     * The class name of source object trigger the event, could be 0.
     *
     * @~chinese 
     * �¼�����Դ���������,����Ϊ�ա�
     */
    char eventSourceClassName[64];
    
    /** @~english
     * Constructor of  CommonScriptData.
     *
     * @~chinese 
     * CommonScriptData�Ĺ��캯����
     */
    CommonScriptData(int inHandler,const char* inName, Ref* inSource = nullptr,const char* inClassName = nullptr)
    : handler(inHandler),
      eventSource(inSource)
    {
        strncpy(eventName, inName, 64);
        
        if (nullptr == inClassName)
        {
            memset(eventSourceClassName, 0, 64*sizeof(char));
        }
        else
        {
            strncpy(eventSourceClassName, inClassName, 64);
        }
    }
};

/**@~english
 * The ScriptEvent wrapper the different script data corresponding to the ScriptEventType in to the unified struct.
 * when the corresponding event is triggered, we could call the `sendEvent` of ScriptEngineProtocol to handle the event.
 * @~chinese 
 * ScriptEvent����ͬ���͵�ScriptEventType��Ӧ�Ľű����ݷ�װ��һ��ͳһ�Ľṹ���档
 * ����Ӧ���¼�������, ������ScriptEngineProtocol��`sendEvent`���������event��
 * @js NA
 * @lua NA
 */
struct ScriptEvent
{
    /** @~english
     * The specific type of ScriptEventType.
     *
     * @~chinese 
     * �ض�ScriptEventType��ֵ��
     */
    ScriptEventType type;
    /** @~english
     * Pointer point to the different data.
     *
     * @~chinese 
     * ָ��ͬ���ݵ�ָ�롣
     */
    void* data;
    
    /**@~english
     * Constructor of ScriptEvent.
     *
     * @~chinese 
     * ScriptEvent�Ĺ��캯����
     */
    ScriptEvent(ScriptEventType inType,void* inData)
    : type(inType),
      data(inData)
    {
    }
};

/** @~english
 * Don't make ScriptEngineProtocol inherits from Ref since setScriptEngine is invoked only once in AppDelegate.cpp,
 * It will affect the lifecycle of ScriptEngine instance, the autorelease pool will be destroyed before destructing ScriptEngine.
 * So a crash will appear on Win32 if you click the close button.
 * @~chinese 
 * ����ScriptEngineProtocol������AppDelegate.cpp��ͨ��setScriptEngine���ú�һֱ���ڣ�����������Ҫ��Ref������
 * ����������Ӱ�쵽�ű�����ʵ���������ڣ���autorelease pool���ڽű����汻����ǰ���á�
 * ��������رհ�ť����win32ƽ̨�ϻ���ֱ�����
 * @js NA
 * @lua NA
 */
class CC_DLL ScriptEngineProtocol
{
public:
    
    /** @~english
     * Constructor of ScriptEngineProtocol.
     *
     * @~chinese 
     * ScriptEngineProtocol�Ĺ��캯����
     */
    ScriptEngineProtocol()
    {};
    
    /**@~english
     * Destructor of ScriptEngineProtocol.
     *
     * @~chinese 
     * ScriptEngineProtocol������������
     */
    virtual ~ScriptEngineProtocol() {};
    
    /** @~english
     * Get the specific script type.
     *
     * @~chinese 
     * ��ȡ�ű���������͡�
     * 
     * @return @~english the specific script type.
     *
     * @~chinese ��ȡ�ű���������͡�
     */
    virtual ccScriptType getScriptType() { return kScriptTypeNone; };

    /** @~english
     * Remove script object,the specific meaning should refer to the ScriptType.
     * For Lua, @see removeScriptObjectByObject of LuaEngine
     * @~chinese 
     * �Ƴ��ű����󣬲�ͬ��ScriptType�в�ͬ�Ĳ�����
     * ����Lua, @see removeScriptObjectByObject of LuaEngine.
     */
    virtual void removeScriptObjectByObject(Ref* obj) = 0;
    
    /** @~english
     * Remove script function handler, only LuaEngine class need to implement this function.
     * @~chinese 
     * �Ƴ�handler������,ֻ��LuaEngine��Ҫʵ�����������
     * @see removeScriptHandler of LuaEngine.
     */
    virtual void removeScriptHandler(int handler) {};
    
    /** @~english
     * Reallocate script function handler, only LuaEngine class need to implement this function.
     * @~chinese 
     * ���·���ű�������handler,ֻ��LuaEngine����Ҫʵ�����������
     * @see reallocateScriptHandler of LuaEngine.
     */
    virtual int reallocateScriptHandler(int handler) { return 0;}
    
    /**@~english
     * Execute script code contained in the given string.
     *
     * @~chinese 
     * ִ�и����ַ����а����Ľű����롣
     * 
     * @param codes @~english holding the valid script code that should be executed.
     * @~chinese ����ִ�еĽű��ַ�����
     * @return @~english 0 if the string is executed correctly,other if the string is executed wrongly.
     * @~chinese ִ����ȷ����0�����򷵻�����ֵ��
     */
    virtual int executeString(const char* codes) = 0;
    
    /**@~english
     * Execute a script file.
     * 
     * @~chinese 
     * ִ��һ���ű��ļ���
     * 
     * @param filename @~english String object holding the filename of the script file that is to be executed.
     * @~chinese �ű��ļ����ļ�����
     * @return @~english 0 if it happen the error or it hasn't return value, otherwise it return the value by calling the lua function.
     * @~chinese �������������ߵ��õ�Lua����û�з���ֵ������0�����򷵻ص���Lua�����ķ���ֵ��
     */
    virtual int executeScriptFile(const char* filename) = 0;
    
    /**@~english
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer for Lua.
     *
     * @~chinese 
     * ִ��ȫ�ֵĽű�������
     * ����Lua,��ȫ�ֺ�����Ӧ���к�������������������һ������ֵ��
     * 
     * @param functionName @~english String object holding the name of the function, in the global script environment, that is to be executed.
     * @~chinese ȫ�ֽű��������ַ������ơ�
     * @return @~english The integer value returned from the script function.
     * @~chinese �ӽű��������ص�����ֵ��
     */
    virtual int executeGlobalFunction(const char* functionName) = 0;
    
    /**@~english
     * When some events triggered in the c++ also needs to pass into script ,call this func.The ScriptEvent contains the data need to passed into the script.
     *
     *
     * @~chinese 
     * ��c++�д�����һЩ�¼���Ҫ���ݵ��ű��㴦��ʱ,��������������������ScriptEvent�а�����Ҫ�����ű��㴦������ݡ�
     */
    virtual int sendEvent(ScriptEvent* evt) = 0;
    
    /** @~english
     * Handle the assert message.
     *
     * @~chinese 
     * ���������Ϣ��
     * 
     * @return @~english return true if current _callFromLua of LuaStack is not equal to 0 otherwise return false for Lua.
     *
     * @~chinese ����true,�����ǰLuaStack��_callFromLua������0,���򷵻ؼ١�
     */
    virtual bool handleAssert(const char *msg) = 0;
    
    /** @~english
     * Set whether the call comes from the script or not, only use for the js.
     *
     * @~chinese 
     * ������������Ƿ����ɽű��㴥���ģ�ֻ����js��
     * @param callFromScript @~english whether the call comes from the script or not.
     * @~chinese �����Ƿ��ýű��㴥����
     */
    virtual void setCalledFromScript(bool callFromScript) { CC_UNUSED_PARAM(callFromScript); };
    
    /** @~english
     * Get the flag that represents whether the call comes from the script or not,only use for the js.
     *
     * @~chinese 
     * ��ȡ�����Ƿ����ɽű��㴥���ı�ǣ�ֻ����js��
     * 
     * @return @~english false.
     * @~chinese false��
     * @lua NA
     * @js NA
     */
    virtual bool isCalledFromScript() { return false; };
    
    /** @~english ConfigType enum.  @~chinese ConfigTypeö���ࡣ*/
    enum class ConfigType
    {
        NONE,
        COCOSTUDIO
    };
    /** @~english
     * Parse configuration file.
     * 
     * @~chinese 
     * ���������ļ���
     * 
     * @param type @~english the specific type value.
     * @~chinese �ض�ConfigType��ֵ��
     * @param str @~english the information data.
     *
     * @~chinese ������Ϣ��
     */
    virtual bool parseConfig(ConfigType type, const std::string& str) = 0;
};

class Node;
/**@~english
 * ScriptEngineManager is a singleton which manager an object instance of ScriptEngineProtocl, such as LuaEngine.
 *
 * @~chinese 
 * ScriptEngineManager��һ����������ScriptEngineProtoclʵ������ĵ���������LuaEngineʵ������
 * 
 * @since v0.99.5-x-0.8.5
 * @js NA
 * @lua NA
 */
class CC_DLL ScriptEngineManager
{
public:
    /** @~english
     * Constructor of ScriptEngineManager.
     *
     * @~chinese 
     * ScriptEngineManager�Ĺ��캯����
     */
    ~ScriptEngineManager(void);
    /** @~english
     * Get the ScriptEngineProtocol object.
     *
     * @~chinese 
     * ��ȡScriptEngineProtocol����ʵ����
     * 
     * @return @~english the ScriptEngineProtocol object.
     *
     * @~chinese ScriptEngineProtocol����ʵ����
     */
    ScriptEngineProtocol* getScriptEngine(void) {
        return _scriptEngine;
    }
    /**@~english
     * Set the ScriptEngineProtocol object should be managed.
     *
     * @~chinese 
     * ������Ҫ�������ScriptEngineProtocol����
     * 
     * @param scriptEngine @~english the ScriptEngineProtocol object should be managered.
     *
     * @~chinese ��Ҫ�������ScriptEngineProtocol����
     */
    void setScriptEngine(ScriptEngineProtocol *scriptEngine);
    
    /**@~english
     * Remove the ScriptEngineProtocol object managed.
     *
     *
     * @~chinese 
     * ɾ���������ScriptEngineProtocol��
     */
    void removeScriptEngine(void);
    /**@~english
     * Get the instance of ScriptEngineManager object.
     *
     * @~chinese 
     * ��ȡScriptEngineManager�����ʵ����
     * 
     * @return @~english the instance of ScriptEngineManager object.
     *
     * @~chinese ScriptEngineManager�����ʵ����
     */
    static ScriptEngineManager* getInstance();
    /**@~english
     * Destroy the singleton of ScriptEngineManager.
     *
     * @~chinese 
     * ����ScriptEngineManager�ĵ�����
     */
    static void destroyInstance();
    /**@~english
     * send the node event to JS
     *
     * @~chinese 
     * ����node�¼���JS��
     * @param node @~english the pointer of node object.
     *
     * @~chinese
     * node����ָ�롣
     *
     * @param action @~english action.
     *
     * @~chinese
     * �¼����͡�
     *
     * @return @~english true if execute successfully,otherwise false.
     *
     * @~chinese ִ�гɹ�����true�����򷵻�false��
     */
    static bool sendActionEventToJS(Action* actionObject, int eventType, void* param);
    /**
     *
     *
     * @lua NA
     * @js NA
     */
    static bool sendNodeEventToJS(Node* node, int action);
    /**@~english
     * send the extended event of Node to JS
     *
     * @~chinese 
     * ������չ��node�¼���JS��
     * @param node @~english the pointer of node object.
     *
     * @~chinese
     * node����ָ�롣
     *
     * @param action @~english action.
     *
     * @~chinese
     * �¼����͡�
     *
     * @return @~english true if execute successfully,otherwise false.
     *
     * @~chinese ִ�гɹ�����true�����򷵻�false��
     */
    static bool sendNodeEventToJSExtended(Node* node, int action);
    /**@~english
     * Call the Lua function when the event of node is triggered.
     * 
     * @~chinese 
     * ��node�¼�����ʱ�ص�Lua������
     * 
     * @param node @~english the nativeobject triggers the event.
     * @~chinese �����¼���node����
     * @param action @~english the specific action type.
     *
     * @~chinese �¼����͡�
     */
    static void sendNodeEventToLua(Node* node, int action);
    /**
     * @deprecated @~english Use getInstance() instead.
     * @~chinese ʹ��getInstance�����
     */
    CC_DEPRECATED_ATTRIBUTE static ScriptEngineManager* sharedManager() { return ScriptEngineManager::getInstance(); };
    /**
     * @deprecated @~english Use destroyInstance() instead.
     * @~chinese ʹ��destroyInstance���
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedManager() { ScriptEngineManager::destroyInstance(); };
    
private:
    ScriptEngineManager(void)
    : _scriptEngine(nullptr)
    {
    }
    
    ScriptEngineProtocol *_scriptEngine;
};

NS_CC_END



#endif // #if CC_ENABLE_SCRIPT_BINDING

// end group
/// @}

#endif // __SCRIPT_SUPPORT_H__
