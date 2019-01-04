#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_escrow_for_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_escrow_for_account() { }
		~CIFast_IFast_ifastcbo_err_ams_escrow_for_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_ESCROW_FOR_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS portfolio can not be set up for Escrow/Assigned account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS portfolio can not be set up for escrow account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS portfolio can not be set up for escrow account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le portefeuille SGP ne peut être réglé pour le compte cédé en garantie.")); }

        // Actions
	};
}



