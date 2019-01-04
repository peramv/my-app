#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfbase_err_obj_required_in_list : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfbase_err_obj_required_in_list() { }
		~CBase_Infrastructure_bfbase_err_obj_required_in_list() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJ_REQUIRED_IN_LIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%GENERIC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check DLL to be sure you have the correct version.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check DLL to be sure you have the correct version.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die DLL, um zu gewährleisten, dass Sie die richtige Version verwenden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el DLL para asegurarse de que tiene la versión correcta.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le DLL pour vous assurer que vous avez la bonne version.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de DLL om er zeker van te zijn dat u de juiste versie hebt")); }
	};
}



