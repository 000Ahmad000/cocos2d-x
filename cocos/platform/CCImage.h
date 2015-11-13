/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __CC_IMAGE_H__
#define __CC_IMAGE_H__
/// @cond DO_NOT_SHOW

#include "base/CCRef.h"
#include "renderer/CCTexture2D.h"

#if defined(CC_USE_WIC)
#include "WICImageLoader-winrt.h"
#endif

/** @~english premultiply alpha, or the effect will wrong when want to use other pixel format in Texture2D,
// such as RGB888, RGB5A1
    @~chinese ͸�����ظ��� ���������Texture2D��ʹ�����������ظ�ʽ���磺RGB888, RGB5A1����Ч���ͻ����
*/
#define CC_RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
    ((unsigned)(unsigned char)(va) << 24))

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/**
 @brief @~english Structure which can tell where mipmap begins and how long is it
 * @~chinese �������mipmap��ʼλ�úͳ��ȵĽṹ��
 */
typedef struct _MipmapInfo
{
    unsigned char* address;
    int len;
    _MipmapInfo():address(NULL),len(0){}
}MipmapInfo;

class CC_DLL Image : public Ref
{
public:
    friend class TextureCache;
    /**
     * @js ctor
     */
    Image();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Image();

    /** @~english Supported formats for Image  @~chinese ֧�ֵ�ͼƬ��ʽ*/
    enum class Format
    {
        //! JPEG
        JPG,
        //! PNG
        PNG,
        //! TIFF
        TIFF,
        //! WebP
        WEBP,
        //! PVR
        PVR,
        //! ETC
        ETC,
        //! S3TC
        S3TC,
        //! ATITC
        ATITC,
        //! TGA
        TGA,
        //! ԭʼ����
        RAW_DATA,
        //! δ֪��ʽ
        UNKNOWN
    };

    /**
    @brief @~english Load the image from the specified path.
     * @~chinese ��ָ����·������ͼƬ
    @param path   @~english the absolute file path.
     * @~chinese �ļ��ľ���·��
    @return @~english true if loaded correctly.
     * @~chinese �����ȷ�����򷵻�true
    */
    bool initWithImageFile(const std::string& path);

    /**
    @brief @~english Load image from stream buffer.
     * @~chinese ��������������ͼƬ
    @param data  @~english stream buffer which holds the image data.
     * @~chinese ���ͼƬ���ݵ���������
    @param dataLen  @~english data length expressed in (number of) bytes.
     * @~chinese ���ݵ��ֽ���
    @return @~english true if loaded correctly.
     * @~chinese �����ȷ�����򷵻�true
    * @js NA
    * @lua NA
    */
    bool initWithImageData(const unsigned char * data, ssize_t dataLen);

    /** @~english Load image from raw data @~chinese ��ԭʼ�����м���ͼƬ
    // @warning kFmtRawData @~english only support RGBA8888 @~chinese ֻ֧��RGBA8888
    */
    bool initWithRawData(const unsigned char * data, ssize_t dataLen, int width, int height, int bitsPerComponent, bool preMulti = false);

    // Getters
    inline unsigned char *   getData()               { return _data; }
    inline ssize_t           getDataLen()            { return _dataLen; }
    inline Format            getFileType()           {return _fileType; }
    inline Texture2D::PixelFormat getRenderFormat()  { return _renderFormat; }
    inline int               getWidth()              { return _width; }
    inline int               getHeight()             { return _height; }
    inline int               getNumberOfMipmaps()    { return _numberOfMipmaps; }
    inline MipmapInfo*       getMipmaps()            { return _mipmaps; }
    inline bool              hasPremultipliedAlpha() { return _hasPremultipliedAlpha; }
    CC_DEPRECATED_ATTRIBUTE inline bool isPremultipliedAlpha()  { return _hasPremultipliedAlpha;   }

    int                      getBitPerPixel();
    bool                     hasAlpha();
    bool                     isCompressed();


    /**
     @brief    @~english Save Image data to the specified file, with specified format.
     * @~chinese ��ָ���ĸ�ʽ��ͼƬ���ݱ��浽ָ�����ļ���
     @param    filePath        @~english the file's absolute path, including file suffix.
     * @~chinese �����ļ���׺�ľ���·��
     @param    isToRGB        @~english whether the image is saved as RGB format.
     * @~chinese ͼƬ�Ƿ���RGB��ʽ���档
     */
    bool saveToFile(const std::string &filename, bool isToRGB = true);
    
    
    /** @~english treats (or not) PVR files as if they have alpha premultiplied.
     Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is
     possible load them as if they have (or not) the alpha channel premultiplied.
     
     By default it is disabled.
     * @~chinese ����PVR�ļ��Ƿ����͸�����ػ�ϡ�
     * ��Ϊ������֪��������ʱPVRͼ���Ƿ�����alphaͨ���Ļ��,
     * ���ܼ�������ʱ��(��û��)͸��ͨ����ϡ�
     * 
     * ��Ĭ��������ǽ��õġ�
     */
    static void setPVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);

protected:
#if defined(CC_USE_WIC)
    bool encodeWithWIC(const std::string& filePath, bool isToRGB, GUID containerFormat);
    bool decodeWithWIC(const unsigned char *data, ssize_t dataLen);
#endif
    bool initWithJpgData(const unsigned char *  data, ssize_t dataLen);
    bool initWithPngData(const unsigned char * data, ssize_t dataLen);
    bool initWithTiffData(const unsigned char * data, ssize_t dataLen);
    bool initWithWebpData(const unsigned char * data, ssize_t dataLen);
    bool initWithPVRData(const unsigned char * data, ssize_t dataLen);
    bool initWithPVRv2Data(const unsigned char * data, ssize_t dataLen);
    bool initWithPVRv3Data(const unsigned char * data, ssize_t dataLen);
    bool initWithETCData(const unsigned char * data, ssize_t dataLen);
    bool initWithS3TCData(const unsigned char * data, ssize_t dataLen);
    bool initWithATITCData(const unsigned char *data, ssize_t dataLen);
    typedef struct sImageTGA tImageTGA;
    bool initWithTGAData(tImageTGA* tgaData);

    bool saveImageToPNG(const std::string& filePath, bool isToRGB = true);
    bool saveImageToJPG(const std::string& filePath);
    
    void premultipliedAlpha();
    
protected:
    /**
     @brief @~english Determine how many mipmaps can we have.
     It's same as define but it respects namespaces
     * @~chinese ����mipmap������������
     * �����ʹ��define��һ���ģ�ֻ���������������ռ�Ĺ���
     */
    static const int MIPMAP_MAX = 16;
    unsigned char *_data;
    ssize_t _dataLen;
    int _width;
    int _height;
    bool _unpack;
    Format _fileType;
    Texture2D::PixelFormat _renderFormat;
    MipmapInfo _mipmaps[MIPMAP_MAX];   // pointer to mipmap images
    int _numberOfMipmaps;
    // false if we can't auto detect the image is premultiplied or not.
    bool _hasPremultipliedAlpha;
    std::string _filePath;


protected:
    // noncopyable
    Image(const Image&    rImg);
    Image & operator=(const Image&);
    
    /*
     @brief @~english The same result as with initWithImageFile, but thread safe. It is caused by
     loadImage() in TextureCache.cpp.
     * @~chinese ����ʹ��initWithImageFile�Ľ����һ���ģ�ֻ�����߳���԰�ȫ������TextureCache.cpp�е� loadImage()������
     @param fullpath  @~english full path of the file.
     * @~chinese �ļ�������·����
     @param imageType @~english the type of image, currently only supporting two types.
     * @~chinese ͼƬ���ͣ���ǰֻ֧����������
     @return  @~english true if loaded correctly.
     * @~chinese �����ȷ�����򷵻�true
     */
    bool initWithImageFileThreadSafe(const std::string& fullpath);
    
    Format detectFormat(const unsigned char * data, ssize_t dataLen);
    bool isPng(const unsigned char * data, ssize_t dataLen);
    bool isJpg(const unsigned char * data, ssize_t dataLen);
    bool isTiff(const unsigned char * data, ssize_t dataLen);
    bool isWebp(const unsigned char * data, ssize_t dataLen);
    bool isPvr(const unsigned char * data, ssize_t dataLen);
    bool isEtc(const unsigned char * data, ssize_t dataLen);
    bool isS3TC(const unsigned char * data,ssize_t dataLen);
    bool isATITC(const unsigned char *data, ssize_t dataLen);
};

// end of platform group
/// @}

NS_CC_END

/// @endcond
#endif    // __CC_IMAGE_H__
