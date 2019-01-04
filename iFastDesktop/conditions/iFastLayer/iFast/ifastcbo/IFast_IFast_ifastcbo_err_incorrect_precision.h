#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_incorrect_precision : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_incorrect_precision() { }
		~CIFast_IFast_ifastcbo_err_incorrect_precision() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INCORRECT_PRECISION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Number of decimal places cannot exceed %NUMOFDECIMALS% for %CURRENCY%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le nombre de decimales ne peut pas depasser %NUMOFDECIMALS% pour %CURRENCY%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anzahl der Dezimalstellen kann %NUMOFDECIMALS% bei %CURRENCY% nicht übersteigen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de decimales no puede exceder %NUMOFDECIMALS% para %CURRENCY%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nombre de décimales ne peut être supérieur à %NUMOFDECIMALS% pour %CURRENCY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aantal posities achter de komma mag niet groter zijn dan %NUMOFDECIMALS% voor %CURRENCY%")); }

        // Actions
	};
}



