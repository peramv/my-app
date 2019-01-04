#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_object_read_only : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_object_read_only() { }
		~CBase_Ifds_dicbocore_err_object_read_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_READ_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Key cannot be specified for non-list CBO's.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bevollmächtigter Eigentümer (21) kann nur für Bevollmächtigten- oder Mittler (Intermediary)-Kontobezeichnungen erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Key cannot be specified for non-list CBO's.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La clé ne peut être spécifiée pour les optimisations de coûts hors liste.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Key cannot be specified for non-list CBO's.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



