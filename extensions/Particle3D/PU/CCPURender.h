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

#ifndef __CC_PU_PARTICLE_3D_RENDER_H__
#define __CC_PU_PARTICLE_3D_RENDER_H__

#include <vector>

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DRender.h"
#include "renderer/CCRenderState.h"

NS_CC_BEGIN

struct PUParticle3D;

/**
* @addtogroup _3d
* @{
*/

/** @class PURender
*@brief @~english PURender inherit from Particle3DRender, is base class of pu renderer.
Specific implementation decisions by different renderers.

@~chinese PURender �̳���Particle3DRender����pu��Ⱦ���Ļ��ࡣ
�����ʵ���ɲ�ͬ����Ⱦ�����Ͷ��塣
*/
class CC_DLL PURender : public Particle3DRender
{
public:

    /**
    * @~english The function is automatically called during initialisation (prepare) activities of a ParticleSystem(internal method).
    * @~chinese ��һ������ϵͳ��ʼ��ʱ�Զ�ִ��(�ڲ�����)��
    */
    virtual void prepare(){};

    /**
    * @~english The function is automatically called when a ParticleSystem is expired(internal method).
    * @~chinese ��һ������ϵͳʧЧʱ�Զ�ִ��(�ڲ�����)��
    */
    virtual void unPrepare(){};

    /**
    * @~english This function is called when the ParticleSystem update-loop where all particles are traversed(internal method).
    * @~chinese ������ϵͳ����ѭ�����ӱ���ʱִ��(�ڲ�����)��
    * @param particle   @~english The current traversed particle. @~chinese ��ǰ�����������ӡ�
    * @param deltaTime   @~english The delta time between two frames. @~chinese ��֮֡���ʱ������
    * @param firstParticle   @~english Is first update particle. @~chinese �Ƿ��ǵ�һ�����µ����ӡ�
    */
    virtual void updateRender(PUParticle3D *particle, float deltaTime, bool firstParticle){};

    /**
    * @~english Get render type.
    * quad,model,box,sphere,beam, or ribbon trail.
    * @~chinese ��ȡ��Ⱦ���͡�
    * �ı��Σ�ģ�ͣ����Σ����Σ������Σ���β�Ρ�
    * @return   @~english The type name. @~chinese �������ơ�
    */
    const std::string& getRenderType(void) const {return _renderType;};

    /**
    * @~english Set render type.
    * @~chinese ������Ⱦ���͡�
    * @param observerType   @~english The type name. @~chinese �������ơ�
    */
    void setRenderType(const std::string& observerType) {_renderType = observerType;};

    /**
    * @~english Clone this renderer.
    * @~chinese ������ǰ��Ⱦ����
    */
    virtual PURender* clone() = 0;

    /**
    * @~english Copy one renderer's attributes to another's(internal method).
    * @~chinese ����һ����Ⱦ�������Ե�����һ��(�ڲ�����)��
    * @param render @~english the renderer need be copied. @~chinese �������Ե���Ⱦ����
    */
    void copyAttributesTo(PURender* render);

public:

    bool autoRotate; ///< Means that the objects to render automatically rotate if the node to which the particle system is attached, rotates.

protected:

    std::string _renderType;
};

/** @class PUParticle3DEntityRender
*@brief @~english PUParticle3DEntityRender inherit from PURender, is base class of entity renderer.
entity include��
quad(billboard).
box.
sphere.

@~chinese PUParticle3DEntityRender �̳���PURender����ʵ����Ⱦ���Ļ��ࡣ
ʵ�������
�ı��Σ�����壩
����
����
*/
class CC_DLL PUParticle3DEntityRender : public PURender
{
public:

    /**
    * @~english Copy one entity renderer's attributes to another's(internal method).
    * @~chinese ����һ��ʵ����Ⱦ�������Ե�����һ��(�ڲ�����)��
    * @param render @~english the renderer need be copied. @~chinese �������Ե���Ⱦ����
    */
    void copyAttributesTo(PUParticle3DEntityRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DEntityRender();
    virtual ~PUParticle3DEntityRender();

protected:

    bool initRender(const std::string &texFile);

protected:

    struct VertexInfo
    {
        Vec3 position;
        Vec2 uv;
        Vec4 color;
    };
    MeshCommand* _meshCommand;
    RenderState::StateBlock* _stateBlock;
    Texture2D*             _texture;
    GLProgramState*        _glProgramState;
    IndexBuffer*           _indexBuffer; //index buffer
    VertexBuffer*          _vertexBuffer; // vertex buffer

    std::vector<VertexInfo> _vertices;
    std::vector<unsigned short> _indices;

    std::string _texFile;
};

/** @class PUParticle3DQuadRender
*@brief @~english PUParticle3DQuadRender inherit from PUParticle3DEntityRender, , implement pu quad rendering.

@~chinese PUParticle3DQuadRender �̳���PUParticle3DEntityRender��ʵ����pu���ı�����Ⱦ��
*/
class CC_DLL PUParticle3DQuadRender : public PUParticle3DEntityRender
{
public:

    enum Type
    {
        POINT,
        ORIENTED_COMMON,
        ORIENTED_SELF,
        ORIENTED_SHAPE,
        PERPENDICULAR_COMMON,
        PERPENDICULAR_SELF,
    };

    enum Origin
    {
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };

    enum RotateType
    {
        TEXTURE_COORDS,
        VERTEX
    };

    /**
    * @~english Create a new quad renderer.
    * @~chinese ����һ���µ��ı�����Ⱦ����
    * @param texFile @~english The texture of particles. @~chinese ����ʹ�õ�����
    */
    static PUParticle3DQuadRender* create(const std::string& texFile = "");
    
    /**
    * @~english Set the orientation type of quad.
    * @~chinese �����ı��εĳ������͡�
    * @param type @~english The orientation type. @~chinese �������͡�
    */
    void setType(Type type);

    /**
    * @~english Get the orientation type of quad.
    * @~chinese ��ȡ�ı��εĳ������͡�
    * @param type @~english The orientation type. @~chinese �������͡�
    */
    Type getType() const { return _type; }

    /**
    * @~english Set the center of quad.
    * @~chinese �����ı��ε����ġ�
    * @param origin @~english The center of quad. @~chinese �ı������ġ�
    */
    void setOrigin(Origin origin) { _origin = origin; }

    /**
    * @~english Get the center of quad.
    * @~chinese ��ȡ�ı��ε����ġ�
    * @return @~english The center of quad. @~chinese �ı������ġ�
    */
    Origin getOrigin() const { return _origin; }

    /**
    * @~english Set the rotation type of quad.
    * @~chinese �����ı��ε���ת���͡�
    * @param type @~english The orientation type. @~chinese ��ת���͡�
    */
    void setRotateType(RotateType type) { _rotateType = type; }

    /**
    * @~english Get the rotation type of quad.
    * @~chinese ��ȡ�ı��ε���ת���͡�
    * @param type @~english The orientation type. @~chinese ��ת���͡�
    */
    RotateType getRotateType() const { return _rotateType; }

    /**
    * @~english Set the direction when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese ����������ΪORIENTED_COMMON��PERPENDICULAR_COMMONʱ���÷���
    * @param dir @~english The direction. @~chinese ����
    */
    void setCommonDirection(const Vec3 &dir) { _commonDir = dir; }

    /**
    * @~english Get the direction when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese ����������ΪORIENTED_COMMON��PERPENDICULAR_COMMONʱ��ȡ����
    * @return @~english The direction. @~chinese ����
    */
    const Vec3& getCommonDirection() const { return _commonDir; }

    /**
    * @~english Set the up when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese ����������ΪORIENTED_COMMON��PERPENDICULAR_COMMONʱ�����ı����ϳ���
    * @param up @~english The up. @~chinese �ı����ϳ���
    */
    void setCommonUp(const Vec3 &up) { _commonUp = up; }

    /**
    * @~english Get the up when type is ORIENTED_COMMON or PERPENDICULAR_COMMON.
    * @~chinese ����������ΪORIENTED_COMMON��PERPENDICULAR_COMMONʱ��ȡ�ı����ϳ���
    * @return @~english The up. @~chinese �ı����ϳ���
    */
    const Vec3& getCommonUp() const { return _commonUp; }

    /**
    * @~english Get frame texture row count.
    * @~chinese ��ȡ����֡�����������
    * @return @~english The row count. @~chinese ������
    */
    unsigned short getTextureCoordsRows() const;

    /**
    * @~english Set frame texture row count.
    * @~chinese ��������֡�����������
    * @param textureCoordsRows @~english The row count. @~chinese ������
    */
    void setTextureCoordsRows(unsigned short textureCoordsRows);

    /**
    * @~english Get frame texture column count.
    * @~chinese ��ȡ����֡�����������
    * @param textureCoordsRows @~english The column count. @~chinese ������
    */
    unsigned short getTextureCoordsColumns() const;

    /**
    * @~english Set frame texture column count.
    * @~chinese ��������֡�����������
    * @param textureCoordsColumns @~english The column count. @~chinese ������
    */
    void setTextureCoordsColumns(unsigned short textureCoordsColumns);

    /**
    * @~english Get frame texture count(row x column).
    * @~chinese ��ȡ����֡��������������x��������
    * @return @~english The total count. @~chinese ������
    */
    unsigned int getNumTextureCoords();

    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese ������ǰ��Ⱦ����
    */
    virtual PUParticle3DQuadRender* clone() override;

    /**
    * @~english Copy one quad renderer's attributes to another's(internal method).
    * @~chinese ����һ���ı�����Ⱦ�������Ե�����һ��(�ڲ�����)��
    * @param render @~english The renderer need be copied. @~chinese �������Ե���Ⱦ����
    */
    void copyAttributesTo(PUParticle3DQuadRender *render);
    
CC_CONSTRUCTOR_ACCESS:
    PUParticle3DQuadRender();
    virtual ~PUParticle3DQuadRender();

protected:

    void getOriginOffset(int &offsetX, int &offsetY);
    void determineUVCoords(PUParticle3D *particle);
    void fillVertex(unsigned short index, const Vec3 &pos, const Vec4 &color, const Vec2 &uv);
    void fillTriangle(unsigned short index, unsigned short v0, unsigned short v1, unsigned short v2);

protected:

    Type _type;
    Origin _origin;
    RotateType _rotateType;
    Vec3 _commonDir;
    Vec3 _commonUp;

    unsigned short _textureCoordsRows;
    unsigned short _textureCoordsColumns;
    float _textureCoordsRowStep;
    float _textureCoordsColStep;
};

/** @class PUParticle3DModelRender
*@brief @~english PUParticle3DModelRender inherit from PURender, , implement pu model rendering.

@~chinese PUParticle3DModelRender �̳���PURender��ʵ����pu��ģ����Ⱦ��
*/
class CC_DLL PUParticle3DModelRender : public PURender
{
public:

    /**
    * @~english Create a new model renderer.
    * @~chinese ����һ���µ�ģ����Ⱦ����
    * @param modelFile @~english The model of particles. @~chinese ����ʹ�õ�ģ�͡�
    * @param texFile @~english The texture of particles. @~chinese ����ʹ�õ�����
    */
    static PUParticle3DModelRender* create(const std::string& modelFile, const std::string &texFile = "");

    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese ������ǰ��Ⱦ����
    */
    virtual PUParticle3DModelRender* clone() override;

    /**
    * @~english Copy one model renderer's attributes to another's(internal method).
    * @~chinese ����һ��ģ����Ⱦ�������Ե�����һ��(�ڲ�����)��
    * @param render @~english The renderer need be copied. @~chinese �������Ե���Ⱦ����
    */
    void copyAttributesTo(PUParticle3DModelRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DModelRender();
    virtual ~PUParticle3DModelRender();

protected:

    std::vector<Sprite3D *> _spriteList;
    std::string _modelFile;
    std::string _texFile;
    Vec3 _spriteSize;
};

/** @class PUParticle3DBoxRender
*@brief @~english PUParticle3DBoxRender inherit from PUParticle3DEntityRender, , implement pu box rendering.

@~chinese PUParticle3DBoxRender �̳���PUParticle3DEntityRender��ʵ����pu��������Ⱦ��
*/
class CC_DLL PUParticle3DBoxRender : public PUParticle3DEntityRender
{
public:

    /**
    * @~english Create a new box renderer.
    * @~chinese ����һ���µ�������Ⱦ����
    * @param texFile @~english The texture of particles. @~chinese ����ʹ�õ�����
    */
    static PUParticle3DBoxRender* create(const std::string &texFile = "");

    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese ������ǰ��Ⱦ����
    */
    virtual PUParticle3DBoxRender* clone() override;

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DBoxRender();
    virtual ~PUParticle3DBoxRender();

protected:

    void reBuildIndices(unsigned short count);
};

/** @class PUSphereRender
*@brief @~english PUSphereRender inherit from PUParticle3DEntityRender, , implement pu sphere rendering.

@~chinese PUSphereRender �̳���PUParticle3DEntityRender��ʵ����pu��������Ⱦ��
*/
class CC_DLL PUSphereRender : public PUParticle3DEntityRender
{
public:

    /**
    * @~english Create a sphere renderer.
    * @~chinese ����һ���µ�������Ⱦ����
    * @param texFile @~english The texture of particles. @~chinese ����ʹ�õ�����
    */
    static PUSphereRender* create(const std::string &texFile = "");

    /**
    * @~english Overwrite function.
    * @~chinese ��д�ĺ�����
    * @see Particle3DRender render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem);
    */
    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;

    /**
    * @~english Clone this renderer.
    * @~chinese ������ǰ��Ⱦ����
    */
    virtual PUSphereRender* clone() override;

    /**
    * @~english Copy one sphere renderer's attributes to another's(internal method).
    * @~chinese ����һ��������Ⱦ�������Ե�����һ��(�ڲ�����)��
    * @param render @~english The renderer need be copied. @~chinese �������Ե���Ⱦ����
    */
    void copyAttributesTo(PUSphereRender *render);

CC_CONSTRUCTOR_ACCESS:
    PUSphereRender();
    virtual ~PUSphereRender();

protected:

    void buildBuffers(unsigned short count);

protected:

    unsigned short _numberOfRings;
    unsigned short _numberOfSegments;
    std::vector<VertexInfo> _vertexTemplate;
};

// end of _3d group
/// @}

NS_CC_END
#endif
