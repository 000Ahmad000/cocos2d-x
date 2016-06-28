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

#ifndef __CC_PU_PARTICLE_3D_FORCE_FIELD_H__
#define __CC_PU_PARTICLE_3D_FORCE_FIELD_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "CCPUNoise.h"

NS_CC_BEGIN

/** @class ForceFieldCalculationFactory
*@brief @~english Internal class, the ForceField calculation factory.
@~chinese �ڲ��࣬�������㹤���ࡣ
*/
class  PUForceFieldCalculationFactory
{
public:
    // Const
    static const Vec3 DEFAULT_WORLDSIZE;

    PUForceFieldCalculationFactory(void) : 
        _octaves(2),
        _frequency(1.0f),
        _amplitude(1.0f),
        _persistence(1.0f),
        _worldSize(DEFAULT_WORLDSIZE)
    {
    };
    virtual ~PUForceFieldCalculationFactory(void){};

    /**
    * @~english Generates the force field.
    * @~chinese ����һ��������
    * @param forceFieldSize   @~english The internal dimensions of the force field. @~chinese ������С��
    * @param octaves   @~english The octaves. @~chinese �˶ȳ���
    * @param frequency   @~english The frequency. @~chinese ����Ƶ�ʡ�
    * @param amplitude   @~english The amplitude. @~chinese ���������
    * @param persistence   @~english The persistence. @~chinese �����ԡ�
    * @param worldSize   @~english The dimensions in the real world. @~chinese ����ʵ�����еĴ�С��
    */
    virtual void generate(unsigned int forceFieldSize, 
        unsigned short octaves, 
        double frequency, 
        double amplitude, 
        double persistence, 
        const Vec3& worldSize) = 0;

    /**
    * @~english Determine the force, based on the position of a particle.
    * @~chinese ����λ����Ϣ�������������
    * @param position   @~english The position of a particle. @~chinese ������С��
    * @param force   @~english The force. @~chinese ����С��
    * @param delta   @~english The radius around the position that contributes to the calculation of the force. @~chinese ��ǰ����λ�õ��������İ뾶��
    */
    virtual void determineForce(const Vec3& position, Vec3& force, float delta) = 0;

    /** Default Getters/Setters
    */
    virtual unsigned short getOctaves(void) const;
    virtual void setOctaves(unsigned short octaves);
    virtual double getFrequency(void) const;
    virtual void setFrequency(double frequency);
    virtual double getAmplitude(void) const;
    virtual void setAmplitude(double amplitude);
    virtual double getPersistence(void) const;
    virtual void setPersistence(double persistence);
    virtual unsigned int getForceFieldSize(void) const;
    virtual void setForceFieldSize(unsigned int forceFieldSize);
    virtual Vec3 getWorldSize(void) const;
    virtual void setWorldSize(const Vec3& worldSize);

protected:
    PUNoise3D _noise3D;
    unsigned short _octaves;
    double _frequency;
    double _amplitude;
    double _persistence;
    Vec3 _mapScale;
    Vec3 _worldSize;
    Vec3 _mappedPosition;
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

/** @class PURealTimeForceFieldCalculationFactory
*@brief @~english Internal class, Factory class to calculate forces in realtime
@~chinese �ڲ��࣬ʵʱ�������㹤���ࡣ
*/
class PURealTimeForceFieldCalculationFactory : public PUForceFieldCalculationFactory
{
public:
    PURealTimeForceFieldCalculationFactory(void) : PUForceFieldCalculationFactory() {};
    virtual ~PURealTimeForceFieldCalculationFactory(void){};

    /** Override from ForceFieldCalculationFactory
    */
    virtual void generate(unsigned int forceFieldSize, 
        unsigned short octaves, 
        double frequency, 
        double amplitude, 
        double persistence, 
        const Vec3& worldSize);

    /** Override from ForceFieldCalculationFactory
    */
    virtual void determineForce(const Vec3& position, Vec3& force, float delta);
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

/** @class PUForceField
*@brief @~english Internal class, This class defines a force field to affect the particle direction. The force field is based on 3D noise. 
The force can be calculated in realtime or based on a precreated 3D force field matrix, which essentially involves one lookup. 
To speed things up, the 3d matrix can be precreated in a separate thread (optionally)
@~chinese �ڲ��࣬���ඨ����һ��Ӱ�����ӷ��������������������3D����������������ʵʱ�������Ԥ�ȴ�����3D�����任���󣬸þ�������ֻ������һ��lookup������
Ϊ�˼���ʵ�֣���3D��������ڶ������߳��н��м��㡣
*/
class PUForceField
{
    public:
        enum ForceFieldType
        {
            FF_REALTIME_CALC,
            FF_MATRIX_CALC
        };

        PUForceField();
        virtual ~PUForceField();

        /**
        * @~english Initialises the ForceField.
        * @~chinese ��ʼ��һ��������
        * @param type   @~english The type of force field. @~chinese �������͡�
        * @param position   @~english The position of force field. @~chinese ����λ�á�
        * @param forceFieldSize   @~english The internal dimensions of the force field. @~chinese ������С��
        * @param octaves   @~english The octaves. @~chinese �˶ȳ���
        * @param frequency   @~english The frequency. @~chinese ����Ƶ�ʡ�
        * @param amplitude   @~english The amplitude. @~chinese ���������
        * @param persistence   @~english The persistence. @~chinese �����ԡ�
        * @param worldSize   @~english The dimensions in the real world. @~chinese ����ʵ�����еĴ�С��
        */
        virtual void initialise(ForceFieldType type,
            const Vec3& position,
            unsigned int forceFieldSize, 
            unsigned short octaves, 
            double frequency, 
            double amplitude, 
            double persistence, 
            const Vec3& worldSize);

        /**
        * @~english Initialises the ForceField.
        * @~chinese ��ʼ��һ��������
        * @param type   @~english The type of force field. @~chinese �������͡�
        * @param forceFieldSize   @~english The internal dimensions of the force field. @~chinese ������С��
        * @param octaves   @~english The octaves. @~chinese �˶ȳ���
        * @param frequency   @~english The frequency. @~chinese ����Ƶ�ʡ�
        * @param amplitude   @~english The amplitude. @~chinese ���������
        * @param persistence   @~english The persistence. @~chinese �����ԡ�
        * @param worldSize   @~english The dimensions in the real world. @~chinese ����ʵ�����еĴ�С��
        */
        virtual void initialise(ForceFieldType type,
            unsigned int forceFieldSize, 
            unsigned short octaves, 
            double frequency, 
            double amplitude, 
            double persistence, 
            const Vec3& worldSize);

        /** Get/Set the base position of the force field */
        const Vec3& getForceFieldPositionBase(void) const;
        void setForceFieldPositionBase(const Vec3& position);

        /** Calculate the force, based on a certain position */
        void determineForce(const Vec3& position, Vec3& force, float delta);

        /** Getters/Setters
        */
        virtual unsigned short getOctaves(void) const;
        virtual void setOctaves(unsigned short octaves);
        virtual double getFrequency(void) const;
        virtual void setFrequency(double frequency);
        virtual double getAmplitude(void) const;
        virtual void setAmplitude(double amplitude);
        virtual double getPersistence(void) const;
        virtual void setPersistence(double persistence);
        virtual unsigned int getForceFieldSize(void) const;
        virtual void setForceFieldSize(unsigned int forceFieldSize);
        virtual Vec3 getWorldSize(void) const;
        virtual void setWorldSize(const Vec3& worldSize);
            
        /** Get/Set the Forcefield type
        */
        ForceFieldType getForceFieldType() const;
        void setForceFieldType(const ForceFieldType forceFieldType);

    protected:
        unsigned short _octaves;
        double _frequency;
        double _amplitude;
        double _persistence;
        Vec3 _worldSize;
        unsigned int _forceFieldSize;
        PUForceFieldCalculationFactory* _forceFieldCalculationFactory; // Internal factory that creates a certain force field type
        Vec3 _forceFieldPositionBase; // Position of the force field
        ForceFieldType _forceFieldType;

        /** Get/Set/Create ForceFieldCalculationFactory */
        PUForceFieldCalculationFactory* getForceFieldCalculationFactory() const;
        void setForceFieldCalculationFactory(PUForceFieldCalculationFactory* forceFieldCalculationFactory);
        PUForceFieldCalculationFactory* createForceFieldCalculationFactory(ForceFieldType type);
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

NS_CC_END

#endif
