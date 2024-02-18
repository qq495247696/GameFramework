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

    // ����(+X��)
    meshData.vertexArray[0].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (-h2), orignPos.z + (-d2));
    meshData.vertexArray[1].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[2].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[3].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (-h2), orignPos.z + (d2));
    // ����(-X��)
    meshData.vertexArray[4].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[5].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[6].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[7].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (-h2), orignPos.z + (-d2));
    // ����(+Y��)
    meshData.vertexArray[8].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[9].Position = D3DXVECTOR3(orignPos.x - w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[10].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[11].Position = D3DXVECTOR3(orignPos.x + w2, orignPos.y + (h2), orignPos.z + (-d2));
    // ����(-Y��)
    meshData.vertexArray[12].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (-d2));
    meshData.vertexArray[13].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[14].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[15].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (-d2));
    // ����(+Z��)
    meshData.vertexArray[16].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (d2));
    meshData.vertexArray[17].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[18].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (h2), orignPos.z + (d2));
    meshData.vertexArray[19].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (d2));
    // ����(-Z��)
    meshData.vertexArray[20].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (-h2), orignPos.z + (-d2));
    meshData.vertexArray[21].Position = D3DXVECTOR3(orignPos.x + (-w2), orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[22].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (h2), orignPos.z + (-d2));
    meshData.vertexArray[23].Position = D3DXVECTOR3(orignPos.x + (w2), orignPos.y + (-h2), orignPos.z + (-d2));

    for (UINT i = 0; i < 4; ++i)
    {
        // ����(+X��)
        meshData.vertexArray[i].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
        meshData.vertexArray[i].Diffuse = color;
        // ����(-X��)
        meshData.vertexArray[i + 4].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
        meshData.vertexArray[i + 4].Diffuse = color;
        // ����(+Y��)
        meshData.vertexArray[i + 8].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
        meshData.vertexArray[i + 8].Diffuse = color;
        // ����(-Y��)
        meshData.vertexArray[i + 12].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
        meshData.vertexArray[i + 12].Diffuse = color;
        // ����(+Z��)
        meshData.vertexArray[i + 16].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
        meshData.vertexArray[i + 16].Diffuse = color;
        // ����(-Z��)
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
       0, 1, 2, 2, 3, 0,        // ����(+X��)
       4, 5, 6, 6, 7, 4,        // ����(-X��)
       8, 9, 10, 10, 11, 8,    // ����(+Y��)
       12, 13, 14, 14, 15, 12,    // ����(-Y��)
       16, 17, 18, 18, 19, 16, // ����(+Z��)
       20, 21, 22, 22, 23, 20    // ����(-Z��)
    };
    return meshData;
}
