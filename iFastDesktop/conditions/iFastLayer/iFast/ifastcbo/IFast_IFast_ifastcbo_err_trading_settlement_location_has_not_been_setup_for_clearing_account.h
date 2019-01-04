#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trading_settlement_location_has_not_been_setup_for_clearing_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trading_settlement_location_has_not_been_setup_for_clearing_account() { }
		~CIFast_IFast_ifastcbo_err_trading_settlement_location_has_not_been_setup_for_clearing_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADING_SETTLEMENT_LOCATION_HAS_NOT_BEEN_SETUP_FOR_CLEARING_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Settlement Location has been setup for this Clearing Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No Settlement Location has been setup for this Clearing Account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No Settlement Location has been setup for this Clearing Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun lieu de règlement n'a été réglé pour ce compte de compensation.")); }

        // Actions
	};
}



