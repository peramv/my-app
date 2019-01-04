#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ordertype_wire : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ordertype_wire() { }
		~CIFast_IFast_ifastcbo_warn_ordertype_wire() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ORDERTYPE_WIRE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Order type should be wire for participant transfers.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'ordre devrait être électronique pour les transferts de participants.")); }

        // Actions
	};
}



