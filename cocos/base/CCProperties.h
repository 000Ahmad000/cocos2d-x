/****************************************************************************
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2015 Chukong Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 ****************************************************************************/


#ifndef __cocos2d_libs__CCProperties__
#define __cocos2d_libs__CCProperties__

#include <string>
#include <functional>
#include <cstdint>
#include <vector>

#include "renderer/CCTexture2D.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Properties;
class Vec2;
class Vec3;
class Vec4;
class Mat4;
class Data;
class Data;


/**
 * @~english Defines a properties file for loading text files.
 *
 * A properties file has very simple syntax and can contain only namespaces and
 * name/value pairs (the properties of a namespace).  
 * The file can have any file extension a user specifies.
 *
 * Here's an example of a simple
 * file that uses all the available features of the markup language:
 *
  @verbatim
     // This is a comment.
  
     // This property is in the default namespace:
     integerProperty = 5
  
     // This line defines a namespace of type "mynamespace" without an ID:
     mynamespace
     {
         // This namespace can be retrieved by searching for its ID, "spriteTexture",
         // or by its name "texture":
         texture spriteTexture 
         {
             fileName = sprite.png
             width = 64
             height = 64
         }
  
         // This property is in the "space" namespace:
         booleanProperty = true
  
         // It's legal to have a name without a value if you leave out the '=' character:
         foo
  
         // In fact, the '=' character is optional if you'd rather write:
         bar 23
  
         // But don't write this or you'll get an error:
         // illegalProperty =
  
         // Or this:
         // = 15
  
         // Properties objects let you retrieve values as various types.
         floatProperty = 3.333
         stringProperty = This is a string.
         vector3Property = 1.0, 5.0, 3.55
         colorProperty = 1.0, 0.4, 0.0, 1.0
     }
  @endverbatim
 * 
 * Retrieving information out of a file like this could be done in two ways.  If the
 * available namespaces and name/value pairs are known in advance they can be queried by ID or name.
 * For example, if the namespace "spriteTexture" and its properties are required then they can
 * be retrieved with a call to getNamespace() followed by calls to getString() and getInt().
 * A namespace is stored and retrieved as a Properties object.
 * Reading the spriteTexture properties out of the file above in this way could be done with the following code:
 * 
  @verbatim
     // Create the top-level Properties object.
     Properties* properties = Properties::createNonRefCounted("example.properties");
     // Retrieve the "spriteTexture" namespace.
     Properties* spriteTexture = properties->getNamespace("spriteTexture");
  
     // Get the values of known texture properties out of the namespace.
     const char* fileName = spriteTexture->getString("fileName");
     int width = spriteTexture->getInt("width");
     int height = spriteTexture->getInt("height");
  
     // Deleting the top-level Properties object will clean up all nested namespaces.
     SAFE_DELETE(properties);
  @endverbatim
 *
 * On the other hand, if the structure of the file is not known in advance its 
 * namespaces and name/value pairs can be retrieved one by one using the getNextNamespace()
 * and getNextProperty() methods.  The following method prints the contents of any properties file
 * to the console:
 * 
  @verbatim
     void printProperties(Properties* properties)
     {
         // Print the name and ID of the current namespace.
         const char* spacename = properties->getNamespace();
         const char* id = properties->getId();
         GP_WARN("Namespace: %s  ID: %s\n{", spacename, id);
  
         // Print all properties in this namespace.
         const char* name = properties->getNextProperty();
         const char* value = NULL;
         while (name != NULL)
         {
             value = properties->getString(name);
             GP_WARN("%s = %s", name, value);
             name = properties->getNextProperty();
         }
         GP_WARN("}\n");
  
         // Print the properties of every namespace within this one.
         Properties* space = properties->getNextNamespace();
         while (space != NULL)
         {
             printProperties(space);
             space = properties->getNextNamespace();
         }
     }
  @endverbatim
 *
 * Note that this method does not keep track of the namespace hierarchy, but could be
 * modified to do so.  Also note that nothing in a properties file indicates the type
 * of a property. If the type is unknown, its string can be retrieved and interpreted
 * as necessary.
 *
 * @~chinese 
 * ����һ�����ڼ����ı��ļ��������ļ���
 *
 * һ�������ļ��﷨�ܼ򵥣�����ֻ���������ռ�ͼ�ֵ�ԣ������ռ��µ����ԣ���
 * ����ļ�����ʹ���û�ָ����������չ����
 *
 * ������һ���򵥵�ʾ���ļ��������� markup ���Ե����п��ù��ܣ�
 *
  @verbatim
     // This is a comment.
  
     // This property is in the default namespace:
     integerProperty = 5
  
     // This line defines a namespace of type "mynamespace" without an ID:
     mynamespace
     {
         // This namespace can be retrieved by searching for its ID, "spriteTexture",
         // or by its name "texture":
         texture spriteTexture 
         {
             fileName = sprite.png
             width = 64
             height = 64
         }
  
         // This property is in the "space" namespace:
         booleanProperty = true
  
         // It's legal to have a name without a value if you leave out the '=' character:
         foo
  
         // In fact, the '=' character is optional if you'd rather write:
         bar 23
  
         // But don't write this or you'll get an error:
         // illegalProperty =
  
         // Or this:
         // = 15
  
         // Properties objects let you retrieve values as various types.
         floatProperty = 3.333
         stringProperty = This is a string.
         vector3Property = 1.0, 5.0, 3.55
         colorProperty = 1.0, 0.4, 0.0, 1.0
     }
  @endverbatim
 * 
 * �����ַ������Դ��ļ��м������ݡ�
 * �����֪���õ������ռ����ֵ�ԣ���ô����ʹ�� ID �����������������ԡ�
 * ���磺���Ҫʹ�� "spriteTexture" ��������ռ估�����ԣ���ô����ͨ������ getNamespace() ��ȡ�����ռ䣬
 * �ٵ��� getString() ���� getInt() ����ȡ���ݡ�
 * �����ռ����ڴ���Ҳ��һ�����Զ���
 * ���Բο����´�������ȡ "spriteTexture" �����ռ��µ����ԣ�
 * 
  @verbatim
     // Create the top-level Properties object.
     Properties* properties = Properties::createNonRefCounted("example.properties");
     // Retrieve the "spriteTexture" namespace.
     Properties* spriteTexture = properties->getNamespace("spriteTexture");
  
     // Get the values of known texture properties out of the namespace.
     const char* fileName = spriteTexture->getString("fileName");
     int width = spriteTexture->getInt("width");
     int height = spriteTexture->getInt("height");
  
     // Deleting the top-level Properties object will clean up all nested namespaces.
     SAFE_DELETE(properties);
  @endverbatim
 *
 * ��һ���棬��������ռ估������δ֪����ô����ʹ�� getNextNamespace() �� getNextProperty() ���������ȡ�����ռ����ֵ�ԡ�
 * ����Ĵ�����Խ������ļ����������������̨��
 * 
  @verbatim
     void printProperties(Properties* properties)
     {
         // Print the name and ID of the current namespace.
         const char* spacename = properties->getNamespace();
         const char* id = properties->getId();
         GP_WARN("Namespace: %s  ID: %s\n{", spacename, id);
  
         // Print all properties in this namespace.
         const char* name = properties->getNextProperty();
         const char* value = NULL;
         while (name != NULL)
         {
             value = properties->getString(name);
             GP_WARN("%s = %s", name, value);
             name = properties->getNextProperty();
         }
         GP_WARN("}\n");
  
         // Print the properties of every namespace within this one.
         Properties* space = properties->getNextNamespace();
         while (space != NULL)
         {
             printProperties(space);
             space = properties->getNextNamespace();
         }
     }
  @endverbatim
 *
 * ע������ʾ�����벻�ܴ����㼶�������ռ䣬����ͨ��������ʵ�֡�
 * ��Ҫע����ǣ��������ļ��У�û�б�ʾ����ֵ���͵��ֶΡ�
 * �������ֵ������δ֪�����Զ�ȡ���ַ������͵�ֵ��
 */
class CC_DLL Properties
{
    friend class Game;

public:

    /**@~english
     * Data types supported by the properties class.
     * @~chinese 
     * Properties ����֧�ֵ����������б�
     */
    enum Type
    {
        NONE,
        STRING,
        NUMBER,
        VECTOR2,
        VECTOR3,
        VECTOR4,
        MATRIX
    };

    /**@~english
     * Creates a Properties runtime settings from the specified URL, where the URL is of
     * the format "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     * 
     * @~chinese 
     * ��ָ���� URL ����һ�� Properties ����URL �ĸ�ʽΪ��
     * "<�ļ�·��>.<��չ��>#<�����ռ� ID>/<�����ռ� ID>/.../<�����ռ� ID>"
     * (���� "#<�����ռ� ID>" �ǿ�ѡ��)
     * 
     * @param url @~english The URL to create the properties from.
     * 
     * @~chinese ָ���� URL��
     * 
     * @return @~english The created Properties or NULL if there was an error.
     * @~chinese ���� Properties ʵ�����������ʧ�ܣ����� nullptr��
     */
    static Properties* createNonRefCounted(const std::string& url);

    /**@~english
     * Destructor.
     * @~chinese 
     * ����������
     */
    ~Properties();

    /**@~english
     * Get the name of the next property.
     *
     * If a valid next property is returned, the value of the property can be
     * retrieved using any of the get methods in this class, passing NULL for
     * the property name.
     *
     * @~chinese 
     * ��ȡ��һ�����Ե����ơ�
     * 
     * �������ֵ��һ����Ч�����ԣ�����ͨ���κ� get ��������ȡ����ֵ��name ����ʹ�� NULL����
     * 
     * @return @~english The name of the next property, or NULL if there are no properties remaining.
     * @~chinese ��һ�����Ե����ƣ�����������򷵻� NULL��
     */
    const char* getNextProperty();

    /**@~english
     * Get the next namespace.
     * @~chinese 
     * ��ȡ��һ�������ռ䡣
     */
    Properties* getNextNamespace();

    /** @~english
     * Rewind the getNextProperty() and getNextNamespace() iterators
     * to the beginning of the file.
     * @~chinese 
     * ���� getNextProperty() �� getNextNamespace() ��ȡ�ĵ��������ļ��Ŀ�ʼ��
     */
    void rewind();

    /**@~english
     * Get a specific namespace by ID or name. This method will optionally
     * perform a depth-first search on all namespaces and inner namespaces
     * within this Property.
     *
     * @~chinese 
     * ͨ��ָ���� ID ������������ȡ�����ռ䡣�÷�������ѡ����
     * ��ǰ��������������ռ��Լ��ڲ��������ռ��н��еݹ���ҡ�
     * 
     * @param id @~english The ID or name of the namespace to find.
     * @~chinese �����ռ��ID�����ơ�
     * @param searchNames @~english If true, namespace names are used in the search,
     *      instead of namespace IDs. By default this parameter is false
     *      and namespace IDs are searched.
     * @~chinese ���Ϊ true ��ʹ�����������ң�����ʹ�� ID ���в��ҡ�Ĭ��ʹ�� ID ���в��ҡ�
     * @param recurse @~english If true, perform a depth-first search, otherwise search
     *      only the immediate child namespaces.
     * 
     * @~chinese ���Ϊ true������еݹ���ң�����ֻ�ڵ�ǰ�����в��ҡ�
     * 
     * @return @~english A properties object with the given ID or name.
     * @~chinese ��ָ�������ƻ� ID ƥ��� Properties ����
     */
    Properties* getNamespace(const char* id, bool searchNames = false, bool recurse = true) const;

    /**@~english
     * Get the name of this Property's namespace.
     *
     * @~chinese 
     * ��ȡ��ǰ����������ռ����ơ�
     * 
     * @return @~english The name of this Property's namespace.
     * @~chinese ��ǰ����������ռ����ơ�
     */
    const char* getNamespace() const;

    /**@~english
     * Get the ID of this Property's namespace. The ID should be a unique identifier,
     * but its uniqueness is not enforced.
     *
     * @~chinese 
     * ��ȡ��ǰ����������ռ� ID��ID Ӧ����һ��Ψһ��ֵ�����ǲ���ǿ��Ҫ����Ψһ�ԡ�
     * 
     * @return @~english The ID of this Property's namespace.
     * @~chinese ��ǰ����������ռ� ID��
     */
    const char* getId() const;

    /**@~english
     * Check if a property with the given name is specified in this Properties object.
     *
     * @~chinese 
     * ����Ƿ����ָ�����Ƶ����ԡ�
     * 
     * @param name @~english The name of the property to query.
     * 
     * @~chinese Ҫ�������Ե����ơ�
     * 
     * @return @~english True if the property exists, false otherwise.
     * @~chinese ������ڷ��� true�����򷵻� false��
     */
    bool exists(const char* name) const;

    /**@~english
     * Returns the type of a property.
     *
     * @~chinese 
     * �������Ե����͡�
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's type.
     *
     * @~chinese ���Ե����ƣ����Ϊ NULL ���ȡ��ǰ��������͡�
     * 
     * @return @~english The type of the property.
     * @~chinese ���Ե����͡�
     */
    Type getType(const char* name = NULL) const;

    /**@~english
     * Get the value of the given property as a string. This can always be retrieved,
     * whatever the intended type of the property.
     *
     * @~chinese 
     * ��ȡָ������ֵ���ַ��������Լ����������͵����ԡ�
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese �������ƣ����Ϊ NULL �򷵻ص�ǰ���Ե�ֵ��
     * @param defaultValue @~english The default value to return if the specified property does not exist.
     * 
     * @~chinese Ĭ��ֵ�����ָ�������Բ����ڣ��򷵻ش�Ĭ��ֵ��
     * 
     * @return @~english The value of the given property as a string, or the empty string if no property with that name exists.
     * @~chinese ָ������ֵ���ַ�����������Բ����ڣ��򷵻�ָ����Ĭ��ֵ���߿��ַ�����
     */
    const char* getString(const char* name = NULL, const char* defaultValue = NULL) const;

    /**@~english
     * Sets the value of the property with the specified name.
     *
     * If there is no property in this namespace with the current name,
     * one is added. Otherwise, the value of the first property with the
     * specified name is updated.
     *
     * If name is NULL, the value current property (see getNextProperty) is
     * set, unless there is no current property, in which case false
     * is returned.
     *
     * @~chinese 
     * ����ָ�����Ƶ�����ֵ�ַ�����
     * 
     * ������Բ����ڣ������Ӹ����ԡ����򣬲��ҵ��ĵ�һ������ֵ�������¡�
     * 
     * ��������� NULL������µ�ǰ���Ե�ֵ�������ǰ������һ�����ԣ��򷵻� false��
     * 
     * @param name @~english The name of the property to set.
     * @~chinese ָ�����������ơ�
     * @param value @~english The property value.
     *
     * @~chinese ���õ�����ֵ��
     * 
     * @return @~english True if the property was set, false otherwise.
     * @~chinese ������óɹ����� true�����򷵻� false��
     */
    bool setString(const char* name, const char* value);

    /**@~english
     * Interpret the value of the given property as a boolean.
     *
     * @~chinese 
     * ��ȡ�������͵�����ֵ��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ơ����Ϊ NULL�����ȡ��ǰ���������ֵ��
     * @param defaultValue @~english the default value to return if the specified property does not exist within the properties file.
     * 
     * @~chinese Ĭ��ֵ������Ҳ���ָ�������ԣ��򷵻ش�Ĭ��ֵ��
     * 
     * @return @~english true if the property exists and its value is "true", otherwise false.
     * @~chinese ָ�����ԵĲ���ֵ��������Բ����ڣ��򷵻�ָ����Ĭ��ֵ���� false��
     */
    bool getBool(const char* name = NULL, bool defaultValue = false) const;

    /**@~english
     * Interpret the value of the given property as an integer.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @~chinese 
     * ��ȡָ�����Ե�����ֵ��
     * ������Բ����ڣ������� 0��
     * ������Դ��ڣ��������������ͣ������������־������ 0��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * 
     * @return @~english The value of the given property interpreted as an integer.
     *   Zero if the property does not exist or could not be scanned.
     * @~chinese ��ȡ���Ե�����ֵ��������Բ����ڻ��߶�ȡʧ���򷵻� 0��
     */
    int getInt(const char* name = NULL) const;

    /**@~english
     * Interpret the value of the given property as a floating-point number.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @~chinese 
     * ��ȡָ�����Եĸ���ֵ��
     * ������Բ����ڣ������� 0��
     * ������Դ��ڣ������Ǹ������ͣ������������־������ 0��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * 
     * @return @~english The value of the given property interpreted as a float.
     *   Zero if the property does not exist or could not be scanned.
     * @~chinese ��ȡ���Եĸ���ֵ��������Բ����ڻ��߶�ȡʧ���򷵻� 0��
     */
    float getFloat(const char* name = NULL) const;

    /**@~english
     * Interpret the value of the given property as a long integer.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @~chinese 
     * ��ȡָ�����Եĳ�����ֵ��
     * ������Բ����ڣ������� 0��
     * ������Դ��ڣ������ǳ��������ͣ������������־������ 0��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * 
     * @return @~english The value of the given property interpreted as a long.
     *   Zero if the property does not exist or could not be scanned.
     * @~chinese ��ȡ���Եĳ�����ֵ��������Բ����ڻ��߶�ȡʧ���򷵻� 0��
     */
    long getLong(const char* name = NULL) const;

    /**@~english
     * Interpret the value of the given property as a Matrix.
     * If the property does not exist, out will be set to the identity matrix.
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to the identity matrix.
     *
     * @~chinese 
     * ��ȡָ�����Եľ���ֵ��
     * ������Բ����ڣ����ز��� out ��������Ϊ��λ����
     * ������Դ��ڣ������Ǿ������ͣ������������־���� out ������Ϊ��λ����
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * @param out @~english The matrix to set to this property's interpreted value.
     * 
     * @~chinese �������Ͳ�������ȡ�ľ���ֵ��
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getMat4(const char* name, Mat4* out) const;

    /**@~english
     * Interpret the value of the given property as a Vec2.
     * If the property does not exist, out will be set to Vec2(0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vec2(0.0f, 0.0f).
     *
     * @~chinese 
     * ��ȡָ�����Ե� Vec2 ֵ��
     * ������Բ����ڣ����ز��� out ��������Ϊ Vec2(0.0f, 0.0f)��
     * ������Դ��ڣ������� Vec2 ���ͣ������������־���� out ������Ϊ Vec2(0.0f, 0.0f)��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese �������Ͳ�������ȡ�� Vec2 ʵ����
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getVec2(const char* name, Vec2* out) const;

    /**@~english
     * Interpret the value of the given property as a Vec3.
     * If the property does not exist, out will be set to Vec3(0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vec3(0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * ��ȡָ�����Ե� Vec3 ֵ��
     * ������Բ����ڣ����ز��� out ��������Ϊ Vec3(0.0f, 0.0f, 0.0f)��
     * ������Դ��ڣ������� Vec3 ���ͣ������������־���� out ������Ϊ Vec3(0.0f, 0.0f, 0.0f)��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese �������Ͳ�������ȡ�� Vec3 ʵ����
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getVec3(const char* name, Vec3* out) const;

    /**@~english
     * Interpret the value of the given property as a Vec4.
     * If the property does not exist, out will be set to Vec4(0.0f, 0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vec4(0.0f, 0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * ��ȡָ�����Ե� Vec4 ֵ��
     * ������Բ����ڣ����ز��� out ��������Ϊ Vec4(0.0f, 0.0f, 0.0f, 0.0f)��
     * ������Դ��ڣ������� Vec3 ���ͣ������������־���� out ������Ϊ Vec4(0.0f, 0.0f, 0.0f, 0.0f)��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese �������Ͳ�������ȡ�� Vec4 ʵ����
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getVec4(const char* name, Vec4* out) const;

    /**@~english
     * Interpret the value of the given property as a Quaternion specified as an axis angle.
     * If the property does not exist, out will be set to Quaternion().
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Quaternion().
     *
     * @~chinese 
     * ��ȡָ�����Ե���Ԫ����
     * ������Բ����ڣ����ز��� out ��������Ϊ Quaternion()��
     * ������Դ��ڣ���������Ԫ�����ͣ������������־���� out ������Ϊ Quaternion()��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * @param out @~english The quaternion to set to this property's interpreted value.
     * 
     * @~chinese �������Ͳ�������ȡ����Ԫ����
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getQuaternionFromAxisAngle(const char* name, Quaternion* out) const;

    /**@~english
     * Interpret the value of the given property as an RGB color in hex and write this color to a Vec3.
     * E.g. 0xff0000 represents red and sets the vector to (1, 0, 0).
     * If the property does not exist, out will be set to Vec3(0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vec3(0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * ����ֵ���� RGB ��ɫ�������洢�� Vec3 �����С�
     * ���磺0xff0000 �����ɫ��out ����ֵΪ Vec3(1, 0, 0)��
     * ������Բ����ڣ����ز��� out ��������Ϊ Vec3(0.0f, 0.0f, 0.0f)��
     * ������Դ��ڣ�������ʧ�ܣ������������־���� out ������Ϊ Vec3(0.0f, 0.0f, 0.0f)��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese �������Ͳ�������ȡ����ɫֵ���ݡ�
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getColor(const char* name, Vec3* out) const;

    /**@~english
     * Interpret the value of the given property as an RGBA color in hex and write this color to a Vec4.
     * E.g. 0xff0000ff represents opaque red and sets the vector to (1, 0, 0, 1).
     * If the property does not exist, out will be set to Vec4(0.0f, 0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vec4(0.0f, 0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * ����ֵ���� RGBA ��ɫ�������洢�� Vec4 �����С�
     * ���磺0xff0000ff ����͸���ĺ�ɫ�����ز��� out ��������Ϊ Vec4(1, 0, 0, 1)��
     * ������Բ����ڣ����ز��� out ��������Ϊ Vec4(0.0f, 0.0f, 0.0f, 0.0f)��
     * ������Դ��ڣ�������ʧ�ܣ������������־���� out ������Ϊ Vec4(0.0f, 0.0f, 0.0f, 0.0f)��
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese ָ�����������ƣ����Ϊ NULL ���ȡ��ǰ���������ֵ��
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese �������Ͳ�������ȡ����ɫֵ���ݡ�
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getColor(const char* name, Vec4* out) const;

    /**@~english
     * Gets the file path for the given property if the file exists.
     * 
     * This method will first search for the file relative to the working directory.
     * If the file is not found then it will search relative to the directory the bundle file is in.
     * 
     * @~chinese 
     * ��ȡָ�����Ե�·��ֵ��
     * 
     * �÷�����������ڹ���Ŀ¼��������ֵ����ʾ���ļ���
     * ���û���ҵ��ļ�����ô��������������Ŀ¼��
     * 
     * @param name @~english The name of the property.
     * @~chinese ���Ե����ơ�
     * @param path @~english The string to copy the path to if the file exists.
     * 
     * @~chinese ���ص�·��ֵ��
     * 
     * @return @~english True if the property exists and the file exists, false otherwise.
     *
     * @~chinese �����ȡ�ɹ����� true�����򷵻� false��
     */
    bool getPath(const char* name, std::string* path) const;

    /**@~english
     * Returns the value of a variable that is set in this Properties object.
     *
     * Variables take on the format ${name} and are inherited from parent Property objects.
     *
     * @~chinese 
     * ��ȡָ�����Եı���ֵ��
     * 
     * �����ĸ�ʽ ${name}���Ǽ̳��Ը������ԵĶ���
     * 
     * @param name @~english Name of the variable to get.
     * @~chinese ���Ե����ơ�
     * @param defaultValue @~english Value to return if the variable is not found.
     *
     * @~chinese Ĭ��ֵ�������Բ�����ʱ���ش�Ĭ��ֵ��
     * 
     * @return @~english The value of the specified variable, or defaultValue if not found.
     * @~chinese ��ȡ���ı���ֵ�������ȡʧ�ܣ��򷵻�ָ����Ĭ��ֵ��
     */
    const char* getVariable(const char* name, const char* defaultValue = NULL) const;

    /**@~english
     * Sets the value of the specified variable.
     *
     * @~chinese 
     * ����ָ�����Եı���ֵ��
     * 
     * @param name @~english Name of the variable to set.
     * @~chinese ָ�����������ơ�
     * @param value @~english The value to set.
     * @~chinese ���õı���ֵ��
     */
    void setVariable(const char* name, const char* value);

    /**@~english
     * Attempts to parse the specified string as a Vec2 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * ���Խ�ָ�����ַ�������Ϊ Vec2 ���ݡ�
     * 
     * ��������򷵻� false������ֵ���� out ������Ϊ `Vec2::ZERO`��
     * 
     * @param str @~english The string to parse.
     * @~chinese Ҫ�������ַ���
     * @param out @~english The value to populate if successful.
     *
     * @~chinese �������� Vec2 ʵ����
     * 
     * @return @~english True if a valid Vec2 was parsed, false otherwise.
     * @~chinese ��������ɹ������� true�����򷵻� false��
     */
    static bool parseVec2(const char* str, Vec2* out);

    /**@~english
     * Attempts to parse the specified string as a Vec3 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * ���Խ�ָ�����ַ�������Ϊ Vec3 ���ݡ�
     * 
     * ��������򷵻� false������ֵ���� out ������Ϊ `Vec3::ZERO`��
     * 
     * @param str @~english The string to parse.
     * @~chinese Ҫ�������ַ���
     * @param out @~english The value to populate if successful.
     *
     * @~chinese �������� Vec3 ʵ����
     * 
     * @return @~english True if a valid Vec3 was parsed, false otherwise.
     * @~chinese ��������ɹ������� true�����򷵻� false��
     */
    static bool parseVec3(const char* str, Vec3* out);
    
    /**@~english
     * Attempts to parse the specified string as a Vec4 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * ���Խ�ָ�����ַ�������Ϊ Vec4 ���ݡ�
     * 
     * ��������򷵻� false������ֵ���� out ������Ϊ `Vec4::ZERO`��
     * 
     * @param str @~english The string to parse.
     * @~chinese Ҫ�������ַ���
     * @param out @~english The value to populate if successful.
     *
     * @~chinese �������� Vec4 ʵ����
     * 
     * @return @~english True if a valid Vec4 was parsed, false otherwise.
     * @~chinese ��������ɹ������� true�����򷵻� false��
     */
    static bool parseVec4(const char* str, Vec4* out);

    /**@~english
     * Attempts to parse the specified string as an axis-angle value.
     *
     * The specified string is expected to contain four comma-separated
     * values, where the first three values represents the axis and the
     * fourth value represents the angle, in degrees.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * ���Խ�ָ�����ַ�������Ϊ��Ԫ����
     * 
     * �����ĸ�ʽΪ���ĸ����ŷָ�����ֵ��ǰ����ֵ��ʾ�ᣬ
     * ���ĸ�ֵ��ʾ�Ƕȡ�
     * 
     * �������ʧ�ܣ��򷵻� false������ֵ���� out ��ȫ�����ݶ�����Ϊ 0��
     * 
     * @param str @~english The string to parse.
     * @~chinese Ҫ�������ַ�����
     * @param out @~english A Quaternion populated with the orientation of the axis-angle, if successful.
     *
     * @~chinese ����������Ԫ��ʵ����
     * 
     * @return @~english True if a valid axis-angle was parsed, false otherwise.
     * @~chinese ��������ɹ������� true�����򷵻� false��
     */
    static bool parseAxisAngle(const char* str, Quaternion* out);

    /**@~english
     * Attempts to parse the specified string as an RGB color value.
     *
     * @~chinese 
     * ���Խ�ָ�����ַ�������Ϊ RGB ��ɫֵ��
     * 
     * @param str @~english The string to parse.
     * @~chinese Ҫ�������ַ�����
     * @param out @~english The value to populate if successful.
     *
     * @~chinese ���ص���ɫֵ��
     * 
     * @return @~english True if a valid RGB color was parsed, false otherwise.
     * @~chinese ��������ɹ������� true�����򷵻� false��
     */
    static bool parseColor(const char* str, Vec3* out);

    /**@~english
     * Attempts to parse the specified string as an RGBA color value.
     *
     * @~chinese 
     * ���Խ�ָ�����ַ�������Ϊ RGBA ��ɫֵ��
     * 
     * @param str @~english The string to parse.
     * @~chinese Ҫ�������ַ�����
     * @param out @~english The value to populate if successful.
     *
     * @~chinese ���ص���ɫֵ��
     * 
     * @return @~english True if a valid RGBA color was parsed, false otherwise.
     * @~chinese ��������ɹ������� true�����򷵻� false��
     */
    static bool parseColor(const char* str, Vec4* out);

private:

    struct Property
    {
        std::string name;
        std::string value;
        Property(const std::string& aname, const std::string& avalue) : name(aname), value(avalue) { }
    };

    Properties();

    Properties(Data* data, ssize_t* dataIdx);
    Properties(const Properties& copy);

    Properties(Data* data, ssize_t* dataIdx, const std::string& name, const char* id, const char* parentID, Properties* parent);

    // Data manipulation methods
    void readProperties();
    void skipWhiteSpace();
    char* trimWhiteSpace(char* str);
    signed char readChar();
    char* readLine(char* output, int num);
    bool seekFromCurrent(int offset);
    bool eof();

    // Called after createNonRefCounted(); copies info from parents into derived namespaces.
    void resolveInheritance(const char* id = NULL);

    // Called by resolveInheritance().
    void mergeWith(Properties* overrides);

    // Clones the Properties object.
    Properties* clone();

    void setDirectoryPath(const std::string* path);
    void setDirectoryPath(const std::string& path);

    // XXX: hack in order to simulate GamePlay's Stream with Cocos2d's Data
    ssize_t *_dataIdx;
    Data *_data;

    std::string _namespace;
    std::string _id;
    std::string _parentID;
    std::vector<Property> _properties;
    std::vector<Property>::iterator _propertiesItr;
    std::vector<Properties*> _namespaces;
    std::vector<Properties*>::const_iterator _namespacesItr;
    std::vector<Property>* _variables;
    std::string* _dirPath;
    Properties* _parent;
};

}

#endif // __cocos2d_libs__CCProperties__
