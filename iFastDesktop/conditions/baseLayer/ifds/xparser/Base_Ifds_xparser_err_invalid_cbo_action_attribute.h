#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_invalid_cbo_action_attribute : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_invalid_cbo_action_attribute() { }
		~CBase_Ifds_xparser_err_invalid_cbo_action_attribute() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CBO_ACTION_ATTRIBUTE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: CBO Action Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Hinzufügen eines nicht mehr existierenden Objekts ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: CBO Action Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : l'attribut action de l'optimisation de coûts pourrait n'avoir aucune valeur de %VALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: CBO Action Attribute may not have a value of %VALUE%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



