
bool print_test(){

    printf("testing util\n");
}
inline bool isPointableNode(const MapNode& n, Client *client, bool liquids_pointable)
{
	const ContentFeatures &features = client->getNodeDefManager()->get(n);
	return features.pointable ||
		(liquids_pointable && features.isLiquid());
}
PointedThing getPointedThing(Client *client, v3f player_position, v3f camera_direction, v3f camera_position,
        core::line3d<f32> shootline, f32 d,
        bool liquids_pointable,
        bool look_for_object,
        std::vector<aabb3f> &hilightboxes,
        ClientActiveObject *&selected_object)
{
	PointedThing result;

	hilightboxes.clear();
	selected_object = NULL;

	INodeDefManager *nodedef = client->getNodeDefManager();
	ClientMap &map = client->getEnv().getClientMap();

	// First try to find a pointed at active object
	if(look_for_object)
	{
		selected_object = client->getSelectedActiveObject(d*BS,
				camera_position, shootline);
		if(selected_object != NULL)
		{
			if(selected_object->doShowSelectionBox())
			{
				aabb3f *selection_box = selected_object->getSelectionBox();
				// Box should exist because object was
				// returned in the first place
				assert(selection_box);

				v3f pos = selected_object->getPosition();
				hilightboxes.push_back(aabb3f(
						selection_box->MinEdge + pos,
						selection_box->MaxEdge + pos));
			}

			result.type = POINTEDTHING_OBJECT;
			result.object_id = selected_object->getId();
			return result;
		}
	}

	// That didn't work, try to find a pointed at node

	f32 mindistance = BS * 1001;
	
	v3s16 pos_i = floatToInt(player_position, BS);

	/*infostream<<"pos_i=("<<pos_i.X<<","<<pos_i.Y<<","<<pos_i.Z<<")"
			<<std::endl;*/

	s16 a = d;
	s16 ystart = pos_i.Y + 0 - (camera_direction.Y<0 ? a : 1);
	s16 zstart = pos_i.Z - (camera_direction.Z<0 ? a : 1);
	s16 xstart = pos_i.X - (camera_direction.X<0 ? a : 1);
	s16 yend = pos_i.Y + 1 + (camera_direction.Y>0 ? a : 1);
	s16 zend = pos_i.Z + (camera_direction.Z>0 ? a : 1);
	s16 xend = pos_i.X + (camera_direction.X>0 ? a : 1);
	
	// Prevent signed number overflow
	if(yend==32767)
		yend=32766;
	if(zend==32767)
		zend=32766;
	if(xend==32767)
		xend=32766;

	for(s16 y = ystart; y <= yend; y++)
	for(s16 z = zstart; z <= zend; z++)
	for(s16 x = xstart; x <= xend; x++)
	{
		MapNode n;
		try
		{
			n = map.getNode(v3s16(x,y,z));
		}
		catch(InvalidPositionException &e)
		{
			continue;
		}
		if(!isPointableNode(n, client, liquids_pointable))
			continue;

		std::vector<aabb3f> boxes = n.getSelectionBoxes(nodedef);

		v3s16 np(x,y,z);
		v3f npf = intToFloat(np, BS);

		for(std::vector<aabb3f>::const_iterator
				i = boxes.begin();
				i != boxes.end(); i++)
		{
			aabb3f box = *i;
			box.MinEdge += npf;
			box.MaxEdge += npf;

			for(u16 j=0; j<6; j++)
			{
				v3s16 facedir = g_6dirs[j];
				aabb3f facebox = box;

				f32 d = 0.001*BS;
				if(facedir.X > 0)
					facebox.MinEdge.X = facebox.MaxEdge.X-d;
				else if(facedir.X < 0)
					facebox.MaxEdge.X = facebox.MinEdge.X+d;
				else if(facedir.Y > 0)
					facebox.MinEdge.Y = facebox.MaxEdge.Y-d;
				else if(facedir.Y < 0)
					facebox.MaxEdge.Y = facebox.MinEdge.Y+d;
				else if(facedir.Z > 0)
					facebox.MinEdge.Z = facebox.MaxEdge.Z-d;
				else if(facedir.Z < 0)
					facebox.MaxEdge.Z = facebox.MinEdge.Z+d;

				v3f centerpoint = facebox.getCenter();
				f32 distance = (centerpoint - camera_position).getLength();
				if(distance >= mindistance)
					continue;
				if(!facebox.intersectsWithLine(shootline))
					continue;

				v3s16 np_above = np + facedir;

				result.type = POINTEDTHING_NODE;
				result.node_undersurface = np;
				result.node_abovesurface = np_above;
				mindistance = distance;

				hilightboxes.clear();
				for(std::vector<aabb3f>::const_iterator
						i2 = boxes.begin();
						i2 != boxes.end(); i2++)
				{
					aabb3f box = *i2;
					box.MinEdge += npf + v3f(-d,-d,-d);
					box.MaxEdge += npf + v3f(d,d,d);
					hilightboxes.push_back(box);
				}
			}
		}
	} // for coords

	return result;
}
