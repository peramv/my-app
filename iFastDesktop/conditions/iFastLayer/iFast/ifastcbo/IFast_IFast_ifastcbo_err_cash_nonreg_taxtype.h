#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cash_nonreg_taxtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cash_nonreg_taxtype() { }
		~CIFast_IFast_ifastcbo_err_cash_nonreg_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CASH_NONREG_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cash instruction is not allowed for any registered tax type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions quant au comptant ne sont autorisées pour aucun type d'impôt enregistré.")); }

        // Actions
	};
}



