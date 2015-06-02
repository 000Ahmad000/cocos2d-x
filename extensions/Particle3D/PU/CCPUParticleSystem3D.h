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

#ifndef __CC_PU_PARTICLE_SYSTEM_3D_H__
#define __CC_PU_PARTICLE_SYSTEM_3D_H__

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticleSystem3D.h"
#include <vector>
#include <map>

NS_CC_BEGIN

class PUListener;
class PUObserver;
class PUBehaviour;
class PUEmitter;
class PUAffector;
class Particle3DRender;

/**
* @addtogroup _3d
* @{
*/

enum PUComponentType
{
    CT_PARTICLE,
    CT_SYSTEM,
    CT_TECHNIQUE,
    CT_EMITTER,
    CT_AFFECTOR,
    CT_OBSERVER
};

/** @struct PUParticle3D
*@brief @~english PUParticle3D inherit from Particle3D, includes all properties of PU particles.
 @~chinese PUParticle3D�̳���Particle3D������PU���ӵ��������ԡ�
*/
struct CC_DLL PUParticle3D : public Particle3D
{
    /**
    @property
    @static
    @~english Default time to alive
    @~chinese ����Ĭ�ϵ�����ʱ��
    */
    static float DEFAULT_TTL;

    /**
    @property
    @static
    @~english Default mass
    @~chinese ����Ĭ�ϵ�����
    */
    static float DEFAULT_MASS;

    PUParticle3D();
    virtual ~PUParticle3D();

    typedef std::vector<PUBehaviour*> ParticleBehaviourList;

    enum ParticleType
    {
        PT_VISUAL,
        PT_TECHNIQUE,
        PT_EMITTER,
        PT_AFFECTOR,
        PT_SYSTEM,
    };

        /** Enumeration which lists a number of reserved event flags. Although custom flags can be used to
        indicate that a certain condition occurs, the first number of flags may not be used as custom flags.
    */
    enum ReservedParticleEventFlags
    {
        PEF_EXPIRED = 1<<0,
        PEF_EMITTED = 1<<1,
        PEF_COLLIDED = 1<<2
    };

    Ref *particleEntityPtr;
    PUEmitter* parentEmitter;

    Ref *visualData;

    ParticleType particleType;
    ///< Values that are assigned as soon as the particle is emitted (non-transformed)
    ///< Vec3 positionInWorld;
    Vec3 originalPosition;
    Vec3 latestPosition;
    ///< Direction (and speed)
    Vec3 direction;
    Vec3 originalDirection;
    float originalDirectionLength; ///< Length of the direction that has been set
    float originalVelocity;
    float originalScaledDirectionLength; ///< Length of the direction after multiplication with the velocity

    /** The rotation axis is used in combination with orientation. Because the rotation axis is part
        of the particle itself, it can be changed independently. */
    Vec3 rotationAxis;
    /** Current and original colour */

    Vec4 originalColor;

    /** The zRotationSpeed is used in combination with zRotation and defines tha actual rotationspeed
        in 2D. */
    float zRotationSpeed; //radian

    //Quaternion orientationInWorld;
    /*@remarks
        The orientation of the particle is only visible if the Particle Renderer - such as the Box renderer - 
        supports orientation.
    */
    Quaternion originalOrientation;


    /** The rotation is used in combination with orientation. Because the rotation speed is part
        of the particle itself, it can be changed independently. */
    float rotationSpeed;

    /** Radius of the particle, to be used for inter-particle collision and such.
    */
    float radius;

    ParticleBehaviourList behaviours;
    void copyBehaviours(const ParticleBehaviourList &list);

    float calculateVelocity() const;

    void setOwnDimensions(float newWidth, float newHeight, float newDepth);
    void calculateBoundingSphereRadius();

    void initForEmission();
    void initForExpiration(float timeElapsed);
    void process(float timeElapsed);

    /** Does this particle have it's own dimensions? */
    bool ownDimensions;

    /** Sets the event flags.
    */
    inline void setEventFlags(unsigned int flags) {eventFlags = flags;}

    /** As setEventFlags, except the flags passed as parameters are appended to the
        existing flags on this object.
    */
    inline void addEventFlags(unsigned int flags) {eventFlags |= flags;}
            
    /** The flags passed as parameters are removed from the existing flags.
    */
    inline void removeEventFlags(unsigned int flags) {eventFlags &= ~flags;}
        
    /** Return the event flags.
    */
    inline unsigned int getEventFlags() const {return eventFlags;}

    /** Determines whether it has certain flags set.
    */
    inline bool hasEventFlags(unsigned int flags) const {return (eventFlags & flags) != 0;}

    unsigned int eventFlags;

    bool isFreezed(void) const
    {
        return freezed;
    }
    //-----------------------------------------------------------------------
    void setFreezed(bool fzd)
    {
        freezed = fzd;
    }
    bool freezed;

    ///< Time to live, number of seconds left of particles natural life
    float timeToLive;

    ///< Total Time to live, number of seconds of particles natural life
    float totalTimeToLive;

    ///< The timeFraction is calculated every update. It is used in other observers, affectors, etc. so it is
    ///< better to calculate it once at the Particle level.
    float timeFraction;

    float mass;///< mass of a particle

    /** Animation attributes
    */
    float textureAnimationTimeStep;
    float textureAnimationTimeStepCount;
    unsigned short textureCoordsCurrent;
    bool textureAnimationDirectionUp;

    float depthInView;///< depth in camera view
    float zRotation; ///< zRotation is used to rotate the particle in 2D (around the Z-axis)   (radian)
    //float widthInWorld;
    //float heightInWorld;
    //float depthInWorld;
    
};

/** @class PUParticleSystem3D
*@brief @~english PUParticleSystem3D inherit from ParticleSystem3D, the class of pu particle system.
 The ParticleSystem3D,the parent of PUParticleSystem3D, is derived from Node, so one particle system can contain multiple particle systems,
 By addChild way to mount a PUParticleSystem3D under another PUParticleSystem3D.
 Each particle system can be defined emitter,affector,renderer,etc. 
 PUParticleSystem3D provides three ways to be created:
 - Directly create an empty PUParticleSystem3D, manually add emitter, affector, etc.(useless)
 - Create PUParticleSystem3D with pu file path, pu material file will be automatically searched.(not recommended)
 - Create PUParticleSystem3D with pu file path and pu material file path.(recommended)
 The resources(textures,scripts,materials) used by pu particle system must use the following file structure and name definition(Can not be modified):
 - Folder - textures
 ----------- scripts
 ----------- materials

 @~chinese PUParticleSystem3D�̳���ParticleSystem3D����pu������ϵͳ�ࡣ
 PUParticleSystem3D�ĸ���ParticleSystem3D�Ǵ�Node��������������һ������ϵͳ���԰����������ϵͳ��
 ͨ��addChild�ķ�ʽ��һ��PUParticleSystem3D���ص���һ��PUParticleSystem3D�¡�
 ÿ������ϵͳ���ɶ��巢������Ӱ��������Ⱦ���ȵȡ�
 PUParticleSystem3D�ṩ�����ִ����ķ�ʽ��
 - ֱ�Ӵ���һ���յ�PUParticleSystem3D���ֶ���ӷ�������Ӱ������(������ʹ��)
 - ͨ��һ��pu�ļ�·��������PUParticleSystem3D��pu�����ļ����Զ���������������ʹ�ã�
 - ͨ��һ��pu�ļ�·����һ��pu�����ļ�·��������PUParticleSystem3D��������ʹ�ã�
 pu������ϵͳʹ�õ���Դ(����pu�ű��������ļ�)����������ļ��ṹ�����ƣ�Ŀǰ���ɸ��ģ���
 - Folder - textures
 ----------- scripts
 ----------- materials
*/
class CC_DLL PUParticleSystem3D : public ParticleSystem3D
{
public:

    typedef std::map<std::string, ParticlePool> ParticlePoolMap;

    /**
    @property
    @static
    @~english Default width of particle
    @~chinese ����Ĭ�ϵĿ��
    */
    static const float DEFAULT_WIDTH;

    /**
    @property
    @static
    @~english Default height of particle
    @~chinese ����Ĭ�ϵĸ߶�
    */
    static const float DEFAULT_HEIGHT;

    /**
    @property
    @static
    @~english Default depth of particle
    @~chinese ����Ĭ�ϵ����
    */
    static const float DEFAULT_DEPTH;

    /**
    @property
    @static
    @~english Default quota of particle
    @~chinese ����Ĭ�ϵ���������
    */
    static const unsigned int DEFAULT_PARTICLE_QUOTA;

    /**
    @property
    @static
    @~english Default quota of emitted emitter
    @~chinese ������ķ�����Ĭ�ϵ���������
    */
    static const unsigned int DEFAULT_EMITTED_EMITTER_QUOTA;

    /**
    @property
    @static
    @~english Default quota of emitted system
    @~chinese �����������ϵͳĬ�ϵ���������
    */
    static const unsigned int DEFAULT_EMITTED_SYSTEM_QUOTA;

    /**
    @property
    @static
    @~english Default maximum velocity of particle
    @~chinese ����Ĭ�ϵ�����ٶ�
    */
    static const float DEFAULT_MAX_VELOCITY;

    /**
    * @~english Create a empty particle system.
    * @~chinese ����һ���յ�����ϵͳ��
    */
    static PUParticleSystem3D* create();

    /**
    * @~english Create a particle system with pu file.
    * @~chinese ͨ��pu�ļ�����һ������ϵͳ��
    * @param filePath @~english The file path of pu. @~chinese pu�ļ�·����
    */
    static PUParticleSystem3D* create(const std::string &filePath);

    /**
    * @~english Create a particle system with pu file and pu material file.
    * @~chinese ͨ��pu�ļ��Ͳ����ļ�����һ������ϵͳ��
    * @param filePath @~english  The file path of pu. @~chinese pu�ļ�·����
    * @param materialPath @~english The file path of pu material. @~chinese pu�����ļ�·����
    */
    static PUParticleSystem3D* create(const std::string &filePath, const std::string &materialPath);
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see node draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see node update(float delta);
    */
    virtual void update(float delta) override;

    /**
    * @~english Force update system.
    * @~chinese ǿ�Ƹ�������ϵͳ��
    * @param delta @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    */
    void forceUpdate(float delta);
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see ParticleSystem3D startParticleSystem();
    */
    virtual void startParticleSystem() override;
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see ParticleSystem3D stopParticleSystem();
    */
    virtual void stopParticleSystem() override;
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see ParticleSystem3D pauseParticleSystem();
    */
    virtual void pauseParticleSystem() override;
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see ParticleSystem3D resumeParticleSystem();
    */
    virtual void resumeParticleSystem() override;

    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see ParticleSystem3D getAliveParticleCount();
    */
    virtual int getAliveParticleCount() const override;

    /**
    * @~english Get the velocity scale, used for scale all particles velocity.
    * @~chinese ��ȡ�������ʣ��������������е����ӡ�
    * @return @~english The velocity scale. @~chinese �������ʡ�
    */
    float getParticleSystemScaleVelocity() const;

    /**
    * @~english Set the velocity scale, used for scale all particles velocity.
    * @~chinese �����������ʣ��������������е����ӡ�
    * @param scaleVelocity @~english The velocity scale. @~chinese �������ʡ�
    */
    void setParticleSystemScaleVelocity(float scaleVelocity) { _particleSystemScaleVelocity = scaleVelocity; }

    /**
    * @~english Set the rotation offset(internal method).
    * If the orientation of the particle system has been changed since the last update, the passed vector is rotated accordingly.
    * @~chinese ������תƫ����(�ڲ�����)��
    * �������ϵͳ�ĳ����Դ��ϴθ��º�ı��ˣ����ݵ�����Ҳ��Ҫ��Ӧ��ת��
    * @param pos @~english The position. @~chinese λ�á�
    */
    void rotationOffset(Vec3& pos);

    /**
    * @~english Get the time elapsed since sysytem started.
    * @~chinese ��ȡ�Դ�����ϵͳ��ʼ���к����ŵ�ʱ�䡣
    * @return @~english The time. @~chinese ���ŵ�ʱ�䡣
    */
    inline float getTimeElapsedSinceStart(void) const {return _timeElapsedSinceStart;};

    /**
    * @~english Get the default width of particle.
    * @~chinese ��ȡ����Ĭ�ϵĿ�ȡ�
    * @return @~english The width of particle. @~chinese ���ӵĿ�ȡ�
    */
    const float getDefaultWidth(void) const;

    /**
    * @~english Set the default width of particle.
    * @~chinese ��������Ĭ�ϵĿ�ȡ�
    * @param width @~english The width of particle. @~chinese ���ӵĿ�ȡ�
    */
    void setDefaultWidth(const float width);

    /**
    * @~english Get the default height of particle.
    * @~chinese ��ȡ����Ĭ�ϵĸ߶ȡ�
    * @return @~english The height of particle. @~chinese ���ӵĸ߶ȡ�
    */
    const float getDefaultHeight(void) const;

    /**
    * @~english Set the default height of particle.
    * @~chinese ��������Ĭ�ϵĸ߶ȡ�
    * @param width @~english The height of particle. @~chinese ���ӵĸ߶ȡ�
    */
    void setDefaultHeight(const float height);

    /**
    * @~english Get the default depth of particle.
    * @~chinese ��ȡ����Ĭ�ϵ���ȡ�
    * @return @~english The depth of particle. @~chinese ���ӵ���ȡ�
    */
    const float getDefaultDepth(void) const;

    /**
    * @~english Set the default depth of particle.
    * @~chinese ��������Ĭ�ϵ���ȡ�
    * @param width @~english The depth of particle. @~chinese ���ӵ���ȡ�
    */
    void setDefaultDepth(const float depth);

    /**
    * @~english Get the world position of system.
    * @~chinese ��ȡ����ϵͳ��������ϵ�µ�λ�á�
    * @return @~english The world position. @~chinese ��������ϵλ�á�
    */
    Vec3 getDerivedPosition();

    /**
    * @~english Get the world rotation of system.
    * @~chinese ��ȡ����ϵͳ��������ϵ�µ���ת��
    * @return @~english The world rotation. @~chinese ��������ϵ��ת��
    */
    Quaternion getDerivedOrientation();

    /**
    * @~english Get the world scale of system.
    * @~chinese ��ȡ����ϵͳ��������ϵ�µ����š�
    * @return @~english The world scale. @~chinese ��������ϵ���š�
    */
    Vec3 getDerivedScale();

    /**
    * @~english Get the maximum velocity of particle.
    * Return the maximum velocity a particle can have, even if the velocity of the particle has been set higher (either by initialisation of the particle or by means of an affector).
    * @~chinese ��ȡ����������ʡ�
    * ���ص������ӵ�������ʣ��������ʱ���Ϊ���ߵ�ֵ��Ҳ�ᱻ��ȡ����Χ���ڡ�
    * @return @~english The maximum velocity. @~chinese ����������ʡ�
    */
    float getMaxVelocity() const;

    /**
    * @~english Set the maximum velocity of particle.
    * @~chinese �������ӵ�������ʡ�
    * @param maxVelocity @~english The maximum velocity. @~chinese ����������ʡ�
    */
    void setMaxVelocity(float maxVelocity);

    /**
    * @~english Set the using material of this system(internal method).
    * @~chinese ��������ϵͳʹ�õĲ�������(�ڲ�����)��
    * @param name @~english The name of material. @~chinese �������ơ�
    */
    void setMaterialName(const std::string &name) { _matName = name; };

    /**
    * @~english Get the using material of this system(internal method).
    * @~chinese ��ȡ����ϵͳʹ�õĲ�������(�ڲ�����)��
    * @return @~english The name of material. @~chinese �������ơ�
    */
    const std::string getMaterialName() const { return _matName; };

    /**
    * @~english Forces emission of particles.
    * The number of requested particles are the exact number that are emitted
    * @~chinese ǿ�Ʒ���ָ����Ŀ�����ӡ�
    * requestedָ����ֵ�Ƿ�����Ŀ��ȷ��ֵ��
    * @param emitter @~english Which emitter need emit particle. @~chinese ��Ҫ�������ӵķ�������
    * @param requested @~english The number of requested particles. @~chinese ���������ӵ�������
    */
    void forceEmission(PUEmitter* emitter, unsigned requested);

    /**
    * @~english Add a Emitter.
    * The pu particle system allows the use of multiple emitters
    * @~chinese ���һ����������
    * pu����ϵͳ����ʹ�ö����������
    * @param emitter @~english The pointer of emitter. @~chinese ������ָ�롣
    */
    void addEmitter(PUEmitter* emitter);

    /**
    * @~english Get the affector by name.
    * @~chinese �������ʻ�ȡӰ������
    * @return @~english The name of affector. @~chinese Ӱ�������ʡ�
    */
    PUAffector* getAffector(const std::string &name);

    /**
    * @~english Get the emitter by name.
    * @~chinese �������ʻ�ȡ��������
    * @return @~english The name of emitter. @~chinese ���������ʡ�
    */
    PUEmitter* getEmitter(const std::string &name);

    /**
    * @~english Remove all emitters.
    * @~chinese �Ƴ����еķ�������
    */
    void removeAllEmitter();

    /**
    * @~english Add a Listener(internal method).
    * Listener is mainly used to monitor particle emissions and disappearance.
    * @~chinese ���һ����������
    * ��������Ҫ�����������ӷ����������
    * @see PUListener
    * @param listener @~english The pointer of listener. @~chinese ������ָ�롣
    */
    void addListener(PUListener *listener);

    /**
    * @~english Remove a Listener(internal method).
    * @~chinese �Ƴ�һ����������
    * @param listener @~english The pointer of listener. @~chinese ������ָ�롣
    */
    void removeListener(PUListener *listener);

    /**
    * @~english Add a Emitter.
    * The pu particle system allows the use of multiple emitters
    * @~chinese ���һ����������
    * pu����ϵͳ����ʹ�ö����������
    * @param emitter @~english The pointer of emitter. @~chinese ������ָ�롣
    */
    void removeAllListener();

    /**
    * @~english Add a Observer.
    * @~chinese ���һ���۲�����
    * @see PUObserver
    * @param observer @~english The pointer of observer. @~chinese �۲���ָ�롣
    */
    void addObserver(PUObserver *observer);

    /**
    * @~english Get a Observer.
    * @~chinese ��ȡһ���۲�����
    * @see PUObserver
    * @return @~english The name of observer. @~chinese �۲������ơ�
    */
    PUObserver* getObserver(const std::string &name);

    /**
    * @~english Remove all Observers.
    * @~chinese �Ƴ����й۲�����
    */
    void removerAllObserver();

    /**
    * @~english Add a behaviour template of particle(internal method).
    * @~chinese ���һ�����ӵ���Ϊģ�塣
    * @see PUBehaviour
    * @param behaviour @~english The pointer of behaviour. @~chinese ��Ϊģ��ָ�롣
    */
    void addBehaviourTemplate(PUBehaviour *behaviour);

    /**
    * @~english Remove all behaviour templates.
    * @~chinese �Ƴ�������Ϊģ�塣
    */
    void removeAllBehaviourTemplate();

    /**
    * @~english Check this system is mark for emission.
    * @~chinese ��鵱ǰ����ϵͳ�Ƿ���Ϊ�����������䡣
    * @return @~english Whether this system is mark for emission. @~chinese ��ǰ����ϵͳ�Ƿ���Ϊ���䡣
    */
    bool isMarkedForEmission() const {return _isMarkedForEmission;};

    /**
    * @~english Mark this system for emission.
    * @~chinese ��ǵ�ǰ����ϵͳ�����������䡣
    * @param isMarked @~english Whether this system is mark for emission. @~chinese ��ǰ����ϵͳ�Ƿ���Ϊ���䡣
    */
    void setMarkedForEmission(bool isMarked) {_isMarkedForEmission = isMarked;};

    /**
    * @~english Clear all particles.
    * @~chinese ����������ӡ�
    */
    void clearAllParticles();

    /**
    * @~english Get the quota of emitted emitters .
    * @~chinese ��ȡ������ķ���������ֵ��
    * @return @~english The quota of emitted emitters. @~chinese ������ķ���������ֵ��
    */
    unsigned int getEmittedEmitterQuota() const { return _emittedEmitterQuota; };

    /**
    * @~english Set the quota of emitted emitters .
    * @~chinese ���ñ�����ķ���������ֵ��
    * @param quota @~english The quota of emitted emitters. @~chinese ������ķ���������ֵ��
    */
    void setEmittedEmitterQuota(unsigned int quota) { _emittedEmitterQuota = quota; };

    /**
    * @~english Get the quota of emitted systems .
    * @~chinese ��ȡ�����������ϵͳ����ֵ��
    * @return @~english The quota of emitted systems. @~chinese �����������ϵͳ����ֵ��
    */
    unsigned int getEmittedSystemQuota() const { return _emittedSystemQuota; };

    /**
    * @~english Set the quota of emitted systems .
    * @~chinese ���ñ����������ϵͳ����ֵ��
    * @param quota @~english The quota of emitted systems. @~chinese �����������ϵͳ����ֵ��
    */
    void setEmittedSystemQuota(unsigned int quota) { _emittedSystemQuota = quota; };

    /**
    * @~english Get the partent system of this system.
    * @~chinese ��ȡ��ǰ����ϵͳ�ĸ�ϵͳ��
    * @return @~english The partent system of this system. @~chinese ����ϵͳ�ĸ�ϵͳ��
    */
    PUParticleSystem3D* getParentParticleSystem()const { return _parentParticleSystem; };

    /**
    * @~english Get the emitted emitter pool.
    * @~chinese ��ȡ������ķ��������ݳء�
    * @return @~english The emitted emitter pool. @~chinese ���������ݳء�
    */
    const ParticlePoolMap& getEmittedEmitterParticlePool() const { return _emittedEmitterParticlePool; };

    /**
    * @~english Get the emitted system pool.
    * @~chinese ��ȡ�����������ϵͳ���ݳء�
    * @return @~english The emitted system pool. @~chinese ����ϵͳ���ݳء�
    */
    const ParticlePoolMap& getEmittedSystemParticlePool() const { return _emittedSystemParticlePool; };

    /**
    * @~english Calculate the real position of the particle(internal method).
    * @~chinese �������ӵ���ʵλ��(�ڲ�����)��
    * @param particle @~english Need handled particle. @~chinese ��Ҫ����������ӡ�
    */
    bool makeParticleLocal(PUParticle3D* particle);

    /**
    * @~english Calculate rotation offset(internal method).
    * @~chinese ������תƫ����(�ڲ�����)��
    */
    void calulateRotationOffset(void);

    /**
    * @~english Clone this system.
    * @~chinese ��¡��ǰ����ϵͳ��
    */
    virtual PUParticleSystem3D* clone();

    /**
    * @~english Copy one system's attributes to another's(internal method).
    * @~chinese ����һ������ϵͳ�����Ե�����һ��(�ڲ�����)��
    * @param system @~english the system which need be copied. @~chinese �������Ե�����ϵͳ��
    */
    virtual void copyAttributesTo(PUParticleSystem3D* system);

CC_CONSTRUCTOR_ACCESS:
    PUParticleSystem3D();
    virtual ~PUParticleSystem3D();

    bool initWithFilePath(const std::string &filePath);
    bool initWithFilePathAndMaterialPath (const std::string &filePath, const std::string &materialPath);

protected:

    void prepared();
    void unPrepared();
    void preUpdator(float elapsedTime);
    void updator(float elapsedTime);
    void postUpdator(float elapsedTime);
    void emitParticles(float elapsedTime);
    void executeEmitParticles(PUEmitter* emitter, unsigned requested, float elapsedTime);
    void emitParticles(ParticlePool &pool, PUEmitter* emitter, unsigned requested, float elapsedTime);
    void processParticle(ParticlePool &pool, bool &firstActiveParticle, bool &firstParticle, float elapsedTime);
    void processMotion(PUParticle3D* particle, float timeElapsed, bool firstParticle);
    void notifyRescaled(const Vec3 &scl);
    void initParticleForEmission(PUParticle3D* particle);
    void initParticleForExpiration(PUParticle3D* particle, float timeElapsed);
    void forceStopParticleSystem();
    
    inline bool isExpired(PUParticle3D* particle, float timeElapsed);

    bool initSystem(const std::string &filePath);
    static void convertToUnixStylePath(std::string &path);

protected:

    std::vector<PUEmitter*>      _emitters;
    std::vector<PUObserver *>    _observers;

    ParticlePoolMap              _emittedEmitterParticlePool;
    ParticlePoolMap              _emittedSystemParticlePool;

    unsigned int                 _emittedEmitterQuota;
    unsigned int                 _emittedSystemQuota;

    //internal
    PUParticle3D::ParticleBehaviourList _behaviourTemplates;
    std::vector<PUListener *>           _listeners;

    bool                                _prepared;
    bool                                _poolPrepared;

    float                               _particleSystemScaleVelocity;
    float                               _timeElapsedSinceStart;

    Quaternion                          _rotationOffset; ///< Rotation offset between 2 updates.

    Vec3                                _rotationCentre; ///< The rotation centre.

    float                               _defaultWidth; ///< Default width of each visual particle.

    float                               _defaultHeight; ///< Default height of each visual particle.

    float                               _defaultDepth; ///< Default depth of each visual particle.
    
    float                               _maxVelocity; ///< Attributes that limit the velocity of the particles in this technique.
    bool                                _maxVelocitySet;

    std::string                         _matName;///< material name

    bool                                _isMarkedForEmission;

    Vec3                                _latestPositionDiff;
    Vec3                                _latestPosition;///<  Keep latest position

    Quaternion                          _latestOrientation;

    PUParticleSystem3D *                _parentParticleSystem;
};

// end of _3d group
/// @}

NS_CC_END

#endif
