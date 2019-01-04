///////////////////////////////////////////////////////////////////////////////
// secxmlcore.cpp : SFL XML package
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Daniel Jebaraj       
// Description: XML read/write helper classes
//

// [VC7] All Ptr classes in the COM dll "msxml.dll"
// were giving ambigous class errors. This is because
// the smart pointer definitions are in msml.dll under
// MSXML namespace and also in comdefsp.h under VC7\include.
// To solve the problem, all Ptr classes such as IXMLDOMNodePtr
// are reference explicitly to one under MSXML namespace.

#define _OG_EXPORT_IMPL

#include "stdafx.h"
#include "grid\secxmlcore.h"

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

using namespace std;

#ifdef NTDDI_VERSION
	//---------------------------------------------------------------
	// NOTE: msxml.h is no longer used on the Windows Vista platform. 
	// Use msxml6.h instead. 
	// 
	// To use MSXML6, make sure that NTDDI_VERSION is defined as 
	// NTDDI_VISTA on Windows Vista platforms and that the MSXML6 SDK 
	// is installed and pathed correctly. 
	//---------------------------------------------------------------
	#if NTDDI_VERSION >= NTDDI_VISTA
		#include <msxml6.h>
	#else
		using namespace MSXML;
	#endif
#else
	using namespace MSXML;
#endif


using namespace rw;

#pragma warning (disable: 4329 4510 4610 4786)

// Helper functions declaration and implementation
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
IXMLDOMNodePtr SECCreateDOMNode(::IXMLDOMDocument* pDoc, // the XML document to use 
									DOMNodeType type, // the type of the node
									BSTR bstrName, BSTR bstrNameSpace = _bstr_t()) // the name of the node (to be used for creation)
	#else
	MSXML::IXMLDOMNodePtr SECCreateDOMNode(MSXML::IXMLDOMDocument* pDoc, // the XML document to use 
										   DOMNodeType type, // the type of the node
										   BSTR bstrName, BSTR bstrNameSpace = _bstr_t()) // the name of the node (to be used for creation)
	#endif
#else
MSXML::IXMLDOMNodePtr SECCreateDOMNode(MSXML::IXMLDOMDocument* pDoc, // the XML document to use 
									   DOMNodeType type, // the type of the node
									   BSTR bstrName, BSTR bstrNameSpace = _bstr_t()) // the name of the node (to be used for creation)
#endif
{
    VARIANT vtype;
	vtype.vt = VT_I4;
    
	if(type == NODE_TEXT || type == NODE_CDATA_SECTION)
		type = NODE_ELEMENT;
	
	V_I4(&vtype) = (int)type;

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		IXMLDOMNodePtr p = NULL;
		pDoc->createNode(vtype, bstrName, bstrNameSpace, &p);
	#else
		MSXML::IXMLDOMNodePtr p = NULL;
		p = pDoc->createNode(vtype, bstrName, bstrNameSpace);
	#endif
#else
	MSXML::IXMLDOMNodePtr p = NULL;
	p = pDoc->createNode(vtype, bstrName, bstrNameSpace);
#endif

	return p;
}

// This function will be called recursively to complete the write process for the entire map
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
bool ResolveAndWriteEntries(::IXMLDOMDocument* pDocCreate, // The document to be used for creating nodes
						::IXMLDOMNode* pDoc, // the node that will hold the children that we create for this run
						const XML_ENTRY_MAP* pEntries, // map entries --->  Recurse and write all entries that are nested below this level
						IXMLWrite* pWrite) // XML write interface. This supplies the map and also access to the data
	#else
	bool ResolveAndWriteEntries(MSXML::IXMLDOMDocument* pDocCreate, // The document to be used for creating nodes
								MSXML::IXMLDOMNode* pDoc, // the node that will hold the children that we create for this run
								const XML_ENTRY_MAP* pEntries, // map entries --->  Recurse and write all entries that are nested below this level
								IXMLWrite* pWrite) // XML write interface. This supplies the map and also access to the data
	#endif
#else
bool ResolveAndWriteEntries(MSXML::IXMLDOMDocument* pDocCreate, // The document to be used for creating nodes
							MSXML::IXMLDOMNode* pDoc, // the node that will hold the children that we create for this run
							const XML_ENTRY_MAP* pEntries, // map entries --->  Recurse and write all entries that are nested below this level
							IXMLWrite* pWrite) // XML write interface. This supplies the map and also access to the data
#endif
{
	if(pEntries == NULL)
		return true;
	
	// now I will attempt to get the resolver for this. The resolver is a feedback/information gathering interface
	IXMLRWResolver* pResolver = pWrite->GetResolver();
	
	if(pResolver == NULL)
	{
		TRACE0("SECXML warning!:Unable to locate resolver. Have you forgotten to create a default resolver?");
		return false;
	}

	bool bContinue(true);
	bool bRetval(true);
	bool bGetValue(true);

	// OnStartWriteLoop will be called only the first time that we hit a level
	// you can use this call to setup any data that you need to go through the traversal
	eTypeSeen seen(eNotSeen);	
	
	if((seen = pWrite->IsFirstLoop(pEntries->dwID)) == eNotSeen ||
		(seen == eOk))
	{
		if( (bContinue = pResolver->OnStartWriteLoop(pEntries) )== false)
		{
			pWrite->MarkAsSeen(pEntries->dwID, eRefused);
				return true;
		}
		else
			pWrite->MarkAsSeen(pEntries->dwID, eOk);
	}
	else if(seen == eRefused) // no more traversal for this node
		return true;
	

	while (bContinue)
	{
		XMLVALUE value;
		
		if(pEntries->dwID == SECENTRYROOTID)
		{
			if(pEntries->listXMLMapEntries_p.empty() == false)
			{
				// recurse and build the tree
				XML_ENTRY_MAP::CXMLList::const_iterator it;
				
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				IXMLDOMNodePtr ptrNode = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t(pEntries->pszName), pEntries->pszNameSpace == NULL ? _bstr_t():_bstr_t(pEntries->pszNameSpace));
	#else
				MSXML::IXMLDOMNodePtr ptrNode = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t(pEntries->pszName), pEntries->pszNameSpace == NULL ? _bstr_t():_bstr_t(pEntries->pszNameSpace));
	#endif
#else
				MSXML::IXMLDOMNodePtr ptrNode = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t(pEntries->pszName), pEntries->pszNameSpace == NULL ? _bstr_t():_bstr_t(pEntries->pszNameSpace));
#endif
	
				if(ptrNode == NULL)
				{
					TRACE0("SECXML warning!:Unable to create node.\n");
					return false;
				}

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				::IXMLDOMNode *pOutNode = NULL;
					pDoc->appendChild(ptrNode, &pOutNode);
	#else
					pDoc->appendChild(ptrNode);
	#endif
#else
				pDoc->appendChild(ptrNode);
#endif
		
				
				it = pEntries->listXMLMapEntries_p.begin();
				
				if(it != pEntries->listXMLMapEntries_p.end())
				{
					bRetval = bRetval && ResolveAndWriteEntries(pDocCreate, pDoc, (*it), pWrite );
					return bRetval;
				}
				else
					return false;
			}
			else
				bContinue = false;

		}
		else if( pEntries->entryType == NODE_ATTRIBUTE)
		{
			bGetValue = pResolver->OnGetValue(pEntries, pDoc, value);
		
			bContinue = false;

			if(bGetValue == false)
				continue;
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				IXMLDOMElementPtr elem = pDoc;
	#else
				MSXML::IXMLDOMElementPtr elem = pDoc;
	#endif
#else
			MSXML::IXMLDOMElementPtr elem = pDoc;
#endif
			ASSERT(elem != NULL); // if this ASSERT triggers check your map. You have an incorrect sequence.
			elem->setAttribute(_bstr_t(pEntries->pszName), _variant_t((LPCTSTR)value));
			
			value.Recycle();
		}
		else if(pEntries->entryType == __NODE_ENTITY_REFERENCE_ATTRIB)
		{
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				IXMLDOMAttributePtr ptrNode = SECCreateDOMNode(pDocCreate, NODE_ATTRIBUTE, _bstr_t(pEntries->pszName));
	#else
				MSXML::IXMLDOMAttributePtr ptrNode = SECCreateDOMNode(pDocCreate, NODE_ATTRIBUTE, _bstr_t(pEntries->pszName));
	#endif
#else
			MSXML::IXMLDOMAttributePtr ptrNode = SECCreateDOMNode(pDocCreate, NODE_ATTRIBUTE, _bstr_t(pEntries->pszName));
#endif
	
			if(ptrNode == NULL)
			{
				TRACE0("SECXML warning!:Unable to create node.\n");
				return false;
			}

			bGetValue = pResolver->OnGetValue(pEntries, pDoc, value);
			
			ASSERT(bGetValue); // there should be a value specified in this context
			
			if(bGetValue == false)
			{
				bContinue = false;
				continue;
			}

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA 
				IXMLDOMNodePtr ptrNodeEntity = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t((LPCTSTR)value));
	#else
				MSXML::IXMLDOMNodePtr ptrNodeEntity = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t((LPCTSTR)value));
	#endif
#else
			MSXML::IXMLDOMNodePtr ptrNodeEntity = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t((LPCTSTR)value));
#endif
			
			if(ptrNodeEntity == NULL)
			{
				TRACE0("SECXML warning!:Unable to create node.\n");
				return false;
			}

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
			::IXMLDOMNode* pNodeOut = NULL;
			ptrNode->appendChild(ptrNodeEntity, &pNodeOut);
	#else
			ptrNode->appendChild(ptrNodeEntity);
	#endif
#else
		ptrNode->appendChild(ptrNodeEntity);
#endif

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				IXMLDOMElementPtr elem = pDoc;
	#else
				MSXML::IXMLDOMElementPtr elem = pDoc;
	#endif
#else
			MSXML::IXMLDOMElementPtr elem = pDoc;
#endif
			ASSERT(elem != NULL);
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				::IXMLDOMAttribute* pOutNode = NULL;
				elem->setAttributeNode(ptrNode, &pOutNode);
	#else
				elem->setAttributeNode(ptrNode);
	#endif
#else
			elem->setAttributeNode(ptrNode);
#endif

			bContinue = false;
			continue;
		}
		else
		{
			bGetValue = pResolver->OnGetValue(pEntries, pDoc, value);
			
			if(bGetValue == false)
			{
				bContinue = false;
				continue;
			}

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				::IXMLDOMNodePtr ptrNode = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t(pEntries->pszName), pEntries->pszNameSpace == NULL ? _bstr_t():_bstr_t(pEntries->pszNameSpace));
	#else
				MSXML::IXMLDOMNodePtr ptrNode = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t(pEntries->pszName), pEntries->pszNameSpace == NULL ? _bstr_t():_bstr_t(pEntries->pszNameSpace));
	#endif
#else
			MSXML::IXMLDOMNodePtr ptrNode = SECCreateDOMNode(pDocCreate, pEntries->entryType, _bstr_t(pEntries->pszName), pEntries->pszNameSpace == NULL ? _bstr_t():_bstr_t(pEntries->pszNameSpace));
#endif
	
			if(ptrNode == NULL)
			{
				TRACE0("SECXML warning!:Unable to create node.\n");
				return false;
			}
		
			if(	(pEntries->entryType == NODE_TEXT
				|| pEntries->entryType == NODE_COMMENT
				|| pEntries->entryType == NODE_DOCUMENT_TYPE
				)
				&& value != NULL)
			{
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
					ptrNode->put_text(_bstr_t(value));
	#else
					ptrNode->Puttext(_bstr_t(value));
	#endif
#else
				ptrNode->Puttext(_bstr_t(value));
#endif
			}
				
			value.Recycle();
		
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
			::IXMLDOMNode* pOutNode = NULL;
			pDoc->appendChild(ptrNode, &pOutNode);
	#else
			pDoc->appendChild(ptrNode);
	#endif
#else
			pDoc->appendChild(ptrNode);
#endif

			if(pEntries->entryType == NODE_COMMENT)
			{
				bContinue = false;
				continue;
			}

			if(pEntries->listXMLMapEntries_p.empty() == false)
			{
				// recurse and build the tree
				XML_ENTRY_MAP::CXMLList::const_iterator it;
			
				for (it = pEntries->listXMLMapEntries_p.begin(); bRetval && it != pEntries->listXMLMapEntries_p.end(); it++)
					bRetval = bRetval && ResolveAndWriteEntries(pDocCreate, ptrNode, (*it), pWrite );
			}

			bContinue = pResolver->OnCanContinueWriteLoop(pEntries, ptrNode);
		}
	}

	pResolver->OnEndWriteLoop(pEntries);

	return bRetval;
}

// Initialize for Read

/*
	NODE_CDATA_SECTION The literal string "#cdata-section". 
	NODE_COMMENT The literal string "#comment". 
	NODE_DOCUMENT The literal string "#document". 
	NODE_DOCUMENT_FRAGMENT The literal string "#document-fragment". 
	NODE_TEXT The literal string "#text". 
*/

const TCHAR* __SEC_LIT_NODE_CDATA_SECTION			=_T("#cdata-section");
const TCHAR* __SEC_LIT_NODE_COMMENT					=_T("#comment");
const TCHAR* __SEC_LIT_NODE_DOCUMENT				=_T("#document");
const TCHAR* __SEC_LIT_NODE_DOCUMENT_FRAGMENT		=_T("#document-fragment");
const TCHAR* __SEC_LIT_NODE_TEXT					=_T("#text");
const TCHAR* __SEC_LIT_ROOT							=_T("root#document");

#pragma warning (push)
#pragma warning (disable: 4239)

bool InitializeForRead(const XML_ENTRY_MAP* pEntries, // map entries 
						CMapSlots& slotMap, // map that holds the ids for all the different paths	
						secxmlstring& _strPath // path of the node
						)
{
	if(pEntries == NULL)
		return true;
	
	secxmlstring strPath;
	
	// initialize ths slot map for this node
	strPath += _strPath;

	if(pEntries->dwID == SECENTRYROOTID)
		strPath += __SEC_LIT_ROOT;
	else
	{
		switch (pEntries->entryType)
		{
			case NODE_CDATA_SECTION:
				strPath += __SEC_LIT_NODE_CDATA_SECTION;		
				break;
			case NODE_COMMENT:
				strPath += __SEC_LIT_NODE_COMMENT;
				break;
			case NODE_DOCUMENT:
				strPath += __SEC_LIT_NODE_DOCUMENT;
				break;
			case NODE_DOCUMENT_FRAGMENT:
				strPath += __SEC_LIT_NODE_DOCUMENT_FRAGMENT;
				break;
			case NODE_TEXT:
				{
					strPath += pEntries->pszName;
					strPath += __SEC_LIT_NODE_TEXT;
					break;
				}
			default:
				strPath += pEntries->pszName;
		}	
	}

	slotMap[strPath] = pEntries;

	TRACE2("Initialize for read. Slot map entry at %s is %x\n", (LPCTSTR)strPath.data(), pEntries->dwID);

	bool bRetval(true);
	bool bAddNumType(false);
	WORD wNumChild(0);

	TCHAR _pszConv[SECXMLDEFBUFSIZE];

	// loop through the children
	if(pEntries->listXMLMapEntries_p.empty() == false)
	{
		// recurse and build the tree
		XML_ENTRY_MAP::CXMLList::const_iterator it;
			
		for (it = pEntries->listXMLMapEntries_p.begin(); bRetval && it != pEntries->listXMLMapEntries_p.end(); it++)
		{
			if((*it)->entryType == NODE_CDATA_SECTION
				|| (*it)->entryType == NODE_COMMENT
				|| (*it)->entryType == NODE_DOCUMENT
				|| (*it)->entryType == NODE_DOCUMENT_FRAGMENT
				)
					bAddNumType = true;
				else
					bAddNumType = false;
				
			if(bAddNumType)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_itot(wNumChild, _pszConv, 10);
				wNumChild++;
				bRetval = bRetval && InitializeForRead((*it), slotMap, strPath + _pszConv);
			}
			else
				bRetval = bRetval && InitializeForRead((*it), slotMap, strPath);
		}
	}	
	
	return bRetval;
}

// Loop through all the elements in a loaded XML document
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		bool LoopTree(IXMLDOMNodePtr node, const secxmlstring& strPrevLevelPath, IXMLRead* pXMLRead)
	#else
		bool LoopTree(MSXML::IXMLDOMNodePtr node, const secxmlstring& strPrevLevelPath, IXMLRead* pXMLRead)
	#endif
#else
	bool LoopTree(MSXML::IXMLDOMNodePtr node, const secxmlstring& strPrevLevelPath, IXMLRead* pXMLRead)
#endif
{
    XMLVALUE xmlvalue;
	eTypeSeen seen(eNotSeen);
	
	ASSERT(pXMLRead != NULL);
	
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		IXMLDOMNodePtr pChild, pNext;
		IXMLDOMNamedNodeMapPtr pattrs;
	#else
		MSXML::IXMLDOMNodePtr pChild, pNext;
		MSXML::IXMLDOMNamedNodeMapPtr pattrs;
	#endif
#else
	MSXML::IXMLDOMNodePtr pChild, pNext;
	MSXML::IXMLDOMNamedNodeMapPtr pattrs;
#endif

	secxmlstring strPath;
	strPath += strPrevLevelPath;

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		CComBSTR bstrname;
        node->get_nodeName(&bstrname);
        strPath += (_bstr_t)bstrname; 

	#else
		_bstr_t bstrname = node->GetnodeName();
		strPath += bstrname;
	#endif
#else
	_bstr_t bstrname = node->GetnodeName();
	strPath += bstrname;
#endif
    
#ifdef _DEBUG
	//afxDump << "\n";
	//afxDump << strPath.data();
	//afxDump << "\n";
#endif
	
	// get the resolver
	IXMLRWResolver* pResolver = pXMLRead->GetResolver();
	
	ASSERT(pResolver != NULL);

	if(pResolver == NULL)
		return false;

	// get the id for this path
	const XML_ENTRY_MAP* pEntries = pXMLRead->LocateEntry(strPath);
	
	if(pEntries != NULL &&
				( (seen = pXMLRead->IsFirstLoop(pEntries->dwID)) == eNotSeen ) ||
				(seen == eOk)
				)
			
			{
				if(pResolver->OnStartReadLoop(pEntries) == false)
				{
					pXMLRead->MarkAsSeen(pEntries->dwID, eRefused);
					return true;
				}
				else
					pXMLRead->MarkAsSeen(pEntries->dwID, eOk);
			}
			else if(pEntries != NULL && seen == eRefused)
				return true;
			

	DOMNodeType nodetype; 

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		node->get_nodeType(&nodetype);
		node->get_attributes(&pattrs); // MSXML6
	#else
		node->GetnodeType();
		pattrs = node->Getattributes();
	#endif
#else
	node->GetnodeType();
	pattrs = node->Getattributes();
#endif

	if (pattrs != NULL)
    {

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
        pattrs->nextNode(&pChild);
	#else
		pChild = pattrs->nextNode();
	#endif
#else
	pChild = pattrs->nextNode();
#endif
        while (pChild)
        {
            
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				BSTR bstrName = NULL;
				pChild->get_nodeName(&bstrName);
	#else
				_bstr_t bstrName = pChild->GetnodeName();
	#endif
#else
			_bstr_t bstrName = pChild->GetnodeName();
#endif
//			TRACE("%s", (strPath + (LPCTSTR)bstrName).data());
            
			// get the id for this path
			const XML_ENTRY_MAP* pEntries = pXMLRead->LocateEntry( strPath + (LPCTSTR)bstrName );
	
			::SysFreeString(bstrName);
			
			if(pEntries != NULL &&
				( (seen = pXMLRead->IsFirstLoop(pEntries->dwID)) == eNotSeen )
				)
			{
				if(pResolver->OnStartReadLoop(pEntries) == false)
				{
					pXMLRead->MarkAsSeen(pEntries->dwID, eRefused);
					return true;
				}
				else
					pXMLRead->MarkAsSeen(pEntries->dwID, eOk);
			}
			else if(pEntries != NULL && seen == eRefused)
				return true;
			
			VARIANT value;
            pChild->get_nodeValue(&value);
            
			if (pEntries && value.vt == VT_BSTR)
			{
//				TRACE("%S", V_BSTR(&value));
				xmlvalue = (LPCTSTR)_bstr_t(V_BSTR(&value));
				pResolver->OnSetValue(pEntries, pChild, xmlvalue); 
			}

            VariantClear(&value);
            pChild.Release();

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
				pattrs->nextNode(&pChild); // MSXML6
	#else
				pChild = pattrs->nextNode();
	#endif
#else
			pChild = pattrs->nextNode();
#endif

        }
        pattrs.Release();
    }
    else if(nodetype == NODE_TEXT || nodetype == NODE_COMMENT || nodetype == NODE_CDATA_SECTION)
	{
			VARIANT value;
            node->get_nodeValue(&value);

			if (pEntries && value.vt == VT_BSTR)
			{
//				TRACE("%S", V_BSTR(&value));
				xmlvalue = _bstr_t(V_BSTR(&value));
				pResolver->OnSetValue(pEntries, pChild, xmlvalue); 
			}

            VariantClear(&value);
	}

//	TRACE("\n");

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		node->get_firstChild(&pChild); // MSXML6
	#else
		pChild = node->GetfirstChild();
	#endif
#else
	pChild = node->GetfirstChild();
#endif
	
	bool bAddNumType(false);
	WORD wNumChild(0);
	
	DOMNodeType type(NODE_INVALID);

	
	TCHAR _pszConv[SECXMLDEFBUFSIZE];
	while (pChild)
	{
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
			pChild->get_nodeType(&type);
	#else
			type = pChild->GetnodeType();
	#endif
#else
		type = pChild->GetnodeType();
#endif

		if(type == NODE_CDATA_SECTION
		|| type == NODE_COMMENT
		|| type == NODE_DOCUMENT
		|| type == NODE_DOCUMENT_FRAGMENT
		)
			bAddNumType = true;
		else
			bAddNumType = false;
		
		if(bAddNumType)
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_itot(wNumChild, _pszConv, 10);
			LoopTree(pChild, strPath + _pszConv, pXMLRead);
		}
		else
			LoopTree(pChild, strPath, pXMLRead);
		
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
			pChild->get_nextSibling(&pNext);
	#else
			pNext = pChild->GetnextSibling();
	#endif
#else
		pNext = pChild->GetnextSibling();
#endif
		pChild = pNext;
		
		if(bAddNumType)
			wNumChild++;
	}

	return S_OK;
}

#pragma warning (pop) //4239

// XML_ENTRY_MAP implementation
//@doc XML_ENTRY_MAP
//@mfunc Constructor for the XML_ENTRY_MAP class
//@parm LPCTSTR | _pszName | The name of the node
//@parm  ENTRYID | _dwID | The unique identifier for this entry
//@parm  DOMNodeType | _entryType | The type of entry. For further details on
//DOMNodeType please refer to the MSDN documentation.
XML_ENTRY_MAP::XML_ENTRY_MAP(LPCTSTR _pszName, ENTRYID _dwID, DOMNodeType _entryType)
{
	pszName = _pszName;
	dwID = _dwID;
	entryType = _entryType;
	pszNameSpace = NULL;
}

//@doc 
//@mfunc Constructor for the XML_ENTRY_MAP class
//@parm LPCTSTR | _pszName | The name of the node
//@parm  ENTRYID | _dwID | The unique identifier for this entry
//@parm  DOMNodeType | _entryType | The type of entry. For further details on
//DOMNodeType please refer to the MSDN documentation.
//@parm  LPCTSTR | _pszNamespace | Namespace qualifier if any
XML_ENTRY_MAP::XML_ENTRY_MAP(LPCTSTR _pszName, ENTRYID _dwID, DOMNodeType _entryType, LPCTSTR _pszNamespace)
{
	pszName = _pszName;
	dwID = _dwID;
	entryType = _entryType;
	pszNameSpace = _pszNamespace;
}


//@doc 
//@mfunc Destructor. Will loop through and free all contained nodes.
XML_ENTRY_MAP::~XML_ENTRY_MAP()
{
	CXMLList::iterator it;
	XML_ENTRY_MAP* pEntry = NULL;
	for (it = listXMLMapEntries_p.begin(); it != listXMLMapEntries_p.end(); it++)
	{
		pEntry = *it;
		if(pEntry)
			delete pEntry;
	}

	listXMLMapEntries_p.clear();
}


// IXMLRResolver implementation

//@doc 
//@mfunc Default constructor.

IXMLRResolver::IXMLRResolver()
{
	// no implementation	
}
	
//@doc 
//@mfunc Destructor.

IXMLRResolver::~IXMLRResolver()
{
	// no implementation
}


// IXMLWResolver implementation

//@doc 
//@mfunc Default constructor.

IXMLWResolver::IXMLWResolver()
{
	// no implementation	
}
	
//@doc 
//@mfunc Destructor.

IXMLWResolver::~IXMLWResolver()
{
	// no implementation
}

// IXMLRWResolver implementation

//@doc 
//@mfunc Default constructor.

IXMLRWResolver::IXMLRWResolver()
{
	// no implementation	
}
	
//@doc 
//@mfunc Destructor.

IXMLRWResolver::~IXMLRWResolver()
{
	// no implementation
}

//@doc 
//@mfunc OnEndWriteLoop is called to allow your code to clean up any
//resources allotted during the write operation.
//@rdesc bool This version does not check the return value.
//@parm const XML_ENTRY_MAP* | pEntry | The entry in context.
bool IXMLRWResolver::OnEndWriteLoop(const XML_ENTRY_MAP* /*pEntry*/)
{
	// no implementation
	// You usually do not have to provide an implementation for this in your derived class
	return true;
}


// CXMLWriter implementation

//@doc CXMLIO
//@mfunc Default constructor.
CXMLIO::CXMLIO()
{
	m_pIXMLWrite = NULL;
	m_pIXMLRead = NULL;
}
	
//@doc CXMLIO
//@mfunc Destructor
CXMLIO::~CXMLIO()
{
	// no implementation
}

//@doc CXMLIO
//@mfunc Call this function to perform a write operation.
//Data will be written to the XML document that is provided
//by the <mf CXMLIO::OnGetDocument> override.
//@rdesc bool 
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		bool CXMLIO::Write()
	#else
		bool CXMLIO::Write()
	#endif
#else
	bool CXMLIO::Write()
#endif
{
	IXMLWrite* pWrite = GetXMLWrite();
	
	if(pWrite == NULL)
		return false;

	const XML_ENTRY_MAP* pEntries = pWrite->GetXMLMap();

	if(pEntries == NULL)
	{
		TRACE0("CXMLIO::Write. There is nothing to write. Map is empty!\n");
		return false;
	}
	
	// create an XML document and persist it
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		::IXMLDOMDocumentPtr doc;
		doc = this->OnGetDocument();
	#else
		MSXML::IXMLDOMDocumentPtr doc;
		doc = this->OnGetDocument();
	#endif
#else
	MSXML::IXMLDOMDocumentPtr doc;
	doc = this->OnGetDocument();
#endif
	
	if(doc == NULL)
		return false;

	try
	{
		// notify
		this->OnStartWrite(doc);
		pWrite->GetResolver()->OnStartWrite();

		ResolveAndWriteEntries(doc, doc, pEntries, pWrite);

		// notify
		this->OnCompleteWrite(doc);
		pWrite->GetResolver()->OnCompleteWrite();
	}
	catch(_com_error error)
	{
		TRACE1("Warning:  Error in CXMLIO::Write \n", error.Description());
		
		return false;
	}
	catch(...)
	{
		throw;
	}

	return true;
}

//@doc CXMLIO
//@mfunc Call this function to perform a read operation.
//Data will be read in from the document returned by the
//<mf CXMLIO::OnGetDocument> override. 
//@rdesc bool 
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		bool CXMLIO::Read()
	#else
		bool CXMLIO::Read()
	#endif
#else
	bool CXMLIO::Read()
#endif
{
	IXMLRead* pXMLRead = GetXMLRead();
	
	if(pXMLRead == NULL)
		return false;

	const XML_ENTRY_MAP* pEntries = pXMLRead->GetXMLMap();

	if(pEntries == NULL)
	{
		TRACE0("There is nothing to write. Map is empty!\n");
		return false;
	}
	
	// create an XML document and persist it
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
	::IXMLDOMDocumentPtr doc;
	#else
		MSXML::IXMLDOMDocumentPtr doc;
	#endif
#else
	MSXML::IXMLDOMDocumentPtr doc;
#endif
	
	doc = this->OnGetDocument();
	
	if(doc == NULL)
		return false;

	// intial settings
	doc->put_async(VARIANT_FALSE);
	
	if (this->OnStartRead(doc) == false)
		return false;

	try
	{	
		secxmlstring strRoot;
		strRoot = SEC_XML_ROOT;

		LoopTree(doc, strRoot, pXMLRead);
		
		this->OnCompleteRead(doc);
	}
	catch(_com_error error)
	{
		TRACE1("Warning:  Error in CXMLIO::Read \n", error.Description());
		
		return false;
	}
	catch(...)
	{
		throw;
	}

	return true;
}

//@doc MSXML
//@mfunc Read and write operations take place on the document returned by this override.
//You can optionally perform any initialization in this override.
//@rdesc MSXML::IXMLDOMDocument* Please refer to the MSDN documentation for more information
//on this interface.
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		::IXMLDOMDocument* CXMLIO::OnGetDocument()
	#else
		MSXML::IXMLDOMDocument* CXMLIO::OnGetDocument()
	#endif
#else
	MSXML::IXMLDOMDocument* CXMLIO::OnGetDocument()
#endif
{

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		::IXMLDOMDocumentPtr doc;
		HRESULT hr = doc.CreateInstance(__uuidof(DOMDocument60));
	#else
		MSXML::IXMLDOMDocumentPtr doc;
		HRESULT hr = doc.CreateInstance(CLSID_DOMDocument);
	#endif
#else
	MSXML::IXMLDOMDocumentPtr doc;
	HRESULT hr = doc.CreateInstance(CLSID_DOMDocument);
#endif

	
	
	if(FAILED(hr))
	{
		TRACE1("SECXML warning!: Unable to create DOM document. CreateInstance returns %x\n", hr);
		return false;
	}

	doc.AddRef();

	return doc;
}

//@doc CXMLIO
//@mfunc Sets the <c IXMLWrite> interface pointer that will be used during the
//XML write operation.
//@rdesc void 
//@parm IXMLWrite* | pXMLWrite | This interface pointer will be used during the write operation. Please refer
//to <c IXMLWrite> for more details.
void CXMLIO::SetXMLWrite(IXMLWrite* pXMLWrite)
{
	m_pIXMLWrite = pXMLWrite;
}
	
//@doc CXMLIO
//@mfunc Returns a pointer to the <c IXMLWrite> interface that will be used for the 
//XML write operation. This pointer can be changed with the <mf CXMLIO::SetXMLWrite> function. 
//@rdesc IXMLWrite* This interface pointer will be used during the write operation. Please refer
//to <c IXMLWrite> for more details. 
IXMLWrite* CXMLIO::GetXMLWrite() const
{	
	return m_pIXMLWrite;
}

//@doc CXMLIO
//@mfunc Sets the <c IXMLRead> interface pointer that will be used during the XML read operation.
//@rdesc void 
//@parm IXMLRead* | pXMLRead | This interface pointer will be used during the read operation. Please refer
//to <c IXMLRead> for more details. 
void CXMLIO::SetXMLRead(IXMLRead* pXMLRead)
{
	m_pIXMLRead = pXMLRead;
}
	
//@doc CXMLIO
//@mfunc Returns a pointer to the <c IXMLRead> interface that will be used for the 
//XML read operation. This pointer can be changed with the <mf CXMLIO::SetXMLRead> function.
//@rdesc IXMLRead* This interface pointer will be used during the read operation. Please refer
//to <c IXMLRead> for more details. 
IXMLRead* CXMLIO::GetXMLRead() const
{	
	return m_pIXMLRead;
}

// CXMLFileIO implementation
// Writes the XML document to a file

//@doc CXMLFileIO
//@mfunc Default constructor.
CXMLFileIO::CXMLFileIO()
{

}
	
//@doc CXMLFileIO
//@mfunc Destructor
CXMLFileIO::~CXMLFileIO()
{

}

//@doc CXMLFileIO
//@mfunc Override that will be called just before the write operation is started. This
//version does not check the return value.
//@rdesc bool This version does not check the return value.
//@parm MSXML::IXMLDOMDocument* | pDoc | Please refer to the MSDN documentation for more
//information on this interface.
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		bool CXMLFileIO::OnStartWrite(::IXMLDOMDocument* pDoc)
	#else
		bool CXMLFileIO::OnStartWrite(MSXML::IXMLDOMDocument* pDoc)
	#endif
#else
	bool CXMLFileIO::OnStartWrite(MSXML::IXMLDOMDocument* pDoc)
#endif
{
	pDoc;
	return true;	
}

//@doc CXMLFileIO
//@mfunc This override will be called when the XML write operation is complete.
//@rdesc bool The return value is not checked in this version. However any exceptions that
//are thrown will be caught and handled.
//@parm MSXML::IXMLDOMDocument* | pDoc | Please refer to the MSDN documentation for more information
//on this interface.
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		bool CXMLFileIO::OnCompleteWrite(::IXMLDOMDocument* pDoc)
	#else
		bool CXMLFileIO::OnCompleteWrite(MSXML::IXMLDOMDocument* pDoc)
	#endif
#else
	bool CXMLFileIO::OnCompleteWrite(MSXML::IXMLDOMDocument* pDoc)
#endif
{
	if(pDoc == NULL)
		return false;

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		::IXMLDOMDocumentPtr doc = pDoc;
	#else
		MSXML::IXMLDOMDocumentPtr doc = pDoc;
	#endif
#else
	MSXML::IXMLDOMDocumentPtr doc = pDoc;
#endif

	if(doc == NULL)
		return false;
	
	const secxmlstring& strFile = GetFileName();
		
	if(_tcslen(strFile.data()) != 0)
	{
		doc->save(_variant_t(strFile.data()));
	}
	else
		return false;

	return true;
}
	

//@doc CXMLFileIO
//@mfunc Will be called when the read operation is about to be started.
//@rdesc bool If this function returns false, then the read operation will
//no continue.
//@parm MSXML::IXMLDOMDocument* | pDoc | Please refer to the MSDN documentation for
//information about this interface.
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		bool CXMLFileIO::OnStartRead(::IXMLDOMDocument* pDoc)
	#else
		bool CXMLFileIO::OnStartRead(MSXML::IXMLDOMDocument* pDoc)
	#endif
#else
	bool CXMLFileIO::OnStartRead(MSXML::IXMLDOMDocument* pDoc)
#endif
{
	const secxmlstring& strFile = GetFileName();
	
	if(_tcslen(strFile.data()) == 0)
		return false;
	
	VARIANT_BOOL vb;
	VARIANT vURL;
	
	VariantInit(&vURL);
	vURL.vt = VT_BSTR;
	_bstr_t bstrFile(strFile.data());
	V_BSTR(&vURL) = bstrFile;

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		pDoc->load(vURL, &vb); // MSXML6
	#else
		vb = pDoc->load(vURL);
	#endif
#else
	vb = pDoc->load(vURL);
#endif

	::SysFreeString(bstrFile);

	return (vb == VARIANT_TRUE);	
}

//@doc CXMLFileIO
//@mfunc This override will be called when the read operation is complete.
//@rdesc bool The return value is not checked in this version.
//@parm MSXML::IXMLDOMDocument* | pDoc | Please refer to the MSDN documentation 
//for more information on this interface.
#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		bool CXMLFileIO::OnCompleteRead(::IXMLDOMDocument* /*pDoc*/)
	#else
		bool CXMLFileIO::OnCompleteRead(MSXML::IXMLDOMDocument* /*pDoc*/)
	#endif
#else
	bool CXMLFileIO::OnCompleteRead(MSXML::IXMLDOMDocument* /*pDoc*/)
#endif
{
	return true;
}

//@doc CXMLFileIO
//@mfunc This function returns the filename that will be used when
//writing and reading.
//@rdesc const <t secxmlstring>& The filename to be used. 
//Use <mf CXMLFileIO::GetFileNameRef> if you intend to modify the returned
//value.
const secxmlstring& CXMLFileIO::GetFileName() const
{
	return m_strFileName;
}

//@doc CXMLFileIO
//@mfunc This function returns the filename that will be used when
//writing and reading.
//@rdesc <t secxmlstring>& Returns a reference to the filename to be used.
//Use <mf CXMLFileIO::GetFileName> if you do not intend to modify the returned
//value.
secxmlstring& CXMLFileIO::GetFileNameRef()
{
	return m_strFileName;
}

//@doc CXMLFileIO
//@mfunc Sets the filename to be used for read and write operations.
//@rdesc void 
//@parm const <t secxmlstring>& | strFileName | The filename to be used.
void CXMLFileIO::SetFileName(LPCTSTR pszFileName)
{
	m_strFileName = pszFileName;
}

// XMLVALUE implementation

//@doc XMLVALUE
//@mfunc Default constructor.
XMLVALUE::XMLVALUE()
:____dwDefSize(50), ____nRadix(10) 
{
	InitValues(true);
}
	
//@doc XMLVALUE
//@mfunc Constructs XMLVALUE from a LPCTSTR.
//@parm LPCTSTR | psz | String that will be used to initialize this object.
XMLVALUE::XMLVALUE(LPCTSTR psz)
:____dwDefSize(50), ____nRadix(10) 
{
	InitValues(true);
	*this = psz;
}

//@doc XMLVALUE
//@mfunc Constructs XMLVALUE from a int value.
//@parm int | n | integer value to be used to initialize this object.
XMLVALUE::XMLVALUE(int n)
:____dwDefSize(50), ____nRadix(10) 
{
	InitValues(true);
	*this = n;
}

//@doc XMLVALUE
//@mfunc Constructs XMLVALUE from a WORD.
//@parm WORD | w | WORD value to be used to intialize this object.
XMLVALUE::XMLVALUE(WORD w)
:____dwDefSize(50), ____nRadix(10) 
{
	InitValues(true);
	*this = w;
}

//@doc XMLVALUE
//@mfunc Constructs XMLVALUE from a long value.
//@parm long | l | long value to be used to intialize this object.
XMLVALUE::XMLVALUE(long l)
:____dwDefSize(50), ____nRadix(10) 
{
	InitValues(true);
	*this = l;
}

//@doc XMLVALUE
//@mfunc Constructs XMLVALUE from a DWORD value.
//@parm DWORD | dw | DWORD value to be used to intialize this object.
XMLVALUE::XMLVALUE(DWORD dw)
:____dwDefSize(50), ____nRadix(10) 
{
	InitValues(true);
	*this = dw;
}

//@doc XMLVALUE
//@mfunc Constructs XMLVALUE from a COleDateTime object.
//@parm const COleDateTime& | dt | COleDateTime value to be used to intialize this object.
//Please refer to the MSDN documentation for more information on COleDateTime.
XMLVALUE::XMLVALUE(const COleDateTime& dt)
:____dwDefSize(50), ____nRadix(10) 
{
	InitValues(true);
	*this = dt;
}


//@doc XMLVALUE
//@mfunc Destructor
XMLVALUE::~XMLVALUE()
{
	Cleanup();
}

// attributes

//@doc XMLVALUE
//@mfunc Returns the value contained as a string.
//@rdesc LPCTSTR String value
LPCTSTR XMLVALUE::GetValue() const
{
	// let the LPCTSTR operator take care of this
	return (LPCTSTR)*this;
}
	
//@doc XMLVALUE
//@mfunc Sets the value
//@rdesc void 
//@parm LPCTSTR | lpsz | The string value to be stored.
void XMLVALUE::SetValue(LPCTSTR lpsz)	
{
	// let the = op take care of this
	*this = lpsz;
}

//@doc XMLVALUE
//@mfunc Returns the radix value that is used internally for conversions.
//@rdesc int radix value
int XMLVALUE::GetRadix() const
{
	return m_nRadix;
}
	
//@doc XMLVALUE
//@mfunc Sets the radix value that is used internally for conversion.
//@rdesc void 
//@parm int | nRadix | The new radix value that is to be used for conversion.
void XMLVALUE::SetRadix(int nRadix)
{
	m_nRadix = nRadix;
}
	
//@doc XMLVALUE
//@mfunc This function returns the default size of any buffer that this class
//will allocate.
//@rdesc DWORD Default buffer size for dynamic allocation.
DWORD XMLVALUE::GetDefAllocSize() const
{
	return m_dwAllocSize;
}
	
//@doc XMLVALUE
//@mfunc Sets the buffer size to be used for dynamic allocation of buffer (internally).
//@rdesc void 
//@parm DWORD | dwDefSize | The new default buffer size.
void XMLVALUE::SetDefAllocSize(DWORD dwDefSize)
{
	m_dwAllocSize = dwDefSize;
}


//@doc XMLVALUE
//@mfunc Attach the LPTSTR to this object.
//@rdesc void 
//@parm LPTSTR | psz | The string to be attached to this object.
void XMLVALUE::Attach(LPTSTR psz)
{
	Cleanup();
	pszValue = psz;
	bFree = true;
}

//@doc XMLVALUE
//@mfunc Detach the contained string from the object.
//@rdesc LPTSTR The string that was contained internally.
LPTSTR XMLVALUE::Detach()
{
	bFree = false;
	LPTSTR p = pszValue;
	pszValue = NULL;
	return p;
}

//@doc XMLVALUE
//@mfunc This function frees any resources that this class manages.
//@rdesc void 
void XMLVALUE::Cleanup()
{
	if(bFree)
		delete[] pszValue;
		
	InitValues();
}

//@doc XMLVALUE
//@mfunc Simple wrapper for Cleanup in this version.
//@rdesc void 
void XMLVALUE::Recycle()
{
	Cleanup();
}

void XMLVALUE::InitValues(bool bInitAll /* = false */)
{
	pszValue = NULL;
	bFree = false;
	
	if(bInitAll == true)
	{
		SetDefAllocSize(____dwDefSize);
		SetRadix(____nRadix);
	}
}

//@doc XMLVALUE
//@mfunc Returns value as LPCTSTR.
XMLVALUE::operator LPCTSTR() const
{
	return pszValue;
}

//@doc XMLVALUE
//@mfunc Returns true if object value is not NULL.
XMLVALUE::operator bool() const
{
	return (pszValue != NULL);
}

//@doc XMLVALUE
//@mfunc Returns true if object value is NULL.
//@rdesc XMLVALUE::operator 
bool XMLVALUE::operator  !() const
{
	return (pszValue == NULL);
}

//@doc XMLVALUE
//@mfunc Assigns the new LPCTSTR value to the object.
//@parm LPCTSTR | psz | The new LPCTSTR value that is to be assigned to the object.
XMLVALUE& XMLVALUE::operator = (LPCTSTR psz)
{
	if(psz == pszValue)
		return *this;

	Cleanup();
	
	pszValue = _tcsdup(psz);
	bFree = true;
	
	return *this;
}

//@doc XMLVALUE
//@mfunc Assigns a value to the object from the integer passed in.
//@parm int | n | Integer value to be used for intialization.
XMLVALUE& XMLVALUE::operator = (int n)
{
	Cleanup();

	// QA: 31989 - #if Secure Code Cleanup.
	pszValue = _itot(n, new TCHAR[m_dwAllocSize], GetRadix());
	bFree = true;
	
	return *this;
}

//@doc XMLVALUE
//@mfunc Assigns a value to the object from the WORD passed in.
//@parm WORD | w | WORD value to be used.
XMLVALUE& XMLVALUE::operator = (WORD w)
{
	Cleanup();

	// QA: 31989 - #if Secure Code Cleanup.
	pszValue = _itot(w, new TCHAR[m_dwAllocSize], GetRadix());
	bFree = true;
	
	return *this;
}

//@doc XMLVALUE
//@mfunc Assigns a value to the object from the DWORD passed in.
//@rdesc XMLVALUE& XMLVALUE::operator 
//@parm DWORD | dw | DWORD value to be used.
XMLVALUE& XMLVALUE::operator = (DWORD dw)
{
	Cleanup();
	
	// QA: 31989 - #if Secure Code Cleanup.
	pszValue = _ultot(dw, new TCHAR[m_dwAllocSize], GetRadix());
	bFree = true;
	
	return *this;
}

//@doc XMLVALUE
//@mfunc Assigns a value to the object from the long value passed in.
//@parm long | n | long value to be used.
XMLVALUE& XMLVALUE::operator = (long n)
{
	Cleanup();
	
	// QA: 31989 - #if Secure Code Cleanup.
	pszValue = _ltot(n, new TCHAR[m_dwAllocSize], GetRadix());
	bFree = true;
	
	return *this;
}

//@doc XMLVALUE
//@mfunc Assigns a value to the object from the COleDateTime value passed in.
//@parm const COleDateTime& | dt | COleDateTime value to be used. Please refer to the
//MSDN documentation for further information on the COleDateTime class.
XMLVALUE& XMLVALUE::operator = (const COleDateTime& dt)
{
	Cleanup();
	
	pszValue = _tcsdup(dt.Format()); // will use defaults for formatting
	// pass formatted string for other forms of formatting if desired
	
	bFree = true;
	
	return *this;
}

// CXMLBaseHelper implementation

//@doc 
//@mfunc Default constructor.
CXMLBaseHelper::CXMLBaseHelper()
{
	m_pXMLMap = NULL;
	m_pResolver = NULL;
}

//@doc 
//@mfunc Destructor
CXMLBaseHelper::~CXMLBaseHelper()
{
	Cleanup();
}

//@doc 
//@mfunc Returns a pointer to <c XML_ENTRY_MAP> that will be used for
//read and write operations.
//@rdesc const XML_ENTRY_MAP* Please refer to the description of this class for further
//information.  
const XML_ENTRY_MAP* CXMLBaseHelper::GetXMLMap() const
{
	return m_pXMLMap;
}

//@doc 
//@mfunc Returns the associated <c IXMLRWResolver> interface.
//@rdesc IXMLRWResolver* 
IXMLRWResolver* CXMLBaseHelper::GetResolver() const
{
	return m_pResolver;
}

eTypeSeen CXMLBaseHelper::IsFirstLoop(DWORD dwID) const
{
	CMapInit::const_iterator it;
	if( (it = m_initMap.find(dwID)) != m_initMap.end())
		return (*it).second;
	else
		return eNotSeen;
}

void CXMLBaseHelper::MarkAsSeen(DWORD dwID, eTypeSeen seen)
{
	m_initMap[dwID] = seen;
}

const XML_ENTRY_MAP* CXMLBaseHelper::LocateEntry(secxmlstring& pszMonikerData) const
{
	CMapSlots::const_iterator it;
	if( (it = m_slotMap.find(pszMonikerData)) != m_slotMap.end())
		return (*it).second;
	else
		return NULL;
}

//@doc 
//@mfunc Sets the <c XML_ENTRY_MAP> structure that is to be used
//@rdesc void 
//@parm XML_ENTRY_MAP* pMap
void CXMLBaseHelper::SetXMLMap(XML_ENTRY_MAP* pMap)
{
	Cleanup();
	m_pXMLMap = pMap;
}

//@doc 
//@mfunc Sets the associated <c IXMLRWResolver> interface pointer. Please refer to the interface description for 
//more details.
//@rdesc void 
//@parm IXMLRWResolver* pResolver
void CXMLBaseHelper::SetResolver(IXMLRWResolver* pResolver)
{
	m_pResolver = pResolver;
}

//@doc 
//@mfunc In addition to calling Initialize, this function has to be called to use this class for a read operation.
//This function performs special intialization that is essential for a read operation.
//@rdesc bool Returns true if this initialization was successful; false otherwise. If false is returned,
//read operations will fail. Write operations may still work as expected.
bool CXMLBaseHelper::InitializeForRead()
{
	secxmlstring strPath;
	bool b = ::InitializeForRead(m_pXMLMap, // map entries 
						m_slotMap, // map that holds the ids for all the different paths	
						strPath // path of the node
						);
	
	m_bInitForRead = b;

	return b;
}

//@doc 
//@mfunc Returns true if this instance is initialized for a read operation; false otherwise.
//Read operations will fail if this initialization has not been performed. Please refer to 
//<mf CXMLBaseHelper::InitializeForRead> for further information. 
//@rdesc bool true if initialized for read; false otherwise.
bool CXMLBaseHelper::IsInitForRead()
{
	return m_bInitForRead;
}

//@doc 
//@mfunc Call this function to clean up the <c XML_ENTRY_MAP> map that is held by this object.
//The resolver object <c IXMLRWResolver> will also be freed.
//@rdesc void 
void CXMLBaseHelper::Cleanup()
{
	if(m_pXMLMap)
		delete m_pXMLMap;

	m_pXMLMap = NULL;
	
	if(m_pResolver)
		delete[] m_pResolver;

	m_pResolver = NULL;
}

// CEntryValueHolder implementation

CEntryValueHolder::CEntryValueHolder()
{
	// no implementation
}

CEntryValueHolder::~CEntryValueHolder()
{
	Cleanup();
}

void CEntryValueHolder::Cleanup()
{
	CDelList::iterator it = m_lstDel.begin();
		 
	for (; it != m_lstDel.end(); it++)
	{
		__DELSTRUCT& delStruct = *it;
		(*(delStruct.pfn))(delStruct.p);
	}

	m_lstDel.clear();
}

void CEntryValueHolder::ManageMemory(void* p, pfnDel pfn)
{
	if(p && pfn)
	{
		__DELSTRUCT delStruct = {p, pfn};
		m_lstDel.push_back(delStruct);
	}
}

