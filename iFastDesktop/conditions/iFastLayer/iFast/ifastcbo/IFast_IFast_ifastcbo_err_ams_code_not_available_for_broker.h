#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_code_not_available_for_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_code_not_available_for_broker() { }
		~CIFast_IFast_ifastcbo_err_ams_code_not_available_for_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_NOT_AVAILABLE_FOR_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code is not available for Broker %BROKER_CODE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Code is not available for Broker %BROKER_CODE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Code is not available for Broker %BROKER_CODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille n'est pas disponible pour le courtier %BROKER_CODE%.")); }

        // Actions
	};
}



