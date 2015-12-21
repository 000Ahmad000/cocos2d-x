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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#ifndef __cocos2d_libs__CCPass__
#define __cocos2d_libs__CCPass__

#include <stdio.h>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderState.h"

NS_CC_BEGIN

class GLProgramState;
class Technique;
class Node;
class VertexAttribBinding;

/**
 * @addtogroup support
 * @{
 */

/**
 * @class Pass
 * @brief
 * @~english
 * Material contains one or more techniques. Each technique can contains one or more passes. And material can active one technique for drawing. Pass contains vertex attribute binding and GLProgramState. The Passes in the same Technique are applied one by one when drawing an object.
 * @~chinese ���ʰ���һ�����߶��Technique��ÿ��Technique���԰���һ�����߶��Pass��Pass�ǶԶ������Ժ�GLProgramState�ķ�װ����������ʱ��������ʹ��ʱ���Լ���һ����Technique�еĶ��Passһ����һ����Ӧ�á�
 */

class CC_DLL Pass : public RenderState
{
    friend class Material;

public:
    
    /**
     * @~english Creates a Pass with a GLProgramState.
     * @~chinese ��GLProgramState����һ��Pass��
     * @param parent @~english Technique who owns this Pass. @~chinese ӵ�����Pass��Technique��
     * @param programState @~english GLProgramState used to create Pass. @~chinese ��������Pass��GLProgramState��
     * @return @~english Created Pass. @~chinese �´�����Pass��
     */
    static Pass* createWithGLProgramState(Technique* parent, GLProgramState* programState);

    /**
     * @~english Creates a Pass.
     * @~chinese ����һ��Pass��
     * @param parent @~english Technique who owns this Pass. @~chinese ӵ�����Pass��Technique��
     * @return @~english Created Pass. @~chinese �´�����Pass��
     */
    static Pass* create(Technique* parent);

    /**
     * @~english Gets the GLProgramState.
     * @~chinese ��ȡGLProgramState��
     * @return @~english GLProgramState in the Pass. @~chinese Pass�е�GLProgramState��
     */
    GLProgramState* getGLProgramState() const;

    /**
     * @~english Binds the GLProgramState and the RenderState. This method must be called before call the actuall draw call.
     * @~chinese ��GLProgramState����Ⱦ״̬���������������ʵ�ʻ���֮ǰ���á�
     * @param modelView @~english Model view matrix which is going to pass to shader. @~chinese ��Ⱦ��shader�е�ģ����ͼ����
     */
    void bind(const Mat4& modelView);
    /**
     * @~english Binds the GLProgramState and the RenderState. This method must be called before call the actuall draw call.
     * @~chinese ��GLProgramState����Ⱦ״̬���������������ʵ�ʻ���֮ǰ���á�
     * @param modelView @~english Model view matrix which is going to pass to shader. @~chinese ��Ⱦ��shader�е�ģ����ͼ����
     * @param bindAttributes @~english binding vertex attribute ? @~chinese �Ƿ�󶨶������ԣ�
     */
    void bind(const Mat4& modelView, bool bindAttributes);
    
    /**
     * @~english Unbinds the Pass. This method must be called AFTER calling the actuall draw call.
     * @~chinese �����Pass�İ󶨣��������������ʵ�ʻ���֮����á�
     */
    void unbind();

    /**
     * @~english Sets a vertex attribute binding for this pass. When a mesh binding is set, the VertexAttribBinding will be automatically bound when the bind() method is called for the pass.
     * @~chinese ���ø�Pass�Ķ�������ԡ� ��������������ú����bind()����ʱ���Զ������õĶ������ԡ�
     * @param binding @~english The VertexAttribBinding to set (or NULL to remove an existing binding). @~chinese �����õĶ�������ԣ�������ΪNULLʱ�Ƴ��Ѿ��󶨵Ķ������ԡ�
     */
    void setVertexAttribBinding(VertexAttribBinding* binding);

    /**
     * @~english Returns the vertex attribute binding for this pass.
     * @~chinese ��ȡ��������ԡ�
     * @return @~english The vertex attribute binding for this pass. @~chinese Pass�еĶ�������ԡ�
     */
    VertexAttribBinding* getVertexAttributeBinding() const;

    /**
     * @~english Get Hash code of the Pass.
     * @~chinese ��ȡ��Pass�Ĺ�ϣ�롣
     * @return @~english Hash code of this pass. @~chinese Pass�Ĺ�ϣ�롣
     */
    uint32_t getHash() const;

    /**
     * @~english Returns a clone (deep-copy) of this instance.
     * @~chinese ��ȡPass��һ����ȿ�����
     * @return @~english Copy of this pass. @~chinese Pass�Ŀ�����
     */
    Pass* clone() const;

protected:
    Pass();
    ~Pass();
    bool init(Technique* parent);
    bool initWithGLProgramState(Technique* parent, GLProgramState *glProgramState);

    void setGLProgramState(GLProgramState* glProgramState);
    Node* getTarget() const;

    GLProgramState* _glProgramState;
    VertexAttribBinding* _vertexAttribBinding;
};

/**
 end of support group
 @}
 */

NS_CC_END



#endif /* defined(__cocos2d_libs__CCPass__) */
