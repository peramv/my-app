#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_ams_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_ams_code() { }
		~CIFast_IFast_ifastcbo_err_invalid_ams_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code can not be the same as any existing fund code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS Code can not be the same as any existing fund code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS Code can not be the same as any existing fund code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille ne peut être identique à aucun code de fonds existant.")); }

        // Actions
	};
}



