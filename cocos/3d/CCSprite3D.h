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

#ifndef __CCSPRITE3D_H__
#define __CCSPRITE3D_H__

#include <unordered_map>

#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCGLProgramState.h"
#include "3d/CCSkeleton3D.h" // need to include for lua-binding
#include "3d/CCAABB.h"
#include "3d/CCBundle3DData.h"
#include "3d/CCMeshVertexIndexData.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

class Mesh;
class Texture2D;
class MeshSkin;
class AttachNode;
struct NodeData;

/** @class Sprite3D
    @brief @~english a sprite3D can be loaded from 3D model files, .obj, .c3t, .c3b, then can be drawed as sprite
    @~chinese һ��sprite3D���Դ�3Dģ���ļ��� OBJ�� .c3t �� .c3b�б����أ�Ȼ��Ϳ�������һ��������
*/
class CC_DLL Sprite3D : public Node, public BlendProtocol
{
public:
    /** @~english  Creates an empty sprite3D without 3D model and texture.
        @~chinese ����һ���յ�Sprite3Dû��3Dģ�ͺ�����
        @return @~english an autoreleased sprite3D object. @~chinese һ���Զ��ͷŵ�Sprite3D����
    */
    static Sprite3D* create();

    /** @~english creates a Sprite3D
        @~chinese ����һ��Sprite3D
        @return @~english an autoreleased sprite3D object. @~chinese һ���Զ��ͷŵ�Sprite3D����
    */
    static Sprite3D* create(const std::string& modelPath);

    /** @~english creates a Sprite3D. It only supports one texture, and overrides the internal texture with 'texturePath'
        @~chinese ����һ��Sprite3D����ֻ֧��һ����������д�ڲ������texturepath��
        @return @~english an autoreleased sprite3D object. @~chinese һ���Զ��ͷŵ�Sprite3D����
    */
    static Sprite3D* create(const std::string& modelPath, const std::string& texturePath);

    /** @~english create 3d sprite asynchronously
        If the 3d model was previously loaded, it will create a new 3d sprite and the callback will be called at once.
        Otherwise it will load the model file in a new thread, and when the 3d sprite is loaded, the callback will be called with the created Sprite3D and a userdefined parameter.
        The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
        @~chinese �첽����3D����
        �����άģ���Ѿ������أ�������������һ���µ�3D���鲢�һص��ᱻ����һ�Ρ�
        �������һ���µ��̼߳���ģ���ļ���һ��������ɣ�����ִ�лص���������ʹ���´�����ģ�ͺ��Զ�����û�������Ϊ������
        ����ص��������̵߳��ã�����ڻص������д����κε�cocos2d�����ǰ�ȫ�ġ�
        @param modelPath @~english  model to be loaded @~chinese �����ص�ģ��
        @param callback @~english  callback after loading @~chinese ������ɺ�Ļص�����
        @param callbackparam @~english  user defined parameter for the callback @~chinese �û�����Ĳ���
    */
    static void createAsync(const std::string& modelPath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam);

    static void createAsync(const std::string& modelPath, const std::string& texturePath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam);

    /** @~english set texture, set the first if multiple textures exist
        @~chinese ��������ֻ���õ�һ���������������Ĵ���
    */
    void setTexture(const std::string& texFile);

    /** @~english set texture, set the first if multiple textures exist
        @~chinese ��������ֻ���õ�һ���������������Ĵ���
    */
    void setTexture(Texture2D* texture);

    /** @~english get Mesh by index
        @~chinese ͨ�������õ�����
        @param index @~english  the specified index of a mesh @~chinese һ����������ָ������
        @return @~english a mesh in the specified index @~chinese ָ��������
    */
    Mesh* getMeshByIndex(int index) const;

    /** @~english get Mesh by Name, it returns the first one if there are more than one mesh with the same name
        @~chinese ͨ�����Ƶõ����������ص�һ������ж��������ͬ���Ƶ�����
        @param name @~english  the specified name of a mesh @~chinese һ��ָ��������
        @return @~english a mesh with the specified name @~chinese ����ָ�����Ƶ�����
    */
    Mesh* getMeshByName(const std::string& name) const;

    /** @~english get mesh array by name
        @~chinese ͨ�����Ƶõ��������
        @param name @~english  the specified name of mesh @~chinese ָ��������
        @return @~english all meshes with the given name @~chinese �����������������е�����
        @lua NA
    */
    std::vector<Mesh*> getMeshArrayByName(const std::string& name) const;

    /** @~english get mesh
        @~chinese �õ�����
        @return @~english a mesh a index 0 @~chinese ��������0
    */
    Mesh* getMesh() const { return _meshes.at(0); }

    /** @return @~english mesh count @~chinese �õ����������
    */
    ssize_t getMeshCount() const { return _meshes.size(); }

    /** @return @~english the skin @~chinese �õ�Ƥ��
    */
    CC_DEPRECATED_ATTRIBUTE MeshSkin* getSkin() const;

    /** @return @~english the skeleton of sprite3d @~chinese �õ�Sprite3D�ĹǼ�
    */
    Skeleton3D* getSkeleton() const { return _skeleton; }

    /** @~english get AttachNode by bone name
        @~chinese �õ�attachnodeͨ������������
        @param boneName @~english  the bone name @~chinese ����������
        @return @~english AttachNode of the bone, nullptr if not exist @~chinese ������������ڷ���nullptr
    */
        AttachNode* getAttachNode(const std::string& boneName);

    /** @~english remove attach node of a bone
        @~chinese ɾ�����������ӵ�attach node
        @param boneName @~english  the bone name @~chinese �ǵ�����
    */
    void removeAttachNode(const std::string& boneName);

    /** @~english remove all attach nodes
        @~chinese ɾ���������ӽڵ�
    */
    void removeAllAttachNode();

    /** @~english set the blend methods for all meshes
        @~chinese ������������Ļ�Ϸ���
        @param blendFunc @~english  the new blendFunc object @~chinese ��blendfunc����
    */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;

    /** @~english get the blend method
        @~chinese �õ���ϵķ���
        @return @~english the blendFunc object @~chinese blendfunc����
    */
    virtual const BlendFunc& getBlendFunc() const override;

    // overrides
    /** @~english set GLProgramState, you should bind attributes by yourself
        @~chinese ����glprogramstate����Ӧ���Լ�������
        @param glProgramState @~english  the new GLProgramState to render with @~chinese �µ�glprogramstate
    */
    virtual void setGLProgramState(GLProgramState* glProgramState) override;

    /** @~english set GLProgram, you should bind attributes by yourself
        @~chinese ����glprogram����Ӧ���Լ�������
        @param glprogram @~english  the new glprogram to render with @~chinese �µ�glprogram
    */
    virtual void setGLProgram(GLProgram* glprogram) override;

    /** @~english Get AABB
        @~chinese �õ�AABB
        @warning If the sprite has animation, it can't be calculated accuratly,
        because bone can drive the vertices, we just use the origin vertices
        to calculate the AABB.
        @return @~english the AABB object @~chinese AABB����
    */
    const AABB& getAABB() const;

    /** @~english Get AABB Recursively,it will merge the aabb its own and all descendants
        @~chinese �ݹ�õ�AABB(�ݹ�ĺϲ������亢�ӵ�AABB)
        @warning Because some times we may have an empty Sprite3D Node as parent, but
        the Sprite3D don't contain any meshes, so getAABB()
        will return a wrong value at that time.
        @return @~english the AABB object @~chinese AABB����
    */
    AABB getAABBRecursively();

    /** @~english  Executes an action, and returns the action that is executed. For Sprite3D special logic are needed to take care of Fading.
        This node becomes the action's target. Refer to Action::getTarget()
        @~chinese ִ��һ��action
        @warning Actions don't retain their target.
        @param action @~english  the action will be excuted @~chinese ����ִ�е�action
        @return @~english An Action pointer @~chinese һ��action��ָ��
    */
    virtual Action* runAction(Action* action) override;

    /** @~english  Force to write to depth buffer, this is useful if you want to achieve effects like fading.
        @~chinese ǿ��д����Ȼ��������������ʹ�õ���Ч����������Ҳ����Ч��
        @param value @~english  the switching vale of method @~chinese �������л���
    */
    void setForceDepthWrite(bool value) { _forceDepthWrite = value; }

    /** @~english whether force to write to depth buffer
        @~chinese �Ƿ�ǿ��д����Ȼ�����
        @return @~english the switching vale of method @~chinese �������л���
    */
    bool isForceDepthWrite() const { return _forceDepthWrite;};

    /** @~english  Returns 2d bounding-box
        @~chinese ���ض�ά��Χ��
        @warning the bouding-box is just get from the AABB which as Z=0, so that is not very accurate.
        @return @~english the rect of boundingbox @~chinese ��Χ�еľ��ο�
    */
    virtual Rect getBoundingBox() const override;

    /** @~english set which face is going to cull, default GL_BACK
        @~chinese �����ĸ��潫Ҫ���޳���Ĭ��gl_back
        @param cullFace @~english  which face is going to cull, GL_BACK, GL_FRONT, GL_FRONT_AND_BACK @~chinese �ĸ��潫Ҫ���޳���gl_back��gl_front��gl_front_and_back
    */
    void setCullFace(GLenum cullFace);

    /** @~english set cull face enable or not
        @~chinese �����Ƿ������޳�
        @param enable @~english  the switching vale of method @~chinese �Ƿ��޳�
    */
    void setCullFaceEnabled(bool enable);

    /** @~english light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff
        @~chinese ���õƹ�����
        @param mask @~english  the lightmask @~chinese �ƹ�����
    */
    void setLightMask(unsigned int mask) { _lightMask = mask; }

    /** @~english light mask getter & setter, light works only when _lightmask & light's flag is true, default value of _lightmask is 0xffff
        @~chinese ���صƹ�����
        @return @~english the lightmask @~chinese �ƹ�����
    */
    unsigned int getLightMask() const { return _lightMask; }

    /** @~english draw
        @~chinese ��
    */
    virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;

    /** @~english Adds a new material to the sprite.
        The Material will be applied to all the meshes that belong to the sprite.
        Internally it will call `setMaterial(material,-1)`
        @~chinese ���������һ���µĲ���
        @param material @~english  the material to be applied @~chinese ���ϱ�Ӧ��
    */
    void setMaterial(Material* material);

    /** @~english Adds a new material to a particular mesh of the sprite.
        meshIndex is the mesh that will be applied to.
        if meshIndex == -1, then it will be applied to all the meshes that belong to the sprite.
        @~chinese �������һ��ָ����������Ӳ���
        @param material @~english  the material to be applied @~chinese ����ӵĲ���
        @param meshIndex @~english  the mesh index of whom want to apply the material @~chinese ��Ӳ��ʵ����������
    */
    void setMaterial(Material* material, int meshIndex);

    /** @~english Get material of a particular mesh of the sprite.
        meshIndex is the mesh that will be applied to.
        if meshIndex == -1, then it will be applied to all the meshes that belong to the sprite.
        @~chinese �����һ��ָ��������Ĳ���
        @param meshIndex @~english  the mesh index @~chinese ��������
        @return @~english the material of given mesh index @~chinese ָ�����Ĳ���
    */
    Material* getMaterial(int meshIndex) const;
    
    /**
    * force set this Sprite3D to 2D render queue
    */
    void setForce2DQueue(bool force2D);

CC_CONSTRUCTOR_ACCESS:

    Sprite3D();
    virtual ~Sprite3D();

    virtual bool init() override;

    bool initWithFile(const std::string& path);

    bool initFrom(const NodeDatas& nodedatas, const MeshDatas& meshdatas, const MaterialDatas& materialdatas);

    /**load sprite3d from cache, return true if succeed, false otherwise*/
    bool loadFromCache(const std::string& path);

    /** load file and set it to meshedatas, nodedatas and materialdatas, obj file .mtl file should be at the same directory if exist */
    bool loadFromFile(const std::string& path, NodeDatas* nodedatas, MeshDatas* meshdatas,  MaterialDatas* materialdatas);

    /** Visits this Sprite3D's children and draw them recursively.
        Note: all its children will rendered as 3D objects
    */
    virtual void visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

    /**generate default material*/
    void genMaterial(bool useLight = false);

    void createNode(NodeData* nodedata, Node* root, const MaterialDatas& matrialdatas, bool singleSprite);
    void createAttachSprite3DNode(NodeData* nodedata,const MaterialDatas& matrialdatas);
    Sprite3D* createSprite3DNode(NodeData* nodedata,ModelData* modeldata,const MaterialDatas& matrialdatas);

    /**get MeshIndexData by Id*/
    MeshIndexData* getMeshIndexData(const std::string& indexId) const;

    void addMesh(Mesh* mesh);

    void onAABBDirty() { _aabbDirty = true; }

    void afterAsyncLoad(void* param);

    static AABB getAABBRecursivelyImp(Node *node);
    
protected:

    Skeleton3D*                  _skeleton; //skeleton

    Vector<MeshVertexData*>      _meshVertexDatas;

    std::unordered_map<std::string, AttachNode*> _attachments;

    BlendFunc                    _blend;

    Vector<Mesh*>              _meshes;

    mutable AABB                 _aabb;                 // cache current aabb
    mutable Mat4                 _nodeToWorldTransform; // cache the matrix
    mutable bool                 _aabbDirty;
    unsigned int                 _lightMask;
    bool                         _shaderUsingLight; // is current shader using light ?
    bool                         _forceDepthWrite; // Always write to depth buffer
    bool                         _usingAutogeneratedGLProgram;

    struct AsyncLoadParam
    {
        std::function<void(Sprite3D*, void*)> afterLoadCallback; // callback after load
        void*                           callbackParam;
        bool                            result; // sprite load result
        std::string                     modlePath;
        std::string                     texPath; //
        MeshDatas* meshdatas;
        MaterialDatas* materialdatas;
        NodeDatas*   nodeDatas;
    };
    AsyncLoadParam             _asyncLoadParam;
};

///////////////////////////////////////////////////////
/** @class Sprite3DCache
    @brief @~english the cache data of Sprite3D, use to speed up Sprite3D::create
    @~chinese һ�����������������Sprite3D�Ĵ���
*/
class CC_DLL Sprite3DCache
{
public:
    struct Sprite3DData
    {
        Vector<MeshVertexData*>   meshVertexDatas;
        Vector<GLProgramState*>   glProgramStates;
        NodeDatas*      nodedatas;
        MaterialDatas*  materialdatas;
        ~Sprite3DData()
        {
            if (nodedatas)
                delete nodedatas;
            if (materialdatas)
                delete materialdatas;
            meshVertexDatas.clear();
            glProgramStates.clear();
        }
    };

    /** @~english get the instance of this object
        @~chinese ��ô˶����ʵ��
        @return @~english the instance of this object @~chinese �˶����ʵ��
    */
    static Sprite3DCache* getInstance();

    /** @~english destroy the instance
        @~chinese ����ʵ��
    */
    static void destroyInstance();

    /** @~english get the SpriteData struct
        @~chinese �õ�spritedata�ṹ
        @param key @~english  the key of sprite3DData @~chinese sprite3ddata��key
        @return @~english the Sprite3DData @~chinese sprite3ddata����
        @lua NA
    */
    Sprite3DData* getSpriteData(const std::string& key) const;

    /** @~english  add the SpriteData into Sprite3D by given the specified key
        @~chinese ���spritedata��Sprite3Dͨ��ָ���Ĺؼ���
        @param key @~english  the key of sprite3DData @~chinese sprite3ddata�Ĺؼ���
        @param spritedata @~english  the spritedata to add @~chinese Ҫ��ӵ�spritedata
        @return @~english Whether or not the operation is successful @~chinese �����Ƿ�ɹ�
        @lua NA
    */
    bool addSprite3DData(const std::string& key, Sprite3DData* spritedata);

    /** @~english remove the SpriteData from Sprite3D by given the specified key
        @~chinese ɾ��spritedata��Sprite3Dͨ��ָ����
        @param key @~english  the key of sprite3DData @~chinese sprite3ddata�ļ�
    */
    void removeSprite3DData(const std::string& key);

    /** @~english remove all the SpriteData from Sprite3D
        @~chinese ��Sprite3Dɾ������spritedata
    */
    void removeAllSprite3DData();

CC_CONSTRUCTOR_ACCESS:
    Sprite3DCache();
    ~Sprite3DCache();

protected:

    static Sprite3DCache*                        _cacheInstance;
    std::unordered_map<std::string, Sprite3DData*> _spriteDatas; //cached sprite data
};

// end of 3d group
/// @}

NS_CC_END
#endif // __SPRITE3D_H_
