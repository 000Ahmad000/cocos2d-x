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

#ifndef __AssetsManager__
#define __AssetsManager__

#include <string>

#include <mutex>

#include "2d/CCNode.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"


namespace cocos2d { namespace network {
    class Downloader;
}}

NS_CC_EXT_BEGIN

/**
 * @addtogroup assets_manager
 * @{
 */

class AssetsManagerDelegateProtocol;

/** 
 * @~english
 *  This class is used to auto update resources, such as pictures or scripts.
 *  The updated package should be a zip file. And in the server there should be a file which contains version code.
 * @~chinese 
 * ���������Զ�������Դ����ͼƬ��ű���Դ��
 * ���°���һ��zip������������Ӧ����һ���ļ������а����汾���롣
 */
class CC_EX_DLL AssetsManager : public Node
{
public:
    /** @~english Error code that can be notified to listener
     * @~chinese �ᱻ���ݽo�¼��������Ĵ�������б�
     */
    enum class ErrorCode
    {
        /** @~english Error caused by creating a file to store downloaded data
         * @~chinese �����ļ�ʧ�ܵĴ���
         */
        CREATE_FILE,
        /** @~english Errors caused by network, there are the following possibilities:
         - network unavaivable
         - timeout
         - ...
         * @~chinese ������󣬿��ܵ�ԭ���У�
         * �� ���粻����
         * �� ��ʱ
         * �� ...
         */
        NETWORK,
        /** @~english There is not a new version
         * @~chinese û���°汾
         */
        NO_NEW_VERSION,
        /** @~english Error caused in uncompressing stage
         - can not open zip file
         - can not read file global information
         - can not read file information
         - can not create a directory
         - ...
         * @~chinese ѹ���׶�����Ĵ���
         * �� ���ܴ�ѹ���ļ�
         * - ���ܶ�ȡ�ļ���ȫ����Ϣ
         * �� ���ܶ�ȡ�ļ���Ϣ
         * �� ���ܴ���һ��Ŀ¼
         * �� ...
         */
        UNCOMPRESS,
    };
    
    /* @brief @~english Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @~chinese ʹ���°���URL��ַ���汾�ļ�URL��ַ�ʹ洢·������һ���µ�AssetsManager����
     * 
     * @param packageUrl @~english URL of new package, the package should be a zip file.
     * @~chinese �°���URL���°�Ӧ����һ��zip�ļ���
     * @param versionFileUrl @~english URL of version file. It should contain version code of new package.
     * @~chinese �汾�ļ���URL����Ӧ�ð����°汾�İ汾�š�
     * @param storagePath @~english The path to store downloaded resources.
     * @~chinese �����洢������Դ��·����
     * @return @~english The AssetsManager object when created successfully, otherwise return nullptr.
     * @~chinese �������ɹ�����AssetsManager���󣬷��򷵻�nullptr��
     * @js NA
     * @lua new
     */
    AssetsManager(const char* packageUrl = NULL, const char* versionFileUrl = NULL, const char* storagePath = NULL);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AssetsManager();
    
    typedef std::function<void(int)> ErrorCallback;
    typedef std::function<void(int)> ProgressCallback;
    typedef std::function<void(void)> SuccessCallback;

    /* @brief @~english Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @~chinese ʹ���°���URL��ַ���汾�ļ�URL��ַ���洢·���Լ��ص���������һ���µ�AssetsManager����
     * 
     * @param packageUrl @~english URL of new package, the package should be a zip file.
     * @~chinese �°���URL���°�Ӧ����һ��zip�ļ���
     * @param versionFileUrl @~english URL of version file. It should contain version code of new package.
     * @~chinese �汾�ļ���URL����Ӧ�ð����°汾�İ汾�š�
     * @param storagePath @~english The path to store downloaded resources.
     * @~chinese �����洢������Դ��·����
     * @param errorCallback @~english The callback to invoke when error happens.
     * @~chinese ������ʱ�Ļص�������
     * @param progressCallback @~english The callback to invoke when progression changes.
     * @~chinese ���ع����н��ȸı�ʱ�Ļص�������
     * @param successCallback @~english The callback to invoke when succeed to update.
     * @~chinese �ɹ�����ʱ�Ļص�������
     * @return @~english The AssetsManager object when created successfully, otherwise return nullptr.
     * @~chinese �������ɹ�����AssetsManager���󣬷��򷵻�nullptr��
     * @js NA
     * @lua new
     */
    static AssetsManager* create(const char* packageUrl, const char* versionFileUrl, const char* storagePath, ErrorCallback errorCallback, ProgressCallback progressCallback, SuccessCallback successCallback );

    /* @brief @~english Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     * @~chinese ����Ƿ����°汾����Դ��
     * ����������ַ����ڸ���֮ǰ���û������Ƿ���и��¡�
     * @return @~english Return true if there is a new version, otherwise return false.
     * @~chinese ������°汾�򷵻�true�����򷵻�false��
     */
    virtual bool checkUpdate();
    
    using Node::update;
    /* @brief @~english Download new package if there is a new version, and uncompress downloaded zip file to the predefined storage path.
     *        Of course it will set search path that stores downloaded files.
     * @~chinese ������°汾�������µİ�������ѹ�����ص�zip�ļ���Ԥ��Ĵ洢·����
     * ��Ȼ�����Ὣ�洢·����ӵ�����·���С�
     */
    virtual void update();
    
    /* @brief @~english Gets url of package.
     * @~chinese ��ȡ��Դ����URL��ַ��
     * @return @~english The package url.
     * @~chinese ��Դ����URL��ַ��
     */
    const char* getPackageUrl() const;
    
    /* @brief @~english Sets package url.
     * @~chinese ������Դ����URL��ַ��
     * @param packageUrl @~english The package url.
     * @~chinese ��Դ����URL��ַ��
     */
    void setPackageUrl(const char* packageUrl);
    
    /* @brief @~english Gets version file url.
     * @~chinese ��ȡ�汾�ļ���URL��ַ��
     * @return @~english The version file url.
     * @~chinese �汾�ļ���URL��ַ��
     */
    const char* getVersionFileUrl() const;
    
    /* @brief @~english Sets version file url.
     * @~chinese ���ð汾�ļ���URL��ַ��
     * @param versionFileUrl @~english The version file url.
     * @~chinese �汾�ļ���URL��ַ��
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief @~english Gets the current version code.
     * @~chinese ��ȡ��ǰ�汾�š�
     * @return @~english The current version code.
     * @~chinese ��ǰ�汾�š�
     */
    std::string getVersion();
    
    /* @brief @~english Deletes recorded version code.
     * @~chinese ɾ�����ذ汾�š�
     */
    void deleteVersion();
    
    /* @brief @~english Gets storage path.
     * @~chinese ��ȡ�洢·����
     * @return @~english The storage path.
     * @~chinese �洢·����
     */
    const char* getStoragePath() const;
    
    /* @brief @~english Sets storage path.
     *
     * @~chinese ���ô洢·����
     * 
     * @param storagePath @~english The path to store downloaded resources.
     * @~chinese �洢������Դ��·����
     * @warm @~english The path should be a valid path.
     * @~chinese ���·��������һ����Ч�ı���·����
     */
    void setStoragePath(const char* storagePath);
    
    /** @brief @~english Sets delegate, the delegate will receive messages
     * @~chinese ���ý�����Ϣ�Ĵ���
     * @param delegate @~english The delegate which extends `AssetsManagerDelegateProtocol`.
     * @~chinese �̳���`AssetsManagerDelegateProtocol`�Ĵ������
     * @js NA
     * @lua NA
     */
    void setDelegate(AssetsManagerDelegateProtocol *delegate);
    
    /** @brief @~english Gets delegate, the delegate will receive messages
     * @~chinese ��ȡ������Ϣ�Ĵ���
     * @return @~english The delegate which extends `AssetsManagerDelegateProtocol`.
     * @~chinese �̳���`AssetsManagerDelegateProtocol`�Ĵ������
     * @js NA
     * @lua NA
     */
    AssetsManagerDelegateProtocol* getDelegate() const { return _delegate ;}
    
    /** @brief @~english Sets connection time out in seconds
     * @~chinese �������ӳ�ʱʱ�䣬����Ϊ��λ
     * @param timeout @~english The time out value.
     * @~chinese ���ӳ�ʱʱ�䡣
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief @~english Gets connection time out in secondes
     * @~chinese ��ȡ���ӳ�ʱʱ�䣬����Ϊ��λ
     * @return @~english The time out value.
     * @~chinese ���ӳ�ʱʱ�䡣
     */
    unsigned int getConnectionTimeout();

protected:
    void checkStoragePath();
    bool uncompress();
    void setSearchPath();
    void downloadAndUncompress();

private:
    /** @brief @~english Initializes storage path.
     * @~chinese ��ʼ���洢·����
     */
    void createStoragePath();
    
    /** @brief @~english Destroys storage path.
     * @~chinese ɾ���洢·����
     */
    void destroyStoragePath();
    
private:
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The version of downloaded resources.
    std::string _version;
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    std::string _downloadedVersion;
    
    cocos2d::network::Downloader* _downloader;

    unsigned int _connectionTimeout;
    
    AssetsManagerDelegateProtocol *_delegate; 
    
    bool _isDownloading;
    bool _shouldDeleteDelegateWhenExit;
    
    std::string keyOfVersion() const;
    std::string keyOfDownloadedVersion() const;
};

/** 
 * @~english
 *  This class is the delegate for receving events during update process of AssetsManager.
 * @~chinese 
 * ������������AssetsManager���¹����н����¼��Ĵ���
 * @see AssetsManager
 */
class AssetsManagerDelegateProtocol
{
public:
    virtual ~AssetsManagerDelegateProtocol(){};
public:
    /* @brief @~english Call back function for error
     * @~chinese ��������ʱ�Ļص�����
       @param errorCode @~english Type of error
     * @~chinese �������
     * @js NA
     * @lua NA
     */
    virtual void onError(AssetsManager::ErrorCode errorCode) {};
    /** @brief @~english Call back function for recording downloading percent
     * @~chinese ��¼���ذٷֱȵĻص�����
     * @param percent @~english How much percent downloaded
     * @~chinese �����˶��ٰٷֱ�
     * @warning @~english This call back function just for recording downloading percent.
              AssetsManager will do some other thing after downloading, if you want to manipulate the downloaded files,
              you should write code in onSuccess() after downloading. 
     * @~chinese ����ص�����ֻ��Ϊ�˼�¼���ذٷֱȡ�
     * AssetsManager���غ����һЩ���������飬�������onSuccess�ص����ж����غõ��ļ�����Ӧ�Ĵ���
     * @js NA
     * @lua NA
     */
    virtual void onProgress(int percent) {};
    /** @brief @~english Call back function for success
     * @~chinese ���³ɹ��Ļص�����
     * @js NA
     * @lua NA
     */
    virtual void onSuccess() {};
};

// Deprecated declaration
CC_DEPRECATED_ATTRIBUTE typedef AssetsManager CCAssetsManager;
CC_DEPRECATED_ATTRIBUTE typedef AssetsManagerDelegateProtocol CCAssetsManagerDelegateProtocol;

/**
 * // AssetsManager
 * @}
 */

NS_CC_EXT_END;

#endif /* defined(__AssetsManager__) */
