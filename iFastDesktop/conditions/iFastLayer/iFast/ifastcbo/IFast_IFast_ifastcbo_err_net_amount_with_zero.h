#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_amount_with_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_amount_with_zero() { }
		~CIFast_IFast_ifastcbo_err_net_amount_with_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_AMOUNT_WITH_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net Amount with zero value is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Net Amount with zero value is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un montant net de valeur nulle n'est pas autorisé.")); }

        // Actions
	};
}



