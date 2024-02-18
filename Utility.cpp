/*********************************************************************
 * \file   Utility.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 18
 *********************************************************************/
#include "Utility.h"

MeshData<VERTEX_3D> CreateBox(float width, float height, float depth, const D3DXCOLOR& color, D3DXVECTOR3 orignPos)
{
    MeshData<VERTEX_3D> meshData;
    meshData.vertexArray.resize(24);

    float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

    // 右面(+X面)
    meshData.vertexArray[0].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (-h2), orignPos.z + (-d2));
    meshData.vertexArray[1].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[2].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[3].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (-h2), orignPos.z + (d2));
    // 左面(-X面)
    meshData.vertexArray[4].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[5].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[6].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[7].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (-h2), orignPos.z + (-d2));
    // 顶面(+Y面)
    meshData.vertexArray[8].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[9].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[10].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[11].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (-d2));
    // 底面(-Y面)
    meshData.vertexArray[12].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (-d2));
    meshData.vertexArray[13].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[14].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[15].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (-d2));
    // 背面(+Z面)
    meshData.vertexArray[16].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[17].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[18].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[19].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (d2));
    // 正面(-Z面)
    meshData.vertexArray[20].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (-d2));
    meshData.vertexArray[21].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[22].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[23].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (-d2));

    for (UINT i = 0; i < 4; ++i)
    {
        // 右面(+X面)
        meshData.vertexArray[i].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
        meshData.vertexArray[i].Diffuse = color;
        // 左面(-X面)
        meshData.vertexArray[i + 4].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
        meshData.vertexArray[i + 4].Diffuse = color;
        // 顶面(+Y面)
        meshData.vertexArray[i + 8].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
        meshData.vertexArray[i + 8].Diffuse = color;
        // 底面(-Y面)
        meshData.vertexArray[i + 12].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
        meshData.vertexArray[i + 12].Diffuse = color;
        // 背面(+Z面)
        meshData.vertexArray[i + 16].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
        meshData.vertexArray[i + 16].Diffuse = color;
        // 正面(-Z面)
        meshData.vertexArray[i + 20].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
        meshData.vertexArray[i + 20].Diffuse = color;
    }

    for (UINT i = 0; i < 6; ++i)
    {
        meshData.vertexArray[i * 4].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
        meshData.vertexArray[i * 4 + 1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
        meshData.vertexArray[i * 4 + 2].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
        meshData.vertexArray[i * 4 + 3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
    }

    meshData.IndexArray = {
       0, 1, 2, 2, 3, 0,        // 右面(+X面)
       4, 5, 6, 6, 7, 4,        // 左面(-X面)
       8, 9, 10, 10, 11, 8,    // 顶面(+Y面)
       12, 13, 14, 14, 15, 12,    // 底面(-Y面)
       16, 17, 18, 18, 19, 16, // 背面(+Z面)
       20, 21, 22, 22, 23, 20    // 正面(-Z面)
    };
    return meshData;
}
