// TestClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	xml_t xml;
	LoadConfig(&xml);
	xmlNode_t* root = xml.FirstChildElement("App")->FirstChildElement("Contents");
	if (!root)
	{
		cout << "not exist process setting" << endl;
	}
	xmlNode_t* node = root->FirstChildElement("ThreadCount");
	int processCount = 0;
	node->GetText();
	sscanf_s(node->GetText(), "%d", &processCount);

	//node = xml.FirstChild()->FirstChild();
	//xml.FirstChild();
	//TiXmlNode* node = xml.FirstChild("Worksheet ss:Name=\"Sheet1\"");
	

	
    return 0;
}

