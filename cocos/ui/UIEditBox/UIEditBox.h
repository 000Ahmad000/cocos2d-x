/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
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

#ifndef __UIEDITTEXT_H__
#define __UIEDITTEXT_H__

#include "base/CCIMEDelegate.h"
#include "ui/GUIDefine.h"
#include "ui/UIButton.h"
#include "ui/UIScale9Sprite.h"

NS_CC_BEGIN

/**
 * @addtogroup ui
 * @{
 */
namespace ui {
        
    class EditBox;
    class EditBoxImpl;
        
    /**
     *@brief @~english Editbox delgate class.
     * It's useful when you want to do some customization duing Editbox input event
     *
     * @~chinese �༭������ࡣ
     * �����붨�Ʊ༭�������¼�ʱ�������ǳ����á�
     * 
     * @js NA
     * @lua NA
     */
    class CC_GUI_DLL EditBoxDelegate
    {
    public:
        virtual ~EditBoxDelegate() {};
            
        /**@~english
         * This method is called when an edit box gains focus after keyboard is shown.
         * @~chinese 
         * ��������ڱ༭�����ʼ��ý���ʱ������
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese һ���༭�����ָ��
         */
        virtual void editBoxEditingDidBegin(EditBox* editBox) {};
            
            
        /**@~english
         * This method is called when an edit box loses focus after keyboard is hidden.
         * @~chinese 
         * ���༭�����༭ʱʧȥ�������õĺ�����
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese һ���༭�����ָ��
         */
        virtual void editBoxEditingDidEnd(EditBox* editBox) {};
            
        /**@~english
         * This method is called when the edit box text was changed.
         * @~chinese 
         * ��������ڱ༭������е��ı����ݿ�ʼ�仯��ʱ�򱻵��á�
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese һ���༭�����ָ��
         * @param text @~english The new text.
         * @~chinese ���ı����ݡ�
         */
        virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) {};
            
        /**@~english
         * This method is called when the return button was pressed or the outside area of keyboard was touched.
         * @~chinese 
         * ��������ڱ༭������Return��ť�����£����߱༭�������������򱻵��ʱ�����á�
         * @param editBox @~english The edit box object that generated the event.
         * @~chinese һ���༭�����ָ��
         */
        virtual void editBoxReturn(EditBox* editBox) = 0;
            
    };
        
    /**
     * @brief @~english Class for edit box.
     *
     * You can use this widget to gather small amounts of text from the user.
     *
     * @~chinese һ�����������ı�����
     * 
     * �����ʹ�����������ȡ�û��������ı�����
     * 
     */
        
    class CC_GUI_DLL EditBox
        : public Widget
        , public IMEDelegate
    {
    public:

        /**@~english
         * The popup keyboard return type.
         * @~chinese 
         * ���̵ķ��ؼ�����
         */
        enum class KeyboardReturnType
        {
            DEFAULT,
            DONE,
            SEND,
            SEARCH,
            GO
        };
            
        /**
         * @brief @~english The EditBox::InputMode defines the type of text that the user is allowed
         * to enter.
         * @~chinese EditBox::InputMode�����˿���������ı�����
         */
        enum class InputMode
        {
            /**@~english
             * The user is allowed to enter any text, including line breaks.
             * @~chinese 
             * �û����������κ��ı�,�������з���
             */
            ANY,
                
            /**@~english
             * The user is allowed to enter an e-mail address.
             * @~chinese 
             * �����û�����һ�������ʼ���ַ��
             */
            EMAIL_ADDRESS,
                
            /**@~english
             * The user is allowed to enter an integer value.
             * @~chinese 
             * �����û�����һ������ֵ��
             */
            NUMERIC,
                
            /**@~english
             * The user is allowed to enter a phone number.
             * @~chinese 
             * �����û�����һ���绰���롣
             */
            PHONE_NUMBER,
                
            /**@~english
             * The user is allowed to enter a URL.
             * @~chinese 
             * �����û�����һ��URL��
             */
            URL,
                
            /**@~english
             * The user is allowed to enter a real number value.
             * This extends kEditBoxInputModeNumeric by allowing a decimal point.
             * @~chinese 
             * �����û�����һ��ʵ��
             * ͨ������һ��С������չ��kEditBoxInputModeNumericģʽ
             */
            DECIMAL,
                
            /**@~english
             * The user is allowed to enter any text, except for line breaks.
             * @~chinese 
             *���˻��з����⣬�û����������κ��ı�,
             */
            SINGLE_LINE,
        };
            
        /**
         * @brief @~english The EditBox::InputFlag defines how the input text is displayed/formatted.
         * @~chinese EditBox::InputFlag���������ʾ�͸�ʽ�������ı���
         */
        enum class InputFlag
        {
            /**@~english
             * Indicates that the text entered is confidential data that should be
             * obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
             * @~chinese 
             * ����������ı��Ǳ��ܵ����ݣ��κ�ʱ��Ӧ����������
             * ��������EDIT_BOX_INPUT_FLAG_SENSITIVE
             */
            PASSWORD,
                
            /**@~english
             * Indicates that the text entered is sensitive data that the
             * implementation must never store into a dictionary or table for use
             * in predictive, auto-completing, or other accelerated input schemes.
             * A credit card number is an example of sensitive data.
             * @~chinese 
             * ����������ı����������ݣ�
             * ����ֹ�洢���ֵ������棬Ҳ���������Զ���ȫ����ʾ�û����롣
             * һ�����ÿ��������һ���������ݵ����ӡ�
             */
            SENSITIVE,
                
            /**@~english
             * This flag is a hint to the implementation that during text editing,
             * the initial letter of each word should be capitalized.
             * @~chinese 
             * �����־������������һ����ʾ,���ı��༭��ʱ���Ƿ��ÿһ�����ʵ�����ĸ��д��
             */
            INITIAL_CAPS_WORD,
                
            /**@~english
             * This flag is a hint to the implementation that during text editing,
             * the initial letter of each sentence should be capitalized.
             * @~chinese 
             * �����־������������һ����ʾ,���ı��༭���Ƿ�ÿ�����ӵ�����ĸ��д��
             */
            INITIAL_CAPS_SENTENCE,
                
            /**@~english
             * Capitalize all characters automatically.
             * @~chinese 
             * �Զ�������������ַ���д��
             */
            INITIAL_CAPS_ALL_CHARACTERS,
        };
            
        /**@~english
         * create a edit box with size.
         * @~chinese 
         * ����һ���̶���С�ı༭��
         * @return @~english An autorelease pointer of EditBox, you don't need to release it only if you retain it again.
         * @~chinese һ���༭�����ָ��, ֻ�е���Է��ض������retain��ʱ�����Ҫ����release
         */
        static EditBox* create(const Size& size,
                               Scale9Sprite* normalSprite,
                               Scale9Sprite* pressedSprite = nullptr,
                               Scale9Sprite* disabledSprite = nullptr);

            
        /**@~english
         * create a edit box with size.
         * @~chinese 
         * ����һ���̶���С�ı༭��
         * @return @~english An autorelease pointer of EditBox, you don't need to release it only if you retain it again.
         * @~chinese һ���༭�����ָ�룬ֻ�е���Է��ض������retain��ʱ�����Ҫ����release
         */
        static EditBox* create(const Size& size,
                               const std::string& normal9SpriteBg,
                               TextureResType texType = TextureResType::LOCAL);
            
        /**@~english
         * Constructor.
         * @~chinese 
         * ���캯����
         * @js ctor
         * @lua new
         */
        EditBox(void);
            
        /**@~english
         * Destructor.
         * @~chinese 
         * ����������
         * @js NA
         * @lua NA
         */
        virtual ~EditBox(void);
            
        /**@~english
         * Init edit box with specified size. This method should be invoked right after constructor.
         * @~chinese 
         * ʹ��ָ����С��ʼ���༭���������Ӧ���ڹ��캯��֮����á�
         * @param size @~english The size of edit box.
         * @~chinese �༭��Ĵ�С��
         * @param normal9SpriteBg  @~english background image of edit box.
         * @~chinese �༭��ı���ͼƬ���֡�
         * @param texType @~english the resource type, the default value is TextureResType::LOCAL
         * @~chinese ��Դ����,Ĭ��ֵ��TextureResType::LOCAL
         * @return @~english Whether initialization is successfully or not.
         * @~chinese �Ƿ��ʼ���ɹ���
         */
        bool initWithSizeAndBackgroundSprite(const Size& size,
                                             const std::string& normal9SpriteBg,
                                             TextureResType texType = TextureResType::LOCAL);
            
        
        /**@~english
         * Init edit box with specified size. This method should be invoked right after constructor.
         * @~chinese 
         * ʹ��ָ����С��ʼ���༭���������Ӧ���ڹ��캯��֮�󱻵��á�
         * @param size @~english The size of edit box.
         * @~chinese �༭��Ĵ�С��
         * @param normal9SpriteBg  @~english background image of edit box.
         * @~chinese �༭��ı���ͼƬ���֡�
         * @return @~english Whether initialization is successfully or not.
         * @~chinese �Ƿ��ʼ���ɹ���
         */
        bool initWithSizeAndBackgroundSprite(const Size& size, Scale9Sprite* normal9SpriteBg);

        /**@~english
         * Sets the delegate for edit box.
         * @~chinese 
         * ���ñ༭��ؼ��Ĵ�����
         * @lua NA
         */
        void setDelegate(EditBoxDelegate* delegate);

        /**
         * @js NA
         * @lua NA
         */
        EditBoxDelegate* getDelegate();
            
#if CC_ENABLE_SCRIPT_BINDING
        /**@~english
         * Registers a script function that will be called for EditBox events.
         *
         * This handler will be removed automatically after onExit() called.
         * @~chinese 
         * ע��һ���ű�����,���༭�򷢳��¼�ʱ������ű������ᱻ����
         * 
         * ����ص�����������onExit�������ú�ɾ����
         * @~english
         * @code
         * -- lua sample
         * local function editboxEventHandler(eventType)
         *     if eventType == "began" then
         *         -- triggered when an edit box gains focus after keyboard is shown
         *     elseif eventType == "ended" then
         *         -- triggered when an edit box loses focus after keyboard is hidden.
         *     elseif eventType == "changed" then
         *         -- triggered when the edit box text was changed.
         *     elseif eventType == "return" then
         *         -- triggered when the return button was pressed or the outside area of keyboard was touched.
         *     end
         * end
         *
         * local editbox = EditBox:create(Size(...), Scale9Sprite:create(...))
         * editbox = registerScriptEditBoxHandler(editboxEventHandler)
         * @endcode
         *
         * @~chinese
         * @code
         * -- lua sample
         * local function editboxEventHandler(eventType)
         *     if eventType == "began" then
         *         -- ���༭���ý��㲢�Ҽ��̵�����ʱ�򱻵���
         *     elseif eventType == "ended" then
         *         -- ���༭��ʧȥ���㲢�Ҽ�����ʧ��ʱ�򱻵���
         *     elseif eventType == "changed" then
         *         -- ���༭����ı����޸ĵ�ʱ�򱻵���
         *     elseif eventType == "return" then
         *         -- ���û�����༭��ļ�����������򣬻��߼��̵�Return��ť�����ʱ������
         *     end
         * end
         *
         * local editbox = EditBox:create(Size(...), Scale9Sprite:create(...))
         * editbox = registerScriptEditBoxHandler(editboxEventHandler)
         * @endcode
         *
         * @param handler @~english A number that indicates a lua function.
         * @~chinese һ��������������ʾһ��lua�������
         * @js NA
         * @lua NA
         */
        void registerScriptEditBoxHandler(int handler);
            
        /**@~english
         * Unregisters a script function that will be called for EditBox events.
         * @~chinese 
         * ע����ע��ı༭���¼������ű�����
         * @js NA
         * @lua NA
         */
        void unregisterScriptEditBoxHandler(void);
        /**@~english
         * get a script Handler
         * @~chinese 
         * ��ȡһ���ű��������
         * @js NA
         * @lua NA
         */
        int  getScriptEditBoxHandler(void){ return _scriptEditBoxHandler ;}
            
#endif // #if CC_ENABLE_SCRIPT_BINDING
            
        /**@~english
         * Set the text entered in the edit box.
         * @~chinese 
         * ���ñ༭����������ı���
         * @param pText @~english The given text.
         * @~chinese �������ı��ַ�����
         */
        void setText(const char* pText);
            
        /**@~english
         * Get the text entered in the edit box.
         * @~chinese 
         * ��ȡ�༭����������ı���
         * @return @~english The text entered in the edit box.
         * @~chinese �༭����������ı���
         */
        const char* getText(void);
            
        /**@~english
         * Set the font for EditBox. Only system font is allowed.
         * @~chinese 
         * ���ñ༭������塣��֧��ϵͳ����
         * @param pFontName @~english The font name.
         * @~chinese �������ơ�
         * @param fontSize @~english The font size.
         * @~chinese �����С��
         */
        void setFont(const char* pFontName, int fontSize);
            
        /**@~english
         * Set the font name. Only system font is allowed.
         * @~chinese 
         * ������������֡���֧��ϵͳ����
         * @param pFontName @~english The font name.
         * @~chinese �������ơ�
         */
        void setFontName(const char* pFontName);
            
        /**@~english
         * Set the font size.
         * @~chinese 
         * ���������С��
         * @param fontSize @~english The font size.
         * @~chinese �����С��
         */
        void setFontSize(int fontSize);
            
        /**@~english
         * Set the font color of the widget's text.
         * @~chinese 
         * ���ñ༭����ı�������ɫ��
         */
        void setFontColor(const Color3B& color);
            
        /**@~english
         * Set the placeholder's font. Only system font is allowed.
         * @~chinese 
         * ����ռλ�������塣��֧��ϵͳ����
         * @param pFontName @~english The font name.
         * @~chinese �������ơ�
         * @param fontSize @~english The font size.
         * @~chinese �����С��
         */
        void setPlaceholderFont(const char* pFontName, int fontSize);
            
        /**@~english
         * Set the placeholder's font name. Only system font is allowed.
         * @~chinese 
         * ����ռλ�����������ơ���֧��ϵͳ����
         * @param pFontName @~english The font name.
         * @~chinese �������ơ�
         */
        void setPlaceholderFontName(const char* pFontName);
            
        /**@~english
         * Set the placeholder's font size.
         * @~chinese 
         * ����ռλ���������С��
         * @param fontSize @~english The font size.
         * @~chinese �����С��
         */
        void setPlaceholderFontSize(int fontSize);
            
        /**@~english
         * Set the font color of the placeholder text when the edit box is empty.
         * @~chinese 
         * ���༭��Ϊ�յ�ʱ������ռλ���ı�������ɫ��
         * @param color @~english The font color in Color3B
         * @~chinese �������ɫ��������Color3B
         */
        void setPlaceholderFontColor(const Color3B& color);

        /**@~english
         * Set the font color of the placeholder text when the edit box is empty.
         * @~chinese 
         * ���༭��Ϊ�յ�ʱ������ռλ���ı�������ɫ
         * @param color @~english The font color in Color4B
         * @~chinese �������ɫ��������Color4B
         */
        void setPlaceholderFontColor(const Color4B& color);
            
        /**@~english
         * Set a text in the edit box that acts as a placeholder when an
         * edit box is empty.
         * @~chinese 
         * ���༭��Ϊ�յ�ʱ�����ñ༭���е�ռλ���ı�
         * @param pText @~english The given text.
         * @~chinese �������ı���
         */
        void setPlaceHolder(const char* pText);
            
        /**@~english
         * Get a text in the edit box that acts as a placeholder when an
         * edit box is empty.
         * @~chinese 
         * ���༭��Ϊ�յ�ʱ�򣬻�ȡ�༭���е�ռλ���ı�
         */
        const char* getPlaceHolder(void);
            
        /**@~english
         * Set the input mode of the edit box.
         * @~chinese 
         * ���ñ༭�������ģʽ��
         * @param inputMode @~english One of the EditBox::InputMode constants.
         * @~chinese EditBox::InputMode����֮һ
         */
        void setInputMode(InputMode inputMode);
            
        /**@~english
         * Sets the maximum input length of the edit box.
         * Setting this value enables multiline input mode by default.
         * Available on Android, iOS and Windows Phone.
         *
         * @~chinese 
         * ���ñ༭�������������󳤶ȡ�
         * �������ֵĬ�������������
         * ������Android,iOS��Windows Phoneƽ̨ʹ��
         * 
         * @param maxLength @~english The maximum length.
         * @~chinese ��󳤶ȡ�
         */
        void setMaxLength(int maxLength);
            
        /**@~english
         * Gets the maximum input length of the edit box.
         *
         * @~chinese 
         * ��ȡ�༭���������볤�ȡ�
         * 
         * @return @~english Maximum input length.
         * @~chinese ��󳤶�
         */
        int getMaxLength();
            
        /**@~english
         * Set the input flags that are to be applied to the edit box.
         * @~chinese 
         * ���ñ༭��������ʶ�������ʶ��EditBox::InputFlag����
         * @param inputFlag @~english One of the EditBox::InputFlag constants.
         * @~chinese EditBox::InputFlag����֮һ
         */
        void setInputFlag(InputFlag inputFlag);
            
        /**@~english
         * Set the return type that are to be applied to the edit box.
         * @~chinese 
         * ���ñ༭��ļ��̵�Return���ͣ�������͵�ȡֵΪEditBox::KeyboardReturnType����֮һ
         * @param returnType @~english One of the EditBox::KeyboardReturnType constants.
         * @~chinese EditBox::KeyboardReturnType����֮һ
         */
        void setReturnType(EditBox::KeyboardReturnType returnType);
            
        virtual void setPosition(const Vec2& pos) override;
        virtual void setVisible(bool visible) override;
        virtual void setContentSize(const Size& size) override;
        virtual void setAnchorPoint(const Vec2& anchorPoint) override;

        /**@~english
         * Returns the "class name" of widget.
         * @~chinese 
         * �������������ַ���
         */
        virtual std::string getDescription() const override;

        /**
         * @js NA
         * @lua NA
         */
        virtual void draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void onEnter(void) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void onExit(void) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardDidShow(IMEKeyboardNotificationInfo& info) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardWillHide(IMEKeyboardNotificationInfo& info) override;
        /**
         * @js NA
         * @lua NA
         */
        virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info) override;

        /*
         * @js NA
         * @lua NA
         */
        void touchDownAction(Ref *sender, TouchEventType controlEvent);
            
    protected:
        virtual void adaptRenderers() override;

        void updatePosition(float dt);
        EditBoxImpl*      _editBoxImpl;
        EditBoxDelegate*  _delegate;
            
        InputMode    _editBoxInputMode;
        InputFlag    _editBoxInputFlag;
        EditBox::KeyboardReturnType  _keyboardReturnType;
            
        Scale9Sprite *_backgroundSprite;
        std::string _text;
        std::string _placeHolder;
            
        std::string _fontName;
        std::string _placeholderFontName;
            
        int _fontSize;
        int _placeholderFontSize;
            
        Color4B _colText;
        Color4B _colPlaceHolder;
            
        int   _maxLength;
        float _adjustHeight;
#if CC_ENABLE_SCRIPT_BINDING
        int   _scriptEditBoxHandler;
#endif
    };
}

// end of ui group
/// @}
NS_CC_END

#endif /* __UIEDITTEXT_H__ */

