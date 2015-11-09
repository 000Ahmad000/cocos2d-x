/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __CC_ANIMATION_H__
#define __CC_ANIMATION_H__

#include "platform/CCPlatformConfig.h"
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "base/CCVector.h"
#include "2d/CCSpriteFrame.h"

#include <string>

NS_CC_BEGIN

class Texture2D;
class SpriteFrame;

/**
 * @addtogroup _2d
 * @{
 */

/** @class AnimationFrame
 *
 * @~english A frame of the animation. It contains information like:
 * - sprite frame name.
 * - # of delay units.
 * - offset
 * @~chinese ֡�����е�һ֡����������һЩ��Ϣ������֡����ʱ�䣬ƫ�ơ�
 
 @since v2.0
 */
class CC_DLL AnimationFrame : public Ref, public Clonable
{
public:
    /** @struct DisplayedEventInfo
     * @~english When the animation display,Dispatches the event of UserData.
     * @~chinese ����ʾ֡����ʱ���ַ�UserData�¼���
     */
    struct DisplayedEventInfo
    {
        Node* target;
        const ValueMap* userInfo;
    };
    
    /**@~english
     * Creates the animation frame with a spriteframe, number of delay units and a notification user info.
     *
     * @~chinese 
     * ʹ�þ���֡,ʱ����û���Ϣ֪ͨ��������������֡��
     * 
     * @param spriteFrame @~english The animation frame with a spriteframe.
     * @~chinese ����֡��
     * @param delayUnits @~english Number of delay units.
     * @~chinese ʱ�䡣
     * @param userInfo @~english A notification user info.
     * @~chinese �û���Ϣ֪ͨ��
     * @since 3.0
     */
    static AnimationFrame* create(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);
    /** @~english Return a SpriteFrameName to be used.
     *
     * @~chinese ����һ��ʹ�õľ���֡��
     * 
     * @return @~english a SpriteFrameName to be used.
     * @~chinese ʹ���еľ���֡��
     */
    SpriteFrame* getSpriteFrame() const { return _spriteFrame; };
    /** @~english Set the SpriteFrame.
     *
     * @~chinese ���þ���֡��
     * 
     * @param frame @~english A SpriteFrame will be used.
     * @~chinese ��ʹ�õľ���֡��
     */
    void setSpriteFrame(SpriteFrame* frame)
    {
        CC_SAFE_RETAIN(frame);
        CC_SAFE_RELEASE(_spriteFrame);
        _spriteFrame = frame;
    }

    /** @~english Gets the units of time the frame takes.
     *
     * @~chinese ��ȡ֡���ѵ�ʱ�䡣
     * 
     * @return @~english The units of time the frame takes.
     * @~chinese ֡���ѵ�ʱ�䡣
     */
    float getDelayUnits() const { return _delayUnits; };
    
    /** @~english Sets the units of time the frame takes.
     *
     * @~chinese ����֡���ѵ�ʱ�䡣
     * 
     * @param delayUnits @~english The units of time the frame takes.
     * @~chinese ��
     */
    void setDelayUnits(float delayUnits) { _delayUnits = delayUnits; };
    
    /** @brief @~english Gets user infomation
     * A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. 
     * If UserInfo is nil, then no notification will be broadcast.
     *
     * @~chinese ��ȡ�û���Ϣ
     * ��֡ʹ������ֵ���ΪUserInfo��ʾʱ��AnimationFrameDisplayedNotification֪ͨ���ᱻ�㲥��
     * ���UserInfo�ǿ�,��ô�����й㲥֪ͨ��
     * 
     * @return @~english A dictionary as UserInfo
     * @~chinese һ����ΪUserInfo���ֵ�
     */
    const ValueMap& getUserInfo() const { return _userInfo; };
    ValueMap& getUserInfo() { return _userInfo; };
    
    /** @~english Sets user infomation.
     * @~chinese �����û���Ϣ��
     * @param userInfo @~english A dictionary as UserInfo.
     * @~chinese һ����ΪUserInfo���ֵ�
     */
    void setUserInfo(const ValueMap& userInfo)
    {
        _userInfo = userInfo;
    }
    
    // Overrides
	virtual AnimationFrame *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    AnimationFrame();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AnimationFrame();
    
    /** @~english initializes the animation frame with a spriteframe, number of delay units and a notification user info
     * @~chinese ʹ�þ���֡,ʱ����û���Ϣ֪ͨ��������ʼ������֡��
     */
    bool initWithSpriteFrame(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);

protected:
    
    /** @~english SpriteFrameName to be used  @~chinese ��ʹ�õ�SpriteFrameName*/
    SpriteFrame* _spriteFrame;

    /**  @~english how many units of time the frame takes  @~chinese ֡���ѵ�ʱ��*/
    float _delayUnits;

    /**  @~english A AnimationFrameDisplayedNotification notification will be broadcast when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcast.  ��
     * @~chinese ��֡ʹ������ֵ���ΪUserInfo��ʾʱ��AnimationFrameDisplayedNotification֪ͨ���ᱻ�㲥�����UserInfo�ǿ�,��ô�����й㲥֪ͨ��*/
    ValueMap _userInfo;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(AnimationFrame);
};


/** @class Animation
 * @~english A Animation object is used to perform animations on the Sprite objects.
 * The Animation object contains AnimationFrame objects, and a possible delay between the frames.
 * You can animate a Animation object by using the Animate action. Example:
 * @~chinese һ�����������ִ�е�֡��������
 * ֡���������������֡���󣬺�֡��ʱ����
 * �������ʹ��һ��Animate�˶�������һ��Animation����
 * @code
 * sprite->runAction(Animate::create(animation));
 * @endcode
*/
class CC_DLL Animation : public Ref, public Clonable
{
public:
    /** @~english Creates an animation.
     * @~chinese ����һ��������
     * @since v0.99.5
     */
    static Animation* create(void);

    /* @~english Creates an animation with an array of SpriteFrame and a delay between frames in seconds.
     * The frames will be added with one "delay unit".
     * @~chinese ʹ��һ��SpriteFrame��֡��ʱ������һ��������
     * ÿ��ʱ��֮�佫�����һ��֡��
     * @since v0.99.5
     * @param arrayOfSpriteFrameNames @~english An array of SpriteFrame.
     * @~chinese һ��SpriteFrame��
     * @param delay @~english A delay between frames in seconds.
     * @~chinese ֮֡����ӳ��롣
     * @param loops @~english The times the animation is going to loop.
     * @~chinese ѭ��������
     */
    static Animation* createWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);

    /* @~english Creates an animation with an array of AnimationFrame, the delay per units in seconds and and how many times it should be executed.
     * @~chinese ʹ��һ��AnimationFrame,֡���ӳ�������ִ�д���������һ��������
     * @since v2.0
     * @param arrayOfAnimationFrameNames @~english An animation with an array of AnimationFrame.
     * @~chinese һ��AnimationFrame��
     * @param delayPerUnit @~english The delay per units in seconds and and how many times it should be executed.
     * @~chinese ֡���ӳ�������ִ�д���������һ��������
     * @param loops @~english The times the animation is going to loop.
     * @~chinese ѭ��������
     */
    static Animation* create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops = 1);

    /** @~english Adds a SpriteFrame to a Animation.
     *
     * @~chinese ���һ��SpriteFrame�������С�
     * 
     * @param frame @~english The frame will be added with one "delay unit".
     * @~chinese ʱ�������������һ֡��
     */
    void addSpriteFrame(SpriteFrame *frame);

    /** @~english Adds a frame with an image filename. Internally it will create a SpriteFrame and it will add it.
     * The frame will be added with one "delay unit".
     * Added to facilitate the migration from v0.8 to v0.9.
     * @~chinese ʹ��ͼƬ�����һ��֡���ڲ����ᴴ��һ��SpriteFrame���������
     * ʱ�������������һ֡��
     * Added to facilitate the migration from v0.8 to v0.9.
     * @param filename @~english The path of SpriteFrame.
     * @~chinese SpriteFrame��·����
     */
    void addSpriteFrameWithFile(const std::string& filename);
    /**
     * @deprecated. Use addSpriteFrameWithFile() instead.
	 @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void addSpriteFrameWithFileName(const std::string& filename){ addSpriteFrameWithFile(filename);}

    /** @~english Adds a frame with a texture and a rect. Internally it will create a SpriteFrame and it will add it.
     * The frame will be added with one "delay unit".
     * Added to facilitate the migration from v0.8 to v0.9.
     * @~chinese ʹ������Ͷ�Ӧ�������һ��֡���ڲ����ᴴ��һ��SpriteFrame���������
     * ʱ�������������һ֡����
     * 
     * @param pobTexture @~english A frame with a texture.
     * @~chinese ֡����
     * @param rect @~english The Texture of rect.
     * @~chinese �����Ӧ����
     */
    void addSpriteFrameWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** @~english Gets the total Delay units of the Animation. 
     *
     * @~chinese ��ȡ������ʱ�䡣
     * 
     * @return @~english The total Delay units of the Animation.
     * @~chinese ������ʱ�䡣
     */
    float getTotalDelayUnits() const { return _totalDelayUnits; };
    
    /** @~english Sets the delay in seconds of the "delay unit".
     *
     * @~chinese ��ʱ�䣬����Ϊ��λ��
     * 
     * @param delayPerUnit @~english The delay in seconds of the "delay unit".
     * @~chinese ��ʱ�䣬����Ϊ��λ��
     */
    void setDelayPerUnit(float delayPerUnit) { _delayPerUnit = delayPerUnit; };
    
    /** @~english Gets the delay in seconds of the "delay unit".
     * 
     * @~chinese ����ʱ�䣬����Ϊ��λ��
     * 
     * @return @~english The delay in seconds of the "delay unit".
     * @~chinese  ʱ�䣬����Ϊ��λ��
     */
    float getDelayPerUnit() const { return _delayPerUnit; };

    
    /** @~english Gets the duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit.
     *
     * @~chinese ��ȡ���������ĳ���ʱ�䣬����Ϊ��λ������totalDelayUnits * delayPerUnit�Ľ����
     * 
     * @return @~english Result of totalDelayUnits * delayPerUnit.
     * @~chinese totalDelayUnits * delayPerUnit�Ľ����
     */
    float getDuration() const;
    
    /** @~english Gets the array of AnimationFrames.
     * 
     * @~chinese ��ȡAnimationFrames���顣
     * 
     * @return @~english The array of AnimationFrames.
     * @~chinese AnimationFrames���顣
     */
    const Vector<AnimationFrame*>& getFrames() const { return _frames; };
    
    /** @~english Sets the array of AnimationFrames. 
     *
     * @~chinese ����AnimationFrames���顣
     * 
     * @param frames @~english The array of AnimationFrames.
     * @~chinese AnimationFrames���顣
     */
    void setFrames(const Vector<AnimationFrame*>& frames)
    {
        _frames = frames;
    }
    
    /** @~english Checks whether to restore the original frame when animation finishes. 
     *
     * @~chinese ����Ƿ��ڶ�������ʱ�ָ�����ʼ֡��
     * 
     * @return @~english Restore the original frame when animation finishes.
     * @~chinese �Ƿ��ڶ�������ʱ�ָ�����ʼ֡��
     */
    bool getRestoreOriginalFrame() const { return _restoreOriginalFrame; };
    
    /** @~english Sets whether to restore the original frame when animation finishes. 
     *
     * @~chinese �����Ƿ��ڶ�������ʱ�ָ�����ʼ֡��
     * 
     * @param restoreOriginalFrame @~english Whether to restore the original frame when animation finishes.
     * @~chinese �Ƿ��ڶ�������ʱ�ָ�����ʼ֡��
     */
    void setRestoreOriginalFrame(bool restoreOriginalFrame) { _restoreOriginalFrame = restoreOriginalFrame; };
    
    /** @~english Gets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... 
     *
     * @~chinese ��ȡ����ѭ��������0��ʾ������ִ�С�1��ʾ����ִ��һ��,����
     * 
     * @return @~english The times the animation is going to loop.
     * @~chinese ����ѭ��������
     */
    unsigned int getLoops() const { return _loops; };
    
    /** @~english Sets the times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ... 
     *
     * @~chinese ���ö���ѭ��������0��ʾ������ִ�С�1��ʾ����ִ��һ��,����
     * 
     * @param loops @~english The times the animation is going to loop.
     * @~chinese ����ѭ��������
     */
    void setLoops(unsigned int loops) { _loops = loops; };
    
    // overrides
	virtual Animation *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Animation();
    virtual ~Animation(void);
    
    /** @~english Initializes a Animation.  @~chinese ��ʼ��һ��������*/
    bool init();
    
    /** @~english Initializes a Animation with frames and a delay between frames.
     * @~chinese ʹ�ö���֡��֮֡����ӳٳ�ʼ��������
     * @since v0.99.5
     */
    bool initWithSpriteFrames(const Vector<SpriteFrame*>& arrayOfSpriteFrameNames, float delay = 0.0f, unsigned int loops = 1);
    
    /** @~english Initializes a Animation with AnimationFrame.
     * @~chinese ʹ��AnimationFrame��ʼ��������
     * @since v2.0
     */
    bool initWithAnimationFrames(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops);

protected:
    /** @~english total Delay units of the Animation.  @~chinese ��������ʱ�䡣*/
    float _totalDelayUnits;

    /** @~english Delay in seconds of the "delay unit".  @~chinese ��ʱ�䣬����Ϊ��λ����*/
    float _delayPerUnit;

    /** @~english duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit.  @~chinese ����������ʱ�䣬����Ϊ��λ������totalDelayUnits * delayPerUnit�Ľ����*/
    float _duration;

    /** @~english array of AnimationFrames.  @~chinese AnimationFrames���顣*/
    Vector<AnimationFrame*> _frames;

    /** @~english whether or not it shall restore the original frame when the animation finishes.  @~chinese �Ƿ��ڶ�������ʱ�ָ�����ʼ֡��*/
    bool _restoreOriginalFrame;

    /** @~english how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ...
     * @~chinese ����ѭ��������0��ʾ������ִ�С�1��ʾ����ִ��һ��,���� 
     */
    unsigned int _loops;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Animation);
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_ANIMATION_H__
