/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
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

#ifndef __CC_LUA_STACK_H_
#define __CC_LUA_STACK_H_

extern "C" {
#include "lua.h"
}

#include "cocos2d.h"
#include "CCLuaValue.h"

/**
 * @addtogroup lua
 * @{
 */


NS_CC_BEGIN

/**@~english
 * LuaStack is used to manager the operation on the lua_State,eg., push data onto the lua_State, execute the function depended on the lua_State, and so on.
 * In the current mechanism, there is only one lua_State in one LuaStack object.
 *
 * @~chinese 
 * LuaStack���ڹ���lua_State����,����: ������ѹ�뵽lua_State��ִ��lua_State�ϵĺ����ȵȡ�
 * �ڵ�ǰ�Ļ���,��һ��LuaStack������ֻ��һ��lua_State
 * 
 * @lua NA
 * @js NA
 */

class LuaStack : public Ref
{
public:
    /**@~english
     * Create a LuaStack object, it will new a lua_State.
     * @~chinese 
     * ����һ��LuaStack����,�����½�һ��lua_State��
     */

    static LuaStack *create(void);
    /**@~english
     * Create a LuaStack object with the existed lua_State.
     * @~chinese 
     * ���ݴ��ڵ�lua_State����һ��LuaStack����
     */

    static LuaStack *attach(lua_State *L);
    
    /** @~english Destructor.  @~chinese ����������*/

    virtual ~LuaStack();
    
    /**@~english
     * Method used to get a pointer to the lua_State that the script module is attached to.
     *
     * @~chinese 
     * ��ȡ�ű�ģ��������lua_Stateָ�롣
     * 
     * @return @~english A pointer to the lua_State that the script module is attached to.
     * @~chinese lua_Stateָ�롣
     */

    lua_State* getLuaState(void) {
        return _state;
    }
    
    /**@~english
     * Add a path to find lua files in.
     *
     * @~chinese 
     * ���һ������Lua�ļ���·����
     * 
     * @param path @~english to be added to the Lua search path.
     * @~chinese ����������·����
     */

    virtual void addSearchPath(const char* path);
    
    /**@~english
     * Add lua loader.
     * 
     * @~chinese 
     * ���Lua���غ�����
     * 
     * @param func @~english a function pointer point to the loader function.
     * @~chinese ���غ����ĺ���ָ�롣
     */

    virtual void addLuaLoader(lua_CFunction func);
    
    /**@~english
     * Reload script code corresponding to moduleFileName.
     * If value of package["loaded"][moduleFileName] is existed, it would set the value nil.Then,it calls executeString function.
     *
     * @~chinese 
     * ���¼��ض�Ӧģ�����Ľű����롣
     * ���package["loaded"][moduleFileName]��ֵ����,����������ֵΪnil��Ȼ���ٵ���executeString������
     * 
     * @param moduleFileName @~english String object holding the filename of the script file that is to be reloaded.
     * @~chinese �����¼��صĽű��ļ�����
     * @return @~english 0 if the string is excuted correctly or other if the string is excuted wrongly.
     * @~chinese ���ִ����ȷ����0�����򷵻�����ֵ��
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
     * ͨ������Lua table,�Ƴ�Ref������Lua table�е����á�
     * ��ص�Lua table����toluafix_refid_ptr_mapping��toluafix_refid_type_mapping tolua_value_root��object_Metatable["tolua_ubox"]��tolua_ubox��
     * ͬʱ��������Ӧ��userdataΪnullptr�Լ��Ƴ�ȥ�ö�����ص�Lua����������
     * 
     * Ŀǰ�Ļ����£������߲���Ҫֱ�ӵ�������������������������LuaEngier�������������Զ������á�
     * 
     * @param object @~english the key object to remove script object.
     * @~chinese �����Ƴ��ű��������õļ�ֵ
     */

    virtual void removeScriptObjectByObject(Ref* object);
    
    /**@~english
     * Remove Lua function reference by nHandler by setting toluafix_refid_function_mapping[nHandle] nil.
     *
     * @~chinese 
     * ͨ������toluafix_refid_function_mapping[nHandle]=nil,�Ƴ�Lua��������
     * 
     * @param nHandler @~english the function reference id to find the correspoinding Lua function pointer.
     * @~chinese Lua����������id��
     */

    virtual void removeScriptHandler(int nHandler);
    
    /**@~english
     * Reallocate Lua function reference id to the Lua function pointer to add reference.
     *
     * @~chinese 
     * ���·���Lua����������id��
     * 
     * @param nHandler @~english the reference id to find the correspoinding Lua function pointer.
     * @~chinese Lua����������id��
     */

    virtual int reallocateScriptHandler(int nHandler);
    
    /**@~english
     * Execute script code contained in the given string.
     *
     * @~chinese 
     * ִ�и����ַ����а����Ľű����롣
     * 
     * @param codes @~english holding the valid script code that should be executed.
     * @~chinese �豻ִ�еĽű������ַ�����
     * @return @~english 0 if the string is excuted correctly,other if the string is excuted wrongly.
     * @~chinese ִ�гɹ�����0�����򷵻�����ֵ��
     */

    virtual int executeString(const char* codes);
    
    /**@~english
     * Execute a script file.
     *
     * @~chinese 
     * ִ��һ���ű��ļ���
     * 
     * @param filename @~english String object holding the filename of the script file that is to be executed.
     * @~chinese �ű��ļ����ļ�����
     * @return @~english the return values by calling executeFunction.
     * @~chinese ��������������ִ�н��û�з���ֵʱ����0�����򷵻�1��
     */

    virtual int executeScriptFile(const char* filename);

    /**@~english
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer.
     *
     * @~chinese 
     * ִ��ȫ�ֵĽű�������
     * ��ȫ�ֺ�����Ӧ�����κβ���,ͬʱ����һ��������
     * 
     * @param functionName @~english String object holding the name of the function, in the global script environment, that is to be executed.
     * @~chinese ȫ�ֽű��������ַ�������
     * @return @~english The integer value returned from the script function.
     * @~chinese �ӽű��������ص�����ֵ��
     */

    virtual int executeGlobalFunction(const char* functionName);
    
    /**@~english
     * Set the stack top index 0.
     * @~chinese 
     * ����Luaջ������Ϊ0��
     */

    virtual void clean(void);
    
    /**@~english
     * Pushes a integer number into the stack.
     * 
     * @~chinese 
     * ��һ������ֵѹ��Luaջ��
     * 
     * @param intValue @~english a integer number.
     * @~chinese ����ֵ��
     */

    virtual void pushInt(int intValue);
    
    /**@~english
     * Pushes a float number into the stack.
     *
     * @~chinese 
     * ��һ������ֵѹ��Luaջ��
     * 
     * @param floatValue @~english a float number.
     * @~chinese ����ֵ��
     */

    virtual void pushFloat(float floatValue);
    
    /**@~english
     * Pushes a long number into the stack.
     * 
     * @~chinese 
     * ��һ����������ѹ��Luaջ��
     * 
     * @param longValue @~english a long number.
     * @~chinese ������ֵ��
     */

    virtual void pushLong(long longValue);
    
    /**@~english
     * Pushes a bool value into the stack.
     * 
     * @~chinese 
     * ��һ������ֵѹ��Luaջ��
     * 
     * @param boolValue @~english a bool value.
     * @~chinese ����ֵ
     */

    virtual void pushBoolean(bool boolValue);
    
    /**@~english
     * Pushes the zero-terminated string pointed into the stack.
     *
     * @~chinese 
     * ��һ����'\0'�������ַ���ָ��ѹ��Luaջ��
     * 
     * @param stringValue @~english a pointer point to a zero-terminated string.
     * @~chinese �ַ���ָ�롣
     */

    virtual void pushString(const char* stringValue);
    
    /**@~english
     * Pushes the string pointed to stringValue with size length into the stack.
     *
     * @~chinese 
     * ��ָ��stringValue���ַ�����ָ��lengthѹ��Luaջ��
     * 
     * @param stringValue @~english a pointer point to the string stringValue.
     * @~chinese �ַ���ָ�롣
     * @param length @~english the size.
     * @~chinese ��Ҫѹ��ĳ��ȡ�
     */

    virtual void pushString(const char* stringValue, int length);
    
    /**@~english
     * Pushes a nil value into the stack.
     * @~chinese 
     * ѹ��һ��nil��Luaջ��
     */

    virtual void pushNil(void);
    
    /**@~english
     * Pushes a Ref object into the stack,please refer to toluafix_pushusertype_ccobject for detail information
     *
     * @~chinese 
     * ��һ��Ref����ѹ�뵽Luaջ����ϸ��Ϣ�����toluafix_pushusertype_ccobject
     * 
     * @see toluafix_pushusertype_ccobject.
     */

    virtual void pushObject(Ref* objectValue, const char* typeName);
    
    /**@~english
     * According to the type of LuaValue, it would called the other push function in the internal.
     *   type                           function
     * LuaValueTypeInt                   pushInt
     * LuaValueTypeFloat                 pushFloat
     * LuaValueTypeBoolean               pushBoolean
     * LuaValueTypeString                pushString
     * LuaValueTypeDict                  pushLuaValueDict
     * LuaValueTypeArray                 pushLuaValueArray
     * LuaValueTypeObject                pushObject
     * 
     * @~chinese 
     * ���ݲ�ͬ���͵�LuaValue,�������ں����ڲ�����������ص�push����
     *    ����                       ����
     * LuaValueTypeInt             pushInt
     * LuaValueTypeFloat           pushFloat
     * LuaValueTypeBoolean         pushBoolean
     * LuaValueTypeString          pushString
     * LuaValueTypeDict            pushLuaValueDict
     * LuaValueTypeArray           pushLuaValueArray
     * LuaValueTypeObject          pushObject
     * 
     * @param value @~english a LuaValue object.
     * @~chinese LuaValue����
     */

    virtual void pushLuaValue(const LuaValue& value);
    
    /**@~english
     * Pushes a Lua table into the stack.
     * The key of table is string.
     * The value of table is got by calling pushLuaValue,@see pushLuaValue.
     * @~chinese 
     * ��һ��Lua tableѹ��Luaջ��
     * ���Lua table��keyֵΪ�ַ�����valueֵ����LuaValue������ͨ������pushLuaValue��ã�@see pushLuaValue��
     * 
     * @param dict @~english a LuaValueDict object.
     * @~chinese LuaValueDict����
     */

    virtual void pushLuaValueDict(const LuaValueDict& dict);
    
    /**@~english
     * Pushes a Lua array table onto the stack.
     * The index of array table is begin at 1.
     * The value of array table is got by calling pushLuaValue,@see pushLuaValue.
     * @~chinese 
     * ��һ��Lua����tableѹ��Luaջ��
     * ����table��������1��ʼ��
     * ���Lua����table�е�ֵͨ������pushLuaValue��ã�@see pushLuaValue��
     *
     * @param array @~english a LuaValueArray object.
     * @~chinese LuaValueArray
     */

    virtual void pushLuaValueArray(const LuaValueArray& array);
    
    /**@~english
     * Get the Lua function pointer from toluafix_refid_function_mapping table by giving nHanlder,then push it into the Lua stack.
     * If the Lua function pointer corresponding to the nHanlder isn't found, it would push nil on the top index of stack, then it would output the error log in the debug model.
     *
     * @~chinese 
     * ͨ��������nHandler����toluafix_refid_function_mapping table��ȡ��Ӧ��Lua����ָ�룬������ѹ��Luaջ��
     * ����޷��ҵ�nHanlder��Ӧ��Lua����ָ��, �����ѹ��һ��nilֵ��ջ�����������ڵ���ģʽ�����������������־��
     * 
     * @return @~english true if get the no-null function pointer otherwise false.
     * @~chinese ����������û��null�ĺ���ָ�����
     */

    virtual bool pushFunctionByHandler(int nHandler);
    
    /**@~english
     * Find and execute the Lua function on the -(numArgs + 1) index on the stack,the function has numArgs variables.
     *
     * @~chinese 
     * ͨ��numArgsֵ����ȡLuaջ��-(numArgs + 1)��������Lua������ִ��
     * 
     * @param numArgs @~english the number of variables.
     * @~chinese ������������
     * @return @~english 0 if it happen the error or it hasn't return value, otherwise it return the value by calling the Lua function��integer type or boolean type.
     * @~chinese ������������û�з���ֵ����0,���򷵻ر�����Lua������һ������ֵ������������ֵ���ǲ���ֵ��
     */

    virtual int executeFunction(int numArgs);
    
    /**@~english
     * Find and execute the Lua function corresponding to the nHandler,the function has numArgs variables.
     *
     * @~chinese 
     * ���Ҳ�ִ��nHandler��Ӧ��Lua���������������numArgs��������
     * 
     * @param nHandler @~english the reference id to the Lua function.
     * @~chinese Lua����������id��
     * @param numArgs @~english the number of variables.
     * @~chinese ������������
     * @return @~english the return value is the same as executeFunction,please @see executeFunction.
     * @~chinese ����ֵ��executeFunctionһ����@see executeFunction
     */

    virtual int executeFunctionByHandler(int nHandler, int numArgs);
    
    /**@~english
     * Find and execute the Lua function corresponding to the handler,the function has numArgs variables.
     * By calling this function, the number of return values is numResults(may be > 1).
     * All the return values are stored in the resultArray.
     *
     * @~chinese 
     * ���Ҳ�ִ��handler��Ӧ��Lua���������������numArgs��������
     * ��������������᷵��numResults������ֵ(���ܴ���1)��
     * ���еķ���ֵ������resultArray�С�
     * 
     * @param handler @~english the reference id corresponding to the Lua function.
     * @~chinese ��ӦLua����������id
     * @param numArgs @~english the number of function parameters.
     * @~chinese ����������������
     * @param numResults @~english the number of return values.
     * @~chinese ����ֵ��������
     * @param resultArray @~english a array used to store the return value.
     * @~chinese һ�����ڴ洢����ֵ�����顣
     * @return @~english 0 if it happen error or it hasn't return value, otherwise return 1.
     * @~chinese ��������������û�з���ֵ����0,���򷵻�1��
     */

    virtual int executeFunctionReturnArray(int handler,int numArgs,int numResults,__Array& resultArray);
    
    /**@~english
     * Find and execute the Lua function corresponding to the handler,the function has numArgs variables..
     * By calling this function, the number of return values is numResults(may be > 1).
     * All the return values are used in the callback func.
     *
     * @~chinese 
     * ���Ҳ�ִ��handler��Ӧ��Lua���������������numArgs��������
     * ��������������᷵��numResults������ֵ(���ܴ���1)��
     * ���еķ���ֵ�������ڻص�����func�С�
     * 
     * @param handler @~english the reference id corresponding to the lua function.
     * @~chinese ��ӦLua����������id��
     * @param numArgs @~english the number of function parameters.
     * @~chinese ����������������
     * @param numResults @~english the number of return values.
     * @~chinese ����ֵ��������
     * @param func @~english callback function which is called if the numResults > 0.
     * @~chinese ��numResults > 0ʱ�������õĻص�������
     * @return @~english 0 if it happen error or it hasn't return value, otherwise return 1.
     * @~chinese ��������������û�з���ֵ����0,���򷵻�1��
     */

    virtual int executeFunction(int handler, int numArgs, int numResults, const std::function<void(lua_State*,int)>& func);
    
    /**@~english
     * Handle the assert message.
     *
     * @~chinese 
     * ����assert��Ϣ��
     * 
     * @param msg @~english the assert message string.
     * @~chinese assert��Ϣ�ַ�����
     * @return @~english return true if current _callFromLua is not equal to 0 otherwise return false.
     * @~chinese �����ǰ_callFromLua��Ϊ0����true�����򷵻�false��
     */

    virtual bool handleAssert(const char *msg);
    
    /**@~english
     * Set the key and sign for xxtea encryption algorithm.
     *
     * @~chinese 
     * ���õ�xxtea�����㷨��key��sign��
     * 
     * @param key @~english a string pointer point to key
     * @~chinese key�ַ���ָ��
     * @param keyLen @~english the length of key
     * @~chinese key�ĳ���
     * @param sign @~english a string pointer point to sign
     * @~chinese sign�ַ���ָ��
     * @param signLen @~english the length of sign
     * @~chinese sign�ĳ���
     */

    virtual void setXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen);
    
    /**@~english
     * Cleanup the key and sign for xxtea encryption algorithm.
     * @~chinese 
     * ���xxtea�����㷨��key��sign��
     */

    virtual void cleanupXXTEAKeyAndSign();
    
    /**@~english
     * Loads a buffer as a Lua chunk.This function uses lua_load to load the Lua chunk in the buffer pointed to by chunk with size chunkSize.
     * if current stack enable the xxtea encryption algorithm and the the beginner of the chunk has the sign, the chunk should be decrypt first.
     *
     * @~chinese 
     * ����һ��Lua����顣�ú���ʹ��lua_loadͨ��һ��ָ�������ָ�����һ���СΪchunkSize��Lua����顣
     * �����ǰ֧��xxtea�㷨������chunk��ͷ����singǩ������ô���صĳ���黹��Ҫ���н��ܲ�����
     * 
     * @param L @~english the current lua_State.
     * @~chinese ��ǰlua_State��
     * @param chunk @~english the chunk pointer.
     * @~chinese �����ָ�롣
     * @param chunkSize @~english the size of buffer.
     * @~chinese ������С��
     * @param chunkName @~english the name of chunk pointer.
     * @~chinese ���������ơ�
     * @return @~english 0, LUA_ERRSYNTAX or LUA_ERRMEM:.
     * @~chinese 0,LUA_ERRSYNTAX��LUA_ERRMEM:��
     */

    int luaLoadBuffer(lua_State *L, const char *chunk, int chunkSize, const char *chunkName);
    
    /**@~english
     * Load the Lua chunks from the zip file
     * 
     * @~chinese 
     * ��zip�ļ�����Lua�����
     * 
     * @param zipFilePath @~english file path to zip file.
     * @~chinese zip�ļ����ļ�·����
     * @return @~english 1 if load sucessfully otherwise 0.
     * @~chinese ���سɹ�����1�����򷵻�0��
     */

    int loadChunksFromZIP(const char *zipFilePath);
    
    /**@~english
     * Load the Lua chunks from current lua_State.
     *
     * @~chinese 
     * �ӵ�ǰ��lua_State�м���Lua����顣
     * 
     * @param L @~english the current lua_State.
     * @~chinese ��ǰ��lua_State��
     * @return @~english 1 if load sucessfully otherwise 0.
     * @~chinese ���سɹ�����1�����򷵻�0��
     */

    int luaLoadChunksFromZIP(lua_State *L);
    
protected:
    LuaStack(void)
    : _state(nullptr)
    , _callFromLua(0)
    , _xxteaEnabled(false)
    , _xxteaKey(nullptr)
    , _xxteaKeyLen(0)
    , _xxteaSign(nullptr)
    , _xxteaSignLen(0)
    {
    }
    
    bool init(void);
    bool initWithLuaState(lua_State *L);
    
    lua_State *_state;
    int _callFromLua;
    bool  _xxteaEnabled;
    char* _xxteaKey;
    int   _xxteaKeyLen;
    char* _xxteaSign;
    int   _xxteaSignLen;
};

NS_CC_END

// end group
/// @}
#endif // __CC_LUA_STACK_H_
