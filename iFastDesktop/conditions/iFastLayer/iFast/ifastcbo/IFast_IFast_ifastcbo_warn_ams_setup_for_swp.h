#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ams_setup_for_swp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ams_setup_for_swp() { }
		~CIFast_IFast_ifastcbo_warn_ams_setup_for_swp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AMS_SETUP_FOR_SWP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS portfolio can not be set up for the account, which has an active SWP.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS portfolio can not be set up for the account, which has an active SWP.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS portfolio can not be set up for the account, which has an active SWP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le portefeuille SGP ne peut être réglé pour le compte, qui comporte un PRP actif.")); }

        // Actions
	};
}



