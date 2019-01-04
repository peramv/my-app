#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_successful_open_option_file : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_successful_open_option_file() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_successful_open_option_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_SUCCESSFUL_OPEN_OPTION_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An Effective date must be set.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Une date d'effet doit être definie.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Effektivdatum muss festgelegt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse una fecha de entrada en vigencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une date d'entrée en vigueur doit être réglée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet een ingangsdatum zijn ingesteld")); }

        // Actions
	};
}



