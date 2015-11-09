/****************************************************************************
Copyright (c) 2008      Apple Inc. All Rights Reserved.
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCTEXTURE2D_H__
#define __CCTEXTURE2D_H__

#include <string>
#include <map>
#include <unordered_map>

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class Image;
class NinePatchInfo;
class SpriteFrame;
typedef struct _MipmapInfo MipmapInfo;

namespace ui
{
    class Scale9Sprite;
}

/**
 * @addtogroup _2d
 * @{
 */

//CONSTANTS:

class GLProgram;

//CLASS INTERFACES:

/** 
 * @brief @~english Texture2D class. This class allows to easily create OpenGL 2D textures from images, text or raw data.
 * The created Texture2D object will always have power-of-two dimensions.
 * Depending on how you create the Texture2D object, the actual image area of the texture might be smaller than the texture dimensions i.e. "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).
 * Be aware that the content of the generated textures will be upside-down!
 * @~chinese Texture2D �ࡣ�����������ɵش�ͼƬ���ı��������ݴ��� OpenGL 2D ����
 * ������ Texture2D ����Ŀ�������Ǳ���Ϊ 2 ���ݴη���
 * ʵ�������ͼ���С����С�ڴ����������С�����磺contentSize != (pixelsWide, pixelsHigh) �� (maxS, maxT) != (1.0,1.0)��
 * ע�⣺���ɵ�����������������µߵ��ġ�
 */
class CC_DLL Texture2D : public Ref
{
public:
    /** @typedef Texture2D::PixelFormat
     * @~english Possible texture pixel formats
     * @~chinese ��������ظ�ʽ��
     */
    enum class PixelFormat
    {
        /** @~english auto detect the type
        * @~chinese �Զ�������͡�
        */
        AUTO,
        /**@~english  32-bit texture: BGRA8888
        * @~chinese 32λ����BGRA8888
        */
        BGRA8888,
        /**@~english  32-bit texture: RGBA8888
        * @~chinese 32λ����RGBA8888
        */
        RGBA8888,
        /**@~english  24-bit texture: RGB888
        * @~chinese 24λ����RGB888
        */
        RGB888,
        /**@~english  16-bit texture without Alpha channel
        * @~chinese ������ alpha ͨ���� 16λ����
        */
        RGB565,
        /**@~english  8-bit textures used as masks
        * @~chinese ��������ʹ�õ� 8λ����
        */
        A8,
        /**@~english  8-bit intensity texture
        * @~chinese 8λ��������
        */
        I8,
        /**@~english  16-bit textures used as masks
        * @~chinese ��������ʹ�õ� 16 λ����
        */
        AI88,
        /**@~english  16-bit textures: RGBA4444
        * @~chinese 16λ����RGBA4444
        */
        RGBA4444,
        /**@~english  16-bit textures: RGB5A1
        * @~chinese 16λ���� RGB5A1
        */
        RGB5A1,
        /**@~english  4-bit PVRTC-compressed texture: PVRTC4
        * @~chinese 4λ PVRTC ѹ������PVRTC4
        */
        PVRTC4,
        /**@~english  4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
        * @~chinese 4λ PVRTC ѹ������PVRTC4���� alpha ͨ����
        */
        PVRTC4A,
        /**@~english  2-bit PVRTC-compressed texture: PVRTC2
        * @~chinese 2λ PVRTC ѹ������PVRTC2
        */
        PVRTC2,
        /**@~english  2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
        * @~chinese 2λ PVRTC ѹ������PVRTC2���� alpha ͨ����
        */
        PVRTC2A,
        /**@~english  ETC-compressed texture: ETC
        * @~chinese ETC ѹ������ETC
        */
        ETC,
        /**@~english  S3TC-compressed texture: S3TC_Dxt1
        * @~chinese S3TC ѹ������S3TC_Dxt1
        */
        S3TC_DXT1,
        /**@~english  S3TC-compressed texture: S3TC_Dxt3
        * @~chinese S3TC ѹ������S3TC_Dxt3
        */
        S3TC_DXT3,
        /**@~english  S3TC-compressed texture: S3TC_Dxt5
        * @~chinese S3TC ѹ������S3TC_Dxt5
        */
        S3TC_DXT5,
        /**@~english  ATITC-compressed texture: ATC_RGB
        * @~chinese ATITC ѹ������ATC_RGB
        */
        ATC_RGB,
        /**@~english  ATITC-compressed texture: ATC_EXPLICIT_ALPHA
        * @~chinese ATITC ѹ������ATC_EXPLICIT_ALPHA
        */
        ATC_EXPLICIT_ALPHA,
        /**@~english  ATITC-compresed texture: ATC_INTERPOLATED_ALPHA
        * @~chinese ATITC ѹ������ATC_INTERPOLATED_ALPHA
        */
        ATC_INTERPOLATED_ALPHA,
        /**@~english  Default texture format: AUTO
        * @~chinese Ĭ�������ʽΪ��AUTO
        */
        DEFAULT = AUTO,
        
        NONE = -1
    };
    
    
    struct PixelFormatInfo {

        PixelFormatInfo(GLenum anInternalFormat, GLenum aFormat, GLenum aType, int aBpp, bool aCompressed, bool anAlpha)
            : internalFormat(anInternalFormat)
            , format(aFormat)
            , type(aType)
            , bpp(aBpp)
            , compressed(aCompressed)
            , alpha(anAlpha)
        {}

        GLenum internalFormat;
        GLenum format;
        GLenum type;
        int bpp;
        bool compressed;
        bool alpha;
    };
    
    typedef std::map<Texture2D::PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;
    
    /**@~english
     * Extension to set the Min / Mag filter
     * @~chinese 
     * �������� Min / Mag ����������չ�ṹ�塣
     */
    typedef struct _TexParams {
        GLuint    minFilter;
        GLuint    magFilter;
        GLuint    wrapS;
        GLuint    wrapT;
    }TexParams;
    
public:
    /** @~english sets the default pixel format for `Image` contains alpha channel.
     * @~chinese Ϊ���� alpha ͨ���� `Image` ��������Ĭ�ϵ����ظ�ʽ��
     * 
     * @param format @~english
     * If the `Image` contains alpha channel, then the options are:
     * - generate 32-bit textures: `Texture2D::PixelFormat::RGBA8888` (default one)
     * - generate 24-bit textures: `Texture2D::PixelFormat::RGB888`
     * - generate 16-bit textures: `Texture2D::PixelFormat::RGBA4444`
     * - generate 16-bit textures: `Texture2D::PixelFormat::RGB5A1`
     * - generate 16-bit textures: `Texture2D::PixelFormat::RGB565`
     * - generate 8-bit textures: Texture2D::PixelFormat::A8 (only use it if you use just 1 color)
     * 
     * How does it work ?
     * - If the image is an RGBA (with Alpha) then the default pixel format will be used (it can be a 8-bit, 16-bit or 32-bit texture)
     * - If the image is an RGB (without Alpha) then: If the default pixel format is RGBA8888 then a RGBA8888 (32-bit) will be used. Otherwise a RGB565 (16-bit texture) will be used.
     * 
     * This parameter is not valid for PVR / PVR.CCZ images.
     * 
     * @~chinese
     * ��� `Image` ������� alpha ͨ������ô����:
     * - ����32λ������: `Texture2D::PixelFormat:RGBA8888` (Ĭ��ֵ)
     * - ����24λ����: `Texture2D::PixelFormat::RGB888`
     * - ����16λ����: `Texture2D::PixelFormat::RGBA4444`
     * - ����16λ����: `Texture2D::PixelFormat::RGB5A1`
     * - ����16λ����: `Texture2D::PixelFormat::RGB565`
     * - ����8λ����: `Texture2D::PixelFormat:A8` (ֻ�е���ʹ�õ�ɫʱ����ʹ�ô˸�ʽ)
     * 
     * ������ι�����?
     * - �����һ�� RGBA (���� alpha ͨ��) ͼ����ʹ��Ĭ�ϵ����ظ�ʽ(��������һ��8λ,16λ��32λ������)
     * - �����һ�� RGB (û�� alpha ͨ��) ͼ����ô����Ĭ�ϵ����ظ�ʽΪ RGBA8888 ʱ��RGBA8888 (32λ) ����ʹ�á�����RGB565(16λ����)����ʹ�á�
     * 
     * ��������� PVR/PVR.CCZ ͼ������Ч�ġ�
     * 
     * @since v0.8
     */
    static void setDefaultAlphaPixelFormat(Texture2D::PixelFormat format);

    /** @~english Returns the default alpha pixel format.
     * @~chinese ����Ĭ�ϵ� alpha ͨ�����ظ�ʽ��
     * @since v0.8
     */
    static Texture2D::PixelFormat getDefaultAlphaPixelFormat();
    CC_DEPRECATED_ATTRIBUTE static Texture2D::PixelFormat defaultAlphaPixelFormat() { return Texture2D::getDefaultAlphaPixelFormat(); };

    /** @~english Treats (or not) PVR files as if they have alpha premultiplied.
     * @~chinese ���ô��� PVR �ļ�ʱ�Ƿ���� alpha Ԥ�ˡ�
     * 
     * @param haveAlphaPremultiplied @~english
     * Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is
     * possible load them as if they have (or not) the alpha channel premultiplied.
     * 
     * By default it is disabled.
     * 
     * deprecated, please use Image::setPVRImagesHavePremultipliedAlpha() instead.
     * 
     * @~chinese 
     * ��Ϊ������ʱ�޷�֪�� PVR ͼ���Ƿ���Ҫ���� alpha Ԥ��,
     * ������Ҫ�ڼ���ʱ�������Ƿ���� alpha Ԥ�ˡ�
     * 
     * ��Ĭ��������ǽ��õġ�
     * 
     * ���ã���ʹ�� `Image::setPVRImagesHavePremultipliedAlpha()` ���档
     * 
     * @since v0.99.5
     */
    CC_DEPRECATED_ATTRIBUTE static void PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);
    
public:
    /**
     * @js ctor
     */
    Texture2D();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Texture2D();
    /**@~english
     * Get texutre name, dimensions and coordinates message by a string.
     * @~chinese 
     * ���ַ�����ʽ��ȡ�������ƣ���С��������Ϣ��
     * @return @~english The string include texture name, dimensions and coordinates message.
     * @~chinese �����������ƣ���С��������Ϣ���ַ�����
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

	/** @~english Release only the gl texture.
     * @~chinese ֻ�ͷ� gl ����
     * @js NA
     * @lua NA
     */
	void releaseGLTexture();

    /** @~english Initializes a Texture2D object with data.
     * @~chinese ʹ��ָ�������ݳ�ʼ�� Texture2D ����
     * @param data @~english Specifies a pointer to the image data in memory.
     * @~chinese ͼ�����ݵ�ָ�롣
     * @param dataLen @~english The image data length.
     * @~chinese ͼ�����ݵĳ��ȡ�
     * @param pixelFormat @~english The image pixelFormat.
     * @~chinese ͼ������ظ�ʽ��
     * @param pixelsWide @~english The image width.
     * @~chinese ͼ��Ŀ�ȡ�
     * @param pixelsHigh @~english The image height.
     * @~chinese ͼ��ĸ߶ȡ�
     * @param contentSize @~english The image content size.
     * @~chinese ͼ�����ݵĴ�С��
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     * @js NA
     * @lua NA
     */
    bool initWithData(const void *data, ssize_t dataLen, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh, const Size& contentSize);

    /** @~english Initializes with mipmaps. 
     * @~chinese ʹ�� mipmaps ͼ���ʼ����
     * @param mipmaps @~english Specifies a pointer to the mipmaps image data in memory.
     * @~chinese mipmaps ͼ�����ݵ�ָ�롣
     * @param mipmapsNum @~english The mipmaps number.
     * @~chinese mipmaps ͼ�����ݵĳ��ȡ�
     * @param pixelFormat @~english The image pixelFormat.
     * @~chinese mipmaps ͼ������ظ�ʽ��
     * @param pixelsWide @~english The image width.
     * @~chinese ͼ��Ŀ�ȡ�
     * @param pixelsHigh @~english The image height.
     * @~chinese ͼ��ĸ߶ȡ�
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);

    /** @~english Update with texture data.
     * @~chinese ʹ��ָ�������ݸ�������
     * @param data @~english Specifies a pointer to the image data in memory.
     * @~chinese ͼ�����ݵ�ָ�롣
     * @param offsetX @~english Specifies a texel offset in the x direction within the texture array.
     * @~chinese ���������е� x ���ƫ������
     * @param offsetY @~english Specifies a texel offset in the y direction within the texture array.
     * @~chinese ���������е� y ���ƫ������
     * @param width @~english Specifies the width of the texture subimage.
     * @~chinese ָ����������ʹ��ͼ��Ŀ�ȡ�
     * @param height @~english Specifies the height of the texture subimage.
     * @~chinese ָ����������ʹ��ͼ��ĸ߶ȡ�
     * @return @~english If the update is success, return true; else return false.
     * @~chinese ������³ɹ������� true�����򷵻� false��
     */
    bool updateWithData(const void *data,int offsetX,int offsetY,int width,int height);
    /**@~english
     * Drawing extensions to make it easy to draw basic quads using a Texture2D object.
     * These functions require GL_TEXTURE_2D and both GL_VERTEX_ARRAY and GL_TEXTURE_COORD_ARRAY client states to be enabled.
     * @~chinese 
     * ������ص���չ��������ʹ�� Texture2D ���ƻ���ͼ�α�ø��򵥡�
     * ��Щ������Ҫ���� GL_TEXTURE_2D��GL_VERTEX_ARRAY �� GL_TEXTURE_COORD_ARRAY ��Щ GL ״̬��
     */
    /** @~english Draws a texture at a given point.
     * @~chinese �ڸ����������������
     */
    void drawAtPoint(const Vec2& point);
    /** @~english Draws a texture inside a rect.
     * @~chinese ��һ�����������ڻ�������
     */
    void drawInRect(const Rect& rect);

    /**@~english
     * Extensions to make it easy to create a Texture2D object from an image file.
     * @~chinese 
     * �򻯴�ͼ���ļ����� Texture2D �������չ������
    */
    /** @~english
	 * Initializes a texture from a `Image` object.
     *
     * We will use the format you specified with setDefaultAlphaPixelFormat to convert the image for texture.
     * NOTE: It will not convert the pvr image file.
     * @~chinese 
     * ʹ�� `Image` �����ʼ������
     * 
     * ���������ʹ�� `setDefaultAlphaPixelFormat` �������õ����ظ�ʽ��ת��ͼ�����ݡ�
     * ע�⣺������ת�� pvr ͼ���ļ���
     * @param image @~english An `Image` object.
     * @~chinese һ�� `Image` ����
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
	 */
    bool initWithImage(Image * image);
    
    /** @~english
	 * Initializes a texture from a UIImage object.
     * 
     * We will use the format you passed to the function to convert the image format to the texture format.
     * If you pass PixelFormat::Automatic, we will auto detect the image render type and use that type for texture to render.
     * @~chinese 
     * ʹ�� `Image` �����ʼ������
     * 
     * ���������ʹ�ò���ָ�������ظ�ʽ��ת��ͼ�����ݡ�
     * ��� format ����ֵΪ `PixelFormat:AUTO`�����Զ����ͼ�����Ⱦ���Ͳ�ʹ�ø�������Ⱦ����
     * @param image @~english An `Image` object.
     * @~chinese һ�� `Image` ����
     * @param format @~english Texture pixel formats.
     * @~chinese �������ظ�ʽ��
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    bool initWithImage(Image * image, PixelFormat format);

    /** @~english Initializes a texture from a string with dimensions, alignment, font name and font size. 
     * @~chinese ʹ��ָ�����ַ������������ƣ������С�������С���ı����뷽ʽ��ʼ��һ������
     * 
     * @param text @~english A null terminated string.
     * @~chinese �Կ��ַ���β���ַ�����
     * @param fontName @~english The font name.
     * @~chinese �������ơ�
     * @param fontSize @~english The font size.
     * @~chinese �����С��
     * @param dimensions @~english The font dimension.
     * @~chinese �����С
     * @param hAlignment @~english The font horizontal text alignment type.
     * @~chinese �ı�ˮƽ���뷽ʽ��
     * @param vAlignment @~english The font vertical text alignment type.
     * @~chinese �ı���ֱ���뷽ʽ��
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    bool initWithString(const char *text,  const std::string &fontName, float fontSize, const Size& dimensions = Size(0, 0), TextHAlignment hAlignment = TextHAlignment::CENTER, TextVAlignment vAlignment = TextVAlignment::TOP);

    /** @~english Initializes a texture from a string using a text definition.
     * @~chinese ʹ��ָ�����ı���ָ�����������Գ�ʼ��һ������
     * @param text @~english A null terminated string.
     * @~chinese �Կ��ַ���β���ַ�����
     * @param textDefinition @~english A FontDefinition object contains font attributes.
     * @~chinese �����������Ե� `FontDefinition` ����
     * @return @~english If the initialization is success, return true; else return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false��
     */
    bool initWithString(const char *text, const FontDefinition& textDefinition);

    /** @~english Sets the min filter, mag filter, wrap s and wrap t texture parameters.
     * If the texture size is NPOT (non power of 2), then in can only use GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}.
     *
     * @~chinese ���� min ��������mag ��������wrap s �� wrap t ��Щ���������
     * ��������СΪ NPOT(�� 2 ���ݴη�)����ôֻ���� GL_TEXTURE_WRAP_{S,T} ��ʹ�� GL_CLAMP_TO_EDGE��
     * 
     * @warning @~english Calling this method could allocate additional texture memory.
     * @code 
     * When this function bound into js or lua,the input parameter will be changed
     * In js: var setTexParameters(var arg1, var arg2, var arg3, var arg4)
     * In lua: local setTexParameters(local arg1, local arg2, local arg3, local arg4)
     * @endcode
     *
     * @~chinese ���ø÷�����������������ڴ档
     * @code 
     * ���˷����󶨵� js ���� lua �У�������Ҫ��Ϊ��
     * js ��: var setTexParameters(var arg1, var arg2, var arg3, var arg4)
     * lua ��: local setTexParameters(local arg1, local arg2, local arg3, local arg4)
     * @endcode
     * @since v0.8
     */
    void setTexParameters(const TexParams& texParams);

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void setTexParameters(const TexParams* texParams) { return setTexParameters(*texParams); };

    /** @~english Sets antialias texture parameters:
     * - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     * - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     *
     * @~chinese ���ÿ�����������:
     * - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     * - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     * 
     * @warning @~english Calling this method could allocate additional texture memory.
     * @~chinese ���ø÷�����������������ڴ档
     * 
     * @since v0.8
     */
    void setAntiAliasTexParameters();

    /** @~english Sets alias texture parameters:
     * - GL_TEXTURE_MIN_FILTER = GL_NEAREST
     * - GL_TEXTURE_MAG_FILTER = GL_NEAREST
     *
     * @~chinese ���þ���������:
     * - GL_TEXTURE_MIN_FILTER = GL_NEAREST
     * - GL_TEXTURE_MAG_FILTER = GL_NEAREST
     * 
     * @warning @~english Calling this method could allocate additional texture memory.
     * @~chinese ���ø÷�����������������ڴ档
     * 
     * @since v0.8
     */
    void setAliasTexParameters();


    /** @~english Generates mipmap images for the texture.
     * It only works if the texture size is POT (power of 2).
     * @~chinese Ϊ�������� mipmaps ͼ��
     * ֻ�е������СΪ POT��2���ݴη��� ����Ч��
     * @since v0.99.0
     */
    void generateMipmap();

    /** @~english Returns the pixel format by string.
     * @~chinese �������ظ�ʽ���ַ�����
     * @since v2.0
     */
    const char* getStringForFormat() const;
    CC_DEPRECATED_ATTRIBUTE const char* stringForFormat() const { return getStringForFormat(); };

    /** @~english Returns the bits-per-pixel of the in-memory OpenGL texture
     * @~chinese �����ڴ��� OpenGL ����ÿ��������ʹ�õ�λ����
    * @since v1.0
    */
    unsigned int getBitsPerPixelForFormat() const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat() const { return getBitsPerPixelForFormat(); };

    /** @~english Helper functions that returns bits per pixels for a given format.
     * @~chinese ������ߺ�����ȡָ�������ظ�ʽ��ÿ��������ʹ�õ�λ����
     * @since v2.0
     */
    unsigned int getBitsPerPixelForFormat(Texture2D::PixelFormat format) const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat(Texture2D::PixelFormat format) const { return getBitsPerPixelForFormat(format); };

    /** @~english Get content size in pixels.  @~chinese ��ȡ����Ĵ�С��������Ϊ��λ��*/
    const Size& getContentSizeInPixels();

    /** @~english Whether or not the texture has their Alpha premultiplied.
     *  @~chinese ��ȡ�����Ƿ��� alpha Ԥ�ˡ�
     */
    bool hasPremultipliedAlpha() const;
    
    /** @~english Whether or not the texture has mip maps.
     * @~chinese ��ȡ�����Ƿ��� mipmaps.
     */
    bool hasMipmaps() const;

    /** @~english Gets the pixel format of the texture.
     *  @~chinese ��ȡ��������ظ�ʽ��
     */
    Texture2D::PixelFormat getPixelFormat() const;
    
    /** @~english Gets the width of the texture in pixels. 
     * @~chinese ��ȡ����Ŀ��(������Ϊ��λ)��
     */
    int getPixelsWide() const;
    
    /** @~english Gets the height of the texture in pixels.
     *  @~chinese ��ȡ����ĸ߶�(������Ϊ��λ)��
     */
    int getPixelsHigh() const;
    
    /** @~english Gets the texture name.
     *  @~chinese ��ȡ��������֡�
     */
    GLuint getName() const;
    
    /** @~english Gets max S.
     *  @~chinese ��ȡ S �����ֵ��
     */
    GLfloat getMaxS() const;
    /** @~english Sets max S. 
     * @~chinese ���� S �����ֵ��
     */
    void setMaxS(GLfloat maxS);
    
    /** @~english Gets max T. 
     * @~chinese ��ȡ T �����ֵ��
     */
    GLfloat getMaxT() const;
    /** @~english Sets max T. 
     * @~chinese ���� T �����ֵ��
     */
    void setMaxT(GLfloat maxT);
    
    /** @~english Get the texture content size.
     * @~chinese ��ȡ�������ݵĴ�С��
     */
    Size getContentSize() const;
    
    /** @~english Set a shader program to the texture.
     * It's used by drawAtPoint and drawInRect
     * @~chinese ����һ��������ʹ�õ� GLProgram��
     * �� `drawAtPoint` �� `drawInRect` ��ʹ�á�
     */
    void setGLProgram(GLProgram* program);

    /** @~english Get a shader program from the texture for `drawAtPoint` & `drawInRect`.
     * @~chinese ��ȡ`drawAtPoint` �� `drawInRect` ʹ�õ�GLProgram��
     */
    GLProgram* getGLProgram() const;


public:
    /** @~english Get pixel info map, the key-value pairs is PixelFormat and PixelFormatInfo.
     * @~chinese ��ȡ������Ϣ��ӳ�䣬�� `PixelFormat` �� `PixelFormatInfo` ��ɵļ�ֵ�ԡ�
     */
    static const PixelFormatInfoMap& getPixelFormatInfoMap();
    
private:
    /**
    * A struct for storing 9-patch image capInsets.
    */

    class NinePatchInfo
    {
    public:
        Rect capInsetSize;
        std::unordered_map<SpriteFrame*, Rect> capInsetMap;
    };

    /**
     * Whether the texture contains a 9-patch capInset info or not.
     *
     * @return True is Texture contains a 9-patch info, false otherwise.
     */
    bool isContain9PatchInfo()const;

    /**
     * Get spriteFrame capInset, If spriteFrame can't be found in 9-patch info map,
     * then single 9-patch texture capInset will be returned.
     * If the arg is nullptr, the capInset of single 9-patch texture will be returned.
     *
     * @param spriteFrame A SpriteFrame object pointer.
     *
     * @return The capInset of the SpriteFrame object.
     */
    const Rect& getSpriteFrameCapInset(SpriteFrame* spriteFrame)const;
    /**
     * Remove the spriteFrame capInset info when the spriteFrame is removed.
     *
     * @param spriteFrame A SpriteFrame object pointer.
     */
    void removeSpriteFrameCapInset(SpriteFrame* spriteFrame);
    /**
     * Add capInset for sprite atlas.
     * When handling single texture, pass nullptr in the first arg.
     *
     * @param spritframe The sprite frame object.
     * @param capInsets The parsed capInset from a .9 patch image.
     */
    void addSpriteFrameCapInset(SpriteFrame* spritframe, const Rect& capInsets);

    /**convert functions*/

    /**
    Convert the format to the format param you specified, if the format is PixelFormat::Automatic, it will detect it automatically and convert to the closest format for you.
    It will return the converted format to you. if the outData != data, you must delete it manually.
    */
    static PixelFormat convertDataToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);

    static PixelFormat convertI8ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertAI88ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertRGB888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertRGBA8888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);

    //I8 to XXX
    static void convertI8ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //AI88 to XXX
    static void convertAI88ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //RGB888 to XXX
    static void convertRGB888ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //RGBA8888 to XXX
    static void convertRGBA8888ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

protected:
    /** pixel format of the texture */
    Texture2D::PixelFormat _pixelFormat;

    /** width in pixels */
    int _pixelsWide;

    /** height in pixels */
    int _pixelsHigh;

    /** texture name */
    GLuint _name;

    /** texture max S */
    GLfloat _maxS;
    
    /** texture max T */
    GLfloat _maxT;

    /** content size */
    Size _contentSize;

    /** whether or not the texture has their Alpha premultiplied */
    bool _hasPremultipliedAlpha;
    
    /** whether or not the texture has mip maps*/
    bool _hasMipmaps;

    /** shader program used by drawAtPoint and drawInRect */
    GLProgram* _shaderProgram;

    static const PixelFormatInfoMap _pixelFormatInfoTables;

    bool _antialiasEnabled;
    NinePatchInfo* _ninePatchInfo;
    friend class SpriteFrameCache;
    friend class TextureCache;
    friend class ui::Scale9Sprite;
};


// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE2D_H__

