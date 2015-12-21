/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

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
#ifndef CC_TERRAIN_H
#define CC_TERRAIN_H

#include <vector>

#include "2d/CCNode.h"
#include "2d/CCCamera.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderState.h"
#include "3d/CCAABB.h"
#include "3d/CCRay.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

/**
    the maximum amount of the chunkes
**/
#define MAX_CHUNKES 256

/** @class Terrain
    @brief @~english Defines a Terrain that is capable of rendering large landscapes from 2D heightmap images.
    Terrains can be constructed from several different internal formats heightmap sources:
     1. RGB888
     2. RGBA8888
     3. Luminance(gray-scale)8

     Terrain use TerrainData struct to initialize.the TerrainData struct warp
     all parameters that Terrain initialization need.
     TerrainData provide several handy constructor for users

    Surface detail is provided via texture splatting, where multiple Detail texture layers can be added
    along with alpha map to define how different Detail texture blend with each other. These DetailTexture
    can be defined in TerrainData. The number of supported Detail texture is Four. although typically 2-3 levels is
    sufficient. For simple usage ,surface detail also is provided via simple Texture.

    Internally, Terrain is divide into smaller, more manageable chunks, which can be culled
    separately for more efficient rendering. The size of the terrain chunks can be controlled
    via the chunkSize property in TerrainData.

    Chunks are managed under the QuadTree.As DE FACTO terminal Node of the QuadTree;
    let us cull chunks efficientlly to reduce drawCall amount And reduce the VBOs'Size that pass to the GPU.

    Level of detail (LOD) is supported using a technique that is similar to texture mipmapping -- called GeoMapping.
    A distance-to-camera based test used to decide
    the appropriate LOD for a terrain chunk. The number of LOD levels is 0 by default (which
    means only the base level is used),the maxium number of LOD levels is 4. Of course ,you can hack the value individually.

    Finally, when LOD is enabled, cracks can begin to appear between terrain Chunks of
    different LOD levels. An acceptable solution might be to simply reduce the lower LOD(high detail,smooth) chunks border,
    And let the higher LOD(rough) chunks to seamlessly connect it.

    We can use ray-terrain intersection to pick a point of the terrain;
    Also we can get an arbitrary point of the terrain's height and normal vector for convenience .
    @~chinese ����һ�����Σ����ܹ���2Dͼ��߶�ͼ���ɡ�
    ���ο��ԴӼ�����ͬ���ڲ���ʽ�߶�ͼ�����ɣ�
     1. RGB888
     2. RGBA8888
     3.���ȣ��Ҷȵȼ���8

    ����ϸ����ͨ�����ϸ�ڵ��������ʵ��
  **/
class CC_DLL Terrain : public Node
{
public:

    /** @~english the crack fix type. use to fix the gaps between different LOD chunks
        @~chinese �����޸����͡������޸���ͬLOD��֮��ļ�϶
    */
    enum class CrackFixedType
    {
        SKIRT,
        INCREASE_LOWER,
    };

    /**
     *DetailMap
     *this struct maintain a detail map data ,including source file ,detail size.
     *the DetailMap can use for terrain splatting
     **/
    struct CC_DLL DetailMap
    {
        /*Constructors*/
        DetailMap();
        DetailMap(const std::string& detailMapSrc, float size = 35);
        /*detail Image source file path*/
        std::string _detailMapSrc;
        /*detailMapSize determine how many tiles that Terrain represent*/
        float _detailMapSize;
    };

    /**
     * Triangle
     */
    struct Triangle
    {
        Triangle(Vec3 p1, Vec3 p2, Vec3 p3);
        bool getInsterctPoint(const Ray &ray, Vec3& interScetPoint) const;
        void transform(Mat4 matrix);
        Vec3 _p1, _p2, _p3;
    };


   /**
    *TerrainData
    *This TerrainData struct warp all parameter that Terrain need to create
    */
    struct CC_DLL TerrainData
    {
        /** @~english empty constructor
            @~chinese �յĹ��캯��
        */
        TerrainData();
        /** @~english constructor, this constructor construct a simple terrain which only have 1 detailmap
            @~chinese ���캯�����ù��캯������һ���򵥵ĵ��Σ�ֻ��1 detailmap
        */
        TerrainData(const char* heightMapsrc, const char* textureSrc, const Size& chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /** @~english constructor, this constructor construct a terrain which have 4 detailmaps, 1 alpha map
            @~chinese ���캯�����ù��캯������һ�����Σ���4��detailmaps��1��Alpha��ͼ
        */
        TerrainData(const char* heightMapsrc, const char* alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const DetailMap& detail4, const Size& chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /** @~english constructor, this constructor construct a terrain which have 3 detailmaps, 1 alpha map
            @~chinese ���캯�����ù��캯������һ�����Σ���3��detailmaps��1��Alpha��ͼ
        */
        TerrainData(const char* heightMapsrc, const char* alphamap, const DetailMap& detail1,const DetailMap& detail2, const DetailMap& detail3, const Size& chunksize = Size(32,32), float mapHeight = 2, float mapScale = 0.1);
        /** @~english deterimine the chunk size,chunk is the minimal subdivision of the Terrain
            @~chinese ȷ�����С�����ǵ��ε���Сϸ��
        */
        Size _chunkSize;
        /** @~english height Map source path
            @~chinese �߶�ͼ��Դ·��
        */
        std::string _heightMapSrc;
        /** @~english the source path of the alpha map
            @~chinese alphaͨ����ͼ��Դ·��
        */
        std::string _alphaMapSrc;
        /** @~english detail maps
            @~chinese ��ϸ�ĵ�ͼ
        */
        DetailMap _detailMaps[4];
        /** @~english terrain Maximum height
            @~chinese �������߶�
        */
        float _mapHeight;
        /** @~english terrain scale factor,you can combine setScale later.
            @~chinese �������ӣ�����Խ��setScale�Ժ�
        */
        float _mapScale;
        /** @~english the amount of detailmap
            @~chinese ��detailmap��
        */
        int _detailMapAmount;
        /** @~english the skirt height ratio, only effect when terrain use skirt to fix crack
            @~chinese ȹ�ߵĸ߶ȱȣ���������ʹ��ȹ�������޸��ѷ�ʱ��Ч
        */
        float _skirtHeightRatio;
    };
private:

    struct ChunkIndices
    {
        GLuint _indices;
        unsigned short _size;
    };

    struct ChunkLODIndices
    {
        int _relativeLod[5];
        ChunkIndices _chunkIndices;
    };


    struct ChunkLODIndicesSkirt
    {
        int _selfLod;
        ChunkIndices _chunkIndices;
    };

    /**
    *terrain vertices internal data format
    */
    struct CC_DLL TerrainVertexData
    {
        /*constructor*/
        TerrainVertexData() {};
        TerrainVertexData(Vec3 v1, Tex2F v2)
        {
            _position = v1;
            _texcoord = v2;
        };
        /*the vertex's attributes*/
        cocos2d::Vec3 _position;
        cocos2d::Tex2F _texcoord;
        cocos2d::Vec3 _normal;
    };

    struct CC_DLL QuadTree;
    /*
        the terminal node of quad, use to subdivision terrain mesh and LOD
    **/
    struct Chunk
    {
        /** @~english Constructor
            @~chinese ���캯��
        */
        Chunk();
        /** @~english destructor
            @~chinese ��������
        */
        ~Chunk();
        /*  @~english vertices
            @~chinese ����
        */
        std::vector<TerrainVertexData> _originalVertices;
        /*  @~english LOD indices
            @~chinese LOD����
        */
        struct LOD
        {
            std::vector<GLushort> _indices;
        };
        GLuint _vbo;
        ChunkIndices _chunkIndices;
        /** @~english we now support four levels of detail
            @~chinese ��������֧���ĸ��������ϸ
        */
        LOD _lod[4];
        /** @~english AABB in local space
            @~chinese �ھֲ��ռ�AABB
        */
        AABB _aabb;
        /** @~english setup Chunk data
            @~chinese �������ݿ�
        */
        void generate(int map_width, int map_height, int m, int n, const unsigned char* data);
        /** @~english calculateAABB
            @~chinese calculateaabb
        */
        void calculateAABB();
        /** @~english internal use draw function
            @~chinese �ڲ�ʹ�õĻ��ƺ���
        */
        void bindAndDraw();
        /** @~english finish opengl setup
            @~chinese OpenGL�������
        */
        void finish();
        /*  @~english use linear-sample vertices for LOD mesh
            @~chinese ʹ�����Բ���LOD���񶥵�
        */
        void updateVerticesForLOD();
        /*  @~english updateIndices
            @~chinese updateindices
        */
        void updateIndicesLOD();

        void updateIndicesLODSkirt();

        /** @~english calculate the average slop of chunk
            @~chinese ������ƽ��б��
        */
        void calculateSlope();

        bool getInsterctPointWithRay(const Ray& ray, Vec3 &interscetPoint);

        /** @~english current LOD of the chunk
            @~chinese ��ǰ�Ŀ�LOD
        */
        int _currentLod;

        int _oldLod;

        int _neighborOldLOD[4];
        /*the left,right,front,back neighbors*/
        Chunk* _left;
        Chunk* _right;
        Chunk* _front;
        Chunk* _back;

        QuadTree* _parent;

        /** @~english the position X in terrain space
            @~chinese λ��x�ڵ��οռ�
        */
        int _posX;
        /** @~english the position Y in terrain space
            @~chinese λ���ڵ��οռ�
        */
        int _posY;
        /** @~english parent terrain
            @~chinese ��ĸ�ĵ���
        */
        Terrain* _terrain;
        /** @~english chunk size
            @~chinese ��Ĵ�С
        */
        Size _size;
        /** @~english chunk's estimated slope
            @~chinese ����б�ʹ���ֵ
        */
        float _slope;
        std::vector<TerrainVertexData> _currentVertices;

        std::vector<Triangle> _trianglesList;
    };

    /**
        QuadTree
        @breif use to hierarchically frustum culling and set LOD
     **/
    struct CC_DLL QuadTree
    {
        /** @~english constructor
            @~chinese ���캯��
        */
        QuadTree(int x, int y, int width, int height, Terrain* terrain);
        /** @~english destructor
            @~chinese ��������
        */
        ~QuadTree();
        /** @~english recursively draw
            @~chinese �ݹ黭
        */
        void draw();
        /** @~english recursively set itself and its children is need to draw
            @~chinese �ݹ�Ļ����Լ������ĺ���
        */
        void resetNeedDraw(bool value);
        /** @~english recursively potential visible culling
            @~chinese �ݹ����ÿɼ���
        */
        void cullByCamera(const Camera* camera, const Mat4& worldTransform);
        /** @~english precalculate the AABB(In world space) of each quad
            @~chinese Ԥ�ȼ����AABB������ռ䣩
        */
        void preCalculateAABB(const Mat4& worldTransform);
        QuadTree* _tl;
        QuadTree* _tr;
        QuadTree* _bl;
        QuadTree* _br;

        bool _isTerminal;
        Chunk* _chunk;
        int _posX;
        int _posY;
        int _height;
        int _width;
        QuadTree* _parent;
        /** @~english AABB's cache (in local space)
            @~chinese AABB�Ļ��棨�ֲ��ռ䣩
        */
        AABB _localAABB;
        /** @~english AABB's cache (in world space)
            @~chinese AABB�Ļ��棨����ռ䣩
        */
        AABB _worldSpaceAABB;
        Terrain* _terrain;
        /** @~english  a flag determine whether a quadTree node need draw
            @~chinese һ����־ȷ���Ƿ���Ҫ�����Ĳ����ڵ�
        */
        bool _needDraw;
    };
    friend QuadTree;
    friend Chunk;
public:
    /** @~english set light map texture
        @~chinese ���ù�����ͼ
    */
    void setLightMap(const std::string& fileName);

    /** @~english set directional light for the terrain
        @~chinese ���õ��ι��յķ���
        @param lightDir @~english The direction of directional light, Note that lightDir is in the terrain's local space. Most of the time terrain is placed at (0,0,0) and without rotation, so lightDir is also in the world space.
                        @~chinese �����Դ�ĳ���ע��÷������ڵ��εľֲ��ռ䣬�����ڵ��δ󲿷�ʱ���Ƕ�������������ϵԭ�㣬����û����ת�����Կ��԰Ѹù�Դ������������������ϵ�С�
    */
    void setLightDir(const Vec3& lightDir);

    /*init function*/
    /** @~english initialize all Properties which terrain need
        @~chinese ��ʼ�����е�����Ҫ������
    */
    bool initProperties();

    /** @~english initialize heightMap data
        @~chinese �߶�ͼ���ݳ�ʼ��
    */
    bool initHeightMap(const std::string& heightMap);

    /** @~english initialize alphaMap ,detailMaps textures
        @~chinese ��ʼ��alphamap��detailmaps����
    */
    bool initTextures();

    /** @~english create and initialize terrain
        @~chinese �����ͳ�ʼ���ĵ���
        @param parameter @~english  all parameter that Terrain need to create @~chinese ����������Ҫ�����в���
        @param fixedType @~english  the crack fix type. use to fix the gaps between different LOD chunks @~chinese �����޸��ͣ������޸���ͬLOD��֮��ļ�϶
        @return @~english A initialized terrain which is marked as "autorelease @~chinese һ����ʼ���ĵ��α����Ϊ���Զ��ͷ�
    */
    static Terrain* create(TerrainData& parameter, CrackFixedType fixedType = CrackFixedType::INCREASE_LOWER);

    /** @~english get specified position's height mapping to the terrain,use bi-linear interpolation method
        @~chinese ��ȡָ��λ�õĸ߶�ӳ�䵽���Σ�ʹ��˫���Բ�ֵ����
        @param x @~english  the X position @~chinese X��λ��
        @param z @~english  the Z position @~chinese Zλ��
        @param normal @~english  the specified position's normal vector in terrain . if this argument is NULL or nullptr,Normal calculation shall be skip. @~chinese ��ָ��λ�õķ���ʸ�����Ρ�����������Ϊ�ջ�nullptr����������Ӧ������
        @return @~english the height value of the specified position of the terrain, if the (X,Z) position is out of the terrain bounds,it shall return 0; @~chinese ���ε�ָ��λ�õĸ߶�ֵ�������x��z��λ�õĵ��α߽磬��������0��
     **/
    float getHeight(float x, float z, Vec3 * normal= nullptr) const;

    /** @~english get specified position's height mapping to the terrain,use bi-linear interpolation method
        @~chinese ��ȡָ��λ�õĸ߶�ӳ�䵽���Σ�ʹ��˫���Բ�ֵ����
        @param pos @~english  the position (X,Z) @~chinese ��λ�ã�x��z��
        @param normal @~english  the specified position's normal vector in terrain . if this argument is NULL or nullptr,Normal calculation shall be skip. @~chinese ��ָ��λ�õķ���ʸ�����Ρ�����������Ϊ�ջ�nullptr����������Ӧ������
        @return @~english the height value of the specified position of the terrain, if the (X,Z) position is out of the terrain bounds,it shall return 0; @~chinese ���ε�ָ��λ�õĸ߶�ֵ�������x��z��λ�õĵ��α߽磬��������0��
     **/
    float getHeight(Vec2 pos, Vec3*Normal = nullptr) const;

    /** @~english get the normal of the specified pistion in terrain
        @~chinese �õ�ָ��λ�õķ���
        @return @~english the normal vector of the specified position of the terrain. @~chinese ���ε�ָ��λ�õķ�������
        @note the fast normal calculation may not get precise normal vector.
     **/
    Vec3 getNormal(int pixelX, int pixelY) const;

    /** @~english get height from the raw height filed
        @~chinese �õ��߶�
        @param pixelX @~english  the position of x in raw height @~chinese X��ԭ�߶ȵ�λ��
        @param pixelY @~english  the position of y in raw height @~chinese Y��ԭ�߶ȵ�λ��
        @return @~english the height of position(x,y) @~chinese λ�ã�x��y���ĸ߶�
    */
    float getImageHeight(int pixelX, int pixelY) const;

    /** @~english show the wireline instead of the surface,Debug Use only
        @~chinese ��ʾ�߿�ģʽ������ʹ��
        @param value @~english  the switching vale of method. @~chinese �������С�
        @Note only support desktop platform
     **/
    void setDrawWire(bool boolValue);

    /** @~english Set threshold distance of each LOD level,must equal or gereater than the chunk size
        @~chinese ÿ������������ֵ�ľ��룬������ڻ���ڿ��Сgereater
        @param lod1 @~english  the threshold of LOD level 1 @~chinese LOD 1����ֵ
        @param lod2 @~english  the threshold of LOD level 2 @~chinese LOD 2����ֵ
        @param lod3 @~english  the threshold of LOD level 3 @~chinese LOD 3����ֵ
        @Note when invoke initHeightMap, the LOD distance will be automatic calculated.
    */
    void setLODDistance(float lod1, float lod2, float lod3);

    /** @~english Switch frustum Culling Flag
        @~chinese ��׶�޳���־����
        @param boolValue @~english  the switching vale of method. @~chinese �������л�����
        @Note frustum culling will remarkable improve your terrain rendering performance.
    */
    void setIsEnableFrustumCull(bool boolValue);

    /** @~english  set the alpha map
        @~chinese ����alpha��ͼ
        @param newAlphaMapTexture @~english  a texture2d to be used as alpha map. @~chinese һ��Texture2D��Ϊ��-��ͼ��
    */
    void setAlphaMap(cocos2d::Texture2D* newAlphaMapTexture);

    /** @~english set the Detail Map
        @~chinese ������ϸ�ĵ�ͼ
        @param index @~english  the index of detailmap to be seted. @~chinese ��detailmapָ�����趨��
        @param detailMap @~english  the detailMap to be seted. @~chinese Ҫ������detailmap��
    */
    void setDetailMap(unsigned int index, DetailMap detailMap);

    // Overrides, internal use only
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

   /**
    * @~english Ray-Terrain intersection.
    * @~chinese ���ߵ����ཻ��
    * @param ray @~english  The ray used for intersection @~chinese �������ڽ����
    * @param intersectionPoint @~english Hit point if hitted. @~chinese ��������εĽ��㣨����н��㣩��
    * @return @~english true if hit, false otherwise. @~chinese ����true����н��㣬���򷵻�false��
    */
    bool getIntersectionPoint(const Ray & ray, Vec3 & intersectionPoint) const;

    /** @~english Ray-Terrain intersection.
        @~chinese ���ߵ����ཻ��
        @param ray @~english  the ray used for intersection @~chinese �������ڽ����
        @return @~english the intersection point @~chinese �����
    */
    Vec3 getIntersectionPoint(const Ray& ray) const;

    /** @~english set the MaxDetailAmount.
        @~chinese ����maxdetailamount��
        @param maxValue @~english  the maximum of detail map @~chinese ϸ��ͼ���
    */
    void setMaxDetailMapAmount(int maxValue);

    /** @~english Convert a world Space position (X,Z) to terrain space position (X,Z)
        @~chinese ��һ������ռ�λ�ã�x��z�����εĿռ�λ�ã�x��z��
        @param worldSpace @~english  a world space position will be converted @~chinese һ������ռ�λ�ý���ת��
        @return @~english a terrain space position @~chinese ���εĿռ�λ��
    */
    Vec2 convertToTerrainSpace(Vec2 worldSpace)const;

    /** @~english reset the heightmap data.
        @~chinese ��λ�߶�ͼ���ݡ�
        @param heightmap @~english  the new height map @~chinese �µĸ߶�ͼ
    */
    void resetHeightMap(const char* heightMap);

    /** @~english get the terrain's mininal height.
        @~chinese �õ����ε���С�߶ȡ�
        @return @~english the min height of map @~chinese ͼ����С�߶�
    */
    float getMinHeight();

    /** @~english get the terrain's maximum height.
        @~chinese �õ����ε����߶ȡ�
        @return @~english the max height of map @~chinese ��ͼ�����߶�
    */
    float getMaxHeight();

    /** @~english get the terrain's AABB(in world space)
        @~chinese �õ����ε�AABB������ռ䣩
        @return @~english the AABB of map @~chinese ��ͼ��AABB
    */
    AABB getAABB();

    /** @~english set the skirt height ratio
        @~chinese ��ȹ�ӵĸ߶ȱ�
        @param ratio @~english  the ratio of skirt height @~chinese ȹ���߶ȱ�
    */
    void setSkirtHeightRatio(float ratio);

    /** @~english get the terrain's quad tree which is also the root node.
        @~chinese �õ����ε��Ĳ����ĸ��ڵ㡣
        @return @~english the terrain's quad tree @~chinese ���ε��Ĳ���
    */
    QuadTree* getQuadTree();

    /** @~english reload sky box after GLESContext reconstructed.
        @~chinese ��պ�glescontext��װ���ؽ���
    */
    void reload();

    /** @~english get the terrain's size
        @~chinese �õ����εĴ�С
        @return @~english the size of terrain @~chinese ���εĴ�С
    */
    Size getTerrainSize() const { return Size(_imageWidth, _imageHeight); }

    /** @~english get the terrain's height data
        @~chinese �õ��ĵ��θ߶�����
        @return @~english the terrain's height data @~chinese ���θ߶�����
    */
    std::vector<float> getHeightData() const;

CC_CONSTRUCTOR_ACCESS:
    Terrain();
    virtual ~Terrain();
    bool initWithTerrainData(TerrainData &parameter, CrackFixedType fixedType);
protected:
    void onDraw(const Mat4 &transform, uint32_t flags);

    /** @~english recursively set each chunk's LOD
        @~chinese �ݹ������ÿ�����ο��LOD
        @param cameraPos @~english  the camera postion in world space @~chinese ������ռ��е������λ��
     **/
    void setChunksLOD(Vec3 cameraPos);

    /** @~english load Vertices from height filed for the whole terrain.
        @~chinese �Ӹ߶�ͼ���ص��ζ��㡣
     **/
    void loadVertices();

    /** @~english calculate Normal Line for each Vertex
        @~chinese ����ÿ������ķ���
     **/
    void calculateNormal();

    //override
    virtual void onEnter() override;

    /** @~english cache all unifrom loactions in GLSL.
        @~chinese ����GLSL������uniform��λ�á�
     **/
    void cacheUniformAttribLocation();

    //IBO generate & cache
    ChunkIndices lookForIndicesLODSkrit(int selfLod, bool* result);

    ChunkIndices lookForIndicesLOD(int neighborLod[4], int selfLod, bool* result);

    ChunkIndices insertIndicesLOD(int neighborLod[4], int selfLod, GLushort* indices, int size);

    ChunkIndices insertIndicesLODSkirt(int selfLod, GLushort * indices, int size);
    
    Chunk * getChunkByIndex(int x,int y) const;

protected:
    std::vector <ChunkLODIndices> _chunkLodIndicesSet;
    std::vector<ChunkLODIndicesSkirt> _chunkLodIndicesSkirtSet;
    Mat4 _CameraMatrix;
    bool _isCameraViewChanged;
    TerrainData _terrainData;
    bool _isDrawWire;
    unsigned char* _data;
    float _lodDistance[3];
    Texture2D * _detailMapTextures[4];
    Texture2D * _alphaMap;
    Texture2D * _lightMap;
    Vec3 _lightDir;
    CustomCommand _customCommand;
    QuadTree* _quadRoot;
    Chunk* _chunkesArray[MAX_CHUNKES][MAX_CHUNKES];
    std::vector<TerrainVertexData> _vertices;
    std::vector<unsigned int> _indices;
    int _imageWidth;
    int _imageHeight;
    Size _chunkSize;
    bool _isEnableFrustumCull;
    int _maxDetailMapValue;
    cocos2d::Image* _heightMapImage;
    Mat4 _oldCameraModelMatrix;
    Mat4 _terrainModelMatrix;
    GLuint _normalLocation;
    GLuint _positionLocation;
    GLuint _texcordLocation;
    float _maxHeight;
    float _minHeight;
    CrackFixedType _crackFixedType;
    float _skirtRatio;
    int _skirtVerticesOffset[4];
    GLint _detailMapLocation[4];
    GLint _alphaMapLocation;
    GLint _alphaIsHasAlphaMapLocation;
    GLint _lightMapCheckLocation;
    GLint _lightMapLocation;
    GLint _detailMapSizeLocation[4];
    GLint _lightDirLocation;
    RenderState::StateBlock* _stateBlock;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundListener;
#endif
};

// end of actions group
/// @}

NS_CC_END
#endif
