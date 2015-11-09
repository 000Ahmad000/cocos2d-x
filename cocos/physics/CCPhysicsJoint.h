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

#ifndef __CCPHYSICS_JOINT_H__
#define __CCPHYSICS_JOINT_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"

struct cpConstraint;

NS_CC_BEGIN

class Node;
class PhysicsBody;
class PhysicsWorld;

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

/**
@class PhysicsJoint
 * @brief @~english An PhysicsJoint object connects two physics bodies together.
 * @~chinese һ��PhysicsJoint(����ؽ�)�������ڽ���������������һ��
 */
class CC_DLL PhysicsJoint
{
protected:
    PhysicsJoint();
    virtual ~PhysicsJoint() = 0;

public:
    /**
    @~english Get the first physics body a connected to this joint. 
    @~chinese �õ����ӵ�����ؽڵĵ�һ��������塣
    */
    inline PhysicsBody* getBodyA() const { return _bodyA; }
    
    /**
    @~english Get the second physics body b connected to this joint. 
    @~chinese �õ����ӵ�����ؽڵĵڶ���������塣
    */
    inline PhysicsBody* getBodyB() const { return _bodyB; }

    /**@~english Get the physics world. @~chinese ��ȡ�������硣*/
    inline PhysicsWorld* getWorld() const { return _world; }
    
    /**@~english
     * Get this joint's tag.
     *
     * @~chinese 
     * �õ��ؽڵ�tag��
     * 
     * @return @~english An interger number.
     * @~chinese tagֵ��
     */
    inline int getTag() const { return _tag; }
    
    /**@~english
     * Set this joint's tag.
     *
     * @~chinese 
     * ����tag��
     * 
     * @param tag @~english An interger number that identifies a PhysicsJoint.
     * @~chinese tag��ֵ��
     */
    inline void setTag(int tag) { _tag = tag; }
    
    /** @~english Determines if the joint is enable.  @~chinese �ؽ��Ƿ��ڿ���״̬��*/
    inline bool isEnabled() const { return _enable; }

    /** @~english Enable or disable the joint. @~chinese ���û��߽��ùؽڡ�*/
    void setEnable(bool enable);
    
    /** @~english Determines if the collsion is enable.  @~chinese ��ײ���Ƿ����á�*/
    inline bool isCollisionEnabled() const { return _collisionEnable; }
    
    /** @~english Enable or disable collision. @~chinese ���û��߽�����ײ�塣*/
    void setCollisionEnable(bool enable);
    
    /** @~english Remove the joint from the world.  @~chinese ɾ���ؽڡ�*/
    void removeFormWorld();

    /** @~english Set the max force between two bodies.  @~chinese ���������������֮������������*/
    void setMaxForce(float force);
    
    /** @~english Get the max force setting.  @~chinese �õ��������֮������������*/
    float getMaxForce() const { return _maxForce; }

protected:
    bool init(PhysicsBody* a, PhysicsBody* b);

    bool initJoint();
    
    /** @~english Create constraints for this type joint  @~chinese Ϊ�������ϴ���Լ��*/
    virtual bool createConstraints() { return false; }

    std::vector<cpConstraint*> _cpConstraints;
    PhysicsBody* _bodyA;
    PhysicsBody* _bodyB;
    PhysicsWorld* _world;

    bool _enable;
    bool _collisionEnable;
    bool _destoryMark;
    int _tag;
    float _maxForce;

    bool _initDirty;

    friend class PhysicsBody;
    friend class PhysicsWorld;
    friend class PhysicsDebugDraw;
};

/**
@class PhysicsJointFixed
* @brief 
@~english A fixed joint fuses the two bodies together at a reference point. Fixed joints are useful for creating complex shapes that can be broken apart later.
 @~chinese �̶��ؽڰ���������������ӵ�һ�����������ڴ������ӵ���״����Щ��״�ں�����Ա��ƻ��ɶ����ĸ��塣
*/
class CC_DLL PhysicsJointFixed : public PhysicsJoint
{
public:
    /** @~english Create a fixed joint.
     
     * @~chinese ����һ���̶��ؽڡ�
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param anchr @~english It's the pivot position.
     * @~chinese ���ӵ��λ�á�
     @return @~english A object pointer.
     * @~chinese �̶�����ؽڡ�
     */
    static PhysicsJointFixed* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);

    virtual bool createConstraints() override;

protected:
    PhysicsJointFixed() {}
    virtual ~PhysicsJointFixed() {}

    Vec2 _anchr;
};

/**
@class PhysicsJointLimit
* @brief @~english A limit joint imposes a maximum distance between the two bodies, as if they were connected by a rope.
 * @~chinese PhysicsJointLimit��������������֮��������룬�ͺ������Ǳ�һ��������������һ����
*/
class CC_DLL PhysicsJointLimit : public PhysicsJoint
{
public:
    /** @~english Create a limit joint.
     
     * @~chinese ����һ��PhysicsJointLimit��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese ���ӵ�һ������ĵ㡣
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese ���ӵڶ�������ĵ㡣
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointLimit��
     */
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);
    
    /** @~english Create a limit joint.
     
     * @~chinese ����һ��PhysicsJointLimit��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese ���ӵ�һ������ĵ㡣
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese ���ӵڶ�������ĵ㡣
     @param min @~english Define the allowed min distance of the anchor points.
     * @~chinese �������ӵ����С���롣
     @param max @~english Define the allowed max distance of the anchor points.
     * @~chinese �������ӵ�������롣
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointLimit��
     */
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float min, float max);

    /** @~english Get the anchor point on body a. @~chinese �õ����ӵ�һ������ĵ㡣*/
    Vec2 getAnchr1() const;
    
    /** @~english Set the anchor point on body a. @~chinese �������ӵ�һ������ĵ㡣*/
    void setAnchr1(const Vec2& anchr1);
    
    /** @~english Get the anchor point on body b. @~chinese �õ����ӵڶ�������ĵ㡣*/
    Vec2 getAnchr2() const;
    
    /** @~english Set the anchor point on body b. @~chinese �������ӵڶ�������ĵ㡣*/
    void setAnchr2(const Vec2& anchr2);
    
    /** @~english Get the allowed min distance of the anchor points. @~chinese �õ��������ӵ����С���롣*/
    float getMin() const;
    /** @~english Set the min distance of the anchor points. @~chinese �����������ӵ����С���롣*/
    void setMin(float min);
  
    /** @~english Get the allowed max distance of the anchor points. @~chinese �õ��������ӵ�������롣*/
    float getMax() const;
    /** @~english Set the max distance of the anchor points. @~chinese �����������ӵ�������롣*/
    void setMax(float max);

    virtual bool createConstraints() override;

protected:
    PhysicsJointLimit() {}
    virtual ~PhysicsJointLimit() {}

    Vec2 _anchr1;
    Vec2 _anchr2;
    float _min;
    float _max;
};

/**
@class PhysicsJointPin
* @brief 
@~english A pin joint allows the two bodies to independently rotate around the anchor point as if pinned together.
 * @~chinese PhysicsJointPin�����������������ת���ͺ������Ǳ�����һ��һ����
*/
class CC_DLL PhysicsJointPin : public PhysicsJoint
{
public:
    /** @~english Create a pin joint.
     
     * @~chinese ����һ��PhysicsJointPin��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param pivot @~english It's the pivot position.
     * @~chinese ���ӵ��λ�á�
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointPin��
     */
    static PhysicsJointPin* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& pivot);

    /** @~english Create a pin joint.
     
     * @~chinese ����һ��PhysicsJointPin��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese ���ӵĵ�һ������ĵ㡣
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese ���ӵĵڶ�������ĵ㡣
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointPin��
     */
    static PhysicsJointPin* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);

    virtual bool createConstraints() override;

protected:
    PhysicsJointPin() {}
    virtual ~PhysicsJointPin() {}

    bool _useSpecificAnchr;
    Vec2 _anchr1;
    Vec2 _anchr2;
};

/** 
@class PhysicsJointDistance
@brief
@~english Set the fixed distance with two bodies  
@~chinese �ùؽ���������������֮������һ���̶����롣
*/
class CC_DLL PhysicsJointDistance : public PhysicsJoint
{
public:
    /** @~english Create a fixed distance joint.
     
     * @~chinese ����һ��PhysicsJointDistance��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese ���ӵĵ�һ������ĵ㡣
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese ���ӵĵڶ�������ĵ㡣
     @return @~english A object pointer.
     * @~chinese ���ش���һ��PhysicsJointDistance��
     */
    static PhysicsJointDistance* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);

    /** @~english Get the distance of the anchor points. @~chinese �õ����ӵ�֮��ľ��롣*/
    float getDistance() const;
    /** @~english Set the distance of the anchor points. @~chinese �������ӵ�֮��ľ��롣*/
    void setDistance(float distance);
    virtual bool createConstraints() override;

protected:
    PhysicsJointDistance() {}
    virtual ~PhysicsJointDistance() {}

    Vec2 _anchr1;
    Vec2 _anchr2;
};

/** 
@class PhysicsJointSpring
@brief
@~english Connecting two physics bodies together with a spring.  
@~chinese PhysicsJointSpring���������������壬��Ч���൱��һ�����ɡ�
*/
class CC_DLL PhysicsJointSpring : public PhysicsJoint
{
public:
    /** @~english Create a spring joint.
     
     * @~chinese ����һ��PhysicsJointSpring��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese ���ӵĵ�һ������ĵ㡣
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese ���ӵĵڶ�������ĵ㡣
     @param stiffness @~english It's the spring constant.
     * @~chinese �ؽڵĵ���ϵ����
     @param damping @~english It's how soft to make the damping of the spring.
     * @~chinese �ؽڵ����ᡣ
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointSpring��
     */
    static PhysicsJointSpring* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float stiffness, float damping);

    /** @~english Get the anchor point on body a. @~chinese �õ����ӵĵ�һ������ĵ㡣*/
    Vec2 getAnchr1() const;

    /** @~english Set the anchor point on body a. @~chinese �������ӵĵ�һ������ĵ㡣*/
    void setAnchr1(const Vec2& anchr1);

    /** @~english Get the anchor point on body b. @~chinese �õ����ӵĵڶ�������ĵ㡣*/
    Vec2 getAnchr2() const;

    /** @~english Set the anchor point on body b. @~chinese �������ӵĵڶ�������ĵ㡣*/
    void setAnchr2(const Vec2& anchr2);
    
    /** @~english Get the distance of the anchor points. @~chinese �õ����ӵ�֮��ľ��롣*/
    float getRestLength() const;
    
    /** @~english Set the distance of the anchor points. @~chinese �������ӵ�֮��ľ��롣*/
    void setRestLength(float restLength);
    
    /** @~english Get the spring constant. @~chinese �õ�����������*/
    float getStiffness() const;
    
    /** @~english Set the spring constant. @~chinese ���õ���������*/
    void setStiffness(float stiffness);
    
    /** @~english Get the spring soft constant. @~chinese �õ�����ϵ����*/
    float getDamping() const;
    
    /** @~english Set the spring soft constant. @~chinese ��������ϵ����*/
    void setDamping(float damping);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointSpring() {}
    virtual ~PhysicsJointSpring() {}

    Vec2 _anchr1;
    Vec2 _anchr2;
    float _stiffness;
    float _damping;
};

/** 
@class PhysicsJointGroove
@brief
@~english Attach body a to a line, and attach body b to a dot.  
@~chinese �ѵ�һ������A���ӵ�һ�����ϣ��ѵڶ����������ӵ�һ�����ϡ�
*/
class CC_DLL PhysicsJointGroove : public PhysicsJoint
{
public:
    /** @~english Create a groove joint.
     
     * @~chinese ����һ��PhysicsJointGroove��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param grooveA @~english The line begin position.
     * @~chinese ���ӵĵ�һ��������ߵĵ�һ���˵㡣
     @param grooveB @~english The line end position.
     * @~chinese ���ӵĵ�һ��������ߵĵڶ����˵㡣
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese ���ӵĵڶ�������ĵ㡣
     @return @~english A object pointer.
     * @~chinese �õ�PhysicsJointGroove��
     */
    static PhysicsJointGroove* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& grooveA, const Vec2& grooveB, const Vec2& anchr2);

    /** @~english Get the line begin position @~chinese �õ���һ�����������ߵĵ�һ���˵㡣*/
    Vec2 getGrooveA() const;

    /** @~english Set the line begin position @~chinese ���õ�һ�����������ߵĵ�һ���˵㡣*/
    void setGrooveA(const Vec2& grooveA);
    
    /** @~english Get the line end position @~chinese �õ���һ�����������ߵĵڶ����˵㡣*/
    Vec2 getGrooveB() const;
    
    /** @~english Set the line end position @~chinese ���õõ���һ�����������ߵĵڶ����˵㡣*/
    void setGrooveB(const Vec2& grooveB);
    
    /** @~english Get the anchor point on body b. @~chinese �õ����ӵĵڶ�������ĵ㡣*/
    Vec2 getAnchr2() const;
    
    /** @~english Set the anchor point on body b. @~chinese �������ӵĵڶ�������ĵ㡣*/
    void setAnchr2(const Vec2& anchr2);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointGroove() {}
    virtual ~PhysicsJointGroove() {}

    Vec2 _grooveA;
    Vec2 _grooveB;
    Vec2 _anchr2;
};

/** 
@class PhysicsJointRotarySpring
@brief
@~english Likes a spring joint, but works with rotary.  
@~chinese ��PhysicsJointSpring���ƣ����Ǹ������������ת��
*/
class CC_DLL PhysicsJointRotarySpring : public PhysicsJoint
{
public:
    /** @~english Create a damped rotary spring joint.
     
     * @~chinese ����һ��PhysicsJointRotarySpring��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param stiffness @~english It's the spring constant.
     * @~chinese �ؽڵĵ���ϵ����
     @param damping @~english It's how soft to make the damping of the spring.
     * @~chinese �ؽڵ����ᡣ
     @return @~english A object pointer.
     * @~chinese �ɷ�����׼��
     */
    static PhysicsJointRotarySpring* construct(PhysicsBody* a, PhysicsBody* b, float stiffness, float damping);

    /** @~english Get the relative angle in radians from the body a to b. @~chinese �õ�������������֮�����Ի��Ƚǡ�*/
    float getRestAngle() const;

    /** @~english Set the relative angle in radians from the body a to b. @~chinese ����������������֮�����Ի��Ƚǡ�*/
    void setRestAngle(float restAngle);

    /** @~english Get the spring constant. @~chinese �õ�����ϵ����*/
    float getStiffness() const;
    
    /** @~english Set the spring constant. @~chinese ���õ���ϵ����*/
    void setStiffness(float stiffness);
    
    /** @~english Get the spring soft constant. @~chinese �õ�����ϵ����*/
    float getDamping() const;

    /** @~english Set the spring soft constant. @~chinese ��������ϵ����*/
    void setDamping(float damping);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointRotarySpring() {}
    virtual ~PhysicsJointRotarySpring() {}

    float _stiffness;
    float _damping;
};

/** 
@~english Likes a limit joint, but works with rotary.  
@~chinese ��PhysicsJointLimit���ƣ����Ǹ������������ת��
*/
class CC_DLL PhysicsJointRotaryLimit : public PhysicsJoint
{
public:
    /** @~english Create a limit rotary joint.
     
     * @~chinese ����һ��PhysicsJointRotaryLimit��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param min @~english It's min rotation limit in radians.
     * @~chinese ��������֮�����С��ת�Ƕȡ�
     @param max @~english It's max rotation limit in radians.
     * @~chinese ��������֮��������ת�Ƕȡ�
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointRotaryLimit��
     */
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b, float min, float max);

    /** @~english Create a limit rotary joint.
     
     * @~chinese ����һ��PhysicsJointRotaryLimit��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointRotaryLimit��
     */
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b);

    /** @~english Get the min rotation limit. @~chinese �õ���С��ת�Ƕȡ�*/
    float getMin() const;
    
    /** @~english Set the min rotation limit. @~chinese ������С��ת�Ƕȡ�*/
    void setMin(float min);
    
    /** @~english Get the max rotation limit. @~chinese �õ������ת�Ƕȡ�*/
    float getMax() const;
    
    /** @~english Set the max rotation limit. @~chinese ���������ת�Ƕȡ�*/
    void setMax(float max);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointRotaryLimit() {}
    virtual ~PhysicsJointRotaryLimit() {}

    float _min;
    float _max;
};

/** 
@~english Works like a socket wrench.  
@~chinese PhysicsJointRatchet����һ��������һ��ӿ�������������塣
*/
class CC_DLL PhysicsJointRatchet : public PhysicsJoint
{
public:
    /** @~english Create a ratchet joint.
     
     * @~chinese ����һ��PhysicsJointRatchet��
     * 
     @param a @~english A is the body to connect.
     * @~chinese Ҫ�����ӵ�����A��
     @param b @~english B is the body to connect.
     * @~chinese Ҫ�����ӵ�����B��
     @param phase @~english Phase is the initial offset to use when deciding where the ratchet angles are.
     * @~chinese �׶εĳ�ʼƫ����ʹ�õ��������ֽǶ������
     @param ratchet @~english Ratchet is the distance between "clicks".
     * @~chinese �����ǡ������֮��ľ��롣
     @return @~english A object pointer.
     * @~chinese �����ɹ�����PhysicsJointRatchet���󣬷��򷵻ؿ�ָ�롣
     */
    static PhysicsJointRatchet* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratchet);

    /** @~english Get the ratchet angle. @~chinese ���ֽǡ�*/
    float getAngle() const;
    
    /** @~english Set the ratchet angle. @~chinese ���ü��ֽǡ�*/
    void setAngle(float angle);
    
    /** @~english Get the initial offset. @~chinese ��õĳ�ʼƫ������*/
    float getPhase() const;
    
    /** @~english Set the initial offset. @~chinese ���ó�ʼƫ������*/
    void setPhase(float phase);
    
    /** @~english Get the distance between "clicks". @~chinese �������֮��ľ��롣*/
    float getRatchet() const;

    /** @~english Set the distance between "clicks". @~chinese �������֮��ľ��롣*/
    void setRatchet(float ratchet);
    virtual bool createConstraints() override;

protected:
    PhysicsJointRatchet() {}
    virtual ~PhysicsJointRatchet() {}

    float _phase;
    float _ratchet;
};

/** 
@~english Keeps the angular velocity ratio of a pair of bodies constant.  
@~chinese ����������֮�����ת���ٶȱ���һ��������
*/
class CC_DLL PhysicsJointGear : public PhysicsJoint
{
public:
    /** @~english Create a gear joint.
     
     * @~chinese ����һ��PhysicsJointGear��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param phase @~english Phase is the initial angular offset of the two bodies.
     * @~chinese ��������ĳ�ʼ�ǶȲ
     @param ratio @~english Ratio is always measured in absolute terms.
     * @~chinese �����������ת���ٶȱȡ�
     @return @~english A object pointer.
     * @~chinese ���ص�PhysicsJointGear��
     */
    static PhysicsJointGear* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratio);

    /** @~english Get the angular offset of the two bodies. @~chinese �õ���������ĳ�ʼ�ǶȲ*/
    float getPhase() const;
    
    /** @~english Set the angular offset of the two bodies. @~chinese ������������ĳ�ʼ�ǶȲ*/
    void setPhase(float phase);
    
    /** @~english Get the ratio. @~chinese �õ���ת���ٶȱ��ʡ�*/
    float getRatio() const;
    
    /** @~english Set the ratio. @~chinese ������ת���ٶȱ��ʡ�*/
    void setRatio(float ratchet);

    virtual bool createConstraints() override;

protected:
    PhysicsJointGear() {}
    virtual ~PhysicsJointGear() {}

    float _phase;
    float _ratio;
};

/** 
@~english Keeps the relative angular velocity of a pair of bodies constant.  
@~chinese PhysicsJointMotor���ڱ�֤�����������Խ��ٶ���һ��������
*/
class CC_DLL PhysicsJointMotor : public PhysicsJoint
{
public:
    /** @~english Create a motor joint.
     
     * @~chinese ����һ��PhysicsJointMotor��
     * 
     @param a @~english A is the body to connect.
     * @~chinese ���ӵĵ�һ�����塣
     @param b @~english B is the body to connect.
     * @~chinese ���ӵĵڶ������塣
     @param rate @~english Rate is the desired relative angular velocity.
     * @~chinese �����������Խ��ٶ�
     @return @~english A object pointer.
     * @~chinese ����PhysicsJointMotor��
     */
    static PhysicsJointMotor* construct(PhysicsBody* a, PhysicsBody* b, float rate);

    /** @~english Get the relative angular velocity. @~chinese �õ���Խ��ٶȡ�*/
    float getRate() const;
    
    /** @~english Set the relative angular velocity. @~chinese ������Խ��ٶȡ�*/
    void setRate(float rate);
    virtual bool createConstraints() override;

protected:
    PhysicsJointMotor() {}
    virtual ~PhysicsJointMotor() {}

    float _rate;
};

/** @} */
/** @} */


NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_JOINT_H__
