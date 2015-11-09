#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H

#include <jni.h>
#include <string>
#include <vector>

using namespace std;

extern "C" {
#include "lua.h"
}


#define LUAJ_ERR_OK                 0
#define LUAJ_ERR_TYPE_NOT_SUPPORT   (-1)
#define LUAJ_ERR_INVALID_SIGNATURES (-2)
#define LUAJ_ERR_METHOD_NOT_FOUND   (-3)
#define LUAJ_ERR_EXCEPTION_OCCURRED (-4)
#define LUAJ_ERR_VM_THREAD_DETACHED (-5)
#define LUAJ_ERR_VM_FAILURE         (-6)

#define LUAJ_REGISTRY_FUNCTION      "luaj_function_id"          // table[function] = id
#define LUAJ_REGISTRY_RETAIN        "luaj_function_id_retain"   // table[id] = retain count

/**
 * @addtogroup lua
 * @{
 */

/**@~english
 * Build a bridge between Java and Lua script.
 * This mechanism make Lua and Java call each other easily.
 * @~chinese 
 * ����һ��Java��Lua֮���������
 * ��ʹJava��Lua����Է���ػ�����á�
 */
class LuaJavaBridge
{
public:
    ///@cond
    /**@~english
     * Bind callStaticMethod of LuaJavaBridge to Lua.
     * In current mechanism, we could call LuaJavaBridge.callStaticMethod(className, methodName, args) in Lua directly.
     * Meanwhile the callStaticMethod of LuaObjcBridge binding function is wrapped in the luaj.lua
     * @~chinese d
     * ��LuaJavaBridge��callStaticMethod��Lua�С�
     * ��ǰ�Ļ�����,���ǿ�����Lua�ű���ֱ�ӵ���LuaJavaBridge.callStaticMethod(className, methodName, args)
     * ͬʱ,callStaticMethod����luaj.lua��������һ���װ��
     */
    static void luaopen_luaj(lua_State *L);
    ///@endcond

    /**@~english
     * Add a reference count for the Lua functionId(+1),and save this reference in the Lua table named luaj_function_id_retain.
     * 
     * @~chinese 
     * ����functionId�����ü���(+1)��ͬʱ�����ֵ����luaj_function_id_retain table�С�
     * 
     * @param functionId @~english the reference id of Lua function.
     * @~chinese Lua����������id��
     * @return @~english the reference count of the functionId if luaj_function_id_retain table exists and the corresponding value for functionId exists, otherwise return 0.
     *
     * @~chinese �����luaj_function_id_retain table�п����ҵ���ӦfunctionId�����ü���ֵ,���ü�����1�����ظ��º�����ü���,���򷵻�0��
     * 
     * @lua NA
     * @js NA
     */
    static int retainLuaFunctionById(int functionId);

    /**@~english
     * Release a reference count for the Lua functionId(-1).If the reference count is still greater than 0,save this reference in the Lua table named luaj_function_id_retain.
     * Otherwise, remove the reference about this functionId in the luaj_function_id table and the luaj_function_id_retain table by set the corresponding value nil. 
     * 
     * @~chinese 
     * ��
     * ����functionId��Ӧ�����ü���(-1)��������º�����ü������Ǵ���0����ô����luaj_function_id_retain�ж�Ӧ��ֵ������,ͨ�����ö�Ӧ��ֵ����Ϊnil�Ƴ�����functionId��luaj_function_id table��luaj_function_id_retain table�����á�
     * 
     * @param functionId @~english the reference id of Lua function.
     * @~chinese Lua����������id��
     * @return @~english the retain count or 0.
     *
     * @~chinese ���ü�����0��
     * 
     * @lua NA
     * @js NA
     */
    static int releaseLuaFunctionById(int functionId);

    /**@~english
     * Call the Lua function corresponding to the functionId with the string pointer arg.
     * 
     * @~chinese 
     * ��argΪ��������������functionId��Ӧ��Lua����ָ�롣
     * 
     * @param functionId @~english the reference id to the Lua function.
     * @~chinese Lua����������id��
     * @param arg @~english the string pointer point to the argument.
     * @~chinese ��Ϊ�����������ַ���ָ�롣
     * @return @~english a number value returned from the Lua function when call sucessfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN,LUA_ERRMEM and LUA_ERRERR.
     *
     * @~chinese ���óɹ�������Lua�����ķ���ֵ�����򣬷���-1��LUA_ERRRUN,LUA_ERRMEM LUA_ERRERR��������������һ�����෴����
     * 
     * @lua NA
     * @js NA
     */
    static int callLuaFunctionById(int functionId, const char *arg);

    /**@~english
     * Call a global Lua function named functionName with the string pointer arg.
     * 
     * @~chinese 
     * ��argΪ��������������һ������ΪfunctionName��Luaȫ�ֺ�����
     * 
     * @param functionName @~english the name of global function.
     * @~chinese ȫ�ֺ�������
     * @param arg @~english the string pointer point to the argument.
     * @~chinese ��Ϊ�����������ַ���ָ�롣
     * @return @~english a number value returned frome the Lua function when call sucessfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN,LUA_ERRMEM and LUA_ERRERR.
     *
     * @~chinese ���óɹ�������Lua�����ķ���ֵ�����򣬷���-1��LUA_ERRRUN,LUA_ERRMEM LUA_ERRERR��������������һ�����෴����
     * 
     * @lua NA
     * @js NA
     */
    static int callLuaGlobalFunction(const char *functionName, const char *arg);

private:
    typedef enum
    {
        TypeInvalid = -1,
        TypeVoid    = 0,
        TypeInteger = 1,
        TypeFloat   = 2,
        TypeBoolean = 3,
        TypeString  = 4,
        TypeVector  = 5,
        TypeFunction= 6,
    } ValueType;

    typedef vector<ValueType> ValueTypes;

    typedef union
    {
        int     intValue;
        float   floatValue;
        int     boolValue;
        string *stringValue;
    } ReturnValue;

    class CallInfo
    {
    public:
        CallInfo(const char *className, const char *methodName, const char *methodSig)
        : m_valid(false)
        , m_error(LUAJ_ERR_OK)
        , m_className(className)
        , m_methodName(methodName)
        , m_methodSig(methodSig)
        , m_returnType(TypeVoid)
        , m_argumentsCount(0)
        , m_retjs(NULL)
        , m_env(NULL)
        , m_classID(NULL)
        , m_methodID(NULL)
        {
            memset(&m_ret, 0, sizeof(m_ret));
        	m_valid = validateMethodSig() && getMethodInfo();
        }
    	~CallInfo(void);

        bool isValid(void) {
        	return m_valid;
        }

        int getErrorCode(void) {
        	return m_error;
        }

        JNIEnv *getEnv(void) {
        	return m_env;
        }

        int argumentTypeAtIndex(size_t index) {
        	return m_argumentsType.at(index);
        }

        bool execute(void);
        bool executeWithArgs(jvalue *args);
        int pushReturnValue(lua_State *L);


    private:
        bool 		m_valid;
        int 		m_error;

        string      m_className;
        string      m_methodName;
        string      m_methodSig;
        int         m_argumentsCount;
        ValueTypes  m_argumentsType;
        ValueType   m_returnType;

        ReturnValue m_ret;
        jstring     m_retjs;

        JNIEnv     *m_env;
        jclass      m_classID;
        jmethodID   m_methodID;

        bool validateMethodSig(void);
        bool getMethodInfo(void);
        ValueType checkType(const string& sig, size_t *pos);
    };

    static int callJavaStaticMethod(lua_State *L);
    static int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);
    static int getMethodInfo(CallInfo *call, const char *className, const char *methodName, const char *paramCode);
    static int fetchArrayElements(lua_State *L, int index);
    static int callAndPushReturnValue(lua_State *L, CallInfo *call, jvalue *args);

    static lua_State *s_luaState;
    static int        s_newFunctionId;
};

// end group
/// @}
#endif //COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H
