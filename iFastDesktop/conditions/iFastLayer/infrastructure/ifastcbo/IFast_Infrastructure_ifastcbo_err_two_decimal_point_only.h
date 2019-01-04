#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_two_decimal_point_only : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_two_decimal_point_only() { }
		~CIFast_Infrastructure_ifastcbo_err_two_decimal_point_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TWO_DECIMAL_POINT_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Military location code is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Military location code is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Militärstationierungscode ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el código de destacamento militar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de localisation militaire n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Code voor militaire locatie is niet toegestaan")); }

        // Actions
	};
}



