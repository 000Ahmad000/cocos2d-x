/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
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
#ifndef __CC_FILEUTILS_H__
#define __CC_FILEUTILS_H__

#include <string>
#include <vector>
#include <unordered_map>

#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"
#include "base/CCValue.h"
#include "base/CCData.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/** @~english Helper class to handle file operations.  @~chinese �����ļ�������ͨ�ù����ࡣ*/
class CC_DLL FileUtils
{
public:
    /**@~english
     *  Gets the instance of FileUtils.
     * @~chinese 
     * ��ȡFileUtils��ʵ����
     */
    static FileUtils* getInstance();

    /**@~english
     *  Destroys the instance of FileUtils.
     * @~chinese 
     * ����FileUtils��ʵ����
     */
    static void destroyInstance();
    
    /**@~english
     * You can inherit from platform dependent implementation of FileUtils, such as FileUtilsAndroid,
     * and use this function to set delegate, then FileUtils will invoke delegate's implementation.
     * For example, your resources are encrypted, so you need to decrypt it after reading data from
     * resources, then you can implement all getXXX functions, and engine will invoke your own getXX
     * functions when reading data of resources.
     *
     * If you don't want to system default implementation after setting delegate, you can just pass nullptr
     * to this function.
     *
     * @~chinese 
     * ����ԴӸ���ƽ̨���ļ�������ʵ���м̳�,���� FileUtilsAndroid, Ȼ��
     * ʹ��������������ô���,Ȼ��FileUtils�����ô����ʵ�֡�
     * ����,�����Դ�Ǽ��ܵ�,�������Ҫ��ȡ���ݺ����Դ���н���,
     * Ȼ��������ʵ������getXXX����,����ȡ��Դ����ʱ�����潫�������Լ���getXX���ܡ�
     * 
     * 
     * �����ô��������㲻��ҪϵͳĬ��ʵ�ֵĴ���,��Ϳ���ͨ�������������ֵΪnullptr
     * 
     * 
     * @warning @~english It will delete previous delegate
     * @~chinese ����ɾ����ǰ��delegate
     * @lua NA
     */
    static void setDelegate(FileUtils *delegate);

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static FileUtils* sharedFileUtils() { return getInstance(); }

    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeFileUtils() { destroyInstance(); }

    /**@~english
     *  The destructor of FileUtils.
     * @~chinese 
     * FileUtils������������
     * @js NA
     * @lua NA
     */
    virtual ~FileUtils();
    
    /**@~english
     *  Purges full path caches.
     * @~chinese 
     * ���·�����档
     */
    virtual void purgeCachedEntries();
    
    /**@~english
     * Gets string from a file.
     * @~chinese 
     * ��һ���ļ����ݶ�ȡΪ�ַ�����
     */
    virtual std::string getStringFromFile(const std::string& filename);
    
    /**@~english
     * Creates binary data from a file.
     * @~chinese 
     * ��һ���ļ����ݶ�ȡΪ���������ݡ�
     *  @return @~english A data object.
     * @~chinese һ�����ݶ���
     */
    virtual Data getDataFromFile(const std::string& filename);
    
    /**@~english
     *  Gets resource file data
     *  @~chinese 
     *  ��ȡ��Դ�ļ�����
     *  @param filename @~english The resource file name which contains the path.
     *             @~chinese ����·������Դ�ļ����ơ�
     *  @param mode @~english The read mode of the file. property like fopen function mode @~chinese �ļ��Ķ�ȡģʽ,������fopenģʽ��ͬ��
     *  @param size @~english If the file read succeeds, it will be the data size, otherwise 0. 
     *               @~chinese ����ļ���ȡ�ɹ�,���������ݴ�С,����Ϊ0��
     * 
     *  @return @~english Upon success, a pointer to the data is returned, otherwise NULL.
     * @~chinese �ڳɹ�ʱ,����һ��ָ�����ݵ�ָ��,����Ϊ�ա�
     *  @warning @~english Recall: you are responsible for calling free() on any Non-NULL pointer returned.
     * @~chinese �ǵ�: ������ص�ָ���Ƿǿյģ�����Ҫ�������free�����ͷ���
     */
    CC_DEPRECATED_ATTRIBUTE virtual unsigned char* getFileData(const std::string& filename, const char* mode, ssize_t *size);

    /**@~english
     *  Gets resource file data from a zip file.
     * @~chinese 
     *  ��һ��zip�ļ���ȡ��Դ�ļ����ݡ�
     *  @param zipFilePath @~english The resource zip file path.
     *                  @~chinese zip�ļ���·����
     *  @param filename @~english The resource file path and name relative to the zip file.
     *                  @~chinese ��Դ��zip�ļ��е����·����
     *  @param size @~english If the file read operation succeeds, it will be the data size, otherwise 0.
     *              @~chinese ����ļ���ȡ�ɹ�,���������ݴ�С,����Ϊ0��
     * 
     *  @return @~english Upon success, a pointer to the data is returned, otherwise nullptr.
     * @~chinese �ڳɹ�ʱ,����һ��ָ�����ݵ�ָ��,����nullptr��
     *  @warning @~english Recall: you are responsible for calling free() on any Non-nullptr pointer returned.
     * @~chinese �ǵ�:������ص�ָ���Ƿǿյģ�����Ҫ�������free�����ͷ���
     */
    virtual unsigned char* getFileDataFromZip(const std::string& zipFilePath, const std::string& filename, ssize_t *size);

    
    /** @~english Returns the fullpath for a given filename.
     
     First it will try to get a new filename from the "filenameLookup" dictionary.
     If a new filename can't be found on the dictionary, it will use the original filename.
     Then it will try to obtain the full path of the filename using the FileUtils search rules: resolutions, and search paths.
     The file search is based on the array element order of search paths and resolution directories.

     For instance:

         We set two elements("/mnt/sdcard/", "internal_dir/") to search paths vector by setSearchPaths,
         and set three elements("resources-ipadhd/", "resources-ipad/", "resources-iphonehd")
         to resolutions vector by setSearchResolutionsOrder. The "internal_dir" is relative to "Resources/".

        If we have a file named 'sprite.png', the mapping in fileLookup dictionary contains `key: sprite.png -> value: sprite.pvr.gz`.
         Firstly, it will replace 'sprite.png' with 'sprite.pvr.gz', then searching the file sprite.pvr.gz as follows:

             /mnt/sdcard/resources-ipadhd/sprite.pvr.gz      (if not found, search next)
             /mnt/sdcard/resources-ipad/sprite.pvr.gz        (if not found, search next)
             /mnt/sdcard/resources-iphonehd/sprite.pvr.gz    (if not found, search next)
             /mnt/sdcard/sprite.pvr.gz                       (if not found, search next)
             internal_dir/resources-ipadhd/sprite.pvr.gz     (if not found, search next)
             internal_dir/resources-ipad/sprite.pvr.gz       (if not found, search next)
             internal_dir/resources-iphonehd/sprite.pvr.gz   (if not found, search next)
             internal_dir/sprite.pvr.gz                      (if not found, return "sprite.png")

        If the filename contains relative path like "gamescene/uilayer/sprite.png",
        and the mapping in fileLookup dictionary contains `key: gamescene/uilayer/sprite.png -> value: gamescene/uilayer/sprite.pvr.gz`.
        The file search order will be:

             /mnt/sdcard/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz      (if not found, search next)
             /mnt/sdcard/gamescene/uilayer/resources-ipad/sprite.pvr.gz        (if not found, search next)
             /mnt/sdcard/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz    (if not found, search next)
             /mnt/sdcard/gamescene/uilayer/sprite.pvr.gz                       (if not found, search next)
             internal_dir/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz     (if not found, search next)
             internal_dir/gamescene/uilayer/resources-ipad/sprite.pvr.gz       (if not found, search next)
             internal_dir/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz   (if not found, search next)
             internal_dir/gamescene/uilayer/sprite.pvr.gz                      (if not found, return "gamescene/uilayer/sprite.png")

     If the new file can't be found on the file system, it will return the parameter filename directly.

     This method was added to simplify multiplatform support. Whether you are using cocos2d-js or any cross-compilation toolchain like StellaSDK or Apportable,
     you might need to load different resources for a given file in the different platforms.

     * @~chinese ����һ���������ļ��������������ļ�·����
     * 
     * �����������Դ��ļ��ֵ�õ�һ�����ļ�����
     * ������ֵ��в����ҵ����ļ���,����ʹ��ԭ�����ļ�����
     * Ȼ���������Զ����Ҫ��ȡ������·���ļ���, ʹ���ļ����������������������:�ֱ���,������·����
     * �ļ������ǻ�������Ԫ�ص�����·���ͷֱ���Ŀ¼��˳���������ġ�
     * 
     * ����:
     * 
     * ���ǽ�����Ԫ��("/mnt/sdcard/", "internal_dir/") ͨ�� setSearchPaths ������������·��������
     * ����������Ԫ��("resources-ipadhd/", "resources-ipad/", "resources-iphonehd")
     * ͨ�� setSearchResolutionsOrder ���õ��ֱ��ʼ����С���� ��internal_dir�� Ŀ¼��·�� ������ڸ�Ŀ¼��·���� "Resources/"
     * 
     * ���������һ���ļ���Ϊ'sprite.png',fileLookup�ֵ��е�ӳ����� `key: sprite.png -> value: sprite.pvr.gz`.
     * ����,�����ļ�������'sprite.png'���'sprite.pvr.gz'��Ȼ��ͨ�����¼�������������'sprite.pvr.gz'�ļ�:
     * 
     * 
            /mnt/sdcard/resources-ipadhd/sprite.pvr.gz      (����Ҳ������������һ��)
            /mnt/sdcard/resources-ipad/sprite.pvr.gz        (����Ҳ������������һ��)
            /mnt/sdcard/resources-iphonehd/sprite.pvr.gz    (����Ҳ������������һ��)
            /mnt/sdcard/sprite.pvr.gz                       (����Ҳ������������һ��)
            internal_dir/resources-ipadhd/sprite.pvr.gz     (����Ҳ������������һ��)
            internal_dir/resources-ipad/sprite.pvr.gz       (����Ҳ������������һ��)
            internal_dir/resources-iphonehd/sprite.pvr.gz   (����Ҳ������������һ��)
            internal_dir/sprite.pvr.gz                      (����Ҳ������򷵻� "sprite.png")
     * 
     * �������ļ����������·��,�� "gamescene/uilayer/sprite.png",
     * ����fileLookup�ֵ��ӳ���ϵ��`key: gamescene/uilayer/sprite.png -> value: gamescene/uilayer/sprite.pvr.gz`.
     * ����ļ�����˳�򽫻���:
     * 
     * 
            /mnt/sdcard/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz      (����Ҳ������������һ��)
            /mnt/sdcard/gamescene/uilayer/resources-ipad/sprite.pvr.gz        (����Ҳ������������һ��)
            /mnt/sdcard/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz    (����Ҳ������������һ��)
            /mnt/sdcard/gamescene/uilayer/sprite.pvr.gz                       (����Ҳ������������һ��)
            internal_dir/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz     (����Ҳ������������һ��)
            internal_dir/gamescene/uilayer/resources-ipad/sprite.pvr.gz       (����Ҳ������������һ��)
            internal_dir/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz   (����Ҳ������������һ��)
            internal_dir/gamescene/uilayer/sprite.pvr.gz                      (����Ҳ������򷵻� "gamescene/uilayer/sprite.png")
     * 
     * �������µ��ļ������ļ�ϵͳ���޷��ҵ�,����ֱ�ӷ��ش����������ļ�����
     * 
     * ���ַ��������ӣ����˶�ƽ̨֧�֡���������ʹ��Cocos2d-JS���κν�����빤����StellaSDK��Apportable��
     * ֻҪһ���������ļ��㶼�ܹ��ڶ�Ӧ��ͬ��ƽ̨�ϼ�����Ӧ����Դ��
     * 
     @since v2.1
     */
    virtual std::string fullPathForFilename(const std::string &filename) const;
    
    /**@~english
     * Loads the filenameLookup dictionary from the contents of a filename.
     * 
     * @~chinese 
     * ͨ��һ���ļ��е����ݼ���filenameLookup�ֵ䡣
     * 
     * @note @~english The plist file name should follow the format below:
     * 
     * @~chinese plist�ļ�����Ӧ��ѭ���¸�ʽ:
     * 
     * @code
     * <?xml version="1.0" encoding="UTF-8"?>
     * <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
     * <plist version="1.0">
     * <dict>
     *     <key>filenames</key>
     *     <dict>
     *         <key>sounds/click.wav</key>
     *         <string>sounds/click.caf</string>
     *         <key>sounds/endgame.wav</key>
     *         <string>sounds/endgame.caf</string>
     *         <key>sounds/gem-0.wav</key>
     *         <string>sounds/gem-0.caf</string>
     *     </dict>
     *     <key>metadata</key>
     *     <dict>
     *         <key>version</key>
     *         <integer>1</integer>
     *     </dict>
     * </dict>
     * </plist>
     * @endcode
     * @param filename @~english The plist file name.
     *
     * @~chinese plist�ļ����ơ�
     * 
     @since v2.1
     * @js loadFilenameLookup
     * @lua loadFilenameLookup
     */
    virtual void loadFilenameLookupDictionaryFromFile(const std::string &filename);
    
    /** @~english
     *  Sets the filenameLookup dictionary.
     *
     * @~chinese 
     * ����filenameLookup�ֵ䡣
     * 
     *  @param filenameLookupDict @~english The dictionary for replacing filename.
     * @~chinese �����滻�ļ������ֵ䡣
     *  @since v2.1
     */
    virtual void setFilenameLookupDictionary(const ValueMap& filenameLookupDict);
    
    /**@~english
     *  Gets full path from a file name and the path of the relative file.
     * @~chinese 
     * ��һ���ļ�������Ե�·���ļ��õ�����·����
     *  @param filename @~english The file name.
     * @~chinese �ļ������֡�
     *  @param relativeFile @~english The path of the relative file.
     * @~chinese ��Ե�·���ļ���
     *  @return @~english The full path.
     *          e.g. filename: hello.png, pszRelativeFile: /User/path1/path2/hello.plist
     *               Return: /User/path1/path2/hello.pvr (If there a a key(hello.png)-value(hello.pvr) in FilenameLookup dictionary. )
     *
     * @~chinese ��������ļ����������ļ�·����
        ����. filename: hello.png, pszRelativeFile: /User/path1/path2/hello.plist
     *  Return: /User/path1/path2/hello.pvr (�����FilenameLookup�ֵ����������ֵ��(hello.png)-value(hello.pvr))
     * 
     */
    virtual std::string fullPathFromRelativeFile(const std::string &filename, const std::string &relativeFile);

    /** @~english
     *  Sets the array that contains the search order of the resources.
     *
     * @~chinese 
     * ���ð�����Դ����˳�������
     * 
     *  @param searchResolutionsOrder @~english The source array that contains the search order of the resources.
     * @~chinese ��������������Դ����˳��
     *  @see getSearchResolutionsOrder(), fullPathForFilename(const char*).
     *  @since v2.1@~english
     *  In js:var setSearchResolutionsOrder(var jsval)
     * @~chinese 
     * js:var setSearchResolutionsOrder(var jsval)
     *  @lua NA
     */
    virtual void setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder);

    /**@~english
      * Append search order of the resources.
      *
      * @~chinese 
      * ��ӵ���Դ����˳��
      * 
      * @see setSearchResolutionsOrder(), fullPathForFilename().
      * @since v2.1
      */
    virtual void addSearchResolutionsOrder(const std::string &order,const bool front=false);
    
    /**@~english
     *  Gets the array that contains the search order of the resources.
     *
     * @~chinese 
     * ��ȡ������Դ������˳�������
     * 
     *  @see setSearchResolutionsOrder(const std::vector<std::string>&), fullPathForFilename(const char*).
     *  @since v2.1
     *  @lua NA
     */
    virtual const std::vector<std::string>& getSearchResolutionsOrder() const;
    
    /** @~english
     *  Sets the array of search paths.
     *
     *  You can use this array to modify the search path of the resources.
     *  If you want to use "themes" or search resources in the "cache", you can do it easily by adding new entries in this array.
     *
     * @~chinese 
     * ��������·�������顣
     * 
     * ������ʹ����������޸���Դ������·����
     * �������ʹ�û����������������Դ,������׿���������ֻҪ������������µ���Ŀ�Ϳ����ˡ�
     * 
     *  @note @~english This method could access relative path and absolute path.
     *        If the relative path was passed to the vector, FileUtils will add the default resource directory before the relative path.
     *        For instance:
     *            On Android, the default resource root path is "assets/".
     *            If "/mnt/sdcard/" and "resources-large" were set to the search paths vector,
     *            "resources-large" will be converted to "assets/resources-large" since it was a relative path.
     *
     * @~chinese ��������ȿ��Է��ʾ���·���ֿ��Է������·����
     * ��������ϴ��ݵ���һ�����·�����ļ����������������·����ǰ�����Ĭ�ϵ���ԴĿ¼
     * ����:
     * ��Android�ϣ�Ĭ�ϵ���Դ��·���� "assets/".
     * �����"/mnt/sdcard/" ��"resources-large" ���ݵ� ����·���ļ�����,��Ϊ����һ�����·����
     * ����"resources-large" �ᱻת���� "assets/resources-large" 
     * 
     *  @param searchPaths @~english The array contains search paths.
     * @~chinese �������������·����
     *  @see fullPathForFilename(const char*)
     *  @since v2.1@~english
     *  In js:var setSearchPaths(var jsval);
     * @~chinese 
     * js:var setSearchPaths(var jsval);
     *  @lua NA
     */
    virtual void setSearchPaths(const std::vector<std::string>& searchPaths);
    
    /**@~english
     * Set default resource root path.
     * @~chinese 
     * ����Ĭ����Դ��·����
     */
    void setDefaultResourceRootPath(const std::string& path);

    /**@~english
      * Add search path.
      *
     * @~chinese 
     * �������·����
     * 
      * @since v2.1
      */
    void addSearchPath(const std::string & path, const bool front=false);
    
    /**@~english
     *  Gets the array of search paths.
     *  
     * @~chinese 
     * ��ȡ���������·����
     * 
     *  @return @~english The array of search paths.
     * @~chinese ���������·����
     *  @see fullPathForFilename(const char*).
     *  @lua NA
     */
    virtual const std::vector<std::string>& getSearchPaths() const;

    /**@~english
     *  Gets the writable path.
     * @~chinese 
     *  ��ȡ��д��·��
     *  @return  @~english The path that can be write/read a file in
     * @~chinese ����д/���ļ���·��
     */
    virtual std::string getWritablePath() const = 0;
    
    /**@~english
     *  Sets writable path.
     * @~chinese 
     * ���ÿ�д��·����
     */
    virtual void setWritablePath(const std::string& writablePath);

    /**@~english
     *  Sets whether to pop-up a message box when failed to load an image.
     * @~chinese 
     * ���õ�ͼƬ����ʧ�ܵ�ʱ���Ƿ񵯳�һ����Ϣ��
     */
    virtual void setPopupNotify(bool notify);
    
    /** @~english Checks whether to pop up a message box when failed to load an image. 
     * @~chinese ��鵱ͼƬ����ʧ�ܵ�ʱ���Ƿ񵯳�һ����Ϣ��
     *  @return @~english True if pop up a message box when failed to load an image, false if not.
     * @~chinese ���ͼƬ����ʧ�ܵ�ʱ��ᵯ��һ����Ϣ���򷵻�true�����򷵻�false.
     */
    virtual bool isPopupNotify() const;

    /**@~english
     *  Converts the contents of a file to a ValueMap.
     * @~chinese 
     * ��һ���ļ�������ת��ΪValueMap��
     *  @param filename @~english The filename of the file to gets content.
     * @~chinese Ҫ��ȡ���ݵĶ�Ӧ�ļ����ļ�����
     *  @return @~english ValueMap of the file contents.
     * @~chinese �ļ������ݡ�
     *  @note @~english This method is used internally.
     * @~chinese �÷������ڲ�ʹ�á�
     */
    virtual ValueMap getValueMapFromFile(const std::string& filename);

  /**   @~english Converts the contents of a file to a ValueMap.
    *   @~chinese ���ļ�������ת����ValueMap
    *   @note @~english This method is used internally.
    *   @~chinese �÷������ڲ�ʹ�á�
    */
    virtual ValueMap getValueMapFromData(const char* filedata, int filesize);

    /** @~english Write a ValueMap to a plist file.
    *   @~chinese ��ValueMap,д�뵽�ļ���
    * @param dict @~english the data which want to write into file
    *             @~chinese ��Ҫд���ļ������ݡ�
    * @param fullPath @~english file fullpath
    *             @~chinese �ļ�����·��
    * @note @~english This method is used internally.
    *   @~chinese �÷������ڲ�ʹ�á�
    */
    virtual bool writeToFile(ValueMap& dict, const std::string& fullPath);

    /**
     *  write a string into a file
     *
     * @param dataStr the string want to save
     * @param fullPath The full path to the file you want to save a string
     * @return bool True if write success
     */
    virtual bool writeStringToFile(std::string dataStr, const std::string& fullPath);


    /**
     * write Data into a file
     *
     *@param retData the data want to save
     *@param fullPath The full path to the file you want to save a string
     *@return bool
     */
    virtual bool writeDataToFile(Data retData, const std::string& fullPath);

    /**
    * write ValueMap into a plist file
    *
    *@param dict the ValueMap want to save
    *@param fullPath The full path to the file you want to save a string
    *@return bool
    */
    virtual bool writeValueMapToFile(ValueMap& dict, const std::string& fullPath);

    /**
    * write ValueVector into a plist file
    *
    *@param vecData the ValueVector want to save
    *@param fullPath The full path to the file you want to save a string
    *@return bool
    */
    virtual bool writeValueVectorToFile(ValueVector vecData, const std::string& fullPath);

    /**@~english
    * Windows fopen can't support UTF-8 filename
    * Need convert all parameters fopen and other 3rd-party libs
    *
     * @~chinese 
     * Windows fopen����֧��utf - 8�ļ���
     * ��Ҫʹ�õ������⽫fopen�����в�������ת��
     * 
    * @param filenameUtf8 @~english std::string name file for convertation from utf-8
     * @~chinese ��Ҫת���ɵ�utf-8�ļ����ļ���
    * @return @~english std::string ansi filename in current locale
     * @~chinese ��ǰ�����±�׼ansi���ļ���
    */
    virtual std::string getSuitableFOpen(const std::string& filenameUtf8) const;
    
    /**@~english Converts the contents of a file to a ValueVector.
    * @~chinese ���ļ�ת����ValueVector
    * @note @~english This method is used internally.
    *   @~chinese �÷������ڲ�ʹ�á�
    */
    virtual ValueVector getValueVectorFromFile(const std::string& filename);
    
    /**@~english
     *  Checks whether a file exists.
     *
     * @~chinese 
     * ���һ���ļ��Ƿ���ڡ�
     * 
     *  @note @~english If a relative path was passed in, it will be inserted a default root path at the beginning.
     * @~chinese ������ݽ����Ĳ�����һ�����·�����������俪ͷ����һ��Ĭ�ϵĸ�·��
     *  @param filename @~english The path of the file, it could be a relative or absolute path.
     * @~chinese �ļ���·���������Ǿ���·����Ҳ���������·��
     *  @return @~english True if the file exists, false if not.
     * @~chinese ����ļ����ڷ���true�����򷵻�false
     */
    virtual bool isFileExist(const std::string& filename) const;

    /**
    *  Gets filename extension is a suffix (separated from the base filename by a dot) in lower case.
    *  Examples of filename extensions are .png, .jpeg, .exe, .dmg and .txt.
    *  @param filePath The path of the file, it could be a relative or absolute path.
    *  @return suffix for filename in lower case or empty if a dot not found.
    */
    virtual std::string getFileExtension(const std::string& filePath) const;

    /**@~english
     *  Checks whether the path is an absolute path.
     *
     * @~chinese 
     * ���·���ǲ��Ǿ���·����
     * 
     *  @note @~english On Android, if the parameter passed in is relative to "assets/", this method will treat it as an absolute path.
     *        Also on Blackberry, path starts with "app/native/Resources/" is treated as an absolute path.
     *
     * @~chinese ��Androidƽ̨�ϣ�������ݽ����Ĳ����������"assets/"����������ͻ�������ɾ���·��
     * ��blackBarryƽ̨�ϣ���"app/native/Resources/"��ͷ��·�������ɾ���·��
     * 
     *  @param path @~english The path that needs to be checked.
     * @~chinese ��Ҫ����·��
     *  @return @~english True if it's an absolute path, false if not.
     * @~chinese ����Ǿ���·������true�����򷵻�false
     */
    virtual bool isAbsolutePath(const std::string& path) const;
    
    /**@~english
     *  Checks whether the path is a directory.
     *
     * @~chinese 
     * ���һ��·���Ƿ���Ŀ¼��
     * 
     *  @param dirPath @~english The path of the directory, it could be a relative or an absolute path.
     * @~chinese Ŀ¼��·���������Ǿ���·����Ҳ���������·��
     *  @return @~english True if the directory exists, false if not.
     * @~chinese ���Ŀ¼���ڷ���true�����򷵻�false
     */
    virtual bool isDirectoryExist(const std::string& dirPath) const;
    
    /**@~english
     *  Creates a directory.
     *
     * @~chinese 
     * ����һ��Ŀ¼��
     * 
     *  @param dirPath @~english The path of the directory, it must be an absolute path.
     * @~chinese Ŀ¼��·��,��������һ������·����
     *  @return @~english True if the directory have been created successfully, false if not.
     * @~chinese ����ɹ�������Ŀ¼����true,�������ʧ�ܷ���false
     */
    virtual bool createDirectory(const std::string& dirPath);
    
    /**@~english
     *  Removes a directory.
     *
     * @~chinese 
     * ɾ��һ��Ŀ¼��
     * 
     *  @param dirPath  @~english The path of the directory, it must be an absolute path.
     * @~chinese Ŀ¼��·��,��������һ������·����
     *  @return @~english True if the directory have been removed successfully, false if not.
     * @~chinese ����ɹ�ɾ����Ŀ¼����true,���ɾ��ʧ�ܷ���false
     */
    virtual bool removeDirectory(const std::string& dirPath);
    
    /**@~english
     *  Removes a file.
     *
     * @~chinese 
     * ɾ��һ���ļ���
     * 
     *  @param filepath @~english The path of the file, it must be an absolute path.
     * @~chinese �ļ���·��,��������һ������·����
     *  @return @~english True if the file have been removed successfully, false if not.
     * @~chinese ����ɹ�ɾ�����ļ�����true,���ɾ��ʧ�ܷ���false
     */
    virtual bool removeFile(const std::string &filepath);
    
    /**@~english
     *  Renames a file under the given directory.
     *
     * @~chinese 
     * ������һ������Ŀ¼�µ��ļ���
     * 
     *  @param path     @~english The parent directory path of the file, it must be an absolute path.
     * @~chinese �ļ��ĸ�Ŀ¼��·��,��������һ������·����
     *  @param oldname  @~english The current name of the file.
     * @~chinese ��ǰ�ļ������ơ�
     *  @param name     @~english The new name of the file.
     * @~chinese ���ļ������ơ�
     *  @return @~english True if the file have been renamed successfully, false if not.
     * @~chinese ����ɹ����������ļ�����true,���������ʧ�ܷ���false
     */
    virtual bool renameFile(const std::string &path, const std::string &oldname, const std::string &name);

    /**
     *  Renames a file under the given directory.
     *
     *  @param oldfullpath  The current fullpath of the file. Includes path and name.
     *  @param newfullpath  The new fullpath of the file. Includes path and name.
     *  @return True if the file have been renamed successfully, false if not.
     */
    virtual bool renameFile(const std::string &oldfullpath, const std::string &newfullpath);

    /**@~english
     *  Retrieve the file size.
     *
     * @~chinese 
     * ��ȡ�ļ���С��
     * 
     *  @note @~english If a relative path was passed in, it will be inserted a default root path at the beginning.
     * @~chinese ������ݽ����Ĳ�����һ�����·�����������俪ͷ����һ��Ĭ�ϵĸ�·��
     *  @param filepath @~english The path of the file, it could be a relative or absolute path.
     * @~chinese �ļ���·��,��������һ����Ի����·����
     *  @return @~english The file size.
     * @~chinese �ļ���С��
     */
    virtual long getFileSize(const std::string &filepath);

    /** @~english Returns the full path cache.  @~chinese ��������·�����档*/
    const std::unordered_map<std::string, std::string>& getFullPathCache() const { return _fullPathCache; }

protected:
    /**@~english
     *  The default constructor.
     * @~chinese 
     * Ĭ�Ϲ��캯����
     */
    FileUtils();
    
    /**@~english
     *  Initializes the instance of FileUtils. It will set _searchPathArray and _searchResolutionsOrderArray to default values.
     *
     * @~chinese 
     * FileUtils�ĳ�ʼ��ʵ��������������_searchPathArray��_searchResolutionsOrderArrayΪĬ��ֵ��
     * 
     *  @note @~english When you are porting Cocos2d-x to a new platform, you may need to take care of this method.
     *        You could assign a default value to _defaultResRootPath in the subclass of FileUtils(e.g. FileUtilsAndroid). Then invoke the FileUtils::init().
     * @~chinese ���㽫Cocos2d-x��ֲ��һ���µ�ƽ̨,��������Ҫ��ע���������
     * �����ָ��һ��Ĭ��ֵ������_defaultResRootPath FileUtils(�硣FileUtilsAndroid)��Ȼ�����FileUtils::init()��
     *  @return @~english true if successed, otherwise it returns false.
     *
     * @~chinese ����ɹ�����true,���򷵻�false��
     * 
     */
    virtual bool init();
    
    /**@~english
     *  Gets the new filename from the filename lookup dictionary.
     *  It is possible to have a override names.
     * @~chinese 
     * ���ļ������Ҵʵ��л�ȡ�µ��ļ���
     * ��������һ���ض��������
     *  @param filename @~english The original filename.
     * @~chinese ԭ�����ļ�����
     *  @return @~english The new filename after searching in the filename lookup dictionary.
     *          If the original filename wasn't in the dictionary, it will return the original filename.
     * @~chinese ���ļ������Ҵʵ��з��ص��µ��ļ���
     * ���ԭʼ�ļ������ڲ��Ҵʵ��У��򷵻�ԭʼ���ļ���
     */
    virtual std::string getNewFilename(const std::string &filename) const;
    
    /**@~english
     *  Checks whether a file exists without considering search paths and resolution orders.
     * @~chinese 
     * �ڲ����ǲ���·���ͽ���˳�������£�����ļ��Ƿ����
     *  @param filename @~english The file (with absolute path) to look up for
     * @~chinese ��Ҫ���ҵ��ļ�������Ҫ����·����
     *  @return @~english Returns true if the file found at the given absolute path, otherwise returns false
     * @~chinese ������ļ�������·����������ֵ��д���,����true,���򷵻�false
     */
    virtual bool isFileExistInternal(const std::string& filename) const = 0;
    
    /**@~english
     *  Checks whether a directory exists without considering search paths and resolution orders.
     * @~chinese 
     * �ڲ����ǲ���·���ͽ���˳�������£����Ŀ¼�Ƿ����
     *  @param dirPath @~english The directory (with absolute path) to look up for
     * @~chinese ��Ҫ���ҵ�Ŀ¼(����·��)
     *  @return @~english Returns true if the directory found at the given absolute path, otherwise returns false
     * @~chinese �����Ŀ¼������·����������ֵ��д���,����true,���򷵻�false
     */
    virtual bool isDirectoryExistInternal(const std::string& dirPath) const;
    
    /**@~english
     *  Gets full path for filename, resolution directory and search path.
     *
     * @~chinese 
     * ���ļ������ֱ���Ŀ¼�Ͳ���·��Ϊ������ȡ����·��
     * 
     *  @param filename @~english The file name.
     * @~chinese �ļ������֡�
     *  @param resolutionDirectory @~english The resolution directory.
     * @~chinese �ֱ���Ŀ¼��
     *  @param searchPath @~english The search path.
     * @~chinese ����·����
     *  @return @~english The full path of the file. It will return an empty string if the full path of the file doesn't exist.
     * @~chinese �����ļ�������·��������ļ�������·�������ڣ��򷵻�һ���յ�string����
     */
    virtual std::string getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath) const;
    
    /**@~english
     *  Gets full path for the directory and the filename.
     *
     * @~chinese 
     * ��Ŀ¼���ļ���Ϊ������ȡ����·��
     * 
     *  @note @~english Only iOS and Mac need to override this method since they are using
     *        `[[NSBundle mainBundle] pathForResource: ofType: inDirectory:]` to make a full path.
     *        Other platforms will use the default implementation of this method.
     * @~chinese ֻ����IOS��Macƽ̨����Ҫ���������������Ϊ������ƽ̨������ʹ��`[[NSBundle mainBundle] pathForResource: ofType: inDirectory:]` 
     * ���������·������������ƽ̨������ʹ�����������Ĭ��ʵ��
     *  @param directory @~english The directory contains the file we are looking for.
     * @~chinese �������ǽ�Ҫ�����ļ���Ŀ¼
     *  @param filename  @~english The name of the file.
     * @~chinese �ļ���
     *  @return @~english The full path of the file, if the file can't be found, it will return an empty string.
     * @~chinese �����ļ�������·����������Ҳ������ļ�����Ż�һ���յ�string����
     */
    virtual std::string getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename) const;
    
    /** @~english Dictionary used to lookup filenames based on a key.
     *  It is used internally by the following methods:
     *
     *  std::string fullPathForFilename(const char*);
     *
     * @~chinese ���ڼ�ֵ�����ļ�����Dictionary����
     * �������ڲ������·���ʹ�õ���
     * 
     * std::string fullPathForFilename(const char*);
     * 
     *  @since v2.1
     */
    ValueMap _filenameLookupDict;
    
    /** @~english
     *  The vector contains resolution folders.
     *  The lower index of the element in this vector, the higher priority for this resolution directory.
     * @~chinese 
     * �����ֱ����ļ��еļ���
     * �ڼ����е�����ֵԽС���ڷֱ���Ŀ¼�е����ȼ���Խ��
     */
    std::vector<std::string> _searchResolutionsOrderArray;
    
    /**@~english
     * The vector contains search paths.
     * The lower index of the element in this vector, the higher priority for this search path.
     * @~chinese 
     * ����������·���ļ��ϡ�
     * �ڼ����е�����ֵԽС���ڲ���·�������ȼ���Խ��
     */
    std::vector<std::string> _searchPathArray;
    
    /**@~english
     *  The default root path of resources.
     *  If the default root path of resources needs to be changed, do it in the `init` method of FileUtils's subclass.
     *  For instance:
     *  On Android, the default root path of resources will be assigned with "assets/" in FileUtilsAndroid::init().
     *  Similarly on Blackberry, we assign "app/native/Resources/" to this variable in FileUtilsBlackberry::init().
     * @~chinese 
     * ��Դ��Ĭ�ϵĸ�·��
     * ���Ҫ�ı������Դ��Ĭ�ϵĸ�·�������ǿ�����FileUtils�����init���������
     * ����:
     * ��Androidƽ̨�ϣ���Դ��Ĭ�ϸ�·������FileUtilsAndroid::init()�б���ֵΪ"assets/" 
     * ��Blackberryƽ̨�ϣ�������FileUtilsBlackberry::init()�а�"app/native/Resources/"�������������
     */
    std::string _defaultResRootPath;
    
    /**@~english
     *  The full path cache. When a file is found, it will be added into this cache. 
     *  This variable is used for improving the performance of file search.
     * @~chinese 
     * ����·���Ļ��档���ļ������ҵ�֮�󣬻���ļ�������·����ӵ���������С�
     * �����������������ļ��������ܵġ�
     */
    mutable std::unordered_map<std::string, std::string> _fullPathCache;
    
    /**@~english
     * Writable path.
     * @~chinese 
     * ��д��·����
     */
    std::string _writablePath;

    /**@~english
     *  The singleton pointer of FileUtils.
     * @~chinese 
     * singleton �ļ�������ĵ�����ָ�롣
     */
    static FileUtils* s_sharedFileUtils;

};

// end of support group
/** @} */

NS_CC_END

#endif    // __CC_FILEUTILS_H__
