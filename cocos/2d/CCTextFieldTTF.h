/****************************************************************************
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

#ifndef __CC_TEXT_FIELD_H__
#define __CC_TEXT_FIELD_H__

#include "2d/CCLabel.h"
#include "base/CCIMEDelegate.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class TextFieldTTF;


/**@~english
 * A input protocol for TextField.
 * @~chinese 
 * �ı�������Э�顣
 */
class CC_DLL TextFieldDelegate
{
public:
    /**@~english
     * Destructor for TextFieldDelegate.
     * @~chinese 
     * ��������
     * @js NA
     */
    virtual ~TextFieldDelegate() {}

    /**
     * @brief @~english The callback method of IME attached on the TextField.
     * @~chinese �ı��༭��������뷨ʱ�Ļص�������
     *
     * @param sender @~english The TextField object.
     * @~chinese �ı��༭��ʵ����
     * @return @~english If the sender doesn't want to attach to the IME, return true.
     * @~chinese �����ϣ���༭��������뷨������true��
     */
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
     * @brief @~english The callback method of IME detached on the TextField.
     * @~chinese �ı��༭��ȡ���������뷨ʱ�Ļص�������
     *
     * @param sender @~english The TextField object.
     * @~chinese �ı��༭��ʵ����
     * @return @~english If the sender doesn't want to attach to the IME, return true.
     * @~chinese �����ϣ���༭��ȡ���������뷨������true��
     */
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
     * @brief @~english The callback method of text inserted on the TextField.
     * @~chinese �ı��༭������ı�ʱ�Ļص�������
     *
     * @param sender @~english The TextField object.
     * @~chinese �ı��༭��ʵ����
     * @param text @~english The text will be inserted.
     * @~chinese ��Ҫ������ַ�����
     * @param nLen @~english The length of the inserted text.
     * @~chinese ��Ҫ������ַ������ȡ�
     * @return @~english If the sender doesn't want to insert text, return true.
     * @~chinese �����ϣ���༭������ı�������true��
     */
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(text);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
     * @brief @~english The callback method of text will be delete on the TextField.
     * @~chinese �ı��༭��ɾ���ı�ʱ�Ļص�������
     *
     * @param sender @~english The TextField object.
     * @~chinese �ı��༭��ʵ����
     * @param delText @~english The text will be deleted.
     * @~chinese ��Ҫɾ�����ַ�����
     * @param nLen @~english The length of the deleted text.
     * @~chinese ��Ҫɾ�����ַ������ȡ�
     * @return @~english If the sender doesn't want to delete text, return true.
     * @~chinese �����ϣ���༭��ɾ���ı�������true��
     */
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(delText);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
     * @brief @~english The callback method of the TextField will be drawn.
     * @~chinese �ı��༭��Ҫ������ʱ�Ļص�������
     *
     * @param sender @~english The TextField object.
     * @~chinese �ı��༭��ʵ����
     * @param renderer @~english The renderer will render the TextField.
     * @~chinese �����ı��༭�����Ⱦ����
     * @param transform @~english The transform matrix used for renderer.
     * @~chinese ��Ⱦ����ʹ�õ�ת�þ���
     * @param flags @~english The flags for the renderer.
     * @~chinese ��Ⱦ����ʹ�õı��λ��
     * @return @~english If you don't want to render the TextField, return true.
     * @~chinese �����ϣ�������ı��༭�򣬷���true��
     */
    virtual bool onVisit(TextFieldTTF * sender,Renderer *renderer, const Mat4 &transform, uint32_t flags)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
};

/**
 *@brief @~english A simple text input field with TTF font.
 * @~chinese һ��ʹ�� TTF ����ʵ�ֵļ򵥵��ı������
 */
class CC_DLL TextFieldTTF : public Label, public IMEDelegate
{
public:
    /**@~english
     * Default constructor.
     * @~chinese 
     * Ĭ�Ϲ��캯����
     * @js ctor
     */
    TextFieldTTF();
    
    /**@~english
     * Default destructor.
     * @~chinese 
     * Ĭ�ϵ�����������
     * @js NA
     * @lua NA
     */
    virtual ~TextFieldTTF();

    /** @~english Creates a TextFieldTTF from placeholder, a fontname, alignment, dimension and font size.
     * @~chinese ʹ��ָ����ռλ������С�����뷽ʽ���������ƺ������С����һ�� TextFieldTTF��
     * @param placeholder @~english The place holder string.
     * @~chinese ռλ���ַ�����
     * @param dimensions @~english The size of the TextField.
     * @~chinese �ı��༭��Ĵ�С��
     * @param alignment @~english The alignment of the TextField.
     * @~chinese �ı��༭��Ķ��뷽ʽ��
     * @param fontName @~english The font name of the TextField.
     * @~chinese ʹ�õ��������ơ�
     * @param fontSize @~english The font size of the TextField.
     * @~chinese ʹ�õ������С��
     * @return @~english A TextFieldTTF object.
     * @~chinese һ�� TextFieldTTF ʵ����
     * @js NA
     */
    static TextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize);
    
    /** @~english Creates a TextFieldTTF from placeholder, a fontname and font size.
     * @~chinese ʹ��ָ����ռλ�����������ƺ������С����һ�� TextFieldTTF��
     * @param placeholder @~english The place holder string.
     * @~chinese ռλ���ַ�����
     * @param fontName @~english The font name of the TextField.
     * @~chinese ʹ�õ��������ơ�
     * @param fontSize @~english The font size of the TextField.
     * @~chinese ʹ�õ������С��
     * @return @~english A TextFieldTTF object.
     * @~chinese һ�� TextFieldTTF ʵ����
     * @js NA
     */
    static TextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize);
    
    /** @~english Initializes the TextFieldTTF with a font name, alignment, dimension and font size.
     * @~chinese ʹ��ָ����ռλ������С�����뷽ʽ���������ƺ������С��ʼ��һ�� TextFieldTTF��
     * @param placeholder @~english The place holder string.
     * @~chinese ռλ���ַ�����
     * @param dimensions @~english The size of the TextField.
     * @~chinese �ı��༭��Ĵ�С��
     * @param alignment @~english The alignment of the TextField.
     * @~chinese �ı��༭��Ķ��뷽ʽ��
     * @param fontName @~english The font name of the TextField.
     * @~chinese ʹ�õ��������ơ�
     * @param fontSize @~english The font size of the TextField.
     * @~chinese ʹ�õ������С��
     * @return @~english If the initialization success, return true; else, return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false
     */
    bool initWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize);
    
    /** @~english Creates a TextFieldTTF from placeholder, a fontname and font size.
     * @~chinese ʹ��ָ����ռλ�����������ƺ������С��ʼ��һ�� TextFieldTTF��
     * @param placeholder @~english The place holder string.
     * @~chinese ռλ���ַ�����
     * @param fontName @~english The font name of the TextField.
     * @~chinese ʹ�õ��������ơ�
     * @param fontSize @~english The font size of the TextField.
     * @~chinese ʹ�õ������С��
     * @return @~english If the initialization success, return true; else, return false.
     * @~chinese �����ʼ���ɹ������� true�����򷵻� false
     */
    bool initWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize);

    /**
     *@brief @~english Open keyboard and receive input text.
     * @~chinese �򿪼��̺ͽ��������ı���
     * @return @~english If the action success, return true; else return false.
     * @~chinese ����ɹ������� true�����򷵻� false��
     */
    virtual bool attachWithIME() override;

    /**
     *@brief    @~english End text input and close keyboard.
     * @~chinese �ı�����������رռ��̡�
     * @return @~english If the action success, return true; else return false.
     * @~chinese ����ɹ������� true�����򷵻� false��
     */
    virtual bool detachWithIME() override;

    //////////////////////////////////////////////////////////////////////////
    // properties
    //////////////////////////////////////////////////////////////////////////
    /**
     * @lua NA
     */
    inline TextFieldDelegate* getDelegate() const { return _delegate; };
    /**
     * @lua NA
     */
    inline void setDelegate(TextFieldDelegate* delegate) { _delegate = delegate; };

    /**@~english
     * Query the currently inputed character count.
     * @~chinese 
     * ��ȡ��ǰ������ַ�����
     *@return @~english The total input character count.
     * @~chinese �������ַ�����
     */
    inline int getCharCount() const { return _charCount; };
    
    /**@~english
     * Query the color of place holder.
     * @~chinese 
     * ��ȡռλ������ɫ��
     *@return @~english The place holder color.
     * @~chinese ռλ������ɫ��
     */
    virtual const Color4B& getColorSpaceHolder();

    /**
     *@brief @~english Change input placeholder color.
     * @~chinese ����ռλ������ɫ��
     *@param color @~english A color value in `Color3B`.
     * @~chinese Color3B ����ɫֵ��
     */
    virtual void setColorSpaceHolder(const Color3B& color);

    /**@~english
     * Change the placeholder color.
     * @~chinese 
     * ����ռλ������ɫ��
     *@param color @~english The placeholder color in Color4B.
     * @~chinese Color4B ����ɫֵ��
     */
    virtual void setColorSpaceHolder(const Color4B& color);

    /**@~english
     * Change the color of input text.
     * @~chinese 
     * ���������ı�����ɫ��
     *@param textColor @~english The text color in Color4B.
     * @~chinese Color4B ����ɫֵ��
     */
    virtual void setTextColor(const Color4B& textColor) override;

    /**@~english
     * Change input text of TextField.
     * @~chinese 
     * �����ı����е��ı���
     *@param text @~english The input text of TextField.
     * @~chinese �ı��ַ�����
     */
    virtual void setString(const std::string& text) override;

    /**@~english
     * Query the input text of TextField.
     * @~chinese 
     * ��ȡ�ı����е��ı���
     *@return @~english Get the input text of TextField.
     * @~chinese �ı����е��ı���
     */
    virtual const std::string& getString() const override;

    /**@~english
     * Change placeholder text.
     * place holder text displayed when there is no text in the text field.
     * @~chinese 
     * ����ռλ���ַ�����
     * �ı�����û����������ʱ����ʾռλ���ַ�����
     *@param text  @~english The place holder string.
     * @~chinese ռλ���ַ�����
     */
    virtual void setPlaceHolder(const std::string& text);

    /**@~english
     * Query the placeholder string.
     * @~chinese 
     * ��ȡռλ���ַ�����
     *@return @~english The placeholder string.
     * @~chinese ռλ���ַ�����
     */
    virtual const std::string& getPlaceHolder() const;

    /**@~english
     * Set enable secure text entry representation.
     * If you want to display password in TextField, this option is very helpful.
     * @~chinese 
     * ����/�ر� ��ȫ���ı����롣
     * �������Ҫ���ı�������ʾ���룬���Կ����˹��ܡ�
     *@param value @~english Whether or not to display text with secure text entry.
     * @~chinese �Ƿ���ʾ������ı���
     * @js NA
     */
    virtual void setSecureTextEntry(bool value);

    /**@~english
     * Query whether the currently display mode is secure text entry or not.
     * @~chinese 
     * ��ȡ��ǰ�Ƿ����˰�ȫ���ı����빦�ܡ�
     *@return @~english Whether current text is displayed as secure text entry.
     * @~chinese ��������˰�ȫ���ı����빦�ܣ����� true�����򷵻� false��
     * @js NA
     */
    virtual bool isSecureTextEntry();

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

protected:
    //////////////////////////////////////////////////////////////////////////
    // IMEDelegate interface
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME() override;
    virtual bool canDetachWithIME() override;
    virtual void insertText(const char * text, size_t len) override;
    virtual void deleteBackward() override;
    virtual const std::string& getContentText() override;

    TextFieldDelegate * _delegate;
    int _charCount;

    std::string _inputText;

    std::string _placeHolder;
    Color4B _colorSpaceHolder;
    Color4B _colorText;

    bool _secureTextEntry;

private:
    class LengthStack;
    LengthStack * _lens;
};

NS_CC_END
// end of ui group
/// @}

#endif    // __CC_TEXT_FIELD_H__
