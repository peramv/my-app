#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitant_sin_not_the_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitant_sin_not_the_same() { }
		~CIFast_IFast_ifastcbo_err_annuitant_sin_not_the_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_SIN_NOT_THE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant's SIN of both side are not the same.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les deux NAS ne sont pas les mêmes.")); }

        // Actions
	};
}



