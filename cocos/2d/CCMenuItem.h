/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCMENU_ITEM_H__
#define __CCMENU_ITEM_H__

// C++ includes
#include <functional>

// cocos2d includes
#include "2d/CCNode.h"
#include "base/CCProtocols.h"

NS_CC_BEGIN

typedef std::function<void(Ref*)> ccMenuCallback;

class Label;
class LabelAtlas;
class Sprite;
class SpriteFrame;
#define kItemSize 32
    
/**
 * @addtogroup _2d
 * @{
 */

/** @class MenuItem
 * @brief @~english MenuItem base class.
 *  Subclass MenuItem (or any subclass) to create your custom MenuItem objects.
 *
 * @~chinese �˵�����ࡣ
 * ʹ�ü̳�MenuItem�������ഴ���Զ���˵��
 */
class CC_DLL MenuItem : public Node
{
public:
    /** @~english Creates a MenuItem with no callback.
     * @~chinese ����һ��û��ָ���ص��Ĳ˵��
     *
     * @return @~english A initialized MenuItem object which is marked as "autorelease".
     * @~chinese һ����ʼ���Ĳ˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItem* create();

    CC_DEPRECATED_ATTRIBUTE static MenuItem* create(Ref *rec, SEL_MenuHandler selector);

    /** @~english Creates a MenuItem with a callback.
     * @~chinese ����һ��ָ���ص��Ĳ˵��
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItem object which is marked as "autorelease".
     * @~chinese һ����ʼ���Ĳ˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItem* create(const ccMenuCallback& callback);

    /** @~english Returns the outside box.
     * @~chinese ���ز˵�������
     * @return @~english The outside box. @~chinese �˵������
     */
    Rect rect() const;

    /** @~english Activate the item.
     * @~chinese ����˵��
     */
    virtual void activate();

    /** @~english The item was selected (not activated), similar to "mouse-over".
     * @~chinese �趨�˵���Ϊѡ��״̬ (û�м���), ���������ͣ��
     */
    virtual void selected();

    /** @~english The item was unselected.
     * @~chinese ȡ��ѡ��״̬��
     */
    virtual void unselected();

    /** @~english Returns whether or not the item is enabled.
     * @~chinese ���ز˵����Ƿ����ã���Ӧ�������
     * @return @~english Whether or not the item is enabled. @~chinese �˵����Ƿ����á�
     */
    virtual bool isEnabled() const;

    /** @~english Enables or disables the item.
     * @~chinese ���û���ò˵��
     * @param enabled @~english true��enable the menu item��false��disabled the menuitem. 
     * @~chinese true�����ò˵��false�����ò˵��
     */
    virtual void setEnabled(bool enabled);

    /** @~english Returns whether or not the item is selected.
     * @~chinese ���ز˵����Ƿ�ѡ�С�
     * @return @~english Return true if the item is selected. @~chinese �˵��ѡ�з���true�����򷵻�false��
     */
    virtual bool isSelected() const;

    /** @~english Set the callback to the menu item.
     * In js,can contain two params,the second param is js callback��s caller.
     * @~chinese ���ò˵���ص���
     * ��js����԰��������������ڶ���������js�ص������ĵ����ߡ�
     * @param callback @~english One callback be invoked if the item is actived. 
     * @~chinese һ���˵������ʱ���õĻص���
     * @lua NA
     */
    void setCallback(const ccMenuCallback& callback);
    
    CC_DEPRECATED_ATTRIBUTE void setTarget(Ref *rec, SEL_MenuHandler selector);

    virtual void onExit() override;
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    MenuItem()
    : _selected(false)
    , _enabled(false)
	, _callback(nullptr)
    {}

    virtual ~MenuItem();
    
    bool initWithCallback(const ccMenuCallback& callback);
    
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref *rec, SEL_MenuHandler selector);

protected:
    bool            _selected;
    bool            _enabled;
    ccMenuCallback _callback;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItem);
};

/** @class MenuItemLabel
 * @brief @~english An base class for "label" MenuItemLabel items.
 * Any Node that supports the LabelProtocol protocol can be added.
 * Supported nodes:
 * - LabelAtlas
 * - Label
 * @~chinese һ��"label"��ʽ���ı��˵�����ࡣ
 * ֧���κ�ʵ��LabelProtocol�ӿڵĽڵ�:
 * - LabelAtlas
 * - Label
 */
class CC_DLL MenuItemLabel : public MenuItem
{
public:
    CC_DEPRECATED_ATTRIBUTE static MenuItemLabel * create(Node*label, Ref* target, SEL_MenuHandler selector);

    /**
     * @~english Creates a MenuItemLabel with a Label and a callback.
     * @~chinese ʹ�ø����ı�ǩ���ص�����һ����ǩ�˵��
     *
     * @param label @~english One Node that supports the LabelProtocol protocol. 
     * @~chinese һ��ʵ����LabelProtocol�ӿڵĽڵ㡣
     * @param callback @~english One callback be invoked if the item is actived. 
     * @~chinese һ���˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItemLabel object which is marked as "autorelease".
     * @~chinese һ����ʼ�����ı��˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemLabel * create(Node* label, const ccMenuCallback& callback);

    /**
     * @~english Creates a MenuItemLabel with a Label without callback.
     * @~chinese ʹ�ø����ı�ǩ����һ��û���趨�ص��ı�ǩ�˵��
     *
     * @param label @~english One Node that supports the LabelProtocol protocol. 
     * @~chinese һ��ʵ��LabelProtocol�ӿڵĽڵ㡣
     *
     * @return @~english A initialized MenuItemLabel object which is marked as "autorelease".
     * @~chinese һ����ʼ�����ı��˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemLabel* create(Node *label);

    /**
     * @~english Sets a new string to the inner label.
     * @~chinese Ϊ���õı�ǩ�����µ��ַ�����
     * @param text @~english The text to display.
     * @~chinese Ҫ��ʾ���ı���
     */
    void setString(const std::string& text);

    /**
     * @~english Gets the color that will be used to disable the item.
     * @~chinese ��ȡ�˵������״̬�µ���ɫ��
     * @return @~english The color that used for disable the item. @~chinese ����״̬�µ���ɫ��
     */
    inline const Color3B& getDisabledColor() const { return _disabledColor; };

    /**
     * @~english Sets the color that will be used to disable the item.
     * @~chinese ���ò˵������״̬�µ���ɫ��
     *
     * @param color @~english The color that will be used to disable the item.
     * @~chinese ����״̬�µ���ɫ��
     */
    inline void setDisabledColor(const Color3B& color) { _disabledColor = color; };
    
    /**
     * @~english Gets the label that is rendered.
     * @~chinese ��ȡ�˵����б�������ʾ�ı��Ľڵ㡣
     * @return @~english The label that is rendered. @~chinese ������Ⱦ�ı��Ľڵ㡣
     */
    inline Node* getLabel() const { return _label; };
    
    /**
     * @~english Sets the label that is rendered.
     * @~chinese ���˵���ָ��һ��������ʾ�ı��Ľڵ㡣
     *
     * @param node @~english One Node that supports the LabelProtocol protocol.
     * @~chinese һ��ʵ����LabelProtocol�ӿڵĽڵ㡣
     */
    void setLabel(Node* node);
    
    // Overrides
    virtual void activate() override;
    virtual void selected() override;
    virtual void unselected() override;
    virtual void setEnabled(bool enabled) override;
    
CC_CONSTRUCTOR_ACCESS:
    
    MenuItemLabel()
    : _originalScale(0.0)
    , _label(nullptr)
    {}

    virtual ~MenuItemLabel();
    
    bool initWithLabel(Node* label, const ccMenuCallback& callback);
    
    CC_DEPRECATED_ATTRIBUTE bool initWithLabel(Node* label, Ref* target, SEL_MenuHandler selector);
    
protected:
    Color3B    _colorBackup;
    float      _originalScale;

    Color3B _disabledColor;
    Node* _label;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemLabel);
};


/** @class MenuItemAtlasFont
 * @brief @~english Helper class that creates a MenuItemLabel class with a LabelAtlas.
 * @~chinese һ�����ڸ������ַ������ô����ı��˵���Ļ��ࡣ
 */
class CC_DLL MenuItemAtlasFont : public MenuItemLabel
{
public:
    /**
     * @~english Creates a menu item from a string and atlas configuration.
     * @~chinese ʹ�ø������ַ������ַ������ô����˵��
     *
     * @param text @~english The text to display. @~chinese Ҫ��ʾ���ı���
     * @param charMapFilePath @~english The file path of char map font. @~chinese �ַ���������ļ�·����
     * @param itemWidth @~english The width of character. @~chinese �ַ��Ŀ�ȡ�
     * @param itemHeight @~english The height of character. @~chinese �ַ��ĸ߶ȡ�
     * @param startingCharacter @~english The starting character. @~chinese ��ʼ�ַ���
     *
     * @return @~english A initialized MenuItemLabel object which is marked as "autorelease".
     * @~chinese һ����ʼ�����ı��˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemAtlasFont* create(const std::string& text, const std::string& charMapFilePath, int itemWidth, int itemHeight, char startingCharacter);

    CC_DEPRECATED_ATTRIBUTE static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);

    /**
     * @~english Creates a menu item from a string, atlas configuration and callback.
     * @~chinese ʹ�ø������ַ������ַ������ü��ص������˵��
     *
     * @param text @~english The text to display. @~chinese Ҫ��ʾ���ı���
     * @param charMapFilePath @~english The file path of char map font. @~chinese �ַ���������ļ�·����
     * @param itemWidth @~english The width of character. @~chinese �ַ��Ŀ�ȡ�
     * @param itemHeight @~english The height of character. @~chinese �ַ��ĸ߶ȡ�
     * @param startingCharacter @~english The starting character. @~chinese ��ʼ�ַ���
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItemLabel object which is marked as "autorelease".
     * @~chinese һ����ʼ�����ı��˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemAtlasFont* create(const std::string& text, const std::string& charMapFilePath, int itemWidth, int itemHeight, char startingCharacter, const ccMenuCallback& callback);
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemAtlasFont(){}

    virtual ~MenuItemAtlasFont(){}
    
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);
    
    bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemAtlasFont);
};


/** @class MenuItemFont
 * @brief @~english A MenuItemFont.
 * Helper class that creates a MenuItemLabel class with a Label.
 * @~chinese MenuItemFont A��
 * һ���ø����������ô���MenuItemLabel�˵���������ࡣ
 */
class CC_DLL MenuItemFont : public MenuItemLabel
{
public:
    /** @~english Creates a menu item from a string without callback with default font setting. 
     * @~chinese ���ڸ������ַ�����Ĭ���������ô���һ��û�лص��Ĳ˵��
     *
     * @param text @~english The text to display. @~chinese Ҫ��ʾ���ı���
     *
     * @return @~english A initialized MenuItemFont object which is marked as "autorelease".
     * @~chinese һ����ʼ����MenuItemFont�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemFont * create(const std::string& text = "");

    CC_DEPRECATED_ATTRIBUTE static MenuItemFont * create(const std::string& value, Ref* target, SEL_MenuHandler selector);

    /** @~english Creates a menu item from a string with a callback with default font setting. 
     * @~chinese ���ڸ������ַ������������ü��ص������˵��
     *
     * @param text @~english The text to display. @~chinese Ҫ��ʾ���ı���
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItemFont object which is marked as "autorelease".
     * @~chinese һ����ʼ����MenuItemFont�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemFont * create(const std::string& text, const ccMenuCallback& callback);

    /** @~english Set default font size.  @~chinese ����Ĭ�������С��
     * @param defaultFontSize @~english The default font size. @~chinese Ĭ�������С��
     */
    static void setFontSize(int defaultFontSize);

    /** @~english Get default font size.  @~chinese ��ȡĬ�������С��
     * @return @~english The default font size. @~chinese Ĭ�������С��
     */
    static int getFontSize();

    CC_DEPRECATED_ATTRIBUTE static int fontSize() { return MenuItemFont::getFontSize(); };

    /** @~english Set the default font name.  @~chinese ����Ĭ����������
     * @param defaultFontName @~english The default font name. @~chinese Ĭ����������
     */
    static void setFontName(const std::string& defaultFontName);

    /** @~english Get the default font name.  @~chinese ��ȡĬ����������
     * @return @~english The default font name. @~chinese Ĭ����������
     */
    static const std::string& getFontName();

    CC_DEPRECATED_ATTRIBUTE static const std::string& fontName() { return MenuItemFont::getFontName(); };

    /** @~english Set the font size.
     * c++ can not overload static and non-static member functions with the same parameter types.
     * so change the name to setFontSizeObj.
     * @~chinese ���������С��
     * c++����������ͬ�������͵ľ�̬���Ǿ�̬��Ա������
     * ���Ը���setFontSizeObj��
     *
     * @param fontSize @~english The font size. @~chinese �����С��
     *
     * @js setFontSize
     */
    void setFontSizeObj(int fontSize);
    
    /** @~english Get the font size .
     * @~chinese ��ȡ�����С��
     * @return @~english The font size. @~chinese �����С��
     * @js getFontSize
     */
    int getFontSizeObj() const;

    CC_DEPRECATED_ATTRIBUTE int fontSizeObj() const { return getFontSizeObj(); };
    
    /**@~english
     * Set the font name .
     * c++ can not overload static and non-static member functions with the same parameter types.
     * so change the name to setFontNameObj.
     * @~chinese 
     * ������������֡�
     * c++����������ͬ�������͵ľ�̬���Ǿ�̬��Ա������
     * ���Ը���setFontNameObj��
     *
     * @param fontName @~english The font name. @~chinese ��������
     *
     * @js setFontName
     */
    void setFontNameObj(const std::string& fontName);

    /** @~english Returns the name of the font.
     * @~chinese ������������ơ�
     *
     * @return @~english The font name. @~chinese ��������
     *
     * @js getFontName
     */
    const std::string& getFontNameObj() const;

    CC_DEPRECATED_ATTRIBUTE const std::string& fontNameObj() const { return getFontNameObj(); }
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemFont();

    virtual ~MenuItemFont();
    
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, Ref* target, SEL_MenuHandler selector);
    
    bool initWithString(const std::string& value, const ccMenuCallback& callback);
    
protected:
    int _fontSize;
    std::string _fontName;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemFont);
};


/** @class MenuItemSprite
 * @brief @~english MenuItemSprite accepts Node<RGBAProtocol> objects as displayed items.
 * Displayed item has 3 different states:
 * - normal
 * - selected
 * - disabled
 * 
 * @~chinese MenuItemSprite����ʵ����Node<RGBAProtocol>�ӿڵ��κνڵ������Ϊ��ʾ�
 * ��ʾ����3����ͬ��״̬:
 * - ����
 * - ѡ��
 * - ������
 * 
 @since v0.8.0
 */
class CC_DLL MenuItemSprite : public MenuItem
{
public:
    /** @~english Creates a menu item with a normal, selected and disabled node. 
     * @~chinese ���ڸ����Ĳ�ͬ״̬����ʾ�Ľڵ㴴���˵��
     *
     * @param normalNode @~english The normal node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     * @param selectedNode @~english The selected node to display. @~chinese ѡ��״̬��ʾ�Ľڵ㡣
     * @param disabledNode @~english The disabled node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     *
     * @return @~english A initialized MenuItemSprite object which is marked as "autorelease".
     * @~chinese һ����ʼ����MenuItemSprite�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemSprite * create(Node* normalNode, Node* selectedNode, Node* disabledNode = nullptr);
    
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Ref* target, SEL_MenuHandler selector);
    
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);

    /** @~english Creates a menu item with a normal and selected node with a callback.  
     * @~chinese ���ڸ����Ĳ�ͬ״̬����ʾ�Ľڵ㼰�ص������˵��
     *
     * @param normalNode @~english The normal node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     * @param selectedNode @~english The selected node to display. @~chinese ѡ��״̬��ʾ�Ľڵ㡣
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItemSprite object which is marked as "autorelease".
     * @~chinese һ����ʼ����MenuItemSprite�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemSprite * create(Node* normalNode, Node* selectedNode, const ccMenuCallback& callback);

    /** @~english Creates a menu item with a normal,selected and disabled node with callback. 
     * @~chinese ���ڸ����Ĳ�ͬ״̬����ʾ�Ľڵ㼰�ص������˵��
     *
     * @param normalNode @~english The normal node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     * @param selectedNode @~english The selected node to display. @~chinese ѡ��״̬��ʾ�Ľڵ㡣
     * @param disabledNode @~english The disabled node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItemSprite object which is marked as "autorelease".
     * @~chinese һ����ʼ����MenuItemSprite�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemSprite * create(Node* normalNode, Node* selectedNode, Node* disabledNode, const ccMenuCallback& callback);

    /** @~english Gets the node used when the item is not selected.  @~chinese ��ȡ����״̬��ʹ�õĽڵ㡣
     * @return @~english The normal node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     */
    inline Node* getNormalImage() const { return _normalImage; };
    
    /** @~english Sets the node used when the item is not selected.  @~chinese ������������״̬�µĽڵ㡣
     * @param normalNode @~english The normal node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     */
    void setNormalImage(Node* normalNode);
    
    /** @~english Gets the node used when the item is selected.  @~chinese ��ȡѡ��״̬��ʹ�õĽڵ㡣
     * @return @~english The selected node to display. @~chinese ѡ��״̬��ʾ�Ľڵ㡣
     */
    inline Node* getSelectedImage() const { return _selectedImage; };
    
    /** @~english Sets the node used when the item is selected.  @~chinese ��������ѡ��״̬�µĽڵ㡣
     * @param selectedNode @~english The selected node to display. @~chinese ѡ��״̬��ʾ�Ľڵ㡣
     */
    void setSelectedImage(Node* selectedNode);
    
    /** @~english Gets the node used when the item is disabled.  @~chinese ��ȡ������״̬��ʹ�õĽڵ㡣
     * @return @~english The disabled node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     */
    inline Node* getDisabledImage() const { return _disabledImage; };
    
    /** @~english Sets the node used when the item is disabled.  @~chinese �������ڲ�����״̬�µĽڵ㡣
     * @param disabledNode @~english The disabled node to display. @~chinese ����״̬��ʾ�Ľڵ㡣
     */
    void setDisabledImage(Node* disabledNode);
    
    
    virtual void selected() override;

    virtual void unselected() override;

    virtual void setEnabled(bool bEnabled) override;
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemSprite()
    :_normalImage(nullptr)
    ,_selectedImage(nullptr)
    ,_disabledImage(nullptr)
    {}
    
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);

    bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
    
protected:
    virtual void updateImagesVisibility();

    Node* _normalImage;
    Node* _selectedImage;
    Node* _disabledImage;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemSprite);
};


/** @class MenuItemImage
 * @brief @~english MenuItemImage accepts images as displayed items.
 * Displayed items has 3 different states:
 * - normal
 * - selected
 * - disabled
 * 
 * For best results try that all images are of the same size.
 * @~chinese ͼƬ�˵������ͼ����Դ��Ϊ��ʾ�
 * ��ʾ����3����ͬ��״̬:
 * - ����
 * - ѡ��
 * - ������
 * 
 * Ϊ�˻�ȡ���Ч��������ͼƬ��Դ�Ĵ�СӦ�ñ���һ�¡�
 */
class CC_DLL MenuItemImage : public MenuItemSprite
{
public:
    /** @~english Creates an empty MenuItemImage.  @~chinese ����һ���յ�ͼƬ�˵��
     * @return @~english A initialized MenuItemImage object which is marked as "autorelease".
     * @~chinese һ����ʼ����ͼƬ�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemImage* create();

    /** @~english Creates a menu item with a normal and selected image. @~chinese ���ڸ�����������ѡ��״̬��ͼƬ��Դ�����˵��
     *
     * @param normalImage @~english The normal image to display. @~chinese ����״̬��ʾ��ͼƬ·����
     * @param selectedImage @~english The selected image to display. @~chinese ѡ��״̬��ʾ��ͼƬ·����
     *
     * @return @~english A initialized MenuItemImage object which is marked as "autorelease".
     * @~chinese һ����ʼ����ͼƬ�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage);

    /** @~english Creates a menu item with a normal,selected  and disabled image. @~chinese ���ڸ�����������ѡ�м�������״̬��ͼƬ��Դ�����˵��
     *
     * @param normalImage @~english The normal image to display. @~chinese ����״̬��ʾ��ͼƬ·����
     * @param selectedImage @~english The selected image to display. @~chinese ѡ��״̬��ʾ��ͼƬ·����
     * @param disabledImage @~english The disabled image to display. @~chinese ����״̬��ʾ��ͼƬ·����
     *
     * @return @~english A initialized MenuItemImage object which is marked as "autorelease".
     * @~chinese һ����ʼ����ͼƬ�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage);

    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, Ref* target, SEL_MenuHandler selector);

    /** @~english Creates a menu item with a normal and selected image with a callback. @~chinese ���ڸ�����������ѡ��״̬��ͼƬ��Դ���ص������˵��
     *
     * @param normalImage @~english The normal image to display. @~chinese ����״̬��ʾ��ͼƬ·����
     * @param selectedImage @~english The selected image to display. @~chinese ѡ��״̬��ʾ��ͼƬ·����
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItemImage object which is marked as "autorelease".
     * @~chinese һ����ʼ����ͼƬ�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback);

    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    
    /** @~english Creates a menu item with a normal,selected and disabled image with a callable object.  
     * @~chinese ���ڸ����Ĳ�ͬ״̬�µ�ͼƬ��Դ���ص������˵��
     *
     * @param normalImage @~english The normal image to display. @~chinese ����״̬��ʾ��ͼƬ·����
     * @param selectedImage @~english The selected image to display. @~chinese ѡ��״̬��ʾ��ͼƬ·����
     * @param disabledImage @~english The disabled image to display. @~chinese ����״̬��ʾ��ͼƬ·����
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     *
     * @return @~english A initialized MenuItemImage object which is marked as "autorelease".
     * @~chinese һ����ʼ����ͼƬ�˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);

    /** @~english Sets the sprite frame for the normal image.  @~chinese ����һ��SpriteFrame���������״̬����ʹ�õ�ͼƬ��*/
    void setNormalSpriteFrame(SpriteFrame* frame);
    /** @~english Sets the sprite frame for the selected image.  @~chinese ����һ��SpriteFrame�����ѡ��״̬����ʹ�õ�ͼƬ��*/
    void setSelectedSpriteFrame(SpriteFrame* frame);
    /** @~english Sets the sprite frame for the disabled image.  @~chinese ����һ��SpriteFrame�����������״̬����ʹ�õ�ͼƬ��*/
    void setDisabledSpriteFrame(SpriteFrame* frame);
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemImage(){}

    virtual ~MenuItemImage(){}
    
    bool init();
    
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    
    bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemImage);
};


/** @class MenuItemToggle
 * @brief @~english A MenuItemToggle.
 * A simple container class that "toggles" it's inner items.
 * The inner items can be any MenuItem.
 * @~chinese �������˵��
 * һ��ʵ���л��ڲ��˵���ļ������ࡣ
 * �ڲ���������κ�MenuItem����
 */
class CC_DLL MenuItemToggle : public MenuItem
{
public:
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle * createWithTarget(Ref* target, SEL_MenuHandler selector, const Vector<MenuItem*>& menuItems);

    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle* createWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, ...)CC_REQUIRES_NULL_TERMINATION;
    
    /**
     *@brief @~english Creates a menu item toggle from a Vector of MenuItem with a callback.
     * @~chinese ���ڸ����Ļص����˵������鴴���˵��������
     *
     * @param callback @~english The callback be invoked if the item is actived. @~chinese �˵������ʱ���õĻص���
     * @param menuItems @~english A array of MenuItem object. @~chinese �˵������顣
     *
     * @return @~english A initialized MenuItemToggle object which is marked as "autorelease".
     * @~chinese һ����ʼ���Ĵ������˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemToggle * createWithCallback(const ccMenuCallback& callback, const Vector<MenuItem*>& menuItems);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported.
    typedef MenuItem* M;
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for lists longer than 10 items, use createWithArray or variadicCreate with NULL as the last argument.
    static MenuItemToggle* createWithCallbackVA(const ccMenuCallback& callback, M item, ...);
#else
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
#endif
    /** @~english Creates a menu item toggle with no callback. @~chinese ����һ��û�лص��Ĳ˵��������
     *
     * @return @~english A initialized MenuItemToggle object which is marked as "autorelease".
     * @~chinese һ����ʼ���Ĵ������˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemToggle* create();
    
    /** @~english Creates a menu item toggle with a item.  @~chinese ����һ�������Ĳ˵�����˵��������
     *
     * @param item @~english One MenuItem object. @~chinese һ���˵������
     *
     * @return @~english A initialized MenuItemToggle object which is marked as "autorelease".
     * @~chinese һ����ʼ���Ĵ������˵���ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static MenuItemToggle* create(MenuItem *item);
    
    /** @~english Add more menu item.  @~chinese ����������Ӳ˵��
     * @param item @~english One MenuItem object. @~chinese һ���˵������
     */
    void addSubItem(MenuItem *item);
    
    /** @~english Return the selected item.  @~chinese ���ر�ѡ�еĲ˵��
     * @return @~english The selected item. @~chinese ��ѡ�еĲ˵���ָ�롣
     */
    MenuItem* getSelectedItem();
    
    CC_DEPRECATED_ATTRIBUTE MenuItem* selectedItem() { return getSelectedItem(); }

    /** @~english Gets the index of the selected item. @~chinese ��ȡ��ѡ�еĲ˵���������
     * @return @~english Return the index of the selected item. @~chinese ���ر�ѡ�еĲ˵���������
     */
    inline unsigned int getSelectedIndex() const { return _selectedIndex; };
    
    /** @~english Sets the index of the selected item. @~chinese ���ñ�ѡ�еĲ˵���������
     * @param index @~english The index of the selected item. @~chinese ��ѡ�еĲ˵���������
     */
    void setSelectedIndex(unsigned int index);
    
    /** @~english Gets the array that contains the subitems.
     *You can add/remove items in runtime, and you can replace the array with a new one.
     * @~chinese ��ȡ�����������Ĳ˵��
     * ������������ʱ��ӻ���ɾ���˵�������滻�����˵������顣
     * @return @~english The array that contains the subitems. @~chinese �����������Ĳ˵��
     * @since v0.7.2
     * @js NA
     * @lua NA
     */
    inline const Vector<MenuItem*>& getSubItems() const { return _subItems; };
    inline Vector<MenuItem*>& getSubItems() { return _subItems; };

    /** @~english Sets the array that contains the subitems. @~chinese �趨�����������Ĳ˵��
     * @param items @~english A array of MenuItem object. @~chinese һ���˵���������顣
     */
    inline void setSubItems(const Vector<MenuItem*>& items) {
        _subItems = items;
    }
    
    // Overrides
    virtual void activate() override;
    virtual void selected() override;
    virtual void unselected() override;
    virtual void setEnabled(bool var) override;
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemToggle()
    : _selectedIndex(0)
    , _selectedItem(nullptr)
    {}

    virtual ~MenuItemToggle();
    
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, va_list args);

    bool initWithCallback(const ccMenuCallback& callback, MenuItem* item, va_list args);

    bool initWithItem(MenuItem *item);

protected:
    unsigned int _selectedIndex;
    MenuItem* _selectedItem;

    /** Array that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
     @since v0.7.2
     */
    Vector<MenuItem*> _subItems;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemToggle);

};


// end of 2d group
/// @}

NS_CC_END

#endif //__CCMENU_ITEM_H__
