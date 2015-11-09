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

#ifndef __CC_EVENT_DISPATCHER_H__
#define __CC_EVENT_DISPATCHER_H__

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

#include "platform/CCPlatformMacros.h"
#include "base/CCEventListener.h"
#include "base/CCEvent.h"
#include "platform/CCStdC.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

class Event;
class EventTouch;
class Node;
class EventCustom;
class EventListenerCustom;

/** @class EventDispatcher
* @brief @~english This class manages event listener subscriptions
and event dispatching.

The EventListener list is managed in such a way that
event listeners can be added and removed even
from within an EventListener, while events are being
dispatched.
 * @~chinese ���������¼��������Ķ��ĺ��¼��ķַ�
 * 
 * 
 * �¼��������б��������ķ�ʽ�����й������¼����ڷַ��Ĺ����У��¼����������Ա���ӻ����Ƴ��������¼��������ڲ��ļ�����
@js NA
*/
class CC_DLL EventDispatcher : public Ref
{
public:
    // Adds event listener.
    
    /** @~english Adds a event listener for a specified event with the priority of scene graph.
     * @~chinese ��һ��ָ�����¼����һ���¼����������ü��������л��ڳ���ͼ�����ȼ� ��
     *  @param listener @~english The listener of a specified event.
     * @~chinese ָ���¼��ļ�������
     *  @param node @~english The priority of the listener is based on the draw order of this node.
     * @~chinese �����������ȼ����ڴ˽ڵ�Ļ���˳��.
     *  @note  @~english The priority of scene graph will be fixed value 0. So the order of listener item
     *          in the vector will be ' <0, scene graph (0 priority), >0'.
     * @~chinese ����ͼ�����ȼ��ᱻ����Ϊ�̶�ֵ0�����������(vector)�е��������Ĵ��򽫻��ǣ�' <0, scene graph (0 priority), >0' .
     * 
     */
    void addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node);

    /** @~english Adds a event listener for a specified event with the fixed priority.
     * @~chinese Ϊָ�����¼����һ���̶����ȼ��¼���������
     *  @param listener @~english The listener of a specified event.
     * @~chinese ָ���¼��ļ�������
     *  @param fixedPriority @~english The fixed priority of the listener.
     * @~chinese �������Ĺ̶����ȼ���
     *  @note @~english A lower priority will be called before the ones that have a higher value.
     *        0 priority is forbidden for fixed priority since it's used for scene graph based priority.
     * @~chinese ֵԽС�Ľ����ֵ����ȵ��á�
     * 0������Ϊ����ͼ�Ļ������ȼ����������ȼ���������Ϊ0
     */
    void addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority);

    /** @~english Adds a Custom event listener.
     It will use a fixed priority of 1.
     * @~chinese ���һ���Զ����¼���������
     * �ü�������ʹ��ֵΪ1��һ���̶����ȼ�.
     * @param eventName @~english A given name of the event.
     * @~chinese ������¼����ơ�
     * @param callback @~english A given callback method that associated the event name.
     * @~chinese ���¼����ƹ����Ļص�������
     * @return @~english the generated event. In order to remove the event later from the dispather 
     * @~chinese ���ز������¼����Ա������ɷ������Ƴ�����¼�
     */
    EventListenerCustom* addCustomEventListener(const std::string &eventName, const std::function<void(EventCustom*)>& callback);

    /////////////////////////////////////////////
    
    // Removes event listener
    
    /** @~english Remove a listener.
     *
     * @~chinese ɾ��һ����������
     * 
     *  @param listener @~english The specified event listener which needs to be removed.
     * @~chinese ��Ҫ���Ƴ����¼���������
     */
    void removeEventListener(EventListener* listener);

    /** @~english Removes all listeners with the same event listener type.
     *
     * @~chinese �Ƴ�����ʹ����ͬ�¼����������͵ļ�����
     * 
     * @param listenerType @~english A given event listener type which needs to be removed.
     * @~chinese ������Ҫɾ�����¼����������͡�
     */
    void removeEventListenersForType(EventListener::Type listenerType);

    /** @~english Removes all listeners which are associated with the specified target.
     *
     * @~chinese �Ƴ�������ָ���ڵ�������ļ�����
     * 
     * @param target @~english A given target node.
     * @~chinese һ��������Ŀ��ڵ㡣
     * @param recursive @~english True if remove recursively, the default value is false.
     * @~chinese �Ƿ�ݹ�ɾ���ӽڵ�ļ�������Ĭ��ֵ��false��
     */
    void removeEventListenersForTarget(Node* target, bool recursive = false);
    
    /** @~english Removes all custom listeners with the same event name.
     *
     * @~chinese ɾ�����е�������ͬ���Զ����¼���������
     * 
     * @param customEventName @~english A given event listener name which needs to be removed.
     * @~chinese ����һ����Ҫɾ�����¼�����������,��
     */
    void removeCustomEventListeners(const std::string& customEventName);

    /** @~english Removes all event listeners.
     * @~chinese ɾ�����е��¼���������
     */
    void removeAllEventListeners();

    /////////////////////////////////////////////
    
    // Pauses / Resumes event listener
    
    /** @~english Pauses all listeners which are associated the specified target.
     *
     * @~chinese ��ͣ������ָ���ڵ�������ļ�����
     * 
     * @param target @~english A given target node.
     * @~chinese һ��������Ŀ��ڵ㡣
     * @param recursive @~english True if pause recursively, the default value is false.
     * @~chinese �Ƿ�ݹ���ͣ�ӽڵ�ļ�����,Ĭ��ֵ��false��
     */
    void pauseEventListenersForTarget(Node* target, bool recursive = false);
    
    /** @~english Resumes all listeners which are associated the specified target.
     *
     * @~chinese �ظ�������ָ���ڵ�������ļ�����
     * 
     * @param target @~english A given target node.
     * @~chinese һ��������Ŀ��ڵ㡣
     * @param recursive @~english True if resume recursively, the default value is false.
     * @~chinese �Ƿ�ݹ�ָ��ӽڵ�ļ�����,Ĭ��ֵ��false��
     */
    void resumeEventListenersForTarget(Node* target, bool recursive = false);
    
    /////////////////////////////////////////////
    
    /** @~english Sets listener's priority with fixed value.
     * 
     * @~chinese ���ü����������ȼ�Ϊ�̶�ֵ��
     * 
     * @param listener @~english A given listener.
     * @~chinese һ�������ļ�������
     * @param fixedPriority @~english The fixed priority value.
     * @~chinese �̶����ȼ���
     */
    void setPriority(EventListener* listener, int fixedPriority);

    /** @~english Whether to enable dispatching events.
     *
     * @~chinese �Ƿ������ɷ�����
     * 
     * @param isEnabled  @~english True if enable dispatching events.
     * @~chinese ���Ϊtrue�������ɷ�����
     */
    void setEnabled(bool isEnabled);

    /** @~english Checks whether dispatching events is enabled.
     *
     * @~chinese ����Ƿ��������ɷ�����
     * 
     * @return @~english True if dispatching events is enabled.
     * @~chinese ���Ϊtrue�������ɷ�����
     */
    bool isEnabled() const;

    /////////////////////////////////////////////
    
    /** @~english Dispatches the event.
     *  Also removes all EventListeners marked for deletion from the
     *  event dispatcher list.
     *
     * @~chinese �¼��ַ���
     * ���Ƴ����¼��ַ��б������б��Ϊɾ�����¼�������
     * 
     * 
     * @param event @~english The event needs to be dispatched.
     * @~chinese ��Ҫ�ַ����¼���
     */
    void dispatchEvent(Event* event);

    /** @~english Dispatches a Custom Event with a event name an optional user data.
     *
     * @~chinese �ַ�һ��ָ���¼����ƺͿ�ѡ�û����ݵ��Զ����¼���
     * 
     * @param eventName @~english The name of the event which needs to be dispatched.
     * @~chinese ��Ҫ�ɷ����¼�����,��
     * @param optionalUserData @~english The optional user data, it's a void*, the default value is nullptr.
     * @~chinese ��ѡ���û�����,������void * ,��������ת����Ĭ��ֵ��nullptr
     */
    void dispatchCustomEvent(const std::string &eventName, void *optionalUserData = nullptr);

    /////////////////////////////////////////////
    
    /** @~english Constructor of EventDispatcher.
     * @~chinese EventDispatcher�Ĺ��캯����
     */
    EventDispatcher();
    /** @~english Destructor of EventDispatcher.
     * @~chinese EventDispatcher������������
     */
    ~EventDispatcher();

#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0
    
    /**@~english
     * To help track down event listener issues in debug builds.
     * Verifies that the node has no event listeners associated with it when destroyed.
     * @~chinese 
     * ������������ڵ��԰汾�и��ٵ����¼���������������⡣
     * ��֤�����ڵ�������ʱû���¼����������������.
     */
    void debugCheckNodeHasNoEventListenersOnDestruction(Node* node);
    
#endif

protected:
    friend class Node;
    
    /** @~english Sets the dirty flag for a node.  @~chinese ���ýڵ�����ǡ�*/
    void setDirtyForNode(Node* node);
    
    /**@~english
     *  The vector to store event listeners with scene graph based priority and fixed priority.
     * @~chinese 
     * �����������洢���л��ڳ���ͼ���ȼ��͹̶����ȼ����¼�������
     */
    class EventListenerVector
    {
    public:
        EventListenerVector();
        ~EventListenerVector();
        size_t size() const;
        bool empty() const;
        
        void push_back(EventListener* item);
        void clearSceneGraphListeners();
        void clearFixedListeners();
        void clear();
        
        inline std::vector<EventListener*>* getFixedPriorityListeners() const { return _fixedListeners; };
        inline std::vector<EventListener*>* getSceneGraphPriorityListeners() const { return _sceneGraphListeners; };
        inline ssize_t getGt0Index() const { return _gt0Index; };
        inline void setGt0Index(ssize_t index) { _gt0Index = index; };
    private:
        std::vector<EventListener*>* _fixedListeners;
        std::vector<EventListener*>* _sceneGraphListeners;
        ssize_t _gt0Index;
    };
    
    /** @~english Adds an event listener with item
     * @~chinese Ϊĳһ�����һ���¼�������
     *  @note @~english if it is dispatching event, the added operation will be delayed to the end of current dispatch
     * @~chinese ��������ڷַ��е��¼�����Ӳ����ᱻ�ӳٵ���ǰ�ַ������Ľ���
     *  @see forceAddEventListener
     */
    void addEventListener(EventListener* listener);
    
    /** @~english Force adding an event listener
     * @~chinese ǿ�����һ���¼�������
     *  @note @~english force add an event listener which will ignore whether it's in dispatching.
     * @~chinese ǿ�����һ���¼������������¼������Ƿ��ڵ��ȹ����ж������
     *  @see addEventListener
     */
    void forceAddEventListener(EventListener* listener);
    
    /** @~english Gets event the listener list for the event listener type.  @~chinese ��ȡָ�����������͵��¼��������б�*/
    EventListenerVector* getListeners(const EventListener::ListenerID& listenerID);
    
    /** @~english Update dirty flag  @~chinese ����'����'*/
    void updateDirtyFlagForSceneGraph();
    
    /** @~english Removes all listeners with the same event listener ID  @~chinese �Ƴ�����ʹ����ͬ�¼�������ID�ļ�����*/
    void removeEventListenersForListenerID(const EventListener::ListenerID& listenerID);
    
    /** @~english Sort event listener  @~chinese �¼�����������*/
    void sortEventListeners(const EventListener::ListenerID& listenerID);
    
    /** @~english Sorts the listeners of specified type by scene graph priority  @~chinese ͨ������ͼ�����ȼ�����ָ�����͵ļ�����*/
    void sortEventListenersOfSceneGraphPriority(const EventListener::ListenerID& listenerID, Node* rootNode);
    
    /** @~english Sorts the listeners of specified type by fixed priority  @~chinese ͨ���̶����ȼ�����ָ�����͵ļ�����*/
    void sortEventListenersOfFixedPriority(const EventListener::ListenerID& listenerID);
    
    /** @~english Updates all listeners
     *  1) Removes all listener items that have been marked as 'removed' when dispatching event.
     *  2) Adds all listener items that have been marked as 'added' when dispatching event.
     * @~chinese �������м�����
     * 1)���¼��ַ��������Ƴ������Ѿ����Ϊ'�Ƴ�'�ļ�������.
     * 2)���¼��ַ���������������Ѿ����Ϊ'���'�ļ�������.
     */
    void updateListeners(Event* event);

    /** @~english Touch event needs to be processed different with other events since it needs support ALL_AT_ONCE and ONE_BY_NONE mode.  @~chinese �����¼��Ĵ����������¼���ͬ����Ϊ�����¼���Ҫ֧��ALL_AT_ONCE��ONE_BY_NONEģʽ*/
    void dispatchTouchEvent(EventTouch* event);
    
    /** @~english Associates node with event listener  @~chinese �����ڵ���¼�������*/
    void associateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** @~english Dissociates node with event listener  @~chinese ����ڵ���¼�������*/
    void dissociateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** @~english Dispatches event to listeners with a specified listener type  @~chinese �ַ��¼�������ָ�����������͵ļ�����*/
    void dispatchEventToListeners(EventListenerVector* listeners, const std::function<bool(EventListener*)>& onEvent);
    
    /** Special version dispatchEventToListeners for touch/mouse event.
     *
     *  Touch/mouse event process flow different with common event,
     *      for scene graph node listeners, touch event process flow should
     *      order by viewport/camera first, because the touch location convert
     *      to 3D world space is different by different camera.
     *  When listener process touch event, can get current camera by Camera::getVisitingCamera().
     */
    void dispatchTouchEventToListeners(EventListenerVector* listeners, const std::function<bool(EventListener*)>& onEvent);
    
    /** @~english Priority dirty flag @~chinese �����ȼ���'����'(dirty flag)*/
    enum class DirtyFlag
    {
        NONE = 0,
        FIXED_PRIORITY = 1 << 0,
        SCENE_GRAPH_PRIORITY = 1 << 1,
        ALL = FIXED_PRIORITY | SCENE_GRAPH_PRIORITY
    };
    
    /** @~english Sets the dirty flag for a specified listener ID  @~chinese Ϊһ��ָ���ļ�����ID����һ��'���־'(dirty flag) */
    void setDirty(const EventListener::ListenerID& listenerID, DirtyFlag flag);
    
    /** @~english Walks though scene graph to get the draw order for each node, it's called before sorting event listener with scene graph priority  @~chinese ��������ͼ��ȡÿһ���ڵ�Ļ���˳�򣬸ú������Գ���ͼ���ȼ�������¼�������֮ǰ������*/
    void visitTarget(Node* node, bool isRootNode);

    /** Remove all listeners in _toRemoveListeners list and cleanup */
    void cleanToRemovedListeners();

    /** @~english Listeners map  @~chinese ������ӳ���*/
    std::unordered_map<EventListener::ListenerID, EventListenerVector*> _listenerMap;
    
    /** @~english The map of dirty flag  @~chinese ���־'(dirty flag)ӳ���*/
    std::unordered_map<EventListener::ListenerID, DirtyFlag> _priorityDirtyFlagMap;
    
    /** @~english The map of node and event listeners  @~chinese �ڵ���¼���������ӳ���*/
    std::unordered_map<Node*, std::vector<EventListener*>*> _nodeListenersMap;
    
    /** @~english The map of node and its event priority  @~chinese �ڵ�������¼����ȼ�ӳ���*/
    std::unordered_map<Node*, int> _nodePriorityMap;
    
    /** @~english key: Global Z Order, value: Sorted Nodes  @~chinese key: ȫ��Z�����, value: �ź���Ľڵ�*/
    std::unordered_map<float, std::vector<Node*>> _globalZOrderNodeMap;
    
    /** @~english The listeners to be added after dispatching event  @~chinese ���¼��ַ�����Ҫ����ӵļ�����*/
    std::vector<EventListener*> _toAddedListeners;

    /** The listeners to be removed after dispatching event */
    std::vector<EventListener*> _toRemovedListeners;

    /** @~english The nodes were associated with scene graph based priority listeners  @~chinese ��Щ�ڵ�����ڳ���ͼ���ȼ��ļ����������*/
    std::set<Node*> _dirtyNodes;
    
    /** @~english Whether the dispatcher is dispatching event  @~chinese ���ȳ����Ƿ����ڽ����¼��ַ�*/
    int _inDispatch;
    
    /** @~english Whether to enable dispatching event  @~chinese �Ƿ�Ҫʹ�ַ��¼�����*/
    bool _isEnabled;
    
    int _nodePriorityIndex;
    
    std::set<std::string> _internalCustomListenerIDs;
};


NS_CC_END

// end of base group
/// @}

#endif // __CC_EVENT_DISPATCHER_H__
