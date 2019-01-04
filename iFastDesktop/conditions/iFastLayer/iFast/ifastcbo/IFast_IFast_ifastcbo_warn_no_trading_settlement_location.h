#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_no_trading_settlement_location : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_no_trading_settlement_location() { }
		~CIFast_IFast_ifastcbo_warn_no_trading_settlement_location() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NO_TRADING_SETTLEMENT_LOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Settlement Location has been setup for this Clearing Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun lieu de règlement n'a été réglé pour ce compte de compensation.")); }

        // Actions
	};
}



