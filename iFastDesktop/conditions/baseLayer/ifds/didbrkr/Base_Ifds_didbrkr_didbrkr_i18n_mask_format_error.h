#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_i18n_mask_format_error : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_i18n_mask_format_error() { }
		~CBase_Ifds_didbrkr_didbrkr_i18n_mask_format_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_I18N_MASK_FORMAT_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Boolean Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrfach-Kontoinhaber (01)-Objekte sind für diesen Kontotyp nicht zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Boolean Attribute may not have a value of %VALUE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : l'attribut booléen pourrait n'avoir aucune valeur de %VALUE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Boolean Attribute may not have a value of %VALUE%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



