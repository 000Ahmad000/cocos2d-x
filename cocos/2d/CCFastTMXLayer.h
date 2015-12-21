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
#ifndef __CC_FAST_TMX_LAYER_H__
#define __CC_FAST_TMX_LAYER_H__

#include <map>
#include <unordered_map>
#include "2d/CCNode.h"
#include "2d/CCTMXXMLParser.h"
#include "renderer/CCPrimitiveCommand.h"
#include "base/CCMap.h"

NS_CC_BEGIN

class TMXMapInfo;
class TMXLayerInfo;
class TMXTilesetInfo;
class Texture2D;
class Sprite;
struct _ccCArray;

namespace experimental{

/**
 * @addtogroup _2d
 * @{
 */

/** @brief @~english FastTMXLayer represents the TMX layer.

 * It is a subclass of SpriteBatchNode. By default the tiles are rendered using a TextureAtlas.
 * If you modify a tile on runtime, then, that tile will become a Sprite, otherwise no Sprite objects are created.
 * The benefits of using Sprite objects as tiles are:
 * - tiles (Sprite) can be rotated/scaled/moved with a nice API.

 * If the layer contains a property named "cc_vertexz" with an integer (in can be positive or negative),
 * then all the tiles belonging to the layer will use that value as their OpenGL vertex Z for depth.

 * On the other hand, if the "cc_vertexz" property has the "automatic" value, then the tiles will use an automatic vertex Z value.
 * Also before drawing the tiles, GL_ALPHA_TEST will be enabled, and disabled after drawing them. The used alpha func will be:

 * glAlphaFunc( GL_GREATER, value ).

 * "value" by default is 0, but you can change it from Tiled by adding the "cc_alpha_func" property to the layer.
 * The value 0 should work for most cases, but if you have tiles that are semi-transparent, then you might want to use a different
 * value, like 0.5.
 
 * For further information, please see the programming guide:
 * http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:tiled_maps
 
 * @~chinese FastTMXLayer������ʾTMX layer��
 * �̳���SpriteBatchNode��tilesĬ��ʹ��TextureAtlas������Ⱦ��
 * �������ʱ�޸�һ��tile����ôtile�����һ��Sprite����֮���򲻻���Sprite���󱻴�����
 * ʹ��Sprite������ΪTile�ĺô���:
 * -  tiles(��Sprite)����ͨ�����Ƶ�API������ת/����/�ƶ�
 * ���layer����һ��������Ϊ"cc_vertexz"������(������/������)����ô����layer��tiles��ʹ�ø�����ֵ��Ϊ����OpenGL������Ⱦ��ʾ��ε�Zֵ��
 * ����,�����cc_vertexz������ֵΪ��automatic������ô��Щtiles��ʹ��һ���Է����Zֵ��
 * �ڻ�����Щtilesʱ���ڻ���ǰ����������GL_ALPHA_TESTΪ���ã����ƺ�����Ϊ���á�ʹ�õ�Alpha�������£�
 * glAlphaFunc( GL_GREATER, value ).
 * ��value��Ĭ��Ϊ0,���������ͨ�������ӡ�cc_alpha_func���������ı��ֵ.
 * ��������value��ֵ��0���������Щtiles�ǰ�͸���ģ���ô��ֵ����ܻ�������ͬ������0.5��
 * ��һ������Ϣ,��μ����ָ��(ע���������Ѳ�����):
 * http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:tiled_maps
 * 
 * @since v3.2
 * @js NA
 */

class CC_DLL TMXLayer : public Node
{
public:
    /** @~english Creates a FastTMXLayer with an tileset info, a layer info and a map info.
     *
     * @~chinese ͨ��ָ��TMXTilesetInfo,TMXLayerInfo��TMXMapInfo����һ��TMXLayer
     * 
     * @param tilesetInfo @~english An tileset info.
     * @~chinese TMXTilesetInfo����.
     * @param layerInfo @~english A layer info.
     * @~chinese TMXLayerInfo����.
     * @param mapInfo @~english A map info.
     * @~chinese TMXMapInfo����.
     * @return @~english An autorelease object.
     * @~chinese һ��autorelease����.
     */
    static TMXLayer * create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    /**
     * @js ctor
     */
    TMXLayer();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXLayer();

    /** @~english Returns the tile gid at a given tile coordinate. It also returns the tile flags.
     * 
     * @~chinese ͨ����������Ƭ���ꡢflags����ѡ��������ƬGID.
     * �÷���Ҫ����Ƭ��ͼ֮ǰû�б��ͷŹ�(�磺û�е��ù�layer->releaseMap()).
     * 
     * @param tileCoordinate @~english The tile coordinate.
     * @~chinese ��Ƭ����.
     * @param flags @~english Tile flags.
     * @~chinese ��Ƭflags.
     * @return @~english Returns the tile gid at a given tile coordinate. It also returns the tile flags.
     * @~chinese ���ع���������Ƭ���ꡢflags����ѡ������ƬGID.
     */
    int getTileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags = nullptr);

    /** @~english Sets the tile gid (gid = tile global id) at a given tile coordinate.
     * The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
     * If a tile is already placed at that position, then it will be removed.
     * @~chinese ���ø����������Ƭ��gid(gid =��Ƭȫ��id)
     * ��ƬGID����ʹ�÷�����tileGIDAt������ã���ʹ��TMX�༭�� -> Tileset Mgr +1�õ�.
     * �����λ��������һ��tile����ô��λ�������е�tile���ᱻ�Ƴ���
     * 
     * @param gid @~english The tile gid.
     * @~chinese ��Ƭgid.
     * @param tileCoordinate @~english The tile coordinate.
     * @~chinese ��Ƭ����.
     */
    void setTileGID(int gid, const Vec2& tileCoordinate);

    /** @~english Sets the tile gid (gid = tile global id) at a given tile coordinate.
     * The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
     * If a tile is already placed at that position, then it will be removed.
     * Use withFlags if the tile flags need to be changed as well.
     *
     * @~chinese ���ø������ꡢflags����Ƭ��gid(gid =��Ƭȫ��id)
     * ��ƬGID����ʹ�÷�����tileGIDAt������ã���ʹ��TMX�༭�� -> Tileset Mgr +1.
     * ���һ����Ƭ�Ѿ������Ǹ�λ��,��ô������ɾ��.
     * ʹ��flags�����Ƭflags��Ҫ����.
     * 
     * @param gid @~english The tile gid.
     * @~chinese ��Ƭgid.
     * @param tileCoordinate @~english The tile coordinate.
     * @~chinese ��Ƭ����.
     * @param flags @~english The tile flags.
     * @~chinese ��Ƭ��flags.
     */
    void setTileGID(int gid, const Vec2& tileCoordinate, TMXTileFlags flags);

    /** @~english Removes a tile at given tile coordinate.
     *
     * @~chinese ɾ��ָ�������ϵ���Ƭ.
     * 
     * @param tileCoordinate @~english The tile coordinate.
     * @~chinese ��Ƭ����.
     */
    void removeTileAt(const Vec2& tileCoordinate);

    /** @~english Returns the position in points of a given tile coordinate.
     *
     * @~chinese ��ȡָ�������λ��(�Ե�Ϊ��λ)
     * 
     * @param tileCoordinate @~english The tile coordinate.
     * @~chinese ��Ƭ����.
     * @return @~english The position in points of a given tile coordinate.
     * @~chinese ������Ƭ������λ��.
     */
    Vec2 getPositionAt(const Vec2& tileCoordinate);

    /** @~english Return the value for the specific property name.
     *
    * @~chinese ��ȡָ��������(propertyName)��ֵ
     * 
     * @param propertyName @~english The specific property name.
     * @~chinese �ض���������.
     * @return @~english Return the value for the specific property name.
     * @~chinese ����ָ��������(propertyName)��ֵ.
     */
    Value getProperty(const std::string& propertyName) const;

    /** @~english Creates the tiles.  @~chinese ������Ƭ��*/
    void setupTiles();
    
    /** @~english Get the tile layer name.
     *
     * @~chinese ��ȡ�������.
     * 
     * @return @~english The layer name.
     * @~chinese �������.
     */
    inline const std::string& getLayerName(){ return _layerName; }
    
    /** @~english Set the tile layer name.
     *
     * @~chinese ���ò������.
     * 
     * @param layerName @~english The layer name.
     * @~chinese �������.
     */
    inline void setLayerName(const std::string& layerName){ _layerName = layerName; }

    /** @~english Size of the layer in tiles.
     *
     * @~chinese ��ȡ��ĳߴ�.
     * 
     * @return @~english Size of the layer in tiles.
     * @~chinese ��Ƭ��ĳߴ�.
     */
    inline const Size& getLayerSize() const { return _layerSize; };
    
    /** @~english Set the size of the layer in tiles. 
     *
     * @~chinese ���ò���Ƭ��ĳߴ�.
     * 
     * @param size @~english Size of the layer in tiles.
     * @~chinese ��Ƭ��ĳߴ�.
     */
    inline void setLayerSize(const Size& size) { _layerSize = size; };
    
    /** @~english Size of the map's tile (could be different from the tile's size).
     *
     * @~chinese ��ȡ��Ƭ�ĳߴ�(��Ƭ�ĳߴ���ܻ�������ͬ).
     * 
     * @return @~english The size of the map's tile.
     * @~chinese ��Ƭ�ĳߴ�(��Ƭ�ĳߴ���ܻ�������ͬ).
     */
    inline const Size& getMapTileSize() const { return _mapTileSize; };
    
    /** @~english Set the size of the map's tile. 
     *
     * @~chinese ������Ƭ�ĳߴ�.
     * 
     * @param size @~english The size of the map's tile.
     * @~chinese ��Ƭ�ĳߴ�.
     */
    inline void setMapTileSize(const Size& size) { _mapTileSize = size; };
    
    /** @~english Pointer to the map of tiles.
     * @~chinese ��ȡָ��tiles��ͼ��ָ��.
     *
     * @return @~english Pointer to the map of tiles.
     * @~chinese ָ��tiles��ͼ��ָ��.
     *
     * @js NA
     * @lua NA
     */
    const uint32_t* getTiles() const { return _tiles; };
    
    /** @~english Set the pointer to the map of tiles.
     *
     * @~chinese ����ָ��tiles��ͼ��ָ�롣
     * 
     * @param tiles @~english A pointer to the map of tiles.
     * @~chinese ָ��tiles��ͼ��ָ��
     */
    void setTiles(uint32_t* tiles) { _tiles = tiles; _quadsDirty = true;};
    
    /** @~english Tileset information for the layer.
     *
     * @~chinese ��ȡ���tileset��Ϣ��
     * 
     * @return @~english Tileset information for the layer.
     * @~chinese ���tileset��Ϣ��
     */
    inline TMXTilesetInfo* getTileSet() const { return _tileSet; };
    
    /** @~english Set the tileset information for the layer. 
     *
     * @~chinese ����layer��Tileset��Ϣ
     * 
     * @param info @~english The tileset information for the layer.
     * @~chinese layer��Tileset��Ϣ
     */
    inline void setTileSet(TMXTilesetInfo* info) {
        CC_SAFE_RETAIN(info);
        CC_SAFE_RELEASE(_tileSet);
        _tileSet = info;
    };
    
    /** @~english Layer orientation, which is the same as the map orientation.
     *
     * @~chinese  ��ȡLayer����(ͬ��ͼ����)
     * 
     * @return @~english Layer orientation, which is the same as the map orientation.
     * @~chinese  Layer����(ͬ��ͼ����)
     */
    inline int getLayerOrientation() const { return _layerOrientation; };
    
    /** @~english Set Layer orientation, which is the same as the map orientation. 
     *
     * @~chinese ���� Layer����(ͬ��ͼ����)
     * 
     * @param orientation @~english Layer orientation,which is the same as the map orientation.
     * @~chinese  Layer����(ͬ��ͼ����)
     */
    inline void setLayerOrientation(int orientation) { _layerOrientation = orientation; };
    
    /** @~english Properties from the layer. They can be added using Tiled. 
     *
     * @~chinese ��ȡlayer�����ԣ����Ա�����Tile���
     * 
     * @return @~english Properties from the layer. They can be added using Tiled.
     * @~chinese layer������
     */
    inline const ValueMap& getProperties() const { return _properties; };
    
    /** @~english Properties from the layer. They can be added using Tiled.
     *
     * @~chinese ��ȡlayer�����ԣ����Ա�����Tile���
     * 
     * @return @~english Properties from the layer. They can be added using Tiled.
     * @~chinese layer������
     */
    inline ValueMap& getProperties() { return _properties; };
    
    /** @~english Set the properties to the layer.
     *
     * @~chinese ���ò�����.
     * 
     * @param properties @~english It is used to set the layer Properties.
     * @~chinese ������������ͼ�������.
     */
    inline void setProperties(const ValueMap& properties)
    {
        _properties = properties;
    };

    /** @~english Returns the tile (Sprite) at a given a tile coordinate.
     * The returned Sprite will be already added to the TMXLayer. Don't add it again.
     * The Sprite can be treated like any other Sprite: rotated, scaled, translated, opacity, color, etc.
     * You can remove either by calling:
     * - layer->removeChild(sprite, cleanup);
     *
     * @~chinese  ͨ��ָ����tile�����ȡ��Ӧ��tile(Sprite)��
     * ���ص�tile(Sprite)Ӧ���Ѿ���ӵ�TMXLayer���벻Ҫ�ظ���ӡ�
     * ���tile(Sprite)��ͬ������Spriteһ����������ת�����š���ת��͸������������ɫ�ȡ�
     * �����ͨ���������·�������������ɾ��:
     * - layer->removeChild(sprite, cleanup);
     * 
     * @param tileCoordinate @~english A tile coordinate.
     * @~chinese ��Ƭ����.
     * @return @~english Returns the tile (Sprite) at a given a tile coordinate.
     * @~chinese ����ָ������λ�õ���Ƭ(Sprite).
     */
    Sprite* getTileAt(const Vec2& tileCoordinate);
    
    /** @~english Set an sprite to the tile,with the tile coordinate and gid.
     *
     * @~chinese ����һ����Ƭ��sprite��
     * 
     * @param sprite @~english A Sprite.
     * @~chinese һ��Sprite��
     * @param pos @~english The tile coordinate.
     * @~chinese ��Ƭ���ꡣ
     * @param gid @~english The tile gid.
     * @~chinese ��Ƭgid��
     */
    void setupTileSprite(Sprite* sprite, Vec2 pos, int gid);

    //
    // Override
    //
    virtual std::string getDescription() const override;
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    void removeChild(Node* child, bool cleanup = true) override;

protected:

    bool initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    void updateTiles(const Rect& culledRect);
    Vec2 calculateLayerOffset(const Vec2& offset);

    /* @~english The layer recognizes some special properties, like cc_vertez  @~chinese ����ʶ��һЩ���������,����cc_vertez*/
    void parseInternalProperties();
    
    Mat4 tileToNodeTransform();
    Rect tileBoundsForClipTransform(const Mat4 &tileToClip);
    
    int getVertexZForPos(const Vec2& pos);
    
    //Flip flags is packed into gid
    void setFlaggedTileGIDByIndex(int index, int gid);
    
    //
    void updateTotalQuads();
    
    void onDraw(Primitive* primitive);
    inline int getTileIndexByPos(int x, int y) const { return x + y * (int) _layerSize.width; }
    
    void updateVertexBuffer();
    void updateIndexBuffer();
    void updatePrimitives();
protected:
    
    //! name of the layer
    std::string _layerName;

    /** @~english size of the layer in tiles  @~chinese ����ƬΪ��λ�Ĳ�Ĵ�С*/
    Size _layerSize;
    /** @~english size of the map's tile (could be different from the tile's size)  @~chinese ��ͼ��Ƭ�Ĵ�С(��Ƭ�Ĵ�С���ܻ�������ͬ)*/
    Size _mapTileSize;
    /** @~english pointer to the map of tiles  @~chinese ָ���ͼ��Ƭ��ָ��*/
    uint32_t* _tiles;
    /** @~english Tileset information for the layer  @~chinese ȷ����Ϣ��*/
    TMXTilesetInfo* _tileSet;
    /** @~english Layer orientation, which is the same as the map orientation  @~chinese ��ȡ��,����һ���ĵ�ͼ��λ*/
    int _layerOrientation;
    /** @~english properties from the layer. They can be added using Tiled  @~chinese The properties from the layer. They can be added using Tiled*/
    ValueMap _properties;

    Texture2D *_texture;
    
    /** @~english container for sprite children. map<index, pair<sprite, gid> >  @~chinese Container for Sprite children. The map < index, pair < Sprite, gid > >*/
    std::map<int, std::pair<Sprite*, int> > _spriteContainer;

    //GLuint _buffersVBO; //0: vertex, 1: indices

    Size _screenGridSize;
    Rect _screenGridRect;
    int _screenTileCount;
    
    int _vertexZvalue;
    bool _useAutomaticVertexZ;
    
    /** @~english tile coordinate to node coordinate transform  @~chinese ��שЭ���ڵ�����任*/
    Mat4 _tileToNodeTransform;
    /** @~english data for rendering  @~chinese ���ݳ���*/
    bool _quadsDirty;
    std::vector<int> _tileToQuadIndex;
    std::vector<V3F_C4B_T2F_Quad> _totalQuads;
    std::vector<GLushort> _indices;
    std::map<int/*vertexZ*/, int/*offset to _indices by quads*/> _indicesVertexZOffsets;
    std::unordered_map<int/*vertexZ*/, int/*number to quads*/> _indicesVertexZNumber;
    std::vector<PrimitiveCommand> _renderCommands;
    bool _dirty;
    
    VertexBuffer* _vertexBuffer;
    
    VertexData* _vData;
    
    IndexBuffer* _indexBuffer;
    
    Map<int , Primitive*> _primitives;
    
public:
    /** @~english Possible orientations of the TMX map  @~chinese TMX�Ŀ��ܷ����ͼ*/
    static const int FAST_TMX_ORIENTATION_ORTHO;
    static const int FAST_TMX_ORIENTATION_HEX;
    static const int FAST_TMX_ORIENTATION_ISO;
};

// end of tilemap_parallax_nodes group
/// @}
} //end of namespace experimental
NS_CC_END

#endif //__CCTMX_LAYER2_H__
