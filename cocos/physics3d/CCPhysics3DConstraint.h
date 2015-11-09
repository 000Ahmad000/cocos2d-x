/***************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __PHYSICS_3D_CONSTRAINT_H__
#define __PHYSICS_3D_CONSTRAINT_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "base/ccConfig.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

class btTypedConstraint;

NS_CC_BEGIN

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_3d
 * @{
*/

class Physics3DRigidBody;

/**
    @class Physics3DConstraint
    @brief @~english Constraint affects the movement of physics object, it usually connet one or two physics object. There are some types of physics constraints.
    @~chinese Լ��Ӱ�����������˶�����ͨ������һ���������������
*/
class CC_DLL Physics3DConstraint : public Ref
{
public:
    enum class ConstraintType
    {
        UNKNOWN,
        POINT_TO_POINT,
        HINGE,
        SLIDER,
        CONE_TWIST,
        SIX_DOF,
    };
    /** @~english get the impulse that break the constraint
        @~chinese ��ȡ����Լ���ķ�ֵ
        @return @~english the impulse that break the constraint @~chinese ����Լ���ķ�ֵ
    */
    float getBreakingImpulse() const;

    /** @~english set the impulse that break the constraint
        @~chinese ���ô���Լ���ķ�ֵ
        @param impulse @~english  the impulse that break the constraint @~chinese ����Լ���ķ�ֵ
    */
    void setBreakingImpulse(float impulse);

    /** @~english is it enabled
        @~chinese Լ���Ƿ�����
        @return @~english whether the constraint is enabled @~chinese Լ���Ƿ�����
    */
    bool isEnabled() const;

    /** @~english set enable or not
        @~chinese ����Լ��
        @param enabled @~english  whether the constraint will be enabled @~chinese Լ���Ƿ�����
    */
    void setEnabled(bool enabled);

    /** @~english get rigid body a
        @~chinese �õ�����a
        @return @~english the Physics3DRigidBody A @~chinese ����a
    */
    Physics3DRigidBody* getBodyA() const { return _bodyA; }

    /** @~english get rigid body b
        @~chinese �õ�����b
        @return @~english the Physics3DRigidBody B @~chinese ����b
    */
    Physics3DRigidBody* getBodyB() const { return _bodyB; }

    /** @~english get constraint type
        @~chinese �õ�Լ������
        @return @~english the constraint type @~chinese Լ������
    */
    ConstraintType getConstraintType() const { return _type; }

    /** @~english get user data
        @~chinese �����û�����
        @param userData @~english the user data will be seted @~chinese �û�����
    */
    void setUserData(void* userData) { _userData = userData; }

    /** @~english get user data
        @~chinese ��ȡ�û�����
        @return @~english the user data @~chinese �û�����
    */
    void* getUserData() const { return _userData; }

    /** @~english get override number of solver iterations
        @~chinese �õ���������������
        @return @~english the override number of solver iterations @~chinese ��������������
    */
    int getOverrideNumSolverIterations() const;

    /** @~english override the number of constraint solver iterations used to solve this constraint, -1 will use the default number of iterations, as specified in SolverInfo.m_numIterations
        @~chinese ����Լ������������������-1��ʹ��Ĭ�ϵ�������
        @param overideNumIterations @~english  the number of constraint solver iterations @~chinese Լ�����ĵ�������
    */
    void setOverrideNumSolverIterations(int overideNumIterations);

#if (CC_ENABLE_BULLET_INTEGRATION)
    btTypedConstraint* getbtContraint() { return _constraint; }
#endif

protected:

    Physics3DConstraint();
    virtual ~Physics3DConstraint();

    btTypedConstraint* _constraint;

    Physics3DRigidBody* _bodyA;
    Physics3DRigidBody* _bodyB;

    ConstraintType      _type;
    void*               _userData;
};

/**
    Point to point constraint limits the translation so that the local pivot points of 2 rigidbodies match in worldspace.
    @~chinese
*/
class CC_DLL Physics3DPointToPointConstraint : public Physics3DConstraint
{
public:
    /** @~english create point to point constraint, limits the translation of local pivot point of rigid body A
        @~chinese ������Ե��Լ�������Ƹ���A�������ƽ��
        @param rbA @~english  The rigid body going to be fixed @~chinese ����A
        @param pivotPointInA @~english  local pivot point in A's local space @~chinese ��һ���ֲ��ռ�ľֲ�֧��
        @return @~english created constraint @~chinese ����Լ��
    */
    static Physics3DPointToPointConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA);

    /** @~english create point to point constraint, make the local pivot points of 2 rigid bodies match in worldspace.
        @~chinese ������Ե��Լ����ʹ�������������������ռ�����ƥ�䡣
        @param rbA @~english  The rigid body A going to be fixed @~chinese ҪԼ���ĸ���A
        @param rbB @~english  The rigid body B going to be fixed @~chinese ҪԼ���ĸ���B
        @param pivotPointInA @~english  local pivot point in A's local space @~chinese ��A�ľֲ��ռ�ľֲ�֧��
        @param pivotPointInB @~english  local pivot point in B's local space @~chinese ��B�ľֲ��ռ�ľֲ�֧��
        @return @~english created constraint @~chinese ����Լ��
    */
    static Physics3DPointToPointConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB);

    /** @~english set pivot point in A's local space
        @~chinese ��A�ľֲ��ռ�����֧��
        @param pivotA @~english  pivot point in A's local space @~chinese ��A�ľֲ��ռ��֧��
    */
    void setPivotPointInA(const cocos2d::Vec3& pivotA);

    /** @~english set pivot point in B's local space
        @~chinese ��B�ľֲ��ռ�����֧��
        @param pivotB @~english  pivot point in B's local space @~chinese ��B�ľֲ��ռ��֧��
    */
    void setPivotPointInB(const cocos2d::Vec3& pivotB);

    /** @~english get pivot point in A's local space
        @~chinese �õ�A�ľֲ��ռ��֧��
        @return @~english pivot point in A's local space @~chinese A�ľֲ��ռ��֧��
    */
    cocos2d::Vec3 getPivotPointInA() const;

    /** @~english get pivot point in B's local space
        @~chinese �õ�B�ľֲ��ռ��֧��
        @return @~english pivot point in B's local space @~chinese B�ľֲ��ռ��֧��
    */
    cocos2d::Vec3 getPivotPointInB() const;

CC_CONSTRUCTOR_ACCESS:
    Physics3DPointToPointConstraint();
    virtual ~Physics3DPointToPointConstraint();
    bool init(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA);
    bool init(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB);

};

/** @~english Hinge constraint restricts two additional angular degrees of freedom, so the body can only rotate around one axis, the hinge axis. This can be useful to represent doors or wheels rotating around one axis.    hinge constraint between two rigidbodies each with a pivotpoint that descibes the axis location in local space
    @~chinese ����Լ�������������ӵĽ����ɶȣ����Ը���ֻ����һ���ᣬ�����ᡣ����ʮ���ʺϱ�ʾ�Ż���Χ��һ������ת����������֮��Ľ���Լ���ɸ��Ծֲ��ռ��ڵ���������ʾ
*/
class CC_DLL Physics3DHingeConstraint : public Physics3DConstraint
{
public:
    /** @~english create hinge constraint
        @~chinese ��������Լ��
        @param rbA @~english  rigid body A @~chinese ����A
        @param rbAFrame @~english  rigid body A's frame @~chinese ����ľ���
        @param useReferenceFrameA @~english  use frame A as reference @~chinese ʹ�þ�����Ϊ�ο�
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese ����һ���Զ��ͷŵ�physics3dhingeconstraint��
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& rbAFrame, bool useReferenceFrameA = false);

    /** @~english create hinge constraint
        @~chinese ��������Լ��
        @param rbA @~english  rigid body A @~chinese ����A
        @param pivotInA @~english  pivot in rigid body A's local space @~chinese �ڸ���A�ľֲ��ռ��ڵ�����
        @param axisInA @~english  axis in rigid body A's local space @~chinese �ڸ���A�ľֲ��ռ��ڵ�����
        @param useReferenceFrameA @~english  use frame A as reference @~chinese ʹ�þ�����Ϊ����
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese ����һ���Զ��ͷŵ�physics3dhingeconstraint��
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotInA, const cocos2d::Vec3& axisInA, bool useReferenceFrameA = false);

    /** @~english create hinge constraint
        @~chinese ��������Լ��
        @param rbA @~english  rigid body A @~chinese ����A
        @param rbB @~english  rigid body B @~chinese ����B
        @param pivotInA @~english  pivot point in A's local space @~chinese ��A�ľֲ��ռ������
        @param pivotInB @~english  pivot point in B's local space @~chinese ��B�ľֲ��ռ������
        @param axisInA @~english  axis in A's local space @~chinese ��A�ľֲ��ռ���
        @param axisInB @~english  axis in B's local space @~chinese ��B�ľֲ��ռ���
        @param useReferenceFrameA @~english  use frame A as reference @~chinese ʹ��֡��Ϊ�ο�
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese ����һ���Զ��ͷŵ�physics3dhingeconstraint��
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotInA,const cocos2d::Vec3& pivotInB, cocos2d::Vec3& axisInA, cocos2d::Vec3& axisInB, bool useReferenceFrameA = false);

    /** @~english create hinge constraint
        @~chinese ��������Լ��
        @param rbA @~english  rigid body A @~chinese ����A
        @param rbB @~english  rigid body B @~chinese ����B
        @param rbAFrame @~english  rigid body A's frame @~chinese ����A�ľ���
        @param rbBFrame @~english  rigid body B's frame @~chinese ����B�ľ���
        @param useReferenceFrameA @~english  use frame A as reference @~chinese ʹ��֡��Ϊ�ο�
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese ����һ���Զ��ͷŵ�physics3dhingeconstraint��
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& rbAFrame, const cocos2d::Mat4& rbBFrame, bool useReferenceFrameA = false);

    /** @~english get rigid body A's frame offset
        @~chinese �õ������֡ƫ��
        @return @~english rigid body A's frame offset @~chinese �����֡ƫ��
    */
    cocos2d::Mat4 getFrameOffsetA() const;

    /** @~english get rigid body B's frame offset
        @~chinese �õ�����B֡ƫ��
        @return @~english rigid body B's frame offset @~chinese ����B֡ƫ��
    */
    cocos2d::Mat4 getFrameOffsetB() const;

    /** @~english set frames for rigid body A and B
        @~chinese Ϊ����A��B����֡
        @param frameA @~english  frame will be seted to rigid body A @~chinese ���ø�����A�ľ���
        @param frameB @~english  frame will be seted to rigid body B @~chinese ���ø�����B�ľ���
    */
    void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

    /** @~english set angular only
        @~chinese ���ý�
        @param angularOnly @~english  angular will be set @~chinese ��Ҫ���õĽ�
    */
    void setAngularOnly(bool angularOnly);

    /** @~english enable angular motor
        @~chinese ʹ�ǵ��
        @param enableMotor @~english  whether to enable AngularMotor @~chinese �Ƿ�����angularmotor
        @param targetVelocity @~english  target velocity @~chinese Ŀ���ٶ�
        @param maxMotorImpulse @~english  max motor impulse @~chinese ���������
    */
    void enableAngularMotor(bool enableMotor, float targetVelocity, float maxMotorImpulse);

    /** @~english extra motor API, including ability to set a target rotation (as opposed to angular velocity)
        @~chinese ����ĵ����API�������趨һ��Ŀ����ת����������ٶȣ�
        @param enableMotor @~english  whether to enable AngularMotor @~chinese �Ƿ�����angularmotor
        @note: setMotorTarget sets angular velocity under the hood, so you must call it every tick to
           maintain a given angular target.
    */
    void enableMotor(bool enableMotor);

    /** @~english set max motor impulse
        @~chinese �������������
        @param maxMotorImpulse @~english   max motor impulse @~chinese ���������
    */
    void setMaxMotorImpulse(float maxMotorImpulse);

    /** @~english set motor target
        @~chinese ���õ����Ŀ��
    */
    void setMotorTarget(const cocos2d::Quaternion& qAinB, float dt);
    /** @~english set motor target
        @~chinese �����˶�Ŀ��
    */
    void setMotorTarget(float targetAngle, float dt);

    /** @~english set limit
        @~chinese ��������
    */
    void setLimit(float low, float high, float _softness = 0.9f, float _biasFactor = 0.3f, float _relaxationFactor = 1.0f);
    /** set axis
        @~chinese
    */
    void setAxis(const cocos2d::Vec3& axisInA);
    /** @~english get lower limit
        @~chinese ��ýϵ͵ļ���
    */
    float getLowerLimit() const;
    /** @~english get upper limit
        @~chinese �������
    */
    float getUpperLimit() const;
    /** @~english get hinge angle
        @~chinese �ѽ���ת��
    */
    float getHingeAngle() const;
    /** @~english get hinge angle
        @~chinese �ѽ���ת��
    */
    float getHingeAngle(const cocos2d::Mat4& transA, const cocos2d::Mat4& transB);

    /** @~english get A's frame
        @~chinese �õ�A�ľ���
    */
    cocos2d::Mat4 getAFrame() const;
    /** @~english get B's frame
        @~chinese �õ�B�ľ���
    */
    cocos2d::Mat4 getBFrame() const;
    /** @~english get angular only
        @~chinese ֻ�л�ý�
    */
    bool getAngularOnly() const;
    /** @~english get enable angular motor
        @~chinese ��ʹ�ǵ��
    */
    bool getEnableAngularMotor() const;
    /** @~english get motor target velosity
        @~chinese �õ��˶�Ŀ���ٶ�
    */
    float getMotorTargetVelosity() const;
    /** @~english get max motor impulse
        @~chinese ���������
    */
    float getMaxMotorImpulse() const;

    /** @~english access for UseFrameOffset
        @~chinese ����useframeoffset
    */
    bool getUseFrameOffset() const;
    /** @~english set use frame offset
        @~chinese ʹ��֡ƫ��
    */
    void setUseFrameOffset(bool frameOffsetOnOff);

CC_CONSTRUCTOR_ACCESS:
    Physics3DHingeConstraint()
    {
        _type = ConstraintType::HINGE;
    }
    virtual ~Physics3DHingeConstraint() {}
};

/**
    It allows the body to rotate around x axis and translate along this axis.
    softness, restitution and damping for different cases
    DirLin - moving inside linear limits
    LimLin - hitting linear limit
    DirAng - moving inside angular limits
    LimAng - hitting angular limit
    OrthoLin, OrthoAng - against constraint axis
*/
class CC_DLL Physics3DSliderConstraint : public Physics3DConstraint
{
public:
    /** @~english create slider constraint
        @~chinese ��������Լ��

        @param rbA @~english  rigid body A @~chinese ����A
        @param rbB @~english  rigid body B @~chinese ����B
        @param frameInA @~english  frame in A's local space @~chinese ��A�ľֲ��ռ����
        @param frameInB @~english  frame in B's local space @~chinese ��B�ľֲ��ռ����
        @param useLinearReferenceFrameA @~english  use fixed frame A for linear limits @~chinese ʹ�ù̶���������Է�Χ
    */
    static Physics3DSliderConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB ,bool useLinearReferenceFrameA);

    /** @~english get A's frame offset
        @~chinese �õ���֡ƫ��
    */
    cocos2d::Mat4 getFrameOffsetA() const;
    /** @~english get B's frame offset
        @~chinese �õ�B��֡ƫ��
    */
    cocos2d::Mat4 getFrameOffsetB() const;
    /** @~english get lower linear limit
        @~chinese ��ýϵ͵���������
    */
    float getLowerLinLimit() const;
    /** @~english set lower linear limit
        @~chinese ���ýϵ͵���������
    */
    void setLowerLinLimit(float lowerLimit);
    /** @~english get upper linear limit
        @~chinese �������Լ���
    */
    float getUpperLinLimit() const;
    /** @~english set upper linear limit
        @~chinese ���ϵ���������
    */
    void setUpperLinLimit(float upperLimit);
    /** @~english get lower angular limit
        @~chinese ��ýϵ͵ļ��޽�
    */
    float getLowerAngLimit() const;
    /** @~english set lower angualr limit
        @~chinese �ͽ�����
    */
    void setLowerAngLimit(float lowerLimit);
    /** @~english get upper anglular limit
        @~chinese ���Ͻǵ�����
    */
    float getUpperAngLimit() const;
    /** @~english set upper anglular limit
        @~chinese ���Ͻ�����
    */
    void setUpperAngLimit(float upperLimit);
    /** @~english use A's frame as linear refference
        @~chinese ʹ�����Բο��ľ���
    */
    bool getUseLinearReferenceFrameA() const;

    float getSoftnessDirLin() const;
    float getRestitutionDirLin() const;
    float getDampingDirLin() const;
    float getSoftnessDirAng() const;
    float getRestitutionDirAng() const;
    float getDampingDirAng() const;
    float getSoftnessLimLin() const;
    float getRestitutionLimLin() const;
    float getDampingLimLin() const;
    float getSoftnessLimAng() const;
    float getRestitutionLimAng() const;
    float getDampingLimAng() const;
    float getSoftnessOrthoLin() const;
    float getRestitutionOrthoLin() const;
    float getDampingOrthoLin() const;
    float getSoftnessOrthoAng() const;
    float getRestitutionOrthoAng() const;
    float getDampingOrthoAng() const;
    void setSoftnessDirLin(float softnessDirLin);
    void setRestitutionDirLin(float restitutionDirLin);
    void setDampingDirLin(float dampingDirLin);
    void setSoftnessDirAng(float softnessDirAng);
    void setRestitutionDirAng(float restitutionDirAng);
    void setDampingDirAng(float dampingDirAng);
    void setSoftnessLimLin(float softnessLimLin);
    void setRestitutionLimLin(float restitutionLimLin);
    void setDampingLimLin(float dampingLimLin);
    void setSoftnessLimAng(float softnessLimAng);
    void setRestitutionLimAng(float restitutionLimAng);
    void setDampingLimAng(float dampingLimAng);
    void setSoftnessOrthoLin(float softnessOrthoLin);
    void setRestitutionOrthoLin(float restitutionOrthoLin);
    void setDampingOrthoLin(float dampingOrthoLin);
    void setSoftnessOrthoAng(float softnessOrthoAng);
    void setRestitutionOrthoAng(float restitutionOrthoAng);
    void setDampingOrthoAng(float dampingOrthoAng);
    void setPoweredLinMotor(bool onOff);
    bool getPoweredLinMotor() const;
    void setTargetLinMotorVelocity(float targetLinMotorVelocity);
    float getTargetLinMotorVelocity() const;
    void setMaxLinMotorForce(float maxLinMotorForce);
    float getMaxLinMotorForce() const;
    void setPoweredAngMotor(bool onOff);
    bool getPoweredAngMotor() const;
    void setTargetAngMotorVelocity(float targetAngMotorVelocity);
    float getTargetAngMotorVelocity() const;
    void setMaxAngMotorForce(float maxAngMotorForce);
    float getMaxAngMotorForce() const;

    float getLinearPos() const;
    float getAngularPos() const;

    /** @~english access for UseFrameOffset
        @~chinese ��ȡuseframeoffset
    */
    bool getUseFrameOffset() const;
    /** @~english set use frame offset
        @~chinese ʹ��֡ƫ��
    */
    void setUseFrameOffset(bool frameOffsetOnOff);

    /** @~english set frames for rigid body A and B
        @~chinese ���ø���A��B��֡
    */
    void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

CC_CONSTRUCTOR_ACCESS:
    Physics3DSliderConstraint()
    {
        _type = ConstraintType::SLIDER;
    }
    virtual ~Physics3DSliderConstraint() {}
};

/**
    It is a special point to point constraint that adds cone and twist axis limits. The x-axis serves as twist axis.
    @~chinese
*/
class CC_DLL Physics3DConeTwistConstraint : public Physics3DConstraint
{
public:
    /** @~english create cone twist constraint
        @~chinese ����Բ׶ŤתԼ��
        rbA rigid body A
        frameA A's local frame
    */
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& frameA);
    /** @~english create cone twist constraint
        @~chinese ����Բ׶ŤתԼ��
        rbA rigid body A
        rbB rigid body B
        frameA rigid body A's local frame
        frameB rigid body B's local frame
    */
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

    /** @~english set limits
        @~chinese �趨����

        @param swingSpan1 @~english  swing span1 @~chinese ��span1
        @param swingSpan2 @~english  swing span2 @~chinese ��span2
        @param twistSpan @~english  twist span @~chinese Ť��
        @param softness @~english  0->1, recommend ~0.8->1. Describes % of limits where movement is free. Beyond this softness %, the limit is gradually enforced until the "hard" (1.0) limit is reached. @~chinese 0 -> 1���Ƽ�~ 0.8 -> 1�������˶��������ˡ�����֮��������ԣ�������ִ��ֱ����Ӳ����1���ﵽ���ޡ�
        @param biasFactor @~english  0->1?, recommend 0.3 +/-0.3 or so. Strength with which constraint resists zeroth order (angular, not angular velocity) limit violation. @~chinese 0��1�����Ƽ�0.3 / 0.3���ҡ�������Լ��������ף��ǣ�û�н��ٶȣ�Υ�����ơ�
        @param relaxationFactor @~english  0->1, recommend to stay near 1. the lower the value, the less the constraint will fight velocities which violate the angular limits. @~chinese 0 -> 1��������1������ֵԽ�ͣ�Խ�ٵ�Լ�������Υ���Ǽ����ٶȡ�
    */
    void setLimit(float swingSpan1,float swingSpan2,float twistSpan, float softness = 1.f, float biasFactor = 0.3f, float relaxationFactor = 1.0f);

    /** @~english get A's frame
        @~chinese �õ��ľ���
    */
    cocos2d::Mat4 getAFrame() const;
    /** @~english get B's frame
        @~chinese �õ�B�ľ���
    */
    cocos2d::Mat4 getBFrame() const;

    /** @~english get swing span1
        @~chinese �õ�span1�ڶ�
    */
    float getSwingSpan1() const;
    /** @~english get swing span2
        @~chinese �õ�span2�ڶ�
    */
    float getSwingSpan2() const;
    /** @~english get twist span
        @~chinese �õ�Ť��
    */
    float getTwistSpan() const;
    /** @~english get twist angle
        @~chinese �õ�Ť��
    */
    float getTwistAngle() const;

    /** @~english set damping
        @~chinese ��������
    */
    void setDamping(float damping);

    /** @~english enable motor
        @~chinese ʹ���
    */
    void enableMotor(bool b);
    /** @~english set max motor impulse
        @~chinese �������������
    */
    void setMaxMotorImpulse(float maxMotorImpulse);
    /** @~english set max motor impulse normalize
        @~chinese �������������淶
    */
    void setMaxMotorImpulseNormalized(float maxMotorImpulse);
    /** @~english get fix thresh
        @~chinese �õ��̶���ֵ
    */
    float getFixThresh() const;
    /** @~english set fix thresh
        @~chinese �趨�̶���ֵ
    */
    void setFixThresh(float fixThresh);

    /** @~english setMotorTarget
        @~chinese setmotortarget
        @param q @~english  the desired rotation of bodyA wrt bodyB. Note: if q violates the joint limits, the internal target is clamped to avoid conflicting impulses (very bad for stability), also don't forget to enableMotor() @~chinese ��������������������ת��ע�⣺���Q�ַ��ؽ����ƣ��ڲ�Ŀ���Ǽн������ͻ�ĳ嶯���ȶ��Ժܲ��Ҳ������enablemotor()
    */
    void setMotorTarget(const btQuaternion& q);

    /** @~english setMotorTarget, q is the desired rotation of frameA wrt frameB in constraint space
        @~chinese setmotortarget��Q���������ת����WRT FRAMEB��Լ���ռ�
    */
    void setMotorTargetInConstraintSpace(const btQuaternion& q);

    /** @~english get point for angle
        @~chinese ��ȡAngle�ĵ�
    */
    cocos2d::Vec3 GetPointForAngle(float fAngleInRadians, float fLength) const;

    /** @~english set A and B's frame
        @~chinese ����A��B�ľ���
    */
    virtual void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

    /** @~english get A's frame offset
        @~chinese �õ���֡ƫ��
    */
    cocos2d::Mat4 getFrameOffsetA() const;

    /** @~english get B's frame offset
        @~chinese �õ�B��֡ƫ��
    */
    cocos2d::Mat4 getFrameOffsetB() const;

CC_CONSTRUCTOR_ACCESS:
    Physics3DConeTwistConstraint()
    {
        _type = ConstraintType::CONE_TWIST;
    }
    virtual ~Physics3DConeTwistConstraint() {}
};

/**
    This generic constraint can emulate a variety of standard constraints, by configuring each of the 6 degrees of freedom (dof).
    The first 3 dof axis are linear axis, which represent translation of rigidbodies, and the latter 3 dof axis represent the angular motion.
    Each axis can be either locked, free or limited. All axis are locked by default.
    For each axis:

    Lowerlimit == Upperlimit -> axis is locked.
    Lowerlimit > Upperlimit -> axis is free
    Lowerlimit < Upperlimit -> axis it limited in that range

    @~chinese
*/
class CC_DLL Physics3D6DofConstraint : public Physics3DConstraint
{
public:
    /** @~english create 6 dof constraint
        @~chinese ����6���ɶ�Լ��
        @param rbA @~english  rigid body A @~chinese ����A
        @param rbB @~english  rigid body B @~chinese ����B
        @param frameInA @~english  frame in A's local space @~chinese ��A�ľֲ��ռ����
        @param frameInB @~english  frame in B's local space @~chinese ��B�ľֲ��ռ����
        @param useLinearReferenceFrameA @~english  use fixed frame A for linear limits @~chinese ʹ�ù̶���������Է�Χ
    */
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameA);

    /** @~english create 6 dof constraint
        @~chinese ����6���ɶ�Լ��
        @param rbB @~english  rigid body B @~chinese ����B
        @param frameInB @~english  frame in B's local space @~chinese ��B�ľֲ��ռ����
        @param useLinearReferenceFrameB @~english  use fixed frame B for linear limits @~chinese ʹ�ù̶���B֡�����Է�Χ
    */
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameB);

    /** @~english set linear lower limit
        @~chinese ������������
    */
    void setLinearLowerLimit(const cocos2d::Vec3& linearLower);

    /** @~english get linear lower limit
        @~chinese �õ���������
    */
    cocos2d::Vec3 getLinearLowerLimit() const;

    /** @~english set linear upper limit
        @~chinese ������������
    */
    void setLinearUpperLimit(const cocos2d::Vec3& linearUpper);

    /** @~english get linear upper limit
        @~chinese �õ���������
    */
    cocos2d::Vec3 getLinearUpperLimit() const;

    /** @~english set angular lower limit
        @~chinese ���ý�����
    */
    void setAngularLowerLimit(const cocos2d::Vec3& angularLower);

    /** @~english get angular lower limit
        @~chinese ��ý�����
    */
    cocos2d::Vec3 getAngularLowerLimit() const;

    /** @~english set angular upper limit
        @~chinese ���ý�����
    */
    void setAngularUpperLimit(const cocos2d::Vec3& angularUpper);

    /** @~english get angular upper limit
        @~chinese ��ý�����
    */
    cocos2d::Vec3 getAngularUpperLimit() const;

    /** @~english is limited?
        @~chinese �����޵ģ�
        @param limitIndex @~english  first 3 are linear, next 3 are angular @~chinese ǰ3���������Եģ���������3��
    */
    bool isLimited(int limitIndex) const;

    /** @~english access for UseFrameOffset
        @~chinese ����useframeoffset
    */
    bool getUseFrameOffset() const;
    /** @~english set use frame offset
        @~chinese ʹ��֡ƫ��
    */
    void setUseFrameOffset(bool frameOffsetOnOff) const;


CC_CONSTRUCTOR_ACCESS:
    Physics3D6DofConstraint()
    {
        _type = ConstraintType::SIX_DOF;
    }
    virtual ~Physics3D6DofConstraint() {}
};

// end of physics_3d group
/// @}
// end of physics group
/// @}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_CONSTRAINT_H__
