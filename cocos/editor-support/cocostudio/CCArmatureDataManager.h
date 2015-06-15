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

#ifndef __CCARMATUREDATAMANAGER_H__
#define __CCARMATUREDATAMANAGER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

struct RelativeData
{
    std::vector<std::string> plistFiles;
    std::vector<std::string> armatures;
    std::vector<std::string> animations;
    std::vector<std::string> textures;
};

/**
 *	@brief	@~english  format and manage armature configuration and armature animation
 * @~chinese ��ʽ�������������ú͹�������
 */
class CC_STUDIO_DLL ArmatureDataManager : public cocos2d::Ref
{
public:
	/** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static ArmatureDataManager *sharedArmatureDataManager() { return ArmatureDataManager::getInstance(); }

    /** @deprecated Use destoryInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purge() { ArmatureDataManager::destroyInstance(); };
    
    /**
    * @~english Get singleton.
    * @~chinese ��ȡ������
    * @return @~english Singleton of `ArmatureDataManager`.
    * @~chinese �������ݹ������ĵ�����
    */
    static ArmatureDataManager *getInstance();

    /**
    * @~english Destory singleton.
    * @~chinese ���ٵ�����
    */
    static void destroyInstance();
    
private:
	/**
     * @js ctor
     */
    ArmatureDataManager(void);
    /**
     * @js NA
     * @lua NA
     */
    ~ArmatureDataManager(void);

public:

    /**
     * @~english  Init ArmatureDataManager.
     * @~chinese ��ʼ���������ݹ�������
     * @return @~english Is initialize succeed.
     * @~chinese �Ƿ��ʼ���ɹ���
     */
    virtual bool init();

    /**
    * @~english Add armature data.
    * @~chinese ���ӹ������ݡ�
    * @param id @~english The id of the armature data.
    * @~chinese �������ݱ�ʶ��
    * @param armatureData @~english ArmatureData *.
    * @~chinese �������ݡ�
    * @param configFilePath @~english Path of config file.
    * @~chinese �����ļ�·����
    */
    void addArmatureData(const std::string& id, ArmatureData *armatureData, const std::string& configFilePath = "");

    /**
     * @~english get armature data.
     * @~chinese ��ȡ�������ݡ�
     * @param id @~english The id of the armature data you want to get.
     * @~chinese Ҫ��ȡ�������ݵı�ʶ��
     * @return @~english ArmatureData.
     * @~chinese �������ݡ�
     */
    ArmatureData *getArmatureData(const std::string& id);

    /**
     * @~english Remove armature data.
     * @~chinese �Ƴ���������
     * @param	id @~english the id of the armature data you want to get
     * @~chinese Ҫ�Ƴ��������ݵı�ʶ
     */
    void removeArmatureData(const std::string& id);

    /**
     * @brief	@~english Add animation data.
     * @~chinese ���Ӷ������ݡ�
     * @param id @~english The id of the animation data.
     * @~chinese �������ݵı�ʶ��
     * @return @~english AnimationData.
     * @~chinese �������ݡ�
     * @param configFilePath @~english Path of config file.
     * @~chinese �����ļ�·����
     */
    void addAnimationData(const std::string& id, AnimationData *animationData, const std::string& configFilePath = "");

    /**
     * @brief @~english Get animation data from _animationDatas(Dictionary).
     * @~chinese ��_animationDatas(Dictionary)�л�ȡ�������ݡ�
     * @param id @~english The id of the animation data you want to get.
     * @~chinese Ҫ��ȡ�������ݵı�ʶ��
     * @return @~english AnimationData.
     * @~chinese �������ݡ�
     */
    AnimationData *getAnimationData(const std::string& id);

    /**
     * @~english Remove animation data.
     * @~chinese �Ƴ��������ݡ�
     * @param id @~english The id of the animation data.
     * @~chinese Ҫ�Ƴ��������ݵı�ʶ��
     */
    void removeAnimationData(const std::string& id);

    /**
     * @~english Add texture data.
     * @~chinese ���Ӳ������ݡ�
     * @param id @~english The id of the texture data.
     * @~chinese �������ݵı�ʶ��
     * @param textureData @~english Texture data.
     * @~chinese �������ݡ�
     * @param configFilePath @~english Path of config file.
     * @~chinese �����ļ�·����
     */
    void addTextureData(const std::string& id, TextureData *textureData, const std::string& configFilePath = "");

    /**
     * @~english Get texture data.
     * @~chinese ��ȡ�������ݡ�
     * @param id @~english The id of the texture data you want to get.
     * @~chinese Ҫ��ȡ�������ݵı�ʶ��
     * @return @~english Texture data.
     * @~chinese �������ݡ�
     */
    TextureData *getTextureData(const std::string& id);

    /**
     * @~english Remove texture data.
     * @~chinese �Ƴ��������ݡ�
     * @param id @~english The id of the texture data you want to get.
     * @~chinese Ҫ�Ƴ��������ݵı�ʶ��
     */
    void removeTextureData(const std::string& id);

    /**
     * @~english Add ArmatureFileInfo, it is managed by `ArmatureDataManager`.
     * @~chinese ��ӹ����ļ���Ϣ���ɹ������ݹ���������
     * @param configFilePath @~english Path of config file.
     * @~chinese �����ļ�·����
     */
    void addArmatureFileInfo(const std::string& configFilePath);

    /**
     *	@~english Add ArmatureFileInfo, it is managed by `ArmatureDataManager`.
     *	It will load data in a new thread
     * @~chinese ��ӹ����ļ���Ϣ���ɹ������ݹ����������������߳��м������ݡ�
     * @param configFilePath @~english Path of config file.
     * @~chinese �����ļ�·����
     * @param target @~english The target of the callback.
     * @~chinese �ص�����Ŀ�����
     * @param selector @~english The selector to be checked.
     * @~chinese �ص�����ѡ������
     */
    void addArmatureFileInfoAsync(const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     * @~english Add ArmatureFileInfo, it is managed by `ArmatureDataManager`.
     * @~chinese ��ӹ����ļ���Ϣ���ɹ������ݹ���������
     * @param imagePath @~english Path of image.
     * @~chinese ͼƬ·����
     * @param plistPath @~english Path of plist.
     * @~chinese plist·����
     * @param configFilePath @~english Path of config file.
     * @~chinese �����ļ�·����
     */
    void addArmatureFileInfo(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath);

    /**
    * @~english Add ArmatureFileInfo, it is managed by `ArmatureDataManager`.
    *			It will load data in a new thread
    * @~chinese ��ӹ����ļ���Ϣ���ɹ������ݹ����������������߳��м������ݡ�
    * @param imagePath @~english Path of image.
    * @~chinese ͼƬ·����
    * @param plistPath @~english Path of plist.
    * @~chinese plist·����
    * @param configFilePath @~english Path of config file.
    * @~chinese �����ļ�·����
    * @param target @~english The target of the callback.
    * @~chinese �ص�����Ŀ�����
    * @param selector @~english The selector to be checked.
    * @~chinese �ص�����ѡ������
    */
    void addArmatureFileInfoAsync(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     * @~english Add sprite frame to `CCSpriteFrameCache`, it will save display name and it's relative image name.
     * @~chinese Ϊ`CCSpriteFrameCache`��Ӿ���֡�����ᱣ����ʾ���Ƽ����ͼƬ���ơ�
     * @param plistPath @~english Path of plist.
     * @~chinese plist·����
     * @param imagePath @~english Path of image.
     * @~chinese ͼƬ·����
     * @param configFilePath @~english Path of config file.
     * @~chinese �����ļ�·����
     */
    void addSpriteFrameFromFile(const std::string& plistPath, const std::string& imagePath, const std::string& configFilePath = "");

    /**
    * @~english Remove ArmatureFileInfo.
    * @~chinese �Ƴ������ļ���Ϣ��
    * @param configFilePath @~english Path of config file.
    * @~chinese �����ļ�·����
    */
    virtual void removeArmatureFileInfo(const std::string& configFilePath);

    /**
     *	@~english Judge whether or not need auto load sprite file.
     * @~chinese �ж��Ƿ���Ҫ�Զ����ؾ����ļ���
     */
    bool isAutoLoadSpriteFile();

    /**
    * @~english  Get data of Armature.
    * @~chinese ��ȡ�������ݡ�
    * @return @~english Map of Armature data.
    * @~chinese ��������map��
    */
    const cocos2d::Map<std::string, ArmatureData*>&     getArmatureDatas() const;

    /**
    * @~english  Get data of Animation.
    * @~chinese ��ȡ�������ݡ�
    * @return @~english Map of Animation data.
    * @~chinese ��������map��
    */
    const cocos2d::Map<std::string, AnimationData*>&    getAnimationDatas() const;

    /**
    * @~english  Get data of Texture.
    * @~chinese ��ȡ�������ݡ�
    * @return @~english Map of Texture data.
    * @~chinese ��������map��
    */
    const cocos2d::Map<std::string, TextureData*>&      getTextureDatas() const;

protected:
    void addRelativeData(const std::string& configFilePath);
    RelativeData *getRelativeData(const std::string& configFilePath);
private:
    /**
     *	@brief	save amature datas
     *  @key	std::string
     *  @value	ArmatureData *
     */
    cocos2d::Map<std::string, ArmatureData*> _armarureDatas;

    /**
     *	@brief	save animation datas
     *  @key	std::string
     *  @value	AnimationData *
     */
    cocos2d::Map<std::string, AnimationData*> _animationDatas;

    /**
     *	@brief	save texture datas
     *  @key	std::string
     *  @value	TextureData *
     */
    cocos2d::Map<std::string, TextureData*> _textureDatas;

    bool _autoLoadSpriteFile;

    std::unordered_map<std::string, RelativeData> _relativeDatas;
};


}

#endif/*__CCARMATUREDATAMANAGER_H__*/
