/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCANIMATE3D_H__
#define __CCANIMATE3D_H__

#include <map>
#include <unordered_map>

#include "3d/CCAnimation3D.h"
#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "2d/CCActionInterval.h"

NS_CC_BEGIN

/**
* @addtogroup _3d
* @{
*/
class Bone3D;
class Sprite3D;
class EventCustom;

/**
 * @enum Animate3DQuality
 * @brief @~english This enum control the animation's quality.
 * @~chinese ��ö�����ڿ��ƶ���������
 */
enum class Animate3DQuality
{
    /**
     * @~english It'll be ignore the curve-evaluating(the animation looks like stop), just acculate transition time.
     * @~chinese ���Զ�������ʱ��������⣨��ֵ�����������п��٣����ܼ��ٶ�������ʱ��
     **/
    QUALITY_NONE = 0, 

    /**
    * @~english Low animation quality, it'll be more efficient.
    * @~chinese �Ͷ����������ϸ߶����������ԣ�Ч�ʸ���
    **/
    QUALITY_LOW, 

    /**
    * @~english High animation quality, which also means more cpu time occupy.
    * @~chinese �߶���������Ч����ã�ͬʱҲ��ζ�Ÿ����CPUʱ��ռ��
    **/
    QUALITY_HIGH,              
};



/**
 * @class Animate3D
 * @brief @~english Animate3D, Animates a Sprite3D given with an Animation3D
 * @~chinese Animate3D ͨ��ָ����Animation3D�����Ķ��������Ը�Sprite3D���Ŷ���
 */
class CC_DLL Animate3D: public ActionInterval
{
public:
    
    /**
     * @~english Create Animate3D using Animation.
     * @~chinese ʹ��Animation3D������Animate3D����
     * @param animation @~english The specified Animation3D object.
     * @~chinese ָ����Animation3D����
     * @return @~english The Animate3D object.
     * @~chinese ��������Animate3D����
     */
    static Animate3D* create(Animation3D* animation);
    
    /**
     * @~english create Animate3D
     * @~chinese ͨ��Animation3D���󣬿�ʼʱ�䣬�Լ�����ʱ��������Animate3D
     * @param animation @~english Animation used to generate animate3D
     * @~chinese ָ����Animation3D����
     * @param fromTime @~english FormTime. 
     * @~chinese ��ʼʱ��
     * @param duration @~english Duration Time the Animate3D lasts.
     * @~chinese �������ŵĳ���ʱ��
     * @return @~english The Animate3D object.
     * @~chinese ��������Animate3D����
     */
    static Animate3D* create(Animation3D* animation, float fromTime, float duration);
    
    /**
     * @~english Create Animate3D by frame section, [startFrame, endFrame)
     * @~chinese ͨ��Animation3D����ʼ֡������֡���Լ�֡��������Animate3D����
     * @param animation @~english Animation used to generate animate3D
     * @~chinese Animation3D����
     * @param startFrame @~english The start frame.
     * @~chinese ��ʼ֡
     * @param endFrame @~english The end frame
     * @~chinese ����֡
     * @param frameRate @~english The frameRate, default is 30 per second
     * @~chinese ֡�ʣ�Ĭ������ʮ֡ÿ��
     * @return @~english Animate3D created using animate
     * @~chinese ��������Animate3D����
     */
    static Animate3D* createWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate = 30.f);
    
    //
    // Overrides
    //
    virtual void stop() override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual Animate3D* reverse() const override;
    virtual Animate3D *clone() const override;
    
    virtual void update(float t) override;
    
    /**
     * @~english Get speed, negative speed means playing reverse 
     * @~chinese ��ȡ�����ٶȣ��������ٶ���ζ�Ŷ������ڵ���
     * @return @~english The speed
     * @~chinese �ٶ�
     */
    float getSpeed() const;

    /**
    * @~english Set speed, negative speed means playing reverse
    * @~chinese ���ò����ٶȣ��������ٶ���ζ�Ŷ������ᵹ��
    * @param speed @~english the speed
    * @~chinese �ٶ�
    */
    void setSpeed(float speed);
    
    /**
     * Get the blend weight
     * @~chinese ��ȡ�������Ȩ��
     * @return the blend weight
     * @~chinese 
     */
    float getWeight() const { return _weight; }

    /**
     * @~english Set the blend weight. It is internally used currently. For example, Sprite3D is playing an Animate3D,
     * and then another Animate3D is going to be played. This function will be used to make the transition from on 
     * Animate3D to another smoothly. 
     * @~chinese ���ö������Ȩ�أ��ú���Ŀǰ�����ڲ�ʹ�ã�������˵����һ��Sprite3D�����ڲ���һ������ͬʱ��һ����������Ҫ�����ŵ������£�
     * �ú�����������������һ����������һ������֮��Ĺ���.
     * @param weight @~english The blend weight, the blend weight must be positive
     * @~chinese Ȩ�أ�Ȩֵ����Ϊ��
     */
    void setWeight(float weight);
    
    /**
     * @~english Set origin interval.
     * @~chinese ���ó�ʼ���ż��
     * @param interval @~english The new interval
     * @~chinese �µĲ��ż��
     */
    void setOriginInterval(float interval);

    /**
    * @~english Get origin interval
    * @~chinese ��ȡ��ʼ���ż��
    * @return @~english Get the origin interval.
    * @~chinese ���ż��
    */
    float getOriginInterval() const {return _originInterval; }
    
    /**
     * @~english Get animate transition time between 3d animations
     * @~chinese ��ȡ����֮��Ĺ���ʱ��
     * @return @~english The tarnsition time.
     * @~chinese ����ʱ��
     */
    static float getTransitionTime() { return _transTime; }
    
    /**
     * @~english Set animate transition time between 3d animations
     * @~chinese ���ö���֮��Ĺ���ʱ��
     * @param transTime @~english The transition time
     * @~chinese �¹���ʱ��
     */
    static void setTransitionTime(float transTime) { if (transTime >= 0.f) _transTime = transTime; }
    
    /**get & set play reverse, these are deprecated, use set negative speed instead*/
    CC_DEPRECATED_ATTRIBUTE bool getPlayBack() const { return _playReverse; }
    CC_DEPRECATED_ATTRIBUTE void setPlayBack(bool reverse) { _playReverse = reverse; }
    
    /**
     * @~english Set the animate quality, see also Animate3DQuality
     * @~chinese ���ö������������ڶ����������������Animate3DQualityö��
     * @param quality @~english The animate quality
     * @~chinese ����������ö��
     * */
    void setQuality(Animate3DQuality quality);
    
    /**
     * @~english Get animate quality, see also Animate3DQuality
     * @~chinese ��ȡ��ǰ�����Ķ���������������������������Animate3DQualityö��
     * @return @~english The animate quality
     * @~chinese ����������ö��
     **/
    Animate3DQuality getQuality() const;


    struct Animate3DDisplayedEventInfo
    {
        int frame;
        Node* target;
        const ValueMap* userInfo;
    };
    void setKeyFrameUserInfo(int keyFrame, const ValueMap &userInfo);
    const ValueMap* getKeyFrameUserInfo(int keyFrame) const;
    ValueMap* getKeyFrameUserInfo(int keyFrame);
    

    
CC_CONSTRUCTOR_ACCESS:
    
    Animate3D();
    virtual ~Animate3D();
    
    /**
    * @~english Remove this action from map
    * @~chinese ��map��ɾ����ǰaction
    */
    void removeFromMap();
    
    /** 
     * @~english Init method, init from the specified animation.
     * @~chinese ͨ��ָ����Animation3D�����ʼ��
     * @param animation @~english The specified animation.
     * @~chinese ָ����Animation3D����
     * @return @~english Return true if success, otherwise return false.
     * @~chinese ����ʼ���ɹ�ʱ����true,��֮����false
     */
    bool init(Animation3D* animation);

    /** 
     * @~english Init method, init from the start time and duration.
     * @~chinese ��ʼ��������ͨ����ʼʱ���Լ�����ʱ���ʼ��
     * @param animation @~english The specified animation.
     * @~chinese ָ����Animation3D����
     * @param fromTime @~english The start time.
     * @~chinese ��ʼʱ��
     * @param duration @~english The animate's duration
     * @~chinese ��������ʱ��
     * @return @~english Return true if success, otherwise return false.
     * @~chinese ����ʼ���ɹ�ʱ����true,��֮����false
     */
    bool init(Animation3D* animation, float fromTime, float duration);

    /**
    * @~english Init with frames
    * @~chinese ͨ����ʼ֡������֡��֡������������
    * @param animation @~english The specified animation
    * @~chinese ָ����Animation3D����
    * @param startFrame @~english The start frame
    * @~chinese ��ʼ֡
    * @param endFrame @~english The end frame
    * @~chinese ����֡
    * @param frameRate @~english The frame rate
    * @~chinese ֡��
    * @return @~english Return true if success, otherwise return false.
    * @~chinese ����ʼ���ɹ�ʱ����true,��֮����false
    */
    bool initWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate);
    
protected:
    
    enum class Animate3DState
    {
        FadeIn,
        FadeOut,
        Running,
    };
    Animate3DState _state; //animation state
    Animation3D* _animation; //animation data

    float      _absSpeed; //playing speed
    float      _weight; //blend weight
    float      _start; //start time 0 - 1, used to generate sub Animate3D
    float      _last; //last time 0 - 1, used to generate sub Animate3D
    bool       _playReverse; // is playing reverse
    static float      _transTime; //transition time from one animate3d to another
    float      _accTransTime; // accumulate transition time
    float      _lastTime;     // last t (0 - 1)
    float      _originInterval;// save origin interval time
    float      _frameRate;
    
    // animation quality
    EvaluateType _translateEvaluate;
    EvaluateType _roteEvaluate;
    EvaluateType _scaleEvaluate;
    Animate3DQuality _quality;
    
    std::unordered_map<Bone3D*, Animation3D::Curve*> _boneCurves; //weak ref
    std::unordered_map<Node*, Animation3D::Curve*> _nodeCurves;
    
    std::unordered_map<int, ValueMap> _keyFrameUserInfos;
    std::unordered_map<int, EventCustom*> _keyFrameEvent;
    std::unordered_map<int, Animate3DDisplayedEventInfo> _displayedEventInfo;

    //sprite animates
    static std::unordered_map<Node*, Animate3D*> s_fadeInAnimates;
    static std::unordered_map<Node*, Animate3D*> s_fadeOutAnimates;
    static std::unordered_map<Node*, Animate3D*> s_runningAnimates;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCANIMATE3D_H__
