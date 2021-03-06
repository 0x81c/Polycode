/*
 Copyright (C) 2011 by Ivan Safrin
 
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
*/

#include "PolySceneLine.h"
#include "PolyRenderer.h"

using namespace Polycode;

SceneLine::SceneLine(Vector3 start, Vector3 end) : SceneMesh(Mesh::LINE_MESH) {
	this->ent1 = NULL;
	this->ent2 = NULL;
	this->start = start;
	this->end = end;	
	initLine();
	ignoreParentMatrix = false;
}

SceneLine::SceneLine(Entity *ent1, Entity *ent2) : SceneMesh(Mesh::LINE_MESH) {
	this->ent1 = ent1;
	this->ent2 = ent2;	
	initLine();
	ignoreParentMatrix = true;

}

void SceneLine::initLine() {
	mesh->addVertex(0,0,0,0,0);
	mesh->addVertex(0,0,0,1,0);
	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;		
}

SceneLine *SceneLine::SceneLineWithPositions(Vector3 start, Vector3 end) {
	return new SceneLine(start, end);
}

SceneLine::~SceneLine() {
}

void SceneLine::setStart(Vector3 start) {
	this->start = start;
}

void SceneLine::setEnd(Vector3 end) {
	this->end = end;
}

void SceneLine::Update(){

	Vector3 v1;
	Vector3 v2;
	
	if(ent1 != NULL && ent2 != NULL) {
		v1 = ent1->getConcatenatedMatrix().getPosition();
		v2 = ent2->getConcatenatedMatrix().getPosition();
        mesh->getVertex(0)->set(v1.x,v1.y,v1.z);
        mesh->getVertex(1)->set(v2.x,v2.y,v2.z);
	} else {
		v1 = start;
		v2 = end;
        mesh->getVertex(0)->set(v1.x,v1.y*yAdjust,v1.z);
        mesh->getVertex(1)->set(v2.x,v2.y*yAdjust,v2.z);
	}
	
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
}