/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCDATA_H__
#define __CCDATA_H__

#include "platform/CCPlatformMacros.h"
#include <stdint.h> // for ssize_t on android
#include <string>   // for ssize_t on linux
#include "platform/CCStdC.h" // for ssize_t on window


/**
 * @addtogroup base
 * @js NA
 * @lua NA
 */
NS_CC_BEGIN

class CC_DLL Data
{
    friend class Properties;
    
public:

    /**@~english
     * This parameter is defined for convenient reference if a null Data object is needed.
     * @~chinese 
     * �������������Ϊnull Data�����Է�����Ҫʱ�������á�
     */
    static const Data Null;
    

    /**@~english
     * Constructor of Data.
     * @~chinese 
     * Data�Ĺ��캯����
     */
    Data();
    

    /**@~english
     * Copy constructor of Data.
     * @~chinese 
     * Data�Ŀ������캯����
     */
    Data(const Data& other);
    

    /**@~english
     * Copy constructor of Data.
     * @~chinese 
     * Data�Ŀ������캯����
     */
    Data(Data&& other);
    

    /**@~english
     * Destructor of Data.
     * @~chinese 
     * Data������������
     */
    ~Data();
    

    /**@~english
     * Overloads of operator=.
     * @~chinese 
     * ���ظ�ֵ��������
     */
    Data& operator= (const Data& other);
    

    /**@~english
     * Overloads of operator=.
     * @~chinese 
     * ���ظ�ֵ��������
     */
    Data& operator= (Data&& other);
    

    /**@~english
     * Gets internal bytes of Data. It will return the pointer directly used in Data, so don't delete it.
     *
     * @~chinese 
     * ��ȡData���ڲ��ֽڡ������᷵��һ��Data��ֱ��ʹ�õ�ָ��,���Բ�Ҫɾ������
     * 
     * @return @~english Pointer of bytes used internal in Data.
     * @~chinese Data���ڲ�ʹ�õ�ָ�롣
     */
    unsigned char* getBytes() const;
    

    /**@~english
     * Gets the size of the bytes.
     *
     * @~chinese 
     * ��ȡ�ֽڵĴ�С��
     * 
     * @return @~english The size of bytes of Data.
     * @~chinese �ֽڵ����ݵĴ�С��
     */
    ssize_t getSize() const;
    

    /** @~english Copies the buffer pointer and its size.
     * @~chinese ��������ָ������Ĵ�С��
     *  @note @~english This method will copy the whole buffer.
     *        Developer should free the pointer after invoking this method.
     * @~chinese �÷���������������������
     * ������ԱӦ���ڵ�������������ͷ�ָ�롣
     *  @see Data::fastSet
     */
    void copy(const unsigned char* bytes, const ssize_t size);
    

    /** @~english Fast set the buffer pointer and its size. Please use it carefully.
     * @~chinese �������û�����ָ������Ĵ�С����С��ʹ������
     *  @param bytes @~english The buffer pointer, note that it have to be allocated by 'malloc' or 'calloc',
     *         since in the destructor of Data, the buffer will be deleted by 'free'.
     * @~chinese ��������ָ��,ע��,һ��Ҫ�ɡ�malloc����calloc������
     * ��Ϊ��Data������������,������������free��ɾ����
     *  @note @~english 1. This method will move the ownship of 'bytes'pointer to Data,
     *        2. The pointer should not be used outside after it was passed to this method.
     * @~chinese 1���÷����ƶ�bufferָ�������Ȩ,
     * 2�����ָ�벻Ӧ�ڴ��ݸ�����������ٽ���ʹ�á�
     *  @see Data::copy
     */
    void fastSet(unsigned char* bytes, const ssize_t size);
    

    /** @~english
     * Clears data, free buffer and reset data size.
     * @~chinese 
     * �������,�ͷŻ��������������ݴ�С��
     */
    void clear();
    

    /** @~english
     * Check whether the data is null.
     *
     * @~chinese 
     * ��������Ƿ�Ϊ�ա�
     * 
     * @return @~english True if the the Data is null, false if not.
     * @~chinese �������Ϊ�շ�����,������Ƿ��ؼ١�
     */
    bool isNull() const;
    
private:
    void move(Data& other);
    
private:
    unsigned char* _bytes;
    ssize_t _size;
};


NS_CC_END


/** @} */
#endif // __CCDATA_H__
