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


#ifndef __CC_RENDERER_H_
#define __CC_RENDERER_H_

#include <vector>
#include <stack>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "platform/CCGL.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class EventListenerCustom;
class QuadCommand;
class TrianglesCommand;
class MeshCommand;

/** 
@class RenderQueue
@brief @~english Class that knows how to sort `RenderCommand` objects.
 Since the commands that have `z == 0` are "pushed back" in
 the correct order, the only `RenderCommand` objects that need to be sorted,
 are the ones that have `z < 0` and `z > 0`.
 @~chinese ���ڶ���Ⱦ��������������
 ����z=0����Ⱦ�����ͨ����ȷ��˳����뵽ĩβ��ֻ��z������0����Ⱦ������Ҫ����
*/
class RenderQueue {
public:
    /**@~english
    RenderCommand will be divided into Queue Groups.
    @~chinese 
    RenderCommand����Ϊ�����顣
    */
    enum QUEUE_GROUP
    {
        /**
        @~english Objects with globalZ smaller than 0. 
        @~chinese globalZС��0�Ķ���*/
        GLOBALZ_NEG = 0,
        /**
        @~english Opaque 3D objects with 0 globalZ. 
        @~chinese globalZ����0�Ĳ�͸��3d����*/
        OPAQUE_3D = 1,
        /**
        @~english Transparent 3D objects with 0 globalZ. 
        @~chinese globalZ����0��͸��3d����*/
        TRANSPARENT_3D = 2,
        /**
        @~english 2D objects with 0 globalZ. 
        @~chinese globalZ����0��2d����*/
        GLOBALZ_ZERO = 3,
        /**
        @~english Objects with globalZ bigger than 0. 
        @~chinese globalZ����0�Ķ���*/
        GLOBALZ_POS = 4,
        QUEUE_COUNT = 5,
    };

public:
    /**
    @~english Constructor. 
    @~chinese ���캯����
    */
    RenderQueue();
    /**
    @~english Push a renderCommand into current renderqueue. 
    @~chinese ����Ⱦ������뵽��ǰ��Ⱦ����ĩβ��
    @param command @~english The command to be pushed in to renderqueue
    @~chinese ��������Ⱦ���е����
    */
    void push_back(RenderCommand* command);
    /**
    @~english Return the number of render commands. 
    @~chinese �õ���Ⱦ�����������
    @return @~english The number of render commands @~chinese ��Ⱦ�������
    */
    ssize_t size() const;
    /**
    @~english Sort the render commands. 
    @~chinese ������Ⱦ���
    */
    void sort();
    /**
    @~english Treat sorted commands as an array, access them one by one. 
    @~chinese ����������Ⱦ�����һ�����飬�������
    @param index @~english array index for commands
    @~chinese ����ֵ
    @return @~english the RenderCommand in the given index
    @~chinese ����λ�õ���Ⱦ����

    */
    RenderCommand* operator[](ssize_t index) const;
    /**
    @~english Clear all rendered commands. 
    @~chinese ���������Ⱦ���
    */
    void clear();
    /**
    @~english Realloc command queues and reserve with given size. 
    Note: this clears any existing commands. 
    @~chinese ����ָ����С���·�����Ⱦ���С�ע��:�������κ����е����
    @param reserveSize @~english max size for command queue
    @~chinese ������е����������
    */
    void realloc(size_t reserveSize);
    /**
    @~english Get a sub group of the render queue. 
    @~chinese �õ���Ⱦ�Ӷ���
    @param group @~english group ID for the sub queque
    @~chinese ����Ⱦ���е���ID
    @return @~english render command array
    @~chinese һ����Ⱦ����
    */
    inline std::vector<RenderCommand*>& getSubQueue(QUEUE_GROUP group) { return _commands[group]; }
    /**
    @~english Get the number of render commands contained in a subqueue. 
    @~chinese �õ���Ⱦ�Ӷ����е���Ⱦ����������
    @param group @~english group ID for the sub queque
    @~chinese ����Ⱦ���е���ID
    @return @~english the number of command in sub queque
    @~chinese ����Ⱦ���е���Ⱦ����������
    */
    inline ssize_t getSubQueueSize(QUEUE_GROUP group) const { return _commands[group].size();}

    /**
    @~english Save the current DepthState, CullState, DepthWriteState render state. 
    @~chinese ���浱ǰDepthState��CullState DepthWriteState״̬��
    */
    void saveRenderState();
    /**
    @~english Restore the saved DepthState, CullState, DepthWriteState render state. 
    @~chinese �ָ������DepthState��CullState DepthWriteState״̬��*/
    void restoreRenderState();
    
protected:
    /**
    @~english The commands in the render queue. 
    @~chinese ��Ⱦ�����е����*/
    std::vector<RenderCommand*> _commands[QUEUE_COUNT];
    
    /**
    @~english Cull state. 
    @~chinese Cull״̬��
    */
    bool _isCullEnabled;
    /**
    @~english Depth test enable state. 
    @~chinese ��Ȳ���״̬��
    */
    bool _isDepthEnabled;
    /**
    @~english Depth buffer write state. 
    @~chinese ��Ȼ���д״̬��
    */
    GLboolean _isDepthWrite;
};

//the struct is not used outside.
struct RenderStackElement
{
    int renderQueueID;
    ssize_t currentIndex;
};

class GroupCommandManager;

/* 
@class Renderer
@brief @~english Class responsible for the rendering in.

Whenever possible prefer to use `QuadCommand` objects since the renderer will automatically batch them.
@~chinese ������Ⱦ���ࡣ 
���ڿ��Խ���batch��Ⱦ��������ó�����QuadCommand��
*/
class CC_DLL Renderer
{
public:
    /**
    @~english The max number of vertices in a vertex buffer object. 
    @~chinese ���㻺��������󶥵������
    */
    static const int VBO_SIZE = 65536;
    /**
    @~english The max numer of indices in a index buffer. 
    @~chinese �������������������������
    */
    static const int INDEX_VBO_SIZE = VBO_SIZE * 6 / 4;
    /**
    @~english The rendercommands which can be batched will be saved into a list, this is the reversed size of this list. 
    @~chinese ����batch����Ⱦ����ŵ�һ�������У�����������еĴ�С��
    */
    static const int BATCH_QUADCOMMAND_RESEVER_SIZE = 64;
    /**
    @~english Reserved for material id, which means that the command could not be batched. 
    @~chinese ����batch�Ĳ���ID��
    */
    static const int MATERIAL_ID_DO_NOT_BATCH = 0;
    /**
    @~english Constructor. 
    @~chinese ���캯����
    */
    Renderer();
    /**
    @~english Destructor. 
    @~chinese ����������
    */
    ~Renderer();

    //TODO: manage GLView inside Render itself
    void initGLView();

    /** 
    @~english Adds a `RenderComamnd` into the renderer  
    @~chinese ��renderer�����һ��RenderComamnd��
    @param command @~english render command to be insert
    @~chinese ���������Ⱦ���
    */
    void addCommand(RenderCommand* command);

    /** 
    @~english Adds a `RenderComamnd` into the renderer specifying a particular render queue ID  
    @~chinese ��ָ��ID����Ⱦ�����в���RenderComamnd��
    @param command @~english render command to be insert
    @~chinese ���������Ⱦ���
    @param renderQueue @~english the queue id the command queue
    @~chinese ������е�id��
    */
    void addCommand(RenderCommand* command, int renderQueue);

    /** 
    @~english Pushes a group into the render queue  
    @~chinese ��Ⱦ������ջ��
    @param renderQueueID @~english the queue id the command queue
    @~chinese ������е�id��
    */
    void pushGroup(int renderQueueID);

    /** 
    @~english Pops a group from the render queue  
    @~chinese ��Ⱦ���г�ջ��
    */
    void popGroup();

    /** 
    @~english Creates a render queue and returns its Id  
    @~chinese ����һ����Ⱦ����,����������Id
    @return @~english the id of newly created render queue.
    @~chinese �´�������Ⱦ����id��
    */
    int createRenderQueue();

    /** 
    @~english Renders into the GLView all the queued `RenderCommand` objects  
    @~chinese ִ�����б������Ⱦ���������Ⱦ��GLView�ϡ�
    */
    void render();

    /** 
    @~english Cleans all `RenderCommand`s in the queue  
    @~chinese ������������е�RenderCommand��
    */
    void clean();

    /** 
    @~english Clear GL buffer and screen  
    @~chinese ������GL�������Ļ��
    */
    void clear();

    /** 
    @~english set color for clear screen  
    @~chinese ������Ļ��յ���ɫ��
    @param clearColor @~english the clear color.
    @~chinese ��յ���ɫ��
    */
    void setClearColor(const Color4F& clearColor);
    /* 
    @~english returns the number of drawn batches in the last frame  
    @~chinese ����ͳ�����ݣ���Ⱦ��batch������
    @return @~english the number of draw batch.
    @~chinese batch���ƵĴ�����
    */
    ssize_t getDrawnBatches() const { return _drawnBatches; }
    /* 
    @~english RenderCommands (except) QuadCommand should update this value  
    @~chinese ����QuadCommand��������Ⱦ����Ӧ�ø�����Ⱦbatch���ͳ������ֵ
    @param number @~english the added number of draw batch
    @~chinese ���ӵ�batch���Ƶ���Ŀ��
    */
    void addDrawnBatches(ssize_t number) { _drawnBatches += number; };
    /* 
    @~english returns the number of drawn triangles in the last frame  
    @~chinese ����ͳ�����ݣ����Ƶ�������������
    @return @~english the number of drawn triangles
    @~chinese ���Ƶ���������Ŀ��
    */
    ssize_t getDrawnVertices() const { return _drawnVertices; }
    /* 
    @~english RenderCommands (except) QuadCommand should update this value  
    @~chinese ����QuadCommand��������Ⱦ����Ӧ�ø�����Ⱦ�Ķ���������ͳ������ֵ��
    @param number @~english the added number of draw vertices
    @~chinese ���ӵĻ��ƶ������Ŀ��
    */
    void addDrawnVertices(ssize_t number) { _drawnVertices += number; };
    /* 
    @~english clear draw stats  
    @~chinese �����Ⱦͳ��״̬��
    */
    void clearDrawStats() { _drawnBatches = _drawnVertices = 0; }

    /**@~english
     * Enable/Disable depth test
     * For 3D object depth test is enabled by default and can not be changed
     * For 2D object depth test is disabled by default
     * @~chinese 
     * ���úͲ�������Ȳ���
     * 3d����Ĭ�ϻ�������Ȳ���,���ܸı�
     * 2d����Ĭ�ϲ�������Ȳ��ԡ�

     @param enable @~english depth test enabled or not.
     @~chinese �Ƿ�������Ȳ��ԡ�
     */
    void setDepthTest(bool enable);
    
    //This will not be used outside.
    inline GroupCommandManager* getGroupCommandManager() const { return _groupCommandManager; };

    /** 
    @~english returns whether or not a rectangle is visible or not.
    @~chinese �ж�һ���������Ƿ�ɼ���
    @param transform @~english matrix for the rect. @~chinese ��������ı任����
    @param size @~english the size of rect. @~chinese �����εĴ�С��
    */
    bool checkVisibility(const Mat4& transform, const Size& size);

protected:

    //Setup VBO or VAO based on OpenGL extensions
    void setupBuffer();
    void setupVBOAndVAO();
    void setupVBO();
    void mapBuffers();
    void drawBatchedTriangles();
    void drawBatchedQuads();

    //Draw the previews queued quads and flush previous context
    void flush();
    
    void flush2D();
    
    void flush3D();

    void flushQuads();
    void flushTriangles();

    void processRenderCommand(RenderCommand* command);
    void visitRenderQueue(RenderQueue& queue);

    void fillVerticesAndIndices(const TrianglesCommand* cmd);
    void fillQuads(const QuadCommand* cmd);

    /* clear color set outside be used in setGLDefaultValues() */
    Color4F _clearColor;

    std::stack<int> _commandGroupStack;
    
    std::vector<RenderQueue> _renderGroups;

    uint32_t _lastMaterialID;

    MeshCommand*              _lastBatchedMeshCommand;
    std::vector<TrianglesCommand*> _batchedCommands;
    std::vector<QuadCommand*> _batchQuadCommands;

    //for TrianglesCommand
    V3F_C4B_T2F _verts[VBO_SIZE];
    GLushort _indices[INDEX_VBO_SIZE];
    GLuint _buffersVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _filledVertex;
    int _filledIndex;
    
    //for QuadCommand
    V3F_C4B_T2F _quadVerts[VBO_SIZE];
    GLushort _quadIndices[INDEX_VBO_SIZE];
    GLuint _quadVAO;
    GLuint _quadbuffersVBO[2]; //0: vertex  1: indices
    int _numberQuads;
    
    bool _glViewAssigned;

    // stats
    ssize_t _drawnBatches;
    ssize_t _drawnVertices;
    //the flag for checking whether renderer is rendering
    bool _isRendering;
    
    bool _isDepthTestFor2D;
    
    GroupCommandManager* _groupCommandManager;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _cacheTextureListener;
#endif
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //__CC_RENDERER_H_
