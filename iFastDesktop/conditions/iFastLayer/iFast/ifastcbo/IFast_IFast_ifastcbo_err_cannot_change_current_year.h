#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_change_current_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_change_current_year() { }
		~CIFast_IFast_ifastcbo_err_cannot_change_current_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_CHANGE_CURRENT_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Year of the Effective Date cannot be updated. Please setup new record for any other year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'année de la date d'entrée en vigueur ne peut être mise à jour. Veuillez régler un nouvel enregistrement pour nimporte quelle autre année.")); }

        // Actions
	};
}



