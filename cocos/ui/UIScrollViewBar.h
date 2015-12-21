/****************************************************************************
Copyright (c) 2015 Neo Kim (neo.kim@neofect.com)

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

#ifndef __UISCROLLVIEWBAR_H__
#define __UISCROLLVIEWBAR_H__

#include "ui/UIScrollView.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

class Sprite;

namespace ui {

/**@~english
 * Scroll bar being attached to ScrollView layout container.
 * @~chinese 
 * ��ӵ�ScrollView���������Ĺ�������
 */
class CC_GUI_DLL ScrollViewBar : public ProtectedNode
{

public:
    /**@~english
     * Default constructor
     * @~chinese 
     * Ĭ�Ϲ��캯��
     * @js ctor
     * @lua new
     */
    ScrollViewBar(ScrollView* parent, ScrollView::Direction direction);
    
    /**@~english
     * Default destructor
     * @~chinese 
     * Ĭ�ϵ���������
     * @js NA
     * @lua NA
     */
    virtual ~ScrollViewBar();
    
    /**@~english
     * Create a ScrollViewBar with its parent ScrollView and direction.
     * @~chinese 
     * ͨ��һ��ScrollView����������򴴽�һ��ScrollViewBar
     * @return @~english A ScrollViewBar instance.
     * @~chinese һ��ScrollViewBarʵ����
     */
    static ScrollViewBar* create(ScrollView* parent, ScrollView::Direction direction);
    
    /**
     * @brief @~english Set the scroll bar position from the left-bottom corner (horizontal) or right-top corner (vertical).
     *
     * @~chinese ���ù�������λ��, ����ƫ��ˮƽ�������½ǻ�ֱ�������Ͻǵľ���������
     * 
     * @param positionFromCorner @~english The position from the left-bottom corner (horizontal) or right-top corner (vertical).
     * @~chinese ƫ��ˮƽ�������½ǻ�ֱ�������Ͻǵľ���
     */
    void setPositionFromCorner(const Vec2& positionFromCorner);
    
    /**
     * @brief @~english Get the scroll bar position from the left-bottom corner (horizontal) or right-top corner (vertical).
     *
     * @~chinese ��ȡƫ��ˮƽ�������½ǻ�ֱ�������Ͻǵľ���
     * 
     * @return @~english A Vec2 struct.
     * @~chinese һ��������.
     */
    Vec2 getPositionFromCorner() const;
    
    /**
     * @brief @~english Set the scroll bar's width
     *
     * @~chinese ���ù������Ŀ��
     * 
     * @param width @~english The scroll bar's width
     * @~chinese �������Ŀ��
     */
    void setWidth(float width);
    
    /**
     * @brief @~english Get the scroll bar's width
     *
     * @~chinese ��ȡ�������Ŀ��
     * 
     * @return @~english the scroll bar's width
     * @~chinese �������Ŀ��
     */
    float getWidth() const;
    
    /**
     * @brief @~english Set scroll bar auto hide state
     *
     * @~chinese ���ù������Զ�����״̬
     * 
     * @param scroll @~english bar auto hide state
     * @~chinese �Ƿ��Զ�����״̬��
     */
    void setAutoHideEnabled(bool autoHideEnabled);
    
    /**
     * @brief @~english Query scroll bar auto hide state
     *
     * @~chinese ��ѯ�������Զ�����״̬
     * 
     * @return @~english True if scroll bar auto hide is enabled, false otherwise.
     * @~chinese ��������˹������Զ�����,�򷵻���,���򷵻ؼ١�
     */
    bool isAutoHideEnabled() const { return _autoHideEnabled; }
    
    /**
     * @brief @~english Set scroll bar auto hide time
     *
     * @~chinese ���ù������Զ�����ʱ��
     * 
     * @param scroll @~english bar auto hide time
     * @~chinese �������Զ����ص�ʱ��
     */
    void setAutoHideTime(float autoHideTime) { _autoHideTime = autoHideTime; }
    
    /**
     * @brief @~english Get the scroll bar's auto hide time
     *
     * @~chinese ��ȡ���������Զ�����ʱ��
     * 
     * @return @~english the scroll bar's auto hide time
     * @~chinese ���������Զ�����ʱ��
     */
    float getAutoHideTime() const { return _autoHideTime; }
    
    /**
     * @brief @~english This is called by parent ScrollView when the parent is scrolled. Don't call this directly.
     *
     * @~chinese ��ScrollView������ʱ�����ô˷��������¹������������߲���Ҫֱ�ӵ��������
     * 
     * @param amount @~english how much the inner container of ScrollView is out of boundary
     * @~chinese ScrollView���ڲ������ĳ����˶��ٱ߽�
     */
    virtual void onScrolled(const Vec2& outOfBoundary);
    
    /**
     * @lua NA
     */
    virtual void setOpacity(GLubyte opacity) override { _opacity = opacity; }
    virtual GLubyte getOpacity() const override { return _opacity; }
    virtual void onEnter() override;
    virtual void update(float deltaTime) override;
    
    /**
     * @brief @~english This is called by parent ScrollView when a touch is began. Don't call this directly.
     * @~chinese ��ScrollView�Ĵ������鿪ʼ��ʱ�����ô˷����������߲���Ҫֱ�ӵ��������
     */
    void onTouchBegan();
    
    /**
     * @brief @~english This is called by parent ScrollView when a touch is ended. Don't call this directly.
     * @~chinese ��ScrollView�Ĵ����¼�������ʱ�����ô˷����������߲���Ҫֱ�ӵ��������
     */
    void onTouchEnded();
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
private:
    float calculateLength(float innerContainerMeasure, float scrollViewMeasure, float outOfBoundaryValue);
    Vec2 calculatePosition(float innerContainerMeasure, float scrollViewMeasure, float innerContainerPosition, float outOfBoundaryValue, float actualLength);
    
    void updateLength(float length);
    void processAutoHide(float deltaTime);
    
    ScrollView* _parent;
    ScrollView::Direction _direction;
    
    Sprite* _upperHalfCircle;
    Sprite* _lowerHalfCircle;
    Sprite* _body;
    
    GLubyte _opacity;
    
    float _marginFromBoundary;
    float _marginForLength;

    bool _touching;
    
    bool _autoHideEnabled;
    float _autoHideTime;
    float _autoHideRemainingTime;
    
};

}
// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UISCROLLVIEWBAR_H__) */
