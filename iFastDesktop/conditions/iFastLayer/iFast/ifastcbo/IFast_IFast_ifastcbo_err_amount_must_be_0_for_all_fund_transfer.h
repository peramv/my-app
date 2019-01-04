#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_must_be_0_for_all_fund_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_must_be_0_for_all_fund_transfer() { }
		~CIFast_IFast_ifastcbo_err_amount_must_be_0_for_all_fund_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_MUST_BE_0_FOR_ALL_FUND_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be 0 for all fund transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag für Gesamtfonds-Transfer muss 0 sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser igual a 0 para la transferencia de todo el fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être de zéro pour le transfert de tous les fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet 0 zijn voor overdracht van alle fondsen")); }

        // Actions
	};
}



