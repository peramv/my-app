#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_time_format : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_time_format() { }
		~CIFast_IFast_ifastcbo_err_invalid_time_format() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TIME_FORMAT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Time Format.Time Format should be %FORMAT% .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format d’heure invalide. Le format d’heure doit être %FORMAT%.")); }

        // Actions
	};
}



