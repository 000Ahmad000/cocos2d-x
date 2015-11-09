/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 Copyright (c) 2014 GamePlay3D team
 
 http://www.cocos2d-x.org


 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Ideas taken from:
   - GamePlay3D: http://gameplay3d.org/
   - OGRE3D: http://www.ogre3d.org/
   - Qt3D: http://qt-project.org/

 ****************************************************************************/

#ifndef __cocos2d_libs__CCRenderState__
#define __cocos2d_libs__CCRenderState__

#include <string>
#include <functional>
#include <cstdint>

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Texture2D;
class Pass;

/**
 * Defines the rendering state of the graphics device.
 */
/**
 * @addtogroup support
 * @{
 */

/**
 * @class RenderState
 * @brief
 * @~english
 * Defines the rendering state of the graphics device.
 * @~chinese �����Կ�����Ⱦ״̬��
 */

class CC_DLL RenderState : public Ref
{
    friend class Material;
    friend class Technique;
    friend class Pass;

public:
    /**
     * @~english Static initializer that is called during game startup.
     * @~chinese ��̬��ʼ����������Ϸ��ʼ����ʱ���á�
     */
    static void initialize();

    /**
     * @~english Static finalizer that is called during game shutdown.
     * @~chinese ��̬���ٺ���������Ϸ������ʱ�����
     */
    static void finalize();

    /**
     * @~english Get name
     * @~chinese ��ȡ����
     * @return @~english Name. @~chinese ���ơ�
     */
    std::string getName() const;

    /** 
     * @~english Texture that will use in the CC_Texture0 uniform.
     Added to be backwards compatible. Use Samplers from .material instead.
     * @~chinese ���������Ϊ�˸�֮ǰ�Ĵ�����ݣ�������ͼͨ��CC_Texture0���ݵ�shader�С� �Ƽ���.material�ļ��е�Sampler�����档
     * @param texture @~english Texture to be binding. @~chinese ��Ҫ�󶨵���ͼ��
     */
    void setTexture(Texture2D* texture);

    /** 
     * @~english Returns the texture that is going to be used for CC_Texture0.
     Added to be backwards compatible.
     * @~chinese Ϊ�˸�֮ǰ�ľɴ�����ݣ�����������ؽ�Ҫ���ݵ�shader CC_Texture0����ͼ��
     * @return @~english texture that is going to be used for CC_Texture0. @~chinese ��CC_Texture0ʹ�õ���ͼ��
     */
    Texture2D* getTexture() const;

    /**
     * @~english Binds the render state for this RenderState and any of its parents, top-down,
     * for the given pass.
     * @~chinese ����Ⱦ״̬���Ӹ��ڵ㵽���ڵ�Ӧ����Ⱦ״̬��
     * @param pass @~english Not used. @~chinese û���õ���
     */
    void bind(Pass* pass);

    /**
     * @~english Returns the topmost RenderState in the hierarchy below the given RenderState.
     * @~chinese ��ȡ�������������RenderState��
     * @return @~english The top most render state below the given RenderState. @~chinese ����RenderState�����RenderState��
     */
    RenderState* getTopmost(RenderState* below);
    
    void setParent(RenderState* parent) { _parent = parent; }

    enum Blend
    {
        BLEND_ZERO = GL_ZERO,
        BLEND_ONE = GL_ONE,
        BLEND_SRC_COLOR = GL_SRC_COLOR,
        BLEND_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
        BLEND_DST_COLOR = GL_DST_COLOR,
        BLEND_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
        BLEND_SRC_ALPHA = GL_SRC_ALPHA,
        BLEND_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
        BLEND_DST_ALPHA = GL_DST_ALPHA,
        BLEND_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
        BLEND_CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
        BLEND_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
        BLEND_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE
    };

    /**
     * @~english Defines the supported depth compare functions.
     *
     * Depth compare functions specify the comparison that takes place between the
     * incoming pixel's depth value and the depth value already in the depth buffer.
     * If the compare function passes, the new pixel will be drawn.
     *
     * The initial depth compare function is DEPTH_LESS.
     *
     * @~chinese ������ȱȽϺ����� ��ȱȽϺ��������˽�Ҫ���Ƶ����ص����������Ȼ����е�������ȱȽ����滻�Ĺ�������ȽϺ���ͨ���ˣ���ô�µ����ؽ������ơ���ȱȽϺ����ĳ�ʼֵΪDEPTH_LESS��
     */
    enum DepthFunction
    {
        DEPTH_NEVER = GL_NEVER,
        DEPTH_LESS = GL_LESS,
        DEPTH_EQUAL = GL_EQUAL,
        DEPTH_LEQUAL = GL_LEQUAL,
        DEPTH_GREATER = GL_GREATER,
        DEPTH_NOTEQUAL = GL_NOTEQUAL,
        DEPTH_GEQUAL = GL_GEQUAL,
        DEPTH_ALWAYS = GL_ALWAYS
    };

    /**
     * @~english Defines culling criteria for front-facing, back-facing and both-side
     * facets.
     * @~chinese ������Ĳü���ʽ��ǰ�桢�����˫��ü���
     */
    enum CullFaceSide
    {
        CULL_FACE_SIDE_BACK = GL_BACK,
        CULL_FACE_SIDE_FRONT = GL_FRONT,
        CULL_FACE_SIDE_FRONT_AND_BACK = GL_FRONT_AND_BACK
    };

    /**
     * @~english Defines the winding of vertices in faces that are considered front facing.
     *
     * The initial front face mode is set to FRONT_FACE_CCW.
     * @~chinese ����ǰ��ķ��򣬳�ʼ�������ʱ��Ϊǰ�棬FRONT_FACE_CCW��
     */
    enum FrontFace
    {
        FRONT_FACE_CW = GL_CW,
        FRONT_FACE_CCW = GL_CCW
    };

    /**
     * @~english Defines the supported stencil compare functions.
     *
     * Stencil compare functions determine if a new pixel will be drawn.
     *
     * The initial stencil compare function is STENCIL_ALWAYS.
     * @~chinese ����ģ��ȽϺ�����ģ��ȽϺ���������һ�������Ƿ񱻻��ơ���ʼģ��ȽϺ���ΪSTENCIL_ALWAYS��
     */
    enum StencilFunction
    {
        STENCIL_NEVER = GL_NEVER,
        STENCIL_ALWAYS = GL_ALWAYS,
        STENCIL_LESS = GL_LESS,
        STENCIL_LEQUAL = GL_LEQUAL,
        STENCIL_EQUAL = GL_EQUAL,
        STENCIL_GREATER = GL_GREATER,
        STENCIL_GEQUAL = GL_GEQUAL,
        STENCIL_NOTEQUAL = GL_NOTEQUAL
    };

    /**
     * @~english Defines the supported stencil operations to perform.
     *
     * Stencil operations determine what should happen to the pixel if the
     * stencil test fails, passes, or passes but fails the depth test.
     *
     * The initial stencil operation is STENCIL_OP_KEEP.
     * @~chinese �����ģ�建����еĲ����� ģ��������������ص�ģ�����ʧ�ܡ�ͨ������ͨ��ģ����Զ�û��ͨ����Ȳ��Ե�ʱ��Ҫ���еĲ�������ʼģ�����ΪSTENCIL_OP_KEEP��
     */
    enum StencilOperation
    {
        STENCIL_OP_KEEP = GL_KEEP,
        STENCIL_OP_ZERO = GL_ZERO,
        STENCIL_OP_REPLACE = GL_REPLACE,
        STENCIL_OP_INCR = GL_INCR,
        STENCIL_OP_DECR = GL_DECR,
        STENCIL_OP_INVERT = GL_INVERT,
        STENCIL_OP_INCR_WRAP = GL_INCR_WRAP,
        STENCIL_OP_DECR_WRAP = GL_DECR_WRAP
    };

    /**
     * @class StateBlock
     * @brief
     * @~english Defines a block of fixed-function render states that can be applied to a
     * RenderState object.
     * @~chinese һϵ����Ⱦ״̬����ϣ�����Ӧ�õ�RenderState�����ϡ�
     */
    class CC_DLL StateBlock : public Ref
    {
        friend class RenderState;
        friend class Pass;
        friend class RenderQueue;
        friend class Renderer;
        
    public:
        /**
         * @~english Creates a new StateBlock with default render state settings.
         * @~chinese ��ȱʡ����Ⱦ״̬���ô����µ�StateBlock
         * @return @~english Created StateBlock. @~chinese �´�����StateBlock��
         */
        static StateBlock* create();

        /** @~english The recommended way to create StateBlocks is by calling `create`.
         * Don't use `new` or `delete` on them.
         * @~chinese ���캯�����Ƽ�ʹ��create������������
         */
        StateBlock();
        
        /** @~english Destructor.
         * @~chinese ����������
         */
        ~StateBlock();

        /**
         * @~english Binds the state in this StateBlock to the renderer.
         *
         * This method handles both setting and restoring of render states to ensure that
         * only the state explicitly defined by this StateBlock is applied to the renderer.
         * @~chinese ����Ⱦ״̬�������������Ӧ��RenderBlock�����õ���Ⱦ״̬�⣬Ҳ��ָ���Щû����StateBlock�����õ�״̬��ȱʡ����Ⱦ״̬��
         */
        void bind();

        /**
         * @~english Explicitly sets the source and destination used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         * @~chinese ���û�Ϻ�����ע���Ϻ���ֻ����blendΪtrueʱ�������á�
         * @param blendFunc @~english Specifies how the blending factors are computed.
         * @~chinese ��Ϻ�����Դ��Ŀ��Ķ��塣
         */
        void setBlendFunc(const BlendFunc& blendFunc);

        /**
         * @~english Toggles blending.
         * @~chinese �����Ƿ����û��
         * @param enabled @~english true to enable, false to disable. @~chinese ���û��Ϊtrue����Ϊfalse��
         */
        void setBlend(bool enabled);

        /**
         * @~english Explicitly sets the source used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         * @~chinese ����Դ�Ļ�Ϸ�ʽ��ע��ֻ�е�blendΪtrueʱ�ú����������á�
         * @param blend @~english Specifies how the source blending factors are computed. @~chinese ����Դ�Ļ�Ϸ�ʽ��
         */
        void setBlendSrc(Blend blend);

        /**
         * @~english Explicitly sets the destination used in the blend function for this render state.
         *
         * Note that the blend function is only applied when blending is enabled.
         * @~chinese ����Ŀ��Ļ�Ϸ�ʽ��ע��ֻ�е�blendΪtrueʱ�������á�
         * @param blend @~english Specifies how the destination blending factors are computed. @~chinese ����Ŀ��Ļ�Ϸ�ʽ��
         */
        void setBlendDst(Blend blend);

        /**
         * @~english Explicitly enables or disables backface culling.
         * @~chinese �����Ƿ�����ü�
         * @param enabled @~english true to enable, false to disable. @~chinese ����ü�Ϊtrue������Ϊfalse��
         */
        void setCullFace(bool enabled);

        /**
         * @~english Sets the side of the facets to cull.
         *
         * When not explicitly set, the default is to cull back-facing facets.
         * @~chinese ���òü����档ȱʡֵΪ�ü����档
         * @param side @~english The side to cull. @~chinese �����õ��档
         */
        void setCullFaceSide(CullFaceSide side);

        /**
         * @~english Sets the winding for front facing polygons.
         *
         * By default, counter-clockwise wound polygons are considered front facing.
         * @~chinese ���ö���Ϊǰ��ĳ���Ĭ��ֵΪ��ʱ�뷽��
         * @param winding @~english The winding for front facing polygons. @~chinese ����Ϊǰ��ĳ���
         */
        void setFrontFace(FrontFace winding);

        /**
         * @~english Toggles depth testing.
         *
         * By default, depth testing is disabled.
         * @~chinese ������Ȳ����Ƿ�����
         * @param enabled @~english true to enable, false to disable. @~chinese Ϊtrue������Ȳ��ԣ�false�ر���Ȳ��ԡ�
         */
        void setDepthTest(bool enabled);

        /**
         * @~english Toggles depth writing.
         * @~chinese �����Ƿ������д��
         * @param enabled @~english true to enable, false to disable. @~chinese true�������д��false�ر����д��
         */
        void setDepthWrite(bool enabled);

        /**
         * @~english Sets the depth function to use when depth testing is enabled.
         *
         * When not explicitly set and when depth testing is enabled, the default
         * depth function is DEPTH_LESS.
         * @~chinese ������ȱȽϺ��������ҽ�����Ȳ��Կ���ʱ��Ч��ȱʡ��ȱȽϺ���ΪDEPTH_LESS��
         * @param func @~english The depth function. @~chinese ��ȱȽϺ�����
         */
        void setDepthFunction(DepthFunction func);

        // /**
        //  * @~english Toggles stencil testing.
        //  *
        //  * By default, stencil testing is disabled.
        //  * @~chinese ����ģ������Ƿ�����Ĭ��ģ����Թرա�
        //  * @param enabled @~english true to enable, false to disable. @~chinese true������false�رա�
        //  */
        // void setStencilTest(bool enabled);

        // /**
        //  * @~english Sets the stencil writing mask.
        //  *
        //  * By default, the stencil writing mask is all 1's.
        //  * @~chinese ����ģ��д�����룬ȱʡģ������д������Ϊ����1.
        //  * @param mask @~english Bit mask controlling writing to individual stencil planes. @~chinese ������������д��ģ�����ϡ�
        //  */
        // void setStencilWrite(unsigned int mask);

        // /**
        //  * @~english Sets the stencil function.
        //  *
        //  * By default, the function is set to STENCIL_ALWAYS, the reference value is 0, and the mask is all 1's.
        //  * @~chinese ����ģ��ȽϺ�����Ĭ�ϵ�ģ�庯��ΪSTENCIL_ALWAYS���ο�ֵΪ0������Ϊȫ��1��
        //  * @param func @~english The stencil function. @~chinese ģ�庯����
        //  * @param ref @~english The stencil reference value. @~chinese ģ��ο�ֵ��
        //  * @param mask @~english The stencil mask. @~chinese ģ�����롣
        //  */
        // void setStencilFunction(StencilFunction func, int ref, unsigned int mask);

        // /**
        //  * @~english Sets the stencil operation.
        //  *
        //  * By default, stencil fail, stencil pass/depth fail, and stencil and depth pass are set to STENCIL_OP_KEEP.
        //  * @~chinese ����ģ�������Ĭ�������ģ�����ʧ�ܡ�ģ�����ʧ����Ȳ���ͨ����ģ�������Ȳ��Զ�ͨ����ģ�����������ΪSTENCIL_OP_KEEP��
        //  * @param sfail @~english The stencil operation if the stencil test fails.@~chinese ģ�����ʧ��ʱ���ģ�������
        //  * @param dpfail @~english The stencil operation if the stencil test passes, but the depth test fails. @~chinese ģ�����ͨ������Ȳ���ʧ��ʱ���ģ�������
        //  * @param dppass @~english The stencil operation if both the stencil test and depth test pass. @~chinese ģ����Ժ���Ȳ��Զ�ʧ��ʱ���ģ�������
        //  */
        // void setStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass);

        /**
         * @~english Sets a render state from the given name and value strings.
         *
         * This method attempts to interpret the passed in strings as render state
         * name and value. This is normally used when loading render states from
         * material files.
         * @~chinese ͨ���������ֺ�ֵ�ַ���������Ⱦ״̬���ú����ڴӲ����ļ��м�����Ⱦ״̬ʱʹ�á�
         * @param name @~english Name of the render state to set. @~chinese ��������Ⱦ״̬�����֡�
         * @param value @~english Value of the specified render state. @~chinese ��������Ⱦ״̬��ֵ��
         */
        void setState(const std::string& name, const std::string& value);

        /**
         * @~english Get hash code of this render state.
         * @~chinese ��ȡ����Ⱦ״̬�Ĺ�ϣ�롣
         * @return @~english Hash code of this render state. @~chinese ����Ⱦ״̬�Ĺ�ϣ�롣
         */
        uint32_t getHash() const;
        /**
         * @~english Is this render state dirty?
         * @~chinese ��Ⱦ״̬�Ƿ��޸Ĺ���
         * @return @~english true dirty, false not dirty. @~chinese true��ʾ�޸Ĺ���falseû���޸Ĺ���
         */
        bool isDirty() const;

        /** StateBlock bits to be used with invalidate */
        enum
        {
            RS_BLEND = (1 << 0),
            RS_BLEND_FUNC = (1 << 1),
            RS_CULL_FACE = (1 << 2),
            RS_DEPTH_TEST = (1 << 3),
            RS_DEPTH_WRITE = (1 << 4),
            RS_DEPTH_FUNC = (1 << 5),
            RS_CULL_FACE_SIDE = (1 << 6),
//            RS_STENCIL_TEST = (1 << 7),
//            RS_STENCIL_WRITE = (1 << 8),
//            RS_STENCIL_FUNC = (1 << 9),
//            RS_STENCIL_OP = (1 << 10),
            RS_FRONT_FACE = (1 << 11),
            
            RS_ALL_ONES = 0xFFFFFFFF,
        };

        /** 
        @~english
         * Invalidates the default StateBlock.
         *
         * Only call it if you are calling GL calls directly. Invoke this function
         * at the end of your custom draw call.
         * This function restores the default render state its defaults values.
         * Since this function might call GL calls, it must be called in a GL context is present.
         * @~chinese ��Ĭ�ϵ�StateBlock״̬ʧЧ��ͨ������£������ֱ�ӵ�����openGL�ĺ������޸���Ⱦ״̬����ôstateBlock�б���
         * ��״̬����openGL��״̬��һ�¡�����������ڰ�openGL����ΪĬ��״̬,������openGL context����ʱ���á�
         * @param stateBits @~english Bitwise-OR of the states that needs to be invalidated
         * @~chinese ��Ҫ���õ�״̬λ������ͨ����λ�������ָ�����״̬��
         */
        static void invalidate(long stateBits);

        /**
         * @~english
         * Restores the global Render State to the default state
         *
         * The difference between `invalidate()` and `restore()`, is that `restore()` will
         * restore the global Render State based on its current state. Only the
         * states that were changed will be restored.
         *
         * Rule of thumb:
         
         - call `restore()` if you want to restore to the default state after using `StateBlock`.
         - call `invalidate()` if you want to restore to the default state after calling manual GL calls.
         * @~chinese ��ȫ�ֵ���Ⱦ״̬����ΪĬ��״̬�� ���������invalidate()���������ڣ�restore()��������ڵ�ǰ��StateBlock��¼��״̬
         * ���ָ�������
         * -����ʹ��stateBlockʱ������ͨ��restore()����stateblock����ΪĬ��״̬��
         * -����ֱ�ӵ���openGL����������״̬ʱ����Ҫ����invalidate()��
         * @param stateOverrideBits @~english Bitwise-OR of the states that needs to be override. @~chinese ������λ�����롣
         */
        static void restore(long stateOverrideBits);

        /***
         * @~english Default render state.
         * @~chinese Ĭ����Ⱦ״̬��
         */
        static StateBlock* _defaultState;

    protected:

        void bindNoRestore();
        static void enableDepthWrite();

        void cloneInto(StateBlock* renderState) const;

        bool _cullFaceEnabled;
        bool _depthTestEnabled;
        bool _depthWriteEnabled;
        DepthFunction _depthFunction;
        bool _blendEnabled;
        Blend _blendSrc;
        Blend _blendDst;
        CullFaceSide _cullFaceSide;
        FrontFace _frontFace;
        bool _stencilTestEnabled;
        unsigned int _stencilWrite;
        StencilFunction _stencilFunction;
        int _stencilFunctionRef;
        unsigned int _stencilFunctionMask;
        StencilOperation _stencilOpSfail;
        StencilOperation _stencilOpDpfail;
        StencilOperation _stencilOpDppass;

        long _bits;

        mutable uint32_t _hash;
        mutable bool _hashDirty;
    };

    void setStateBlock(StateBlock* state);
    StateBlock* getStateBlock() const;

protected:
    RenderState();
    ~RenderState();
    bool init(RenderState* parent);
    void cloneInto(RenderState* state) const;

    mutable uint32_t _hash;
    mutable bool _hashDirty;

    /**
     * The StateBlock of fixed-function render states that can be applied to the RenderState.
     */
    mutable StateBlock* _state;

    /**
     * The RenderState's parent. Weak Reference
     */
    RenderState* _parent;

    // name, for filtering
    std::string _name;

    Texture2D* _texture;
};

/**
 end of support group
 @}
 */

NS_CC_END

#endif /* defined(__cocos2d_libs__CCRenderState__) */
