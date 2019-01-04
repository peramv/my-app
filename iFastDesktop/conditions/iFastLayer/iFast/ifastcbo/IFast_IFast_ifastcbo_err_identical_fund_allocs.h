#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_identical_fund_allocs : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_identical_fund_allocs() { }
		~CIFast_IFast_ifastcbo_err_identical_fund_allocs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTICAL_FUND_ALLOCS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund allocations must differ in fund/class combination.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund allocations must differ in fund/class combination.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds-Zuweisungen müssen sich in der Fonds/Klassen-Kombination unterscheiden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las asignaciones de fondos deben diferir en combinación de fondo/clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La répartition des fonds doit s'effectuer dans des fonds/classes différent(e)s.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondsallocaties moeten verschillend zijn in fonds/categoriecombinatie")); }

        // Actions
	};
}



