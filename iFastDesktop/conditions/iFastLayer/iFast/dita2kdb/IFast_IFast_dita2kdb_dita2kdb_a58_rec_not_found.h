#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_a58_rec_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_a58_rec_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_a58_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A58_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Next Key did not match expected format.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Next Key did not match expected format.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nächster Schlüssel passte nicht zum erwarteten Format")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La clave siguiente no coincidió con el formato esperado")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La prochaine clé de correspondait pas au format escompté.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volgende sleutel komt niet overeen met de verwachte indeling")); }

        // Actions
	};
}



