#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_no_a56_rec_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_no_a56_rec_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_no_a56_rec_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_A56_REC_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Clan Plan not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Clan Plan not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Clanplan nicht verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Clan Plan no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun régime de clan disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Clan Plan is niet beschikbaar")); }

        // Actions
	};
}



