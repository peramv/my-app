#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_num_units_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_num_units_required() { }
		~CIFast_IFast_ifastdbrkr_err_num_units_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NUM_UNITS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Number of Units must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Number of Units must be entered.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nombre d'unités est requis.")); }

        // Actions
	};
}



