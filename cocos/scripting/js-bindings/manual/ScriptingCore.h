/******************************************************************
 * Created by Rolando Abarca on 3/14/12.
 * Copyright (c) 2012 Zynga Inc. All rights reserved.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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
 ******************************************************************/

#ifndef __SCRIPTING_CORE_H__
#define __SCRIPTING_CORE_H__


#include "jsapi.h"
#include "jsfriendapi.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "js_bindings_config.h"
#include "js_bindings_core.h"
#include "spidermonkey_specifics.h"
#include "js_manual_conversions.h"
#include "mozilla/Maybe.h"

#include <assert.h>
#include <memory>

#define ENGINE_VERSION "Cocos2d-JS v3.9"

void js_log(const char *format, ...);

typedef void (*sc_register_sth)(JSContext* cx, JS::HandleObject global);

void registerDefaultClasses(JSContext* cx, JS::HandleObject global);


class SimpleRunLoop : public cocos2d::Ref
{
public:
    void update(float d);
};

/**
 * @addtogroup jsb
 * @{
 */

/**
 * @brief @~english ScriptingCore is the main class which manages interaction with JavaScript environment
 * @~chinese ScriptingCore�ǹ�����JavaScript���������ĺ�����
 * @details @~english It creates the JavaScript context and its global object.
 * It also manages object bindings between C++ scope and JavaScript scope, 
 * for most cocos2d classes, if you create an object in JavaScript scope, it will also create a C++ object,
 * ScriptingCore will manage a proxy between them and synchronize the life cycle.
 * It can: 
 * - Execute JavaScript functions in different ways with different parameters
 * - Evaluate JavaScript commands or string
 * - Execute a JavaScript file
 * - Clean a JavaScript file cache
 * - Clean all JavaScript files
 * - Cleanup or reset the JavaScript context
 * - Invoke garbage collection of JavaScript context
 * - etc...
 * @~chinese ������JavaScript�����ĺ�ȫ�ֶ���
 * ��������C++������JavaScript��������֮��İ󶨣�
 * ���ڴ����cocos2d�࣬�����JavaScript�����ڴ���һ������������ͬʱ����һ��c++����,
 * ScriptingCore��Ϊ��ͬ�����¶������һ������ͬ����ͬ�����µ��������ڡ�
 * ������:
 * - �Բ�ͬ�ķ�ʽ�벻ͬ�Ĳ���ִ��JavaScript����
 * - ִ��JavaScript������ַ���
 * - ִ��һ��JavaScript�ļ�
 * - ����һ��JavaScript�ļ�����
 * - �������е�JavaScript�ļ�����
 * - ���������JavaScript������
 * - ����JavaScript�����ĵ������ռ�
 * - �ȵ�...
 */
class ScriptingCore : public cocos2d::ScriptEngineProtocol
{
private:
    JSRuntime *_rt;
    JSContext *_cx;
    mozilla::Maybe<JS::PersistentRootedObject> _global;
    mozilla::Maybe<JS::PersistentRootedObject> _debugGlobal;
    SimpleRunLoop* _runLoop;

    bool _callFromScript;
    ScriptingCore();
public:
    ~ScriptingCore();

    /**@~english
     * ScriptingCore is a singleton class, you can retrieve its instance with this function.
     * @~chinese 
     * ScriptingCore��һ�������࣬����������������ȡ����ʵ����
     * @return @~english The ScriptingCore instance.
     * @~chinese ScriptingCoreʵ����
     */
    static ScriptingCore *getInstance();
    
    /**@~english
     * Gets the script type, for ScriptingCore, it will return `cocos2d::kScriptTypeJavascript`
     * @~chinese 
     * ��ȡ�ű����ͣ���������`cocos2d::kScriptTypeJavascript`
     * @return `cocos2d::kScriptTypeJavascript`
     */
    virtual cocos2d::ccScriptType getScriptType() override { return cocos2d::kScriptTypeJavascript; };

    /**
     * @brief @~english Removes the C++ object's linked JavaScript proxy object from JavaScript context
     * @~chinese ��JavaScript��������ɾ��ָ��C++�����JavaScript�������
     * @param obj @~english Object to be removed
     * @~chinese ��Ҫ��ɾ���Ķ���
     */
    virtual void removeScriptObjectByObject(cocos2d::Ref* obj) override;
    
    /**
     * @brief @~english Useless in ScriptingCore, please use evalString
     * @~chinese ��ScriptingCore�����ã���ʹ��evalString
     * @see evalString
     */
    virtual int executeString(const char* codes) override { return 0; }
    
    /**
     * @brief @~english Pause scheduled tasks and actions for an object proxy.
     * @~chinese ��ͣ���������ָ��Ľڵ����������Ͷ�����
     * @param p @~english The object proxy
     * @~chinese �������
     */
    void pauseSchedulesAndActions(js_proxy_t* p);
    /**
     * @brief @~english Resume scheduled tasks and actions for an object proxy.
     * @~chinese �ָ����������ָ��Ľڵ����������Ͷ�����
     * @param p @~english The object proxy
     * @~chinese �������
     */
    void resumeSchedulesAndActions(js_proxy_t* p);
    /**
     * @brief @~english Cleanup scheduled tasks and actions for an object proxy.
     * @~chinese ������������ָ��Ľڵ����������Ͷ�����
     * @param p @~english The object proxy
     * @~chinese �������
     */
    void cleanupSchedulesAndActions(js_proxy_t* p);

    /**
     * @brief @~english Useless in ScriptingCore, please use runScript
     * @~chinese ��ScriptingCore������,��ʹ��runScript
     * @see runScript
     */
    virtual  int executeScriptFile(const char* filename) override { return 0; }

    /**
     * @brief @~english Useless in ScriptingCore, please use executeFunctionWithOwner
     * @~chinese ��ScriptingCore������,��ʹ��executeFunctionWithOwner
     * @see executeFunctionWithOwner
     */
    virtual int executeGlobalFunction(const char* functionName) override { return 0; }

    virtual int sendEvent(cocos2d::ScriptEvent* message) override;
    virtual bool parseConfig(ConfigType type, const std::string& str) override;
    /**
     * @brief @~english Useless in ScriptingCore
     * @~chinese ��ScriptingCore������
     * @return @~english false
     * @~chinese false
     */
    virtual bool handleAssert(const char *msg) override { return false; }

    virtual void setCalledFromScript(bool callFromScript) override { _callFromScript = callFromScript; };
    virtual bool isCalledFromScript() override { return _callFromScript; };
    
    /**
     * @brief @~english Execute a js function with a JavaScript object as parameter.
     * By passing a native object, ScriptingCore will found its JavaScript object with the proxy. 
     * Then the function will be invoked with the native object's js proxy as caller.
     * @~chinese ��һ��JavaScript������Ϊ����ִ��һ��js������
     * ͨ������һ��C++ԭ������ScriptingCore�����ҵ�����JavaScript�������
     * Ȼ��ʹ�ô��������Ϊjs�����ߵ���ָ����JS������
     * @param nativeObj @~english The caller object's C++ proxy.
     *                  @~chinese �����߶����c++�������
     * @param name      @~english The function name.
     *                  @~chinese ���������֡�
     * @param obj       @~english The JavaScript object as parameter.
     *                  @~chinese ��Ϊ������JavaScript����
     * @return @~english Return the js function's boolean result if successfully invoked, otherwise return false.
     * @~chinese ������óɹ�����js�����Ĳ�����������򷵻�false��
     */
    bool executeFunctionWithObjectData(void* nativeObj, const char *name, JSObject *obj);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments count and arguments.
     * @~chinese ��һ��JavaScript�����ߣ������������������Ͳ���ִ��һ��js������
     * @param owner     @~english The caller object.
     *                  @~chinese �����߶���
     * @param name      @~english The function name.
     *                  @~chinese ���������֡�
     * @param argc      @~english The arguments count.
     *                  @~chinese ����������
     * @param vp        @~english The arguments.
     *                  @~chinese ������
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese ���óɹ�ʱ����true�����򷵻�false��
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments count, arguments and a return value.
     * @~chinese ��һ��JavaScript�����ߣ������������������������ͷ���ִֵ��һ��js������
     * @param owner     @~english The caller object.
     *                  @~chinese �����߶���
     * @param name      @~english The function name.
     *                  @~chinese ���������֡�
     * @param argc      @~english The arguments count.
     *                  @~chinese ����������
     * @param vp        @~english The arguments.
     *                  @~chinese ������
     * @param retVal    @~english The js object to save the return value.
     *                  @~chinese �������淵��ֵ��js����
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese ���óɹ�ʱ����true�����򷵻�false��
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp, JS::MutableHandleValue retVal);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments array.
     * This is more reliable in js memory management
     * @~chinese ��һ��JavaScript�����ߣ��������Ͳ�������ִ��һ��js������
     * �����js�ڴ������˵���ӿɿ�
     * @param owner     @~english The caller object.
     *                  @~chinese ���ö���
     * @param name      @~english The function name.
     *                  @~chinese ���������֡�
     * @param args      @~english The arguments array.
     *                  @~chinese �������顣
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese ���óɹ�ʱ����true�����򷵻�false��
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments array and a return value.
     * This is more reliable in js memory management
     * @~chinese ��һ��JavaScript�����ߣ������������������һ������ִֵ��һ��js������
     * �����js�ڴ������˵���ӿɿ�
     * @param owner     @~english The caller object.
     *                  @~chinese ���ö���
     * @param name      @~english The function name.
     *                  @~chinese ���������֡�
     * @param args      @~english The arguments array.
     *                  @~chinese �������顣
     * @param retVal    @~english The js object to save the return value.
     *                  @~chinese �������淵��ֵ��js����
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese ���óɹ�ʱ����true�����򷵻�false��
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args, JS::MutableHandleValue retVal);

    /**
     * @brief @~english Execute a js function with a js this object and the js function object.
     * @~chinese ��js this�����һ��js��������ִ�����js������
     * @param thisObj   @~english The js this object.
     *                  @~chinese js this����
     * @param callback  @~english The js function object.
     *                  @~chinese js��������
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese ���óɹ�ʱ����true�����򷵻�false��
     */
    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback);
    /**
     * @brief @~english Execute a js function with a js this object, the js function object, arguments and a return value.
     * @~chinese ��js this�����һ��js��������ִ�����js������
     * @param thisObj   @~english The js this object.
     *                  @~chinese js this����
     * @param callback  @~english The js function object.
     *                  @~chinese js��������
     * @param vp        @~english The arguments array.
     *                  @~chinese �������顣
     * @param retVal    @~english The js object to save the return value.
     *                  @~chinese �������淵��ֵ��js����
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese ���óɹ�ʱ����true�����򷵻�false��
     */
    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback, const JS::HandleValueArray& vp, JS::MutableHandleValue retVal);

    /**@~english
     * Evaluate the specified js code string
     * @~chinese 
     * ִ��ָ����JS�����ַ���
     * @param string    @~english The string with the javascript code to be evaluated
     * @~chinese javascript������ַ���
     * @param outVal    @~english The jsval that will hold the return value of the evaluation.
     * @~chinese ���������淵��ֵ��jsval��
     * @param filename  @~english The filename
     * @~chinese �ļ���
     * @param cx        @~english The js context
     * @~chinese js�����Ķ���
     * @param global    @~english The js global object
     * @~chinese js��ȫ�ֶ���
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese ���óɹ�ʱ����true�����򷵻�false��
     */
    bool evalString(const char *string, jsval *outVal, const char *filename = NULL, JSContext* cx = NULL, JSObject* global = NULL);
    
    /**
     @brief @~english Get script object for the given path
     * @~chinese Ϊ������js�ű�·����ȡ�ű�����
     @param path @~english The script file path
     * @~chinese �ű��ļ�·��
     @return @~english Script object
     * @~chinese �ű�����
     */
    JSScript* getScript(const char *path);

    /**@~english
     * Compile the specified js file
     * @~chinese 
     * ����ָ��·���µ�js�ļ�
     * @param path    @~english The path of the script to to compiled
     * @~chinese �ű��ļ���·��
     * @param global    @~english The js global object
     * @~chinese js��ȫ�ֶ���
     * @param cx        @~english The js context
     * @~chinese js������
     */
    void compileScript(const char *path, JSObject* global = NULL, JSContext* cx = NULL);

    /**@~english
     * Run the specified js file
     * @~chinese 
     * ִ��ָ����js�ļ�
     * @param path @~english The path of the script to be executed
     * @~chinese �ű��ļ���·��
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese �ɹ�ʱ����true�����򷵻�false��
     */
    bool runScript(const char *path);
    /**@~english
     * Run the specified js file
     * @~chinese 
     * ִ��ָ����js�ļ�
     * @param path @~english The path of the script to be executed
     * @~chinese �ű��ļ���·��
     * @param global @~english The global object to execute the script
     * @~chinese ִ�нű���ȫ�ֶ���
     * @param global @~english The context to execute the script
     * @~chinese ִ�нű���js���л���
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese �ɹ�ʱ����true�����򷵻�false��
     */
    bool runScript(const char *path, JS::HandleObject global, JSContext* cx = NULL);

    /**@~english
     * Require the specified js file
     * The difference between run and require is that require returns the export object of the script
     * @param path @~english The path of the script to be executed
     * @param jsvalRet @~english On success, return the value from the last executed expression statement processed in the script
     * @return @~english Return true if succeed, otherwise return false.
     * @see https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey/JSAPI_reference/JS_ExecuteScript
     */
    bool requireScript(const char *path, JS::MutableHandleValue jsvalRet);
    /**@~english
     * Require the specified js file
     * The difference between run and require is that require returns the export object of the script
     * @param path @~english The path of the script to be executed
     * @param global @~english The global object to execute the script
     * @param global @~english The context to execute the script
     * @param jsvalRet @~english On success, return the value from the last executed expression statement processed in the script
     * @return @~english Return true if succeed, otherwise return false.
     * @see https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey/JSAPI_reference/JS_ExecuteScript
     */
    bool requireScript(const char *path, JS::HandleObject global, JSContext* cx, JS::MutableHandleValue jsvalRet);
    
    /**@~english
     * Clean script object for the specified js file
     * @~chinese 
     * ���js�ļ���Ӧ�Ľű��������
     * @param path @~english The path of the js file to be cleaned
     * @~chinese �ű��ļ���·��
     */
    void cleanScript(const char *path);
    
    /**@~english
     * Gets the cached script objects for all executed js file
     * @~chinese 
     * ��ȡ������ִ�е�js�ļ��Ļ���ű�����
     * @return @~english The cached script object map
     * @~chinese ����ű������
     */
    std::unordered_map<std::string, JSScript*> &getFileScript();
    /**@~english
     * Clean all script objects
     * @~chinese 
     * ������нű����󻺴�
     */
    void cleanAllScript();
    
    /**@~english
     * Initialize everything, including the js context, js global object etc.
     * @~chinese 
     * ��ʼ�����еĶ���������js�����ģ�jsȫ�ֶ���ȡ�
     */
    void start();

    /**@~english
     * Cleanup everything, including script cache, js context, global object etc.
     * @~chinese 
     * ������нű����󻺴棬js�����ģ�ȫ�ֶ��󣬵ȵȡ�
     */
    void cleanup();

    /**@~english
     * Cleanup everything then initialize everything
     * @~chinese 
     * ����Ȼ�����³�ʼ�����е�һ��
     */
    void reset();

    /**@~english
     * Add the register_sth callback to the list of functions that need to be called after the creation of the context.
     * It's normally used to register script bindings in the js context for bound classes
     * @~chinese 
     * ���register_sth�ص��������б��У��б��е����лص�������js�����Ĵ����󱻵��á�
     * ��ͨ�����ڽ��Ѱ󶨵���ע�ᵽjs�������С�
     * @param callback @~english The callback to register something to the js context
     * @~chinese ����ע��󶨵Ļص�����
     */
    void addRegisterCallback(sc_register_sth callback);

    /**@~english
     * Create a new context. If one is already there, it will destroy the old context and create a new one.
     * @~chinese 
     * ����һ���µ�js�����ġ����һ���ɵ��������Ѿ����ڣ������ݻپɵ������Ĳ�����һ���µġ�
     */
    void createGlobalContext();

    /**@~english
     * Removes all rooted object in the given js context, rooted object won't be garbage collected.
     * @~chinese 
     * �ڸ�����js������ɾ�����еĸ����󣬸����󲻻ᱻ�������ջ��ƻ��ա�
     * @param cx @~english The js context
     * @~chinese js������
     */
    static void removeAllRoots(JSContext *cx);

    /**@~english
     * Simulate a touch event and dispatch it to a js object.
     * @~chinese 
     * ģ��һ�������¼�����������ɵ�һ��javascript����
     * @param eventType @~english The touch event type
     * @~chinese �����¼�����
     * @param pTouch @~english The touch object
     * @~chinese �������
     * @param obj @~english The js object
     * @~chinese js����
     * @param retval @~english The return value of the touch event callback
     * @~chinese �����¼��ص��ķ���ֵ
     * @return @~english Return 1 if succeed, otherwise return 0.
     * @~chinese ����ɹ�,����1,���򷵻�0��
     */
    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj, JS::MutableHandleValue retval);
    /**@~english
     * Simulate a touch event and dispatch it to a js object.
     * @~chinese 
     * ģ��һ�������¼�����������ɵ�һ��javascript����
     * @param eventType @~english The touch event type
     * @~chinese �����¼�����
     * @param pTouch @~english The touch object
     * @~chinese �������
     * @param obj @~english The js object
     * @~chinese js����
     * @return @~english Return 1 if succeed, otherwise return 0.
     * @~chinese ����ɹ�,����1,���򷵻�0��
     */
    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj);
    /**@~english
     * Simulate a multi touch event and dispatch it to a js object.
     * @~chinese 
     * ģ��һ����㴥���¼�����������ɵ�һ��javascript����
     * @param eventType @~english The touch event type
     * @~chinese �����¼�����
     * @param touches @~english Touchs list for multitouch
     * @~chinese ��㴥�����
     * @param obj @~english The js object
     * @~chinese js����
     * @return @~english Return 1 if succeed, otherwise return 0.
     * @~chinese ����ɹ�,����1,���򷵻�0��
     */
    int executeCustomTouchesEvent(cocos2d::EventTouch::EventCode eventType,
                                  const std::vector<cocos2d::Touch*>& touches, JSObject *obj);
    /**@~english
     * Gets the current global context.
     * @~chinese 
     * ��ȡ��ǰȫ��js�����ġ�
     * @return @~english the global context
     * @~chinese ȫ��js������
     */
    JSContext* getGlobalContext() {
        return _cx;
    };

    /**@~english
     * Report an error in the js context
     * @~chinese 
     * ��js�����ı���һ������
     * @param cx @~english The js context
     * @~chinese js������
     * @param message @~english The error message
     * @~chinese ������Ϣ
     * @param report @~english The js error report object
     * @~chinese js���󱨸����
     */
    static void reportError(JSContext *cx, const char *message, JSErrorReport *report);

    /**@~english
     * Log something to the js context using CCLog.
     * @~chinese 
     * ��js�����Ĵ�ӡһ��log��Ϣ
     * @param cx @~english The js context
     * @~chinese js������
     * @param argc @~english The arguments count
     * @~chinese ��������
     * @param vp @~english The arguments
     * @~chinese ����
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese �ɹ�ʱ����true�����򷵻�false��
     */
    static bool log(JSContext *cx, uint32_t argc, jsval *vp);

    /**@~english
     * Sets a js value to the targeted js obejct's reserved slot, which is not exposed to script environment.
     * @~chinese 
     * ����һ��jsֵ��Ŀ��js�����Ԥ���洢�ۣ���Щֵ�����ᱻ��¶�ڽű�������
     * @param i @~english The slot index
     * @~chinese �洢��λ������
     * @param obj @~english The targeted object
     * @~chinese Ŀ�����
     * @param value @~english The js value to set to the slot
     * @~chinese ��Ҫ���洢��jsֵ
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese �ɹ�ʱ����true�����򷵻�false��
     */
    bool setReservedSpot(uint32_t i, JSObject *obj, jsval value);

    /**@~english
     * Runs a script from script environment, it should be invoked from script environment
     * Bound to `__jsc__.executeScript` and `window.executeScript`
     * @~chinese 
     * �ӽű�����������һ���ű�����Ӧ�ôӽű��б�����
     * ���󶨵�`__jsc__.executeScript`��`window.executeScript`
     * @param cx @~english The js context
     * @~chinese js������
     * @param argc @~english The arguments count
     * @~chinese ��������
     * @param vp @~english The arguments
     * @~chinese ����
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese �ɹ�ʱ����true�����򷵻�false��
     */
    static bool executeScript(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Forces a cycle of garbage collection, it should be invoked from script environment
     * Bound to `__jsc__.garbageCollect` and `window.garbageCollect`
     * @~chinese 
     * ǿ��ִ��һ���������գ���Ӧ�ôӽű��б�����
     * �󶨵�`__jsc__.garbageCollect`��`window.garbageCollect`
     * @param cx @~english The js context
     * @~chinese js������
     * @param argc @~english The arguments count
     * @~chinese ��������
     * @param vp @~english The arguments
     * @~chinese ����
     */
    static bool forceGC(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Dump all named rooted objects, it should be invoked from script environment
     * Bound to `__jsc__.dumpRoot`
     * @~chinese 
     * ��ӡ����������������Ӧ�ôӽű��б�����
     * �󶨵�`__jsc__.dumpRoot`
     * @param cx @~english The js context
     * @~chinese js������
     * @param argc @~english The arguments count
     * @~chinese ��������
     * @param vp @~english The arguments
     * @~chinese ����
     */
    static bool dumpRoot(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Adds a js object to root so that it won't be touched by the garbage collection, it should be invoked from script environment
     * Bound to `__jsc__.addGCRootObject`
     * @~chinese 
     * ���һ��js���󵽸��ڴ��У��������Ͳ��ᱻ�������ջ�����Ӱ�졣��Ӧ�ôӽű��б�����
     * �󶨵�`__jsc__.addGCRootObject`
     * @param cx @~english The js context
     * @~chinese js������
     * @param argc @~english The arguments count
     * @~chinese ��������
     * @param vp @~english The arguments
     * @~chinese ����
     */
    static bool addRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Removes a js object from root, it should be invoked from script environment
     * Bound to `__jsc__.removeGCRootObject`
     * @~chinese 
     * �Ӹ��ڴ���ɾ��һ��js����Ӧ�ôӽű��б�����
     * �󶨵�`__jsc__.removeGCRootObject`
     * @param cx @~english The js context
     * @~chinese js������
     * @param argc @~english The arguments count
     * @~chinese ��������
     * @param vp @~english The arguments
     * @~chinese ����
     */
    static bool removeRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Check whether a js object's C++ proxy is still valid, it should be invoked from script environment
     * Bound to `window.__isObjectValid`
     * @~chinese 
     * ���һ��js�����c++�����Ƿ���Ȼ��Ч����Ӧ�ôӽű��б�����
     * �󶨵�`window.__isObjectValid`
     * @param cx @~english The js context
     * @~chinese js������
     * @param argc @~english The arguments count
     * @~chinese ��������
     * @param vp @~english The arguments
     * @~chinese ����
     */
    static bool isObjectValid(JSContext *cx, uint32_t argc, jsval *vp);

    /**@~english
     * Log a string to the debug environment.
     * Enable the debug environment so that it can be invoked.
     * @~chinese 
     * ��ӡһ���ַ��������Ի�����
     * ���õ��Ի������Ա������Ա����á�
     * @param str @~english The message to log
     * @~chinese ��Ϣ��־
     */
    void debugProcessInput(const std::string& str);
    /**@~english
     * Enable the debug environment, mozilla Firefox's remote debugger or Code IDE can connect to it.
     * @~chinese 
     * ���õ��Ի�����mozilla Firefox��Զ�̵�������Code IDE������������
     * @param port @~english The port to connect with the debug enviroment, default value is 5086
     * @~chinese ���Ի������Ӷ˿ڣ�Ĭ��ֵ��5086
     */
    void enableDebugger(unsigned int port = 5086);
    /**@~english
     * Gets the debug environment's global object
     * @~chinese 
     * ��ȡ���Ի�����ȫ�ֶ���
     * @return @~english The debug environment's global object
     * @~chinese ���Ի�����ȫ�ֶ���
     */
    JSObject* getDebugGlobal() { return _debugGlobal.ref().get(); }
    /**@~english
     * Gets the global object
     * @~chinese 
     * ��ȡȫ�ֶ���
     * @return @~english The global object
     * @~chinese ȫ�ֶ���
     */
    JSObject* getGlobalObject() { return _global.ref().get(); }

    /**@~english
     * Checks whether a C++ function is overrided in js prototype chain
     * @~chinese 
     * ���һ��c++�����Ƿ���js�̳����б�����
     * @param obj @~english The js object
     * @~chinese js����
     * @param name @~english The function name
     * @~chinese ������
     * @param native @~english The native function
     * @~chinese ԭ��C++����
     * @return @~english The global object
     * @~chinese ȫ�ֶ���
     */
    bool isFunctionOverridedInJS(JS::HandleObject obj, const std::string& name, JSNative native);
    
private:
    void string_report(JS::HandleValue val);
    void initRegister();

public:
    int handleNodeEvent(void* data);
    int handleActionEvent(void* data);
    int handleComponentEvent(void* data);
    
    bool handleTouchesEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    bool handleTouchesEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event, JS::MutableHandleValue jsvalRet);

    bool handleTouchEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, cocos2d::Touch* touch, cocos2d::Event* event);
    bool handleTouchEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, cocos2d::Touch* touch, cocos2d::Event* event, JS::MutableHandleValue jsvalRet);

    bool handleMouseEvent(void* nativeObj, cocos2d::EventMouse::MouseEventType eventType, cocos2d::Event* event);
    bool handleMouseEvent(void* nativeObj, cocos2d::EventMouse::MouseEventType eventType, cocos2d::Event* event, JS::MutableHandleValue jsvalRet);

    bool handleKeybardEvent(void* nativeObj, cocos2d::EventKeyboard::KeyCode keyCode, bool isPressed, cocos2d::Event* event);
    bool handleFocusEvent(void* nativeObj, cocos2d::ui::Widget* widgetLoseFocus, cocos2d::ui::Widget* widgetGetFocus);

    void restartVM();
};

JSObject* NewGlobalObject(JSContext* cx, bool debug = false);

bool jsb_set_reserved_slot(JSObject *obj, uint32_t idx, jsval value);
bool jsb_get_reserved_slot(JSObject *obj, uint32_t idx, jsval& ret);

js_proxy_t* jsb_new_proxy(void* nativeObj, JSObject* jsObj);
js_proxy_t* jsb_get_native_proxy(void* nativeObj);
js_proxy_t* jsb_get_js_proxy(JSObject* jsObj);
void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy);

template <class T>
jsval getJSObject(JSContext* cx, T* nativeObj)
{
    js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, nativeObj);
    return proxy ? OBJECT_TO_JSVAL(proxy->obj) : JSVAL_NULL;
}

void removeJSObject(JSContext* cx, void* nativeObj);

/**@~english
 * // JSB
 * @}
 * @~chinese 
 * / / JSB
 * @ }
 */

#endif /* __SCRIPTING_CORE_H__ */
