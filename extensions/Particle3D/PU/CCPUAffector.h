/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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

#ifndef __CC_PU_PARTICLE_3D_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_AFFECTOR_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DAffector.h"
#include <vector>
#include <string>

NS_CC_BEGIN

struct PUParticle3D;
class PUParticleSystem3D;

/**
* @addtogroup _3d
* @{
*/

/** @class PUAffector
*@brief @~english PUAffector inherit from Particle3DAffector, the base class of pu affector.
 affectors modify particles in a particle system over their lifetime. This class defines
 the interface, and provides a few implementations of some basic functions.

 @~chinese PUAffector�̳���Particle3DAffector����puӰ�����Ļ��ࡣ
 Ӱ�����������ӵ����������ڸı�������Ϊ��һ�����ߣ���ǰ�ඨ���˽ӿڣ�
 �����ṩ��һЩ�Ѿ�ʵ�ֻ�������������ʹ�á�
*/
class CC_DLL PUAffector : public Particle3DAffector
{
    friend class PUParticleSystem3D;
public:
    /**
        The AffectSpecialisation enumeration is used to specialise the affector even more. This enumeration 
        isn't used by all affectors; in some cases it isn't even applicable.
    */
    enum AffectSpecialisation
    {
        AFSP_DEFAULT,
        AFSP_TTL_INCREASE,
        AFSP_TTL_DECREASE
    };
    
    /**
    * @~english Perform activities when a affector is started(internal method).
    * @~chinese ��Ӱ������ʼ����ʱִ��(�ڲ�����)
    */
    virtual void notifyStart();

    /**
    * @~english Perform activities when a affector is stopped(internal method).
    * @~chinese ��Ӱ����ֹͣ����ʱִ��(�ڲ�����)
    */
    virtual void notifyStop();

    /**
    * @~english Perform activities when a affector is paused(internal method).
    * @~chinese ��Ӱ������ͣ����ʱִ��(�ڲ�����)
    */
    virtual void notifyPause();

    /**
    * @~english Perform activities when a affector is resumed(internal method).
    * @~chinese ��Ӱ�����ָ�����ʱִ��(�ڲ�����)
    */
    virtual void notifyResume();

    /**
    * @~english Notify that the affector is rescaled(internal method).
    * @~chinese ��Ӱ������Ҫ����ʱִ��(�ڲ�����)
    */
    virtual void notifyRescaled(const Vec3& scale);

    /**
    * @~english The function is automatically called during initialisation (prepare) activities of a ParticleSystem(internal method).
    * @~chinese ��һ������ϵͳ��ʼ��ʱ�Զ�ִ��(�ڲ�����)
    */
    virtual void prepare();

    /**
    * @~english The function is automatically called when a ParticleSystem is expired(internal method).
    * @~chinese ��һ������ϵͳʧЧʱ�Զ�ִ��(�ڲ�����)
    */
    virtual void unPrepare();

    /**
    * @~english This function is called before the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese ������ϵͳ����ѭ�����ӱ���ǰִ��(�ڲ�����)
    * @param deltaTime   @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    */
    virtual void preUpdateAffector(float deltaTime);

    /**
    * @~english This function is called when the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese ������ϵͳ����ѭ�����ӱ���ʱִ��(�ڲ�����)
    * @param particle   @~english The current traversed particle. @~chinese ��ǰ�����������ӡ�
    * @param delta   @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    */
    virtual void updatePUAffector(PUParticle3D* particle, float delta);

    /**
    * @~english This function is called after the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese ������ϵͳ����ѭ�����ӱ�����ִ��(�ڲ�����)
    * @param deltaTime   @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    */
    virtual void postUpdateAffector(float deltaTime);

    /**
    * @~english This function is called when the first particle in the update-loop is processed(internal method).
    * @~chinese ���ӱ���ʱ��һ������ִ��(�ڲ�����)
    * @param particle   @~english The current traversed particle. @~chinese ��ǰ�����������ӡ�
    * @param deltaTime   @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    */
    virtual void firstParticleUpdate(PUParticle3D *particle, float deltaTime);

    /**
    * @~english Initialise a newly emitted particle(internal method).
    * @~chinese ��ʼ��һ�������������(�ڲ�����)
    * @param particle   @~english Particle pointer to a particle to initialise. @~chinese ��Ҫ��ʼ�����ӵ�ָ�롣
    */
    virtual void initParticleForEmission(PUParticle3D* particle);

    /**
    * @~english Process a particle(internal method).
    * @~chinese ����һ������(�ڲ�����)
    * @param particle   @~english The particle to be processed. @~chinese Ҫ����������ӡ�
    * @param delta   @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    * @param firstParticle   @~english Is the first particle. @~chinese �Ƿ��ǵ�һ�����ӡ�
    */
    void process(PUParticle3D* particle, float delta, bool firstParticle);

    /**
    * @~english Set position of affector.
    * @~chinese ����Ӱ������λ��
    * @param pos   @~english The position in local coordinate system. @~chinese �ֲ�����ϵ�µ�λ�á�
    */
    void setLocalPosition(const Vec3 &pos) { _position = pos; };

    /**
    * @~english Get position of affector.
    * @~chinese ��ȡӰ������λ��
    * @return   @~english The position in local coordinate system. @~chinese �ֲ�����ϵ�µ�λ�á�
    */
    const Vec3 getLocalPosition() const { return _position; };

    /**
    * @~english Set the mass of affector.
    * @~chinese ����Ӱ����������
    * @param mass      @~english The mass of affector. @~chinese Ӱ������������
    */
    void setMass(float mass);

    /**
    * @~english Get the mass of affector.
    * @~chinese ��ȡӰ����������
    * @return      @~english The mass of affector. @~chinese Ӱ������������
    */
    float getMass() const;

    /**
    * @~english Calculate the world position of the affector.
    * @~chinese ����Ӱ����������λ��
    * @return      @~english The position in world coordinate system. @~chinese Ӱ��������������ϵ�µ�λ�á�
    */
    const Vec3& getDerivedPosition();

    /**
    * @~english Get the AffectSpecialisation enumeration��isn't used by all affectors.
    * @~chinese ��ȡAffectSpecialisation��ö��ֵ��������Ӱ������ʹ�á�
    * @return      @~english The enumeration. @~chinese ö������
    */
    const AffectSpecialisation& getAffectSpecialisation(void) const {return _affectSpecialisation;};

    /**
    * @~english Set the AffectSpecialisation enumeration.
    * @~chinese ����AffectSpecialisation��ö��ֵ��
    * @param affectSpecialisation      @~english The enumeration. @~chinese ö������
    */
    void setAffectSpecialisation(const AffectSpecialisation& affectSpecialisation) {_affectSpecialisation = affectSpecialisation;};

    /**
    * @~english Get the type of affector.
    * @~chinese ��ȡӰ�������͡�
    * @return      @~english The type. @~chinese ���͡�
    */
    const std::string& getAffectorType(void) const {return _affectorType;};

    /**
    * @~english Set the type of affector.
    * @~chinese ����Ӱ�������͡�
    * @param affectorType      @~english The type. @~chinese ���͡�
    */
    void setAffectorType(const std::string& affectorType) {_affectorType = affectorType;};

    /**
    * @~english Add a emitter name that excludes Particles emitted by this emitter from being affected��
    * @~chinese ���һ�����������ƣ�Ӱ��������Ӱ��÷�������������ӡ�
    * @param emitterName      @~english The name of emitter. @~chinese ���������ơ�
    */
    void addEmitterToExclude(const std::string& emitterName);

    /**
    * @~english Remove a emitter name that excludes particles emitted by this emitter.
    * @~chinese �Ƴ�һ�����������ƣ�Ӱ��������Ӱ��÷�������������ӡ�
    * @param emitterName      @~english The name of emitter. @~chinese ���������ơ�
    */
    void removeEmitterToExclude(const std::string& emitterName);

    /**
    * @~english Get the name of affector
    * @~chinese ��ȡӰ���������ơ�
    * @return      @~english The name of affector. @~chinese Ӱ�������ơ�
    */
    const std::string& getName(void) const {return _name;};

    /**
    * @~english Set the name of affector
    * @~chinese ����Ӱ���������ơ�
    * @param name      @~english The name of affector. @~chinese Ӱ�������ơ�
    */
    void setName(const std::string& name) {_name = name;};

    /**
    * @~english Copy one affector's attributes to another's(internal method).
    * @~chinese ����һ��Ӱ���������Ե�����һ��(�ڲ�����)��
    * @param affector @~english The affector need be copied. @~chinese �������Ե�Ӱ������
    */
    virtual void copyAttributesTo (PUAffector* affector);

CC_CONSTRUCTOR_ACCESS:
    PUAffector();
    virtual ~PUAffector();

protected:

    float calculateAffectSpecialisationFactor (const PUParticle3D* particle);
    
protected:

    Vec3 _position; ///< Although the scale is on a Particle System level, the affector can also be scaled.

    Vec3 _affectorScale; ///< affector scale
    Vec3 _derivedPosition; ///< Because the public attribute position is sometimes used for both localspace and worldspace position, the _derivedPosition attribute is introduced.

    AffectSpecialisation _affectSpecialisation;///< The _affectSpecialisation is used to specialise the affector.

    std::string _affectorType;///< Type of the affector

    std::vector<std::string> _excludedEmitters; //< Excluded emitter list

    std::string _name;///< Name of the affector (optional)

    float _mass;///< The mass of affector
};

// end of _3d group
/// @}

NS_CC_END

#endif
