#include "TileGrid.h"
TileGrid* TileGrid::_tileGridInstance = NULL;
TileGrid::TileGrid(){
	CurrentTileNumbers = new vector<int>();
	ObjectTiles = new vector<Tile>();
	RootQuadTree = NULL;
	QuadTree* _quadTree = new QuadTree();
	CurrentObjects = new map<int, GameObject*>();
	LoadObjectTileFromFile(FILEPATH_OBJECTTILE);

	LoadQuadtreeFromFile(FILEPATH_QUADTREE);
}
TileGrid* TileGrid::getInstance(){
	if (_tileGridInstance == NULL)
		_tileGridInstance = new TileGrid();
	return _tileGridInstance;
};
TileGrid::~TileGrid(){
}
void TileGrid::LoadObjectTileFromFile(string filePath){
	ifstream file(filePath);
	if (!file) {
		MessageBox(G_hWnd, strcat("Cannot open file:",filePath.c_str()), "Error", MB_OK);
		return;
	}

	//Read text in file

	//pretermit 3 first lines
	string line;
	getline(file, line);
	getline(file, line);
	getline(file, line);


	// import to matrix use world-coordinates type
	while (!file.eof())
	{
		getline(file, line);
		Tile* tile = new Tile(line);
		
		ObjectTiles->push_back(*tile);

	}
	file.close();
	
}
void TileGrid::LoadQuadtreeFromFile(string filePath){
	ifstream file(filePath);
	if (!file) {
		MessageBox(G_hWnd, strcat("Cannot open file:", filePath.c_str()), "Error", MB_OK);
		return;
	}

	//Read text in file

	//pretermit 1 first lines
	string line;
	getline(file, line);

	//creat 1 list contain all quadtree

	//map<int, QuadTree*>* quadTrees = new map<int, QuadTree*>();
	map<int, QuadTree*> quadTrees;
	// import quadtree from file
	//quadTree list
	while (!file.eof())
	{
		getline(file, line);
		QuadTree* quadTree = new QuadTree(line);
	/*	pair<int, QuadTree*> quadTreePair;
		quadTreePair.first = quadTree->getID();
		quadTreePair.second = quadTree;*/
		quadTrees.insert(pair<int, QuadTree*>(quadTree->ID, quadTree));
	}
	
	// specify child quadtree of all quadtree, begin at root quadtree
	RootQuadTree = specifyQuatreeChilds(quadTrees,0);
	
	file.close();

};
QuadTree* TileGrid::specifyQuatreeChilds(map<int, QuadTree*> quadTrees, int id){
	map<int, QuadTree*>::iterator it = quadTrees.find(id);
	QuadTree* quadTree = it->second;		//quadtree is identifed
	if (quadTree->ChildNodeCout)		//has child tree
	{
		quadTree->LeftTop = specifyQuatreeChilds(quadTrees, id * 10 + 1);
		quadTree->RightTop = specifyQuatreeChilds(quadTrees, id * 10 + 2);
		quadTree->LeftBottom= specifyQuatreeChilds(quadTrees, id * 10 + 3);
		quadTree->RightBottom = specifyQuatreeChilds(quadTrees, id * 10 + 4);
	}
	return quadTree;

}
void TileGrid::DeleteTileNumberInCurrentQuadTrees(int number){
	for (int i = 0; i < CurrentQuadTrees.size(); i++)
	{
		QuadTree* qt = CurrentQuadTrees.at(i);
		vector<int>& tileIDs = qt->ChildIndexs;
		auto it = tileIDs.begin();
		while (it != tileIDs.end())
		{
			if (*it == number)
			{
				it = tileIDs.erase(it);
			}
			else
				++it;
		}
	}
}
void TileGrid::UpdateCurrentTileNumbers(int x, int y){
	CurrentTileNumbers->clear();

	//insert tiles exist on screen to CurrentTile
	GetTileIDInQuadTree(x, y, RootQuadTree);
}
void TileGrid::UpdateCurrentTileNumbers(Camera* camera){
	CurrentTileNumbers->clear();

	//insert tiles exist on screen to CurrentTile
	GetTileIDInQuadTree(camera->_viewport.x, camera->_viewport.y, RootQuadTree);
}
bool TileGrid::isThisObjectIsOnThisQuadTree(GameObject* object, QuadTree* quadtree)
{
	RECT quadtreeRECT = { quadtree->XNode,										//left
							quadtree->YNode + quadtree->HeightNode 	,			//top
								quadtree->XNode + quadtree->WidthNode,			//right
									quadtree->YNode };							//bottom
	if (object->_posX >= quadtreeRECT.left
		&&object->_posX <= quadtreeRECT.right
		&&object->_posY <= quadtreeRECT.top
		&&object->_posY >= quadtreeRECT.bottom)
		return true;
	else
		return false;

}
void TileGrid::UpdateObjectInQuadTreeBaseOnPosition(Camera* camera)
{
	for (int i = 0; i < CurrentQuadTrees.size(); i++)
	{

		QuadTree* qt = CurrentQuadTrees.at(i);
		vector<int>& tileIDs = qt->ChildIndexs;
		for (int i = 0; i < tileIDs.size(); i++)
		{
			int TileNumber = tileIDs.at(i);

			auto it = CurrentObjects->find(TileNumber);
			GameObject* object = it->second;
			//check position
			if (object->getObjectID() != ObjectID::Ground_ID)
				//ground can't moving => don't need to check
			{
				
				if (!isThisObjectIsOnThisQuadTree(object, qt))
					//consider what quadtree is really containing this object
					// choose 1 in all current quadtrees, otherwise delete object, because this object move too far
				{
					//delete in this quadtree
					auto it = tileIDs.begin();
					while (it != tileIDs.end())
					{
						
						if (*it == TileNumber)
						{
							it = tileIDs.erase(it);
						}
						else
							++it;
					}


					//add to quadtree really containing
					bool hascontain;		//1ofall current quadtree has contain this object
					for (int i = 0; i < CurrentQuadTrees.size(); i++)
					{

						QuadTree* otherQTree = CurrentQuadTrees.at(i);
						if (isThisObjectIsOnThisQuadTree(object, otherQTree))
						{
							otherQTree->ChildIndexs.push_back(TileNumber);			//push back or push orderly?
							hascontain = true;
						}	
					}
					if (hascontain = false)
						//delete;
						;
				}
				
			}
		}
	}

	//auto it = CurrentObjects->begin();
	//while (it != CurrentObjects->end())
	//{
	//	int object_first = it->first;
	//	GameObject* object = it->second;
	//	//check object is destroy yet?
	//	if (object->getObjectID() != ObjectID::Ground_ID)
	//		//ground can't moving => don't need to check
	//	{
	//		//consider what quadtree is really containing this object
	//		
	//		for (int i = 0; i < CurrentQuadTrees.size(); i++)
	//		{
	//			QuadTree* qt = CurrentQuadTrees.at(i);
	//			vector<int> tileIDs = qt->ChildIndexs;
	//			if (thisObjectIsOnThisQuadTree(object, qt))
	//				//quadtree is really containing this object
	//			{
	//				//check was contained yet
	//				int i = 0;
	//				while (i < tileIDs.size() && object_first != tileIDs.at(i))
	//				{
	//					i++;
	//				}
	//				if (i == tileIDs.size()) //no element has value =
	//					//add
	//				{
	//					
	//				}
	//			}
	//		}
	//	}
	//	else
	//		++it;
	//}
}
void TileGrid::UpdateCurrentQuadTrees(Camera* camera)
{
	//save value
	vector<QuadTree*> OldQuadTrees = CurrentQuadTrees;
	//update
	CurrentQuadTrees.clear();
	CurrentNewInsideQuadTrees.clear();
	CurrentOutsideQuadTrees.clear();
	GetCurrentQuadTrees(camera->_viewport.x, camera->_viewport.y, RootQuadTree);

	//compare
	for (auto it = OldQuadTrees.begin(); it != OldQuadTrees.end(); it++)
	{
		//if (OldQuadTrees.size() == 0)
		//{
		//	break;
		//}
		int i = 0;
		while (i < CurrentQuadTrees.size() && *it != CurrentQuadTrees.at(i))
			i++;
		if (i == CurrentQuadTrees.size()) //no element in OldQuadTrees has value = it
										//add to outside
		{
			QuadTree* a = *it;
			CurrentOutsideQuadTrees.push_back(a);
		}

	}

	if (OldQuadTrees.size() == 0)
	{
		CurrentNewInsideQuadTrees = CurrentQuadTrees;
		return;
	}
		

	for (auto it = CurrentQuadTrees.begin(); it != CurrentQuadTrees.end(); it++)
	{
		if (OldQuadTrees.size() == 0)
		{
			CurrentNewInsideQuadTrees = CurrentQuadTrees;
			return;
		}
			
		int i = 0;
		while (i < OldQuadTrees.size() && *it != OldQuadTrees.at(i))
			i++;
		if (i == OldQuadTrees.size())	//no element in OldQuadTrees has value = it
										//add to new-inside
		{
			QuadTree* a= *it;
			CurrentNewInsideQuadTrees.push_back(a);
		}
			
	}
}

void TileGrid::UpdateCurrentObjects(Camera* camera){


	//ELEMENTS IN NEW_INSIDE => ADD
	for (int i = 0; i < CurrentNewInsideQuadTrees.size();i++)
	{
		QuadTree* qt = CurrentNewInsideQuadTrees.at(i);
		vector<int> tileIDs= qt->ChildIndexs;
		for (int i = 0; i < tileIDs.size(); i++)
		{
			int TileNumber = tileIDs.at(i);
			Tile objectTile = ObjectTiles->at(TileNumber);
			GameObject* ob = CreateObject(objectTile.ID, objectTile.X, objectTile.Y);

			CurrentObjects->insert(pair<int, GameObject*>(TileNumber, ob));
		}
	}
	//ELEMENT IS OUTSIDE OR IS DESTROY => DELETE
	//outside->delete
	for (int i = 0; i < CurrentOutsideQuadTrees.size(); i++)
	{
		QuadTree* qt = CurrentOutsideQuadTrees.at(i);
		vector<int> tileIDs = qt->ChildIndexs;
		for (int i = 0; i < tileIDs.size(); i++)
		{
			int TileNumber = tileIDs.at(i);

			auto it =CurrentObjects->find(TileNumber);
			GameObject* object = it->second;

			
			DeleteTileNumberInCurrentQuadTrees(it->first);
			CurrentObjects->erase(TileNumber);
			delete object;
			
		}
	}
	//if object status is destroy ->delete
	auto it = CurrentObjects->begin();
	while (it != CurrentObjects->end())
	{
		GameObject* object = it->second;
		//check object is destroy yet?
		if (object->getObjectStatus() == ObjectStatus::Died_OS)
		{//delete object and erase from CurrentObjects
			
			//if enemy->can give out item
			if (object->getObjectType() == ObjectType::Enemy_OT)
			{
				//probality:30%
				int random = rand() % 10 - 6;// random (-6->3)
				if (random>0) //=30%
					//give out item
				{
					HPTonic* hpTonic = new HPTonic(object->_posX, object->_posY);	//appear in position enemy was destroyed
					//add to currentObjectList
					TileGrid::AddObjectToCurrentObjectList(hpTonic);
				}
			}

			//if skree -> create bullet
			if (object->getObjectID()== ObjectID::Skree_ID 
				&&object->getHP()>0)	//die by accident (hurtle into ground)
			{
				//create bullet
				//bullet is appear at location skree was exploded
				Bullet* bullet = NULL;
				bullet = new Bullet(BulletType::BulletFromSkree, object->_posX, object->_posY, Direction::Left_Direction);
				//add to currentObjectList
				TileGrid::AddObjectToCurrentObjectList(bullet);
				bullet = new Bullet(BulletType::BulletFromSkree, object->_posX, object->_posY, Direction::TopLeft_Direction);
				TileGrid::AddObjectToCurrentObjectList(bullet);
				bullet = new Bullet(BulletType::BulletFromSkree, object->_posX, object->_posY, Direction::Top_Direction);
				TileGrid::AddObjectToCurrentObjectList(bullet);
				bullet = new Bullet(BulletType::BulletFromSkree, object->_posX, object->_posY, Direction::TopRight_Direction);
				TileGrid::AddObjectToCurrentObjectList(bullet);
				bullet = new Bullet(BulletType::BulletFromSkree, object->_posX, object->_posY, Direction::Right_Direction);
				TileGrid::AddObjectToCurrentObjectList(bullet);
			}
			//delte object
			DeleteTileNumberInCurrentQuadTrees(it->first);
			it = CurrentObjects->erase(it);
			delete object;
			
		}
		else
			++it;
	}
		

	
}
void TileGrid::Update(Camera* camera, int time){
	//Update object to match quadtree it is being on
	UpdateObjectInQuadTreeBaseOnPosition(camera);

	//update outside and newinside - quadtree
	UpdateCurrentQuadTrees(camera);

	//UpdateCurrentTileNumbers(camera);				//update tiles in viewport
	UpdateCurrentObjects(camera);

	//update position of all objects
	for (auto it = CurrentObjects->begin(); it != CurrentObjects->end(); it++)
	{
		GameObject* object = it->second;
			object->Update(time);
	}
}
void TileGrid::Update2(int time)
{
	for (auto it = CurrentObjects->begin(); it != CurrentObjects->end(); it++)
	{
		GameObject* object = it->second;
		object->Update2(time);
	}
}
void TileGrid::Draw(Camera* camera)
{
	for (auto it = CurrentObjects->begin(); it != CurrentObjects->end(); it++)
	{
		GameObject* object = it->second;
		object->Draw(camera);
		if (object->getObjectID() == ObjectID::BubbleDoor_ID)
			object->Draw(camera);
	}
}
void TileGrid::handleCollision(int playerX, int playerY, int deltaTime)
{

	for (auto it = CurrentObjects->begin(); it != CurrentObjects->end(); it++)
	{
		//find bullet object
		GameObject* object = it->second;

	
		if (object->getObjectStatus() != ObjectStatus::Survival_OS)	// then don't check collision
			continue;
		//else, check and handle
		switch (object->getObjectID())
			//check collision vs enemy and ground
		{
		case (ObjectID::Bullet_ID):

			object->handleCollision(*CurrentObjects, deltaTime);
			break;
		case ObjectID::Zoomer_ID:
		case ObjectID::Ripper_ID:
		case ObjectID::Zeb_ID:
		case ObjectID::Waver_ID:
			//check collision with ground
			object->handleCollision(*CurrentObjects, deltaTime);
			break;
		case ObjectID::Skree_ID:
		case ObjectID::Rio_ID:
			//check collision with ground
			object->handleCollision(*CurrentObjects, deltaTime);
			//motion base on player
			object->handleCollision(playerX, playerY, deltaTime);
			break;
		}
			
	}
}
GameObject* TileGrid::CreateObject(int id, int x, int y){

	ObjectIDFromFile obID = ObjectIDFromFile(id);
	GameObject* object;
	switch (obID){
	case ObjectIDFromFile::Ground_IDFF:
		object = new Ground(x, y);
		return object;
		break;
	case ObjectIDFromFile::Gate_IDFF:
		object = new Gate(x, y);
		return object;
		break;
	case ObjectIDFromFile::BubbleDoor_IDFF:
		object = new BubbleDoor(x, y);
		return object;
		break;
	case ObjectIDFromFile::Zoomer_IDFF:
		object = new Zoomer(x, y);
		return object;
		break;
	case ObjectIDFromFile::Zoomer2_IDFF:
		object = new Zoomer(x, y, 2);
		return object;
		break;
	case ObjectIDFromFile::Skree_IDFF:
		object = new Skree(x, y);
		return object;
		break;
	case ObjectIDFromFile::Skree2_IDFF:
		object = new Skree(x, y, 2);
		return object;
		break;
	case ObjectIDFromFile::MaruMari_IDFF:
		object = new MaruMari(x, y);
		return object;
		break;
	}
};

void TileGrid::AddObjectToCurrentObjectList(GameObject* object)
{
	map<int, GameObject*>* currentObjects = TileGrid::getInstance()->getCurrentObjects();
	int key = 10000; //usually object number <10000.
	while (currentObjects->count(key)) // existed
		key++;
	//insert object with the key
	currentObjects->insert(pair<int, GameObject*>(key, object));
}
map<int, GameObject*>* TileGrid::getCurrentObjects(){
	return CurrentObjects;
};
void TileGrid::GetTileIDInQuadTree(int x, int y, QuadTree* quadTree){
	if (quadTree->ChildNodeCout)		//has child tree
	{
		GetTileIDInQuadTree(x, y, quadTree->LeftTop);
		GetTileIDInQuadTree(x, y, quadTree->RightTop);
		GetTileIDInQuadTree(x, y, quadTree->LeftBottom);
		GetTileIDInQuadTree(x, y, quadTree->RightBottom);
	}
	Box cameraBox = Box(x, y, _screenWidth, -_screenHeight);
	Box quadTreeBox = Box(quadTree->XNode, quadTree->YNode, quadTree->WidthNode, quadTree->HeightNode);
	if (isCollide(cameraBox, quadTreeBox))			//has overlap together			
		//import tile
		for (vector<int>::iterator index = quadTree->ChildIndexs.begin(); index != quadTree->ChildIndexs.end(); index++)
		{
			CurrentTileNumbers->push_back(*index);
		}
}
void TileGrid::GetCurrentQuadTrees(int x, int y, QuadTree* quadTree){
	if (quadTree->ChildNodeCout)		//has child tree
	{
		GetCurrentQuadTrees(x, y, quadTree->LeftTop);
		GetCurrentQuadTrees(x, y, quadTree->RightTop);
		GetCurrentQuadTrees(x, y, quadTree->LeftBottom);
		GetCurrentQuadTrees(x, y, quadTree->RightBottom);
	}
	else	//child QuadTree
	{
		Box cameraBox = Box(x, y, _screenWidth, -_screenHeight);
		Box quadTreeBox = Box(quadTree->XNode, quadTree->YNode, quadTree->WidthNode, quadTree->HeightNode);
		if (isCollide(cameraBox, quadTreeBox))			//has overlap together		
			CurrentQuadTrees.push_back(quadTree);
	}
	
};