#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_virtual_base_method_not_supported : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_virtual_base_method_not_supported() { }
		~CBase_Ifds_dicore_virtual_base_method_not_supported() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("VIRTUAL_BASE_METHOD_NOT_SUPPORTED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Cache Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Todesbenachrichtigungs-Datum muss nach dem Todesdatum liegen oder mit diesem übereinstimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Cache Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : l'attribut cache pourrait n'avoir aucune valeur de %VALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Cache Attribute may not have a value of %VALUE%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



