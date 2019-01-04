#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_fld_not_validated : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_fld_not_validated() { }
		~CIFast_IFast_dicbocore_err_fld_not_validated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FLD_NOT_VALIDATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUNDNAME% is not RRIF eligible - cannot set up systematic for this RIF account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FUNDNAME% is not RRIF eligible - cannot set up systematic for this RIF account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FUNDNAME% ist nicht RRIF-geeignet – Systematic für dieses RIF-Konto kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El %FUNDNAME% no es apto para RRIF - No se puede configurar un plan sistemático para esta cuenta RIF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%FUNDNAME% n'est pas admissible au FERR – la systématique ne peut être réglée pour ce compte FRR.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FUNDNAME% komt niet in aanmerking voor RRIF - systeemplan voor dit RIF-account kan niet worden ingesteld")); }

        // Actions
	};
}



