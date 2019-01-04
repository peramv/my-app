#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_dated_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_dated_trade() { }
		~CIFast_IFast_ifastcbo_err_future_dated_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DATED_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Future dated trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zukünftiger Handel")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Operación con fecha futura")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de transaction postérieure à la date actuell")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("In de toekomst gedateerde handel")); }

        // Actions
	};
}



