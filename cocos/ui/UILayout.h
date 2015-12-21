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

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN

class DrawNode;
class LayerColor;
class LayerGradient;
class StencilStateManager;
struct CC_DLL ResourceData;

namespace ui {
    
class LayoutManager;
class Scale9Sprite;

/**
 * @brief @~english Layout interface for creating LayoutManger and do actual layout.
 * @~chinese ���ֽ��棬���ڴ���LayoutManger���֡�
 * @js NA
 */
class CC_GUI_DLL LayoutProtocol
{
public:
    /**
     * @brief @~english Default constructor.
     * @~chinese Ĭ�Ϲ��캯����
     */
    LayoutProtocol(){}

    /**
     * @brief @~english Default destructor.
     * @~chinese Ĭ�ϵ�����������
     */
    virtual ~LayoutProtocol(){}

    /**
     * @brief @~english Create a custom layout manager.
     * @~chinese ����һ�����ֹ�������
     * 
     * @return @~english A LayoutManager descendants instance.
     * @~chinese LayoutManager���ʵ����
     */
    virtual LayoutManager* createLayoutManager() = 0;
    
    /**
     * @brief @~english Return the content size of layout.
     * @~chinese ����Layout��content��С��
     * 
     * @return @~english A content size in Size.
     * @~chinese һ��content�ߴ硣
     */
    virtual Size getLayoutContentSize()const = 0;
    
    /**
     * @brief @~english Get all elements of the layout.
     * @~chinese ��ȡLayout�����е�Ԫ�ء�
     * 
     * @return @~english A vector of Node pointers.
     * @~chinese һ�������ڵ��ָ������顣
     */
    virtual const Vector<Node*>& getLayoutElements()const = 0;
    
    /**
     * @brief @~english The main function to do the layout job.
     *  Different layout manager should implement its own layout algorithm.
     *
     * @~chinese ���ֹ��ܵ���Ҫ������
     * ��ͬ�Ĳ��ֹ�����Ӧ��ʵ���Լ��Ĳ����㷨��
     * 
     */
    virtual void doLayout() = 0;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef RELATIVE
#undef RELATIVE
#endif
#endif

/**
 * @brief @~english A container for holding a few child widgets.
 * The child widgets could be rearranged according to the layout type and it also enables clipping, set background image and color.
 *
 * There are mainly four types of layout:
 * - Absolute layout: This the default layout type, child elements are arranged by their absolute position.
 * - Horizontal layout: child elements are arranged horizontally.
 * - Vertical layout: child elements are arranged vertically.
 * - Relative layout: child elements are arranged relative to certain rules.
 *
 * @~chinese һ�������ؼ���������
 * �ӽڵ���Ը��ݲ���������������,�������Կ�������,���ñ���ͼ�����ɫ��
 * 
 * ��Ҫ���������͵Ĳ���:
 * - ���Բ���:���Ĭ�ϵĲ������͡���Ԫ�ذ��վ���λ�����С�
 * - ˮƽ����:��Ԫ��ˮƽ���С�
 * - ��ֱ����:��Ԫ�ش�ֱ���С�
 * - ��Բ���:��Ԫ�������һ���Ĺ������С�
 * 
 */
class CC_GUI_DLL Layout : public Widget, public LayoutProtocol
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * @~english
     * Layout type, default is ABSOLUTE.
     * @~chinese 
     * ��������,Ĭ���Ǿ���(ABSOLUTE)���֡�
     */
    enum class Type
    {
        ABSOLUTE,
        VERTICAL,
        HORIZONTAL,
        RELATIVE
    };
    
    /**
     * @~english
     * Clipping Type, default is STENCIL.
     * @~chinese 
     * ��������,Ĭ����STENCIL��
     */
    enum class ClippingType
    {
        STENCIL,
        SCISSOR
    };
    
    /**
     * @~english
     * Background color type, default is NONE.
     * @~chinese 
     * ������ɫ����, Ĭ����NONE.
     */
    enum class BackGroundColorType
    {
        NONE,
        SOLID,
        GRADIENT
    };
    
    /**
     * @~english
     * Default constructor
     * @~chinese 
     * Ĭ�Ϲ��캯��
     * @js ctor
     * @lua new
     */
    Layout();
    
    /**
     * @~english
     * Default destructor
     * @~chinese 
     * Ĭ�ϵ���������
     * @js NA
     * @lua NA
     */
    virtual ~Layout();
    
    /**
     * @~english
     * Create a empty layout.
     * @~chinese 
     * ����һ���յ�layout��
     */
    static Layout* create();
    
    /**
     * @~english
     * Sets a background image for layout.
     * @~chinese 
     * ����layout�ı���ͼ��
     * 
     * @param fileName @~english image file path.
     * @~chinese ͼ���ļ�·����
     * @param texType @see TextureResType. 
     */
    void setBackGroundImage(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * @~english
     * Sets a background image capInsets for layout, it only affects the scale9 enabled background image
     * @~chinese 
     * ����layout������capInsets,��ֻ�ڿ���scale9��Ӱ�챳��ͼ����Ⱦ
     * 
     * @param capInsets @~english The capInsets in Rect.
     * @~chinese capInsets�ľ��Ρ�
     * 
     */
    void setBackGroundImageCapInsets(const Rect& capInsets);
    
    /**
     * @~english
     * Query background image's capInsets size.
     * @~chinese 
     * ��ѯ����ͼ���capInsets��
     * @return @~english The background image capInsets.
     * @~chinese ����ͼ���capInsets��
     */
    const Rect& getBackGroundImageCapInsets()const;
    
    /**
     * @~english
     * Sets Color Type for layout's background
     * @~chinese 
     * ���ò��ֵı�����ɫ����
     * 
     * @param type   @see `BackGroundColorType`
     */
    void setBackGroundColorType(BackGroundColorType type);
    
    /**
     * @~english
     * Query the layout's background color type.
     * @~chinese 
     * ��ѯ���ֵı�����ɫ���͡�
     * @return @~english The layout's background color type.
     * @~chinese ���ֵı�����ɫ���͡�
     */
    BackGroundColorType getBackGroundColorType()const;
    
    /**
     * @~english
     * Enable background image scale9 rendering.
     * @~chinese 
     * ��������ͼ��scale9����Ⱦģʽ��
     * 
     * @param enabled @~english True means enable scale9 rendering for background image, false otherwise.
     * @~chinese ����true������false��ر�scale9��Ⱦ
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    /**
     * @~english
     * Query background image scale9 enable status.
     * @~chinese 
     * ��ѯ����ͼ��scale9����״̬��
     * @return @~english Whether background image is scale9 enabled or not.
     * @~chinese �Ƿ�����scale9����ͼ��
     */
    bool isBackGroundImageScale9Enabled()const;
    
    /**
     * @~english
     * Set background color for layout
     * The color only applies to layout when it's color type is BackGroundColorType::SOLID
     *
     * @~chinese 
     * ����layout�ı�����ɫ
     * ������ɫ����ΪBackGroundColorType::SOLID��ʱ�򣬲Ż�Ӱ��Layout
     * 
     * @param color @~english Color in Color3B.
     * @~chinese Color3B���͵���ɫ��
     */
    void setBackGroundColor(const Color3B &color);
    
    /**
     * @~english
     * Query the layout's background color.
     * @~chinese 
     * ��ѯ���ֵı�����ɫ��
     *
     * @return @~english Background color in Color3B.
     * @~chinese Color3B���͵ı�����ɫ��
     */
    const Color3B& getBackGroundColor()const;
    
    /**
     * @~english
     * Set start and end background color for layout.
     * This setting only take effect when the layout's  color type is BackGroundColorType::GRADIENT
     * @~chinese 
     * Ϊ�������ÿ�ʼ�ͽ����ı�����ɫ��
     * ������ֻ�����ֵ���ɫ������BackGroundColorType::GRADIENTʱ��Ч
     * 
     * @param startColor @~english Color value in Color3B.
     * @~chinese Color3B���͵���ɫ��
     * @param endColor @~english Color value in Color3B.
     * @~chinese Color3B���͵���ɫ��
     */
    void setBackGroundColor(const Color3B &startColor, const Color3B &endColor);
    
    /**
     * @~english
     * Get the gradient background start color.
     * @~chinese 
     * ��ȡ���䱳����ɫ��ʼ��ֵ��
     * @return @~english Gradient background start color value.
     * @~chinese ���䱳����ɫ��ʼ��ֵ��
     */
    const Color3B& getBackGroundStartColor()const;
    
    /**
     * @~english
     * Get the gradient background end color.
     * @~chinese 
     * ��ȡ���䱳����ɫ�Ľ���ֵ��
     * @return @~english Gradient background end color value.
     * @~chinese ���䱳����ɫ������ֵ��
     */
    const Color3B& getBackGroundEndColor()const;
    
    /**
     * @~english
     * Sets background color opacity of layout.
     * @~chinese 
     * ���ò��ֵı�����ɫ��͸���ȡ�
     * 
     * @param opacity @~english The opacity in `GLubyte`.
     * @~chinese ��GLubyte����͸���ȡ�
     */
    void setBackGroundColorOpacity(GLubyte opacity);
    
    /**
     * @~english
     * Get the layout's background color opacity.
     * @~chinese 
     * ��ȡ���ֵı�����ɫ��͸���ȡ�
     * @return @~english Background color opacity value.
     * @~chinese ������ɫ�Ĳ�͸��ֵ��
     */
    GLubyte getBackGroundColorOpacity()const;
    
    /**
     * @~english
     * Sets background color vector for layout.
     * This setting only take effect when layout's color type is BackGroundColorType::GRADIENT
     * @~chinese 
     * ���ò��ֵı�����ɫʸ����
     * ������ֻ�����ֵ���ɫ������BackGroundColorType::GRADIENTʱ��Ч
     * 
     * @param vector @~english The color vector in `Vec2`.
     * @~chinese Vec2���͵���ɫ������
     */
    void setBackGroundColorVector(const Vec2 &vector);
    
    /**
     * @~english
     * Get the layout's background color vector.
     * @~chinese 
     * ��ȡlayout�ı�����ɫ������
     * @return @~english Background color vector.
     * @~chinese ������ɫ������
     */
    const Vec2& getBackGroundColorVector()const;
    
    /**
     * @~english
     * Set layout's background image color.
     * @~chinese 
     * ����layout����ͼ�����ɫ��
     * @param color @~english Background color value in `Color3B`.
     * @~chinese Color3B���͵ı�����ɫֵ��
     */
    void setBackGroundImageColor(const Color3B& color);
    
    /**
     * @~english
     * Set opacity of background image.
     * @~chinese 
     * ���ñ���ͼ��Ĳ�͸���ȡ�
     * @param opacity @~english Background image opacity in GLubyte.
     * @~chinese ����ͼ����GLubyte�Ĳ�͸���ȡ�
     */
    void setBackGroundImageOpacity(GLubyte opacity);
    
    /**
     * @~english
     * Get color of layout's background image.
     * @~chinese 
     * �õ�layout�ı���ͼ����ɫ��
     *
     * @return @~english Layout's background image color.
     * @~chinese layout�ı���ͼ�����ɫ��
     */
    const Color3B& getBackGroundImageColor()const;
    
    /**
     * @~english
     * Get the opacity of layout's background image.
     * @~chinese 
     * ��ȡlayout�ı���ͼ��͸���ȡ�
     *
     * @return @~english The opacity of layout's background image.
     * @~chinese layout����ͼƬ�Ĳ�͸����.
     */
    GLubyte getBackGroundImageOpacity()const;
    
    /**
     * @~english
     * Remove the background image of layout.
     * @~chinese 
     * ɾ��layout�ı���ͼ��
     */
    void removeBackGroundImage();
    
    /**
     * @~english
     * Gets background image texture size.
     * @~chinese 
     * ��ȡ����ͼ�������С��
     * 
     * @return @~english background image texture size.
     * @~chinese ����ͼ�������С��
     */
    const Size& getBackGroundImageTextureSize() const;
    
    /**
     * @~english
     * Toggle layout clipping.
     * If you do need clipping, you pass true to this function.
     * @~chinese 
     * �л����ּ��á�
     * �������Ҫ�ü�,����Ҫ����true�����������
     * 
     * @param enabled @~english Pass true to enable clipping, false otherwise.
     * @~chinese ����true�����ü�ģʽ��false��ر�
     */
    virtual void setClippingEnabled(bool enabled);
    
    
    /**
     * @~english
     * Change the clipping type of layout.
     * On default, the clipping type is `ClippingType::STENCIL`.
     * @~chinese 
     * �ı�layout�ļ������͡�
     * ��Ĭ�������,���������ǡ�ClippingType:STENCIL����
     * @see `ClippingType`
     * @param type @~english The clipping type of .
     * @~chinese layout�ļ������͡�
     */
    void setClippingType(ClippingType type);

    /**
     * @see `setClippingType(ClippingType)`
     */
    ClippingType getClippingType()const;
    
    /**
     * @~english
     * Gets if layout is clipping enabled.
     * @~chinese 
     * ��ȡlayout�Ƿ����˼��á�
     * 
     * @return @~english if layout is clipping enabled.
     * @~chinese �Ƿ������˲����Ǽ��á�
     */
    virtual bool isClippingEnabled()const;
    
    /**
     * @~english
     * Returns the "class name" of widget.
     * @~chinese 
     * �������������
     */
    virtual std::string getDescription() const override;
    
    /**
     * @~english
     * Change the layout type.
     * @~chinese 
     * �ı䲼�����͡�
     *@param type @~english Layout type.
     * @~chinese �������͡�
     */
    virtual void setLayoutType(Type type);
    
    /**
     * @~english
     * Query layout type.
     * @~chinese 
     * ��ѯlayout���͡�
     * @return @~english Get the layout type.
     * @~chinese layout����
     */
    virtual  Type getLayoutType() const;

    
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    /**
     * @~english
     * Adds a child to the container with z order and tag
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * ����z order�ͱ�ǩ���һ���ӽڵ㵽����
     * ����ӽڵ㱻��ӵ�һ���������еĽڵ�,��onEnter���͡�onEnterTransitionDidFinish����������ִ�С�
     * 
     * @param child @~english A child node
     * @~chinese һ���ӽڵ�
     * @param localZOrder @~english Z order for drawing priority. Please refer to setLocalZOrder(int)
     * @~chinese z order�������ȼ��������setLocalZOrder(int)
     * @param tag @~english A integer  to identify the node easily. Please refer to setTag(int)
     * @~chinese һ������������ʶ��ڵ㡣�����setTag(int)
     */
    virtual void addChild(Node* child, int localZOrder, int tag) override;
    virtual void addChild(Node* child, int localZOrder, const std::string &name) override;
    
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    virtual void removeChild(Node* child, bool cleanup = true) override;
    
    /**
     * @~english
     * Removes all children from the container with a cleanup.
     *
     * @~chinese 
     * ��������ɾ�����е��ӽڵ㡣
     * 
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren() override;

    /**
     * @~english
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * ��������ɾ�������ӽڵ㣬������Ӧ�������� - ���ݲ�ͬ�Ĳ��������������������е�actions��
     * 
     * @param cleanup @~english true if all running actions on all children nodes should be cleanup, false otherwise.
     * @~chinese �������true�����������ӽڵ��actions��false������
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;

    /**
     * @~english
     * force refresh widget layout
     * @~chinese 
     * ǿ��ˢ�¿ؼ��Ĳ���
     */
    virtual void forceDoLayout();
    
    /**
     * @~english
     * request to refresh widget layout
     * @~chinese 
     * ����ˢ�¿ؼ��Ĳ���
     */
    virtual void requestDoLayout();
    
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    
    /**
     * @lua NA
     */
    virtual void onExit() override;
    
    /**
     * @~english
     * If a layout is loop focused which means that the focus movement will be inside the layout
     * @~chinese 
     * ���һ��������ѭ����ȡ���㣬����ζ�Ž�����layout���ƶ�
     * @param loop @~english pass true to let the focus movement loop inside the layout
     * @~chinese ����true�������ڲ��������ѭ������
     */
    void setLoopFocus(bool loop);
    
    /**
     * @return @~english If focus loop is enabled, then it will return true, otherwise it returns false. The default value is false.
     * @~chinese ��������˽���ѭ��,��ô��������true,���򷵻�false��Ĭ��ֵ��false��
     */
    bool isLoopFocus()const;
    
    /**
     * @param pass @~english To specify whether the layout pass its focus to its child
     * @~chinese Ҫָ��layout�Ƿ񴫵ݽ��㵽�����ӽڵ���
     */
    void setPassFocusToChild(bool pass);
    
    /**
     * @return @~english To query whether the layout will pass the focus to its children or not. The default value is true
     * @~chinese ��ѯ�����Ƿ�ᴫ�ݽ��㵽�ӽڵ��ϡ�Ĭ��ֵΪtrue
     */
    bool isPassFocusToChild()const;
    
    /**
     * @~english
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.
     *  If the widget is not in a layout, it will return itself
     * @~chinese 
     * ��һ���ؼ�����layout�У�����Ե���������������ָ���ķ����е���һ������ؼ���
     * ���û���ڲ��ֿؼ�,���������Լ�
     * @param direction @~english the direction to look for the next focused widget in a layout
     * @~chinese Ѱ����һ�������ϵĽ���ؼ�
     * @param current  @~english the current focused widget
     * @~chinese ��ǰ�Ľ���ؼ�
     * @return @~english the next focused widget in a layout
     * @~chinese layout�е���һ������ؼ�
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current) override;
    
    /**
     * @~english
     * To specify a user-defined functor to decide which child widget of the layout should get focused
     * @~chinese 
     * Ҫָ��һ���û�����ĺ���������Щ���ֵ��ӽڵ�ؼ�Ӧ�õõ�����
     * @param FocusDirection @~english the finding direction
     * @~chinese ���ҵķ���
     * @param this @~english previous focused widget
     * @~chinese ֮ǰ�Ľ���ؼ�
     * @return @~english return the index of widget in the layout
     * @~chinese �����ҵ��Ŀؼ�
     */
    std::function<int(FocusDirection, Widget*)> onPassFocusToChild;
    
    /** 
     * Override function. Set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true. 
     * @param mask Mask being set
     * @param applyChildren If true call this function recursively from this node to its children.
     */
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

    ResourceData getRenderFile();

CC_CONSTRUCTOR_ACCESS:
    //override "init" method of widget.
    virtual bool init() override;
    
protected:
    //override "onSizeChanged" method of widget.
    virtual void onSizeChanged() override;
    
    //init background image renderer.
    void addBackGroundImage();
    
    void supplyTheLayoutParameterLackToChild(Widget* child);
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    
    void stencilClippingVisit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    void scissorClippingVisit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    
    void setStencilClippingSize(const Size& size);
    const Rect& getClippingRect();
    
    virtual void doLayout()override;
    virtual LayoutManager* createLayoutManager()override;
    virtual Size getLayoutContentSize()const override;
    virtual const Vector<Node*>& getLayoutElements()const override;
    
    //clipping
    void onBeforeVisitStencil();
    void onAfterDrawStencil();
    void onAfterVisitStencil();

    /**
     * @~english draw fullscreen quad to clear stencil bits
     * @~chinese ������Ļ�ĸ���ȥ���ģ��
     */
    void drawFullScreenQuadClearStencil();
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    void updateBackGroundImageColor();
    void updateBackGroundImageOpacity();
    void updateBackGroundImageRGBA();
    
    /**
     * @~english
     * get the content size of the layout, it will accumulate all its children's content size
     * @~chinese 
     * ���layout�����ݵĴ�С�����������������ӽڵ�����ݴ�С
     */
    Size getLayoutAccumulatedSize() const;
    
    /**
     * @~english
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child 
     * will get the focus.  The current algorithm to determine which child will get focus is nearest-distance-priority algorithm
     * @~chinese 
     * ��layout�õ����㣬���������ַ�����ȷ�����ݽ��㵽��Щ�ӽڵ�
     * ���õ��Ľ��㡣Ŀǰ�����ݾ��������㷨��ȷ����Щ�ӽڵ㽫�õ�����
     * @param dir @~english next focused widget direction
     * @~chinese ���������ҽ���ķ���
     * @return @~english The index of child widget in the container
     * @~chinese �ӿؼ��������е�����
     */
     int findNearestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * @~english
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child
     * will get the focus.  The current algorithm to determine which child will get focus is farthest-distance-priority algorithm
     * @~chinese 
     * ��layout�õ����㣬���������ַ�����ȷ�����ݽ��㵽��Щ�ӽڵ�
     * ���õ��Ľ��㡣Ŀǰ�����ݾ��������㷨��ȷ����Щ�ӽڵ㽫�õ�����
     * @param dir @~english next focused widget direction
     * @~chinese ���������ҽ���ķ���
     * @return @~english The index of child widget in the container
     * @~chinese �ӿؼ��������е�����
     */
    int findFarthestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * @~english
     * calculate the nearest distance between the baseWidget and the children of the layout
     * @~chinese 
     * ��������ؼ���layout���ӽڵ�֮����������
     *
     * @param the @~english base widget which will be used to calculate the distance between the layout's children and itself
     * @~chinese �������ڼ���layout���ӽڵ������֮��ľ���Ļ����ؼ�
     *
     * @return @~english return the nearest distance between the baseWidget and the layout's children
     * @~chinese ���ػ����ؼ��������layout���ӽڵ�֮��ľ���
     */
    float calculateNearestDistance(Widget* baseWidget);
    
    /**
     * @~english
     * calculate the farthest distance between the baseWidget and the children of the layout
     * @~chinese 
     * ��������ؼ���layout���ӽڵ�֮����������
     *
     * @param the @~english base widget which will be used to calculate the distance between the layout's children and itself
     * @~chinese �������ڼ���layout���ӽڵ������֮��ľ���Ļ����ؼ�
     *
     * @return @~english return the farthest distance between the baseWidget and the layout's children
     * @~chinese ���ػ����ؼ��������layout���ӽڵ�֮��ľ���
     */
    float calculateFarthestDistance(Widget* baseWidget);
    
    /**
     * @~english
     *  when a layout pass the focus to it's child, use this method to determine which algorithm to use, nearest or farthest distance algorithm or not
     * @~chinese 
     * ��һ�����ֽ����㴫�ݸ������ӽڵ�,���ʹ�����ַ�����ȷ��ʹ���ĸ��㷨���ݣ��������Զ�ľ����㷨��
     */
    void findProperSearchingFunctor(FocusDirection dir, Widget* baseWidget);
    
    /**
     * @~english
     * find the first non-layout widget in this layout
     * @~chinese 
     * ������������е�һ������ layout ���͵Ŀؼ�
     */
    Widget *findFirstNonLayoutWidget();
    
    /**
     * @~english
     * find the first focus enabled widget index in the layout, it will recursive searching the child widget
     * @~chinese 
     * ������layout�еĵ�һ�����ý���Ŀؼ�����������ݹ������ӿؼ�
     */
    int findFirstFocusEnabledWidgetIndex();
    
    /**@~english
     * find a focus enabled child Widget in the layout by index
     * @~chinese 
     * �������ҵ�һ�����ý�����ӿؼ�
     */
    Widget* findFocusEnabledChildWidgetByIndex(ssize_t index);
    
    /**
     * @~english
     * get the center point of a widget in world space
     * @~chinese 
     * �õ�һ���ؼ�������ռ����ĵ�
     */
    Vec2 getWorldCenterPoint(Widget* node)const;
    
    /**
     * @~english
     * this method is called internally by nextFocusedWidget. When the dir is Right/Down, then this method will be called
     * @~chinese 
     * nextFocusedWidget�ڲ����ô˷�������dir������/���£���˷�����������
     * @param dir  @~english the direction.
     * @~chinese ����
     * @param current  @~english the current focused widget
     * @~chinese ��ǰ����Ŀؼ�
     * @return @~english the next focused widget
     * @~chinese ��һ������ؼ�
     */
    Widget* getNextFocusedWidget(FocusDirection direction,Widget *current);
    
    /**
     * @~english
     * this method is called internally by nextFocusedWidget. When the dir is Left/Up, then this method will be called
     * @~chinese 
     * nextFocusedWidget�ڲ����ô˷�������dir����/�ϣ���ô��������ᱻ����
     * @param dir  @~english the direction.
     * @~chinese ����
     *@param current  @~english the current focused widget
     * @~chinese ��ǰ����ؼ�
     *@return @~english the next focused widget
     * @~chinese ��һ������ؼ�
     */
    Widget* getPreviousFocusedWidget(FocusDirection direction, Widget *current);
    
    /**
     * @~english
     * find the nth element in the _children array. Only the Widget descendant object will be returned
     * @~chinese 
     * �ҵ�_children��n��Ԫ�ء�ֻ�м̳���Widget�Ķ���ᱻ����
     * @param index  @~english The index of a element in the _children array
     * @~chinese _children�����е�һ��Ԫ�ص�����
     */
    Widget* getChildWidgetByIndex(ssize_t index)const;

    /**
     * @~english
     * whether it is the last element according to all their parents
     * @~chinese 
     * �Ƿ����丸�ڵ�����һ��Ԫ��
     */
    bool  isLastWidgetInContainer(Widget* widget, FocusDirection direction)const;
    
    /**
     * @~english Lookup any parent widget with a layout type as the direction,
     * if the layout is loop focused, then return true, otherwise
     * It returns false
     * @~chinese �����κθ��ؼ��Ĳ������͡�����,
     * ���������ѭ������,�򷵻�true,���򷵻�false
     */
    bool  isWidgetAncestorSupportLoopFocus(Widget* widget, FocusDirection direction)const;
    
    /**
     * @~english
     * pass the focus to the layout's next focus enabled child
     * @~chinese 
     * ���ݽ������һ����ȡ������ӽڵ�
     */
    Widget* passFocusToChild(FocusDirection direction, Widget* current);
    
    /**
     * @~english
     * If there are no focus enabled child in the layout, it will return false, otherwise it returns true
     * @~chinese 
     * �����layout�н������õ��ӽڵ�û�н��㣬�򷵻�false�����򷵻�true
     */
    bool checkFocusEnabledChild()const;
    
protected:
    
    //background
    bool _backGroundScale9Enabled;
    Scale9Sprite* _backGroundImage;
    std::string _backGroundImageFileName;
    Rect _backGroundImageCapInsets;
    BackGroundColorType _colorType;
    TextureResType _bgImageTexType;
    Size _backGroundImageTextureSize;
    Color3B _backGroundImageColor;
    GLubyte _backGroundImageOpacity;

    LayerColor* _colorRender;
    LayerGradient* _gradientRender;
    Color3B _cColor;
    Color3B _gStartColor;
    Color3B _gEndColor;
    Vec2 _alongVector;
    GLubyte _cOpacity;
    
    //clipping
    bool _clippingEnabled;
    Type _layoutType;
    ClippingType _clippingType;
    DrawNode* _clippingStencil;
    bool _scissorOldState;
    Rect _clippingOldRect;
    Rect _clippingRect;
    Layout* _clippingParent;
    bool _clippingRectDirty;
    
    //clipping
    StencilStateManager *_stencileStateManager;

    GroupCommand _groupCommand;
    CustomCommand _beforeVisitCmdStencil;
    CustomCommand _afterDrawStencilCmd;
    CustomCommand _afterVisitCmdStencil;
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
    
    bool _doLayoutDirty;
    bool _isInterceptTouch;
    
    //whether enable loop focus or not
    bool _loopFocus;
    //on default, it will pass the focus to the next nearest widget
    bool _passFocusToChild;
     //when finding the next focused widget, use this variable to pass focus between layout & widget
    bool _isFocusPassing;
};
    
}
NS_CC_END
// end of ui group
/// @}
#endif /* defined(__Layout__) */
