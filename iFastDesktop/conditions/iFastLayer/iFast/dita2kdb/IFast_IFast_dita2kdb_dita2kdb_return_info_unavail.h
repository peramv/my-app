#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_return_info_unavail : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_return_info_unavail() { }
		~CIFast_IFast_dita2kdb_dita2kdb_return_info_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_RETURN_INFO_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to delete record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to delete record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht gelöscht werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible eliminar registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer l'enregistrement")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kon niet worden gewist")); }

        // Actions
	};
}



