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

#ifndef __CC_EXTENTIONS_CCCOMRENDER_H__
#define __CC_EXTENTIONS_CCCOMRENDER_H__

#include "CCComBase.h"
#include "2d/CCComponent.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

 /** 
 @���� ComRender
 @���� ��Ⱦ��� ��װ���ص��������Ⱦ����,ȷ�����ʵ�ֵ�һ����
 @ϸ�� ʵ�ֻ�ȡ�������Ⱦ����
 @�� ���
 */
class CC_STUDIO_DLL ComRender : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
CC_CONSTRUCTOR_ACCESS:
    /**
     *  @js ctor
     */
    /**
    @���� ��Ⱦ������캯��
    */
    ComRender(void);
    /**
    @���� ��Ⱦ������캯��
    @���� node ��װ��Ⱦ����ָ��
    @���� comName ��Ⱦ�������
    */
    ComRender(cocos2d::Node *node, const char *comName);
    /**
     * @js NA
     * @lua NA
     */
    /**
    @���� ��Ⱦ�����������
    */
    virtual ~ComRender(void);
    
public:
    /**
     * @js NA
     * @lua NA
     */
    /**
    @���� node����onEnter��ʱ�򣬻���������onEnter
    @���� ��
    */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    /**
    @���� node����onExit��ʱ�򣬻���������onExit
    @���� ��
    */
    virtual void onExit() override;
    /**
    @���� ����cocos studio 1.x �����༭�����������ݷ����л�
    @���� r SerData����ָ��
    @���� true �����л��ɹ���false �����л�ʧ��
    */
    virtual bool serialize(void* r) override;
    /**
    @���� ��ȡ��Ⱦ�����װ����Ⱦ�����ָ��
    @���� ��Ⱦ����ָ��
    */
    virtual cocos2d::Node* getNode();
    /**
    @���� ������Ⱦ�����װ����Ⱦ����ָ��
    @���� ��Ⱦ����ָ��
    @���� ��
    */
    virtual void setNode(cocos2d::Node *node);
   /**
    @���� ������Ⱦ���
    @���� ��Ⱦ���ָ��
    */
    static ComRender* create(void);
   /**
    @���� ������Ⱦ����ָ�����齨���ƴ�����Ⱦ���
    @���� node ��Ⱦ����ָ��
    @���� comName ��Ⱦ�������
    @���� ��Ⱦ���ָ��
    */
    static ComRender* create(cocos2d::Node *node, const char *comName);
private:
    /**
    @���� ����cocos studio 1.x �����༭��������json���ݣ���doc��ֵ
    @���� fileName cocos studio 1.x �����༭��������json·��
    @���� doc json����
    @���� true ����json�ɹ����������jsonʧ��
    */
    bool readJson(const std::string &fileName, rapidjson::Document &doc);

private:
    cocos2d::Node *_render;
};

}
#endif  // __FUNDATION__CCCOMPONENT_H__
