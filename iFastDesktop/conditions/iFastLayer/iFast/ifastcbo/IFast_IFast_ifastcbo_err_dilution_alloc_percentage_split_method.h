#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_split_method : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_split_method() { }
		~CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_split_method() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_ALLOC_PERCENTAGE_SPLIT_METHOD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Enter Percentage or modify all records to contain only Responsibility Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Saisissez un pourcentage ou modifiez tous les enregistrements afin qu'ils ne comportent que la date de responsabilité.")); }

        // Actions
	};
}



