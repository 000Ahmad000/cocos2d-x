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

#ifndef __CC_LUA_VALUE_H_
#define __CC_LUA_VALUE_H_

#include <string>
#include <map>
#include <list>

extern "C" {
#include "lua.h"
}

#include "base/ccTypes.h"
#include "base/CCRef.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
using std::memset;
using std::memcpy;
#endif

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

typedef int LUA_FUNCTION;
typedef int LUA_TABLE;
typedef int LUA_STRING;

class LuaValue;

typedef std::map<std::string, LuaValue>   LuaValueDict;
typedef LuaValueDict::const_iterator      LuaValueDictIterator;
typedef std::list<LuaValue>               LuaValueArray;
typedef LuaValueArray::const_iterator     LuaValueArrayIterator;

/// @cond
typedef enum {
    LuaValueTypeInt,
    LuaValueTypeFloat,
    LuaValueTypeBoolean,
    LuaValueTypeString,
    LuaValueTypeDict,
    LuaValueTypeArray,
    LuaValueTypeObject
} LuaValueType;
/// @endcond

/// @cond
typedef union {
    int                 intValue;
    float               floatValue;
    bool                booleanValue;
    std::string*        stringValue;
    LuaValueDict*     dictValue;
    LuaValueArray*    arrayValue;
    Ref*           ccobjectValue;
} LuaValueField;
/// @endcond

/**@~english
 * Wrap different general types of data into a same specific type named LuaValue.
 * The general types supported are as follows:int,float,bool,std::string,const char*,LuaValueDict,LuaValueArray,Ref object.
 *
 * @~chinese 
 * LuaValue��һЩ�����������ݵĸ߼���װ��
 * ֧�ֵĳ�����������:int,float,bool,std::string,const char*,LuaValueDict,LuaValueArray,Ref object.
 * 
 * @lua NA
 * @js NA
 */
class LuaValue
{
public:
    
    /**@~english
     * Construct a LuaValue object by a int value.
     *
     * @~chinese 
     * ͨ��һ��intֵ����һ��LuaValue����
     * 
     * @param intValue @~english a int value.
     * @~chinese intֵ��
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue intValue(const int intValue);
    
    /**@~english
     * Construct a LuaValue object by a float value.
     *
     * @~chinese 
     * ͨ��һ��floatֵ����һ��LuaValue����
     * 
     * @param floatValue @~english a float value.
     * @~chinese floatֵ��
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue floatValue(const float floatValue);
    
    /**@~english
     * Construct a LuaValue object by a boolean value.
     *
     * @~chinese 
     * ͨ��һ��boolֵ����һ��LuaValue����
     * 
     * @param booleanValue @~english a bool value.
     * @~chinese boolֵ��
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue booleanValue(const bool booleanValue);
    
    /**@~english
     * Construct a LuaValue object by a string pointer.
     *
     * @~chinese 
     * ͨ��һ���ַ���ָ�빹��һ��LuaValue����
     * 
     * @param stringValue @~english a string pointer.
     * @~chinese �ַ���ָ�롣
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue stringValue(const char* stringValue);
    
    /**@~english
     * Construct a LuaValue object by a std::string object.
     *
     * @~chinese 
     * ͨ��һ��std::string�ַ�������һ��LuaValue����
     * 
     * @param stringValue @~english a std::string object.
     * @~chinese std::string�ַ�����
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue stringValue(const std::string& stringValue);
    
    /**@~english
     * Construct a LuaValue object by a LuaValueDict value.
     *
     * @~chinese 
     * ͨ��һ��LuaValueDict������һ��LuaValue����
     * 
     * @param dictValue @~english a LuaValueDict object.
     * @~chinese LuaValueDict����
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue dictValue(const LuaValueDict& dictValue);
    
    /**@~english
     * Construct a LuaValue object by a LuaValueArray value.
     *
     * @~chinese 
     * ͨ��һ��LuaValueArray������һ��LuaValue����
     * 
     * @param arrayValue @~english a LuaValueArray object.
     * @~chinese LuaValueArray����
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue arrayValue(const LuaValueArray& arrayValue);
    
    /**@~english
     * Construct a LuaValue object by a Ref object and the type name of object.
     *
     * @~chinese 
     * ͨ��һ��Ref�����Լ���Ӧ���������ֹ���һ��LuaValue����
     * 
     * @param ccobjectValue @~english a Ref object.
     * @~chinese Ref����
     * @param objectTypename @~english a string pointer point to the typename of object.
     * @~chinese һ��ָ������������ֵ��ַ���ָ�롣
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue ccobjectValue(Ref* ccobjectValue, const char* objectTypename);
    
    /**@~english
     * Construct a LuaValue object by a Ref object.
     *
     * @~chinese 
     * ͨ��һ��Ref�����Լ���Ӧ���������ֹ���һ��LuaValue����
     * 
     * @param ccobjectValue @~english a Ref object.
     * @~chinese Ref����
     * @param objectTypename @~english a std::string object represent the typename of object.
     * @~chinese һ����std::string��ʾ�Ķ����������֡�
     * @return @~english a LuaValue object.
     * @~chinese LuaValue����
     */
    static const LuaValue ccobjectValue(Ref* ccobjectValue, const std::string& objectTypename);
    
    
    /**@~english
     * Default constructor of LuaValue.
     * Set the default value for _type and _ccobjectType,and init the _field.
     * @~chinese 
     * LuaValue��Ĭ�Ϲ��캯����
     * ����_type��_ccobjectType��Ĭ��ֵ,ͬʱ��ʼ��_field��
     */
    LuaValue(void)
    : _type(LuaValueTypeInt)
    , _ccobjectType(nullptr)
    {
        memset(&_field, 0, sizeof(_field));
    }
    
    /**@~english
     * Copy constructor of LuaValue.
     * @~chinese 
     * �������캯����
     */
    LuaValue(const LuaValue& rhs);
    
    /**@~english
     * Override of operator= .
     * @~chinese 
     * ��ֵ���������غ�����
     */
    LuaValue& operator=(const LuaValue& rhs);
    
    /**@~english
     * Destructor.
     * @~chinese 
     * ����������
     */
    ~LuaValue(void);
    
    /**@~english
     * Get the type of LuaValue object.
     * 
     * @~chinese 
     * LuaValue��������͡�
     * 
     * @return @~english the type of LuaValue object.
     * @~chinese LuaValue��������͡�
     */
    const LuaValueType getType(void) const {
        return _type;
    }
    
    /**@~english
     * Get the typename of the Ref object.
     *
     * @~chinese 
     * �õ�Ref������������֡�
     * 
     * @return @~english the type name of Ref object.
     * @~chinese Ref������������֡�
     */
    const std::string& getObjectTypename(void) const {
        return *_ccobjectType;
    }
    
    /**@~english
     * Get the int value of LuaValue object.
     *
     * @~chinese 
     * ��ȡLuaValue�����intֵ��
     * 
     * @return @~english the int value.
     * @~chinese intֵ��
     */
    int intValue(void) const {
        return _field.intValue;
    }
    
    /**@~english
     * Get the float value of LuaValue object.
     *
     * @~chinese 
     * ��ȡLuaValue�����floatֵ��
     * 
     * @return @~english the float value.
     * @~chinese floatֵ��
     */
    float floatValue(void) const {
        return _field.floatValue;
    }
    
    /**@~english
     * Get the boolean value of LuaValue object.
     *
     * @~chinese 
     * ��ȡLuaValue�����boolֵ��
     * 
     * @return @~english the boolean value.
     * @~chinese boolֵ��
     */
    bool booleanValue(void) const {
        return _field.booleanValue;
    }
    
    /**@~english
     * Get the std::string value of LuaValue object.
     *
     * @~chinese 
     * ��ȡLuaValue�����std::stringֵ��
     * 
     * @return @~english the refrence about string value.
     * @~chinese std::stringֵ��
     */
    const std::string& stringValue(void) const {
        return *_field.stringValue;
    }
    
    /**@~english
     * Get the LuaValueDict value of LuaValue object.
     *
     * @~chinese 
     * ��ȡLuaValue�����LuaValueDictֵ��
     * 
     * @return @~english the LuaValueDict value.
     * @~chinese LuaValueDictֵ��
     */
    const LuaValueDict& dictValue(void) const {
        return *_field.dictValue;
    }
    
    /**@~english
     * Get the LuaValueArray value of LuaValue object.
     *
     * @~chinese 
     * ��ȡLuaValue�����LuaValueArrayֵ��
     * 
     * @return @~english the LuaValueArray value.
     * @~chinese LuaValueArrayֵ��
     */
    const LuaValueArray& arrayValue(void) const {
        return *_field.arrayValue;
    }
    
    /**@~english
     * Get the Ref object of LuaValue object.
     *
     * @~chinese 
     * ��ȡLuaValue�����Ref����ָ�롣
     * 
     * @return @~english the pointer point to a Ref object.
     * @~chinese Ref����ָ�롣
     */
    Ref* ccobjectValue(void) const {
        return _field.ccobjectValue;
    }
    
private:
    LuaValueField _field;
    LuaValueType  _type;
    std::string*    _ccobjectType;
    
    void copy(const LuaValue& rhs);
};

NS_CC_END

// end group
/// @}
#endif // __CC_LUA_VALUE_H_
