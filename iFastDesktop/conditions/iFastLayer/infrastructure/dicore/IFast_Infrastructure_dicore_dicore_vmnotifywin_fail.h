﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_vmnotifywin_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_vmnotifywin_fail() { }
		~CIFast_Infrastructure_dicore_dicore_vmnotifywin_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMNOTIFYWIN_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmNotifyWin error.  Return Code: %rc%, HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmNotifyWin error.  Return Code: %rc%, HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmNotifyWin-Fehler.  Rückgabecode: %rc%, HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de VmNotifyWin.  Código de retorno:  %rc%, HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur Windows de notification du gestionnaire de l'affichage. Code de renvoi : %rc%, HWND : %hwnd%, message : %msg%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmNotifyWin-fout.  Retourcode: %rc%, HWND: %hwnd%, MSG %msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check system")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



