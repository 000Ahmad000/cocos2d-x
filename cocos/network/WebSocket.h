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

"[WebSocket module] is based in part on the work of the libwebsockets  project
(http://libwebsockets.org)"

 ****************************************************************************/

#ifndef __CC_WEBSOCKET_H__
#define __CC_WEBSOCKET_H__

#include <string>
#include <vector>

#include "platform/CCPlatformMacros.h"
#include "platform/CCStdC.h"

struct libwebsocket;
struct libwebsocket_context;
struct libwebsocket_protocols;

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

class WsThreadHelper;
class WsMessage;

/**
 * @ WebSocket 
 * @brief @~english WebSocket is wrapper of the libwebsockets-protocol, let the developer could call the websocket easily.
 * @~chinese WebSocket��libwebsockets-protocol�ĸ߲��װ�������ÿ������ܷ���ĵ���websocket�Ĺ��ܡ�
 */
class CC_DLL WebSocket
{
public:
    /**
     * @~english Construtor of WebSocket.
     * @~chinese ���캯��
     * @js ctor
     */
    WebSocket();
    /**
     * @~english Destructor of WebSocket.
     * @~chinese ��������
     * @js NA
     * @lua NA
     */
    virtual ~WebSocket();

    /**
     * @~english Data structure for message
     * @~chinese message�����ݽṹ
     */
    struct Data
    {
        Data():bytes(nullptr), len(0), issued(0), isBinary(false){}
        char* bytes;
        ssize_t len, issued;
        bool isBinary;
    };

    /**
     * @~english ErrorCode enum used to represent the error in the Websocket.
     * @~chinese Websocket�Ĵ�����ö��
     */
    enum class ErrorCode
    {
        TIME_OUT,           /** &lt; value 0 */
        CONNECTION_FAILURE, /** &lt; value 1 */
        UNKNOWN,            /** &lt; value 2 */
    };

    /**
     *@~english State enum used to represent the Websocket state.
     *@~chinese Websocket��״̬ö��
     */
    enum class State
    {
        CONNECTING,  /** &lt; value 0 */
        OPEN,        /** &lt; value 1 */
        CLOSING,     /** &lt; value 2 */
        CLOSED,      /** &lt; value 3 */
    };

    /**
     * @~english The delegate class is used to process websocket events.
     * The most member function are pure virtual functions,they should be implemented the in subclass.
     * @~chinese ���ڴ���websocket�¼��Ĵ����ࡣ������Ա����Ϊ���麯����������Ҫ��������ʵ�֡�
     * @lua NA
     */
    class Delegate
    {
    public:
        /** Destructor of Delegate. */
        virtual ~Delegate() {}
        /**
         * @~english This function to be called after the client connection complete a handshake with the remote server.
         *This means that the WebSocket connection is ready to send and receive data.
         * @~chinese ��������ڿͻ�����ɺ�Զ�̷��������ֺ󱻵��ã�����ζ��WebSocket�Ѿ�׼���÷��ͺͽ��������ˡ�
         * @param ws @~english The WebSocket object connected. @~chinese �����ϵ�WebSocket��
         */
        virtual void onOpen(WebSocket* ws) = 0;
        /**
         * @~english This function to be called when data has appeared from the server for the client connection.
         * @~chinese �������ݴӷ���˴���ʱ�������������
         * @param ws @~english The WebSocket object connected. @~chinese �����ϵ�WebSocket��
         * @param data @~english Data object for message. @~chinese ��Ϣ���ݡ�
         */
        virtual void onMessage(WebSocket* ws, const Data& data) = 0;
        /**
         * @~english When the WebSocket object connected wants to close or the protocol won't get used at all and current _readyState is State::CLOSING,this function is to be called.
         * @~chinese ���������ϵ�WebSocket������رջ��߲�ʹ��Э�鲢�ҵ�ǰ��_readyState��State::CLOSINGʱ������������ᴥ����
         * @param ws @~english The WebSocket object connected. @~chinese �����ϵ�WebSocket��
         */
        virtual void onClose(WebSocket* ws) = 0;
        /**
         * @~english This function is to be called in the following cases:
         * 1. client connection is failed.
         * 2. the request client connection has been unable to complete a handshake with the remote server.
         * 3. the protocol won't get used at all after this callback and current _readyState is State::CONNECTING.
         * 4. when a socket descriptor needs to be removed from an external polling array. in is again the struct libwebsocket_pollargs containing the fd member to be removed. If you are using the internal polling loop, you can just ignore it and current _readyState is State::CONNECTING.
         * @~chinese ������������¼�������»ᱻ����:
         * 1. ����ʧ��
         * 2. �ͻ��˺ͷ��������ʧ��
         * 3. ������ʹ��Э�鲢�ҵ�ǰ��_readyStateΪState::CONNECTING
         * 4. ��һ��socket��������Ҫ���ⲿ��ѯ�������������Ƴ�ʱ������fd��Ա��libwebsocket_pollargs�ṹҲҪ���Ƴ����������ʹ���ڲ���ѯѭ��ʱ����ɺ��������ҵ�ǰ��_readyStateΪState::CONNECTING.
         * @param ws @~english The WebSocket object connected. @~chinese �����ϵ�WebSocket��
         * @param error @~english WebSocket::ErrorCode enum,would be ErrorCode::TIME_OUT or ErrorCode::CONNECTION_FAILURE. @~chinese WebSocket�Ĵ�����ö�٣�����ΪErrorCode::TIME_OUT��ErrorCode::CONNECTION_FAILURE��
         */
        virtual void onError(WebSocket* ws, const ErrorCode& error) = 0;
    };


    /**
     *  @~english The initialized method for websocket.
     *            It needs to be invoked right after websocket instance is allocated.
     *  @~chinese WebSocket�ĳ�ʼ������������WebSocketʵ��������󱻴�����
     *  @param  delegate @~english The delegate which want to receive event from websocket. @~chinese ��������websocket
     *  @param  url      @~english The URL of websocket server. @~chinese websocket�����URL��ַ
     *  @param  protocols @~english The protocol of the socket. @~chinese websocket������Э�顣
     *  @return @~english true: Success, false: Failure. @~chinese true:�ɹ���false:ʧ��
     *  @lua NA
     */
    bool init(const Delegate& delegate,
              const std::string& url,
              const std::vector<std::string>* protocols = nullptr);

    /**
     *  @~english Sends string data to websocket server. @~chinese ��websocket����˷����ַ�������
     *  
     *  @param message @~english string data. @~chinese �ַ�������
     *  @lua sendstring
     */
    void send(const std::string& message);

    /**
     *  @~english Sends binary data to websocket server. @~chinese ��websocket����˷��Ͷ���������
     *  
     *  @param binaryMsg @~english binary string data. @~chinese �������ַ�������
     *  @param len @~english the size of binary string data. @~chinese �������ַ������ݵĳ���
     *  @lua sendstring
     */
    void send(const unsigned char* binaryMsg, unsigned int len);

    /**
     *  @~english Closes the connection to server. @~chinese �رյ�����˵����ӡ�
     */
    void close();

    /**
     *  @~english Gets current state of connection. @~chinese ��ȡ��ǰ���ӵ�״̬��
     *  @return @~english State the state value coule be State::CONNECTING, State::OPEN, State::CLOSING or State::CLOSED. @~chinese ����State���͵�ֵ������ΪState::CONNECTING, State::OPEN, State::CLOSING ���� State::CLOSED
     */
    State getReadyState();

private:
    virtual void onSubThreadStarted();
    virtual int onSubThreadLoop();
    virtual void onSubThreadEnded();
    virtual void onUIThreadReceiveMessage(WsMessage* msg);


    friend class WebSocketCallbackWrapper;
    int onSocketCallback(struct libwebsocket_context *ctx,
                         struct libwebsocket *wsi,
                         int reason,
                         void *user, void *in, ssize_t len);

private:
    State        _readyState;
    std::string  _host;
    unsigned int _port;
    std::string  _path;

    ssize_t _pendingFrameDataLen;
    ssize_t _currentDataLen;
    char *_currentData;

    friend class WsThreadHelper;
    WsThreadHelper* _wsHelper;

    struct libwebsocket*         _wsInstance;
    struct libwebsocket_context* _wsContext;
    Delegate* _delegate;
    int _SSLConnection;
    struct libwebsocket_protocols* _wsProtocols;
};

}

NS_CC_END

// end group
/// @}

#endif /* defined(__CC_JSB_WEBSOCKET_H__) */
