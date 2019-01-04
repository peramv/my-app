#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_severe_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_severe_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_severe_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SEVERE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Forms already loaded.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Forms already loaded.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Formulare sind bereits geladen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los formularios ya están cargados.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les formulaires ont déjà été téléchargés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Formulieren zijn al geladen")); }

        // Actions
	};
}



