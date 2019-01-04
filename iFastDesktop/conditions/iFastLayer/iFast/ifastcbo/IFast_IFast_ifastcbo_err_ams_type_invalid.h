#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_type_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_type_invalid() { }
		~CIFast_IFast_ifastcbo_err_ams_type_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_TYPE_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Type %AMSTYPE% is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Type %AMSTYPE% is invalid.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Type %AMSTYPE% is invalid.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de service de gestion de portefeuille %AMSTYPE% est invalide.")); }

        // Actions
	};
}



