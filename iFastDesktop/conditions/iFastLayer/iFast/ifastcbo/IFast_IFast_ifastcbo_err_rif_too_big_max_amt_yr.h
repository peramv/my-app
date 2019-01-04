#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_too_big_max_amt_yr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_too_big_max_amt_yr() { }
		~CIFast_IFast_ifastcbo_err_rif_too_big_max_amt_yr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_TOO_BIG_MAX_AMT_YR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maximum Amount is greater than current Account Value.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Maximum Amount is greater than current Account Value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Maximaler Betrag ist größer als der aktuelle Kontowert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto máximo es mayor que el valor actual de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant maximal excède la valeur du compte courant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Maximumbedrag is groter dan de huidige accountwaarde")); }

        // Actions
	};
}



