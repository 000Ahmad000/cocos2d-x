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

#ifndef __CC_PARTICLE_3D_RENDER_H__
#define __CC_PARTICLE_3D_RENDER_H__

#include <vector>

#include "renderer/CCRenderState.h"
#include "base/CCRef.h"
#include "math/CCMath.h"


NS_CC_BEGIN

class ParticleSystem3D;
class Renderer;
class MeshCommand;
class Sprite3D;
class GLProgramState;
class IndexBuffer;
class VertexBuffer;
class Texture2D;

/**
* @addtogroup _3d
* @{
*/

/** @class Particle3DRender
*@brief @~english Particle3DRender is a base class, define interfaces.
 Specific implementation decisions by different renderers.
 Renderer is mainly determined how particles rendered, such as billboard rendering, model rendering, etc.
 One particle system must have a renderer.

 @~chinese Particle3DRender ����Ⱦ���Ļ��࣬������Ⱦ�����нӿڡ�
 �����ʵ���ɲ�ͬ����Ⱦ�����Ͷ��塣
 ��Ⱦ����Ҫ�Ǿ���������α���Ⱦ�����繫�����Ⱦ��ģ����Ⱦ��
 ����ϵͳ����Ҫ����Ⱦ����
*/
class CC_DLL Particle3DRender : public Ref
{
    friend class ParticleSystem3D;
public:

    /**
    * @~english Render particles(internal method).
    * @~chinese ��Ⱦ����(�ڲ�����)
    * @param renderer   @~english The pointer of cocos renderer. @~chinese cocos��Ⱦ����ָ�롣
    * @param transform   @~english The model-view matrix. @~chinese ģ����ͼ�任����
    * @param particleSystem   @~english The pointer of particle system. @~chinese ����ϵͳ��ָ�롣
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) = 0;

    /**
    * @~english Perform activities when a Renderer is started(internal method).
    * @~chinese ��Ⱦ����ʼʱִ�еĻ(�ڲ�����)
    */
    virtual void notifyStart();

    /**
    * @~english Perform activities when a Renderer is stopped(internal method).
    * @~chinese ��Ⱦ��ֹͣʱִ�еĻ(�ڲ�����)
    */
    virtual void notifyStop();

    /**
    * @~english Notify that the Particle System is rescaled(internal method).
    * @~chinese ����ϵͳ�����ź�ִ�еĻص�(�ڲ�����)
    */
    virtual void notifyRescaled(const Vec3& scale);
    
    /**
    * @~english Set the render visible or invisible.
    * @~chinese ������Ⱦ�Ƿ�ɼ���
    * @param isVisible @~english Whether the render is visible. @~chinese ��Ⱦ�Ƿ�ɼ���
    */
    void setVisible(bool isVisible) { _isVisible = isVisible; }
    

    /**
    * @~english Checks the render visible.
    * @~chinese �����Ⱦ�Ƿ�ɼ���
    * @return @~english Whether the render is visible. @~chinese ��Ⱦ�Ƿ�ɼ���
    */
    bool isVisible() const { return _isVisible; }

    /**
    * @~english Set the depth test enable or disable, default is enabled.
    * @~chinese ������Ȳ��Կ�����Ĭ�Ͽ�����
    * @param isDepthTest @~english Whether the depth test enabled. @~chinese ��Ȳ����Ƿ�����
    * @see glEnable(GL_DEPTH_TEST) and glDisable(GL_DEPTH_TEST);
    */
    void setDepthTest(bool isDepthTest);

    /**
    * @~english Set the depth write enable or disable, default is disable.
    * @~chinese �������д������Ĭ�Ϲرա�
    * @param isDepthWrite @~english Whether the depth write enabled. @~chinese ���д�Ƿ�����
    */
    void setDepthWrite(bool isDepthWrite);

    /**
    * @~english Set the blend function.
    * @~chinese ����͸���Ļ�Ϸ��̡�
    * @param blendFunc   @~english The parameter of blend. @~chinese ��ϲ�����
    * @see glBlendFunc(GLenum sfactor,GLenum dfactor);
    */
    void setBlendFunc(const BlendFunc& blendFunc);

    /**
    * @~english Copy one renderer's attributes to another's(internal method).
    * @~chinese ����һ����Ⱦ�������Ե�����һ��(�ڲ�����)��
    * @param render @~english the renderer which need be copied. @~chinese �������Ե���Ⱦ����
    */
    void copyAttributesTo (Particle3DRender *render);

CC_CONSTRUCTOR_ACCESS:
    Particle3DRender();
    virtual ~Particle3DRender();
    
protected:
    ParticleSystem3D *_particleSystem;
    RenderState::StateBlock* _stateBlock;  ///< render state
    bool  _isVisible;
    Vec3 _rendererScale;
    bool _depthTest;
    bool _depthWrite;
};


/** @class Particle3DQuadRender
*@brief @~english Particle3DQuadRender inherit from Particle3DRender, implement billboard rendering.
 @~chinese Particle3DQuadRender �̳���Particle3DRender��ʵ�����ӵ�billboard��Ⱦ��
*/
class CC_DLL Particle3DQuadRender : public Particle3DRender
{
public:

    /**
    * @~english Create a new billboard renderer.
    * @~chinese ����һ���µĹ������Ⱦ����
    * @param texFile @~english The texture of particles. @~chinese ����ʹ�õ�����
    */
    static Particle3DQuadRender* create(const std::string& texFile = "");
    
    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

CC_CONSTRUCTOR_ACCESS:
    Particle3DQuadRender();
    virtual ~Particle3DQuadRender();

protected:

    bool initQuadRender(const std::string& texFile);
    
protected:
    MeshCommand*           _meshCommand; ///< render command
    Texture2D*             _texture; ///< the texture of particles
    GLProgramState*        _glProgramState; ///< OpenGL Program State
    IndexBuffer*           _indexBuffer; ///< index buffer
    VertexBuffer*          _vertexBuffer; ///<  vertex buffer
    
    struct posuvcolor
    {
        Vec3 position;
        Vec2 uv;
        Vec4 color;
    };

    std::vector<posuvcolor> _posuvcolors;   ///< vertex data
    std::vector<unsigned short> _indexData; ///< index data
};

/** @class Particle3DModelRender
*@brief @~english Particle3DModelRender inherit from Particle3DRender, implement model rendering.
@~chinese Particle3DModelRender �̳���Particle3DRender��ʵ�����ӵ�ģ����Ⱦ��
*/
class CC_DLL Particle3DModelRender : public Particle3DRender
{
public:

    /**
    * @~english Create a new model renderer.
    * @~chinese ����һ���µ�ģ����Ⱦ����
    * @param modelFile @~english The model of particles. @~chinese ����ʹ�õ�ģ�͡�
    * @param texFile @~english The texture of particles. @~chinese ����ʹ�õ�����
    */
    static Particle3DModelRender* create(const std::string& modelFile, const std::string &texFile = "");

    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;
    
CC_CONSTRUCTOR_ACCESS:
    Particle3DModelRender();
    virtual ~Particle3DModelRender();
    
protected:
    std::vector<Sprite3D *> _spriteList; ///< model list
    std::string _modelFile;///< model file path
    std::string _texFile;///< texture file path
    Vec3 _spriteSize;///< model size
};

// end of _3d group
/// @}

NS_CC_END

#endif
