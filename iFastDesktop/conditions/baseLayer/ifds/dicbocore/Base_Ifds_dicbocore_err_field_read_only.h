#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_field_read_only : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_field_read_only() { }
		~CBase_Ifds_dicbocore_err_field_read_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_READ_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("CBO not found for key")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Treuhänder (13) kann nur für Treuhänder-Kontoarten erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("CBO not found for key")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Optimisation de coûts introuvable pour la clé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("CBO not found for key")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check XML input")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Check XML input")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check XML input")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie XML.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Check XML input")); }
	};
}



