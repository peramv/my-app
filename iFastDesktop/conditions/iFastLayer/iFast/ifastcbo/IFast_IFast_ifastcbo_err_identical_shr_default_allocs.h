#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_identical_shr_default_allocs : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_identical_shr_default_allocs() { }
		~CIFast_IFast_ifastcbo_err_identical_shr_default_allocs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTICAL_SHR_DEFAULT_ALLOCS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder allocations must differ in allocation type and/or effective date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Shareholder allocations must differ in allocation type and/or effective date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktionär-Zuweisungen müssen sich in Zuweisungstyp und/oder Effektivdatum unterscheiden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las asignaciones de accionistas deben diferir en tipo de asignación y/o fecha de entrada en vigencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les répartitions de l'actionnaire doivent différer en type d'attribution ou en date d'entrée en vigueur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aandeelhoudersallocaties moet verschillend zijn in allocatietype en/of ingangsdatum")); }

        // Actions
	};
}



