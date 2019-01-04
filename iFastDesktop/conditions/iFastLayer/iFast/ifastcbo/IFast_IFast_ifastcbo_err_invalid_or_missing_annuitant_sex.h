#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_or_missing_annuitant_sex : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_or_missing_annuitant_sex() { }
		~CIFast_IFast_ifastcbo_err_invalid_or_missing_annuitant_sex() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_OR_MISSING_ANNUITANT_SEX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid or missing Annuitant Sex.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Invalide ou manquante Rentier Sexe.")); }

        // Actions
	};
}



