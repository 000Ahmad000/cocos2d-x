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

#ifndef __CCTRANSFORMHELP_H__
#define __CCTRANSFORMHELP_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/*
 * @~english Use to calculate the matrix of node from parent node.
 * @~chinese ��������ڵ��Ը��ڵ�ı任����
 * @js NA
 * @lua NA
 */
class CC_STUDIO_DLL TransformHelp
{
public:
    TransformHelp();

    /**
    * @~english Transform a node by the matrix from parent node.
    * @~chinese ͨ�����ڵ�ľ���任�ӽڵ㡣
    * @param node @~english Child node.
    * @~chinese �ӽڵ㡣
    * @param parentNode @~english Parent node.
    * @~chinese ���ڵ㡣
    */
    static void transformFromParent(BaseData &node, const BaseData &parentNode);
    /**
    * @~english Transform parent node by the matrix from node.
    * @~chinese ͨ���ӽڵ�ľ���任���ڵ㡣
    * @param node @~english Child node.
    * @~chinese �ӽڵ㡣
    * @param parentNode @~english Parent node.
    * @~chinese ���ڵ㡣
    */
    static void transformToParent(BaseData &node, const BaseData &parentNode);

    /**
    * @~english Transform a node by the matrix from parent node without scale.
    * @~chinese ͨ�����ڵ�ľ���任�ӽڵ㣬�����š�
    * @param node @~english Child node.
    * @~chinese �ӽڵ㡣
    * @param parentNode @~english Parent node.
    * @~chinese ���ڵ㡣
    */
    static void transformFromParentWithoutScale(BaseData &node, const BaseData &parentNode);
    /**
    * @~english Transform parent node by the matrix from node without scale.
    * @~chinese ͨ���ӽڵ�ľ���任���ڵ㣬�����š�
    * @param node @~english Child node.
    * @~chinese �ӽڵ㡣
    * @param parentNode @~english Parent node.
    * @~chinese ���ڵ㡣
    */
    static void transformToParentWithoutScale(BaseData &node, const BaseData &parentNode);

    /**
    * @~english Get matrix from node attribute.
    * @~chinese ��ȡ�ڵ����Ծ���
    * @param _node @~english Node.
    * @~chinese �ڵ㡣
    * @param _matrix @~english Matrix.
    * @~chinese ����
    */
    static void nodeToMatrix(const BaseData &_node, cocos2d::AffineTransform &_matrix);
    /**
    * @~english Get matrix from node attribute.
    * @~chinese ��ȡ�ڵ����Ծ���
    * @param node @~english Node.
    * @~chinese �ڵ㡣
    * @param matrix @~english Matrix.
    * @~chinese ����
    */
    static void nodeToMatrix(const BaseData &node, cocos2d::Mat4 &matrix);
    /**
    * @~english Set node attribute by matrix.
    * @~chinese ͨ���������ýڵ����ԡ�
    * @param _matrix @~english Matrix.
    * @~chinese ����
    * @param _node @~english Node.
    * @~chinese �ڵ㡣
    */
    static void matrixToNode(const cocos2d::AffineTransform &_matrix, BaseData &_node);
    /**
    * @~english Set node attribute by matrix.
    * @~chinese ͨ���������ýڵ����ԡ�
    * @param _matrix @~english Matrix.
    * @~chinese ����
    * @param _node @~english Node.
    * @~chinese �ڵ㡣
    */
    static void matrixToNode(const cocos2d::Mat4 &_matrix, BaseData &_node);

    /**
    * @~english Change target data by concat source data.
    * @~chinese ͨ���������Ŀ�����ݡ�
    * @param target @~english Target data.
    * @~chinese Ŀ�����ݡ�
    * @param source @~english Source data.
    * @~chinese Դ���ݡ�
    */
    static void nodeConcat(BaseData &target, BaseData &source);
    /**
    * @~english Change target data ay sub source data.
    * @~chinese ͨ���������Ŀ�����ݡ�
    * @param target @~english Target data.
    * @~chinese Ŀ�����ݡ�
    * @param source @~english Source data.
    * @~chinese Դ���ݡ�
    */
    static void nodeSub(BaseData &target, BaseData &source);
public:
    static cocos2d::AffineTransform helpMatrix1;
    static cocos2d::AffineTransform helpMatrix2;

    static cocos2d::Vec2 helpPoint1;
    static cocos2d::Vec2 helpPoint2;
};

}

#endif /*__CCTRANSFORMHELP_H__*/
