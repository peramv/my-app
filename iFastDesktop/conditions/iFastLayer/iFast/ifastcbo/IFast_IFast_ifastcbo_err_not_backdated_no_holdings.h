#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_not_backdated_no_holdings : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_not_backdated_no_holdings() { }
		~CIFast_IFast_ifastcbo_err_not_backdated_no_holdings() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_BACKDATED_NO_HOLDINGS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only backdated transactions can be posted to accounts with no holdings.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Only backdated transactions can be posted to accounts with no holdings.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Only backdated transactions can be posted to accounts with no holdings.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seules des transactions antidatées peuvent être enregistrées dans des comptes n'ayant aucun portefeuille.")); }

        // Actions
	};
}



