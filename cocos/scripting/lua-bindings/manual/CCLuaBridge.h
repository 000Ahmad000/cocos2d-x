/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#ifndef __LUA_BRIDGE_H_
#define __LUA_BRIDGE_H_

#include <string>
#include <map>
#include "CCLuaEngine.h"

extern "C" {
#include "lua.h"
}

using namespace std;
/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN
/** @~english LuaBridge Error enum, with inline docs.  @~chinese LuaBridge�Ĵ���ö��*/
typedef enum {
    kLuaBridgeErrorOk                   = 0,  /** &lt; value 0 */
    kLuaBridgeErrorInvalidParameters    = -1, /** &lt; value -1 */
    kLuaBridgeErrorClassNotFound        = -2, /** &lt; value -2 */
    kLuaBridgeErrorMethodNotFound       = -3, /** &lt; value -3 */
    kLuaBridgeErrorExceptionOccurred    = -4, /** &lt; value -4 */
    kLuaBridgeErrorMethodSignature      = -5, /** &lt; value -5 */
    kLuaBridgeErrorJavaVMError          = -6, /** &lt; value -6 */
} LuaBridgeError;

#define LUA_BRIDGE_REGISTRY_FUNCTION    "lua_bridge_function_id"        // table[function] = id
#define LUA_BRIDGE_REGISTRY_RETAIN      "lua_bridge_function_id_retain" // table[id] = retain count

/**@~english
 * Build bridge between ObjC and Lua.
 * It makes Lua and ObjC can call each other conveniently.
 *
 * @~chinese 
 * ����ObjC��Lua֮���������
 * ��ʹLua��ObjC����Է���ػ�����á�
 * 
 * @lua NA
 * @js NA
 */
class LuaBridge
{
public:
    /**@~english
     * Get the LuaStack of LuaEngine.
     *
     * @~chinese 
     * ��ȡLuaEngine��LuaStack����
     * 
     * @return @~english the LuaStack object.
     * @~chinese LuaStack����
     */
    static LuaStack *getStack(void);
    /**@~english
     * Push the function pointer corresponding to functionId on the top of lua stack by searching the `lua_bridge_function_id` table.
     * If it don't find the function pointer corresponding to functionId, it will reset stack top index to the index before searching.
     *
     * @~chinese 
     * ͨ�����ҡ�lua_bridge_function_id�� table��functionId��Ӧ�ĺ���ָ��ѹ�뵽Luaջ����
     * ���û���ҵ�functionId��Ӧ�ĺ���ָ��,��������Luaջ������Ϊ����ǰ��Luaջ��������
     *
     * @param functionId @~english the value used to search the `lua_bridge_function_id` table.
     * @~chinese ���ڲ��ҡ�lua_bridge_function_id����ĺ�������id��

     * @return @~english Return 0 if the `lua_bridge_function_id` table or the function pointer corresponding to functionId don't exist, otherwise return -1.
     * @~chinese ���������`lua_bridge_function_id` table�����ڻ��߶�ӦfunctionId�ĺ���ָ�벻���ڣ�����0�����򣬷���-1��
     */
    static int pushLuaFunctionById(int functionId);
    
    /**@~english
     * The retain count would be increase by 1 corresponding to functionId in the `lua_bridge_function_id_retain` table if it could be found.
     * If `lua_bridge_function_id_retain` table is not existed or the type of lua_bridge_function_id_retain[functionId] isn't LUA_TNUMBER, It would return 0.
     * The top index of Lua stack the same as before calling this function.
     *
     * @~chinese 
     * ����ڶ�Ӧ��'lua_bridge_function_id_retain'���п����ҵ�functionId�����ü���ֵ����ô��Ӧ�����ü���ֵ��1��
     * ���`lua_bridge_function_id_retain`�����ڻ���lua_bridge_function_id_retain[functionId]��Ӧ��ֵ�����Ͳ���LUA_TNUMBER����������0�����򷵻ظ��º�����ü�����
     * Luaջ����������ǰ��һ�¡�
     * 
     * @param functionId @~english the value used to search the `lua_bridge_function_id_retain` table.
     * @~chinese ���ڲ��ҡ�lua_bridge_function_id_retain�� table�ĺ�������id��
     * @return @~english the retain count or 0.
     * @~chinese ���ü�����0��
     */
    static int retainLuaFunctionById(int functionId);
    
    /**@~english
     *
     * The retain count would be reduced by 1 corresponding to functionId in the `lua_bridge_function_id_retain` table if it could be found.
     * If `lua_bridge_function_id` table or `lua_bridge_function_id_retain` aren't existed or the type of lua_bridge_function_id_retain[functionId] isn't LUA_TNUMBER , it would return 0.
     * If the value of retain count is 0 after reducing, it would update the `lua_bridge_function_id_retain` table and `lua_bridge_function_id_retain` table to remove the  reference corresponding to this functionId
     *
     * @~chinese 
     * 
     * ����ڶ�Ӧ��'lua_bridge_function_id_retain'���п����ҵ�functionId�����ü���ֵ����ô��Ӧ�����ü���ֵ��1��
     * ���`lua_bridge_function_id`����`lua_bridge_function_id_retain`�����ڻ���lua_bridge_function_id_retain[functionId]��Ӧ��ֵ�����Ͳ���LUA_TNUMBER����������0��
     * ͬʱ��������ü�������Ϊ0,����ɾ�����functionId��Ӧ�ڡ�lua_bridge_function_id_retain�� table�͡�lua_bridge_function_id_retain�� table�е�ֵ������0�����򷵻����ü�����
     * 
     * @param functionId @~english the value used to search the `lua_bridge_function_id` table and `lua_bridge_function_id` table.
     * @~chinese ���ڲ��ҡ�lua_bridge_function_id�� table�͡�lua_bridge_function_id�� table�еĺ�������id��
     * @return @~english the retain count or 0.
     * @~chinese ���ü���ֵ��0��
     */
    static int releaseLuaFunctionById(int functionId);
    
protected:
    static int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);

    static lua_State *s_luaState;
    static int        s_newFunctionId;
};

NS_CC_END

// end group
/// @}

#endif // __LUA_BRIDGE_H_
