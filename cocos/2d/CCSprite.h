/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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

#ifndef __SPRITE_NODE_CCSPRITE_H__
#define __SPRITE_NODE_CCSPRITE_H__

#include <string>
#include "2d/CCNode.h"
#include "2d/CCDrawNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCCustomCommand.h"
#include "2d/CCAutoPolygon.h"

NS_CC_BEGIN

class SpriteBatchNode;
class SpriteFrame;
class Animation;
class Rect;
class Size;
class Texture2D;
struct transformValues_;

#ifdef SPRITE_RENDER_IN_SUBPIXEL
#undef SPRITE_RENDER_IN_SUBPIXEL
#endif

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define SPRITE_RENDER_IN_SUBPIXEL
#else
#define SPRITE_RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

/**
 * @addtogroup _2d
 * @{
 */

/**@~english
 * Sprite is a 2d image ( http://en.wikipedia.org/wiki/Sprite_(computer_graphics) ).
 *
 * Sprite can be created with an image, or with a sub-rectangle of an image.
 *
 * To optimize the Sprite rendering, please follow the following best practices:
 *  - Put all your sprites in the same spritesheet (http://www.codeandweb.com/what-is-a-sprite-sheet).
 *  - Use the same blending function for all your sprites.
 *  - ...and the Renderer will automatically "batch" your sprites (will draw all of them in one OpenGL call).
 *
 *  To gain an additional 5% ~ 10% more in the rendering, you can parent your sprites into a `SpriteBatchNode`.
 *  But doing so carries the following limitations:
 *
 *  - The Alias/Antialias property belongs to `SpriteBatchNode`, so you can't individually set the aliased property.
 *  - The Blending function property belongs to `SpriteBatchNode`, so you can't individually set the blending function property.
 *  - `ParallaxNode` is not supported, but can be simulated with a "proxy" sprite.
 *  - Sprites can only have other Sprites (or subclasses of Sprite) as children.
 *
 * The default anchorPoint in Sprite is (0.5, 0.5).
 * @~chinese 
 * Sprite ��һ��2Dͼ��ڵ�(http://en.wikipedia.org/wiki/Sprite_(computer_graphics) ).
 * 
 * ����ʹ��һ��ͼƬ����ͼƬ��һ���������������� Sprite ����
 * 
 * Ϊ���Ż� Sprite ����Ⱦ,����ѭ�������ʵ��:
 * - �����е� Sprite ����ͬһ�� spritesheet ��(http://www.codeandweb.com/what-is-a-sprite-sheet)��
 * - ���е� Sprite ʹ����ͬ�Ļ�Ϻ�����
 * - ��������Ⱦ���ͻ��Զ������������е� Sprite (�����е� Sprite ����һ��OpenGL��������Ⱦ����)��
 * 
 * ͨ���� Sprite ����һ�� SpriteBatchNode ���ڵ��У����Ի�ö���� 5% ~ 10% ����Ⱦ�Ż���
 * ��������������������:
 * - ֻ������ SpriteBatchNode �ڵ�ı������޷�Ϊÿ�� Sprite ���ò�ͬ�ı�����
 * - ֻ������ SpriteBatchNode �ڵ�Ļ�Ϻ������޷�Ϊÿ�� Sprite ���ò�ͬ�Ļ�Ϻ�����
 * - ��֧�� ParallaxNode�����ǿ���ʹ�ô��� Sprite ��ģ�⡣
 * - ÿ�� Sprite ���ӽڵ�ֻ���� Sprite ����������Ķ���
 * 
 * Ĭ��ê��(0.5,0.5)��
 */
class CC_DLL Sprite : public Node, public TextureProtocol
{
public:
     /** @~english Sprite invalid index on the SpriteBatchNode.  @~chinese �� SpriteBatchNode �е���Ч����ֵ��*/
    static const int INDEX_NOT_INITIALIZED = -1;

    /// @name Creators
    /// @{

    /**@~english
     * Creates an empty sprite without texture. You can call setTexture method subsequently.
     *
     * @~chinese 
     * ����һ��û������Ŀ� Sprite���������Ժ���� setTexture ������������
     * 
     * @memberof @~english Sprite
     * @~chinese Sprite
     * @return @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* create();

    /**@~english
     * Creates a sprite with an image filename.
     *
     * After creation, the rect of sprite will be the size of the image,
     * and the offset will be (0,0).
     *
     * @~chinese 
     * ʹ��һ��ͼƬ�ļ����� Sprite��
     * 
     * �����ɹ�֮��Sprite �Ĵ�С��ͼƬ��Сһ�¡�ƫ����Ϊ (0,0)��
     * 
     * @param   filename @~english A path to image file, e.g., "scene1/monster.png".
     * @~chinese ͼ���ļ���·�������磺"scene1/monster.png"
     * @return  @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* create(const std::string& filename);
    
    /** @~english
     * Creates a polygon sprite with a polygon info.
     *
     * @~chinese 
     * ʹ��һ��PolygonInfo���� Sprite��
     * 
     * @param polygonInfo @~english A specified polygon info, you can get that from AutoPolygon.
     * @~chinese һ��ָ����polygon info������Դ�AutoPolygon���ȡpolygon info.
     * @return @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* create(const PolygonInfo& info);

    /**@~english
     * Creates a sprite with an image filename and a rect.
     *
     * @~chinese 
     * ʹ��ͼƬ�ļ���ָ���ľ������򴴽�һ�� Sprite��
     * 
     * @param   filename @~english A path to image file, e.g., "scene1/monster.png".
     * @~chinese ͼ���ļ���·�������磺"scene1/monster.png"
     * @param   rect     @~english A subrect of the image file.
     * @~chinese ָ���ľ�������
     * @return  @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* create(const std::string& filename, const Rect& rect);

    /**@~english
     * Creates a sprite with a Texture2D object.
     *
     * After creation, the rect will be the size of the texture, and the offset will be (0,0).
     *
     * @~chinese 
     * ʹ��ָ���������� Sprite��
     * 
     * ������Sprite �Ĵ�С��ָ��������һ�£�����ƫ����Ϊ (0,0)��
     * 
     * @param   texture    @~english A pointer to a Texture2D object.
     * @~chinese ָ�����������
     * @return  @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* createWithTexture(Texture2D *texture);

    /**@~english
     * Creates a sprite with a texture and a rect.
     *
     * After creation, the offset will be (0,0).
     *
     * @~chinese 
     * ʹ��ָ����������������򴴽� Sprite��
     * 
     * ������ƫ����Ϊ (0,0)��
     * 
     * @param   texture     @~english A pointer to an existing Texture2D object.
     *                      You can use a Texture2D object for many sprites.
     * @~chinese ���е��������
     * һ�����������Ա���� Sprite ʹ�á�
     * @param   rect        @~english Only the contents inside the rect of this texture will be applied for this sprite.
     * @~chinese ָ���ľ�������
     * @param   rotated     @~english Whether or not the rect is rotated.
     * @~chinese �Ƿ���ת��
     * @return  @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false);

    /**@~english
     * Creates a sprite with an sprite frame.
     *
     * @~chinese 
     * ʹ�� SpriteFrame ����һ�� Sprite��
     * 
     * @param   spriteFrame    @~english A sprite frame which involves a texture and a rect.
     * @~chinese SpriteFrame ʵ����
     * @return  @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* createWithSpriteFrame(SpriteFrame *spriteFrame);

    /**@~english
     * Creates a sprite with an sprite frame name.
     *
     * A SpriteFrame will be fetched from the SpriteFrameCache by spriteFrameName param.
     * If the SpriteFrame doesn't exist it will raise an exception.
     *
     * @~chinese 
     * ʹ�� SpriteFrame ������������ Sprite��
     * 
     * ͨ��ָ�������ƴ� SpriteFrameCache ��ȡ�� SpriteFrame ����Ȼ���ʼ�� Sprite��
     * ��������� SpriteFrame ������һ���쳣��
     * 
     * @param   spriteFrameName @~english A null terminated string which indicates the sprite frame name.
     * @~chinese ָ���� SpriteFrame ���ơ�
     * @return  @~english An autoreleased sprite object.
     * @~chinese һ�� Sprite ʵ�����Ѿ��� autorelese����
     */
    static Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);

    //  end of creators group
    /// @}


    /// @{
    /// @name BatchNode methods

    /**@~english
     * Updates the quad according the rotation, position, scale values.
     * @~chinese 
     * ͨ����ת��λ���Լ����ŵ�ֵ������ Sprite �Ļ������ԡ�
     */
    virtual void updateTransform() override;

    /**@~english
     * Returns the batch node object if this sprite is rendered by SpriteBatchNode.
     *
     * @~chinese 
     * �����ǰ Sprite ͨ�� SpriteBatchNode ��Ⱦ������ SpriteBatchNode ʵ����
     * 
     * @return @~english The SpriteBatchNode object if this sprite is rendered by SpriteBatchNode,
     *         nullptr if the sprite isn't used batch node.
     * @~chinese �����ǰ Sprite ͨ�� SpriteBatchNode ��Ⱦ������ SpriteBatchNode ʵ�������򷵻� nullptr��
     */
    virtual SpriteBatchNode* getBatchNode() const;
    /**@~english
     * Sets the batch node to sprite.
     * @~chinese 
     * ������Ⱦ�� Sprite �� SpriteBatchNode ����
     * @warning @~english This method is not recommended for game developers. Sample code for using batch node
     * @code
     * SpriteBatchNode *batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 15);
     * Sprite *sprite = Sprite::createWithTexture(batch->getTexture(), Rect(0, 0, 57, 57));
     * batch->addChild(sprite);
     * layer->addChild(batch);
     * @endcode
     * @~chinese ���Ƽ�������ֱ�ӵ������������ʹ�� SpriteBatchNode ��ʾ�����룺
     * @code
     * SpriteBatchNode *batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 15);
     * Sprite *sprite = Sprite::createWithTexture(batch->getTexture(), Rect(0, 0, 57, 57));
     * batch->addChild(sprite);
     * layer->addChild(batch);
     * @endcode
     */
    virtual void setBatchNode(SpriteBatchNode *spriteBatchNode);

    /// @} end of BatchNode methods


    /// @{
    /// @name Texture / Frame methods

    /** @~english Sets a new texture (from a filename) to the sprite.
     *
     * @~chinese ����һ���µ�����ʹ��ָ�����ļ�����
     * 
     *  @memberof @~english Sprite
     *  It will call `setTextureRect()` with the texture's content size.
     * @~chinese Sprite
     * �˺������ȡ����Ĵ�С������ `setTextureRect()`
     * @param filename @~english The file path of the image file.
     * @~chinese ͼƬ�ļ���·����
     */
    virtual void setTexture(const std::string &filename );

    /** @~english @overload
     *
     *  The Texture's rect is not changed.
     * @~chinese @overload
     * 
     * ����ľ���������û�иı�ġ�
     */
    virtual void setTexture(Texture2D *texture) override;

    virtual Texture2D* getTexture() const override;

    /**@~english
     * Updates the texture rect of the Sprite in points.
     *
     * It will call `setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)` with \p rotated = false, and \p utrimmedSize = rect.size.
     * @~chinese 
     * ��������ľ�������
     * 
     * �������� `setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)` ���� \p rotated = false, \p utrimmedSize = rect.size��
     */
    virtual void setTextureRect(const Rect& rect);

    /** @~english
     * It will update the texture coordinates and the vertex rectangle.
     * @~chinese
     * ���� Sprite �Ķ���������������ꡣ
     * @param rect @~english The used rect of the texture.
     * @~chinese ʹ�õ������������
     * @param rotated @~english Whether rotate or not.
     * @~chinese �Ƿ���ת��
     * @param untrimmedSize @~english The size before trimmed.
     * @~chinese �ü�ǰ�Ĵ�С��
     */
    virtual void setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize);

    /**@~english
     * Sets the vertex rect.
     *
     * It will be called internally by setTextureRect.
     * Useful if you want to create 2x images from SD images in Retina Display.
     * Do not call it manually. Use setTextureRect instead.
     * @~chinese 
     * ���ö������ꡣ
     * 
     * �˷����� setTextureRect ���á�
     * �����Ҫ��ͼƬ�ļ����� 2x �� Retina ��Ļ��������Ҫʹ�����������
     * ��Ҫ�ֶ���������ʹ��setTextureRect�����档
     */
    virtual void setVertexRect(const Rect& rect);

    /** @{@~english
     * Sets a new SpriteFrame to the Sprite.
     * @~chinese 
     * ����һ���µ�SpriteFrame��
     */
    virtual void setSpriteFrame(const std::string &spriteFrameName);
    virtual void setSpriteFrame(SpriteFrame* newFrame);
    /** @} */

    /** @deprecated Use `setSpriteFrame()` instead. */
    CC_DEPRECATED_ATTRIBUTE virtual void setDisplayFrame(SpriteFrame *newFrame) { setSpriteFrame(newFrame); }

    /**@~english
     * Returns whether or not a SpriteFrame is being displayed.
     * @~chinese 
     * ���� SpriteFrame �Ƿ���ʾ�ˡ�
     */
    virtual bool isFrameDisplayed(SpriteFrame *frame) const;

    /**@~english
     * Returns the current displayed frame.
     * @~chinese 
     * ���ص�ǰ��ʾ�� SpriteFrame ʵ����
     */
    virtual SpriteFrame* getSpriteFrame() const;
    /** @deprecated Use `getSpriteFrame()` instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual SpriteFrame* getDisplayFrame() const { return getSpriteFrame(); }
    /** @deprecated Use `getSpriteFrame()` instead. */
    CC_DEPRECATED_ATTRIBUTE virtual SpriteFrame* displayFrame() const { return getSpriteFrame(); };

    /// @} End of frames methods


    /// @{
    /// @name Animation methods
    /**@~english
     * Changes the display frame with animation name and index.
     * The animation name will be get from the AnimationCache.
     * @~chinese 
     * ��֡������ѡȡָ����֡���ڵ�ǰ��ʾ��
     * ֡�����Ǹ������ƴ� AnimationCache ��ȡ�ġ�
     */
    virtual void setDisplayFrameWithAnimationName(const std::string& animationName, ssize_t frameIndex);
    /// @}


    /// @{
    /// @name Sprite Properties' setter/getters.

    /**@~english
     * Whether or not the Sprite needs to be updated in the Atlas.
     *
     * @~chinese 
     * Sprite�Ƿ���Ҫ��atlas������¡�
     * 
     * @return @~english True if the sprite needs to be updated in the Atlas, false otherwise.
     * @~chinese �����Ҫ���£����� true�����򷵻� false
     */
    virtual bool isDirty() const { return _dirty; }

    /**@~english
     * Makes the Sprite to be updated in the Atlas.
     * @~chinese 
     * ���� Sprite �� Atlas �Ƿ���Ҫ���¡�
     */
    virtual void setDirty(bool dirty) { _dirty = dirty; }

    /**@~english
     * Returns the quad (tex coords, vertex coords and color) information.
     * @~chinese 
     * ��ȡ Sprite �� �������꣬���������Լ���ɫ��Ϣ��
     * @js  NA
     * @lua NA
     */
    inline V3F_C4B_T2F_Quad getQuad() const { return _quad; }

    /**@~english
     * Returns whether or not the texture rectangle is rotated.
     * @~chinese 
     * ������������Ƿ���ת��
     */
    inline bool isTextureRectRotated() const { return _rectRotated; }

    /**@~english
     * Returns the index used on the TextureAtlas.
     * @~chinese 
     * ���� TextureAtlas ������ֵ��
     */
    inline ssize_t getAtlasIndex() const { return _atlasIndex; }

    /**@~english
     * Sets the index used on the TextureAtlas.
     *
     * @~chinese 
     * ���� TextureAtlas ������ֵ��
     * 
     * @warning @~english Don't modify this value unless you know what you are doing.
     * @~chinese ��Ҫ�����޸����ֵ��������֪��������ʲô��
     */
    inline void setAtlasIndex(ssize_t atlasIndex) { _atlasIndex = atlasIndex; }

    /**@~english
     * Returns the rect of the Sprite in points.
     * @~chinese 
     * ���� Sprite �ľ�������
     */
    inline const Rect& getTextureRect() const { return _rect; }

    /**@~english
     * Gets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
     * @~chinese 
     * ��ʹ�� SpriteBatchNode ������Ⱦʱ���˷������Ի�ȡʹ�õ� TextureAtlas ʵ����
     */
    inline TextureAtlas* getTextureAtlas() const { return _textureAtlas; }

    /**@~english
     * Sets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
     * @~chinese 
     * ��ʹ�� SpriteBatchNode ������Ⱦʱ��ͨ���˷�����������ʹ�õ� TextureAtlas ʵ����
     */
    inline void setTextureAtlas(TextureAtlas *textureAtlas) { _textureAtlas = textureAtlas; }

    /**@~english
     * Gets the offset position of the sprite. Calculated automatically by editors like Zwoptex.
     * @~chinese 
     * ��ȡ Sprite ��ƫ��λ�á�Zwoptex �ȱ༭�������Զ��������ֵ��
     */
    inline const Vec2& getOffsetPosition() const { return _offsetPosition; }


    /**@~english
     * Returns the flag which indicates whether the sprite is flipped horizontally or not.
     *
     * It only flips the texture of the sprite, and not the texture of the sprite's children.
     * Also, flipping the texture doesn't alter the anchorPoint.
     * If you want to flip the anchorPoint too, and/or to flip the children too use:
     * sprite->setScaleX(sprite->getScaleX() * -1);
     *
     * @~chinese 
     * ���� Sprite �Ƿ�ˮƽ��ת��
     * 
     * ��ֻ��ת��ǰ Sprite ��������Ӱ���ӽڵ㡣
     * ���⣬��ת�����ı�ê�㡣
     * ������뷭תê�㣬����/���߷�ת�ӽڵ㣬��ʹ�ã�
     * sprite->setScaleX(sprite->getScaleX() * -1);
     * 
     * @return @~english true if the sprite is flipped horizontally, false otherwise.
     * @~chinese �����ˮƽ��ת������ true�����򷵻� false��
     */
    bool isFlippedX() const;
    /**@~english
     * Sets whether the sprite should be flipped horizontally or not.
     *
     * @~chinese 
     * �����Ƿ����ˮƽ��ת��
     * 
     * @param flippedX @~english true if the sprite should be flipped horizontally, false otherwise.
     * @~chinese true ��ʾҪˮƽ��ת�������ʾ��ˮƽ��ת��
     */
    void setFlippedX(bool flippedX);

    /** @deprecated Use isFlippedX() instead.
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated Use setFlippedX() instead
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flippedX) { setFlippedX(flippedX); };

    /**@~english
     * Return the flag which indicates whether the sprite is flipped vertically or not.
     *
     * It only flips the texture of the sprite, and not the texture of the sprite's children.
     * Also, flipping the texture doesn't alter the anchorPoint.
     * If you want to flip the anchorPoint too, and/or to flip the children too use:
     * sprite->setScaleY(sprite->getScaleY() * -1);
     *
     * @~chinese 
     * �����Ƿ�ֱ��ת��
     * 
     * ��ֻ��ת��ǰ Sprite ��������Ӱ���ӽڵ㡣
     * ���⣬����ת���ı�ê�㡣
     * ������뷭תê�㣬����/���߷�ת�ӽڵ㣬��ʹ�ã�
     * sprite->setScaleY(sprite->getScaleY() * -1);
     * 
     * @return @~english true if the sprite is flipped vertically, false otherwise.
     * @~chinese ����Ǵ�ֱ��ת���� true�����򷵻� false��
     */
    bool isFlippedY() const;
    /**@~english
     * Sets whether the sprite should be flipped vertically or not.
     *
     * @~chinese 
     * �����Ƿ���д�ֱ��ת��
     * 
     * @param flippedY @~english true if the sprite should be flipped vertically, false otherwise.
     * @~chinese true ��ʾҪ��ֱ��ת�������ʾ����ֱ��ת��
     */
    void setFlippedY(bool flippedY);

    /// @} End of Sprite properties getter/setters

    /** @deprecated Use isFlippedY() instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated Use setFlippedY() instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flippedY) { setFlippedY(flippedY); };

    //
    // Overrides
    //
    /// @{
    /// @name Functions inherited from TextureProtocol.
    /**
     * @~english
     * @code
     * When this function bound into js or lua,the parameter will be changed.
     * In js: var setBlendFunc(var src, var dst).
     * In lua: local setBlendFunc(local src, local dst).
     * @endcode
     * @~chinese 
     * @code
     * ����������󶨵�js��lua,���������ı䡣
     * ��js ��: var setBlendFunc(var src, var dst)��
     * ��lua��: local setBlendFunc(local src, local dst)��
     * @endcode
    */
    inline void setBlendFunc(const BlendFunc &blendFunc) override { _blendFunc = blendFunc; }
    /**
    * @js  NA
    * @lua NA
    */
    inline const BlendFunc& getBlendFunc() const override { return _blendFunc; }
    /// @}

    /**
     * @js NA
     */
    virtual std::string getDescription() const override;

    /// @{
    /// @name Functions inherited from Node.
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual void setScale(float scaleX, float scaleY) override;
    /**
    * @js  NA
    * @lua NA
    */
    virtual void setPosition(const Vec2& pos) override;
    virtual void setPosition(float x, float y) override;
    virtual void setRotation(float rotation) override;
    virtual void setRotationSkewX(float rotationX) override;
    virtual void setRotationSkewY(float rotationY) override;
    virtual void setSkewX(float sx) override;
    virtual void setSkewY(float sy) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void reorderChild(Node *child, int zOrder) override;
    using Node::addChild;
    virtual void addChild(Node *child, int zOrder, int tag) override;
    virtual void addChild(Node *child, int zOrder, const std::string &name) override;
    virtual void sortAllChildren() override;
    virtual void setScale(float scale) override;
    virtual void setPositionZ(float positionZ) override;
    virtual void setAnchorPoint(const Vec2& anchor) override;
    virtual void ignoreAnchorPointForPosition(bool value) override;
    virtual void setVisible(bool bVisible) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void setOpacityModifyRGB(bool modify) override;
    virtual bool isOpacityModifyRGB() const override;
    /// @}

CC_CONSTRUCTOR_ACCESS:
	/**
     * @js ctor
     */
    Sprite();
    virtual ~Sprite();

    /* @~english Initializes an empty sprite with nothing init.  @~chinese ��ʼ��һ���յ�Sprite��*/
    virtual bool init() override;

    /**@~english
     * Initializes a sprite with a texture.
     *
     * After initialization, the rect used will be the size of the texture, and the offset will be (0,0).
     *
     * @~chinese 
     * ʹ��ָ���������ʼ��һ��Sprite��
     * 
     * ��ʼ����Sprite �Ĵ�С������һ�£�ƫ����Ϊ (0,0)��
     * 
     * @param   texture    @~english A pointer to an existing Texture2D object.
     *                      You can use a Texture2D object for many sprites.
     * @~chinese ���е� Texture2D �����ָ�롣һ��������Ա���� Sprite ʹ�á�
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    virtual bool initWithTexture(Texture2D *texture);
    
    
    /**
     * Initializes a sprite with a PolygonInfo.
     *
     * After initialization, the rect used will be the size of the texture, and the offset will be (0,0).
     *
     * @param   PolygonInfo    a Polygon info contains the structure of the polygon.
     * @return  True if the sprite is initialized properly, false otherwise.
     */
    virtual bool initWithPolygon(const PolygonInfo& info);

    /**@~english
     * Initializes a sprite with a texture and a rect.
     *
     * After initialization, the offset will be (0,0).
     *
     * @~chinese 
     * ʹ��ָ������������������ʼ��һ�� Sprite��
     * 
     * ��ʼ����ƫ����Ϊ (0,0)��
     * 
     * @param   texture    @~english A pointer to an exisiting Texture2D object.
     *                      You can use a Texture2D object for many sprites.
     * @~chinese ���е� Texture2D �����ָ�롣һ��������Ա���� Sprite ʹ�á�
     * @param   rect        @~english Only the contents inside rect of this texture will be applied for this sprite.
     * @~chinese ��Ҫ��ָ���������н�ȡ�ľ�������
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    virtual bool initWithTexture(Texture2D *texture, const Rect& rect);

    /**@~english
     * Initializes a sprite with a texture and a rect in points, optionally rotated.
     *
     * After initialization, the offset will be (0,0).
     * @~chinese 
     * ʹ��ָ������������������Ƿ���ת��ʼ��һ��Sprite��
     * 
     * ��ʼ����ƫ����Ϊ (0,0)��
     * @note    @~english This is the designated initializer.
     *
     * @~chinese �����ض��ĳ�ʼ��������
     * 
     * @param   texture    @~english A Texture2D object whose texture will be applied to this sprite.
     * @~chinese ���е� Texture2D �����ָ�롣
     * @param   rect        @~english A rectangle assigned the contents of texture.
     * @~chinese ��Ҫ��ָ���������н�ȡ�ľ�������
     * @param   rotated     @~english Whether or not the texture rectangle is rotated.
     * @~chinese �Ƿ���ת����
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    virtual bool initWithTexture(Texture2D *texture, const Rect& rect, bool rotated);

    /**@~english
     * Initializes a sprite with an SpriteFrame. The texture and rect in SpriteFrame will be applied on this sprite.
     *
     * @~chinese 
     * ʹ��ָ���� SpriteFrame ��ʼ��һ�� Sprite��
     * 
     * @param   spriteFrame  @~english A SpriteFrame object. It should includes a valid texture and a rect.
     * @~chinese SpriteFrame ����������һ����Ч������;�������
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    virtual bool initWithSpriteFrame(SpriteFrame *spriteFrame);

    /**@~english
     * Initializes a sprite with an sprite frame name.
     *
     * A SpriteFrame will be fetched from the SpriteFrameCache by name.
     * If the SpriteFrame doesn't exist it will raise an exception.
     *
     * @~chinese 
     * ʹ��ָ���� SpriteFrame ���Ƴ�ʼ��һ�� Sprite��
     * 
     * ���ȴ� SpriteFrameCache �л�ȡָ�����Ƶ� SpriteFrame��
     * Ȼ��ʹ����� SpriteFrame ��ʼ�� Sprite��
     * 
     * @param   spriteFrameName  @~english A key string that can fected a valid SpriteFrame from SpriteFrameCache.
     * @~chinese һ���ַ��������ڴ� SpriteFrameCache �л�ȡ SpriteFrame ����
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    virtual bool initWithSpriteFrameName(const std::string& spriteFrameName);

    /**@~english
     * Initializes a sprite with an image filename.
     *
     * This method will find filename from local file system, load its content to Texture2D,
     * then use Texture2D to create a sprite.
     * After initialization, the rect used will be the size of the image. The offset will be (0,0).
     *
     * @~chinese 
     * ʹ��ָ����ͼƬ�ļ���ʼ��һ�� Sprite��
     * 
     * �÷������ӱ����ļ�ϵͳ���ҵ��ļ����������Ϊ Texture2D ����
     * Ȼ��ʹ�� Texture2D �����ʼ�� Sprite��
     * ��ʼ����Sprite ��С��ͼƬ��Сһ�£�ƫ����Ϊ (0,0)��
     * 
     * @param   filename @~english The path to an image file in local file system.
     * @~chinese ͼƬ�ļ���·����
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     * @lua     init
     */
    virtual bool initWithFile(const std::string& filename);

    /**@~english
     * Initializes a sprite with an image filename, and a rect.
     *
     * This method will find filename from local file system, load its content to Texture2D,
     * then use Texture2D to create a sprite.
     * After initialization, the offset will be (0,0).
     *
     * @~chinese 
     * ʹ��ָ��ͼƬ�ļ����ض����������ʼ��һ�� Sprite��
     * 
     * �÷������ӱ����ļ�ϵͳ���ҵ��ļ����������Ϊ Texture2D ����
     * Ȼ��ʹ�� Texture2D �����ʼ�� Sprite��
     * ��ʼ����Sprite ��С��ͼƬ��Сһ�£�ƫ����Ϊ (0,0)��
     * 
     * @param   filename @~english The path to an image file in local file system.
     * @~chinese ͼƬ�ļ���·����
     * @param   rect        @~english The rectangle assigned the content area from texture.
     * @~chinese ��Ҫ��ͼƬ�н�ȡ�ľ�������
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     * @lua     init
     */
    virtual bool initWithFile(const std::string& filename, const Rect& rect);
    
    /**
     * returns a copy of the polygon information associated with this sprite
     * because this is a copy process it is slower than getting the reference, so use wisely
     *
     * @return a copy of PolygonInfo
     */
    PolygonInfo getPolygonInfo() const;
    
    /**
     * set the sprite to use this new PolygonInfo
     *
     * @param PolygonInfo the polygon information object
     */
    void setPolygonInfo(const PolygonInfo& info);
protected:

    void updateColor() override;
    virtual void setTextureCoords(Rect rect);
    virtual void updateBlendFunc();
    virtual void setReorderChildDirtyRecursively();
    virtual void setDirtyRecursively(bool value);


    
    //
    // Data used when the sprite is rendered using a SpriteSheet
    //
    TextureAtlas*       _textureAtlas;      /// SpriteBatchNode texture atlas (weak reference)
    ssize_t             _atlasIndex;        /// Absolute (real) Index on the SpriteSheet
    SpriteBatchNode*    _batchNode;         /// Used batch node (weak reference)

    bool                _dirty;             /// Whether the sprite needs to be updated
    bool                _recursiveDirty;    /// Whether all of the sprite's children needs to be updated
    bool                _shouldBeHidden;    /// should not be drawn because one of the ancestors is not visible
    Mat4              _transformToBatch;

    //
    // Data used when the sprite is self-rendered
    //
    BlendFunc        _blendFunc;            /// It's required for TextureProtocol inheritance
    Texture2D*       _texture;              /// Texture2D object that is used to render the sprite
    SpriteFrame*     _spriteFrame;
    TrianglesCommand _trianglesCommand;     ///
#if CC_SPRITE_DEBUG_DRAW
    DrawNode *_debugDrawNode;
#endif //CC_SPRITE_DEBUG_DRAW
    //
    // Shared data
    //

    // texture
    Rect _rect;                             /// Rectangle of Texture2D
    bool   _rectRotated;                    /// Whether the texture is rotated

    // Offset Position (used by Zwoptex)
    Vec2 _offsetPosition;
    Vec2 _unflippedOffsetPositionFromCenter;

    // vertex coords, texture coords and color info
    V3F_C4B_T2F_Quad _quad;
    PolygonInfo  _polyInfo;

    // opacity and RGB protocol
    bool _opacityModifyRGB;

    // image is flipped
    bool _flippedX;                         /// Whether the sprite is flipped horizontally or not
    bool _flippedY;                         /// Whether the sprite is flipped vertically or not

    bool _insideBounds;                     /// whether or not the sprite was inside bounds the previous frame
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Sprite);
};


// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPRITE_NODE_CCSPRITE_H__
