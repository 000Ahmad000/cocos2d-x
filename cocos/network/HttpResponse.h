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

#ifndef __HTTP_RESPONSE__
#define __HTTP_RESPONSE__

#include "network/HttpRequest.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

/** 
 * @brief @~english A HttpResponse class is wrapped to the related responsed data came back from the HttpClient.
 * @~chinese HttpResponse�Ƕ�HttpClient���ص���Ӧ���ݵķ�װ��
 * @see samples/TestCpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp.
 * @since v2.0.2.
 * @lua NA
 */
class CC_DLL HttpResponse : public cocos2d::Ref
{
public:
    /** @~english
     * Constructor, it's used by HttpClient internal, users don't need to create HttpResponse manually.
     * @~chinese 
     * ���캯��,HttpResponse��HttpClient�ڲ�����,�û�����Ҫ�ֶ�����HttpResponse��
     * @param request @~english the corresponding HttpRequest which leads to this response.
     * @~chinese ��Ӧ��HttpRequest����
     */
    HttpResponse(HttpRequest* request)
    {
        _pHttpRequest = request;
        if (_pHttpRequest)
        {
            _pHttpRequest->retain();
        }
        
        _succeed = false;
        _responseData.clear();
        _errorBuffer.clear();
        _responseDataString = "";
    }
    
    /** @~english
     * Destructor, it will be called in HttpClient internal.
     * Users don't need to destruct HttpResponse object manually.
     * @~chinese 
     * ��������ʱ, ��Ҳ��HttpClient�ڲ����á�
     * �û������ֶ��Ĵ����������������
     */
    virtual ~HttpResponse()
    {
        if (_pHttpRequest)
        {
            _pHttpRequest->release();
        }
    }
    
    /** @~english
     * Override autorelease method to prevent developers from calling it.
     * If this method is called , it would trigger CCASSERT.
     * @~chinese 
     * ��дautorelease�������Է������ߵ�������
     * ���������������ʱ,��������CCASSERT��
     * @return @~english always return nullptr.
     * @~chinese ʼ�շ���nullptr��
     */
    cocos2d::Ref* autorelease(void)
    {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                        therefore, autorelease is forbidden here");
        return NULL;
    }
    
    // getters, will be called by users
    
    /** @~english
     * Get the corresponding HttpRequest object which leads to this response.
     * There's no paired setter for it, because it's already setted in class constructor.
     * @~chinese 
     * ��ö�Ӧ�����Ӧ��HttpRequest����
     * ����û�ж�Ӧ��setter��������Ϊ_pHttpRequest���ڹ��캯���и�ֵ�ġ�
     * @return @~english the corresponding HttpRequest object which leads to this response.
     * @~chinese ��Ӧ�����Ӧ��HttpRequest����
     */
    inline HttpRequest* getHttpRequest()
    {
        return _pHttpRequest;
    }
        
    /** @~english
     * To see if the HttpReqeust is returned successfully.
     * Althrough users can judge if (http response code == 200), we want an easier way.
     * If this getter returns false, you can call getResponseCode and getErrorBuffer to find more details.
     * @~chinese 
     * �ж�HttpReqeust�Ƿ񷵻سɹ���
     * ��Ȼ�û�����ͨ��(response code == 200)�Ƿ�������ж�,������Ҳ��Ҫһ�ָ��򵥵ķ�����
     * �������ʧ��,����ͨ������getResponseCode��getErrorBuffer��ȡ�����ϸ�ڡ�
     * @return @~english bool the flag that represent whether the http request return sucesssfully or not.
     * @~chinese �ж�HttpReqeust�Ƿ񷵻سɹ��ı�ǡ�
     */
    inline bool isSucceed()
    {
        return _succeed;
    };
    
    /** @~english
     * Get the http response data.
     * @~chinese 
     * ��ȡhttp��Ӧ���ݡ�
     * @return @~english the pointer that point to the _responseData.
     * @~chinese ָ��_responseData��ָ�롣
     */
    inline std::vector<char>* getResponseData()
    {
        return &_responseData;
    }
    
    /**@~english
     * Get the response headers.
     * @~chinese 
     * ��Ӧͷ��
     * @return @~english the pointer that point to the _responseHeader.
     * @~chinese ָ��_responseHeader��ָ�롣
     */
    inline std::vector<char>* getResponseHeader()
    {
        return &_responseHeader;
    }

    /** @~english
     * Get the http response code to judge whether response is successful or not.
     * If _responseCode is not 200, you should check the meaning for _responseCode by the net.
     * @~chinese 
     * ��ȡ��Ӧ�������ж���Ӧ�ɹ����
     * ��_responseCode��Ϊ200ʱ����Ӧ��ͨ���������һ�¶�Ӧ��Ӧ������塣
     * @return @~english the value of _responseCode
     * @~chinese _responseCode�ļ�ֵ
     */
    inline long getResponseCode()
    {
        return _responseCode;
    }

    /** @~english
     * Get the error buffer which will tell you more about the reason why http request failed.
     * @~chinese 
     * ��ȡ���󻺴棬��������ϸ������HttpRequestʧ�ܵ�ԭ��
     * @return @~english the pointer that point to _errorBuffer.
     * @~chinese ָ��_errorBuffer��ָ�롣
     */
    inline const char* getErrorBuffer()
    {
        return _errorBuffer.c_str();
    }
    
    // setters, will be called by HttpClient
    // users should avoid invoking these methods
    
    
    /** @~english
     * Set whether the http request is returned successfully or not,
     * This setter is mainly used in HttpClient, users mustn't set it directly
     * @~chinese 
     * ����http request�Ƿ�ɹ��ı��,
     * ���setter��HttpClient������,�û�����ֱ�ӵ��á�
     * @param value @~english the flag represent whether the http request is successful or not.
     * @~chinese �Ƿ�ɹ��ı�ǡ�
     */
    inline void setSucceed(bool value)
    {
        _succeed = value;
    };
    
    
    /** @~english
     * Set the http response data buffer, it is used by HttpClient.
     * @~chinese 
     * ����http��Ӧ�����ݻ���,����HttpClient���á�
     * @param data @~english the pointer point to the response data buffer.
     * @~chinese ָ��response���ݻ�������ָ�롣
     */
    inline void setResponseData(std::vector<char>* data)
    {
        _responseData = *data;
    }
    
    /** @~english
     * Set the http response headers buffer, it is used by HttpClient.
     * @~chinese 
     * ����http����Ӧͷ����,����HttpClient���á�
     * @param data @~english the pointer point to the response headers buffer.
     * @~chinese ָ��response headers��������ָ�롣
     */
    inline void setResponseHeader(std::vector<char>* data)
    {
        _responseHeader = *data;
    }
    
    
    /** @~english
     * Set the http response code.
     * @~chinese 
     * ����http��Ӧ�롣
     * @param value @~english the http response code that represent whether the request is successful or not.
     * @~chinese http��Ӧ����,��ʾ����ɹ����
     */
    inline void setResponseCode(long value)
    {
        _responseCode = value;
    }
    
    
    /** @~english
     * Set the error buffer which will tell you more the reason why http request failed.
     * @~chinese 
     * ����http��Ӧ�Ĵ��󻺴棬�����������������http����ʧ�ܵ�ԭ��
     * @param value @~english a string pointer that point to the reason.
     * @~chinese ָ����󻺴��ָ�롣
     */
    inline void setErrorBuffer(const char* value)
    {
        _errorBuffer.clear();
        _errorBuffer.assign(value);
    };
    
    /**@~english
     * Set the response data by the string pointer and the defined size.
     * @~chinese 
     * ����ָ����С���ַ���ָ��������Ӧ���ݡ�
     * @param value @~english a string pointer that point to response data buffer.
     * @~chinese ָ����Ӧ���ݻ����ָ�롣
     * @param n @~english the defined size that the response data buffer would be copied.
     * @~chinese ��value��������Ӧ���ݵĴ�С��
     */
    inline void setResponseDataString(const char* value, size_t n)
    {
        _responseDataString.clear();
        _responseDataString.assign(value, n);
    }
    
    /**@~english
     * Get the string pointer that point to the response data.
     * @~chinese 
     * ��ȡ��Ӧ���ݵ��ַ���ָ�롣
     * @return @~english the string pointer that point to the response data.
     * @~chinese ָ����Ӧ���ݵ��ַ���ָ�롣
     */
    inline const char* getResponseDataString()
    {
        return _responseDataString.c_str();
    }
    
protected:
    bool initWithRequest(HttpRequest* request);
    
    // properties
    HttpRequest*        _pHttpRequest;  /// the corresponding HttpRequest pointer who leads to this response 
    bool                _succeed;       /// to indecate if the http request is successful simply
    std::vector<char>   _responseData;  /// the returned raw data. You can also dump it as a string
    std::vector<char>   _responseHeader;  /// the returned raw header data. You can also dump it as a string
    long                _responseCode;    /// the status code returned from libcurl, e.g. 200, 404
    std::string         _errorBuffer;   /// if _responseCode != 200, please read _errorBuffer to find the reason
    std::string         _responseDataString; // the returned raw data. You can also dump it as a string
    
};

}

NS_CC_END

// end group
/// @}

#endif //__HTTP_RESPONSE_H__
