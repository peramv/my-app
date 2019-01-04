#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_price : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_price() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_price() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PRICE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There was an internal problem.  An attempt was made to execute invalid code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter darf nicht auf dieses Konto zugreifen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There was an internal problem.  An attempt was made to execute invalid code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a eu un problème interne. Une tentative d'exécution d'un code invalide a été faite.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("There was an internal problem.  An attempt was made to execute invalid code.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact a support representative and report this message.")); }
	};
}



