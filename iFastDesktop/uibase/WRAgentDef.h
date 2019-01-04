#ifndef _WRAGENTDEF_H_
#define _WRAGENTDEF_H_


// WinRunner OG Agent Definitions
// Include in OG-derived class header file.

#define WR_ST_SVC_MSG_STR		_TEXT("WR_ST_SVC_MSG_STR")

// Put inside class definition
#define DECLARE_USING_WR_AGENT  \
public: \
	static UINT WR_ST_SVC_MSG;

// Put near message handler declarations
#define DECLARE_WR_AGENT_MSG  \
	afx_msg LRESULT OnWRStingMsg(WPARAM wParam, LPARAM lParam);

// Put at top of class implementation file
#define IMPLEMENT_USING_WR_AGENT(TheClass)  \
    UINT TheClass::WR_ST_SVC_MSG = RegisterWindowMessage(WR_ST_SVC_MSG_STR);

// Put in message map
#define WR_AGENT_MSG_MAP_ENTRY  \
	ON_REGISTERED_MESSAGE(WR_ST_SVC_MSG, OnWRStingMsg)

// Put in class implementation file
#define IMPLEMENT_WR_AGENT_TOOLBAR_MSG(TheClass)  \
    LRESULT TheClass::OnWRStingMsg(WPARAM wParam, LPARAM lParam)    \
    {   \
	    CWRAgentSvc* pWRAgent = CWRAgentSvc::Instance();    \
    \
	    return pWRAgent->HandleWRToolBarMsg(wParam, this);   \
    }
#define IMPLEMENT_WR_AGENT_GRID_MSG(TheClass)  \
    LRESULT TheClass::OnWRStingMsg(WPARAM wParam, LPARAM lParam)    \
    {   \
	    CWRAgentSvc* pWRAgent = CWRAgentSvc::Instance();    \
    \
	    return pWRAgent->HandleWRGridMsg(wParam, this);   \
    }

#define IMPLEMENT_WR_AGENT_TREE_CTRL_MSG(TheClass)  \
    LRESULT TheClass::OnWRStingMsg(WPARAM wParam, LPARAM lParam)    \
    {   \
	    CWRAgentSvc* pWRAgent = CWRAgentSvc::Instance();    \
    \
	    return pWRAgent->HandleWRTreeMsg(wParam, this ,0);   \
    }

#define IMPLEMENT_WR_AGENT_TREE_VIEW_MSG(TheClass)  \
    LRESULT TheClass::OnWRStingMsg(WPARAM wParam, LPARAM lParam)    \
    {   \
	    CWRAgentSvc* pWRAgent = CWRAgentSvc::Instance();    \
    \
	    return pWRAgent->HandleWRTreeMsg(wParam ,0, this);   \
    }

#define IMPLEMENT_WR_AGENT_TAB_CTRL_MSG(TheClass)  \
    LRESULT TheClass::OnWRStingMsg(WPARAM wParam, LPARAM lParam)    \
    {   \
	    CWRAgentSvc* pWRAgent = CWRAgentSvc::Instance();    \
    \
	    return pWRAgent->HandleWRTabMsg(wParam, this, 0);   \
    }

#define IMPLEMENT_WR_AGENT_TAB_WND_MSG(TheClass)  \
    LRESULT TheClass::OnWRStingMsg(WPARAM wParam, LPARAM lParam)    \
    {   \
	    CWRAgentSvc* pWRAgent = CWRAgentSvc::Instance();    \
    \
	    return pWRAgent->HandleWRTabMsg(wParam, 0, this);   \
    }

#endif //_WRAGENTDEF_H_