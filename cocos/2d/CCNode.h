/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
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

#ifndef __CCNODE_H__
#define __CCNODE_H__

#include "base/ccMacros.h"
#include "base/CCVector.h"
#include "base/CCProtocols.h"
#include "base/CCScriptSupport.h"
#include "math/CCAffineTransform.h"
#include "math/CCMath.h"
#include "2d/CCComponentContainer.h"
#include "2d/CCComponent.h"

NS_CC_BEGIN

class GridBase;
class Touch;
class Action;
class LabelProtocol;
class Scheduler;
class ActionManager;
class Component;
class ComponentContainer;
class EventDispatcher;
class Scene;
class Renderer;
class Director;
class GLProgram;
class GLProgramState;
class Material;
class Camera;
class PhysicsBody;

/**
 * @addtogroup _2d
 * @{
 */

enum {
    kNodeOnEnter,
    kNodeOnExit,
    kNodeOnEnterTransitionDidFinish,
    kNodeOnExitTransitionDidStart,
    kNodeOnCleanup
};

bool CC_DLL nodeComparisonLess(Node* n1, Node* n2);

class EventListener;

/** @class Node
* @brief @~english Node is the base element of the Scene Graph. Elements of the Scene Graph must be Node objects or subclasses of it.
 The most common Node objects are: Scene, Layer, Sprite, Menu, Label.

 The main features of a Node are:
 - They can contain other Node objects (`addChild`, `getChildByTag`, `removeChild`, etc)
 - They can schedule periodic callback (`schedule`, `unschedule`, etc)
 - They can execute actions (`runAction`, `stopAction`, etc)

 Subclassing a Node usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding `draw` to render the node

 Properties of Node:
 - position (default: x=0, y=0)
 - scale (default: x=1, y=1)
 - rotation (in degrees, clockwise) (default: 0)
 - anchor point (default: x=0, y=0)
 - contentSize (default: width=0, height=0)
 - visible (default: true)

 Limitations:
 - A Node is a "void" object. If you want to draw something on the screen, you should use a Sprite instead. Or subclass Node and override `draw`.

 @~chinese �ڵ��ǳ���ͼ�Ļ���Ԫ�ء�����ͼ�Ļ���Ԫ�ر����ǽڵ��������ǽڵ��������ࡣ
 һЩ���õĽڵ����Scene, Layer, Sprite, Menu, Label.
 һ���ڵ����Ҫ�ص�:
 - ���ǿ��԰��������Ľڵ����(`addChild`, `getChildByTag`, `removeChild`, etc)
 - ���ǿ��԰��Ŷ��ڵĻص�(`schedule`, `unschedule`, etc)
 - ���ǿ���ִ��һЩ����(`runAction`, `stopAction`, etc)
 ����ڵ�ͨ����ζ��(��һ��/���е�):
 - ��д��ʼ����Դ���ҿ��԰��Żص�
 - �����ص����������е�ʱ��
 - ��д��draw������Ⱦ�ڵ�
 �ڵ������:
 - λ�ã�Ĭ��ֵ��x=0,y=0��
 - ���ţ�Ĭ��ֵ��x=1,y=1��
 - ��ת���ԽǶ�Ϊ��λ����˳ʱ�뷽�򣩣�Ĭ��ֵ��0��
 - ê�㣨Ĭ��ֵ��x=0,y=0��
 - ���ݴ�С��Ĭ��ֵ��width=0,heigh=0��
 - �ɼ��ԣ�Ĭ��ֵ��true��
 �����ԣ�Limitations:
 - һ���ڵ�����һ����void�������������Ҫ�ڳ����л�һЩ��������Ӧ��ʹ�þ����������档�����ǽڵ�����ಢ����д��draw��.

 */

class CC_DLL Node : public Ref
{
public:

    enum {
        FLAGS_TRANSFORM_DIRTY = (1 << 0),
        FLAGS_CONTENT_SIZE_DIRTY = (1 << 1),
        FLAGS_RENDER_AS_3D = (1 << 3),

        FLAGS_DIRTY_MASK = (FLAGS_TRANSFORM_DIRTY | FLAGS_CONTENT_SIZE_DIRTY),
    };
    /**
     @{
     @name Properties
     @brief @~english @~chinese ����
     */

    /** 
     @property INVALID_TAG
     @~english Default tag used for all the nodes 
     @~chinese �������еĽڵ��Ĭ��Tag
     */
    static const int INVALID_TAG = -1;

    /// @} end of properties

    /**
     @{
     @name Constructor, Destructor and Initializers
     @brief @~english 
     @~chinese ���캯�������������ͳ�ʼ������
     */

    /**
     * @~english Allocates and initializes a node.
     * @~chinese ���䲢�ҳ�ʼ��һ���ڵ�.
     * @return @~english A initialized node which is marked as "autorelease".
     * @~chinese һ����ʼ���Ľڵ㣬�ýڵ���Զ������Ϊ��autorelease��(�Զ��ͷ�).
     */
    static Node * create();

    /**
     * @~english Gets the description string. It makes debugging easier.
     * @~chinese �õ������Ե��ַ������⽫��ʹ�õ��Ը��Ӽ򵥡�
     * @return @~english A string @~chinese һ���ַ���
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /// @} end of initializers



    /**
     @{
     @name Setters & Getters for Graphic Peroperties
     @brief @~english 
     @~chinese ͼ������ֵ�Ļ�ȡ���������ú���
     */

    /**
     @~english LocalZOrder is the 'key' used to sort the node relative to its siblings.

     The Node's parent will sort all its children based ont the LocalZOrder value.
     If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front of the other node in the array.
     
     Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     And Nodes that have LocalZOder values < 0 are the "left" subtree
     While Nodes with LocalZOder >=0 are the "right" subtree.
     
     @~chinese LocalZOrder�ǡ�key��(�ؼ�)���ֱ�ڵ�����ֵܽڵ������ԡ�
     ���ڵ㽫��ͨ��LocalZOrder��ֵ���ֱ����е��ӽڵ㡣
     ��������ڵ���ͬ����LocalZOrder,��ô�ȼ����ӽڵ�����Ľڵ㽫����ʾ�ں����Ľڵ��ǰ�档
     
     ͬ���ģ�����ͼʹ�á�In-Order����˳�򣩡��������㷨������ ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     ����ӵ��С��0��LocalZOrder��ֵ�Ľڵ��ǡ�left����������������
     ����ӵ�д���0��LocalZOrder��ֵ�ýڵ��ǡ�right����������������
     
     @see `setGlobalZOrder`
     @see `setVertexZ`
     *
     * @param localZOrder @~english The local Z order value.
     * @~chinese ���ڽڵ��е�˳��ֵ
     */
    virtual void setLocalZOrder(int localZOrder);

    CC_DEPRECATED_ATTRIBUTE virtual void setZOrder(int localZOrder) { setLocalZOrder(localZOrder); }
    
    /* 
     @~english Helper function used by `setLocalZOrder`. Don't use it unless you know what you are doing.
     @~chinese `setLocalZOrder`ʹ�õĸ�����������Ҫʹ����������֪�����ڸ�ʲô��
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void _setLocalZOrder(int z);

    /**
     * @~english Gets the local Z order of this node.
     * @~chinese �õ�����ڵ�ľֲ�Z˳��
     *
     * @see `setLocalZOrder(int)`
     *
     * @return @~english The local (relative to its siblings) Z order. @~chinese �ֲ�Z��˳��(������ֵܽڵ�)��
     */
    virtual int getLocalZOrder() const { return _localZOrder; }
    CC_DEPRECATED_ATTRIBUTE virtual int getZOrder() const { return getLocalZOrder(); }

    /**
     
     @~english Defines the oder in which the nodes are renderer.
     Nodes that have a Global Z Order lower, are renderer first.
     
     In case two or more nodes have the same Global Z Order, the oder is not guaranteed.
     The only exception if the Nodes have a Global Z Order == 0. In that case, the Scene Graph order is used.
     
     By default, all nodes have a Global Z Order = 0. That means that by default, the Scene Graph order is used to render the nodes.
     
     Global Z Order is useful when you need to render nodes in an order different than the Scene Graph order.
     
     Limitations: Global Z Order can't be used by Nodes that have SpriteBatchNode as one of their ancestors.
     And if ClippingNode is one of the ancestors, then "global Z order" will be relative to the ClippingNode.
     @~chinese ������Ⱦ�ڵ��˳��
     ӵ��ȫ��Z˳��ԽС�Ľڵ㣬������Ⱦ
     
     �����������߸���Ľڵ�ӵ����ͬ��ȫ��Z˳����ô��Ⱦ˳���޷���֤��
     Ψһ������������ڵ��ȫ��Z˳��Ϊ�㣬��ô����ͼ˳���ǿ���ʹ�õġ� 
     
     Ĭ�ϵģ����еĽڵ�ȫ��Z˳�����㡣�����˵��Ĭ��ʹ�ó���ͼ˳������Ⱦ�ڵ㡣
     
     ȫ��Z˳���Ƿǳ����õĵ�����Ҫ��Ⱦ�ڵ㰴�ղ�ͬ��˳������ǳ���ͼ˳��
     
     ������: ȫ��Z˳���ܹ���ӵ�м̳С�SpriteBatchNode���Ľڵ�ʹ�á�
     ���������ClippingNode��������֮һ���ϴ�����ô��global Z order�� ����͡�ClippingNode���йء�

     @see `setLocalZOrder()`
     @see `setVertexZ()`

     @since v3.0
     *
     * @param globalZOrder @~english The global Z order value. @~chinese ȫ��Z��˳��
     */
    virtual void setGlobalZOrder(float globalZOrder);
    /**
     * @~english Returns the Node's Global Z Order.
     * @~chinese ���ؽڵ��ȫ��Z˳��
     *
     * @see `setGlobalZOrder(int)`
     *
     * @return @~english The node's global Z order @~chinese �ڵ��ȫ��Z��˳��
     */
    virtual float getGlobalZOrder() const { return _globalZOrder; }

    /**
     * @~english Sets the scale (x) of the node.
     *
     * It is a scaling factor that multiplies the width of the node and its children.
     * @~chinese ���ýڵ�����ţ�x����
     * 
     * ����һ���������ӣ�������Խڵ�Ŀ��Լ������ӽڵ㡣
     *
     * @param scaleX   @~english The scale factor on X axis. @~chinese X�����������. 
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     */
    virtual void setScaleX(float scaleX);
    /**
     * @~english Returns the scale factor on X axis of this node
     * @~chinese ���ظýڵ��X����������ӡ�
     *
     * @see setScaleX(float)
     *
     * @return @~english The scale factor on X axis. @~chinese X����������ӡ�
     */
    virtual float getScaleX() const;


    /**
     * @~english Sets the scale (y) of the node.
     *
     * It is a scaling factor that multiplies the height of the node and its children.
     * @~chinese ���ýڵ�����ţ�y����
     *
     * ����һ���������ӣ�������Խڵ�Ŀ��Լ������ӽڵ㡣
     *
     * @param scaleY   @~english The scale factor on Y axis. @~chinese Y�����������
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API
     */
    virtual void setScaleY(float scaleY);
    /**
     * @~english Returns the scale factor on Y axis of this node
     * @~chinese ���ظýڵ��Y����������ӡ�
     *
     * @see `setScaleY(float)`
     *
     * @return @~english The scale factor on Y axis. @~chinese Y�����������
     */
    virtual float getScaleY() const;

    /**
     * @~english Changes the scale factor on Z axis of this node
     *
     * The Default value is 1.0 if you haven't changed it before.
     * @~chinese �ı�ýڵ��Z����������ӡ�
     *
     * �����֮ǰû�иı��������ô����Ĭ��ֵ��1.0��
     *
     * @param scaleZ   @~english The scale factor on Z axis. @~chinese Z����������� 
     *
     * @warning @~english The physics body doesn't support this.@~chinese ����ڵ㲻֧�����API 
     */
    virtual void setScaleZ(float scaleZ);
    /**
     * @~english Returns the scale factor on Z axis of this node
     * @~chinese ���ظýڵ��Z����������ӡ�
     *
     * @see `setScaleZ(float)`
     *
     * @return @~english The scale factor on Z axis. @~chinese Z����������ӡ� 
     */
    virtual float getScaleZ() const;


    /**
     * @~english Sets the scale (x,y,z) of the node.
     *
     * It is a scaling factor that multiplies the width, height and depth of the node and its children.
     * @~chinese ���ýڵ�����ţ�x,y,z��.
     *
     * �������ӽ�����Ըýڵ�����ӽڵ�Ŀ��ߺ���ȡ�
     *
     * @param scale     @~english The scale factor for X, Y and Z axis. @~chinese X,Y,Z����������� 
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     */
    virtual void setScale(float scale);
    /**
     * @~english Gets the scale factor of the node,  when X and Y have the same scale factor.
     * @~chinese �õ��ýڵ���������ӣ���X���Y������ͬ����������ʱ��
     *
     * @warning @~english Assert when `_scaleX != _scaleY` @~chinese �ж� �� `_scaleX != _scaleY` 
     * @see setScale(float)
     *
     * @return @~english The scale factor of the node. @~chinese �ýڵ���������� 
     */
    virtual float getScale() const;

    /**
     * @~english Sets the scale (x,y) of the node.
     *
     * It is a scaling factor that multiplies the width and height of the node and its children.
     * @~chinese ���ýڵ�����ţ�x,y��.
     *
     * �������ӳ��Ըýڵ�����ӽڵ�Ŀ���ߡ�
     *
     * @param scaleX     @~english The scale factor on X axis. @~chinese X����������ӡ� 
     * @param scaleY     @~english The scale factor on Y axis. @~chinese Y����������ӡ� 
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     */
    virtual void setScale(float scaleX, float scaleY);

    /**
     * @~english Sets the position (x,y) of the node in its parent's coordinate system.
     *
     * Usually we use `Vec2(x,y)` to compose Vec2 object.
     * This code snippet sets the node in the center of screen.
     * @~chinese ���ýڵ��λ���ڸ��ڵ������ϵϵͳ�С�
     *
     * ͨ������ʹ��`Vec2(x,y)` ����� Vec2 ����
     * ��һ�δ������ýڵ�����Ļ�м䡣
     *
     @code
     Size size = Director::getInstance()->getWinSize();
     node->setPosition(size.width/2, size.height/2);
     @endcode
     *
     * @param position  @~english The position (x,y) of the node in OpenGL coordinates. @~chinese ����ڵ��λ�ã�x,y����OpenGL����ϵ�С� 
     */
    virtual void setPosition(const Vec2 &position);

    /** @~chinese ���ù�һ��λ������(x, y)��ʹ�ô�0��1�Ĺ�һ��ֵ
    ��������λ�ð������µ��߼�����ת����
    @~english Sets the position (x,y) using values between 0 and 1.
     The positions in pixels is calculated like the following:

     @code
     // pseudo code
     void setNormalizedPosition(Vec2 pos) {
       Size s = getParent()->getContentSize();
       _position = pos * s;
     }
     @endcode
     *
     * @param position @~english The normalized position (x,y) of the node, using value between 0 and 1. @~chinese ��һ����λ������ 
     */
    virtual void setNormalizedPosition(const Vec2 &position);

    /**
     * @~english Gets the position (x,y) of the node in its parent's coordinate system.
     * @~chinese �õ��ڸ��ڵ�����ϵ�нڵ��λ�ã�x,y����
     *
     * @see setPosition(const Vec2&)
     *
     * @code
     * In js and lua return value is table which contains x,y.
     * @endcode
     * @return @~english The position (x,y) of the node in OpenGL coordinates. @~chinese �ڵ���OpenGL����ϵ�е�λ�ã�x,y)�� 
     */
    virtual const Vec2& getPosition() const;

    /** @~english Returns the normalized position.
     * @~chinese �õ��ڸ��ڵ�����ϵ�нڵ��һ����λ�ã�x,y����
     * 
     * @return @~english The normalized position. @~chinese ��һ��λ�� 
     */
    virtual const Vec2& getNormalizedPosition() const;

    /**
     * @~english Sets the position (x,y) of the node in its parent's coordinate system.
     *
     * Passing two numbers (x,y) is much efficient than passing Vec2 object.
     * This method is bound to Lua and JavaScript.
     * Passing a number is 10 times faster than passing a object from Lua to c++.
     * @~chinese ���ýڵ��������ڵ�����ϵ�е�λ�ã�x,y����
     *
     * �����������֣�x,y���ȴ���Vec2�������Ч�ʡ�
     * ���������Lua��JavaScript�󶨻����£�
     * �ӽű���C++����һ�����ֱȴ���һ�������10����
     *
     @code
     // sample code in Lua
     local pos  = node::getPosition()  -- returns Vec2 object from C++.
     node:setPosition(x, y)            -- pass x, y coordinate to C++.
     @endcode
     *
     * @param x     @~english X coordinate for position. @~chinese X��λ�� 
     * @param y     @~english Y coordinate for position. @~chinese Y��λ�� 
     */
    virtual void setPosition(float x, float y);
    /**
     * @~english Gets position in a more efficient way, returns two number instead of a Vec2 object.
     * @~chinese ��һ������Ч�ʵķ�����ȡλ�ã�ͨ��ָ����������������ֶ�����Vec2����
     *
     * @see `setPosition(float, float)`
     *
     * @param x @~english To receive x coordinate for position. @~chinese ������ȡX��λ�õĲ��� 
     * @param y @~english To receive y coordinate for position. @~chinese ������ȡY��λ�õĲ��� 
     */
    virtual void getPosition(float* x, float* y) const;
    /** @~english Sets the x coordinate of the node in its parent's coordinate system.
     * @~chinese ���ýڵ��ڸ��ڵ�����ϵ�µ�X��λ��
     *
     * @param x @~english The x coordinate of the node. @~chinese X������ 
     */
    virtual void  setPositionX(float x);
    /** @~english Gets the x coordinate of the node in its parent's coordinate system.
     * @~chinese ��ȡ�ڵ��ڸ��ڵ�����ϵ�µ�X��λ��
     *
     * @return @~english The x coordinate of the node. @~chinese X������ 
     */
    virtual float getPositionX(void) const;
    /** @~english Sets the y coordinate of the node in its parent's coordinate system.
     * @~chinese ���ýڵ��ڸ��ڵ�����ϵ�µ�Y��λ��
     *
     * @param y @~english The y coordinate of the node. @~chinese Y������ 
     */
    virtual void  setPositionY(float y);
    /** @~english Gets the y coordinate of the node in its parent's coordinate system.
     * @~chinese ��ȡ�ڵ��ڸ��ڵ�����ϵ�µ�Y��λ��
     *
     * @return @~english The y coordinate of the node. @~chinese Y������ 
     */
    virtual float getPositionY(void) const;

    /**
     * @~english Sets the position (X, Y, and Z) in its parent's coordinate system.
     * @~chinese ���ýڵ��ڸ��ڵ�����ϵ�е�λ�ã�x,y,z����
     * 
     * @param position @~english The position (X, Y, and Z) in its parent's coordinate system. @~chinese �ڵ��ڸ��ڵ�����ϵ�е�λ�ã�x,y,z�� 
     * @js NA
     */
    virtual void setPosition3D(const Vec3& position);
    /**
     * @~english Returns the position (X,Y,Z) in its parent's coordinate system.
     * @~chinese ��ȡ�ڵ��ڸ�����ϵ��λ�ã�X,Y,Z����
     *
     * @return @~english The position (X, Y, and Z) in its parent's coordinate system. @~chinese �ڵ��ڸ�����ϵ��λ�ã�X,Y,Z�� 
     * @js NA
     */
    virtual Vec3 getPosition3D() const;

    /**
     * @~english Sets the 'z' coordinate in the position. It is the OpenGL Z vertex value.
     *
     * The OpenGL depth buffer and depth testing are disabled by default. You need to turn them on.
     * In order to use this property correctly.
     *
     * `setPositionZ()` also sets the `setGlobalZValue()` with the positionZ as value.
     * @~chinese ����λ�õġ�z��������ϵ����OpneGL Zλ�á�
     *
     * OpenGL��Ȼ������Ȳ���Ĭ��ֵ�ǹرյģ�����Ҫ������
     * ����ȷ��ʹ��������ԡ�
     *
     * `setPositionZ()` ͬ������ `setGlobalZValue()` �á�positionZ�� ��Ϊֵ��
     *
     * @see `setGlobalZValue()`
     *
     * @param positionZ  @~english OpenGL Z vertex of this node. @~chinese �ýڵ��OpenGL Zλ�� 
     * @js setVertexZ
     */
    virtual void setPositionZ(float positionZ);
    CC_DEPRECATED_ATTRIBUTE virtual void setVertexZ(float vertexZ) { setPositionZ(vertexZ); }

    /**
     * @~english Gets position Z coordinate of this node.
     * @~chinese �õ��ýڵ��Z������ϵ��λ�á�
     *
     * @see setPositionZ(float)
     *
     * @return @~english The position Z coordinate of this node. @~chinese �ýڵ��Z������ϵ�� 
     * @js getVertexZ
     */
    virtual float getPositionZ() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getVertexZ() const { return getPositionZ(); }

    /**
     * @~english Changes the X skew angle of the node in degrees.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew function.
     *
     * This angle describes the shear distortion in the X direction.
     * Thus, it is the angle between the Y coordinate and the left edge of the shape
     * The default skewX angle is 0. Positive values distort the node in a CW direction.
     * @~chinese �ı�ýڵ�X�����б�ǣ���λ�Ƕȡ�
     *
     * `setRotationalSkew()`�� `setSkew()` �Ĳ�ͬʱ��ǰһ��ģ��Flash����б���ܡ�
     * Ȼ����һ��ʹ����������б���ܡ�
     *
     * ����Ƕ���������X�᷽������α䣨shear distortion����
     * ��ˣ�����Ƕ���Y���ͼ�����֮�䡣
     * Ĭ��ֵskewX�Ƕ���0����ֵʹ�ýڵ㰴˳ʱ����Ρ�
     *
     * @param skewX @~english The X skew angle of the node in degrees. @~chinese �ýڵ��X�����б�ǡ� 
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     */
    virtual void setSkewX(float skewX);
    /**
     * @~english Returns the X skew angle of the node in degrees.
     * @~chinese ���ظýڵ��X����б�ǣ���λ�Ƕȡ�
     *
     * @see `setSkewX(float)`
     *
     * @return @~english The X skew angle of the node in degrees. @~chinese �ýڵ��X����б�ǡ� 
     */
    virtual float getSkewX() const;


    /**
     * @~english Changes the Y skew angle of the node in degrees.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew function.
     *
     * This angle describes the shear distortion in the Y direction.
     * Thus, it is the angle between the X coordinate and the bottom edge of the shape.
     * The default skewY angle is 0. Positive values distort the node in a CCW direction.
     * @~chinese �ı�ýڵ�Y�����б�ǣ���λ�Ƕȡ�
     *
     * `setRotationalSkew()`�� `setSkew()` �Ĳ�ͬʱ��ǰһ��ģ��Flash����б���ܡ�
     * Ȼ����һ��ʹ����������б���ܡ�
     *
     * ����Ƕ���������Y�᷽������α䣨shear distortion����
     *  ��ˣ�����Ƕ���X���ͼ�εױ�֮�䡣
     * Ĭ��ֵskewY�Ƕ���0����ֵʹ�ýڵ㰴˳ʱ����Ρ�
     *
     * @param skewY    @~english The Y skew angle of the node in degrees. @~chinese �ýڵ��Y�����б�ǡ� 
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     */
    virtual void setSkewY(float skewY);
    /**
     * @~english Returns the Y skew angle of the node in degrees.
     * @~chinese ���ظýڵ��Y����б�ǣ���λ�Ƕȡ�
     *
     * @see `setSkewY(float)`
     *
     * @return @~english The Y skew angle of the node in degrees. @~chinese �ýڵ��Y����б�ǡ� 
     */
    virtual float getSkewY() const;


    /**
     * @~english Sets the anchor point in percent.
     *
     * anchorPoint is the point around which all transformations and positioning manipulations take place.
     * It's like a pin in the node where it is "attached" to its parent.
     * The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
     * But you can use values higher than (1,1) and lower than (0,0) too.
     * The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
     * @~chinese ����ê�㣬�ðٷֱȱ�ʾ��
     *
     * һ��ê�������е�ת���Ͷ�λ���������ĵ㡣
     * �������ڽڵ��������丸��Ĵ�ͷ�롣
     * ê���Ǳ�׼���ģ�����ٷֱ�һ����(0,0)��ʾ���½ǣ�(1,1)��ʾ���Ͻǡ�
     * ���������ʹ�ñȣ�1,1,�����ߵ�ֵ���߱ȣ�0,0�����͵�ֵ��
     * Ĭ�ϵ�ê���ǣ�0.5,0.5�����������ʼ�ڽڵ������λ�á�
     * @note @~english If node has a physics body, the anchor must be in the middle, you cann't change this to other value. @~chinese ����ڵ��������壬ê����������ģ��㲻�ܹ����ֵ�� 
     *
     * @param anchorPoint   @~english The anchor point of node. @~chinese �ڵ��ê�㡣 
     */
    virtual void setAnchorPoint(const Vec2& anchorPoint);
    /**
     * @~english Returns the anchor point in percent.
     * @~chinese �����ðٷֱȱ�ʾ��ê�㡣
     *
     * @see `setAnchorPoint(const Vec2&)`
     *
     * @return @~english The anchor point of node. @~chinese �ڵ��ê�� 
     */
    virtual const Vec2& getAnchorPoint() const;
    /**
     * @~english Returns the anchorPoint in absolute pixels.
     * @~chinese ����ê��ľ�������λ��
     *
     * @warning @~english You can only read it. If you wish to modify it, use anchorPoint instead. @~chinese ��ֻ�ܹ���ȡ������������޸�����ʹ��setAnchoPoint�� 
     * @see `getAnchorPoint()`
     *
     * @return @~english The anchor point in absolute pixels. @~chinese �������ص�ê�㡣 
     */
    virtual const Vec2& getAnchorPointInPoints() const;


    /**
     * @~english Sets the untransformed size of the node.
     *
     * The contentSize remains the same no matter the node is scaled or rotated.
     * All nodes has a size. Layer and Scene has the same size of the screen.
     * @~chinese ���ò�ת���ڵ�Ĵ�С��
     *
     * contentSize��Ȼ����ͬ�ģ����۽ڵ������Ż�����ת��
     * ���еĽڵ㶼�д�С��ͼ��ͳ�������ͬ����Ļ��С��
     *
     * @param contentSize   @~english The untransformed size of the node. @~chinese δת���ڵ�Ĵ�С 
     */
    virtual void setContentSize(const Size& contentSize);
    /**
     * @~english Returns the untransformed size of the node.
     * @~chinese ���ؽڵ�δ����״̬�µĴ�С��
     *
     * @see `setContentSize(const Size&)`
     *
     * @return @~english The untransformed size of the node. @~chinese �ڵ�δ����״̬�µĴ�С 
     */
    virtual const Size& getContentSize() const;


    /**
     * @~english Sets whether the node is visible.
     *
     * The default value is true, a node is default to visible.
     * @~chinese ���ýڵ��Ƿ�ɼ���
     *
     * Ĭ��ֵ��true,һ���ڵ�Ĭ���ǿɼ��ġ�
     *
     * @param visible   @~english true if the node is visible, false if the node is hidden. @~chinese true ����ڵ��ǿɼ��ģ�false ����ڵ������صġ� 
     */
    virtual void setVisible(bool visible);
    /**
     * @~english Determines if the node is visible.
     * @~chinese �жϽڵ��Ƿ�ɼ���
     *
     * @see `setVisible(bool)`
     *
     * @return @~english true if the node is visible, false if the node is hidden. @~chinese true ����ڵ��ǿɼ���, false ����ڵ������صġ� 
     */
    virtual bool isVisible() const;


    /**
     * @~english Sets the rotation (angle) of the node in degrees.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * @~chinese ���ýڵ����ת��angle���Ƕȡ�
     *
     * 0 ��Ĭ�ϵ���ת�Ƕȡ�
     * ����˳ʱ����ת�ڵ㣬������ʱ����ת�ڵ㡣
     *
     * @param rotation     @~english The rotation of the node in degrees. @~chinese �ڵ����ת�Ƕȡ� 
     */
    virtual void setRotation(float rotation);
    /**
     * @~english Returns the rotation of the node in degrees.
     * @~chinese ���ؽڵ����ת�Ƕȡ�
     *
     * @see `setRotation(float)`
     *
     * @return @~english The rotation of the node in degrees. @~chinese �ڵ����ת�Ƕȡ� 
     */
    virtual float getRotation() const;

    /**
     * @~english Sets the rotation (X,Y,Z) in degrees.
     * Useful for 3d rotations.
     * @~chinese ���ã�X,Y,Z����ת�Ƕȡ�
     * ��3d��ת�ǳ����á�
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     *
     * @param rotation @~english The rotation of the node in 3d. @~chinese 3D�ռ��е���ת�Ƕ� 
     * @js NA
     */
    virtual void setRotation3D(const Vec3& rotation);
    /**
     * @~english Returns the rotation (X,Y,Z) in degrees.
     * @~chinese ��ȡ��X,Y,Z������ת�Ƕȡ�
     * 
     * @return @~english The rotation of the node in 3d. @~chinese 3D�ռ��е���ת�Ƕ� 
     * @js NA
     */
    virtual Vec3 getRotation3D() const;
    
    /**
     * @~english Set rotation by quaternion. You should make sure the quaternion is normalized.
     * @~chinese ͨ����Ԫ��������3D�ռ��е���ת�Ƕȡ���Ҫ��֤��Ԫ���Ǿ�����һ���ġ�
     *
     * @param quat @~english The rotation in quaternion, note that the quat must be normalized. 
     * @~chinese ��Ԫ������ע����Ԫ�������Ǿ�����һ����
     * @js NA
     */
    virtual void setRotationQuat(const Quaternion& quat);
    
    /**
     * @~english Return the rotation by quaternion, Note that when _rotationZ_X == _rotationZ_Y, the returned quaternion equals to RotationZ_X * RotationY * RotationX,
     * @~chinese ��ȡ��Ԫ������3D�ռ���ת�Ƕȣ���`_rotationZ_X == _rotationZ_Y`��ʱ����Ԫ��ֵ����`RotationZ_X * RotationY * RotationX`������ֵ����`RotationY * RotationX`��
     * it equals to RotationY * RotationX otherwise.
     *
     * @return @~english The rotation in quaternion. @~chinese ��Ԫ������ 
     * @js NA
     */
    virtual Quaternion getRotationQuat() const;

    /**
     * @~english Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality,
     * while the second one uses the real skew function.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * @~chinese ���ýڵ�X�����ת�Ƕȣ�����Ϊˮƽ��ת��б��
     *
     * `setRotationalSkew()` �� `setSkew()`�Ĳ�ͬ��ǰһ����ģ��Flash����б����
     * Ȼ����һ��ʹ����������б���ܡ�
     *
     * 0 ��Ĭ�ϵ���ת�Ƕȡ�
     * �����ڵ�˳ʱ����ת�������ڵ���ʱ����ת��
     *
     * @param rotationX    @~english The X rotation in degrees which performs a horizontal rotational skew. @~chinese X�����ת�Ƕȱ���Ϊˮƽ��ת��б�� 
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     * @js setRotationX
     */
    virtual void setRotationSkewX(float rotationX);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationX(float rotationX) { return setRotationSkewX(rotationX); }

    /**
     * @~english Gets the X rotation (angle) of the node in degrees which performs a horizontal rotation skew.
     * @~chinese �õ�X��ڵ����ת�Ƕȣ�����Ϊˮƽ��ת��б��horizontal rotation skew��.
     *
     * @see `setRotationSkewX(float)`
     *
     * @return @~english The X rotation in degrees. @~chinese X�����ת�Ƕȡ� 
     * @js getRotationX 
     */
    virtual float getRotationSkewX() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationX() const { return getRotationSkewX(); }

    /**
     * @~english Sets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality,
     * while the second one uses the real skew function.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * @~chinese ����Y��ڵ����ת�Ƕȣ�����Ϊ��ֱ��ת��б��
     *
     * `setRotationalSkew()` ��`setSkew()` �Ĳ�ͬ��ǰһ��ʹ��Flash��б����
     * ��һ��ʹ������������б���ܡ�
     *
     * 0 Ĭ�ϵ���ת�Ƕȡ�
     * ������ʾ˳ʱ����ת��������ʾ��ʱ����ת��
     *
     * @param rotationY    @~english The Y rotation in degrees. @~chinese Y�����ת�Ƕȡ� 
     *
     * @warning @~english The physics body doesn't support this. @~chinese ����ڵ㲻֧�����API 
     * @js setRotationY
     */
    virtual void setRotationSkewY(float rotationY);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationY(float rotationY) { return setRotationSkewY(rotationY); }

    /**
     * @~english Gets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     * @~chinese �õ��ڵ�Y�����ת�Ƕȣ�����Ϊ��ֱ��ת��б��vertical rotational skew.��
     *
     * @see `setRotationSkewY(float)`
     *
     * @return @~english The Y rotation in degrees. @~chinese Y����ת�Ƕȡ� 
     * @js getRotationY
     */
    virtual float getRotationSkewY() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationY() const { return getRotationSkewY(); }

    /**
     * @~english Sets the arrival order when this node has a same ZOrder with other children.
     *
     * A node which called addChild subsequently will take a larger arrival order,
     * If two children have the same Z order, the child with larger arrival order will be drawn later.
     * @~chinese ���õ���˳�򣬵�����ڵ�������ӽڵ�����ͬ��ZOrderʱ��
     *
     * һ��������֮�������addChild�����Ľڵ㽫���и���ĵ���˳��ֵ��
     * ��������Ӷ�������ͬ��Z��˳������и��󵽴�˳������ཫ��󻭡�
     *
     * @warning @~english This method is used internally for localZOrder sorting, don't change this manually @~chinese ����������ڲ�������localZOrder���򣬲����ֶ��ĸı䡣
     *
     * @param orderOfArrival   @~english The arrival order. @~chinese ����˳�� 
     */
    void setOrderOfArrival(int orderOfArrival);
    /**
     * @~english Returns the arrival order, indicates which children is added previously.
     * @~chinese ���ص���˳��ָ����һ�������ȱ���ӡ�
     *
     * @see `setOrderOfArrival(unsigned int)`
     *
     * @return @~english The arrival order. @~chinese ����˳�� 
     */
    int getOrderOfArrival() const;


    /** @deprecated No longer needed
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE void setGLServerState(int serverState) { /* ignore */ };
    /** @deprecated No longer needed
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE int getGLServerState() const { return 0; }

    /**
     * @~english Sets whether the anchor point will be (0,0) when you position this node.
     *
     * This is an internal method, only used by Layer and Scene. Don't call it outside framework.
     * The default value is false, while in Layer and Scene are true.
     * @~chinese ����Ĩ��Ϊ��0,0������ڷ�����ڵ��ʱ��
     *
     * ����һ���ڲ�������������Layer��Sceneʹ�á���Ҫ�ڿ������á�
     * Ĭ��ֵ��false,������Layer��Scene����true.
     *
     * @param ignore    @~english true if anchor point will be (0,0) when you position this node. @~chinese true ���ê���ǣ�0,0������ڷ�����ڵ��ʱ�� 
     * @todo @~english This method should be renamed as setIgnoreAnchorPointForPosition(bool) or something with "set".
     * @~chinese �������Ӧ�ñ�����ΪsetIgnoreAnchorPointForPosition(bool) �����������С�set�������ơ�
     */
    virtual void ignoreAnchorPointForPosition(bool ignore);
    /**
     * @~english Gets whether the anchor point will be (0,0) when you position this node.
     * @~chinese �õ��ڵ��ê���Ƿ�Ϊ��0,0��������ڷ�����ڵ�ʱ��
     *
     * @see `ignoreAnchorPointForPosition(bool)`
     *
     * @return @~english true if the anchor point will be (0,0) when you position this node. @~chinese ���ê���� (0,0) ����ڷ�����ڵ�ʱ����true�� 
     */
    virtual bool isIgnoreAnchorPointForPosition() const;

    /// @}  end of Setters & Getters for Graphic Properties


    /// @{
    /// @name Children and Parent
    /// @brief @~english @~chinese ���ӽڵ��ϵ

    /**
     * @~english Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese ���һ���ӽڵ㵽�����ڣ�z-order��0.
     *
     * ����ӽڵ㱻��ӵ���һ����running����ŵģ����ڵ㣬��ô'onEnter'�� 'onEnterTransitionDidFinish' �����������á�
     *
     * @param child     @~english A child node. @~chinese һ���ӽڵ㡣 
     */
    virtual void addChild(Node * child);
    /**
     * @~english Adds a child to the container with a local z-order.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese ���һ���ӽڵ㵽�����У�������һ���ֲ�Z��˳��
     *
     * ����ӽڵ㱻��ӵ���һ����running����ŵģ����ڵ㣬��ô'onEnter'�� 'onEnterTransitionDidFinish' �����������á�
     *
     * @param child         @~english A child node. @~chinese һ���ӽڵ㡣 
     * @param localZOrder   @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`. @~chinese Z��˳��Ϊ�˻滭������Ȩ�� ��ο� `setLocalZOrder(int)` 
     */
    virtual void addChild(Node * child, int localZOrder);
    /**
     * @~english Adds a child to the container with z order and tag.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese ���һ���ӽڵ㵽�����У���Z��˳���һ����ǡ�
     *
     * ����ӽڵ㱻��ӵ���һ����running����ŵģ����ڵ㣬��ô'onEnter'�� 'onEnterTransitionDidFinish' �����������á�
     *
     * @param child         @~english A child node. @~chinese һ���ӽڵ� 
     * @param localZOrder   @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`. @~chinese Z��˳��Ϊ�˻滭������Ȩ�� ��ο� `setLocalZOrder(int)` 
     * @param tag           @~english An integer to identify the node easily. Please refer to `setTag(int)`. @~chinese һ�����������׷ֱ�ڵ����������ο� `setTag(int)` 
     * 
     * @~english Please use `addChild(Node* child, int localZOrder, const std::string &name)` instead.
     * @~chinese ��ʹ��`addChild(Node* child, int localZOrder, const std::string &name)`
     */
     virtual void addChild(Node* child, int localZOrder, int tag);
    /**
     * @~english Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese ���һ���ӽڵ㵽�����У�������һ���ֲ�Z��˳��
     *
     * ����ӽڵ㱻��ӵ���һ����running����ŵģ����ڵ㣬��ô'onEnter'�� 'onEnterTransitionDidFinish' �����������á�
     *
     * @param child     @~english A child node. @~chinese һ���ӽڵ㡣 
     * @param localZOrder    @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`. @~chinese Z��˳��Ϊ�˻滭������Ȩ�� ��ο� `setLocalZOrder(int)` 
     * @param name      @~english A string to identify the node easily. Please refer to `setName(int)`. @~chinese һ��������ǽڵ�����֣���ο�`setName(int)` 
     *
     */
    virtual void addChild(Node* child, int localZOrder, const std::string &name);
    /**
     * @~english Gets a child from the container with its tag.
     * @~chinese ��������ͨ����ǵõ���Ӧ���ӽڵ㡣
     *
     * @param tag   @~english An identifier to find the child node. @~chinese һ����ʶ�������ҵ��ӽڵ㡣 
     *
     * @return @~english A node object whose tag equals to the input parameter. @~chinese һ�����������Ĳ�����ͬ�Ľڵ���� 
     *
     * Please use `getChildByName()` instead.
     */
     virtual Node * getChildByTag(int tag) const;
    
     /**
     * Gets a child from the container with its tag that can be cast to Type T.
     *
     * @param tag   An identifier to find the child node.
     *
     * @return a Node with the given tag that can be cast to Type T.
    */
    template <typename T>
    inline T getChildByTag(int tag) const { return static_cast<T>(getChildByTag(tag)); }
    
    /**
     * @~english Gets a child from the container with its name.
     * @~chinese ��������ͨ�����ֵõ���Ӧ���ӽڵ㡣
     *
     * @param name   @~english An identifier to find the child node. @~chinese һ�����������ҵ��ӽڵ㡣 
     *
     * @return @~english A node object whose name equals to the input parameter. @~chinese һ������������Ĳ�����ͬ�Ľڵ���� 
     *
     * @since v3.2
     */
    virtual Node* getChildByName(const std::string& name) const;
    /**
     * @~english Gets a child from the container with its name that can be cast to Type T.
     * @~chinese ͨ�����ֻ��һ���ӽڵ���󣬲�������ڵ������Ա�ת��Ϊ����T��
     *
     * @param name   @~english An identifier to find the child node. @~chinese һ�����������ҵ��ӽڵ㡣 
     *
     * @return @~english A node with the given name that can be cast to Type T. @~chinese һ������������Ĳ�����ͬ���ҿ��Ա�ת��Ϊ����T�Ľڵ���� 
    */
    template <typename T>
    inline T getChildByName(const std::string& name) const { return static_cast<T>(getChildByName(name)); }
    /** 
     * @~english Search the children of the receiving node to perform processing for nodes which share a name.
     * @~chinese ���ӽڵ���Ѱ��ƥ�����ֻ�������ʽ�Ľڵ㲢����Щ�ڵ�ִ�лص�������
     *
     * @param name @~english The name to search for, supports c++11 regular expression.
     * @~chinese ���������������ַ�����֧��C++11������ʽ
     *
     * @~english Search syntax options:
     * - `//`: Can only be placed at the begin of the search string. This indicates that it will search recursively.
     * - `..`: The search should move up to the node's parent. Can only be placed at the end of string.
     * - `/` : When placed anywhere but the start of the search string, this indicates that the search should move to the node's children.
     * @code
     * enumerateChildren("//MyName", ...): This searches the children recursively and matches any node with the name `MyName`.
     * enumerateChildren("[[:alnum:]]+", ...): This search string matches every node of its children.
     * enumerateChildren("A[[:digit:]]", ...): This searches the node's children and returns any child named `A0`, `A1`, ..., `A9`.
     * enumerateChildren("Abby/Normal", ...): This searches the node's grandchildren and returns any node whose name is `Normal`
     * and whose parent is named `Abby`.
     * enumerateChildren("//Abby/Normal", ...): This searches recursively and returns any node whose name is `Normal` and whose
     * parent is named `Abby`.
     * @endcode
     * 
     * @~chinese �����﷨˵��:
     * - `//`: �������ַ���������б�ܿ�ͷ��ʱ��������ݹ���У�������ǰ�ڵ�������ӽڵ�����
     * - `..`: �������ַ����������������ʱ���������ѯ��ǰ�ڵ�ĸ��ڵ�
     * - `/` : �������ַ����ڲ������ڿ�ͷ����������б�ܣ���������ָ�����ӽڵ�
     * @code
     * enumerateChildren("//MyName", ...): ��ѯ�����ӽڵ�����ƥ����������Ϊ`MyName`�Ľڵ㡣
     * enumerateChildren("[[:alnum:]]+", ...): ���������ʽ��ƥ�����������ֵ�ֱ���ӽڵ㡣
     * enumerateChildren("A[[:digit:]]", ...): ���������ʽ��ƥ����������Ϊ`A0`, `A1`, ..., `A9`���ӽڵ㡣
     * enumerateChildren("Abby/Normal", ...): ƥ����ΪAbby��ֱ���ӽڵ����ΪNormal���ӽڵ㡣
     * enumerateChildren("//Abby/Normal", ...): ��ѯ�����ӽڵ�����ƥ����������ΪNormal���Ҹ��ڵ�����ΪAbby�Ľڵ㡣
     * @endcode
     *
     * @warning @~english Only support alphabet or number for name, and not support unicode.
     * @~chinese name����ֻ֧����ĸ�����֣���֧��unicode�ַ�
     *
     * @param callback @~english A callback function to execute on nodes that match the `name` parameter. The function takes the following arguments:
     *  `node` 
     *      A node that matches the name
     *  And returns a boolean result. Your callback can return `true` to terminate the enumeration.
     * @~chinese �ص�����������ƥ�䵽�Ľڵ㶼�ᱻ����ص�����ִ�У�����ص������Ĳ�����`node`��ƥ�䵽�Ľڵ㡣���ҷ���һ������ֵ��
     * �����߿������Լ�����Ļص������з���`true`���ս�enumerateChildren����������
     * @since v3.2
     */
    virtual void enumerateChildren(const std::string &name, std::function<bool(Node* node)> callback) const;
    /**
     * @~english Returns the array of the node's children.
     * @~chinese ���������ӽڵ�����顣
     *
     * @return @~english the array the node's children. @~chinese �ӽڵ����顣 
     */
    virtual Vector<Node*>& getChildren() { return _children; }
    virtual const Vector<Node*>& getChildren() const { return _children; }
    
    /** 
     * @~english Returns the amount of children.
     * @~chinese �����ӽڵ������
     *
     * @return @~english The amount of children. @~chinese �ӽڵ������ 
     */
    virtual ssize_t getChildrenCount() const;

    /**
     * @~english Sets the parent node.
     * @~chinese ���ýڵ�ĸ��ڵ�
     *
     * @param parent    @~english A pointer to the parent node. @~chinese ָ�򸸽ڵ��ָ�롣 
     */
    virtual void setParent(Node* parent);
    /**
     * @~english Returns a pointer to the parent node.
     * @~chinese ����ָ�򸸽ڵ��ָ�롣
     *
     * @see `setParent(Node*)`
     *
     * @returns @~english A pointer to the parent node. @~chinese ָ�򸸽ڵ��ָ�롣 
     */
    virtual Node* getParent() { return _parent; }
    virtual const Node* getParent() const { return _parent; }


    ////// REMOVES //////

    /**
     * @~english Removes this node itself from its parent node with a cleanup.
     * If the node orphan, then nothing happens.
     * @~chinese �Ӹ��ڵ���ɾ��һ���ڵ㣬��һ��cleanup������
     * �������ڵ���һ���½ڵ㣬��ôʲô�����ᷢ����
     * @see `removeFromParentAndCleanup(bool)`
     */
    virtual void removeFromParent();
    /**
     * @~english Removes this node itself from its parent node.
     * If the node orphan, then nothing happens.
     * @~chinese �Ӹ��ڵ���ɾ��һ���ڵ�
     * �������ڵ���һ���½ڵ㣬��ôʲô�����ᷢ����
     * @param cleanup   @~english true if all actions and callbacks on this node should be removed, false otherwise.
     * @~chinese true ������ڵ������еĶ����ͻص����ᱻɾ��, false �Ͳ���ɾ����
     * @js removeFromParent
     * @lua removeFromParent
     */
    virtual void removeFromParentAndCleanup(bool cleanup);

    /**
     * @~english Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     * @~chinese ��������ɾ��һ�����ӣ�ȡ����cleanup������ͬʱ���ܻ�������еĻ�Ķ�����
     *
     * @param child     @~english The child node which will be removed. @~chinese ϣ����ɾ�����ӽڵ㡣 
     * @param cleanup   @~english True if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese true ������ڵ������еĶ����ͻص����ᱻɾ��, false �Ͳ���ɾ����
     */
    virtual void removeChild(Node* child, bool cleanup = true);

    /**
     * @~english Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     * @~chinese ��һ��������ɾ��һ������ͨ�����ֵ��ȡ����cleanup����ͬʱ��������еĻ�Ķ�����
     *
     * @param tag       @~english An interger number that identifies a child node. @~chinese һ������ʶ���ӽڵ�������� 
     * @param cleanup   @~english True if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese true ������ڵ������еĶ����ͻص����ᱻɾ���� false �Ͳ���ɾ����
     *
     * Please use `removeChildByName` instead.
     */
     virtual void removeChildByTag(int tag, bool cleanup = true);
    /**
     * @~english Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     * @~chinese ͨ������ɾ��һ���ڵ㣬Ĭ�ϻ�ɾ�����ж�����
     *
     * @param name      @~english A string that identifies a child node. @~chinese ���ڱ�ʾ�ڵ������
     * @param cleanup   @~english True if all running actions and callbacks on the child node will be cleanup, false otherwise. 
     * @~chinese true ������ڵ������еĶ����ͻص����ᱻɾ���� false �Ͳ���ɾ����
     */
    virtual void removeChildByName(const std::string &name, bool cleanup = true);
    /**
     * @~english Removes all children from the container with a cleanup.
     * @~chinese ��������ɾ�����еĺ��ӣ���������ж����ͻص���
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren();
    /**
     * @~english Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     * @~chinese ��������ɾ�����еĺ���, ȡ����cleanup������ͬʱ���ܻ�������еĻ�Ķ�����
     *
     * @param cleanup   @~english True if all running actions on all children nodes should be cleanup, false oterwise.
     * @~chinese true ������ڵ������еĶ����ͻص����ᱻɾ��, false �Ͳ���ɾ����
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);

    /**
     * @~english Reorders a child according to a new z value.
     * @~chinese ��һ�������趨һ���µ�z��ֵ����������
     *
     * @param child     @~english An already added child node. It MUST be already added. @~chinese һ���Ѿ�����ӵ��ӽڵ㣬���������Ѿ���ӵġ� 
     * @param localZOrder @~english Z order for drawing priority. Please refer to setLocalZOrder(int).
     * @~chinese Z��˳��Ϊ�˻滭���ȼ�����ο�setLocalZOrder(int)��
     */
    virtual void reorderChild(Node * child, int localZOrder);

    /**
     * @~english Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @~chinese �ڻ滭֮ǰ���������еĺ�������һ�Σ�������ÿ����ӻ���ɾ���ӽڵ�ʱ������
     * ����������Դ���ȵ�������ܡ�
     * @note @~english Don't call this manually unless a child added needs to be removed in the same frame.
     * @~chinese ��Ҫ�ֶ������������������һ����ӹ����ӽڵ㽫Ҫ��ɾ��������ṹ�ڡ�
     */
    virtual void sortAllChildren();

    /// @} end of Children and Parent
    
    /// @{
    /// @name Tag & User data
    /// @brief @~english @~chinese ��ǩ���û�����

    /**
     * @~english Returns a tag that is used to identify the node easily.
     * @~chinese ����һ���������򵥷ֱ�ڵ�ı�ǡ�
     *
     * @return @~english An integer that identifies the node. @~chinese һ���ֱ�ڵ�������� 
     *
     * Please use `getTag()` instead.
     */
     virtual int getTag() const;
    /**
     * @~english Changes the tag that is used to identify the node easily.
     *
     * Please refer to getTag for the sample code.
     * @~chinese �ı���������ֱ�ڵ�ı�ǡ�
     *
     * ��ο� getTag ����ͬ���롣
     *
     * @param tag   @~english A integer that identifies the node. @~chinese һ������ʶ��ڵ�������� 
     *
     * Please use `setName()` instead.
     */
     virtual void setTag(int tag);
    
    /** @~english Returns a string that is used to identify the node.
     * @~chinese ��������ʶ��ڵ�����֡�
     * @return @~english A string that identifies the node. @~chinese ����ʶ��ڵ�����֡� 
     * 
     * @since v3.2
     */
    virtual const std::string& getName() const;
    /** @~english Changes the name that is used to identify the node easily.
     * @~chinese ��������ʶ��ڵ�����֡�
     * @param name @~english A string that identifies the node. @~chinese ����ʶ��ڵ������ 
     *
     * @since v3.2
     */
    virtual void setName(const std::string& name);

    
    /**
     * @~english Returns a custom user data pointer.
     *
     * You can set everything in UserData pointer, a data block, a structure or an object.
     * @~chinese ����һ���û��Զ������ݵ�ָ�롣
     *
     * �������������UserData ָ��Ϊ, һ�����ݿ�, �ṹ�����һ������
     *
     * @return @~english A custom user data pointer. @~chinese �û��Զ������ݵ�ָ�롣 
     * @lua NA
     */
    virtual void* getUserData() { return _userData; }
    /**
    * @lua NA
    */
    virtual const void* getUserData() const { return _userData; }

    /**
     * @~english Sets a custom user data pointer.
     *
     * You can set everything in UserData pointer, a data block, a structure or an object, etc.
     * @~chinese ����һ���û��Զ������ݵ�ָ�롣
     *
     * �������������UserData ָ��Ϊ, һ�����ݿ�, �ṹ�����һ�����󣬵ȵȡ�
     * @warning @~english Don't forget to release the memory manually,
     *          especially before you change this data pointer, and before this node is autoreleased.
     * @~chinese ��Ҫ����Ҫ�ֶ��ͷ��ڴ棬
     *          �ر�������ı��������ָ��֮ǰ��������ڵ㱻�Զ��ͷ�֮ǰ��
     *
     * @param userData  @~english A custom user data pointer. @~chinese һ���û��Զ�������ָ�롣 
     * @lua NA
     */
    virtual void setUserData(void *userData);

    /**
     * @~english Returns a user assigned Object.
     *
     * Similar to userData, but instead of holding a void* it holds an object.
     * @~chinese ����һ���û��趨�Ķ���
     *
     * ��userData����, ����ֻ��ָ��һ��Ref���͵Ķ���
     *
     * @return @~english A user assigned Object. @~chinese һ���û�����Ķ��� 
     * @lua NA
     */
    virtual Ref* getUserObject() { return _userObject; }
    /**
    * @lua NA
    */
    virtual const Ref* getUserObject() const { return _userObject; }

    /**
     * @~english Returns a user assigned Object.
     *
     * Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method,
     * and the previous UserObject (if existed) will be released.
     * The UserObject will be released in Node's destructor.
     * @~chinese ����һ���û�����Ķ���
     *
     * ��userData����, ����ӵ�е���һ�����������void*
     * UserObject�������������������һ��
     * Ȼ��֮ǰ��UserObject ��������ڵĻ������ᱻ�ͷš�
     * UserObject �����ڽڵ�������������ͷš�
     *
     * @param userObject    @~english A user assigned Object. @~chinese һ���û�����Ķ��� 
     */
    virtual void setUserObject(Ref *userObject);

    /// @} end of Tag & User Data


    /// @{
    /// @name GLProgram
    /// @brief @~english @~chinese OpenGL��ɫ������
    /**
     * @~english Return the GLProgram (shader) currently used for this node.
     * @~chinese ���ص�ǰ��������ڵ����ɫ������ (shader) 
     *
     * @return @~english The GLProgram (shader) currently used for this node. @~chinese ��ǰ��������ڵ��GLProgram (shader) 
     */
    GLProgram* getGLProgram() const;
    CC_DEPRECATED_ATTRIBUTE GLProgram* getShaderProgram() const { return getGLProgram(); }
    /**
     * @~english Sets the shader program for this node
     *
     * Since v2.0, each rendering node must set its shader program.
     * It should be set in initialize phase.
     * @~chinese Ϊ����ڵ�������ɫ������
     *
     * �Դ� v2.0, ÿһ����Ⱦ�Ľڵ�����������Լ�����ɫ������
     * ��Ӧ���ڳ�ʼ���׶α����á�
     @code
     node->setGLrProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
     @endcode
     *
     * @param glprogram @~english The shader program. @~chinese ��ɫ������ 
     */
    virtual void setGLProgram(GLProgram *glprogram);
    CC_DEPRECATED_ATTRIBUTE void setShaderProgram(GLProgram *glprogram) { setGLProgram(glprogram); }
    
    /**
     * @~english Return the GLProgramState currently used for this node.
     * @~chinese ���ؽڵ㵱ǰʹ�õ�OpenGL��ɫ������״̬
     *
     * @return @~english The GLProgramState currently used for this node.
     * @~chinese �ڵ㵱ǰʹ�õ�OpenGL��ɫ������״̬
     */
    GLProgramState *getGLProgramState() const;
    /**
     * @~english Set the GLProgramState for this node.
     * @~chinese ���ýڵ㵱ǰʹ�õ�OpenGL��ɫ������״̬
     *
     * @param glProgramState @~english The GLProgramState for this node. @~chinese OpenGL��ɫ������״̬ 
     */
    virtual void setGLProgramState(GLProgramState *glProgramState);
    
    /// @} end of Shader Program


    /**
     * @~english Returns whether or not the node is "running".
     *
     * If the node is running it will accept event callbacks like onEnter(), onExit(), update().
     * @~chinese ���ؽڵ��Ƿ��ǡ�running(���)����
     *
     * ����ڵ��ǻ�ģ������������¼��ص�����onEnter(), onExit(), update()
     *
     * @return @~english Whether or not the node is running. @~chinese �ڵ��Ƿ��ǡ�running(���)���� 
     */
    virtual bool isRunning() const;

    /**
     * @~english Schedules for lua script.
     * @~chinese Lua script��ʱ���
     * @js NA
     *
     * @param handler @~english The key to search lua function. @~chinese ����Ѱ��Lua������key 
     * @param priority @~english A given priority value. @~chinese һ�����������ȼ� 
     */
    void scheduleUpdateWithPriorityLua(int handler, int priority);

    /// @}  end Script Bindings


    /// @{
    /// @name Event Callbacks
    /// @brief @~english @~chinese �¼��ص�����

    /**
     * @~english Event callback that is invoked every time when Node enters the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
     * @~chinese ÿ�ε�Node���롰stage��ʱ�ŵ����¼��ص���
     * ���Node���롰stage��״̬ʱ������һ��ת����transition��,��ô�¼����������ת����ʼ��ʱ�򱻵��á�
     * ��onEnter�����У��㲻�ܹ����롰sister/brother�����ýڵ㡣
     * �������д��onEnter��������Ӧ�õ������ĸ��࣬e.g., Node::onEnter().
     * @lua NA
     */
    virtual void onEnter();

    /** @~chinese ÿ�ε�Node���롰stage��ʱ�ŵ����¼��ص���
     * ���Node���롰stage��״̬ʱ������һ��ת����transition��,��ô�¼����������ת��������ʱ�򱻵��á�
     * �������д��onEnterTransitionDidFinish���� ��Ӧ�õ������ĸ���, e.g. Node::onEnterTransitionDidFinish()
     * @~english Event callback that is invoked when the Node enters in the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish();

    /**
     * @~english Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @~chinese ÿ�ε�Node�뿪��stage��ʱ�ŵ����¼��ص���
     * ���Node�뿪��stage��״̬ʱ������һ��ת����transition��, ��ô�¼����������ת��������ʱ�򱻵��á�
     * ��onEnter���������㲻�ܹ�����һ�����ýڵ㡣
     * �������дonExit, ��Ӧ�õ������ĸ���, e.g., Node::onExit().
     * @lua NA
     */
    virtual void onExit();

    /**
     * @~english Event callback that is called every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
     * @~chinese ÿ�ε�Node�뿪��stage��ʱ�ŵ����¼��ص���
     * ���Node�뿪��stage��״̬ʱ������һ��ת����transition��, ��ô�¼����������ת����ʼ��ʱ�򱻵��á�
     * @lua NA
     */
    virtual void onExitTransitionDidStart();

    /// @} end of event callbacks.


    /**
     * @~english Stops and removes all running actions and schedulers
     * @~chinese ֹͣ���Ƴ����еĻ�ŵĶ����͵�������
     */
    virtual void cleanup();

    /**
     * @~english Override this method to draw your own node.
     * The following GL states will be enabled by default:
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     * @~chinese ��д����������������Լ��Ľڵ㡣
     * ���µ�GL״̬��Ĭ�Ͽ����ģ�
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * �����ڻ�������Ľڵ�֮���ܹ��ر����ǡ�
     * ��������㿪����������GL״̬����ô�ڻ�������Ľڵ�֮����Ҫ�ر����ǡ�
     * 
     * @param renderer A given renderer.
     * @param transform A transform matrix.
     * @param flags Renderer flag.
     */
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    virtual void draw() final;

    /**
     * @~english Visits this node's children and send their render command recursively.
     * @~chinese ���������ӽڵ㣬����ѭ���ݹ�÷������ǵ���Ⱦָ�
     *
     * @param renderer @~english A given renderer. @~chinese ָ��һ����Ⱦ�� 
     * @param parentTransform @~english A transform matrix. @~chinese ���ڵ����任���� 
     * @param parentFlags @~english Renderer flag. @~chinese ��Ⱦ����ǩ 
     */
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
    virtual void visit() final;


    /** 
     @~english Returns the Scene that contains the Node.
     It returns `nullptr` if the node doesn't belong to any Scene.
     This function recursively calls parent->getScene() until parent is a Scene object. The results are not cached. It is that the user caches the results in case this functions is being used inside a loop.@~chinese ���ذ����ýڵ�ĳ�����
     �������ڵ㲻�����κεĳ�������������`nullptr`��
     �������ѭ���ݹ�ص���parent->getScene() ֱ��������һ��Scene���󡣽�����ᱻ���档ֻ�е��������������һ��ѭ����ʱ���û��ŻỺ����������
     *
     * @return @~english The Scene that contains the node. @~chinese �����ýڵ�ĳ��� 
     */
    virtual Scene* getScene() const;

    /**
     * @~english Returns an AABB (axis-aligned bounding-box) in its parent's coordinate system.
     * @~chinese ���ظ�����ϵ�е�һ��AABB(�����Χ���)��
     *
     * @return @~english An AABB (axis-aligned bounding-box) in its parent's coordinate system @~chinese �����Χ��� 
     */
    virtual Rect getBoundingBox() const;

    /** @deprecated Use getBoundingBox instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual Rect boundingBox() const { return getBoundingBox(); }

    /** @~english Set event dispatcher for node.
     * @~chinese ���ýڵ���¼��ַ���
     *
     * @param dispatcher @~english The event dispatcher. @~chinese �¼��ַ��� 
     */
    virtual void setEventDispatcher(EventDispatcher* dispatcher);
    /** @~english Get the event dispatcher.
     * @~chinese ��ȡ�ڵ���¼��ַ���
     *
     * @return @~english The event dispatcher. @~chinese �¼��ַ��� 
     */
    virtual EventDispatcher* getEventDispatcher() const { return _eventDispatcher; };

    /// @{
    /// @name Actions
    /// @brief @~english @~chinese ����

    /**
     * @~english Sets the ActionManager object that is used by all actions.
     * @~chinese ���ñ����ж���ʹ�õ�ActionManager����
     *
     * @warning @~english If you set a new ActionManager, then previously created actions will be removed.
     * @~chinese �����������һ���µ�ActionManager, ��ô֮ǰ�����Ķ������ᱻɾ����
     *
     * @param actionManager     @~english A ActionManager object that is used by all actions. @~chinese ActionManager�����ж���ʹ�á� 
     */
    virtual void setActionManager(ActionManager* actionManager);
    /**
     * @~english Gets the ActionManager object that is used by all actions.
     * @~chinese �õ������ж���ʹ�õ�ActionManager����
     * @see setActionManager(ActionManager*)
     * @return @~english An ActionManager object. @~chinese ActionManager���� 
     */
    virtual ActionManager* getActionManager() { return _actionManager; }
    virtual const ActionManager* getActionManager() const { return _actionManager; }

    /**
     * @~english Executes an action, and returns the action that is executed.
     *
     * This node becomes the action's target. Refer to Action::getTarget().
     * @~chinese ִ��һ�����������ҷ���ִ�еĸö�����
     *
     * ����ڵ㽫���ɶ�����Ŀ�꣬�ο�Action::getTarget()
     * @warning @~english Actions don't retain their target. @~chinese �������洢����Ŀ�ꡣ 
     *
     * @param action @~english An Action pointer. @~chinese �������� 
     */
    virtual Action* runAction(Action* action);

    /**
     * @~english Stops and removes all actions from the running action list .
     * @~chinese ֹͣ���Ҵӻ�����б���ɾ�����еĶ�����
     */
    void stopAllActions();

    /**
     * @~english Stops and removes an action from the running action list.
     * @~chinese ֹͣ���Ҵӻ�����б���ɾ��һ��������
     *
     * @param action    @~english The action object to be removed. @~chinese ��Ҫ��ɾ���Ķ��� 
     */
    void stopAction(Action* action);

    /**
     * @~english Removes an action from the running action list by its tag.
     * @~chinese ͨ�������ı�Ǵӻ�����б���ɾ��һ��������
     *
     * @param tag   @~english A tag that indicates the action to be removed. @~chinese �����ı�� 
     */
    void stopActionByTag(int tag);
    
    /**
     * @~english Removes all actions from the running action list by its tag.
     * @~chinese ͨ�������ı�Ǵӻ�����б���ɾ��������
     *
     * @param tag   @~english A tag that indicates the action to be removed. @~chinese �����ı�� 
     */
    void stopAllActionsByTag(int tag);

    /**
     * Removes all actions from the running action list by its flags.
     *
     * @param flags   A flag field that removes actions based on bitwise AND.
     */
    void stopActionsByFlags(unsigned int flags);

    /**
     * @~english Gets an action from the running action list by its tag.
     * @~chinese ͨ�������ı�Ǵӻ�����б��еõ�һ��������
     *
     * @see `setTag(int)`, `getTag()`.
     *
     * @return @~english The action object with the given tag. @~chinese �����ı�� 
     */
    Action* getActionByTag(int tag);

    /**
     * @~english Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).
     *
     * Composable actions are counted as 1 action. Example:
     *    If you are running 1 Sequence of 7 actions, it will return 1.
     *    If you are running 7 Sequences of 2 actions, it will return 7.
     * @~chinese ���ػ�ŵĶ����������ڵ������еĶ��������� (��actionsToAdd״̬�Ķ����Ͷ��������е�).
     *
     * ��ɵĶ�������Ϊһ�����������磺
     *    �������������7����е�1Sequence, �������� 1.
     *    �������������2�������е�7��Sequencesm,�������� 7.
     * @todo Rename to getNumberOfRunningActions()
     *
     * @return @~english The number of actions that are running plus the ones that are schedule to run.
     * @~chinese ���ػ�ŵĶ����������ڵ������еĶ���������
     */
    ssize_t getNumberOfRunningActions() const;

    /** @deprecated Use getNumberOfRunningActions() instead */
    CC_DEPRECATED_ATTRIBUTE ssize_t numberOfRunningActions() const { return getNumberOfRunningActions(); };

    /// @} end of Actions


    /// @{
    /// @name Scheduler and Timer
    /// @brief @~english @~chinese �������ͼ�ʱ��

    /**
     * @~english Sets a Scheduler object that is used to schedule all "updates" and timers.
     * @~chinese ����һ�����������������ڵ������еġ�update���Ͷ�ʱ����
     *
     * @warning @~english If you set a new Scheduler, then previously created timers/update are going to be removed.
     * @~chinese �����������һ���µĵ���������ô֮ǰ������timers/update���ᱻɾ���� 
     * @param scheduler     @~english A Shdeduler object that is used to schedule all "update" and timers. @~chinese һ�������ڵ������еġ�update���Ͷ�ʱ���ĵ��������� 
     */
    virtual void setScheduler(Scheduler* scheduler);
    /**
     * @~english Gets a Sheduler object. @~chinese �õ����������� 
     *
     * @see setScheduler(Scheduler*)
     * @return @~english A Scheduler object. @~chinese ���������� 
     */
    virtual Scheduler* getScheduler() { return _scheduler; }
    virtual const Scheduler* getScheduler() const { return _scheduler; }


    /**
     * @~english Checks whether a selector is scheduled. @~chinese ���һ��ѡ�����Ƿ��ڵ����С� 
     *
     * @param selector      @~english A function selector @~chinese ����ѡ���� 
     * @return @~english Whether the funcion selector is scheduled. @~chinese ����ѡ�����Ƿ��ڵ����� 
     * @js NA
     * @lua NA
     */
    bool isScheduled(SEL_SCHEDULE selector);

    /**
     * @~english Checks whether a lambda function is scheduled. @~chinese ���һ��lambda�����Ƿ��ڵ����С� 
     *
     * @param key      @~english key of the callback @~chinese lambda�ص�������key 
     * @return @~english Whether the lambda function selector is scheduled. @~chinese ����lambda�����Ƿ��ڵ����� 
     * @js NA
     * @lua NA
     */
    bool isScheduled(const std::string &key);

    /**
     * @~english Schedules the "update" method.
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     * @~chinese ����"update"������
     *
     * �������ȼ�������0���������������ÿһ֡�������á�
     * ӵ�н�С������ֵ�ĵ��ȷ�����������ӵ�ýϴ�������ֵ�ķ���֮ǰ�����á�
     * ÿһ���ڵ�ֻ��һ"update"�ܹ�������(�㲻�ܹ���2����update��ѡ����)��
     * @lua NA
     */
    void scheduleUpdate(void);

    /**
     * @~english Schedules the "update" method with a custom priority.
     *
     * This selector will be called every frame.
     * Scheduled methods with a lower priority will be called before the ones that have a higher value.
     * Only one "update" selector could be scheduled per node (You can't have 2 'update' selectors).
     * @~chinese ʹ��һ���Զ������ȼ�����"update"������
     *
     * ���ѡ����������ÿһ֡�����á�
     * ӵ�н�С������ֵ�ĵ��ȷ�����������ӵ�ýϴ�������ֵ�ķ���֮ǰ�����á�
     * ÿһ���ڵ�ֻ��һ"update"�ܹ�������(�㲻�ܹ���2����update��ѡ����)��
     * @lua NA
     *
     * @param priority @~english A given priority value. @~chinese ���ȼ���ֵ����ֵԽС���ȼ�Խ�ߣ� 
     */
    void scheduleUpdateWithPriority(int priority);

    /*
     * @~english Unschedules the "update" method. @~chinese ȡ������"update"������ 
     * @see scheduleUpdate();
     */
    void unscheduleUpdate(void);

    /**
     * @~english Schedules a custom selector.
     *
     * If the selector is already scheduled, then the interval parameter will be updated without scheduling it again.
     * @~chinese ����һ���Զ����ѡ������
     *
     * ������ѡ�����Ѿ��������ˣ���ô�ڲ��Ĳ������ᱻ���¶������ٴε��ȡ�
     @code
     // firstly, implement a schedule function
     void MyNode::TickMe(float dt);
     // wrap this function into a selector via schedule_selector macro.
     this->schedule(CC_SCHEDULE_SELECTOR(MyNode::TickMe), 0, 0, 0);
     @endcode
     *
     * @param selector  @~english The SEL_SCHEDULE selector to be scheduled. @~chinese �������ȵ� SEL_SCHEDULE ѡ������ 
     * @param interval  @~english Tick interval in seconds. 0 means tick every frame. If interval = 0, it's recommended to use scheduleUpdate() instead.
     * @~chinese ����Ϊʱ������0����ʱ����Ϊÿ֡�����interval = 0���Ǿ��Ƽ�ʹ��scheduleUpdate()�����档
     * @param repeat    @~english The selector will be excuted (repeat + 1) times, you can use CC_REPEAT_FOREVER for tick infinitely.
     * @~chinese ���ѡ�������ᱻִ�еĴ�����repeat+1��,�����ʹ��kRepeatForever�������ظ���
     * @param delay     @~english The amount of time that the first tick will wait before execution.
     * @~chinese ��һ�ε��ȿ�ʼִ��ǰ�ĵȴ���ʱ�䡣
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);

    /**
     * @~english Schedules a custom selector with an interval time in seconds.
     * @~chinese ָ��һ������Ϊ��λ��ʱ����������һ���Զ����ѡ������
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      @~english The SEL_SCHEDULE selector to be scheduled. @~chinese ���ᱻ���ȵ�SEL_SCHEDULEѡ������ 
     * @param interval      @~english Callback interval time in seconds. 0 means tick every frame,
     * @~chinese ����Ϊ��λ��ʱ������0������ÿ֡��ִ�С�
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval);

    /**
     * @~english Schedules a selector that runs only once, with a delay of 0 or larger
     * @~chinese ����һ��ֻ����һ�ε�ѡ������������һ��0���߸������ʱ��
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      @~english The SEL_SCHEDULE selector to be scheduled. @~chinese ���ᱻ���ȵ�SEL_SCHEDULEѡ������ 
     * @param delay         @~english The amount of time that the first tick will wait before execution.
     * @~chinese ��һ�ε��ȿ�ʼִ��ǰ�ĵȴ�ʱ�䡣
     * @lua NA
     */
    void scheduleOnce(SEL_SCHEDULE selector, float delay);

    /**
     * @~english Schedules a lambda function that runs only once, with a delay of 0 or larger
     * @~chinese ����һ��ֻ����һ�ε�lambda�ص�������������һ��0���߸������ʱ��һ��key���������ص���
     *
     * @param callback      @~english The lambda function to be scheduled. @~chinese lambda�ص����� 
     * @param delay         @~english The amount of time that the first tick will wait before execution. @~chinese ��һ�ε��ȿ�ʼִ��ǰ�ĵȴ�ʱ�䡣 
     * @param key           @~english The key of the lambda function. To be used if you want to unschedule it. @~chinese �������lambda������key����������ȡ������ 
     * @lua NA
     */
    void scheduleOnce(const std::function<void(float)>& callback, float delay, const std::string &key);

    /**
     * @~english Schedules a custom selector, the scheduled selector will be ticked every frame.
     * @~chinese ����һ���Զ����ѡ���������ѡ��������ÿ֡�����á�
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      @~english A function wrapped as a selector @~chinese ���ᱻ���ȵ�SEL_SCHEDULEѡ���� 
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector);

    /**
     * @~english Schedules a lambda function. The scheduled lambda function will be called every frame.
     * @~chinese ����һ���Զ����lambda�ص�����������ص���������ÿ֡�����á�
     *
     * @param callback      @~english The lambda function to be scheduled. @~chinese lambda�ص����� 
     * @param key           @~english The key of the lambda function. To be used if you want to unschedule it. @~chinese �������lambda������key����������ȡ������ 
     * @lua NA
     */
    void schedule(const std::function<void(float)>& callback, const std::string &key);

    /**
     * @~english Schedules a lambda function. The scheduled lambda function will be called every "interval" seconds
     * @~chinese ����һ��lambda�ص���������ָ�����ȵ�ʱ����������Ϊ��λ����
     *
     * @param callback      @~english The lambda function to be scheduled @~chinese lambda�ص����� 
     * @param interval      @~english Callback interval time in seconds. 0 means every frame @~chinese ����Ϊ��λ��ʱ������0������ÿ֡��ִ�С� 
     * @param key           @~english The key of the lambda function. To be used if you want to unschedule it @~chinese �������lambda������key����������ȡ������ 
     * @lua NA
     */
    void schedule(const std::function<void(float)>& callback, float interval, const std::string &key);

    /**
     * @~english Schedules a lambda function. @~chinese ����һ��lambda�ص����� 
     *
     * @param callback  @~english The lambda function to be schedule. @~chinese lambda�ص����� 
     * @param interval  @~english Tick interval in seconds. 0 means tick every frame. @~chinese ����Ϊ��λ��ʱ������0������ÿ֡��ִ�С� 
     * @param repeat    @~english The selector will be executed (repeat + 1) times, you can use CC_REPEAT_FOREVER for tick infinitely.
     * @~chinese ���ѡ�������ᱻִ�еĴ�����repeat+1��,�����ʹ��kRepeatForever�������ظ���
     * @param delay     @~english The amount of time that the first tick will wait before execution.
     * @~chinese ��һ�ε��ȿ�ʼִ��ǰ�ĵȴ�ʱ�䡣
     * @param key       @~english The key of the lambda function. To be used if you want to unschedule it. @~chinese �������lambda������key����������ȡ������ 
     * @lua NA
     */
    void schedule(const std::function<void(float)>& callback, float interval, unsigned int repeat, float delay, const std::string &key);

    /**
     * @~english Unschedules a custom selector. @~chinese ȡ������һ���Զ����ѡ������ 
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      @~english A function wrapped as a selector. @~chinese SEL_SCHEDULEѡ���� 
     * @lua NA
     */
    void unschedule(SEL_SCHEDULE selector);

    /**
     * @~english Unschedules a lambda function. @~chinese ȡ������һ��lambda�ص����� 
     *
     * @param key      @~english The key of the lambda function to be unscheduled. @~chinese lambda�ص�������Ӧ��key 
     * @lua NA
     */
    void unschedule(const std::string &key);

    /**
     * @~english Unschedule all scheduled selectors and lambda functions: custom selectors, and the 'update' selector and lambda functions.
     * @~chinese ȡ����������ѡ�����ͻص��������Լ�update���ȡ�����Ӱ�춯����
     * Actions are not affected by this method.
     * @lua NA
     */
    void unscheduleAllCallbacks();

    CC_DEPRECATED_ATTRIBUTE void unscheduleAllSelectors() { unscheduleAllCallbacks(); }

    /**
     * @~english Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter.
     * @~chinese �ָ����еĵ��ȹ���ѡ�������������¼���������
     * ���������onEnter�������ڲ����á�
     */
    virtual void resume(void);
    /**
     * @~english Pauses all scheduled selectors, actions and event listeners.
     * This method is called internally by onExit.
     * @~chinese ��ͣ���еĵ��ȹ���ѡ�������������¼���������
     * ���������onExit�������ڲ����á�
     */
    virtual void pause(void);

    /**
     * @~english Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter.
     * @~chinese �ָ����еĵ��ȹ���ѡ�������������¼���������
     * ���������onEnter�������ڲ����á�
     */
    CC_DEPRECATED_ATTRIBUTE void resumeSchedulerAndActions();
    /**
     * @~english Pauses all scheduled selectors, actions and event listeners.
     * This method is called internally by onExit.
     * @~chinese ��ͣ���еĵ��ȹ���ѡ�������������¼���������
     * ���������onExit�������ڲ����á�
     */
    CC_DEPRECATED_ATTRIBUTE void pauseSchedulerAndActions();

    /**
     * @~english Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".
     * @~chinese ���"scheduleUpdate"�����ò�������ڵ��ǻ�Ծ�Ļ���update�������ᱻÿ֡�Զ����á�
     * @param delta In seconds.
     */
    virtual void update(float delta);

    /// @} end of Scheduler and Timer

    /// @{
    /// @name Transformations
    /// @brief @~english @~chinese ����任����

    /**
     * @~english Calls children's updateTransform() method recursively.
     *
     * This method is moved from Sprite, so it's no longer specific to Sprite.
     * As the result, you apply SpriteBatchNode's optimization on your customed Node.
     * e.g., `batchNode->addChild(myCustomNode)`, while you can only addChild(sprite) before.
     * @~chinese �ݹ�ĵ��ú��ӵ�updateTransform()������
     *
     * ��������Ǵ�Sprite����Ǩ�Ƶģ����������ֻ������Sprite.
     * ��ˣ���������Զ���ڵ���ΪSpriteBatchNode�����Ż���
     * e.g., `batchNode->addChild(myCustomNode)`, ��ǰ��ֻ����addChild(sprite)
     */
    virtual void updateTransform();

    /**
     * @~english Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     * @~chinese ����������ڵ㣨�ֲ����Ŀռ�����ϵת���ɸ��ڵ�Ŀռ�����ϵ�ľ���
     * �������������Ϊ��λ��
     *
     * @return The transformation matrix.
     */
    virtual const Mat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;

    /**
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     * Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see getNodeToWorldTransform
     *
     * @param ancestor The parent's node pointer.
     * @since v3.7
     * @return The transformation matrix.
     */
    virtual Mat4 getNodeToParentTransform(Node* ancestor) const;

    /**
     * Returns the affine transform matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     *
     * Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see getNodeToWorldAffineTransform
     *
     * @param ancestor The parent's node pointer.
     * @since v3.7
     * @return The affine transformation matrix.
     */
    virtual AffineTransform getNodeToParentAffineTransform(Node* ancestor) const;

    /** 
     * @~english Sets the transformation matrix manually.
     * @~chinese �ֶ����ñ任����
     *
     * @param transform @~english A given transformation matrix. @~chinese ����仯���� 
     */
    virtual void setNodeToParentTransform(const Mat4& transform);

    /** @deprecated use getNodeToParentTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToParentTransform() const { return getNodeToParentAffineTransform(); }

    /**
     * @~english Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     * @~chinese ���ؽ����ڵ�Ŀռ�����ϵת���ɽڵ㣨�ֲ����Ŀռ�����ϵת�ľ���
     * �������������Ϊ��λ��
     *
     * @return @~english The transformation matrix. @~chinese ����仯���� 
     */
    virtual const Mat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;

    /** @deprecated Use getParentToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform parentToNodeTransform() const { return getParentToNodeAffineTransform(); }

    /**
     * @~english Returns the world affine transform matrix. The matrix is in Pixels.
     * @~chinese ���ؽڵ㵽�����������任���󡣾���λ�����ء�
     *
     * @return @~english transformation matrix, in pixels. @~chinese �ڵ㵽�����������任���� 
     */
    virtual Mat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;

    /** @deprecated Use getNodeToWorldTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToWorldTransform() const { return getNodeToWorldAffineTransform(); }

    /**
     * @~english Returns the inverse world affine transform matrix. The matrix is in Pixels.
     * @~chinese ������ڵ㵽�������任���󡣾���λ�����ء�
     *
     * @return @~english The transformation matrix. @~chinese ����任���� 
     */
    virtual Mat4 getWorldToNodeTransform() const;
    virtual AffineTransform getWorldToNodeAffineTransform() const;

    /** @deprecated Use getWorldToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform worldToNodeTransform() const { return getWorldToNodeAffineTransform(); }

    /// @} end of Transformations


    /// @{
    /// @name Coordinate Converters
    /// @brief @~english @~chinese ����ת��

    /**
     * @~english Converts a Vec2 to node (local) space coordinates. The result is in Points.
     * @~chinese ��Vec2 ת���ɽڵ� (�ֲ�) �ռ�����ϵ�������PointsΪ��λ��
     *
     * @param worldPoint @~english A given coordinate. @~chinese һ���������� 
     * @return @~english A point in node (local) space coordinates. @~chinese ���������ڽڵ�����ϵ�е����� 
     */
    Vec2 convertToNodeSpace(const Vec2& worldPoint) const;

    /**
     * @~english Converts a Vec2 to world space coordinates. The result is in Points.
     * @~chinese ��Vec2ת��������ռ�����ϵ�������PointsΪ��λ��
     *
     * @param nodePoint @~english A given coordinate. @~chinese һ���������� 
     * @return @~english A point in world space coordinates. @~chinese ������������������ϵ�е����� 
     */
    Vec2 convertToWorldSpace(const Vec2& nodePoint) const;

    /**
     * @~english Converts a Vec2 to node (local) space coordinates. The result is in Points.
     * treating the returned/received node point as anchor relative.
     * @~chinese ��Vec2ת���ɽڵ�(�ֲ�)�ռ�����ϵ. �����PointsΪ��λ��
     * ���갴���������ê��������
     *
     * @param worldPoint @~english A given coordinate. @~chinese һ���������� 
     * @return @~english A point in node (local) space coordinates, anchor relative. @~chinese ���������ڽڵ�����ϵ�е����꣬��ê����� 
     */
    Vec2 convertToNodeSpaceAR(const Vec2& worldPoint) const;

    /**
     * @~english Converts a local Vec2 to world space coordinates.The result is in Points.
     * treating the returned/received node point as anchor relative.
     * @~chinese ��Vec2ת��������ռ�����ϵ�������PointsΪ��λ��
     * ���갴�����ê��������
     *
     * @param nodePoint @~english A given coordinate. @~chinese һ���������� 
     * @return @~english A point in world space coordinates, anchor relative. @~chinese ������������������ϵ�е����꣬��ê����� 
     */
    Vec2 convertToWorldSpaceAR(const Vec2& nodePoint) const;

    /**
     * @~english Convenience methods which take a Touch instead of Vec2.
     * @~chinese ��������ת���ɱ�������ϵ��λ��
     *
     * @param touch @~english A given touch. @~chinese ��������� 
     * @return @~english A point in node space coordinates. @~chinese ��������ϵ��λ�� 
     */
    Vec2 convertTouchToNodeSpace(Touch * touch) const;

    /**
     * @~english Converts a Touch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
     * @~chinese ������ (��������ϵ) ת���ɱ�������ϵ�����갴�����ê��������
     *
     * @param touch @~english A given touch. @~chinese ��������� 
     * @return @~english A point in world space coordinates, anchor relative. @~chinese ��������ϵ��λ�ã���ê����� 
     */
    Vec2 convertTouchToNodeSpaceAR(Touch * touch) const;

	/**
     * @~english Sets an additional transform matrix to the node.
     *
     * In order to remove it, call it again with the argument `nullptr`.
     * @~chinese Ϊ�ڵ�����һ������ת������
     *
     * ͨ���������"nullptr"ɾ����.
     *
     * @note @~english The additional transform will be concatenated at the end of getNodeToParentTransform.
     *        It could be used to simulate `parent-child` relationship between two nodes (e.g. one is in BatchNode, another isn't).
     * @~chinese �������ת������������getNodeToParentTransform֮��
     *        �����Ա������������ڵ�֮��ģ��`parent-child`�Ĺ�ϵ(e.g. ����һ����BatchNode��, ��һ��ȴ����).
     *
     * @param additionalTransform An additional transform matrix.
     */
    void setAdditionalTransform(Mat4* additionalTransform);
    void setAdditionalTransform(const AffineTransform& additionalTransform);

    /// @} end of Coordinate Converters

    /// @{
    /// @name component functions
    /// @brief @~english @~chinese ���ϵͳ
    /**
     * @~english Gets a component by its name. @~chinese ͨ�����ֵõ���� 
     *
     * @param name @~english A given name of component. @~chinese ��������� 
     * @return @~english The Component by name. @~chinese ���ֶ�Ӧ����� 
     */
    Component* getComponent(const std::string& name);

    /**
     * @~english Adds a component. @~chinese ���һ����� 
     *
     * @param component @~english A given component. @~chinese һ����� 
     * @return @~english True if added success. @~chinese �����ӳɹ�����true�����򷵻�false 
     */
    virtual bool addComponent(Component *component);

    /**
     * @~english Removes a component by its name. @~chinese ͨ������ɾ��һ����� 
     *
     * @param name @~english A given name of component. @~chinese ��������� 
     * @return @~english True if removed success. @~chinese ���ɾ���ɹ�����true�����򷵻�false 
     */
    virtual bool removeComponent(const std::string& name);

    /** 
     * @~english Removes a component by its pointer. @~chinese ͨ��ָ��ɾ��һ����� 
     *
     * @param component @~english A given component. @~chinese ���ָ�� 
     * @return @~english True if removed success. @~chinese ���ɾ���ɹ�����true�����򷵻�false 
     */
    virtual bool removeComponent(Component *component);
    /**
     * @~english Removes all components @~chinese ɾ��������� 
     */
    virtual void removeAllComponents();
    /// @} end of component functions


#if CC_USE_PHYSICS
    /**
     * @~english Set the PhysicsBody that let the sprite effect with physics. @~chinese ����PhysicsBody���þ���sprite������������ܡ� 
     * @note @~english This method will set anchor point to Vec2::ANCHOR_MIDDLE if body not null, and you cann't change anchor point if node has a physics body.
     * @~chinese ���body�ǿգ����������������ê��ΪVec2::ANCHOR_MIDDLE, ���ҵ�������body���ڵ�������㲻���Ըı����ê�㡣
     *
     * @param body @~english A given physics body. @~chinese ���Ӹ��ڵ������body 
     */
    void setPhysicsBody(PhysicsBody* body);

    /**
     * @~english Get the PhysicsBody the sprite have. @~chinese �õ�����ӵ�е�����body 
     *
     * @return @~english The PhysicsBody the sprite have. @~chinese ���������body 
     */
    PhysicsBody* getPhysicsBody() const { return _physicsBody; }
    
    /**
     * @~english Remove this node from physics world. it will remove all the physics bodies in it's children too.
     * @~chinese ������������ɾ������ڵ������body�����һ�ɾ�����ӽڵ��е���������body
     */
    void removeFromPhysicsWorld();
    
    /** 
     * @~english Update the transform matrix from physics. @~chinese ������������ͬ���任���� 
     */
    void updateTransformFromPhysics(const Mat4& parentTransform, uint32_t parentFlags);

    /** 
     * @~english Update physics body transform matrix. @~chinese ���ڵ�ı仯����ͬ��������body�� 
     */
    virtual void updatePhysicsBodyTransform(const Mat4& parentTransform, uint32_t parentFlags, float parentScaleX, float parentScaleY);
#endif
    
    // overrides
    virtual GLubyte getOpacity() const;
    virtual GLubyte getDisplayedOpacity() const;
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled() const;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    
    virtual const Color3B& getColor() const;
    virtual const Color3B& getDisplayedColor() const;
    virtual void setColor(const Color3B& color);
    virtual void updateDisplayedColor(const Color3B& parentColor);
    virtual bool isCascadeColorEnabled() const;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    
    virtual void setOpacityModifyRGB(bool value) {CC_UNUSED_PARAM(value);}
    virtual bool isOpacityModifyRGB() const { return false; };

    void setOnEnterCallback(const std::function<void()>& callback) { _onEnterCallback = callback; }
    const std::function<void()>& getOnEnterCallback() const { return _onEnterCallback; }   
    void setOnExitCallback(const std::function<void()>& callback) { _onExitCallback = callback; }
    const std::function<void()>& getOnExitCallback() const { return _onExitCallback; }   
    void setonEnterTransitionDidFinishCallback(const std::function<void()>& callback) { _onEnterTransitionDidFinishCallback = callback; }
    const std::function<void()>& getonEnterTransitionDidFinishCallback() const { return _onEnterTransitionDidFinishCallback; }   
    void setonExitTransitionDidStartCallback(const std::function<void()>& callback) { _onExitTransitionDidStartCallback = callback; }
    const std::function<void()>& getonExitTransitionDidStartCallback() const { return _onExitTransitionDidStartCallback; }
    
    /** get & set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true */
    unsigned short getCameraMask() const { return _cameraMask; }
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true);

CC_CONSTRUCTOR_ACCESS:
    // Nodes should be created using create();
    Node();
    virtual ~Node();

    virtual bool init();

protected:
    /// lazy allocs
    void childrenAlloc(void);
    
    /// helper that reorder a child
    void insertChild(Node* child, int z);

    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    void detachChild(Node *child, ssize_t index, bool doCleanup);

    /// Convert cocos2d coordinates to UI windows coordinate.
    Vec2 convertToWindowSpace(const Vec2& nodePoint) const;

    Mat4 transform(const Mat4 &parentTransform);
    uint32_t processParentFlags(const Mat4& parentTransform, uint32_t parentFlags);

    virtual void updateCascadeOpacity();
    virtual void disableCascadeOpacity();
    virtual void updateCascadeColor();
    virtual void disableCascadeColor();
    virtual void updateColor() {}
    
    bool doEnumerate(std::string name, std::function<bool (Node *)> callback) const;
    bool doEnumerateRecursive(const Node* node, const std::string &name, std::function<bool (Node *)> callback) const;
    
    //check whether this camera mask is visible by the current visiting camera
    bool isVisitableByVisitingCamera() const;
    
    // update quaternion from Rotation3D
    void updateRotationQuat();
    // update Rotation3D from quaternion
    void updateRotation3D();
    
private:
    void addChildHelper(Node* child, int localZOrder, int tag, const std::string &name, bool setTag);
    
protected:

    float _rotationX;               ///< rotation on the X-axis
    float _rotationY;               ///< rotation on the Y-axis

    // rotation Z is decomposed in 2 to simulate Skew for Flash animations
    float _rotationZ_X;             ///< rotation angle on Z-axis, component X
    float _rotationZ_Y;             ///< rotation angle on Z-axis, component Y
    
    Quaternion _rotationQuat;      ///rotation using quaternion, if _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX, else _rotationQuat = RotationY * RotationX

    float _scaleX;                  ///< scaling factor on x-axis
    float _scaleY;                  ///< scaling factor on y-axis
    float _scaleZ;                  ///< scaling factor on z-axis

    Vec2 _position;                ///< position of the node
    float _positionZ;               ///< OpenGL real Z position
    Vec2 _normalizedPosition;
    bool _usingNormalizedPosition;
    bool _normalizedPositionDirty;

    float _skewX;                   ///< skew angle on x-axis
    float _skewY;                   ///< skew angle on y-axis

    Vec2 _anchorPointInPoints;     ///< anchor point in points
    Vec2 _anchorPoint;             ///< anchor point normalized (NOT in points)

    Size _contentSize;              ///< untransformed size of the node
    bool _contentSizeDirty;         ///< whether or not the contentSize is dirty

    Mat4 _modelViewTransform;    ///< ModelView transform of the Node.

    // "cache" variables are allowed to be mutable
    mutable Mat4 _transform;      ///< transform
    mutable bool _transformDirty;   ///< transform dirty flag
    mutable Mat4 _inverse;        ///< inverse transform
    mutable bool _inverseDirty;     ///< inverse transform dirty flag
    mutable Mat4 _additionalTransform; ///< transform
    bool _useAdditionalTransform;   ///< The flag to check whether the additional transform is dirty
    bool _transformUpdated;         ///< Whether or not the Transform object was updated since the last frame

    int _localZOrder;               ///< Local order (relative to its siblings) used to sort the node
    float _globalZOrder;            ///< Global order used to sort the node

    Vector<Node*> _children;        ///< array of children nodes
    Node *_parent;                  ///< weak reference to parent node
    Director* _director;            //cached director pointer to improve rendering performance
    int _tag;                         ///< a tag. Can be any number you assigned just to identify this node
    
    std::string _name;               ///<a string label, an user defined string to identify this node
    size_t _hashOfName;            ///<hash value of _name, used for speed in getChildByName

    void *_userData;                ///< A user assingned void pointer, Can be point to any cpp object
    Ref *_userObject;               ///< A user assigned Object

    GLProgramState *_glProgramState; ///< OpenGL Program State

    int _orderOfArrival;            ///< used to preserve sequence while sorting children with the same localZOrder

    Scheduler *_scheduler;          ///< scheduler used to schedule timers and updates

    ActionManager *_actionManager;  ///< a pointer to ActionManager singleton, which is used to handle all the actions

    EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events

    bool _running;                  ///< is running

    bool _visible;                  ///< is this node visible

    bool _ignoreAnchorPointForPosition; ///< true if the Anchor Vec2 will be (0,0) when you position the Node, false otherwise.
                                          ///< Used by Layer and Scene.

    bool _reorderChildDirty;          ///< children order dirty flag
    bool _isTransitionFinished;       ///< flag to indicate whether the transition was finished

#if CC_ENABLE_SCRIPT_BINDING
    int _scriptHandler;               ///< script handler for onEnter() & onExit(), used in Javascript binding and Lua binding.
    int _updateScriptHandler;         ///< script handler for update() callback per frame, which is invoked from lua & javascript.
    ccScriptType _scriptType;         ///< type of script binding, lua or javascript
#endif
    
    ComponentContainer *_componentContainer;        ///< Dictionary of components
    
    // opacity controls
    GLubyte		_displayedOpacity;
    GLubyte     _realOpacity;
    Color3B	    _displayedColor;
    Color3B     _realColor;
    bool		_cascadeColorEnabled;
    bool        _cascadeOpacityEnabled;

    static int s_globalOrderOfArrival;
    
    // camera mask, it is visible only when _cameraMask & current camera' camera flag is true
    unsigned short _cameraMask;
    
    std::function<void()> _onEnterCallback;
    std::function<void()> _onExitCallback;
    std::function<void()> _onEnterTransitionDidFinishCallback;
    std::function<void()> _onExitTransitionDidStartCallback;

//Physics:remaining backwardly compatible  
#if CC_USE_PHYSICS
    PhysicsBody* _physicsBody;
public:
    void setPhysicsBody(Component* physicsBody) 
    { 
        addComponent(physicsBody);
    }
    PhysicsBody* getPhysicsBody() const { return _physicsBody; }

    friend class PhysicsBody;
#endif

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Node);
};


/**
 * This is a helper function, checks a GL screen point is in content rectangle space.
 *
 * The content rectangle defined by origin(0,0) and content size.
 * This function convert GL screen point to near and far planes as points Pn and Pf,
 * then calculate the intersect point P which the line PnPf intersect with content rectangle.
 * If P in content rectangle means this node be hit.
 *
 * @param pt        The point in GL screen space.
 * @param camera    Which camera used to unproject pt to near/far planes.
 * @param w2l       World to local transform matrix, used to convert Pn and Pf to rectangle space.
 * @param rect      The test rectangle in local space.
 * @parma p         Point to a Vec3 for store the intersect point, if don't need them set to nullptr.
 * @return true if the point is in content rectangle, false otherwise.
 */
bool CC_DLL isScreenPointInRect(const Vec2 &pt, const Camera* camera, const Mat4& w2l, const Rect& rect, Vec3 *p);

// NodeRGBA

/** @class __NodeRGBA
 * @brief __NodeRGBA is a subclass of Node that implements the RGBAProtocol protocol.
 
 All features from Node are valid, plus the following new features:
 - opacity
 - RGB colors
 
 Opacity/Color propagates into children that conform to the RGBAProtocol if cascadeOpacity/cascadeColor is enabled.
 @since v2.1
 @js NA
 */
class CC_DLL __NodeRGBA : public Node, public __RGBAProtocol
{
public:
    // overrides
    virtual GLubyte getOpacity() const override { return Node::getOpacity(); }
    virtual GLubyte getDisplayedOpacity() const  override { return Node::getDisplayedOpacity(); }
    virtual void setOpacity(GLubyte opacity) override { return Node::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override { return Node::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const  override { return Node::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override { return Node::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor(void) const override { return Node::getColor(); }
    virtual const Color3B& getDisplayedColor() const override { return Node::getDisplayedColor(); }
    virtual void setColor(const Color3B& color) override { return Node::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor) override { return Node::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const override { return Node::isCascadeColorEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override { return Node::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue) override { return Node::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const override { return Node::isOpacityModifyRGB(); }

CC_CONSTRUCTOR_ACCESS:
    __NodeRGBA();
    virtual ~__NodeRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__NodeRGBA);
};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCNODE_H__
