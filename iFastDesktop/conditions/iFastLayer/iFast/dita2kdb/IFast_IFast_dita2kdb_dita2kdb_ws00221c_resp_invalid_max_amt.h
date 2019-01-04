#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_max_amt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_max_amt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_max_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_MAX_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Birthdate cannot be after today.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Birthdate cannot be after today.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geburtsdatum darf nicht nach dem heutigen Datum liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de nacimiento no puede ser posterior a la de hoy.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance ne peut être postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum mag niet later zijn dan vandaag")); }

        // Actions
	};
}



