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


#ifndef __UILISTVIEW_H__
#define __UILISTVIEW_H__

#include "ui/UIScrollView.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui{
    
/**
 * @~english
 * ListView click item event type.
 * @~chinese 
 * ListView����¼����͡�
 */
typedef enum
{
    LISTVIEW_ONSELECTEDITEM_START,
    LISTVIEW_ONSELECTEDITEM_END
}ListViewEventType;

/**
 * @~english
 * A callback which would be called when a ListView item is clicked.
 * @~chinese 
 * ListView�������ʱ�򣬵��õĻص�����
 * @deprecated @~english Use `ccListViewCallback` instead.
 * @~chinese ��ʹ��ccListViewCallback���档
 */
typedef void (Ref::*SEL_ListViewEvent)(Ref*,ListViewEventType);
#define listvieweventselector(_SELECTOR) (SEL_ListViewEvent)(&_SELECTOR)

/**
 * @brief @~english ListView is a view group that displays a list of scrollable items.
 * The list items are inserted to the list by using `addChild` or  `insertDefaultItem`.
 * @~chinese ListView�ؼ���һ����ʾ������Ŀ�б����ͼ�顣
 * �б�����ͨ��ʹ��`addChild`��`insertDefaultItem`���뵽�б��еġ�
 * @warning @~english The list item in ListView doesn't support cell reuse at the moment, if you have a large amount of data need to be displayed, use  `TableView` instead.
 * ListView is a subclass of  `ScrollView`, so it shares many features of ScrollView.
 * @~chinese ��ListView�ؼ��б��֧�ָ��ýڵ㣬������д�����������Ҫ��ʾ����ʹ��`TableView`���档
 * ListView�ؼ���ScrollView�����࣬�������̳���ScrollView���ص㡣
 */
class CC_GUI_DLL ListView : public ScrollView
{
 
    DECLARE_CLASS_GUI_INFO
public:

    /**
     * @~english
     * Gravity for docking elements in ListView.
     * @~chinese 
     * ListView��ͣ��Ԫ�������ķ���
     */
    enum class Gravity
    {
        LEFT,
        RIGHT,
        CENTER_HORIZONTAL,
        TOP,
        BOTTOM,
        CENTER_VERTICAL
    };
    
    /**
     * @~english
     * ListView element item click event.
     * @~chinese 
     * ListView�ؼ�Ԫ�صĵ���¼�����
     */
    enum class EventType
    {
        ON_SELECTED_ITEM_START,
        ON_SELECTED_ITEM_END
    };
    
    /**
     * ListView supports magnetic scroll.
     * With CENTER type, ListView tries to align its items in center of current view.
     * With BOTH_END type, ListView tries to align its items in left or right end if it is horizontal, top or bottom in vertical. The aligning side (left or right, top or bottom) is determined by user's scroll direction.
     */
    enum class MagneticType
    {
        NONE,
        CENTER,
        BOTH_END,
        LEFT,
        RIGHT,
        TOP,
        BOTTOM,
    };
    
    /**
     * ListView item click callback.
     * @~chinese 
     * ListView�ؼ�Ԫ�صĵ���ص���
     */
    typedef std::function<void(Ref*, EventType)> ccListViewCallback;
    
    /**
     * @~english
     * Default constructor
     * @~chinese 
     * Ĭ�Ϲ��캯��
     * @js ctor
     * @lua new
     */
    ListView();
    
    /**
     * @~english
     * Default destructor
     * @~chinese 
     * Ĭ�ϵ���������
     * @js NA
     * @lua NA
     */
    virtual ~ListView();
    
    /**
     * @~english
     * Create an empty ListView.
     * @~chinese 
     * ����һ����ListView
     * @return @~english A ListView instance.
     * @~chinese һ��ListViewʵ����
     */
    static ListView* create();
    
    /**
     * @~english
     * Set a item model for listview.
     * When calling `pushBackDefaultItem`, the model will be used as a blueprint and new model copy will be inserted into ListView.
     *
     * @~chinese 
     * �趨һ��ListView��ģ�͡�
     * ������`pushBackDefaultItem`����ģ�ͽ���Ϊһ����ͼ���¸����������뵽ListView�ؼ���
     *
     * @param model  @~english Model in `Widget*`.
     * @~chinese Widget��ģ��
     */
    void setItemModel(Widget* model);
    
    /**
     * @~english
     * Insert a default item(create by a cloned model) at the end of the listview.
     * @~chinese 
     * ����һ��Ĭ���ͨ����¡ģʽ��������ListView��β����
     */
    void pushBackDefaultItem();
    
    /**
     * @~english
     * Insert a default item(create by cloning model) into listview at a give index.
     * @~chinese 
     * ����һ��Ĭ���ͨ����¡ģʽ��������ListView��ָ��λ�á�
     * @param index  @~english A index in ssize_t.
     * @~chinese ָ����λ������
     */
    void insertDefaultItem(ssize_t index);
    
    /**
     * @~english
     * Insert a custom item into the end of ListView.
     * @~chinese 
     * ����һ���Զ����ListView��β����
     * @param item @~english A item in `Widget*`.
     * @~chinese һ��`Widget*`��Ŀ
     */
    void pushBackCustomItem(Widget* item);
    
    
    /**
     * @brief @~english Insert a custom widget into ListView at a given index.
     * @~chinese �����Զ��崰��С�ؼ���ListView��ָ����������
     * 
     * @param item @~english A widget pointer to be inserted.
     * @~chinese Ҫ�����һ��С�ؼ�ָ�롣
     *
     * @param index @~english A given index in ssize_t.
     * @~chinese ָ������
     */
    void insertCustomItem(Widget* item, ssize_t index);
    
    /**
     * @~english
     *  Removes the last item of ListView.
     * @~chinese 
     * ɾ��ListView���һ����Ŀ
     */
    void removeLastItem();
    
    /**
     * @~english
     * Remove a item at given index.
     *
     * @~chinese 
     * �ڸ���������ɾ��һ����Ŀ
     * 
     * @param index @~english A given index in ssize_t.
     * @~chinese ��������
     */
    void removeItem(ssize_t index);
    
    
    /**
     * @brief @~english Remove all items in current ListView.
     * @~chinese ɾ����ǰListView�е�������Ŀ��
     */
    void removeAllItems();
    
    /**
     * @~english
     * Return a item at a given index.
     *
     * @~chinese 
     * ����һ������������������Ŀ��
     * 
     * @param index @~english A given index in ssize_t.
     * @~chinese ����������
     *
     * @return @~english A widget instance.
     * @~chinese һ��С�ؼ�ʵ����
     */
    Widget* getItem(ssize_t index)const;
    
    /**
     * @~english
     * Return all items in a ListView.
     * @~chinese 
     * ����ListView�е�������Ŀ��
     *
     * @returns @~english A vector of widget pointers.
     * @~chinese һ���ؼ�ָ�����顣
     */
    Vector<Widget*>& getItems();
    
    /**
     * @~english
     * Return the index of specified widget.
     *
     * @~chinese 
     * ����ָ������С�ؼ���������
     * 
     * @param item  @~english A widget pointer.
     * @~chinese һ���ؼ�ָ�롣
     * @return @~english The index of a given widget in ListView.
     * @~chinese �����ؼ���ListView��������
     */
    ssize_t getIndex(Widget* item) const;
    
    /**
     * @~english
     * Set the gravity of ListView.
     * @~chinese 
     * ���õ�ListView������
     * @see `ListViewGravity`
     */
    void setGravity(Gravity gravity);
    
    /**
     * Set magnetic type of ListView.
     * @see `MagneticType`
     */
    void setMagneticType(MagneticType magneticType);
    
    /**
     * Get magnetic type of ListView.
     */
    MagneticType getMagneticType() const;
    
    /**
     * Set magnetic allowed out of boundary.
     */
    void setMagneticAllowedOutOfBoundary(bool magneticAllowedOutOfBoundary);
    
    /**
     * Query whether the magnetic out of boundary is allowed.
     */
    bool getMagneticAllowedOutOfBoundary() const;
    
    /**
     * Set the margin between each item in ListView.
     *
     * @~chinese 
     * ����ListView��ÿһ��֮��ı߾ࡣ
     * 
     * @param margin @~english margin
     * @~chinese �߾�
     */
    void setItemsMargin(float margin);
    
    
    /**
     * @brief @~english Query margin between each item in ListView.
     *
     * @~chinese ��ѯListViewÿ����֮��ı߾ࡣ
     *
     * @return @~english A margin in float.
     * @~chinese һ���߾ม����
     */
    float getItemsMargin()const;
    
    //override methods
    virtual void doLayout() override;
    virtual void requestDoLayout() override;
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    virtual void removeAllChildren() override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void removeChild(Node* child, bool cleaup = true) override;

	/**
	 * @brief Query the closest item to a specific position in inner container.
	 *
	 * @param targetPosition Specifies the target position in inner container's coordinates.
	 * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
	 * @return A item instance if list view is not empty. Otherwise, returns null.
	 */
	Widget* getClosestItemToPosition(const Vec2& targetPosition, const Vec2& itemAnchorPoint) const;
	
	/**
	 * @brief Query the closest item to a specific position in current view.
     * For instance, to find the item in the center of view, call 'getClosestItemToPositionInCurrentView(Vec2::ANCHOR_MIDDLE, Vec2::ANCHOR_MIDDLE)'.
	 *
	 * @param positionRatioInView Specifies the target position with ratio in list view's content size.
	 * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
	 * @return A item instance if list view is not empty. Otherwise, returns null.
	 */
	Widget* getClosestItemToPositionInCurrentView(const Vec2& positionRatioInView, const Vec2& itemAnchorPoint) const;
	
    /**
     * @brief Query the center item
     * @return A item instance.
     */
    Widget* getCenterItemInCurrentView() const;
    
    /**
     * @brief Query the leftmost item in horizontal list
     * @return A item instance.
     */
    Widget* getLeftmostItemInCurrentView() const;
    
    /**
     * @brief Query the rightmost item in horizontal list
     * @return A item instance.
     */
    Widget* getRightmostItemInCurrentView() const;
    
    /**
     * @brief Query the topmost item in horizontal list
     * @return A item instance.
     */
    Widget* getTopmostItemInCurrentView() const;
    
    /**
     * @brief Query the bottommost item in horizontal list
     * @return A item instance.
     */
    Widget* getBottommostItemInCurrentView() const;

    /**
     * Override functions
     */
    virtual void jumpToBottom() override;
    virtual void jumpToTop() override;
    virtual void jumpToLeft() override;
    virtual void jumpToRight() override;
    virtual void jumpToTopLeft() override;
    virtual void jumpToTopRight() override;
    virtual void jumpToBottomLeft() override;
    virtual void jumpToBottomRight() override;
    virtual void jumpToPercentVertical(float percent) override;
    virtual void jumpToPercentHorizontal(float percent) override;
    virtual void jumpToPercentBothDirection(const Vec2& percent) override;

    /**
     * @brief Jump to specific item
     * @param itemIndex Specifies the item's index
     * @param positionRatioInView Specifies the position with ratio in list view's content size.
     * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
     */
    void jumpToItem(int itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint);
    
	/**
	 * @brief Scroll to specific item
	 * @param positionRatioInView Specifies the position with ratio in list view's content size.
	 * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
	 * @param timeInSec Scroll time
	 */
    void scrollToItem(int itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint);
	void scrollToItem(int itemIndex, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint, float timeInSec);
	
    /**
     * @brief Query current selected widget's idnex.
     *
     * @return @~english A index of a selected item.
     * @~chinese ѡ�еĿؼ���������
     */
    ssize_t getCurSelectedIndex() const;
    
    /**
     * @~english
     * Add a event click callback to ListView, then one item of Listview is clicked, the callback will be called.
     * @~chinese 
     * ���ListView����¼��Ļص���ListView�е�һ����Ŀ�����������ûص�������
     * @deprecated @~english Use  `addEventListener` instead.
     * @~chinese ʹ��addEventListener���档
     * @param target @~english A pointer of `Ref*` type.
     * @~chinese һ��`Ref*`ָ��
     * @param selector @~english A member function pointer with type of `SEL_ListViewEvent`.
     * @~chinese `SEL_ListViewEvent`���͵ĳ�Ա����ָ�롣
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerListView(Ref* target, SEL_ListViewEvent selector);

    /**
     * @~english
     * Add a event click callback to ListView, then one item of Listview is clicked, the callback will be called.
     * @~chinese 
     * ���ListView����¼��Ļص���ListView�е�һ����Ŀ�����������ûص�������
     * @param callback @~english A callback function with type of `ccListViewCallback`.
     * @~chinese һ��ccListViewCallback���͵Ļص�������
     */
    void addEventListener(const ccListViewCallback& callback);
    using ScrollView::addEventListener;

    /**
     * @~english
     * Changes scroll direction of ListView.
     *  Direction Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll.
     *
     * @~chinese 
     * �ı�ListView�Ĺ�������
     * Direction Direction::VERTICAL��ζ�Ŵ�ֱ����,Direction::HORIZONTAL��ζ��ˮƽ������
     *
     * @param dir @~english Set the list view's scroll direction.
     * @~chinese ����ListView�Ĺ�������
     */
    virtual void setDirection(Direction dir) override;
    
    virtual std::string getDescription() const override;
    
    /**
     * @brief @~english Refresh view and layout of ListView manually.
     * This method will mark ListView content as dirty and the content view will be refreshed in the next frame.
     * @~chinese �ֶ�ˢ��view��ListView�Ĳ��֡�
     * �÷������б���ͼ���ݱ��Ϊdirty��������ͼ������һ֡ˢ�¡�
     */
    CC_DEPRECATED_ATTRIBUTE void requestRefreshView();

    
    /**
     * @brief @~english Refresh content view of ListView.
     * @~chinese ����ListView����ͼ��
     */
    CC_DEPRECATED_ATTRIBUTE void refreshView();

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void handleReleaseLogic(Touch *touch) override;
    
    void updateInnerContainerSize();
    void remedyLayoutParameter(Widget* item);
    void remedyVerticalLayoutParameter(LinearLayoutParameter* layoutParameter, ssize_t itemIndex);
    void remedyHorizontalLayoutParameter(LinearLayoutParameter* layoutParameter,ssize_t itemIndex);
    
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    void selectedItemEvent(TouchEventType event);
    virtual void interceptTouchEvent(Widget::TouchEventType event,Widget* sender,Touch* touch) override;
    
    virtual Vec2 getHowMuchOutOfBoundary(const Vec2& addition = Vec2::ZERO) override;
    
    virtual void startAttenuatingAutoScroll(const Vec2& deltaMove, const Vec2& initialVelocity) override;
    
    void startMagneticScroll();
    
protected:
    Widget* _model;
    
    Vector<Widget*> _items;
    
    Gravity _gravity;
    
    MagneticType _magneticType;
    bool _magneticAllowedOutOfBoundary;
    
    float _itemsMargin;
    
    ssize_t _curSelectedIndex;

    bool _innerContainerDoLayoutDirty;
    
    Ref*       _listViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_ListViewEvent    _listViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccListViewCallback _eventCallback;
};

}
NS_CC_END
// end of ui group
/// @}

#endif /* defined(__ListView__) */
