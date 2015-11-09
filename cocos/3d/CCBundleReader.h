/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __CC_BUNDLE_READER_H__
#define __CC_BUNDLE_READER_H__

#include <string>
#include <vector>

#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCConsole.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class BundleReader
 * @brief @~english BundleReader is an interface for reading sequence of bytes.
 * @~chinese BundleReader�ṩ�˽ӿ����ڶ�ȡ�ֽ�����
 * @js NA
 * @lua NA
 */
class BundleReader: public cocos2d::Ref
{
public:
    /**
     * Constructor.
     */
    BundleReader();
    
    /**
     * Destructor.
     */
    ~BundleReader();
    
    /**
     * @~english Initialise
     * @~chinese ��ʼ��
     * @param buffer @~english The data buffer pointer
     * @~chinese ���ݻ���ָ��
     * @param length @~english The data buffer size
     * @~chinese ���ݻ����С
     */
    void init(char* buffer, ssize_t length);

    /**
     * @~english Reads an array of elements.
     * @~chinese ��ȡһϵ��Ԫ��
     * @param ptr   @~english The pointer to the memory to copy into.
     *              The available size should be at least bytes.
     * @~chinese ָ�򱻿��������ָ�룬��ָ�����ڴ����ڴ��С�����ܹ�������ж�ȡԪ��
     * @param size  @~english The size of each element to be read, in bytes.
     * @~chinese ÿ��Ԫ�ص����ݴ�С�����ֽڼ�
     * @param count @~english The number of elements to read.
     * @~chinese ��Ҫ��ȡ��Ԫ�ظ���
     * @return @~english The number of elements read.
     * @~chinese ��ȡ��Ԫ�ظ���
     */
    ssize_t read(void* ptr, ssize_t size, ssize_t count);

    /**
     * @~english Reads a line from the buffer.
     * @~chinese ���ж�ȡ���ݣ����������ָ���Ļ�����
     * @param num @~english The amount of lines to reads
     * @~chinese ��Ҫ��ȡ������
     * @param line @~english The result
     * @~chinese ��������
     * @return @~english The result, same as line.
     * @~chinese ����ȡ��������ָ�룬��line������ͬ
     */
    char* readLine(int num, char* line);

    /**
     * @~english Check if the file pointer is at the end of the buffer or not.
     * @~chinese ��鵱ǰ���ļ�ָ��(��ָ��)�Ƿ��ڻ������Ľ�β
     * @return @~english Returns true if the end of the buffer has been reached, otherwise returns false.
     * @~chinese ����ڻ�����ĩβ����true����֮����false
     */
    bool eof();

    /**
     * @~english Returns the length of the buffer in bytes.
     * @~chinese ���ػ����С�����ֽڼ�
     */
    ssize_t length();

    /**
     * @~english Returns the position of the file pointer.
     * @~chinese ���ص�ǰ�ļ�ָ�루��ָ�룩���ڻ�������λ��
     * @return @~english @~english The position of the file pointer
     * @~chinese �ļ�ָ���ڻ�������λ��
     */
    ssize_t tell();

    /**
     * @~english Sets the position of the file pointer.
     * @~chinese �����ļ�ָ�루��ָ�룩��λ�ã�����λ�õ��� ��λ�� + ƫ����
     * @param offset @~english The offset
     * @~chinese λ�õ�ƫ����
     * @param origin @~english The base position.
     * @~chinese λ�õĻ�λ��
     * @return @~english The result of the seek
     * @~chinese ���ý��
     */
    bool seek(long int offset, int origin);

    /**
     * @~english Sets the file pointer at the start of the file.
     * @~chinese ���ļ�ָ�루��ָ�룩��Ϊ�ļ��Ŀ�ʼλ��
     * @return @~english The result of the rewind.
     * @~chinese ���ý��
     */
    bool rewind();

    /**
     * @~english Read binary typed value.
     * @~chinese �Զ����Ʒ�ʽ��ȡָ�����͵�ֵ
     * @param ptr @~english The specified type pointer. 
     * @~chinese ָ�����͵����ݽ���ָ��
     * @return @~english The result of the read.
     * @~chinese ��ȡ���
     */
    template<typename T> bool read(T* ptr);

    /**
     * Read binary typed value array.
     * @~chinese �Զ����Ʒ�ʽ��ȡָ�����͵�ֵ����
     * @param length @~english Length of the array @~chinese ����ĳ���
     * @param values @~english Output array to store the result @~chinese ���ڱ�����������
     * @return the result of the read.
     */
    template<typename T> bool readArray(unsigned int* length, std::vector<T>* values);

    /**
     * @~english Read the string from the bundle, first read length, then read string text.
     * @~chinese ��bundle�ж�ȡ�ַ��������Ƚ����ȡ���ȣ�Ȼ���ȡ�ַ������ı�
     * @return @~english The result string.
     * @~chinese ���ر���ȡ���ַ���
     */
    std::string readString();

    /**
     * @~english Read the matrix.
     * @~chinese ��ȡ����
     * @note @~english the matrix type must be the 4*4 float matrix
     * @~chinese �þ��������4*4��float�;���
     * @param m @~english The result matrix.
     * @~chinese Ŀ�����
     * @return @~english The result of the reading.
     * @~chinese ��ȡ�Ľ��
     */
    bool readMatrix(float* m);

private:
    ssize_t _position;
    ssize_t  _length;
    char* _buffer;
};

/// @cond 

/**
* @~english Template read routines
* @~chinese ���ڶ�ȡBundle�������ݵ�ģ�庯��
* @param ptr  @~english The generic type pointer to get the value.
* @~chinese ���Խ������ݵķ���ָ��
* @return @~english The result of the load.
* @~chinese ��ȡ���
*/
template<typename T>
inline bool BundleReader::read(T *ptr)
{
    return (read(ptr, sizeof(T), 1) == 1);
}

/**
* @~english Template function to read array of value.
* @~chinese ���ڴ�bundle�ж�ȡ�����ģ�庯��
* @param length @~english The length of the array.
* @~chinese ����ĳ���
* @param values @~english The result array of value.
* @~chinese ��ȡ���ݵĽ�������
* @return @~english The result of the reading.
* @~chinese ��ȡ���
*/
template<typename T>
inline bool BundleReader::readArray(unsigned int *length, std::vector<T> *values)
{
    if (!read(length))
    {
        return false;
    }
    
    if (*length > 0 && values)
    {
        values->resize(*length);
        if (read(&(*values)[0], sizeof(T), *length) != *length)
        {
            return false;
        }
    }
    return true;
}

/**
* @~english Specalization for char
* @~chinese ģ�庯�����ػ��汾��ר���ڶ�ȡ�ַ�
*/
template<>
inline bool BundleReader::read<char>(char *ptr)
{
    if (read(ptr, sizeof(char), 1) == 1)
    {
        return true;
    }
    else
    {
        *ptr = -1;
        return false;
    }
}

/**
* @~english Specalization for std::string
* @~chinese ģ�庯�����ػ��汾��ר�����ڶ�ȡstd::string���ַ���
*/
template<>
inline bool BundleReader::read<std::string>(std::string *ptr)
{
    CCLOG("can not read std::string, use readString() instead");
    return false;
}

/**
* @~english Template function to read array of value.
* @~chinese ���ڴ�bundle�ж�ȡ�ַ��������ģ�庯���ػ��汾
* @param length @~english The length of the array.
* @~chinese ����ĳ���
* @param values @~english The result array of value.
* @~chinese ��ȡ���ݽ����ַ�������
* @return @~english The result of the reading.
* @~chinese ��ȡ���
*/
template<>
inline bool BundleReader::readArray<std::string>(unsigned int *length, std::vector<std::string> *values)
{
    if (!read(length))
    {
        return false;
    }
    values->clear();
    if (*length > 0 && values)
    {
        for (int i = 0; i < (int)*length; ++i)
        {
            values->push_back(readString());
        }
    }
    return true;
}

/// @endcond

// end of 3d group
/// @}

NS_CC_END

#endif
