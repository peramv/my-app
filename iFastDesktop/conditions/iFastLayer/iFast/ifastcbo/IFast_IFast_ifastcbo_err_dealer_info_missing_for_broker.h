#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dealer_info_missing_for_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dealer_info_missing_for_broker() { }
		~CIFast_IFast_ifastcbo_err_dealer_info_missing_for_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEALER_INFO_MISSING_FOR_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Dealer information available for Broker Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No Dealer information available for Broker Code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur le courtier n'est disponible pour le code de courtier.")); }

        // Actions
	};
}



