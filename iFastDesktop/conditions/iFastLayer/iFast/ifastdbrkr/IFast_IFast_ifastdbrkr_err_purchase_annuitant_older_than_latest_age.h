#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_purchase_annuitant_older_than_latest_age : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_purchase_annuitant_older_than_latest_age() { }
		~CIFast_IFast_ifastdbrkr_err_purchase_annuitant_older_than_latest_age() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant is older than the latest age to open/purchase selected contract.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge du crédirentier est supérieur à l'âge maximal pour ouvrir/acheter le contrat sélectionné.")); }

        // Actions
	};
}



