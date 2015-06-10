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

#ifndef __UITEXTFIELD_H__
#define __UITEXTFIELD_H__

#include "ui/UIWidget.h"
#include "2d/CCTextFieldTTF.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {

/** @class UICCTextField
*@brief @~english A helper class which inherit from @see `TextFieldTTF` and implements the @see `TextFieldDelegate` protocol.
 It is mainly be used internally by @see `UITextField` class.

 @~chinese ��TextFieldTTF��������������ʵ����TextFieldDelegate�����Э��İ����ࡣ
 ����Ҫ����UITextField����ʹ�á�
 @js NA
 @lua NA
*/
class CC_GUI_DLL UICCTextField: public TextFieldTTF, public TextFieldDelegate
{
public:
    /**
    * @~english Default constructor.
    * @~chinese Ĭ�Ϲ�����
    */
    UICCTextField();

    /**
    * @~english Default destructor.
    * @~chinese Ĭ��������
    */
    ~UICCTextField();
    
    virtual void onEnter() override;
    
    /**
    * @~english Create a UICCTextField intance with a placeholder, a fontName and a fontSize.
    * @~chinese ͨ��һ��ռλ�����������ƺ������С������һ��UICCTextField��
    * @param placeholder @~english Placeholder in string. @~chinese ռλ����
    * @param fontName @~english Font name in string. @~chinese �������ơ�
    * @param fontSize @~english Font size in float. @~chinese �����С��
    * @return @~english A UICCTextField instance. @~chinese һ��UICCTextFieldʵ����
    */
    static UICCTextField* create(const std::string& placeholder,
                                 const std::string& fontName,
                                 float fontSize);
    
    //override functions
    virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender) override;
    virtual bool onTextFieldInsertText(TextFieldTTF * pSender,
                                       const char * text,
                                       size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * pSender,
                                           const char * delText,
                                           size_t nLen) override;
    void insertText(const char* text, size_t len) override;
    void deleteBackward() override;
    
    /**
    * @~english Open up the IME.
    * @~chinese �����뷨�༭��
    */
    void openIME();

    /**
    * @~english Close the IME.
    * @~chinese �ر����뷨�༭��
    */
    void closeIME();
    
    /**
    * @~english Toggle enable max length limitation.
    * @~chinese ������󳤶�����
    * @param enable @~english True to enable max length, false otherwise. @~chinese True��ʾ������󳤶����ƣ���֮�رա�
    */
    void setMaxLengthEnabled(bool enable);

    /**
    * @~english Query max length enable state.
    * @~chinese ������󳤶����ƵĿ���״̬��
    * @return @~english Whether max length is enabled or not. @~chinese ��󳤶������Ƿ����á�
    */
    bool isMaxLengthEnabled()const;

    /**
    * @~english Set maxmize length.
    * @~chinese ������󳤶ȡ�
    * @param length  @~english The maxmize length in integer. @~chinese ���͵�λ����󳤶�ֵ��
    */
    void setMaxLength(int length);

    /**
    * @~english Get maximize length.
    * @~chinese �����󳤶ȡ�
    * @return @~english Maximize length. @~chinese ��󳤶ȡ�
    */
    int getMaxLength()const;

    /**
    * @~english Return the total inputed charaters.
    * @~chinese ��ȡ�ܹ�������ַ�����
    *@return @~english Total inputed character count. @~chinese �ܹ�������ַ�����
    */
    int getCharCount()const;
    
    
    /**
    * @~english Toggle password input mode.
    * @~chinese ������������ģʽ��
    * @param enable @~english True if enable password input, false otherwise. @~chinese True��ʾ������������ģʽ����֮�رա�
    */
    void setPasswordEnabled(bool enable);
    
    /**
    * @~english Query whether password input mode is enabled or not.
    * @~chinese ������������ģʽ�Ƿ�����
    * @return @~english True if password input is enabled, false otherwise. @~chinese True��ʾ������������ģʽ����֮�رա�
    */
    bool isPasswordEnabled()const;
    
    /**
    * @~english Change password style text.
    * @~chinese �ı�����ģʽ�µ��ı���ʽ��
    * @param styleText @~english The styleText for password mask, the default value is "*". @~chinese ����������ı���ʽ��Ĭ��Ϊ��*����
    */
    void setPasswordStyleText(const std::string& styleText);
    
    /**
    * @~english Set the password text content.
    * @~chinese �������롣
    * @param text @~english The content of password. @~chinese ���롣
    */
    void setPasswordText(const std::string& text);

    
    /**
    * @~english Toggle attach with IME.
    * @~chinese �Ƿ�������뷨�༭����
    * @param attach @~english True if attach with IME, false otherwise. @~chinese True�����������뷨�༭������֮��������
    */
    void setAttachWithIME(bool attach);
    
    /**
    * @~english Query whether the IME is attached or not.
    * @~chinese �����Ƿ�������뷨�༭����
    * @return @~english True if IME is attached, false otherwise. @~chinese True�����������뷨�༭������֮��������
    */
    bool getAttachWithIME()const;
    
    /**
    * @~english  Toggle detach with IME.
    * @~chinese �Ƿ�ȡ���������뷨�༭����
    * @param detach @~english True if detach with IME, false otherwise. @~chinese True�������������뷨�༭������֮������
    */
    void setDetachWithIME(bool detach);
    
    /**
    * @~english Query whether IME is detached or not.
    * @~chinese �����Ƿ񲻹������뷨�༭����
    * @return True @~english if IME is detached, false otherwise. @~chinese True�������������뷨�༭������֮������
    */
    bool getDetachWithIME()const;
    
    /**
    * @~english Toggle enable text insert.
    * @~chinese �����Ƿ������ı����롣
    * @param insert @~english True if enable insert text, false otherwise. @~chinese True��ʾ�����ı����룬��֮������
    */
    void setInsertText(bool insert);
    
    /**
    * @~english Query whether insert text is enabled or not.
    * @~chinese �����Ƿ������ı����롣
    * @return @~english True if insert text is enabled, false otherwise. @~chinese True��ʾ�����ı����룬��֮������
    */
    bool getInsertText()const;
     
    /**
    * @~english Toggle enable delete backward.
    * @~chinese ���������ɾ��
    * @param deleteBackward @~english True if enable delete backward, false otherwise. @~chinese True��ʾ������ɾ����֮�رա�
    */
    void setDeleteBackward(bool deleteBackward);
    
    /**
    * @~english Query whether delete backward is enabled   or not.
    * @~chinese �����Ƿ�����ɾ��
    * @return @~english True if delete backward is enabled, false otherwise. @~chinese True��ʾ������ɾ����֮�رա�
    */
    bool getDeleteBackward()const;
protected:
    bool _maxLengthEnabled;
    int _maxLength;
    bool _passwordEnabled;
    std::string _passwordStyleText;
    bool _attachWithIME;
    bool _detachWithIME;
    bool _insertText;
    bool _deleteBackward;
};

/**
* TextField event type.
 * @deprecated Use @see `TextField::EventType` instead.
 */
typedef enum
{
    TEXTFIELD_EVENT_ATTACH_WITH_IME,
    TEXTFIELD_EVENT_DETACH_WITH_IME,
    TEXTFIELD_EVENT_INSERT_TEXT,
    TEXTFIELD_EVENT_DELETE_BACKWARD,
}TextFiledEventType;

/**
 * A callback which would be called when a TextField event happens.
 * @deprecated Use @see `ccTextFieldCallback` instead.
 */
typedef void (Ref::*SEL_TextFieldEvent)(Ref*, TextFiledEventType);
#define textfieldeventselector(_SELECTOR) (SEL_TextFieldEvent)(&_SELECTOR)

/** @class TextField
 @brief @~english A widget which allows users to input text.
 The rendering of the input text are based on @see `TextFieldTTF'.
 If you want to use system control behavior, please use @see `EditBox` instead.

 @~chinese һ�������û������widget��
 �����ı�����Ⱦ����TextFieldTTF��
 ���������ϵͳ������Ϊ����ʹ��EditBox�������
 @js NA
 @lua NA
*/
class CC_GUI_DLL TextField : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
    * TextField event type.
    */
    enum class EventType
    {
        ATTACH_WITH_IME,
        DETACH_WITH_IME,
        INSERT_TEXT,
        DELETE_BACKWARD,
    };
    /**
    * @~english A callback which would be called when a TextField event happens.
    * @~chinese ��TextField��һ���¼�����ʱ���еĻص���
    */
    typedef std::function<void(Ref*, EventType)> ccTextFieldCallback;
    
    
    /**
    * @~english Default constructor.
    * @~chinese Ĭ�Ϲ�������
    *
    */
    TextField();
    
    /**
    * @~english Default destructor.
    * @~chinese Ĭ����������
    */
    virtual ~TextField();
    
    /**
    * @~english Create an empty TextField.
    * @~chinese ����һ���յ�TextField��
    * @return @~english A TextField instance. @~chinese  TextFieldʵ����
    */
    static TextField* create();
    
    /**
    * @~english Create a TextField with a placeholder, a font name and a font size.
    * @~chinese ͨ��һ��ռλ����һ���������ƺ������С������һ��TextField��
    * @param placeholder @~english The placeholder string. @~chinese ռλ����
    * @param fontName @~english The font name. @~chinese �������ơ�
    * @param fontSize @~english The font size. @~chinese �����С��
    * @return @~english A TextField instance. @~chinese TextFieldʵ����
    */
    static TextField* create(const std::string& placeholder,
                             const std::string& fontName,
                             int fontSize);
    
    /**
    * @~english Set the touch size
    * The touch size is used for @see `hitTest`.
    * @~chinese ���ô��������С��
    * ������С����hitTest��
    * @param size @~english A delimitation zone. @~chinese һ���޶�����
    */
    void setTouchSize(const Size &size);
    
    /**
    * @~english Get current touch size of TextField.
    * @~chinese ��ȡ��ǰ�Ĵ��������С��
    * @return @~english The TextField's touch size. @~chinese ���������С��
    */
    Size getTouchSize()const;
    
    /**
    * @~english Toggle enable touch area.
    * @~chinese ���û�رմ�������
    * @param enable @~english True if enable touch area, false otherwise. @~chinese True���������������򣬷�֮�رա�
    */
    void setTouchAreaEnabled(bool enable);
    
    virtual bool hitTest(const Vec2 &pt) override;
    
    
    /**
    * @~english Set placeholder of TextField.
    * @~chinese ����ռλ����
    * @param value @~english The string value of placeholder. @~chinese ռλ����
    */
    void setPlaceHolder(const std::string& value);
    
    /**
    * @~english Get the placeholder of TextField.
    * @~chinese ��ȡռλ����
    * @return @~english A placeholder string. @~chinese ռλ����
    */
    const std::string& getPlaceHolder()const;
    
    /**
    * @~english Query the placeholder string color.
    * @~chinese ����ռλ��ʹ����ɫ��
    * @return @~english The color of placeholder. @~chinese ռλ����ɫ��
    */
    const Color4B& getPlaceHolderColor()const;
    
    /**
    * @~english Change the placeholder color.
    * @~chinese �ı�ռλ����ɫ��
    * @param color @~english A color value in `Color3B`. @~chinese ռλ����ɫ��
    */
    void setPlaceHolderColor(const Color3B& color);
    
    /**
    * @~english Change the placeholder color.
    * @~chinese �ı�ռλ����ɫ��
    * @param color @~english A color value in `Color4B`. @~chinese ռλ����ɫ��
    */
    void setPlaceHolderColor(const Color4B& color);
    
    /**
    * @~english Query the text string color.
    * @~chinese �����ı���ɫ��
    * @return @~english The color of the text. @~chinese �ı���ɫ��
    */
    const Color4B& getTextColor()const;
    
    /**
    * @~english Change the text color.
    * @~chinese �ı��ı���ɫ��
    * @param textColor @~english The color value in `Color4B`. @~chinese �ı���ɫ��
    */
    void setTextColor(const Color4B& textColor);
     
    /**
    * @~english Change font size of TextField.
    * @~chinese �ı������С��
    * @param size @~english The integer font size. @~chinese �����С��
    */
    void setFontSize(int size);
    
    /**
    * @~english Query the font size.
    * @~chinese �����ȡ�����С��
    * @return @~english The integer font size. @~chinese �����С��
    */
    int getFontSize()const;
    
    /**
    * @~english Change the font name of TextField.
    * @~chinese �ı��������ơ�
    * @param name @~english The font name string. @~chinese �������ơ�
    */
    void setFontName(const std::string& name);
    
    /**
    * @~english Query the TextField's font name.
    * @~chinese �����ȡ�������ơ�
    * @return @~english The font name string. @~chinese �������ơ�
    */
    const std::string& getFontName()const;
    
    
    /**
    * @~english Detach the IME.
    * @~chinese ȡ���������뷨�༭����
    */
    virtual void didNotSelectSelf();
    
    /**
    * @~english Change content of TextField.
    * @~chinese �ı��ı����ݡ�
    * @deprecated Use @see `setString(const std::string&)` instead.
    * @param text @~english A string content. @~chinese �ı����ݡ�
    */
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& text){this->setString(text);}

    /**
    * @~english Query the content of TextField.
    * @~chinese �����ȡ�ı����ݡ�
    * @deprecated Use @see `getString` instead.
    * @return @~english The string value of TextField. @~chinese �ı����ݡ�
    */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue()const{return this->getString();}
    
    /**
    * @~english Change content of TextField.
    * @~chinese �ı��ı����ݡ�
    * @param text @~english A string content. @~chinese �ı����ݡ�
    */
    void setString(const std::string& text);
    
    /**
    * @~english Query the content of TextField.
    * @~chinese �����ȡ�ı����ݡ�
    * @return @~english The string value of TextField. @~chinese �ı����ݡ�
    */
    const std::string& getString()const;
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    
    
    /**
    * @~english Toggle maximize length enable
    * @~chinese ������󳤶����ơ�
    * @param enable @~english True if enable maximize length, false otherwise. @~chinese True����������󳤶����ƣ���֮�رա�
    */
    void setMaxLengthEnabled(bool enable);
    
    /**
    * @~english Query whether max length is enabled or not.
    * @~chinese �����Ƿ�������󳤶����ơ�
    * @return @~english True if maximize length is enabled, false otherwise. @~chinese True����������󳤶����ƣ���֮�رա�
    */
    bool isMaxLengthEnabled()const;
    
    /**
    * @~english Change maximize input length limitation.
    * @~chinese �ı�������볤�����ơ�
    * @param length @~english A character count in integer. @~chinese ��󳤶ȡ�
    */
    void setMaxLength(int length);
    
    /**
    * @~english Query maximize input length of TextField.
    * @~chinese  ����������볤�ȡ�
    * @return @~english The integer value of maximize input length. @~chinese ��󳤶ȡ�
    */
    int getMaxLength()const;
    
    /**
    * @~english Query the input string length.
    * @~chinese ���������ַ������ȡ�
    * @return @~english A integer length value. @~chinese �ַ������ȡ�
    */
    int getStringLength() const;
    
    /**
    * @~english Toggle enable password input mode.
    * @~chinese ������������ģʽ��
    * @param enable @~english True if enable password input mode, false otherwise. @~chinese True��ʾ������������ģʽ����֮�رա�
    */
    void setPasswordEnabled(bool enable);
    
    /**
    * @~english Query whether password is enabled or not.
    * @~chinese ������������ģʽ�Ƿ�����
    * @return @~english True if password is enabled, false otherwise. @~chinese True��ʾ������������ģʽ����֮�رա�
    */
    bool isPasswordEnabled()const;

    /**
    * @~english Change password style text.
    * @~chinese �ı�����ģʽ�µ��ı���ʽ��
    * @param styleText @~english The styleText for password mask, the default value is "*". @~chinese ����������ı���ʽ��Ĭ��Ϊ��*����
    */
    void setPasswordStyleText(const char* styleText);
    
    /**
    * @~english Query the password style text.
    * @~chinese ��������ģʽ���ı���ʽ��
    * @return @~english A password style text. @~chinese ����ģʽ���ı���ʽ��
    */
    const char* getPasswordStyleText()const;
    
    virtual void update(float dt) override;
    
    /**
    * @~english Query whether the IME is attached or not.
    * @~chinese �����Ƿ����뷨�༭���ѱ�������
    * @return @~english True if IME is attached, false otherwise. @~chinese True��ʾ�ѱ���������֮δ������
    */
    bool getAttachWithIME()const;
    
    /**
    * @~english Toggle attach with IME.
    * @~chinese ���ù������뷨�༭����
    * @param attach @~english True if attach with IME, false otherwise. @~chinese True��ʾ�ѱ���������֮δ������
    */
    void setAttachWithIME(bool attach);
    
    /**
    * @~english Query whether IME is detached or not.
    * @~chinese �����Ƿ����뷨�༭���ѱ�ȡ��������
    * @return @~english True if IME is detached, false otherwise. @~chinese True��ʾ�ѱ�ȡ����������֮�ѹ�����
    */
    bool getDetachWithIME()const;
    
    /**
    * @~english Toggle detach with IME.
    * @~chinese ����ȡ���������뷨�༭����
    * @param detach @~english True if detach with IME, false otherwise. @~chinese True��ʾ�ѱ�ȡ����������֮�ѹ�����
    */
    void setDetachWithIME(bool detach);
    
    
    /**
    * @~english Whether it is ready to get the inserted text or not.
    * @~chinese �Ƿ��������ı�ģʽ��
    * @return @~english True if the insert text is ready, false otherwise. @~chinese True��ʾ���������ı�ģʽ����֮δ������
    */
    bool getInsertText()const;
    
    /**
    * @~english Toggle enable insert text mode
    * @~chinese ���ز����ı�ģʽ��
    * @param insertText @~english True if enable insert text, false otherwise. @~chinese True��ʾ���������ı�ģʽ����֮δ������
    */
    void setInsertText(bool insertText);
     
    /**
    * @~english Whether it is ready to delete backward in TextField.
    * @~chinese �Ƿ������ɾ��
    * @return @~english True is the delete backward is enabled, false otherwise. @~chinese True��ʾ�����ɾ����֮������
    */
    bool getDeleteBackward()const;
    
    /**
    * @~english Toggle enable delete backward mode.
    * @~chinese ���ػ�ɾģʽ��
    * @param deleteBackward @~english True is delete backward is enabled, false otherwise. @~chinese True��ʾ�����ɾ����֮������
    */
    void setDeleteBackward(bool deleteBackward);
    
    /**
    * @~english Add a event listener to TextField, when some predefined event happens, the callback will be called.
    * @~chinese ���һ������������һЩԤ�����¼�����ʱ���лص�������
    * @deprecated Use @see `addEventListener` instead.
    * @param target @~english A pointer of `Ref*` type. @~chinese Ref���͵�ָ�롣
    * @param selecor @~english A member function pointer with type of `SEL_TextFieldEvent`. @~chinese ���Լ����Ļص�������
    */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerTextField(Ref* target, SEL_TextFieldEvent selecor);
    /**
    * @~english Add a event listener to TextField, when some predefined event happens, the callback will be called.
    * @~chinese ���һ������������һЩԤ�����¼�����ʱ���лص�������
    * @param callback @~english A callback function with type of `ccTextFieldCallback`. @~chinese ���Լ����Ļص�������
    */
    void addEventListener(const ccTextFieldCallback& callback);
    
    /**
    * @~english Returns the "class name" of widget.
    * @~chinese ����widget�������ơ�
    * @return @~english The "class name" of widget. @~chinese widget�������ơ�
    */
    virtual std::string getDescription() const override;
    
    /**
    * @~english Get the the renderer size in auto mode.
    * @~chinese ��ȡ��Ⱦʱ�Ĵ�С��
    *
    * @return @~english A delimitation zone. @~chinese һ���޶�����
    */
    virtual Size getAutoRenderSize();
    //overide functions.
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual void onEnter() override;
    
    /**
    * @~english Attach the IME for inputing.
    * @~chinese �������뷨�༭���������롣
    */
    void attachWithIME();
    
    /**
    * @~english Change the text area size.
    * @~chinese �ı��ı������С��
    * @param size @~english A delimitation zone. @~chinese һ���޶�����
    */
    void setTextAreaSize(const Size &size);
    
    /**
    * @~english Change horizontal text alignment.
    * @~chinese �ı��ı�ˮƽ�������͡�
    * @param alignment @~english A alignment arguments in @see `TextHAlignment`. @~chinese ˮƽ�������͡�
    */
    void setTextHorizontalAlignment(TextHAlignment alignment);

    /**
    * @~english Inquire the horizontal alignment
    * @~chinese ��ȡˮƽ�������͡�
    * @return @~english The horizontal alignment @~chinese ˮƽ�������͡�
    */
    TextHAlignment getTextHorizontalAlignment() const;
    
    /**
    * @~english Change the vertical text alignment.
    * @~chinese �ı��ı���ֱ�������͡�
    * @param alignment @~english A alignment arguments in @see `TextVAlignment`. @~chinese ��ֱ�������͡�
    */
    void setTextVerticalAlignment(TextVAlignment alignment);

    /**
    * @~english Inquire the horizontal alignment
    * @~chinese ��ȡ�ı���ֱ�������͡�
    * @return @~english The horizontal alignment @~chinese ��ֱ�������͡�
    */
    TextVAlignment getTextVerticalAlignment() const;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void initRenderer() override;
    void attachWithIMEEvent();
    void detachWithIMEEvent();
    void insertTextEvent();
    void deleteBackwardEvent();
    virtual void onSizeChanged() override;
  
    void textfieldRendererScaleChangedWithSize();
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    UICCTextField* _textFieldRenderer;

    float _touchWidth;
    float _touchHeight;
    bool _useTouchArea;
    
    Ref* _textFieldEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_TextFieldEvent _textFieldEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccTextFieldCallback _eventCallback;
    
    std::string _passwordStyleText;
    bool _textFieldRendererAdaptDirty;
private:
    enum class FontType
    {
        SYSTEM,
        TTF
    };

    std::string _fontName;
    int _fontSize;
    FontType _fontType;
};

}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__TextField__) */
