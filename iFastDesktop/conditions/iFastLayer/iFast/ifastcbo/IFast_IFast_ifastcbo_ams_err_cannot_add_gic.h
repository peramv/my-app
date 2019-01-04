#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_err_cannot_add_gic : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_err_cannot_add_gic() { }
		~CIFast_IFast_ifastcbo_ams_err_cannot_add_gic() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_ERR_CANNOT_ADD_GIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot add GIC funds to AMS allocations.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cannot add GIC funds to AMS allocations.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cannot add GIC funds to AMS allocations.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter les fonds CPG aux répartitions de service de gestion de portefeuille.")); }

        // Actions
	};
}



