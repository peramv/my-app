#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_purchase_annuitant_older_than_latest_age : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_purchase_annuitant_older_than_latest_age() { }
		~CIFast_IFast_ifastcbo_warn_purchase_annuitant_older_than_latest_age() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant is older than latest age to open/purchase %CONTRACTAGE% years.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge du crédirentier est supérieur à l'âge maximal de %CONTRACTAGE% ans pour ouvrir/acheter le contrat.")); }

        // Actions
	};
}



