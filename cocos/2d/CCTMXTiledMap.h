/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
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
#ifndef __CCTMX_TILE_MAP_H__
#define __CCTMX_TILE_MAP_H__

#include "2d/CCNode.h"
#include "2d/CCTMXObjectGroup.h"
#include "base/CCValue.h"

NS_CC_BEGIN

class TMXLayer;
class TMXLayerInfo;
class TMXTilesetInfo;
class TMXMapInfo;

/**
 * @addtogroup _2d
 * @{
 */


/** Possible orientations of the TMX map.*/
enum
{
    /** @~english  Orthogonal orientation. @~chinese ��������*/
    TMXOrientationOrtho,

    /** @~english  Hexagonal orientation. @~chinese  �����εĳ���*/
    TMXOrientationHex,

    /** @~english Isometric orientation. @~chinese �Ⱦ೯�� */
    TMXOrientationIso,
    
    /** @~english Isometric staggered orientation. @~chinese �Ⱦཻ���� */
    TMXOrientationStaggered,
};

/** @brief @~english TMXTiledMap knows how to parse and render a TMX map.

 * It adds support for the TMX tiled map format used by http://www.mapeditor.org
 * It supports isometric, hexagonal and orthogonal tiles.
 * It also supports object groups, objects, and properties.

 * Features:
 * - Each tile will be treated as an Sprite.
 * - The sprites are created on demand. They will be created only when you call "layer->tileAt(position)".
 * - Each tile can be rotated / moved / scaled / tinted / "opaqued", since each tile is a Sprite.
 * - Tiles can be added/removed in runtime.
 * - The z-order of the tiles can be modified in runtime.
 * - Each tile has an anchorPoint of (0,0).
 * - The anchorPoint of the TMXTileMap is (0,0).
 * - The TMX layers will be added as a child.
 * - The TMX layers will be aliased by default.
 * - The tileset image will be loaded using the TextureCache.
 * - Each tile will have a unique tag.
 * - Each tile will have a unique z value. top-left: z=1, bottom-right: z=max z.
 * - Each object group will be treated as an MutableArray.
 * - Object class which will contain all the properties in a dictionary.
 * - Properties can be assigned to the Map, Layer, Object Group, and Object.

 * Limitations:
 * - It only supports one tileset per layer.
 * - Embedded images are not supported.
 * - It only supports the XML format (the JSON format is not supported).

 * Technical description:
 * Each layer is created using an TMXLayer (subclass of SpriteBatchNode). If you have 5 layers, then 5 TMXLayer will be created,
 * unless the layer visibility is off. In that case, the layer won't be created at all.
 * You can obtain the layers (TMXLayer objects) at runtime by:
 * - map->getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
 * - map->getLayer(name_of_the_layer);

 * Each object group is created using a TMXObjectGroup which is a subclass of MutableArray.
 * You can obtain the object groups at runtime by:
 * - map->getObjectGroup(name_of_the_object_group);

 * Each object is a TMXObject.

 * Each property is stored as a key-value pair in an MutableDictionary.
 * You can obtain the properties at runtime by:

 * map->getProperty(name_of_the_property);
 * layer->getProperty(name_of_the_property);
 * objectGroup->getProperty(name_of_the_property);
 * object->getProperty(name_of_the_property);

 * @~chinese TMXTiledMap֪����ν�������ȾTMX��ͼ��
 * 
 * http://www.mapeditor.org�����������֧��TMX tiled��ͼ��ʽ
 * ��֧�ֵȾ�б��(isometric),������(hexagonal),ֱ�����(orthogonal)tiles
 * Ҳ֧�ֶ�����,������Լ�������
 * 
 * �ص�:
 * - ÿ��TMXTiledMap��������һ������
 * - ��Щ������Ҫʱ���������ҽ�������layer->tileAt(position)ʱ�Żᱻ����
 * - ÿ��tile�̳��˾�����ص㣬������ת/�ƶ�/����/��ɫ/͸����
 * - Tiles����������ʱ��ӻ�ɾ��
 * - Tiles��z-order���������ʱ�޸�
 * - ÿ��tile��ê����(0,0)
 * - TMXTileMap��ê����(0,0)
 * - TMX layers���Ե����ӽڵ����
 * - TXM layersĬ�ϻ�����һ������
 * - TilesetͼƬ������ʹ��TextureCacheʱ����
 * - ÿ��tile����һ��Ψһ��tag
 * - ÿ��tile����һ��Ψһ��zֵ.����(top-left): z=1, ����(bottom-right): z=max z
 * - ÿ��������(object group)���������ɱ�����(MutaleArray)
 * - ��������������Զ��洢��һ���ֵ�(dictionary)��
 * - ���Կ��Ը�ֵ����ͼ(Map),��(Layer),��������(Object Group)�Լ�����(Object)
 * 
 * ����:
 * - ÿ��layerֻ֧��һ��tileset
 * - ��֧��Ƕ��ʽͼƬ(Embedded images)
 * - ֻ֧��XML��ʽ(��֧��JSON��ʽ)��
 * 
 * ��������:
 * ÿ��layer��������TMXLayer(�̳���SpriteBatchNode)��
 * ���layer�ǿ��ӵ�,��ô�������5��layer,��5��TMXLayer������.
 * ���������,��layer�������ᱻ������
 * ������ʱ,��ͨ�����»�ȡlayers(TMXLayer objects):
 * - map->getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
 * - map->getLayer(name_of_the_layer);
 * 
 * ÿ�������鱻������һ���̳���MutableArray��TMXObjectGroup
 * ����ʱ,��ͨ�����»�ȡ�ö�����:
 * - map->getObjectGroup(name_of_the_object_group);//name_of_the_object_group ��������
 * ÿ��object����һ��TMXObject
 * ÿ�����Զ�ͨ��key-value�Դ洢��һ��MutableDictionary��
 * ����ʱ,��ͨ�����»�ȡ����:
 * 
 * map->getProperty(name_of_the_property);
 * layer->getProperty(name_of_the_property);
 * objectGroup->getProperty(name_of_the_property);
 * object->getProperty(name_of_the_property);
 * 
 * @since v0.8.1
 */
class CC_DLL TMXTiledMap : public Node
{
public:
    /** @~english Creates a TMX Tiled Map with a TMX file.
     *
     * @~chinese ͨ��ָ��TMX�ļ�����һ��TMX Tiled��ͼ��
     * 
     * @param tmxFile @~english A TMX file.
     * @~chinese TMX�ļ���
     * @return @~english An autorelease object.
     * @~chinese һ��autorelease����
     */
    static TMXTiledMap* create(const std::string& tmxFile);

    /** @~english Initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources. 
     *
     * @~chineseͨ��һ��ָ����TMX��ʽ��XML��TMX��Դ·������һ��TMX Tiled��ͼ��
     * 
     * @param tmxString @~english A TMX formatted XML string.
     * @~chinese TMX��ʽ��XML�ַ�����
     * @param resourcePath @~english The path to TMX resources.
     * @~chinese TMX����Դ·����
     * @return @~english An autorelease object.
     * @~chinese һ��autorelease����
     * @js NA
     */
    static TMXTiledMap* createWithXML(const std::string& tmxString, const std::string& resourcePath);

    /** @~english Return the TMXLayer for the specific layer. 
     *
     * @~chinese ͨ��layerName��ȡ��Ӧ��TMXLayer��
     * 
     * @param layerName @~english A specific layer.
     * @~chinese һ��ָ���Ĳ����ơ�
     * @return @~english The TMXLayer for the specific layer.
     * @~chinese ָ�������Ƶ�TMXLayer�㡣
     */
    TMXLayer* getLayer(const std::string& layerName) const;

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE TMXLayer* layerNamed(const std::string& layerName) const { return getLayer(layerName); };

    /** @~english Return the TMXObjectGroup for the specific group. 
     *
     * @~chinese ͨ��groupName��ȡ��Ӧ��TMXObjectGroup��
     * 
     * @param groupName @~english The group Name.
     * @~chinese �����ơ�
     * @return @~english A Type of TMXObjectGroup.
     * @~chinese TMXObjectGroup��
     */
    TMXObjectGroup* getObjectGroup(const std::string& groupName) const;

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE TMXObjectGroup* objectGroupNamed(const std::string& groupName) const { return getObjectGroup(groupName); };

    /** @~english Return the value for the specific property name. 
     *
     * @~chinese  ͨ��propertyName��ȡ��Ӧ��Property��
     * 
     * @param propertyName @~english The specific property name.
     * @~chinese ָ������������
     * @return @~english Return the value for the specific property name.
     * @~chinese ����ָ����������ֵ��
     */
    Value getProperty(const std::string& propertyName) const;

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Value propertyNamed(const char *propertyName) const { return getProperty(propertyName); };

    /** @~english Return properties dictionary for tile GID. 
     *
     * @~chinese ͨ��GID��ȡ��Ӧ�������ֵ�(properties dictionary)��
     * 
     * @param GID @~english The tile GID.
     * @~chinese ��ƬGID��
     * @return @~english Return properties dictionary for tile GID.
     * @~chinese ���������ֵ䡣
     */
    Value getPropertiesForGID(int GID) const;

    CC_DEPRECATED_ATTRIBUTE Value propertiesForGID(int GID) const { return getPropertiesForGID(GID); };

    /** @~english Assings properties to argument value, returns true if it did found properties 
     * for that GID and did assinged a value, else it returns false.
     *
     * @~chinese ͨ��ָ��GID�������Ӧ�����Ա���,����������ֵvalue,
     * ��ɹ����ҵ�����ֵ�ɹ�,�򷵻�true,��֮��Ϊfalse��
     * 
     * @param GID @~english The tile GID.
     * @~chinese ��ƬGID��
     * @param value @~english Argument value.
     * @~chinese ����ֵ��
     * @return @~english Return true if it did found properties for that GID and did assinged a value, else it returns false.
     * @~chinese ��ɹ����ҵ�����ֵ�ɹ�,�򷵻�true,��֮��Ϊfalsee��
     */
    bool getPropertiesForGID(int GID, Value** value);

    /** @~english The map's size property measured in tiles. 
     *
     * @~chinese ��ȡ��tiles��Ϊ��λ�ĵ�ͼ�ߴ�
     * 
     * @return @~english The map's size property measured in tiles.
     * @~chinese ��tiles����Ϊ��׼�ĵ�ͼ�ߴ硣
     */
    inline const Size& getMapSize() const { return _mapSize; };
    
    /** @~english Set the map's size property measured in tiles. 
     *
     * @~chinese ������tiles����Ϊ��׼�ĵ�ͼ�ߴ硣
     * 
     * @param mapSize @~english The map's size property measured in tiles.
     * @~chinese ��tiles����Ϊ��׼�ĵ�ͼ�ߴ硣
     */
    inline void setMapSize(const Size& mapSize) { _mapSize = mapSize; };

    /** @~english The tiles's size property measured in pixels. 
     *
     * @~chinese ��ȡ�����ص�Ϊ��׼��tile�ߴ����ԡ�
     * 
     * @return @~english The tiles's size property measured in pixels.
     * @~chinese �����ص�Ϊ��׼��tile�ߴ����ԡ�
     */
    inline const Size& getTileSize() const { return _tileSize; };
    
    /** @~english Set the tiles's size property measured in pixels. 
     *
     * @~chinese ���������ص�Ϊ��׼��tile�ߴ����ԡ�
     * 
     * @param tileSize @~english The tiles's size property measured in pixels.
     * @~chinese �����ص�Ϊ��׼��tile�ߴ����ԡ�
     */
    inline void setTileSize(const Size& tileSize) { _tileSize = tileSize; };

    /** @~english Map orientation. 
     *
     * @~chinese ��ȡ��ͼ����(orientation)
     * 
     * @return @~english Map orientation.
     * @~chinese ��ͼ����(orientation)
     */
    inline int getMapOrientation() const { return _mapOrientation; };
    
    /** @~english Set map orientation. 
     *
     * @~chinese ���õ�ͼ����(orientation)
     * 
     * @param mapOrientation @~english The map orientation.
     * @~chinese ��ͼ����(orientation)
     */
    inline void setMapOrientation(int mapOrientation) { _mapOrientation = mapOrientation; };

    /** @~english Get the Object groups. 
     *
     * @~chinese ��ȡ�����顣
     * 
     * @return @~english The object groups.
     * @~chinese �����顣
     */
    inline const Vector<TMXObjectGroup*>& getObjectGroups() const { return _objectGroups; };
    inline Vector<TMXObjectGroup*>& getObjectGroups() { return _objectGroups; };
    
    /** @~english Set the object groups. 
     *
     * @~chinese ���ö����顣
     * 
     * @param groups @~english The object groups.
     * @~chinese �����顣
     */
    inline void setObjectGroups(const Vector<TMXObjectGroup*>& groups) {
        _objectGroups = groups;
    };
    
    /** @~english Properties. 
     *
     * @~chinese ��ȡ���ԡ�
     * 
     * @return @~english Properties.
     * @~chinese ValueMap���ԡ�
     */
    inline ValueMap& getProperties() { return _properties; };
    
    /** @~english Set the properties.
     *
     * @~chinese �������ԡ�
     * 
     * @param properties @~english A  Type of ValueMap to set the properties.
     * @~chinese ValueMap���ԡ�
     */
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };
    
    /** @~english Get the description.
     * @~chinese ��ȡ������
     * @js NA
     */
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TMXTiledMap();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXTiledMap();
    
    /** @~english initializes a TMX Tiled Map with a TMX file  @~chinese ͨ��ָ����TMX�ļ���ʼ��TMXTiledMap*/
    bool initWithTMXFile(const std::string& tmxFile);
    
    /** @~english initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources  @~chinese ͨ��ָ����TMX��ʽXML�ַ�������ʼ��TMXTiledMap */
    bool initWithXML(const std::string& tmxString, const std::string& resourcePath);

protected:
    TMXLayer * parseLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    TMXTilesetInfo * tilesetForLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    void buildWithMapInfo(TMXMapInfo* mapInfo);

    /** @~english the map's size property measured in tiles  @~chinese ����ƬΪ��λ�ĵ�ͼ��С*/
    Size _mapSize;
    /** @~english the tiles's size property measured in pixels  @~chinese ������Ϊ��λ����Ƭ��С*/
    Size _tileSize;
    /** @~english map orientation  @~chinese ��ͼ��λ*/
    int _mapOrientation;
    /** @~english object groups  @~chinese ������*/
    Vector<TMXObjectGroup*> _objectGroups;
    /** @~english properties  @~chinese ����*/
    ValueMap _properties;
    
    //! tile properties
    ValueMapIntKey _tileProperties;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TMXTiledMap);

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_TILE_MAP_H__


