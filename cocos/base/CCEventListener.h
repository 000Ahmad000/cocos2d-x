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

#ifndef __CCEVENTLISTENER_H__
#define __CCEVENTLISTENER_H__

#include <functional>
#include <string>
#include <memory>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Event;
class Node;

/** @class EventListener
 *  @brief @~english The base class of event listener.
 *  If you need custom listener which with different callback, you need to inherit this class.
 *  For instance, you could refer to EventListenerAcceleration, EventListenerKeyboard, EventListenerTouchOneByOne, EventListenerCustom.
 * @~chinese �¼��������Ļ��ࡣ
 * �������Ҫ�Զ����в�ͬ�ص��ļ�����ʱ,����Ҫ�̳�����ࡣ
 * ����,����Բο�EventListenerAcceleration,EventListenerKeyboard,EventListenerTouchOneByOne EventListenerCustom��
 */
class CC_DLL EventListener : public Ref
{
public:
    /** @~english Type Event type. @~chinese �¼����͡�*/
    enum class Type
    {
        UNKNOWN,
        TOUCH_ONE_BY_ONE,
        TOUCH_ALL_AT_ONCE,
        KEYBOARD,
        MOUSE,
        ACCELERATION,
        FOCUS,
		GAME_CONTROLLER,
        CUSTOM
    };

    typedef std::string ListenerID;

CC_CONSTRUCTOR_ACCESS:
    /**@~english
     * Constructor
     * @~chinese 
     * ���캯��
     * @js ctor
     */
    EventListener();

    /** @~english
     * Initializes event with type and callback function
     * @~chinese 
     * ��ʼ���¼��ͻص�����
     * @js NA
     */
    bool init(Type t, const ListenerID& listenerID, const std::function<void(Event*)>& callback);
public:
    /** @~english Destructor.
     * @~chinese ����������
     * @js NA 
     */
    virtual ~EventListener();

    /** @~english Checks whether the listener is available.
     * 
     * @~chinese ����Ƿ�������ǿ��õġ�
     * 
     * @return @~english True if the listener is available.
     * @~chinese ����������ǿ��õ�,����true��
     */
    virtual bool checkAvailable() = 0;

    /** @~english Clones the listener, its subclasses have to override this method.
     * @~chinese ��¡������,�������������д�˷�����
     */
    virtual EventListener* clone() = 0;

    /** @~english Enables or disables the listener.
     * @~chinese ���û���ü�������
     * @note @~english Only listeners with `enabled` state will be able to receive events.
     *        When an listener was initialized, it's enabled by default.
     *        An event listener can receive events when it is enabled and is not paused.
     *        paused state is always false if it is a fixed priority listener.
     *
     * @~chinese ֻ�м��������ڡ����á�״̬ʱ���ܹ������¼���
     * ��һ����������ʼ��,��Ĭ�������õġ�
     * ��һ����������������״̬��û����ͣ���������յ��¼���
     * �������һ���̶����ȼ��ļ�����,������ͣ״̬��ʱ�����ֵʼ��Ϊfalse��
     * 
     * @param enabled @~english True if enables the listener.
     * @~chinese �������������ֵΪtrue��
     */
    inline void setEnabled(bool enabled) { _isEnabled = enabled; };

    /** @~english Checks whether the listener is enabled.
     *
     * @~chinese ���������Ƿ���á�
     * 
     * @return @~english True if the listenrt is enabled.
     * @~chinese ������������ã�ֵΪtrue��
     */
    inline bool isEnabled() const { return _isEnabled; };

protected:

    /** @~english Sets paused state for the listener
     *  The paused state is only used for scene graph priority listeners.
     *  `EventDispatcher::resumeAllEventListenersForTarget(node)` will set the paused state to `true`,
     *  while `EventDispatcher::pauseAllEventListenersForTarget(node)` will set it to `false`.
     * @~chinese ���ü���������ͣ״̬
     * ��ͣ״̬�������ڳ���ͼ�����ȼ�������
     * `EventDispatcher::resumeAllEventListenersForTarget(node)` ����������ͣ״̬Ϊ `true`,
     *  Ȼ�� `EventDispatcher::pauseAllEventListenersForTarget(node)` ����������ͣ״̬Ϊ `false`.
     *  @note @~english 1) Fixed priority listeners will never get paused. If a fixed priority doesn't want to receive events,
     *           call `setEnabled(false)` instead.
     *        2) In `Node`'s onEnter and onExit, the `paused state` of the listeners which associated with that node will be automatically updated.
     * @~chinese 1) �̶����ȼ��ļ�������������ͣ.  �����һ���̶����ȼ��ļ�������������¼�,����
     *           `setEnabled(false)` ����.
     *           2) �ڽڵ�(`Node`)�� onEnter �� onExit ������, �����Զ����¹����ڵ�ļ���������ͣ״̬.
     */
    inline void setPaused(bool paused) { _paused = paused; };

    /** @~english Checks whether the listener is paused  @~chinese ���������Ƿ���ͣ*/
    inline bool isPaused() const { return _paused; };

    /** @~english Marks the listener was registered by EventDispatcher  @~chinese ��Ǽ������Ѿ������뵽�¼��ɷ���(EventDispatcher)*/
    inline void setRegistered(bool registered) { _isRegistered = registered; };

    /** @~english Checks whether the listener was registered by EventDispatcher  @~chinese ���������Ƿ�ע�ᵽ�¼��ɷ���(EventDispatcher)*/
    inline bool isRegistered() const { return _isRegistered; };

    /** @~english Gets the type of this listener
     * @~chinese ��ȡ������(listener)������
     *  @note @~english It's different from `EventType`, e.g. TouchEvent has two kinds of event listeners - EventListenerOneByOne, EventListenerAllAtOnce
     * @~chinese ����ͬ��`EventType`, ����. TouchEvent�������¼������� - EventListenerOneByOne, EventListenerAllAtOnce
     */
    inline Type getType() const { return _type; };

    /** @~english Gets the listener ID of this listener
     *  When event is being dispatched, listener ID is used as key for searching listeners according to event type.
     * @~chinese ��ȡ��������ID 
     * ���¼��ɷ�,������ID�����ڲ��ҷ����¼����͵ļ������Ĺؼ���.
     */
    inline const ListenerID& getListenerID() const { return _listenerID; };

    /** @~english Sets the fixed priority for this listener
     * @~chinese Ϊ���������ù̶����ȼ�
     *  @note @~english This method is only used for `fixed priority listeners`, it needs to access a non-zero value.
     *  0 is reserved for scene graph priority listeners
     * @~chinese �˷��������� `fixed priority listeners`, ����Ҫ����һ������(non-zero)ֵ.
     * 0 ���������ڳ���ͼ������������ȼ�
     */
    inline void setFixedPriority(int fixedPriority) { _fixedPriority = fixedPriority; };

    /** @~english Gets the fixed priority of this listener
     * @~chinese ��ȡ�����������ȼ�
     *  @return @~english 0 if it's a scene graph priority listener, non-zero for fixed priority listener
     * @~chinese ����ǳ���ͼ��������򷵻�0,�����̶����ȼ��ļ��������ط���(non-zero)ֵ
     */
    inline int getFixedPriority() const { return _fixedPriority; };

    /** @~english Sets the node associated with this listener  @~chinese ���úͼ����������Ľڵ�*/
    inline void setAssociatedNode(Node* node) { _node = node; };

    /** @~english Gets the node associated with this listener
     * @~chinese ��ȡ�ͼ����������Ľڵ�
     *  @return @~english nullptr if it's a fixed priority listener, otherwise return non-nullptr
     * @~chinese ����ǹ̶����ȼ��ļ������򷵻ؿ�ָ��(nullptr),���򷵻طǿ�ָ��(non-nullptr)
     */
    inline Node* getAssociatedNode() const { return _node; };

    ///////////////
    // Properties
    //////////////
    std::function<void(Event*)> _onEvent;   /// @~english Event callback function @~chinese �¼��ص�����

    Type _type;                             /// @~english Event listener type @~chinese �¼�������������
    ListenerID _listenerID;                 /// @~english Event listener ID @~chinese �¼���������ID
    bool _isRegistered;                     /// @~english Whether the listener has been added to dispatcher. @~chinese �������Ƿ񱻼��뵽�ɷ��� 

    int   _fixedPriority;   // @~english The higher the number, the higher the priority, 0 is for scene graph base priority. @~chinese ��ֵԽ�ߣ����ȼ�Խ��. 0 �ǳ���ͼ��Ļ������ȼ�.
    Node* _node;            // @~english scene graph based priority @~chinese �¼������������Ľڵ�
    bool _paused;           // @~english Whether the listener is paused @~chinese �������Ƿ���ͣ
    bool _isEnabled;        // @~english Whether the listener is enabled @~chinese �������Ƿ�����
    friend class EventDispatcher;
};

NS_CC_END

// end of base group
/// @}

#endif // __CCEVENTLISTENER_H__
