#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_rxtranstype_taxtype_combination : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_rxtranstype_taxtype_combination() { }
		~CIFast_IFast_ifastcbo_err_invalid_rxtranstype_taxtype_combination() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction Type is invalid for Tax Type of the Account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktionsart für die Steuerart des Kontos ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de transacción no es válido para el tipo tributario de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de transaction invalide pour le type d'imposition du compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactietype is ongeldig voor belastingtype van het account")); }

        // Actions
	};
}



