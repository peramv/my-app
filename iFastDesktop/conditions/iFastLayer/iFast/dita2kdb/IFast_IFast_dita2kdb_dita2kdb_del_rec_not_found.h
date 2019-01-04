#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_del_rec_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_del_rec_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_del_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_DEL_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please send again as last record was deleted.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Please send again as last record was deleted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte erneut senden, da der letzte Eintrag gelöscht wurde")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Por favor vuelva a enviarlo ya que se eliminó el último registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez envoyer à nouveau puisque le dernier enregistrement a été supprimé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wilt u opnieuw versturen, het laatste record werd gewist")); }

        // Actions
	};
}



