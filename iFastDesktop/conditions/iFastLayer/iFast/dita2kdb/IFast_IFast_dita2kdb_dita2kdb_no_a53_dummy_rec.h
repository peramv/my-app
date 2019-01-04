#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_no_a53_dummy_rec : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_no_a53_dummy_rec() { }
		~CIFast_IFast_dita2kdb_dita2kdb_no_a53_dummy_rec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_A53_DUMMY_REC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid fund code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid fund code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Fondscode")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de fondo no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de fonds invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige fondscode")); }

        // Actions
	};
}



