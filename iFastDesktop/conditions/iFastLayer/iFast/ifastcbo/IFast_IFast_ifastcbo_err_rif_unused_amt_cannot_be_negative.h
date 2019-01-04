#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_unused_amt_cannot_be_negative : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_unused_amt_cannot_be_negative() { }
		~CIFast_IFast_ifastcbo_err_rif_unused_amt_cannot_be_negative() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_UNUSED_AMT_CANNOT_BE_NEGATIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unused Max Amount cannot be negative.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant maximal non utilisé ne peut être négatif.")); }

        // Actions
	};
}



