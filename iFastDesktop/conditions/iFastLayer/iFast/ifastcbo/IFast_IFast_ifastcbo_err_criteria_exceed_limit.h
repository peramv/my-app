#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_criteria_exceed_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_criteria_exceed_limit() { }
		~CIFast_IFast_ifastcbo_err_criteria_exceed_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CRITERIA_EXCEED_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The number of criteria entered exceed maximum limit.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Anzahl der eingegebenen Kriterien überschreitet die Maximalgrenze.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de criterios introducidos excede el límite máximo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nombre de critères saisi excède la limite maximale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het aantal ingevoerde criteria overschrijdt het maximum")); }

        // Actions
	};
}



