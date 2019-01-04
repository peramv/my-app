#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_transfer_out : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_transfer_out() { }
		~CIFast_IFast_ifastcbo_warn_resp_transfer_out() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_TRANSFER_OUT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please complete the transfer information. Account balance for transferring out RESP will be updated with these amounts when transfer is settled.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez remplir l'information sur le transfert. Le solde du compte pour le transfert sortant REEE sera mis à jour avec ces montants lorsque le transfert sera réglé.")); }

        // Actions
	};
}



