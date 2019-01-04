#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tup_tolerance_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tup_tolerance_units() { }
		~CIFast_IFast_ifastcbo_warn_tup_tolerance_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TUP_TOLERANCE_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The estimated traded unit position tolerance level for the account fund class is %TOLUNITS% units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le niveau de tolérance de la position estimée de l'unité échangée pour la classe de fonds du compte est %TOLUNITS% unités.")); }

        // Actions
	};
}



