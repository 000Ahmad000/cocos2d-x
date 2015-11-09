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

#ifndef __UIPAGEVIEW_H__
#define __UIPAGEVIEW_H__

#include "ui/UILayout.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {

/**
 *PageView page turn event type.
 *@deprecated Use `PageView::EventType` instead.
 */
typedef enum
{
    PAGEVIEW_EVENT_TURNING,
}PageViewEventType;

/**
 *A callback which would be called when a PageView turning event is happening.
 *@deprecated Use `PageView::ccPageViewCallback` instead.
 */
typedef void (Ref::*SEL_PageViewEvent)(Ref*, PageViewEventType);
#define pagevieweventselector(_SELECTOR)(SEL_PageViewEvent)(&_SELECTOR)

/** @class PageView
*@brief @~english Layout manager that allows the user to flip left & right and up & down through pages of data.
 
 @~chinese Layout�Ĺ��������������û��ڶ��Layout֮�����һ��������л���ʾ��
*/
class CC_GUI_DLL PageView : public Layout
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Page turn event tpye.
     */
    enum class EventType
    {
        TURNING
    };
    
    /**
     * Touch direction type.
     */
    enum class TouchDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    
    enum class Direction
    {
        HORIZONTAL,
        VERTICAL
    };
    
    /**
     * @~english PageView page turn event callback.
     * @~chinese ҳ�淭ҳʱ���¼��ص���
     */
    typedef std::function<void(Ref*,EventType)> ccPageViewCallback;

    /**
     * @~english Default constructor
     * @~chinese Ĭ�Ϲ�����
     * @js ctor
     * @lua new
     */
    PageView();
    
    /**
     * @~english Default destructor
     * @~chinese Ĭ��������
     * @js NA
     * @lua NA
     */
    virtual ~PageView();
    
    /**
     * @~english Create an empty PageView.
     * @~chinese ����һ���յ�PageView��
     * @return @~english A PageView instance.
     */
    static PageView* create();
    
    /**
     * @~english Add a widget as a page of PageView in a given index.
     * @~chinese ��һ��widget��ӵ�ָ����PageViewҳ�С�
     * @param widget    @~english Widget to be added to pageview. @~chinese ����ӵ�PageView�е�Widget��
     * @param pageIdx   @~english A given index. @~chinese ҳ������
     * @param forceCreate   @~english If `forceCreate` is true and `widget` isn't exists, pageview would create a default page and add it. @~chinese ���forceCreateΪTrue������ָ��ҳ�����ڣ����ᴴ��һ��Ĭ��ҳ����widget���롣
     */
    void addWidgetToPage(Widget* widget, ssize_t pageIdx, bool forceCreate);
    
    /**
     * @~english Insert a page into the end of PageView.
     * @~chinese ��PageView��������һҳ��
     * @param page @~english Page to be inserted. @~chinese �������ҳ��
     */
    void addPage(Layout* page);
    
    /**
     * @~english Insert a page into PageView at a given index.
     * @~chinese ��ָ��λ�ò���һҳ��
     * @param page  @~english Page to be inserted. @~chinese �������ҳ��
     * @param idx   @~english A given index. @~chinese ҳ�����š�
     */
    void insertPage(Layout* page, int idx);
    
    /**
     * @~english Remove a page of PageView.
     * @~chinese ��PageView���Ƴ�һҳ��
     * @param page  @~english Page to be removed. @~chinese ���Ƴ���ҳ��
     */
    void removePage(Layout* page);

    /**
     * @~english Remove a page at a given index of PageView.
     * @~chinese �Ƴ�ָ��λ�õ�ҳ��
     * @param index  @~english A given index. @~chinese ҳ�����š�
     */
    void removePageAtIndex(ssize_t index);

    /**
     * Changes scroll direction of PageView
     *
     * @see `Direction`
     * @param direction Scroll direction enum.
     * @since v3.8
     */
    void setDirection(Direction direction);

    /**
     * Query scroll direction of PageView.
     *
     * @see `Direction`
     * @since v3.8
     * @return PageView scroll direction.
     */
    Direction getDirection()const;
    
    /**
     * @~english Remove all pages of the PageView.
     * @~chinese �Ƴ�PageView������ҳ��
     */
    void removeAllPages();
    
    /**
     * @~english Scroll to a page with a given index.
     * @~chinese ������һ��ָ����ҳ��
     * @param idx   @~english A given index in the PageView. Index start from 0 to pageCount-1. 
     * @~chinese ҳ�����š�������0��pageCount-1
     */
    void scrollToPage(ssize_t idx);


    /**
     * @~english Gets current displayed page index.
     * @~chinese ��ȡ��ǰ��ʾҳ�������š�
     * @return @~english current page index. @~chinese ��ǰҳ�����š�
     */
    ssize_t getCurPageIndex() const;

    /**
     * Jump to a page with a given index without scrolling.
     * This is the different between scrollToPage.
     *
     * @param index A given index in PageView. Index start from 0 to pageCount -1.
     */
    void setCurPageIndex(ssize_t index);
     
    /**
     * @~english Get all the pages in the PageView.
     * @~chinese ��ȡ����ҳ���б�
     * @return @~english A vector of Layout pionters. @~chinese һ��Layoutָ�����顣
     */
    Vector<Layout*>& getPages();
    
    
    /**
     * @~english Get a page at a given index
     * @~chinese ��ȡָ����ҳ��
     * @param index @~english A given index. @~chinese ҳ�����š�
     * @return @~english A layout pointer in PageView container. @~chinese һ������PageView�е�layoutָ�롣
     */
    Layout* getPage(ssize_t index);
    
    /**
     * @~english Add a page turn callback to PageView, then when one page is turning, the callback will be called.
     * @~chinese ���һ��ҳ���л�ʱ�Ļص���������ҳ���л�ʱ�����á�
     * @deprecated Use `PageView::addEventListener` instead.
     * @param target @~english A pointer of `Ref*` type.��@~chinese һ��Ref����ָ�롣
     * @param selector @~english A member function pointer with signature of `SEL_PageViewEvent`.��@~chinese �ص�������
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerPageView(Ref *target, SEL_PageViewEvent selector);

    
    /**
     * @~english Add a page turn callback to PageView, then when one page is turning, the callback will be called.
     * @~chinese ���һ��ҳ���л�ʱ�Ļص���������ҳ���л�ʱ�����á�
     * @param callback @~english A page turning callback. @~chinese �ص�������
     */
    void addEventListener(const ccPageViewCallback& callback);
    
    //override methods
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    virtual void update(float dt) override;
    virtual void setLayoutType(Type type) override{};
    virtual Type getLayoutType() const override{return Type::ABSOLUTE;};
    virtual std::string getDescription() const override;
    /**
     * @lua NA
     */
    virtual void onEnter() override;

    /**   
     * @~english If you don't specify the value, the pageView will turn page when scrolling at the half width of a page.
     * @~chinese ���û��ָ����ֵ��pageView���ڹ���ҳ��һ��ʱ�л�����һҳ��
     * @param threshold  @~english A threshold in float. @~chinese �л�ҳ������ֵ��
     */
    void setCustomScrollThreshold(float threshold);

    /**
     * @~english Query the custom scroll threshold of the PageView.
     * @~chinese �����趨���л�ҳ������ֵ��
     * @return @~english Custom scroll threshold in float. @~chinese �л�ҳ������ֵ��
     */
    float getCustomScrollThreshold()const;

    /**
     * @~english Set using user defined scroll page threshold or not.
     * If you set it to false, then the default scroll threshold is pageView.width / 2
     * @~chinese �Ƿ�ʹ���û����õ��л�ҳ������ֵ��
     * �����Ϊfalse����ôpageView���ڹ���ҳ��һ��ʱ�л�����һҳ��
     * @param flag @~english True if using custom scroll threshold, false otherwise. @~chinese �л�ҳ������ֵ��
     */
    void setUsingCustomScrollThreshold(bool flag);

    /**
     * @~english Query whether use user defined scroll page threshold or not.
     * @~chinese �����Ƿ�ʹ���û��Զ���ҳ���л�����ֵ��
     * @return @~english True if using custom scroll threshold, false otherwise. @~chinese True����ʹ���û����õ�ҳ���л�����ֵ����֮��ʹ�á�
     */
    bool isUsingCustomScrollThreshold()const;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:

    Layout* createPage();
    float getPositionXByIndex(ssize_t idx)const;
    float getPositionYByIndex(ssize_t idx)const;
    ssize_t getPageCount()const;

    void updateBoundaryPages();
    virtual bool scrollPages(Vec2 touchOffset);
    void movePages(Vec2 offset);
    void pageTurningEvent();
    void updateAllPagesSize();
    void updateAllPagesPosition();
    void autoScroll(float dt);

    virtual void handleMoveLogic(Touch *touch) ;
    virtual void handleReleaseLogic(Touch *touch) ;
    virtual void interceptTouchEvent(TouchEventType event, Widget* sender,Touch *touch) override;
    
    
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;

    virtual void doLayout() override;

protected:
    enum class AutoScrollDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    bool _isAutoScrolling;
    float _autoScrollDistance;
    float _autoScrollSpeed;
    AutoScrollDirection _autoScrollDirection;
    Direction _direction;
    
    ssize_t _curPageIdx;
    Vector<Layout*> _pages;

    TouchDirection _touchMoveDirection;
   
    Widget* _leftBoundaryChild;
    Widget* _rightBoundaryChild;
    
    float _leftBoundary;
    float _rightBoundary;
    float _customScrollThreshold;
    bool _usingCustomScrollThreshold;

    float _childFocusCancelOffset;

    Ref* _pageViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_PageViewEvent _pageViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccPageViewCallback _eventCallback;
};

}
NS_CC_END
// end of ui group
/// @}

#endif /* defined(__PageView__) */
