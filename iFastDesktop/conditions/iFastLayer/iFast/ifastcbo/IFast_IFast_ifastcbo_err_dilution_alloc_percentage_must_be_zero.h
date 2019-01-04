#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_must_be_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_must_be_zero() { }
		~CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_must_be_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_ALLOC_PERCENTAGE_MUST_BE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage must be 0. Based on the first record, split factor is based on Responsibility Date")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage doit être de zéro. Selon le premier enregistrement, le facteur de partage repose sur la date de responsabilité.")); }

        // Actions
	};
}



