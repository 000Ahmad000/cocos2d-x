/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __Manifest__
#define __Manifest__

#include <string>
#include <unordered_map>
#include <vector>

#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "network/CCDownloader.h"
#include "platform/CCFileUtils.h"

#include "json/document.h"

NS_CC_EXT_BEGIN

struct DownloadUnit
{
    std::string srcUrl;
    std::string storagePath;
    std::string customId;
};
/**
 * @addtogroup assets_manager
 * @{
 */

typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;

/**
 * @~english Manifest is an abstraction of the assets list. 
 * It's initialized and parsed with a manifest file.
 * It contains all defined assets, and can be compared to generate difference between local and remote manifest.
 * @~chinese Manifest����Դ�б�ĳ���
 * ������ͨ��һ��manifest�ļ�����ʼ������������Դ�б���Ϣ��
 * ����������manifest�ļ��ж������Դ�����ҿ��������Ƚϱ��غ�Զ��manifest��Դ�Ĳ��죬�Ա�����ĸ��¹�����ʹ�á�
 */
class CC_EX_DLL Manifest : public Ref
{
public:
    
    friend class AssetsManagerEx;
    
    /** @~english Type of difference between local and remote asset
     * @~chinese ���غ�Զ����Դ�Ĳ�������
     */
    enum class DiffType {
        /** @~english Added in remote, absent in local
         * @~chinese ��Զ����Դ�б��д��ڣ��ڱ��ز�����
         */
        ADDED,
        /** @~english Deleted in remote, present in local
         * @~chinese ��Զ����Դ�б�����ɾ�����ڵ�����Ȼ����
         */
        DELETED,
        /** @~english Updated in remote, local version is old
         * @~chinese ��Զ����Դ�б����Ѹ��£����صİ汾�Ǿɵ�
         */
        MODIFIED
    };

    /** @~english Download state of a updating asset
     * @~chinese ���ظ�����Դ��״̬
     */
    enum class DownloadState {
        /** @~english Wait to be updated
         * @~chinese �ȴ�����
         */
        UNSTARTED,
        /** @~english Downloading
         * @~chinese ������
         */
        DOWNLOADING,
        /** @~english Updated
         * @~chinese �Ѹ���
         */
        SUCCESSED
    };
    
    /** @~english The asset object
     * @~chinese ��Դ����
     */
    struct Asset {
        /** @~english The version number string, suggested to use md5.
         * @~chinese �汾�ŵ��ַ���������ʹ��md5��
         */
        std::string md5;
        /** @~english The url address of the remote asset
         * @~chinese Զ����Դ��url��ַ
         */
        std::string path;
        /** @~english Indicate whether the asset is compressed or not
         * @~chinese ָʾ��Դ�Ƿ�ѹ��
         */
        bool compressed;
        /** @~english The download state
         * @~chinese ���ص�״̬
         */
        DownloadState downloadState;
    };

    /** @~english Object indicate the difference between two Assets
     * @~chinese ��ʾ������Դ֮������Ķ���
     */
    struct AssetDiff {
        /** @~english The asset object
         * @~chinese ��Դ����
         */
        Asset asset;
        /** @~english Type of difference between local and remote asset
         * @~chinese ���غ�Զ����Դ����������
         */
        DiffType type;
    };
    
    /** @brief @~english Check whether the version informations have been fully loaded
     * @~chinese ���汾��Ϣ�Ƿ��Ѽ���
     * @return @~english The version informations have been loaded or not
     * @~chinese ���ذ汾��Ϣ�Ƿ��Ѽ���
     */
    bool isVersionLoaded() const;
    
    /** @brief @~english Check whether the manifest have been fully loaded
     * @~chinese �����Դ�嵥�Ƿ�������
     * @return @~english The manifest have been loaded or not
     * @~chinese �����嵥�Ƿ��Ѿ�������
     */
    bool isLoaded() const;
    
    /** @brief @~english Gets remote package url.
     * @~chinese ��ȡԶ����Դ��url��
     * @return @~english The remote package url
     * @~chinese Զ����Դ��url
     */
    const std::string& getPackageUrl() const;
    
    /** @brief @~english Gets remote manifest file url.
     * @~chinese ��ȡԶ����Դ�嵥�ļ���url��
     * @return @~english The remote manifest file url
     * @~chinese Զ����Դ�嵥�ļ���url
     */
    const std::string& getManifestFileUrl() const;
    
    /** @brief @~english Gets remote version file url.
     * @~chinese ��ȡԶ�̰汾�ļ���url��
     * @return @~english The remote version file url
     * @~chinese Զ�̰汾�ļ���url
     */
    const std::string& getVersionFileUrl() const;
    
    /** @brief @~english Gets manifest version.
     * @~chinese ��ȡ��Դ�嵥�İ汾��
     * @return @~english The manifest version
     * @~chinese ��Դ�嵥�İ汾
     */
    const std::string& getVersion() const;
    
    /** @brief @~english Get the search paths list related to the Manifest.
     * @~chinese Manifest�������·���б�
     * @return @~english The search paths
     * @~chinese ����·���б�
     */
    std::vector<std::string> getSearchPaths() const;
    
protected:
    
    /** @brief @~english Constructor for Manifest class
     * @~chinese Manifest��Դ�嵥��Ĺ��캯��
     * @param manifestUrl @~english Url of the local manifest
     * @~chinese ������Դ�嵥��ַ
     */
    Manifest(const std::string& manifestUrl = "");
    
    /** @brief @~english Load the json file into local json object
     * @~chinese ����json�ļ���json����
     * @param url @~english Url of the json file
     * @~chinese json�ļ���Url
     */
    void loadJson(const std::string& url);
    
    /** @brief @~english Parse the version file information into this manifest
     * @~chinese �����汾�ļ��İ汾��Ϣ�����Manifest
     * @param versionUrl @~english Url of the local version file
     * @~chinese �汾�ļ���Url
     */
    void parseVersion(const std::string& versionUrl);
    
    /** @brief @~english Parse the manifest file information into this manifest
     * @~chinese ����Manifest�ļ���Ϣ
     * @param manifestUrl @~english Url of the local manifest
     * @~chinese Manifest�ı���url��ַ
     */
    void parse(const std::string& manifestUrl);
    
    /** @brief @~english Check whether the version of this manifest equals to another.
     * @~chinese ������Manifest�İ汾�Ƿ������һ��Manifest����
     * @param b   @~english The other manifest
     * @~chinese ��һ��Manifest����
     * @return @~english Return true if the version of this manifest equals to b, otherwise return false.
     * @~chinese �������򷵻�true�����򷵻�false��
     */
    bool versionEquals(const Manifest *b) const;
    
    /** @brief @~english Generate difference between this Manifest and another.
     * @~chinese �������Manifest�������һ��֮�������
     * @param b   @~english The other manifest
     * @~chinese ��һ��Manifest����
     * @return @~english Return the different assets between this manifest and b.
     * @~chinese ���Manifest�������һ��֮��Ĳ�����Դ�б�
     */
    std::unordered_map<std::string, AssetDiff> genDiff(const Manifest *b) const;
    
    /** @brief @~english Generate assets list for resuming previous download.
     * @~chinese ���ɿ������ڻָ�֮ǰһ�����ص���Դ�б�
     * @param units   @~english The download units reference to be modified by the generation result
     * @~chinese ������Դ�б�����ᱻ���������������
     */
    void genResumeAssetsList(DownloadUnits *units) const;
    
    /** @brief @~english Prepend all search paths to the FileUtils.
     * @~chinese ��FileUtils�����Ȳ������Manifest������ص�����·����
     */
    void prependSearchPaths();
    
    void loadVersion(const rapidjson::Document &json);
    
    void loadManifest(const rapidjson::Document &json);
    
    void saveToFile(const std::string &filepath);
    
    Asset parseAsset(const std::string &path, const rapidjson::Value &json);
    
    void clear();
    
    /** @brief @~english Gets all groups.
     * @~chinese ��ȡ�����顣
     */
    const std::vector<std::string>& getGroups() const;
    
    /** @brief @~english Gets all groups version.
     * @~chinese �õ�������İ汾��
     */
    const std::unordered_map<std::string, std::string>& getGroupVerions() const;
    
    /** @brief @~english Gets version for the given group.
     * @~chinese ������İ汾��
     * @param group   @~english Key of the requested group
     * @~chinese ��ļ�ֵ
     */
    const std::string& getGroupVersion(const std::string &group) const;
    
    /** 
     * @brief @~english Gets assets.
     * @~chinese ���������Դ��
     */
    const std::unordered_map<std::string, Asset>& getAssets() const;
    
    /** @brief @~english Set the download state for an asset
     * @~chinese Ϊһ����Դ��������״̬
     * @param key   @~english Key of the asset to set
     * @~chinese Ҫ�޸ĵ���Դ��ֵ
     * @param state @~english The current download state of the asset
     * @~chinese ��Դ�ĵ�ǰ����״̬
     */
    void setAssetDownloadState(const std::string &key, const DownloadState &state);
    
private:
    
    //! Indicate whether the version informations have been fully loaded
    bool _versionLoaded;
    
    //! Indicate whether the manifest have been fully loaded
    bool _loaded;
    
    //! Reference to the global file utils
    FileUtils *_fileUtils;
    
    //! The local manifest root
    std::string _manifestRoot;
    
    //! The remote package url
    std::string _packageUrl;
    
    //! The remote path of manifest file
    std::string _remoteManifestUrl;
    
    //! The remote path of version file [Optional]
    std::string _remoteVersionUrl;
    
    //! The version of local manifest
    std::string _version;
    
    //! All groups exist in manifest [Optional]
    std::vector<std::string> _groups;
    
    //! The versions of all local group [Optional]
    std::unordered_map<std::string, std::string> _groupVer;
    
    //! The version of local engine
    std::string _engineVer;
    
    //! Full assets list
    std::unordered_map<std::string, Asset> _assets;
    
    //! All search paths
    std::vector<std::string> _searchPaths;
    
    rapidjson::Document _json;
};

/**
 * // AssetsManager
 * @}
 */

NS_CC_EXT_END
#endif /* defined(__Manifest__) */
