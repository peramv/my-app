#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_wrong_record_lngth_on_read : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_wrong_record_lngth_on_read() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_wrong_record_lngth_on_read() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_WRONG_RECORD_LNGTH_ON_READ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Language field cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Langue doit être renseignee")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Sprache-Feld darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo de idioma no puede estar en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Langue doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Taalveld mag niet leeg zijn")); }

        // Actions
	};
}



