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

#ifndef __CCBONE_H__
#define __CCBONE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CCTween.h"
#include "cocostudio/CCDecorativeDisplay.h"
#include "cocostudio/CCDisplayManager.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCNode.h"
#include "math/CCMath.h"

namespace cocostudio {

class Armature;

class CC_STUDIO_DLL Bone : public cocos2d::Node
{
public:
    /**
    * @~english Allocates and initializes a bone.
    * @~chinese ���䲢��ʼ��һ����ͷ����
    * @return @~english An initialized bone which is marked as "autorelease".
    * @~chinese һ����ʼ����������Ϊ�Զ��ͷŵĹ�ͷ����
    */
    static Bone *create();

    /**
    * @~english Allocates and initializes a bone.
    * @~chinese ���䲢��ʼ��һ����ͷ����
    * @param name  @~english If name is not null, then set name to the bone's name.
    * @~chinese ����ǿգ��򽫸ò�����Ϊ��ͷ�����ơ�
    * @return @~english An initialized bone which is marked as "autorelease".
    * @~chinese һ����ʼ����������Ϊ�Զ��ͷŵĹ�ͷ����
    */
    static Bone *create(const std::string& name);

public:
    /**
     *  @js ctor
     */
    Bone();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Bone(void);
    virtual bool init() override;

    /**
     * @~english Initializes a Bone with the specified name.
     * @~chinese ��ָ�������Ƴ�ʼ��һ�ι�ͷ��
     * @param name @~english Bone's name.
     * @~chinese ��ͷ�����ơ�
     */
    virtual bool init(const std::string& name);

    /**
     * @see DisplayManager::addDisplay(DisplayData *displayData, int index).
     */
    void addDisplay(DisplayData *displayData, int index);

    /**
    * @see DisplayManager::addDisplay(DisplayData *displayData, int index).
    */
    void addDisplay(cocos2d::Node *display, int index);

    /**
    * @see DisplayManager::removeDisplay(int index).
    */
    void removeDisplay(int index);

    /** @deprecated Use `changeDisplayWithIndex(int index, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    /** @deprecated Use `changeDisplayWithName(const std::string& name, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);

    /** @see `DisplayManager::changeDisplayWithIndex(int index, bool force)` */
    void changeDisplayWithIndex(int index, bool force);
    /** @see `DisplayManager::changeDisplayWithName(const std::string& name, bool force)` */
    void changeDisplayWithName(const std::string& name, bool force);

    /**
     * @~english Add a child to this bone, and it will let this child call `setParent(Bone *parent)` function to set self to it's parent
     * @~chinese Ϊ��ǰ��ͷ���һ���ӹ�ͷ��ͬʱ���ӹ�ͷ�����`setParent(Bone *parent)`������ǰ��ͷ��Ϊ�丸��ͷ��
     * @param child @~english The child you want to add
     * @~chinese Ҫ��ӵ��ӹ�ͷ��
     */
    void addChildBone(Bone *child);

    /**
     * @~english Set parent bone.
     * If parent is NUll, then also remove this bone from armature.
     * It will not set the Armature, if you want to add the bone to a Armature, you should use `Armature::addBone(Bone *bone, const char* parentName)`.
     * @~chinese ���ø���ͷ���������ͷ����ΪNULL���򽫵�ǰ��ͷ�ӹ������Ƴ���
     * ����������Թ����������øı䣬���Ҫ����ͷ���������Ӧ����`Armature::addBone(Bone *bone, const char* parentName)`��
     * @param parent @~english the parent bone.
     *          nullptr : remove this bone from armature
     * @~chinese ����ͷ��Ϊnullptrʱ������ǰ��ͷ�ӹ������Ƴ���
     */
    void setParentBone(Bone *parent);

    /**
     * @~english Get parent bone
     * @~chinese ��ȡ����ͷ
     * @return @~english parent bone
     * @~chinese ����ͷ
     */
    Bone *getParentBone();

    using Node::removeFromParent;
    /**
     * @~english Remove itself from its parent.
     * @~chinese ����ǰ��ͷ�Ӹ���ͷ���Ƴ�
     * @param recursion @~english   whether remove recursionly
     * @~chinese �Ƿ�ݹ��Ƴ�
     */
    void removeFromParent(bool recursion);

    /**
     * @~english Removes a child Bone
     * @~chinese ����ǰ��ͷ�Ӹ���ͷ���Ƴ�
     * @param bone @~english  the bone you want to remove
     * @~chinese Ҫ�Ƴ��Ĺ�ͷ
     */
    void removeChildBone(Bone *bone, bool recursion);

    void update(float delta) override;

    void updateDisplayedColor(const cocos2d::Color3B &parentColor) override;
    void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateColor() override;

    /**
    * @~english Update zorder
    * @~chinese ����Z����
    */
    void updateZOrder();

    virtual void setLocalZOrder(int zOrder) override;

    /**
    * @~english Get tween of bone.
    * @~chinese ��ȡ�������ԡ�
    * @return @~english Tween.
    * @~chinese ����
    */
    Tween *getTween();

    /*
     * @~english Set whether or not the bone's transform property changed. if true, the bone will update the transform.
     * @~chinese ���ù�ͷ�ı��������Ƿ��Ѹı䣬���Ϊ�棬��ͷ������±��Ρ�
     * @param dirty @~english  Is the transform property changed.
     * @~chinese �Ƿ�ı䡣
     */
    virtual void setTransformDirty(bool dirty) { _boneTransformDirty = dirty; }

    /*
    * @~english Whether or not the bone's transform property changed.
    * @~chinese ��ͷ�ı��������Ƿ��Ѹı䣬���Ϊ�棬��ͷ������±��Ρ�
    * @return @~english Is dirty.
    * @~chinese �Ƿ��Ѹı�
    */
    virtual bool isTransformDirty() { return _boneTransformDirty; }

    /**
    * @~english Returns the armature affine transform matrix. The matrix is in Pixels.
    * @~chinese ���ؽڵ㵽�����������任���󡣾���λ�����ء�
    * @return @~english Transformation matrix, in pixels. 
    * @~chinese �ڵ㵽�����������任����
    */
    virtual cocos2d::Mat4 getNodeToArmatureTransform() const;
    virtual cocos2d::Mat4 getNodeToWorldTransform() const override;

    /** @see `DisplayManager::getDisplayRenderNode()` */
    cocos2d::Node *getDisplayRenderNode();
    /** @see `DisplayManager::getDisplayRenderNodeType()` */
    DisplayType getDisplayRenderNodeType();

    /*
     * @~english Get the ColliderBody list in this bone. The object in the Array is ColliderBody.
     * @~chinese ��ȡ��ͷ����ײ�壬�����еĶ���Ϊ��ײ�塣
     * @return @~english The ColliderBody list in this bone.
     * @~chinese ��ͷ����ײ�塣
     */
    virtual ColliderDetector* getColliderDetector() const;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(ColliderFilter *filter);
    virtual ColliderFilter *getColliderFilter();
#endif

    /*
    * @~english Set bone data.
    * @~chinese ���ù�ͷ���ݡ�
    * @param boneData @~english Bone data.
    * @~chinese ��ͷ���ݡ�
    */
    virtual void setBoneData(BoneData *boneData);
    /*
    * @~english Get bone data.
    * @~chinese ��ȡ��ͷ���ݡ�
    * @return @~english Bone data.
    * @~chinese ��ͷ���ݡ�
    */
    virtual BoneData *getBoneData() const;

    /*
    * @~english Set armature.
    * @~chinese ���ù�����
    * @param boneData @~english Armature.
    * @~chinese ������
    */
    virtual void setArmature(Armature *armature);
    /*
    * @~english Get armature.
    * @~chinese ��ȡ������
    * @return @~english Armature.
    * @~chinese ������
    */
    virtual Armature *getArmature() const;

    /*
    * @~english Set child armature.
    * @~chinese �����ӹ�����
    * @param boneData @~english Child armature.
    * @~chinese �ӹ�����
    */
    virtual void setChildArmature(Armature *childArmature);
    /*
    * @~english Get childe armature.
    * @~chinese ��ȡ�ӹ�����
    * @return @~english Child armature.
    * @~chinese �ӹ�����
    */
    virtual Armature *getChildArmature() const;

    /*
    * @~english Get display manager.
    * @~chinese ��ȡ��ʾ��������
    * @return @~english Display manager.
    * @~chinese ��ʾ��������
    */
    virtual DisplayManager *getDisplayManager() const { return _displayManager; }

    /**
     * @lua NA
     * @~english Set whether or not ignore the movement bone data.
     * @~chinese �����Ƿ���Ի��ͷ�����ݡ�
     * @param ignore @~english  Is ignore.
     * @~chinese �Ƿ���ԡ�
     */
    virtual void setIgnoreMovementBoneData(bool ignore) { _ignoreMovementBoneData = ignore; }
    /*
    * @~english Whether or not ignore the movement bone data.
    * @~chinese �Ƿ���Ի��ͷ�����ݡ�
    * @return @~english Is ignore.
    * @~chinese �Ƿ���ԡ�
    */
    virtual bool isIgnoreMovementBoneData() const { return _ignoreMovementBoneData; }

    /*
     * @deprecated Use `isIgnoreMovementBoneData()` instead
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool getIgnoreMovementBoneData() const { return isIgnoreMovementBoneData(); }

    
    /*
     * @~english Set blend function.
     * @~chinese ���û�Ϻ�����
     * @param blendFunc @~english Blend function.
     * @~chinese ��Ϻ�����
     */
    virtual void setBlendFunc(const cocos2d::BlendFunc& blendFunc);
    /*
    * @~english Get blend function.
    * @~chinese ��ȡ��Ϻ�����
    * @return @~english Blend function.
    * @~chinese ��Ϻ�����
    */
    virtual cocos2d::BlendFunc getBlendFunc(void) { return _blendFunc; }

    /*
     * @~english Set if blend function is dirty.
     * @~chinese ���û�Ϻ����Ƿ�Ϊdirty��
     * @param dirty @~english Is dirty.
     * @~chinese �Ƿ�dirty��
     */
    virtual void setBlendDirty(bool dirty) { _blendDirty = dirty; }
    /*
    * @~english Get is blend function dirty.
    * @~chinese ��ȡ��Ϻ����Ƿ�Ϊ�ࡣ
    * @return @~english Is dirty.
    * @~chinese �Ƿ��ࡣ
    */
    virtual bool isBlendDirty(void) { return _blendDirty; }

    /*
    * @~english Get tween frame data.
    * @~chinese ��ȡ����ؼ�֡���ݡ�
    * @return @~english Tween frame data.
    * @~chinese ����ؼ�֡���ݡ�
    */
    virtual FrameData *getTweenData() const { return _tweenData; }

    /*
    * @~english Get world info.
    * @~chinese ��ȡ������Ϣ��
    * @return @~english World info.
    * @~chinese ������Ϣ��
    */
    virtual BaseData *getWorldInfo() const { return _worldInfo; }
protected:
    void applyParentTransform(Bone *parent);

    /*
     *  The origin state of the Bone. Display's state is effected by _boneData, m_pNode, _tweenData
     *  when call setData function, it will copy from the BoneData.
     */
    BoneData *_boneData;

    //! A weak reference to the Armature
    Armature *_armature;

    //! A weak reference to the child Armature
    Armature *_childArmature;

    DisplayManager *_displayManager;

    /*
     *	When Armature play an animation, if there is not a MovementBoneData of this bone in this MovementData, this bone will be hidden.
     *	Set IgnoreMovementBoneData to true, then this bone will also be shown.
     */
    bool _ignoreMovementBoneData;

    cocos2d::BlendFunc _blendFunc;
    bool _blendDirty;

    Tween *_tween;				//! Calculate tween effect

    //! Used for making tween effect in every frame
    FrameData *_tweenData;

    Bone *_parentBone;	               //! A weak reference to its parent
    bool _boneTransformDirty;          //! Whether or not transform dirty

    //! self Transform, use this to change display's state
    cocos2d::Mat4 _worldTransform;

    BaseData *_worldInfo;
    
    //! Armature's parent bone
    Bone *_armatureParentBone;
    
    //! Data version
    float _dataVersion;
};

}

#endif /*__CCBONE_H__*/
