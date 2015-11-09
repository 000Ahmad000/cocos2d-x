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

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "2d/CCProtectedNode.h"
#include "ui/UILayoutParameter.h"
#include "ui/GUIDefine.h"
#include "ui/GUIExport.h"
#include "base/CCMap.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class EventListenerTouchOneByOne;
class Camera;

namespace ui {
    class LayoutComponent;

/**@~english
 * Touch event type.
 * @~chinese 
 * �����¼����͡�
 *@deprecated use `Widget::TouchEventType` instead
 */
typedef enum
{
    TOUCH_EVENT_BEGAN,
    TOUCH_EVENT_MOVED,
    TOUCH_EVENT_ENDED,
    TOUCH_EVENT_CANCELED
}TouchEventType;
    
/**@~english
 * Touch event callback.
 * @~chinese 
 * �����¼��ص���
 *@deprecated use `Widget::ccWidgetTouchCallback` instead
 */
typedef void (Ref::*SEL_TouchEvent)(Ref*,TouchEventType);
#define toucheventselector(_SELECTOR) (SEL_TouchEvent)(&_SELECTOR)


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif
#endif

/**
 *@brief @~english Base class for all ui widgets.
 * This class inherent from `ProtectedNode` and `LayoutParameterProtocol`.
 * If you want to implements your own ui widget, you should subclass it.
 * @~chinese ����UI�ؼ��Ļ��ࡣ
 * ����̳���`ProtectedNode`��`LayoutParameterProtocol`��
 * �������ʵ���Լ���UI�ؼ�����Ӧ�ü̳�����ࡣ
 */
class CC_GUI_DLL Widget : public ProtectedNode, public LayoutParameterProtocol
{
public:
    /**@~english
     * Widget focus direction.
     * @~chinese 
     * �ؼ����㷽��
     */
    enum class FocusDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    
    /**@~english
     * Widget position type for layout.
     * @~chinese 
     * ����ϵͳ�еĿؼ�λ�����͡�
     */
    enum class PositionType
    {
        ABSOLUTE,
        PERCENT
    };
    
    /**@~english
     * Widget size type for layout.
     * @~chinese 
     * ����ϵͳ�еĿؼ��ߴ����͡�
     */
    enum class SizeType
    {
        ABSOLUTE,
        PERCENT
    };
    
    /**@~english
     * Touch event type.
     * @~chinese 
     * �����¼����͡�
     */
    enum class TouchEventType
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELED
    };
    
    /**@~english
     * Texture resource type.
     * - LOCAL: It means the texture is loaded from image.
     * - PLIST: It means the texture is loaded from texture atlas.
     * @~chinese 
     * ������Դ���͡�
     * - LOCAL������ζ������Ӷ���ͼ����ء�
     * - PLIST������ζ�����������ͼ���м��ء�
     */
    enum class TextureResType
    {
        LOCAL = 0,
        PLIST = 1
    };
    
    /**@~english
     * Widget bright style.
     * @~chinese 
     * �ؼ��ĸ������ԡ�
     */
    enum class BrightStyle
    {
        NONE = -1,
        NORMAL,
        HIGHLIGHT
    };

    
    /**@~english
     * Widget touch event callback.
     * @~chinese 
     * �ؼ������¼��ص���
     */
    typedef std::function<void(Ref*,Widget::TouchEventType)> ccWidgetTouchCallback;
    /**@~english
     * Widget click event callback.
     * @~chinese 
     * �ؼ�����¼��ص���
     */
    typedef std::function<void(Ref*)> ccWidgetClickCallback;
    /**@~english
     * Widget custom event callback.
     * It is mainly used together with Cocos Studio.
     * @~chinese 
     * �ؼ��û������¼��ص���
     * ����Ҫ��Cocos Studioһ��ʹ�á�
     */
    typedef std::function<void(Ref*, int)> ccWidgetEventCallback;
    /**@~english
     * Default constructor
     * @~chinese 
     * Ĭ�Ϲ��캯��
     * @js ctor
     * @lua new
     */
    Widget(void);
    
    /**@~english
     * Default destructor
     * @~chinese 
     * Ĭ�ϵ���������
     * @js NA
     * @lua NA
     */
    virtual ~Widget();
    /**@~english
     * Create and return a empty Widget instance pointer.
     * @~chinese 
     * ����������һ���յĿؼ�ʵ����ָ�롣
     */
    static Widget* create();

    /**@~english
     * Sets whether the widget is enabled
     * 
     * true if the widget is enabled, widget may be touched , false if the widget is disabled, widget cannot be touched.
     *
     * Note: If you want to change the widget's appearance to disabled state, you should also call `setBright(false)`.
     *
     * The default value is true, a widget is default to enable touch.
     *
     * @~chinese 
     * �����Ƿ������˿ؼ�
     * 
     * �������Ϊtrue�������˿ؼ�������������Ӧ�����¼����������Ϊfalse��ؼ��ǽ��õģ�������Ӧ�����¼���
     * 
     * ���ѣ��������ı�һ���ؼ������Ϊ������״̬������`setEnabled(false)`���⣬����Ҫ����`setBright(false)`��������۲���ı䡣
     * 
     * Ĭ��ֵ��true,һ���ؼ���Ĭ�����ô�����
     * 
     * @param enabled @~english Set to true to enable touch, false otherwise.
     * @~chinese ����Ϊtrue�����ô������������ô�����Ӧ��
     */
    virtual void setEnabled(bool enabled);

    /**@~english
     * Determines if the widget is enabled or not.
     *
     * @~chinese 
     * ���ؼ��Ƿ������ˡ�
     * 
     * @return @~english true if the widget is enabled, false if the widget is disabled.
     * @~chinese ��������˿ؼ�����true���ؼ��ǽ��õķ���false��
     */
    bool isEnabled() const;

    /**@~english
     * Sets whether the widget is bright
     * The default value is true, a widget is default to bright
     *
     * @~chinese 
     * ���ÿؼ��Ƿ������Ĭ��ֵ��true��������Ϊfalse����ؼ�����ǰ��ġ�
     * 
     * @param bright @~english true if the widget is bright, false if the widget is dark.
     * @~chinese ����true��ؼ��Ǹ����ģ���������false��
     */
    void setBright(bool bright);

    /**@~english
     * Determines if the widget is bright
     *
     * @~chinese 
     * ���ؿؼ��Ƿ����
     * 
     * @return @~english true if the widget is bright, false if the widget is dark.
     * @~chinese ����ؼ��Ǹ����ķ���true�����򷵻�false��
     */
    bool isBright() const;

    /**@~english
     * Sets whether the widget is touch enabled.
     *
     * The default value is false, a widget is default to touch disabled.
     *
     * @~chinese 
     * �����Ƿ���Ӧ�����¼���
     * 
     * Ĭ��ֵ��false���ؼ�Ĭ���ǽ��ô����ġ�
     * 
     * @param enabled   @~english True if the widget is touch enabled, false if the widget is touch disabled.
     * @~chinese �������true�����ô�����������á�
     */
    virtual void setTouchEnabled(bool enabled);

    /**@~english
     * To set the bright style of widget.
     *
     * @~chinese 
     * ���ÿؼ��ĸ������
     * 
     * @see BrightStyle
     *
     * @param style   @~english BrightStyle::NORMAL means the widget is in normal state, BrightStyle::HIGHLIGHT means the widget is in highlight state.
     * @~chinese BrightStyle::NORMAL��ζ�Ų���������״̬��BrightStyle::HIGHLIGHT��ζ�Ų������ڸ���״̬��
     */
    void setBrightStyle(BrightStyle style);

    /**@~english
     * Determines if the widget is touch enabled
     *
     * @~chinese 
     * ��ȡ�����Ƿ�����
     * 
     * @return @~english true if the widget is touch enabled, false if the widget is touch disabled.
     * @~chinese ������������򷵻�true�����򷵻�false��
     */
    bool isTouchEnabled() const;

    /**@~english
     * Determines if the widget is highlighted
     *
     * @~chinese 
     * ��ȡ�Ƿ������ʾ
     * 
     * @return @~english true if the widget is highlighted, false if the widget is not hignlighted .
     * @~chinese ���������ʾ�򷵻�true�����򷵻�false��
     */
    bool isHighlighted() const;

    /**@~english
     * Sets whether the widget is highlighted
     *
     * The default value is false, a widget is default to not highlighted
     *
     * @~chinese 
     * �����Ƿ������ʾ
     * 
     * Ĭ��ֵ��false���ؼ�Ĭ�ϲ�������ʾ
     * 
     * @param hilight   @~english true if the widget is hilighted, false if the widget is not hilighted.
     * @~chinese �������true�����ø�����
     */
    void setHighlighted(bool highlight);

    /**@~english
     * Gets the left boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ�����߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @deprecated use `getLeftBoundary` instead.
     * @return @~english The left boundary position of this widget.
     * @~chinese ����ؼ�����߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    CC_DEPRECATED_ATTRIBUTE float getLeftInParent(){return this->getLeftBoundary();}

    /**@~english
     * Gets the left boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ�����߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @return @~english The left boundary position of this widget.
     * @~chinese ����ؼ�����߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    float getLeftBoundary() const;

    /**@~english
     * Gets the bottom boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ��ĵױ߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @deprecated use `getBottomBoundary` instead.
     * @return @~english The bottom boundary position of this widget.
     * @~chinese ����ؼ��ĵױ߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    CC_DEPRECATED_ATTRIBUTE float getBottomInParent(){return this->getBottomBoundary();}
    /**@~english
     * Gets the bottom boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ��ĵױ߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @return @~english The bottom boundary position of this widget.
     * @~chinese ����ؼ��ĵױ߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    float getBottomBoundary() const;

    /**@~english
     * Gets the right boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ����ұ߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @deprecated use `getRightBoundary` instead.
     * @return @~english The right boundary position of this widget.
     * @~chinese ����ؼ����ұ߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    CC_DEPRECATED_ATTRIBUTE float getRightInParent(){return this->getRightBoundary();}
    /**@~english
     * Gets the right boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ����ұ߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @return @~english The right boundary position of this widget.
     * @~chinese ����ؼ����ұ߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    float getRightBoundary() const;

    /**@~english
     * Gets the top boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ����ϱ߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @deprecated use `getTopBoundary` instead.
     * @return @~english The top boundary position of this widget.
     * @~chinese ����ؼ����ϱ߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    CC_DEPRECATED_ATTRIBUTE float getTopInParent(){return this->getTopBoundary();}
    /**@~english
     * Gets the top boundary position of this widget in parent's coordination system.
     * @~chinese 
     * ��ȡ����ؼ����ϱ߽��ڸ��ڵ�����ϵ�е�λ�á�
     * @return @~english The top boundary position of this widget.
     * @~chinese ����ؼ����ϱ߽��ڸ��ڵ�����ϵ�е�λ�á�
     */
    float getTopBoundary() const;

    virtual void visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    /**@~english
     * Sets the touch event target/selector to the widget
     * @~chinese 
     * ���ô����¼�����Ӧѡ������Ŀ�ꡣ
     */
    CC_DEPRECATED_ATTRIBUTE void addTouchEventListener(Ref* target,SEL_TouchEvent selector);
    /**@~english
     * Set a callback to touch vent listener.
     * @~chinese 
     * ���ô����¼��Ļص�������
     *@param callback  @~english The callback in `ccWidgetEventCallback.`
     * @~chinese �ص�����
     */
    void addTouchEventListener(const ccWidgetTouchCallback& callback);
    
    /**@~english
     * Set a click event handler to the widget.
     * @~chinese 
     * ����һ������¼��Ļص�������
     * @param callback @~english The callback in `ccWidgetClickCallback`.
     * @~chinese �ص�������
     */
    void addClickEventListener(const ccWidgetClickCallback& callback);
    /**@~english
     * Set a event handler to the widget in order to use cocostudio editor and framework
     * @~chinese 
     * ����һ������Cocos Studio�¼�����Ļص�����
     * @param callback @~english The callback in `ccWidgetEventCallback`.
     * @~chinese �ص�������
     * @lua NA
     */
    virtual void addCCSEventListener(const ccWidgetEventCallback& callback);

    /**@~english
     * Changes the position (x,y) of the widget in OpenGL coordinates
     *
     * Usually we use p(x,y) to compose a Vec2 object.
     * The original point (0,0) is at the left-bottom corner of screen.
     *
     * @~chinese 
     * ��OpenGL����ϵ�����ÿؼ�λ��(x,y)
     * 
     * ͨ������ʹ��p(x,y)���һ��Vec2����
     * ԭ��(0,0)����Ļ�����½ǡ�
     * 
     * @param pos  @~english The position (x,y) of the widget in OpenGL coordinates
     * @~chinese �ؼ���OpenGL����ϵ�е�λ��(x,y)
     */
    virtual void setPosition(const Vec2 &pos) override;

    /**@~english
     * Set the percent(x,y) of the widget in OpenGL coordinates
     *
     * @~chinese 
     * ���ÿؼ���OpenGL����ϵ�еİٷֱ�λ��(x,y)
     * 
     * @param percent  @~english The percent (x,y) of the widget in OpenGL coordinates
     * @~chinese �ؼ���OpenGL����ϵ�еİٷֱ�λ��
     */
    void setPositionPercent(const Vec2 &percent);

    /**@~english
     * Gets the percent (x,y) of the widget in OpenGL coordinates
     *
     * @~chinese 
     * ��ȡ�ؼ���OpenGL����ϵ�еİٷֱ�λ��(x,y)
     * 
     * @see setPosition(const Vec2&)
     *
     * @return @~english The percent (x,y) of the widget in OpenGL coordinates
     * @~chinese �ؼ���OpenGL����ϵ�еİٷֱ�λ��
     */
    const Vec2& getPositionPercent();

    /**@~english
     * Changes the position type of the widget
     *
     * @~chinese 
     * ���ÿؼ���λ������
     * 
     * @see `PositionType`
     *
     * @param type  @~english the position type of widget
     * @~chinese λ������
     */
    void setPositionType(PositionType type);

    /**@~english
     * Gets the position type of the widget
     *
     * @~chinese 
     * ��ȡ�ؼ���λ������
     * 
     * @see `PositionType`
     *
     * @return @~english The position type of widget
     * @~chinese λ������
     */
    PositionType getPositionType() const;

    /**@~english
     * Sets whether the widget should be flipped horizontally or not.
     *
     * @~chinese 
     * ���ÿؼ��Ƿ�Ӧ��ˮƽ��ת��
     * 
     * @param flippedX @~english true if the widget should be flipped horizaontally, false otherwise.
     * @~chinese ����true��ؼ�ˮƽ��ת�����򲻷�ת��
     */
    virtual void setFlippedX(bool flippedX);

    /**@~english
     * Returns the flag which indicates whether the widget is flipped horizontally or not.
     *
     * It not only flips the texture of the widget, but also the texture of the widget's children.
     * Also, flipping relies on widget's anchor point.
     * Internally, it just use setScaleX(-1) to flip the widget.
     *
     * @~chinese 
     * ���ؿؼ��Ƿ�ˮƽ��ת��
     * 
     * ��������ת�ؼ�������������һ��ᷭת�ؼ������ӽڵ������
     * ���⣬��ת���ǿؼ���ê����Ƶġ�
     * �ڲ�ʵ���ϣ���ֻ��ʹ��`setScaleX(-1)`��ʵ�ַ�ת��
     * 
     * @return @~english true if the widget is flipped horizaontally, false otherwise.
     * @~chinese true��ؼ�ˮƽ��ת�����򲻷�ת��
     */
    virtual bool isFlippedX()const{return _flippedX;};

    /**@~english
     * Sets whether the widget should be flipped vertically or not.
     *
     * @~chinese 
     * ���ÿؼ��Ƿ�Ӧ��ֱ��ת��
     * 
     * @param flippedY @~english true if the widget should be flipped vertically, flase otherwise.
     * @~chinese ����true��ؼ���ֱ��ת�����򲻷�ת��
     */
    virtual void setFlippedY(bool flippedY);

    /**@~english
     * Return the flag which indicates whether the widget is flipped vertically or not.
     *
     * It not only flips the texture of the widget, but also the texture of the widget's children.
     * Also, flipping relies on widget's anchor point.
     * Internally, it just use setScaleY(-1) to flip the widget.
     *
     * @~chinese 
     * ���ؿؼ��Ƿ�ֱ��ת��
     * 
     * ��������ת�ؼ�������������һ��ᷭת�ؼ������ӽڵ������
     * ���⣬��ת���ǿؼ���ê����Ƶġ�
     * �ڲ�ʵ���ϣ���ֻ��ʹ��`setScaleY(-1)`��ʵ�ַ�ת��
     * 
     * @return @~english true if the widget is flipped vertically, flase otherwise.
     * @~chinese true��ؼ���ֱ��ת�����򲻷�ת��
     */
    virtual bool isFlippedY()const{return _flippedY;};

    /** @deprecated Use isFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated Use setFlippedX() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flipX) { setFlippedX(flipX); };
    /** @deprecated Use isFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated Use setFlippedY() instead */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flipY) { setFlippedY(flipY); };

    //override the setScale function of Node
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual void setScale(float scale) override;
    virtual void setScale(float scalex, float scaley) override;
    using Node::setScaleZ;
    virtual float getScaleX() const override;
    virtual float getScaleY() const override;
    virtual float getScale() const override;
    using Node::getScaleZ;
    
    /**@~english
     * Checks a point if in parent's area.
     * @~chinese 
     * ���һ��λ�õ��Ƿ��ڸ��ڵ������ڡ�
     * 
     * @deprecated  use `isClippingParentContainsPoint` instead.
     * @param pt @~english A point in `Vec2`.
     * @~chinese Vec2���͵�λ�õ㡣
     * @return @~english true if the point is in parent's area, flase otherwise.
     * @~chinese ��������ڸ��ڵ������ڣ�����true�����򷵻�false��
     */
    CC_DEPRECATED_ATTRIBUTE bool clippingParentAreaContainPoint(const Vec2 &pt){return this->isClippingParentContainsPoint(pt);}

    /**@~english
     * Checks a point if in parent's area.
     * @~chinese 
     * ���һ��λ�õ��Ƿ��ڸ��ڵ������ڡ�
     * 
     * @param pt @~english A point in `Vec2`.
     * @~chinese Vec2���͵�λ�õ㡣
     * @return @~english true if the point is in parent's area, flase otherwise.
     * @~chinese ��������ڸ��ڵ������ڣ�����true�����򷵻�false��
     */
    bool isClippingParentContainsPoint(const Vec2& pt);

    /**@~english
     * Gets the touch began point of widget when widget is selected.
     * @~chinese 
     * ��ȡ�����ڿؼ���ѡ��ʱ����ʼλ�á�
     * @deprecated use `getTouchBeganPosition` instead.
     * @return @~english the touch began point.
     * @~chinese �������ʼλ�á�
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchStartPos()const{return this->getTouchBeganPosition();}
    /**@~english
     * Gets the touch began point of widget when widget is selected.
     * @~chinese 
     * ��ȡ�����ڿؼ���ѡ��ʱ����ʼλ�á�
     * @return @~english the touch began point.
     * @~chinese �������ʼλ�á�
     */
    const Vec2& getTouchBeganPosition()const;

    /*@~english
     * Gets the touch move point of widget when widget is selected.
     * @~chinese 
     * ��ȡ�����ڿؼ���ѡ��ʱ�ĵ�ǰ�ƶ�λ�á�
     * @deprecated use `getTouchMovePosition` instead.
     * @return @~english the touch move point.
     * @~chinese ����ĵ�ǰ�ƶ�λ�á�
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchMovePos()const{ return this->getTouchMovePosition();}
    /*@~english
     * Gets the touch move point of widget when widget is selected.
     * @~chinese 
     * ��ȡ�����ڿؼ���ѡ��ʱ�ĵ�ǰ�ƶ�λ�á�
     * @return @~english the touch move point.
     * @~chinese ����ĵ�ǰ�ƶ�λ�á�
     */
    const Vec2& getTouchMovePosition()const;

    /*@~english
     * Gets the touch end point of widget when widget is selected.
     * @~chinese 
     * ��ȡ�����ڿؼ���ѡ��ʱ���յ�λ�á�
     * @deprecated use `getTouchEndPosition` instead.
     * @return @~english the touch end point.
     * @~chinese ������յ�λ�á�
     */
    CC_DEPRECATED_ATTRIBUTE const Vec2& getTouchEndPos()const{return this->getTouchEndPosition();}
    /*@~english
     * Gets the touch end point of widget when widget is selected.
     * @~chinese 
     * ��ȡ�����ڿؼ���ѡ��ʱ���յ�λ�á�
     * @return @~english the touch end point.
     * @~chinese ������յ�λ�á�
     */
    const Vec2& getTouchEndPosition()const;

    /**@~english
     * Changes the widget's size
     * @~chinese 
     * ���ÿؼ��ĳߴ�
     * @deprecated use `setContentSize` instead.
     * @param size @~english Widget's size
     * @~chinese �ؼ��ĳߴ�
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setSize(const Size &size);
    /**@~english
     * Changes the widget's size
     * @~chinese 
     * ���ÿؼ��ĳߴ�
     * @param contentSize @~english Widget's size
     * @~chinese �ؼ��ĳߴ�
     */
    virtual void setContentSize(const Size& contentSize) override;

    /**@~english
     * Changes the widget's size in percentage
     * @~chinese 
     * ���ÿؼ��İٷֱȳߴ�
     * 
     * @param percent @~english Widget's size in percentage
     * @~chinese �ؼ��İٷֱȳߴ�
     */
    virtual void setSizePercent(const Vec2 &percent);

    /**@~english
     * Changes the size type of widget.
     * @~chinese 
     * �ı�ؼ��ĳߴ����͡�
     * 
     * @see `SizeType`
     *
     * @param type @~english Widget's size type
     * @~chinese �ؼ��ĳߴ����͡�
     */
    void setSizeType(SizeType type);

    /**@~english
     * Gets the size type of widget.
     * @~chinese 
     * ��ȡ�ؼ��ĳߴ����͡�
     * 
     * @see `SizeType`
     *
     * @return @~english Widget's size type
     * @~chinese �ؼ��ĳߴ����͡�
     */
    SizeType getSizeType() const;

    /**@~english
     * Get the size of widget
     * @~chinese 
     * ��ȡ�ؼ��ĳߴ�
     * 
     * @return @~english Widget content size.
     * @~chinese �ؼ����ݳߴ硣
     */
    CC_DEPRECATED_ATTRIBUTE const Size& getSize() const;
    
    /**@~english
     * Get the user defined widget size.
     * @~chinese 
     * ��ȡ�û�����Ŀؼ��ߴ硣
     *@return @~english User defined size.
     * @~chinese �û�����ĳߴ硣
     */
    const Size& getCustomSize() const;
    
    /**@~english
     * Get the content size of widget.
     * @~chinese 
     * ��ȡ�ؼ��ߴ硣
     * @warning @~english This API exists mainly for keeping back compatibility.
     * @~chinese ���API�Ĵ�����Ҫ���ڱ��ּ����ԡ�
     * @return  @~english User defined size.
     * @~chinese �û�����ĳߴ硣
     */
    virtual const Size& getLayoutSize() {return _contentSize;};

    /**@~english
     * Get size percent of widget.
     * @~chinese 
     * ��ȡ�ؼ��İٷֱȳߴ硣
     * 
     * @return @~english Percent size.
     * @~chinese �ؼ��İٷֱȳߴ硣
     */
    const Vec2& getSizePercent();

    /**@~english
     * Checks a point is in widget's content space.
     * This function is used for determining touch area of widget.
     * @~chinese 
     * ���һ�����Ƿ��ڿؼ������ݿռ��
     * ������������ڼ��ؼ��Ĵ�����Ӧ����
     * 
     * @param pt @~english The point in `Vec2`.
     * @~chinese Vec2���͵ĵ㡣
     * @param camera    @~english The camera look at widget, used to convert GL screen point to near/far plane.
     * @~chinese ָ���۲�ؼ��������Camera������ת��GL��Ļ���굽3D��ƽ���Զƽ��
     * @param p         @~english Point to a Vec3 for store the intersect point, if don't need them set to nullptr.
     * @~chinese һ���������潻����3D����㣬�������Ҫ��������Ϊnullptr
     * @return @~english true if the point is in widget's content space, flase otherwise.
     * @~chinese ������ڿؼ������ݿռ��ڷ���true�����򷵻�false��
     */
    virtual bool hitTest(const Vec2 &pt, const Camera* camera, Vec3 *p) const;

    /**@~english
     * A callback which will be called when touch began event is issued.
     * @~chinese 
     * �����¼���ʼʱ�Ļص�������
     *@param touch @~english The touch info.
     * @~chinese ������Ϣ��
     *@param unusedEvent @~english The touch event info.
     * @~chinese �����¼���Ϣ��
     *@return @~english True if user want to handle touches, false otherwise.
     * @~chinese �����Ҫ��Ӧ��������¼��򷵻�true�����򷵻�false��
     */
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);

    /**@~english
     * A callback which will be called when touch moved event is issued.
     * @~chinese 
     * �����¼��д����ƶ�ʱ�Ļص�������
     *@param touch @~english The touch info.
     * @~chinese ������Ϣ��
     *@param unusedEvent @~english The touch event info.
     * @~chinese �����¼���Ϣ��
     */
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);

    /**@~english
     * A callback which will be called when touch ended event is issued.
     * @~chinese 
     * �����¼�����ʱ�Ļص�������
     *@param touch @~english The touch info.
     * @~chinese ������Ϣ��
     *@param unusedEvent @~english The touch event info.
     * @~chinese �����¼���Ϣ��
     */
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);

    /**@~english
     * A callback which will be called when touch cancelled event is issued.
     * @~chinese 
     * �����¼�ȡ��ʱ�Ļص�������
     *@param touch @~english The touch info.
     * @~chinese ������Ϣ��
     *@param unusedEvent @~english The touch event info.
     * @~chinese �����¼���Ϣ��
     */
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

    /**@~english
     * Sets a LayoutParameter to widget.
     * @~chinese 
     * �o�ؼ�����һ�����ֲ�����LayoutParameter����
     * 
     * @see LayoutParameter
     * @param parameter @~english LayoutParameter pointer
     * @~chinese ���ֲ�������ָ��
     */
    void setLayoutParameter(LayoutParameter* parameter);

    /**@~english
     * Gets LayoutParameter of widget.
     * @~chinese 
     * ��ȡ�ؼ��Ĳ��ֲ�����LayoutParameter����
     * 
     * @see LayoutParameter
     * @return @~english LayoutParameter
     * @~chinese ���ֲ�������ָ��
     */
    LayoutParameter* getLayoutParameter()const override;
    /**@~english
     * Gets LayoutParameter of widget.
     * @~chinese 
     * �������ͻ�ȡ�ؼ��Ĳ��ֲ�����LayoutParameter����
     * 
     * @see LayoutParameter
     * @deprecated use `getLayoutParameter()` instead.
     * @param type  @~english Relative or Linear
     * @~chinese ���ֲ������ͣ���Ի�����
     * @return @~english LayoutParameter
     * @~chinese ���ֲ�������ָ��
     */
    CC_DEPRECATED_ATTRIBUTE LayoutParameter* getLayoutParameter(LayoutParameter::Type type);


    /**@~english
     * Toggle whether ignore user defined content size for widget.
     * Set true will ignore user defined content size which means 
     * the widget size is always equal to the return value of `getVirtualRendererSize`.
     * @~chinese 
     * �����Ƿ�����û�����ͨ��`setContentSize`�趨�Ŀؼ��ߴ硣
     * ����Ϊtrue�������û�����ĳߴ磬��ζ�ſؼ��ߴ���Զ����`getVirtualRendererSize`�ķ���ֵ��
     * 
     * @param ignore @~english Set member variabl _ignoreSize to ignore
     * @~chinese �Ƿ���Կؼ��ߴ磬������`_ignoreSize`���ԡ�
     */
    virtual void ignoreContentAdaptWithSize(bool ignore);

    /**@~english
     * Query whether the widget ignores user defined content size or not
     * @~chinese 
     * ��ѯ�Ƿ�����û�����Ŀؼ��ߴ硣
     * 
     * @return @~english True means ignore user defined content size, false otherwise.
     * @~chinese ����true��ζ�ź����û�����ĳߴ磬���򷵻�false��
     */
    bool isIgnoreContentAdaptWithSize() const;

    /**@~english
     * Gets position of widget in world space.
     * @~chinese 
     * ��ȡ������ռ��пؼ���λ�á�
     * 
     * @return @~english Position of widget in world space.
     * @~chinese ����ռ��пؼ���λ�á�
     */
    Vec2 getWorldPosition()const;

    /**@~english
     * Gets the inner Renderer node of widget.
     * For example, a button's Virtual Renderer is its texture renderer.
     * @~chinese 
     * �ؼ����ڲ���Ⱦ�ڵ㡣
     * ���磬һ����ť��������Ⱦ�ڵ�����������ڵ㡣
     * 
     * @return @~english Node pointer.
     * @~chinese ����ڵ��ָ�롣
     */
    virtual Node* getVirtualRenderer();


    /**@~english
     * Get the virtual renderer's size
     * @~chinese 
     * ��ȡ������Ⱦ�ڵ�ĳߴ�
     * @return @~english Widget virtual renderer size.
     * @~chinese ������Ⱦ�ڵ�ĳߴ硣
     */
    virtual Size getVirtualRendererSize() const;
    

    /**@~english
     * Returns the string representation of widget class name
     * @~chinese 
     * ���ؿؼ��������
     * @return @~english get the class description.
     * @~chinese �ؼ����������
     */
    virtual std::string getDescription() const override;

    /**@~english
     * Create a new widget copy of the original one.
     * @~chinese 
     * ����һ���µĿؼ�������
     * @return @~english A cloned widget copy of original.
     * @~chinese һ����¡�Ŀؼ���
     */
    Widget* clone();

    virtual void onEnter() override;

    virtual void onExit() override;

    /**@~english
     * Update all children's contents size and position recursively.
     * @~chinese 
     * �ݹ�ظ��������ӽڵ�ĳߴ��λ�á�
     * @see `updateSizeAndPosition(const Size&)`
     */
    void updateSizeAndPosition();

    /**@~english
     * Update all children's contents size and position recursively.
     * @~chinese 
     * �ݹ�ظ��������ӽڵ�ĳߴ��λ�á�
     */
    void updateSizeAndPosition(const Size& parentSize);
    
    /**@~english
     * Set the tag of action.
     * @~chinese 
     * ���ö����ı�ǩ��
     * @param tag  @~english A integer tag value.
     * @~chinese һ��������ǩֵ��
     */
    void setActionTag(int tag);

    /**@~english
     * Get the action tag.
     * @~chinese 
     * ��ȡ������ǩ��
     *@return @~english Action tag.
     * @~chinese ������ǩ��
     */
    int getActionTag()const;
    
    /**
     * @brief @~english Allow widget touch events to propagate to its parents. Set false will disable propagation
     * @~chinese ����ؼ��Ĵ����¼����ϴ��������ڵ㣬����Ϊfalse����ֹ���ϴ�����
     * @param isPropagate  @~english True to allow propagation, false otherwise.
     * @~chinese true�������ϴ�����false������
     * @since v3.3
     */
    void setPropagateTouchEvents(bool isPropagate);
    
    /**@~english
     * Return whether the widget is propagate touch events to its parents or not
     * @~chinese 
     * ���ؿؼ��Ƿ��������¼��������丸�ڵ�
     * @return @~english whether touch event propagation is allowed or not.
     * @~chinese Been touch event propagation charges or not.
     * @since v3.3
     */
    bool isPropagateTouchEvents()const;
    
    /**@~english
     * Toggle widget to swallow touches or not.
     * @~chinese 
     * ���ÿؼ��Ƿ����ɴ����¼���
     * @param swallow @~english True to swallow touch, false otherwise.
     * @~chinese true�����ɴ����¼���false�����ɡ�
     * @since v3.3
     */
    void setSwallowTouches(bool swallow);
    
    /**@~english
     * Return whether the widget is swallowing touch or not
     * @~chinese 
     * ��ѯ�ؼ��Ƿ����ɴ����¼�
     * @return @~english Whether touch is swallowed.
     * @~chinese �Ƿ����ɴ����¼���
     * @since v3.3
     */
    bool isSwallowTouches()const;
    
    /**@~english
     * Query whether widget is focused or not.
     * @~chinese 
     * ��ѯ�ؼ��Ƿ�ӵ�н��㡣
     * @return @~english  whether the widget is focused or not
     * @~chinese �Ƿ�ӵ�н���
     */
    bool isFocused()const;
    
    /**@~english
     * Toggle widget focus status.
     * @~chinese 
     * �л��ؼ��Ƿ�ӵ�н��㡣
     * @param focus  @~english pass true to let the widget get focus or pass false to let the widget lose focus
     * @~chinese ��trueʹ�ؼ���ý��㣬�����ÿؼ�ʧȥ����
     */
    void setFocused(bool focus);
    
    /**@~english
     * Query widget's focus enable state.
     * @~chinese 
     * ��ѯ�ؼ��Ƿ�ӵ�н��㡣
     * @return @~english true represent the widget could accept focus, false represent the widget couldn't accept focus
     * @~chinese ����true����ؼ�ӵ�н��㣬��֮����false��
     */
    bool isFocusEnabled()const;
    
    /**@~english
     * Allow widget to accept focus.
     * @~chinese 
     * ����ؼ����ܽ��㡣
     * @param enable @~english pass true/false to enable/disable the focus ability of a widget
     * @~chinese ͨ������true/false�����û����һ���ؼ���ȡ����
     */
    void setFocusEnabled(bool enable);
    
    /**@~english
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction. 
     *  If the widget is not in a layout, it will return itself
     * @~chinese 
     * ��һ���ؼ���һ�������У������Ե�����������õ���ָ���ķ����ϵ���һ���ؼ��������Ϊ�������ҡ�
     * ����ؼ�û���ڲ����У�������������
     *@param direction @~english the direction to look for the next focused widget in a layout
     * @~chinese ָ���ķ���
     *@param current  @~english the current focused widget
     * @~chinese ��ǰӵ�н���Ŀؼ�
     *@return @~english the next focused widget in a layout
     * @~chinese ��������һ����ȡ����Ŀؼ�
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current);
    
    /**@~english
     * when a widget calls this method, it will get focus immediately.
     * @~chinese 
     * �������������ʱ���ؼ�������ӵ�н��㡣
     */
    void requestFocus();

    /**@~english
     * Return a current focused widget in your UI scene.
     * No matter what widget object you call this method on, it will return you the exact one focused widget.
     * @~chinese 
     * ��ȡ��ǰӵ�н���Ŀؼ���
     * ���ܶ�ʲô�ؼ������������������������ص�ǰӵ�н���Ŀؼ���
     * @param isWidget  @~english Unused parameter
     * @~chinese ���õĲ���
     * @deprecated use `getCurrentFocusedWidget` instead.
     */
    CC_DEPRECATED_ATTRIBUTE Widget* getCurrentFocusedWidget(bool isWidget){
        CC_UNUSED_PARAM(isWidget);
        return getCurrentFocusedWidget();
    }

    /**@~english
     * Return a current focused widget in your UI scene.
     * No matter what widget object you call this method on, it will return you the exact one focused widget.
     * @~chinese 
     * ��ȡ��ǰӵ�н���Ŀؼ���
     * ���ܶ�ʲô�ؼ������������������������ص�ǰӵ�н���Ŀؼ���
     */
    Widget* getCurrentFocusedWidget()const;

    /*@~english
     * Enable or disable the Android Dpad focus navigation feature
     * @~chinese 
     * ������ر�Androidϵͳ��Dpad���㵼������
     * @param enable  @~english set true to enable dpad focus navigation, otherwise disenable dpad focus navigation
     * @~chinese ����Ϊtrue����Androidϵͳ��Dpad���㵼�����ܣ�����ر�
     */
    static void enableDpadNavigation(bool enable);

    /**@~english
     * When a widget lose/get focus, this method will be called. Be Caution when you provide your own version of focus system, 
     * you must call widget->setFocused(true/false) to change the focus state of the current focused widget;
     * @~chinese 
     * ��һ���ؼ�ʧȥ���߻�ý��㣬����ص������������á������ṩ�Լ��İ汾�Ľ���ϵͳʱ��
     * ��ע��һ��Ҫ����widget->setFocused(true/false)���ı�ؼ��Ľ���״̬;
     */
    std::function<void(Widget*,Widget*)> onFocusChanged;

    /**@~english
     * Use this function to manually specify the next focused widget regards to each direction
     * @~chinese 
     * ʵ������������ֶ�ָ�����������ϵ���һ������ؼ�
     */
    std::function<Widget*(FocusDirection)> onNextFocusedWidget;
    
    /**@~english
     * Toggle use unify size.
     * @~chinese 
     * �����Ƿ�ʹ�ù�һ���ĳߴ硣
     * @param enable @~english True to use unify size, false otherwise.
     * @~chinese ����true��ʹ�ù�һ���ߴ磬����ʹ�á�
     */
    void setUnifySizeEnabled(bool enable);

    /**@~english
     * Query whether unify size enable state. 
     * @~chinese 
     * ��ѯ�Ƿ�ʹ�ù�һ���ĳߴ硣
     * @return @~english true represent the widget use Unify Size, false represent the widget couldn't use Unify Size
     * @~chinese true��ʹ�ù�һ���ߴ磬����ʹ�á�
     */
    bool isUnifySizeEnabled()const;

    /**@~english
     * Set callback name.
     * @~chinese 
     * ���ûص����������ơ�
     * @param callbackName @~english A string representation of callback name.
     * @~chinese �ص����������ơ�
     */
    void setCallbackName(const std::string& callbackName) { _callbackName = callbackName; }


    /**@~english
     * Query callback name.
     * @~chinese 
     * ��ѯ�ص����������ơ�
     * @return @~english The callback name.
     * @~chinese �ص����������ơ�
     */
    const std::string& getCallbackName() const{ return _callbackName; }
    
    /**@~english
     * Set callback type.
     * @~chinese 
     * ���ûص��������͡�
     * @param callbackType @~english A string representation of callback type.
     * @~chinese �ص����������͡�
     */
    void setCallbackType(const std::string& callbackType) { _callbackType = callbackType; }

    /**@~english
     * Query callback type.
     * @~chinese 
     * ��ѯ�ص��������͡�
     * @return @~english Callback type string.
     * @~chinese �ص����������͡�
     */
    const std::string& getCallbackType() const{ return _callbackType; }

    /**@~english
     * Toggle layout component enable.
     * @~chinese 
     * �����Ƿ����ò��������
     * @param enable @~english Enable layout Component or not
     * @~chinese �Ƿ����ò��������
     */
    void setLayoutComponentEnabled(bool enable);

    /**@~english
     * Query whether layout component is enabled or not. 
     * @~chinese 
     * ��ѯ�Ƿ����ò��������
     * @return @~english true represent the widget use Layout Component, false represent the widget couldn't use Layout Component.
     * @~chinese ����true����ʹ�ò������������ʹ�á�
     */
    bool isLayoutComponentEnabled()const;

CC_CONSTRUCTOR_ACCESS:

    //initializes state of widget.
    virtual bool init() override;

    /*
     * @brief @~english Sends the touch event to widget's parent, if a widget wants to handle touch event under another widget, 
     *        it must override this function.
     * @~chinese �������¼����͸��ؼ��Ľڵ㣬���һ���ؼ��봦�����¼�������������������
     * @param  event  @~english the touch event type, it could be BEGAN/MOVED/CANCELED/ENDED
     * @~chinese �����¼����ͣ����ܵ�ֵ�ǣ�BEGAN/MOVED/CANCELED/ENDED
     * @param @~english parent
     * @~chinese ���ڵ�
     * @param @~english point
     * @~chinese ����
     */
    virtual void interceptTouchEvent(TouchEventType event, Widget* sender, Touch *touch);
    
    /**
     *@brief @~english Propagate touch events to its parents
     * @~chinese ���ϴ��������¼����丸�ڵ�
     */
    void propagateTouchEvent(TouchEventType event, Widget* sender, Touch *touch);
    
    friend class PageView;
    /**@~english
     * This method is called when a focus change event happens
     * @~chinese 
     * ��������¼�����ʱ����ô˷���
     * @param widgetLostFocus  @~english The widget which lose its focus
     * @~chinese ʧȥ����Ŀؼ�
     * @param widgetGetFocus  @~english The widget which get its focus
     * @~chinese ��ý���Ŀؼ�
     */
    void onFocusChange(Widget* widgetLostFocus, Widget* widgetGetFocus);
    
    /**@~english
     * Dispatch a EventFocus through a EventDispatcher
     * @~chinese 
     * ͨ��EventDispatcher�ַ���������¼�
     * @param widgetLoseFocus  @~english The widget which lose its focus
     * @~chinese ʧȥ����Ŀؼ�
     * @param widgetGetFocus  @~english The widget which get its focus
     * @~chinese ��ý���Ŀؼ�
     */
    void dispatchFocusEvent(Widget* widgetLoseFocus, Widget* widgetGetFocus);
    
protected:
    /**@~english
     * Get GLProgramState under normal state 
     * @~chinese 
     * ��ȡ����״̬�µ�GLProgramState
     * @since v3.4
     */
    GLProgramState* getNormalGLProgramState()const;
    
    /**@~english
     * Get GLProgramState under disabled state 
     * @~chinese 
     * ��ȡ����״̬�µ�GLProgramState
     * @since v3.4
     */
    GLProgramState* getGrayGLProgramState()const;
     
    
    //call back function called when size changed.
    virtual void onSizeChanged();

    //initializes renderer of widget.
    virtual void initRenderer();

    //call back function called widget's state changed to normal.
    virtual void onPressStateChangedToNormal();
    //call back function called widget's state changed to selected.
    virtual void onPressStateChangedToPressed();
    //call back function called widget's state changed to dark.
    virtual void onPressStateChangedToDisabled();

    void pushDownEvent();
    void moveEvent();

    virtual void releaseUpEvent();
    virtual void cancelUpEvent();

    
    virtual void adaptRenderers(){};
    void updateChildrenDisplayedRGBA();
    
    void copyProperties(Widget* model);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    
    Widget* getWidgetParent();
    void updateContentSizeWithTextureSize(const Size& size);
    
    bool isAncestorsEnabled();
    Widget* getAncensterWidget(Node* node);
    bool isAncestorsVisible(Node* node);

    void cleanupWidget();
    LayoutComponent* getOrCreateLayoutComponent();

protected:
    bool _usingLayoutComponent;
    bool _unifySize;
    bool _enabled;
    bool _bright;
    bool _touchEnabled;
    bool _highlight;
    bool _affectByClipping;
    bool _ignoreSize;
    bool _propagateTouchEvents;

    BrightStyle _brightStyle;
    SizeType _sizeType;
    PositionType _positionType;

    //used for search widget by action tag in UIHelper class
    int _actionTag;

    Size _customSize;

    Vec2 _sizePercent;
    Vec2 _positionPercent;

    bool _hitted;
    // weak reference of the camera which made the widget passed the hit test when response touch begin event
    // it's useful in the next touch move/end events
    const Camera *_hittedByCamera;
    EventListenerTouchOneByOne* _touchListener;
    Vec2 _touchBeganPosition;
    Vec2 _touchMovePosition;
    Vec2 _touchEndPosition;

    bool _flippedX;
    bool _flippedY;

    //use map to enble switch back and forth for user layout parameters
    Map<int,LayoutParameter*> _layoutParameterDictionary;
    LayoutParameter::Type _layoutParameterType;

    bool _focused;
    bool _focusEnabled;

    static Widget *_focusedWidget;  //both layout & widget will be stored in this variable

    Ref*       _touchEventListener;
    #if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #elif _MSC_VER >= 1400 //vs 2005 or higher
    #pragma warning (push)
    #pragma warning (disable: 4996)
    #endif
    SEL_TouchEvent    _touchEventSelector;
    #if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #pragma GCC diagnostic warning "-Wdeprecated-declarations"
    #elif _MSC_VER >= 1400 //vs 2005 or higher
    #pragma warning (pop)
    #endif
    ccWidgetTouchCallback _touchEventCallback;
    ccWidgetClickCallback _clickEventListener;
    ccWidgetEventCallback _ccEventCallback;
    
    std::string _callbackType;
    std::string _callbackName;
private:
    class FocusNavigationController;
    static FocusNavigationController* _focusNavigationController;
};
}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__Widget__) */
