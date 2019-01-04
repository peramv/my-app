#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfbase_err_obj_required : public CConditionObject
	{
	public:
		CBase_Ifds_bfbase_err_obj_required() { }
		~CBase_Ifds_bfbase_err_obj_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJ_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Object required")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  CBO für Feld %FIELD% darf nicht festgelegt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Object required")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Objet requis")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Object required")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Check system")); }
	};
}



