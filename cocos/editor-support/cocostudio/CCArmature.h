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

#ifndef __CCARMATURE_H__
#define __CCARMATURE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCBatchNode.h"
#include "cocostudio/CCArmatureAnimation.h"
#include "cocostudio/CCSpriteFrameCacheHelper.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CocosStudioExport.h"
#include "math/CCMath.h"

class b2Body;
struct cpBody;

namespace cocostudio {

CC_DEPRECATED_ATTRIBUTE typedef ProcessBase CCProcessBase;
CC_DEPRECATED_ATTRIBUTE typedef BaseData CCBaseData;
CC_DEPRECATED_ATTRIBUTE typedef DisplayData CCDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef SpriteDisplayData CCSpriteDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureDisplayData CCArmatureDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef ParticleDisplayData CCParticleDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef BoneData CCBoneData;
CC_DEPRECATED_ATTRIBUTE typedef FrameData CCFrameData;
CC_DEPRECATED_ATTRIBUTE typedef MovementBoneData CCMovementBoneData;
CC_DEPRECATED_ATTRIBUTE typedef MovementData CCMovementData;
CC_DEPRECATED_ATTRIBUTE typedef AnimationData CCAnimationData;
CC_DEPRECATED_ATTRIBUTE typedef ContourData CCContourData;
CC_DEPRECATED_ATTRIBUTE typedef TextureData CCTextureData;
CC_DEPRECATED_ATTRIBUTE typedef DecorativeDisplay CCDecorativeDisplay;
CC_DEPRECATED_ATTRIBUTE typedef DisplayData CCDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef DisplayFactory CCDisplayFactory;
CC_DEPRECATED_ATTRIBUTE typedef BatchNode CCBatchNode;
CC_DEPRECATED_ATTRIBUTE typedef DecorativeDisplay CCDecorativeDisplay;
CC_DEPRECATED_ATTRIBUTE typedef DisplayManager CCDisplayManager;
CC_DEPRECATED_ATTRIBUTE typedef ColliderBody CCColliderBody;
CC_DEPRECATED_ATTRIBUTE typedef ColliderDetector CCColliderDetector;
CC_DEPRECATED_ATTRIBUTE typedef SpriteFrameCacheHelper CCSpriteFrameCacheHelper;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureData CCArmatureData;
CC_DEPRECATED_ATTRIBUTE typedef Bone CCBone;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureAnimation CCArmatureAnimation;
CC_DEPRECATED_ATTRIBUTE typedef Armature CCArmature;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureDataManager CCArmatureDataManager;
CC_DEPRECATED_ATTRIBUTE typedef cocos2d::tweenfunc::TweenType CCTweenType;

class CC_STUDIO_DLL Armature : public cocos2d::Node, public cocos2d::BlendProtocol
{

public:

    /**
    * @~english Allocates and initializes an armature.
    * @~chinese ���䲢�ҳ�ʼ��������������
    * @return @~english An initialized armature which is marked as "autorelease".
    * @~chinese һ����ʼ������������Ϊ�Զ��ͷŵĹ�����������
    */
    static Armature *create();

    /**
    * @~english Allocates an armature, and use the `ArmatureData` named name in `ArmatureDataManager` to initializes the armature.
    * @~chinese ��������������󣬲�ʹ��`ArmatureDataManager`����name������`ArmatureData`������г�ʼ����
    * @param name  @~english Armature will use the name to find the `ArmatureData` to initializes it.
    * @~chinese �������Ը�name������`ArmatureData`���Թ������г�ʼ����
    * @return @~english An initialized armature which is marked as "autorelease".
    * @~chinese һ����ʼ������������Ϊ�Զ��ͷŵĹ�����������
    */
    static Armature *create(const std::string& name);

    /**
    * @~english Allocates an armature, and use the `ArmatureData` named name in `ArmatureDataManager` to initializes the armature.
    * @~chinese ��������������󣬲�ʹ��`ArmatureDataManager`����name������`ArmatureData`������г�ʼ����
    * @param name  @~english Armature will use the name to find the `ArmatureData` to initializes it.
    * @~chinese ��������name������`ArmatureData`���Թ������г�ʼ����
    * @param parentBone  @~english The armature will set the parentBone as its parent.
    * @~chinese ��������parentBone��Ϊ����ͷ��
    * @return @~english An initialized armature which is marked as "autorelease".
    * @~chinese һ����ʼ������������Ϊ�Զ��ͷŵĹ�����������
    */
    static Armature *create(const std::string& name, Bone *parentBone);

public:
    /**
     *  @js ctor
     */
    Armature();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Armature(void);
    virtual bool init() override;

    /**
    * @~english Init an armature with specified name.
    * @~chinese ��ָ�������Ƴ�ʼ��������
    * @param name @~english Armature name.
    * @~chinese �������ơ�
    */
    virtual bool init(const std::string& name);

    /**
    * @~english Init an armature with specified name.
    * @~chinese ��ָ�������Ƴ�ʼ��������
    * @param name @~english Armature name.
    * @~chinese �������ơ�
    * @param parentBone @~english The armature will set the parentBone as its parent.
    * @~chinese �������Ըò�����Ϊ����ͷ��
    */
    virtual bool init(const std::string& name, Bone *parentBone);

    /**
     * @~english Add a bone to this Armature.
     * @~chinese ��һ�ι�ͷ����������С�
     * @param bone  @~english The bone you want to add to Armature.
     * @~chinese Ҫ��ӵĹ�ͷ��
     * @param parentName @~english The parent Bone's name you want to add to. If it's nullptr, then set Armature to its parent.
     * @~chinese �Ըò�����Ϊ���ƵĹ�ͷ����Ϊ��ͷ����Ӻ�ĸ���ͷ������ò���Ϊ�գ���ͷ����Ӻ��Թ�����Ϊ����ͷ��
     */
    virtual void addBone(Bone *bone, const std::string& parentName);

    /**
     * @~english Get a bone with the specified name.
     * @~chinese ��ָ�������ƻ�ȡһ�ι�ͷ��
     * @param name @~english The bone's name you want to get.
     * @~chinese Ҫ��ȡ��ͷ�����ơ�
     */
    virtual Bone *getBone(const std::string& name) const;

    /**
     * @~english Change a bone's parent with the specified parent name.
     * @~chinese ����ָ�������ƣ�����һ�ι�ͷ�ĸ���ͷ��
     * @param bone @~english The bone you want to change parent.
     * @~chinese Ҫ���ĵ�һ�ι�ͷ��
     * @param parentName @~english The new parent's name.
     * @~chinese �¸���ͷ�����ơ�
     */
    virtual void changeBoneParent(Bone *bone, const std::string& parentName);

    /**
     * @~english Remove a bone with the specified name. If recursion it will also remove child Bone recursionly.
     * @~chinese ����ָ�������ƣ��Ƴ�һ�ι�ͷ�����ݲ�������������Ƿ���ӹ�ͷ���еݹ��Ƴ���
     * @param bone @~english The bone you want to remove.
     * @~chinese Ҫ�Ƴ��Ĺ�ͷ��
     * @param recursion @~english Determine whether remove the bone's child recursion.
     * @~chinese �Ƿ�ݹ��Ƴ���
     */
    virtual void removeBone(Bone *bone, bool recursion);

    /**
     * @~english Get Armature's bone dictionary.
     * @~chinese ��ȡ��ͷ�б�
     * @return @~english Armature's bone dictionary.
     * @~chinese ��ͷ�б�
     */
    const cocos2d::Map<std::string, Bone*>& getBoneDic() const;

    /**
    * @~english Get armature's boundingBox by calculating all bones' boundingBox.
    * @~chinese ͨ���������й�ͷ����߿򣬵õ����׹�������߿�
    * @return @~english Armature's boundingBox.
    * @~chinese ��������߿�
    */
    virtual cocos2d::Rect getBoundingBox() const override;

    /**
    * @~english Get a bone containing the specified point.
    * @~chinese ��ȡһ�ΰ���ָ�������Ĺ�ͷ��
    * @param x @~english Specified point x.
    * @~chinese ָ�����X���ꡣ
    * @param y @~english Specified point y.
    * @~chinese ָ�����Y���ꡣ
    * @return @~english The bone containing the specified point, if no bone found, return null.
    * @~chinese �����õ�Ĺ��������û�й������ҵ������ؿա�
    */
    Bone *getBoneAtPoint(float x, float y) const;

    // overrides
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override; 
    virtual const cocos2d::Mat4& getNodeToParentTransform() const override;
    inline void setBlendFunc(const cocos2d::BlendFunc &blendFunc) override { _blendFunc = blendFunc; }
    inline const cocos2d::BlendFunc &getBlendFunc(void) const override{ return _blendFunc; }
	

    /**
     * @~english Set contentsize and Calculate anchor point.
     * @~chinese ���ô�С������ê�㡣
     */
    virtual void updateOffsetPoint();
    virtual void setAnchorPoint(const cocos2d::Vec2& point) override;
    virtual const cocos2d::Vec2& getAnchorPointInPoints() const override;

    /**
    * @~english Get offset points of bones.
    * @~chinese ��ȡ��ͷ������ƫ������
    */
    virtual const cocos2d::Vec2& getOffsetPoints() const;

    /**
    * @~english Set animation for armature.
    * @~chinese Ϊ�������ö�����
    * @param animation @~english Armature animation.
    * @~chinese ����������
    */
    virtual void setAnimation(ArmatureAnimation *animation);

    /**
    * @~english Get animation of armature.
    * @~chinese ��ù������õĶ�����
    * @return @~english Animation of armature.
    * @~chinese ����������
    */
    virtual ArmatureAnimation *getAnimation() const;

    /**
    * @~english Get is the armature is transformed.
    * @~chinese ��ù����Ƿ��Ѿ���������任��
    * @return @~english Is the armature is transformed.
    * @~chinese �����Ƿ��Ѿ���������任��
    */
    virtual bool getArmatureTransformDirty() const;


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(ColliderFilter *filter);
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    CC_DEPRECATED_ATTRIBUTE virtual void drawContour();
#endif

    /**
    * @~english Set armature data for armature.
    * @~chinese Ϊ�����������ݡ�
    * @param armatureData @~english Armature data.
    * @~chinese �������ݡ�
    */
    virtual void setArmatureData(ArmatureData *armatureData) { _armatureData = armatureData; }

    /**
    * @~english Get armature data of armature.
    * @~chinese ��ȡ�������ݡ�
    * @return @~english Armature data.
    * @~chinese �������ݡ�
    */
    virtual ArmatureData *getArmatureData() const { return _armatureData; }

    /**
    * @~english Set parent bone for armature.
    * @~chinese Ϊ�������ø���ͷ��
    * @param parentBone @~english Parent bone.
    * @~chinese ����ͷ��
    */
    virtual void setParentBone(Bone *parentBone);

    /**
    * @~english Get parent bone of armature.
    * @~chinese ��ȡ�����ĸ���ͷ��
    * @return @~english Parent bone.
    * @~chinese �������ݡ�
    */
    virtual Bone *getParentBone() const;

    /**
    * @~english Set version for armature.
    * @~chinese Ϊ�������ð汾�š�
    * @param version @~english Armature version.
    * @~chinese �����汾�š�
    */
    virtual void setVersion(float version) { _version = version; }

    /**
    * @~english Get version of armature.
    * @~chinese ��ȡ�����İ汾�š�
    * @return @~english Armature version.
    * @~chinese �����汾�š�
    */
    virtual float getVersion() const { return _version; }

    /**
    * @~english Set BatchNode for armature.
    * @~chinese Ϊ�����������νڵ㡣
    * @param batchNode @~english BatchNode.
    * @~chinese ���νڵ㡣
    */
    virtual void setBatchNode(BatchNode *batchNode) { _batchNode = batchNode; }

    /**
    * @~english Get BatchNode of armature.
    * @~chinese ��ȡ���������νڵ㡣
    * @return @~english BatchNode.
    * @~chinese ���νڵ㡣
    */
    virtual BatchNode *getBatchNode() const { return _batchNode; }

#if ENABLE_PHYSICS_BOX2D_DETECT
    virtual b2Fixture *getShapeList();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void setBody(b2Body *body);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual b2Body *getBody() const;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    /**
     *  @js NA
     *  @lua NA
     */
    virtual cpShape *getShapeList();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void setBody(cpBody *body);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual cpBody *getBody() const;
#endif

protected:

    /*
     * Used to create Bone internal
     * @js NA
     * @lua NA
     */
    Bone *createBone(const std::string& boneName );

protected:
    ArmatureData *_armatureData;

    BatchNode *_batchNode;

    Bone *_parentBone;
    float _version;

    mutable bool _armatureTransformDirty;

    cocos2d::Map<std::string, Bone*> _boneDic;                    //! The dictionary of the bones, include all bones in the armature, no matter it is the direct bone or the indirect bone. It is different from m_pChindren.

    cocos2d::Vector<Bone*> _topBoneList;

    cocos2d::BlendFunc _blendFunc;                    //! It's required for CCTextureProtocol inheritance

    cocos2d::Vec2 _offsetPoint;
    cocos2d::Vec2 _realAnchorPointInPoints;

    ArmatureAnimation *_animation;

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Body *_body;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpBody *_body;
#endif
};

}

#endif /*__CCARMATURE_H__*/
