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

#ifndef __TRIGGEROBJ_H__
#define __TRIGGEROBJ_H__

#include "CocoStudio.h"
#include "base/CCVector.h"

namespace cocos2d {
class EventListenerCustom;
}

namespace cocostudio {

/** 
 * @class BaseTriggerCondition
 * @brief @~english condition base class.
 * @~chinese �������������ࡣ
*/
class CC_STUDIO_DLL BaseTriggerCondition : public cocos2d::Ref
{
protected:
    /**
     * @brief @~english BaseTriggerCondition constructor.
     * @~chinese �������������๹�캯����
     */
    BaseTriggerCondition(void);
public:
    /**
     * @brief @~english BaseTriggerCondition destructor.
     * @~chinese ������������������������
     */
    virtual ~BaseTriggerCondition(void);

    /**
     * @brief @~english initialize a BaseTriggerCondition.
     * @~chinese ��ʼ��������������
     * @return @~english true Initialize successfully false failed to initialize.
     * @~chinese true ��ʼ���ɹ�������false��
     */
    virtual bool init();

    /**
     * @brief @~english Detect condition of trigger.
     * @~chinese �����������жϡ�
     * @return @~english true Detect successfully false failed to Detect.
     * @~chinese true �����ɹ�������false��
     */
    virtual bool detect();

    /**
     * @brief @~english Deserialization json data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x �����༭�����������ݡ�
     * @param val @~english Json object point.
     * @~chinese json����ָ�롣
     */
    virtual void serialize(const rapidjson::Value &val);

    /**
     * @brief @~english Deserialization binary data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x�����Ķ��������ݡ�
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭���������������ݼ���������
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭����������������node����
     */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);

    /**
     * @brief @~english it is called when the trigger condition is removed , you can override this method to implement free the resources here.
     * @~chinese ���������Ƴ���ʱ�򱻵��ã��������������������Դ�ͷŵ����
     */
    virtual void removeAll();
};

/** 
 * @class BaseTriggerAction
 * @brief @~english Action base class.
 * @~chinese �������������ࡣ
*/
class CC_STUDIO_DLL BaseTriggerAction : public cocos2d::Ref
{
protected:
    /**
     * @brief @~english BaseTriggerAction constructor.
     * @~chinese �������������๹�캯����
     */
    BaseTriggerAction(void);
public:
    /**
     * @brief @~english BaseTriggerAction destructor.
     * @~chinese ������������������������
     */
    virtual ~BaseTriggerAction(void);

    /**
     * @brief @~english initialize a BaseTriggerAction.
     * @~chinese ��ʼ��������������
     * @return @~english true Initialize successfully false failed to initialize.
     * @~chinese true ��ʼ���ɹ�������false��
     */
    virtual bool init();

    /**
     * @brief @~english BaseTriggerAction execution.
     * @~chinese ����������ִ�С�
     */
    virtual void done();

    /**
     * @brief @~english Deserialization json data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x �����༭�����������ݡ�
     * @param val @~english Json object point.
     * @~chinese json����ָ�롣
     */
    virtual void serialize(const rapidjson::Value &val);

    /**
     * @brief @~english Deserialization binary data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x�����Ķ��������ݡ�
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭���������������ݼ���������
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭����������������node����
     */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);

    /**
     * @brief @~english It is called when the trigger action is removed , you can override this method to implement free the resources here.
     * @~chinese ���������Ƴ���ʱ�򱻵��ã��������������������Դ�ͷŵ����
     */
    virtual void removeAll();
};

/** 
 * @class TriggerObj
 * @brief @~english Trigger class.
 * @~chinese ��������
*/
class CC_STUDIO_DLL TriggerObj : public cocos2d::Ref
{
public:
    /**
     * @brief @~english TriggerObj constructor.
     * @~chinese TriggerObj���캯����
     */
    TriggerObj(void);

    /**
     * @brief @~english TriggerObj destructor.
     * @~chinese TriggerObj����������
     */
    virtual ~TriggerObj(void);

    /**
     * @brief @~english initialize a TriggerObj.
     * @~chinese ��ʼ����������
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true ��ʼ���ɹ�������false��
     */
    virtual bool init();

    /**
     * @brief @~english Allocates and initializes a create.
     * @~chinese ���䲢�ҳ�ʼ����������
     * @return @~english A initialized TriggerObj which is marked as "autorelease".
     * @~chinese һ����ʼ���Ĵ��������ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�)��
     */
    static TriggerObj* create(void);

    /**
     * @brief @~english Detect condition of trigger.
     * @~chinese �����������жϡ�
     * @return @~english true Detect successfully false failed to Detect.
     * @~chinese true �����ɹ�������false��
     */
    virtual bool detect();

    /**
     * @brief @~english trigger execution.
     * @~chinese ����������ִ�С�
     */
    virtual void done();

    /**
     * @brief @~english it is called when the trigger is removed , you can override this method to implement free the resources here.
     * @~chinese ���������Ƴ���ʱ�򱻵��ã��������������������Դ�ͷŵ����
     */
    virtual void removeAll();

    /**
     * @brief @~english Deserialization json data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x �����༭�����������ݡ�
     * @param val @~english json object point.
     * @~chinese json����ָ�롣
     */
    virtual void serialize(const rapidjson::Value &val);

    /**
     * @brief @~english Deserialization binary data of cocos studio 1.x scene editor.
     * @~chinese �����л�cocos studio 1.x�����Ķ��������ݡ�
     * @param cocoLoader @~english loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭���������������ݼ���������
     * @param cocoNode @~english loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭����������������node����
     */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);

    /**
     * @brief @~english get unique id of trigger.
     * @~chinese ��ȡ������Ψһid��
     * @return @~english unique id of trigger.
     * @~chinese ������Ψһid��
     */
    unsigned int getId();

    /**  
     * @brief @~english enables or disables the trigger.
     * @~chinese ���û���ô�������
     * @param enabled @~english true enable the trigger, false disabled the trigger. 
     * @~chinese true�����ô����� false�����ô�������
     */
    void setEnabled(bool enabled);
  
private:
    cocos2d::Vector<BaseTriggerCondition*> _cons;
    cocos2d::Vector<BaseTriggerAction*> _acts;
    unsigned int _id;
    bool _enabled;
    cocos2d::Vector<cocos2d::EventListenerCustom*> _listeners;
};

}

#endif


