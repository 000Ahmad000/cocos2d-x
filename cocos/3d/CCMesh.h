/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCMESH_H__
#define __CCMESH_H__

#include <string>

#include "3d/CCBundle3DData.h"
#include "3d/CCAABB.h"

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "renderer/CCMeshCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class Texture2D;
class MeshSkin;
class MeshIndexData;
class GLProgramState;
class GLProgram;
class Material;
class Renderer;
class Scene;
class Pass;

/** 
 * @class Mesh
 * @brief @~english Mesh: contains ref to index buffer, GLProgramState, texture, skin, blend function, aabb and so on
 * @~chinese Mesh�����ڴ洢�����е��������棬Gl��Ⱦ״̬��������Ƥ��Ƭ�λ�Ϸ����Լ�AABB������.
 */
class CC_DLL Mesh : public Ref
{
    friend class Sprite3D;
public:
    /**
     * @~english The indices array
     * @~chinese ������������
     */
    typedef std::vector<unsigned short> IndexArray;
    /**
     * @~english Create mesh from positions, normals, and so on, single SubMesh
     * @~chinese ͨ��λ�ã����߼���������������һ��������������
     * @param positions @~english The positions list.
     * @~chinese λ������
     * @param normals @~english The normals list.
     * @~chinese ��������
     * @param texs @~english The texture UV corodinates list.
     * @~chinese �����UV��������
     * @param indices @~english The indices list
     * @~chinese ������������
     * @return @~english The Mesh object.
     * @~chinese ��������Mesh����
     */
    static Mesh* create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const IndexArray& indices);
    /**create mesh with vertex attributes*/
    CC_DEPRECATED_ATTRIBUTE static Mesh* create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, int numIndex, const std::vector<MeshVertexAttrib>& attribs, int attribCount){ return create(vertices, perVertexSizeInFloat, indices, attribs); }
    
    /**
     * @~english Create mesh from vertices, indices and attribs
     * @~chinese ͨ���������飬���������Լ�������������������
     * @param vertices @~english the vertices list.
     * @~chinese ��������
     * @param perVertexSizeInFloat @~english Each vertex element's size.
     * @~chinese ÿ������Ԫ�صĴ�С
     * @param indices @~english The indices list.
     * @~chinese ��������
     * @param attribs @~english The mesh vertices attributes list.
     * @~chinese ������������
     * @return @~english The Mesh object.
     * @~chinese ������������
     * @lua NA
     */
    static Mesh* create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, const std::vector<MeshVertexAttrib>& attribs);
    
    /** 
     *@~english  Create mesh from name, mesh index data and skin
     * @~chinese ͨ�����ƣ�MeshIndexData�����Լ���Ƥ������Mesh����
     * @param name @~english The name.
     * @~chinese ����
     * @param indexData @~english The indexData list.
     * @~chinese ���������б�
     * @param skin @~english The MeshSkin object.
     * @~chinese ������Ƥ��Ϣ
     * @return @~english The Mesh object.
     * @~chinese ������������
     * @lua NA
     */
    static Mesh* create(const std::string& name, MeshIndexData* indexData, MeshSkin* skin = nullptr);
    
    /**
     * @~english Get the vertex buffer.
     * @~chinese ��ȡ���㻺��
     * @return @~english The VBO ID.
     * @~chinese ���㻺��ľ��ID
     * @lua NA
     */
    GLuint getVertexBuffer() const;
    /**
     * @~english Check if the mesh have specified vertex attribute or not
     * @~chinese ��������Ƿ�ӵ��ָ���Ķ�������
     * @param attrib @~english The attribute type ID.
     * @~chinese ��������ID
     * @return @~english Return true if the mesh have specified attribute, otherwise return false.
     * @~chinese �����������ָ����������ʱ����true����֮����false
     * @lua NA
     */
    bool hasVertexAttrib(int attrib) const;
    /**
     * @~english Get the mesh vertex attribute count.
     * @~chinese ���ظ���������Ķ������Ե�����
     * @return @~english The vertex attribute count.
     * @~chinese �������Ե�����
     */
    ssize_t getMeshVertexAttribCount() const;
    /**
     * @~english Get MeshVertexAttribute by index
     * @~chinese ͨ����������ȡ����Ķ�������
     * @param idx @~english The index.
     * @~chinese ������������
     * @return @~english The MeshVertexAttribute object.
     * @~chinese MeshVertexAttribute ����
     **/
    const MeshVertexAttrib& getMeshVertexAttribute(int idx);
    /**
     * @~english Get per vertex size in bytes.
     * @~chinese ��ȡÿһ����������ݴ�С�����ֽڼ�
     * @return @~english The per vertex size in bytes.
     * @~chinese ÿ����������ݴ�С
     */
    int getVertexSizeInBytes() const;

    /** 
     * @~english Texture setter.
     * @~chinese ������������
     * @param texPath @~english The texture file path.
     * @~chinese �����ļ���·��
     */
    void setTexture(const std::string& texPath);

    /**
     * @~english Texture setter.
     * @~chinese ������������
     * @param tex @~english The Texture2D object.
     * @~chinese Texture2D ����
     */
    void setTexture(Texture2D* tex);

    /**
     * @~english Texture getter.
     * @~chinese ��ȡ����
     * @return @~english The Texture2D object.
     * @~chinese Texture2D ����
     */
    Texture2D* getTexture() const;
    
    /**
     * @~english Visible setter
     * @~chinese ���ÿɼ���
     * @param visible @~english The visiblity
     * @~chinese �ɼ���
     */
    void setVisible(bool visible);

    /**
     * Visible getter.
     * @~chinese ��ȡ�ɼ���
     * @return the visiblity of the mesh.
     * @~chinese �ɼ���
     */
    bool isVisible() const;
    
    /**
     * @~english The skin getter.
     * @~chinese ��ȡ��Ƥ��Ϣ
     * @return @~english The MeshSkin Object.
     * @~chinese MeshSkin ����
     * @lua NA
     */
    MeshSkin* getSkin() const { return _skin; }
    
    /**
     * @~english Mesh index data getter.
     * @~chinese ��ȡ������������
     * @return @~english The MeshIndexData object.
     * @~chinese MeshIndexData ����
     * @lua NA
     */
    MeshIndexData* getMeshIndexData() const { return _meshIndexData; }
    
    /**
     * @~english Get GLProgramState.
     * @~chinese ���GL shader״̬
     * @return @~english The GLProgramState object.
     * @~chinese GLProgramState ����
     * @lua NA
     */
    GLProgramState* getGLProgramState() const;
    
    /**
     * @~english Get the mesh's name.
     * @~chinese ��ȡ��������
     * @return @~english The mesh's name.
     * @~chinese ��������
     */
    const std::string& getName() const { return _name; }
    
    /**
     * @~english Set the blending function.
     * @~chinese ����Ƭ�λ�Ϻ���
     * @param blendFunc @~english The specified blending function.
     * @~chinese �����Ļ�Ϻ���
     */
    void setBlendFunc(const BlendFunc &blendFunc);

    /**
     * @~english Get the mesh's blending function.
     * @~chinese ��ȡƬ�λ�Ϻ���
     * @return The blending function.
     * @~chinese ��Ϻ���
     */
    const BlendFunc &getBlendFunc() const;
    
    /** 
     * @~english Get primitive type.
     * @~chinese ��ȡ�������������ͣ���ν�������������ͣ��������Ժ��ַ�ʽ������������֯����
     * @return @~english The primitive type.
     * @~chinese ��������������
     * @lua NA
     */
    GLenum getPrimitiveType() const;
    /**
     * @~english Get index count
     * @~chinese ��ȡ��������
     * @return @~english The index count of the mesh.
     * @~chinese�������������
     * @lua NA
     */
    ssize_t getIndexCount() const;
    /**
     * @~english Get the mesh's index data format.
     * @~chinese ��ȡ�����������������
     * @return @~english The index data format, should be GL_UNSIGNED_SHORT.
     * @~chinese ����������������ͣ�ͨ��Ϊ GL_UNSIGNED_SHORT����
     * @lua NA
     */
    GLenum getIndexFormat() const;
    /**
     * @~english Get the mesh's index buffer object(IBO) handle.
     * @~chinese ��ȡ����Ķ��㻺�����(IBO)��GL���
     * @return @~english The IBO handle.
     * @~chinese ���㻺�����(IBO)��GL���
     * @lua NA
     */
    GLuint getIndexBuffer() const;
    
    /**
     * @~english Get the mesh's AABB in local space.
     * @~chinese ��ȡ����ľֲ�����ϵ�µ�AABB
     * @return @~english The AABB object.
     * @~chinese AABB����
     */
    const AABB& getAABB() const { return _aabb; }

    /**  
     * @~english Sets a new GLProgramState for the Mesh
     * @~chinese Ϊ���������µ�GLProgrameState����
     * @param glProgramState @~english The new GLProgramState object.
     * @~chinese ��GLProgrameState����
     * @note @~english A new Material will be created for it
     * @~chinese �µĲ��ʽ��ᱻ����
     */
    void setGLProgramState(GLProgramState* glProgramState);

    /**
     * @~english Sets a new Material to the Mesh 
     * @~chinese �����������²���
     * @param material @~english The new Material object.
     * @~chinese �²���
     */
    void setMaterial(Material* material);

    /**
     * @~english Get the Material which being used by the Mesh 
     * @~chinese ��ȡ��ǰMesh��ʹ�õĲ���
     * @return @~english The material object. @~chinese ���ʶ���
     */
    Material* getMaterial() const;

    void draw(Renderer* renderer, float globalZ, const Mat4& transform, uint32_t flags, unsigned int lightMask, const Vec4& color, bool forceDepthWrite);

    /** 
     * @~english Get the MeshCommand.
     * @~chinese ��ȡMeshCommand
     * @return @~english The MeshCommand object
     * @~chinese MeshCommand ����
     */
    MeshCommand& getMeshCommand() { return _meshCommand; }

    /**
     * @~english Set a specified skin to mesh.
     * @~chinese ����������ָ������Ƥ��Ϣ
     * @param skin @~english The specified skin object.
     * @~chinese ָ����MeshSkin����
     */
    void setSkin(MeshSkin* skin);
    /**
     * @~english Set the mesh index data.
     * @~chinese �����������������
     * @param indexdata @~english The specified MeshIndexData.
     * @~chinese ָ����MeshIndexData����
     */
    void setMeshIndexData(MeshIndexData* indexdata);

    /**
     * @~english Set the mesh's name.
     * @~chinese �������������
     * @param name @~english The mesh's new name.
     * @~chinese �����������
     */
    void setName(const std::string& name) { _name = name; }
 
    /** 
     * @~english Calculate the AABB of the mesh.
     * @~chinese ���������AABB
     * @note @~english The AABB is in the local space, not the world space
     * @~chinese ��AABB��������ľֲ�����ϵ�£�������������ϵ��
     */
    void calculateAABB();
    
    /**
     * force set this Sprite3D to 2D render queue
     */
    void setForce2DQueue(bool force2D) { _force2DQueue = force2D; }

CC_CONSTRUCTOR_ACCESS:

    Mesh();
    virtual ~Mesh();

protected:
    void resetLightUniformValues();
    void setLightUniforms(Pass* pass, Scene* scene, const Vec4& color, unsigned int lightmask);
    void bindMeshCommand();

    Texture2D*          _texture;  //texture that submesh is using
    MeshSkin*           _skin;     //skin
    bool                _visible; // is the submesh visible
    bool                _isTransparent; // is this mesh transparent, it is a property of material in fact
    bool                _force2DQueue; // add this mesh to 2D render queue
    
    std::string         _name;
    MeshCommand         _meshCommand;
    MeshIndexData*      _meshIndexData;
    GLProgramState*     _glProgramState;
    BlendFunc           _blend;
    bool                _blendDirty;
    Material*           _material;
    AABB                _aabb;
    std::function<void()> _visibleChanged;
    
    ///light parameters
    std::vector<Vec3> _dirLightUniformColorValues;
    std::vector<Vec3> _dirLightUniformDirValues;
    
    std::vector<Vec3> _pointLightUniformColorValues;
    std::vector<Vec3> _pointLightUniformPositionValues;
    std::vector<float> _pointLightUniformRangeInverseValues;
    
    std::vector<Vec3> _spotLightUniformColorValues;
    std::vector<Vec3> _spotLightUniformPositionValues;
    std::vector<Vec3> _spotLightUniformDirValues;
    std::vector<float> _spotLightUniformInnerAngleCosValues;
    std::vector<float> _spotLightUniformOuterAngleCosValues;
    std::vector<float> _spotLightUniformRangeInverseValues;
};

// end of 3d group
/// @}


NS_CC_END

#endif // __CCMESH_H__
