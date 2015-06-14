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

#ifndef __CCDISPLAYMANAGER_H__
#define __CCDISPLAYMANAGER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDecorativeDisplay.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

class Bone;

/**
 *  @~english DisplayManager manages Bone's display
 * @~chinese ��ʾ�������������ͷ����ʾ��
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DisplayManager : public cocos2d::Ref
{
public:
    static DisplayManager *create(Bone *bone);

public:
    DisplayManager();
    ~DisplayManager();

    bool init(Bone *bone);

    /**
     * @~english Use BoneData to init the display list.
     * If display is a sprite, and it have texture info in the TexutreData, then use TexutreData to init the display's anchor point.
     * If the display is a Armature, then create a new Armature.
     * @~chinese ʹ�ù�ͷ��������ʼ����ʾ�б������ʾΪ���鲢�����ڲ����������в�����Ϣ��
     * ��ôʹ�ò������ݳ�ʼ����ʾ��ê�㡣�����ʾΪ��������ô����һ���¹�����
     * @param boneData @~english Bone data.
     * @~chinese �������ݡ�
     */
    virtual void initDisplayList(BoneData *boneData);

    /**
     * @~english Add display and use  _DisplayData init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     * @~chinese �����ʾ��ʹ��_DisplayData����ʼ����ʾ������������Ѿ�����ʾ�����串�ǡ�
     * �������Ϊ��ǰ��ʾ��������ͬʱ����ʾ����Ϊ_index����ʾ��
     *
     *	@param 	displayData @~english it include the display information, like DisplayType.
     *					If you want to create a sprite display, then create a `SpriteDisplayData` param
     * @~chinese ��ʾ���ݣ�������ʾ��Ϣ��������ʾ���ࡣ
     * Ҫ����һ��������ʾ���򴴽�һ��`SpriteDisplayData`������
     *
     *	@param 	index @~english the index of the display you want to replace or add to
     *					-1 : append display from back
     * @~chinese Ҫ��ӻ򸲸ǵ���ʾ��������Ϊ-1ʱ����ʾ��������
     */
    void addDisplay(DisplayData *displayData, int index);

    /**
    * @~english Add node and use node to init the display.
    * If index already have a display, then replace it.
    * If index is current display index, then also change display to _index
    * @~chinese Ϊ��ͷ���ӽڵ㣬��ʹ�ýڵ�����ʼ����ʾ�ԡ�
    * ���������������ʾ�����串�ǡ�
    * �������Ϊ��ǰ��ʾ��������ͬʱ����ʾ����Ϊ_index����ʾ��
    * @param display @~english The node to add.
    * @~chinese Ҫ��ӵĽڵ㡣
    * @param index @~english The index of the display you want to replace or add to
    *          -1 : append display from back
    * @~chinese Ҫ��ӻ򸲸ǵ���ʾ��������Ϊ-1ʱ����ʾ��������
    */
    void addDisplay(cocos2d::Node *display, int index);

    /**
    * @~english Remove a display.
    * @~chinese Ϊ��ͷ�Ƴ���ʾ��
    * @param index @~english The index of the display you want to remove.
    * @~chinese Ҫ�Ƴ�����ʾ��������
    */
    void removeDisplay(int index);

    /**
    * @~english Get list of decorative display.
    * @~chinese ���װ����ʾ�б�
    * @return @~english The list of decorative display.
    * @~chinese װ����ʾ�б�
    */
    const cocos2d::Vector<DecorativeDisplay*>& getDecorativeDisplayList() const;

    /** @deprecated Use `changeDisplayWithIndex(int index, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    /** @deprecated Use `changeDisplayWithName(const std::string& name, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);
    
    /**
     * @~english Change display by index. You can just use this method to change display in the display list.
     * The display list is just used for this bone, and it is the displays you may use in every frame.
     *
     * Note : if index is the same with prev index, the method will not effect.
     *
     * @~chinese ͨ�������ı���ʾ������ͨ���˷����ı���ʾ�б��е���ʾ��
     * ��ʾ�б��Ϊ��ǰ��ͷʹ�ã��ǿ���ÿ֡��ʹ�õ���ʾ��
     *
     * @param index @~english The index of the display you want to change
     * @~chinese Ҫ�ı����ʾ��������
     * @param force @~english If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
     * @~chinese ���Ϊ�棬ǿ�ƽ���ʾ��Ϊָ������ʾ�����ߵ�ǰ����ʾ�ᱻ����Ϊ��flash��ÿ���ؼ�֡�б༭����ʾ����ֵ��
     */
    void changeDisplayWithIndex(int index, bool force);

    /**
    * @~english Change display by name. You can just use this method to change display in the display list.
    * The display list is just used for this bone, and it is the displays you may use in every frame.
    *
    * Note : if index is the same with prev index, the method will not effect.
    *
    * @~chinese ͨ�����Ƹı���ʾ������ͨ���˷����ı���ʾ�б��е���ʾ��
    * ��ʾ�б��Ϊ��ǰ��ͷʹ�ã��ǿ���ÿ֡��ʹ�õ���ʾ��
    *
    * @param name @~english The name of the display you want to change
    * @~chinese Ҫ�ı����ʾ�����ơ�
    * @param force @~english If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
    * @~chinese ���Ϊ�棬ǿ�ƽ���ʾ��Ϊָ������ʾ�����ߵ�ǰ����ʾ�ᱻ����Ϊ��flash��ÿ���ؼ�֡�б༭����ʾ����ֵ��
    */
    void changeDisplayWithName(const std::string& name, bool force);

    /**
    * @~english Get display render node.
    * @~chinese �����ʾ��Ⱦ�ڵ㡣
    * @return @~english The display render node.
    * @~chinese ��ʾ��Ⱦ�ڵ㡣
    */
    cocos2d::Node *getDisplayRenderNode() const;
    /**
    * @~english Get type of display render node.
    * @~chinese �����ʾ��Ⱦ�ڵ����͡�
    * @return @~english The type of display render node.
    * @~chinese ��ʾ��Ⱦ�ڵ����͡�
    */
    DisplayType getDisplayRenderNodeType() const;

    /**
    * @~english Get current display index.
    * @~chinese ��õ�ǰ��ʾ������
    * @return @~english Current display index.
    * @~chinese ��ʾ��ǰ��ʾ������
    */
    int getCurrentDisplayIndex() const;

    /**
    * @~english Set current decorative display.
    * @~chinese ���õ�ǰװ����ʾ��
    * @param decoDisplay @~english Current decorative display.
    * @~chinese ��ǰװ����ʾ��
    */
    virtual void setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay);
    /**
    * @~english Get current decorative display.
    * @~chinese ��ȡ��ǰװ����ʾ��
    * @return @~english Current decorative display.
    * @~chinese ��ǰװ����ʾ��
    */
    virtual DecorativeDisplay *getCurrentDecorativeDisplay() const;
    /**
    * @~english Get current decorative display by index.
    * @~chinese ͨ��������ȡ��ǰװ����ʾ��
    * @param index @~english Index of display.
    * @~chinese ��ʾ��������
    * @return @~english Current decorative display.
    * @~chinese ��ǰװ����ʾ��
    */
    virtual DecorativeDisplay *getDecorativeDisplayByIndex(int index) const;

    /**
     * @~english Sets whether the display is visible.
     * The default value is true, a node is default to visible.
     * @~chinese ������ʾ�Ƿ�ɼ���Ĭ�Ϻͽڵ�һ��Ϊ�ɼ���
     *
     * @param visible @~english True if the node is visible, false if the node is hidden.
     * @~chinese �ڵ�ɼ�ʱΪ�棬����Ϊ�١�
     */
    virtual void setVisible(bool visible);
    /**
     * @~english Determines if the display is visible
     * @~chinese �����ʾ�Ƿ�ɼ���
     *
     * @see setVisible(bool)
     * @return @~english true if the node is visible, false if the node is hidden.
     * @~chinese �ڵ�ɼ�ʱΪ�棬����Ϊ�١�
     */
    virtual bool isVisible() const;

    /**
    * @see Node:getContentSize().
    */
    cocos2d::Size getContentSize() const;
    /**
    * @see Node:getBoundingBox().
    */
    cocos2d::Rect getBoundingBox() const;

    /**
    * @see Node:getAnchorPoint().
    */
    cocos2d::Vec2 getAnchorPoint() const;
    /**
    * @see Node:getAnchorPointInPoints().
    */
    cocos2d::Vec2 getAnchorPointInPoints() const;

    /**
    * @~english Check if the position is inside the bone.
    * @~chinese ���λ�õ������Ƿ��ڹ�ͷ�С�
    * @param _point @~english The point to be checked.
    * @~chinese Ҫ���ĵ㡣
    */
    virtual bool containPoint(cocos2d::Vec2 &_point);

    /**
     * @~english Check if the position is inside the bone.
     * @~chinese ���λ�õ������Ƿ��ڹ�ͷ�С�
     * @param x @~english The x of point to be checked.
     * @~chinese Ҫ���ĵ�x���ꡣ
     * @param y @~english The y of point to be checked.
     * @~chinese Ҫ���ĵ�y���ꡣ
     */
    virtual bool containPoint(float x, float y);

    /**
    * @~english Set force change display.
    * @~chinese �����Ƿ�ǿ�Ƹı���ʾ��
    * @param force @~english Is force change display.
    * @~chinese �Ƿ�ǿ�Ƹı���ʾ��
    */
    virtual void setForceChangeDisplay(bool force) { _forceChangeDisplay = force; }
    /**
    * @~english Get force change display.
    * @~chinese �Ƿ�ǿ�Ƹı���ʾ��
    * @return @~english Is force change display.
    * @~chinese �Ƿ�ǿ�Ƹı���ʾ��
    */
    virtual bool isForceChangeDisplay() const { return _forceChangeDisplay; }
protected:
    cocos2d::Vector<DecorativeDisplay*> _decoDisplayList;
    //! Display render node.
    cocos2d::Node *_displayRenderNode;
    //! Display render node type
    DisplayType _displayType;
    //! Include current display information, like contour sprite, etc.
    DecorativeDisplay *_currentDecoDisplay;
    //! Current display index
    int _displayIndex;

    bool _forceChangeDisplay;

    //! Whether of not the bone is visible. Default is true
    bool _visible;

    Bone *_bone;
};

}

#endif /*__CCDISPLAYMANAGER_H__*/
