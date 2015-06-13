/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#ifndef __CCPHYSICS_CONTACT_H__
#define __CCPHYSICS_CONTACT_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEvent.h"
#include "base/CCEventCustom.h"

NS_CC_BEGIN

class PhysicsShape;
class PhysicsBody;
class PhysicsWorld;

typedef Vec2 Vect;

typedef struct CC_DLL PhysicsContactData
{
    static const int POINT_MAX = 4;
    Vec2 points[POINT_MAX];
    int   count;
    Vec2 normal;
    
    PhysicsContactData()
    : count(0)
    {}
}PhysicsContactData;

/**
 * @addtogroup core
 * @{
 */

/** @class PhysicsContact
 * @brief @~english Contact infomation. 
 * It will created automatically when two shape contact with each other. And it will destoried automatically when two shape separated.
 *
 * @~chinese ��ײ��Ϣ��
 * ���������״�䷢����ײʱ���Զ�����PhysicsContact���󣬲�����ײ����ʱ�Զ����١�
 */
class CC_DLL PhysicsContact : public EventCustom
{
public:
    
    enum class EventCode
    {
        NONE,
        BEGIN,
        PRESOLVE,
        POSTSOLVE,
        SEPARATE
    };
    
    /** @~english Get contact shape A. @~chinese ��ȡ��ײ����״A��*/
    inline PhysicsShape* getShapeA() const { return _shapeA; }
    
    /** @~english Get contact shape B. @~chinese ��ȡ��ײ����״B��*/
    inline PhysicsShape* getShapeB() const { return _shapeB; }
    
    /** @~english Get contact data. @~chinese ��ȡ��ײ���ݡ�*/
    inline const PhysicsContactData* getContactData() const { return _contactData; }
    
    /** @~english Get previous contact data. @~chinese ��ȡ��ײʱ������״�Ӵ�ǰ����ײ���ݡ�*/
    inline const PhysicsContactData* getPreContactData() const { return _preContactData; }
    
    /** 
     * @~english Get the user data.  
     * @~chinese ��ȡ�û����ݡ�
     * @lua NA
     */
    inline void* getData() const { return _data; }
    
    /**
     * @~english Set data to contact. 
     * You must manage the memory yourself, Generally you can set data at contact begin, and distory it at contact separate.
     *
     * @~chinese �����û����ݡ�
     * ����Ҫ�Լ������ⲿ�����ݵ��ͷţ�ͨ���������������״��һ�νӴ���ʱ�������û����ݣ�Ȼ������״�����ʱ���ͷ����ݡ�
     * @lua NA
     */
    inline void setData(void* data) { _data = data; }

    /** @~english Get the event code. @~chinese ��ȡ��ײ�¼����롣 */
    EventCode getEventCode() const { return _eventCode; };

private:
    static PhysicsContact* construct(PhysicsShape* a, PhysicsShape* b);
    bool init(PhysicsShape* a, PhysicsShape* b);
    
    void setEventCode(EventCode eventCode) { _eventCode = eventCode; };
    inline bool isNotificationEnabled() const { return _notificationEnable; }
    inline void setNotificationEnable(bool enable) { _notificationEnable = enable; }
    inline PhysicsWorld* getWorld() const { return _world; }
    inline void setWorld(PhysicsWorld* world) { _world = world; }
    inline void setResult(bool result) { _result = result; }
    inline bool resetResult() { bool ret = _result; _result = true; return ret; }
    
    void generateContactData();

private:
    PhysicsContact();
    ~PhysicsContact();
    
private:
    PhysicsWorld* _world;
    PhysicsShape* _shapeA;
    PhysicsShape* _shapeB;
    EventCode _eventCode;
    bool _notificationEnable;
    bool _result;
    
    void* _data;
    void* _contactInfo;
    PhysicsContactData* _contactData;
    PhysicsContactData* _preContactData;
    
    friend class EventListenerPhysicsContact;
    friend class PhysicsWorldCallback;
    friend class PhysicsWorld;
};

/** @class PhysicsContactPreSolve
 * @brief @~english Presolve value generated when onContactPreSolve called.
 * @~chinese onContactPreSolve�ص������õ�ʱ������PhysicsContactPreSolve����
 */
class CC_DLL PhysicsContactPreSolve
{
public:
    /** @~english Get restitution between two bodies.
     * @~chinese ��ȡ���������ĵ�����
     */
    float getRestitution() const;
    
    /** @~english Get friction between two bodies. 
     * @~chinese ��ȡ����������Ħ������
     */
    float getFriction() const;
    
    /** @~english Get surface velocity between two bodies.
     * @~chinese ��ȡ���������ı����ٶ�ֵ��
     */
    Vec2 getSurfaceVelocity() const;
    
    /** @~english Set the restitution. 
     * @~chinese ���õ�����
     */
    void setRestitution(float restitution);
    
    /** @~english Set the friction. 
     * @~chinese ����Ħ������
     */
    void setFriction(float friction);
    
    /** @~english Set the surface velocity. 
     * @~chinese ���ñ����ٶȡ�
     */
    void setSurfaceVelocity(const Vect& velocity);
    
    /** @~english Ignore the rest of the contact presolve and postsolve callbacks.
     * @~chinese ������һ�εĽӴ���
     */
    void ignore();
    
private:
    PhysicsContactPreSolve(void* contactInfo);
    ~PhysicsContactPreSolve();
    
private:
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/** @class PhysicsContactPostSolve
 * @brief @~english Postsolve value generated when onContactPostSolve called.
 * @~chinese onContactPreSolve�ص������õ�ʱ������PhysicsContactPostSolve����
 */
class CC_DLL PhysicsContactPostSolve
{
public:
    /** @~english Get restitution between two bodies.
     * @~chinese ��ȡ�������彨�ĵ�����
     */
    float getRestitution() const;
    
    /** @~english Get friction between two bodies.
     * @~chinese ��ȡ����������Ħ������
     */
    float getFriction() const;
    
    /** @~english Get surface velocity between two bodies.
     * @~chinese ��ȡ���������ı����ٶȡ�
     */
    Vec2 getSurfaceVelocity() const;
    
private:
    PhysicsContactPostSolve(void* contactInfo);
    ~PhysicsContactPostSolve();
    
private:
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/** @class EventListenerPhysicsContact
 * @brief @~english Contact listener. It will recive all the contact callbacks. 
 * @~chinese ��ײ�¼������������Խ��յ�������ײ�¼���
 */
class CC_DLL EventListenerPhysicsContact : public EventListenerCustom
{
public:
    /** @~english Create the listener. @~chinese ������������*/
    static EventListenerPhysicsContact* create();
    
    virtual bool checkAvailable() override;
    
    virtual EventListenerPhysicsContact* clone() override;
    
protected:
    /**
     * @~english It will be call when two body have contact.
     * if return false, it will not invoke callbacks.
     * @~chinese ����������ײʱ�������������������������false�Ļ�����ײ�ص������ᱻ���á�
     */
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB);
    
public:
    /**
     * @~english It will called at two shapes start to contact, and only call it once.
     * @~chinese ����ص�����ײ��������״��һ�νӴ�ʱ�����ã�����ֻ�ᱻ����һ�Ρ�
     */
    std::function<bool(PhysicsContact& contact)> onContactBegin;
        
    /**
     * @~english Two shapes are touching during this step. 
     * Return false from the callback to make world ignore the collision this step or true to process it normally. 
     * Additionally, you may override collision values, restitution, or surface velocity values.
     *
     * @~chinese ��ײ��������״�໥�Ӵ���
     * ����false�Ļ����������罫������һ�εĽӴ���������������������״����һ�νӴ���
     * �����������ص����Զ�����ײ���ԣ����絯���������ٶȵȡ�
     */
    std::function<bool(PhysicsContact& contact, PhysicsContactPreSolve& solve)> onContactPreSolve;
    
    /**
     * @~english Two shapes are touching and their collision response has been processed. 
     * You can retrieve the collision impulse or kinetic energy at this time if you want to use it to calculate sound volumes or damage amounts. 
     *
     * @~chinese ������״�໥�Ӵ��������ǵ���ײ��Ӧ�ѱ�����
     * �������ʹ�������������������˺�ֵ����ʱ����Լ�����ײ�������ܡ�
     */
    std::function<void(PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    
    /**
     * @~english It will called at two shapes separated, and only call it once.
     * onContactBegin and onContactSeparate will called in pairs.
     *
     * @~chinese ����ص���������ײ����״����ʱ�����ã�����ֻ�ᱻ����һ�Ρ�
     * onContactBegin��onContactSeparate�ǳɶԱ����õġ�
     */
    std::function<void(PhysicsContact& contact)> onContactSeparate;
    
protected:
    bool init();
    void onEvent(EventCustom* event);
    
protected:
    EventListenerPhysicsContact();
    virtual ~EventListenerPhysicsContact();
    
    friend class PhysicsWorld;
};

/** @class EventListenerPhysicsContactWithBodies
 * @brief @~english This event listener only be called when bodyA and bodyB have contacts. 
 * @~chinese ��ײ�¼���������ֻ���Խ��յ�����bodyA�͸���bodyB֮�����ײ�¼���
 */
class CC_DLL EventListenerPhysicsContactWithBodies : public EventListenerPhysicsContact
{
public:
    /** @~english Create the listener. @~chinese ������ײ��������*/
    static EventListenerPhysicsContactWithBodies* create(PhysicsBody* bodyA, PhysicsBody* bodyB);
    
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB) override;

    virtual EventListenerPhysicsContactWithBodies* clone() override;
    
protected:
    PhysicsBody* _a;
    PhysicsBody* _b;
    
protected:
    EventListenerPhysicsContactWithBodies();
    virtual ~EventListenerPhysicsContactWithBodies();
};

/** @class EventListenerPhysicsContactWithShapes
 * @brief @~english This event listener only be called when shapeA and shapeB have contacts. 
 * @~chinese ��ײ�¼���������ֻ���Խ��յ���״shapeA����״shapeB֮�����ײ�¼���
 */
class CC_DLL EventListenerPhysicsContactWithShapes : public EventListenerPhysicsContact
{
public:
    /** @~english Create the listener. @~chinese ������ײ��������*/
    static EventListenerPhysicsContactWithShapes* create(PhysicsShape* shapeA, PhysicsShape* shapeB);
    
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB) override;
    virtual EventListenerPhysicsContactWithShapes* clone() override;
    
protected:
    PhysicsShape* _a;
    PhysicsShape* _b;
    
protected:
    EventListenerPhysicsContactWithShapes();
    virtual ~EventListenerPhysicsContactWithShapes();
};

/** @class EventListenerPhysicsContactWithGroup
 * @brief @~english This event listener only be called when shapeA or shapeB is in the group your specified.
 * @~chinese ��ײ�¼���������ֻ���Ը����������״֮�����ײ�¼���
 */
class CC_DLL EventListenerPhysicsContactWithGroup : public EventListenerPhysicsContact
{
public:
    /** @~english Create the listener. @~chinese ������ײ�������� */
    static EventListenerPhysicsContactWithGroup* create(int group);
    
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB) override;
    virtual EventListenerPhysicsContactWithGroup* clone() override;
    
protected:
    int _group;
    
protected:
    EventListenerPhysicsContactWithGroup();
    virtual ~EventListenerPhysicsContactWithGroup();
};

/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif //__CCPHYSICS_CONTACT_H__
