#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_out_of_limits_alloc_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_out_of_limits_alloc_amount() { }
		~CIFast_IFast_ifastcbo_err_rif_out_of_limits_alloc_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be between 0 and %AMOUNT%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le montant doit être compris entre 0 et %AMOUNT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Betrag muss zwischen 0 und %AMOUNT% liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto debe ser entre 0 y 100 %AMOUNT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant doit être situé entre 0 et %AMOUNT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag moet tussen 0 en %AMOUNT% liggen")); }

        // Actions
	};
}



