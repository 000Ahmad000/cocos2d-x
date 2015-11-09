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

#ifndef __UISCROLLVIEW_H__
#define __UISCROLLVIEW_H__

#include "ui/UILayout.h"
#include "ui/GUIExport.h"
#include <list>

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

class EventFocusListener;

namespace ui {

class ScrollViewBar;

/**
 * @enum ScrollviewEventType
 * @brief @~english Scrollview scroll event type.
 * @~chinese ������ͼ�Ĺ����¼�����
 * @deprecated use @see `ScrollView::EventType` instead.
 */
typedef enum
{
    SCROLLVIEW_EVENT_SCROLL_TO_TOP,
    SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM,
    SCROLLVIEW_EVENT_SCROLL_TO_LEFT,
    SCROLLVIEW_EVENT_SCROLL_TO_RIGHT,
    SCROLLVIEW_EVENT_SCROLLING,
    SCROLLVIEW_EVENT_BOUNCE_TOP,
    SCROLLVIEW_EVENT_BOUNCE_BOTTOM,
    SCROLLVIEW_EVENT_BOUNCE_LEFT,
    SCROLLVIEW_EVENT_BOUNCE_RIGHT
}ScrollviewEventType;

/**
 * @~english A callback which would be called when a ScrollView is scrolling.
 * @~chinese ��������ͼ����ʱ�ᴥ���Ļص�����
 *@deprecated Use @see `ccScrollViewCallback` instead.
 */
typedef void (Ref::*SEL_ScrollViewEvent)(Ref*, ScrollviewEventType);
#define scrollvieweventselector(_SELECTOR) (SEL_ScrollViewEvent)(&_SELECTOR)

/**
 * @class ScrollView
 * @brief @~english Layout container for a view hierarchy that can be scrolled by the user, allowing it to be larger than the physical display.
 * It holds a inner `Layout` container for storing child items horizontally or vertically.
 * @~chinese һ���ܹ����û�����������һ������Ͳ���������ͼ��������ߴ������Ļ��ʾ������ߴ磬���ڲ�ά����һ����������ˮƽ�Ļ�ֱ�Ĵ���ӽڵ�
 */
class CC_GUI_DLL ScrollView : public Layout
{

    DECLARE_CLASS_GUI_INFO

public:
    /**
     * @enum Direction
     * @brief @~english ScrollView scroll direction type.
     * @~chinese ������ͼ�Ĺ�������
     */
    enum class Direction
    {
        /**
         * @~english User can not scroll the view.
         * @~chinese ��ֹ����
         **/
        NONE,
        /**
        * @~english User can scroll the view vertically.
        * @~chinese ��ֱ����
        **/
        VERTICAL,
        /**
        * @~english User can scroll the view horizontally.
        * @~chinese ˮƽ����
        **/
        HORIZONTAL,
        /**
        * @~english User can scroll the view both horizontally and vertically.
        * @~chinese ˮƽ����ֱ����
        **/
        BOTH
    };

    /**
     * @enum EventType
     * @brief @~english Scrollview scroll event type.
     * @~chinese ������ͼ�Ĺ����¼�
     */
    enum class EventType
    {
        SCROLL_TO_TOP,
        SCROLL_TO_BOTTOM,
        SCROLL_TO_LEFT,
        SCROLL_TO_RIGHT,
        SCROLLING,
        BOUNCE_TOP,
        BOUNCE_BOTTOM,
        BOUNCE_LEFT,
        BOUNCE_RIGHT,
        CONTAINER_MOVED
    };

    /**
     * @~english A callback which would be called when a ScrollView is scrolling.
     * @~chinese �ڹ�����ͼ����ʱ�������Ļص�����
     */
    typedef std::function<void(Ref*, EventType)> ccScrollViewCallback;

    /**
     * @~english Default constructor
     * @~chinese Ĭ�Ϲ��캯��
     * @js ctor
     * @lua new
     */
    ScrollView();

    /**
     * @~english Default destructor
     * @~chinese Ĭ����������
     * @js NA
     * @lua NA
     */
    virtual ~ScrollView();

    /**
     * @~english Create an empty ScrollView.
     * @~chinese ����һ���յĹ�����ͼ
     * @return @~english A ScrollView instance.
     * @~chinese �������Ĺ�����ͼ�Ķ���
     */
    static ScrollView* create();

    /**
     * @~english Changes scroll direction of scrollview.
     * @~chinese �ı������ͼ�ķ���
     * @see `Direction`
     * @param dir @~english Scroll direction enum.
     * @~chinese ���������ö��
     */
    virtual void setDirection(Direction dir);

    /**
     * @~english Query scroll direction of scrollview.
     * @~chinese ��ȡ������ͼ�Ĺ�������
     * @see `Direction`      @~english Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll
     * @~chinese Direction::VERTICAL��ζ����ֱ������Direction::HORIZONTAL��ζ��ˮƽ����
     * @return @~english Scrollview scroll direction.
     * @~chinese ������ͼ�ɹ�������
     */
    Direction getDirection()const;

    /**
     * @~english Get inner container of scrollview.
     *
     * Inner container is a child of scrollview.
     * @~chinese ��ȡ������ͼ���ڲ������������ò�������Ϊ������ͼ���ӽڵ� 
     * @return @~english Inner container pointer.
     */
    Layout* getInnerContainer()const;

    /**
     * @~english Scroll inner container to bottom boundary of scrollview.
     * @~chinese ���ڲ��Ĳ�������������������ͼ�ĵײ��߽�
     * @param second @~english Time in seconds.
     * @~chinese �ö�������ʱ�䣬�����
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �ö�������ʱ�������ٶ��Ƿ��˥��
     */
    void scrollToBottom(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to top boundary of scrollview.
     * @~chinese ���ڲ���������������������ͼ�Ķ����߽�
     * @param second @~english Time in seconds.
     * @~chinese �ö��������ʱ�䣬�����
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �ö�������ʱ�������ٶ��Ƿ��˥��
     */
    void scrollToTop(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to left boundary of scrollview.
     * @~chinese ���ڲ�����������������ͼ����˱߽�
     * @param second @~english Time in seconds.
     * @~chinese ����ִ������ʱ�䣬�����
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToLeft(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to right boundary of scrollview.
     * @~chinese ���ڲ���������������������ͼ���Ҷ˱߽�
     * @param time @~english Time in seconds.
     * @~chinese ����ִ������ʱ�䣬�����
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToRight(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to top and left boundary of scrollview.
     * @~chinese �����ڲ�����������������ͼ�����Ͻ�
     * @param second @~english Time in seconds.
     * @~chinese ����ִ������ʱ�䣬�����
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToTopLeft(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to top and right boundary of scrollview.
     * @~chinese �����ڲ���������������ʹͽ�����Ͻ�
     * @param time @~english Time in seconds.
     * @~chinese ��������ʱ�䣬�����
     * @param attenuated Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToTopRight(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to bottom and left boundary of scrollview.
     * @~chinese �����ڲ�������������ͼ�����½�
     * @param second @~english Time in seconds.
     * @~chinese ����ִ������ʱ�䣬�����
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToBottomLeft(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to bottom and right boundary of scrollview.
     * @~chinese �����ڲ�������������ͼ�����½�
     * @param time @~english Time in seconds
     * @~chinese ����ִ������ʱ��
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToBottomRight(float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to vertical percent position of scrollview.
     * @~chinese ���ٷֱ���ֱ�����ڲ���������
     * @param percent @~english A value between 0 and 100.
     * @~chinese �ٷֱȣ���0��100
     * @param second @~english Time in seconds.
     * @~chinese ����ִ��ʱ��
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToPercentVertical(float percent, float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to horizontal percent position of scrollview.
     * @~chinese ���ٷֱ�ˮƽ�����ڲ���������
     * @param percent @~english A value between 0 and 100.
     * @~chinese �ٷֱȣ���0��100
     * @param second @~english Time in seconds.
     * @~chinese ����ִ��ʱ��
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToPercentHorizontal(float percent, float timeInSec, bool attenuated);

    /**
     * @~english Scroll inner container to both direction percent position of scrollview.
     * @~chinese ����ֱ�����ˮƽ����ֱ�һ���İٷֱȹ����ڲ���������
     * @param percent @~english A value between 0 and 100.
     * @~chinese �ٷֱȣ�x��������ˮƽ�ٷֱȣ�y����������ֱ�ٷֱ�
     * @param second @~english Time in seconds.
     * @~chinese ��������ʱ��
     * @param attenuated @~english Whether scroll speed attenuate or not.
     * @~chinese �����ٶ��Ƿ���˥��
     */
    void scrollToPercentBothDirection(const Vec2& percent, float timeInSec, bool attenuated);

    /**
     * @~english Move inner container to bottom boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ�׶�
     */
    virtual void jumpToBottom();

    /**
     * @~english Move inner container to top boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ����
     */
    virtual void jumpToTop();

    /**
     * @~english Move inner container to left boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ���
     */
    virtual void jumpToLeft();

    /**
     * @~english Move inner container to right boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ�Ҷ�
     */
    virtual void jumpToRight();

    /**
     * @~english Move inner container to top and left boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ�����Ͻ�
     */
    virtual void jumpToTopLeft();

    /**
     * @~english Move inner container to top and right boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ�����Ͻ�
     */
    virtual void jumpToTopRight();

    /**
     * @~english Move inner container to bottom and left boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ�����½�
     */
    virtual void jumpToBottomLeft();

    /**
     * @~english Move inner container to bottom and right boundary of scrollview.
     * @~chinese ���ڲ���������������ͼ�����½�
     */
    virtual void jumpToBottomRight();

    /**
     * @~english Move inner container to vertical percent position of scrollview.
     * @~chinese ��һ���İٷֱ���ֱ������ͼ�ڵĲ�������
     * @param percent @~english A value between 0 and 100.
     * @~chinese �ٷֱȣ���0��100
     */
    virtual void jumpToPercentVertical(float percent);

    /**
     * @~english Move inner container to horizontal percent position of scrollview.
     * @~chinese ��һ���İٷֱ���ֱ������ͼ�ڵĲ�������
     * @param percent   @~english A value between 0 and 100.
     * @~chinese �ٷֱȣ���0��100
     */
    virtual void jumpToPercentHorizontal(float percent);

    /**
     * @~english Move inner container to both direction percent position of scrollview.
     * @~chinese ��ֱ�����ˮƽ����ֱ�һ���İٷֱȹ�������
     * @param percent  @~english  A value between 0 and 100.
     * @~chinese x����Ϊˮƽ����İٷֱȣ�y����Ϊ��ֱ����İٷֱ�
     */
    virtual void jumpToPercentBothDirection(const Vec2& percent);

    /**
     * @~english Change inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     * @~chinese �����ڲ����������ĳߴ��С���ڲ������ĳߴ������ڻ���ڹ�����ͼ�ĳߴ�
     * @param size @~english Inner container size.
     * @~chinese �ڲ������ĳߴ�
     */
    void setInnerContainerSize(const Size &size);

    /**
     * @~english Get inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     * @~chinese ��ȡ�ڲ������ĳߴ磬�ڲ������ĳߴ������ڻ���ڹ�����ͼ�ĳߴ�
     * @return @~english The inner container size.
     * @~chinese �ڲ������ĳߴ�
     */
    const Size& getInnerContainerSize() const;
    
    /**
     * Set inner container position
     *
     * @param pos Inner container position.
     */
    void setInnerContainerPosition(const Vec2 &pos);
    
    /**
     * Get inner container position
     *
     * @return The inner container position.
     */
    const Vec2 getInnerContainerPosition() const;

    /**
     * @~english Add callback function which will be called  when scrollview event triggered.
     * @~chinese ���һ���ص��������ûص�������������ͼ��������ʱ����
     * @deprecated Use @see `addEventListener` instead.
     * @param target @~english A pointer of `Ref*` type.
     * @~english Ref* ָ��
     * @param selector @~english A member function pointer with type of `SEL_ScrollViewEvent`.
     * @~chinese `SEL_ScrollViewEvent`���͵ĳ�Ա����ָ��
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerScrollView(Ref* target, SEL_ScrollViewEvent selector);

    /**
     * @~english Add callback function which will be called  when scrollview event triggered.
     * @~chinese ���һ���ص��������ûص��������ڹ����¼�����ʱ������
     * @param callback @~english A callback function with type of `ccScrollViewCallback`.
     * @~chinese `ccScrollViewCallback` ���͵Ļص�����
     */
    virtual void addEventListener(const ccScrollViewCallback& callback);

    //override functions
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    virtual void addChild(Node* child, int localZOrder, int tag) override;
    virtual void addChild(Node* child, int localZOrder, const std::string &name) override;
    virtual void removeAllChildren() override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleaup = true) override;
    virtual Vector<Node*>& getChildren() override;
    virtual const Vector<Node*>& getChildren() const override;
    virtual ssize_t getChildrenCount() const override;
    virtual Node * getChildByTag(int tag) const override;
    virtual Node* getChildByName(const std::string& name)const override;
    //touch event callback
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    virtual void update(float dt) override;

    /**
     * @brief @~english Toggle bounce enabled when scroll to the edge.
     * @~chinese ���õ��������߽�ʱ���Ƿ��ڲ�������������(bounce)Ч��
     * @param enabled @~english True if enable bounce, false otherwise.
     * @~chinese �Ƿ�������(bounce)Ч��
     */
    void setBounceEnabled(bool enabled);

    /**
     * @brief @~english Query bounce state.
     * @~chinese ��ȡ����(bounce)״̬
     * @return @~english True if bounce is enabled, false otherwise.
     * @~chinese ��������ʱ����true����֮����false
     */
    bool isBounceEnabled() const;

    /**
     * @brief @~english Toggle whether enable scroll inertia while scrolling.
     * @~chinese �����Ƿ�����������
     * @param enabled @~english True if enable inertia, false otherwise.
     * @~chinese ��Ϊtrue�������������ԣ���֮������
     */
    void setInertiaScrollEnabled(bool enabled);

    /**
     * @brief @~english Query inertia scroll state.
     * @~chinese ��ȡ������ͼ�Ƿ�����������
     * @return @~english True if inertia is enabled, false otherwise.
     * @~chinese �������Կ���ʱ����true����֮����false
     */
    bool isInertiaScrollEnabled() const;
    
    /**
     * @brief Toggle scroll bar enabled.
     *
     * @param enabled True if enable scroll bar, false otherwise.
     */
    void setScrollBarEnabled(bool enabled);
    
    /**
     * @brief Query scroll bar state.
     *
     * @return True if scroll bar is enabled, false otherwise.
     */
    bool isScrollBarEnabled() const;
    
    /**
     * @brief Set the scroll bar positions from the left-bottom corner (horizontal) and right-top corner (vertical).
     *
     * @param positionFromCorner The position from the left-bottom corner (horizontal) and right-top corner (vertical).
     */
    void setScrollBarPositionFromCorner(const Vec2& positionFromCorner);
    
    /**
     * @brief Set the vertical scroll bar position from right-top corner.
     *
     * @param positionFromCorner The position from right-top corner
     */
    void setScrollBarPositionFromCornerForVertical(const Vec2& positionFromCorner);
    
    /**
     * @brief Get the vertical scroll bar's position from right-top corner.
     *
     * @return positionFromCorner
     */
    Vec2 getScrollBarPositionFromCornerForVertical() const;
    
    /**
     * @brief Set the horizontal scroll bar position from left-bottom corner.
     *
     * @param positionFromCorner The position from left-bottom corner
     */
    void setScrollBarPositionFromCornerForHorizontal(const Vec2& positionFromCorner);
    
    /**
     * @brief Get the horizontal scroll bar's position from right-top corner.
     *
     * @return positionFromCorner
     */
    Vec2 getScrollBarPositionFromCornerForHorizontal() const;
    
    /**
     * @brief Set the scroll bar's width
     *
     * @param width The scroll bar's width
     */
    void setScrollBarWidth(float width);
    
    /**
     * @brief Get the scroll bar's width
     *
     * @return the scroll bar's width
     */
    float getScrollBarWidth() const;
    
    /**
     * @brief Set the scroll bar's color
     *
     * @param the scroll bar's color
     */
    void setScrollBarColor(const Color3B& color);
    
    /**
     * @brief Get the scroll bar's color
     *
     * @return the scroll bar's color
     */
    const Color3B& getScrollBarColor() const;
    
    /**
     * @brief Set the scroll bar's opacity
     *
     * @param the scroll bar's opacity
     */
    void setScrollBarOpacity(GLubyte opacity);
    
    /**
     * @brief Get the scroll bar's opacity
     *
     * @return the scroll bar's opacity
     */
    GLubyte getScrollBarOpacity() const;
    
    /**
     * @brief Set scroll bar auto hide state
     *
     * @param scroll bar auto hide state
     */
    void setScrollBarAutoHideEnabled(bool autoHideEnabled);
    
    /**
     * @brief Query scroll bar auto hide state
     *
     * @return True if scroll bar auto hide is enabled, false otherwise.
     */
    bool isScrollBarAutoHideEnabled() const;
    
    /**
     * @brief Set scroll bar auto hide time
     *
     * @param scroll bar auto hide time
     */
    void setScrollBarAutoHideTime(float autoHideTime);
    
    /**
     * @brief Get the scroll bar's auto hide time
     *
     * @return the scroll bar's auto hide time
     */
    float getScrollBarAutoHideTime() const;
    
    /**
     * @~english Set layout type for scrollview.
     * ���ù�����ͼ�Ĳ�������
     * @see `Layout::Type`
     * @param type  @~english Layout type enum.
     * @~chinese �������͵�ö��
     */
    virtual void setLayoutType(Type type) override;

    /**
     * @~english Get the layout type for scrollview.
     * @~chinese ��ȡ������ͼ�ĵ�ǰ��������
     * @see `Layout::Type`
     * @return @~english LayoutType
     * @~chinese ��������
     */
    virtual Type getLayoutType() const override;

    /**
     * @~english Return the "class name" of widget.
     * @~chinese ����������
     */
    virtual std::string getDescription() const override;

    /**
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     *  @~english When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.
     *  If the widget is not in a layout, it will return itself
     * @~chinese ��һ���ؼ��ǲ���ʱ������Ե��ô˷�����ȡָ����������һ���н���Ŀؼ��������ǰ�ؼ����ǲ��֣�����������
     * @param direction @~english The direction to look for the next focused widget in a layout
     * @~chinese ָ������
     * @param current  @~english The current focused widget
     * @~chinese ��ǰ����Ŀؼ�
     * @return @~english The next focused widget in a layout
     * @~chinese ��һ���н���Ŀؼ�
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current) override;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    enum class MoveDirection
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
    };
    
    virtual void initRenderer() override;

    virtual void onSizeChanged() override;
    virtual void doLayout() override;

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    
    virtual void initScrollBar();
    virtual void removeScrollBar();
    
    Vec2 flattenVectorByDirection(const Vec2& vector);
    
    virtual Vec2 getHowMuchOutOfBoundary(const Vec2& addition = Vec2::ZERO);
    bool isOutOfBoundary(MoveDirection dir);
    bool isOutOfBoundary();
    
    void moveChildren(float offsetX, float offsetY);
    void moveChildrenToPosition(const Vec2& position);
	
	bool calculateCurrAndPrevTouchPoints(Touch* touch, Vec3* currPt, Vec3* prevPt);
	void gatherTouchMove(const Vec2& delta);
    Vec2 calculateTouchMoveVelocity() const;
    
    virtual void startAttenuatingAutoScroll(const Vec2& deltaMove, const Vec2& initialVelocity);
    void startAutoScroll(const Vec2& deltaMove, float timeInSec, bool attenuated);
    void startAutoScrollToDestination(const Vec2& des, float timeInSec, bool attenuated);
    bool isNecessaryAutoScrollBrake();
    void processAutoScrolling(float deltaTime);

    void startInertiaScroll(const Vec2& touchMoveVelocity);
    
    bool startBounceBackIfNeeded();

    void jumpToDestination(const Vec2& des);

    virtual bool scrollChildren(float touchOffsetX, float touchOffsetY);

    virtual void handlePressLogic(Touch *touch);
    virtual void handleMoveLogic(Touch *touch);
    virtual void handleReleaseLogic(Touch *touch);

    virtual void interceptTouchEvent(Widget::TouchEventType event,Widget* sender,Touch *touch) override;
    
    void processScrollEvent(MoveDirection dir, bool bounce);
    void processScrollingEvent();
    void dispatchEvent(ScrollviewEventType scrollEventType, EventType eventType);
    
    void updateScrollBar(const Vec2& outOfBoundary);

protected:
    Layout* _innerContainer;

    Direction _direction;

    float _topBoundary;
    float _bottomBoundary;
    float _leftBoundary;
    float _rightBoundary;

    bool _bePressed;

    float _childFocusCancelOffsetInInch;
    
    // Touch move speed
    std::list<Vec2> _touchMoveDisplacements;
    std::list<float> _touchMoveTimeDeltas;
    long long _touchMovePreviousTimestamp;
    
    bool _autoScrolling;
    bool _autoScrollAttenuate;
    Vec2 _autoScrollStartPosition;
    Vec2 _autoScrollTargetDelta;
    float _autoScrollTotalTime;
    float _autoScrollAccumulatedTime;
    bool _autoScrollCurrentlyOutOfBoundary;
    bool _autoScrollBraking;
    Vec2 _autoScrollBrakingStartPosition;
    
    bool _inertiaScrollEnabled;

    bool _bounceEnabled;
    
    Vec2 _outOfBoundaryAmount;
    bool _outOfBoundaryAmountDirty;
    
    bool _scrollBarEnabled;
    ScrollViewBar* _verticalScrollBar;
    ScrollViewBar* _horizontalScrollBar;
    
    Ref* _scrollViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_ScrollViewEvent _scrollViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccScrollViewCallback _eventCallback;
};

}
// end of ui group
/// @}
NS_CC_END
#endif /* defined(__CocoGUI__ScrollView__) */
