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


#ifndef __CCRENDERCOMMAND_H_
#define __CCRENDERCOMMAND_H_

#include <stdint.h>

#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

/**
@class RenderCommand
@brief
@~english Base class of the `RenderCommand` hierarchy.
*
 The `Renderer` knows how to render `RenderCommands` objects.
 * @~chinese ��RenderCommand�����νṹ�Ļ��ࡣ
 * 
 * ��Ⱦ����֪����γ��֡�RenderCommands������
 */
class CC_DLL RenderCommand
{
public:
    /**
    @~english Enum the type of render command.  
    @~chinese ö�٣���Ⱦ��������͡�
    */
    enum class Type
    {
        /** 
        @~english Reserved type. 
        @~chinese ����,δ֪���͡�
        */
        UNKNOWN_COMMAND,
        /** 
        @~english Quad command, used for draw quad. 
        @~chinese Quad Command,���ڻ��ı��Ρ�
        */
        QUAD_COMMAND,
        /**
        @~english Custom command, used for calling callback for rendering. 
        @~chinese �Զ�������,���ڵ��ûص�����������Ⱦ��
        */
        CUSTOM_COMMAND,
        /**
        @~english Batch command, used for draw batches in texture atlas. 
        @~chinese ����������,����������ȾTextureAtlas��
        */
        BATCH_COMMAND,
        /**
        @~english Group command, which can group command in a tree hierarchy. 
        @~chinese Group command, ���Խ���Ⱦ������֯�����νṹ��
        */
        GROUP_COMMAND,
        /**
        @~english Mesh command, used to draw 3D meshes. @
        ~chinese ��������,��������3d����
        */
        MESH_COMMAND,
        /**
        @~english Primitive command, used to draw primitives such as lines, points and triangles. 
        @~chinese Primitive command,���ڻ��Ƹ���ͼԪ,����,��������Ρ�*/
        PRIMITIVE_COMMAND,
        /**
        @~english Triangles command, used to draw triangles. 
        @~chinese Triangles command,�������������Ρ�
        */
        TRIANGLES_COMMAND
    };

    /**@~english
     Init function, will be called by all the render commands.
     * @~chinese 
     * ��ʼ��������ÿһ����Ⱦ�������á�
     @param globalZOrder @~english The global order of command, used for rendercommand sorting.
     * @~chinese ��Ⱦ�����global Z,����rendercommand����
     @param modelViewTransform @~english Modelview matrix when submitting the render command.
     * @~chinese ��Ⱦ�����ModelView����
     @param flags @~english Flag used to indicate whether the command should be draw at 3D mode or not.
     * @~chinese ���ڱ�ʾ��Ⱦ�����Ƿ��ǲ���3D��Ⱦģʽ��
     */
    void init(float globalZOrder, const Mat4& modelViewTransform, uint32_t flags);
    
    /** 
    @~english Get global Z order.  
    @~chinese ���Global Z��
    @return 
    @~english the global Z of render command.
    @~chinese ��Ⱦ�����global Z��
    */
    inline float getGlobalOrder() const { return _globalOrder; }

    /** 
    @~english Returns the Command type.  
    @~chinese ������������͡�
    @return
    @~english The type of render command.
    @~chinese ��Ⱦ�������͡�
    */
    inline Type getType() const { return _type; }
    
    /** 
    @~english Retruns whether is transparent.  
    @~chinese �Ƿ���͸�������塣
    @return
    @~english The transparent status.
    @~chinese ͸��״̬��
    */
    inline bool isTransparent() const { return _isTransparent; }
    
    /** 
    @~english Set transparent flag.  
    @~chinese ����͸���ı�ʾ��
    @param isTransparent
    @~english The transparent status.
    @~chinese ͸��״̬��
    */
    inline void setTransparent(bool isTransparent) { _isTransparent = isTransparent; }
    /**@~english
     Get skip batching status, if a rendering is skip batching, it will be forced to be rendering separately.
     * @~chinese 
     * ȡ��Skip Batching״̬,��״̬�µ�����ᵥ������һ����Ⱦ��
     @return 
     @~english the Skip Batching status.
     @~chinese Skip Batching��״̬��
     */
    inline bool isSkipBatching() const { return _skipBatching; }
    /**
    @~english Set skip batching. 
    @~chinese ����Skip Batching ״̬��
    @param value
    @~english the skip batching status.
    @~chinese skip batching ��״̬��
    */
    inline void setSkipBatching(bool value) { _skipBatching = value; }
    /**
    @~english Whether the command should be rendered at 3D mode. 
    @~chinese �����Ƿ���3d��Ⱦģʽ��
    @return
    @~english the 3D mode status.
    @~chinese 3D��Ⱦģʽ��
    */
    inline bool is3D() const { return _is3D; }
    /**
    @~english Set the command rendered in 3D mode or not. 
    @~chinese ����3d��Ⱦģʽ��
    @param value
    @~english the 3D model status.
    @~chinese 3D��Ⱦģʽ��״̬��
    */
    inline void set3D(bool value) { _is3D = value; }
    /**
    @~english Get the depth by current model view matrix. 
    @~chinese �õ���Ŀǰ��ģ����ͼ�����µ���ȡ�
    @return
    @~english the depth value.
    @~chinese ���ֵ��
    */
    inline float getDepth() const { return _depth; }
    
protected:
    /**Constructor.*/
    RenderCommand();
    /**Destructor.*/
    virtual ~RenderCommand();
    //used for debug but it is not implemented.
    void printID();

    /**Type used in order to avoid dynamic cast, faster.*/
    Type _type;

    /**Commands are sort by global Z order.*/
    float _globalOrder;
    
    /**Transparent flag.*/
    bool  _isTransparent;
    
    /**
     QuadCommand and TrianglesCommand could be auto batched if there material ID is the same, however, if
     a command is skip batching, it would be forced to draw in a separate function call, and break the batch.
     */
    bool _skipBatching;
    
    /**Is the command been rendered on 3D pass.*/
    bool _is3D;
    
    /**Depth from the model view matrix.*/
    float _depth;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif //__CCRENDERCOMMAND_H_
