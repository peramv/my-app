#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_aip_withdrawal_exists_tx_to_another_resp_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_aip_withdrawal_exists_tx_to_another_resp_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_aip_withdrawal_exists_tx_to_another_resp_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AIP withdrawal exists, transfer to another RESP not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un retrait PRA existe, le transfert vers un autre REEE n'est donc pas autorisé.")); }

        // Actions
	};
}



