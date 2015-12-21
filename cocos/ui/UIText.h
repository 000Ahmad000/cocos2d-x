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

#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/ccTypes.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN

class Label;

namespace ui {

/**
 * @class Text
 * @brief @~english For creating a system font or a TTF font Text.
 * @~chinses ������ʾϵͳ�����ttf������ı��ؼ�
 */
class CC_GUI_DLL Text : public Widget
{

    DECLARE_CLASS_GUI_INFO

public:
    /** 
     * @~english Type Text type.
     * @~chinses ��������
     */
    enum class Type
    {
        SYSTEM,
        TTF
    };
    /**
     * @~english Default constructor.
     * @~chinese Ĭ�Ϲ��캯��
     * @js ctor
     * @lua new
     */
    Text();

    /**
     * @~english Default destructor.
     * @~chinese Ĭ����������
     * @js NA
     * @lua NA
     */
    virtual ~Text();

    /**
     * @~english Create a Text object.
     * @~chinese ����һ���ı�����
     * @return An autoreleased Text object.
     * @~chinese ���������ı�����
     */
    static Text* create();

    /**
     *  @~english Create a Text object with textContent, fontName and fontSize.
     *  The fontName could be a system font name or a TTF file path.
     *  Usage:
     *  @code
     *       //create a system font UIText.
     *       Text *text = Text::create("Hello", "Arial", 20);
     *       //create a TTF font UIText.
     *       Text *text = Text::create("Hello", "xxx\xxx.ttf", 20);
     *  @endcode
     * @~chinese ͨ��ָ���ı����ݣ��������ƣ������С������һ���ı������������Ʊ�����ϵͳ�������������ƣ���һ��ָ����ttf�ļ�·��
     * ������
     *  @code
     *       //create a system font UIText.
     *       Text *text = Text::create("Hello", "Arial", 20);
     *       //create a TTF font UIText.
     *       Text *text = Text::create("Hello", "xxx\xxx.ttf", 20);
     *  @endcode
     * @param textContent @~english Text content string.
     * @~chinese �ı����ݵ��ַ���
     * @param fontName @~english A given font name.
     * @~chinese ָ��������
     * @param fontSize @~english A given font size.
     * @~chinese �����С
     * @return @~english An autoreleased Text object.
     * @~chinese �ı�����
     */
    static Text* create(const std::string& textContent,
                        const std::string& fontName,
                        float fontSize);

    /**
     * @~english Changes the string value of label.
     * @~chinese �����ı���������ʾ���ı�
     * @param text  @~english The string value.
     * @~chinese ָ���ַ���
     */
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& text)
    {
        this->setString(text);
    }
    /**
    * @~english Changes the string value of label.
    * @~chinese �����ı���������ʾ���ı�
    * @param text  @~english String value.
    * @~chinese ָ���ַ���
    */
    void setString(const std::string& text);

    /**
     * @~english Gets the string value of label.
     * @~chinese ��ȡ�ı������е��ı��ַ���
     * @return @~english String value.
     * @~chinese �ַ���
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue()
    {
        return this->getString();
    }

    /**
    * @~english Gets the string value of label.
    * @~chinese ��ȡ�ı������е��ı��ַ���
    * @return @~english String value.
    * @~chinese �ַ���
    */
    const std::string& getString()const;

    /**
     * @~english Gets the string length of the label.
     * @~chinese ��ȡ�ı���ǩ���ַ�������
     * @return  @~english String length.
     * @~chinese �ַ�������
     * @note @~english This length will be larger than the raw string length,
     * if you want to get the raw string length,
     * you should call this->getString().size() instead.
     * @~chinese �ó��Ƚ����ԭʼ�ַ�������Ҫ�����������ԭʼ�ַ������ȣ������this->getString().size()
     */
    ssize_t getStringLength()const;

    /**
     * @~english Sets the font size of label.
     * @~chinese �����ı�����������С
     * @param size @~english The font size.
     * @~chinese �����С
     */
    void setFontSize(float size);

    /**
     * @~english Gets the font size of label.
     * @~chinese ��ȡ�ı�����������С
     * @return @~english The font size.
     * @~chinese �����С
     */
    float getFontSize()const;

    /**
     * @~english Sets the font name of label.
     *  If you are trying to use a system font, you could just pass a font name
     * If you are trying to use a TTF, you should pass a file path to the TTF file
     * Usage:
     * @code
     *          //create a system font UIText
     *         Text *text = Text::create("Hello", "Arial", 20);
     *         // it will change the font to system font no matter the previous font type is TTF or system font
     *         text->setFontName("Marfelt");
     *         //it will change the font to TTF font no matter the previous font type is TTF or system font
     *         text->setFontName("xxxx/xxx.ttf");
     * @endcode
     * @~chinese �����ı���������壬�������Ҫʹ��ϵͳ���壬ֻ�轫��������Ϊ�������ݼ��ɣ������ʹ��TTF�ļ�������Ҫ����TTF�ļ���·��
     * ������
     * Usage:
     * @code
     *          //create a system font UIText
     *         Text *text = Text::create("Hello", "Arial", 20);
     *         // it will change the font to system font no matter the previous font type is TTF or system font
     *         text->setFontName("Marfelt");
     *         //it will change the font to TTF font no matter the previous font type is TTF or system font
     *         text->setFontName("xxxx/xxx.ttf");
     * @endcode
     * @param name @~english The font name.
     * @~chinese ��������
     */
    void setFontName(const std::string& name);

    /** 
     * @~english Gets the font name.
     * @~chinese ��ȡ��������
     * @return @~english Font name.
     * @~chinese ��������
     */
    const std::string& getFontName()const;

    /**
     * @~english Gets the font type.
     * @~chinese ��ȡ��������
     * @return @~english The font type.
     * @~chinese ��������
     */
    Type getType() const;

    /**
     * @~english Sets the touch scale enabled of label.
     * @~chinese �����ı������Ƿ�֧�ִ����Ŵ�
     * @param enabled @~english Touch scale enabled of label.
     * @~chinese �Ƿ�֧�ִ����Ŵ�
     */
    void setTouchScaleChangeEnabled(bool enabled);

    /**
     * @~english Gets the touch scale enabled of label.
     * @~chinese ��ȡ��ǰ�ı������Ƿ�֧�ִ����Ŵ�
     *
     * @return  @~english Touch scale enabled of label.
     * @~chinese �Ƿ�֧�ִ����Ŵ�
     */
    bool isTouchScaleChangeEnabled()const;

    //override "getVirtualRendererSize" method of widget.
    virtual Size getVirtualRendererSize() const override;

    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;

    /** 
     * @~english Gets the render size in auto mode.
     * @~chinses ��ȡ���Զ�ģʽ�µ���Ⱦ�ߴ�
     * @return @~english The size of render size in auto mode.
     * @~chinses �Զ�ģʽ����Ⱦ�ߴ�
     */
    virtual Size getAutoRenderSize();

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    /**
     * @~english Sets the rendering size of the text, you should call this method
     * along with calling `ignoreContentAdaptWithSize(false)`, otherwise the text area
     * size is calculated by the real size of the text content.
     * @~chinese �����ı���ʵ����Ⱦ�ߴ磨�ı��򣩣������ͬʱ����`ignoreContentAdaptWithSize(false)`��������Ⱦ�ߴ磨�ı��򣩽���
     * �����ı����ݵ�ʵ�ʴ�С����
     * @param size @~english The text rendering area size.
     * @~chinese �ı���Ⱦ�ߴ磨�ı���
     */
    void setTextAreaSize(const Size &size);

    /** 
     * @~chinese Return the text rendering area size.
     * @~chinese �����ı������ʵ����Ⱦ�ߴ磨�ı���
     * @return @~chinese The text rendering area size.
     * @~chinese �ı����С
     */
    const Size& getTextAreaSize()const;

    /** 
     * @~chinese Sets text horizontal alignment.
     * @~chinese �����ı�ˮƽ�����������
     * @param alignment @~chinese Horizontal text alignment type
     * @~chinese ˮƽ�����������
     */
    void setTextHorizontalAlignment(TextHAlignment alignment);

    /** 
     * @~chinese Gets text horizontal alignment.
     * @~chinese ��ȡ�ı�����ˮƽ�����������
     * @return Horizontal @~chinese text alignment type
     * @~chinese ˮƽ�����������
     */
    TextHAlignment getTextHorizontalAlignment()const;

    /** 
     * @~chinese Sets text vertical alignment.
     * @~chinese �����ı�������ֱ�����������
     * @param alignment @~chinese The vertical text alignment type
     * @~chinese ��ֱ�����������
     */
    void setTextVerticalAlignment(TextVAlignment alignment);

    /** 
     * @~chinese Gets text vertical alignment.
     * @~chinese ��ȡ�ı���ֱ�����������
     * @return @~chinese The vertical text alignment type
     * @~chinese �ı���ֱ�����������
     */
    TextVAlignment getTextVerticalAlignment()const;

    /** 
     * @~chinese Sets text color.
     * @~chinese �����ı���ɫ
     * @param color @~chinese Text color.
     * @~chinese �ı���ɫ
     */
    void setTextColor(const Color4B color);

    /** 
     * @~chinese Gets text color.
     * @~chinese ��ȡ�ı���ɫ
     * @return @~chinese Text color.
     * @~chinese �ı���ɫ
     */
    const Color4B& getTextColor() const;

    /**
     * @~chinese Enable shadow for the label.
     * @~chinese �����ı���Ӱ
     * @todo support blur for shadow effect
     *
     * @param shadowColor @~chinese The color of shadow effect.
     * @~chinese ��Ӱ��ɫ
     * @param offset @~chinese The offset of shadow effect.
     * @~chinese ��Ӱƫ����
     * @param blurRadius @~chinese The blur radius of shadow effect.
     * @~chinese ��Ӱģ���뾶
     */
    void enableShadow(const Color4B& shadowColor = Color4B::BLACK,
                      const Size &offset = Size(2,-2),
                      int blurRadius = 0);

    /**
     * @~chinese Enable outline for the label.
     * It only works on IOS and Android when you use System fonts.
     * @~chinese �����ı�������ֻ�ڰ�׿����IOSƽ̨��ʹ��ϵͳ����ʱ��Ч
     * @param outlineColor @~chinese The color of outline.
     * @~chinese ������ɫ
     * @param outlineSize @~chinese The size of outline.
     * @~chinese �����ߴ�
     */
    void enableOutline(const Color4B& outlineColor,int outlineSize = 1);

    /**
     * @~chinese Enable the glow effect of the text,Only support for TTF.
     * @~chinese �����ı��ĻԹ�Ч������֧��TTF����
     * 
     * @param glowColor @~chinese The color of glow.
     * @~chinese �Թ���ɫ
     */
    void enableGlow(const Color4B& glowColor);

    /** 
     * @~chinese Disable all text effects, including shadow, outline and glow.
     * @~chinese ���������ı���Ч��������Ӱ�������Լ��Թ�
     */
    void disableEffect();

    /**
     * @~chinese Disable specific text effect.
     * @~chinese ����ָ�����ı���Ч
     * @param effect @~chinese The specified text effect.
     * @~chinese ָ�����ı���Ч
     * @see `LabelEffect`
     */
    void disableEffect(LabelEffect effect);

    /**
    * Return whether the shadow effect is enabled.
    */
    bool isShadowEnabled() const;
    /**
    * Return shadow effect offset value.
    */
    Size getShadowOffset() const;
    /**
    * Return the shadow effect blur radius.
    */
    float getShadowBlurRadius() const;
    /**
    * Return the shadow effect color value.
    */
    Color4B getShadowColor() const;
    /**
    * Return the outline effect size value.
    */
    int getOutlineSize() const;
    /**
    * Return current effect type.
    */
    LabelEffect getLabelEffectType() const;
    /**
    * Return current effect color vlaue.
    */
    Color4B getEffectColor() const;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& textContent,
                      const std::string& fontName,
                      float fontSize);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;

    void labelScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    bool _touchScaleChangeEnabled;
    float _normalScaleValueX;
    float _normalScaleValueY;
    std::string _fontName;
    float _fontSize;
    float _onSelectedScaleOffset;
    Label* _labelRenderer;
    bool _labelRendererAdaptDirty;
    Type _type;
};

}

NS_CC_END

// end of ui group
/// @}

#endif /* defined(__CocoGUI__Label__) */
