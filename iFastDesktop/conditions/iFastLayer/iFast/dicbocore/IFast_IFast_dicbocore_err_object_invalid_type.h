#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_object_invalid_type : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_object_invalid_type() { }
		~CIFast_IFast_dicbocore_err_object_invalid_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_INVALID_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUNDNAME% is not RRSP eligible - cannot set up systematic for this RSP account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FUNDNAME% is not RRSP eligible - cannot set up systematic for this RSP account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FUNDNAME% ist nicht RRSP-geeignet – Systematic für dieses RSP-Konto kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El %FUNDNAME% no es apto para RRSP - No se puede configurar un plan sistemático para esta cuenta RSP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FUNDNAME% n'est pas admissible au REER – la systématique ne peut être réglée pour ce compte RER.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FUNDNAME% komt niet in aanmerking voor RRSP - systeemplan voor dit RSP-account kan niet worden ingesteld")); }

        // Actions
	};
}



