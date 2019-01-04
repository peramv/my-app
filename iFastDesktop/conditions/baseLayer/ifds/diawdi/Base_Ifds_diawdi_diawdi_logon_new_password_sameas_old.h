#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_diawdi_diawdi_logon_new_password_sameas_old : public CConditionObject
	{
	public:
		CBase_Ifds_diawdi_diawdi_logon_new_password_sameas_old() { }
		~CBase_Ifds_diawdi_diawdi_logon_new_password_sameas_old() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_NEW_PASSWORD_SAMEAS_OLD")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Root element name is unknown.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es muss wenigstens ein ID-Typ für jedes Objekt eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Root element name is unknown.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : le nom de l'élément racine est inconnu.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Root element name is unknown.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



