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

#ifndef __CCFRAME_H__
#define __CCFRAME_H__

#include <string>
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "2d/CCTweenFunction.h"
#include "CCTimelineMacro.h"
#include "cocostudio/CocosStudioExport.h"

using namespace cocos2d;

NS_TIMELINE_BEGIN

class Timeline;
class ActionTimeline;

class CC_STUDIO_DLL Frame : public cocos2d::Ref
{
public:
    /** 
    * @~english Set frame index.
    * @~chinese ����֡������
    * @param frameIndex @~english Frame index.
    * @~chinese ֡������
    */
    virtual void setFrameIndex(unsigned int frameIndex) { _frameIndex = frameIndex; }
    /**
    * @~english Get frame index.
    * @~chinese ��ȡ֡������
    * @return @~english Frame index.
    * @~chinese ֡������
    */
    virtual unsigned int getFrameIndex() const { return _frameIndex; }

    /**
    * @~english Set timeline.
    * @~chinese ����ʱ���ߡ�
    * @param timeline @~english Timeline.
    * @~chinese ʱ���ߡ�
    */
    virtual void setTimeline(Timeline* timeline) { _timeline = timeline; }
    /**
    * @~english Get timeline.
    * @~chinese ��ȡʱ���ߡ�
    * @return @~english Timeline.
    * @~chinese ʱ���ߡ�
    */
    virtual Timeline* getTimeline() const { return _timeline; }

    /**
    * @~english Set node.
    * @~chinese ���ýڵ㡣
    * @param node @~english Node.
    * @~chinese �ڵ㡣
    */
    virtual void setNode(cocos2d::Node* node) { _node = node; }
    /**
    * @~english Get node.
    * @~chinese ��ȡ�ڵ㡣
    * @return @~english Node.
    * @~chinese �ڵ㡣
    */
    virtual cocos2d::Node* getNode() const { return _node; }

    /**
    * @~english Set is tween.
    * @~chinese �����Ƿ񲹼䡣
    * @param tween @~english Is tween.
    * @~chinese �Ƿ񲹼䡣
    */
    virtual void setTween(bool tween) { _tween = tween; }
    /**
    * @~english Get is tween.
    * @~chinese ��ȡ�Ƿ񲹼䡣
    * @return @~english Is tween.
    * @~chinese �Ƿ񲹼䡣
    */
    virtual bool isTween() const { return _tween; }

    /**
    * @~english Set tween type.
    * @~chinese ���ò������ࡣ
    * @param tweenType @~english Tween type.
    * @~chinese �������ࡣ
    */
    virtual void setTweenType(const tweenfunc::TweenType& tweenType) { _tweenType = tweenType; }
    /**
    * @~english Get tween type.
    * @~chinese ��ȡ�������ࡣ
    * @return @~english Tween type.
    * @~chinese �������ࡣ
    */
    virtual tweenfunc::TweenType getTweenType() const { return _tweenType; }
    
    /**
    * @~english Set tween params, to make easing with params, need `setTweenType(TweenType::CUSTOM_EASING)`.
    * @~chinese ���ò��������Ҫʹ�ò����������Ҫ����`setTweenType(TweenType::CUSTOM_EASING)`��
    * @param tweenType @~english Tween params.
    * @~chinese ���������
    */
    virtual void setEasingParams(const std::vector<float>& easingParams);
    /**
    * @~english Set tween params.
    * @~chinese ��ȡ���������
    * @return @~english Tween params.
    * @~chinese ���������
    */
    virtual const std::vector<float>& getEasingParams() const;
    
    virtual bool isEnterWhenPassed() { return _enterWhenPassed; }

    /**
    * @~english Calling when enter this frame.
    * @~chinese �������֡ʱ���á�
    * @param nextFrame @~english Next frame.
    * @~chinese ��һ֡��
    * @param currentFrameIndex @~english Current frame Index.
    * @~chinese ��ǰ֡������
    */
    virtual void onEnter(Frame* nextFrame, int currentFrameIndex) = 0;

    /**
    * @~english Calculate attribute by tween percent.
    * @~chinese ���ݵ�ǰ����ٷֱȼ��㵱ǰ���ԡ�
    * @param nextFrame @~english percent.
    * @~chinese ����ٷֱȡ�
    */
    virtual void apply(float percent);

    virtual Frame* clone() = 0;
protected:
    Frame();
    virtual ~Frame();
    
    virtual void onApply(float percent) {};
    //update percent depends _tweenType, and return the Calculated percent
    virtual float tweenPercent(float percent);
    
    virtual void emitEvent();
    virtual void cloneProperty(Frame* frame);
protected:

    unsigned int    _frameIndex;
    bool            _tween;
    bool            _enterWhenPassed;
    
    tweenfunc::TweenType _tweenType;
    std::vector<float>   _easingParam;
    Timeline* _timeline;
    cocos2d::Node*  _node;
};


class CC_STUDIO_DLL VisibleFrame : public Frame
{
public:
    static VisibleFrame* create();

    VisibleFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set visible.
    * @~chinese �����Ƿ�ɼ���
    * @param visible @~english Is visible.
    * @~chinese �Ƿ�ɼ���
    */
    inline void setVisible(bool visible) { _visible = visible;}
    /**
    * @~english Get visible.
    * @~chinese ��ȡ�Ƿ�ɼ���
    * @return @~english Is visible.
    * @~chinese �Ƿ�ɼ���
    */
    inline bool isVisible() const { return _visible; }

protected:
    bool _visible;
};


class CC_STUDIO_DLL TextureFrame : public Frame
{
public:
    static TextureFrame* create();

    TextureFrame();

    virtual void setNode(cocos2d::Node* node) override;

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set texture name.
    * @~chinese ���ò������ơ�
    * @param textureName @~english Texture name.
    * @~chinese �������ơ�
    */
    inline void setTextureName(std::string textureName) { _textureName = textureName;}
    /**
    * @~english Get texture name.
    * @~chinese ��ȡ�������ơ�
    * @return @~english Texture name.
    * @~chinese �������ơ�
    */
    inline std::string getTextureName() const { return _textureName; }

protected:
    cocos2d::Sprite* _sprite;
    std::string _textureName;
};

class CC_STUDIO_DLL RotationFrame : public Frame
{
public:
    static RotationFrame* create();

    RotationFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set rotation.
    * @~chinese ������ת��
    * @param rotation @~english Rotation angle.
    * @~chinese ��ת�Ƕȡ�
    */
    inline void  setRotation(float rotation) { _rotation = rotation; }
    /**
    * @~english Get rotation.
    * @~chinese ��ȡ��ת��
    * @return @~english Rotation angle.
    * @~chinese ��ת�Ƕȡ�
    */
    inline float getRotation() const { return _rotation; }

protected:
    virtual void onApply(float percent) override;
    
    float _rotation;
    float _betwennRotation;
};

class CC_STUDIO_DLL SkewFrame : public Frame
{
public:
    static SkewFrame* create();

    SkewFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set skew x.
    * @~chinese ���ú������졣
    * @param skewx @~english Skew x.
    * @~chinese �������졣
    */
    inline void  setSkewX(float skewx) { _skewX = skewx; }
    /**
    * @~english Get skew x.
    * @~chinese ��ȡ�������졣
    * @return @~english Skew x.
    * @~chinese �������졣
    */
    inline float getSkewX() const { return _skewX; }

    /**
    * @~english Set skew y.
    * @~chinese �����������졣
    * @param skewx @~english Skew y.
    * @~chinese �������졣
    */
    inline void  setSkewY(float skewy) { _skewY = skewy; }
    /**
    * @~english Get skew y.
    * @~chinese ��ȡ�������졣
    * @return @~english Skew y.
    * @~chinese �������졣
    */
    inline float getSkewY() const { return _skewY; }

protected:
    virtual void onApply(float percent) override;
    
    float _skewX;
    float _skewY;
    float _betweenSkewX;
    float _betweenSkewY;
};


class CC_STUDIO_DLL RotationSkewFrame : public SkewFrame
{
public:
    static RotationSkewFrame* create();

    RotationSkewFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;
    
protected:
    virtual void onApply(float percent) override;
};


class CC_STUDIO_DLL PositionFrame : public Frame
{
public:
    static PositionFrame* create();

    PositionFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set position.
    * @~chinese �������ꡣ
    * @param position @~english Position.
    * @~chinese ���ꡣ
    */
    inline void setPosition(const cocos2d::Point& position) { _position = position; }
    /**
    * @~english Get position.
    * @~chinese ��ȡ���ꡣ
    * @return @~english Position.
    * @~chinese ���ꡣ
    */
    inline cocos2d::Point getPosition() const { return _position; }

    /**
    * @~english Set position x.
    * @~chinese ����x���ꡣ
    * @param x @~english Position x.
    * @~chinese x���ꡣ
    */
    inline void setX(float x) { _position.x = x; }
    /**
    * @~english Set position y.
    * @~chinese ����y���ꡣ
    * @param x @~english Position y.
    * @~chinese y���ꡣ
    */
    inline void setY(float y) { _position.y = y; }

    /**
    * @~english Get position x.
    * @~chinese ��ȡx���ꡣ
    * @return @~english Position x.
    * @~chinese x���ꡣ
    */
    inline float getX() const { return _position.x; }
    /**
    * @~english Get position y.
    * @~chinese ��ȡy���ꡣ
    * @return @~english Position y.
    * @~chinese y���ꡣ
    */
    inline float getY() const { return _position.y; }
    
protected:
    virtual void onApply(float percent) override;
    
    cocos2d::Point _position;
    float _betweenX;
    float _betweenY;
};


class CC_STUDIO_DLL ScaleFrame : public Frame
{
public:
    static ScaleFrame* create();

    ScaleFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set scale.
    * @~chinese ��������ֵ��
    * @param scale @~english Scale.
    * @~chinese ����ֵ��
    */
    inline void  setScale(float scale) { _scaleX = scale; _scaleY = scale; }

    /**
    * @~english Set scale x.
    * @~chinese ����x����ֵ��
    * @param scaleX @~english Scale x.
    * @~chinese x����ֵ��
    */
    inline void  setScaleX(float scaleX) { _scaleX = scaleX; }
    /**
    * @~english Get scale x.
    * @~chinese ��ȡx����ֵ��
    * @return @~english Scale x.
    * @~chinese x����ֵ��
    */
    inline float getScaleX() const { return _scaleX; }

    /**
    * @~english Set scale y.
    * @~chinese ����y����ֵ��
    * @param scaleX @~english Scale y.
    * @~chinese y����ֵ��
    */
    inline void  setScaleY(float scaleY) { _scaleY = scaleY;}
    /**
    * @~english Get scale y.
    * @~chinese ��ȡy����ֵ��
    * @return @~english Scale y.
    * @~chinese y����ֵ��
    */
    inline float getScaleY() const { return _scaleY; }

protected:
    virtual void onApply(float percent) override;
    
    float _scaleX;
    float _scaleY;
    float _betweenScaleX;
    float _betweenScaleY;
};


class CC_STUDIO_DLL AnchorPointFrame : public Frame
{
public:
    static AnchorPointFrame* create();

    AnchorPointFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set anchor point.
    * @~chinese ����ê�㡣
    * @param point @~english Anchor point.
    * @~chinese ê�㡣
    */
    inline void setAnchorPoint(const cocos2d::Point& point) { _anchorPoint = point; }
    /**
    * @~english Get anchor point.
    * @~chinese ��ȡê�㡣
    * @return @~english Anchor point.
    * @~chinese ê�㡣
    */
    inline cocos2d::Point getAnchorPoint() const { return _anchorPoint; }

protected:
    cocos2d::Point _anchorPoint;
};



enum InnerActionType
{
    LoopAction,
    NoLoopAction,
    SingleFrame
};

class CC_STUDIO_DLL InnerActionFrame : public Frame
{
public:
    static const std::string AnimationAllName;
    
    static InnerActionFrame* create();
    InnerActionFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set inner action type.
    * @~chinese ����Ƕ�׶������͡�
    * @param type @~english Inner action type.
    * @~chinese Ƕ�׶������͡�
    */
    inline void setInnerActionType(InnerActionType type) { _innerActionType = type; }
    /**
    * @~english Get inner action type.
    * @~chinese ��ȡǶ�׶������͡�
    * @return @~english Inner action type.
    * @~chinese Ƕ�׶������͡�
    */
    inline InnerActionType getInnerActionType() const { return _innerActionType; }
    
    inline void setEnterWithName(bool isEnterWithName) { _enterWithName = isEnterWithName;}
    
    /**
    * @~english Set start frame index.
    * @~chinese ������ʼ֡������
    * @param type @~english Start frame index.
    * @~chinese ��ʼ֡������
    */
	void setStartFrameIndex(int frameIndex);
    /**
    * @~english Get start frame index.
    * @~chinese ��ȡ��ʼ֡������
    * @return @~english Start frame index.
    * @~chinese ��ʼ֡������
    */
    inline int  getStartFrameIndex() const { return _startFrameIndex; }

    /**
    * @~english Set end frame index.
    * @~chinese ���ý���֡������
    * @param type @~english End frame index.
    * @~chinese ����֡������
    */
	void setEndFrameIndex(int frameIndex);
    /**
    * @~english Get end frame index.
    * @~chinese ��ȡ����֡������
    * @return @~english End frame index.
    * @~chinese ����֡������
    */
    inline int  getEndFrameIndex() const { return _endFrameIndex; }
    
    /**
    * @~english Set animation name.
    * @~chinese ���ö������ơ�
    * @param animationNamed @~english Animation name.
    * @~chinese �������ơ�
    */
	void setAnimationName(const std::string& animationNamed);
    
    /**
    * @~english Set single frame index.
    * @~chinese ���õ�֡������
    * @param frameIndex @~english Single frame index.
    * @~chinese ��֡������
    */
    inline void setSingleFrameIndex(int frameIndex) { _singleFrameIndex = frameIndex;}
    /**
    * @~english Get single frame index.
    * @~chinese ��ȡ��֡������
    * @return @~english Single frame index.
    * @~chinese ��֡������
    */
    inline int  getSingleFrameIndex() const { return _singleFrameIndex;}

protected:
    InnerActionType _innerActionType;
    int _startFrameIndex;
    int _endFrameIndex;
    int _singleFrameIndex;
    std::string _animationName;
    bool _enterWithName;
};


class CC_STUDIO_DLL ColorFrame : public Frame
{
public:
    static ColorFrame* create();
    ColorFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /** @deprecated Use method setAlpha() and getAlpha() of AlphaFrame instead */
    CC_DEPRECATED_ATTRIBUTE inline void    setAlpha(GLubyte alpha) { _alpha = alpha; }
    CC_DEPRECATED_ATTRIBUTE inline GLubyte getAlpha() const { return _alpha; }

    /**
    * @~english Set color.
    * @~chinese ������ɫ��
    * @param color @~english Color.
    * @~chinese ��ɫ��
    */
    inline void setColor(const cocos2d::Color3B& color) { _color = color; }
    /**
    * @~english Get color.
    * @~chinese ��ȡ��ɫ��
    * @return @~english Color.
    * @~chinese ��ɫ��
    */
    inline cocos2d::Color3B getColor() const { return _color; }

protected:
    virtual void onApply(float percent) override;
    
    GLubyte _alpha;
    cocos2d::Color3B _color;

    int _betweenRed;
    int _betweenGreen;
    int _betweenBlue;
};

class CC_STUDIO_DLL AlphaFrame : public Frame
{
public:
    static AlphaFrame* create();
    AlphaFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set alpha.
    * @~chinese ����͸���ȡ�
    * @param alpha @~english Alpha.
    * @~chinese ͸���ȡ�
    */
    inline void setAlpha(GLubyte alpha) { _alpha = alpha; }
    /**
    * @~english Get alpha.
    * @~chinese ��ȡ͸���ȡ�
    * @return @~english Alpha.
    * @~chinese ͸���ȡ�
    */
    inline GLubyte getAlpha() const { return _alpha; }

protected:
    virtual void onApply(float percent) override;
    
    GLubyte _alpha;
    int _betweenAlpha;
};

class CC_STUDIO_DLL EventFrame : public Frame
{
public:
    static EventFrame* create();
    void init();

    EventFrame();

    virtual void setNode(cocos2d::Node* node) override;
    
    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set frame event.
    * @~chinese ����֡�¼���
    * @param event @~english Frame event.
    * @~chinese ֡�¼���
    */
    inline void setEvent(std::string event) { _event = event;}
    /**
    * @~english Get frame event.
    * @~chinese ��ȡ֡�¼���
    * @return @~english Frame event.
    * @~chinese ֡�¼���
    */
    inline std::string getEvent() const { return _event; }

protected:
    std::string _event;
    ActionTimeline* _action;
};

class CC_STUDIO_DLL ZOrderFrame : public Frame
{
public:
    static ZOrderFrame* create();

    ZOrderFrame();

    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;

    /**
    * @~english Set z order.
    * @~chinese ����z�����
    * @param zorder @~english Z order.
    * @~chinese z�����
    */
    inline void setZOrder(int zorder) { _zorder = zorder;}
    /**
    * @~english Get z order.
    * @~chinese ��ȡz�����
    * @return @~english Z order.
    * @~chinese z�����
    */
    inline int getZOrder() const { return _zorder; }

protected:
    int _zorder;
};


class CC_STUDIO_DLL BlendFuncFrame : public Frame
{
public:
    static BlendFuncFrame* create();
    
    BlendFuncFrame();
    
    virtual void onEnter(Frame *nextFrame, int currentFrameIndex) override;
    virtual Frame* clone() override;
    
    /**
    * @~english Get blend function.
    * @~chinese ��ȡ��Ϻ�����
    * @return @~english Blend function.
    * @~chinese ��Ϻ�����
    */
    inline BlendFunc getBlendFunc() const { return _blendFunc; }
    /**
    * @~english Set blend function.
    * @~chinese ���û�Ϻ�����
    * @param zorder @~english Blend function.
    * @~chinese ��Ϻ�����
    */
    inline void setBlendFunc(BlendFunc blendFunc) { _blendFunc = blendFunc; }
    
protected:
    BlendFunc  _blendFunc;
};
NS_TIMELINE_END


#endif /*__CCFRAME_H__*/
