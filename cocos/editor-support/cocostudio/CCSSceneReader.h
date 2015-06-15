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

#ifndef __CCSSCENEREADER_H__
#define __CCSSCENEREADER_H__

#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/** 
 * @class SceneReader
 * @brief @~english Reader of parsing export data of cocos studio 1.x scene reader.
 * @~chinese cocos studio 1.x �����༭���������ݽ�������
*/
class CC_STUDIO_DLL SceneReader
{
public:

    enum class AttachComponentType
    {
        ///parent: Empty Node
        ///            ComRender(Sprite, Armature, TMXTiledMap, ParticleSystemQuad, GUIComponent)
        ///            ComAttribute
        ///            ComAudio
        ///            ....
        EMPTY_NODE,
        
        ///parent:   ComRender(Sprite, Armature, TMXTiledMap, ParticleSystemQuad, GUIComponent)
        ///          ComAttribute
        ///          ComAudio
        ///          .....
        RENDER_NODE,
        
        /// Default AttachComponentType is _EmptyNode
        DEFAULT = EMPTY_NODE,
    };

    /**
     * @brief @~english Get instance point of SceneReader.
     * @~chinese SceneReader����ָ�롣
     */
    static SceneReader* getInstance();

    /**
     * @brief @~english Destroy instance point of SceneReader.
     * @~chinese ����SceneReader����ָ�롣
     *  @js purge
     *  @lua destroySceneReader
     */
    static void destroyInstance();

    /**
     * @brief @~english Get version string of SceneReader.
     * @~chinese SceneReader�汾���ַ�����
     */
    static const char* sceneReaderVersion();

    /**
     * @brief @~english Create a scene with json or binary file path and type of attach component.
     * @~chinese ���ݶ����ƻ���json·���ͽṹ���������ͣ�����������
     * @param fileName @~english Json or binary file path
     * @~chinese json���߶������ļ�·��
     * @param attachComponent @~english Type of attach component
     * @~chinese ����ṹ����������
     *  @js purge
     *  @lua destroySceneReader
     */
    cocos2d::Node* createNodeWithSceneFile(const std::string &fileName, AttachComponentType attachComponent = AttachComponentType::EMPTY_NODE);

    /**
     * @brief @~english Call selector after each of the components created.
     * @~chinese ����ÿ�����������Ϻ�ص�������
     * @param @~english Callback function of selector
     * @~chinese selector �ص�����
     */
    void setTarget(const std::function<void(cocos2d::Ref* obj, void* doc)>& selector);

    /**
     * @brief @~english Get Node point by tag.
     * @~chinese ����nTag��ȡnodeָ�롣
     * @param tag @~english Tag of node.
     * @~chinese node��tag��
     * @return @~english Node point by tag.
     * @~chinese ����tag����nodeָ�롣
     */
    cocos2d::Node* getNodeByTag(int nTag);

    /**
     * @brief @~english Get the type of attach component.
     * @~chinese ��ȡ��������ṹ���������͡�
     */
    inline AttachComponentType getAttachComponentType(){return _attachComponent;}
CC_CONSTRUCTOR_ACCESS:

    /**
     * @brief @~english SceneReader constructor.
     * @~chinese SceneReader���캯����
     * @js ctor
     */
    SceneReader(void);

    /**
     * @brief @~english SceneReader destructor.
     * @~chinese SceneReader����������
     */
    virtual ~SceneReader(void);
    
private:
    /**
     * @brief @~english Get component name with class name.
     * @~chinese ����������ȡ������ơ�
     * @param @~english Component name
     * @~chinese �������
     */
    std::string getComponentClassName(const std::string& name);

    /**
     * @brief @~english Create component point with class name.
     * @~chinese �����������������
     * @param classname @~english Class name.
     * @~chinese ������
     * @return @~english Component point.
     * @~chinese ���ָ�롣
     */
    cocos2d::Component* createComponent(const std::string classname);

    /**
     * @brief @~english Create node object and add it to parent node with json file path.
     * @~chinese ���������ṹ��node����
     * @param dict @~english Json object.
     * @~chinese json����
     * @param parent @~english Parent node point.
     * @~chinese ����nodeָ�롣
     * @param attachComponent @~english Type of attach component
     * @~chinese ����ṹ����������
     * @return @~english Node object point.
     * @~chinese node����ָ�롣
     */
    cocos2d::Node* createObject(const rapidjson::Value& dict, cocos2d::Node* parent, AttachComponentType attachComponent);

    /**
     * @brief @~english Set property of node.
     * @~chinese ����node�������ԡ�
     * @param dict @~english Json object.
     * @~chinese json����
     * @param node @~english Node point.
     * @~chinese nodeָ�롣
     */
    void setPropertyFromJsonDict(const rapidjson::Value& dict, cocos2d::Node *node);

     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor and assign to doc.
     * @~chinese ����cocos studio 1.x �����༭������json���ݣ��ж�json����Ч�ԣ���json����doc��ֵ��
     * @param fileName @~english Json file path.
     * @~chinese json·����
     * @param doc @~english Json data object
     * @~chinese json���ݶ���
     * @return @~english true parse successfully, false failed to parse.
     * @~chinese true �����ɹ�������false��
     */
    bool readJson(const std::string &fileName, rapidjson::Document& doc);

    /**
     * @brief @~english Create node object and add it to parent node by binary file path.
     * @~chinese ���������ṹ��node����
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭���������������ݼ���������
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭����������������node����
     * @param parent @~english Parent node point.
     * @~chinese ��nodeָ�롣
     * @param attachComponent @~english Type of attach component
     * @~chinese ����ṹ����������
     * @return @~english Node object point.
     * @~chinese node����ָ�롣
     */
    cocos2d::Node* createObject(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node* parent, AttachComponentType attachComponent);

    /**
     * @brief @~english Create node object and add it to parent node with binary file path.
     * @~chinese ���������ṹ��node����
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭���������������ݼ���������
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x�����༭����������������node����
     * @param node @~english Node point.
     * @~chinese nodeָ�롣
     */
    void setPropertyFromJsonDict(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node *node);

    /**
     * @brief @~english get Node point by tag based on its parent node point.
     * @~chinese ����tag��parentָ�룬��parent�ĺ����м����tagƥ���ȡnodeָ�롣
     * @param parent @~english Parent node point.
     * @~chinese ��nodeָ�롣
     * @param tag @~english Tag of node.
     * @~chinese node��tag��
     * @return @~english Node point by tag.
     * @~chinese ����tag����nodeָ�롣
     */
    cocos2d::Node* nodeByTag(cocos2d::Node *parent, int tag);
private:
    static SceneReader* s_sharedReader;
    std::function<void(cocos2d::Ref* obj, void* doc)> _fnSelector;
    cocos2d::Node*      _node;
    AttachComponentType _attachComponent;
};


}

#endif
