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

#ifndef __CC_PARTICLE_SYSTEM_3D_H__
#define __CC_PARTICLE_SYSTEM_3D_H__

#include "2d/CCNode.h"
#include "math/CCMath.h"
#include <vector>
#include <map>
#include <list>

NS_CC_BEGIN

class Particle3DEmitter;
class Particle3DAffector;
class Particle3DRender;

/**
* @addtogroup _3d
* @{
*/

/** @struct Particle3D
*@brief @~english Particle3D is a container of particle Properties.
 @~chinese Particle3D ���������Ե�����
*/
struct CC_DLL Particle3D
{
    Particle3D();
    virtual ~Particle3D();

    Vec3 position; ///< position
    Quaternion orientation;///<  Orientation of the particle
    Vec4 color;  ///< particle color
    Vec2 lb_uv; ///< left bottom uv
    Vec2 rt_uv; ///< right top uv
    float width;///<Own width
    float height;///<Own height
    float depth;///<Own depth
    
    std::map<std::string, void*> userDefs; ///<user defined property
};

/** @class DataPool 
*@brief @~english DataPool is a data pool, used for recycling data.
 @~chinese DataPool �����ݳأ��������ݵ������á�
*/
template<typename T>
class CC_DLL DataPool
{
public:
    typedef typename std::list<T*> PoolList;
    typedef typename std::list<T*>::iterator PoolIterator;

    DataPool(){};
    ~DataPool(){};

    /**
    * @~english Allocates a data from unallocated pool.
    * @~chinese ��δ�������ȡ��һ������
    * @return @~english A allocated data. @~chinese һ���ѷ�������ݡ�
    */
    T* createData(){
        if (_locked.empty()) return nullptr;
        T* p = _locked.front();
        //_released.push_back(p);
        //_locked.erase(_locked.begin());
        _released.splice(_released.end(), _locked, _locked.begin());
        return p;
    };

    /**
    * @~english Push current data into unallocated pool.
    * @~chinese �ѵ�ǰ�����ݷ���δ����ء�
    */
    void lockLatestData(){
        _locked.push_back(*_releasedIter);
        _releasedIter = _released.erase(_releasedIter);
        if (_releasedIter != _released.begin() && _releasedIter != _released.end())
        {
            --_releasedIter;
        }
    };

    /**
    * @~english Push the specified data into unallocated pool.
    * @~chinese ��ָ�������ݷ���δ����ء�
    * @param data   @~english The pointer of data. @~chinese ���ݵ�ָ�롣
    */
    void lockData(T *data){
        PoolIterator tempIter = _releasedIter;
        T *ptr = getFirst();
        while (ptr)
        {
            if (ptr == data) break;
            ptr = getNext();
        }
        if (ptr)
            lockLatestData();
        _releasedIter = tempIter;
    }

    /**
    * @~english Push all allocated datas into unallocated pool.
    * @~chinese ���ѷ�����е��������ݷ���δ������С�
    */
    void lockAllDatas(){
        _locked.splice(_locked.end(), _released);
        //_locked.insert(_locked.end(), _released.begin(), _released.end());
        //_released.clear();
        _releasedIter = _released.begin();
    };

    /**
    * @~english Get the first data of allocated pool.
    * @~chinese ��ȡ�ѷ�����еĵ�һ�����ݡ�
    * @return @~english The pointer of data. @~chinese ���ݵ�ָ�롣
    */
    T* getFirst(){
        _releasedIter = _released.begin();
        if (_releasedIter == _released.end()) return nullptr;
        return *_releasedIter;
    };

    /**
    * @~english Get the next data of allocated pool.
    * @~chinese ��ȡ�ѷ�����е���һ�����ݡ�
    * @return @~english The pointer of data. @~chinese ���ݵ�ָ�롣
    */
    T* getNext(){
        if (_releasedIter == _released.end()) return nullptr;
        ++_releasedIter;
        if (_releasedIter == _released.end()) return nullptr;
        return *_releasedIter;
    };

    /**
    * @~english Get the allocated pool.
    * @~chinese ��ȡ�ѷ���ء�
    * @return @~english The allocated pool. @~chinese �ѷ���ء�
    */
    const PoolList& getActiveDataList() const { return _released; };

    /**
    * @~english Get the unallocated pool.
    * @~chinese ��ȡδ����ء�
    * @return @~english The unallocated pool. @~chinese δ����ء�
    */
    const PoolList& getUnActiveDataList() const { return _locked; };

    /**
    * @~english add a new data into unallocated pool.
    * @~chinese ���һ�������ݵ�δ������С�
    */
    void addData(T* data){
        _locked.push_back(data); 
    };

    /**
    * @~english To determine whether the allocated pool is empty.
    * @~chinese �ж��ѷ�����Ƿ�Ϊ�ա�
    */
    bool empty() const { return _released.empty(); };

    /**
    * @~english Remove all datas.
    * @~chinese �Ƴ����е����ݡ�
    */
    void removeAllDatas(){
        lockAllDatas();
        for (auto iter : _locked){
            delete iter;
        }
        _locked.clear();
    };

private:

    PoolIterator _releasedIter;///< the iterater of allocated pool
    PoolList _released;///< allocated pool
    PoolList _locked;///< unallocated pool
};

typedef DataPool<Particle3D> ParticlePool;

/** @class ParticleSystem3D
*@brief @~english ParticleSystem3D is a base class, define interfaces.
 Different particle systems can have their own implementation.
 a particle system consist of:
 - one Emitter(how to emit particles)
 - multiple affector(how to affect particles)
 - one renderer(how to render particles)

 @~chinese ParticleSystem3D ��3D����ϵͳ�Ļ��࣬������3D����ϵͳ����ĸ��ֽӿڡ�
 �����ʵ���ɲ�ͬ������ϵͳ������
 һ������ϵͳ��ɣ�
 - һ��������(��η�������)
 - ���Ӱ����(���Ӱ������)
 - һ����Ⱦ��(�����Ⱦ����)
*/
class CC_DLL ParticleSystem3D : public Node, public BlendProtocol
{
public:

    enum class State
    {
        STOP,
        RUNNING,
        PAUSE,
    };
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see node update(float delta);
    */
    virtual void update(float delta) override;
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see node draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    /**
    * @~english Set the blend function.
    * @~chinese ����͸���Ļ�Ϸ��̡�
    * @param blendFunc   @~english The parameter of blend. @~chinese ��ϲ�����
    * @see glBlendFunc(GLenum sfactor,GLenum dfactor);
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    
    /**
    * @~english Get the blend function.
    * @~chinese ��ȡ͸���Ļ�Ϸ��̡�
    * @return @~english The parameter of blend. @~chinese ��ϲ�����
    */
    virtual const BlendFunc &getBlendFunc() const override;
    
    /**
    * @~english Start particle system simulation.
    * @~chinese ��ʼ����ϵͳģ�⡣
    */
    virtual void startParticleSystem();
    
    /**
    * @~english Stop particle system simulation.
    * @~chinese ֹͣ����ϵͳģ�⡣
    */
    virtual void stopParticleSystem();
    
    /**
    * @~english Pause particle system simulation.
    * @~chinese ��ͣ����ϵͳģ�⡣
    */
    virtual void pauseParticleSystem();
    
    /**
    * @~english Resume particle system simulation.
    * @~chinese �ָ�����ϵͳģ�⡣
    */
    virtual void resumeParticleSystem();
    
    /**
    * @~english Set Emitter.
    * @~chinese ���÷�������
    * @param emitter   @~english The pointer of emitter. @~chinese ������ָ�롣
    */
    void setEmitter(Particle3DEmitter* emitter);

    /**
    * @~english Set Render.
    * @~chinese ������Ⱦ����
    * @param render   @~english The pointer of render. @~chinese ��Ⱦ��ָ�롣
    */
    void setRender(Particle3DRender* render);

    /**
    * @~english Add one affector.
    * @~chinese ���һ��Ӱ������
    * @param affector   @~english The pointer of affector. @~chinese Ӱ����ָ�롣
    */
    void addAffector(Particle3DAffector* affector);
    
    /**
    * @~english Remove one affector.
    * @~chinese �Ƴ�һ��Ӱ������
    * @param index   @~english The index of affector. @~chinese Ӱ�����������š�
    */
    void removeAffector(int index);
    
    /**
    * @~english Remove all affectors.
    * @~chinese �Ƴ����е�Ӱ������
    */
    void removeAllAffector();

    /**
    * @~english Get the quota of particle.
    * @~chinese ��ȡ�ɷ���������������ޡ�
    * @return @~english The quota. @~chinese ����ֵ��
    */
    unsigned int getParticleQuota() const;

    /**
    * @~english Set particle quota.
    * @~chinese ���ÿɷ�������������ޡ�
    * @param quota   @~english The quota. @~chinese ����ֵ��
    */
    void setParticleQuota(unsigned int quota);
    
    /**
    * @~english Get one affector.
    * @~chinese ��ȡ��������
    * @return @~english The pointer of affector. @~chinese ������ָ�롣
    */
    Particle3DAffector* getAffector(int index);
    
    /**
    * @~english Get particle pool.
    * @~chinese ��ȡ���ӳء�
    * @return @~english The particle pool. @~chinese ���ӳء�
    */
    const ParticlePool& getParticlePool()
    {
        return  _particlePool;
    }
    
    /**
    * @~english Get the number of alive particles .
    * @~chinese ��ȡ��������������
    * @return @~english The number of alive particles. @~chinese ��������������
    */
    virtual int getAliveParticleCount() const
    {
        return 0;
    }
    
    /**
    * @~english Get the state of particle system(running, paused, stopped).
    * @~chinese ��ȡ��ǰ����ϵͳ��״̬(���С���ͣ��ֹͣ)��
    * @return @~english The state. @~chinese ��ǰ״̬��
    */
    State getState() const { return _state; }

    /**
    * @~english Checks whether the particle using local coordinate.
    * @~chinese �ж��Ƿ������Ƿ���þֲ�����ϵ��
    * @return @~english Whether the particle using local coordinate. @~chinese �����Ƿ���þֲ�����ϵ��
    */
    bool isKeepLocal(void) const { return _keepLocal; }

    /**
    * @~english Set the particle using local coordinate or world coordinate.
    * @~chinese �������Ӳ��þֲ�����ϵ��ȫ������ϵ��
    * @return @~english Whether the particle using local coordinate. @~chinese �����Ƿ���þֲ�����ϵ��
    */
    void setKeepLocal(bool keepLocal);

    /**
    * @~english Set the particle System enable or disable.
    * @~chinese ��������ϵͳ���û򲻿��á�
    * @param enabled @~english Whether the particle system enabled. @~chinese ����ϵͳ�Ƿ���á�
    */
    void setEnabled (bool enabled);
    
    /**
    * @~english Get the particle System enabled.
    * @~chinese ��ȡ����ϵͳ�Ƿ���á�
    * @return @~english Whether the particle system enabled. @~chinese ����ϵͳ�Ƿ���á�
    */
    bool isEnabled(void) const { return _isEnabled; }

CC_CONSTRUCTOR_ACCESS:
    ParticleSystem3D();
    virtual ~ParticleSystem3D();
    
protected:
    
    State                            _state; ///< current state
    Particle3DEmitter*               _emitter; ///< the emitter
    std::vector<Particle3DAffector*> _affectors; ///< the list of affector
    Particle3DRender*                _render; ///< the renderer
    
    //particles
    ParticlePool                     _particlePool; ///< particle pool
    int                              _aliveParticlesCnt; ///< the number of alive particles
    unsigned int                     _particleQuota; ///< the quota of particle
    
    BlendFunc                        _blend; ///< the blend function

    bool _keepLocal; ///< use local coordinate
    bool _isEnabled;
};

// end of _3d group
/// @}

NS_CC_END

#endif
