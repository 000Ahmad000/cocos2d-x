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

#ifndef __AssetsManagerEx__
#define __AssetsManagerEx__

#include <string>
#include <unordered_map>
#include <vector>

#include "base/CCEventDispatcher.h"
#include "platform/CCFileUtils.h"
#include "network/CCDownloader.h"

#include "CCEventAssetsManagerEx.h"

#include "Manifest.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "json/document.h"


NS_CC_EXT_BEGIN

/**
 * @addtogroup assets_manager
 * @{
 */

/**
 * @brief @~english This class is used for resources hot update, you can update images or scripts during runtime of the game.
 * Compare to AssetsManager class, it's a upgraded version. 
 * It's based on manifest configuration files to compare between local version and remote version, 
 * then generate a list of assets which need to be upgraded, download them then finish the update process.
 * It contains the following features:
 * - Multi thread downloading support
 * - Two levels progression support: File level progression and byte level progression
 * - Zip compressed file support
 * - Download resuming
 * - Detailed progression informations and error informations
 * - Possibility to retry failed assets
 * Please refer to this detailed document for its usage: 
 * http://cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/en
 * @~chinese ����������Դ�ȸ���֧�֣�������Ϸ�����ж�̬��Ƭ��ű�����AssetsManager����ȣ�����һ�������汾��֧�ָ�ǿ����ȸ��¹��ܡ�
 * AssetsManagerEx����manifest�����ļ����Ƚϱ��غ�Զ����Դ�İ汾��������Ҫ���µ���Դ�б��������ǲ���ɸ��¹��̡�
 * ����������Ҫ�����ԣ�
 * - ���̲߳�������֧��
 * - �������ͳ����Ϣ���ļ����Լ��ֽڼ�
 * - Zipѹ���ļ�֧��
 * - �ϵ�����
 * - ��ϸ�Ĵ��󱨸�
 * - �ļ�����ʧ������֧��
 * ��ϸ��ʹ�÷�ʽ����ο�������ĵ��� 
 * http://cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/zh
 */
class CC_EX_DLL AssetsManagerEx : public Ref
{
public:
    
    /** @~english Update states
     * @~chinese �ȸ���״̬�б�
     */
    enum class State
    {
        /** @~english Unchecked whether there is a new version
         * @~chinese ��δ����Ƿ�����°汾
         */
        UNCHECKED,
        /** @~english Before downloading the version manifest file
         * @~chinese �����ذ汾manifest�ļ�֮ǰ
         */
        PREDOWNLOAD_VERSION,
        /** @~english Downloading the version manifest file
         * @~chinese �������ذ汾manifest�ļ�
         */
        DOWNLOADING_VERSION,
        /** @~english After successfully downloaded and parsed the version manifest
         * @~chinese �ɹ����ز������汾manifest֮��
         */
        VERSION_LOADED,
        /** @~english Before downloading the resources manifest file
         * @~chinese ��������Դmanifest�ļ�֮ǰ
         */
        PREDOWNLOAD_MANIFEST,
        /** @~english Downloading the resources manifest file
         * @~chinese ����������Դmanifest�ļ�
         */
        DOWNLOADING_MANIFEST,
        /** @~english After successfully downloaded and parsed the resources manifest
         * @~chinese �ɹ����ز�������Դmanifest֮��
         */
        MANIFEST_LOADED,
        /** @~english New version detected, needed to be updated
         * @~chinese ��鵽�°汾����Ҫ����
         */
        NEED_UPDATE,
        /** @~english Updating new version
         * @~chinese ������
         */
        UPDATING,
        /** @~english Updated to the latest version
         * @~chinese �Ѹ��µ����°汾
         */
        UP_TO_DATE,
        /** @~english Failed to update new version
         * @~chinese ����ʧ��
         */
        FAIL_TO_UPDATE
    };
    
    const static std::string VERSION_ID;
    const static std::string MANIFEST_ID;
    
    /** @brief @~english Create function for creating a new AssetsManagerEx, use local manifest path and storage path as parameters.
     * @~chinese AssetsManagerEx�Ĺ��캯����ʹ�ñ���manifest�ļ���ַ����Դ�洢·����Ϊ������
     @param manifestUrl   @~english The url for the local manifest file
     * @~chinese ������Դmanifest�ļ���ַ
     @param storagePath   @~english The storage path for downloaded assetes
     * @~chinese ��Դ�Ĵ洢·��
     @warning @~english   The cached manifest in your storage path have higher priority and will be searched first,
                only if it doesn't exist, AssetsManagerEx will use the given manifestUrl.
     * @~chinese ��Դ�洢·���л����manifest�ļ��Ȱ��ڵ�ԭʼmanifest�ļ��и��ߵ����ȼ������Ȼ�����Ƿ��л����manifest��
     * ֻ�е���������ʱ��AssetsManagerEx�Ž�ʹ��ָ����manifestUrl��
     */
    static AssetsManagerEx* create(const std::string &manifestUrl, const std::string &storagePath);
    
    /** @brief @~english  Check out if there is a new version of manifest.
     *          You may use this method before updating, then let user determine whether
     *          he wants to update resources.
     * @~chinese ����Ƿ����°汾��
     * ����������ַ����ڸ���֮ǰ���û������Ƿ�Ҫ������Դ��
     */
    void checkUpdate();
    
    /** @brief @~english Update with the current local manifest.
     * @~chinese ���Ը�����Դ
     */
    void update();
    
    /** @brief @~english Reupdate all failed assets under the current AssetsManagerEx context, failed assets are noted in the previous update process.
     * @~chinese ������������ʧ�ܵ���Դ����Щʧ�ܵ���Դ����ǰһ�θ��¹����м�¼������
     */
    void downloadFailedAssets();
    
    /** @brief @~english Gets the current update state.
     * @~chinese ��ȡ��ǰ���µ�״̬��
     * @return @~english The current update state.
     * @~chinese ����״̬
     */
    State getState() const;
    
    /** @brief @~english Gets storage path.
     * @~chinese ��ȡ�洢·����
     * @return @~english The storage path.
     * @~chinese �洢·��
     */
    const std::string& getStoragePath() const;
    
    /** @brief @~english Function for retrieve the local manifest object.
     * @~chinese ��ȡ������Դ�嵥����
     * @return @~english The local manifest.
     * @~chinese ���ص���Դ�嵥
     */
    const Manifest* getLocalManifest() const;
    
    /** @brief @~english Function for retrieve the remote manifest object
     * @~chinese ��ȡԶ����Դ�嵥����
     * @return @~english The remote manifest.
     * @~chinese Զ�̵���Դ�嵥
     */
    const Manifest* getRemoteManifest() const;
    
CC_CONSTRUCTOR_ACCESS:
    
    AssetsManagerEx(const std::string& manifestUrl, const std::string& storagePath);
    
    virtual ~AssetsManagerEx();
    
protected:
    
    std::string basename(const std::string& path) const;
    
    std::string get(const std::string& key) const;
    
    void initManifests(const std::string& manifestUrl);
    
    void loadLocalManifest(const std::string& manifestUrl);
    
    void prepareLocalManifest();
    
    void setStoragePath(const std::string& storagePath);
    
    void adjustPath(std::string &path);
    
    void dispatchUpdateEvent(EventAssetsManagerEx::EventCode code, const std::string &message = "", const std::string &assetId = "", int curle_code = 0, int curlm_code = 0);
    
    void downloadVersion();
    void parseVersion();
    void downloadManifest();
    void parseManifest();
    void startUpdate();
    void updateSucceed();
    bool decompress(const std::string &filename);
    void decompressDownloadedZip();
    
    /** @brief @~english Update a list of assets under the current AssetsManagerEx context
     * @~chinese ����һ�������б��е���Դ
     */
    void updateAssets(const DownloadUnits& assets);
    
    /** @brief @~english Retrieve all failed assets during the last update
     * @~chinese ��ȡ�ϴθ���ʧ��ʱ��ʧ����Դ�б�
     */
    const DownloadUnits& getFailedAssets() const;
    
    /** @brief @~english Function for destorying the downloaded version file and manifest file
     * @~chinese ������������ذ汾
     */
    void destroyDownloadedVersion();
    
    /** @brief @~english  Call back function for error handling,
     * the error will then be reported to user's listener registed in EventListenerAssetsManagerEx
     * @~chinese ��Դ����ʧ��ʱ�Ļص�����,
     * ������󽫱�������û���EventListenerAssetsManagerEx��ע��ļ�����
     * @param error @~english The error object contains ErrorCode, message, asset url, asset key
     * @~chinese ����Ķ������������롢��Ϣ����ԴURL��ַ����Դ��������ֵ
     * @warning @~english AssetsManagerEx internal use only
     * @~chinese ����AssetsManagerEx�ڲ�ʹ��
     * @js NA
     * @lua NA
     */
    virtual void onError(const network::DownloadTask& task,
                         int errorCode,
                         int errorCodeInternal,
                         const std::string& errorStr);
    
    /** @brief @~english  Call back function for recording downloading percent of the current asset,
     the progression will then be reported to user's listener registed in addUpdateProgressEventListener
     * @~chinese ��¼��Դ���صİٷֱȵĻص�������
     * ����Ľ�չ����������û���EventListenerAssetsManagerEx��ע��ļ�����
     @param total       @~english Total size to download for this asset
     * @~chinese ����Դ���ܴ�С
     @param downloaded  @~english Total size already downloaded for this asset
     * @~chinese ����Դ�Ѿ����صĲ��ִ�С
     @param url         @~english The url of this asset
     * @~chinese ����Դ��URL��ַ
     @param customId    @~english The key of this asset
     * @~chinese ����Դ��������ֵ
     @warning @~english AssetsManagerEx internal use only
     * @~chinese ����AssetsManagerEx�ڲ�ʹ��
     * @js NA
     * @lua NA
     */
    virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);
    
    /** @brief @~english  Call back function for success of the current asset
     the success event will then be send to user's listener registed in addUpdateEventListener
     * @~chinese ��Դ���سɹ��Ļص�����
     * ��Դ���سɹ����¼��������͵���EventListenerAssetsManagerEx��ע��ļ�����
     @param srcUrl      @~english The url of this asset
     * @~chinese ����Դ��url
     @param customId    @~english The key of this asset
     * @~chinese ����Դ��������ֵ
     @warning @~english AssetsManagerEx internal use only
     * @~chinese ����AssetsManagerEx�ڲ�ʹ��
     * @js NA
     * @lua NA
     */
    virtual void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    
private:
    void batchDownload();
    
    //! The event of the current AssetsManagerEx in event dispatcher
    std::string _eventName;
    
    //! Reference to the global event dispatcher
    EventDispatcher *_eventDispatcher;
    //! Reference to the global file utils
    FileUtils *_fileUtils;
    
    //! State of update
    State _updateState;
    
    //! Downloader
    std::shared_ptr<network::Downloader> _downloader;
    
    //! The reference to the local assets
    const std::unordered_map<std::string, Manifest::Asset> *_assets;
    
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The local path of cached version file
    std::string _cacheVersionPath;
    
    //! The local path of cached manifest file
    std::string _cacheManifestPath;
    
    //! The local path of cached temporary manifest file
    std::string _tempManifestPath;
    
    //! The path of local manifest file
    std::string _manifestUrl;
    
    //! Local manifest
    Manifest *_localManifest;
    
    //! Local temporary manifest for download resuming
    Manifest *_tempManifest;
    
    //! Remote manifest
    Manifest *_remoteManifest;
    
    //! Whether user have requested to update
    bool _waitToUpdate;
    
    //! All assets unit to download
    DownloadUnits _downloadUnits;
    
    //! All failed units
    DownloadUnits _failedUnits;
    
    //! All files to be decompressed
    std::vector<std::string> _compressedFiles;
    
    //! Download percent
    float _percent;
    
    //! Download percent by file
    float _percentByFile;
    
    //! Indicate whether the total size should be enabled
    int _totalEnabled;
    
    //! Indicate the number of file whose total size have been collected
    int _sizeCollected;
    
    //! Total file size need to be downloaded (sum of all file)
    double _totalSize;
    
    //! Downloaded size for each file
    std::unordered_map<std::string, double> _downloadedSize;
    
    //! Total number of assets to download
    int _totalToDownload;
    //! Total number of assets still waiting to be downloaded
    int _totalWaitToDownload;
    
    //! Marker for whether the assets manager is inited
    bool _inited;
};

/**
 * // AssetsManager
 * @}
 */

NS_CC_EXT_END

#endif /* defined(__AssetsManagerEx__) */
