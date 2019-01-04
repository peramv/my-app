#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_setup_for_pac : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_setup_for_pac() { }
		~CIFast_IFast_ifastcbo_err_ams_setup_for_pac() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_SETUP_FOR_PAC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS portfolio can not be set up for the account, which has an active pending PAC.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS portfolio can not be set up for the account, which has an active pending PAC.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS portfolio can not be set up for the account, which has an active pending PAC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le portefeuille de service de gestion de portefeuille ne peut être réglé pour le compte, qui comporte un PAC actif en suspens.")); }

        // Actions
	};
}



