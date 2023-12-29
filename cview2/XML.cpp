#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <libxml\parser.h>
#include <libxml\tree.h>

constexpr auto USERNAME = "username";
constexpr auto USERPASS = "password";
constexpr auto USERGROUP = "group";
constexpr auto USERSTATUS = "status";

constexpr auto USERSTR = "users";
constexpr auto CONFIGSTR = "config";

constexpr auto CONFIG = 0;
constexpr auto USERS = 1;

constexpr auto ADD = 2;
constexpr auto DELETETYPE = 3;

class XMLParser {
private:
	std::string xmlFile;

	std::string username = "";
	std::string password = "";
	std::string group = "";
	std::string status = "";

	xmlDocPtr doc = nullptr;
	xmlNodePtr rootNode = nullptr;

	xmlNode* FindNode(xmlNode* node, int type, const char* param1, const char* param2 = "", const char* param3 = "") {
		switch (type) {
		case ADD:
			return AddFind(node, param1);
		case DELETETYPE:
			return DelFind(node, param1, param2);
		default:
			throw "XMLFinderWrongType";
		}
	}

	xmlNode* AddFind(xmlNode* node, const char* name) {
		xmlNode* result;

		if (node == NULL) return NULL;

		while (node) {
			if (xmlStrcmp(node->name, BAD_CAST name) == 0) {
				return node;
			}
			if (result = AddFind(node->children, name)) return result;
			node = node->next;
		}
		return NULL;
	}
	xmlNode* DelFind(xmlNode* node, const char* header, const char* content) {
		xmlNode* result;
		if (node == NULL) return NULL;
		while (node) {
			if (xmlStrcmp(node->name, BAD_CAST header) == 0
				&& (xmlStrcmp(node->children->children->children->content, BAD_CAST content) == 0)) return node->children;
			if (result = DelFind(node->children, header, content)) return result;
			node = node->next;
		}
		return NULL;
	}


public:

	XMLParser(const std::string& xmlFile) : xmlFile(xmlFile) {
		xmlInitParser();
		LIBXML_TEST_VERSION;
		doc = xmlReadFile(xmlFile.c_str(), "UTF-8", XML_PARSE_NOBLANKS);
		if (doc == nullptr) {
			throw "Error opening XML";
		}
		rootNode = xmlDocGetRootElement(doc)->children;
		if (rootNode == nullptr) {
			xmlFreeDoc(doc);
			throw "Error: No root node";
		}
	}
	~XMLParser() {
		xmlFreeDoc(doc);
		xmlCleanupParser();
	}

	void ReadConfig(int& authType, int& passwordPolicy, int& maxTries, int& timeout, int& maxPasswordLength, int& minPasswordLength) {
		xmlNode* node = FindNode(rootNode, ADD, CONFIGSTR);
	}

	void GetUserData(std::string& username, std::string& password, std::string& group, std::string& status ) {
		xmlNode* node = FindNode(rootNode, DELETETYPE, USERSTR, username.c_str());
		for (xmlNode wnode = node->children->next; i )
	}

};