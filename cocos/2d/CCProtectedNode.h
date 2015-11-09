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

#ifndef __CPROTECTEDCNODE_H__
#define __CPROTECTEDCNODE_H__


#include "2d/CCNode.h"

NS_CC_BEGIN
	
/**
 * @addtogroup _2d
 * @{
 */

/**
 *@brief @~english A inner node type mainly used for UI module.
 * It is useful for composing complex node type and it's children are protected.
 * @~chinese ��Ҫ����UIģ����ڲ��ڵ����͡�
 * ������ϳ����ӵĽڵ����͡����е��ӽڵ㶼Ϊ protected��
 */
class  CC_DLL ProtectedNode : public Node
{
public:
    /**@~english
     * Creates a ProtectedNode with no argument.
     * @~chinese 
     * ��ʹ�ò�������һ��ProtectedNode��
     *@return @~english A instance of ProtectedNode.
     * @~chinese ProtectedNode��ʵ����
     */
    static ProtectedNode * create(void);
    
    /// @{
    /// @name Children and Parent
    
    /**@~english
     * Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * ���һ�� Z ֵΪ 0 ���ӽڵ㡣
     * 
     * �����ǰ�ڵ��������У���ô 'onEnter' �� 'onEnterTransitionDidFinish' �ᱻ�������á�
     * 
     * @param child @~english A child node
     * @~chinese һ���ӽڵ�
     */
    virtual void addProtectedChild(Node * child);
    /**@~english
     * Adds a child to the container with a local z-order.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * ���һ�� z ֵΪ localZOrder ���ӽڵ㡣
     * 
     * �����ǰ�ڵ��������У���ô 'onEnter' �� 'onEnterTransitionDidFinish' �ᱻ�������á�
     * 
     * @param child     @~english A child node
     * @~chinese һ���ӽڵ�
     * @param localZOrder    @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @~chinese ���ڿ��ƻ���˳��� z ֵ�������`setLocalZOrder(int)`
     */
    virtual void addProtectedChild(Node * child, int localZOrder);
    /**@~english
     * Adds a child to the container with z order and tag.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * ָ�� z ֵ�� tag ����ӽڵ�
     * 
     * �����ǰ�ڵ��������У���ô 'onEnter' �� 'onEnterTransitionDidFinish' �ᱻ�������á�
     * 
     * @param child     @~english A child node
     * @~chinese һ���ӽڵ�
     * @param localZOrder    @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @~chinese ���ڿ��ƻ���˳��� z ֵ�������`setLocalZOrder(int)`
     * @param tag       @~english An integer to identify the node easily. Please refer to `setTag(int)`
     * @~chinese һ�����ڱ�ʶ�ڵ�������������`setTag(int)`
     */
    virtual void addProtectedChild(Node* child, int localZOrder, int tag);
    /**@~english
     * Gets a child from the container with its tag.
     *
     * @~chinese 
     * ͨ�� tag ֵ��ȡһ���ӽڵ㡣
     * 
     * @param tag   @~english An identifier to find the child node.
     *
     * @~chinese һ�����ڱ�ʶ�ڵ��������
     * 
     * @return @~english a Node object whose tag equals to the input parameter.
     * @~chinese tag ֵ�����������ͬ���ӽڵ�ʵ����
     */
    virtual Node * getProtectedChildByTag(int tag);
    
    ////// REMOVES //////
    
    /**@~english
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * ɾ��һ���ӽڵ㡣����ͨ������ cleanup �Ĳ���ֵ���������������е� action��
     * 
     * @param child     @~english The child node which will be removed.
     * @~chinese ����ɾ�����ӽڵ㡣
     * @param cleanup   @~english true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese ���Ϊ true���������ӽڵ���ص� action �ͻص���
     */
    virtual void removeProtectedChild(Node* child, bool cleanup = true);
    
    /**@~english
     * Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * ͨ�� tag ֵ��ɾ���ӽڵ㡣����ͨ������ cleanup �Ĳ���ֵ���������������е� action��
     * 
     * @param tag       @~english An interger number that identifies a child node.
     * @~chinese ���ڱ�ʶ�ӽڵ�� tag ֵ��
     * @param cleanup   @~english true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese ���Ϊ true���������ӽڵ���ص� action �ͻص���
     */
    virtual void removeProtectedChildByTag(int tag, bool cleanup = true);
    
    /**@~english
     * Removes all children from the container with a cleanup.
     *
     * @~chinese 
     * �Ƴ������ӽڵ㡣
     * 
     * @see `removeAllChildrenWithCleanup(bool)`.
     */
    virtual void removeAllProtectedChildren();
    /**@~english
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * �Ƴ������ӽڵ㣬�� cleanup Ϊ true ʱ�������нڵ���صĲ�������������
     * 
     * @param cleanup   @~english true if all running actions on all children nodes should be cleanup, false oterwise.
     * @~chinese ���Ϊ true���������ӽڵ���ص� action �ͻص���
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllProtectedChildrenWithCleanup(bool cleanup);
    
    /**@~english
     * Reorders a child according to a new z value.
     *
     * @~chinese 
     * Ϊһ���ӽڵ������µ� z ֵ����������
     * 
     * @param child     @~english An already added child node. It MUST be already added.
     * @~chinese һ���Ѿ����ڵ��ӽڵ㡣
     * @param localZOrder @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @~chinese ���ڿ��ƻ���˳��� z ֵ������� `setLocalZOrder(int)`
     */
    virtual void reorderProtectedChild(Node * child, int localZOrder);
    
    /**@~english
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @~chinese 
     * �ڻ���֮ǰ�������ӽڵ����һ�����������ÿ���һ���ڵ������һ�Σ����Դ��������ܡ�
     * @note @~english Don't call this manually unless a child added needs to be removed in the same frame
     * @~chinese ��Ҫ�ֶ����ô˺���������һ���ӽڵ���Ҫ�ڵ�ǰ֡ɾ����
     */
    virtual void sortAllProtectedChildren();
    
    /// @} end of Children and Parent
    
    /**
     * @js NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    virtual void cleanup() override;
    
    virtual void onEnter() override;

    virtual void onEnterTransitionDidFinish() override;
    
    virtual void onExit() override;
    
    virtual void onExitTransitionDidStart() override;

    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void disableCascadeColor() override;
    virtual void disableCascadeOpacity()override;
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;
CC_CONSTRUCTOR_ACCESS:
    ProtectedNode();
    virtual ~ProtectedNode();
    
protected:
    
    /// helper that reorder a child
    void insertProtectedChild(Node* child, int z);
    
    Vector<Node*> _protectedChildren;        ///< array of children nodes
    bool _reorderProtectedChildDirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProtectedNode);
};

// end of 2d group
/// @}

NS_CC_END

#endif // __CPROTECTEDCNODE_H__
