/****************************************************************************
 Copyright (c) 2012      greathqy
 Copyright (c) 2012      cocos2d-x.org
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

#ifndef __CCHTTPCLIENT_H__
#define __CCHTTPCLIENT_H__

#include <thread>
#include <condition_variable>
#include "base/CCVector.h"
#include "base/CCScheduler.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpCookie.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {
    


/** @~english Singleton that handles asynchronous http requests.
 *
 * Once the request completed, a callback will be issued in main thread when it provided during make request.
 *
 * @~chinese ���ڴ����첽http����ĵ�����
 *
 * һ�����һ������,������һ�����߳��е��õĻص����������������󷵻ش���
 * 
 * @lua NA
 */
class CC_DLL HttpClient
{
public:
	/**@~english
	* The buffer size of _responseMessage
    * @~chinese 
    * _responseMessage�Ļ����С
	*/
	static const int RESPONSE_BUFFER_SIZE = 256;

    /**@~english
     * Get instance of HttpClient.
     *
     * @~chinese 
     * HttpClient��ʵ����
     * 
     * @return @~english the instance of HttpClient.
     * @~chinese HttpClientʵ����
     */
    static HttpClient *getInstance();
    
    /** @~english
     * Destroy the instance of HttpClient. 
     * @~chinese 
     * ����HttpClientʵ����
     */
    static void destroyInstance();

    /** @~english
     * Enable cookie support.
     *
     * @~chinese 
     * ����cookie֧�֡�
     * 
     * @param cookieFile @~english the filepath of cookie file.
     * @~chinese cookie�ļ����ļ�����
     */
    void enableCookies(const char* cookieFile);
    
    /**@~english
     * Get the cookie filename
     * 
     * @~chinese 
     * ��ȡCookie�ļ���
     * 
     * @return @~english the cookie filename
     * @~chinese Cookie�ļ���
     */
    const std::string& getCookieFilename();
    
    /**@~english
     * Set root certificate path for SSL verification.
     *
     * @~chinese 
     * ����SSL֤��·����
     * 
     * @param caFile @~english a full path of root certificate.if it is empty, SSL verification is disabled.
     * @~chinese SSL֤���ȫ·����������ֵΪ��, SSL��֤������Ч��
     */
    void setSSLVerification(const std::string& caFile);
    
    /**@~english
     * Get ths SSL CA filename
     * 
     * @~chinese 
     * ���SSL֤����ļ���
     * 
     * @return @~english the SSL CA filename
     * @~chinese SSL֤���ļ���
     */
    const std::string& getSSLVerification();
        
    /**@~english
     * Add a request to task queue
     *
     * @~chinese 
     * ���һ��request�����������
     * 
     * @param request @~english a HttpRequest object, which includes url, response callback etc.
     * @~chinese һ��HttpRequest����,����url,��Ӧ�ص��ȡ�
     */
    void send(HttpRequest* request);

    /**@~english
     * Immediate send a request
     *
     * @~chinese 
     * ��������һ��request
     * 
     * @param request @~english a HttpRequest object, which includes url, response callback etc.
     * @~chinese HttpRequest����,����url,��Ӧ�ص��ȡ�
     */
    void sendImmediate(HttpRequest* request);
    
    /**@~english
     * Set the timeout value for connecting in seconds.
     *
     * @~chinese 
     * ����Ϊ��λ�������ӳ�ʱʱ�䡣
     * 
     * @param value @~english the timeout value for connecting in seconds.
     * @~chinese ����Ϊ��λ�����ӳ�ʱʱ�䡣
     */
    void setTimeoutForConnect(int value);
    
    /**@~english
     * Get the timeout value for connecting in seconds.
     *
     * @~chinese 
     * ��ȡ����Ϊ��Ȭ�����ӳ�ʱʱ�䡣
     * 
     * @return @~english the timeout value for connecting in seconds.
     * @~chinese ����Ϊ��λ�����ӳ�ʱʱ�䡣
     */
    int getTimeoutForConnect();
    
    /**@~english
     * Set the timeout value for reading in seconds.
     *
     * @~chinese 
     * ��������Ϊ��λ��read��ʱʱ�䡣
     * 
     * @param value @~english the timeout value for reading in seconds.
     * @~chinese ����Ϊ��λ��read��ʱʱ�䡣
     */
    void setTimeoutForRead(int value);

    /**@~english
     * Get the timeout value for reading in seconds.
     *
     * @~chinese 
     * �������Ϊ��λ��read��ʱʱ�䡣
     * 
     * @return @~english the timeout value for reading in seconds.
     * @~chinese ����Ϊ��λ��read��ʱʱ�䡣
     */
    int getTimeoutForRead();
    
    /**@~english
     *Get the Cookie object
     *
     *@~chinese
     *��ȡCookie����
     *
     * @return @~english the Cookie object
     * @~chinese Cookie����
     */
    HttpCookie* getCookie() const {return _cookie; }
    
    /**@~english
     *Get the _cookieFileMutex that represents the std::mutex of the cookie files
     *
     *@~chinese
     *��ȡcookie�ļ�������_cookieFileMutex
     *
     * @return @~english the std::mutex 
     * @~chinese std::mutex
     */
    std::mutex& getCookieFileMutex() {return _cookieFileMutex;}
    
    /**@~english
     *Get the _sslCaFileMutex that represents the std::mutex of the SSL files
     *
     *@~chinese
     *��ȡSSL�ļ�������_cookieFileMutex
     *
     * @return @~english the std::mutex 
     * @~chinese std::mutex
     */
    std::mutex& getSSLCaFileMutex() {return _sslCaFileMutex;}
private:
    HttpClient();
    virtual ~HttpClient();
    bool init(void);
    
    /**@~english
     * Init pthread mutex, semaphore, and create new thread for http requests
     * @~chinese 
     * ��ʼ��pthread�����ź���,Ϊhttp���󴴽����߳�
     * @return @~english bool
     * @~chinese boolֵ
     */
    bool lazyInitThreadSemphore();
    void networkThread();
    void networkThreadAlone(HttpRequest* request, HttpResponse* response);

    void dispatchResponseCallbacks();
    
    void processResponse(HttpResponse* response, char* responseMessage);
    void increaseThreadCount();
    void decreaseThreadCountAndMayDeleteThis();
    
private:
    bool _isInited;
    
    int _timeoutForConnect;
    std::mutex _timeoutForConnectMutex;
    
    int _timeoutForRead;
    std::mutex _timeoutForReadMutex;
    
    int  _threadCount;
    std::mutex _threadCountMutex;
    
    Scheduler* _scheduler;
    std::mutex _schedulerMutex;
    
    Vector<HttpRequest*>  _requestQueue;
    std::mutex _requestQueueMutex;
    
    Vector<HttpResponse*> _responseQueue;
    std::mutex _responseQueueMutex;
    
    std::string _cookieFilename;
    std::mutex _cookieFileMutex;
    
    std::string _sslCaFilename;
    std::mutex _sslCaFileMutex;
    
    HttpCookie* _cookie;
    
    std::condition_variable_any _sleepCondition;
    
	char _responseMessage[RESPONSE_BUFFER_SIZE];
    
    HttpRequest* _requestSentinel;
};

} // namespace network

NS_CC_END

// end group
/// @}

#endif //__CCHTTPCLIENT_H__
