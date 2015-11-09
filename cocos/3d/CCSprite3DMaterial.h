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

#ifndef __CCSPRIT3DMATERIAL_H__
#define __CCSPRIT3DMATERIAL_H__

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"
#include "renderer/CCMaterial.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

class Texture2D;

/** @class Sprite3DMaterial
 *  @brief @~english Sprite3DMaterial: Material for Sprite3D.
	@~chinese 3D����ʹ�õĲ���
    @js NA
    @lua NA
 */
class CC_DLL Sprite3DMaterial : public Material
{
public:
    /** @~english Material type, there are mainly two types of materials. Built in materials and Custom material
        @~chinese �������͡���Ҫ����2�ֲ��ʣ����ò��ʺ����Զ������
    */
    enum class MaterialType
    {
        /** @~english Built in material
            @~chinese ���ò���
        */
        UNLIT, /**@~english unlit material.  @~chinese �޹��ղ��� */
        UNLIT_NOTEX, /**@~english unlit material without texture.  @~chinese �޹������������ */
        VERTEX_LIT, /**@~english vertex lit.  @~chinese ������� */
        DIFFUSE, /**@~english diffuse (pixel lighting).  @~chinese ɢ��⣨���ع��գ� */
        DIFFUSE_NOTEX, /**@~english diffuse (without texture).  @~chinese ɢ��⣨������ */
        BUMPED_DIFFUSE, /**@~english bumped diffuse.  @~chinese ��͹������ */
        
        /** @~english Custom material
            @~chinese �Զ������
        */
        CUSTOM, /**@~english Create from material file.  @~chinese �Ӳ����ļ����� */
    };

    /** @~english Get material type
        @~chinese ��ȡ��������
        @return @~english Material type @~chinese ��������
    */
    MaterialType getMaterialType() const { return _type; }

    /** @~english Create built in material from material type
        @~chinese ����ָ���������ʹ������ò���
        @param type @~english  Material type @~chinese ��������
        @param skinned @~english  Has skin? @~chinese �Ƿ���Ƥ��
        @return @~english Created material @~chinese �����Ĳ���
    */
    static Sprite3DMaterial* createBuiltInMaterial(MaterialType type, bool skinned);

    /** @~english Create material with file name, it creates material from cache if it is previously loaded
        @~chinese ͨ�������ļ��������ʣ���������Ѿ������ع��򷵻ػ����еĲ���
        @param path @~english  Path of material file @~chinese �����ļ�·��
        @return @~english Created material @~chinese �����Ĳ���
    */
    static Sprite3DMaterial* createWithFilename(const std::string& path);

    /** @~english Create material with GLProgramState
        @~chinese ʹ��GLProgramState��������
        @param programState @~english  GLProgramState instance @~chinese GLProgramStateʵ��
        @return @~english Created material @~chinese �����Ĳ���
    */
    static Sprite3DMaterial* createWithGLStateProgram(GLProgramState* programState);

    /** @~english Create all build in materials
        @~chinese ����ȫ�����ò���
    */
    static void createBuiltInMaterial();

    /** @~english Release all built in materials
        @~chinese �ͷ�ȫ�����ò���
    */
    static void releaseBuiltInMaterial();

    /** @~english Release all cached materials
        @~chinese �ͷ�ȫ������Ĳ���
    */
    static void releaseCachedMaterial();

    /** @~english Clone material
        @~chinese ��¡����
    */
    virtual Material* clone() const override;
    
protected:
    
    MaterialType _type;
    static std::unordered_map<std::string, Sprite3DMaterial*> _materials; //cached material
    static Sprite3DMaterial* _unLitMaterial;
    static Sprite3DMaterial* _unLitNoTexMaterial;
    static Sprite3DMaterial* _vertexLitMaterial;
    static Sprite3DMaterial* _diffuseMaterial;
    static Sprite3DMaterial* _diffuseNoTexMaterial;
    static Sprite3DMaterial* _bumpedDiffuseMaterial;
    
    static Sprite3DMaterial* _unLitMaterialSkin;
    static Sprite3DMaterial* _vertexLitMaterialSkin;
    static Sprite3DMaterial* _diffuseMaterialSkin;
    static Sprite3DMaterial* _bumpedDiffuseMaterialSkin;
};

/** @class Sprite3DMaterialCache
    @brief @~english the sprite3D material is only texture for now
	@~chinese ��ǰ�Ĳ��ʽ���ʹ��������
    @js NA
    @lua NA
*/
class Sprite3DMaterialCache
{
public:
    /** @~english get & destroy cache
        @~chinese �õ��˶����ʵ��
        @return @~english the instance of this object @~chinese �˶����ʵ��
    */
    static Sprite3DMaterialCache* getInstance();

    /** @~english destroy the instance
        @~chinese ����ʵ��
    */
    static void destroyInstance();

    /** @~english add to cache
        @~chinese ��ӵ�������
        @param key @~english  the key of material @~chinese ���ʵļ�
        @param tex @~english  the Texture2D to add @~chinese ��ӵ�Texture2D
        @return @~english Whether or not the operation is successful @~chinese �Ƿ�ɹ�
    */
    bool addSprite3DMaterial(const std::string& key, Texture2D* tex);

    /** @~english get material from cache
        @~chinese �ӻ����л�ò���
        @param key @~english  the key of material @~chinese ���ʵļ�
        @return @~english the Texture2D of the given material @~chinese �������ʵ�Texture2D
    */
    Texture2D* getSprite3DMaterial(const std::string& key);

    /** @~english remove all spritematerial
        @~chinese ɾ������spritematerial
    */
    void removeAllSprite3DMaterial();

    /** @~english remove unused spritematerial
        @~chinese ɾ��δʹ�õ�spritematerial
    */
    void removeUnusedSprite3DMaterial();
    
CC_CONSTRUCTOR_ACCESS:
    
    Sprite3DMaterialCache();
    ~Sprite3DMaterialCache();
    
protected:
    static Sprite3DMaterialCache* _cacheInstance;//instance
    std::unordered_map<std::string, Texture2D*> _materials; //cached material
    
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCSPRIT3DMATERIAL_H__
