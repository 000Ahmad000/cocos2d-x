/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __CCTIMELINE_ACTION_H__
#define __CCTIMELINE_ACTION_H__

#include "CCTimeLine.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCAction.h"

NS_TIMELINE_BEGIN

struct AnimationInfo
{
    AnimationInfo():startIndex(0),endIndex(0){}
    AnimationInfo(const std::string& otherName, int otherStartIndex, int otherEndIndex)
    :name(otherName),
    startIndex(otherStartIndex),
    endIndex(otherEndIndex)
    {
    }
    std::string name;
    int startIndex;
    int endIndex;
};

class CC_STUDIO_DLL ActionTimelineData : public cocos2d::Ref
{
public:
    /**
    * @~english Allocates and initializes an `ActionTimelineData`.
    * @~chinese ���䲢�ҳ�ʼ��һ��`ActionTimelineData`����
    * @param actionTag @~english Action tag.
    * @~chinese ����TAG��
    * @return @~english An initialized `ActionTimelineData` which is marked as "autorelease".
    * @~chinese һ����ʼ������������Ϊ�Զ��ͷŵ�`ActionTimelineData`����
    */
    static ActionTimelineData* create(int actionTag);

    /**
    * @~english Set action tag.
    * @~chinese ���ö���TAG��
    * @param actionTag @~english Action tag.
    * @~chinese ����TAG��
    */
    virtual void setActionTag(int actionTag) { _actionTag = actionTag; }
    /**
    * @~english Get action tag.
    * @~chinese ��ȡ����TAG��
    * @return @~english Action tag.
    * @~chinese ����TAG��
    */
    virtual int getActionTag() const { return _actionTag; }
CC_CONSTRUCTOR_ACCESS:
    ActionTimelineData();
    /**
    * @~english Initializes an `ActionTimelineData`.
    * @~chinese ��ʼ��һ��`ActionTimelineData`��
    * @param actionTag  @~english Action tag.
    * @~chinese ����TAG��
    */
    virtual bool init(int actionTag);
protected:
    int _actionTag;
};


class CC_STUDIO_DLL ActionTimeline : public cocos2d::Action
{
public:
    friend class Frame;

    /**
    * @~english Allocates and initializes an `ActionTimeline`.
    * @~chinese ���䲢�ҳ�ʼ��һ��`ActionTimeline`����
    * @param actionTag @~english Action tag.
    * @~chinese ����TAG��
    * @return @~english An initialized `ActionTimeline` which is marked as "autorelease".
    * @~chinese һ����ʼ������������Ϊ�Զ��ͷŵ�`ActionTimeline`����
    */
    static ActionTimeline* create();

    ActionTimeline();
    virtual ~ActionTimeline();

    /**
    * @~english Play specified animation.
    * @~chinese ����ָ���Ķ�����
    * @param animationName @~english Name of specified animation.
    * @~chinese ָ�����������ơ�
    * @param loop @~english Is play loop.
    * @~chinese �Ƿ�ѭ�����š�
    */
    virtual void play(std::string animationName, bool loop);

    virtual bool init();

    /** @~english Goto the specified frame index, and start playing from this index.
    * @~chinese ��ת��ָ��֡���Ӹ�֡��ʼ���Ŷ�����
     * @param startIndex @~english The animation will play from this index.
     * @~chinese �������Ӵ�֡��ʼ���š�
     */
    virtual void gotoFrameAndPlay(int startIndex);

    /** @~english Goto the specified frame index, and start playing from this index.
    * @~chinese ��ת��ָ��֡���������Ӹ�������ʼ���Ŷ�����
     * @param startIndex @~english The animation will play from this index.
     * @~chinese �������Ӹ�����λ�ÿ�ʼ���š�
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese �����Ƿ�ѭ�����š�
     */
    virtual void gotoFrameAndPlay(int startIndex, bool loop);

    /** @~english Goto the specified frame index, and start playing from start index, end at end index.
    * @~chinese ��ת��ָ��֡���Ӹ�֡��ʼ���Ŷ��������ŵ�ָ���Ľ���֡λ��ֹͣ��
     * @param startIndex @~english The animation will play from this index.
     * @~chinese �������Ӵ�֡��ʼ���š�
     * @param endIndex @~english The animation will end at this index.
     * @~chinese �������ŵ���֡������
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese �����Ƿ�ѭ�����š�
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, bool loop);

    /** @~english Goto the specified frame index, and start playing from start index, end at end index.
    * @~chinese��ת��ָ��֡�����Ҵ���ʼ֡��ʼ���ţ�������ֹ֡ͣ��
     * @param startIndex @~english The animation will play from this index.
     * @~chinese �������Ӵ�֡��ʼ���š�
     * @param endIndex @~english The animation will end at this index.
     * @~chinese �������ŵ���֡������
     * @param currentFrameIndex @~english set current frame index. 
     * @~chinese ���õ�ǰ֡������
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese �����Ƿ�ѭ�����š�
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, int currentFrameIndex, bool loop);

    /** @~english Goto the specified frame index, and pause at this index.
    * @~chinese ��ת��ָ��֡������ͣ�ڸ�֡��
     * @param startIndex @~english The animation will pause at this index.
     * @~chinese ��������ͣ�ڸ�֡��
     */
    virtual void gotoFrameAndPause(int startIndex);

    /** @~english Pause the animation. 
     * @~chinese ��ͣ������
    */
    virtual void pause();
    /** @~english Resume the animation. 
    * @~chinese ����������
    */
    virtual void resume();

    /** @~english Whether or not Action is playing.
    * @~chinese �Ƿ��ڲ��š�
    */
    virtual bool isPlaying() const;

    /** @~english Set the animation speed, this will speed up or slow down the speed. 
    * @~chinese ���ö����ٶȣ�ʹ�������ٻ���١�
    * @param speed @~english Animation speed.
    * @~chinese ���������ٶȡ�
    */
    virtual void  setTimeSpeed(float speed) { _timeSpeed = speed; }

    /** @~english Get current animation speed.
     *   @~chinese ��ȡ��ǰ�����ٶȡ�
     * @return @~english Animation speed.
     * @~chinese ���������ٶȡ�
     */
    virtual float getTimeSpeed() const { return _timeSpeed; }

    /** @~english Set duration of the whole action.
    *   @~chinese �������嶯��ʱ����
    * @param duration @~english Animation duration.
    * @~chinese ����ʱ����
    */
    virtual void setDuration(int duration) { _duration = duration; }
    /** @~english Get duration of the whole action.
    *   @~chinese ��ȡ����ʱ����
    * @return @~english Animation duration.
    * @~chinese ����ʱ����
    */
    virtual int  getDuration() const { return _duration; }

    /** @~english Get start frame index of this action.
    *   @~chinese ��������ʼ֡������
    * @return @~english Start frame index.
    * @~chinese ��ʼ֡������
    */
    virtual int getStartFrame() const { return _startFrame; }

    /** @~english End frame of this action.
    *   When action play to this frame, if action is not loop, then it will stop,  or it will play from start frame again. 
    *   @~chinese �����Ľ���֡������
    *   ���������ŵ���֡ʱ�������ѭ�����ţ��򶯻�ֹͣ����������ʼ֡��ͷ���š�
    * @return @~english End frame.
    * @~chinese ����֡������
    */
    virtual int  getEndFrame() const { return _endFrame; }

    /** @~english Set current frame index, this will cause action plays to this frame. 
    *   @~chinese ���õ�ǰ֡����������ʹ������������֡��
    * @param frameIndex @~english Current frame index.
    * @~chinese ��ǰ֡������
    */
    virtual void setCurrentFrame(int frameIndex);
    /** @~english Get current frame. 
    *   @~chinese ��ȡ��ǰ֡������
    * @return @~english Current frame index.
    * @~chinese ��ǰ֡������
    */
    virtual int  getCurrentFrame() const { return _currentFrame; }

    /** @~english Add Timeline to ActionTimeline.
    *   @~chinese ��ʱ������붯��ʱ���ᡣ
    * @param timeline @~english Timeline.
    * @~chinese ʱ���ᡣ
    */
    virtual void addTimeline(Timeline* timeline);
    /** @~english Remove Timeline to ActionTimeline.
    *   @~chinese ��ʱ����Ӷ���ʱ�������Ƴ���
    * @param timeline @~english Timeline.
    * @~chinese ʱ���ᡣ
    */
    virtual void removeTimeline(Timeline* timeline);

    /** @~english Get timelines.
    *   @~chinese ��ȡʱ�����б�
    * @return @~english Timelines.
    * @~chinese ʱ�����б�
    */
    virtual const cocos2d::Vector<Timeline*>& getTimelines() const { return _timelineList; }
    
    /** AnimationInfo*/
    /** @~english Add animationInfo.
    *   @~chinese ���Ӷ�����Ϣ��
    * @param animationInfo @~english Animation info.
    * @~chinese ������Ϣ��
    */
    virtual void addAnimationInfo(const AnimationInfo& animationInfo);
    /** @~english Remove animationInfo.
    *   @~chinese �Ƴ�������Ϣ��
    * @param animationName @~english Name of animation info.
    * @~chinese ������Ϣ�����ơ�
    */
    virtual void removeAnimationInfo(std::string animationName);
    /** @~english Is animationInfo exists.
    *   @~chinese �Ƿ񶯻���Ϣ���ڡ�
    * @param animationName @~english Name of animation info.
    * @~chinese ������Ϣ�����ơ�
    * @return @~english Is exists.
    * @~chinese �Ƿ���ڡ�
    */
    virtual bool IsAnimationInfoExists(const std::string& animationName);
    /** @~english Get animationInfo.
    *   @~chinese ��ȡ������Ϣ��
    * @param animationInfo @~english Animation info name.
    * @~chinese ������Ϣ�����ơ�
    */
    virtual AnimationInfo getAnimationInfo(const std::string& animationName);

    /** @~english Set ActionTimeline's frame event callback function.
    *   @~chinese ���ö���ʱ�����֡�¼��ص�������
    * @param listener @~english Callback function .
    * @~chinese �ص�������
    */
    void setFrameEventCallFunc(std::function<void(Frame *)> listener);
    /** @~english Clear ActionTimeline's frame event callback function.
    *   @~chinese �������ʱ�����֡�¼��ص�������
    */
    void clearFrameEventCallFunc();

    /** @~english Last frame callback will call when arriving last frame.
    *   @~chinese �������������һ֡ʱ������������һ֡�Ļص���
    * @param listener @~english Callback function .
    * @~chinese �ص�������
    */
    void setLastFrameCallFunc(std::function<void()> listener);
    /** @~english Clear last frame callback.
    *   @~chinese ����������������һ֡ʱ�������һ֡�Ļص���
    */
    void clearLastFrameCallFunc();

    /** Inherit from Action. */

    /** Returns a clone of ActionTimeline */
    virtual ActionTimeline* clone() const override; 

    /** Returns a reverse of ActionTimeline. 
     *  Not implement yet.
     */
    virtual ActionTimeline* reverse() const override { return nullptr; }

    virtual void step(float delta) override; 
    virtual void startWithTarget(cocos2d::Node *target) override;  
    virtual bool isDone() const override { return false; }
protected:
    virtual void gotoFrame(int frameIndex);
    virtual void stepToFrame(int frameIndex);

    /** emit frame event, call it when enter a frame*/
    virtual void emitFrameEvent(Frame* frame);

    std::map<int, cocos2d::Vector<Timeline*>> _timelineMap;
    cocos2d::Vector<Timeline*> _timelineList;

    int     _duration;
    double  _time;
    float   _timeSpeed;
    float   _frameInternal;
    bool    _playing;
    int     _currentFrame;
    int     _startFrame;
    int     _endFrame;
    bool    _loop;

    std::function<void(Frame*)> _frameEventListener;
    std::function<void()> _lastFrameListener;
    std::map<std::string, AnimationInfo> _animationInfos;
};

NS_TIMELINE_END


#endif /*__CCTIMELINE_ACTION_H__*/
