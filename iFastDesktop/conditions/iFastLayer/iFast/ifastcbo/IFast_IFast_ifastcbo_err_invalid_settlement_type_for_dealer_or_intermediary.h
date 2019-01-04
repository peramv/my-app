#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_settlement_type_for_dealer_or_intermediary : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_settlement_type_for_dealer_or_intermediary() { }
		~CIFast_IFast_ifastcbo_err_invalid_settlement_type_for_dealer_or_intermediary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SETTLEMENT_TYPE_FOR_DEALER_OR_INTERMEDIARY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid settlement type for dealer/intermediary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Abrechnungsart für Händler/Mittler")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de liquidación no válido para agente/intermediario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de règlement invalide pour le courtier/l'intermédiaire")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig betalingstype voor handelaar/tussenpersoon")); }

        // Actions
	};
}



