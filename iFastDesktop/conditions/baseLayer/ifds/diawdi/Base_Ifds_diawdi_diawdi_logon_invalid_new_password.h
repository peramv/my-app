#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_diawdi_diawdi_logon_invalid_new_password : public CConditionObject
	{
	public:
		CBase_Ifds_diawdi_diawdi_logon_invalid_new_password() { }
		~CBase_Ifds_diawdi_diawdi_logon_invalid_new_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_INVALID_NEW_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Process Action Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Geburtsdatum. Das Geburtsdatum darf nicht in der Zukunft liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Process Action Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : l'attribut action du processus pourrait n'avoir aucune valeur de %VALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Process Action Attribute may not have a value of %VALUE%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



