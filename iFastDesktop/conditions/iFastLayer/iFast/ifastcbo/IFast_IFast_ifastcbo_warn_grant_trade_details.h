#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_grant_trade_details : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_grant_trade_details() { }
		~CIFast_IFast_ifastcbo_warn_grant_trade_details() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GRANT_TRADE_DETAILS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Grant transaction with transaction number %TRANSNUM% should be cancelled before proceeding with allocation modification.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction de subvention dont les numéro de transaction sont %TRANSNUM% devrait être annulée avant l'exécution de la modification de répartition.")); }

        // Actions
	};
}



