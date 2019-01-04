#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_spliccomamount_is_greater : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_spliccomamount_is_greater() { }
		~CIFast_IFast_ifastcbo_err_warn_spliccomamount_is_greater() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_SPLICCOMAMOUNT_IS_GREATER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Gross amount %AMOUNT% of money-in fund is less than total split commission amount %SPLITAMOUNT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant brut de %AMOUNT% du fonds d'entrée d'argent est inférieur au montant total de partage de commission de %SPLITAMOUNT%.")); }

        // Actions
	};
}



