#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tfsa_deceased_annuitant_dod_updated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tfsa_deceased_annuitant_dod_updated() { }
		~CIFast_IFast_ifastcbo_warn_tfsa_deceased_annuitant_dod_updated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TFSA_DECEASED_ANNUITANT_DOD_UPDATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is change on Deceased Annuitant's date of death.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de décès du crédirentier décédé a été modifiée.")); }

        // Actions
	};
}



