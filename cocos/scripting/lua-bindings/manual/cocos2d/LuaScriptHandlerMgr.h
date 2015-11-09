/****************************************************************************
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
#ifndef __LUA_SCRIPT_HANDLER_MGR_H__
#define __LUA_SCRIPT_HANDLER_MGR_H__


extern "C" {
#include "tolua++.h"
}


#include "base/CCRef.h"
#include "base/ccMacros.h"
#include "2d/CCActionInstant.h"
#include <vector>
#include <map>

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

class ScheduleHandlerDelegate;

/// @cond
typedef std::vector<ScheduleHandlerDelegate*> VecShedule;
typedef std::map<cocos2d::Node*,VecShedule> MapNodeSchedules;

class ScheduleHandlerDelegate:public cocos2d::Ref
{
public:
    ScheduleHandlerDelegate():_isUpdateSchedule(false)
    {}
    virtual ~ScheduleHandlerDelegate()
    {}
    
    static ScheduleHandlerDelegate* create();
    
    void scheduleFunc(float elapse);
    
    virtual void update(float elapse);
    
    void setUpdateSchedule(bool isUpdateSchedule){ _isUpdateSchedule = isUpdateSchedule; }
    bool isUpdateSchedule(){ return _isUpdateSchedule; }
private:
    bool _isUpdateSchedule;
};
/// @endcond

/**@~english
 * The LuaCallFunc is wrapped to call the callback function in the Lua conveniently and don't insert useless code to processing the Lua in the CallFuncN.
 *
 * @~chinese 
 * LuaCallFunc��Ϊ����Lua���ܷ���ص��ûص����������еķ�װ��ͨ����װ������Ҫ��CallFuncN����һЩ�������������Lua��
 * 
 * @lua NA
 * @js NA
 */
class LuaCallFunc:public cocos2d::CallFuncN
{
public:
    /**@~english
     * Default constructor.
     * @~chinese 
     * Ĭ�Ϲ��캯����
     */
    LuaCallFunc():_functionLua(nullptr)
    {}
    
    /**@~english
     * Destructor.
     * @~chinese 
     * ����������
     */
    virtual ~LuaCallFunc()
    {}
    
    /**@~english
     * Create a LuaCallFunc object by a function pointer for callback.
     *
     * @~chinese 
     * ͨ��һ��ָ��ص������ĺ���ָ�봴��һ��LuaCallFunc����
     * 
     * @param func @~english a function pointer for callback.
     * @~chinese �ص������ĺ���ָ�롣
     */
    static LuaCallFunc* create(const std::function<void(void* self,Node*)>& func);
    
    /**@~english
     * Init a LuaCallFunc object by a function pointer for callback.
     *
     * @~chinese 
     * ʹ��һ���ص������ĺ���ָ������ʼ��LuaCallFunc����
     * 
     * @param func @~english a function pointer for callback.
     * @~chinese �ص������ĺ���ָ�롣
     */
    bool initWithFunction(const std::function<void(void* self,Node*)>& func);
    virtual LuaCallFunc* clone() const override;
    virtual void execute() override;
protected:
    std::function<void(void* self,Node*)> _functionLua;
    
};

/**@~english
 * In order to reduce the coupling of lua script engine and native c++ engine.
 * In the current mechanism, for the class derived frome the Ref, we constuct a mapping relationship among c++ Ref object ,HandlerType and the reference id corresponding to the pointer of Lua function.Then, using the ScriptHandlerMgr to manager uniformly.
 * By this mechanism,when native c++ Ref object wants to call the Lua function, we didn't insert the processing code in the native c++ class.
 * @~chinese 
 * Ϊ�˼���lua�ű������c++�������ϡ�
 * �ڵ�ǰ�Ļ���,����Ref������,���ǻṹ��һ��Ref����HandlerType�Լ�ָ��Lua����ָ�������id��ӳ���ϵ��Ȼ��,ʹ��ScriptHandlerMgr����ͳһ����
 * ͨ�����ֻ���,��c++ Ref���������Lua����ʱ,����������ԭ��c++���в��봦��ű��Ĵ��롣
 */
class ScriptHandlerMgr
{
public:
    
    /**@~english
     * HandlerType enum.
     * This enum class represent the processing event type for c++ calling the Lua function.
     *
     * @~chinese 
     * HandlerTypeö�١�
     * ���ö�����ʾc++�ص�����Lua�������¼����͡�
     * 
     * @js NA
     */
    enum class HandlerType: int
    {
        NODE = 0,
        MENU_CLICKED,
        CALLFUNC,
        SCHEDULE,
        TOUCHES,
        KEYPAD,
        ACCELEROMETER,
        
        CONTROL_TOUCH_DOWN,
        CONTROL_TOUCH_DRAG_INSIDE,
        CONTROL_TOUCH_DRAG_OUTSIDE,
        CONTROL_TOUCH_DRAG_ENTER,
        CONTROL_TOUCH_DRAG_EXIT,
        CONTROL_TOUCH_UP_INSIDE,
        CONTROL_TOUCH_UP_OUTSIDE,
        CONTROL_TOUCH_UP_CANCEL,
        CONTROL_VALUE_CHANGED,
        
        WEBSOCKET_OPEN,
        WEBSOCKET_MESSAGE,
        WEBSOCKET_CLOSE,
        WEBSOCKET_ERROR,
        
        GL_NODE_DRAW,
        
        SCROLLVIEW_SCROLL,
        SCROLLVIEW_ZOOM,
        
        TABLECELL_TOUCHED,
        TABLECELL_HIGHLIGHT,
        TABLECELL_UNHIGHLIGHT,
        TABLECELL_WILL_RECYCLE,
        TABLECELL_SIZE_FOR_INDEX,
        TABLECELL_AT_INDEX,
        TABLEVIEW_NUMS_OF_CELLS,
        
        XMLHTTPREQUEST_READY_STATE_CHANGE,
        
        ASSETSMANAGER_PROGRESS,
        ASSETSMANAGER_SUCCESS,
        ASSETSMANAGER_ERROR,
        
        STUDIO_EVENT_LISTENER,
        ARMATURE_EVENT,
        
        EVENT_ACC,
        EVENT_CUSTIOM,
        
        EVENT_KEYBOARD_PRESSED,
        EVENT_KEYBOARD_RELEASED,
        
        EVENT_TOUCH_BEGAN,
        EVENT_TOUCH_MOVED,
        EVENT_TOUCH_ENDED,
        EVENT_TOUCH_CANCELLED,
        
        EVENT_TOUCHES_BEGAN,
        EVENT_TOUCHES_MOVED,
        EVENT_TOUCHES_ENDED,
        EVENT_TOUCHES_CANCELLED,
        
        EVENT_MOUSE_DOWN,
        EVENT_MOUSE_UP,
        EVENT_MOUSE_MOVE,
        EVENT_MOUSE_SCROLL,
        
        EVENT_SPINE,
        
        EVENT_PHYSICS_CONTACT_BEGIN,
        EVENT_PHYSICS_CONTACT_PRESOLVE,
        EVENT_PHYSICS_CONTACT_POSTSOLVE,
        EVENT_PHYSICS_CONTACT_SEPARATE,
        
        EVENT_FOCUS,
        
        EVENT_CONTROLLER_CONNECTED,
        EVENT_CONTROLLER_DISCONNECTED,
        EVENT_CONTROLLER_KEYDOWN,
        EVENT_CONTROLLER_KEYUP,
        EVENT_CONTROLLER_KEYREPEAT,
        EVENT_CONTROLLER_AXIS,
        
        EVENT_SPINE_ANIMATION_START,
        EVENT_SPINE_ANIMATION_END,
        EVENT_SPINE_ANIMATION_COMPLETE,
        EVENT_SPINE_ANIMATION_EVENT,
        
        EVENT_CUSTOM_BEGAN = 10000,
        EVENT_CUSTOM_ENDED = 11000,
    };
    
    ///! @cond
    typedef int Handler;
    typedef std::pair<HandlerType, Handler> HandlerPair;
    typedef std::vector<HandlerPair> VecHandlerPairs;
    typedef std::map<void*,VecHandlerPairs> MapObjectHandlers;
    /// @endcond
    
    /**@~english
     * Default constructor.
     *
     * @~chinese 
     * Ĭ�Ϲ��캯����
     * 
     * @lua NA
     * @js NA
     */
    ScriptHandlerMgr(void);
    
    /**@~english
     * Destructor.
     *
     * @~chinese 
     * ����������
     * 
     * @lua NA
     * @js NA
     */
    virtual ~ScriptHandlerMgr(void);
    
    /**@~english
     * Get the instance of the ScriptHandlerMgr.
     *
     * @~chinese 
     * ��ȡScriptHandlerMgr��ʵ������
     * 
     * @return @~english the instance of the ScriptHandlerMgr.
     * @~chinese ScriptHandlerMgr��ʵ������
     * @js NA
     */
    static ScriptHandlerMgr* getInstance(void);
    
    /**@~english
     * Destroy the instance of the ScriptHandlerMgr.
     *
     * @~chinese 
     * ����ScriptHandlerMgr��ʵ������
     * 
     * @lua NA
     * @js NA
     */
    static void destroyInstance(void);
    
    /**@~english
     * Construct or update the mapping relationship among c++ Ref object ,HandlerType and the reference id corresponding to the pointer of Lua function.
     *
     * @~chinese 
     * ���������c++ Ref����,HandlerType�Լ���ӦLua������ָ������id��ӳ���ϵ��
     * 
     * @param object @~english a Ref object.
     * @~chinese Ref����
     * @param handler @~english a reference id corresponding to the pointer of Lua function.
     * @~chinese ��ӦLua����ָ�������id��
     * @param handlerType @~english ScriptHandlerMgr::HandlerType.
     * @~chinese ScriptHandlerMgr::HandlerType��
     * @lua registerScriptHandler
     * @js NA
     */
    void addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType);
    
    /**@~english
     * By the handlerType and Ref object, find the correct reference id corresponding to the pointer of Lua function.
     * If found, remove the reference of Lua function corresponding to this id in the 'toluafix_refid_function_mapping' table.
     * 
     * @~chinese 
     * ͨ��handlerType��Ref���󣬲��Ҷ���Lua����ָ�������id��
     * ����ҵ�,���Ƴ�Lua����toluafix_refid_function_mapping table�ж�Ӧid��Lua���������á�
     * 
     * @param object @~english a Ref object.
     * @~chinese һ��Ref����
     * @param handlerType @~english ScriptHandlerMgr::HandlerType.
     * @~chinese ScriptHandlerMgr::HandlerType��
     * @lua unregisterScriptHandler
     * @js NA
     */
    void removeObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    
    /**@~english
     * By the handlerType and object, find the correct reference id corresponding to the pointer of Lua function.
     *
     * @~chinese 
     * ����handlerType��Ref����,�ҵ���ӦLua����ָ�������id��
     * 
     * @param object @~english a Ref object.
     * @~chinese һ��Ref����
     * @param handlerType @~english ScriptHandlerMgr::HandlerType.
     * @~chinese ScriptHandlerMgr::HandlerType��
     * @return @~english reference id corresponding to the pointer of Lua function,otherwise 0.
     * @~chinese Lua����ָ�������id����0��
     * @lua NA
     * @js NA
     */
    int  getObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    
    /**@~english
     * Remove the all relationship among the object, HandlerType and the reference id corresponding to the pointer of Lua function.
     * Meanwhile, remove the reference of Lua function corresponding to the id the object has in the 'toluafix_refid_function_mapping' table.
     *
     * @~chinese 
     * �Ƴ����к�object��HandlerType�Լ�����id��ص�ӳ���ϵ��
     * ͬʱ,��������id, �Ƴ�`toluafix_refid_function_mapping`��Lua����ָ������á�
     * 
     * @param object @~english the Ref object.
     * @~chinese һ��Ref����
     * @js NA
     */
    void removeObjectAllHandlers(void* object);
    
    /**@~english
     * Add customizable relationship among c++ Ref object, HandlerType and the reference id corresponding to the pointer of Lua function.
     * In the customizable relationship, we don't pass the HandlerType, it will obtain the HandlerType by auto-increasing.
     * The HandlerTypes used to customizable relationship are between EVENT_CUSTOM_BEGAN(10000) and EVENT_CUSTOM_ENDED(11000).
     * If the HandlerType increased more than EVENT_CUSTOM_ENDED(110000),it would trigger assert.
     *
     * @~chinese
     * ����Զ����c++ Ref����,HandlerType�Ͷ�ӦLua����ָ�������id��ӳ���ϵ��
     * �������Զ���ӳ���ϵ��,���ǲ��贫��HandlerType����, ��������ڲ���ͨ�������ӵķ�����ȡHandlerType��
     * �����Զ���ӳ���ϵ��HandlerTypes��ȡֵ��Χ��EVENT_CUSTOM_BEGAN(10000)��EVENT_CUSTOM_ENDED(11000)֮�䡣
     * ���HandlerType���ӳ���EVENT_CUSTOM_ENDED(110000),�����������ԡ�
     * 
     * @param object @~english the Ref object.
     * @~chinese Ref����
     * @param handler @~english a reference index corresponding to the pointer of Lua function.
     * @~chinese Lua����ָ�������id��
     * @return @~english ScriptHandlerMgr::HandlerType the ScriptHandlerMgr::HandlerType value after adding.
     * @~chinese ����Զ���ӳ���ϵ���ScriptHandlerMgr::HandlerTypeֵ��
     * @lua NA
     * @js NA
     */
    ScriptHandlerMgr::HandlerType addCustomHandler(void* object, int handler);
    
private:
    void init(void);
    static ScriptHandlerMgr* _scriptHandlerMgr;
    MapObjectHandlers _mapObjectHandlers;
};

NS_CC_END

// end group
/// @}

/// @cond
TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);
/// @endcond

#endif //__LUA_SCRIPT_HANDLER_MGR_H__
