/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
Copyright (c) 2009      Matt Oswald
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CC_SPRITE_BATCH_NODE_H__
#define __CC_SPRITE_BATCH_NODE_H__

#include <vector>

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCBatchCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */


class Sprite;

/** @~english SpriteBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *
 * A SpriteBatchNode can reference one and only one texture (one image file, one texture atlas).
 * Only the Sprites that are contained in that texture can be added to the SpriteBatchNode.
 * All Sprites added to a SpriteBatchNode are drawn in one OpenGL ES draw call.
 * If the Sprites are not added to a SpriteBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.
 *
 *
 * Limitations:
 *  - The only object that is accepted as child (or grandchild, grand-grandchild, etc...) is Sprite or any subclass of Sprite. eg: particles, labels and layer can't be added to a SpriteBatchNode.
 *  - Either all its children are Aliased or Antialiased. It can't be a mix. This is because "alias" is a property of the texture, and all the sprites share the same texture.
 *
 * @~chinese SpriteBatchNode ��������ڵ�:����������ӽڵ㣬����ͨ��һ�� OpenGL ���û��������ӽڵ㡣
 * (ͨ������Ϊ����������ơ�)��
 * 
 * һ�� SpriteBatchNode ��������һ����ֻ��һ������(һ��ͼ���ļ�, ����һ�������ͼ��)��
 * ֻ�е� Sprite ʹ�õ������� SpriteBatchNode һ��ʱ�������Ϊ SpriteBatchNode ���ӽڵ㡣
 * ������ӵ� SpriteBatchNode ���ӽڵ��ͨ��һ�� OpenGL ����ȫ�����Ƴ�����
 * ��� Sprite û����ӵ� SpriteBatchNode����ôһ�� OpenGL ����ֻ�ܻ���һ�� Sprite������Ч���Ǻܵ͵ġ�
 * 
 * 
 * ����:
 * - ֻ�� Sprite ���� Sprite �����ʵ�������������Ϊ SpriteBatchNode ���ӽڵ㡣���磺particle��label �� layer ������Ϊ SpriteBatchNode ���ӽڵ㡣
 * - ���е��ӽڵ�Ҫô���б�����Ҫô��û�б��������ܻ��ʹ�á���Ϊ������������������ԣ������е��ӽڵ㹲��ͬһ������
 * 
 * @since v0.7.1
 */
class CC_DLL SpriteBatchNode : public Node, public TextureProtocol
{
    static const int DEFAULT_CAPACITY = 29;

public:
    /** @~english Creates a SpriteBatchNode with a texture2d and capacity of children.
     * The capacity will be increased in 33% in runtime if it runs out of space.
     *
     * @~chinese ʹ��ָ�����������ӽڵ���������һ�� SpriteBatchNode��
     * ������й�������ӵ��ӽڵ�������ָ�������ޣ����������� 33%%��
     * 
     * @param tex @~english A texture2d.
     * @~chinese ָ��������ʵ����
     * @param capacity @~english The capacity of children.
     * @~chinese �ӽڵ��������ޡ�
     * @return @~english Return an autorelease object.
     * @~chinese ����һ�� SpriteBatchNode ʵ�����ѱ� autorelease ����
     */
    static SpriteBatchNode* createWithTexture(Texture2D* tex, ssize_t capacity = DEFAULT_CAPACITY);

    /** @~english Creates a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
     * The capacity will be increased in 33% in runtime if it runs out of space.
     * The file will be loaded using the TextureMgr.
     *
     * @~chinese ʹ��ָ����ͼƬ�ļ���.png��.jpeg��.pvr�ȣ����ӽڵ����޴���һ�� SpriteBatchNode��
     * ������й�������ӵ��ӽڵ�������ָ�������ޣ����������� 33%%��
     * ͼƬ�ļ���ͨ�� TextureMgr ���ء�
     * 
     * @param fileImage @~english A file image (.png, .jpeg, .pvr, etc).
     * @~chinese ͼƬ�ļ�·����.png��.jpeg��.pvr�ȣ���
     * @param capacity @~english The capacity of children.
     * @~chinese �ӽڵ��������ޡ�
     * @return @~english Return an autorelease object.
     * @~chinese ����һ�� SpriteBatchNode ʵ�����ѱ� autorelease ����
     */
    static SpriteBatchNode* create(const std::string& fileImage, ssize_t capacity = DEFAULT_CAPACITY);


    /** @~english Returns the TextureAtlas object. 
     *
     * @~chinese ��ȡʹ�õ� TextureAtlas ʵ����
     * 
     * @return @~english The TextureAtlas object.
     * @~chinese TextureAtlas ʵ����
     */
    inline TextureAtlas* getTextureAtlas() { return _textureAtlas; }

    /** @~english Sets the TextureAtlas object. 
     *
     * @~chinese ���� TextureAtlas ʵ����
     * 
     * @param textureAtlas @~english The TextureAtlas object.
     * @~chinese TextureAtlas ʵ����
     */
    inline void setTextureAtlas(TextureAtlas* textureAtlas)
    { 
        if (textureAtlas != _textureAtlas)
        {
            CC_SAFE_RETAIN(textureAtlas);
            CC_SAFE_RELEASE(_textureAtlas);
            _textureAtlas = textureAtlas;
        }
    }

    /** @~english Returns an array with the descendants (children, gran children, etc.).
     * This is specific to BatchNode. In order to use the children, use getChildren() instead.
     * 
     * @~chinese ���ذ����ӽڵ����������ӽڵ�����飨�ӽڵ㣬�ӽڵ���ӽڵ�...����
     * ���� SpriteBatchNode �Ķ��ƽӿڡ����Ҫ��ȡ�ӽڵ㣬��ʹ�� getChildren()��
     * 
     * @return @~english An array with the descendants (children, gran children, etc.).
     * @~chinese �����ӽڵ����������ӽڵ�����顣
     */
    inline const std::vector<Sprite*>& getDescendants() const { return _descendants; }

    /** @~english Increase the Atlas Capacity.  @~chinese ���� Atlas ���������ޡ�*/
    void increaseAtlasCapacity();

    /** @~english Removes a child given a certain index. It will also cleanup the running actions depending on the cleanup parameter.
     *
     * @~chinese ɾ��ָ������ֵ���ӽڵ㡣����ͨ������ doCleanup ָ���Ƿ������ӽڵ���ص� action��
     * 
     * @param index @~english A certain index.
     * @~chinese ��Ҫɾ�����ӽڵ�����ֵ��
     * @param doCleanup @~english Whether or not to cleanup the running actions.
     * @~chinese �Ƿ�Ҫ�����ӽڵ���ص� action��
     * @warning @~english Removing a child from a SpriteBatchNode is very slow.
     * @~chinese �� SpriteBatchNode ɾ���ӽڵ�Ƚ�����
     */
    void removeChildAtIndex(ssize_t index, bool doCleanup);
    
    /** @~english Append the child. 
     *
     * @~chinese �����ӽڵ㡣
     * 
     * @param sprite @~english A Sprite.
     * @~chinese ��Ҫ���ӵ��ӽڵ㡣
     */
    void appendChild(Sprite* sprite);
    
    /** @~english Remove a sprite from Atlas. 
     *
     * @~chinese �� Atlas ��ɾ��һ�� Sprite��
     * 
     * @param sprite @~english A Sprite.
     * @~chinese ��Ҫɾ���� Sprite��
     */
    void removeSpriteFromAtlas(Sprite *sprite);
    
    /** @~english Rebuild index with a sprite all child. 
     *
     * @~chinese ���¹��������ӽڵ��������
     * 
     * @param parent @~english The parent sprite.
     * @~chinese ��Ҫ���µ� Sprite��
     * @param index @~english The child index.
     * @~chinese ��Ҫ���µ�����ֵ
     * @return @~english Index.
     * @~chinese ���ظ��º������ֵ
     */
    ssize_t rebuildIndexInOrder(Sprite *parent, ssize_t index);
    
    /** @~english Get the Max image block index,in all child.
     *
     * @~chinese ��ȡ�����ӽڵ��У�Atlas ���������ֵ��
     * 
     * @param sprite @~english The parent sprite.
     * @~chinese ���ڵ�
     * @return @~english Index.
     * @~chinese ����ֵ
     */
    ssize_t highestAtlasIndexInChild(Sprite *sprite);
    
    /** @~english Get the Min image block index,in all child. 
     *
     * @~chinese ��ȡ�����ӽڵ��У�Atlas ����С����ֵ��
     * 
     * @param sprite @~english The parent sprite.
     * @~chinese ���ڵ�
     * @return @~english Index.
     * @~chinese ����ֵ
     */
    ssize_t lowestAtlasIndexInChild(Sprite *sprite);
    
    /** @~english Get the nearest index from the sprite in z.
     *
     * @~chinese ��ȡ��ָ���� z ֵ��ӽ��� Atlas ����ֵ��
     * 
     * @param sprite @~english The parent sprite.
     * @~chinese ���ڵ�
     * @param z @~english Z order for drawing priority.
     * @~chinese ���ƻ���˳��� z ֵ
     * @return @~english Index.
     * @~chinese ����ֵ
     */
    ssize_t atlasIndexForChild(Sprite *sprite, int z);
    /* @~english Sprites use this to start sortChildren, don't call this manually.  @~chinese ����ʹ�����sortChildren��ʼ,����֮Ϊ�ֶ���*/
    void reorderBatch(bool reorder);

    //
    // Overrides
    //
    // TextureProtocol
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;

    /**
     * @js NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void addChild(Node * child, int zOrder, const std::string &name) override;
    virtual void reorderChild(Node *child, int zOrder) override;
        
	virtual void removeChild(Node *child, bool cleanup) override;
    /**
     * @js NA
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
	virtual void sortAllChildren() override;
	/**
	* @js NA
	*/
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	/**
	* @js NA
	*/
    virtual std::string getDescription() const override;

    /** @~english Inserts a quad at a certain index into the texture atlas. The Sprite won't be added into the children array.
     * This method should be called only when you are dealing with very big AtlasSprite and when most of the Sprite won't be updated.
     * For example: a tile map (TMXMap) or a label with lots of characters (LabelBMFont).
     * @~chinese ��ָ���� Sprite �����ȡ Atlas ���ݲ����뵽ָ��������ֵλ�ã�Sprite ���󲻻ᱻ���Ϊ�ӽڵ㡣
     * ֻ�е���Ҫ����ܴ�� AtlasSprite �������д󲿷� Sprite ��������µ���������Ե������������
     * ���磺һ�� tile map(TMXMap) ���߰����ܶ��ַ��� label (LableBMFont)��
     */
    void insertQuadFromSprite(Sprite *sprite, ssize_t index);
    /* @~english This is the opposite of "addQuadFromSprite".
     * It add the sprite to the children and descendants array, but it doesn't update add it to the texture atlas
     * @~chinese ������ "addQuadFromSprite" �෴�ķ���.
     * �˷����� Sprite ��ӵ��ӽڵ��У����ǲ�������� Atlas ���ݡ�
     */
    SpriteBatchNode * addSpriteWithoutQuad(Sprite *child, int z, int aTag);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    SpriteBatchNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteBatchNode();
    
    /** @~english initializes a SpriteBatchNode with a texture2d and capacity of children.
     The capacity will be increased in 33% in runtime if it runs out of space.
     * @~chinese ʹ��ָ�����������ӽڵ��������޳�ʼ��һ�� SpriteBatchNode��
     * ������й�������ӵ��ӽڵ�������ָ�������ޣ����������� 33%%��
     */
    bool initWithTexture(Texture2D *tex, ssize_t capacity = DEFAULT_CAPACITY);
    /** @~english initializes a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and a capacity of children.
     The capacity will be increased in 33% in runtime if it runs out of space.
     The file will be loaded using the TextureMgr.
     * @~chinese ʹ��ָ����ͼƬ�ļ���.png��.jpeg��.pvr�ȣ����ӽڵ����޳�ʼ��һ�� SpriteBatchNode��
     * ������й�������ӵ��ӽڵ�������ָ�������ޣ����������� 33%%��
     * ͼƬ�ļ���ͨ�� TextureMgr ���ء�
     * @js init
     * @lua init
     */
    bool initWithFile(const std::string& fileImage, ssize_t capacity = DEFAULT_CAPACITY);
    bool init() override;
    
protected:
    /** Updates a quad at a certain index into the texture atlas. The Sprite won't be added into the children array.
     This method should be called only when you are dealing with very big AtlasSprite and when most of the Sprite won't be updated.
     For example: a tile map (TMXMap) or a label with lots of characters (LabelBMFont)
     */
    void updateQuadFromSprite(Sprite *sprite, ssize_t index);   

    void updateAtlasIndex(Sprite* sprite, ssize_t* curIndex);
    void swap(ssize_t oldIndex, ssize_t newIndex);
    void updateBlendFunc();

    TextureAtlas *_textureAtlas;
    BlendFunc _blendFunc;
    BatchCommand _batchCommand;     // render command

    // all descendants: children, grand children, etc...
    // There is not need to retain/release these objects, since they are already retained by _children
    // So, using std::vector<Sprite*> is slightly faster than using cocos2d::Array for this particular case
    std::vector<Sprite*> _descendants;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_SPRITE_BATCH_NODE_H__
