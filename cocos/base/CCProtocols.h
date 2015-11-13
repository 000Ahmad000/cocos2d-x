/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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

#ifndef __BASE_CCPROTOCOLS_H__
#define __BASE_CCPROTOCOLS_H__
/// @cond DO_NOT_SHOW

#include <string>

#include "base/ccTypes.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

/**
 * @~english
 * RGBA protocol that affects Node's color and opacity
 * @~chinese 
 * RGBAЭ��Ӱ��ڵ����ɫ�Ͳ�͸����
 */
class CC_DLL __RGBAProtocol
{
public:
    virtual ~__RGBAProtocol() {}
    
    /**
     * @~english
     * Changes the color with R,G,B bytes
     *
     * @~chinese 
     * �ı���ɫ��R,G,Bֵ
     * 
     * @param color @~english Example: Color3B(255,100,0) means R=255, G=100, B=0
     * @~chinese ����:Color3B(255,100,0) ����˼��ʵ�� R=255, G=100, B=0
     * @js NA
     * @lua NA
     */
    virtual void setColor(const Color3B& color) = 0;
    
    /**
     * @~english
     * Returns color that is currently used.
     *
     * @~chinese 
     * ���ص�ǰʹ�õ���ɫ��
     * 
     * @return @~english The Color3B contains R,G,B bytes.
     * @~chinese Color3B����R,G,Bֵ��
     * @js NA
     * @lua NA
     */
    virtual const Color3B& getColor() const = 0;
    
    /**
     * @~english
     * Returns the displayed color.
     *
     * @~chinese 
     * ������ʾ��ɫ��
     * 
     * @return @~english The Color3B contains R,G,B bytes.
     * @~chinese Color3B����R,G,Bֵ��
     * @js NA
     * @lua NA
     */
    virtual const Color3B& getDisplayedColor() const = 0;
    
    /**
     * @~english
     * Returns the displayed opacity.
     *
     * @~chinese 
     * ������ʾ��͸���ȡ�
     * 
     * @return  @~english The opacity of sprite, from 0 ~ 255
     * @~chinese ����Ĳ�͸���ȣ���Χ��0 ~ 255
     * @js NA
     * @lua NA
     */
    virtual GLubyte getDisplayedOpacity() const = 0;

    /**
     * @~english
     * Returns the opacity.
     *
     * The opacity which indicates how transparent or opaque this node is.
     * 0 indicates fully transparent and 255 is fully opaque.
     *
     * @~chinese 
     * ���ز�͸���ȡ�
     * 
     * ��͸����,��ʾ�ڵ�͸����͸����
     * 0��ʾ��ȫ͸����255����ȫ��͸���ġ�
     * 
     * @return  @~english The opacity of sprite, from 0 ~ 255
     * @~chinese �����͸���ȣ���Χ��0 ~ 255
     * @js NA
     * @lua NA
     */
    virtual GLubyte getOpacity() const = 0;
    
    /**
     * @~english
     * Changes the opacity.
     *
     * @~chinese 
     * �ı䲻͸���ȡ�
     * 
     * @param opacity   @~english Goes from 0 to 255, where 255 means fully opaque and 0 means fully transparent.
     * @~chinese ��0��255,255��ζ����ȫ��͸��,0��ʾ��ȫ͸����
     * @js NA
     * @lua NA
     */
    virtual void setOpacity(GLubyte opacity) = 0;
    
    // optional
    
    /**
     * @~english
     * Changes the OpacityModifyRGB property.
     * If this property is set to true, then the rendered color will be affected by opacity.
     * Normally, r = r * opacity/255, g = g * opacity/255, b = b * opacity/255.
     *
     * @~chinese 
     * OpacityModifyRGB���Ա仯��
     * �������������Ϊtrue,��ô���ܵ���͸���ȵ�Ӱ�������ɫ��
     * ͨ�������,r = r * opacity/255, g = g * opacity/255, b = b * opacity/255.
     * 
     * @param value @~english If true, then the opacity will be applied as: glColor(R,G,B,opacity);
     *              If false, then the opacity will be applied as: glColor(opacity, opacity, opacity, opacity);
     * @~chinese �������Ϊtrue,��ô��͸����������ʹ��: glColor(R,G,B,opacity);
     * ���Ϊfalse,��͸���Ƚ�������ʹ��: glColor(opacity, opacity, opacity, opacity);
     *
     * @js NA
     * @lua NA
     */
    virtual void setOpacityModifyRGB(bool value) = 0;
    
    /**
     * @~english
     * Returns whether or not the opacity will be applied using glColor(R,G,B,opacity)
     * or glColor(opacity, opacity, opacity, opacity)
     *
     * @~chinese 
     * �����Ƿ񽫲��ò�͸���ȣ�glColor��R��G��B��opacity��
     * ����glColor(opacity, opacity, opacity, opacity)
     * 
     * @return  @~english Returns opacity modify flag.
     * @~chinese ���ز�͸�����޸ı�־��
     * @js NA
     * @lua NA
     */
    virtual bool isOpacityModifyRGB() const = 0;
    
    /**
     * @~english
     *  whether or not color should be propagated to its children.
     * @~chinese 
     * ��ɫ�Ƿ�Ӧ�ô��������ӽڵ㡣
     * @js NA
     * @lua NA
     */
    virtual bool isCascadeColorEnabled() const = 0;

    /**
     * @~english
     *  Set whether or not color should be propagated to its children.
     * @~chinese
     * ������ɫ�Ƿ�Ӧ�ô��������ӽڵ㡣
     *
     * @param cascadeColorEnabled @~english whether or not color should be propagated to its children.
     * @~chinese
     * ��ɫ�Ƿ�Ӧ�ô��������ӽڵ㡣
     *
     * @js NA
     * @lua NA
     */
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) = 0;
    
    /**
     * @~english
     *  recursive method that updates display color
     * @~chinese 
     * ʹ�õݹ�ķ���ȥ������ʾ����ɫ
     * @js NA
     * @lua NA
     */
    virtual void updateDisplayedColor(const Color3B& color) = 0;
    
    /**
     * @~english
     *  whether or not opacity should be propagated to its children.
     * @~chinese 
     * ��͸�����Ƿ�Ӧ�ô��������ӽڵ㡣
     * @js NA
     * @lua NA
     */
    virtual bool isCascadeOpacityEnabled() const = 0;

    /**
     * @~english Set whether or not opacity should be propagated to its children.
     * @~chinese
     * ���ò�͸�����Ƿ�Ӧ�ô��������ӽڵ㡣
     * @js NA
     * @lua NA
     */
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) = 0;
    
    /**
     * @~english
     *  recursive method that updates the displayed opacity.
     * @~chinese 
     * ʹ�õݹ�ķ���ȥ������ʾ�Ĳ�͸���ȡ�
     * @js NA
     * @lua NA
     */
    virtual void updateDisplayedOpacity(GLubyte opacity) = 0;
};

/**
 * @~english
 * Specify the blending function according glBlendFunc
 * Please refer to glBlendFunc in OpenGL ES Manual
 * http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBlendFunc.xml for more details.
 * @~chinese 
 * ָ��glBlendFunc��Ϻ���
 * �����glBlendFunc��OpenGL ES�ֲ�
 * http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBlendFunc.xml for more details.
 */
class CC_DLL BlendProtocol
{
public:
    virtual ~BlendProtocol() {}

    /**
     * @~english
     * Sets the source blending function.
     *
     * @~chinese 
     * ����Դ��Ϻ�����
     * 
     * @param blendFunc @~english A structure with source and destination factor to specify pixel arithmetic, 
     *                  e.g. {GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
     * @~chinese �ṹ��Դ��Ŀ������ָ����������,
     * ����GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
     * @js NA
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc &blendFunc) = 0;

    /**
     * @~english
     * Returns the blending function that is currently being used.
     * 
     * @~chinese 
     * ���ص�ǰ����ʹ�õĻ�Ϻ�����
     * 
     * @return @~english A BlendFunc structure with source and destination factor which specified pixel arithmetic.
     * @~chinese BlendFunc�ṹָ��Դ��Ŀ�������������㡣
     * @js NA
     * @lua NA
     */
    virtual const BlendFunc &getBlendFunc() const = 0;
};

/**
 * @~english
 * Node objects that uses a Texture2D to render the images.
 * The texture can have a blending function.
 * If the texture has alpha premultiplied the default blending function is:
 *   src=GL_ONE dst= GL_ONE_MINUS_SRC_ALPHA
 * else
 *   src=GL_SRC_ALPHA dst= GL_ONE_MINUS_SRC_ALPHA
 * But you can change the blending function at any time.
 * @~chinese 
 * �ڵ����ʹ��Texture2D��ʾͼ��
 * ������Ի�Ϻ�����
 * ������͸�������Ĭ�ϻ�Ϻ�����:
 * src = GL_ONE dst = GL_ONE_MINUS_SRC_ALPHA
 * ����:
 * src = GL_SRC_ALPHA dst = GL_ONE_MINUS_SRC_ALPHA
 * ��������κ�ʱ��ı��Ϻ�����
 */
class CC_DLL TextureProtocol : public BlendProtocol
{
public:
    virtual ~TextureProtocol() {}

    /**
     * @~english
     * Returns the currently used texture
     *
     * @~chinese 
     * ���ص�ǰʹ�õ�����
     * 
     * @return  @~english The texture that is currently being used.
     * @~chinese ��������ʹ�õ�����
     * @js NA
     * @lua NA
     */
    virtual Texture2D* getTexture() const = 0;

    /**
     * @~english
     * Sets a new texture. It will be retained.
     *
     * @~chinese 
     * ����һ���µ�����
     * 
     * @param texture @~english A valid Texture2D object, which will be applied to this sprite object.
     * @~chinese һ����ЧTexture2D����,������Ӧ�õ�������顣
     * @js NA
     * @lua NA
     */
    virtual void setTexture(Texture2D *texture) = 0;
};

/**
 * @~english
 * Common interface for Labels
 * @~chinese 
 * ͨ�ýӿڵı�ǩ
 */
class CC_DLL LabelProtocol
{
public:
    virtual ~LabelProtocol() {}

    /**
     * @~english
     * Sets a new label using a string
     *
     * @~chinese 
     * ʹ��һ���ַ�������һ���µ�Label
     * 
     * @param label @~english A null terminated string
     * @~chinese �Կ��ַ���β���ַ���
     * @js NA
     * @lua NA
     */
    virtual void setString(const std::string &label) = 0;

    /**
     * @~english
     * Returns the string that is currently being used in this label 
     *
     * @~chinese 
     * �����ַ�����Ŀǰʹ�õ������ǩ
     * 
     * @return @~english The string that is currently being used in this label
     * @~chinese ���Label����ʹ�õ��ַ���
     * @js NA
     * @lua NA
     */
    virtual const std::string& getString() const = 0;
};

/**
 * @~english
 * OpenGL projection protocol 
 * @~chinese 
 * OpenGLͶӰЭ��
 */
class CC_DLL DirectorDelegate
{
public:
    virtual ~DirectorDelegate() {}

    /**
     * @~english
     * Will be called by Director when the projection is updated, and "custom" projection is used
     * @~chinese 
     * ��DirectorͶӰʱ����,����ʹ�á�custom��ͶӰ�ķ���
     * @js NA
     * @lua NA
     */
    virtual void updateProjection() = 0;
};

NS_CC_END

/// @endcond
#endif // __BASE_CCPROTOCOLS_H__
