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
    static ActionTimelineData* create(int actionTag);

    virtual void setActionTag(int actionTag) { _actionTag = actionTag; }
    virtual int getActionTag() const { return _actionTag; }
CC_CONSTRUCTOR_ACCESS:
    ActionTimelineData();
    virtual bool init(int actionTag);
protected:
    int _actionTag;
};


class CC_STUDIO_DLL ActionTimeline : public cocos2d::Action
{
public:
    friend class Frame;

    static ActionTimeline* create();

    ActionTimeline();
    virtual ~ActionTimeline();

    virtual void play(std::string animationName, bool loop);

    virtual bool init();

    /** @~english Goto the specified frame index, and start playing from this index.
    * @~chinese ��ת��ָ��֡���������Ӹ�������ʼ���Ŷ�����
     * @param startIndex @~english The animation will play from this index.
     * @~chinese �������Ӹ�����λ�ÿ�ʼ���š�
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
    * @~chinese ��ת��ָ��֡���������Ӹÿ�ʼ������ʼ���Ŷ������ڽ���������ֹͣ����
     * @param startIndex @~english The animation will play from this index.
     * @~chinese �������Ӹ�����λ�ÿ�ʼ���š�
     * @param endIndex @~english The animation will end at this index.
     * @~chinese �������Ӹ�����λ��ֹͣ���š�
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese �����Ƿ�ѭ�����š�
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, bool loop);

    /** @~english Goto the specified frame index, and start playing from start index, end at end index.
    * @~chinese ��ת��ָ��֡���������Ӹÿ�ʼ������ʼ���Ŷ������ڽ���������ֹͣ����
     * @param startIndex @~english The animation will play from this index.
     * @~chinese �������Ӹ�����λ�ÿ�ʼ���š�
     * @param endIndex @~english The animation will end at this index.
     * @~chinese �������Ӹ�����λ��ֹͣ���š�
     * @param currentFrameIndex @~english set current frame index. 
     * @~chinese ���õ�ǰ֡������
     * @param loop @~english Whether or not the animation need loop. 
     * @~chinese �����Ƿ�ѭ�����š�
     */
    virtual void gotoFrameAndPlay(int startIndex, int endIndex, int currentFrameIndex, bool loop);

    /** @~english Goto the specified frame index, and pause at this index.
    * @~chinese ��ת��ָ��֡���������ڸ���������ͣ��
     * @param startIndex @~english The animation will pause at this index.
     * @~chinese �������ڸ���������ͣ��
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
    */
    virtual void  setTimeSpeed(float speed) { _timeSpeed = speed; }

    /** @~english Get current animation speed.
     *   @~chinese ��ȡ��ǰ�����ٶȡ�
     */
    virtual float getTimeSpeed() const { return _timeSpeed; }

    /** @~english duration of the whole action.
    *   @~chinese ���嶯��ʱ����
    */
    virtual void setDuration(int duration) { _duration = duration; }
    virtual int  getDuration() const { return _duration; }

    /** @~english Start frame index of this action.
    *   @~chinese ��������ʼ֡������
    */
    virtual int getStartFrame() const { return _startFrame; }

    /** @~english End frame of this action..
    *   When action play to this frame, if action is not loop, then it will stop,  or it will play from start frame again. 
    *   @~chinese �����Ľ���֡������
    *   ���������ŵ���֡ʱ�������ѭ�����ţ��򶯻�ֹͣ����������ʼ֡��ͷ���š�
    */
    virtual int  getEndFrame() const { return _endFrame; }

    /** @~english Set current frame index, this will cause action plays to this frame. 
    *   @~chinese ���õ�ǰ֡����������ʹ������������֡��
    */
    virtual void setCurrentFrame(int frameIndex);
    /** @~english Get current frame. 
    *   @~chinese ��ȡ��ǰ֡������
    */
    virtual int  getCurrentFrame() const { return _currentFrame; }

    /** @~english add Timeline to ActionTimeline.
    *   @~chinese ��ʱ�����붯��ʱ���
    */
    virtual void addTimeline(Timeline* timeline);
    virtual void removeTimeline(Timeline* timeline);

    virtual const cocos2d::Vector<Timeline*>& getTimelines() const { return _timelineList; }
    
    /** AnimationInfo*/
    virtual void addAnimationInfo(const AnimationInfo& animationInfo);
    virtual void removeAnimationInfo(std::string animationName);
    virtual bool IsAnimationInfoExists(const std::string& animationName);
    virtual AnimationInfo getAnimationInfo(const std::string& animationName);

    /** @~english Set ActionTimeline's frame event callback function .
    *   @~chinese ���ö���ʱ����֡�¼��ص�������
    */
    void setFrameEventCallFunc(std::function<void(Frame *)> listener);
    void clearFrameEventCallFunc();

    /** @~english Last frame callback will call when arriving last frame .
    *   @~chinese �������������һ֡ʱ������������һ֡�Ļص���
    */
    void setLastFrameCallFunc(std::function<void()> listener);
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
