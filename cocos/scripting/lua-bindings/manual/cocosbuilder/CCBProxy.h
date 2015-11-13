#ifndef __CCBPROXY_H_
#define __CCBPROXY_H_

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

/**
 * @addtogroup lua
 * @{
 */

/**@~english
 * CCBProxy is a proxy for cocosbuilder.
 * By using CCBProxy we could create a CCBReader object conveniently and set the Lua callback function when some events triggered should be passed onto Lua.
 * @~chinese 
 * CCBProxy��cocosbuilder�����ࡣ
 * ͨ��ʹ��CCBProxy�����ǿ��Է���ش���һ��CCBReader���󣬲����ûص��������ڴ���һЩ��Ҫ���ݸ�Lua���¼���
 */
class CCBProxy : public Layer{
public:
    /**@~english
     * Default constructor,do nothing.
     *
     * @~chinese 
     * Ĭ�Ϲ��캯��,�����κ����顣
     * 
     * @lua NA
     * @js NA
     */
    CCBProxy() { }
    
    /**@~english
     * Destructor.
     *
     * @~chinese 
     * ����������
     * 
     * @lua NA
     * @js NA
     */
    virtual ~ CCBProxy(){ }
    
    /**@~english
     * Create a CCBProxy object.
     * 
     * @~chinese 
     * ����һ��CCBProxy����
     * 
     * @return @~english a CCBProxy object.
     *
     * @~chinese CCBProxy����
     * 
     * @lua NA
     * @js NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBProxy, create);
    
    /**@~english
     * Create a CCBReader object.
     * 
     * @~chinese 
     * ����һ��CCBReader����
     * 
     * @return @~english a CCBReader object.
     *
     * @~chinese CCBReader����
     * 
     * @lua NA
     * @js NA
     */
    CCBReader* createCCBReader();
    
    /**@~english
     * Read a ccb file.
     *
     * @~chinese 
     * ��ȡһ��ccb�ļ���
     * 
     * @param pszFileName @~english the string pointer point to the file name.
     * @~chinese ccb�ļ����ơ�
     * @param pCCBReader @~english the CCBreader object pointer.
     * @~chinese CCBreader����ָ�롣
     * @param bSetOwner @~english whether to set the owner or not.
     * @~chinese �Ƿ����������ߡ�
     * @return @~english a Node object pointer.
     * @~chinese һ��Node����ָ�롣
     * @js NA
     */
    Node* readCCBFromFile(const char *pszFileName,CCBReader* pCCBReader,bool bSetOwner = false);
    
    /**@~english
     * Get the real type name of pNode.
     * By using the dynamic_cast function, we could get the real type name of pNode.
     *
     * @~chinese 
     * ��ȡpNode����ʵ��������
     * ͨ������dynamic_cast����,���ǿ��Ի�ȡpNode����ʵ��������
     * 
     * @param pNode @~english the Node object used to query.
     * @~chinese ���ڲ�ѯ��Node����ָ�롣
     * @return @~english a string pointer point to the real type name or return "No Support".
     * @~chinese ����һ����ʵ���������ߡ�No Support����
     * @js NA
     */
    const char* getNodeTypeName(Node* pNode);
    
    /**@~english
     * Set relationship between the Lua callback function reference id handle and the node.
     * According to the different controlEvents values,we would choose different ScriptHandlerMgr::HandlerTyp.
     * When node receive the events information should be passed into Lua, it would find the Lua callback funtion by the handle.Then, push the related data into Lua stack.
     * Finally. call the Lua function.
     * 
     * @~chinese 
     * ���ö�ӦLua�ص�������handle��node�����ӳ���ϵ��
     * ͬʱ���ݲ�ͬcontrolEventsֵ,���ǻ�ѡ��ͬ��ScriptHandlerMgr::HandlerTyp������ӳ���ϵ��
     * ��node���յ���Ҫ���ݵ�Lua���¼�ʱ������ͨ��handle�ҵ���Ӧ��Lua������Ȼ��������Ϣ��Ϊ��������ѹ��Luaջ�У�������Lua������
     * 
     * @param node @~english the node object have related with handle.And it would be push into the Lua stack as the function parameter��when the events are triggered.
     * @~chinese ��handl������node�������¼�����ʱ��������ΪLua�����Ĳ���ѹ�뵽Luaջ�С�
     * @param handle @~english the Lua callback function reference id.
     * @~chinese Lua������reference id��
     * @param controlEvents @~english the combination value of Control::EventType, default 0.
     * @~chinese Control::EventType�����ֵ,Ĭ��Ϊ0��
     * @js NA
     */
    void setCallback(Node* node,int handle, int controlEvents = 0);
};

// end group
/// @}

/// @cond
class CCBLayerLoader:public LayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBLayerLoader, loader);
};
/// @endcond

#endif // __CCBPROXY_H_
