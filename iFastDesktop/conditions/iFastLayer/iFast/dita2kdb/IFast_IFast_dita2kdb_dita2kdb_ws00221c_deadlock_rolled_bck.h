#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_deadlock_rolled_bck : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_deadlock_rolled_bck() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_deadlock_rolled_bck() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_DEADLOCK_ROLLED_BCK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Freeing the persitent buffers failed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Freeing the persitent buffers failed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entlastung des permanenten Buffers fehlgeschlagen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fallo la liberación de los búferes persistentes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de libération de la mémoire tampon continue")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Leegmaken van de vaste buffers is mislukt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact technical support.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact technical support.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an den technischen Support.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact technical support.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec le soutien technique.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met de technische dienst")); }
	};
}



