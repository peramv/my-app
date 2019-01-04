#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_trans_amt_cannot_be_earlier_than_init_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_trans_amt_cannot_be_earlier_than_init_date() { }
		~CIFast_IFast_ifastcbo_err_net_trans_amt_cannot_be_earlier_than_init_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_TRANS_AMT_CANNOT_BE_EARLIER_THAN_INIT_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net transaction amount cannot be earlier than the initial date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date du montant net de la transaction ne peut pas être plus récente que la date initiale.")); }

        // Actions
	};
}



