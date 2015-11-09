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

#ifndef __cocos2d_libs__LayoutComponent__
#define __cocos2d_libs__LayoutComponent__
#include "2d/CCComponent.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {

    /**
     * @brief @~english A component class used for layout.
     * The LayoutComponent holds all the data for layouting.
     * @~chinese ����layout������ࡣ
     * LayoutComponent������������ڲ��ֵ����ݡ�
     */
    class CC_GUI_DLL LayoutComponent : public Component
    {
    public:

        /**
         * @~english
         * Default constructor
         *
         * @~chinese 
         * Ĭ�Ϲ��캯��
         * 
         * @lua new
         */
        LayoutComponent();

        /**
         * @~english
         * Default destructor
         *
         * @~chinese 
         * Ĭ�ϵ���������
         * 
         * @lua NA
         */
        ~LayoutComponent();

        virtual bool init()override;

        /**
         * @~english
         * Create a LayoutComponent instance with default settings.
         * @~chinese 
         * ��Ĭ�����ô���һ��LayoutComponentʵ����
         */
        CREATE_FUNC(LayoutComponent);

        /**
         * @~english
         * Bind a LayoutComponent to a specified node.
         * If the node has already binded a LayoutComponent named __LAYOUT_COMPONENT_NAME, just return the LayoutComponent.
         * Otherwise, create a new LayoutComponent and bind the LayoutComponent to the node.
         * @~chinese 
         * ��LayoutComponent�󶨵�һ��ָ���Ľڵ㡣
         * ����ڵ��Ѿ���һ������__LAYOUT_COMPONENT_NAME��LayoutComponent,��ֻ����LayoutComponent��
         * ���򣬴���һ���µ�LayoutComponent����LayoutComponent���ڵ㡣
         * @param node @~english A Node* instance pointer.
         * @~chinese һ���ڵ�ָ��
         * @return @~english The binded LayoutComponent instance pointer.
         * @~chinese ��LayoutComponentʵ����ָ�롣
         */
        static LayoutComponent* bindLayoutComponent(Node* node);

        /**
         * @~english
         * Horizontal dock position type.
         * @~chinese 
         * ˮƽͣ��λ�����͡�
         */
        enum class HorizontalEdge
        {
            None,
            Left,
            Right,
            Center
        };

        /**
         * @~english
         * Vertical dock position type.
         * @~chinese 
         * ��ֱͣ��λ�����͡�
         */
        enum class VerticalEdge
        {
            None,
            Bottom,
            Top,
            Center
        };

        /**
         * @~english
         * Percent content size is used to adapt node's content size based on parent's content size.
         * If set to true then node's content size will be changed based on the value setted by @see setPercentContentSize
         * @~chinese 
         * ���ݸ��ڵ�����ݴ�С���ٷֱȵ����ڵ�����ݴ�С��
         * �������Ϊtrue������ڸ��ڵ����ı�����Ĵ�С��@see setPercentContentSize
         *
         * @param isUsed @~english True to enable percent content size, false otherwise.
         * @~chinese �����򷵻�true��δ�����򷵻�false��
         */
        void setUsingPercentContentSize(bool isUsed);

        /**
         * @~english
         * Query whether use percent content size or not.
         * @~chinese 
         * ��ѯ�Ƿ����˰ٷֱȿ������ݴ�С��
         * @return @~english True if using percent content size, false otherwise.
         * @~chinese ��������˰ٷֱȿ��ƴ�С�򷵻�true,���򷵻�false��
         */
        bool getUsingPercentContentSize()const;

        /**
         * @~english
         * Set percent content size.
         * The value should be [0-1], 0 means the child's content size will be 0
         * and 1 means the child's content size is the same as its parents.
         * @~chinese 
         * ���ðٷֱȴ�С��
         * ֵӦ����0 - 1֮��, 0��ζ���ӽڵ�����ݴ�СΪ0
         * 1��ζ���ӽڵ�����ݴ�С���丸�ڵ�һ����
         * @param percent @~english The percent (x,y) of the node in [0-1] scope.
         * @~chinese �ٷֱ�(x,y)����(0 - 1)��Χ�ڡ�
         */
        void setPercentContentSize(const Vec2 &percent);

        /**
         * @~english
         * Query the percent content size value.
         * @~chinese 
         * ��ѯ���ݴ�С�ٷֱ�ֵ��
         * @return @~english Percet (x,y) in Vec2.
         * @~chinese Vec2���͵İٷֱ�����(x,y)��
         */
        Vec2 getPercentContentSize()const;

        /**
         * @~english
         * Query the anchor position.
         * @~chinese 
         * ��ѯê���λ�á�
         * @return @~english Anchor position to it's parent
         * @~chinese ê���λ��
         */
        const Point& getAnchorPosition()const;

        /**
         * @~english
         * Change the anchor position to it's parent.
         * @~chinese 
         * ����ê���λ��
         * @param point @~english A value in (x,y) format.
         * @~chinese һ��(x,y)��ʽ��ֵ��
         */
        void setAnchorPosition(const Point& point);

        /**
         * @~english
         * Query the owner's position.
         * @~chinese 
         * ��ѯ���component�����ߵ�λ�á�
         * @return @~english The owner's position.
         * @~chinese λ������
         */
        const Point& getPosition()const;

        /**
         * @~english
         * Change the position of component owner.
         * @~chinese 
         * ����component�����ߵ�λ��
         * @param position @~english A position in (x,y)
         * @~chinese λ������(x,y)
         */ 
        void setPosition(const Point& position);

        /**
         * @~english
         * Whether position percentX is enabled or not. 
         * @~chinese 
         * �Ƿ�����percentX������λ�á�
         * @return @~english True if position percertX is enable, false otherwise.
         * @~chinese ��������򷵻�true�����򷵻�false��
         */
        bool isPositionPercentXEnabled()const;
        
        /**
         * @~english
         * Toggle position percentX enabled.
         * @~chinese 
         * percentX�ٷֱȶ�λ���ء�
         * @param isUsed  @~english True if enable position percentX, false otherwise.
         * @~chinese �������true����������false�رա�
         */
        void setPositionPercentXEnabled(bool isUsed);

        /**
         * @~english
         * Query the position percent X value.
         * @~chinese 
         * ��ѯx��İٷֱȶ�λ��Ϣ
         *@return @~english Position percent X value in float.
         * @~chinese һ���ٷֱȵ�x����ֵ
         */
        float getPositionPercentX()const;

        /**
         * @~english
         * Change position percent X value.
         * @~chinese 
         * �ı�x���ϵİٷֱȶ�λֵ
         * @param percentMargin @~english Margin in float.
         * @~chinese һ��������
         */
        void setPositionPercentX(float percentMargin);

        /**
         * @~english
         * Whether position percentY is enabled or not.
         * @~chinese 
         * �Ƿ���percentY��y��İٷֱȶ�λ
         * @see `setPositionPercentYEnabled`
         * @return @~english True if position percentY is enabled, false otherwise.
         * @~chinese ��������򷵻�true�����򷵻�false
         */
        bool isPositionPercentYEnabled()const;

        /**
         * @~english
         * Toggle position percentY enabled.
         * @~chinese 
         * y��ٷֱȶ�λpercentY���ÿ���
         * @param isUsed @~english True if position percentY is enabled, false otherwise.
         * @~chinese �������true����y��İٷֱȶ�λ������false��ر�
         */
        void setPositionPercentYEnabled(bool isUsed);

        /**
         * @~english
         * Query the position percentY Y value.
         * @~chinese 
         * ��ѯy��İٷֱȶ�λֵpercentY
         * @return @~english Position percent Y value in float.
         * @~chinese y��İٷֱȶ�λ����ֵ
         */
        float getPositionPercentY()const;

        /**
         * @~english
         * Change position percentY value.
         * @~chinese 
         * �ı�y��İٷֱȶ�λ��ϢpercentY
         * @param percentMargin @~english Margin in float.
         * @~chinese һ������ֵ
         */
        void setPositionPercentY(float percentMargin);

        /**
         * @~english
         * Query element horizontal dock type.
         * @~chinese 
         * ��ѯԪ��ˮƽ��������͡�
         * @return @~english Horizontal dock type.
         * @~chinese ˮƽ�������͡�
         */
        HorizontalEdge getHorizontalEdge()const;

        /**
         * @~english
         * Change element's horizontal dock type.
         * @~chinese 
         * ����Ԫ�ص�ˮƽ��������
         * @param hEage @~english Horizontal dock type @see `HorizontalEdge`
         * @~chinese ˮƽ��������
         */
        void setHorizontalEdge(HorizontalEdge hEage);

        /**
         * @~english
         * Query element vertical dock type.
         * @~chinese 
         * ��ѯԪ�ش�ֱ��λ���͡�
         *@return @~english Vertical dock type.
         * @~chinese ��ֱ��λ���͡�
         */
        VerticalEdge getVerticalEdge()const;

        /**
         * @~english
         * Change element's vertical dock type.
         * @~chinese 
         * �ı�Ԫ�صĴ�ֱ��λ���͡�
         * @param vEage @~english Vertical dock type @see `VerticalEdge`.
         * @~chinese ��ֱ��λ����
         */
        void setVerticalEdge(VerticalEdge vEage);

        /**
         * @~english
         * Query left margin of owner relative to its parent.
         * @~chinese 
         * ��ȡ�����ߵ���߾�
         * @return @~english Left margin in float.
         * @~chinese ��߾ม����
         */
        float getLeftMargin()const;

        /**
         * @~english
         * Change left margin of owner relative to its parent.
         * @~chinese 
         * ���������ߵ���߾�
         * @param margin @~english Margin in float.
         * @~chinese ��߾ม����
         */
        void setLeftMargin(float margin);

        /**
         * @~english
         * Query the right margin of owner relative to its parent.
         * @~chinese 
         * ��ȡ�����ߵ��ұ߾�
         * @return @~english Right margin in float.
         * @~chinese �ұ߾ม����
         */
        float getRightMargin()const;

        /**
         * @~english
         * Change right margin of owner relative to its parent.
         * @~chinese 
         * ���������ߵ��ұ߾�
         * @param margin @~english Margin in float.
         * @~chinese �ұ߾ม����
         */
        void setRightMargin(float margin);

        /**
         * @~english
         * Query the top margin of owner relative to its parent.
         * @~chinese 
         * ��ȡ�����ߵ��ϱ߾�
         * @return @~english Top margin in float.
         * @~chinese �ϱ߾ม����
         */
        float getTopMargin()const;

        /**
         * @~english
         * Change the top margin of owner relative to its parent.
         * @~chinese 
         * ���������ߵ��ϱ߾�
         * @param margin @~english Margin in float.
         * @~chinese �ϱ߾ม����
         */
        void setTopMargin(float margin);

        /**
         * @~english
         * Query the bottom margin of owner relative to its parent.
         * @~chinese 
         * ��ȡ�����ߵ��±߾�
         * @return @~english Bottom margin in float.
         * @~chinese �±߾ม����
         */
        float getBottomMargin()const;

        /**
         * @~english
         * Change the bottom margin of owner relative to its parent.
         * @~chinese 
         * ���������ߵ��±߾�
         * @param margin @~english in float.
         * @~chinese �±߾ม����
         */
        void setBottomMargin(float margin);

        /**
         * @~english
         * Query owner's content size.
         * @~chinese 
         * ��ȡ���������ݵĳߴ�
         * @return @~english Owner's content size.
         * @~chinese �����ߵ����ݳߴ�
         */
        const Size& getSize()const;

        /**
         * @~english
         * Change the content size of owner.
         * @~chinese 
         * ���������ߵ����ݳߴ�
         * @param size @~english Content size in @see `Size`.
         * @~chinese ���ݳߴ�
         */
        void setSize(const Size& size);

        /**
         * @~english
         * Query whether percent width is enabled or not.
         * @~chinese 
         * ��ѯ�Ƿ������˰ٷֱȿ��ƿ��
         * @return @~english True if percent width is enabled, false, otherwise.
         * @~chinese ��������򷵻�true�����򷵻�false
         */
        bool isPercentWidthEnabled()const;

        /**
         * @~english
         * Toggle enable percent width.
         * @~chinese 
         * �ٷֱȿ��ƿ�ȵĿ���
         * @param isUsed @~english True if percent width is enabled, false otherwise.
         * @~chinese �������true�����ٷֱȿ��ƿ�ȣ�����false��Ϊ�ر�
         */
        void setPercentWidthEnabled(bool isUsed);

        /**
         * @~english
         * Query content size width of owner.
         * @~chinese 
         * ��ѯ�����ߵ����ݿ�ȡ�
         * @return @~english Content size width in float.
         * @~chinese ���ݿ�ȸ�������
         */
        float getSizeWidth()const;

        /**
         * @~english
         * Change content size width of owner.
         * @~chinese 
         * ���������ߵ����ݿ��
         * @param width @~english Content size width in float.
         * @~chinese ���ݿ�ȸ�����
         */
        void setSizeWidth(float width);

        /**
         * @~english
         * Query percent width of owner.
         * @~chinese 
         * ��ѯ�����ߵİٷֱȿ�ȡ�
         * @return @~english percent width in float.
         * @~chinese �ٷֱȿ�ȸ�������
         */
        float getPercentWidth()const;

        /**
         * @~english
         * Change percent width of owner.
         * @~chinese 
         * ���������ߵİٷֱȿ��
         * @param percentWidth @~english Percent Width in float.
         * @~chinese �ٷֱȿ�ȸ�����
         */
        void setPercentWidth(float percentWidth);

        /**
         * @~english
         * Query whether percent height is enabled or not.
         * @~chinese 
         * ��ѯ�Ƿ����ðٷֱȿ��Ƹ߶�
         * @return @~english True if percent height is enabled, false otherwise.
         * @~chinese ��������򷵻�true�����򷵻�false
         */
        bool isPercentHeightEnabled()const;

        /**
         * @~english
         * Toggle enable percent height.
         * @~chinese 
         * �ٷֱȿ��Ƹ߶ȵĿ���
         * @param isUsed @~english True if percent height is enabled, false otherwise.
         * @~chinese ����true�����ٷֱȿ��Ƹ߶ȣ�����Ϊ�ر�
         */
        void setPercentHeightEnabled(bool isUsed);

        /**
         * @~english
         * Query size height of owner.
         * @~chinese 
         * ��ѯ�����ߵĸ߶ȴ�С
         * @return @~english Size height in float.
         * @~chinese �߶ȸ�����
         */
        float getSizeHeight()const;

        /**
         * @~english
         * Change size height of owner.
         * @~chinese 
         * �ı������ߵĸ߶�
         * @param height @~english Size height in float.
         * @~chinese �߶�(������)
         */
        void setSizeHeight(float height);

        /**
         * @~english
         * Query percent height of owner.
         * @~chinese 
         * ��ȡ�����ߵİٷֱȸ߶�
         * @return @~english Percent height in float.
         * @~chinese �߶Ȱٷֱ�(������)
         */
        float getPercentHeight()const;

        /**
         * @~english
         * Change percent height value of owner.
         * @~chinese 
         * ���ø߶Ȱٷֱ�
         * @param percentHeight @~english Percent height in float.
         * @~chinese �߶Ȱٷֱ�(������)
         */
        void setPercentHeight(float percentHeight);

        /**
         * @~english
         * Query whether stretch width is enabled or not.
         * @~chinese 
         * ��ѯ�Ƿ������Զ�������ȡ�
         * @return @~english True if stretch width is enabled, false otherwise.
         * @~chinese ����������򷵻�true�����򷵻�false
         */
        bool isStretchWidthEnabled()const;

        /**
         * @~english
         * Toggle enable stretch width.
         * @~chinese 
         * ���ùر��Զ�������ȵĿ���
         * @param isUsed @~english True if enable stretch width, false otherwise.
         * @~chinese �������true����������false��ر�
         */
        void setStretchWidthEnabled(bool isUsed);

        /**
         * @~english
         * Query whether stretch height is enabled or not.
         * @~chinese 
         * ��ѯ�Ƿ������Զ������߶�
         * @return @~english True if stretch height is enabled, false otherwise.
         * @~chinese ����������򷵻�true�����򷵻�false
         */
        bool isStretchHeightEnabled()const;

        /**
         * @~english
         * Toggle enable stretch height.
         * @~chinese 
         * ���ùر��Զ������߶ȵĿ���
         * @param isUsed @~english True if stretch height is enabled, false otherwise.
         * @~chinese �������true����������false��ر�
         */
        void setStretchHeightEnabled(bool isUsed);
        
        /**
         * @~english
         * Toggle enable percent only.
         * @~chinese 
         * ����ʹ�ðٷֱȵĿ���
         * @param enable @~english True if percent only is enabled, false otherwise.
         * @~chinese ����true���ʹ�ðٷֱ����ݣ�false���ʹ�õ�����
         */
        void setPercentOnlyEnabled(bool enable);

        /**
         * @~english
         * Toggle active enabled of LayoutComponent's owner.
         * @~chinese 
         * LayoutComponent�������Ƿ񼤻�Ŀ���
         * @param enable @~english True if active layout component, false otherwise.
         * @~chinese �������true�򼤻����ر�
         */
        void setActiveEnabled(bool enable);

        /**
         * @~english
         * Refresh layout of the owner.
         * @~chinese 
         * ˢ�������ߵĲ�����Ϣ��
         */
        void refreshLayout();

    protected:
        Node* getOwnerParent();
        void refreshHorizontalMargin();
        void refreshVerticalMargin();
    protected:
        HorizontalEdge  _horizontalEdge;
        VerticalEdge    _verticalEdge;

        float           _leftMargin;
        float           _rightMargin;
        float           _bottomMargin;
        float           _topMargin;

        bool            _usingPositionPercentX;
        float           _positionPercentX;
        bool            _usingPositionPercentY;
        float           _positionPercentY;

        bool            _usingStretchWidth;
        bool            _usingStretchHeight;

        float           _percentWidth;
        bool            _usingPercentWidth;
        
        float           _percentHeight;
        bool            _usingPercentHeight;

        bool            _actived;
        bool            _isPercentOnly;
    };
}

// end of ui group
/// @}
NS_CC_END
#endif /* defined(__cocos2d_libs__LayoutComponent__) */
