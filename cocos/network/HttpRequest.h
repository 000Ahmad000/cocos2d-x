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

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>
#include <vector>
#include "base/CCRef.h"
#include "base/ccMacros.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

class HttpClient;
class HttpResponse;

typedef std::function<void(HttpClient* client, HttpResponse* response)> ccHttpRequestCallback;
typedef void (cocos2d::Ref::*SEL_HttpResponse)(HttpClient* client, HttpResponse* response);
#define httpresponse_selector(_SELECTOR) (cocos2d::network::SEL_HttpResponse)(&_SELECTOR)

/** @~english
 * Defines the object which users must packed for HttpClient::send(HttpRequest*) method.
 * @~chinese 
 * һ���������ݷ�װ�࣬����HttpClient::send��
 * @see tests/test-cpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp
 * @since v2.0.2
 *
 * @lua NA
 */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef DELETE
#undef DELETE
#endif
#endif

class CC_DLL HttpRequest : public Ref
{
public:
    /**@~english
     * The HttpRequest type enum used in the HttpRequest::setRequestType.
     * @~chinese 
     * HttpRequestö���࣬����HttpRequest::setRequestTypeʱ�õ���
     */
    enum class Type
    {
        GET,
        POST,
        PUT,
        DELETE,
        UNKNOWN,
    };
    
    /** @~english
     *  Constructor.
     *   Because HttpRequest object will be used between UI thread and network thread,
         requestObj->autorelease() is forbidden to avoid crashes in AutoreleasePool
         new/retain/release still works, which means you need to release it manually
     * @~chinese 
     * ���캯����
     * ��ΪHttpRequest���󽫻���UI�̺߳������߳���ʹ�ã�����requestObj->autorelease()�Ǳ���ֹ�ģ��������Ա���AutoreleasePool�еı�����
     * new/retain/release������Ч������ζ������Ҫ�ֶ��ĵ���release������
     * @see httprequest.cpp��
     */
    HttpRequest()
    {
        _requestType = Type::UNKNOWN;
        _url.clear();
        _requestData.clear();
        _tag.clear();
        _pTarget = nullptr;
        _pSelector = nullptr;
        _pCallback = nullptr;
        _pUserData = nullptr;
    };
    
    /** @~english Destructor.  @~chinese ����������*/
    virtual ~HttpRequest()
    {
        if (_pTarget)
        {
            _pTarget->release();
        }
    };
    
    /** @~english
     * Override autorelease method to avoid developers to call it.
     * If this function was called, it would trigger assert in debug mode
     *
     * @~chinese 
     * ����autorelease�������⿪���ߵ��á�
     * ���������������ã���debugģʽ�½��ᴥ��assert
     * 
     * @return Ref* @~english always return nullptr.
     * @~chinese ʼ�շ���nullptr��
     */
    Ref* autorelease(void)
    {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return NULL;
    }
            
    // setter/getters for properties
     
    /** @~english
     * Set request type of HttpRequest object before being sent,now it support the enum value of HttpRequest::Type.
     *
     * @~chinese 
     * �ڷ���HttpRequest����ǰ������HttpRequest������ֵ����������HttpRequest::Type��ö�������е�����һ��ֵ��
     * 
     * @param type @~english the request type.
     * @~chinese �������͡�
     */
    inline void setRequestType(Type type)
    {
        _requestType = type;
    };
    /** @~english
     * Get the request type of HttpRequest object.
     *
     * @~chinese 
     * ��ȡHttpRequest������������͡�
     * 
     * @return @~english HttpRequest::Type.
     * @~chinese HttpRequest::Type��
     */
    inline Type getRequestType()
    {
        return _requestType;
    };
    
    /** @~english
     * Set the url address of HttpRequest object.
     * The url value could be like these: "http://httpbin.org/ip" or "https://httpbin.org/get"
     *
     * @~chinese
     * ����HttpRequest�����url��
     * url��ֵ����:��http://httpbin.org/ip����https://httpbin.org/get��
     * 
     * @param url @~english the string pointer to the url.
     * @~chinese url�ַ���ָ�롣
     */
    inline void setUrl(const char* url)
    {
        _url = url;
    };
    /** @~english
     * Get the url address of HttpRequest object.
     *
     * @~chinese 
     * ��ȡHttpRequest�����url�ַ���ָ�롣
     * 
     * @return @~english const char* the pointer of _url.
     * @~chinese ָ��url���ַ���ָ�롣
     */
    inline const char* getUrl()
    {
        return _url.c_str();
    };
    
    /** @~english
     * Set the request data of HttpRequest object.
     *
     * @~chinese 
     * ����HttpRequest������������ݡ�
     * 
     * @param buffer @~english the buffer of request data, it support binary data.
     * @~chinese �������ݵĻ���ָ��,��֧�ֶ��������ݡ�
     * @param len @~english the size of request data.
     * @~chinese �������ݵĴ�С��
     */
    inline void setRequestData(const char* buffer, size_t len)
    {
        _requestData.assign(buffer, buffer + len);
    };
    /** @~english
     * Get the request data pointer of HttpRequest object.
     *
     * @~chinese 
     * ��ȡHttpRequest�����������ݵ�ָ�롣
     * 
     * @return @~english char* the request data pointer.
     * @~chinese ָ���������ݵ�ָ�롣
     */
    inline char* getRequestData()
    {
        if(_requestData.size() != 0)
            return &(_requestData.front());

        return nullptr;
    }
    /** @~english
     * Get the size of request data
     *
     * @~chinese 
     * ����������ݵĴ�С
     * 
     * @return @~english ssize_t the size of request data
     * @~chinese �������ݵĴ�С
     */
    inline ssize_t getRequestDataSize()
    {
        return _requestData.size();
    }
    
    /** @~english
     * Set a string tag to identify your request.
     * This tag can be found in HttpResponse->getHttpRequest->getTag().
     *
     * @~chinese 
     * �����ַ�����ǩ����ʶ��request��
     * ����ַ�����ǩ����ͨ��HttpResponse->getHttpRequest->getTag()��á�
     * 
     * @param tag @~english the string pointer to tag
     * @~chinese ָ���ǩ���ַ���ָ�롣
     */
    inline void setTag(const char* tag)
    {
        _tag = tag;
    };
    /** @~english
     * Get the string tag to identify the request.
     * The best practice is to use it in your MyClass::onMyHttpRequestCompleted(sender, HttpResponse*) callback.
     *
     * @~chinese 
     * ��ȡ����ʶ��request���ַ�����ǩ��
     * ��ѵ�ʹ�õ�����MyClass::onMyHttpRequestCompleted(���ͷ�,HttpResponse *)�ص���ʹ�á�
     * 
     * @return @~english const char* the pointer of _tag
     * @~chinese ָ��_tag���ַ���ָ��
     */
    inline const char* getTag()
    {
        return _tag.c_str();
    };
    
    /**@~english
     * Set user-customed data of HttpRequest object.
     * You can attach a customed data in each request, and get it back in response callback.
     * But you need to new/delete the data pointer manually.
     *
     * @~chinese 
     * ����HttpRequest������û��Զ������ݡ�
     * �������ÿһ��request�и���һ���Զ������ݣ�Ȼ������Ӧ�ص���ȡ��������ݡ�
     * �����Զ������ݣ�����Ҫ�ֶ���new/delete����ָ��
     * 
     * @param pUserData @~english the pointer point to customed data
     * @~chinese �Զ�������ָ��
     */
    inline void setUserData(void* pUserData)
    {
        _pUserData = pUserData;
    };
    /** @~english
     * Get the user-customed data pointer which were pre-setted.
     * Don't forget to delete it. HttpClient/HttpResponse/HttpRequest will do nothing with this pointer.
     *
     * @~chinese 
     * ��ȡԤ����û��Զ�������ָ�롣
     * ��Ҫ����delete����HttpClient��HttpResponse��HttpRequest����������ָ����д���
     * 
     * @return @~english void* the pointer of user-customed data.
     * @~chinese ָ���û��Զ������ݵ�ָ�롣
     */
    inline void* getUserData()
    {
        return _pUserData;
    };
    
    /**@~english
     * Set the target and related callback selector.
     * When response come back, it would call (pTarget->*pSelector) to process something.
     *
     * @~chinese 
     * ����target����صĻص���������
     * ����Ӧ����ʱ,��������(pTarget->*pSelector)������һЩ���顣
     * 
     * @param pTarget @~english the target object pointer.
     * @~chinese Ŀ�����ָ�롣
     * @param pSelector @~english the callback function.
     * @~chinese �ص�������
     */
    CC_DEPRECATED_ATTRIBUTE inline void setResponseCallback(Ref* pTarget, SEL_CallFuncND pSelector)
    {
        setResponseCallback(pTarget, (SEL_HttpResponse) pSelector);
    }
    
    /**@~english
     * Set the target and related callback selector of HttpRequest object.
     * When response come back, we would call (pTarget->*pSelector) to process response data.
     *
     * @~chinese 
     * ����target����ػص�������
     * ����Ӧ����ʱ,���ǽ�����(pTarget->*pSelector)��������Ӧ���ݡ�
     * 
     * @param pTarget @~english the target object pointer.
     * @~chinese Ŀ�����ָ�롣
     * @param pSelector @~english the SEL_HttpResponse function.
     * @~chinese �ص�������
     */
    CC_DEPRECATED_ATTRIBUTE inline void setResponseCallback(Ref* pTarget, SEL_HttpResponse pSelector)
    {
        _pTarget = pTarget;
        _pSelector = pSelector;
        
        if (_pTarget)
        {
            _pTarget->retain();
        }
    }
    /**@~english
     * Set response callback function of HttpRequest object.
     * When response come back, we would call _pCallback to process response data.
     *
     * @~chinese 
     * ����HttpRequest�������Ӧ�ص�������
     * ����Ӧ����ʱ,�������_pCallback��������Ӧ���ݡ�
     * 
     * @param callback @~english the ccHttpRequestCallback function.
     * @~chinese ccHttpRequestCallback������
     */
    inline void setResponseCallback(const ccHttpRequestCallback& callback)
    {
        _pCallback = callback;
    }
    
    /** @~english
     * Get the target of callback selector function, mainly used by HttpClient.
     *
     * @~chinese 
     * ��ȡ�ص�������target������Ҫ����HttpClient��
     * 
     * @return @~english Ref* the target of callback selector funtion
     * @~chinese �ص�������target����
     */
    inline Ref* getTarget()
    {
        return _pTarget;
    }

    /**@~english
     * This sub class is just for migration SEL_CallFuncND to SEL_HttpResponse,someday this way will be removed.
     * 
     * @~chinese 
     * ���ڽ�SEL_CallFuncNDת����SEL_HttpResponse�����࣬����ཫ�ᱻ�Ƴ���
     * 
     * @lua NA
     */
    class _prxy
    {
    public:
        /** @~english Constructor.  @~chinese ���캯����*/
        _prxy( SEL_HttpResponse cb ) :_cb(cb) {}
        /** @~english Destructor.  @~chinese ����������*/
        ~_prxy(){};
        /** @~english operator override.  @~chinese ���������ء�*/
        operator SEL_HttpResponse() const { return _cb; }
        CC_DEPRECATED_ATTRIBUTE operator SEL_CallFuncND()   const { return (SEL_CallFuncND) _cb; }
    protected:
        SEL_HttpResponse _cb;
    };
    
    /** @~english
     * Get _prxy object by the _pSelector.
     *
     * @~chinese 
     * ����_pSelector��ȡ_prxy����
     * 
     * @return @~english the _prxy object
     * @~chinese _prxy����
     */
    inline _prxy getSelector()
    {
        return _prxy(_pSelector);
    }
    
    /**@~english
     * Get ccHttpRequestCallback callback function.
     *
     * @~chinese 
     * ��ȡccHttpRequestCallback�ص�������
     * 
     * @return @~english ccHttpRequestCallback callback function.
     * @~chinese ccHttpRequestCallback�ص�������
     */
    inline const ccHttpRequestCallback& getCallback()
    {
        return _pCallback;
    }
    
    /** @~english
     * Set custom-defined headers.
     *
     * @~chinese 
     * �����Զ��������ͷ��
     * 
     * @param pHeaders @~english the string vector of custom-defined headers.
     * @~chinese �����Զ�������ͷ��std::vector<std::string>��
     */
    inline void setHeaders(std::vector<std::string> pHeaders)
   	{
   		_headers=pHeaders;
   	}
   
    /** @~english
     * Get custom headers.
     *
     * @~chinese 
     * ��ȡ�Զ��������ͷ��
     * 
     * @return @~english the string vector of custom-defined headers.
     * @~chinese �����Զ�������ͷ��std::vector<std::string>��
     */
   	inline std::vector<std::string> getHeaders()
   	{
   		return _headers;
   	}
    
protected:
    // properties
    Type                        _requestType;    /// kHttpRequestGet, kHttpRequestPost or other enums
    std::string                 _url;            /// target url that this request is sent to
    std::vector<char>           _requestData;    /// used for POST
    std::string                 _tag;            /// user defined tag, to identify different requests in response callback
    Ref*                        _pTarget;        /// callback target of pSelector function
    SEL_HttpResponse            _pSelector;      /// callback function, e.g. MyLayer::onHttpResponse(HttpClient *sender, HttpResponse * response)
    ccHttpRequestCallback       _pCallback;      /// C++11 style callbacks
    void*                       _pUserData;      /// You can add your customed data here 
    std::vector<std::string>    _headers;		      /// custom http headers
};

}

NS_CC_END

// end group
/// @}

#endif //__HTTP_REQUEST_H__
