/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __UIRICHTEXT_H__
#define __UIRICHTEXT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {
    
/** @class RichElement
*@brief @~english Rich text element base class.
 It defines the basic common properties for all rich text element.
 
 @~chinese ���ı�Ԫ�ػ��ࡣ
 �����������еĸ��ı�Ԫ�ص�ͨ�����ԡ�
*/
class CC_GUI_DLL RichElement : public Ref
{
public:
    /**
     *@brief Rich element type.
     */
    enum class Type
    {
        TEXT,
        IMAGE,
        CUSTOM
    };
    
    /**
     * @~english Default constructor.
     * @~chinese Ĭ�Ϲ�����
     * @js ctor
     * @lua new
     */
    RichElement(){};
    
    /**
     * @~english Default destructor.
     * @~chinese Ĭ��������
     * @js NA
     * @lua NA
     */
    virtual ~RichElement(){};

    
    /**
     * @~english Initialize a rich element with different arguments.
     * @~chinese ͨ����ͬ�Ĳ�����ʼ��һ�����ı�Ԫ�ء�
     * @param tag @~english A integer tag value. @~chinese ��ǩֵ��
     * @param color @~english A color in @see `Color3B`. @~chinese ��ɫֵ�� 
     * @param opacity @~english A opacity value in `GLubyte`. @~chinese ��͸���ȡ�
     * @return @~english True if initialize success, false otherwise. @~chinese True������ʼ���ɹ�����֮ʧ�ܡ�
     */
    bool init(int tag, const Color3B& color, GLubyte opacity);
protected:
    Type _type;
    int _tag;
    Color3B _color;
    GLubyte _opacity;
    friend class RichText;
};
    
/** @class RichElementText
*@brief @~english Rich element for displaying text.

 @~chinese ������ʾ�ı���RichElementText��
*/
class CC_GUI_DLL RichElementText : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese Ĭ�Ϲ�����
     * @js ctor
     * @lua new
     */
    RichElementText(){_type = Type::TEXT;};

    
    /**
     * @~english Default destructor.
     * @~chinese Ĭ��������
     * @js NA
     * @lua NA
     */
    virtual ~RichElementText(){};
    
    /**
     * @~english Initialize a RichElementText with various arguments.
     * @~chinese ͨ�����������ʼ��һ��RichElementText�ࡣ
     * @param tag @~english A integer tag value. @~chinese ��ǩֵ��
     * @param color @~english A color in Color3B. @~chinese ��ɫֵ��
     * @param opacity @~english A opacity in GLubyte. @~chinese ��͸���ȡ�
     * @param text @~english Content string. @~chinese �ı����ݡ�
     * @param fontName @~english Content font name. @~chinese �ı��������ơ�
     * @param fontSize @~english Content font size. @~chinese �ı������С��
     * @return @~english True if initialize scucess, false otherwise. @~chinese True������ʼ���ɹ�����֮ʧ�ܡ�
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);

    
    /**
     * @~english Create a RichElementText with various arguments.
     * @~chinese ͨ�������������һ��RichElementText�ࡣ
     * @param tag @~english A integer tag value. @~chinese ��ǩֵ��
     * @param color @~english A color in Color3B. @~chinese ��ɫֵ��
     * @param opacity @~english A opacity in GLubyte. @~chinese ��͸���ȡ�
     * @param text @~english Content string. @~chinese �ı����ݡ�
     * @param fontName @~english Content font name. @~chinese �ı��������ơ�
     * @param fontSize @~english Content font size. @~chinese �ı������С��
     * @return @~english RichElementText instance. @~chinese ���ı���ʵ����
     */
    static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
    friend class RichText;
    
};
    
/** @class RichElementImage
*@brief @~english Rich element for displaying images.

 @~chinese ������ʾͼƬ��RichElementImage��
*/
class CC_GUI_DLL RichElementImage : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese Ĭ�Ϲ�����
     * @js ctor
     * @lua new
     *
     */
    RichElementImage(){_type = Type::IMAGE;};

    
    /**
     * @~english Default destructor.
     * @~chinese Ĭ��������
     * @js NA
     * @lua NA
     */
    virtual ~RichElementImage(){};

    
    /**
     * @~english Initialize a RichElementImage with various arguments.
     * @~chinese ͨ�����������ʼ��һ��RichElementImage�ࡣ
     * @param tag @~english A integer tag value. @~chinese ��ǩֵ��
     * @param color @~english A color in Color3B. @~chinese ��ɫֵ��
     * @param opacity @~english A opacity in GLubyte. @~chinese ��͸���ȡ�
     * @param filePath @~english A image file name. @~chinese ͼƬ�ļ�����
     * @return @~english True if initialize success, false otherwise. @~chinese True������ʼ���ɹ�����֮ʧ�ܡ�
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);

    
    /**
     * @~english Create a RichElementImage with various arguments.
     * @~chinese ͨ�������������һ��RichElementImage�ࡣ
     * @param tag @~english A integer tag value. @~chinese ��ǩֵ��
     * @param color @~english A color in Color3B. @~chinese ��ɫֵ��
     * @param opacity @~english A opacity in GLubyte. @~chinese ��͸���ȡ�
     * @param filePath @~english A image file name. @~chinese ͼƬ�ļ�����
     * @return @~english A RichElementImage instance. @~chinese һ��RichElementImageʵ����
     */
    static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
protected:
    std::string _filePath;
    Rect _textureRect;
    int _textureType;
    friend class RichText;
};
    
/** @class RichElementCustomNode
*@brief @~english Rich element for displaying custom node type.

 @~chinese ������ʾ�Զ���ڵ����͵�RichElementCustomNode��
*/
class CC_GUI_DLL RichElementCustomNode : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese Ĭ�Ϲ�����
     * @js ctor
     * @lua new
     */
    RichElementCustomNode(){_type = Type::CUSTOM;};

    
    /**
     * @~english Default destructor.
     * @~chinese Ĭ��������
     * @js NA
     * @lua NA
     */
    virtual ~RichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};

    
    /**
     * @~english Initialize a RichElementCustomNode with various arguments.
     * @~chinese ͨ�����������ʼ��һ��RichElementCustomNode�ࡣ
     * @param tag @~english A integer tag value. @~chinese ��ǩֵ��
     * @param color @~english A color in Color3B. @~chinese ��ɫֵ��
     * @param opacity @~english A opacity in GLubyte. @~chinese ��͸���ȡ�
     * @param customNode @~english A custom node pointer. @~chinese �Զ���ڵ�ָ�롣
     * @return @~english True if initialize success, false otherwise. @~chinese True������ʼ���ɹ�����֮ʧ�ܡ�
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    
    /**
     * @~english Create a RichElementCustomNode with various arguments.
     * @~chinese ͨ�������������һ��RichElementCustomNode�ࡣ
     * @param tag @~english A integer tag value. @~chinese ��ǩֵ��
     * @param color @~english A color in Color3B. @~chinese ��ɫֵ��
     * @param opacity @~english A opacity in GLubyte. @~chinese ��͸���ȡ�
     * @param customNode @~english A custom node pointer. @~chinese �Զ���ڵ�ָ�롣
     * @return @~english A RichElementCustomNode instance. @~chinese True������ʼ���ɹ�����֮ʧ�ܡ�
     */
    static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
protected:
    Node* _customNode;
    friend class RichText;
};
    
/**
*@brief @~english A container for displaying various RichElements.
 We could use it to display texts with images easily.

 @~chinese һ����ʾ���RichElement�������ࡣ
 ���ǿ���ʹ������������ʾ��ͼƬ���ı���
*/
class CC_GUI_DLL RichText : public Widget
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese Ĭ�Ϲ�����
     * @js ctor
     * @lua new
     */
    RichText();
    
    /**
     * @~english Default destructor.
     * @~chinese Ĭ��������
     * @js NA
     * @lua NA
     */
    virtual ~RichText();
    
    /**
     * @~english Create a empty RichText.
     * @~chinese ����һ���յ�RichText��
     * @return @~english RichText instance. @~chinese RichTextʵ����
     */
    static RichText* create();
    
    /**
     * @~english Insert a RichElement at a given index.
     * @~chinese ��ָ��λ�ò���һ��RichElement��
     * @param element @~english A RichElement type. @~chinese һ��RichElement�ࡣ
     * @param index @~english A given index. @~chinese ����ֵ��
     */
    void insertElement(RichElement* element, int index);
    
    /**
     * @~english Add a RichElement at the end of RichText.
     * @~chinese ������������һ��RichElement��
     * @param element @~english A RichElement instance. @~chinese һ��RichElement�ࡣ
     */
    void pushBackElement(RichElement* element);
    
    /**
     * @~english Remove a RichElement at a given index.
     * @~chinese �Ƴ�ָ��λ�õ�RichElement��
     * @param index @~english A integer index value. @~chinese ����ֵ��
     */
    void removeElement(int index);
    
    /**
     * @~english Remove specific RichElement.
     * @~chinese �Ƴ�һ��RichElement��
     * @param element @~english A RichElement type. @~chinese һ��RichElement��ָ�롣
     */
    void removeElement(RichElement* element);
    
    /**
     * @~english Set vertical space between each RichElement.
     * @~chinese ����ÿ��RichElement�Ĵ�ֱ�����
     * @param space @~english Point in float. @~chinese ��ֱ���ֵ��
     */
    void setVerticalSpace(float space);
    
    /**
     * @~english Rearrange all RichElement in the RichText.
     * It's usually called internally.
     * @~chinese �����������е�RichElement��
     * ���ڲ����á�
     */
    void formatText();

    //override functions.
    virtual void setAnchorPoint(const Vec2 &pt) override;
    virtual Size getVirtualRendererSize() const override;
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void adaptRenderers() override;

    virtual void initRenderer() override;
    void pushToContainer(Node* renderer);
    void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B& color, GLubyte opacity);
    void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity);
    void handleCustomRenderer(Node* renderer);
    void formarRenderers();
    void addNewLine();
protected:
    bool _formatTextDirty;
    Vector<RichElement*> _richElements;
    std::vector<Vector<Node*>*> _elementRenders;
    float _leftSpaceWidth;
    float _verticalSpace;
    Node* _elementRenderersContainer;
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIRichText__) */
