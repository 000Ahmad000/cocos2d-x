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
#ifndef __TRIGGERMNG_H__
#define __TRIGGERMNG_H__

#include "CocoStudio.h"

namespace cocos2d {
class EventDispatcher;
class EventListener;
}

namespace cocostudio {

class TriggerObj;

/** 
 * @class ArmatureMovementDispatcher
 * @brief @~english Armature action state dispatcher.
 * @~chinese  Armature����״̬�¼��ַ�����
*/
class CC_STUDIO_DLL ArmatureMovementDispatcher : public cocos2d::Ref
{
public:
    /**
     * @brief @~english ArmatureMovementDispatcher constructor.
     * @~chinese ArmatureMovementDispatcher���캯����
     */
    ArmatureMovementDispatcher(void);
    /**
     * @brief @~english ArmatureMovementDispatcher destructor.
     * @~chinese ArmatureMovementDispatcher����������
     */
    ~ArmatureMovementDispatcher(void);
public:
    /**
     * @brief @~english Add armature event callback function to trigger object.
     * @~chinese Ϊ���������������¼��ص���
     * @param pTarget @~english Trigger object point.
     * @~chinese ����������ָ�롣
     * @param mecf @~english Callback function.
     * @~chinese �ص�������
     */
    void addAnimationEventCallBack(cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Remove armature event callback function from trigger object.
     * @~chinese Ϊ�����������Ƴ��¼��ص���
     * @param pTarget @~english Trigger object point.
     * @~chinese ����������ָ�롣
     * @param mecf @~english Callback function.
     * @~chinese �ص�������
     */
    void removeAnnimationEventCallBack(cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Animation event callback function.
     * @~chinese Armature�¼��ص��ķ�����
     * @param armature @~english Armature object point.
     * @~chinese 1.x������������ָ�롣
     * @param movementType @~english Armature movement type.
     * @~chinese 1.x���������ƶ����͡�
     * @param movementID @~english Armature movement action id.
     * @~chinese 1.x������������ID��
     */
    void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    
private:
    std::unordered_map<cocos2d::Ref*, SEL_MovementEventCallFunc> *_mapEventAnimation;

};

/** 
 * @class TriggerMng
 * @brief @~english Trigger manager.
 * @~chinese  Armature����״̬�¼��ַ�����
*/
class CC_STUDIO_DLL TriggerMng
{
public:
    /**
     * @brief @~english TriggerMng constructor.
     * @~chinese TriggerMng���캯����
     */
    TriggerMng(void);

    /**
     * @brief @~english TriggerMng destructor.
     * @~chinese TriggerMng����������
     */
    virtual ~TriggerMng(void);

public:
    /**
     * @brief @~english Get instance point of TriggerMng.
     * @~chinese TriggerMng����ָ�롣
     */
    static TriggerMng* getInstance();

    /**
     * @brief @~english Destroy instance point of TriggerMng.
     * @~chinese ����TriggerMng����ָ�롣
     */
    static void destroyInstance();

    /**
     * @brief @~english Get version string of TriggerMng.
     * @~chinese TriggerMng�汾���ַ�����
     */
    static const char* triggerMngVersion();
    
public:
     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor.
     * @~chinese ����cocos studio 1.x �����༭������json���ݡ�
     * @param root @~english json data object
     * @~chinese json���ݶ���
     */
    void parse(const rapidjson::Value &root);

    /**
     * @brief @~english Parse binary data of cocos studio 1.x scene editor.
     * @~chinese ����cocos studio 1.x�����Ķ��������ݡ�
     * @param pCocoLoader @~english loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭���������������ݼ���������
     * @param pCocoNode @~english loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭����������������node����
     */
    void parse(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode);

    /**
     * @brief @~english remove all triggers.
     * @~chinese �Ƴ����д�������
     */
    void removeAll(void);

    /**
     * @brief @~english Get triggers with event id.
     * @~chinese ���ݴ������¼�id,��ȡ�󶨵����id�ϵ����д�������
     * @param event @~english Event id.
     * @~chinese �¼�id��
     * @return @~english Trigger vector.
     * @~chinese ���������顣
     */
    cocos2d::Vector<TriggerObj*>* get(unsigned int event) const;

    /**
     * @brief @~english Get trigger with trigger id.
     * @~chinese ���ݴ�����id,��ȡ��������
     * @param id @~english Trigger unique id.
     * @~chinese ������Ψһid��
     * @return @~english Trigger point.
     * @~chinese ��ȡ������ָ�롣
     */
    TriggerObj* getTriggerObj(unsigned int id) const;

    /**
     * @brief @~english Remove trigger with trigger point.
     * @~chinese ���ݴ�����ָ�룬�Ƴ���������
     * @param Obj @~english Trigger point.
     * @~chinese ������ָ�롣
     * @return @~english true remove successfully false failed to remove .
     * @~chinese true�ɹ��Ƴ�������false��
     */
    bool removeTriggerObj(TriggerObj *Obj);

    /**
     * @brief @~english Remove trigger with trigger unique id.
     * @~chinese ���ݴ�����id���Ƴ���������
     * @param id @~english Trigger unique id.
     * @~chinese ������Ψһid��
     * @return @~english true remove successfully false failed to remove .
     * @~chinese true�ɹ��Ƴ�������false��
     */
    bool removeTriggerObj(unsigned int id);

    /** @brief @~english Returns whether _triggerObjs is empty (i.e. whether its size is 0).
     * @~chinese ����_triggerObjs Vector�Ƿ�Ϊ��(���������СΪ0)��
     * @return @~english true _triggerObjs isn't empty false empty .
     * @~chinese true û�д�����������false��
     */
    bool isEmpty(void) const;

    /**
     * @brief @~english Add armature event callback to trigger object.
     * @~chinese Ϊ���������������¼��ص���
     * @param pTarget @~english Trigger object point.
     * @~chinese ����������ָ�롣
     * @param mecf @~english Callback function.
     * @~chinese �ص�������
     */
    void addArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Remove armature event callback function with armature point, trigger point, callback function.
     * @~chinese Ϊ�����������Ƴ��¼��ص���
     * @param pTarget @~english Trigger object point.
     * @~chinese ����������ָ�롣
     * @param mecf @~english Callback function.
     * @~chinese �ص�������
     */
    void removeArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Remove all event callback functions binding to armature point.
     * @~chinese �Ƴ��󶨵�Armature�����¼��ص���
     * @param pAr @~english Armature point.
     * @~chinese 1.x��������ָ�롣
     */
    void removeArmatureAllMovementCallBack(Armature *pAr);

    /**
     * @brief @~english Remove all armature event callback functions. 
     * @~chinese �Ƴ�Armature�����¼��ص���
     */
    void removeAllArmatureMovementCallBack();

    /**
     * @brief @~english Dispatch trigger events. 
     * @~chinese  �ַ��������¼���
     * @param tEvent @~english Trigger event.
     * @~chinese �������¼���
     */
    void dispatchEvent(cocos2d::EventCustom* tEvent);

    /**
     * @brief @~english Remove trigger event listener. 
     * @~chinese �Ƴ��������¼���������
     * @param listener @~english Trigger event listener.
     * @~chinese �������¼���������
     */
    void removeEventListener(cocos2d::EventListener* listener);

    /**
     * @brief @~english Add a trigger event listener with the fixed priority.
     * @~chinese ���Ӵ������¼�����������ָ�����ȼ���
     * @param listener @~english Trigger event listener.
     * @~chinese �������¼���������
     * @param fixedPriority @~english The fixed priority of the listener
     * @~chinese ���������ȼ�
     */
    void addEventListenerWithFixedPriority(cocos2d::EventListener* listener, int fixedPriority);

private:
    /**
    @���� ����cocos studio 1.x�����Ķ����ƶ���ת��Ϊjson��������lua����
    @���� document json����
    @���� pCocoLoader cocos studio 1.x�������������ݼ���������
    @���� pCocoNode cocos studio 1.x��������������node����
    @���� ��
    */
    /**
     * @brief @~english Transform binary object into a json object, assign to document.
     * @~chinese ����cocos studio 1.x�����Ķ����ƶ���ת��Ϊjson���󣬲���ֵ��document��
     * @param document @~english Json data object
     * @~chinese json���ݶ���
     * @param pCocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭���������������ݼ���������
     * @param pCocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭����������������node����
     */
    void buildJson(rapidjson::Document &document, cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode);

private:
    static TriggerMng *_sharedTriggerMng;
    std::unordered_map<unsigned int, TriggerObj*> _triggerObjs;
    std::unordered_map<Armature*, ArmatureMovementDispatcher*> *_movementDispatches;
    cocos2d::EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events
};

}

#endif
