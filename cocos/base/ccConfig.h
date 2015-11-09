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

#ifndef __CCCONFIG_H__
#define __CCCONFIG_H__

#include "platform/CCPlatformConfig.h"


/**
 * @file
 * @~english
 * cocos2d (cc) configuration file.
 * @~chinese 
 * cocos2d(cc)�����ļ���
*/


/** @def CC_ENABLE_STACKABLE_ACTIONS
 * @~english If enabled, actions that alter the position property (eg: MoveBy, JumpBy, BezierBy, etc..) will be stacked.
 * If you run 2 or more 'position' actions at the same time on a node, then end position will be the sum of all the positions.
 * If disabled, only the last run action will take effect.
 * Enabled by default. Disable to be compatible with v2.0 and older versions.
 * @~chinese 
 * �������, �ı�λ�����ԵĶ���(�� MoveBy, JumpBy, BezierBy..)����ŵ�ջ����.
 * �����һ������(`node`)��ͬʱ������2�������ı�λ�����ԵĶ���, �������(`node`)������λ�û������иı�λ�����Զ�����ʸ����.
 * �������, ֻ�����һ���ı�λ�����ԵĶ�������Ч.
 * Ĭ������. ������Ϊ�˺�v2.0����ɵİ汾����.
 * @since v2.1
 */
#ifndef CC_ENABLE_STACKABLE_ACTIONS
#define CC_ENABLE_STACKABLE_ACTIONS 1
#endif


/** @def CC_ENABLE_GL_STATE_CACHE
 * @~english If enabled, cocos2d will maintain an OpenGL state cache internally to avoid unnecessary switches.
 * In order to use them, you have to use the following functions, instead of the GL ones:
 *  - ccGLUseProgram() instead of glUseProgram().
 *  - GL::deleteProgram() instead of glDeleteProgram().
 *  - GL::blendFunc() instead of glBlendFunc().

 * If this functionality is disabled, then ccGLUseProgram(), GL::deleteProgram(), GL::blendFunc() will call the GL ones, without using the cache.

 * It is recommended to enable whenever possible to improve speed.
 * If you are migrating your code from GL ES 1.1, then keep it disabled. Once all your code works as expected, turn it on.

 * Default value: Enabled by default

 * @~chinese 
 * �������,cocos2d��ά��һ��OpenGL�ڲ�����,�Ա��ⲻ��Ҫ���л���
 * Ϊ��ʹ������,�����ʹ�����º���,������GL�ĺ���:
 * - ʹ��ccGLUseProgram()������glUseProgram()��
 * - ʹ��GL::deleteProgram()������glDeleteProgram()��
 * - GL::blendFunc()������glBlendFunc()��
 * 
 * ������ô˹���,��ôccGLUseProgram(),GL:deleteProgram(),GL:blendFunc()������GL�ĺ���,����ʹ�û��档
 * 
 * ���������Ծ���������ٶȡ�
 * ��������ڴ�GL ES 1.1Ǩ�����Ĵ���,�Ƚ�������һ�����д�����Ԥ�ڵ���������,�ٰ����򿪡�
 * 
 * Ĭ��ֵ:Ĭ������
 * 
 * @since v2.0.0
 */
#ifndef CC_ENABLE_GL_STATE_CACHE
#define CC_ENABLE_GL_STATE_CACHE 1
#endif


/** @def CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
 * @~english If enabled, the texture coordinates will be calculated by using this formula:
 * - texCoord.left = (rect.origin.x*2+1) / (texture.wide*2);
 * - texCoord.right = texCoord.left + (rect.size.width*2-2)/(texture.wide*2);

 * The same for bottom and top.

 * This formula prevents artifacts by using 99% of the texture.
 * The "correct" way to prevent artifacts is by using the spritesheet-artifact-fixer.py or a similar tool.

 * Affected nodes:
 * - Sprite / SpriteBatchNode and subclasses: LabelBMFont, TMXTiledMap.
 * - LabelAtlas.
 * - QuadParticleSystem.
 * - TileMap.

 * To enabled set it to 1. Disabled by default.

 * @~chinese 
 * �������,�����������ͨ��ʹ�������ʽ:
 * - texCoord.left = (rect.origin.x*2+1) / (texture.wide*2);
 * - texCoord.right = texCoord.left + (rect.size.width*2-2)/(texture.wide*2);
 *
 * �ײ��Ͷ����ļ��㷽ʽҲ���ơ�
 * 
 * �����ʽʹ�����������99%�ķ�ֹʧ��.
 * ��ȷ��ֹʧ��ķ�����ʹ��spritesheet-artifact-fixer.py��һ�����ƵĹ���.
 *
 * Ӱ��ڵ�:
 * - Sprite / SpriteBatchNode and subclasses: LabelBMFont, TMXTiledMap.
 * - LabelAtlas.
 * - QuadParticleSystem.
 * - TileMap.
 * 
 * ʹ��������Ϊ1Ϊ������Ĭ������½��á�
 * 
 * @since v0.99.5
 */
#ifndef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0
#endif


/** @def CC_DIRECTOR_STATS_INTERVAL
 * @~english Seconds between FPS updates.
 * 0.5 seconds, means that the FPS number will be updated every 0.5 seconds.
 * Having a bigger number means a more reliable FPS.

 * Default value: 0.1f
 * @~chinese 
 * FPS����������
 * 0.5��,��ζ��FPS������ÿ0.5�����һ�Ρ�
 * �����ֵ��ζ��һ�����ɿ���FPS��
 * 
 * Ĭ��ֵ:0.1 f
 */
#ifndef CC_DIRECTOR_STATS_INTERVAL
#define CC_DIRECTOR_STATS_INTERVAL (0.1f)
#endif


/** @def CC_DIRECTOR_FPS_POSITION
 * @~english Position of the FPS.

 * Default: 0,0 (bottom-left corner).
 * @~chinese CC_DIRECTOR_FPS_POSITION
 * FPS��λ�á�
 * 
 * Ĭ��ֵ:0,0(���²��Ľ���)��
 */
#ifndef CC_DIRECTOR_FPS_POSITION
#define CC_DIRECTOR_FPS_POSITION Vec2(0,0)
#endif


/** @def CC_DIRECTOR_DISPATCH_FAST_EVENTS
 * @~english If enabled, and only when it is used with FastDirector, the main loop will wait 0.04 seconds to
 * dispatch all the events, even if there are not events to dispatch.
 * If your game uses lot's of events (eg: touches) it might be a good idea to enable this feature.
 * Otherwise, it is safe to leave it disabled.

 * To enable set it to 1. Disabled by default.
 * @~chinese
 * �������, ֻ�д˹��ܱ�FastDirectorʹ��ʱ, ��ѭ���Ż�ȴ� 0.04 ��ȥ�ַ����еĻ(Event), ��ʹ��ʱû��
 * �κλ��Ҫ�ַ���
 * ��������Ϸʹ�úܶ���¼�(��:�����¼�)���������һ��������������������ԡ�
 * ����,���ǰ�ȫ�İ������á�
 * 
 * ʹ��������Ϊ1�����á�Ĭ������½��á�
 * 
 * @warning @~english This feature is experimental.
 * @~chinese �������Ŀǰ�������Եġ�
 * @warning This feature is experimental.
 */
#ifndef CC_DIRECTOR_DISPATCH_FAST_EVENTS
 #define CC_DIRECTOR_DISPATCH_FAST_EVENTS 0
#endif


/** @def CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
 * @~english If enabled, cocos2d-mac will run on the Display Link thread. If disabled cocos2d-mac will run in its own thread.
 * If enabled, the images will be drawn at the "correct" time, but the events might not be very responsive.
 * If disabled, some frames might be skipped, but the events will be dispatched as they arrived.
 * To enable set it to a 1, to disable it set to 0. Enabled by default.
 * Only valid for cocos2d-mac. Not supported on cocos2d-ios.
 * @~chinese 
 * �������,cocos2d-mac�Ṥ����Display Link�߳��ϡ��������cocos2d-mac�����������Լ����̡߳�
 * ������ã�ͼƬ��������ȷ��ʱ����ƣ������¼����ܲ�����Ӧ�ĺܼ�ʱ��
 * �������,һЩ֡���ܱ�����,�����¼�һ�����ｫ�ᱻ���Ϸַ���
 * ʹ��������Ϊ1����,����Ϊ0���á�Ĭ�����á�
 * ֻ��cocos2d-mac��Ч����֧��cocos2d-ios��
 */
#ifndef CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
#define CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD 1
#endif


/** @def CC_NODE_RENDER_SUBPIXEL
 * @~english If enabled, the Node objects (Sprite, Label,etc) will be able to render in subpixels.
 * If disabled, integer pixels will be used.
 * To enable set it to 1. Enabled by default.
 * @~chinese 
 * �������,�ڵ����(Sprite, Label��)�ܹ�����������Ⱦ��
 * �������,��ʹ���������ء�
 * ʹ��������Ϊ1���á�Ĭ�����á�
 */
#ifndef CC_NODE_RENDER_SUBPIXEL
#define CC_NODE_RENDER_SUBPIXEL 1
#endif


/** @def CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
 * @~english If enabled, the Sprite objects rendered with SpriteBatchNode will be able to render in subpixels.
 * If disabled, integer pixels will be used.
 * To enable set it to 1. Enabled by default.
 * @~chinese 
 * �������,ʹ��SpriteBatchNode��Ⱦ��Sprite�ܹ�����������Ⱦ��
 * �������,��ʹ���������ء�
 * ʹ��������Ϊ1���á�Ĭ�����á�
 */
#ifndef CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define CC_SPRITEBATCHNODE_RENDER_SUBPIXEL    1
#endif


/** @def CC_TEXTURE_ATLAS_USE_VAO
 * @~english By default, TextureAtlas (used by many cocos2d classes) will use VAO (Vertex Array Objects).
 * Apple recommends its usage but they might consume a lot of memory, specially if you use many of them.
 * So for certain cases, where you might need hundreds of VAO objects, it might be a good idea to disable it.
 * To disable it set it to 0. Enabled by default.
 * @~chinese 
 * Ĭ�������,TextureAtlas(���cocos2d��ʹ��)��ʹ��VAO(�����������)��
 * ƻ����˾����ʹ��,�����ǿ��ܻ����Ĵ������ڴ�,�ر������ʹ�úܶ�Ļ���
 * ������ĳЩ�����,��������Ҫ���ٸ�VAO����,��ʱ�������������һ�������⡣
 * ��������Ϊ0��������Ĭ�����á�
 */
#ifndef CC_TEXTURE_ATLAS_USE_VAO
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        #define CC_TEXTURE_ATLAS_USE_VAO 1
    #else

        /* @~english Some Windows display adapter driver cannot support VAO.
         * Some android devices cannot support VAO very well, so we disable it by default for android platform.
         * Blackberry also doesn't support this feature.
         * @~chinese һЩWindows��ʾ��������������֧��VAO��
         * һЩ��׿�豸���ܺܺõ�֧��VAO�����������ڰ�׿ƽ̨Ĭ���ǽ������ġ�
         * ��ݮ�ֻ�Ҳ��֧��������ԡ�
         * Blackberry also doesn't support this feature.
         */
		#define CC_TEXTURE_ATLAS_USE_VAO 0
    #endif
#endif



/** @def CC_USE_LA88_LABELS
 * @~english If enabled, it will use LA88 (Luminance Alpha 16-bit textures) for LabelTTF objects.
 * If it is disabled, it will use A8 (Alpha 8-bit textures).
 * LA88 textures are 6% faster than A8 textures, but they will consume 2x memory.
 * This feature is enabled by default.
 * @~chinese 
 * �������,����ΪLabelTTF����ʹ��LA88(Luminance Alpha 16-bit������)��
 * ������ǽ��õ�,����ʹ��A8(Alpha 8-bit����)��
 * LA88�����A8�����6%,�����ǻ�����2�����ڴ档
 * ���������Ĭ�����á�
 * @since v0.99.5
 */
#ifndef CC_USE_LA88_LABELS
#define CC_USE_LA88_LABELS 1
#endif


/** @def CC_SPRITE_DEBUG_DRAW
 * @~english If enabled, all subclasses of Sprite will draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default:
 * 0 -- disabled
 * 1 -- draw bounding box
 * 2 -- draw texture box
 * @~chinese 
 * �������,���е�Sprite���ཫ��һ���߽��
 * �����ڵ���Ŀ�ġ�����������á�
 * ʹ��������Ϊ����0��ֵ�����á�Ĭ������½��á�
 * 0��������
 * 1�������߽��
 * 2������������
 */
#ifndef CC_SPRITE_DEBUG_DRAW
#define CC_SPRITE_DEBUG_DRAW 0
#endif

/** @def CC_LABEL_DEBUG_DRAW
* If enabled, all subclasses of Label will draw a bounding box.
* Useful for debugging purposes only. It is recommended to leave it disabled.
* To enable set it to a value different than 0. Disabled by default:
* 0 -- disabled
* 1 -- draw bounding box
*/
#ifndef CC_LABEL_DEBUG_DRAW
#define CC_LABEL_DEBUG_DRAW 0
#endif

/** @def CC_SPRITEBATCHNODE_DEBUG_DRAW
 * @~english If enabled, all subclasses of Sprite that are rendered using an SpriteBatchNode draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * �������,���������ѩ�̳���ʹ��SpriteBatchNode��һ���߽��
 * �����ڵ���Ŀ�ġ�����������á�
 * ʹ��������Ϊ����0��ֵ�����á�Ĭ������½��á�
 */
#ifndef CC_SPRITEBATCHNODE_DEBUG_DRAW
#define CC_SPRITEBATCHNODE_DEBUG_DRAW 0
#endif


/** @def CC_LABELBMFONT_DEBUG_DRAW
 * @~english If enabled, all subclasses of LabelBMFont will draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * �������,���е�����LabelBMFont����һ���߽��
 * �����ڵ���Ŀ�ġ�����������á�
 * ʹ��������Ϊ����0��ֵ�����á�Ĭ������½��á�
 */
#ifndef CC_LABELBMFONT_DEBUG_DRAW
#define CC_LABELBMFONT_DEBUG_DRAW 0
#endif


/** @def CC_LABELATLAS_DEBUG_DRAW
 * @~english If enabled, all subclasses of LabeltAtlas will draw a bounding box
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * �������,���е�����LabeltAtlas����һ���߽��
 * �����ڵ���Ŀ�ġ�����������á�
 * ʹ��������Ϊ����0��ֵ�����á�Ĭ������½��á�
 */
#ifndef CC_LABELATLAS_DEBUG_DRAW
#define CC_LABELATLAS_DEBUG_DRAW 0
#endif


/** @def CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
 * @~english If enabled (in conjunction with assertion macros) will verify on Node destruction that the node being destroyed has no event
 * listeners still associated with it in the event dispatcher. This can be used to track down problems where the event dispatch
 * system has dangling pointers to destroyed nodes.
 * Note: event listener verification will always be disabled in builds where assertions are disabled regardless of this setting.
 * @~chinese 
 * �������(�Ͷ���һ��), ������֤ Node ������������ node ����ʱû���� EventDispather ��ϵ�� EventListener.
 * ����������������Щ���⡪�� EventDispather ϵͳ����ָ��������node������ָ��.
 * ע��: �����Ա�����ʱ, ���۴˴�����Ϊ��ֵ, ���������� EventListener ��֤�����ǽ��õ�.
 */
#ifndef CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
#define CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS 0
#endif


/** @def CC_ENABLE_PROFILERS
 * @~english If enabled, will activate various profilers within cocos2d. This statistical data will be output to the console
 * once per second showing average time (in milliseconds) required to execute the specific routine(s).
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * �������,����cocos2d������ַ����������ͳ�����ݽ������������̨
 * һ��ÿ����ʾ�����ƽ��ʱ��(�Ժ���Ϊ��λ)��ִ���ض�������(s)��
 * �����ڵ���Ŀ�ġ�����������á�
 * Ҫ���ÿ��Խ�������Ϊ��Ϊ0��ֵ��Ĭ������½��á�
 */
#ifndef CC_ENABLE_PROFILERS
#define CC_ENABLE_PROFILERS 0
#endif


/** @~english Enable Lua engine debug log.  @~chinese �Ƿ�ʹ��Lua���������־��*/
#ifndef CC_LUA_ENGINE_DEBUG
#define CC_LUA_ENGINE_DEBUG 0
#endif


/** @~english Use physics integration API.  @~chinese ʹ��������API��*/
#ifndef CC_USE_PHYSICS
#define CC_USE_PHYSICS 1
#endif


/** @~english Use 3d physics integration API.  @~chinese ʹ��3d������API��*/
#ifndef CC_USE_3D_PHYSICS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define CC_USE_3D_PHYSICS 1
#endif
#endif

#if (CC_USE_3D_PHYSICS)
/** Use bullet physics engine. */
#ifndef CC_ENABLE_BULLET_INTEGRATION
#define CC_ENABLE_BULLET_INTEGRATION 1
#endif
#endif

/** @~english Use 3D navigation API. @~chinese �Ƿ�ʹ�õ��������ܡ�*/
#ifndef CC_USE_NAVMESH
#define CC_USE_NAVMESH 1
#endif

/** @~english Use culling or not.  @~chinese �Ƿ�ʹ���޳����ܡ�*/
#ifndef CC_USE_CULLING
#define CC_USE_CULLING 1
#endif


/** @~english Support PNG or not. If your application don't use png format picture, you can undefine this macro to save package size.
 * @~chinese ֧��PNG����������Ӧ�ó���ʹ��png��ʽ��ͼƬ,���������ȡ������걣����Ĵ�С��
*/
#ifndef CC_USE_PNG
#define CC_USE_PNG  1
#endif // CC_USE_PNG


/** @~english Support JPEG or not. If your application don't use jpeg format picture, you can undefine this macro to save package size.
 * @~chinese ֧��JPEG����������Ӧ�ó���ʹ��jpeg��ʽ��ͼƬ,�����ȡ������궨������С����С��
 */
#ifndef CC_USE_JPEG
#define CC_USE_JPEG  1
#endif // CC_USE_JPEG


/** @~english Support TIFF or not. If your application don't use TIFF format picture, you can undefine this macro to save package size.
 * @~chinese ֧��TIFF����������Ӧ�ó���ʹ��TIFF��ʽ��ͼƬ,�����ȡ������궨������С����С��
 */
#ifndef CC_USE_TIFF
#define CC_USE_TIFF  1
#endif // CC_USE_TIFF


/** @~english Support webp or not. If your application don't use webp format picture, you can undefine this macro to save package size.
 * @~chinese ֧��webp����������Ӧ�ó���ʹ��webp��ʽͼƬ,�����ȡ������궨������С����С��
 */
#ifndef CC_USE_WEBP
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#define CC_USE_WEBP  1
#endif
#endif // CC_USE_WEBP


 /** @~english Support WIC (Windows Image Component) or not. Replaces PNG, TIFF and JPEG
  * @~chinese �Ƿ�֧��WIC(Windowsͼ�����)��ȡ��PNG,TIFF��JPEG
 */
#ifndef CC_USE_WIC
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define CC_USE_WIC  1
#undef CC_USE_TIFF
#undef CC_USE_JPEG
#undef CC_USE_PNG
#endif
#endif // CC_USE_WIC


/** @~english Enable Script binding.  @~chinese ���ýű��󶨡�*/
#ifndef CC_ENABLE_SCRIPT_BINDING
#define CC_ENABLE_SCRIPT_BINDING 1
#endif


/** @def CC_CONSTRUCTOR_ACCESS
 * @~english Indicate the init functions access modifier. If value equals to protected, then these functions are protected.
 * If value equals to public, these functions are public,
 * protected by default.
 * @~chinese 
 * ����init�����������η������ֵ����protected,��ô��Щ�����ܵ�������
 * ���ֵ���ڹ���,��Щ�����ǹ�����,
 * Ĭ������±�����
 */
#ifndef CC_CONSTRUCTOR_ACCESS
  #ifdef CC_ENABLE_SCRIPT_BINDING
    #define CC_CONSTRUCTOR_ACCESS public
  #else
    #define CC_CONSTRUCTOR_ACCESS protected
  #endif
#endif


/** @def CC_ENABLE_ALLOCATOR
 * @~english Turn on creation of global allocator and pool allocators
 * as specified by CC_ALLOCATOR_GLOBAL below.
 * @~chinese 
 * �򿪴���ȫ�ַ������ͳط�������
 * ����CC_ALLOCATOR_GLOBAL�涨��
 */
#ifndef CC_ENABLE_ALLOCATOR
# define CC_ENABLE_ALLOCATOR 0
#endif


/** @def CC_ENABLE_ALLOCATOR_DIAGNOSTICS
 * @~english Turn on debugging of allocators. This is slower, uses
 * more memory, and should not be used for production builds.
 * @~chinese 
 * �򿪵��Է�������������,ʹ�ø�����ڴ�,��Ҫ���ڲ�Ʒ������
 */
#ifndef CC_ENABLE_ALLOCATOR_DIAGNOSTICS
# define CC_ENABLE_ALLOCATOR_DIAGNOSTICS CC_ENABLE_ALLOCATOR
#endif


/** @def CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE
 * @~english Turn on override of global new and delete
 * as specified by CC_ALLOCATOR_GLOBAL_NEW_DELETE below.
 * @~chinese 
 * ����ȫ�ֵ�new��delete����д��
 * ����CC_ALLOCATOR_GLOBAL_NEW_DELETE�涨��
 */
#ifndef CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE
# define CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE 0
# endif//CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE


/** @def CC_ALLOCATOR_GLOBAL
 * @~english Specify allocator to use for global allocator.
 * @~chinese 
 * ָ��Ҫʹ�÷���������ȫ�ַ�������
 */
#ifndef CC_ALLOCATOR_GLOBAL
# define CC_ALLOCATOR_GLOBAL cocos2d::allocator::AllocatorStrategyDefault
#endif


/** @def CC_ALLOCATOR_GLOBAL_NEW_DELETE
 * @~english Specify allocator to use when overriding of new and delete.
 * @~chinese 
 * ����д��new��delete��ָ��Ҫʹ�õķ�������
 */
#ifndef CC_ALLOCATOR_GLOBAL_NEW_DELETE
# define CC_ALLOCATOR_GLOBAL_NEW_DELETE cocos2d::allocator::AllocatorStrategyGlobalSmallBlock
#endif

#endif // __CCCONFIG_H__
