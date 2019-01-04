﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_fund_class_exchangein_stop_flag_on : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_fund_class_exchangein_stop_flag_on() { }
		~CIFast_IFast_ifastcbo_err_warn_fund_class_exchangein_stop_flag_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_FUND_CLASS_EXCHANGEIN_STOP_FLAG_ON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% and Class %CLASS% has Exchange In stop flag turned on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund %FUND% and Class %CLASS% has Exchange In stop flag turned on.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund %FUND% and Class %CLASS% has Exchange In stop flag turned on.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt d'échange entrant du fonds %FUND% et de la classe %CLASS% est activé.")); }

        // Actions
	};
}



