#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_settle_type_dealer_interm : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_settle_type_dealer_interm() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_settle_type_dealer_interm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SETTLE_TYPE_DEALER_INTERM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Settlement Type for Dealer/Intermediary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Abrechnungsart für Händler/Mittler")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de liquidación no válido para agente/intermediario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de règlement invalide pour le courtier/l'intermédiaire")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig betalingstype voor handelaar/tussenpersoon")); }

        // Actions
	};
}



