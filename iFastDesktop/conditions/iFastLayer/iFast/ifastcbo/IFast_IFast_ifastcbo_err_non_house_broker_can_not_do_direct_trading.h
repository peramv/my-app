#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_non_house_broker_can_not_do_direct_trading : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_non_house_broker_can_not_do_direct_trading() { }
		~CIFast_IFast_ifastcbo_err_non_house_broker_can_not_do_direct_trading() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_HOUSE_BROKER_CAN_NOT_DO_DIRECT_TRADING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This broker can not do direct trading. Please select a house broker.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("This broker can not do direct trading. Please select a house broker.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("This broker can not do direct trading. Please select a house broker.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce courtier ne peut effectuer d'opération directe. Veuillez sélectionner un courtier immobilier.")); }

        // Actions
	};
}



