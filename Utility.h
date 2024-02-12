#pragma once
#include "main.h"
#include "render.h"
#include <vector>
#include"RenderInfo.h"
template<class VertexType = VERTEX_3D, class IndexType = DWORD>
struct MeshData
{
	std::vector<VertexType> vertexArray;
	std::vector<IndexType> IndexArray;
};
//---------------------------------------------------
//创建立方体
//--------------------------------------------------
//[in]width : 立方体的长
//[in]height : 立方体的高
//[in]depth : 立方体的宽
//[in]color : 颜色
//[in]orignPos : 坐标
MeshData<VERTEX_3D> CreateBox(float width, float height, float depth, const D3DXCOLOR& color, D3DXVECTOR3 orignPos = D3DXVECTOR3(0, 0, 0));