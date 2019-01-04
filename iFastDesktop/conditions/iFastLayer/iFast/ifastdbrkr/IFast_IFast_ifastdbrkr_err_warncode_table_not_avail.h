#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_warncode_table_not_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_warncode_table_not_avail() { }
		~CIFast_IFast_ifastdbrkr_err_warncode_table_not_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARNCODE_TABLE_NOT_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("WarnCode table is not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tableau du code d'avertissement n'est pas disponible.")); }

        // Actions
	};
}



