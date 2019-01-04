#include "stdafx.h"
#include "ifsuppext.hpp"

static ifsupp::PFNMGMTCOINFO s_pfnMgmtCoInfo = NULL;

void ifsupp::SetMgmtCoInfoCallback(PFNMGMTCOINFO pfn) {
   s_pfnMgmtCoInfo = pfn;
}

void __stdcall ifsupp::GetMgmtCoInfoCallback(ifsupp::PFNMGMTCOINFO& p) {
   p = s_pfnMgmtCoInfo;;
}

static ifsupp::PFNKICKSTATUSBAR s_pfnKickStatusBar = NULL;

void ifsupp::SetStatusBarKicker(ifsupp::PFNKICKSTATUSBAR pfn) {
   s_pfnKickStatusBar = pfn;
}

void __stdcall ifsupp::GetStatusBarKicker(ifsupp::PFNKICKSTATUSBAR& p) {
   p = s_pfnKickStatusBar;
}