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

#ifndef __DICTIONARYHELPER_H__
#define __DICTIONARYHELPER_H__

#include "json/document.h"
#include "cocostudio/CocosStudioExport.h"

#define DICTOOL DictionaryHelper::getInstance()

namespace cocostudio {
/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DictionaryHelper
{
public:
    DictionaryHelper();
    ~DictionaryHelper();

    /**
    * @~english Gets the static instance of DictionaryHelper.
    * @~chinese ��ȡDictionaryHelper�ľ�̬ʵ��.
    */
    static DictionaryHelper* getInstance();
    /**
    * @~english Destroy DictionaryHelper static instance.
    * @~chinese �ͷ�DictionaryHelper�ľ�̬ʵ��.
    */
    static void destroyInstance();
    
    /**
    * @~english Get a child json item from the root node.
    * @~chinese ��ȡ���ڵ��µ�һ����json�ڵ�.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~chinese key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @return @~english child json item @~chinese ��json��
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key);
    /**
    * @~english Get a child json item from the root node.
    * @~chinese ��ȡ���ڵ��µ�һ����json�ڵ�.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame idx    @~english index of child json item in root[key] @~chinese ��json��root[key]�����е�����ֵ
    *
    * @return @~english child json item @~chinese ��json��
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, const char* key, int idx);
    /**
    * @~english Get a child json item from the root node.
    * @~chinese ��ȡ���ڵ��µ�һ����json�ڵ�.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame idx    @~english index of child json item @~chinese ��json�������е�����ֵ
    *
    * @return @~english child json item @~chinese ��json��
    */
    const rapidjson::Value& getSubDictionary_json(const rapidjson::Value &root, int idx);

    /**
    * @~english Get the integer value of a child json item from the root node.
    * @~chinese ��ȡroot��һ���ӽڵ��������ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english integer value of item @~chinese �ӽڵ��������ֵ
    */
    int   getIntValue_json(const rapidjson::Value& root, const char* key, int def = 0);
    /**
    * @~english Get the float value of a child json item from the root node.
    * @~chinese ��ȡroot��һ���ӽڵ�ĸ�����ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english float value of item @~chinese �ӽڵ�ĸ�����ֵ
    */
    float getFloatValue_json(const rapidjson::Value& root, const char* key, float def = 0.0f);
    /**
    * @~english Get the boolean value of a child json item from the root node.
    * @~chinese ��ȡroot��һ���ӽڵ�Ĳ�����ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english boolean value of item @~chinese �ӽڵ�Ĳ�����ֵ
    */
    bool  getBooleanValue_json(const rapidjson::Value& root, const char* key, bool def = false);
    /**
    * @~english Get the string value of a child json item from the root node.
    * @~chinese ��ȡroot��һ���ӽڵ�Ĳ�����ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english string value of item @~chinese �ӽڵ���ַ�������ֵ
    */
    const char* getStringValue_json(const rapidjson::Value& root, const char* key, const char *def = NULL);
    /**
    * @~english Get the size of a child json array from the root node.
    * @~chinese ��ȡ���ڵ���һ���������ӽڵ�������С.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english size of child json array @~chinese ��json����Ĵ�С
    */
    int   getArrayCount_json(const rapidjson::Value& root, const char* key, int def = 0);

    /**
    * @~english Get the integer value at desired index of a child array item from the root node.
    * @~chinese ��ȡһ����json������ָ��λ�ýڵ������ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame idx    @~english index of item in child json @~chinese Ŀ���������json�����е�����ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english integer value of item @~chinese Ŀ���������ֵ
    */
    int   getIntValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, int def = 0);
    /**
    * @~english Get the float value at desired index of a child array item from the root node.
    * @~chinese ��ȡһ����json������ָ��λ�ýڵ�ĸ�����ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame idx    @~english index of item in child json @~chinese Ŀ���������json�����е�����ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english float value of item @~chinese Ŀ����ĸ�����ֵ
    */
    float getFloatValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, float def = 0.0f);
    /**
    * @~english Get the boolean value at desired index of a child array item from the root node.
    * @~chinese ��ȡһ����json������ָ��λ�ýڵ�Ĳ�����ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame idx    @~english index of item in child json @~chinese Ŀ���������json�����е�����ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english boolean value of item @~chinese Ŀ����Ĳ�����ֵ
    */
    bool  getBoolValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, bool def = false);
    /**
    * @~english Get the string value at desired index of a child array item from the root node.
    * @~chinese ��ȡһ����json������ָ��λ�ýڵ���ַ���ֵ.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame idx    @~english index of item in child json @~chinese Ŀ���������json�����е�����ֵ
    *
    * @parame def    @~english default value to be returned if child not found
    *                @~chinese ����ӽڵ㲻���ڷ��ص�Ĭ��ֵ
    *
    * @return @~english string value of item @~chinese Ŀ������ַ���ֵ
    */
    const char* getStringValueFromArray_json(const rapidjson::Value& root, const char* arrayKey, int idx, const char *def = NULL);
    /**
    * @~english Get the child json item at desired index of a child array item from the root node.
    * @~chinese ��ȡһ��json������ָ��λ�õ�json��.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese ��json��Ŀ�ļ�ֵ
    *
    * @parame idx    @~english index of item in child json @~chinese Ŀ���������json�����е�����ֵ
    *
    * @return @~english child json item @~chinese ��json��
    */
    const rapidjson::Value &getDictionaryFromArray_json(const rapidjson::Value &root, const char* key, int idx);

    /**
    * @~english Check whether a json item is valid or not.
    * @~chinese ���json���Ƿ���Ч.
    *
    * @parame root   @~english json node to be check @~chinese  ������json��
    *
    * @return @~english if the item is valid @~chinese ��������Ƿ���Ч
    */
    bool checkObjectExist_json(const rapidjson::Value &root);
    /**
    * @~english Check whether a json item is valid or not.
    * @~chinese ���json���Ƿ���Ч.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame key    @~english key of child json item @~chinese �ӽڵ��ֵ
    *
    * @return @~english if the item is valid @~chinese ��������Ƿ���Ч
    */
    bool checkObjectExist_json(const rapidjson::Value &root, const char* key);
    /**
    * @~english Check whether a json item is valid or not.
    * @~chinese ���json���Ƿ���Ч.
    *
    * @parame root   @~english root node of json @~chinese json���ڵ�
    *
    * @parame idx    @~english index of child item @~chinese �ӽڵ�����
    *
    * @return @~english if the item is valid @~chinese ��������Ƿ���Ч
    */
    bool checkObjectExist_json(const rapidjson::Value &root, int index);
};

}

#endif /* defined(__CocoGUI__DictionaryHelper__) */
