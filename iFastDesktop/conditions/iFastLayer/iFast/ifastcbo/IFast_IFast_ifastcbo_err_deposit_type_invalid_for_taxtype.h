#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_type_invalid_for_taxtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_type_invalid_for_taxtype() { }
		~CIFast_IFast_ifastcbo_err_deposit_type_invalid_for_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_TYPE_INVALID_FOR_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Code is not valid for tax type of the to account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Code für die Steuerart des Kontos nicht gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código no es válido para el tipo tributario de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code invalide pour le type d'imposition du compte cible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Code is ongeldig voor belastingtype van het naar-account")); }

        // Actions
	};
}



