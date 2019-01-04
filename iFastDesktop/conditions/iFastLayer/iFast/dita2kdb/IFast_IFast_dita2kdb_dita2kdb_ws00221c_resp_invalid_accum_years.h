#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_accum_years : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_accum_years() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_accum_years() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACCUM_YEARS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax jurisdiction cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Juridiction fiscale doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuer-Rechtssprechung darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La jurisdicción tributaria no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Juridiction fiscale doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingrechtsgebied kan niet leeg zijn")); }

        // Actions
	};
}



