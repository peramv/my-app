#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_incremented_amt_is_rdr_adviced : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_incremented_amt_is_rdr_adviced() { }
		~CIFast_IFast_ifastcbo_err_incremented_amt_is_rdr_adviced() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INCREMENTED_AMT_IS_RDR_ADVICED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Request for additional amount is RDR Adviced. Please setup a new PAC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande d’un montant supplémentaire est RDR Adviced. Créez un nouveau PAC.")); }

        // Actions
	};
}



