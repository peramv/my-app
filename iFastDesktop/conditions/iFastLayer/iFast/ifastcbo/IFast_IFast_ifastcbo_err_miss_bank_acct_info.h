#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_miss_bank_acct_info : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_miss_bank_acct_info() { }
		~CIFast_IFast_ifastcbo_err_miss_bank_acct_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISS_BANK_ACCT_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing bank account information.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Missing bank account information or bank account currency does not match the settlement currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehlende Kontoinformation oder Kontowährung stimmt nicht mit Abrechnungswährung überein. Bitte überprüfen Sie Bankkonto- und Währungsinformationen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta información de la cuenta bancaria o la divisa de la cuenta bancaria no coincide con la divisa de liquidación. Por favor revise la información de la cuenta bancaria y divisa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information manquante sur le compte bancaire")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ontbrekende bankrekeninggegevens of bankrekeningvaluta komen niet overeen met de betalingsvaluta. Controleer de bankrekening- en valutagegevens")); }

        // Actions
	};
}



