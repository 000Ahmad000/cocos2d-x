/****************************************************************************
 Copyright (c) 2015 Chris Hannon http://www.channon.us
 Copyright (c) 2013-2015 Chukong Technologies Inc.

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

*based on the SocketIO library created by LearnBoost at http://socket.io
*using spec version 1 found at https://github.com/LearnBoost/socket.io-spec

Usage is described below, a full working example can be found in TestCpp under ExtionsTest/NetworkTest/SocketIOTest

creating a new connection to a socket.io server running at localhost:3000

    SIOClient *client = SocketIO::connect(*delegate, "ws://localhost:3000");

the connection process will begin and if successful delegate::onOpen will be called
if the connection process results in an error, delegate::onError will be called with the err msg

sending a message to the server

    client->send("Hello!");

emitting an event to be handled by the server, argument json formatting is up to you

    client->emit("eventname", "[{\"arg\":\"value\"}]");

registering an event callback, target should be a member function in a subclass of SIODelegate
CC_CALLBACK_2 is used to wrap the callback with std::bind and store as an SIOEvent

    client->on("eventname", CC_CALLBACK_2(TargetClass::targetfunc, *targetclass_instance));

event target function should match this pattern, *this pointer will be made available

    void TargetClass::targetfunc(SIOClient *, const std::string&)

disconnect from the endpoint by calling disconnect(), onClose will be called on the delegate once complete
in the onClose method the pointer should be set to NULL or used to connect to a new endpoint

    client->disconnect();

 ****************************************************************************/

#ifndef __CC_SOCKETIO_H__
#define __CC_SOCKETIO_H__

#include <string>
#include "platform/CCPlatformMacros.h"
#include "base/CCMap.h"


/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

class SIOClientImpl;
class SIOClient;

/**@~english
 * Singleton and wrapper class to provide static creation method as well as registry of all sockets.
 *
 * @~chinese 
 * һ���򵥷�װ�׽���ע��ľ�̬���������ĵ����ࡣ
 * 
 * @lua NA
 */
class CC_DLL SocketIO
{
public:
    /**
     * @~english Get instance of SocketIO.
     * @~chinese ��ȡSocketIO��ʵ������������
     * 
     * @return @~english the instance of SocketIO.
     * @~chinese SocketIO��ʵ����
     */
    static SocketIO* getInstance();

    /**
     * @~english Destroy the instance of SocketIO.
     * @~chinese ����SocketIO��ʵ������������
     */
    static void destroyInstance();

    /**
     * @~english The delegate class to process socket.io events.
     * @~chinese �����׽����¼��Ĵ����ࡣ
     * 
     * @lua NA
     */
    class SIODelegate
    {
    public:
        /** @~english Destructor of SIODelegate.  @~chinese ����������*/
        virtual ~SIODelegate() {}

        /**@~english
         * This is kept for backwards compatibility, connect is now fired as a socket.io event "connect"
         * 
         * This function would be called when the related SIOClient object receive messages that mean it have connected to endpoint successfully.
         *
         * @~chinese 
         * ���������Ϊ����ǰ�����Զ������ģ�connect��socket.io�°汾�л���"connect"�¼�����
         * 
         * �������������ص�SIOClient�������ӳɹ�ʱ�����á�
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese ���ӵ�SIOClient����
         */
        virtual void onConnect(SIOClient* client) { CC_UNUSED_PARAM(client); CCLOG("SIODelegate onConnect fired"); };

        /**@~english
         * 
         * This is kept for backwards compatibility, message is now fired as a socket.io event "message"
         *
         * This function would be called when the related SIOClient object receive message or json message.
         *
         * @~chinese 
         * ���������Ϊ����ǰ�����Զ������ģ�message��socket.io�°汾�л���"message"�¼�����
         * 
         * �������������ص�SIOClient������յ���Ϣʱ�����á�
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese ���ӵ�SIOClient����
         * @param data @~english the message,it could be json message
         * @~chinese ���յ�����Ϣ,��������json��ʽ�ġ�
         */
        virtual void onMessage(SIOClient* client, const std::string& data) { CC_UNUSED_PARAM(client); CCLOG("SIODelegate onMessage fired with data: %s", data.c_str()); };

        /**@~english
         * This is kept for backwards compatibility, close is now fired as a socket.io event "close"
         *
         * This function would be called when the related SIOClient object disconnect or receive disconnect signal.
         *
         * @~chinese 
         * ���������Ϊ����ǰ�����Զ������ģ�close��socket.io�°汾�л���"close"�¼�����
         * 
         * �������������ص�SIOClient����Ͽ�����ʱ�����á�
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese ���ӵ�SIOClient����
         */
        virtual void onClose(SIOClient* client) = 0;

        /**@~english
         * Pure virtual callback function, this function should be overrided by the subclass.
         *
         * This function would be called when the related SIOClient object receive error signal or didn't connect the endpoint but do some network operation, eg.,send and emit,etc.
         *
         * @~chinese 
         * ����ص�����,�������Ӧ�ñ����า�ǡ�
         * 
         * �������������ص�SIOClient������յ������źŻ����ڶϿ�����״̬��ִ��һЩ�������ʱ�����磺send��emit�ȣ������á�
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese ���ӵ�SIOClient����
         * @param data @~english the error message
         * @~chinese ������Ϣ��
         */
        virtual void onError(SIOClient* client, const std::string& data) = 0;

        /**@~english
         * Fire event to script when the related SIOClient object receive the fire event signal.
         *
         * @~chinese 
         *  ����ص�SIOClient������յ������¼��ź�ʱת���¼����ű��㡣
         * 
         * @param client @~english the connected SIOClient object.
         * @~chinese ���ӵ�SIOClient����
         * @param eventName @~english the event's name.
         * @~chinese �¼������ơ�
         * @param data @~english the event's data information.
         * @~chinese �¼���������Ϣ��
         */
        virtual void fireEventToScript(SIOClient* client, const std::string& eventName, const std::string& data) { CC_UNUSED_PARAM(client); CCLOG("SIODelegate event '%s' fired with data: %s", eventName.c_str(), data.c_str()); };
    };

    /**
     * @~english Static client creation method, similar to socketio.connect(uri) in JS.
     * @~chinese ��̬�����������׽��ֿͻ��ˡ���JS�е�����ʽΪsocketio.connect(uri)
     * 
     * @param uri @~english the URI of the socket.io server.
     * @~chinese �׽��ֵķ����URI��
     * @param delegate @~english the delegate which want to receive events from the socket.io client.
     * @~chinese ���մ���ͻ����¼��Ĵ���
     *
     * @return SIOClient* @~english an initialized SIOClient if connected successfully, otherwise nullptr.
     * @~chinese ������ӳɹ�����һ����ʼ����SIOClient���󣬷��򷵻�nullptr��
     */
    static SIOClient* connect(const std::string& uri, SocketIO::SIODelegate& delegate);

    /**
     * @~english Static client creation method, similar to socketio.connect(uri) in JS.
     * @~chinese ��̬�����������׽��ֿͻ��ˡ���JS�е�����ʽΪsocketio.connect(uri)
     * 
     * @param delegate @~english the delegate which want to receive events from the socket.io client.
     * @~chinese ���մ���ͻ����¼��Ĵ���
     * @param uri @~english the URI of the socket.io server.
     * @~chinese �׽��ֵķ����URI��
     *
     * @return SIOClient* @~english an initialized SIOClient if connected successfully, otherwise nullptr.
     * @~chinese ������ӳɹ�����һ����ʼ����SIOClient���󣬷��򷵻�nullptr��
     */
    CC_DEPRECATED_ATTRIBUTE  static SIOClient* connect(SocketIO::SIODelegate& delegate, const std::string& uri);

private:

    SocketIO();
    virtual ~SocketIO(void);

    static SocketIO *_inst;

    cocos2d::Map<std::string, SIOClientImpl*> _sockets;

    SIOClientImpl* getSocket(const std::string& uri);
    void addSocket(const std::string& uri, SIOClientImpl* socket);
    void removeSocket(const std::string& uri);

    friend class SIOClientImpl;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(SocketIO)
};

//c++11 style callbacks entities will be created using CC_CALLBACK (which uses std::bind)
typedef std::function<void(SIOClient*, const std::string&)> SIOEvent;
//c++11 map to callbacks
typedef std::unordered_map<std::string, SIOEvent> EventRegistry;

/**
 * @~english A single connection to a socket.io endpoint.
 * @~chinese һ���׽������ӡ�
 * 
 * @lua NA
 */
class CC_DLL SIOClient
    : public cocos2d::Ref
{
private:
    int _port;
    std::string _host, _path, _tag;
    bool _connected;
    SIOClientImpl* _socket;

    SocketIO::SIODelegate* _delegate;

    EventRegistry _eventRegistry;

    void fireEvent(const std::string& eventName, const std::string& data);

    void onOpen();
    void onConnect();
    void socketClosed();

    friend class SIOClientImpl;

public:
    /**
     * @~english Construtor of SIOClient class.
     * @~chinese SIOClient���캯����
     * 
     * @param host @~english the string that represent the host address.
     * @~chinese ������ַ���ַ�����ʾ��
     * @param port @~english the int value represent the port number.
     * @~chinese �˿ںš�
     * @param path @~english the string that represent endpoint.
     * @~chinese �ն�·����
     * @param impl @~english the SIOClientImpl object.
     * @~chinese SIOClientImpl����
     * @param delegate @~english the SIODelegate object.
     * @~chinese SIODelegate����
     */
    SIOClient(const std::string& host, int port, const std::string& path, SIOClientImpl* impl, SocketIO::SIODelegate& delegate);

    /**
     * @~english Destructior of SIOClient class.
     * @~chinese ����������
     */
    virtual ~SIOClient();

    /**
     * @~english Get the delegate for the client
     * @~chinese �õ��ͻ��˵Ĵ���
     * 
     * @return @~english the delegate object for the client.
     * @~chinese �ͻ��˵�ί�ж���
     */
    SocketIO::SIODelegate* getDelegate() { return _delegate; };

    /**
     * @~english Disconnect from the endpoint, onClose will be called for the delegate when complete
     * @~chinese �Ͽ���Զ���ն˵����ӣ��Ͽ����ʱ�����onClose�������á�
     */
    void disconnect();

    /**
     * @~english Send a message to the socket.io server.
     * @~chinese ����һ����Ϣ���׽��ַ���ˡ�
     * 
     * @param s @~english message.
     * @~chinese ��Ϣ��
     */
    void send(const std::string& s);
    /**
     * @~english Emit the eventname and the args to the endpoint that _path point to.
     * @~chinese ��_pathָ����ն˷��͸������¼���������
     * 
     * @param eventname @~english the name of event. @~chinese �¼����ơ�
     * @param args @~english the argument of event. @~chinese �¼�������
     */
    void emit(const std::string& eventname, const std::string& args);

    /**@~english
     * Used to register a socket.io event callback.
     * Event argument should be passed using CC_CALLBACK2(&Base::function, this).
     *
     * @~chinese 
     * ע��һ���׽����¼��ص���
     * �ص�����Ӧ��ͨ��CC_CALLBACK2ʹ�á�
     *
     * @param eventName @~english the name of event. @~chinese �¼������ơ�
     * @param e @~english the callback function. @~chinese �ص�������
     */
    void on(const std::string& eventName, SIOEvent e);
    
    /**
     * @~english Set tag of SIOClient.
     * The tag is used to distinguish the various SIOClient objects.
     * @~chinese ��SIOClient���ñ�ǩ�����ڷ������ָ���SIOClient����
     * 
     * @param tag @~english string object.
     * @~chinese ��ǩ���ַ�������
     */
    void setTag(const char* tag);
    

    /**
     * @~english Get tag of SIOClient.
     * @~chinese ��ȡSIOClient�ı�ǩ��
     * 
     * @return const char *  @~english the pointer point to the _tag.
     * @~chinese ��ǩ��ָ�롣
     */
    inline const char* getTag()
    {
        return _tag.c_str();
    };

};

}

NS_CC_END

// end group
/// @}

#endif /* defined(__CC_JSB_SOCKETIO_H__) */
