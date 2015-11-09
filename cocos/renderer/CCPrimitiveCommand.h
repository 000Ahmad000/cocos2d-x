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

#ifndef _CC_PRIMITIVE_COMMAND_H__
#define _CC_PRIMITIVE_COMMAND_H__

#include "renderer/CCPrimitive.h"
#include "renderer/CCRenderCommand.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN
class GLProgramState;
/**@~english
 Command used to render primitive, similar to QuadCommand.
 Every QCommand will have generate material ID by give textureID, glProgramState, Blend function. 
 However, primitive command could not be batched.
 * @~chinese 
 * ������QuadCommand��������������Ⱦ����ͼԪ��
 * ÿ��Command��ʹ��textureID, glProgramState����Ϻ��������ɲ���ID��
 * �������batch��Ⱦ��
 */
class CC_DLL PrimitiveCommand : public RenderCommand
{
public:
    /**@~english
     Constructor.
     * @~chinese 
     * ���캯����
     */
    PrimitiveCommand();
    /**@~english
     Destructor.
     * @~chinese 
     * ����������
     */
    ~PrimitiveCommand();
    
    
    /** @~english Initializes the command.
     * @~chinese ��ʼ����Ⱦ���
     @param globalOrder @~english GlobalZOrder of the command.
     * @~chinese �����GlobalZOrder��
     @param textureID @~english The openGL handle of the used texture.
     * @~chinese ����ʹ�õ�����
     @param glProgramState @~english The specified glProgram and its uniform.
     * @~chinese ����ʹ�õ�GLProgramState������GLProgram�Ͷ�Ӧ��uniform��
     @param blendType @~english Blend function for the command.
     * @~chinese ����Ļ�Ϻ�����
     @param primitive @~english Rendered primitive for the command.
     * @~chinese ����Ļ���ͼԪ��
     @param mv @~english ModelView matrix for the command.
     * @~chinese �����ModelView����
     @param flags @~english to indicate that the command is using 3D rendering or not.
     * @~chinese �����������Ƿ�ʹ��3 d��Ⱦ��
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive, const Mat4& mv, uint32_t flags);
    CC_DEPRECATED_ATTRIBUTE void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive,const Mat4& mv);
    
    /**@~english Get the generated material ID. @~chinese ���ɵĲ���ID��*/
    inline uint32_t getMaterialID() const { return _materialID; }
    /**@~english Get the texture ID used for drawing. @~chinese ����ʹ�õ�����*/
    inline GLuint getTextureID() const { return _textureID; }
    /**@~english Get the glprogramstate used for drawing. @~chinese ��Ⱦʹ�õ�GLProgramState��*/
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**@~english Get the blend funcion for drawing. @~chinese �õ��Ļ���ʱʹ�õĻ�Ϻ�����*/
    inline BlendFunc getBlendType() const { return _blendType; }
    /**@~english Get the modelview matrix when draw the primtive. @~chinese ����primtiveʱ���ModelView����*/
    inline const Mat4& getModelView() const { return _mv; }
    /**@~english Execute and draw the commmand, called by renderer. @~chinese ִ�кͻ��Ƹ�����,����Ⱦ�����á�*/
    void execute() const;
protected:
    
    uint32_t _materialID;
    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;
    Primitive* _primitive;
    Mat4 _mv;
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //_CC_PRIMITIVE_COMMAND_H__
