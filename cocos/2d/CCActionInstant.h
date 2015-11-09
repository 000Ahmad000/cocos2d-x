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

#ifndef __CCINSTANT_ACTION_H__
#define __CCINSTANT_ACTION_H__

#include <functional>
#include "2d/CCAction.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** @class ActionInstant
 * @brief @~english Instant actions are immediate actions. They don't have a duration like the ActionInterval actions.
 * @~chinese ��ʱ�����ǻ�������ִ�еĶ���������û�г���ʱ�䶯����ActionInterval���ĳ���ʱ�����ԡ�
 **/
class CC_DLL ActionInstant : public FiniteTimeAction //<NSCopying>
{
public:
    //
    // Overrides
    //
    virtual ActionInstant* clone() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }
    
    virtual ActionInstant * reverse() const override
    {
        CC_ASSERT(0);
        return nullptr;
    }

    virtual bool isDone() const override;
    
    virtual void step(float dt) override;
    
    virtual void update(float time) override;
};

/** @class Show
 * @brief @~english Show the node instantly.
 * @~chinese ��ʾ��������������ʾһ���ڵ㡣
 **/
class CC_DLL Show : public ActionInstant
{
public:
    /** @~english Allocates and initializes the action.
     *
     * @~chinese ��������ʼ��������
     * 
     * @return @~english  An autoreleased Show object.
     * @~chinese һ�����ͷŵ�Show��������
     */
    static Show * create();

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual ActionInstant* reverse() const override;
    virtual Show* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    Show(){}
    virtual ~Show(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Show);
};

/** @class Hide
 * @brief @~english Hide the node.
 * @~chinese ���ض���������������һ���ڵ�
 */
class CC_DLL Hide : public ActionInstant
{
public:
    /** @~english Allocates and initializes the action.
     *
     * @~chinese ��������ʼ��������
     * 
     * @return @~english An autoreleased Hide object.
     * @~chinese һ�����ͷŵ�Hide��������
     */
    static Hide * create();

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual ActionInstant* reverse() const override;
    virtual Hide* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    Hide(){}
    virtual ~Hide(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Hide);
};

/** @class ToggleVisibility
 * @brief @~english Toggles the visibility of a node.
 * @~chinese ToggleVisibility���������л�һ���ڵ�Ŀɼ��ԡ�
 */
class CC_DLL ToggleVisibility : public ActionInstant
{
public:
    /** @~english Allocates and initializes the action.
     *
     * @~chinese ��������ʼ��������
     * 
     * @return @~english An autoreleased ToggleVisibility object.
     * @~chinese һ�����ͷŵ�ToggleVisibility��������
     */
    static ToggleVisibility * create();

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual ToggleVisibility* reverse() const override;
    virtual ToggleVisibility* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    ToggleVisibility(){}
    virtual ~ToggleVisibility(){}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ToggleVisibility);
};

/** @class RemoveSelf
 * @brief @~english Remove the node.
 * @~chinese RemoveSelf��������ɾ��ִ�ж����Ľڵ㡣
 */
class CC_DLL RemoveSelf : public ActionInstant
{
public:
    /** @~english Create the action.
     *
     * @~chinese ����������
     * 
     * @param isNeedCleanUp @~english Is need to clean up, the default value is true.
     * @~chinese �Ƿ���Ҫ����Ĭ��ֵ��true��
     * @return @~english An autoreleased RemoveSelf object.
     * @~chinese һ�����ͷŵ�RemoveSelf��������
     */
    static RemoveSelf * create(bool isNeedCleanUp = true);

    //
    // Override
    //
    virtual void update(float time) override;
    virtual RemoveSelf* clone() const override;
    virtual RemoveSelf* reverse() const override;
    
CC_CONSTRUCTOR_ACCESS:
    RemoveSelf() : _isNeedCleanUp(true){}
    virtual ~RemoveSelf(){}

    /** @~english init the action  @~chinese ��ʼ������ */
    bool init(bool isNeedCleanUp);

protected:
    bool _isNeedCleanUp;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(RemoveSelf);
};

/** @class FlipX
 * @brief @~english Flips the sprite horizontally.
 * @~chinese FlipX��������ˮƽ��תһ�����顣
 * @since v0.99.0
 */
class CC_DLL FlipX : public ActionInstant
{
public:
    /** @~english Create the action.
     *
     * @~chinese ����������
     * 
     * @param x @~english Flips the sprite horizontally if true.
     * @~chinese ���Ϊtrue��ˮƽ��ת���飬ֵΪfalseʱ��ָ�����ԭʼ״̬��
     * @return @~english  An autoreleased FlipX object.
     * @~chinese һ�����ͷŵ�FlipX����
     */
    static FlipX * create(bool x);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual FlipX* reverse() const override;
    virtual FlipX* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX() :_flipX(false) {}
    virtual ~FlipX() {}

    /** @~english init the action  @~chinese ��ʼ������ */
    bool initWithFlipX(bool x);

protected:
    bool    _flipX;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX);
};

/** @class FlipY
 * @brief @~english Flips the sprite vertically.
 * @~chinese FlipY����������ֱ��תһ�����顣
 * @since v0.99.0
 */
class CC_DLL FlipY : public ActionInstant
{
public:
    /** @~english Create the action.
     *
     * @~chinese ����������
     * 
     * @param y @~english Flips the sprite vertically if true.
     * @~chinese ���Ϊtrue��ֱ��ת���飬ֵΪfalseʱ��ָ�����ԭʼ״̬��
     * @return @~english An autoreleased FlipY object.
     * @~chinese һ�����ͷŵ�FlipY����
     */
    static FlipY * create(bool y);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual FlipY* reverse() const override;
    virtual FlipY* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipY() :_flipY(false) {}
    virtual ~FlipY() {}

    /** @~english init the action  @~chinese ��ʼ������ */
    bool initWithFlipY(bool y);

protected:
    bool    _flipY;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipY);
};

/** @class Place
 * @brief @~english Places the node in a certain position.
 * @~chinese Place�������Խ��ڵ�������ض�λ�á�
 */
class CC_DLL Place : public ActionInstant //<NSCopying>
{
public:

    /** @~english Creates a Place action with a position.
     *
     * @~chinese ��λ�ò�������һ��������
     * 
     * @param pos  @~english A certain position.
     * @~chinese һ���ض���λ�á�
     * @return @~english  An autoreleased Place object.
     * @~chinese һ�����ͷŵ�Place����
     */
    static Place * create(const Vec2& pos);

    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual Place* reverse() const override;
    virtual Place* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    Place(){}
    virtual ~Place(){}

    /** @~english Initializes a Place action with a position  @~chinese ��һ��λ�ó�ʼ������ */
    bool initWithPosition(const Vec2& pos);

protected:
    Vec2 _position;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Place);
};


/** @class CallFunc
 * @brief @~english Calls a 'callback'.
 * @~chinese ����һ���ص�������
 */
class CC_DLL CallFunc : public ActionInstant //<NSCopying>
{
public:
    /** @~english Creates the action with the callback of type `std::function<void()>`.
     * This is the preferred way to create the callback.
     * When this function bound in js or lua ,the input param will be changed.
     * In lua:local create(local funcID).
     *
     * @~chinese ��һ���ص���������CallFunc�������ص�������������`std::function<void()>`��
     * ���Ǵ����ص���������ѡ������
     * ���API����js��lua�У���������ᱻ�ı䡣
     * lua: local create(local funcID).
     * 
     * @param func  @~english A callback function need to be executed.
     * @~chinese ��Ҫ��ִ�еĻص�������
     * @return @~english  An autoreleased CallFunc object.
     * @~chinese һ�����ͷŵ�CallFunc����
     */
    static CallFunc * create(const std::function<void()>& func);

    /** @~english Creates the action with the callback
     * typedef void (Ref::*SEL_CallFunc)();
     * @~chinese ������ĺ������ʹ���CallFunc����
     * typedef void (Ref::*SEL_CallFunc)();
     * @deprecated @~english Use the std::function API instead. @~chinese ʹ��`std::function`API���
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static CallFunc * create(Ref* target, SEL_CallFunc selector);

public:
    /** @~english Executes the callback.
     * @~chinese ִ�лص���
     */
    virtual void execute();

    /** @~english Get the selector target.
     *
     * @~chinese ��ȡ�ص�������ִ�����塣
     * 
     * @return @~english The selector target.
     * @~chinese �ص�������ִ�����塣
     */
    inline Ref* getTargetCallback()
    {
        return _selectorTarget;
    }

    /** @~english Set the selector target.
     *
     * @~chinese ���ûص�������ִ�����塣
     * 
     * @param sel @~english The selector target.
     * @~chinese �ص�������ִ�����塣
     */
    inline void setTargetCallback(Ref* sel)
    {
        if (sel != _selectorTarget)
        {
            CC_SAFE_RETAIN(sel);
            CC_SAFE_RELEASE(_selectorTarget);
            _selectorTarget = sel;
        }
    }
    //
    // Overrides
    //
    virtual void update(float time) override;
    virtual CallFunc* reverse() const override;
    virtual CallFunc* clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    CallFunc()
    : _selectorTarget(nullptr)
    , _callFunc(nullptr)
    , _function(nullptr)
    {
    }
    virtual ~CallFunc();

    /** @~english Initializes the action with the callback
     * typedef void (Ref::*SEL_CallFunc)();
     * @~chinese ������ĺ������ͳ�ʼ����CallFunc����
     * typedef void (Ref::*SEL_CallFunc)();
     * @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target);
    
    /** @~english initializes the action with the `std::function<void()>`
     * @~chinese ��`std::function<void()>`�ص�������ʼ������
     * @lua NA
     */
    bool initWithFunction(const std::function<void()>& func);

protected:
    /** @~english Target that will be called  @~chinese �ص�������ִ������ */
    Ref*   _selectorTarget;

    union
    {
        SEL_CallFunc    _callFunc;
        SEL_CallFuncN    _callFuncN;
    };
    
    /** @~english function that will be called  @~chinese �ص�����*/
    std::function<void()> _function;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFunc);
};

/** @class CallFuncN
 * @brief @~english Calls a 'callback' with the node as the first argument. N means Node.
 * @~chinese ʹ�ýڵ���Ϊ��һ���������ûص�������CallFuncN������N����ڵ㡣
 * @js NA
 */
class CC_DLL CallFuncN : public CallFunc
{
public:
    /** @~english Creates the action with the callback of type `std::function<void()>`.
     * This is the preferred way to create the callback.
     *
     * @~chinese ��һ���ص���������CallFunc�������ص�������������`std::function<void()>`��
     * ���Ǵ����ص�����ѡ������
     * 
     * @param func  @~english A callback function need to be excuted.
     * @~chinese ���ᱻִ�еĻص�������
     * @return @~english  An autoreleased CallFuncN object.
     * @~chinese һ�����ͷŵ�CallFuncN����
     */
    static CallFuncN * create(const std::function<void(Node*)>& func);

    /** @~english Creates the action with the callback.
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @~chinese ������ķ�������CallFuncN������
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE static CallFuncN * create(Ref* target, SEL_CallFuncN selector);

    //
    // Overrides
    //
    virtual CallFuncN* clone() const override;
    virtual void execute() override;
    
CC_CONSTRUCTOR_ACCESS:
    CallFuncN():_functionN(nullptr){}
    virtual ~CallFuncN(){}

    /** @~english initializes the action with the `std::function<void(Node*)>`  @~chinese ��`std::function<void(Node*)>`��ʼ������ */
    bool initWithFunction(const std::function<void(Node*)>& func);
    
    /** @~english initializes the action with the callback
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @~chinese ������Ļص����ͳ�ʼ������
     * typedef void (Ref::*SEL_CallFuncN)(Node*);
     * @deprecated Use the std::function API instead.
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_CallFuncN selector);

protected:
    /** @~english function that will be called with the "sender" as the 1st argument  @~chinese �ص�������������`sender`��Ϊ��һ������ */
    std::function<void(Node*)> _functionN;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(CallFuncN);
};

/** @class __CCCallFuncND
 * @deprecated Please use CallFuncN instead.
 * @brief @~english Calls a 'callback' with the node as the first argument and the 2nd argument is data.
 * ND means: Node and Data. Data is void *, so it could be anything.
 * @~chinese ʹ�ýڵ���Ϊ��һ��������������Ϊ�ڶ������������ûص���__CCCallFuncND������
 * ND����˼�ǣ��ڵ�����ݡ�����������void *���������������κζ�����
 * @js NA
 */
class CC_DLL  __CCCallFuncND : public CallFunc
{
public:
    /** @~english Creates the action with the callback and the data to pass as an argument.
     *
     * @~chinese ��Ŀ��ڵ㣬�ص�������������Ϊ����������������
     * 
     * @param target    @~english A certain target.
     * @~chinese Ŀ��ڵ㡣
     * @param selector  @~english The callback need to be excuted.
     * @~chinese �ص�������
     * @param d @~english Data, is void* type.
     * @~chinese ���ݣ�������void *��
     * @return @~english An autoreleased __CCCallFuncND object.
     * @~chinese һ�����ͷŵ�__CCCallFuncND����
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncND * create(Ref* target, SEL_CallFuncND selector, void* d);
    
    //
    // Overrides
    //
    virtual __CCCallFuncND* clone() const override;
    virtual void execute() override;
    
CC_CONSTRUCTOR_ACCESS:
    __CCCallFuncND() {}
    virtual ~__CCCallFuncND() {}
    
    /** @~english initializes the action with the callback and the data to pass as an argument  @~chinese ��Ŀ��ڵ㣬�ص�������������Ϊ��������ʼ������ */
    bool initWithTarget(Ref* target, SEL_CallFuncND selector, void* d);

protected:
    SEL_CallFuncND _callFuncND;
    void* _data;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncND);
};


/** @class __CCCallFuncO
 * @deprecated Please use CallFuncN instead.
 * @brief @~english Calls a 'callback' with an object as the first argument. O means Object.
 * @~chinese ��һ��������Ϊ�ص������ĵ�һ��������__CCCallFuncO������O��ζ�Ŷ���
 * @since v0.99.5
 * @js NA
 */

class CC_DLL __CCCallFuncO : public CallFunc
{
public:
    /** @~english Creates the action with the callback.
     * typedef void (Ref::*SEL_CallFuncO)(Ref*);
     *
     * @~chinese ʹ��Ŀ��ڵ㣬�ص������Ͷ��󴴽�����
     * typedef void (Ref::*SEL_CallFuncO)(Ref*);
     * 
     * @param target    @~english A certain target.
     * @~chinese һ���ض���Ŀ��ڵ㡣
     * @param selector  @~english The callback need to be excuted.
     * @~chinese �ص�������
     * @param object    @~english An object as the callback's first argument.
     * @~chinese ��Ϊ�ص������ĵ�һ�������Ķ���
     * @return @~english An autoreleased __CCCallFuncO object.
     * @~chinese һ�����ͷŵ� __CCCallFuncO����
     */
    CC_DEPRECATED_ATTRIBUTE static __CCCallFuncO * create(Ref* target, SEL_CallFuncO selector, Ref* object);
    //
    // Overrides
    //
    virtual __CCCallFuncO* clone() const override;
    virtual void execute() override;
    
    Ref* getObject() const;
    void setObject(Ref* obj);
    
CC_CONSTRUCTOR_ACCESS:
    __CCCallFuncO();
    virtual ~__CCCallFuncO();

    bool initWithTarget(Ref* target, SEL_CallFuncO selector, Ref* object);
    
protected:
    Ref* _object;
    SEL_CallFuncO _callFuncO;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__CCCallFuncO);
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCINSTANT_ACTION_H__
