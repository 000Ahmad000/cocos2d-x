/****************************************************************************
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

#ifndef __CC_PARTICLE_3D_AFFECTOR_H__
#define __CC_PARTICLE_3D_AFFECTOR_H__

#include "base/CCRef.h"
#include <vector>

NS_CC_BEGIN

class ParticleSystem3D;
struct Particle3D;

/**
* @addtogroup _3d
* @{
*/

/** @class Particle3DAffector
*@brief @~english Particle3DAffector is a base class, define interfaces.
 Specific implementation decisions by different affectors.
 Affector is mainly bound particles behavior after launch, such as acceleration, rotation, etc.
 One particle system works well without affector.

 @~chinese Particle3DAffector ��Ӱ�����Ļ��࣬����Ӱ�������нӿڡ�
 �����ʵ���ɲ�ͬ��Ӱ�������Ͷ��塣
 Ӱ������Ҫ��Լ�������ڷ�������Ϊ��������١���ת�ȡ�
 ����ϵͳ����û��Ӱ������
*/
class CC_DLL Particle3DAffector : public Ref
{
    friend class ParticleSystem3D;
public:
    
    /**
    * @~english Update affector(internal method).
    * @~chinese ����Ӱ����(�ڲ�����)
    * @param particle   @~english The current particle. @~chinese ��ǰ�����ӡ�
    * @param deltaTime   @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    */
    virtual void updateAffector(Particle3D* particle, float deltaTime);
    
    /**
    * @~english Set the affector enable or disable.
    * @~chinese ����Ӱ�������û򲻿��á�
    * @param enabled @~english Whether the affector enabled. @~chinese Ӱ�����Ƿ���á�
    */
    void setEnabled (bool enabled) { _isEnabled = enabled; }
    
    /**
    * @~english Get the affector enabled.
    * @~chinese ��ȡӰ�����Ƿ���á�
    * @return @~english Whether the affector enabled. @~chinese Ӱ�����Ƿ���á�
    */
    bool isEnabled(void) const { return _isEnabled; }

CC_CONSTRUCTOR_ACCESS:
    Particle3DAffector();
    virtual ~Particle3DAffector();
    
protected:
    ParticleSystem3D* _particleSystem;
    bool _isEnabled;
};

// end of _3d group
/// @}

NS_CC_END

#endif
