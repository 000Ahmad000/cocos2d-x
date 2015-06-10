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

#ifndef __UILOADINGBAR_H__
#define __UILOADINGBAR_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {
    class Scale9Sprite;

/** @class LoadingBar
*@brief @~english Visual indicator of progress in some operation.
 Displays a bar to the user representing how far the operation has progressed.

 @~chinese ��һЩ�����н����������������ʾ��
 ��ʾ���û�һ������ʾ�����Ѿ�����˶��١�
*/
class CC_GUI_DLL LoadingBar : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Loading bar progress direction.
     */
    enum class Direction
    {
        LEFT,
        RIGHT
    };

    /**
     * @~english Default constructor.
     * @~chinese Ĭ�Ϲ�����
     * @js ctor
     * @lua new
     */
    LoadingBar();
    
    /**
     * @~english Default destructor.
     * @~chinese Ĭ��������
     * @js NA
     * @lua NA
     */
    virtual ~LoadingBar();
    
    /**
     * @~english Create an empty LoadingBar.
     * @~chinese ����һ���յ�LoadingBar��
     * @return @~english A LoadingBar instance. @~chinese 
     */
    static LoadingBar* create();
    
     
    /**
     * @~english Create a LoadingBar with a texture name and a predefined progress value.
     * @~chinese ʹ��һ�������һ�����Ȱٷֱȴ���һ��LoadingBar��
     * @param textureName @~english LoadingBar background texture name. @~chinese LoadingBar��������
     * @param percentage @~english A percentage in float. @~chinese ��ʾ�Ľ��Ȱٷֱȡ�
     * @return @~english A LoadingBar instance. @~chinese һ��LoadingBarʵ����
     */
    static LoadingBar* create(const std::string& textureName, float percentage = 0);
    
    
    /**
     * @~english Create a LoadingBar with a texture name along with its texture type and a predefined progress value.
     * @~chinese ʹ��һ�������������ͺ�һ�����Ȱٷֱȴ���һ��LoadingBar��
     * @param textureName @~english LoadingBar background texture name. @~chinese LoadingBar��������
     * @param texType @~english LoadingBar background texture type. @~chinese LoadingBar�����������͡�
     * @param percentage @~english A percentage in float, default value is 0. @~chinese ��ʾ�Ľ��Ȱٷֱȡ�
     * @return @~english A LoadingBar instance. @~chinese һ��LoadingBarʵ����
     */
    static LoadingBar* create(const std::string& textureName,
                              TextureResType texType,
                              float percentage = 0);
    
    /**
     * @~english Change the progress direction of LoadingBar.
     * @~chinese �ı������ʾ����
     * @see Direction  `LEFT` means progress left to right, `RIGHT` otherwise.
     * @param direction @~english Direction @~chinese ��ʾ����
     */
    void setDirection(Direction direction);
    
    /**
     * @~english Get the progress direction of LoadingBar.
     * @~chinese ��ȡ������ʾ����
     * @see Direction  `LEFT` means progress left to right, `RIGHT` otherwise.
     * @return @~english LoadingBar progress direction. @~chinese ��ʾ����
     */
    Direction getDirection()const;
    
    /**
     * @~english Load texture for LoadingBar.
     * @~chinese LoadingBar���뱳������
     * @param texture   @~english File name of texture. @~chinese �������ơ�
     * @param texType   @~english Texture resource type,@see TextureResType. @~chinese ������Դ���͡�
     */
    void loadTexture(const std::string& texture,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * @~english Changes the progress value of LoadingBar.
     * @~chinese �ı�LoadingBar�ĵ�ǰ���ȡ�
     * @param percent   @~english Percent value from 1 to 100. @~chinese ����ֵ��1��100.
     */
    void setPercent(float percent);
    
    /**
     * @~english Get the progress value of LoadingBar.
     * @~chinese ��ȡLoadingBar��ǰ�Ľ��ȡ�
     * @return @~english Progress value from 1 to 100. @~chinese ����ֵ��1��100.
     */
    float getPercent() const;
    
    /**
     * @~english Enable scale9 renderer.
     * @~chinese �Ƿ�����Ⱦ�����š�
     * @param enabled @~english Set to true will use scale9 renderer, false otherwise. @~chinese True��ʾ������Ⱦ�����ţ���֮�رա�
     */
    void setScale9Enabled(bool enabled);
    
    
    /**
     * @~english Query whether LoadingBar is using scale9 renderer or not.
     * @~chinese ����LoadingBar�Ƿ�������Ⱦ�����š�
     * @return @~english Whether LoadingBar uses scale9 renderer or not. @~chinese True��ʾ������Ⱦ�����ţ���֮�رա�
     */
    bool isScale9Enabled()const;
    
    /**
     * @~english Set capInsets for LoadingBar.
     * This setting only take effect when enable scale9 renderer.
     * @~chinese ����CapInsets��
     * ֻ�е�������Ⱦ�����ź����Ҫ���á�
     * @param capInsets @~english CapInset in `Rect`. @~chinese CapInset�ľ�������
     */
    void setCapInsets(const Rect &capInsets);
    
    
    /**
     * @~english Query LoadingBar's capInsets.
     * @~chinese ����LoadingBar��capInsets��
     * @return @~english CapInsets of LoadingBar. @~chinese CapInset�ľ�������
     */
    const Rect& getCapInsets()const;
    
    //override methods.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual std::string getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
   
    void setScale9Scale();
    void updateProgressBar();
    void barRendererScaleChangedWithSize();
    
    virtual void adaptRenderers() override;
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    Direction _direction;
    float _percent;
    float _totalLength;
    Scale9Sprite* _barRenderer;
    TextureResType _renderBarTexType;
    Size _barRendererTextureSize;
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    std::string _textureFile;
    bool _barRendererAdaptDirty;
};

}
// end of ui group
/// @}
NS_CC_END
#endif /* defined(__CocoGUI__LoadingBar__) */
