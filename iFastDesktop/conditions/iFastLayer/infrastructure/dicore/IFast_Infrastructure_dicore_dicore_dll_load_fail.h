#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_dll_load_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_dll_load_fail() { }
		~CIFast_Infrastructure_dicore_dicore_dll_load_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DLL_LOAD_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%GENERIC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check path for .DLL's and the DLL name you are trying to load.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check path for .DLL's and the DLL name you are trying to load.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Durchsuchen Sie den Pfad nach .Dlls und nach dem Dll-Namen, die Sie gerade zu laden versuchen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check path for .DLL's and the DLL name you are trying to load.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le chemin pour le .DLL's et le nom du DLL que vous essayez de télécharger.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het pad voor DLL's en de DLL-naam die u probeert te laden")); }
	};
}



