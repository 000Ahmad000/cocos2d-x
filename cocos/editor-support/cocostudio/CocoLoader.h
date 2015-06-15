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

#ifndef _COCOLOADER_H
#define _COCOLOADER_H

#include <stdint.h>
#include "json/document.h"
#include "cocostudio/CocosStudioExport.h"

#pragma pack (4)

namespace cocostudio{
        
class CocoLoader;
    
struct CC_STUDIO_DLL stExpCocoAttribDesc
{
    char     m_cTypeName;
    uint32_t m_szName;
public:
    /**
    * @~english Get type name.
    * @~chinese ��ȡ��������.
    *
    * @parame pCoco  @~english property loader @~chinese ���Լ�����
    *
    * @return @~english type name @~chinese ��������
    */
    char* GetName(CocoLoader*	pCoco);
};

struct CC_STUDIO_DLL stExpCocoObjectDesc
{
    unsigned char	m_cAttribNum;
    uint32_t		m_szName;
    uint32_t		m_pAttribDescArray;
public:
    /**
    * @~english Get type name.
    * @~chinese ��ȡ��������.
    *
    * @parame pCoco  @~english property loader @~chinese ���Լ�����
    *
    * @return @~english type name @~chinese ��������
    */
    char*	GetName(CocoLoader*	pCoco);
    /**
    * @~english Get attribute count.
    * @~chinese ��ȡ��������.
    *
    * @return @~english count of attributes @~chinese ��������
    */
    int		GetAttribNum();
    /**
    * @~english Get attributes description array.
    * @~chinese ��ȡ������������.
    *
    * @parame pCoco  @~english property loader @~chinese ���Լ�����
    *
    * @return @~english attributes description array @~chinese ������������
    */
    stExpCocoAttribDesc*	GetAttribDescArray(CocoLoader*	pCoco);
};

struct CC_STUDIO_DLL stExpCocoNode
{
public:
    int16_t			m_ObjIndex;
    int16_t			m_AttribIndex;
    unsigned char	m_ChildNum;
    uint32_t		m_szValue;
    uint32_t		m_ChildArray;
public:
    /**
    * @~english Get json value type.
    * @~chinese ��ȡjsonֵ������.
    *
    * @parame pCoco  @~english property loader @~chinese ���Լ�����
    *
    * @return @~english json value type @~chinese jsonֵ����
    */
    rapidjson::Type		GetType(CocoLoader*	pCoco);
    /**
    * @~english Get type name.
    * @~chinese ��ȡ��������.
    *
    * @parame pCoco  @~english property loader @~chinese ���Լ�����
    *
    * @return @~english type name @~chinese ��������
    */
    char*				GetName(CocoLoader*	pCoco);
    /**
    * @~english Get type name.
    * @~chinese ��ȡ��������.
    *
    * @parame pCoco  @~english property loader @~chinese ���Լ�����
    *
    * @return @~english type name @~chinese ��������
    */
    char*				GetValue(CocoLoader*	pCoco);
    /**
    * @~english Get child array.
    * @~chinese ��ȡ�������ӽڵ�����.
    *
    * @return @~english count of child @~chinese �ӽڵ�����
    */
    int					GetChildNum();
    /**
    * @~english Get child array.
    * @~chinese ��ȡ�ӽڵ��б�.
    *
    * @parame pCoco  @~english property loader @~chinese ���Լ�����
    *
    * @return @~english child array @~chinese �ӽڵ��б�
    */
    stExpCocoNode*		GetChildArray(CocoLoader*	pCoco);
public:
    void WriteJson(CocoLoader* pCoco,void* pFileName = nullptr, int vLayer = 0, bool bEndNode = false, bool bParentNodeIsArray = false);
};

struct CC_STUDIO_DLL stCocoFileHeader
{
    char		m_FileDesc[32];
    char		m_Version[32];
    uint32_t	m_nDataSize;
    uint32_t	m_nCompressSize;
    uint32_t	m_ObjectCount;
    uint32_t	m_lAttribMemAddr;
    uint32_t	m_CocoNodeMemAddr;
    uint32_t	m_lStringMemAddr;
    
};

class CC_STUDIO_DLL CocoLoader
{
    stCocoFileHeader*			m_pFileHeader;
    stExpCocoNode*				m_pRootNode;
    stExpCocoObjectDesc*		m_pObjectDescArray;
    char*						m_pMemoryBuff;
    
public:
    CocoLoader();
    ~CocoLoader();
public:

    /**
    * @~english Read binary data buffer.
    * @~chinese ��ȡ�����ƻ���.
    *
    * @parame pBinBuff  @~english binary buffer @~chinese �����ƻ���
    *
    * @return @~english if load successed @~chinese �Ƿ��ȡ�ɹ�
    */
    bool					ReadCocoBinBuff(char* pBinBuff);
    /**
    * @~english Get the header of description data.
    * @~chinese ��ȡ��������ͷ.
    *
    * @return @~english header buffer pointer @~chinese ͷ���ݻ�����ָ��
    */
    stCocoFileHeader*		GetFileHeader(){ return m_pFileHeader; }
    /**
    * @~english Get the root node.
    * @~chinese ��ȡ���ڵ�.
    *
    * @return @~english root node @~chinese ���ڵ�
    */
    stExpCocoNode*			GetRootCocoNode(){ return	m_pRootNode; }
    /**
    * @~english Get attributes description array.
    * @~chinese ��ȡ������������.
    *
    * @return @~english attributes description array @~chinese ������������
    */
    stExpCocoObjectDesc*	GetCocoObjectDescArray(){ return	m_pObjectDescArray; }
    /**
    * @~english Get attribute description buffer address
    * @~chinese ��ȡ����������������ַ
    *
    * @return @~english buffer address @~chinese ��������ַ
    */
    char*					GetMemoryAddr_AttribDesc();
    /**
    * @~english Get node address
    * @~chinese ��ȡ�ڵ�ָ��
    *
    * @return @~english buffer address @~chinese ��������ַ
    */
    char*					GetMemoryAddr_CocoNode();
    /**
    * @~english Get string buffer address
    * @~chinese ��ȡ�ַ�����������ַ
    *
    * @return @~english buffer address @~chinese ��������ַ
    */
    char*					GetMemoryAddr_String();
    
};

}

#pragma pack ()
#endif
