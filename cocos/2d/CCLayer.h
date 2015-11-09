/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCLAYER_H__
#define __CCLAYER_H__

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCCustomCommand.h"


NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

class __Set;
class TouchScriptHandlerEntry;

class EventListenerTouch;
class EventListenerKeyboard;
class EventListenerAcceleration;

class Touch;

//
// Layer
//
/** @class Layer
 * @brief @~english Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
 * @~chinese ͼ����Node���һ������ڵ㣬��ʵ����TouchEventsDelegateЭ�顣
 * 
 * �����д�Node�ڵ�̳й����Ĺ��ܶ�����Ч��,��������������¹���:
 * - �����Խ���iPhone����
 * - �����Եõ����ٶȼ������¼�
*/
class CC_DLL Layer : public Node
{
public:    
    /** @~english Creates a fullscreen black layer.
     *
     * @~chinese ����һ��ȫ����ɫ��ͼ�㡣
     * 
     * @return @~english An autoreleased Layer object.
     * @~chinese һ��autoreleasedͼ�����
     */
    static Layer *create();

    // Deprecated touch callbacks.
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    

    /** @~english Callback function for touch began.
     *
     * @~chinese ������ʼʱ�Ļص�����
     * 
     * @param touch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @return @~english if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
     * @~chinese �������false,��ôonTouchMoved��onTouchEnded onTouchCancelled��Զ���ᱻ����
     * @js NA
     */
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    /** @~english Callback function for touch moved.
     *
     * @~chinese �����ƶ�ʱ�Ļص�����
     * 
     * @param touch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    /** @~english Callback function for touch ended.
     *
     * @~chinese ��������ʱ�Ļص�����
     * 
     * @param touch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    /** @~english Callback function for touch cancelled.
     *
     * @~chinese ����ȡ��ʱ�Ļص�����
     * 
     * @param touch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    /** @~english Callback function for multiple touches began.
     *
     * @~chinese ��㴥����ʼʱ�Ļص�����
     * 
     * @param touches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    /** @~english Callback function for multiple touches moved.
     *
     * @~chinese ��㴥���ƶ�ʱ�Ļص�����
     * 
     * @param touches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    /** @~english Callback function for multiple touches ended.
     *
     * @~chinese ��㴥������ʱ�Ļص�����
     * 
     * @param touches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    /** @~english Callback function for multiple touches cancelled.
     *
     * @~chinese ��㴥��ȡ��ʱ�Ļص�����
     * 
     * @param touches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    /** 
      @deprecated Please override onAcceleration 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(Acceleration* accelerationValue) final {};

    /** @~english Callback funtion for acceleration.
     * @~chinese ���ټ��¼��ص�������
     * @param acc @~english Acceleration information.
     * @~chinese ���ټ���Ϣ��
     * @param unused_event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);

    CC_DEPRECATED_ATTRIBUTE virtual void registerWithTouchDispatcher() final {};

    /** @~english whether or not it will receive Touch events.
     * You can enable / disable touch events with this property.
     * Only the touches of this node will be affected. This "method" is not propagated to it's children.
     * @~chinese �Ƿ���մ����¼���
     * �����Ե��ø÷��������û��߽��ô����¼���
     * ֻ�е��ø÷����Ľڵ�ĽӴ����ܵ�Ӱ�졣��������������ᴫ�������ĺ��ӡ�
     * @since v0.8.1
     * @js NA
    */
    CC_DEPRECATED_ATTRIBUTE bool isTouchEnabled() const;
    CC_DEPRECATED_ATTRIBUTE void setTouchEnabled(bool value);
    
    CC_DEPRECATED_ATTRIBUTE virtual void setTouchMode(Touch::DispatchMode mode);
    CC_DEPRECATED_ATTRIBUTE virtual Touch::DispatchMode getTouchMode() const;

    /** @~english
     * swallowsTouches of the touch events. Default is true
     * @~chinese 
     * �������ɴ����¼���Ĭ��ֵ��True.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setSwallowsTouches(bool swallowsTouches);
    CC_DEPRECATED_ATTRIBUTE virtual bool isSwallowsTouches() const;

    /** @~english whether or not it will receive Accelerometer events
     * You can enable / disable accelerometer events with this property.
     * @~chinese �Ƿ���ռ��ٶȼƵ��¼�
     * �����Ե��ø÷��������û���ü��ټ��¼�
     * @since v0.8.1
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool isAccelerometerEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerEnabled(bool value);
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerInterval(double interval);

    /** @~english whether or not it will receive keyboard or keypad events
     * You can enable / disable accelerometer events with this property.
     * it's new in cocos2d-x
     * @~chinese �Ƿ���յ����̻���������¼�
     * �����ø÷������û��߽��ü����¼�
     * ����cocos2d-x��һ���·���
     * @js NA
     */

    CC_DEPRECATED_ATTRIBUTE virtual bool isKeyboardEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setKeyboardEnabled(bool value);

    /** @~english
     * Please use onKeyPressed instead.
     * @~chinese 
     * ��ʹ��onKeyPressed�������档
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void keyPressed(int keyCode) final {};
    
    /** @~english
     * Please use onKeyReleased instead.
     * @~chinese 
     * ��ʹ��onKeyReleased�������档
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void keyReleased(int keyCode) final {};

    /** @~english Callback function for key pressed.
     * @~chinese ��������ȥʱ�Ļص�����
     * @param keyCode @~english KeyCode information.
     * @~chinese ������Ϣ��
     * @param event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    /** @~english Callback function for key released.
     * @~chinese �����ͷ�ʱ�Ļص�����
    * @param keyCode @~english KeyCode information.
     * @~chinese ������Ϣ��
    * @param event @~english Event information.
     * @~chinese �¼���Ϣ��
    * @js NA
    */
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    CC_DEPRECATED_ATTRIBUTE virtual bool isKeypadEnabled() const final { return _keyboardEnabled; }
    CC_DEPRECATED_ATTRIBUTE virtual void setKeypadEnabled(bool value);

    /** 
      @deprecated Please override onKeyReleased and check the keycode of KeyboardEvent::KeyCode::Menu(KEY_BACKSPACE) instead. 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void keyBackClicked() final {};
    CC_DEPRECATED_ATTRIBUTE virtual void keyMenuClicked() final {};

    // Overrides
    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    Layer();
    virtual ~Layer();

    virtual bool init() override;

protected:
    //add the api for avoid use deprecated api
    CC_DEPRECATED_ATTRIBUTE void _addTouchListener() {}

    CC_DEPRECATED_ATTRIBUTE void addTouchListener() {}
    CC_DEPRECATED_ATTRIBUTE int executeScriptTouchHandler(EventTouch::EventCode eventType, Touch* touch, Event* event);
    CC_DEPRECATED_ATTRIBUTE int executeScriptTouchesHandler(EventTouch::EventCode eventType, const std::vector<Touch*>& touches, Event* event);

    bool _touchEnabled;
    bool _accelerometerEnabled;
    bool _keyboardEnabled;
    EventListener* _touchListener;
    EventListenerKeyboard* _keyboardListener;
    EventListenerAcceleration* _accelerationListener;

    Touch::DispatchMode _touchMode;
    bool _swallowsTouches;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Layer);

};


/** @class __LayerRGBA
 * @brief @~english LayerRGBA is a subclass of Layer that implements the RGBAProtocol protocol using a solid color as the background.
 *
 * All features from Layer are valid, plus the following new features that propagate into children that conform to the RGBAProtocol:
 * - opacity
 * - RGB colors
 * @~chinese LayerRGBA����Layer�����࣬��ʵ����RGBAProtocolЭ�鲢��ʹ�ô�ɫ��Ϊ������
 * 
 * �����д�Layer�̳й����Ĺ��ܶ�����Ч��,��������ʵ����һЩ�����ԣ���Щ���Կ��Զ����з��� RGBAProtocol�ĺ��ӽ����Ч��
 * - ��͸��
 * - RGB��ɫ
 * @since 2.1
 * @js NA
 */
class CC_DLL __LayerRGBA : public Layer, public __RGBAProtocol
{
public:
    CREATE_FUNC(__LayerRGBA);
    
    
    //
    // Overrides
    //
    virtual GLubyte getOpacity() const override { return Layer::getOpacity(); }
    virtual GLubyte getDisplayedOpacity() const override { return Layer::getDisplayedOpacity(); }
    virtual void setOpacity(GLubyte opacity) override { Layer::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override { Layer::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override { Layer::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor() const override { return Layer::getColor(); }
    virtual const Color3B& getDisplayedColor() const override { return Layer::getDisplayedColor(); }
    virtual void setColor(const Color3B& color) override { Layer::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor) override { Layer::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override { Layer::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue) override { Layer::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const override { return Layer::isOpacityModifyRGB(); }

CC_CONSTRUCTOR_ACCESS:
    __LayerRGBA();
    virtual ~__LayerRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__LayerRGBA);
};

//
// LayerColor
//
/** @class LayerColor
 * @brief @~english LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.

 * All features from Layer are valid, plus the following new features:
 * - opacity
 * - RGB colors
 * @~chinese LayerColor��Layer������࣬������ʵ���� RGBAProtocolЭ��
 *
 * �����д�Layer�̳й����Ĺ��ܶ�����Ч��,��������ʵ����һЩ�����ԣ���Щ���Կ��Զ����з��� RGBAProtocol�ĺ��ӽ����Ч��
 * - ��͸��
 * - RGB��ɫ
 */
class CC_DLL LayerColor : public Layer, public BlendProtocol
{
public:
    /** @~english Creates a fullscreen black layer.
     *
     * @~chinese ����һ��ȫ���ĺ�ɫͼ��
     *
     * @return @~english An autoreleased LayerColor object.
     * @~chinese һ���Զ��ͷŵ�LayerColor����
     */
    static LayerColor* create();
    /** @~english Creates a Layer with color, width and height in Points.
     *
     * @~chinese ͨ����ɫ,��Ⱥ͸߶�������һ��ͼ��
     * 
     * @param color @~english The color of layer.
     * @~chinese ͼ�����ɫ��
     * @param width @~english The width of layer.
     * @~chinese ͼ��Ŀ�ȡ�
     * @param height @~english The height of layer.
     * @~chinese ͼ��ĸ߶ȡ�
     * @return @~english An autoreleased LayerColor object.
     * @~chinese һ���Զ��ͷ�LayerColor����
     */
    static LayerColor * create(const Color4B& color, GLfloat width, GLfloat height);
    /** @~english Creates a Layer with color. Width and height are the window size.
     *
     * @~chinese ʹ����ɫ����һ��ͼ�㡣��Ⱥ͸߶ȵ��ڴ��ڴ�С��
     * 
     * @param color @~english The color of layer.
     * @~chinese ͼ�����ɫ��
     * @return @~english An autoreleased LayerColor object.
     * @~chinese һ���Զ��ͷŵ�LayerColor����
     */
    static LayerColor * create(const Color4B& color);

    /** @~english Change width in Points.
     * 
     * @~chinese �޸�ͼ��Ŀ��
     * 
     * @param w @~english The width of layer.
     * @~chinese ͼ��Ŀ��
     */
    void changeWidth(GLfloat w);
    /** @~english Change height in Points.
     *
     * @~chinese �޸�ͼ��ĸ߶�
     * 
     * @param h @~english The height of layer.
     * @~chinese ͼ��ĸ߶ȡ�
     */
    void changeHeight(GLfloat h);
    /** @~english Change width and height in Points.
     * 
     * @~chinese �޸�ͼ��Ŀ�Ⱥ͸߶�
     * 
     * @param w @~english The width of layer.
     * @~chinese ͼ��Ŀ�ȡ�
     * @param h @~english The Height of layer.
     * @~chinese ͼ��ĸ߶ȡ�
    @since v0.8
    */
    void changeWidthAndHeight(GLfloat w ,GLfloat h);

    //
    // Overrides
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void setContentSize(const Size & var) override;
    /** @~english BlendFunction. Conforms to BlendProtocol protocol
     * @~chinese ��Ϻ���,����BlendProtocolЭ��
     * @lua NA
     */
    virtual const BlendFunc& getBlendFunc() const override;
    /**
     *@code@~english
     *When this function bound into js or lua,the parameter will be changed
     */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerColor();
    virtual ~LayerColor();
    
    bool init() override;
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
    bool initWithColor(const Color4B& color);

protected:
    void onDraw(const Mat4& transform, uint32_t flags);

    virtual void updateColor() override;

    BlendFunc _blendFunc;
    Vec2 _squareVertices[4];
    Color4F  _squareColors[4];
    CustomCommand _customCommand;
    Vec3 _noMVPVertices[4];
private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerColor);

};

//
// LayerGradient
//
/** @class LayerGradient
 * @brief @~english LayerGradient is a subclass of LayerColor that draws gradients across the background.
 * All features from LayerColor are valid, plus the following new features:
 * - direction
 * - final color
 * - interpolation mode

 * Color is interpolated between the startColor and endColor along the given
 * vector (starting at the origin, ending at the terminus).  If no vector is
 * supplied, it defaults to (0, -1) -- a fade from top to bottom.
 * If 'compressedInterpolation' is disabled, you will not see either the start or end color for
 * non-cardinal vectors; a smooth gradient implying both end points will be still
 * be drawn, however.

 * If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
 * @~chinese LayerGradient����LayerColor������,�������ƽ��䱳����
 * 
 * �����д�LayerColor�̳����Ĺ�������Ч��,�ټ��������µ�����:
 * - ����
 * - ������ɫ
 * - ��ֵģʽ
 * 
 * ��ɫ���ø���������(��ԭ��,����յ�)��ʹ��endColor��startColor���в�ֵ�õ���
 * ���û���ṩ����,��Ĭ��Ϊ(0,1) ���� ��ʾ���ϵ��½��䡣
 * 
 * �����compressedInterpolation���ǽ��õ�,�㲻�ῴ���Ŀ�ʼ���������ɫ�ݶ�
 *
 * ��������ˡ�compressedInterpolation��(Ĭ��ģʽ),���������Ŀ�ʼ�ͽ�������ɫ�ݶȡ�
 * 
 * @since v0.99.5
 */
class CC_DLL LayerGradient : public LayerColor
{
public:
    /** @~english Creates a fullscreen black layer.
     *
     * @~chinese ����һ��ȫ���ĺ�ɫͼ�㡣
     * 
     * @return @~english An autoreleased LayerGradient object.
     * @~chinese һ���Զ��ͷŵ�LayerGradient����
     */
    static LayerGradient* create();

    /** @~english Creates a full-screen Layer with a gradient between start and end.
     *
     * @~chinese ����һ��ȫ���ĺ��ڿ�ʼ�ͽ�����ɫ֮����ݶ�ͼ�㡣
     * 
     * @param start @~english The start color.
     * @~chinese �����ɫ��
     * @param end @~english The end color.
     * @~chinese �յ���ɫ��
     * @return @~english An autoreleased LayerGradient object.
     * @~chinese һ���Զ��ͷ�LayerGradient����
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end);

    /** @~english Creates a full-screen Layer with a gradient between start and end in the direction of v.
     *
     * @~chinese �ڷ���V�ϣ�ʹ�ÿ�ʼ��ɫ�ͽ�����ɫ��ֵ������һ��ȫ���Ĵ���ɫ�ݶȵ�ͼ�㡣
     * 
     * @param start @~english The start color.
     * @~chinese ��ʼ��ɫ��
     * @param end @~english The end color.
     * @~chinese ������ɫ��
     * @param v @~english The direction of gradient color.
     * @~chinese ��ɫ�ݶȵķ���
     * @return @~english An autoreleased LayerGradient object.
     * @~chinese һ���Զ��ͷ�LayerGradient����
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end, const Vec2& v);
    
    /** @~english Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors.
     * Default: true.
     *
     * @~chinese Ϊ���ڹ淶�ͷǹ淶�������ռ�����ʾ���е���ɫ�ݶ�,�Ƿ���Ҫѹ����ֵ��
     * Ĭ��ֵ: True
     * 
     * @param compressedInterpolation @~english The interpolation will be compressed if true.
     * @~chinese �����ֵ��ѹ����Ϊtrue.
     */
    void setCompressedInterpolation(bool compressedInterpolation);
    /** @~english Get the compressedInterpolation
     *
     * @~chinese ��ѯ�Ƿ��ֵ��ѹ��
     * 
     * @return @~english The interpolation will be compressed if true.
     * @~chinese �����ֵ��ѹ���򷵻��棬���򷵻ؼ�
     */
    bool isCompressedInterpolation() const;

    /** @~english Sets the start color of the gradient.
     * 
     * @~chinese ���ÿ�ʼ������ɫ��
     * 
     * @param startColor @~english The start color.
     * @~chinese ��ʼ��ɫ��
     */
    void setStartColor( const Color3B& startColor );
    /** @~english Returns the start color of the gradient.
     *
     * @~chinese ���ؿ�ʼ��ɫ�ݶȡ�
     * 
     * @return @~english The start color.
     * @~chinese ��ʼ��ɫ��
     */
    const Color3B& getStartColor() const;

    /** @~english Sets the end color of the gradient.
     *
     * @~chinese ���ý���������ɫ��
     * 
     * @param endColor @~english The end color.
     * @~chinese ������ɫ��
     */
    void setEndColor( const Color3B& endColor );
    /** @~english Returns the end color of the gradient.
     *
     * @~chinese ���ؽ�������ɫ�ݶȡ�
     * 
     * @return @~english The end color.
     * @~chinese ������ɫ��
     */
    const Color3B& getEndColor() const;

    /** @~english Returns the start opacity of the gradient.
     *
     * @~chinese ���ؿ�ʼ�Ĳ�͸�����ݶȡ�
     * 
     * @param startOpacity @~english The start opacity, from 0 to 255.
     * @~chinese ��ʼ��͸����,��0��255��
     */
    void setStartOpacity( GLubyte startOpacity );
    /** @~english Returns the start opacity of the gradient.
     *
     * @~chinese ���ؿ�ʼ�Ĳ�͸�����ݶȡ�
     * 
     * @return @~english The start opacity.
     * @~chinese ��ʼ�Ĳ�͸���ȡ�
     */
    GLubyte getStartOpacity() const;

    /** @~english Returns the end opacity of the gradient.
     *
     * @~chinese ���ؽ�����͸���Ľ��䡣
     * 
     * @param endOpacity @~english The end opacity, from 0 to 255.
     * @~chinese ��͸��,��0��255��
     */
    void setEndOpacity( GLubyte endOpacity );
    /** @~english Returns the end opacity of the gradient.
     *
     * @~chinese ���ؽ�����͸���Ľ��䡣
     * 
     * @return @~english The end opacity.
     * @~chinese ��͸����
     */
    GLubyte getEndOpacity() const;

    /** @~english Sets the directional vector that will be used for the gradient.
    The default value is vertical direction (0,-1). 
     *
     * @~chinese �����ݶȷ���������
     * Ĭ��ֵ�Ǵ�ֱ����(0,1)��
     * 
     * @param alongVector @~english The direction of gradient.
     * @~chinese �ݶȵķ���
     */
    void setVector(const Vec2& alongVector);
    /** @~english Returns the directional vector used for the gradient.
     *
     * @~chinese �����ݶȷ���������
     * 
     * @return @~english The direction of gradient.
     * @~chinese �ݶȵķ���
     */
    const Vec2& getVector() const;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerGradient();
    virtual ~LayerGradient();
    
    virtual bool init() override;
    /** @~english Initializes the Layer with a gradient between start and end.
     * @~chinese ʹ�ÿ�ʼ�ͽ�����ɫ����ʼ��ͼ�㡣
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    /** @~english Initializes the Layer with a gradient between start and end in the direction of v.
     * @~chinese ʹ�ÿ�ʼ�ͽ�����ɫ���Լ��ݶȷ�������ʼ��ͼ��
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end, const Vec2& v);

protected:
    virtual void updateColor() override;

    Color3B _startColor;
    Color3B _endColor;
    GLubyte _startOpacity;
    GLubyte _endOpacity;
    Vec2   _alongVector;
    bool    _compressedInterpolation;
};


/** @class LayerMultiplex
 * @brief @~english MultipleLayer is a Layer with the ability to multiplex it's children.
 * Features:
 * - It supports one or more children
 * - Only one children will be active a time
 * @~chinese MultipleLayer��һ��ͼ�㣬��֧�ֶ�·���ú��ӽڵ�
 * �ص�:
 * - ��֧��һ���������ӽڵ�
 * - ͬʱֻ��һ�����ӽڵ�ᱻ����
 */
class CC_DLL LayerMultiplex : public Layer
{
public:
    /** @~english Creates and initializes a LayerMultiplex object.
     * @~chinese ��������ʼ��һ��LayerMultiplex����
     * @lua NA
     * 
     * @return @~english An autoreleased LayerMultiplex object.
     * @~chinese һ��autoreleased LayerMultiplex����
     */
    static LayerMultiplex* create();

    /** @~english Creates a LayerMultiplex with an array of layers.
     * @~chinese ʹ�����鴴��һ��LayerMultiplex�㡣
     @since v2.1
     * @js NA
     *
     * @param arrayOfLayers @~english An array of layers.
     * @~chinese һ������Ĳ㡣
     * @return @~english An autoreleased LayerMultiplex object.
     * @~chinese һ��autoreleased LayerMultiplex����
     */
    static LayerMultiplex* createWithArray(const Vector<Layer*>& arrayOfLayers);

    /** @~english Creates a LayerMultiplex with one or more layers using a variable argument list.
     * @~chinese ����һ���䳤�����б�������LayerMultiplex
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported
    typedef Layer* M;
    static LayerMultiplex* create(M m1, std::nullptr_t listEnd) { return createVariadic(m1, NULL); }
    static LayerMultiplex* create(M m1, M m2, std::nullptr_t listEnd) { return createVariadic(m1, m2, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use createWithArray or createVariadic with NULL as the last argument
    static LayerMultiplex* createVariadic(Layer* item, ...) CC_REQUIRES_NULL_TERMINATION;
#else
    static LayerMultiplex * create(Layer* layer, ... );
#endif

    /** @~english Creates a LayerMultiplex with one layer.
     * @~chinese Creates a LayerMultiplex with one layer.
     * ʹ��һ��ͼ�������� MultiplexLayer
     *
     * @param layer @~english A certain layer.
     * @~chinese ĳһͼ�㡣
     * @return @~english An autoreleased LayerMultiplex object.
     * @~chinese һ���Զ��ͷŵ�LayerMultiplex����
     * @js NA
     * @lua NA
     */
    static LayerMultiplex * createWithLayer(Layer* layer);


    /** @~english Add a certain layer to LayerMultiplex.
     *
     * @~chinese ���ͼ�㵽LayerMultiplex��
     * 
     * @param layer @~english A layer need to be added to the LayerMultiplex.
     * @~chinese ����ӵ�LayerMultiplex��ͼ��
     */
    void addLayer(Layer* layer);

    /** @~english Switches to a certain layer indexed by n.
     The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @~chinese �л���ĳһ������Ϊn��ͼ�㡣
     * ��ǰ(�ɵ�)ͼ�㽫�����ĸ������Ƴ����� (cleanup = true)ʱ��
     * 
     * @param n @~english The layer indexed by n will display.
     * @~chinese ͼ��n������ʾ��
     */
    void switchTo(int n);
    /** @~english release the current layer and switches to another layer indexed by n.
     * The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @~chinese �ͷŵ�ǰͼ��ͬʱ�л�����һ������Ϊn��ͼ�㡣
     * ��ǰ(�ɵ�)ͼ�㽫�����ĸ������Ƴ����� (cleanup = true)ʱ��
     * 
     * @param n @~english The layer indexed by n will display.
     * @~chinese ����ʾ�㱻n��
     */
    void switchToAndReleaseMe(int n);

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    LayerMultiplex();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayerMultiplex();
    
    virtual bool init() override;
    /** @~english initializes a MultiplexLayer with one or more layers using a variable argument list.
     * @~chinese ʹ��һ��ͼ�����һ���䳤�����б�����ʼ�� MultiplexLayer
     * @js NA
     * @lua NA
     */
    bool initWithLayers(Layer* layer, va_list params);
    
    /** @~english initializes a MultiplexLayer with an array of layers
     * @~chinese ʹ��һ��ͼ����������ʼ�� LayerMultiplex
     * @since v2.1
     */
    bool initWithArray(const Vector<Layer*>& arrayOfLayers);

protected:
    unsigned int _enabledLayer;
    Vector<Layer*>    _layers;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerMultiplex);
};


// end of _2d group
/// @}

NS_CC_END

#endif // __CCLAYER_H__

