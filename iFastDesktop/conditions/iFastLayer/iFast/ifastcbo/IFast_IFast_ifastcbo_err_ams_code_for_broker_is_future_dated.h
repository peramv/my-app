#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_code_for_broker_is_future_dated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_code_for_broker_is_future_dated() { }
		~CIFast_IFast_ifastcbo_err_ams_code_for_broker_is_future_dated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_FOR_BROKER_IS_FUTURE_DATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code for Broker %BROKER_CODE% is Future Dated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Code for Broker %BROKER_CODE% is Future Dated.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Code for Broker %BROKER_CODE% is Future Dated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille du courtier %BROKER_CODE% est postérieur à la date actuelle.")); }

        // Actions
	};
}



