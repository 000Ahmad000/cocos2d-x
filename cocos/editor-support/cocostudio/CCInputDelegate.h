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

#ifndef __CC_EXTENTIONS_CCINPUTDELEGATE_H__
#define __CC_EXTENTIONS_CCINPUTDELEGATE_H__

#include "platform/CCPlatformMacros.h"
#include "base/CCTouch.h"
#include "base/CCEvent.h"
#include "base/ccTypes.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventListener.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocos2d {
    class __Set;
}

namespace cocostudio {

/** 
 * @class InputDelegate
 * @brief @~english InputDelegate.
 * @~chinese �������
 * @details @~english component input delegate include touch, accelerometer, keypad
 * @~chinese �������������߼�����̳����أ��Ӷ������߼������ȡ���롣
 *  @lua NA.
*/
class CC_STUDIO_DLL InputDelegate
{
CC_CONSTRUCTOR_ACCESS:
    /**
     * @brief @~english InputDelegate constructor.
     * @~chinese ��������캯����
     * @js ctor
     */
    InputDelegate(void);

    /**
     * @brief @~english InputDelegate destructor.
     * @~chinese �����������������
     * @js NA
     */
    virtual ~InputDelegate(void);
    
public:

    /** 
     * @brief @~english Whether or not it will receive Touch events.
     * @~chinese �Ƿ���մ����¼���
     * @return @~english true receive touch events, false don't receive touch events.
     * @~chinese true ���մ����¼���false �����ܴ���ʱ�䡣
    */
    virtual bool isTouchEnabled() const;

    /** 
     * @brief @~english Enable / disable touch events with this property.
     * @~chinese ���ø÷��������û��߽��ô����¼���
     * @param value @~english true enable touch events false disable touch events.
     * @~chinese true ���ô����¼� false ���ô����¼���
    */
    virtual void setTouchEnabled(bool value);

    /** 
     * @brief @~english Whether or not it will receive accelerometer events.
     * @~chinese �Ƿ���ռ��ټ��¼���
     * @return @~english true receive accelerometer events, false don't receive accelerometer events.
     * @~chinese true ���ռ��ټ��¼���false �����ܼ��ټ��¼���
    */
    virtual bool isAccelerometerEnabled() const;

    /** 
     * @brief @~english Enable / disable accelerometer events with this property.
     * @~chinese ���ø÷��������û��߽��ü��ټ��¼���
     * @param value @~english true enable accelerometer events false disable accelerometer events.
     * @~chinese true ���ü��ټ��¼� false ���ü��ټ��¼���
    */
    virtual void setAccelerometerEnabled(bool value);

    /** 
     * @brief @~english Whether or not it will receive keyboard or keypad events.
     * @~chinese �Ƿ���ռ��̻���������¼���
     * @return @~english true receive keyboard or keypad events, false don't receive keyboard or keypad events.
     * @~chinese true ���ռ��̻���������¼���false �����ܼ��̻���������¼���
    */
    virtual bool isKeypadEnabled() const;

    /** 
     * @brief @~english Enable / disable keyboard or keypad events with this property.
     * @~chinese ���ø÷��������û��߽��ü��̻���������¼���
     * @param value @~english true enable keyboard or keypad events false disable keyboard or keypad events.
     * @~chinese true ���ü��̻���������¼� false ���ü��̻���������¼���
    */
    virtual void setKeypadEnabled(bool value);

    /** 
     * @brief @~english Set dispatchMode with this property.
     * @~chinese ������Ϣ�ַ���ʽ��
     * @param mode @~english Dispatch mode include all at once and one by one.
     * @~chinese ���÷ַ�ģʽ�� ��㴥���͵��㴥����
    */
    virtual void setTouchMode(cocos2d::Touch::DispatchMode mode);

    /** 
     * @brief @~english Get dispatch mode.
     * @~chinese ��ȡ��Ϣ�ַ���ʽ��
     * @return @~english Return dispatch mode, all at once or one by one.
     * @~chinese ��ȡ�ַ�ģʽ����㴥�����ߵ��㴥����
    */
    virtual cocos2d::Touch::DispatchMode getTouchMode() const;

    /**
     * @brief @~english Set receive touch priority with this property.
     * @~chinese ���ô����¼��������ȼ���
     * @param priority @~english Receive touch priority.
     * @~chinese �����¼��������ȼ���
    */
    virtual void setTouchPriority(int priority);

    /**
     * @brief @~english Get receive touch priority with this property.
     * @~chinese ���ô����¼��������ȼ���
    */
    virtual int  getTouchPriority() const;

    /** 
     * @brief @~english Callback function for accelerate began.
     * @~chinese ���ټƻص�����
     * @param accelerationValue @~english Acceleration infomation.
     * @~chinese ���ټ���Ϣ��
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(cocos2d::Acceleration* accelerationValue) final { CC_UNUSED_PARAM(accelerationValue); };

     /** 
      @deprecated Please override onTouchBegan 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};

     /** 
      @deprecated Please override onTouchMoved 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}

     /** 
      @deprecated Please override onTouchEnded 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}

     /** 
      @deprecated Please override onTouchCancelled 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}

     /** 
      @deprecated Please override onTouchesBegan 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}

     /** 
      @deprecated Please override onTouchesMoved 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}

     /** 
      @deprecated Please override onTouchesEnded 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}

     /** 
      @deprecated Please override onTouchesCancelled 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}

    /** 
     * @brief @~english Callback funtion for acceleration.
     * @~chinese ���ټ��¼��ص�������
     * @param acc @~english Acceleration information.
     * @~chinese ���ټ���Ϣ��
     * @param event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event) {};

    /**
     * @brief @~english Callback function for key pressed.
     * @~chinese ��������ȥʱ�Ļص�����
     * @param keyCode @~english KeyCode information.
     * @~chinese ������Ϣ��
     * @param event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};

    /** 
     * @brief @~english Callback function for key released.
     * @~chinese �����ͷ�ʱ�Ļص�����
     * @param keyCode @~english KeyCode information.
     * @~chinese ������Ϣ��
     * @param event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
    */
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};

    /** 
     * @brief @~english Callback function for touch began.
     * @~chinese ������ʼʱ�Ļص�����
     * @param touch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param event @~english Event information.
     * @~chinese �¼���Ϣ��
     * @return @~english if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
     * @~chinese �������false,��ôonTouchMoved��onTouchEnded onTouchCancelled��Զ���ᱻ����
     * @js NA
     */
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    /**
     * @brief @~english Callback function for touch moved.
     * @~chinese �����ƶ�ʱ�Ļص�����
     * @param pTouch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param pEvent @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);

    /**
     * @brief @~english Callback function for touch ended.
     * @~chinese ��������ʱ�Ļص�����
     * @param pTouch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param pEvent @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

    /**
     * @brief @~english Callback function for touch cancelled.
     * @~chinese ����ȡ��ʱ�Ļص�����
     * @param pTouch @~english Touch infomation.
     * @~chinese ������Ϣ��
     * @param pEvent @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

    /**
     * @brief @~english Callback function for multiple touches began.
     * @~chinese ��㴥����ʼʱ�Ļص�����
     * @param pTouches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param pEvent @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

    /**
     * @brief @~english Callback function for multiple touches moved.
     * @~chinese ��㴥���ƶ�ʱ�Ļص�����
     * @param pTouches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param pEvent @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

     /**
     * @brief @~english Callback function for multiple touches ended.
     * @~chinese ��㴥������ʱ�Ļص�����
     * @param pTouches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param pEvent @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

     /**
     * @brief @~english Callback function for multiple touches cancelled.
     * @~chinese ��㴥��ȡ��ʱ�Ļص�����
     * 
     * @param pTouches @~english Touches information.
     * @~chinese ��㴥����Ϣ��
     * @param pEvent @~english Event information.
     * @~chinese �¼���Ϣ��
     * @js NA
     */
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

protected:   
    bool _touchEnabled;
    cocos2d::EventListener* _touchListener;
    bool _accelerometerEnabled;
    cocos2d::EventListener*  _accelerometerListener;
    bool _keypadEnabled;
    cocos2d::EventListener*  _keyboardListener;
private:
     int _touchPriority;
    cocos2d::Touch::DispatchMode _touchMode;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
