#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_date_affect_min_max_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_date_affect_min_max_amt() { }
		~CIFast_IFast_ifastcbo_err_deposit_date_affect_min_max_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_DATE_AFFECT_MIN_MAX_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit date changed to previous year, may affect the min/max amount.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Deposit date not in the same year of trade date may affect the min/max amount")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Depot-Datum wurde auf das vorige Jahr geändert, könnte sich auf den Min/Max-Betrag auswirken.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de depósito cambió al año anterior,  puede afectar el monto mínimo/máximo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le changement de la date de dépôt par rapport à l'année précédente peut influencer le montant min/max.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Depositodatum is gewijzigd in vorig jaar, kan van invloed zijn op min.-/max.-bedrag")); }

        // Actions
	};
}



