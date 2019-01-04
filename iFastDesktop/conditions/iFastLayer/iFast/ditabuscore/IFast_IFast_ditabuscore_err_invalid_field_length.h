#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_invalid_field_length : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_invalid_field_length() { }
		~CIFast_IFast_ditabuscore_err_invalid_field_length() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FIELD_LENGTH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown System Identification/Management Company.  (%MSG%).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%MSG% is an unknown System/Management Company.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%MSG% ist ein unbekanntes System / Management-Unternehmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%MSG% es un sistema o compañía administradora desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Identification de système/d'environnement inconnue (%MSG%)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%MSG% is een onbekend systeem of beheerbedrijf")); }

        // Actions
	};
}



