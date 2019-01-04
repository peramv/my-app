#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_trans_amt_exceed_net_cesg_owning : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_trans_amt_exceed_net_cesg_owning() { }
		~CIFast_IFast_ifastcbo_err_net_trans_amt_exceed_net_cesg_owning() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_TRANS_AMT_EXCEED_NET_CESG_OWNING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net transaction amount exceeds net CESG owing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de la transaction nette excède le solde SCEE net.")); }

        // Actions
	};
}



