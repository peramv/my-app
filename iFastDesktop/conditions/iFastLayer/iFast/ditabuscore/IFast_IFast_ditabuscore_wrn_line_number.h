#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_wrn_line_number : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_wrn_line_number() { }
		~CIFast_IFast_ditabuscore_wrn_line_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WRN_LINE_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 5; }

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



