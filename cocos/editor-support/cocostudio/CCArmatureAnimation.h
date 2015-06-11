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


#ifndef __CCANIMATION_H__
#define __CCANIMATION_H__

#include "cocostudio/CCProcessBase.h"
#include "cocostudio/CCTween.h"
#include "cocostudio/CocosStudioExport.h"
#include <queue>

namespace cocostudio {


enum MovementEventType
{
    START,
    COMPLETE,
    LOOP_COMPLETE
};


class Armature;
class Bone;

typedef void (cocos2d::Ref::*SEL_MovementEventCallFunc)(Armature *, MovementEventType, const std::string&);
typedef void (cocos2d::Ref::*SEL_FrameEventCallFunc)(Bone *, const std::string&, int, int);

#define movementEvent_selector(_SELECTOR) (cocostudio::SEL_MovementEventCallFunc)(&_SELECTOR)
#define frameEvent_selector(_SELECTOR) (cocostudio::SEL_FrameEventCallFunc)(&_SELECTOR)

struct FrameEvent
{
    Bone *bone;
    std::string frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
};

struct MovementEvent
{
    Armature *armature;
    MovementEventType movementType;
    std::string movementID;
};

class  CC_STUDIO_DLL ArmatureAnimation : public ProcessBase
{
public:
    /**
    * @~english Create with a Armature.
    * @~chinese ʹ��һ�׹�������������������
    * @param armature  @~english The Armature ArmatureAnimation will bind to.
    * @~chinese ��Ҫ�󶨶����Ĺ�����
    * @return @~english Binded armature animation.
    * @~chinese �Ѱ󶨵Ĺ���������
    */
    static ArmatureAnimation *create(Armature *armature);
public:
	/**
     * @js ctor
     */
    ArmatureAnimation();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ArmatureAnimation(void);

    /**
    * @~english Init with a Armature.
    * @~chinese ʹ��һ�׹������г�ʼ����
    * @param armature  @~english The Armature ArmatureAnimation will bind to.
    * @~chinese ��Ҫ�󶨶����Ĺ�����
    */
    virtual bool init(Armature *armature);

    /** @deprecated Use `setSpeedScale(float speedScale)` instead */
    CC_DEPRECATED_ATTRIBUTE virtual void setAnimationScale(float animationScale);
    /** @deprecated Use `getSpeedScale()` instead */
    CC_DEPRECATED_ATTRIBUTE virtual float getAnimationScale() const;

    /**
    * @~english Scale animation play speed.
    * @~chinese ���Ŷ��������ٶȡ�
    * @param speedScale @~english Scale value.
    * @~chinese ���������ٶ�����ֵ��
    */
    virtual void setSpeedScale(float speedScale);

    /**
    * @~english Get animation play speed scale.
    * @~chinese ��ȡ���������ٶ�����ֵ��
    * @return @~english Scale value.
    * @~chinese ���������ٶ�����ֵ��
    */
    virtual float getSpeedScale() const;

    using ProcessBase::play;
    /**
    * @~english Play animation by animation name.
    * @~chinese ���ݶ������Ʋ��Ŷ�����
    * @param  animationName  @~english The animation name you want to play
    * @~chinese Ҫ���ŵĶ������ơ�
    * @param  durationTo @~english The frames between two animation changing-over.
    *         It's meaning is changing to this animation need how many frames
    *         -1 : use the value from MovementData get from flash design panel
    * @~chinese ���������л�ʱ����Ҫ��֡������ζ���л����ö���ʱ��Ҫ����֡��
    *    -1��ʹ��Flash����������MovementData�е�ֵ
    * @param  loop @~english  Whether the animation is loop
    *         loop < 0 : use the value from MovementData get from flash design panel
    *         loop = 0 : this animation is not loop
    *         loop > 0 : this animation is loop
    * @~chinese �����Ƿ�ѭ����
    *         loop < 0 : ʹ��Flash����������MovementData�е�ֵ
    *         loop = 0 : ��ѭ��
    *         loop > 0 : ѭ��
    */
    virtual void play(const std::string& animationName, int durationTo = -1,  int loop = -1);

    /** @deprecated Use `playWithIndex(int animationIndex,  int durationTo, int loop)` instead */
    CC_DEPRECATED_ATTRIBUTE virtual void playByIndex(int animationIndex,  int durationTo = -1, int loop = -1);

    /**
    * @~english Play animation by index, the other param is the same to `play`.
    * @~chinese ����֡�������Ŷ�����������������`play`��
    * @param  animationIndex  @~english the animation index you want to play.
    * @~chinese Ҫ���ŵĶ�����ʼ֡������
    */
    virtual void playWithIndex(int animationIndex,  int durationTo = -1, int loop = -1);

    /**
    * @~english Update movementList and play animation, the other param is the same to `play`.
    * @~chinese ˢ�¶����б����Ŷ�����������������`play`��
    * @param movementNames @~english New movement names.
    * @~chinese �µĶ����б����Ƽ��ϡ�
    */
    virtual void playWithNames(const std::vector<std::string>& movementNames, int durationTo = -1, bool loop = true);

    /**
    * @~english Update movementList and play animation, the other param is the same to `play`.
    * @~chinese ˢ�¶����б����Ŷ�����������������`play`��
    * @param movementIndexes @~english New movement indexes.
    * @~chinese �µĶ����б��������ϡ�
    */
    virtual void playWithIndexes(const std::vector<int>& movementIndexes, int durationTo = -1, bool loop = true);

    /**
     * @~english Go to specified frame and play current movement.
     * You need first switch to the movement you want to play, then call this function.
     * @~chinese ��ת��ָ����֡���Ӹ�֡��ʼ���ŵ�ǰ������
     *  ��Ҫ���л���Ҫ���ŵĶ������ٵ��øú�����
     * 
     * example : 
     *@code
     *           playByIndex(0);
     *           gotoAndPlay(0);
     *           playByIndex(1);
     *           gotoAndPlay(0);
     *           gotoAndPlay(15);
     *@endcode
     * @param frameIndex @~english Index of frame.
     * @~chinese Ҫ��ת��֡������
     */
    virtual void gotoAndPlay(int frameIndex);

    /**
     * @~english Go to specified frame and pause current movement.
     * @~chinese ��ת��ָ����֡����ͣ��ǰ������
     * @param frameIndex @~english Index of frame.
     * @~chinese Ҫ��ת��֡������
     */
    virtual void gotoAndPause(int frameIndex);

    virtual void pause() override;
    virtual void resume() override;
    virtual void stop() override;

    /**
    * @~english Get movement count.
    * @~chinese ��ö���������
    * @return @~english Movement count.
    * @~chinese ����������
    */
    ssize_t getMovementCount() const;

    virtual void update(float dt) override;

    /**
     * @~english Get current movementID
     * @~chinese ��õ�ǰ����ID
     * @return @~english The name of current movement
     * @~chinese ��õ�ǰ��������
     */
    std::string getCurrentMovementID() const;

    /** @deprecated Use `setMovementEventCallFunc(std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> listener)` instead */
    CC_DEPRECATED_ATTRIBUTE void setMovementEventCallFunc(cocos2d::Ref *target, SEL_MovementEventCallFunc callFunc);
    /** @deprecated Use `setFrameEventCallFunc(std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> listener)` instead */
    CC_DEPRECATED_ATTRIBUTE void setFrameEventCallFunc(cocos2d::Ref *target, SEL_FrameEventCallFunc callFunc);
    
    /**
    * @~english Set armature's movement event callback function.
    * To disconnect this event, just `setMovementEventCallFunc(nullptr, nullptr)`;
    * @~chinese ���ù����Ķ����¼��ص������� Ҫ�Ը��¼�ȡ�������������`setMovementEventCallFunc(nullptr, nullptr);`
    * @param frameIndex @~english Movement event callback function.
    * @~chinese �����¼��ص�������
    */
    void setMovementEventCallFunc(std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> listener);

    /**
    * @~english Set armature's frame event callback function.
    * To disconnect this event, just `setFrameEventCallFunc(nullptr, nullptr)`;
    * @~chinese ���ù�����֡�¼��ص������� Ҫ�Ը��¼�ȡ�������������`setFrameEventCallFunc(nullptr, nullptr);`
    * @param frameIndex @~english Frame event callback function.
    * @~chinese ֡�¼��ص�������
    */
    void setFrameEventCallFunc(std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> listener);

    /**
    * @~english Set animation data.
    * @~chinese ���ö������ݡ�
    * @param data @~english Animation data.
    * @~chinese �������ݡ�
    */
    virtual void setAnimationData(AnimationData *data) 
    {
        if (_animationData != data)
        {
            CC_SAFE_RETAIN(data);
            CC_SAFE_RELEASE(_animationData);
            _animationData = data; 
        }
    }

    /**
    * @~english Get animation data.
    * @~chinese ��ȡ�������ݡ�
    * @return @~english Animation data.
    * @~chinese �������ݡ�
    */
    virtual AnimationData *getAnimationData() const { return _animationData; }


    /** 
     * @~english Returns a user assigned Object. Similar to userData, but instead of holding a void* it holds an object
     * @~chinese �����û�����Ķ���������userData��������void*����һ������
     * @return @~english A user assigned Object
     * @~chinese �û�����Ķ���
     * @js NA
     * @lua NA
     */
    virtual Ref* getUserObject() { return _userObject; }
    /** 
    * @js NA
    * @lua NA
    */
    virtual const Ref* getUserObject() const { return _userObject; }

    /**
     * @~english Returns a user assigned Object. Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method, and the previous UserObject (if existed) will be relese.
     * The UserObject will be released in Node's destructure.
     * @~chinese �����û�����Ķ���������userData��������void*����һ������
     * �û������ڸ÷����б���һ�Σ�ͬʱ��һ���û�����������ڣ������ͷš�
     * �û�������ڽڵ�������������ͷš�
     *
     * @param userObject  @~english  A user assigned Object
     * @~chinese �����û�����Ķ���
     */
    virtual void setUserObject(Ref *userObject);
protected:

    /**
     * Update(float dt) will call this handler, you can handle your logic here
     * @js NA
     * @lua NA
     */
    void updateHandler() override;

    /**
     * Update current key frame, and process auto stop, pause
     * @js NA
     * @lua NA
     */
    void updateFrameData(float currentPercent);

    /**
     * Emit a frame event
     * @js NA
     * @lua NA
     */
    void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);

    /**
     * Emit a movement event
     */
    void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);

    void updateMovementList();

    bool isIgnoreFrameEvent() const { return _ignoreFrameEvent; }

    friend class Tween;
protected:
    //! AnimationData save all MovementDatas this animation used.
    AnimationData *_animationData;

    //! Scale the animation speed
    float _speedScale;

    MovementData *_movementData;				//! MovementData save all MovementFrameDatas this animation used.

    Armature *_armature;						//! A weak reference of armature

    std::string _movementID;				//! Current movment's name

    int _toIndex;								//! The frame index in MovementData->m_pMovFrameDataArr, it's different from m_iFrameIndex.

    cocos2d::Vector<Tween*> _tweenList;

    bool _ignoreFrameEvent;
    
    std::queue<FrameEvent*> _frameEventQueue;
    std::queue<MovementEvent*> _movementEventQueue;

    std::vector<std::string> _movementList;
    
    bool _onMovementList;
    bool _movementListLoop;
    unsigned int _movementIndex;
    int _movementListDurationTo;

    cocos2d::Ref *_userObject;
protected:
    /**
     * MovementEvent CallFunc.
     * @param Armature* a Armature
     * @param MovementEventType, Event Type, like START, COMPLETE.
     * @param const char*, Movement ID, also called Movement Name
     */
    SEL_MovementEventCallFunc _movementEventCallFunc;

    /**
     * FrameEvent CallFunc.
     * @param Bone*, a Bone
     * @param const char*, the name of this frame event
     * @param int, origin frame index
     * @param int, current frame index, animation may be delayed
     */
    SEL_FrameEventCallFunc _frameEventCallFunc;


    cocos2d::Ref *_movementEventTarget;
    cocos2d::Ref *_frameEventTarget;
    
    
    std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> _movementEventListener;
    std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> _frameEventListener;
};

}

#endif /*__CCANIMATION_H__*/
