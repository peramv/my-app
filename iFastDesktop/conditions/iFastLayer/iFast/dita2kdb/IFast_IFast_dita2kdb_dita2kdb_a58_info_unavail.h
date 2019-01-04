#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_a58_info_unavail : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_a58_info_unavail() { }
		~CIFast_IFast_dita2kdb_dita2kdb_a58_info_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A58_INFO_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to delete last remaining Address for Shareholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to delete last remaining Address for Shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Letzte bleibende Adresse für Aktionär kann nicht gelöscht werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible eliminar la última dirección que queda para el accionista")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer la dernière adresse restante pour l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verwijderen van het laatste overgebleven adres van aandeelhouder is niet mogelijk")); }

        // Actions
	};
}



