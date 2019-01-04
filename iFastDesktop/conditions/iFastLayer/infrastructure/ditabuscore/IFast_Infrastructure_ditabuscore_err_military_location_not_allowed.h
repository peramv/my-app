#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_military_location_not_allowed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_military_location_not_allowed() { }
		~CIFast_Infrastructure_ditabuscore_err_military_location_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MILITARY_LOCATION_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
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



