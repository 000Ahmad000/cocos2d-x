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
 *  @lua NA
 */
 /** 
 @���� InputDelegate
 @���� �߼������ȡ����ӿڸ�����
 @ϸ�� �����ȡ����ӿڣ����߼�����̳����أ��Ӷ������߼������ȡ���롣
 @�� ���
 */
/** 
 * @class InputDelegate
 * @brief @~english InputDelegate.
 * @~chinese �������
 * @details @~english 
 * @~chinese �����ȡ����ӿڣ����߼�����̳����أ��Ӷ������߼������ȡ���롣
 *  @lua NA.
*/
class CC_STUDIO_DLL InputDelegate
{
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    InputDelegate(void);
    /**
     * @js NA
     */
    virtual ~InputDelegate(void);
    
public:
    /**
    @���� �����Ƿ����
    @���� true ���Խ��յ������¼� ������ܲ���
    */
    virtual bool isTouchEnabled() const;
    /**
    @���� ���ô�������
    @���� value true ���������¼����շ��򲻿���
    @���� ��
    */
    virtual void setTouchEnabled(bool value);
    /**
    @���� ���ټ��Ƿ����
    @���� true ���Խ��յ����ټ��¼� ������ܲ���
    */
    virtual bool isAccelerometerEnabled() const;
    /**
    @���� ���ü��ټƿ���
    @���� value true �������ټ��¼����շ��򲻿���
    @���� ��
    */
    virtual void setAccelerometerEnabled(bool value);
    /**
    @���� �����Ƿ����
    @���� true ���Խ��յ����ټ��¼� ������ܲ���
    */
    virtual bool isKeypadEnabled() const;
    /**
    @���� ���ü��̿���
    @���� value true ���������¼����շ��򲻿���
    @���� ��
    */
    virtual void setKeypadEnabled(bool value);
    /**
    @���� ���ô����¼���������
    @���� mode ALL_AT_ONCE ��������¼�һ�ν���  ONE_BY_ONE �������ʱ��һ������һ������
    @���� ��
    */
    virtual void setTouchMode(cocos2d::Touch::DispatchMode mode);
    /**
    @���� ��ȡ�����¼���������
    @���� ALL_AT_ONCE ��������¼�һ�ν���  ONE_BY_ONE �������ʱ��һ������һ������
    */
    virtual cocos2d::Touch::DispatchMode getTouchMode() const;
    /**
    @���� ���ô����¼��������ȼ�
    @���� priority ���ȼ���ֵ
    @���� ��
    */
    virtual void setTouchPriority(int priority);
    /**
    @���� ��ȡ�����¼��������ȼ�
    @���� �����¼��������ȼ���ֵ
    */
    virtual int  getTouchPriority() const;
 /** @deprecated Please override onAcceleration */
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 2.x ���ռ��ټ��麯����3.x������ʹ�ô˽ӿ�
    @���� accelerationValue ���ټ�������������
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(cocos2d::Acceleration* accelerationValue) final { CC_UNUSED_PARAM(accelerationValue); };
    // Deprecated touch callbacks.
    /**
     * @js NA
     */
     /**
    @���� cocos2d-x 2.x ���մ�����ʼ�麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    /**
     * @js NA
     */
   /**
    @���� cocos2d-x 2.x ���մ��������麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
   /**
    @���� cocos2d-x 2.x ���մ���ֹͣ�麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 2.x ���մ���ȡ���麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 2.x ���ն�㴥����ʼ�麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 2.x ���ն�㴥�������麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 2.x ���ն�㴥�������麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 2.x ���ն�㴥��ȡ���麯����3.x������ʹ�ô˽ӿ�
    @���� pTouch ���������������� 
    @���� pEvent �¼����� 
    @���� ��
    */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���ռ��ټ��麯��
    @���� acc ���ټ�������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���ռ��̰����麯��
    @���� keyCode ���°���
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���ռ���̧���麯��
    @���� keyCode ̧�𰴼�
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���մ�����ʼ�麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���մ��������麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���մ��������麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���մ���ȡ���麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���ն�㴥����ʼ�麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���ն�㴥�������麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���ն�㴥�������麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
    */
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    /**
    @���� cocos2d-x 3.x ���ն�㴥��ȡ���麯��
    @���� touch ����������������
    @���� pEvent �¼����� 
    @���� ��
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
