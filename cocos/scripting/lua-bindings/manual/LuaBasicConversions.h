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
#ifndef __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
#define __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__

extern "C" {
#include "lua.h"
#include "tolua++.h"
}
#include "tolua_fix.h"
#include "cocos2d.h"

using namespace cocos2d;

extern std::unordered_map<std::string, std::string>  g_luaType;
extern std::unordered_map<std::string, std::string>  g_typeCast;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName = "");
#endif

#define LUA_PRECONDITION( condition, ...) if( ! (condition) ) {														\
cocos2d::log("lua: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );                                                         \
cocos2d::log(__VA_ARGS__);                                                  \
}                                                                           \

/**
 * @addtogroup lua
 * @{
 */

/**@~english
 * If the typename of userdata at the given acceptable index of stack is equal to type it return true,otherwise return false .
 * If def != 0, lo could greater than the top index of stack, return value is true.
 * If the value of the given index is nil, return value also is true.
 *
 * @~chinese 
 * ��������Ϸ���Luaջ�����ϵ�userdata���������ֺ�typeһ������true,���򷵻�false��
 * ���def != 0,lo���ܴ���ָ��Luaջ������,���ҷ���ֵΪtrue��
 * �������Luaջ�����ϵ�ֵ��nil,����ֵҲΪtrue��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param type @~english the typename used to judge.
 * @~chinese �����жϵ��������֡�
 * @param def @~english whether has default value,0 means have not default value,otherwise have default values.
 * @~chinese �Ƿ���Ĭ��ֵ, 0��ʾû��Ĭ��ֵ��������Ĭ��ֵ��
 * @return @~english Return true if the typename of userdata at the given accepteable index of stack is equal to type, otherwise return false.
 * @~chinese ��������Ϸ���Luaջ������userdata���������ֵ���type,����lo����ջ����������Ĭ��ֵ������ջ�ϵ�ֵΪnil, ���᷵��true�����򷵻�false��
 */
extern bool luaval_is_usertype(lua_State* L,int lo,const char* type, int def);
// to native

/**
 * @name luaval_to_native
 * @brief @~english
 * The following function are all used to convert the Lua values at the given acceptable index to the corresponding c++ values.
 * If the Lua values can be converted the return value is true, otherwise return false.
 * If it happens error during the conversion process, it outputs the error msg in the console to provide information about the name of calling function, the typename of value at the given acceptable index, and so on.
 * @~chinese ���µĺ�������������ָ��Lua�����ϵ�Luaֵת�ɶ�Ӧ��c++ֵ��
 * ���Luaֵ���Ա�ת��������true,���򷵻�false.
 * �����ת�������з����˴��󣬽����ڿ���̨���������Ϣ��������Ϣ������˵��ú�����ָ��Lua����Luaֵ���������ֵ���Ϣ��
 @{
 **/


/**@~english
 * Get a unsigned long value from the given acceptable index of Lua stack.
 * If the value at the given acceptable index of Lua stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��unsigned londֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ����
 * @param outValue @~english the pointer to store the value converted from the Lua value.
 * @~chinese ָ��unsigned long��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_ulong(lua_State* L,int lo, unsigned long* outValue, const char* funcName="");

/**@~english
 * Get a unsigned short value from the given acceptable index of Lua stack.
 * If the value at the given acceptable index of Lua stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��unsigned shortֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the unsigned short value converted from the Lua value.
 * @~chinese ָ��unsigned shor��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue, const char* funcName = "");

/**@~english
 * Get a int value from the given acceptable index of Lua stack.
 * If the value at the given acceptable index of Lua stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��intֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of Lua stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the int value converted from the Lua value.
 * @~chinese ָ��int��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_int32(lua_State* L,int lo,int* outValue, const char* funcName = "");

/**@~english
 * Get a unsigned int value from the given acceptable index of Lua stack.
 * If the value at the given acceptable index of Lua stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��unsigned intֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of Lua stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the unsigned int value converted from the Lua value.
 * @~chinese ָ��unsigned int��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName = "");

/**@~english
 * Get a uint16_t value from the given acceptable index of Lua stack.
 * If the value at the given acceptable index of Lua stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��uint16_tֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of Lua stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the uint16_t value converted from the Lua value.
 * @~chinese ָ��uint16_t��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue, const char* funcName = "");

/**@~english
 * Get a boolean value from the given acceptable index of Lua stack.
 * If the value at the given acceptable index of Lua stack has type boolean it returns true, otherwise returns false.
 * Any Lua value is different from false or nil, the value of conversion is true, otherwise the value is false.
 * If the lo is non-valid index, the value of coversion also is false.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��booleanֵ��
 * �������Luaջ����ֵ����Ϊboolean����true,���򷵻�false��
 * �κβ�����false��nil��Luaֵ,��ȡ��ֵ��true������Ϊfalse��
 * ���lo����Ч������,��ȡ��ֵҲΪfalse��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of Lua stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the boolean value converted from the Lua value.
 * @~chinese ָ��boolean��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the type at the given acceptable index of stack is a boolean, otherwise return false.
 * @~chinese �������Luaջ������ֵ��������boolean����true,���򷵻�false��
 */
extern bool luaval_to_boolean(lua_State* L,int lo,bool* outValue, const char* funcName = "");

/**@~english
 * Get a double value from the given acceptable index of Lua stack.
 * If the value at the given acceptable index of Lua stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��doubleֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of Lua stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the double value converted from the Lua value.
 * @~chinese ָ��double��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_number(lua_State* L,int lo,double* outValue, const char* funcName = "");

/**@~english
 * Get a long long value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��long longֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the long long value converted from the Lua value.
 * @~chinese ָ��long long��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_long_long(lua_State* L,int lo,long long* outValue, const char* funcName = "");

/**@~english
 * Get a std::string value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a string or a number convertible to a string it returns true, otherwise returns false.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::stringֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ�ַ��������֣�����true�����򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store std::string value converted from the Lua value.
 * @~chinese ָ��std::string��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is is a string or a number convertible to a string, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ�ַ��������֣�����true�����򷵻�false��
 */
extern bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName = "");

/**@~english
 * Get a long value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��longֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the long value converted from the Lua value.
 * @~chinese ָ��long��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_long(lua_State* L,int lo, long* outValue, const char* funcName = "");

/**@~english
 * Get a ssize_t value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��ssize_tֵ��
 * �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to store the ssize_t value converted from the Lua value.
 * @~chinese ָ��ssize_t��ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a number or a string convertible to a number, otherwise return false.
 * @~chinese �������Luaջ��������һ�����ֻ�һ������תΪ���ֵ��ַ���,����true,���򷵻�false��
 */
extern bool luaval_to_ssize(lua_State* L,int lo, ssize_t* outValue, const char* funcName = "");

/**@~english
 * Get a Size object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `width` and `height` key and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Size����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table����"width"��"height"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Size�����Ӧ�ĳ�Ա���������򣬶�Ӧ�ĳ�Ա��������Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Size object which stores the values from the Lua table.
 * @~chinese ָ��Size�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_size(lua_State* L,int lo,Size* outValue, const char* funcName = "");

/**@~english
 * Get a Rect object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`,`y`,`width` and `height` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Rect����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table��"x"��"y"��"width"��"height"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Rect�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��ֵ����Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Rect object which stores the values from the Lua table.
 * @~chinese ָ��Rect�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_rect(lua_State* L,int lo,Rect* outValue, const char* funcName = "");

/**@~english
 * Get a Color3B object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `r`,`g` and `b` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Color3B����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table��"r"��"g"��"b"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Color3B�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��ֵ����Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Color3B object which stores the values from the Lua table.
 * @~chinese ָ��Color3B�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese  ���ú�������,����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_color3b(lua_State* L,int lo,Color3B* outValue, const char* funcName = "");

/**@~english
 * Get a Color4B object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `r`,`g`, `b` and 'a' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Color4B����
 * �������Luaջ��������һ��table������true�����򷵻�false��
 * ���table��"r"��"g"��"b"��"a"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Color4B�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��ֵ����Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Color4B object which stores the values from the Lua table.
 * @~chinese ָ��Color4B�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luaval_to_color4b(lua_State* L,int lo,Color4B* outValue, const char* funcName = "");

/**@~english
 * Get a Color4F object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `r`,`g`, `b` and 'a' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Color4F����
 * �������Luaջ��������һ��table������true�����򷵻�false��
 * ���table��"r"��"g"��"b"��"a"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Color4F�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��ֵ����Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Color4F object which stores the values from the Lua table.
 * @~chinese ָ��Color4F�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luaval_to_color4f(lua_State* L,int lo,Color4F* outValue, const char* funcName = "");
#if CC_USE_PHYSICS

/**@~english
 * Get a PhysicsMaterial object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `density`,`restitution` and 'friction' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��PhysicsMaterial����
 * �������Luaջ��������һ��table������true�����򷵻�false��
 * ���table�С�density��,��restitution���͡�friction�������Ҷ�Ӧ��ֵ��Ϊnil,��ô��Щֵ�ḳֵ��PhysicsMaterial�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��ֵ����Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a cocos2d::PhysicsMaterial object which stores the values from the Lua table.
 * @~chinese ָ��cocos2d::PhysicsMaterial�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luaval_to_physics_material(lua_State* L,int lo, cocos2d::PhysicsMaterial* outValue, const char* funcName = "");
#endif //#if CC_USE_PHYSICS

/**@~english
 * Get a AffineTransform object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `a`, `b`, `c`, `d` , `tx` and `ty` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��AffineTransform����
 * �������Luaջ��������һ��table������true�����򷵻�false��
 * ���table�С�a������b������c��,��d��,��tx���͡�ty�������Ҷ�Ӧ��ֵ��Ϊnil,��ô��Щֵ�ḳֵ��AffineTransform�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��ֵ����Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a AffineTransform object which stores the values from the Lua table.
 * @~chinese ָ��AffineTransform�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luaval_to_affinetransform(lua_State* L,int lo, AffineTransform* outValue, const char* funcName = "");

/**@~english
 * Get a FontDefinition object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `fontName`, `fontSize`, `fontAlignmentH`, `fontAlignmentV` , `fontFillColor` ,`fontDimensions`, `shadowEnabled` and `strokeEnabled` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 * If the values about `shadowEnabled` and `strokeEnabled` are true, there would be more keys such as `shadowOffset`, `shadowBlur` ,`shadowOpacity`, `strokeColor`, and `strokeSize`.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��FontDefinition����
 * �������Luaջ��������һ��table������true�����򷵻�false��
 * ���table���С�fontName��,��fontSize��,��fontAlignmentH��,��fontAlignmentV��,��fontFillColor��,��fontDimensions��,��shadowEnabled���͡�strokeEnabled�����Ҷ�Ӧ��ֵ��Ϊnil,��ô��Щֵ�ḳֵ��FontDefinition�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��ֵ����Ϊ0��
 * ���table�С�shadowEnabled���͡�strokeEnabled����Ӧ��ֵΪtrue,������Ҹ���ļ�����Ӧ��ֵ���确shadowOffset��,��shadowBlur��,��shadowOpacity��,��strokeColor��,��strokeSize����
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a FontDefinition object which stores the values from the Lua table.
 * @~chinese ָ��FontDefinition�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luaval_to_fontdefinition(lua_State* L, int lo, FontDefinition* outValue , const char* funcName = "");

/**@~english
 * Get a Mat object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * The table is array-table which begin the index starts at 1.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Mat����
 * �������Luaջ��������һ��table������true�����򷵻�false��
 * table��Ӧ����һ��array-table�����������Ǵ�1��ʼ��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Mat object which stores the values from the Lua table.
 * @~chinese ָ��Mat�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luaval_to_mat4(lua_State* L, int lo, cocos2d::Mat4* outValue , const char* funcName = "");

/**@~english
 * Get a __Array object value frome the given acceptable index of stack.
 * Because __Array is deprecated, so this function would be not called anymore.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��__Array����
 * ��Ϊ__Array�������ã������������Ҳ�������á�
 */
extern bool luaval_to_array(lua_State* L,int lo, __Array** outValue, const char* funcName = "");

/**@~english
 * Get a __Dictionary object value from the given acceptable index of stack.
 * Because __Dictionary is deprecated, so this function would be not called anymore.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��__Dictionary����
 * ��Ϊ__Dictionary�������ã������������Ҳ�������á�
 */
extern bool luaval_to_dictionary(lua_State* L,int lo, __Dictionary** outValue, const char* funcName = "");

/**@~english
 * Get a array of Vec2 object from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ������Vec2��������顣
 * �������Luaջ��������һ��table������true�����򷵻�false��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param points @~english the pointer to a array of Vec2 object which stores the values from the Lua table.
 * @~chinese ָ�򴢴�Vec2���������ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param numPoints @~english a int pointer to store the size of a Vec2 object array.
 * @~chinese ָ�������С��intָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luaval_to_array_of_vec2(lua_State* L,int lo,cocos2d::Vec2 **points, int *numPoints, const char* funcName = "");

/**@~english
 * Get a __Array object value by the argc numbers of Lua values in the stack.
 * Because __Array is deprecated, so this function would be not called anymore.
 * @~chinese 
 * ��Luaջ�л�ȡargc������������һ��__Array����
 * ��Ϊ__Array�������ã������������Ҳ�������á�
 */
extern bool luavals_variadic_to_array(lua_State* L,int argc, __Array** ret);

/**@~english
 * Get a cocos2d::ValueVector object value by the argc numbers of Lua values in the stack.
 *
 * @~chinese 
 * ��Luaջ�л�ȡarc��Lua values������һ��cocos2d::ValueVector����
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param argc @~english the numbers of Lua values in the stack.
 * @~chinese Luaջ������
 * @param ret @~english the pointer to a ValueVector object which stores the values from the Lua table.
 * @~chinese ָ�򴢴�Luaֵ��ValueVector����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @return @~english Return false if argc equal to 0 or L equal to nullptr, otherwise return true.
 * @~chinese �������Luaջ��������һ��table������true�����򷵻�false��
 */
extern bool luavals_variadic_to_ccvaluevector(lua_State* L, int argc, cocos2d::ValueVector* ret);

/**@~english
 * Get a Vec2 object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`,and 'y' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Vec2����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table����"x"��"y"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Vec2�����Ӧ�ĳ�Ա���������򣬶�Ӧ�ĳ�Ա��������Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Vec2 object which stores the values from the Lua table.
 * @~chinese ָ��Vec2�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_vec2(lua_State* L,int lo,cocos2d::Vec2* outValue, const char* funcName = "");

/**@~english
 * Get a Vec3 object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, 'y' and `z` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Vec3����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table����"x","y"��"z"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Vec3�����Ӧ�ĳ�Ա���������򣬶�Ӧ�ĳ�Ա��������Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese Ŀǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Vec3 object which stores the values from the Lua table.
 * @~chinese ָ��Vec3�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_vec3(lua_State* L,int lo,cocos2d::Vec3* outValue, const char* funcName = "");

/**@~english
 * Get a Vec4 object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, 'y', `z` and `w` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Vec4����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table����"x"��"y"��"z"��"w"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��Vec4�����Ӧ�ĳ�Ա���������򣬶�Ӧ�ĳ�Ա��������Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Vec4 object which stores the values from the Lua table.
 * @~chinese ָ��Vec4�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_vec4(lua_State* L,int lo,cocos2d::Vec4* outValue, const char* funcName = "");

/**@~english
 * Get a BlendFunc object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `src` and 'dst' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��BlendFunc����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table����"src"��"dst"�����Ҷ�Ӧ��ֵ��Ϊnil����ô��Щֵ�ḳֵ��BlendFunc�����Ӧ�ĳ�Ա���������򣬶�Ӧ�ĳ�Ա��������Ϊ0��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a BlendFunc object which stores the values from the Lua table.
 * @~chinese ָ��BlendFunc�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_blendfunc(lua_State* L, int lo, cocos2d::BlendFunc* outValue, const char* funcName = "");

/**@~english
 * Get a TTFConfig object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `fontFilePath`, `fontSize`, `glyphs`, `customGlyphs`, `distanceFieldEnabled` and 'outlineSize' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be given the default value.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��BlendFunc����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table���С�fontFilePath��,��fontSize������glyphs��,��customGlyphs��,��distanceFieldEnabled���͡�outlineSize�����Ҷ�Ӧ��ֵ����nil,��ô��Щֵ�ḳֵ��TTFConfig�����Ӧ�ĳ�Ա����������,�м�ֵ�ĳ�Ա�ļ�ֵ��������Ĭ��ֵ��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a TTFConfig object which stores the values from the Lua table.
 * @~chinese ָ��TTFConfig�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_ttfconfig(lua_State* L, int lo, cocos2d::TTFConfig* outValue, const char* funcName = "");

/**@~english
 * Get a Uniform object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `location`, `size`, `type` and `name` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be given the default value.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Uniform����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table���С�location��,��size��,��type���͡�name���������Ҷ�Ӧ��ֵ����nil,��ô��Щֵ�ḳֵ��Uniform�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��������������Ĭ��ֵ��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a Uniform object which stores the values from the Lua table.
 * @~chinese ָ��Uniform�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_uniform(lua_State* L, int lo, cocos2d::Uniform* outValue, const char* funcName = "");

/**@~english
 * Get a VertexAttrib object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `index`, `size`, `type` and `name` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be given the default value.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��VertexAttrib����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table���С�index��,��size��,��type���͡�name���������Ҷ�Ӧ��ֵ����nil,��ô��Щֵ�ḳֵ��VertexAttrib�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��������������Ĭ��ֵ��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a VertexAttrib object which stores the values from the Lua table.
 * @~chinese ָ��VertexAttrib�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_vertexattrib(lua_State* L, int lo, cocos2d::VertexAttrib* outValue, const char* funcName = "");


/**@~english
 * Get a Vec2 object value from the given acceptable index of stack.
 * At current, the Point is typedef of Vec2.@see luaval_to_vec2
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Vec2����@see luaval_to_vec2��
 */
static inline bool luaval_to_point(lua_State* L,int lo,cocos2d::Vec2* outValue, const char* funcName = "")
{
    return luaval_to_vec2(L, lo, outValue);
}

CC_DEPRECATED_ATTRIBUTE static inline bool luaval_to_kmMat4(lua_State* L, int lo, cocos2d::Mat4* outValue , const char* funcName = "")
{
    return luaval_to_mat4(L, lo, outValue);
}
CC_DEPRECATED_ATTRIBUTE static inline bool luaval_to_array_of_Point(lua_State* L,int lo,cocos2d::Vec2 **points, int *numPoints, const char* funcName = "")
{
    return luaval_to_array_of_vec2(L, lo, points, numPoints);
}

/**@~english
 * Get a cocos2d::Vector of type T objects by the argc numbers of Lua values in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�ϻ�ȡһ������argc��type T�����cocos2d::Vector��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param argc @~english the numbers of Lua values in the stack.
 * @~chinese Luaջ������
 * @param ret @~english a cocos2d::Vector of type T objects.
 * @~chinese ָ��cocos2d::Vector�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @return @~english Return false if argc equal to 0 , L equal to nullptr or the Lua userdata at the index isn't `cc.Ref` type, otherwise return true.
 * @~chinese ��argc����0��LΪnullptr����Luaջ�����ϵ�userdata����"cc.Ref"���ͣ�����ֵΪfalse,���򷵻�true��
 */
template <class T>
bool luavals_variadic_to_ccvector( lua_State* L, int argc, cocos2d::Vector<T>* ret)
{
    if (nullptr == L || argc == 0 )
        return false;
    
    bool ok = true;
    
    for (int i = 0; i < argc; i++)
    {
        if (lua_isuserdata(L, i + 2))
        {
            tolua_Error err;
            
            if (!tolua_isusertype(L, i + 2, "cc.Ref", 0, &err))
            {
                ok = false;
                break;
            }
            T obj = static_cast<T>(tolua_tousertype(L, i + 2, nullptr));
            ret->pushBack(obj);
        }
    }
    
    return ok;
}


/**@~english
 * Get a cocos2d::Vector of type T objects from a Lua table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��type T��cocos2d::Vector����
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a cocos2d::Vector of type T objects.
 * @~chinese ָ��cocos2d::Vector�����ָ��,���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��tableʱ����true,���򷵻�false��
 */
template <class T>
bool luaval_to_ccvector(lua_State* L, int lo , cocos2d::Vector<T>* ret, const char* funcName = "")
{
    if (nullptr == L || nullptr == ret)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
        ok = false;
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            
            if (lua_isnil(L, -1) || !lua_isuserdata(L, -1))
            {
                lua_pop(L, 1);
                continue;
            }
            

            T cobj = static_cast<T>(tolua_tousertype(L, -1, NULL) );
            if (NULL != cobj)
                ret->pushBack(cobj);
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

/**@~english
 * Get a pointer points to a std::vector<std::string> from a Lua array table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::vector<std::string>
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a std::vector<std::string>.
 * @~chinese ָ��std::vector<std::string>��ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��tableʱ����true,���򷵻�false��
 */
bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret, const char* funcName = "");

/**@~english
 * Get a pointer points to a std::vector<int> from a Lua array table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::vector<int>
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a std::vector<int>.
 * @~chinese ָ��std::vector<int>��ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��tableʱ����true,���򷵻�false��
 */
bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName = "");


/**@~english
 * Get a pointer points to a cocos2d::Map whose key/value pair is string value and T object from a Lua hash-map table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::Map<std::string, T>
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a cocos2d::Map whose key/value pair is string value and T object.
 * @~chinese ָ��cocos2d::Map<std::string, T>��ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��tableʱ����true,���򷵻�false��
 */
template <class T>
bool luaval_to_ccmap_string_key(lua_State* L, int lo, cocos2d::Map<std::string, T>* ret, const char* funcName = "")
{
    if(nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        std::string stringKey = "";
        lua_pushnil(L);                                             /* first key L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }
            
            if (lua_isnil(L, -1) || !lua_isuserdata(L, -1))
            {
                lua_pop(L, 1);
                continue;
            }
            
            luaval_to_std_string(L, -2, &stringKey);
            T obj = static_cast<T>(tolua_tousertype(L, -1, NULL) );
            if (nullptr != obj)
                ret->insert(stringKey, obj);
                
            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
    }
    
    return ok;
}

/**@~english
 * Get a cocos2d::Value object from the given acceptable index of stack.
 * The type of Lua value at the index could be a Lua table, LUA_TSTRING, LUA_TBOOLEAN or LUA_TNUMBER.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::Value����
 * ����Luaջ�����ϵ����Ϳ�����table,LUA_TSTRING,LUA_TBOOLEAN����LUA_TNUMBER��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a cocos2d::Value object.
 * @~chinese ָ��һ��cocos2d::Value�����ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the L and ret is not nullptr,otherwise return false.
 * @~chinese ���L��ret����nullptr����true,���򷵻�false��
 */
extern bool luaval_to_ccvalue(lua_State* L, int lo, cocos2d::Value* ret, const char* funcName = "");

/**@~english
 * Get a cocos2d::ValueMap object from the given acceptable index of stack.
 * The type of Lua value at the index should be a Lua table.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::ValueMap����
 * ����Luaջ�����ϵ�Ӧ����һ��table��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a cocos2d::ValueMap object.
 * @~chinese ָ��cocos2d:ValueMap�����ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��tableʱ����true,���򷵻�false��
 */
extern bool luaval_to_ccvaluemap(lua_State* L, int lo, cocos2d::ValueMap* ret, const char* funcName = "");

/**@~english
 * Get a cocos2d::ValueMapIntKey object from the given acceptable index of stack.
 * The type of Lua value at the index should be a Lua table.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::ValueMapIntKey����
 * ����Luaջ�����ϵ�Ӧ����һ��table
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a cocos2d::ValueMapIntKey object.
 * @~chinese ָ��cocos2d::ValueMapIntKey�����ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��tableʱ����true,���򷵻�false��
 */
extern bool luaval_to_ccvaluemapintkey(lua_State* L, int lo, cocos2d::ValueMapIntKey* ret, const char* funcName = "");

/**@~english
 * Get a cocos2d::ValueVector object from the given acceptable index of stack.
 * The type of Lua value at the index should be a Lua array table.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::ValueVector����
 * ����Luaջ�����ϵ�Ӧ����һ��table
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a cocos2d::ValueVector object.
 * @~chinese ָ��cocos2d::ValueVector�����ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��tableʱ����true,���򷵻�false��
 */
extern bool luaval_to_ccvaluevector(lua_State* L, int lo, cocos2d::ValueVector* ret, const char* funcName = "");


/**@~english
 * Get a Type T object from the given acceptable index of stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��Type T����
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param type @~english a string pointer points to the type name.
 * @~chinese ��������
 * @param ret @~english the pointer points to a Type T object.
 * @~chinese ָ��type T���͵�ָ�롣
 * @return @~english Return true if the type of Lua value at the index is a Lua userdata, otherwise return false.
 * @~chinese ��Luaջ�����ϵ�ֵ��һ��Lua userdata����true�����򷵻�false��
 */
template <class T>
bool luaval_to_object(lua_State* L, int lo, const char* type, T** ret, const char* funcName = "")
{
    if(nullptr == L || lua_gettop(L) < lo)
        return false;
    
    if (!luaval_is_usertype(L, lo, type, 0))
        return false;
    
    *ret = static_cast<T*>(tolua_tousertype(L, lo, 0));
    
    if (nullptr == *ret)
        CCLOG("Warning: %s argument %d is invalid native object(nullptr)", funcName, lo);
    
    return true;
}

/**@~english
 * Get a cocos2d::MeshVertexAttrib object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `size`, `type`, `vertexAttrib`, `vertexAttrib` and `attribSizeBytes` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::MeshVertexAttrib����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table�С�size������type������vertexAttrib��,��vertexAttrib���͡�attribSizeBytes����,���Ҷ�Ӧ��ֵ����nil,��ô��Щֵ�ḳֵ��VertexAttrib�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��������������Ĭ��ֵ��
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english the pointer to a cocos2d::MeshVertexAttrib object which stores the values from the Lua table.
 * @~chinese ָ��cocos2d:MeshVertexAttrib�����ָ�룬���ڴ����Lua�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_mesh_vertex_attrib(lua_State* L, int lo, cocos2d::MeshVertexAttrib* ret, const char* funcName = "");

/**@~english
 * Get a pointer points to a std::vector<float> from a Lua array table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::vector<float>��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a std::vector<float>.
 * @~chinese ָ��std::vector<float>��ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName = "");

/**@~english
 * Get a pointer points to a std::vector<unsigned shortt> from a Lua array table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::vector<unsigned short>��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a std::vector<unsigned short>.
 * @~chinese ָ��std::vector<unsigned short>��ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_std_vector_ushort(lua_State* L, int lo, std::vector<unsigned short>* ret, const char* funcName = "");

/**@~english
 * Get a cocos2d::Quaternion object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, `y`, `z` and `w` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.Otherwise, the value of members of outValue would be 0.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::Quaternion����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table�С�x��,��y������z���͡�w�����棬������Ӧ��ֵ��Ϊ��,��ô��Щֵ�ḳֵ��cocos2d::Quaternion�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��������������Ĭ��ֵ��
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a cocos2d::Quaternion object which stores the values from the Lua table.
 * @~chinese ָ��cocos2d::Quaternion�����ָ�룬���ڴ����Lua��ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_quaternion(lua_State* L,int lo,cocos2d::Quaternion* outValue, const char* funcName = "");

/**@~english
 * Get a cocos2d::Texture2D::TexParams object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `minFilter`, `magFilter`, `wrapS` and `wrapT` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.Otherwise, the value of members of outValue would be 0.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::Texture2D::TexParams����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table�С�minFilter��,��magFilter��,��wrapS���͡�wrapT���������Ҷ�Ӧ��ֵ����nil,��ô��Щֵ�ḳֵ��cocos2d::Texture2D::TexParams�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��������������Ĭ��ֵ��
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a cocos2d::Quaternion object which stores the values from the Lua table.
 * @~chinese ָ��cocos2d::Texture2D::TexParams�Ķ���ָ�룬���ڴ洢��Lua��ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_texparams(lua_State* L,int lo,cocos2d::Texture2D::TexParams* outValue, const char* funcName = "");

/**@~english
 * Get a cocos2d::V3F_C4B_T2F object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `vertices`, `colors`, and `texCoords` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::V3F_C4B_T2F����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table���С�vertices��,��colors��,�͡�texCoords�������Ҷ�Ӧ��ֵ����nil,��ô��Щֵ�ḳֵ��cocos2d::V3F_C4B_T2F�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��������������Ĭ��ֵ��
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a cocos2d::V3F_C4B_T2F object which stores the values from the Lua table.
 * @~chinese ָ��cocos2d:V3F_C4B_T2F�����ָ�룬���ڴ�����Lua table�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_v3f_c4b_t2f(lua_State* L,int lo,cocos2d::V3F_C4B_T2F* outValue, const char* funcName = "");


/**@~english
 * Get a cocos2d::Tex2F object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `u`, and `v` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.Otherwise, the value of members of outValue would be 0.
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��cocos2d::Tex2F����
 * �������Luaջ��������һ��table,����true,���򷵻�false��
 * ���table���С�u���͡�v�������Ҷ�Ӧ��ֵ����nil,��ô��Щֵ�ḳֵ��cocos2d::Tex2FF�����Ӧ�ĳ�Ա����������,��Ӧ�ĳ�Ա��������Ĭ�ϸ�Ϊ0��
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param outValue @~english the pointer to a cocos2d::Tex2F object which stores the values from the Lua table.
 * @~chinese ָ��cocos2d:Tex2F�����ָ�룬���ڴ洢��Lua table�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_tex2f(lua_State* L, int lo, cocos2d::Tex2F* outValue, const char* funcName = "");

/**@~english
 * Get a pointer points to a std::vector<cocos2d::V3F_C4B_T2F> from a Lua array table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::vector<cocos2d::V3F_C4B_T2F>
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a std::vector<cocos2d::V3F_C4B_T2F>.
 * @~chinese ָ��std::vector<cocos2d::V3F_C4B_T2F>��ָ�룬���ڴ����Lua table�л�ȡ��ֵ��
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_std_vector_v3f_c4b_t2f(lua_State* L, int lo, std::vector<cocos2d::V3F_C4B_T2F>* ret, const char* funcName = "");

/**@~english
 * Get a pointer points to a std::vector<cocos2d::Vec2> from a Lua array table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::vector<cocos2d::cocos2d::Vec2>��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a std::vector<cocos2d::Vec2>.
 * @~chinese ָ��std::vector<cocos2d::Vec2>��ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_std_vector_vec2(lua_State* L, int lo, std::vector<cocos2d::Vec2>* ret, const char* funcName = "");

/**@~english
 * Get a pointer points to a std::vector<cocos2d::Vec3> from a Lua array table in the stack.
 *
 * @~chinese 
 * �Ӹ���Luaջ�����ϻ�ȡһ��std::vector<cocos2d::Vec3>��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Luaջ������
 * @param ret @~english a pointer points to a std::vector<cocos2d::Vec3>.
 * @~chinese ָ��std::vector<cocos2d::Vec3>��ָ�롣
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese ���ú������֣�����ģʽ�´�����Ϣ��������õ�����������֡�
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese �������Luaջ��������һ��table,����true,���򷵻�false��
 */
extern bool luaval_to_std_vector_vec3(lua_State* L, int lo, std::vector<cocos2d::Vec3>* ret, const char* funcName = "");

extern bool luaval_to_std_map_string_string(lua_State* L, int lo, std::map<std::string, std::string>* ret, const char* funcName);

/**@}**/

// from native

/**
 * @name native_to_luaval
 * @~english The following function are all used to convert native c++ values to the the corresponding Lua values,then push it into the Lua stack.
 * @~chinese ���º����������ڽ�native c++��ֵת���ɶ�ӦLua��ʹ�õ�ֵ������ת�����ֵ����ѹ�뵽Luaջ��
 * @{
 **/

/**@~english
 * Push a table converted from a cocos2d::Vec2 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2}
 *
 * @~chinese 
 * ��һ��cocos2d::Vec2����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{ x = numberValue1,y = numberValue2 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param vec2  @~english a cocos2d::Vec2 object.
 * @~chinese cocos2d::Vec2����
 */
extern void vec2_to_luaval(lua_State* L,const cocos2d::Vec2& vec2);

/**@~english
 * Push a table converted from a cocos2d::Vec3 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3}
 *
 * @~chinese 
 * ��һ��cocos2d::Vec2����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{ x = numberValue1,y = numberValue2,z = numberValue3 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param vec3  @~english a cocos2d::Vec3 object.
 * @~chinese cocos2d::Vec3����
 */
extern void vec3_to_luaval(lua_State* L,const cocos2d::Vec3& vec3);

/**@~english
 * Push a table converted from a cocos2d::Vec4 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3, w=numberValue4}
 *
 * @~chinese 
 * ��һ��cocos2d::Vec4����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{ x = numberValue1,y = numberValue2,z = numberValue3,w = numberValue4 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param vec4  @~english a cocos2d::Vec4 object.
 * @~chinese cocos2d::Vec4����
 */
extern void vec4_to_luaval(lua_State* L,const cocos2d::Vec4& vec4);

/**@~english
 * Push a table converted from a cocos2d::Vec2 array into the Lua stack.
 * The table size is count.
 * The format of table as follows: {vec2_table1,vec2_table2,...,vec2_tableCount}.
 *
 * @~chinese 
 * ��һ��cocos2d::Vec2������ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�Ĵ�СΪcount��
 * ��ĸ�ʽ����:{ vec2_table1 vec2_table2,��,vec2_tableCount }��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param points @~english a pointer points to a cocos2d::Vec2 array.
 * @~chinese ָ��cocos2d:Vec2������ָ�롣
 * @param count @~english the number of cocos2d::Vec2 object should be converted to a Lua table.
 * @~chinese ��Ҫ��ת����Lua table�е�cocos2d::Vec2������
 */
extern void vec2_array_to_luaval(lua_State* L,const cocos2d::Vec2* points, int count);

/**@~english
 * Push a table converted from a cocos2d::Size object into the Lua stack.
 * The format of table as follows: {width=numberValue1, height=numberValue2}
 *
 * @~chinese 
 * ��һ��cocos2d::Size����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{ width= numberValue1, height = numberValue2}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param sz  @~english a cocos2d::Size object.
 * @~chinese cocos2d::Size����
 */
extern void size_to_luaval(lua_State* L,const Size& sz);

/**@~english
 * Push a table converted from a cocos2d::Rect object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, width=numberValue3, height=numberValue4}
 *
 * @~chinese 
 * ��һ��cocos2d::Rec����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{x=numberValue1,y=numberValue2, width=numberValue3, height=numberValue4}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param rt  @~english a cocos2d::Rect object.
 * @~chinese cocos2d::Rect����
 */
extern void rect_to_luaval(lua_State* L,const Rect& rt);

/**@~english
 * Push a table converted from a cocos2d::Color3B object into the Lua stack.
 * The format of table as follows: {r=numberValue1, g=numberValue2, b=numberValue3}
 *
 * @~chinese 
 * ��һ��cocos2d::Color3B����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{ r = numberValue1,g = numberValue2,b = numberValue3 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param cc  @~english a cocos2d::Color3B object.
 * @~chinese cocos2d::Color3B����
 */
extern void color3b_to_luaval(lua_State* L,const Color3B& cc);

/**@~english
 * Push a table converted from a cocos2d::Color4B object into the Lua stack.
 * The format of table as follows: {r=numberValue1, g=numberValue2, b=numberValue3, a=numberValue4}
 *
 * @~chinese 
 * ��һ��cocos2d::Color4B����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{r=numberValue1,g=numberValue2,b=numberValue3, a=numberValue4}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param cc @~english a cocos2d::Color4B object.
 * @~chinese cocos2d::Color4B����
 */
extern void color4b_to_luaval(lua_State* L,const Color4B& cc);

/**@~english
 * Push a table converted from a cocos2d::Color4F object into the Lua stack.
 * The format of table as follows: {r=numberValue1, g=numberValue2, b=numberValue3, a=numberValue4}
 *
 * @~chinese 
 * ��һ��cocos2d::Color4F����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{ r=numberValue1,g=numberValue2,b=numberValue3,a=numberValue4 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param cc @~english a cocos2d::Color4F object.
 * @~chinese cocos2d::Color4F����
 */
extern void color4f_to_luaval(lua_State* L,const Color4F& cc);
#if CC_USE_PHYSICS

/**@~english
 * Push a table converted from a cocos2d::PhysicsMaterial object into the Lua stack.
 * The format of table as follows: {density=numberValue1, restitution=numberValue2, friction=numberValue3}
 *
 * @~chinese 
 * ��һ��cocos2d::PhysicsMaterial����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{density=numberValue1, restitution=numberValue2, friction=numberValue3 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param pm @~english a cocos2d::PhysicsMaterial object.
 * @~chinese cocos2d::PhysicsMaterial����
 */
extern void physics_material_to_luaval(lua_State* L,const PhysicsMaterial& pm);

/**@~english
 * Push a table converted from a cocos2d::PhysicsRayCastInfo object into the Lua stack.
 * The format of table as follows: {shape=userdata, start=vec2_table1, ended=vec2_table2, contact=vec2_table3, normal=vec2_table4, fraction=numberValue}
 *
 * @~chinese 
 * ��һ��cocos2d::PhysicsRayCastInfo����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{shape=userdata,start=vec2_table1, ended=vec2_table2, contact=vec2_table3, normal=vec2_table4, fraction=numberValue}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param info @~english a cocos2d::PhysicsRayCastInfo object.
 * @~chinese cocos2d::PhysicsRayCastInfo����
 */
extern void physics_raycastinfo_to_luaval(lua_State* L, const PhysicsRayCastInfo& info);

/**@~english
 * Push a table converted from a cocos2d::PhysicsContactData object into the Lua stack.
 * The format of table as follows: {points=vec2_array_table, normal=vec2_table, POINT_MAX=numberValue}
 *
 * @~chinese 
 * ��һ��cocos2d::PhysicsContactData����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * ��ĸ�ʽ����:{points=vec2_array_table, normal=vec2_table, POINT_MAX=numberValue}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param data @~english a cocos2d::PhysicsContactData object.
 * @~chinese cocos2d::PhysicsContactData����
 */
extern void physics_contactdata_to_luaval(lua_State* L, const PhysicsContactData* data);
#endif //#if CC_USE_PHYSICS

/**@~english
 * Push a table converted from a cocos2d::AffineTransform object into the Lua stack.
 * The format of table as follows: {a=numberValue1, b=numberValue2, c=numberValue3, d=numberValue4,tx=numberValue5, ty=numberValue6}
 *
 * @~chinese 
 * ��һ��cocos2d::AffineTransform����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{a=numberValue1, b=numberValue2, c=numberValue3, d=numberValue4,tx=numberValue5, ty=numberValue6}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::AffineTransform object.
 * @~chinese cocos2d::AffineTransform����
 */
extern void affinetransform_to_luaval(lua_State* L,const AffineTransform& inValue);

/**@~english
 * Push a table converted from a cocos2d::FontDefinition object into the Lua stack.
 * The format of table as follows: {fontName=stringValue1, fontSize=numberValue1, fontAlignmentH=numberValue2, fontAlignmentV=numberValue3,fontFillColor=color3b_table1, fontDimensions=size_table1, shadowEnabled=booleanValue1, shadowOffset=size_table2, shadowBlur=numberValue4, shadowOpacity=numberValue5, shadowEnabled=booleanValue2, strokeColor=color3b_table2, strokeSize=size_table3}
 *
 * @~chinese 
 * ��һ��cocos2d::FontDefinition����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{{fontName=stringValue1, fontSize=numberValue1, fontAlignmentH=numberValue2, fontAlignmentV=numberValue3,fontFillColor=color3b_table1, fontDimensions=size_table1, shadowEnabled=booleanValue1, shadowOffset=size_table2, shadowBlur=numberValue4, shadowOpacity=numberValue5, shadowEnabled=booleanValue2, strokeColor=color3b_table2, strokeSize=size_table3}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::FontDefinition object.
 * @~chinese cocos2d::FontDefinition����
 */
extern void fontdefinition_to_luaval(lua_State* L,const FontDefinition& inValue);

extern void array_to_luaval(lua_State* L, __Array* inValue);
extern void dictionary_to_luaval(lua_State* L, __Dictionary* dict);


/**@~english
 * Push a table converted from a cocos2d::Mat4 object into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberValue16}
 *
 * @~chinese 
 * ��һ��cocos2d::Mat4����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * ��ĸ�ʽ����:{ numberValue1,numberValue2,��,numberValue16 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param mat @~english a cocos2d::Mat4 object.
 * @~chinese cocos2d::Mat4����
 */
extern void mat4_to_luaval(lua_State* L, const cocos2d::Mat4& mat);

/**@~english
 * Push a table converted from a cocos2d::BlendFunc object into the Lua stack.
 * The format of table as follows: {src=numberValue1, dst=numberValue2}
 *
 * @~chinese 
 * ��һ��cocos2d::BlendFunc����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{ src=numberValue1,dst=numberValue2 }
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param func @~english a cocos2d::BlendFunc object.
 * @~chinese cocos2d::BlendFunc����
 */
extern void blendfunc_to_luaval(lua_State* L, const cocos2d::BlendFunc& func);

/**@~english
 * Push a table converted from a cocos2d::TTFConfig object into the Lua stack.
 * The format of table as follows: {fontFilePath=stringValue1, fontSize=numberValue1, glyphs=numberValue2, customGlyphs=stringValue2,distanceFieldEnabled=booleanValue1, outlineSize=numberValue3}
 *
 * @~chinese 
 * ��һ��cocos2d::TTFConfig����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{fontFilePath=stringValue1, fontSize=numberValue1, glyphs=numberValue2, customGlyphs=stringValue2,distanceFieldEnabled=booleanValue1, outlineSize=numberValue3}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param config @~english a cocos2d::TTFConfig object.
 * @~chinese cocos2d::TTFConfig����
 */
extern void ttfconfig_to_luaval(lua_State* L, const cocos2d::TTFConfig& config);

/**@~english
 * Push a table converted from a cocos2d::Uniform object into the Lua stack.
 * The format of table as follows: {location=numberValue1, size=numberValue2, type=numberValue3, name=stringValue1}
 *
 * @~chinese 
 * ��һ��cocos2d::Uniform����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{location=numberValue1, size=numberValue2, type=numberValue3, name=stringValue1}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param uniform @~english a cocos2d::Uniform object.
 * @~chinese cocos2d::Uniform����
 */
extern void uniform_to_luaval(lua_State* L, const cocos2d::Uniform& uniform);

/**@~english
 * Push a table converted from a cocos2d::VertexAttrib object into the Lua stack.
 * The format of table as follows: {index=numberValue1, size=numberValue2, type=numberValue3, name=stringValue1}
 *
 * @~chinese 
 * ��һ��cocos2d::VertexAttrib����ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{index=numberValue1, size=numberValue2, type=numberValue3, name=stringValue1}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param verAttrib @~english a cocos2d::VertexAttrib object.
 * @~chinese cocos2d::VertexAttrib����
 */
extern void vertexattrib_to_luaval(lua_State* L, const cocos2d::VertexAttrib& verAttrib);


static inline void point_to_luaval(lua_State* L,const cocos2d::Vec2& pt)
{
    vec2_to_luaval(L, pt);
}


CC_DEPRECATED_ATTRIBUTE static inline void points_to_luaval(lua_State* L,const cocos2d::Vec2* points, int count)
{
    vec2_array_to_luaval(L, points, count);
}

/**@~english
 * Push a table converted from a cocos2d::Vector object into the Lua stack.
 * The format of table as follows: {userdata1, userdata2, ..., userdataVectorSize}
 * The object in the cocos2d::Vector which would be pushed into the table should be Ref type.
 *
 * @~chinese 
 * ��һ��cocos2d::Vector<T>ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����: {userdata1, userdata2,... UserdataVectorSize},
 * cocos2d:Vector�е�Type T������Ҫ��Ref���͡�
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::Vector object.
 * @~chinese cocos2d::Vector<T>����
 */
template <class T>
void ccvector_to_luaval(lua_State* L,const cocos2d::Vector<T>& inValue)
{
    lua_newtable(L);
    
    if (nullptr == L)
        return;
    
    int indexTable = 1;
    for (const auto& obj : inValue)
    {
        if (nullptr == obj)
            continue;
        

        if (nullptr != dynamic_cast<cocos2d::Ref *>(obj))
        {
            std::string typeName = typeid(*obj).name();
            auto iter = g_luaType.find(typeName);
            if (g_luaType.end() != iter)
            {
                lua_pushnumber(L, (lua_Number)indexTable);
                int ID = (obj) ? (int)obj->_ID : -1;
                int* luaID = (obj) ? &obj->_luaID : NULL;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)obj,iter->second.c_str());
                lua_rawset(L, -3);
                ++indexTable;
            }
        }
    }
}

/**@~english
 * Push a table converted from a cocos2d::Map object into the Lua stack.
 * The format of table as follows: {name1=userdata1, name2=userdata2, ..., nameMapSize=userdataMapSize}
 * The object in the cocos2d::Map which would be pushed into the table should be Ref type.
 *
 * @~chinese 
 * ��һ��cocos2d::Map<std::string, T>ת����Lua table,Ȼ����ѹ��Luaջ�С�
 * table�ĸ�ʽ����:{name1=userdata1, name2=userdata2, ..., nameMapSize=userdataMapSize}
 * cocos2d::Map�е�Type T������ҪΪRef���͡�
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param v @~english a cocos2d::Map object.
 * @~chinese cocos2d::Map<std::string, T>����
 */
template <class T>
void ccmap_string_key_to_luaval(lua_State* L, const cocos2d::Map<std::string, T>& v)
{
    lua_newtable(L);
    
    if(nullptr == L)
        return;
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        std::string key = iter->first;
        T obj = iter->second;
        if (nullptr != dynamic_cast<cocos2d::Ref *>(obj))
        {
            std::string name = typeid(*obj).name();
            auto typeIter = g_luaType.find(name);
            if (g_luaType.end() != typeIter)
            {
                lua_pushstring(L, key.c_str());
                int ID = (obj) ? (int)obj->_ID : -1;
                int* luaID = (obj) ? &obj->_luaID : NULL;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)obj,typeIter->second.c_str());
                lua_rawset(L, -3);
            }
        }
    }
}

/**@~english
 * Push a Lua value converted from a cocos2d::Value object into the Lua stack.
 * Different cocos2d::Value type, different Lua value pushed into the Lua stack.
 * Value::Type::BOOLEAN -> push a boolean value into the Lua stack.
 * Value::Type::FLOAT,Value::Type::DOUBLE -> push a lua_Number value into the Lua stack.
 * Value::Type::INTEGER -> push a integer value into the Lua stack.
 * Value::Type::STRING -> push a string value into the Lua stack.
 * Value::Type::VECTOR -> push a array table into the Lua stack.
 * Value::Type::MAP  -> push a hash table into the Lua stack.
 * Value::Type::INT_KEY_MAP -> push a hash table into the Lua stack.
 *
 * @~chinese 
 * ��һ��cocos2d::Value����ת���ɶ�Ӧ��Luaֵѹ��Luaջ�С�
 * cocos2d::Value�����Ͳ�ͬ��ѹ��Luaջ��LuaֵҲ��һͬ��
 * Value::Type::BOOLEAN -> ��һ��boolֵѹ��Luaջ��
 * Value::Type::FLOAT -> ��һ��lua_Numberֵѹ��Luaջ��
 * Value::Type::INTEGER -> ��һ��integerֵѹ��Luaջ��
 * Value::Type::STRING -> ��һ���ַ���ѹ��Luaջ��
 * Value::Type::VECTOR -> ��һ������tableѹ��Luaջ��
 * Value::Type::MAP -> ��һ��hash-tableѹ��Luaջ��
 * Value::Type::INT_KEY_MAP -> ��һ��hash-tableѹ��Luaջ��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::Value object.
 * @~chinese ccocos2d::Value����
 */
void ccvalue_to_luaval(lua_State* L,const cocos2d::Value& inValue);

/**@~english
 * Push a Lua hash table converted from a cocos2d::ValueMap object into the Lua stack.
 * The type of value of the key/value pair would be Value::Type::BOOLEAN,Value::Type::FLOAT,Value::Type::DOUBLE,Value::Type::INTEGER,Value::Type::STRING,Value::Type::VECTOR,Value::Type::MAP,Value::Type::INT_KEY_MAP.
 *
 * @~chinese 
 * ��һ����cocos2d::ValueMapת��������hash-tableѹ��Luaջ��
 * key/value����ֵ�����Ϳ�����Value::Type::BOOLEAN,Value::Type::FLOAT��Value::Type::DOUBLE�� Value::Type::INTEGER��Value::Type::STRING��Value::Type::VECTOR, Value::Type::MAP��Value::Type::INT_KEY_MAP��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::ValueMap object.
 * @~chinese cocos2d::ValueMap����
 */
void ccvaluemap_to_luaval(lua_State* L,const cocos2d::ValueMap& inValue);

/**@~english
 * Push a Lua hash table converted from a cocos2d::ValueMapIntKey object into the Lua stack.
 * The type of value of the key/value pair would be Value::Type::BOOLEAN,Value::Type::FLOAT��Value::Type::DOUBLE�� Value::Type::INTEGER��Value::Type::STRING��Value::Type::VECTOR, Value::Type::MAP��Value::Type::INT_KEY_MAP.
 *
 * @~chinese 
 * ��һ����cocos2d::ValueMapIntKeyת��������hash-tableѹ��Luaջ��
 * ��/ֵ����ֵ�����Ϳ�����Value::Type::BOOLEAN,Value::Type::FLOAT��Value::Type::DOUBLE�� Value::Type::INTEGER��Value::Type::STRING��Value::Type::VECTOR, Value::Type::MAP��Value::Type::INT_KEY_MAP��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::ValueMapIntKey object.
 * @~chinese cocos2d::ValueMapIntKey����
 */
void ccvaluemapintkey_to_luaval(lua_State* L, const cocos2d::ValueMapIntKey& inValue);

/**@~english
 * Push a Lua array table converted from a cocos2d::ValueVector object into the Lua stack.
 * The type of value of the Vector would be Value::Type::BOOLEAN,Value::Type::FLOAT��Value::Type::DOUBLE�� Value::Type::INTEGER��Value::Type::STRING��Value::Type::VECTOR, Value::Type::MAP��Value::Type::INT_KEY_MAP.
 *
 * @~chinese 
 * ��һ����cocos2d::ValueVectorת��������array tableѹ��Luaջ��
 * �����е�ֵ���Ϳ�����Value::Type::BOOLEAN,Value::Type::FLOAT��Value::Type::DOUBLE�� Value::Type::INTEGER��Value::Type::STRING��Value::Type::VECTOR, Value::Type::MAP��Value::Type::INT_KEY_MAP��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::ValueVector object.
 * @~chinese cocos2d::ValueVector����
 */
void ccvaluevector_to_luaval(lua_State* L, const cocos2d::ValueVector& inValue);

/**@}**/

/**@~english
 * Get the real typename for the specified typename.
 * Because all override functions wouldn't be bound,so we must use `typeid` to get the real typename.
 *
 * @~chinese 
 * ��ȡret�������ʵtypename��
 * ��Ϊ����override���������ᱻ��,�������Ǳ���ʹ�á�typeid������ȡ��ʵ�ĵ�typename��
 * 
 * @param ret @~english the pointer points to a type T object.
 * @~chinese ָ��type T�����ָ�롣
 * @param type @~english the string pointer points to specified typename.
 * @~chinese �ض�typename���ַ���ָ�롣
 * @return @~english return the pointer points to the real typename, or nullptr.
 * @~chinese ����ָ����ʵtypename���ַ���ָ�����nullptr��
 */
template <class T>
const char* getLuaTypeName(T* ret,const char* type)
{
    if (nullptr != ret)
    {
        std::string hashName = typeid(*ret).name();
        auto iter =  g_luaType.find(hashName);
        if(g_luaType.end() != iter)
        {
            return iter->second.c_str();
        }
        else
        {
            return type;
        }
    }
    
    return nullptr;
}

/**@~english
 * Push the native object by userdata format into the Lua stack.@see toluafix_pushusertype_ccobject and tolua_pushusertype. if the native object is nullptr, push a nil value to the Lua stack
 *
 * @~chinese
 * ��һ��native������Lua userdata����ʽѹ�뵽Luaջ�С�@see toluafix_pushusertype_ccobject and tolua_pushusertype�����native����Ϊnullptr,��һ��nilֵѹ��Luaջ�С�
 * 
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param type @~english the string pointer points to the typename.
 * @~chinese typename�ַ�����
 * @param ret @~english the native object pointer.
 * @~chinese native����ָ�롣
 */
template <class T>
void object_to_luaval(lua_State* L,const char* type, T* ret)
{
    if(nullptr != ret)
    {
        if (std::is_base_of<cocos2d::Ref, T>::value)
        {
            // use c style cast, T may not polymorphic
            cocos2d::Ref* dynObject = (cocos2d::Ref*)(ret);
            int ID = (int)(dynObject->_ID) ;
            int* luaID = &(dynObject->_luaID);
            toluafix_pushusertype_ccobject(L,ID, luaID, (void*)ret,type);
        }
        else
        {
            tolua_pushusertype(L,(void*)ret,getLuaTypeName(ret, type));
        }
    }
    else
    {
        lua_pushnil(L);
    }
}

/**@~english
 * Push a table converted from a cocos2d::MeshVertexAttrib object into the Lua stack.
 * The format of table as follows: {size=numberValue1, type=numberValue2, vertexAttrib=numberValue3, attribSizeBytes=numberValue4}
 *
 * @~chinese 
 * ����cocos2d::MeshVertexAttribת���ɵ�Lua tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{size=numberValue1, type=numberValue2, vertexAttrib=numberValue3, attribSizeBytes=numberValue4}��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::MeshVertexAttrib object.
 * @~chinese cocos2d::MeshVertexAttrib����
 */
void mesh_vertex_attrib_to_luaval(lua_State* L, const cocos2d::MeshVertexAttrib& inValue);

/**@~english
 * Push a Lua array table converted from a std::vector<std::string> into the Lua stack.
 * The format of table as follows: {stringValue1, stringValue2, ..., stringVectorSize}
 *
 * @~chinese 
 * ����std::vector<std::string>ת���ɵ�Lua array tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{stringValue1, stringValue2, ..., stringVectorSize}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a std::vector<std::string> value.
 * @~chinese std::vector< std::string>ֵ��
 */
void ccvector_std_string_to_luaval(lua_State* L, const std::vector<std::string>& inValue);

/**@~english
 * Push a Lua array table converted from a std::vector<int> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @~chinese 
 * ����std::vector<int>ת���ɵ�Lua array tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{numberValue1,numberValue2,��,numberVectorSize}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a std::vector<int> vaule.
 * @~chinese std::vector<int>ֵ��
 */
void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue);

/**@~english
 * Push a Lua array table converted from a std::vector<float> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @~chinese 
 * ����std::vector<float>ת���ɵ�Lua array tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{numberValue1, numberValue2, ..., numberVectorSize}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a std::vector<float> vaule.
 * @~chinese std::vector<float>ֵ��
 */
void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue);

/**@~english
 * Push a Lua array table converted from a std::vector<unsigned short> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @~chinese 
 * ����std::vector<unsigned short>ת���ɵ�Lua array tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{numberValue1, numberValue2, ..., numberVectorSize}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a std::vector<unsigned short> vaule.
 * @~chinese std::vector<unsigned short>ֵ��
 */
void ccvector_ushort_to_luaval(lua_State* L, const std::vector<unsigned short>& inValue);

/**@~english
 * Push a table converted from a cocos2d::Quaternion object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3, w=numberValue4}
 *
 * @~chinese 
 * ����cocos2d::Quaternionת���ɵ�Lua tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{x=numberValue1, y=numberValue2, z=numberValue3, w=numberValue4}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::Quaternion object.
 * @~chinese cocos2d::Quaternion����
 */
void quaternion_to_luaval(lua_State* L,const cocos2d::Quaternion& inValue);

/**@~english
 * Push a table converted from a cocos2d::Texture2D::TexParams object into the Lua stack.
 * The format of table as follows: {minFilter=numberValue1, magFilter=numberValue2, wrapS=numberValue3, wrapT=numberValue4}
 *
 * @~chinese 
 * ����cocos2d::Texture2D::TexParamsת���ɵ�Lua tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{minFilter=numberValue1, magFilter=numberValue2, wrapS=numberValue3, wrapT=numberValue4}
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a cocos2d::Texture2D::TexParams object.
 * @~chinese cocos2d::Texture2D::TexParams����
 */
void texParams_to_luaval(lua_State* L, const cocos2d::Texture2D::TexParams& inValue);

/**@~english
 * Push a Lua array table converted from a std::vector<cocos2d::Vec3> into the Lua stack.
 * The format of table as follows: {vec3Value1, vec3Value2, ..., vec3ValueSize}.
 *
 * @~chinese 
 * ����std::vector<cocos2d::Vec3>ת���ɵ�Lua array tableѹ�뵽Luaջ��
 * table�ĸ�ʽ����:{vec3Value1, vec3Value2, ..., vec3ValueSize}��
 * 
 * @param L @~english the current lua_State.
 * @~chinese ��ǰlua_State��
 * @param inValue @~english a std::vector<cocos2d::Vec3> vaule.
 * @~chinese std::vector<cocos2d::Vec3>ֵ��
 */
void std_vector_vec3_to_luaval(lua_State* L, const std::vector<cocos2d::Vec3>& inValue);

/**
 * Push a Lua dict table converted from a std::map<std::string, std::string> into the Lua stack.
 *
 * @param L the current lua_State.
 * @param inValue a std::map<std::string, std::string> vaule.
 */
void std_map_string_string_to_luaval(lua_State* L, const std::map<std::string, std::string>& inValue);

// end group
/// @}
#endif //__COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
