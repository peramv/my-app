#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_stop_flag_set_for_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_stop_flag_set_for_fund() { }
		~CIFast_IFast_ifastcbo_warn_stop_flag_set_for_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_STOP_FLAG_SET_FOR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%LEVEL% Level Stop Rule Active For the Fund %FUND% and Class %CLASS% .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%LEVEL% Niveau Stop règle active pour le Fonds %FUND% et classe %CLASS% .")); }

        // Actions
	};
}



