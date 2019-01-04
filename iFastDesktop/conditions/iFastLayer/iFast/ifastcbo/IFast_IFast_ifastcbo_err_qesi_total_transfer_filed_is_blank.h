#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_qesi_total_transfer_filed_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_qesi_total_transfer_filed_is_blank() { }
		~CIFast_IFast_ifastcbo_err_qesi_total_transfer_filed_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_QESI_TOTAL_TRANSFER_FILED_IS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You must indicate if the transfer-in entails a full or partial RESP property to proceed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez indiquer si le transfert entrant entraîne une propriété REEE totale ou partielle avant de procéder.")); }

        // Actions
	};
}



