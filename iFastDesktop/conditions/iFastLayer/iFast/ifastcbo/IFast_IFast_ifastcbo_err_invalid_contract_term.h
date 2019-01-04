#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_contract_term : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_contract_term() { }
		~CIFast_IFast_ifastcbo_err_invalid_contract_term() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CONTRACT_TERM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Term's value is outside of range.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Contract Term's value is outside of range.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Wert der Vertragsbedingungen liegt außerhalb des Bereichs.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor de la duración del contrato se encuentra fuera de rango.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de l'échéance du contrat est hors plage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarde overeenkomstduur ligt buiten het bereik")); }

        // Actions
	};
}



