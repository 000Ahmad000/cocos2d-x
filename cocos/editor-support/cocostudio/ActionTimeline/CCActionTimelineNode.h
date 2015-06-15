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

#ifndef __COCOSSTUDIO_CCACTIONTIMELINENODE_H__
#define __COCOSSTUDIO_CCACTIONTIMELINENODE_H__

#include "CCActionTimeline.h"
#include "CCTimelineMacro.h"
#include "cocostudio/CocosStudioExport.h"

NS_TIMELINE_BEGIN

class ActionTimeline;

class CC_STUDIO_DLL ActionTimelineNode : public cocos2d::Node
{
public:
    static ActionTimelineNode* create(cocos2d::Node* root, ActionTimeline* action);
    
    ActionTimelineNode();
    ~ActionTimelineNode();
    
    bool init() override;

    /** @~english Initialize with root node and actiontimeline.
    *   @~chinese ʹ�ø��ڵ��ʱ���ᶯ����ʼ����
    * @param root @~english Root node.
    * @~chinese ���ڵ㡣
    * @param action @~english Action time line.
    * @~chinese ʱ���ᶯ����
    * @return @~english Is init succeed.
    * @~chinese �Ƿ��ʼ���ɹ���
    */
    bool init(cocos2d::Node* root, ActionTimeline* action);
    
    /** @~english Set root node.
    *   @~chinese ���ø��ڵ㡣
    * @param root @~english Root node.
    * @~chinese ���ڵ㡣
    */
    virtual void setRoot(cocos2d::Node* root);
    /** @~english Get root node.
    *   @~chinese ��ȡ���ڵ㡣
    * @return @~english Root node.
    * @~chinese ���ڵ㡣
    */
    virtual cocos2d::Node* getRoot();
    
    /** @~english Set action time line.
    *   @~chinese ����ʱ���ᶯ����
    * @param action @~english Action time line.
    * @~chinese ʱ���ᶯ����
    */
    virtual void setActionTimeline(ActionTimeline* action);
    /** @~english Get action time line.
    *   @~chinese ��ȡʱ���ᶯ����
    * @return @~english Action time line.
    * @~chinese ʱ���ᶯ����
    */
    virtual ActionTimeline* getActionTimeline();
    
protected:
    cocos2d::Node* _root;
    ActionTimeline* _action;
};

NS_TIMELINE_END


#endif /*__COCOSSTUDIO_CCACTIONTIMELINENODE_H__*/
