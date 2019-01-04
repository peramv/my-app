#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_code_restricted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_code_restricted() { }
		~CIFast_IFast_ifastcbo_err_ams_code_restricted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_RESTRICTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code %AMSCODE% is restricted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Code %AMSCODE% is restricted.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Code %AMSCODE% is restricted.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille %AMSCODE% est restreint.")); }

        // Actions
	};
}



