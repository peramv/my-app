#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_broker_from_transfer_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_broker_from_transfer_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_broker_from_transfer_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BROKER_FROM_TRANSFER_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker: From: Transfer not allowed for fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Courtier : de : transfert non autorisé pour le fonds")); }

        // Actions
	};
}



