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

#ifndef __cocos2d_libs__FlatBuffersSerialize__
#define __cocos2d_libs__FlatBuffersSerialize__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "cocostudio/CocosStudioExport.h"

namespace flatbuffers
{
    class FlatBufferBuilder;
    template<typename T> struct Offset;
    struct String;
    
    struct CSParseBinary;
    struct NodeTree;
    
    struct WidgetOptions;
    
    struct SingleNodeOptions;
    struct SpriteOptions;
    struct ParticleSystemOptions;
    struct TMXTiledMapOptions;
    
    struct ButtonOptions;
    struct CheckBoxOptions;
    struct ImageViewOptions;
    struct TextBMFontOptions;
    struct TextOptions;
    struct TextFieldOptions;
    struct LoadingBarOptions;
    struct SliderOptions;
    struct PanelOptions;
    struct ScrollViewOptions;
    struct PageViewOptions;
    struct ListViewOptions;
    
    struct ProjectNodeOptions;
    
    struct ComponentOptions;
    struct ComAudioOptions;
    
    struct TextAtlasOptions;
    
    struct NodeAction;
    struct AnimationInfo;
    struct TimeLine;
    struct Frame;
    struct PointFrame;
    struct ScaleFrame;
    struct ColorFrame;
    struct TextureFrame;
    struct EventFrame;
    struct IntFrame;
    struct BoolFrame;
    struct InnerActionFrame;
    struct EasingData;
}

namespace tinyxml2
{
    class XMLElement;
}

namespace cocostudio {
    
class CC_STUDIO_DLL FlatBuffersSerialize
{
    
public:
    /**
    * @~english Gets the static instance of FlatBuffersSerialize.
    * @~chinese ��ȡFlatBuffersSerialize�ľ�̬ʵ��.
    */
    static FlatBuffersSerialize* getInstance();
    /**
    * @~english Destroy FlatBuffersSerialize static instance.
    * @~chinese �ͷ�FlatBuffersSerialize�ľ�̬ʵ��.
    */
    static void destroyInstance();

    /** 
    * @deprecated @~english Use method destroyInstance() instead @~chinese �����ã���ʹ��destroyInstance()
    */
    CC_DEPRECATED_ATTRIBUTE static void purge();

    FlatBuffersSerialize();
    ~FlatBuffersSerialize();

    /**
    * @~english Destroy FlatBufferBuilder instance.
    * @~chinese �ͷ�FlatBufferBuilder�ľ�̬ʵ��.
    */
    void deleteFlatBufferBuilder();

    /**
    * @~english Serialize flat buffers with XML.
    * @~chinese ����xml�������л�flat buffer.
    *
    * @parame xmlFileName           @~english input xml file name @~chinese xml�ļ�����
    *
    * @parame flatbuffersFileName   @~english output flatbuffer file name @~chinese �����flat buffer�ļ���
    *
    * @return @~english error message @~chinese ������Ϣ
    */
    std::string serializeFlatBuffersWithXMLFile(const std::string& xmlFileName,
                                                const std::string& flatbuffersFileName);

    /**
    * @~english Create node tree flatbuffer from xml object
    * @~chinese ����xml���ݴ���flat buffer�ڵ���
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @parame classType   @~english root node class type @~chinese ���ڵ�����
    *
    * @return @~english error message @~chinese ������Ϣ
    */
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTree(const tinyxml2::XMLElement* objectData,
                                                              std::string classType);
    
    /**
    * @~english Create node action flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ�ڵ㶯������
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::NodeAction> createNodeAction(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create time line flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽʱ��������
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::TimeLine> createTimeLine(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create point frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽpoint֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::PointFrame> createPointFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create scale frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ����֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::ScaleFrame> createScaleFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create color frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ��ɫ֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::ColorFrame> createColorFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create texture frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ����֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::TextureFrame> createTextureFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create event frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ�¼�֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::EventFrame> createEventFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create int frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ����֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::IntFrame> createIntFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create bool frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ������֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::BoolFrame> createBoolFrame(const tinyxml2::XMLElement* objectData);
    /**
    * @~english Create inner action frame flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽǶ��֡����
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::InnerActionFrame> createInnerActionFrame(const tinyxml2::XMLElement* objectData);
    
    /**
    * @~english Create easing data flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ��������
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::EasingData> createEasingData(const tinyxml2::XMLElement* objectData);

    /**
    * @~english Create animation info flatbuffer from xml object
    * @~chinese ����xml�ڵ㴴��flat buffer��ʽ��������
    *
    * @parame objectData  @~english xml descriptoin object @~chinese xml��ʽ��������
    *
    * @return @~english flatbuffer object @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::AnimationInfo> createAnimationInfo(const tinyxml2::XMLElement* objectData);
    /**/

    /**
    * @~english Get resource type embed default or user added
    * @~chinese ��ȡ��Դ���ͣ��༭���Դ�Ĭ����Դ/�û������Դ
    *
    * @parame key  @~english resource type key @~chinese ��Դ���ͼ�ֵ
    *
    * @return @~english resource type @~chinese ��Դ����
    */
    int getResourceType(std::string key);
    /**
    * @~english Get GUI widget class type of a special component
    * @~chinese ��ȡָ�������UI�������
    *
    * @parame name  @~english component class name @~chinese ���������
    *
    * @return @~english widget class name @~chinese UI�������
    */
    std::string getGUIClassName(const std::string &name);
    /**
    * @~english Get GUI widget reader class name or a special widget
    * @~chinese ��ȡָ��UI�����reader����
    *
    * @parame widget  @~english UI widget component @~chinese UI���
    *
    * @return @~english widget reader class name @~chinese UI���reader����
    */
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    /**
    * @~english Choose flat buffer builder that can convert current xml project file to flat buffer data for simulator use
    * @~chinese ѡ����Խ���ǰxml��Ŀ�ļ�ת���ɹ�ģ����ʹ�����ݵ�flat buffer������
    *
    * @parame xmlFileName  @~english xml project file @~chinese xml��Ŀ�ļ�
    *
    * @return @~english flat buffer builder @~chinese flat buffer������
    */
    flatbuffers::FlatBufferBuilder* createFlatBuffersWithXMLFileForSimulator(const std::string& xmlFileName);
    /**
    * @~english Convert xml project object to flat buffer data for simulator use
    * @~chinese ��xml��Ŀ����ת��Ϊflat buffer���ݹ�ģ����ʹ��
    *
    * @parame objectData  @~english xml project object @~chinese xml��Ŀ����
    *
    * @parame classType   @~english root node class type @~chinese ���ڵ�����
    *
    * @return @~english flat buffer data @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::NodeTree> createNodeTreeForSimulator(const tinyxml2::XMLElement* objectData,
                                                                          std::string classType);
    /**
    * @~english Convert xml project object to flat buffer data for simulator use
    * @~chinese ��xml��Ŀ����ת��Ϊflat buffer���ݹ�ģ����ʹ��
    *
    * @parame objectData  @~english xml project object @~chinese xml��Ŀ����
    *
    * @return @~english flat buffer data @~chinese flat buffer����
    */
    flatbuffers::Offset<flatbuffers::ProjectNodeOptions> createProjectNodeOptionsForSimulator(const tinyxml2::XMLElement* objectData);
	/** 
    * @~english Get csd format version
    * @~chinese ��ȡcsd��ʽ�汾
    *
    * ��return @~english csd version @~chinese csd �汾
    */
    std::string getCsdVersion() { return _csdVersion; }
    
public:
    std::vector<flatbuffers::Offset<flatbuffers::String>> _textures;
    std::vector<flatbuffers::Offset<flatbuffers::String>> _texturePngs;
    bool _isSimulator;
    
private:
    flatbuffers::FlatBufferBuilder* _builder;
    flatbuffers::Offset<flatbuffers::CSParseBinary>* _csparsebinary;
    std::string _csdVersion;
};
}

#endif /* defined(__cocos2d_libs__FlatBuffersSerialize__) */
