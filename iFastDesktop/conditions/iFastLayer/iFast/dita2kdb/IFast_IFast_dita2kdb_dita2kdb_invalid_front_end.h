#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_front_end : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_front_end() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_front_end() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_FRONT_END")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid profile.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Profil invalide")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Profil")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Perfil no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Profil invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig profiel")); }

        // Actions
	};
}



