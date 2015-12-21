/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __CC_TRIANGLES_COMMAND__
#define __CC_TRIANGLES_COMMAND__

#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgramState.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

/** @class TrianglesCommand
@brief
@~english
 Command used to render one or more Triangles, which is similar to QuadCommand.
 Every TrianglesCommand will have generate material ID by give textureID, glProgramState, Blend function
 if the material id is the same, these TrianglesCommands could be batched to save draw call.
 * @~chinese 
 * ���������ڻ���һ������������,��QuadCommand���ơ�
 * ÿ��TrianglesCommand��ʹ��textureID,glProgramState,��Ϲ��ܵ����ɲ���ID,
 * �������ID����ͬ��,��ЩTrianglesCommands���Խ�����������ơ�
*/
class CC_DLL TrianglesCommand : public RenderCommand
{
public:
    /**@~english The structure of Triangles.  @~chinese �����εĽṹ��*/
    struct Triangles
    {
        /**@~english Vertex data pointer. @~chinese ��������ָ�롣*/
        V3F_C4B_T2F* verts;
        /**@~english Index data pointer. @~chinese ��������ָ�롣*/
        unsigned short* indices;
        /**@~english The number of vertices. @~chinese �����������*/
        ssize_t vertCount;
        /**@~english The number of indices. @~chinese ������������*/
        ssize_t indexCount;
    };
    /**@~english Construtor. @~chinese ���캯����*/
    TrianglesCommand();
    /**@~english Destructor. @~chinese ����������*/
    ~TrianglesCommand();
    
    /** @~english Initializes the command.
     * @~chinese ��ʼ�����
     @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese ��Ⱦ�����GlobalZOrder��
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese �����openGL�����
     @param glProgramState @~english The specified glProgram and its uniform.
     * @~chinese ָ����glProgram����uniform������
     @param blendType @~english Blend function for the command.
     * @~chinese ��Ⱦ����Ļ�Ϻ�����
     @param triangles @~english Rendered triangles for the command.
     * @~chinese ��Ⱦ�������Ρ�
     @param mv @~english ModelView matrix for the command.
     * @~chinese ModelView����
     @param flags @~english to indicate that the command is using 3D rendering or not.
     * @~chinese �������Ƿ�ʹ��3d��Ⱦ��
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv, uint32_t flags);
    /**
    @~english Deprecated function, the params is similar as the upper init function, with flags equals 0. 
    @~chinese Deprecated����,����Ϊ��init��������,������flags����0��
    @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese ��Ⱦ�����GlobalZOrder��
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese �����openGL�����
     @param glProgramState @~english The specified glProgram and its uniform.
     * @~chinese ָ����glProgram����uniform������
     @param blendType @~english Blend function for the command.
     * @~chinese ��Ⱦ����Ļ�Ϻ�����
     @param triangles @~english Rendered triangles for the command.
     * @~chinese ��Ⱦ�������Ρ�
     @param mv @~english ModelView matrix for the command.
     * @~chinese ModelView����
    */
    CC_DEPRECATED_ATTRIBUTE void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv);
    /**
    @~english Apply the texture, shaders, programs, blend functions to GPU pipeline. 
    @~chinese Ӧ��������ɫ������,��ϵ�openGL��Ⱦ�����С�
    */
    void useMaterial() const;
    /**
    @~english Get the material id of command. 
    @~chinese �õ��Ĳ���ID��
    @return @~english Material ID.
    @~chinese ����ID��
    */
    inline uint32_t getMaterialID() const { return _materialID; }
    /**
    @~english Get the openGL texture handle. 
    @~chinese �õ������openGL�����
    @return @~english openGL texture handle.
    @~chinese �����openGL�����
    */
    inline GLuint getTextureID() const { return _textureID; }
    /**
    @~english Get a const reference of triangles. 
    @~chinese �õ���Ⱦ�����ε����ݡ�
    @return @~english The triangles to be rendered.
    @~chinese ����Ⱦ�����Ρ�
    */
    inline const Triangles& getTriangles() const { return _triangles; }
    /**
    @~english Get the vertex count in the triangles. 
    @~chinese �����εĶ�������
    @return @~english the vertex count.
    @~chinese �����εĶ�����Ŀ��
    */
    inline ssize_t getVertexCount() const { return _triangles.vertCount; }
    /**
    @~english Get the index count of the triangles. 
    @~chinese �õ������ε�������Ŀ��
    @return @~english The index count.
    @~chinese �����ε�������Ŀ��
    */
    inline ssize_t getIndexCount() const { return _triangles.indexCount; }
    /**
    @~english Get the vertex data pointer. 
    @~chinese �õ��������ݵ�ָ�롣
    @return @~english The pointer of the vertex data.
    @~chinese �������ݵ�ָ�롣
    */
    inline const V3F_C4B_T2F* getVertices() const { return _triangles.verts; }
    /**
    @~english Get the index data pointer. 
    @~chinese �õ��������ݵ�ָ�롣
    @return @~english The pointer of index data.
    @~chinese �������ݵ�ָ�롣
    */
    inline const unsigned short* getIndices() const { return _triangles.indices; }
    /**
    @~english Get the GLProgram and uniform. 
    @~chinese �õ���Ⱦ��GLProgram��unifrom����
    @return @~english GLProgram and its uniform.
    @~chinese GLProgram��uniform������
    */
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**
    @~english Get the blend function. 
    @~chinese �õ���Ϻ�����
    @return @~english The blend function.
    @~chinese ��Ϻ�����
    */
    inline BlendFunc getBlendType() const { return _blendType; }
    /**
    @~english Get the model view matrix. 
    @~chinese �õ�ModelView����
    @return @~english The ModelView matrix.
    @~chinese ModelView����
    */
    inline const Mat4& getModelView() const { return _mv; }
    
protected:
    /** Generate the material ID by textureID, glProgramState, and blend function. */
    void generateMaterialID();
    
    /** Generated material id. */
    uint32_t _materialID;
    /** OpenGL handle for texture.*/
    GLuint _textureID;
    /** GLprogramstate for the commmand. encapsulate shaders and uniforms. */
    GLProgramState* _glProgramState;
    /** Blend function when rendering the triangles.*/
    BlendFunc _blendType;
    /** Rendered triangles. */
    Triangles _triangles;
    /** Model view matrix when rendering the triangles.*/
    Mat4 _mv;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif // defined(__CC_TRIANGLES_COMMAND__)
