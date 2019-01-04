#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_where_use_type_fund_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_where_use_type_fund_invalid() { }
		~CIFast_IFast_ifastcbo_err_where_use_type_fund_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WHERE_USE_TYPE_FUND_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Network Sender is only applicable for Client.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'expéditeur du réseau n'est applicable que pour le client.")); }

        // Actions
	};
}



