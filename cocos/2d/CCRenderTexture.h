/****************************************************************************
Copyright (c) 2009      Jason Booth
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
#ifndef __CCRENDER_TEXTURE_H__
#define __CCRENDER_TEXTURE_H__

#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "platform/CCImage.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class EventCustom;

/**
 * @addtogroup _2d
 * @{
 */

/**
 * @brief @~english RenderTexture is a generic rendering target. To render things into it,
 * simply construct a render target, call begin on it, call visit on any cocos
 * scenes or objects to render them, and call end. For convenience, render texture
 * adds a sprite as it's display child with the results, so you can simply add
 * the render texture to your scene and treat it like any other Node.
 * There are also functions for saving the render texture to disk in PNG or JPG format.
 * @~chinese RenderTexture��һ��ͨ�õ���Ⱦ�ڵ㡣Ҫ�����н�����Ⱦ��ֻ��򵥵Ĺ���һ�� RenderTexture ����
 * Ȼ����� begin �������ٵ�����Ҫ��Ⱦ�ĳ�����������յ��� end �������ɡ�
 * Ϊ�˷��������RenderTexture �����һ�� Sprite ��Ϊ��ʾ����Ľڵ㣬����Խ���� Sprite ��Ϊһ�� Node ���
 * ���κγ����н�����Ⱦ����ʾ��
 * ���⣬������ͨ���ӿڽ���Ⱦ�Ľ������Ϊ PNG �� JPG ��ʽ�ļ���
 * @since v0.8.1
 */
class CC_DLL RenderTexture : public Node 
{
public:
    /** @~english Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format. 
     *
     * @~chinese ʹ��ָ���Ŀ�ȣ��߶ȣ����ظ�ʽ�����ģ���ʽ��ʼ��һ��RenderTexture����
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture����Ŀ�ȡ�
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture����ĸ߶ȡ�
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese ���ظ�ʽ(ֻ��RGB��RGBA��ʽ����)��
     * @param depthStencilFormat @~english The depthStencil format.
     * @~chinese ���ģ���ʽ��
     */
    static RenderTexture * create(int w ,int h, Texture2D::PixelFormat format, GLuint depthStencilFormat);

    /** @~english Creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid. 
     *
     * @~chinese ʹ��ָ���Ŀ�ȣ��߶ȣ����ظ�ʽ��ʼ��һ��RenderTexture���󡣣�ֻ��RGB��RGBA��ʽ���á���
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture����Ŀ�ȡ�
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture����ĸ߶ȡ�
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese ���ظ�ʽ(ֻ��RGB��RGBA��ʽ����)��
     */
    static RenderTexture * create(int w, int h, Texture2D::PixelFormat format);

    /** @~english Creates a RenderTexture object with width and height in Points, pixel format is RGBA8888. 
     *
     * @~chinese ָ����ȣ��߶ȳ�ʼ��һ��RenderTexture���󡣣����ظ�ʽ��RGBA8888����
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture����Ŀ�ȡ�
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture����ĸ߶ȡ�
     */
    static RenderTexture * create(int w, int h);

    /** @~english Starts grabbing.  @~chinese ��ʼ��Ⱦ��*/
    virtual void begin();

    /** @~english Starts rendering to the texture while clearing the texture first.
     * This is more efficient than calling -clear first and then -begin.
     *
     * @~chinese ʹ��ָ������ɫ����������ʼ��Ⱦ��
     * �������ʵ�ֱ��ȵ��� clear �ٵ��� begin ����Ч��
     * 
     * @param r @~english Red.
     * @~chinese ��ɫ����ֵ��
     * @param g @~english Green.
     * @~chinese ��ɫ����ֵ��
     * @param b @~english Blue.
     * @~chinese ��ɫ����ֵ��
     * @param a @~english Alpha.
     * @~chinese ͸���ȡ�
     */
    virtual void beginWithClear(float r, float g, float b, float a);

    /** @~english Starts rendering to the texture while clearing the texture first.
     * This is more efficient than calling -clear first and then -begin.
     *
     * @~chinese ʹ��ָ������ɫ�����������������ʼ��Ⱦ��
     * �������ʵ�ֱ��ȵ��� clear �ٵ��� begin ����Ч��
     * 
     * @param r @~english Red.
     * @~chinese ��ɫ����ֵ��
     * @param g @~english Green.
     * @~chinese ��ɫ����ֵ��
     * @param b @~english Blue.
     * @~chinese ��ɫ����ֵ��
     * @param a @~english Alpha.
     * @~chinese ͸���ȡ�
     * @param depthValue @~english The depth Value.
     * @~chinese ���ֵ��
     */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue);

    /** @~english Starts rendering to the texture while clearing the texture first.
     * This is more efficient then calling -clear first and then -begin. 
     *
     * @~chinese ʹ��ָ������ɫ������Լ�ģ��������������ʼ��Ⱦ��
     * �������ʵ�ֱ��ȵ��� clear �ٵ��� begin ����Ч��
     * 
     * @param r @~english Red.
     * @~chinese ��ɫ����ֵ��
     * @param g @~english Green.
     * @~chinese ��ɫ����ֵ��
     * @param b @~english Blue.
     * @~chinese ��ɫ����ֵ��
     * @param a @~english Alpha.
     * @~chinese ͸���ȡ�
     * @param depthValue @~english The depth Value.
     * @~chinese ���ֵ��
     * @param stencilValue @~english A specified stencil value.
     * @~chinese ָ����ģ�塣
     */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);

    /** @~english End is key word of lua, use other name to export to lua.
     * @~chinese ��Ϊ end �� lua �еĹؼ��֣��˽ӿ���Ϊ lua binding ���ӵġ�
     * @js NA
     */
    inline void endToLua(){ end();};

    /** @~english Ends grabbing.  @~chinese ������Ⱦ��*/
    virtual void end();

    /** @~english Clears the texture with a color. 
     *
     * @~chinese ʹ��ָ������ɫ�������
     * 
     * @param r @~english Red.
     * @~chinese ��ɫ����ֵ��
     * @param g @~english Green.
     * @~chinese ��ɫ����ֵ��
     * @param b @~english Blue.
     * @~chinese ��ɫ����ֵ��
     * @param a @~english Alpha.
     * @~chinese ͸���ȡ�
     */
    void clear(float r, float g, float b, float a);

    /** @~english Clears the texture with a specified depth value. 
     *
     * @~chinese ʹ��ָ������������Ȼ��档
     * 
     * @param depthValue @~english A specified depth value.
     * @~chinese һ��ָ�������ֵ��
     */
    virtual void clearDepth(float depthValue);

    /** @~english Clears the texture with a specified stencil value.
     *
     * @~chinese ʹ��ָ����ֵ���ģ�建�档
     * 
     * @param stencilValue @~english A specified stencil value.
     * @~chinese ָ����ģ�塣
     */
    virtual void clearStencil(int stencilValue);
    
    /* @~english Creates a new Image from with the texture's data.
     * Caller is responsible for releasing it by calling delete.
     *
     * @~chinese ��������������һ�� Image ʵ����
     * ʹ�����������Ҫ�������ٸ� Image ʵ����
     * 
     * @param flipImage @~english Whether or not to flip image.
     * @~chinese �Ƿ�תͼ��
     * @return @~english An image.
     * @~chinese һ�� Image ʵ����
     * @js NA
     */
    Image* newImage(bool flipImage = true);
    
    CC_DEPRECATED_ATTRIBUTE Image* newCCImage(bool flipImage = true) { return newImage(flipImage); };

    /** @~english Saves the texture into a file using JPEG format. The file will be saved in the Documents folder.
     * Returns true if the operation is successful.
     *
     * @~chinese ��������ΪJPEG��ʽ�ļ������ļ����������ڡ��ĵ����ļ��С�
     * ��������ɹ�����true��
     * 
     * @param filename @~english The file name.
     * @~chinese �ļ������֡�
     * @param isRGBA @~english The file is RGBA or not.
     * @~chinese ���ļ��Ƿ�ΪRGBA��ʽ��
     * @param callback @~english When the file is save finished,it will callback this function.
     * @~chinese ���ļ�����ɹ�����Ҫ���õĻص�������
     * @return @~english Returns true if the operation is successful.
     * @~chinese ��������ɹ�����true��
     */
    bool saveToFile(const std::string& filename, bool isRGBA = true, std::function<void (RenderTexture*, const std::string&)> callback = nullptr);

    /** @~english saves the texture into a file. The format could be JPG or PNG. The file will be saved in the Documents folder.
        Returns true if the operation is successful.
     * Notes: since v3.x, saveToFile will generate a custom command, which will be called in the following render->render().
     * So if this function is called in a event handler, the actual save file will be called in the next frame. If we switch to a different scene, the game will crash.
     * To solve this, add Director::getInstance()->getRenderer()->render(); after this function.
     *
     * @~chinese ��������һ���ļ��С�������JPG��PNG��ʽ�����ļ����������ڡ��ĵ����ļ��С�
     * ��������ɹ�����true��
     * ע:��Ϊv3.x��saveToFile������һ���Զ������������� render->render() �б����á�
     * ��ˣ������һ���¼���������У������������������ļ�����һ֡��ʹ�á���ʱ�����л���һ����ͬ�ĳ�������Ϸ�������
     * Ϊ�˽��������⣬���������ִ����֮�����һ�� Director::getInstance()->getRenderer()->render()��
     * 
     * @param filename @~english The file name.
     * @~chinese �ļ������֡�
     * @param format @~english The image format.
     * @~chinese ͼ���ʽ��
     * @param isRGBA @~english The file is RGBA or not.
     * @~chinese �Ƿ�Ϊ RGBA ��ʽ��
     * @param callback @~english When the file is save finished,it will callback this function.
     * @~chinese ���ļ�������ɺ�Ļص�������
     * @return @~english Returns true if the operation is successful.
     * @~chinese ��������ɹ�����true��
     */
    bool saveToFile(const std::string& filename, Image::Format format, bool isRGBA = true, std::function<void (RenderTexture*, const std::string&)> callback = nullptr);
    
    /** @~english Listen "come to background" message, and save render texture.
     * It only has effect on Android.
     * 
     * @~chinese �����˵���̨����Ϣ����������Ⱦ����
     * ��ֻ��Android����Ч����
     * 
     * @param event @~english Event Custom.
     * @~chinese �Զ����¼���
     */
    void listenToBackground(EventCustom *event);
    
    /** @~english Listen "come to foreground" message and restore the frame buffer object.
     * It only has effect on Android.
     *
     * @~chinese �����ص�ǰ̨����Ϣ�����ָ�֡����������
     * ��ֻ��Android����Ч����
     * 
     * @param event @~english Event Custom.
     * @~chinese �Զ����¼���
     */
    void listenToForeground(EventCustom *event);
    
    /** @~english Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT. They can be OR'ed. Valid when "autoDraw" is true. 
     *
     * @~chinese ��Ч�ı�־:GL_COLOR_BUFFER_BIT GL_DEPTH_BUFFER_BIT GL_STENCIL_BUFFER_BIT�����ǿ���ʹ�á��򡱲�������ϱ�ǡ�����autoDraw��Ϊ true ʱ��Ч��
     * 
     * @return @~english Clear flags.
     * @~chinese �����ʹ�õ� GL ��־��
     */
    inline unsigned int getClearFlags() const { return _clearFlags; };
    
    /** @~english Set flags.
     *
     * @~chinese ���ñ�־��
     * 
     * @param clearFlags @~english Valid flags: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT.
     * @~chinese ��Ч�ı�־:GL_COLOR_BUFFER_BIT GL_DEPTH_BUFFER_BIT GL_STENCIL_BUFFER_BIT��
     */
    inline void setClearFlags(unsigned int clearFlags) { _clearFlags = clearFlags; };
    
    /** @~english Clear color value. Valid only when "autoDraw" is true. 
     *
     * @~chinese �����ʹ�õ���ɫֵ��ֻ�е���autoDraw��Ϊ true ʱ��Ч��
     * 
     * @return @~english Color value.
     * @~chinese ��ɫֵ��
     */
    inline const Color4F& getClearColor() const { return _clearColor; };
    
    /** @~english Set color value. 
     *
     * @~chinese ���������ʹ�õ���ɫֵ��
     * 
     * @param clearColor @~english Color value.
     * @~chinese ��ɫֵ��
     */
    inline void setClearColor(const Color4F &clearColor) { _clearColor = clearColor; };
    
    /** @~english Value for clearDepth. Valid only when "autoDraw" is true. 
     *
     * @~chinese �����ʹ�õ����ֵ��ֻ�е���autoDraw��Ϊ true ʱ��Ч��
     * 
     * @return @~english Value for clearDepth.
     * @~chinese ʹ�õ����ֵ��
     */
    inline float getClearDepth() const { return _clearDepth; };
    
    /** @~english Set Value for clearDepth.
     *
     * @~chinese ���������ʹ�õ����ֵ��
     * 
     * @param clearDepth @~english Value for clearDepth.
     * @~chinese ʹ�õ����ֵ��
     */
    inline void setClearDepth(float clearDepth) { _clearDepth = clearDepth; };
    
    /** @~english Value for clear Stencil. Valid only when "autoDraw" is true.
     *
     * @~chinese ��ȡ�����ʹ�õ�ģ�塣ֻ�е���autoDraw��Ϊ true ʱ��Ч��
     * 
     * @return @~english Value for clear Stencil.
     * @~chinese ʹ�õ�ģ��
     */
    inline int getClearStencil() const { return _clearStencil; };
    
    /** @~english Set Value for clear Stencil.
     *
     * @~chinese ���������ʹ�õ�ģ�塣
     * 
     * @param clearStencil @~english Value for clear Stencil.
     * @~chinese ʹ�õ�ģ��
     */
    inline void setClearStencil(int clearStencil) { _clearStencil = clearStencil; };
    
    /** @~english When enabled, it will render its children into the texture automatically. Disabled by default for compatiblity reasons.
     * Will be enabled in the future.
     *
     * @~chinese ������ʱ�������Զ���Ⱦ�ӽڵ㡣���ڼ����ԵĿ��ǣ�Ĭ��ֵΪ�رա�
     * ��δ���������á�
     * 
     * @return @~english Return the autoDraw value.
     * @~chinese �����Ƿ��Զ���Ⱦ��
     */
    inline bool isAutoDraw() const { return _autoDraw; };
    
    /** @~english Set a valve to control whether or not render its children into the texture automatically. 
     *
     * @~chinese �����Ƿ��Զ���Ⱦ�ӽڵ㡣
     * 
     * @param isAutoDraw @~english Whether or not render its children into the texture automatically.
     * @~chinese �Ƿ��Զ���Ⱦ�ӽڵ㡣
     */
    inline void setAutoDraw(bool isAutoDraw) { _autoDraw = isAutoDraw; };

    /** @~english Gets the Sprite being used. 
     *
     * @~chinese ����ʹ�õ� Sprite��
     * 
     * @return @~english A Sprite.
     * @~chinese Sprite ʵ����
     */
    inline Sprite* getSprite() const { return _sprite; };
    
    /** @~english Sets the Sprite being used. 
     *
     * @~chinese ����ʹ�õ� Sprite��
     * 
     * @param sprite @~english A Sprite.
     * @~chinese Sprite ʵ����
     */
    inline void setSprite(Sprite* sprite) {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(_sprite);
        _sprite = sprite;
    };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    /** @~english Flag: Use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
     *
     * @~chinese ��־��ʹ�ôӳ����м���Ķ�ջ����������µ��ӵ�����ͶӰ����
     * 
     * @param keepMatrix @~english Wether or not use stack matrix computed from scene hierarchy or generate new modelView and projection matrix.
     * @~chinese �Ƿ�ʹ�ôӳ����м���Ķ�ջ����������µ��ӵ�����ͶӰ����
     * @js NA
     */
    void setKeepMatrix(bool keepMatrix);
    /**@~english Used for grab part of screen to a texture. 
     * @~chinese ���ڽ�ȡ��Ļ�����һ���֡�
     * @param rtBegin @~english The position of renderTexture on the fullRect.
     * @~chinese ��Ҫ��ȡ�����λ�á�
     * @param fullRect @~english The total size of screen.
     * @~chinese ��Ҫ��ȡ�ľ��������С��
     * @param fullViewport @~english The total viewportSize.
     * @~chinese �Ӵ���С��
     */
    void setVirtualViewport(const Vec2& rtBegin, const Rect& fullRect, const Rect& fullViewport);

public:
    /** @~english FIXME: should be procted.
     * but due to a bug in PowerVR + Android,
     * the constructor is public again.
     * @~chinese Ӧ��Ϊ protected��
     * �������� PowerVR + ��׿������ bug��
     * ���Թ��캯������ public��
     * @js ctor
     */
    RenderTexture();

    /**
     * @js NA
	 * @lua NA
     */
    virtual ~RenderTexture();
    /** @~english Initializes a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid.
     *
     * @~chinese ʹ��ָ���Ŀ�ȣ��߶Ⱥ����ظ�ʽ��ʼ��һ��RenderTexture���󣬣�ֻ��RGB��RGBA��ʽ���á���
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture����Ŀ�ȡ�
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture����ĸ߶ȡ�
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese ���ظ�ʽ(ֻ��RGB��RGBA��ʽ����)��
     * @return @~english If successed,it will return true.
     * @~chinese ����ɹ�,��������true��
     */
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format);
    /** @~english Initializes a RenderTexture object with width and height in Points and a pixel format( only RGB and RGBA formats are valid ) and depthStencil format. 
     *
     * @~chinese ʹ��ָ���Ŀ�ȣ��߶ȣ����ظ�ʽ�����ģ���ʽ��ʼ��һ��RenderTexture����
     * 
     * @param w @~english The RenderTexture object width.
     * @~chinese RenderTexture����Ŀ�ȡ�
     * @param h @~english The RenderTexture object height.
     * @~chinese RenderTexture����ĸ߶ȡ�
     * @param format @~english In Points and a pixel format( only RGB and RGBA formats are valid ).
     * @~chinese ���ظ�ʽ(ֻ��RGB��RGBA��ʽ����)��
     * @param depthStencilFormat @~english The depthStencil format.
     * @~chinese ���ģ���ʽ��
     * @return @~english If successed,it will return true.
     * @~chinese ����ɹ�,��������true��
     */
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format, GLuint depthStencilFormat);

protected:
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags);
    
    //flags: whether generate new modelView and projection matrix or not
    bool         _keepMatrix;
    Rect         _rtTextureRect;
    Rect         _fullRect;
    Rect         _fullviewPort;
    
    GLuint       _FBO;
    GLuint       _depthRenderBufffer;
    GLint        _oldFBO;
    Texture2D* _texture;
    Texture2D* _textureCopy;    // a copy of _texture
    Image*     _UITextureImage;
    Texture2D::PixelFormat _pixelFormat;
    
    // code for "auto" update
    GLbitfield   _clearFlags;
    Color4F    _clearColor;
    GLclampf     _clearDepth;
    GLint        _clearStencil;
    bool         _autoDraw;

    Sprite* _sprite;
    
    GroupCommand _groupCommand;
    CustomCommand _beginWithClearCommand;
    CustomCommand _clearDepthCommand;
    CustomCommand _clearCommand;
    CustomCommand _beginCommand;
    CustomCommand _endCommand;
    CustomCommand _saveToFileCommand;
    std::function<void (RenderTexture*, const std::string&)> _saveFileCallback;
protected:
    //renderer caches and callbacks
    void onBegin();
    void onEnd();

    void onClear();
    void onClearDepth();

    void onSaveToFile(const std::string& fileName, bool isRGBA = true);
    
    Mat4 _oldTransMatrix, _oldProjMatrix;
    Mat4 _transformMatrix, _projectionMatrix;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(RenderTexture);

};

// end of textures group
/// @}

NS_CC_END

#endif //__CCRENDER_TEXTURE_H__
