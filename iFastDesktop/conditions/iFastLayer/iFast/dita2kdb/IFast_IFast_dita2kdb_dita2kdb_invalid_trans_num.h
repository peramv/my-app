#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_trans_num : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_trans_num() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_trans_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_TRANS_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - No company access.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Aucun acces a la societe")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Kein Unternehmens-Zugriff")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - No tiene acceso a la compañía")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – aucun accès d'entreprise")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Geen bedrijfstoegang")); }

        // Actions
	};
}



