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

#ifndef __CCDISPLAYFACTORY_H__
#define __CCDISPLAYFACTORY_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

class Skin;
class Bone;
class DecorativeDisplay;
class DisplayData;
/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DisplayFactory
{
public:
    /*
    * @~english Add display.
    * @~chinese ������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    * @param displayData @~english Display data.
    * @~chinese ��ʾ���ݡ�
    */
    static void addDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create display.
    * @~chinese ������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    */
    static void createDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Update display.
    * @~chinese ������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param dt, @~english Delta time.
    * @~chinese ���ʱ�䡣
    * @param dirty @~english Is dirty.
    * @~chinese �Ƿ�Ϊ�ࡣ
    */
    static void updateDisplay(Bone *bone, float dt, bool dirty);

    /*
    * @~english Add sprite display.
    * @~chinese ���Ӿ�����ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    * @param displayData @~english Display data.
    * @~chinese ��ʾ���ݡ�
    */
    static void addSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create sprite display.
    * @~chinese ����������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    */
    static void createSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Initialize sprite display.
    * @~chinese ��ʼ��������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    * @param displayName @~english Display name.
    * @~chinese ��ʾ���ơ�
    * @param skin @~english The skin.
    * @~chinese Ƥ����
    */
    static void initSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, const char *displayName, Skin *skin);

    /*
    * @~english Add armature display.
    * @~chinese ���ӹ�����ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    * @param displayData @~english Display data.
    * @~chinese ��ʾ���ݡ�
    */
    static void addArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create armature display.
    * @~chinese ����������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    */
    static void createArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Update armature display.
    * @~chinese ���¹�����ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param display @~english Display node.
    * @~chinese ��ʾ�ڵ㡣
    * @param dt, @~english Delta time.
    * @~chinese ���ʱ�䡣
    */
    static void updateArmatureDisplay(Bone *bone, cocos2d::Node *display, float dt);

    /*
    * @~english Add particle display.
    * @~chinese ����������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    * @param displayData @~english Display data.
    * @~chinese ��ʾ���ݡ�
    */
    static void addParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    /*
    * @~english Create particle display.
    * @~chinese ����������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param decoDisplay @~english `DecorativeDisplay` object.
    * @~chinese `DecorativeDisplay`����
    */
    static void createParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    /*
    * @~english Update particle display.
    * @~chinese ����������ʾ��
    * @param bone @~english The bone.
    * @~chinese ��ͷ��
    * @param display @~english Display node.
    * @~chinese ��ʾ�ڵ㡣
    * @param dt, @~english Delta time.
    * @~chinese ���ʱ�䡣
    */
    static void updateParticleDisplay(Bone *bone, cocos2d::Node *display, float dt);
};


}

#endif /*__CCDISPLAYFACTORY_H__*/
