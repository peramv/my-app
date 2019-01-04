#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_mgmt_co_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_mgmt_co_not_found() { }
		~CBase_Ifds_dita2kdb_dita2kdb_mgmt_co_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_MGMT_CO_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'utilisateur n'est pas autorise a acceder a l'ecran des details de comptes.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assistance technique.")); }
	};
}



