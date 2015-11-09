/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.
 
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

#ifndef __COCOS2D_UI_WEBVIEW_H
#define __COCOS2D_UI_WEBVIEW_H

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS )


#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/CCData.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN
namespace experimental{
    namespace ui{
        
class WebViewImpl;

/**
 * @brief @~english A View that displays web pages. 
 *
 * @~chinese һ��������ʾwebҳ��Ŀؼ���
 * 
 * @note @~english WebView displays web pages base on system widget.
 * It's mean WebView displays web pages above all graphical elements of cocos2d-x.
 * @~chinese WebViewʹ�ò���ϵͳ�������ʾ��ҳ���ݡ�
 * ����ζ��WebView�ᴦ�����е�Cocos2D-X��Ⱦ�ڵ�����档
 * @js NA
 */
class CC_GUI_DLL WebView : public cocos2d::ui::Widget {
public:
    /**@~english
     * Allocates and initializes a WebView.
     * @~chinese 
     * ����ͳ�ʼ��һ��WebView��
     */
    static WebView *create();

    /**@~english
     * Set javascript interface scheme.
     *
     * @~chinese 
     * ����javascript�ӿ�scheme��
     * 
     * @see WebView::setOnJSCallback()
     */
    void setJavascriptInterfaceScheme(const std::string &scheme);

    /**@~english
     * Sets the main page contents, MIME type, content encoding, and base URL.
     *
     * @~chinese 
     * ������ҳ���ݡ�MIME���͡����ݱ����baseURL
     * 
     * @param data @~english The content for the main page.
     * @~chinese ��ҳ������ݡ�
     * @param MIMEType @~english The MIME type of the data.
     * @~chinese MIME���͵����ݡ�
     * @param encoding @~english The encoding of the data.
     * @~chinese ���ݵı��롣
     * @param baseURL @~english The base URL for the content.
     * @~chinese baseURL
     */
    void loadData(const cocos2d::Data &data,
                  const std::string &MIMEType,
                  const std::string &encoding,
                  const std::string &baseURL);
    
    /**@~english
     * Sets the main page content and base URL.
     *
     * @~chinese 
     * ������ҳ���ݺ�baseURL��
     * 
     * @param string @~english The content for the main page.
     * @~chinese ��ҳ������ݡ�
     * @param baseURL @~english The base URL for the content.
     * @~chinese baseURL
     */
    void loadHTMLString(const std::string &string, const std::string &baseURL = "");

    /**@~english
     * Loads the given URL.
     *
     * @~chinese 
     * ���ظ���URL����ҳ
     * 
     * @param url @~english Content URL.
     * @~chinese һ��URL�ַ���
     */
    void loadURL(const std::string &url);

    /**@~english
     * Loads the given fileName.
     *
     * @~chinese 
     * ����ָ������ҳ�ļ�
     * 
     * @param fileName @~english WebPage fileName.
     * @~chinese ��ҳ�ļ���
     */
    void loadFile(const std::string &fileName);

    /**@~english
     * Stops the current load.
     * @~chinese 
     * ֹͣ��ǰҳ��ļ���
     */
    void stopLoading();

    /**@~english
     * Reloads the current URL.
     * @~chinese 
     * ���¼��ص�ǰURL��
     */
    void reload();

    /**@~english
     * Gets whether this WebView has a back history item.
     *
     * @~chinese 
     * �жϵ�ǰWebView�Ƿ��л�����ʷ��¼
     * 
     * @return @~english WebView has a back history item.
     * @~chinese ���WebView�л�����ʷ��¼���򷵻�True;���򷵻�false��
     */
    bool canGoBack();

    /**@~english
     * Gets whether this WebView has a forward history item.
     *
     * @~chinese 
     * �жϵ�ǰWebView�Ƿ���ǰ����ʷ��¼
     * 
     * @return @~english WebView has a forward history item.
     * @~chinese ���WebView��ǰ����ʷ��¼���򷵻�True;���򷵻�false
     */
    bool canGoForward();

    /**@~english
     * Goes back in the history.
     * @~chinese 
     * ����һ����ʷҳ��
     */
    void goBack();

    /**@~english
     * Goes forward in the history.
     * @~chinese 
     * ǰ��һ����ʷҳ��
     */
    void goForward();

    /**@~english
     * Evaluates JavaScript in the context of the currently displayed page.
     * @~chinese 
     * �ڵ�ǰ��ʾҳ����������л�����ִ��һ��js�ű���
     */
    void evaluateJS(const std::string &js);

    /**@~english
     * Set WebView should support zooming. The default value is false.
     * @~chinese 
     * ����WebView�Ƿ�֧�����š�Ĭ��ֵ��False
     */
    void setScalesPageToFit(const bool scalesPageToFit);
    
    /**@~english
     * Call before a web view begins loading.
     *
     * @~chinese 
     * ��WebView��ʼ����һ��ҳ��֮ǰ�ص��ĺ���
     * 
     * @param callback @~english The web view that is about to load new content.
     * @~chinese һ���ص�����������ָ��������Ҫ��ӵ����ݡ�
     * @return @~english YES if the web view should begin loading content; otherwise, NO .
     * @~chinese �����True,��WebViewӦ�ÿ�ʼ��������;����,��False.
     */
    void setOnShouldStartLoading(const std::function<bool(WebView *sender, const std::string &url)>& callback);
    
    /**@~english
     * A callback which will be called when a WebView event happens.
     * @~chinese 
     * һ���ص�������������WebView�¼�������ʱ�򱻵��á�
     */
    typedef std::function<void(WebView *sender, const std::string &url)> ccWebViewCallback;

    /**@~english
     * Call after a web view finishes loading.
     *
     * @~chinese 
     * ����WebView����ҳ����ɺ���õĻص�����
     * 
     * @param callback @~english A @see ccWebViewCallback callback.
     * @~chinese һ��ccWebViewCallback�ص�
     */
    void setOnDidFinishLoading(const ccWebViewCallback& callback);
    
    /**@~english
     * Call if a web view failed to load content.
     *
     * @~chinese 
     * ����WebView����ҳ��ʧ��ʱ����õĻص�������
     * 
     * @param callback @~english A @see ccWebViewCallback callback.
     * @~chinese һ��ccWebViewCallback�ص�
     */
    void setOnDidFailLoading(const ccWebViewCallback& callback);
    
    /**@~english
     * This callback called when load URL that start with javascript interface scheme.
     * @~chinese 
     * ����ص�����������javascript�ӿ�scheme��ʱ�򱻵��á�
     */
    void setOnJSCallback(const ccWebViewCallback& callback);
    
    /**@~english
     * Get the callback when WebView is about to start.
     * @~chinese 
     * ����WebView��ʼ����ҳ��Ļص�������
     */
    std::function<bool(WebView *sender, const std::string &url)> getOnShouldStartLoading()const;
    
    /**@~english
     * Get the callback when WebView has finished loading.
     * @~chinese 
     * ��ȡ��ǰWebView����ɼ���ʱ���õĻص�����
     */
    ccWebViewCallback getOnDidFinishLoading()const;
    
    /**@~english
     * Get the callback when WebView has failed loading.
     * @~chinese 
     * ��ȡ��ǰWebView����ʧ��ʱ���õĻص�����
     */
    ccWebViewCallback getOnDidFailLoading()const;

    /**@~english
     *Get the Javascript callback.
     * @~chinese 
     * ��ȡJavascript�ص�������
     */
    ccWebViewCallback getOnJSCallback()const;

    virtual void draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) override;

    /**@~english
     * Toggle visibility of WebView.
     * @~chinese 
     * ����WebView�Ŀɼ��ԡ�
     */
    virtual void setVisible(bool visible) override;
    
protected:
    virtual cocos2d::ui::Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
    std::function<bool(WebView *sender, const std::string &url)> _onShouldStartLoading;
    
    ccWebViewCallback _onDidFinishLoading;
    
    ccWebViewCallback _onDidFailLoading;
   
    ccWebViewCallback _onJSCallback;

CC_CONSTRUCTOR_ACCESS:
    /**@~english
     * Default constructor.
     * @~chinese 
     * Ĭ�Ϲ��캯����
     */
    WebView();
    
    /**@~english
     * Default destructor.
     * @~chinese 
     * Ĭ������������
     */
    virtual ~WebView();

private:
    WebViewImpl *_impl;
    friend class WebViewImpl;
};
        
      } // namespace ui
   } // namespace experimental
}//namespace cocos2d

#endif
// end group
/// @}
#endif //__COCOS2D_UI_WEBVIEW_H
