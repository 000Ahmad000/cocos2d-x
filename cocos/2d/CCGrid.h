/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (C) 2013-2014 Chukong Technologies Inc.
 
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
#ifndef __EFFECTS_CCGRID_H__
#define __EFFECTS_CCGRID_H__

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

class Texture2D;
class Grabber;
class GLProgram;
class Node;

/**
 * @addtogroup _2d
 * @{
 */

/** @~english Base class for Other grid.
 * @~chinese ����������Ļ��ࡣ
*/
class CC_DLL GridBase : public Ref
{
public:
    /**
     * @~english create one Grid  @~chinese ����һ������
     *
     * @param gridSize @~english The grid size @~chinese ����Ĵ�С
     * @param texture @~english The texture pointer. @~chinese һ������ָ��
     * @param flipped @~english Whether texture flipped or not. @~chinese �Ƿ�������Ҫ��ת
     *
     * @return @~english A GridBase instance. @~chinese һ��GridBaseʵ��
     */
    static GridBase* create(const Size& gridSize, Texture2D *texture, bool flipped);

    /**
     * @~english create one Grid  @~chinese ����һ������
     *
     * @param gridSize @~english The gride size. @~chinese ����Ĵ�С
     *
     * @return @~english A GridBase instance. @~chinese һ��GridBaseʵ��
     */
    static GridBase* create(const Size& gridSize);
    /**@~english
     * Destructor.
     * @~chinese 
     * ����������
     * @js NA
     * @lua NA
     */
    virtual ~GridBase(void);

    /**@~english
     *Init the Grid base.
     * @~chinese 
     * ��ʼ��������ࡣ
     @param gridSize @~english the size of the grid.
     * @~chinese ����Ĵ�С��
     @param texture @~english The texture used for grab.
     * @~chinese ��ץȡ������
     @param flipped @~english whether or not the grab texture should be flip by Y or not.
     * @~chinese �Ƿ�Ӧ����Y�᷽��ת��ץȡ������
     * @return @~english True if initailize success, false otherwise. @~chinese �����ʼ���ɹ����򷵻��棬���򷵻ؼ١�
     */
    bool initWithSize(const Size& gridSize);
    bool initWithSize(const Size& gridSize, const Rect& rect);
    bool initWithSize(const Size& gridSize, Texture2D *texture, bool flipped);
    bool initWithSize(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect);

    /**@}*/
    /** @{
    Getter and setter of the active state of the grid.
     */
    /** @~english
     * Get the active state of grid.
     * @~chinese 
     * ��ȡ����Ļ״̬��
     */
    inline bool isActive(void) const { return _active; }
    /**
     * @~english Set the active state of grid.
     * @~chinese ��������Ļ״̬
     *
     * @param active @~english true if the grid is active, false otherwise @~chinese ��������ڻ״̬���򷵻��棬���򷵻ؼ١�
     */
    void setActive(bool active);

    /** @~english Get number of times that the grid will be reused.  @~chinese ��ȡ���񽫱����õĴ�����*/
    inline int getReuseGrid(void) const { return _reuseGrid; }
    /** @~english Set number of times that the grid will be reused.  @~chinese �������񽫱����õĴ�����*/
    inline void setReuseGrid(int reuseGrid) { _reuseGrid = reuseGrid; }

    /** @~english Get the size of the grid.  @~chinese ��ȡ����Ĵ�С��*/
    inline const Size& getGridSize(void) const { return _gridSize; }
    /**@~english Set the size of the grid. @~chinese ��������Ĵ�С*/
    inline void setGridSize(const Size& gridSize) { _gridSize = gridSize; }

    /** @~english Pixels between the grids.  @~chinese ��ȡ����֮������ء�*/
    inline const Vec2& getStep(void) const { return _step; }
    /**@~english Get the pixels between the grids. @~chinese ��������֮������ء�*/
    inline void setStep(const Vec2& step) { _step = step; }

    /** @~english is texture flipped.  @~chinese �����Ƿ�ת��*/
    inline bool isTextureFlipped(void) const { return _isTextureFlipped; }
    /**@~english Set the texture flipped or not. @~chinese ���������Ƿ�ת��*/
    void setTextureFlipped(bool flipped);
    
    /**@~english
     * Init and reset the Grid status before draw.
     * @~chinese 
     * �ڻ���ǰ��������ʼ����������Ⱦ�����״̬��
     */
    void beforeDraw(void);
    /**
     * @~english  Init and reset the Grid status before draw.
     * @~chinese �ڻ��ƺ�������ʼ����������Ⱦ�����״̬
     *
     * @param target @~english A Node pointer. @~chinese һ��Node�ڵ�ָ��
     */
    void afterDraw(Node *target);

    /**@~english
     * Interface for custom action when before blit.
     * @~chinese 
     * ��Blitǰ���������ƶ���
     * @js NA
     */
    virtual void beforeBlit() {}
    /**
     * @~english Interface for custom action when after blit.
     * @~chinese ��Blit���������ƶ���
     */
    virtual void afterBlit() {}

    /**@~english Used to blit the texture with grid to screen. @~chinese ���ڿ�������������ͼ����Ļ��*/
    virtual void blit(void);
    /**@~english Reuse the grid vertices. @~chinese �������񶥵㡣*/
    virtual void reuse(void);
    /**@~english Calculate the vertices used for the blit. @~chinese ��������blit�Ķ��㡣*/
    virtual void calculateVertexPoints(void);
    
    /**@~english Change projection to 2D for grabbing. @~chinese �ı�ͶӰΪץס2 d��*/
    void set2DProjection(void);
    
    /**
     * @brief Set the effect grid rect.
     * @param rect The effect grid rect.
     */
    void setGridRect(const Rect& rect);
    /**
     * @brief Get the effect grid rect.
     * @return Return the effect grid rect.
     */
    inline const Rect& getGridRect() const {return _gridRect;}

protected:
    bool _active;
    int  _reuseGrid;
    Size _gridSize;
    Texture2D *_texture;
    Vec2 _step;
    Grabber *_grabber;
    bool _isTextureFlipped;
    GLProgram* _shaderProgram;
    Director::Projection _directorProjection;
    Rect _gridRect;
};

/**@~english
 * Grid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 * @~chinese 
 * Grid3D��һ��3D����ʵ�֡�ÿ�����㶼������ά��:x,y,z
 */
class CC_DLL Grid3D : public GridBase
{
public:
    /**
     * @~english create one Grid  @~chinese ����һ������
     *
     * @param gridSize @~english The grid size @~chinese ����Ĵ�С
     * @param texture @~english The texture pointer. @~chinese һ������ָ��
     * @param flipped @~english Whether texture flipped or not. @~chinese �Ƿ�������Ҫ��ת
     *
     * @return @~english A Grid3D instance. @~chinese һ��Grid3Dʵ��
     */
    static Grid3D* create(const Size& gridSize);
    static Grid3D* create(const Size& gridSize, const Rect& rect);
    static Grid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    static Grid3D* create(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect);

    /**@~english
     * Constructor.
     * @~chinese 
     * ���캯����
     * @js ctor
     */
    Grid3D();
    /**@~english
     * Destructor.
     * @~chinese 
     * ����������
     * @js NA
     * @lua NA
     */
    ~Grid3D(void);

    /** @~english Returns the vertex at a given position.
     * @~chinese ����һ��������λ�õĶ��㡣
     * @js NA
     * @lua NA
     */
    Vec3 getVertex(const Vec2& pos) const;
    /** @deprecated Use getVertex() instead 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 vertex(const Vec2& pos) const { return getVertex(pos); }
    /** @~english Returns the original (non-transformed) vertex at a given position.
     * @~chinese ����һ��������λ�õ�ԭʼ��(û�о�������任��)���㡣
     * @js NA
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& pos) const;
    /** @deprecated Use getOriginalVertex() instead 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 originalVertex(const Vec2& pos) const { return getOriginalVertex(pos); }

    /** @~english Sets a new vertex at a given position.
     * @~chinese ��һ��������λ��������һ���µĶ��㡣
     * @lua NA
     */
    void setVertex(const Vec2& pos, const Vec3& vertex);
    /**@~english
     * Implementations for interfaces in base calss.
     * @~chinese 
     * ʵ��Grid�����һЩ�ӿ�
     */
    virtual void beforeBlit() override;
    virtual void afterBlit() override;
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;

    /**@~english
     * Set the depth test state when blit.
     * @~chinese 
     * ����blit����Ȳ���״̬��
     @js NA
     */
    void setNeedDepthTestForBlit( bool neededDepthTest) { _needDepthTestForBlit = neededDepthTest; }
    /**
     * @~english Get the depth test state when blit.
     * @~chinese ��ȡblit����Ȳ���״̬
     *
     * @return @~english Return true if depth test is enabled, false otherwise. @~chinese �����Ȳ����ǿ����ģ��򷵻��棬���򷵻ؼ١�
     */
    bool getNeedDepthTestForBlit() const { return _needDepthTestForBlit; }
protected:
    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLvoid *_originalVertices;
    GLushort *_indices;
    bool _needDepthTestForBlit;
    bool _oldDepthTestValue;
    bool _oldDepthWriteValue;
};

/**@~english
 * TiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 * the tiles can be separated from the grid.
 * @~chinese 
 * TiledGrid3D��һ��3D����ʵ�֡�����ͬ��Grid3D,
 * ÿһ����Ƭ(tile)���Զ���������
*/
class CC_DLL TiledGrid3D : public GridBase
{
public:
    /**
     * @~english Create one Grid.  @~chinese ����һ������
     *
     * @param gridSize @~english The grid size. @~chinese ����Ĵ�С
     * @param texture @~english A texture2D pointer. @~chinese һ������ָ��
     * @param flipped @~english Whether the texture is flipped or not. @~chinese �Ƿ�����Ӧ�÷�ת��
     *
     * @return @~english A TiledGrid3D instance. @~chinese һ�� TiledGrid3D ʵ����
     */
    static TiledGrid3D* create(const Size& gridSize);
    static TiledGrid3D* create(const Size& gridSize, const Rect& rect);
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect);
=======
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize);
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize, const Rect& rect);
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect);

    /**@~english
     * Constructor.
     * @~chinese 
     * ���캯����
     * @js ctor
     */
    TiledGrid3D();
    /**@~english
     * Destructor.
     * @~chinese 
     * ����������
     * @js NA
     * @lua NA
     */
    ~TiledGrid3D();

    /** @~english Returns the tile at the given position.
     * @~chinese ���ظ���λ�õ���Ƭ��
     * @js NA
     * @lua NA
     */
    Quad3 getTile(const Vec2& pos) const;
    /** @~english returns the tile at the given position 
     * @~chinese ���ظ���λ�õ���Ƭ.
     * @deprecated Use getTile instead.
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& pos) const { return getTile(pos); }
    /** @~english Returns the original tile (untransformed) at the given position.
     * @~chinese ���ظ���λ�õ�û�о�������任����Ƭ��
     * @js NA
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& pos) const;
    /** @~english returns the original tile (untransformed) at the given position 
     * @~chinese ���ظ���λ�õ�û�о�������任����Ƭ��
     * @deprecated use getOriginalTile instead.
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& pos) const { return getOriginalTile(pos); }

    /** @~english Sets a new tile.
     * @~chinese ����һ���µ���Ƭ��
     * @lua NA
     */
    void setTile(const Vec2& pos, const Quad3& coords);

    /**@~english
     * Implementations for interfaces in base calss.
     * @~chinese 
     * ʵ��Grid�����һЩ�ӿڡ�
     */
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;
protected:
    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLvoid *_originalVertices;
    GLushort *_indices;
};

// end of effects group
/// @}

NS_CC_END

#endif // __EFFECTS_CCGRID_H__
