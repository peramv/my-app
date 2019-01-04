#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_field_mustbe_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_field_mustbe_empty() { }
		~CIFast_IFast_ditabuscore_err_field_mustbe_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_MUSTBE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation percentages must sum up to 100%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocation percentages must sum up to 100%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zuweisungs-Prozentsätze müssen 100% ergeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los porcentajes asignados deben sumar 100%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les pourcentages de répartition doivent totaliser 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Allocatiepercentages moeten in totaal 100% zijn")); }

        // Actions
	};
}



