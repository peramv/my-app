#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_g1_g2_total_not_matching : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_g1_g2_total_not_matching() { }
		~CIFast_IFast_ifastcbo_err_g1_g2_total_not_matching() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("G1_G2_TOTAL_NOT_MATCHING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sum of G1 and G2 units should match with the Total Units of Trade.")); }
        virtual DString GetMessage_FR_CA() const { return DString(I_("Somme de G1 et G2 unités doit correspondre avec les Unités totales du commerce.")); }
        virtual DString GetMessage_FR_FR() const { return DString(I_("Somme de G1 et G2 unités doit correspondre avec les Unités totales du commerce.")); }
        // Actions
	};
}



