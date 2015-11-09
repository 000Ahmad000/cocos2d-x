/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
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

#ifndef _COCOS2D_CCLABEL_H_
#define _COCOS2D_CCLABEL_H_

#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCQuadCommand.h"
#include "2d/CCFontAtlas.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */


/**
 * @struct TTFConfig
 * @see `GlyphCollection`
 */
typedef struct _ttfConfig
{
    std::string fontFilePath;
    float fontSize;

    GlyphCollection glyphs;
    const char *customGlyphs;

    bool distanceFieldEnabled;
    int outlineSize;

    _ttfConfig(const char* filePath = "",float size = 12, const GlyphCollection& glyphCollection = GlyphCollection::DYNAMIC,
        const char *customGlyphCollection = nullptr,bool useDistanceField = false,int outline = 0)
        :fontFilePath(filePath)
        ,fontSize(size)
        ,glyphs(glyphCollection)
        ,customGlyphs(customGlyphCollection)
        ,distanceFieldEnabled(useDistanceField)
        ,outlineSize(outline)
    {
        if(outline > 0)
        {
            distanceFieldEnabled = false;
        }
    }
}TTFConfig;

class Sprite;
class SpriteBatchNode;
class DrawNode;
class EventListenerCustom;

/**
 * @brief @~english Label is a subclass of Node that knows how to render text labels.
 *
 * Label can be created with:
 * - A true type font file.
 * - A bitmap font file.
 * - A char map file.
 * - The built in system font.
 *
 * Bitmap Font supported editors:
 * - http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
 * - http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
 * - http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
 * - http://www.angelcode.com/products/bmfont/ (Free, Windows only)
 * @~chinese Label(�ı�)��Node������,��֪�������Ⱦ�ı���
 * 
 * �ı�����ͨ�����·���������:
 * - һ��TTF�����ļ���
 * - һ��λͼ�����ļ���
 * - һ���ַ�ӳ���ļ���
 * -  ���õ�ϵͳ���塣
 * 
 * ֧��λͼ����ı༭��:
 * - http://glyphdesigner.71squared.com/ (��ҵ��, Mac OS X)
 * - http://www.n4te.com/hiero/hiero.jnlp (��ѵ�, Java)
 * - http://slick.cokeandcode.com/demos/hiero.jnlp (��ѵ�, Java)
 * - http://www.angelcode.com/products/bmfont/ (��ѵ�, Windows only)
 * @js NA
 */
class CC_DLL Label : public Node, public LabelProtocol, public BlendProtocol
{
public:
    /// @name Creators
    /// @{

    /**@~english
     * Allocates and initializes a Label, with default settings.
     *
     * @~chinese 
     * ʹ��Ĭ�����÷���ͳ�ʼ��һ���ı���
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ���Զ��ͷŵ��ı�����
     */
    static Label* create();

    /**@~english
     * Allocates and initializes a Label, base on platform-dependent API.
     *
     * @~chinese 
     * ����ƽ̨��ص�API�����ͳ�ʼ��һ���ı�
     * 
     * @param text @~english The initial text.
     * @~chinese ��ʼ�ı����ݡ�
     * @param font @~english A font file or a font family name.
     * @~chinese һ�������ļ����������ơ�
     * @param fontSize @~english The font size. This value must be > 0.
     * @~chinese �����С�����ֵ�������0��
     * @param dimensions @~english dimensions of the label node
     * @~chinese �ı������ݴ�С��
     * @param hAlignment @~english The text horizontal alignment.
     * @~chinese ˮƽ���뷽ʽ��
     * @param vAlignment @~english The text vertical alignment.
     *
     * @~chinese ��ֱ���뷽ʽ��
     * 
     * @warning @~english It will generate texture by the platform-dependent code.
     *
     * @~chinese ����ͨ��ƽ̨��صĴ�������������
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ���Զ��ͷŵ��ı�����
     */
    static Label* createWithSystemFont(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**@~english
     * Allocates and initializes a Label, based on FreeType2.
     *
     * @~chinese 
     * ʹ��FreeType2�ⴴ���ͳ�ʼ��һ���ı���
     * 
     * @param text @~english The initial text.
     * @~chinese ����ı����ݡ�
     * @param fontFilePath @~english A font file.
     * @~chinese һ��TTF�����ļ���
     * @param fontSize @~english The font size. This value must be > 0.
     * @~chinese �����С�����ֵ�������0��
     * @param dimensions @~english dimensions of the label node
     * @~chinese �ı������ݴ�С
     * @param hAlignment @~english The text horizontal alignment.
     * @~chinese ˮƽ���뷽ʽ��
     * @param vAlignment @~english The text vertical alignment.
     *
     * @~chinese ��ֱ���뷽ʽ��
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ���Զ��ͷŵ��ı�����
     */
    static Label * createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**@~english
     * Allocates and initializes a Label, base on FreeType2.
     *
     * @~chinese 
     * ʹ��FreeType2�ⴴ���ͳ�ʼ��һ���ı�
     * 
     * @param ttfConfig @~english A pointer to a TTFConfig object.
     * @~chinese һ��TTFConfig����ʵ����
     * @param text @~english The initial text.
     * @~chinese ����ı����ݡ�
     * @param hAlignment @~english The text horizontal alignment.
     * @~chinese ˮƽ���뷽ʽ
     * @param maxLineWidth @~english The max line width.
     *
     * @~chinese ����߿�
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ���Զ��ͷŵ��ı�����
     * @see TTFConfig setTTFConfig setMaxLineWidth
     */
    static Label* createWithTTF(const TTFConfig& ttfConfig, const std::string& text, 
        TextHAlignment hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0);

    /**@~english
     * Allocates and initializes a Label, with a bitmap font file.
     *
     * @~chinese 
     * ʹ��λͼ�����ļ������ͳ�ʼ��һ���ı���
     * 
     * @param bmfontPath @~english A bitmap font file, it's a FNT format.
     * @~chinese һ��λͼ�����ļ�,����FNT��ʽ��
     * @param text @~english The initial text.
     * @~chinese ��ʼ�ı����ݡ�
     * @param hAlignment @~english Text horizontal alignment.
     * @~chinese ˮƽ���뷽ʽ��
     * @param maxLineWidth @~english The max line width.
     * @~chinese ����߿�
     * @param imageOffset The first character offset in BMfont
     *@~english
     * @~chinese ��һ���ַ�����λͼ�ļ��е�ƫ��
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ����ǩ�Զ��ͷŶ���
     * @see setBMFontFilePath setMaxLineWidth
     */
    static Label* createWithBMFont(const std::string& bmfontPath, const std::string& text,
        const TextHAlignment& hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0,
        const Vec2& imageOffset = Vec2::ZERO);

    /**@~english
     * Allocates and initializes a Label, with char map configuration.
     *
     * @~chinese 
     * ʹ���ַ�ӳ���ļ��������ͳ�ʼ��һ���ı�
     * 
     * @param charMapFile @~english A char map file, it's a PNG format.
     * @~chinese һ���ַ�ӳ���ļ�,����һ��PNG��ʽ���ļ���
     * @param itemWidth @~english The width in points of each element.
     * @~chinese ÿ��Ԫ�صĿ��,��λ�ǡ��㡱��
     * @param itemHeight @~english The height in points of each element.
     * @~chinese ÿ��Ԫ�صĸ߶�,��λ���㡱��
     * @param startCharMap @~english The starting char of the char map.
     *
     * @~chinese �ַ�ӳ���ļ�����ʼ�ַ�
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ���Զ��ͷŵ��ı�����
     */
    static Label * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Allocates and initializes a Label, with char map configuration.
     *
     * @~chinese 
     * ʹ���ַ�ӳ���ļ������ͳ�ʼ��һ���ı�
     * 
     * @param texture @~english A pointer to an existing Texture2D object.
     * @~chinese һ�����е��������ָ�롣
     * @param itemWidth @~english The width in points of each element.
     * @~chinese ÿ��Ԫ�صĿ��,��λ�ǡ��㡱��
     * @param itemHeight @~english The height in points of each element.
     * @~chinese ÿ��Ԫ�صĸ߶ȣ���λ�ǡ��㡱��
     * @param startCharMap @~english The starting char of the char map.
     *
     * @~chinese �ַ�ӳ���ļ�����ʼ�ַ�
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ���Զ��ͷŵ��ı�����
     */
    static Label * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Allocates and initializes a Label, with char map configuration.
     *
     * @~chinese 
     * ʹ���ַ�ӳ���ļ��������ͳ�ʼ��һ���ı�
     * 
     * @param plistFile @~english A configuration file of char map.
     *
     * @~chinese һ���ַ�ӳ��������ļ���
     * 
     * @return @~english An automatically released Label object.
     * @~chinese һ���Զ��ͷŵ��ı�����
     */
    static Label * createWithCharMap(const std::string& plistFile);

    //  end of creators group
    /// @}

    /// @{
    /// @name Font methods

    /**@~english
     * Sets a new TTF configuration to Label.
     * @~chinese
     * ����һ���µ�TTFConfig
     * @see `TTFConfig`
     */
    virtual bool setTTFConfig(const TTFConfig& ttfConfig);

    /**@~english
     * Returns the TTF configuration object used by the Label.
     * @~chinese 
     * �����ı������TTF���ö���
     * @see `TTFConfig`
     */
    virtual const TTFConfig& getTTFConfig() const { return _fontConfig;}

    /** @~english Sets a new bitmap font to Label  @~chinese ���ı�����һ���µ�λͼ����*/
    virtual bool setBMFontFilePath(const std::string& bmfontFilePath, const Vec2& imageOffset = Vec2::ZERO);

    /** @~english Returns the bitmap font used by the Label. @~chinese ���ص�ǰ�ı�ʹ�õ�λͼ����.*/
    const std::string& getBMFontFilePath() const { return _bmFontPath;}

    /**@~english
     * Sets a new char map configuration to Label.
     *
     * @~chinese 
     * ���ı�����һ���µ��ַ�ӳ���ļ���
     * 
     * @see `createWithCharMap(const std::string&,int,int,int)`
     */
    virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Sets a new char map configuration to Label.
     *
     * @~chinese 
     * ���ı�����һ���µ��ַ�ӳ���ļ�
     * 
     * @see `createWithCharMap(Texture2D*,int,int,int)`
     */
    virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);

    /**@~english
     * Sets a new char map configuration to Label.
     *
     * @~chinese 
     * ���ı�����һ���µ��ַ�ӳ���ļ�
     * 
     * @see `createWithCharMap(const std::string&)`
     */
    virtual bool setCharMap(const std::string& plistFile);

    /**@~english
     * Sets a new system font to Label.
     *
     * @~chinese 
     * ���ı�����һ���µ�ϵͳ����
     * 
     * @param font @~english A font file or a font family name.
     * @~chinese һ�������ļ�����������
     */
    virtual void setSystemFontName(const std::string& font);

    /** @~english Returns the system font used by the Label. @~chinese �����ı�ʹ�õ�ϵͳ���塣*/
    virtual const std::string& getSystemFontName() const { return _systemFont;}

    /* @~english Sets the system font size of Label. @~chinese �����ı�ʹ�õ�ϵͳ�����С��*/
    virtual void setSystemFontSize(float fontSize);

    /** @~english Returns the bitmap font path used by the Label. @~chinese �����ı�ʹ�õ�λͼ����·����*/
    virtual float getSystemFontSize() const { return _systemFontSize;}

    /**
     * @warning @~english This method is not recommended for game developers.
     * @~chinese ����������Ƽ���Ϸ�����ߵ���,���Ǹ��༭���õġ�
     */
    virtual void requestSystemFontRefresh() { _systemFontDirty = true;}

    //  end of font methods
    /// @}

    /** @~english Sets the text that this Label is to display. @~chinese �����ı���ʾ���ַ�����*/
    virtual void setString(const std::string& text) override;

    /** @~english Return the text the Label is displaying. @~chinese �����ı���ʾ���ַ�����*/
    virtual const std::string& getString() const override {  return _utf8Text; }

    /**
     * @~english Get the string's display line number.
     * @~chinese ��ȡ�ı���ʾ��������
     *
     * @return @~english Label line number. @~chinese �ı�������
     */
    int getStringNumLines();

    /**
     * @~english Get the string length.
     * @~chinese ��ȡ�ַ����ĳ���
     *
     * @return @~english Label string length. @~chinese �ı����ַ�������
     */
    int getStringLength();

    /**@~english
     * Sets the text color of Label.
     *
     * The text color is different from the color of Node.
     *
     * @~chinese 
     * �����ı����ַ�������ɫ��
     * 
     * �ı�����ɫ��ͬ�ڽڵ����ɫ��
     * 
     * @warning @~english Limiting usage when the Label created with true type font or system font.
     * @~chinese ֻ��ʹ��TTF�������ϵͳ���崴�����ı�����ſ��Ե������������
     */
    virtual void setTextColor(const Color4B &color);

    /** @~english Returns the text color of the Label. @~chinese �����ı����ַ�������ɫ��*/
    const Color4B& getTextColor() const { return _textColor;}

    /**@~english
     * Enable shadow effect to Label.
     *
     * @~chinese 
     * �����ı�����ӰЧ��
     * 
     */
    virtual void enableShadow(const Color4B& shadowColor = Color4B::BLACK,const Size &offset = Size(2,-2), int blurRadius = 0);

    /**@~english
     * Enable outline effect to Label.
     * @~chinese 
     * �����ı������Ч����
     * @warning @~english Limiting use to only when the Label created with true type font or system font.
     * @~chinese ֻ��ʹ��TTF�������ϵͳ���崴�����ı�����ſ��Ե������������
     */
    virtual void enableOutline(const Color4B& outlineColor,int outlineSize = -1);

    /**@~english
    * Enable glow effect to Label.
     * @~chinese 
     * �����ı��ķ���Ч��
    * @warning @~english Limiting use to only when the Label created with true type font.
     * @~chinese ֻ��ʹ��TTF���崴�����ı�����ſ��Ե������������
    */
    virtual void enableGlow(const Color4B& glowColor);

    /**@~english
     * Disable all effect to Label.
     * @~chinese 
     * ���������ı���Ч��
     * @warning @~english Please use disableEffect(LabelEffect::ALL) instead of this API.
     * @~chinese ��ʹ��disableEffect(LabelEffect:ALL)���������API��
     */
    virtual void disableEffect();

    /**@~english
     * Disable effect to Label.
     *
     * @~chinese 
     * �����ı���Ч��
     * 
     * @see `LabelEffect`
     */
    virtual void disableEffect(LabelEffect effect);

    /** @~english Sets the Label's text horizontal alignment. @~chinese �����ı���ˮƽ���롣*/
    void setAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment);}

    /** @~english Returns the Label's text horizontal alignment. @~chinese ��ȡ�ı��Ķ��뷽ʽ��*/
    TextHAlignment getTextAlignment() const { return _hAlignment;}

    /** @~english Sets the Label's text alignment. @~chinese �����ı���ˮƽ�ʹ�ֱ���뷽ʽ��*/
    void setAlignment(TextHAlignment hAlignment,TextVAlignment vAlignment);

    /** @~english Sets the Label's text horizontal alignment. @~chinese �����ı���ˮƽ���롣*/
    void setHorizontalAlignment(TextHAlignment hAlignment) { setAlignment(hAlignment,_vAlignment); }

    /** @~english Returns the Label's text horizontal alignment. @~chinese �����ı���ˮƽ���롣*/
    TextHAlignment getHorizontalAlignment() const { return _hAlignment; }

    /** @~english Sets the Label's text vertical alignment. @~chinese �����ı���ֱ���롣*/
    void setVerticalAlignment(TextVAlignment vAlignment) { setAlignment(_hAlignment,vAlignment); }

    /** @~english Returns the Label's text vertical alignment. @~chinese �����ı���ֱ���롣*/
    TextVAlignment getVerticalAlignment() const { return _vAlignment; }

    /**@~english
     * Specify what happens when a line is too long for Label.
     *
     * @~chinese 
     * ָ�����ı�̫��ʱ���Ƿ���Ҫ���С�
     * 
     * @param breakWithoutSpace @~english Lines are automatically broken between words if this value is false.
     * @~chinese ���������false����ô���ı�����ʱ���Զ����С�
     */
    void setLineBreakWithoutSpace(bool breakWithoutSpace);

    /**@~english
     * Makes the Label at most this line untransformed width.
     * The Label's max line width be used for force line breaks if the value not equal zero.
     * @~chinese 
     * �����ı�������п�
     * ����ı����п�������Ļ�����ô����������ǿ�ƻ���
     */
    void setMaxLineWidth(float maxLineWidth);
    /**
     *@~english Return the maximize line width.
     *@~chinese ��ȡ�ı�������п�
     * @return @~english The maximize line width. @~chinese �ı�������п�
     */
    float getMaxLineWidth() { return _maxLineWidth; }

    /**@~english
     * Makes the Label exactly this untransformed width.
     *
     * The Label's width be used for text align if the value not equal zero.
     * @~chinese 
     * �����ı����п�
     * 
     * ����п�Ϊ0�������������������ı���
     */
    void setWidth(float width) { setDimensions(width,_labelHeight);}
    /**
     * @~english Get the label width.
     * @~chinese �����ı����п�
     *
     * @return @~english The line width. @~chinese �п�
     */
    float getWidth() const { return _labelWidth; }

    /**@~english
     * Makes the Label exactly this untransformed height.
     *
     * The Label's height be used for text align if the value not equal zero.
     * The text will display of incomplete when the size of Label not enough to support display all text.
     * @~chinese 
     * �����ı����и�
     * 
     * ����и߲�Ϊ0�������������������ı�
     * ����ı����ݴ����ı��Ĵ�С����ô���ܻ���ʾ������
     */
    void setHeight(float height){ setDimensions(_labelWidth, height); }
    /**
     *@~english Get the label height.
     *@~chinese �����ı����и�
     *
     * @return @~english The line height. @~chinese �и�
     */
    float getHeight() const { return _labelHeight; }

    /** @~english Sets the untransformed size of the Label in a more efficient way.
     * @~chinese ����Ч�������ı���С�ķ����������С��δ��������任�Ĵ�С��
     */
    void setDimensions(float width, float height);
    /**
     * @~english Get the dimension of label.
     * @~chinese ��ȡ�ı��Ĵ�С
     *
     * @return @~english the dimension in Size. @~chinese �ı���С
     */
    const Size& getDimensions() const{ return _labelDimensions;}

    /** @~english Update content immediately. @~chinese ���������ı����ݡ�*/
    virtual void updateContent();

    /**@~english
     * Provides a way to treats each character like a Sprite.
     * @~chinese 
     * �ṩ��һ�ַ���,���԰�ÿ���ַ�����������������
     * @warning @~english No support system font.
     * @~chinese ��֧��ϵͳ���塣
     */
    virtual Sprite * getLetter(int lettetIndex);

    /** @~english Makes the Label to clip upper and lower margin for reduce height of Label.
     *@~chinese �����Ƿ�ü��ı����±߾࣬��Ҫ���������ı��ĵ��ԡ�
     */
    void setClipMarginEnabled(bool clipEnabled) { _clipEnabled = clipEnabled; }

    /**
     *@~english Determines whether clipping upper and lower margin of label.
     *@~chinese �ж��ı��Ƿ�ü����±߾�
     *
     * @return @~english Retuen true if enable clipping margin, otherwise return false.
     * @~chinese �������ü��ı����±߿��򷵻��棬���򷵻ؼ١�
     */
    bool isClipMarginEnabled() const { return _clipEnabled; }

    /** @~english Sets the line height of the Label.
     * @~chinese �����ı����иߡ�
     * @warning @~english Not support system font.
     * @~chinese ��֧��ϵͳ���塣
     * @since v3.2.0
     */
    void setLineHeight(float height);

    /**@~english
     * Returns the line height of this Label.
     * @~chinese 
     * ��������ı����иߡ�
     * @warning @~english Not support system font.
     * @~chinese ��֧��ϵͳ����
     * @since v3.2.0
     */
    float getLineHeight() const;

    /**@~english
     * Sets the additional kerning of the Label.
     *
     * @~chinese 
     * �����ı����ַ���ࡣ
     * 
     * @warning @~english Not support system font.
     * @~chinese ��֧��ϵͳ���塣
     * @since v3.2.0
     */
    void setAdditionalKerning(float space);

    /**@~english
     * Returns the additional kerning of the Label.
     *
     * @~chinese 
     * �����ı����ַ����
     * 
     * @warning @~english Not support system font.
     * @~chinese ��֧��ϵͳ���塣
     * @since v3.2.0
     */
    float getAdditionalKerning() const;

    /**
     * @~english Get the font atlas
     * @~chinese ����һ��FontAtlas����ָ��
     *
     * @return @~english A FontAtlas pointer @~chinese FontAtlasָ��
     */
    FontAtlas* getFontAtlas() { return _fontAtlas; }

    virtual const BlendFunc& getBlendFunc() const override { return _blendFunc; }
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual bool isOpacityModifyRGB() const override { return _isOpacityModifyRGB; }
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;

    virtual std::string getDescription() const override;

    virtual const Size& getContentSize() const override;
    virtual Rect getBoundingBox() const override;

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleanup = true) override;
    virtual void setGlobalZOrder(float globalZOrder) override;

    CC_DEPRECATED_ATTRIBUTE static Label* create(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);
    CC_DEPRECATED_ATTRIBUTE virtual void setFontDefinition(const FontDefinition& textDefinition);
    CC_DEPRECATED_ATTRIBUTE FontDefinition getFontDefinition() const { return _getFontDefinition(); }
    CC_DEPRECATED_ATTRIBUTE int getCommonLineHeight() const { return (int)getLineHeight();}

CC_CONSTRUCTOR_ACCESS:
    /**@~english
     * Constructor of Label.
     * @~chinese 
     * ���캯���ı�ǩ��
     * @js NA
     */
    Label(TextHAlignment hAlignment = TextHAlignment::LEFT,
      TextVAlignment vAlignment = TextVAlignment::TOP);

    /**@~english
     * Destructor of Label.
     * @~chinese 
     * ���������ı�ǩ��
     * @js NA
     * @lua NA
     */
    virtual ~Label();

protected:
    struct LetterInfo
    {
        char16_t utf16Char;
        bool valid;
        float positionX;
        float positionY;
        int atlasIndex;
        int lineIndex;
    };

    enum class LabelType {
        TTF,
        BMFONT,
        CHARMAP,
        STRING_TEXTURE
    };

    virtual void setFontAtlas(FontAtlas* atlas, bool distanceFieldEnabled = false, bool useA8Shader = false);

    void computeStringNumLines();

    void onDraw(const Mat4& transform, bool transformUpdated);
    void onDrawShadow(GLProgram* glProgram);
    void drawSelf(bool visibleByCamera, Renderer* renderer, uint32_t flags);

    bool multilineTextWrapByChar();
    bool multilineTextWrapByWord();

    void updateLabelLetters();
    virtual void alignText();
    void computeAlignmentOffset();
    bool computeHorizontalKernings(const std::u16string& stringToRender);

    void recordLetterInfo(const cocos2d::Vec2& point, char16_t utf16Char, int letterIndex, int lineIndex);
    void recordPlaceholderInfo(int letterIndex, char16_t utf16Char);
    
    void updateQuads();

    void createSpriteForSystemFont(const FontDefinition& fontDef);
    void createShadowSpriteForSystemFont(const FontDefinition& fontDef);

    virtual void updateShaderProgram();

    void reset();

    FontDefinition _getFontDefinition() const;

    virtual void updateColor() override;

    LabelType _currentLabelType;
    bool _contentDirty;
    std::u16string _utf16Text;
    std::string _utf8Text;
    int _numberOfLines;

    std::string _bmFontPath;
    TTFConfig _fontConfig;
    float _outlineSize;

    bool _systemFontDirty;
    std::string _systemFont;
    float _systemFontSize;
    Sprite* _textSprite;
    Sprite* _shadowNode;

    FontAtlas* _fontAtlas;
    Vector<SpriteBatchNode*> _batchNodes;
    std::vector<LetterInfo> _lettersInfo;

    //! used for optimization
    Sprite *_reusedLetter;
    Rect _reusedRect;
    int _lengthOfString;

    //layout relevant properties.
    float _lineHeight;
    float _lineSpacing;
    float _additionalKerning;
    int* _horizontalKernings;
    bool _lineBreakWithoutSpaces;
    float _maxLineWidth;
    Size _labelDimensions;
    float _labelWidth;
    float _labelHeight;
    TextHAlignment _hAlignment;
    TextVAlignment _vAlignment;

    float _textDesiredHeight;
    std::vector<float> _linesWidth;
    std::vector<float> _linesOffsetX;
    float _letterOffsetY;
    float _tailoredTopY;
    float _tailoredBottomY;

    LabelEffect _currLabelEffect;
    Color4F _effectColorF;
    Color4B _textColor;
    Color4F _textColorF;

    QuadCommand _quadCommand;
    CustomCommand _customCommand;
    Mat4  _shadowTransform;
    GLuint _uniformEffectColor;
    GLuint _uniformTextColor;
    bool _useDistanceField;
    bool _useA8Shader;

    bool _shadowDirty;
    bool _shadowEnabled;
    Size _shadowOffset;
    
    Color4F _shadowColor4F;
    Color3B _shadowColor3B;
    GLubyte _shadowOpacity;
    float _shadowBlurRadius;

    bool _clipEnabled;
    bool _blendFuncDirty;
    BlendFunc _blendFunc;

    /// whether or not the label was inside bounds the previous frame
    bool _insideBounds;

    bool _isOpacityModifyRGB;

    std::unordered_map<int, Sprite*> _letters;

    EventListenerCustom* _purgeTextureListener;
    EventListenerCustom* _resetTextureListener;

#if CC_LABEL_DEBUG_DRAW
    DrawNode* _debugDrawNode;
#endif
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Label);
};

// end group
/// @}

NS_CC_END

#endif /*__COCOS2D_CCLABEL_H */
