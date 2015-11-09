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
#ifndef __CCTMX_LAYER_H__
#define __CCTMX_LAYER_H__

#include "2d/CCSpriteBatchNode.h"
#include "2d/CCTMXXMLParser.h"
#include "base/ccCArray.h"
NS_CC_BEGIN

class TMXMapInfo;
class TMXLayerInfo;
class TMXTilesetInfo;
struct _ccCArray;

/**
 * @addtogroup _2d
 * @{
 */


/** @brief @~english TMXLayer represents the TMX layer.
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
 
 * @~chinese TMXLayer������ʾTMX layer��
 * �̳���SpriteBatchNode��tilesʹ��TextureAtlas������Ⱦ��
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
 * @since v0.8.1
 * @~english Tiles can have tile flags for additional properties. At the moment only flip horizontal and flip vertical are used. These bit flags are defined in TMXXMLParser.h.
 * @~chinese ��Ƭ������flags�������ԡ�Ŀǰֻ��ˮƽ��ת�ʹ�ֱ��ת�õ�����Щflags��TMXXMLParser.h�ж���.
 * @since 1.1
 */


class CC_DLL TMXLayer : public SpriteBatchNode
{
public:
    /** @~english Creates a TMXLayer with an tileset info, a layer info and a map info.
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

    /** @~english Initializes a TMXLayer with a tileset info, a layer info and a map info.
     *
     * @~chinese ʹ��ָ��TMXTilesetInfo,TMXLayerInfo��TMXMapInfo��ʼ��һ��TMXLayer
     * 
     * @param tilesetInfo @~english An tileset info.
     * @~chinese TMXTilesetInfo����.
     * @param layerInfo @~english A layer info.
     * @~chinese TMXLayerInfo����.
     * @param mapInfo @~english A map info.
     * @~chinese TMXMapInfo����.
     * @return @~english If initializes success,it will return true.
     * @~chinese �����ʼ���ɹ�,������true.
     */
    bool initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);

    /** @~english Dealloc the map that contains the tile position from memory.
     * Unless you want to know at runtime the tiles positions, you can safely call this method.
     * If you are going to call layer->tileGIDAt() then, don't release the map.
     * @~chinese ���ڴ����ͷŰ���tileλ����Ϣ�ĵ�ͼ��
     * ����������ʱ��Ҫ֪��tiles��λ����Ϣ�⣬�㶼�ɰ�ȫ�ĵ��ô˷�����
     * �����֮��Ҫ����layer->tileGIDAt(),�벻Ҫ�ͷŵ�ͼ.
     */
    void releaseMap();

    /** @~english Returns the tile (Sprite) at a given a tile coordinate.
     * The returned Sprite will be already added to the TMXLayer. Don't add it again.
     * The Sprite can be treated like any other Sprite: rotated, scaled, translated, opacity, color, etc.
     * You can remove either by calling:
     * - layer->removeChild(sprite, cleanup);
     * - or layer->removeTileAt(Vec2(x,y));
     *
     * @~chinese  ͨ��ָ����tile�����ȡ��Ӧ��tile(Sprite)��
     * ���ص�tile(Sprite)Ӧ���Ѿ���ӵ�TMXLayer���벻Ҫ�ظ���ӡ�
	 * ���tile(Sprite)��ͬ������Spriteһ����������ת�����š���ת��͸������������ɫ�ȡ�
     * �����ͨ���������·�������������ɾ��:
     * - layer->removeChild(sprite, cleanup);
     * - �� layer->removeTileAt(Vec2(x,y));
     * 
     * @param tileCoordinate @~english A tile coordinate.
     * @~chinese ��Ƭ����.
     * @return @~english Returns the tile (Sprite) at a given a tile coordinate.
     * @~chinese ����ָ������λ�õ���Ƭ(Sprite).
     */
    Sprite* getTileAt(const Vec2& tileCoordinate);

    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE Sprite* tileAt(const Vec2& tileCoordinate) { return getTileAt(tileCoordinate); };
    
    /** @~english Returns the tile gid at a given tile coordinate. It also returns the tile flags.
     * This method requires the tile map has not been previously released (eg. don't call [layer releaseMap]).
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

	uint32_t getTileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags = nullptr);

    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE uint32_t tileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags = nullptr){
        return getTileGIDAt(tileCoordinate, flags);
    };

    /** @~english Sets the tile gid (gid = tile global id) at a given tile coordinate.
     * The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
     * If a tile is already placed at that position, then it will be removed.
     *
     * @~chinese ���ø����������Ƭ��gid(gid =��Ƭȫ��id)
     * ��ƬGID����ʹ�÷�����tileGIDAt������ã���ʹ��TMX�༭�� -> Tileset Mgr +1�õ�.
     * �����λ��������һ��tile����ô��λ�������е�tile���ᱻ�Ƴ���
     * 
     * @param gid @~english The tile gid.
     * @~chinese ��Ƭgid.
     * @param tileCoordinate @~english The tile coordinate.
     * @~chinese ��Ƭ����.
     */
    void setTileGID(uint32_t gid, const Vec2& tileCoordinate);

    /** @~english Sets the tile gid (gid = tile global id) at a given tile coordinate.
     * The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
     * If a tile is already placed at that position, then it will be removed.
     * Use withFlags if the tile flags need to be changed as well.
     * 
     * @~chinese ���ø������ꡢflags����Ƭ��gid(gid =��Ƭȫ��id)
     * ��ƬGID����ʹ�÷�����tileGIDAt������ã���ʹ��TMX�༭�� -> Tileset Mgr +1.
     * ���һ����Ƭ�Ѿ������Ǹ�λ��,��ô������ɾ��.
     * �����Ƭ��flags��Ҫ���ģ���ʹ��withFlags�ķ�����
     * 
     * @param gid @~english The tile gid.
     * @~chinese ��Ƭgid.
     * @param tileCoordinate @~english The tile coordinate.
     * @~chinese ��Ƭ����.
     * @param flags @~english The tile flags.
     * @~chinese ��Ƭ��flags.
     */
    void setTileGID(uint32_t gid, const Vec2& tileCoordinate, TMXTileFlags flags);

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
     * @~chinese ָ����Ƭ������λ��.
     */
	Vec2 getPositionAt(const Vec2& tileCoordinate);

    /**
    * @js NA
    */
    CC_DEPRECATED_ATTRIBUTE Vec2 positionAt(const Vec2& tileCoordinate) { return getPositionAt(tileCoordinate); };

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

    /**
    * @js NA
    */
    CC_DEPRECATED_ATTRIBUTE Value propertyNamed(const std::string& propertyName) const { return getProperty(propertyName); };

    /** @~english Creates the tiles.  @~chinese ����tiles*/
    void setupTiles();
    
    /** @~english Get the layer name. 
     *
     * @~chinese ��ȡ�������.
     * 
     * @return @~english The layer name.
     * @~chinese �������.
     */
    inline const std::string& getLayerName(){ return _layerName; }
    
    /** @~english Set the layer name.
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
    
    /** @~english Set size of the layer in tiles.
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
     * @~chinese ��Ƭ�ĳߴ�.
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
     * @js NA
     * @lua NA
     * @return @~english Pointer to the map of tiles.
     * @~chinese ָ��tiles��ͼ��ָ��.
     */
    uint32_t* getTiles() const { return _tiles; };
    
    /** @~english Set a pointer to the map of tiles.
     *
     * @~chinese ����ָ��tiles��ͼ��ָ�롣
     * 
     * @param tiles @~english A pointer to the map of tiles.
     * @~chinese ָ��tiles��ͼ��ָ��
     */
    void setTiles(uint32_t* tiles) { _tiles = tiles; };
    
    /** @~english Tileset information for the layer. 
     *
     * @~chinese ��ȡlayer��Tileset��Ϣ
     * 
     * @return @~english Tileset information for the layer.
     * @~chinese layer��Tileset��Ϣ
     */
    inline TMXTilesetInfo* getTileSet() const { return _tileSet; };
    
    /** @~english Set tileset information for the layer.
     *
     * @~chinese ����layer��Tileset��Ϣ
     * 
     * @param info @~english The tileset information for the layer.
     * @~chinese layer��Tileset��Ϣ
     * @js NA
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
    
    /** @~english Set layer orientation, which is the same as the map orientation.
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
    
    /** @~english Set an Properties from to layer.
     *
     * @~chinese ���ò�����.
     * 
     * @param properties @~english It is used to set the layer Properties.
     * @~chinese ������������ͼ�������.
     */
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };

    //
    // Override
    //
    /** @~english TMXLayer doesn't support adding a Sprite manually.
     * @~chinese TMXLayer��֧���ֶ����һ��Sprite.
     @warning @~english addchild(z, tag); is not supported on TMXLayer. Instead of setTileGID.
     * @~chinese addchild(z, tag);������TMXLayer��ʹ�ã�����setTileGID����
     */
    using SpriteBatchNode::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;

    // super method
    void removeChild(Node* child, bool cleanup) override;

    /**
    * @js NA
    */
    virtual std::string getDescription() const override;

protected:
    Vec2 getPositionForIsoAt(const Vec2& pos);
    Vec2 getPositionForOrthoAt(const Vec2& pos);
    Vec2 getPositionForHexAt(const Vec2& pos);
    Vec2 getPositionForStaggeredAt(const Vec2& pos);
    Vec2 calculateLayerOffset(const Vec2& offset);

    /* optimization methods  @~chinese �Ż�����*/
    Sprite* appendTileForGID(uint32_t gid, const Vec2& pos);
    Sprite* insertTileForGID(uint32_t gid, const Vec2& pos);
    Sprite* updateTileForGID(uint32_t gid, const Vec2& pos);

    /* @~english The layer recognizes some special properties, like cc_vertez  @~chinese ��ʶ��һЩ��������ԣ�����cc_vertez*/
    void parseInternalProperties();
    void setupTileSprite(Sprite* sprite, Vec2 pos, int gid);
    Sprite* reusedTileWithRect(Rect rect);
    int getVertexZForPos(const Vec2& pos);

    // index
    ssize_t atlasIndexForExistantZ(int z);
    ssize_t atlasIndexForNewZ(int z);


    //! name of the layer
    std::string _layerName;
    
    //! TMX Layer supports opacity
    unsigned char _opacity;
    
    //! Only used when vertexZ is used
    int _vertexZvalue;
    bool _useAutomaticVertexZ;

    //! used for optimization
    Sprite *_reusedTile;
    ccCArray *_atlasIndexArray;
    
    // used for retina display
    float _contentScaleFactor;
    
    /** @~english size of the layer in tiles  @~chinese ����ƬΪ��λ�Ĳ��С*/
    Size _layerSize;
    
    /** @~english size of the map's tile (could be different from the tile's size)  @~chinese ��ͼ��Ƭ�Ĵ�С(����Ƭ�Ĵ�С���ܻ�������ͬ)*/
    Size _mapTileSize;
    
    /** @~english pointer to the map of tiles  @~chinese ָ���ͼ��Ƭ��ָ��*/
    uint32_t* _tiles;
    
    /** @~english Tileset information for the layer  @~chinese ��ĵ�����Ϣ*/
    TMXTilesetInfo* _tileSet;
    
    /** @~english Layer orientation, which is the same as the map orientation  @~chinese �㷽�������ͼ������ͬ*/
    int _layerOrientation;
    
    /** @~english properties from the layer. They can be added using Tiled  @~chinese �����ԡ����ǿ���ʹ����Ƭ�������*/
    ValueMap _properties;
};

// end of tilemap_parallax_nodes group
/** @} */


NS_CC_END

#endif //__CCTMX_LAYER_H__

