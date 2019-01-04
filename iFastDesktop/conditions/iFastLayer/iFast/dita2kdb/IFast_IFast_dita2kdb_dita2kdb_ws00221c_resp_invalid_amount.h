#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_amount : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_amount() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spouse's birthday must be entered if shareholder's birthday is unknown.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Spouse's birthday must be entered if shareholder's birthday is unknown.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geburtsdatum des Ehepartners muss eingegeben werden, wenn der Geburtstag des Aktionärs unbekannt ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse la fecha de nacimiento del cónyuge si no se conoce la del accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du conjoint est requise si celle de l'actionnaire est inconnue.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum echtgenoot of echtgenote moet worden ingevoerd als de geboortedatum van de aandeelhouder onbekend is")); }

        // Actions
	};
}



