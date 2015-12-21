/****************************************************************************
 Copyright (c) 2012      cocos2d-x.org
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

#ifndef __CC_LUA_ENGINE_H__
#define __CC_LUA_ENGINE_H__

extern "C" {
#include "lua.h"
}

#include "cocos2d.h"
#include "base/CCScriptSupport.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "cocos2d/LuaScriptHandlerMgr.h"
#include "Lua-BindingsExport.h"


/**
 * @addtogroup lua
 * @{
 */


NS_CC_BEGIN

/**@~english
 * The LuaEngine integrated into the cocos2d-x to process the interactive operation between lua and c++.
 *
 * @~chinese 
 * LuaEngine���ɵ�cocos2d-x�У����ڴ���Lua��c++֮��Ľ���������
 * 
 * @lua NA
 * @js NA
 */
class CC_LUA_DLL LuaEngine : public ScriptEngineProtocol
{
public:
    /**@~english
     * Get instance of LuaEngine.
     *
     * @~chinese 
     * ��ȡLuaEngine��ʵ����
     * 
     * @return @~english the instance of LuaEngine.
     * @~chinese LuaEngine��ʵ����
     */

    static LuaEngine* getInstance(void);
    /**@~english
     * Get defaultEngine of LuaEngine, it was deprecated.
     *
     * @~chinese 
     * ��ȡLuaEngine��Ĭ��ʵ��,�����á�
     * 
     * @return @~english the instance of LuaEngine.
     * @~chinese LuaEngine��ʵ����
     */

    CC_DEPRECATED_ATTRIBUTE static LuaEngine* defaultEngine(void) { return LuaEngine::getInstance(); }
    
    /** @~english
     * Destructor of LuaEngine.
     * @~chinese 
     * LuaEngine������������
     */

    virtual ~LuaEngine(void);
    
    /**@~english
     * Get ccScriptType of LuaEngine used, it is always kScriptTypeLua.
     *
     * @~chinese 
     * ��ȡLuaEngineʹ�õ�ccScriptTypeֵ,������kScriptTypeLua��
     * 
     * @return @~english kScriptTypeLua.
     * @~chinese kScriptTypeLua��
     */

    virtual ccScriptType getScriptType() override {
        return kScriptTypeLua;
    };
    
    /**@~english
     * Get LuaStack of the LuaEngine.
     * All the interactive operation are all base on the LuaStack.
     *
     * @~chinese 
     * ��ȡLuaEngine��LuaStack��
     * ����c++��Lua�Ľ����������ǻ���LuaStack��
     * 
     * @return @~english LuaStack object.
     * @~chinese LuaStack����
     */

    LuaStack *getLuaStack(void) {
        return _stack;
    }
    
    /**@~english
     * Add a path to find Lua files in.
     *
     * @~chinese 
     * ���һ������Lua�ļ�������·����
     * 
     * @param path @~english to be added to the Lua path.
     * @~chinese ������Lua�ļ�����·����
     */

    virtual void addSearchPath(const char* path);
    
    /**@~english
     * Add Lua loader.
     *
     * @~chinese 
     * ���Lua��������
     * 
     * @param func @~english a function pointer point to the loader function.
     * @~chinese ָ��������ĺ���ָ�롣
     */

    virtual void addLuaLoader(lua_CFunction func);
    
    /**@~english
     * Reload script code corresponding to moduleFileName.
     * If value of package["loaded"][moduleFileName] is existed, it would set the value nil.Then,it calls executeString function.
     *
     * @~chinese 
     * ���¼��ض�ӦmoduleFileNameָ��Ľű��ļ���
     * ���package["loaded"][moduleFileName]ֵ��Ϊnil,����������ֵΪnil,Ȼ��,����executeString������
     * 
     * @param moduleFileName @~english String object holding the filename of the script file that is to be executed.
     * @~chinese �ű��ļ����ļ�����
     * @return @~english 0 if the string is executed correctly or other if the string is executed wrongly.
     * @~chinese ���ִ����ȷ,����0�����򷵻�����ֵ��
     */

    virtual int reload(const char* moduleFileName);
    
    /**@~english
     * Remove the related reference about the Ref object stored in the Lua table by set the value of corresponding key nil:
     * The related Lua tables are toluafix_refid_ptr_mapping,toluafix_refid_type_mapping,tolua_value_root and object_Metatable["tolua_ubox"] or tolua_ubox.
     * Meanwhile set the corresponding userdata nullptr and remove the all the lua function reference corresponding to this object.
     * 
     * In current mechanism, this function is called in the destructor of Ref object, developer don't call this functions.
     *
     * @~chinese 
     * ͨ���������Lua table,�Ƴ�Ref������Lua table�е����á�
     * ��ص�Lua table����toluafix_refid_ptr_mapping��toluafix_refid_type_mapping tolua_value_root��object_Metatable["tolua_ubox"]��tolua_ubox��
     * ͬʱ��������Ӧ��userdataΪnullptr�Լ��Ƴ�ȥ�ö�����ص�Lua���������á�
     * 
     * Ŀǰ�Ļ����£������߲���������������������������LuaEngier�������������Զ������á�
     * 
     * @param object @~english the key object to remove script object.
     * @~chinese �����Ƴ��ű�����ļ�ֵ��
     */

    virtual void removeScriptObjectByObject(Ref* object) override;
    
    /**@~english
     * Remove Lua function reference by nHandler by setting toluafix_refid_function_mapping[nHandle] nil.
     *
     * @~chinese 
     * ͨ������toluafix_refid_function_mapping[nHandle]=nil,�Ƴ�Lua��������,��
     * 
     * @param nHandler @~english the function refrence index to find the correspoinding Lua function pointer.
     * @~chinese Lua����������id��
     */

    virtual void removeScriptHandler(int nHandler) override;
    
    /**@~english
     * Reallocate Lua function reference index to the Lua function pointer to add reference.
     *
     * @~chinese 
     * ���·���Lua����������id��
     * 
     * @param nHandler @~english the function refrence index to find the correspoinding Lua function pointer.
     * @~chinese Lua����������id��
     */

    virtual int reallocateScriptHandler(int nHandler) override;
    
    /**@~english
     * Execute script code contained in the given string.
     *
     * @~chinese 
     * ִ�и����ַ����а����Ľű����롣
     * 
     * @param codes @~english holding the valid script code that should be executed.
     * @~chinese �豻ִ�еĽű������ַ�����
     * @return @~english 0 if the string is executed correctly,other if the string is executed wrongly.
     * @~chinese ִ�гɹ�����0�����򷵻�����ֵ��
     */

    virtual int executeString(const char* codes) override;
    
    /**@~english
     * Execute a script file.
     *
     * @~chinese 
     * ִ��һ���ű��ļ���
     * 
     * @param filename @~english String object holding the filename of the script file that is to be executed.
     * @~chinese �ű��ļ����ļ�����
     * @return @~english  0 if it happen error or it hasn't return value, otherwise return 1.
     * @~chinese ��������������ִ�н��û�з���ֵ����0�����򷵻�1��
     */

    virtual int executeScriptFile(const char* filename) override;
    
    /**@~english
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer.
     *
     * @~chinese 
     * ִ��ȫ�ֵĽű�������
     * ��ȫ�ֺ�����Ӧ�����κβ���,ͬʱ����һ��������
     * 
     * @param functionName @~english String object holding the name of the function, in the global script environment, that is to be executed.
     * @~chinese ȫ�ֽű��������ַ������ơ�
     * @return @~english The integer value returned from the script function.
     * @~chinese �ӽű��������ص�����ֵ��
     */

    virtual int executeGlobalFunction(const char* functionName) override;
    virtual int executeNodeEvent(Node* pNode, int nAction);
    virtual int executeMenuItemEvent(MenuItem* pMenuItem);
    virtual int executeNotificationEvent(__NotificationCenter* pNotificationCenter, const char* pszName);
    virtual int executeCallFuncActionEvent(CallFunc* pAction, Ref* pTarget = NULL);
    virtual int executeSchedule(int nHandler, float dt, Node* pNode = NULL);
    virtual int executeLayerTouchesEvent(Layer* pLayer, int eventType, __Set *pTouches);
    virtual int executeLayerTouchEvent(Layer* pLayer, int eventType, Touch *pTouch);
    virtual int executeLayerKeypadEvent(Layer* pLayer, int eventType);
    virtual int executeAccelerometerEvent(Layer* pLayer, Acceleration* pAccelerationValue);
    virtual int executeEvent(int nHandler, const char* pEventName, Ref* pEventSource = NULL, const char* pEventSourceClassName = NULL);
    /**@~english
     * Handle the assert message.
     *
     * @~chinese 
     * ���������Ϣ��
     * 
     * @return @~english return true if current _callFromLua of LuaStack is not equal to 0 otherwise return false.
     * @~chinese ����true,�����ǰLuaStack��_callFromLua������0,���򷵻�false��
     */

    virtual bool handleAssert(const char *msg) override;
    
    /**@~english
     * Parse the config information data.
     * 
     * @~chinese 
     * ����������Ϣ��
     * 
     * @param type @~english in current mechanism,it always ConfigType::COCOSTUDIO.
     * @~chinese �ڵ�ǰ�Ļ�����,������ConfigType::COCOSTUDIO��
     * @param str  @~english the information data.
     * @~chinese ���ݵ���Ϣ��
     * @return @~english if __onParseConfig function exist in the Lua, it return the value that _stack->executeFunction returns otherwise return false.
     * @~chinese ���__onParseConfig Lua��������ʱ,���ķ���ֵ��ִ��_stack->executeFunction����ֵһ�������򷵻�false��
     */

    virtual bool parseConfig(ConfigType type, const std::string& str) override;
    
    /**@~english
     * When some events triggered in the c++ also needs to pass on to lua to handle, we could call this function to send events.
     *
     * @~chinese 
     * ��c++�д�����һЩ�¼���Ҫ���ݵ�Lua�㴦��ʱ,������������������¼���
     * 
     * @param message @~english the ScriptEvent object that has ScriptEventType and the pointer to information data.
     * @~chinese ScriptEvent���󣬰�����ScriptEventType����Ϣ���ݵ�ָ�롣
     * @return @~english default return 0 otherwise return values the same as handleNodeEvent, handleMenuClickedEvent or handleCallFuncActionEvent,etc.
     * @~chinese Ĭ�Ϸ���0,���򷵻�ֵ��handleNodeEvent,handleMenuClickedEvent��handleCallFuncActionEvent�ȵ�һ����
     */

    virtual int sendEvent(ScriptEvent* message) override;
    
    /**@~english
     * Pass on the events related with ScrollView,TableCell,AssertManager, Armature, Accelerometer, Keyboard, Touch, Touches ,Mouse and Custom event to lua to handle.
     *
     * @~chinese 
     * ����ScrollView,TableCell,AssertManager,Armature,Accelerometer,Keyboard,Touch,Touches, Mouse�Լ��Զ����¼���ص��¼����ݸ�Lua����
     * 
     * @param type @~english Different ScriptHandlerMgr::HandlerType means different processing for the data.
     * @~chinese ��ͬ��ScriptHandlerMgr::HandlerType��ζ�Ų�ͬ�����ݴ������̡�
     * @param data @~english The pointer point to the information which should be pass on to lua, it would be parsed in the function to convert to the specific data according to the ScriptHandlerMgr::HandlerType,then pass to lua as function parameters.
     * @~chinese ������Ϣָ�룬���ݲ�ͬ��ScriptHandlerMgr::HandlerType�����ں����ڲ��������ɲ�ͬ�����ݣ�Ȼ����Ϊ��������ѹ�뵽Lua��ջ��
     * @return @~english default return 0 otherwise return values according different ScriptHandlerMgr::HandlerType.
     * @~chinese Ĭ�Ϸ���0,������ݲ�ͬ��ScriptHandlerMgr::HandlerType������ֵҲ��ͬ��
     */

    virtual int handleEvent(ScriptHandlerMgr::HandlerType type,void* data);
    /**@~english
     * Pass on the events related with TableCell and TableView to lua to handle.
     *
     * @~chinese 
     * ����TableCell,TableView��ص��¼����ݸ�Lua����
     * 
     * @param type @~english Different ScriptHandlerMgr::HandlerType means different processing for the data.
     * @~chinese ��ͬ��ScriptHandlerMgr::HandlerType��ζ�Ų�ͬ�����ݴ������̡�
     * @param data @~english The pointer point to the information which should be pass on to lua, it would be parsed in the function to convert to the specific data according to the ScriptHandlerMgr::HandlerType,then pass to lua as function parameters.
     * @~chinese ������Ϣָ�룬���ݲ�ͬ��ScriptHandlerMgr::HandlerType�����ں����ڲ��������ɲ�ͬ�����ݣ�Ȼ����Ϊ��������ѹ�뵽Lua��ջ��
     * @param numResults @~english The number of the return values.
     * @~chinese ����ֵ��������
     * @param func @~english The callback would be called when numResults is > 0.
     * @~chinese ��numResults > 0ʱ������õĻص�������
     * @return @~english default return 0 otherwise return values according different ScriptHandlerMgr::HandlerType.
     * @~chinese Ĭ�Ϸ���0,������ݲ�ͬ��ScriptHandlerMgr::HandlerType������ֵҲ��ͬ��
     */

    virtual int handleEvent(ScriptHandlerMgr::HandlerType type, void* data, int numResults, const std::function<void(lua_State*,int)>& func);
private:
    LuaEngine(void)
    : _stack(nullptr)
    {
    }
    bool init(void);
    int handleNodeEvent(void* data);
    int handleMenuClickedEvent(void* data);
    int handleCallFuncActionEvent(void* data);
    int handleScheduler(void* data);
    int handleKeypadEvent(void* data);
    int handleAccelerometerEvent(void* data);
    int handleCommonEvent(void* data);
    int handleTouchEvent(void* data);
    int handleTouchesEvent(void* data);
    int handlerControlEvent(void* data);
    int handleEvenCustom(void* data);
    int handleAssetsManagerEvent(ScriptHandlerMgr::HandlerType type,void* data);
    int handleTableViewEvent(ScriptHandlerMgr::HandlerType type,void* data);
    int handleTableViewEvent(ScriptHandlerMgr::HandlerType type,void* data, int numResults, const std::function<void(lua_State*,int)>& func);
    int handleArmatureWrapper(ScriptHandlerMgr::HandlerType type,void* data);
    int handleEventAcc(void* data);
    int handleEventKeyboard(ScriptHandlerMgr::HandlerType type,void* data);
    int handleEventTouch(ScriptHandlerMgr::HandlerType type, void* data);
    int handleEventTouches(ScriptHandlerMgr::HandlerType type, void* data);
    int handleEventMouse(ScriptHandlerMgr::HandlerType type, void* data);
    
private:
    static LuaEngine* _defaultEngine;
    LuaStack *_stack;
};

NS_CC_END

// end group
/// @}

#endif // __CC_LUA_ENGINE_H__
