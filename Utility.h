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
//����������
//--------------------------------------------------
//[in]width : ������ĳ�
//[in]height : ������ĸ�
//[in]depth : ������Ŀ�
//[in]color : ��ɫ
//[in]orignPos : ����
MeshData<VERTEX_3D> CreateBox(float width, float height, float depth, const D3DXCOLOR& color, D3DXVECTOR3 orignPos = D3DXVECTOR3(0, 0, 0));